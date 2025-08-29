#include <deci/ast_t.hpp>
#include "iec61131.y.hpp"

#include <regex>

#define CLEAN_RELEASE(x) \
	if (x != nullptr) { delete x; } x = nullptr;
#define RECURVE_TRANSLATION(refStr, level, iter, param) \
	if (iter != nullptr) { \
		iter->Translation(refStr, level, param); \
	}
#define RECURVE_SYNTAXERROR(e, me, iter) \
	if (iter != nullptr) { \
		e = iter->GetSyntaxErrors(); me.insert(me.end(), e.begin(), e.end()); \
	}
#define RECURVE_IDENTIFIER(i, mi, iter) \
	if (iter != nullptr) { \
		i = iter->GetIdentifiers(); mi.insert(mi.end(), i.begin(), i.end()); \
	}

namespace deci {

void ast_symbol_table::SplitVariantAndConstant(symbol_table& table)
{
	variant_table variant;
	constant_table constant;
	std::map<std::string, std::vector<symbol>> symbolMap = table.GetSymbolMap();
	
	for (auto iter = symbolMap.begin();
		iter != symbolMap.end(); ++iter)
	{
		if (iter->second.size() != 0 && iter->second.at(0).GetRWType() == symbol_rw::symbol_read)
		{
			constant.AddSymbol(iter->second);
		}

		if (iter->second.size() != 0 && iter->second.at(0).GetRWType() == symbol_rw::symbol_readwrite)
		{
			variant.AddSymbol(iter->second);
		}
	}

	m_variant = m_variant + variant;
	m_constant = m_constant + constant;
}

ast_symbol_table::ast_symbol_table(void)
{
	m_variant.clear();
	m_function.clear();
}

ast_symbol_table::ast_symbol_table(const symbol_table& variant, const function_table& function)
{
	m_function = function;
	SplitVariantAndConstant((symbol_table&)variant);
}

ast_symbol_table::ast_symbol_table(const symbol_table& variant, const symbol_table& constant, const function_table& function)
{
	m_constant = constant;
	m_function = function;
	SplitVariantAndConstant((symbol_table&)variant);
}

ast_symbol_table::~ast_symbol_table(void)
{
	m_variant.clear();
	m_function.clear();
}

void ast_symbol_table::SetVariant(const symbol_table& variant)
{
	m_variant = variant;
}

void ast_symbol_table::SetConstant(const symbol_table& constant)
{
	m_constant = constant;
}

void ast_symbol_table::SetFunction(const function_table& function)
{
	m_function = function;
}

symbol_table ast_symbol_table::GetVariant(void) const
{
	return m_variant;
}

symbol_table ast_symbol_table::GetConstant(void) const
{
	return m_constant;
}

function_table ast_symbol_table::GetFunction(void) const
{
	return m_function;
}


void ast_check_ctrl::SetIsCondition(const bool bCondition)
{
	m_bConditon = bCondition;
}

bool ast_check_ctrl::GetIsCondition(void)
{
	return m_bConditon;
}

void ast_item_t::init()
{
	// 递归访问的，不能删除父节点(m_pParent)
	this->m_pParent = nullptr;
	this->m_nType = parser_t::symbol_kind::YYNTOKENS;
	this->m_errors.clear();
	this->m_locations.clear();
	this->m_identifierLocation.initialize();
}

std::string ast_item_t::GetIndent(int nCount)
{
	std::string strIndent;
	while (nCount > 0)
	{
		strIndent += "    ";
		nCount--;
	}
	return strIndent;
}

int ast_item_t::Translation(std::string&, int nDeepLevel, ast_symbol_table&) const
{
	return nDeepLevel;
}

int ast_item_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table&, ast_check_ctrl&)
{
	queueType.push(AstSymbolType::AstSymbolType_UNUSE);
	return 0;
}

int ast_item_t::GetType(void) const
{
	return this->m_nType;
}

std::string ast_item_t::GetValue(void) const
{
	return std::string();
}

std::vector<symbol> ast_item_t::GetIdentifiers(void)
{
	return std::vector<symbol>();
}

std::vector<SyntaxError> ast_item_t::GetSyntaxErrors(void)
{
	return this->m_errors;
}

void ast_item_t::SetLocations(std::vector<location> locations)
{
	this->m_locations = locations;
}

void ast_item_t::SetIdentifierLocation(location& location)
{
	this->m_identifierLocation = location;
}

location ast_item_t::GetLocation(void)
{
	location refLocation;

	if (this->m_locations.size() != 0)
	{
		refLocation.begin = this->m_locations[0].begin;
		refLocation.end = this->m_locations[this->m_locations.size() - 1].end;
	}

	return refLocation;
}

location ast_item_t::GetIdentifierLocation(void)
{
	return this->m_identifierLocation;
}

ast_item_t::ast_item_t()
{
	this->init();
}

ast_item_t::~ast_item_t()
{
	this->init();
}

void ast_t::init()
{
	for (ast_item_t* iter : this->m_statements)
	{
		CLEAN_RELEASE(iter);
	}
	this->m_statements.clear();
	this->m_nType = parser_t::symbol_kind::S_statement_list;
}

void ast_t::Append(ast_item_t* item)
{
	this->m_statements.push_back(item);
}

std::vector<ast_item_t*> ast_t::GetStatements(void)
{
	return this->m_statements;
}

int ast_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	for (auto item : this->m_statements) {
		std::string strStmt;
		RECURVE_TRANSLATION(strStmt, nDeepLevel, item, table);
		output = output + strStmt + "\n";
	}
	return nDeepLevel;
}

int ast_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;

	if (control.GetIsCondition() && this->m_statements.size() != 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_ShouldOnlyOne);
		this->m_errors.push_back(error);
	}

	for (auto item : this->m_statements) {
		nErrorSum += item->SyntaxCheck(queueType, table, control);
		RECURVE_SYNTAXERROR(errors, this->m_errors, item);
	}

	queueType.push(AstSymbolType::AstSymbolType_UNUSE);
	return nErrorSum;
}

std::vector<symbol> ast_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	for (auto item : this->m_statements) {
		RECURVE_IDENTIFIER(identifiertemp, identifiers, item);
	}

	return identifiers;
}

ast_t::ast_t()
{
	this->init();
}

ast_t::~ast_t()
{
	this->init();
}

int ast_boolean_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table&) const
{
	if (this->value)
	{
		output = output + "true";
	}
	else
	{
		output = output + "false";
	}
	return nDeepLevel;
}

int ast_boolean_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table&, ast_check_ctrl&)
{
	queueType.push(AstSymbolType::AstSymbolType_BOOL);
	return 0;
}

std::string ast_boolean_t::GetValue(void) const
{
	return this->value ? "TRUE" : "FALSE";
}

