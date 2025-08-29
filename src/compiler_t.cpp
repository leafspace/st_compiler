#include <deci.hpp>
#include <deci/scanner_t.hpp>
#include "iec61131.y.hpp"

#include <sstream>
#include <map>

namespace deci
{
compiler_t::compiler_t(void)
{
	this->initialize();
}

compiler_t::compiler_t(std::string& strName, std::istream& input, bool bInteractive)
{
	this->SetSource(strName, input, bInteractive);
}

compiler_t::compiler_t(std::string& strName, std::string& input, bool bInteractive)
{
	this->SetSource(strName, input, bInteractive);
}

compiler_t::~compiler_t(void)
{
	this->initialize();
}

void compiler_t::SetMode(compiler_mode nMode)
{
	m_nCompilerMode = nMode;
}

void compiler_t::SetSource(std::string& strName, std::istream& input, bool bInteractive)
{
	this->initialize();
	m_sourceString = strName;
	m_pSourceStream = &input;
	m_bInteractive = bInteractive;
}

void compiler_t::SetSource(std::string& strName, std::string& input, bool bInteractive)
{
	this->initialize();
	m_sourceName = strName;
	m_sourceString = input;
	m_bInteractive = bInteractive;
}

void compiler_t::SetOuterVariant(variant_table& table)
{
	m_outerIdentifierTable = table;
}

void compiler_t::SetCheckCtrlIsCondition(bool isCondition)
{
	m_checkCtrl.SetIsCondition(isCondition);

	if (m_sourceString.size() != 0)
	{
		for (int i = m_sourceString.size() - 1; i >= 0; i--) 
		{
			if (m_sourceString[i] == ' ') 
			{
				continue;
			}

			if (m_sourceString[i] != ';')
			{
				m_sourceString = m_sourceString.substr(0, i + 1) + ";";
			}

			break;
		}
	}
}

std::vector<SyntaxError> compiler_t::GetSyntaxErrors(void)
{
	return m_syntaxErrors;
}

std::vector<SyntaxError> compiler_t::GetSemanticErrors(void)
{
	return m_semanticErrors;
}

std::vector<SyntaxError> compiler_t::GetErrors(void)
{
	std::vector<SyntaxError> refErrors;
	refErrors.insert(refErrors.end(), m_syntaxErrors.begin(), m_syntaxErrors.end());
	refErrors.insert(refErrors.end(), m_semanticErrors.begin(), m_semanticErrors.end());

	auto compare = [](SyntaxError& aError, SyntaxError& bError) -> bool 
	{ 
		if (aError.beginLine != bError.beginLine)
		{
			return aError.beginLine < bError.beginLine;
		}
		else if (aError.beginColumn != bError.beginColumn)
		{
			return aError.beginColumn < bError.beginColumn;
		}
		else if (aError.endLine != bError.endLine)
		{
			return aError.endLine < bError.endLine;
		}
		else if (aError.endColumn != bError.endColumn)
		{
			return aError.endColumn < bError.endColumn;
		}
		return true;
	};
	std::sort(refErrors.begin(), refErrors.end(), compare);
	return refErrors;
}

bool compiler_t::SyntaxCheck(void)
{
	std::queue<AstSymbolType> queueType;

	this->SyntaxInitalize();
	this->CreateSyntaxTree();
	m_syntaxTree->SyntaxCheck(queueType, 
		ast_symbol_table(this->m_innerIdentifierTable + this->m_outerIdentifierTable, this->m_innerFunctionTable), m_checkCtrl);

	std::vector<SyntaxError> astErrors = m_syntaxTree->GetSyntaxErrors();
	m_semanticErrors.insert(m_semanticErrors.end(), astErrors.begin(), astErrors.end());

	std::vector<symbol> identifiers = m_syntaxTree->GetIdentifiers();
	m_usedIdentifierTable.AddSymbol(identifiers);

	this->SyntaxCheckDeclare();
	this->SyntaxCheckIdentifierType();
	//this->SyntaxCheckUniqueness();

	this->FillSyntaxErrorMsg();

	return this->IsCompiled();
}

std::string compiler_t::SyntaxTranslation(void)
{
	std::string translation;
	ast_symbol_table table(m_innerIdentifierTable + m_outerIdentifierTable, m_innerFunctionTable);

	m_syntaxTree->Translation(translation, 0, table);

	std::string source = "\n\n";
	std::string target = "\n";
	std::string::size_type nPos = 0;
	std::string::size_type sourceSize = source.size();
	while ((nPos = translation.find("\n\n")) != std::string::npos)
	{
		translation.replace(nPos, sourceSize, target);
	}
	return translation;
}

bool compiler_t::IsCompiled(void)
{
	switch (m_nCompilerMode)
	{
	case compiler_mode::normal:
	{
		int nErrorCount = 0;
		int nWarningCount = 0;
		std::vector<SyntaxError> errors;
		errors.insert(errors.end(), m_syntaxErrors.begin(), m_syntaxErrors.end());
		errors.insert(errors.end(), m_semanticErrors.begin(), m_semanticErrors.end());

		for (auto iter : errors)
		{
			if (iter.type < SyntaxType::SyntaxWarning_End
				&& iter.type > SyntaxType::SyntaxWarning_Begin)
			{
				nWarningCount++;
			}
			else
			{
				nErrorCount++;
			}
		}

		return nErrorCount == 0;
	}
		break;
	case compiler_mode::strict:
		return !(m_syntaxErrors.size() != 0 || m_semanticErrors.size() != 0);
		break;
	default:
		break;
	}
	return true;
}

void compiler_t::PrintSyntaxError(std::vector<SyntaxError>& errors)
{
	for (auto iter : errors)
	{
		std::cout 
			<< std::setw(3) << iter.beginLine << "."
			<< std::setw(3) << iter.beginColumn << ":"
			<< std::setw(3) << iter.endLine << "."
			<< std::setw(3) << iter.endColumn << " ["
			<< std::setw(2) << (int)iter.type << "] "
			<< iter.GetType() << ": " 
			<< iter.msg << std::endl;
	}
}

void compiler_t::initialize(void)
{
	this->SyntaxInitalize();
	this->FunctionInitalize();

	m_outerIdentifierTable.clear();

	m_nCompilerMode = compiler_mode::normal;
	m_sourceName = "";
	m_sourceString = "";
	m_pSourceStream = nullptr;
	m_bInteractive = false;

	m_syntaxTree.reset();
}

void compiler_t::SyntaxInitalize(void)
{
	m_syntaxErrors.clear();
	m_semanticErrors.clear();
	m_innerIdentifierTable.clear();
	m_usedIdentifierTable.clear();
}

void compiler_t::FunctionInitalize(void)
{
	m_innerFunctionTable.clear();

	// 填充内置函数
	m_innerFunctionTable.AddFunction(symbol("TIMERS"),
		std::vector<symbol>{symbol(AstSymbolType::AstSymbolType_UNUSE), symbol(AstSymbolType::AstSymbolType_UDINT)},
		std::string("Sleep"));
}

void compiler_t::CreateSyntaxTree(void)
{
	std::shared_ptr<ast_t> ast(new ast_t());
	if (m_pSourceStream != nullptr)
	{
		deci_scanner_t scanner(*m_pSourceStream, m_sourceName, m_bInteractive);
		parser_t parser(scanner, ast, m_syntaxErrors, m_usedIdentifierTable);
		parser.parse();
	}
	else
	{
		deci_scanner_t scanner(m_sourceString, m_bInteractive);
		parser_t parser(scanner, ast, m_syntaxErrors, m_usedIdentifierTable);
		parser.parse();
	}
	m_syntaxTree = ast;
}

void compiler_t::SyntaxCheckDeclare(void)
{
	std::vector<SyntaxError> syntaxErrors;

	std::map<std::string, std::vector<symbol>> params;          // 定义的标识符
	std::map<std::string, std::vector<symbol>> identifierMap;   // 使用的标识符

	std::map<std::string, std::vector<symbol>> innerIdentifierParams;
	std::map<std::string, std::vector<symbol>> outerIdentifierParams;
	std::map<std::string, std::vector<symbol>> innerFunctionParams;

	innerIdentifierParams = this->m_innerIdentifierTable.GetSymbolMap();
	outerIdentifierParams = this->m_outerIdentifierTable.GetSymbolMap();
	innerFunctionParams = this->m_innerFunctionTable.GetSymbolMap();

	identifierMap = this->m_usedIdentifierTable.GetSymbolMap();
	params.insert(innerIdentifierParams.begin(), innerIdentifierParams.end());
	params.insert(outerIdentifierParams.begin(), outerIdentifierParams.end());
	params.insert(innerFunctionParams.begin(), innerFunctionParams.end());

	for (auto iter = identifierMap.begin();
		iter != identifierMap.end();)
	{
		if (params.find(iter->first) != params.end())
		{
			std::string key = iter->first;
			identifierMap.erase(iter++);
			params.erase(key);
		}
		else
		{
			std::vector<symbol> symbols = iter->second;

			for (symbol& symbol : symbols)
			{
				SyntaxError error(symbol.GetLocation(), deci::SyntaxType::SyntaxError_Declaration);
				error.msg = "未定义的标识符 " + iter->first;
				syntaxErrors.push_back(error);
			}

			iter++;
		}
	}

	for (auto iter = params.begin();
		iter != params.end(); iter++)
	{
		if (innerFunctionParams.find(iter->first) == innerFunctionParams.end())
		{
			SyntaxError error(deci::SyntaxType::SyntaxWarning_UnuseParam);
			error.msg = "未使用的标识符 " + iter->first;
			syntaxErrors.push_back(error);
		}
	}

	m_semanticErrors.insert(m_semanticErrors.end(), syntaxErrors.begin(), syntaxErrors.end());
}

void compiler_t::SyntaxCheckIdentifierType(void)
{
	// TODO: 

}

void compiler_t::FillSyntaxErrorMsg(void)
{
	for (std::vector<SyntaxError>::iterator iter = m_syntaxErrors.begin();
		iter != m_syntaxErrors.end(); ++iter)
	{
		iter->FillErrorMsg();
	}

	for (std::vector<SyntaxError>::iterator iter = m_semanticErrors.begin();
		iter != m_semanticErrors.end(); ++iter)
	{
		iter->FillErrorMsg();
	}
}

} // namespace deci
