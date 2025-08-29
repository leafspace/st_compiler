#include <deci.hpp>
#include <iostream>
#include <sstream>

#include <Windows.h>

#define CLASS_TYPE

std::string& Utf8ToAnsi(std::string& strUtf8)
{
	size_t n = strUtf8.size() * 2;
	if (n == 0)
	{
		return strUtf8;
	}
	wchar_t* sl = new wchar_t[n];

	char* sm = new char[n];
	//多字节(UTF8)编码转换为宽字节编码
	MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, sl, n);

	//宽字节转换为多字节(Ansi)编码
	WideCharToMultiByte(CP_ACP, 0, sl, -1, sm, n, NULL, 0);

	strUtf8 = sm;
	delete[] sl;
	delete[] sm;

	return strUtf8;
}

int main_repl(int argc, char* argv[]) {
	while (true) {
		std::cout << ">> ";

		try
		{
#ifdef  CLASS_TYPE
			deci::variant_table variants;
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_DINT, std::string("IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_DINT, std::string("IDENTIFIER.IN")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_INT, std::string("INT_IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_BOOL, std::string("BOOL_IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_REAL, std::string("REAL_IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_DINT, std::string("DINT_IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_DINT, std::string("CONST_IDENTIFIER"), deci::symbol_rw::symbol_read));

			deci::compiler_t compiler(std::string("std::cin"), std::cin, true);
			compiler.SetOuterVariant(variants);
			compiler.SyntaxCheck();
			std::vector<deci::SyntaxError> errors = compiler.GetErrors();
			std::string translation = compiler.SyntaxTranslation();
			compiler.PrintSyntaxError(errors);
#else
			std::vector<deci::SyntaxError> errors;
			std::map<std::string, void*> params;
			std::vector<std::string> identfiers;
			std::shared_ptr<deci::ast_t> ast = deci::Parse(errors, identfiers, "std::cin", std::cin, true);
			deci::SyntaxCheck(errors, params, ast);
			deci::PrintSyntaxError(errors);

			std::string translation = deci::SyntaxTranslation(ast);
#endif //  CLASS_TYPE

			

			std::cout << "Tranlate to C++" << std::endl;
			std::cout << translation << std::endl;
		}
		catch (const std::exception&)
		{
			std::cout << "Exception " << std::endl;
		}
	}

	return 0;
}

int run(const char* filename) {
	std::ifstream input;
	input.open(filename, std::ios::in);

	if (input.good()) {
		std::stringstream stream;
		stream << input.rdbuf();
		std::string strInput = stream.str();

		Utf8ToAnsi(strInput);
		try
		{
			std::cout << "===================================================" << std::endl;
			std::cout << "Begin " << filename << std::endl;

#ifdef CLASS_TYPE
			deci::variant_table variants;
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_DINT, std::string("IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_DINT, std::string("IDENTIFIER.IN")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_INT,  std::string("INT_IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_BOOL, std::string("BOOL_IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_REAL, std::string("REAL_IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_DINT, std::string("DINT_IDENTIFIER")));
			variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_DINT, std::string("CONST_IDENTIFIER"), deci::symbol_rw::symbol_read));

			deci::compiler_t compiler(std::string(""), strInput);
			compiler.SetOuterVariant(variants);
			compiler.SyntaxCheck();
			std::vector<deci::SyntaxError> errors = compiler.GetErrors();
			std::string translation = compiler.SyntaxTranslation();
			compiler.PrintSyntaxError(errors);
#else
			std::vector<deci::SyntaxError> errors;
			std::map<std::string, void*> params;
			std::vector<std::string> identfiers;
			std::shared_ptr<deci::ast_t> ast = deci::Parse(errors, identfiers, strInput);
			deci::SyntaxCheck(errors, params, ast);
			deci::PrintSyntaxError(errors);
			std::string translation = deci::SyntaxTranslation(ast);
#endif //  CLASS_TYPE

			std::cout << "Translate to C++" << std::endl;
			std::cout << translation << std::endl;
			std::cout << "===================================================" << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception " << e.what() << std::endl;
			return -1;
		}
	}
	return 0;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		return main_repl(argc, argv);
	}

	for (int i = 1; i < argc; ++i) {
		if (run(argv[i]) != 0) {
			return -1;
		}
	}

	std::cout << "===================================================" << std::endl;
	deci::variant_table variants;
	variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_INT, std::string("INT_IDENTIFIER")));
	variants.AddSymbol(deci::symbol(deci::AstSymbolType::AstSymbolType_BOOL, std::string("BOOL_IDENTIFIER")));
	deci::compiler_t compiler(std::string(""), std::string("INT_IDENTIFIER"));
	compiler.SetCheckCtrlIsCondition(true);
	compiler.SetOuterVariant(variants);
	compiler.SyntaxCheck();
	std::vector<deci::SyntaxError> errors = compiler.GetErrors();
	std::string translation = compiler.SyntaxTranslation();

	compiler.PrintSyntaxError(errors);
	std::cout << translation << std::endl;

	return 0;
}