ast_boolean_t::ast_boolean_t(bool value) :value(value)
{
}

ast_boolean_t::~ast_boolean_t()
{
}

void ast_number_t::init(void)
{
	this->m_dbValue = 0;
	this->m_strValue = "";
}

SyntaxType ast_number_t::SyntaxCheckBasalStrValueValid(ast_basal_number& number) const
{
	SyntaxType errorType = SyntaxType::SyntaxError_None;

	// 根据‘#’所在的位置，取出底数值与数据值
	int nHex = atoi(this->m_strValue.substr(0, this->m_strValue.find('#')).c_str());
	std::string strValue = this->m_strValue.substr(this->m_strValue.find('#') + 1);

	// number 中的数值要去除下划线
	while (strValue.find("_") != std::string::npos)
	{
		strValue.replace(strValue.find("_"), 1, "");
	}

	// 指数的范围在[0,35] 即 ['0', 'Z']
	if (nHex > 35 || nHex < 0)
	{
		errorType = SyntaxType::SyntexError_NumberBasal;
		goto ERROR_REF;
	}

	char cHex = nHex >= 10 ? (char)((nHex - 10) + 'A') : (char)(nHex + '0');

	// 字符范围必须在指数范围内
	for (std::string::iterator iter = strValue.begin();
		iter != strValue.end(); ++iter)
	{
		*iter = (char)toupper(*iter);
		if (*iter >= cHex)
		{
			errorType = SyntaxType::SyntexError_NumberBasal;
			goto ERROR_REF;
		}
	}

ERROR_REF:

	number.m_nHex = nHex;
	number.m_strValue = strValue;

	return errorType;
}

SyntaxType ast_number_t::SyntaxCheckTypeStrValueValid(ast_type_number& number) const
{
	SyntaxType errorType = SyntaxType::SyntaxError_None;
	// 根据‘#’所在的位置，取出类型值与数据值
	number.m_strType = this->m_strValue.substr(0, this->m_strValue.find('#'));
	std::string strValue = this->m_strValue.substr(this->m_strValue.find('#') + 1);

	for (std::string::iterator iter = number.m_strType.begin();
		iter != number.m_strType.end(); ++iter)
	{
		*iter = (char)toupper(*iter);
	}

	std::string strSymbol = "";
	if (*strValue.begin() == '+' || *strValue.begin() == '-')
	{
		strSymbol = *strValue.begin();
		strValue = strValue.substr(1);
	}

	// 将字符串转为数值
	number.m_dbValue = atof(strValue.c_str());
	if (strSymbol == "-")
	{
		number.m_dbValue = -1 * number.m_dbValue;
		if (number.m_strType == ASTSYMBOL_TYPE_USINT ||
			number.m_strType == ASTSYMBOL_TYPE_UINT ||
			number.m_strType == ASTSYMBOL_TYPE_UDINT)
		{
			errorType = SyntaxType::SyntaxWarning_NumberChange;
		}
	}

	return errorType;
}

int ast_number_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table&) const
{
	output = output + this->GetValue();
	return nDeepLevel;
}

int ast_number_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table&, ast_check_ctrl&)
{
	std::vector<SyntaxError> errors;

	// 基底数数值正则表达式
	//const std::string strBasalRegex = "[0-9]+\\#({[A-Z]}|_({[A-Z]}|{[0-9]}))(_?({[A-Z]}|{[0-9]}))*";
	// 数据类型数值正则表达式
	//const std::string strTypeRegex = "(SINT|INT|DINT|USINT|UINT|UDINT|REAL)\\#(\\-|\\+)?[0-9]+(\\.)?[0-9]*";

	ast_basal_number basalNumber;
	ast_type_number typeNumber;

	// 检查数据类型是否符合语法要求
	if (this->m_strValue.size() != 0)
	{
		// 初步检查, 使用正则表达式简单检查是否符合基本规则
		//if (std::regex_match(this->m_strValue, 
		//	std::regex(strBasalRegex, std::regex_constants::grep | std::regex_constants::icase)))
		if (isdigit(*this->m_strValue.begin()))
		{
			SyntaxType errorType = this->SyntaxCheckBasalStrValueValid(basalNumber);
			if (errorType != SyntaxType::SyntaxError_None)
			{
				SyntaxError error(this->GetLocation(), errorType);
				errors.push_back(error);
			}
			else
			{
				// 将正确的基底数数值字符串转化为十进制数值类型
				this->m_dbValue = basalNumber.ConvertValue();
			}

			queueType.push(AstSymbolType::AstSymbolType_DINT);
		}

		// 初步检查, 使用正则表达式简单检查是否符合基本规则
		//if (std::regex_match(this->m_strValue, 
		//	std::regex(strTypeRegex, std::regex_constants::grep | std::regex_constants::icase)))
		if (isalpha(*this->m_strValue.begin()))
		{
			SyntaxType errorType = this->SyntaxCheckTypeStrValueValid(typeNumber);
			if (errorType != SyntaxType::SyntaxError_None)
			{
				SyntaxError error(this->GetLocation(), errorType);
				errors.push_back(error);
			}
			else
			{
				// 将正确的数据类型数值转化为十进制数值类型
				this->m_dbValue = typeNumber.ConvertValue();
			}

			if (AST_SYMBOL_MAP.find(typeNumber.m_strType) != AST_SYMBOL_MAP.end())
			{
				queueType.push(AST_SYMBOL_MAP.at(typeNumber.m_strType));
			}
			else
			{
				queueType.push(AstSymbolType::AstSymbolType_UNKNOWN);
			}
		}
	}
	else
	{
		queueType.push(AstSymbolType::AstSymbolType_REAL);
	}

	this->m_errors.clear();
	this->m_errors = errors;
	return errors.size();
}

std::string ast_number_t::GetValue(void) const
{
	return std::to_string(this->m_dbValue);
}

ast_number_t::ast_number_t(double value)
{
	this->init();
	this->m_dbValue = value;
	m_nType = parser_t::symbol_kind::S_NUMBER;
}

ast_number_t::ast_number_t(std::string& value)
	:m_strValue(value)
{
	this->init();
	this->m_strValue = value;
	m_nType = parser_t::symbol_kind::S_NUMBER;
}

ast_number_t::~ast_number_t()
{
}

symbol_rw ast_identifier_t::GetIdentifierRWType(void)
{
	switch (m_nIdentifierType)
	{
	case Identifier_Type::Identifier_Function:
	case Identifier_Type::Identifier_Constant:
		return symbol_rw::symbol_read;
		break;
	case Identifier_Type::Identifier_Variant:
	default:
		return symbol_rw::symbol_readwrite;
		break;
	}
	return symbol_rw();
}

