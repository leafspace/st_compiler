%{
    #include <deci.hpp>
    #include <deci/scanner_t.hpp>
    #include "iec61131.y.hpp"
    
    #define YY_NO_UNISTD_H
    #define yyterminate() return deci::parser_t::make_END();
    #define YY_USER_ACTION this->cloc.step(); this->cloc.columns(yyleng); 
    #define DEFAULT_LOCATION_ARGUMENT this->cloc
%}

%option yylineno
%option caseless
%option nodefault
%option noyywrap
%option c++
%option yyclass="deci_scanner_t"
%option prefix="deci_"

L             [A-Z]
D             [0-9]

ASC           [\x00-\x7f]
ASCN          [\x00-\t\v-\x7f]
U             [\x80-\xbf]
U2            [\xc2-\xdf]
U3            [\xe0-\xef]
U4            [\xf0-\xf4]

UANY          {ASC}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
UANYN         {ASCN}|{U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}
UONLY         {U2}{U}|{U3}{U}{U}|{U4}{U}{U}{U}

%x DIV_COMMENTS
%x BRACE_COMMENTS

%%

"/*"                 { BEGIN(DIV_COMMENTS); }
<DIV_COMMENTS>"*/"   { BEGIN(INITIAL); }
<DIV_COMMENTS>\n     { this->cloc.lines(); this->cloc.step(); /* Ingnore multiline comments */ }
<DIV_COMMENTS>.      { /* Ingnore multiline comments */ }

"(*"                 { BEGIN(BRACE_COMMENTS); }
<BRACE_COMMENTS>"*)" { BEGIN(INITIAL); }
<BRACE_COMMENTS>\n   { this->cloc.lines(); this->cloc.step(); /* Ingnore multiline comments */ }
<BRACE_COMMENTS>.    { /* Ingnore multiline comments */ }

"//".*               { /* Ignore single line comments */ }

