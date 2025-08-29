#pragma once
#ifndef __DECI_SCANNER_HEADER__
#define __DECI_SCANNER_HEADER__

#ifndef yyFlexLexerOnce
#undef yyFlexLexer
#define yyFlexLexer deci_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL deci::parser_t::symbol_type deci_scanner_t::get_next_token()

#include "iec61131.y.hpp"

#include <sstream>

class deci_scanner_t : public deci_FlexLexer {
	std::string fname;
	deci::location cloc;
	bool interactive;
	std::stringstream ssInput;
public:
	deci::parser_t::symbol_type get_next_token();

	// 使用文件作为输入到词法分析器
	deci_scanner_t(std::istream& input, const std::string& fname, bool interactive)
		:deci_FlexLexer(&input), fname(fname), cloc(), interactive(interactive)
	{
		this->cloc.initialize(&this->fname, 1, 1);
	}

	// 使用字符串作为输入到词法分析器
	deci_scanner_t(std::string& input, bool interactive)
		:deci_FlexLexer(nullptr), ssInput(input), cloc(), interactive(interactive)
	{
		switch_streams(&ssInput, 0);
		this->cloc.initialize(&this->fname, 1, 1);
	}
};

#endif /* __DECI_SCANNER_HEADER__ */