int ast_identifier_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table&) const
{
	output = output + this->value;
	return nDeepLevel;
}

int ast_identifier_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl&)
{
	// 根据Identifier的类型到table找到数据类型
	switch (m_nIdentifierType)
	{
	case Identifier_Type::Identifier_Function:
	{
		std::vector<symbol> argumentes = table.GetFunction().GetArguments(this->value);
		if (table.GetFunction().GetSymbol(this->value).size() == 0)
		{
			queueType.push(AstSymbolType::AstSymbolType_UNKNOWN);
			break;
		}

		queueType.push(AstSymbolType::AstSymbolType_UNUSE);
		if (argumentes.size() != 0)
		{
			queueType.push(argumentes.at(0).GetType());
		}
	}
		break;
	case Identifier_Type::Identifier_Constant:
	case Identifier_Type::Identifier_Variant:
	{
		std::vector<symbol> variantSymbols = table.GetVariant().GetSymbol(this->value);
		std::vector<symbol> constantSymbols = table.GetConstant().GetSymbol(this->value);
		if (variantSymbols.size() == 0 && constantSymbols.size() == 0 ||
			variantSymbols.size() != 0 && constantSymbols.size() != 0)
		{
			queueType.push(AstSymbolType::AstSymbolType_UNKNOWN);
			break;
		}

		if (variantSymbols.size() != 0)
		{
			this->m_nIdentifierType = Identifier_Type::Identifier_Variant;
			queueType.push(variantSymbols.at(0).GetType());
		}
		
		if (constantSymbols.size() != 0)
		{
			this->m_nIdentifierType = Identifier_Type::Identifier_Constant;
			queueType.push(constantSymbols.at(0).GetType());
		}
	}
		break;
	default:
		queueType.push(AstSymbolType::AstSymbolType_UNKNOWN);
		break;
	}

	return 0;
}

std::string ast_identifier_t::GetValue(void) const
{
	return this->value;
}

std::vector<symbol> ast_identifier_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers = { symbol(this->value, this->GetIdentifierLocation()) };
	return identifiers;
}

ast_identifier_t::ast_identifier_t(const std::string& value) :value(value)
{
	m_nType = parser_t::symbol_kind::S_IDENTIFIER;
	m_nIdentifierType = Identifier_Type::Identifier_Variant;
}

ast_identifier_t::ast_identifier_t(const std::string& value, const Identifier_Type type) :value(value)
{
	m_nType = parser_t::symbol_kind::S_IDENTIFIER;
	m_nIdentifierType = type;
}

ast_identifier_t::~ast_identifier_t()
{
}

void ast_arg_list_t::init()
{
	for (ast_item_t* iter : this->args)
	{
		CLEAN_RELEASE(iter);
	}
	this->m_nType = parser_t::symbol_kind::S_statement_list;
	this->args.clear();
}

void ast_arg_list_t::Append(ast_item_t* item)
{
	this->args.push_back(item);
}

int ast_arg_list_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	for (auto iter = this->args.begin();
		iter != this->args.end(); )
	{
		std::string strAst;
		(*iter)->Translation(strAst, nDeepLevel, table);

		output = output + strAst;
		if (++iter != this->args.end())
		{
			output = output + ",";
		}
	}
	return 0;
}

int ast_arg_list_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;

	for (auto item : args) {
		nErrorSum += item->SyntaxCheck(types, table, control);
		RECURVE_SYNTAXERROR(errors, this->m_errors, item);
		queueType.push(types.front());
	}

	return nErrorSum;
}

std::vector<symbol> ast_arg_list_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	for (auto item : args) {
		RECURVE_IDENTIFIER(identifiertemp, identifiers, item);
	}

	return identifiers;
}

ast_arg_list_t::ast_arg_list_t()
{
	this->init();
}

ast_arg_list_t::~ast_arg_list_t()
{
	this->init();
}

void ast_postfix_t::init()
{
	CLEAN_RELEASE(this->arglist);
	CLEAN_RELEASE(this->identifier);
}

int ast_postfix_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strArgs;
	std::string strIdentifier = this->identifier->GetValue();

	RECURVE_TRANSLATION(strArgs, nDeepLevel, this->arglist, table);

	// ST内置函数改为C++系统函数
	std::string coverIdentifier = table.GetFunction().GetCoverIdentifier(strIdentifier);
	if (coverIdentifier.size() != 0)
	{
		strIdentifier = coverIdentifier;
	}

	output = output + this->GetIndent(nDeepLevel) + strIdentifier + "(" + strArgs + ");";
	return nDeepLevel;
}

int ast_postfix_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;

	this->identifier->SyntaxCheck(queueType, table, control);
	
	if (this->arglist != nullptr)
		this->arglist->SyntaxCheck(types, table, control);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->arglist);

	// 检查参数列表与函数名的数量以及类型是否匹配
	if (table.GetFunction().GetSymbol(this->identifier->GetValue()).size() != 0)
	{
		std::vector<symbol> symbols = table.GetFunction().GetArguments(this->identifier->GetValue());
		for (size_t i = 1; i < symbols.size(); i++)
		{
			if (types.size() == 0)
			{
				SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_FunctionParamUnpair);
				this->m_errors.push_back(error);
				break;
			}

			// 获取最前面的参数类型
			AstSymbolType argType = types.front();
			types.pop();

			if (UpgradeType(argType, symbols[i].GetType()) == AstSymbolType::AstSymbolType_UNKNOWN)
			{
				SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_FunctionParamUnpair);
				this->m_errors.push_back(error);
				break;
			}
		}
	}

	return this->m_errors.size();
}

std::vector<symbol> ast_postfix_t::GetIdentifiers(void)
{
	if (arglist == nullptr) {
		std::vector<symbol> identifiers = { symbol(this->identifier->GetValue(), this->GetIdentifierLocation()) };
		return identifiers;
	}
	return arglist->GetIdentifiers();
}

ast_postfix_t::ast_postfix_t(const std::string& identifier, ast_arg_list_t* arglist)
	:arglist(arglist)
{
	m_nType = parser_t::symbol_kind::S_postfix_expr;
	this->identifier = new ast_identifier_t(identifier, Identifier_Type::Identifier_Function);
	this->identifier->Parent(this);
	if (this->m_locations.size() != 0)
	{
		this->identifier->SetLocations({ this->m_locations.at(0) });
	}
}

ast_postfix_t::~ast_postfix_t()
{
	this->init();
}