EXIT                 { return deci::parser_t::make_EXIT(DEFAULT_LOCATION_ARGUMENT);           }
RETURN               { return deci::parser_t::make_RETURN(DEFAULT_LOCATION_ARGUMENT);         }
WHILE                { return deci::parser_t::make_WHILE(DEFAULT_LOCATION_ARGUMENT);          }
END_WHILE            { return deci::parser_t::make_END_WHILE(DEFAULT_LOCATION_ARGUMENT);      }
REPEAT               { return deci::parser_t::make_REPEAT(DEFAULT_LOCATION_ARGUMENT);         }
UNTIL                { return deci::parser_t::make_UNTIL(DEFAULT_LOCATION_ARGUMENT);          }
END_REPEAT           { return deci::parser_t::make_END_REPEAT(DEFAULT_LOCATION_ARGUMENT);     }
FOR                  { return deci::parser_t::make_FOR(DEFAULT_LOCATION_ARGUMENT);            }
TO                   { return deci::parser_t::make_TO(DEFAULT_LOCATION_ARGUMENT);             }
BY                   { return deci::parser_t::make_BY(DEFAULT_LOCATION_ARGUMENT);             }
DO                   { return deci::parser_t::make_DO(DEFAULT_LOCATION_ARGUMENT);             }
END_FOR              { return deci::parser_t::make_END_FOR(DEFAULT_LOCATION_ARGUMENT);        }
IF                   { return deci::parser_t::make_IF(DEFAULT_LOCATION_ARGUMENT);             }
THEN                 { return deci::parser_t::make_THEN(DEFAULT_LOCATION_ARGUMENT);           }
ELSEIF               { return deci::parser_t::make_ELSEIF(DEFAULT_LOCATION_ARGUMENT);         }
ELSIF                { return deci::parser_t::make_ELSIF(DEFAULT_LOCATION_ARGUMENT);          }
ELSE                 { return deci::parser_t::make_ELSE(DEFAULT_LOCATION_ARGUMENT);           }
END_IF               { return deci::parser_t::make_END_IF(DEFAULT_LOCATION_ARGUMENT);         }
CASE                 { return deci::parser_t::make_CASE(DEFAULT_LOCATION_ARGUMENT);           }
OF                   { return deci::parser_t::make_OF(DEFAULT_LOCATION_ARGUMENT);             }
END_CASE             { return deci::parser_t::make_END_CASE(DEFAULT_LOCATION_ARGUMENT);       }
XOR                  { return deci::parser_t::make_XOR(DEFAULT_LOCATION_ARGUMENT);            }
(OR|[|])             { return deci::parser_t::make_OR(DEFAULT_LOCATION_ARGUMENT);             }
MOD                  { return deci::parser_t::make_MOD(DEFAULT_LOCATION_ARGUMENT);            }
(NOT|[~])            { return deci::parser_t::make_NOT(DEFAULT_LOCATION_ARGUMENT);            }
(AND|[&])            { return deci::parser_t::make_AND(DEFAULT_LOCATION_ARGUMENT);            }
[=]                  { return deci::parser_t::make_EQU(DEFAULT_LOCATION_ARGUMENT);            }
\<\>                 { return deci::parser_t::make_NEQU(DEFAULT_LOCATION_ARGUMENT);           }
\>                   { return deci::parser_t::make_GR(DEFAULT_LOCATION_ARGUMENT);             }
\<                   { return deci::parser_t::make_LS(DEFAULT_LOCATION_ARGUMENT);             }
\>\=                 { return deci::parser_t::make_GE(DEFAULT_LOCATION_ARGUMENT);             }
\<\=                 { return deci::parser_t::make_LE(DEFAULT_LOCATION_ARGUMENT);             }
\*\*                 { return deci::parser_t::make_POW(DEFAULT_LOCATION_ARGUMENT);            }
\;                   { return deci::parser_t::make_ST_END(DEFAULT_LOCATION_ARGUMENT);         }
:=                   { return deci::parser_t::make_ASSIGN(DEFAULT_LOCATION_ARGUMENT);         }
\:                   { return deci::parser_t::make_COLON(DEFAULT_LOCATION_ARGUMENT);          }
\+                   { return deci::parser_t::make_SUM(DEFAULT_LOCATION_ARGUMENT);            }
\-                   { return deci::parser_t::make_SUB(DEFAULT_LOCATION_ARGUMENT);            }
\*                   { return deci::parser_t::make_MUL(DEFAULT_LOCATION_ARGUMENT);            }
,                    { return deci::parser_t::make_COMMA(DEFAULT_LOCATION_ARGUMENT);          }
\/                   { return deci::parser_t::make_DIV(DEFAULT_LOCATION_ARGUMENT);            }
\)                   { return deci::parser_t::make_BCLOSE(DEFAULT_LOCATION_ARGUMENT);         }
\(                   { return deci::parser_t::make_BOPEN(DEFAULT_LOCATION_ARGUMENT);          }
\]                   { return deci::parser_t::make_CCLOSE(DEFAULT_LOCATION_ARGUMENT);         }
\[                   { return deci::parser_t::make_COPEN(DEFAULT_LOCATION_ARGUMENT);          }

ON                   { return deci::parser_t::make_BOOLEAN(true,  DEFAULT_LOCATION_ARGUMENT); }
OFF                  { return deci::parser_t::make_BOOLEAN(false, DEFAULT_LOCATION_ARGUMENT); }
TRUE                 { return deci::parser_t::make_BOOLEAN(true,  DEFAULT_LOCATION_ARGUMENT); }
FALSE                { return deci::parser_t::make_BOOLEAN(false, DEFAULT_LOCATION_ARGUMENT); }
BOOL#0               { return deci::parser_t::make_BOOLEAN(false, DEFAULT_LOCATION_ARGUMENT); }
BOOL#1               { return deci::parser_t::make_BOOLEAN(true,  DEFAULT_LOCATION_ARGUMENT); }

(SINT|INT|DINT|USINT|UINT|UDINT|REAL)\#(\-|\+)?[0-9]+(\.)?[0-9]* {
                        return deci::parser_t::make_NUMBER_STR(yytext, DEFAULT_LOCATION_ARGUMENT);
                     }

(({L}|_({L}|{D}))(_?({L}|{D}))*)+(_+)?(\[[0-9]+((,)[0-9]+)?\])?(\.({L}|_({L}|{D}))(_?({L}|{D}))*)?(_+)?(\[[0-9]+((,)[0-9]+)?\])? {
                        return deci::parser_t::make_IDENTIFIER(yytext, DEFAULT_LOCATION_ARGUMENT);
                     }

[0-9]+\#([0-9]|[A-Z])+(_?([0-9]|[A-Z])+)* {
                        return deci::parser_t::make_NUMBER_STR(yytext, DEFAULT_LOCATION_ARGUMENT);
                     }

[0-9]+\.[0-9]*       {
                        return deci::parser_t::make_NUMBER(atof(yytext), DEFAULT_LOCATION_ARGUMENT);
                     }

[0-9]+               {
                        return deci::parser_t::make_NUMBER(atof(yytext), DEFAULT_LOCATION_ARGUMENT);
                     }

[\n]                 {
                        if (this->interactive)
                        {
                          return deci::parser_t::make_END(DEFAULT_LOCATION_ARGUMENT);
                        }
                        else
                        {
                          this->cloc.lines();
                          this->cloc.step();
                        }
                     }

<<EOF>>              {
                        return deci::parser_t::make_END(DEFAULT_LOCATION_ARGUMENT);
                     }

[ \r\t\v]            {
                        // IGNORE SPACES;
                     }

.                    {
                        throw deci::parser_t::syntax_error(DEFAULT_LOCATION_ARGUMENT, "未知的标识符");
                     }
%%