int ast_binary_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strOperA;
	std::string strOperB;

	_ASSERT(this->a);
	_ASSERT(this->b);

	this->a->Translation(strOperA, nDeepLevel, table);
	this->b->Translation(strOperB, nDeepLevel, table);

	switch (this->m_nType)
	{
	case parser_t::symbol_kind::S_or_expr:
		// 或
		output = output + "(" + strOperA + " || " + strOperB + ")";
		break;
	case parser_t::symbol_kind::S_xor_expr:
	{
		// 异或 XOR = (!A && B) || (A && !B)
		output = output + "(!" + strOperA + " && " + strOperB + ")";
		output = output + " || ";
		output = output + "(" + strOperA + " && !" + strOperB + ")";
	}
	break;
	case parser_t::symbol_kind::S_and_expr:
		// 且
		output = output + "(" + strOperA + " && " + strOperB + ")";
		break;
	case parser_t::symbol_kind::S_eql_expr:
	{
		// 等于 / 不等于
		_ASSERT(this->identifier == "eq" || this->identifier == "neq");

		std::map<std::string, std::string> operatorMap;
		operatorMap["eq"] = " == ";
		operatorMap["neq"] = " != ";

		output = output + "(" + strOperA + operatorMap[this->identifier] + strOperB + ")";
	}
	break;
	case parser_t::symbol_kind::S_cmp_expr:
	{
		// 比较运算符
		_ASSERT(
			this->identifier == "ls" || this->identifier == "gr" ||
			this->identifier == "le" || this->identifier == "ge"
		);

		std::map<std::string, std::string> operatorMap;
		operatorMap["ls"] = " < ";
		operatorMap["gr"] = " > ";
		operatorMap["le"] = " <= ";
		operatorMap["ge"] = " >= ";

		output = output + "(" + strOperA + operatorMap[this->identifier] + strOperB + ")";
	}
	break;
	case parser_t::symbol_kind::S_add_expr:
	{
		// 加减法
		_ASSERT(this->identifier == "sum" || this->identifier == "sub");

		std::map<std::string, std::string> operatorMap;
		operatorMap["sum"] = " + ";
		operatorMap["sub"] = " - ";

		output = output + "(" + strOperA + operatorMap[this->identifier] + strOperB + ")";
	}
	break;
	case parser_t::symbol_kind::S_mul_expr:
	{
		// 乘除法、取余法
		_ASSERT(
			this->identifier == "mul" || this->identifier == "div" ||
			this->identifier == "mod"
		);

		std::map<std::string, std::string> operatorMap;
		operatorMap["mul"] = " * ";
		operatorMap["div"] = " / ";
		operatorMap["mod"] = " % ";

		output = output + "(" + strOperA + operatorMap[this->identifier] + strOperB + ")";
	}
	break;
	case parser_t::symbol_kind::S_pow_expr:
		output = output + "pow(" + strOperA + " , " + strOperB + ")";
		break;
	default:
		break;
	}
	return nDeepLevel;
}

int ast_binary_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> memberAType;
	std::queue<AstSymbolType> memberBType;

	nErrorSum += this->a->SyntaxCheck(memberAType, table, control);
	nErrorSum += this->b->SyntaxCheck(memberBType, table, control);

	RECURVE_SYNTAXERROR(errors, this->m_errors, this->a);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->b);

	// 必须保证A与B的值有且只有一个类型数据返回
	if (memberAType.size() != 1 || memberBType.size() != 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_FunctionParamUnpair);
		this->m_errors.push_back(error);

		queueType.push(AstSymbolType::AstSymbolType_UNKNOWN);
		return ++nErrorSum;
	}

	switch (this->m_nType)
	{
	case parser_t::symbol_kind::S_or_expr:
	case parser_t::symbol_kind::S_xor_expr:
	case parser_t::symbol_kind::S_and_expr:
		// 需要保证两边都必须是BOOL类型的数
		if (memberAType.front() != AstSymbolType::AstSymbolType_BOOL ||
			memberBType.front() != AstSymbolType::AstSymbolType_BOOL)
		{
			SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_BinaryTypeUnpair);
			this->m_errors.push_back(error);
		}
		queueType.push(AstSymbolType::AstSymbolType_BOOL);
		break;
	case parser_t::symbol_kind::S_eql_expr:
	case parser_t::symbol_kind::S_cmp_expr:
		if (UpgradeType(memberAType.front(), memberBType.front()) == AstSymbolType::AstSymbolType_UNKNOWN)
		{
			SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_BinaryTypeUnpair);
			this->m_errors.push_back(error);
		}
		queueType.push(AstSymbolType::AstSymbolType_BOOL);
		break;
	case parser_t::symbol_kind::S_add_expr:
	case parser_t::symbol_kind::S_mul_expr:
	case parser_t::symbol_kind::S_pow_expr:
		// 需要保证两边必须是数值类型
		if (memberAType.front() < AstSymbolType::AstSymbolType_NUMBER_BEGIN ||
			memberAType.front() > AstSymbolType::AstSymbolType_NUMBER_END ||
			memberBType.front() < AstSymbolType::AstSymbolType_NUMBER_BEGIN ||
			memberBType.front() > AstSymbolType::AstSymbolType_NUMBER_END)
		{
			SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_BinaryTypeUnpair);
			this->m_errors.push_back(error);

			queueType.push(AstSymbolType::AstSymbolType_UNKNOWN);
			break;
		}
		queueType.push(UpgradeType(memberAType.front(), memberBType.front()));

		break;
	default:
		break;
	}

	return this->m_errors.size();
}

std::vector<symbol> ast_binary_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->a);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->b);

	return identifiers;
}

ast_binary_t::ast_binary_t(const std::string& identifier, ast_item_t* a, ast_item_t* b)
	:identifier(identifier), a(a), b(b)
{
	std::map<std::string, parser_t::symbol_kind::symbol_kind_type> tokenTypeMap;
	tokenTypeMap["or"] = parser_t::symbol_kind::S_or_expr;
	tokenTypeMap["xor"] = parser_t::symbol_kind::S_xor_expr;
	tokenTypeMap["and"] = parser_t::symbol_kind::S_and_expr;
	tokenTypeMap["eq"] = parser_t::symbol_kind::S_eql_expr;
	tokenTypeMap["neq"] = parser_t::symbol_kind::S_eql_expr;
	tokenTypeMap["ls"] = parser_t::symbol_kind::S_cmp_expr;
	tokenTypeMap["gr"] = parser_t::symbol_kind::S_cmp_expr;
	tokenTypeMap["le"] = parser_t::symbol_kind::S_cmp_expr;
	tokenTypeMap["ge"] = parser_t::symbol_kind::S_cmp_expr;
	tokenTypeMap["sum"] = parser_t::symbol_kind::S_add_expr;
	tokenTypeMap["sub"] = parser_t::symbol_kind::S_add_expr;
	tokenTypeMap["mul"] = parser_t::symbol_kind::S_mul_expr;
	tokenTypeMap["mod"] = parser_t::symbol_kind::S_mul_expr;
	tokenTypeMap["div"] = parser_t::symbol_kind::S_mul_expr;
	tokenTypeMap["pow"] = parser_t::symbol_kind::S_pow_expr;

	if (tokenTypeMap.find(this->identifier) != tokenTypeMap.end())
	{
		m_nType = tokenTypeMap[this->identifier];
	}
}

ast_binary_t::~ast_binary_t()
{
	CLEAN_RELEASE(this->a);
	CLEAN_RELEASE(this->b);
}

int ast_unary_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strChain;
	RECURVE_TRANSLATION(strChain, nDeepLevel, this->chain, table);

	switch (this->m_nType)
	{
	case parser_t::symbol_kind::S_SUM:
		output = output + "(" + strChain + ")";
		break;
	case parser_t::symbol_kind::S_SUB:
		output = output + "-1 * (" + strChain + ")";
		break;
	default:
		output = output + "!(" + strChain + ")";
		break;
	}

	return nDeepLevel;
}

int ast_unary_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;

	this->chain->SyntaxCheck(types, table, control);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->chain);

	if (types.size() != 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_UnaryCountUnpair);
		this->m_errors.push_back(error);

		queueType.push(types.front());
		return this->m_errors.size();
	}

	switch (this->m_nType)
	{
	case parser_t::symbol_kind::S_SUM:
	case parser_t::symbol_kind::S_SUB:
		// 需要保证必须是数值类型
		if (types.front() < AstSymbolType::AstSymbolType_NUMBER_BEGIN ||
			types.front() > AstSymbolType::AstSymbolType_NUMBER_END)
		{
			SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_UnaryTypeUnpair);
			this->m_errors.push_back(error);

			queueType.push(AstSymbolType::AstSymbolType_UNKNOWN);
			break;
		}
		queueType.push(types.front());
		break;
	default:
		if (types.front() != AstSymbolType::AstSymbolType_BOOL)
		{
			SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_UnaryTypeUnpair);
			this->m_errors.push_back(error);

			queueType.push(AstSymbolType::AstSymbolType_UNKNOWN);
			break;
		}

		queueType.push(AstSymbolType::AstSymbolType_BOOL);
		break;
	}
	return this->m_errors.size();
}

std::vector<symbol> ast_unary_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers = this->chain->GetIdentifiers();
	return identifiers;
}

ast_unary_t::ast_unary_t(const std::string& identifier, ast_item_t* chain)
	: identifier(identifier), chain(chain)
{
	std::map<std::string, parser_t::symbol_kind::symbol_kind_type> tokenTypeMap;
	tokenTypeMap["not"] = parser_t::symbol_kind::S_unary_expr;
	tokenTypeMap["neg"] = parser_t::symbol_kind::S_unary_expr;
	tokenTypeMap["sum"] = parser_t::symbol_kind::S_SUM;
	tokenTypeMap["sub"] = parser_t::symbol_kind::S_SUB;
	if (tokenTypeMap.find(this->identifier) != tokenTypeMap.end())
	{
		m_nType = tokenTypeMap[this->identifier];
	}
}

ast_unary_t::~ast_unary_t()
{
	CLEAN_RELEASE(this->chain);
}

int ast_return_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strChain;
	RECURVE_TRANSLATION(strChain, nDeepLevel, this->chain, table);
	output = output + strChain + "";
	return nDeepLevel;
}

int ast_return_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	std::vector<SyntaxError> errors;
	this->chain->SyntaxCheck(queueType, table, control);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->chain);

	if (!control.GetIsCondition() && 
		(this->Parent() && this->Parent()->GetType() != parser_t::symbol_kind::S_assign_expr) &&
		(this->chain && this->chain->GetType() != parser_t::symbol_kind::S_postfix_expr))
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_NotStatement);
		this->m_errors.push_back(error);
	}

	if (control.GetIsCondition() && (this->chain && 
			(this->chain->GetType() != parser_t::symbol_kind::S_cmp_expr && 
			this->chain->GetType() != parser_t::symbol_kind::S_assign_expr) &&
			!(this->chain->GetType() == parser_t::symbol_kind::S_IDENTIFIER && queueType.front() == AstSymbolType::AstSymbolType_BOOL)))
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_ShouldBeCondition);
		this->m_errors.push_back(error);
	}

	return this->m_errors.size();
}

std::vector<symbol> ast_return_t::GetIdentifiers(void)
{
	return this->chain->GetIdentifiers();
}

ast_return_t::ast_return_t(ast_item_t* chain) :chain(chain)
{
	m_nType = parser_t::symbol_kind::S_assign_expr;
}

ast_return_t::~ast_return_t()
{
	CLEAN_RELEASE(this->chain);
}

int ast_set_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strChain;

	RECURVE_TRANSLATION(strChain, nDeepLevel, this->chain, table);
	output = output + this->GetIndent(nDeepLevel) + this->identifier->GetValue() + " = " + strChain + ";\n";
	return nDeepLevel;
}

int ast_set_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;
	std::queue<AstSymbolType> identifierTypes;

	this->chain->SyntaxCheck(types, table, control);
	this->identifier->SyntaxCheck(identifierTypes, table, control);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->chain);

	if (types.size() != 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_UnaryCountUnpair);
		this->m_errors.push_back(error);

		queueType.push(types.front());
		return this->m_errors.size();
	}

	// 确定返回值跟identifier一致
	if (identifierTypes.front() != AstSymbolType::AstSymbolType_UNKNOWN)
	{
		if (UpgradeType(types.front(), identifierTypes.front()) == AstSymbolType::AstSymbolType_UNKNOWN)
		{
			SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_UnaryTypeUnpair);
			this->m_errors.push_back(error);
		}
	}

	// 确定identifier必须是可读可写的
	if (((ast_identifier_t*)(this->identifier))->GetIdentifierRWType() == symbol_rw::symbol_read)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_IdentifierReadOnly);
		this->m_errors.push_back(error);
	}

	queueType.push(AstSymbolType::AstSymbolType_UNUSE);

	return this->m_errors.size();
}

std::string ast_set_t::GetValue(void) const
{
	return std::string();
}

std::vector<symbol> ast_set_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers = this->chain->GetIdentifiers();
	identifiers.push_back(symbol(this->identifier->GetValue(), this->GetIdentifierLocation()));
	return identifiers;
}

ast_set_t::ast_set_t(const std::string& identifier, ast_item_t* chain) :chain(chain)
{
	m_nType = parser_t::symbol_kind::S_assign_expr;
	this->identifier = new ast_identifier_t(identifier);
	this->identifier->Parent(this);
	if (this->m_locations.size() > 0)
	{
		this->identifier->SetLocations({this->m_locations.at(0)});
	}
}

ast_set_t::~ast_set_t()
{
	CLEAN_RELEASE(this->identifier);
	CLEAN_RELEASE(this->chain);
}

int ast_exit_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table&) const
{
	output = output + this->GetIndent(nDeepLevel) + "break;\n";
	return nDeepLevel;
}

ast_exit_t::ast_exit_t() {
	m_nType = parser_t::symbol_kind::S_exit_statement;
}

ast_exit_t::~ast_exit_t() {
}

int ast_if_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strCondition;
	std::string strTruePath;
	std::string strElsePath;
	std::string strElsifPath;

	RECURVE_TRANSLATION(strCondition, 0, this->condition, table);
	RECURVE_TRANSLATION(strTruePath, nDeepLevel + 1, this->true_path, table);
	RECURVE_TRANSLATION(strElsifPath, nDeepLevel, this->elseif_path, table);
	RECURVE_TRANSLATION(strElsePath, nDeepLevel + 1, this->else_path, table);

	output = output + this->GetIndent(nDeepLevel) + "if (" + strCondition + ") \n";
	output = output + this->GetIndent(nDeepLevel) + "{ \n";
	output = output + strTruePath + "\n";
	output = output + this->GetIndent(nDeepLevel) + "} \n";

	if (this->elseif_path != nullptr)
	{
		output = output + strElsifPath;
	}

	if (this->else_path != nullptr)
	{
		output = output + this->GetIndent(nDeepLevel) + "else \n";
		output = output + this->GetIndent(nDeepLevel) + "{ \n";
		output = output + strElsePath + "\n";
		output = output + this->GetIndent(nDeepLevel) + "} \n";
	}

	return nDeepLevel;
}

int ast_if_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;
	std::queue<AstSymbolType> conditionTypes;

	nErrorSum += this->condition->SyntaxCheck(conditionTypes, table, control);
	nErrorSum += this->true_path->SyntaxCheck(types, table, control);

	RECURVE_SYNTAXERROR(errors, this->m_errors, this->condition);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->true_path);
	if (this->else_path)
	{
		nErrorSum += this->else_path->SyntaxCheck(types, table, control);
		RECURVE_SYNTAXERROR(errors, this->m_errors, this->else_path);
	}

	if (this->elseif_path)
	{
		nErrorSum += this->elseif_path->SyntaxCheck(types, table, control);
		RECURVE_SYNTAXERROR(errors, this->m_errors, this->elseif_path);
	}

	// 判断条件中的数量必须为1且类型必须是BOOL类型
	if (conditionTypes.size() != 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_ConditionCountUnpair);
		this->m_errors.push_back(error);

		queueType.push(AstSymbolType::AstSymbolType_UNUSE);
		return this->m_errors.size();
	}
	
	if (conditionTypes.front() != AstSymbolType::AstSymbolType_BOOL)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_ConditionTypeUnpair);
		this->m_errors.push_back(error);
	}

	queueType.push(AstSymbolType::AstSymbolType_UNUSE);
	return this->m_errors.size();
}

std::vector<symbol> ast_if_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->condition);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->true_path);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->else_path);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->elseif_path);

	return identifiers;
}

ast_if_t::ast_if_t(ast_item_t* condition, ast_t* true_path, ast_t* else_path, ast_t* elseif_path)
	: condition(condition), true_path(true_path), else_path(else_path), elseif_path(elseif_path) {
	m_nType = parser_t::symbol_kind::S_if_statement;
}

ast_if_t::~ast_if_t()
{
	CLEAN_RELEASE(this->condition);
	CLEAN_RELEASE(this->true_path);
	CLEAN_RELEASE(this->else_path);
}

int ast_elsif_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strCondition;
	std::string strPath;

	RECURVE_TRANSLATION(strCondition, 0, this->condition, table);
	RECURVE_TRANSLATION(strPath, nDeepLevel + 1, this->path, table);

	output = output + this->GetIndent(nDeepLevel) + "else if (" + strCondition + ") \n";
	output = output + this->GetIndent(nDeepLevel) + "{ \n";
	output = output + strPath + "\n";
	output = output + this->GetIndent(nDeepLevel) + "} \n";

	return nDeepLevel;
}

int ast_elsif_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;
	std::queue<AstSymbolType> conditionTypes;

	nErrorSum += this->condition->SyntaxCheck(conditionTypes, table, control);
	nErrorSum += this->path->SyntaxCheck(types, table, control);

	RECURVE_SYNTAXERROR(errors, this->m_errors, this->condition);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->path);

	// 判断条件中的数量必须为1且类型必须是BOOL类型
	if (conditionTypes.size() != 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_ConditionCountUnpair);
		this->m_errors.push_back(error);

		queueType.push(AstSymbolType::AstSymbolType_UNUSE);
		return this->m_errors.size();
	}

	if (conditionTypes.front() != AstSymbolType::AstSymbolType_BOOL)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_ConditionTypeUnpair);
		this->m_errors.push_back(error);
	}

	queueType.push(AstSymbolType::AstSymbolType_UNUSE);
	return this->m_errors.size();
}

std::vector<symbol> ast_elsif_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->condition);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->path);

	return identifiers;
}

ast_elsif_t::ast_elsif_t(ast_item_t* condition, ast_t* path)
	: condition(condition), path(path)
{
}

ast_elsif_t::~ast_elsif_t()
{
	CLEAN_RELEASE(this->condition);
	CLEAN_RELEASE(this->path);
}

double ast_enumeration_t::GetNumber(void)
{
	if (this->number)
	{
		return atof(this->number->GetValue().c_str());
	}
	return 0.0;
}

int ast_enumeration_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strNumber;
	std::string strCase;

	RECURVE_TRANSLATION(strNumber, 0, this->number, table);
	RECURVE_TRANSLATION(strCase, nDeepLevel + 1, this->case_path, table);

	output = output + this->GetIndent(nDeepLevel) + "case " + strNumber + ":\n";
	output = output + this->GetIndent(nDeepLevel) + "{\n";
	output = output + strCase;
	output = output + this->GetIndent(nDeepLevel + 1) + "break;\n";
	output = output + this->GetIndent(nDeepLevel) + "}\n";

	return nDeepLevel;
}

int ast_enumeration_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;

	nErrorSum += this->number->SyntaxCheck(types, table, control);
	nErrorSum += this->case_path->SyntaxCheck(types, table, control);

	RECURVE_SYNTAXERROR(errors, this->m_errors, this->number);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->case_path);

	queueType.push(AstSymbolType::AstSymbolType_UNUSE);
	return nErrorSum;
}

std::vector<symbol> ast_enumeration_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->number);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->case_path);

	return identifiers;
}

ast_enumeration_t::ast_enumeration_t(ast_item_t* number, ast_t* case_path)
	: number(number), case_path(case_path)
{
}

ast_enumeration_t::ast_enumeration_t(double number, ast_t* case_path)
	: case_path(case_path)
{
	this->number = new ast_number_t(number);
	this->number->Parent(this);
	if (this->m_locations.size() != 0)
	{
		this->number->SetLocations({ this->m_locations.at(0) });
	}
}

ast_enumeration_t::ast_enumeration_t(std::string& number, ast_t* case_path)
	: case_path(case_path)
{
	this->number = new ast_number_t(number);
	this->number->Parent(this);
	if (this->m_locations.size() != 0)
	{
		this->number->SetLocations({ this->m_locations.at(0) });
	}
}

ast_enumeration_t::~ast_enumeration_t()
{
	CLEAN_RELEASE(this->number);
	CLEAN_RELEASE(this->case_path);
}

int ast_case_t::SyntaxCheckUniqueness(void)
{
	std::vector<SyntaxError> errors;

	if (this->branchs)
	{
		std::vector<ast_item_t*> branchLst = this->branchs->GetStatements();
		std::map<long long, ast_item_t*> branchMap;

		for (auto iter : branchLst)
		{
			double dbCaseNumber = ((ast_enumeration_t*)(iter))->GetNumber();
			long long nCaseNumber = (long long)dbCaseNumber;

			// 1. 必须是整数
			if ((dbCaseNumber - nCaseNumber) != 0.0)
			{
				SyntaxError error(iter->GetLocation(), SyntaxType::SyntexError_CaseNumberInteger);
				errors.push_back(error);
			}

			// 2. 必须不能重复
			if (branchMap.find(nCaseNumber) != branchMap.end())
			{
				SyntaxError error(iter->GetLocation(), SyntaxType::SyntexError_CaseNumberRepeat);
				errors.push_back(error);
			}

			branchMap[nCaseNumber] = iter;
		}
	}

	this->m_errors.insert(this->m_errors.end(), errors.begin(), errors.end());
	return (int)errors.size();
}

int ast_case_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strEnumeration;
	std::string strBranchs;
	std::string strElsePath;

	RECURVE_TRANSLATION(strEnumeration, nDeepLevel, this->enumeration, table);
	RECURVE_TRANSLATION(strBranchs, nDeepLevel + 1, this->branchs, table);
	RECURVE_TRANSLATION(strElsePath, nDeepLevel + 2, this->else_path, table);

	output = output + this->GetIndent(nDeepLevel) + "switch(" + strEnumeration + ")\n";
	output = output + this->GetIndent(nDeepLevel) + "{\n";
	output = output + strBranchs;
	if (this->else_path != nullptr)
	{
		output = output + this->GetIndent(nDeepLevel + 1) + "default:\n";
		output = output + this->GetIndent(nDeepLevel + 1) + "{\n";
		output = output + strElsePath;
		output = output + this->GetIndent(nDeepLevel + 2) + "break;\n";
		output = output + this->GetIndent(nDeepLevel + 1) + "}\n";
	}
	output = output + this->GetIndent(nDeepLevel) + "}\n";

	return nDeepLevel;
}

int ast_case_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;
	std::queue<AstSymbolType> enumerationTypes;

	nErrorSum += this->enumeration->SyntaxCheck(enumerationTypes, table, control);
	nErrorSum += this->branchs->SyntaxCheck(types, table, control);

	RECURVE_SYNTAXERROR(errors, this->m_errors, this->enumeration);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->branchs);

	if (this->else_path != nullptr)
	{
		nErrorSum += this->else_path->SyntaxCheck(types, table, control);
		RECURVE_SYNTAXERROR(errors, this->m_errors, this->else_path);
	}

	// 语义检查 （唯一性检查）
	nErrorSum += this->SyntaxCheckUniqueness();

	if (enumerationTypes.size() != 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_EnumerationCountUnpair);
		this->m_errors.push_back(error);

		queueType.push(AstSymbolType::AstSymbolType_UNUSE);
		return this->m_errors.size();
	}

	if (!IsDigit(enumerationTypes.front()) || enumerationTypes.front() == AstSymbolType::AstSymbolType_REAL)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_EnumerationTypeUnpair);
		this->m_errors.push_back(error);
	}

	queueType.push(AstSymbolType::AstSymbolType_UNUSE);
	return this->m_errors.size();
}

std::vector<symbol> ast_case_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->enumeration);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->branchs);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->else_path);

	return identifiers;
}

ast_case_t::ast_case_t(ast_item_t* enumeration, ast_t* branchs, ast_t* else_path)
	: enumeration(enumeration), branchs(branchs), else_path(else_path)
{
}

ast_case_t::~ast_case_t()
{
	CLEAN_RELEASE(this->enumeration);
	CLEAN_RELEASE(this->branchs);
	CLEAN_RELEASE(this->else_path);
}

ast_loop_t::ast_loop_t() : end_loc_pos(-1)
{
}

ast_loop_t::~ast_loop_t()
{
}

int ast_for_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strStart;
	std::string strFinish;
	std::string strLoop;
	std::string strStep;

	if (this->start != nullptr)
	{
		this->start->Translation(strStart, nDeepLevel, table);
		strStart = this->identifier->GetValue() + " = " + strStart;
	}

	if (this->finish != nullptr)
	{
		this->finish->Translation(strFinish, nDeepLevel, table);
		strFinish = this->identifier->GetValue() + " <= " + strFinish;
	}

	RECURVE_TRANSLATION(strLoop, nDeepLevel + 1, this->loop, table);

	if (this->step != nullptr)
	{
		this->step->Translation(strStep, nDeepLevel, table);
		strStep = this->identifier->GetValue() + " += " + strStep;
	}

	output = output + this->GetIndent(nDeepLevel) + "for (" + strStart + "; " + strFinish + "; " + strStep + ")\n";
	output = output + this->GetIndent(nDeepLevel) + "{\n";
	output = output + this->GetIndent(nDeepLevel) + strLoop + "\n";
	output = output + this->GetIndent(nDeepLevel) + "}\n";

	return nDeepLevel;
}

int ast_for_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> identifierTypes;
	std::queue<AstSymbolType> startTypes;
	std::queue<AstSymbolType> finishTypes;
	std::queue<AstSymbolType> loopTypes;
	std::queue<AstSymbolType> stepTypes;

	nErrorSum += this->identifier->SyntaxCheck(identifierTypes, table, control);
	nErrorSum += this->start->SyntaxCheck(startTypes, table, control);
	nErrorSum += this->finish->SyntaxCheck(finishTypes, table, control);
	nErrorSum += this->loop->SyntaxCheck(loopTypes, table, control);

	RECURVE_SYNTAXERROR(errors, this->m_errors, this->start);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->finish);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->loop);
	if (this->step)
	{
		RECURVE_SYNTAXERROR(errors, this->m_errors, this->step);
	}

	// identifier 与start\finish\step 必须是兼容类型
	if (startTypes.size() != 1 || finishTypes.size() != 1 ||
		stepTypes.size() > 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_LoopForCountUnpair);
		this->m_errors.push_back(error);

		queueType.push(AstSymbolType::AstSymbolType_UNUSE);
		return this->m_errors.size();
	}

	if (UpgradeType(identifierTypes.front(), finishTypes.front()) == AstSymbolType::AstSymbolType_UNKNOWN ||
		UpgradeType(startTypes.front(), finishTypes.front()) == AstSymbolType::AstSymbolType_UNKNOWN ||
		(stepTypes.size() != 0 && UpgradeType(finishTypes.front(), stepTypes.front()) == AstSymbolType::AstSymbolType_UNKNOWN))
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_LoopForTypeUnpair);
		this->m_errors.push_back(error);
	}

	queueType.push(AstSymbolType::AstSymbolType_UNUSE);
	return this->m_errors.size();
}

std::vector<symbol> ast_for_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->start);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->finish);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->loop);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->step);

	identifiers.push_back(symbol(this->identifier->GetValue(), this->GetIdentifierLocation()));
	return identifiers;
}

ast_for_t::ast_for_t(const std::string& identifier, ast_item_t* start, ast_item_t* finish, ast_t* loop, ast_item_t* step)
	:start(start), finish(finish), loop(loop), step(step) {
	m_nType = parser_t::symbol_kind::S_for_statement;
	this->identifier = new ast_identifier_t(identifier);
	this->identifier->Parent(this);
	if (this->m_locations.size() > 1)
	{
		this->identifier->SetLocations({ this->m_locations.at(1) });
	}
}

ast_for_t::~ast_for_t()
{
	CLEAN_RELEASE(this->identifier);
	CLEAN_RELEASE(this->start);
	CLEAN_RELEASE(this->finish);
	CLEAN_RELEASE(this->loop);
	CLEAN_RELEASE(this->step);
}

int ast_while_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strCondition;
	std::string strLoop;

	RECURVE_TRANSLATION(strCondition, nDeepLevel, this->condition, table);
	RECURVE_TRANSLATION(strLoop, nDeepLevel + 1, this->loop, table);

	output = output + this->GetIndent(nDeepLevel) + "while(" + strCondition + ")\n";
	output = output + this->GetIndent(nDeepLevel) + "{\n";
	output = output + strLoop + "\n";
	output = output + this->GetIndent(nDeepLevel) + "}\n";

	return nDeepLevel;
}

int ast_while_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;
	std::queue<AstSymbolType> conditionTypes;

	nErrorSum += this->condition->SyntaxCheck(conditionTypes, table, control);
	nErrorSum += this->loop->SyntaxCheck(types, table, control);

	RECURVE_SYNTAXERROR(errors, this->m_errors, this->condition);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->loop);

	// condition 必须是一个bool类型
	if (conditionTypes.size() != 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_LoopWhileCountUnpair);
		this->m_errors.push_back(error);

		queueType.push(AstSymbolType::AstSymbolType_UNUSE);
		return this->m_errors.size();
	}

	if (conditionTypes.front() != AstSymbolType::AstSymbolType_BOOL)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_LoopWhileTypeUnpair);
		this->m_errors.push_back(error);
	}

	queueType.push(AstSymbolType::AstSymbolType_UNUSE);
	return this->m_errors.size();
}

std::vector<symbol> ast_while_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->condition);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->loop);

	return identifiers;
}

ast_while_t::ast_while_t(ast_item_t* condition, ast_t* loop)
	:condition(condition), loop(loop)
{
	m_nType = parser_t::symbol_kind::S_while_statement;
}

ast_while_t::~ast_while_t()
{
	CLEAN_RELEASE(this->condition);
	CLEAN_RELEASE(this->loop);
}

int ast_repeat_t::Translation(std::string& output, int nDeepLevel, ast_symbol_table& table) const
{
	std::string strCondition;
	std::string strLoop;

	RECURVE_TRANSLATION(strCondition, nDeepLevel, this->condition, table);
	RECURVE_TRANSLATION(strLoop, nDeepLevel + 1, this->loop, table);

	output = output + this->GetIndent(nDeepLevel) + "do\n";
	output = output + this->GetIndent(nDeepLevel) + "{\n";
	output = output + strLoop + "\n";
	output = output + this->GetIndent(nDeepLevel) + "} while (" + strCondition + ");\n";

	return nDeepLevel;
}

int ast_repeat_t::SyntaxCheck(std::queue<AstSymbolType>& queueType, ast_symbol_table& table, ast_check_ctrl& control)
{
	int nErrorSum = 0;
	std::vector<SyntaxError> errors;
	std::queue<AstSymbolType> types;
	std::queue<AstSymbolType> conditionTypes;

	nErrorSum += this->condition->SyntaxCheck(conditionTypes, table, control);
	nErrorSum += this->loop->SyntaxCheck(types, table, control);

	RECURVE_SYNTAXERROR(errors, this->m_errors, this->condition);
	RECURVE_SYNTAXERROR(errors, this->m_errors, this->loop);

	// condition 必须是一个bool类型
	if (conditionTypes.size() != 1)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_LoopRepeatCountUnpair);
		this->m_errors.push_back(error);

		queueType.push(AstSymbolType::AstSymbolType_UNUSE);
		return this->m_errors.size();
	}

	if (conditionTypes.front() != AstSymbolType::AstSymbolType_BOOL)
	{
		SyntaxError error(this->GetLocation(), SyntaxType::SyntexError_LoopRepeatTypeUnpair);
		this->m_errors.push_back(error);
	}

	queueType.push(AstSymbolType::AstSymbolType_UNUSE);
	return this->m_errors.size();
}


std::vector<symbol> ast_repeat_t::GetIdentifiers(void)
{
	std::vector<symbol> identifiers;
	std::vector<symbol> identifiertemp;

	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->condition);
	RECURVE_IDENTIFIER(identifiertemp, identifiers, this->loop);

	return identifiers;
}

ast_repeat_t::ast_repeat_t(ast_item_t* condition, ast_t* loop)
	:condition(condition), loop(loop)
{
	m_nType = parser_t::symbol_kind::S_repeat_statement;
}

ast_repeat_t::~ast_repeat_t()
{
	CLEAN_RELEASE(this->condition);
	CLEAN_RELEASE(this->loop);
}

ast_error_t::ast_error_t()
{
	m_nType = parser_t::symbol_kind::S_YYerror;
}

ast_error_t::~ast_error_t()
{
}

}