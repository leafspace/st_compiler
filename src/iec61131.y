%skeleton "lalr1.cc"
%require "3.0"
%defines
%locations
%define api.parser.class {parser_t}

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace {deci}

%code requires {
  #include <deci.hpp>

  class deci_scanner_t;
}

%code top
{
  #include "iec61131.y.hpp"
  #include <deci/scanner_t.hpp>

  #define yylex(SCANNER) SCANNER.get_next_token()

  using namespace deci;
}

%lex-param   { deci_scanner_t& scanner }

%parse-param { deci_scanner_t& scanner }
%parse-param { std::shared_ptr<ast_t>& ast }
%parse-param { std::vector<SyntaxError>& errors }
%parse-param { symbol_table& symbols }

%define parse.trace
%define parse.error custom

%define api.token.prefix {TOK_}

%left SUM SUB
%left MUL DIV
%right POW

%precedence NUMBER
%precedence NUMBER_STR
%precedence ASSIGN
%precedence COLON

%token END 0           "end of file"
%token <bool>        BOOLEAN    "boolean"
%token <double>      NUMBER     "number" 
%token <std::string> NUMBER_STR "number_str"
%token <std::string> IDENTIFIER "identifier"
%token               BOPEN      "("
%token               BCLOSE     ")"
%token               COPEN      "["
%token               CCLOSE     "]"
%token               SUM        "+"
%token               SUB        "-"
%token               MUL        "*"
%token               DIV        "/"
%token               MOD        "MOD"
%token               NOT        "NOT"
%token               ASSIGN     ":="
%token               COMMA      ","
%token               XOR        "XOR"
%token               OR         "OR"
%token               AND        "AND"
%token               EQU        "="
%token               NEQU       "<>"
%token               GR         ">"
%token               LS         "<"
%token               GE         ">="
%token               LE         "<="
%token               POW        "**"
%token               ST_END     ";"
%token               COLON      ":"
%token               IF         "IF"
%token               THEN       "THEN"
%token               ELSIF      "ELSIF"
%token               ELSEIF     "ELSEIF"
%token               ELSE       "ELSE"
%token               END_IF     "END_IF"
%token               CASE       "CASE"
%token               OF         "OF"
%token               END_CASE   "END_CASE"
%token               FOR        "FOR"
%token               TO         "TO"
%token               BY         "BY"
%token               DO         "DO"
%token               END_FOR    "END_FOR"
%token               WHILE      "WHILE"
%token               END_WHILE  "END_WHILE"
%token               REPEAT     "REPEAT"
%token               UNTIL      "UNTIL"
%token               END_REPEAT "END_REPEAT"
%token               EXIT       "EXIT"
%token               RETURN     "RETURN"

%type <ast_arg_list_t*>         argument_list "argument list"

%type <ast_t*>                  statement_list loop_statement_list elsif_statement_list case_statement_list
%type <ast_item_t*>             statement expression_statement expression
%type <ast_item_t*>             assign_expr or_expr xor_expr and_expr eql_expr cmp_expr
%type <ast_item_t*>             add_expr mul_expr pow_expr unary_expr postfix_expr primary_expr
%type <ast_item_t*>             if_statement elsif_statement
%type <ast_item_t*>             case_statement case_enumeration_statement for_statement while_statement repeat_statement 
%type <ast_exit_t*>             exit_statement

%start entry

%%

entry:
    statement_list                          { ast->Append($1);  ast->SetLocations({@1}); $1->Parent(ast.get()); }
;

statement_list:
    statement                               { $$ = new ast_t(); if ($1 != nullptr) { $$->Append($1); $$->SetLocations({@1});     $1->Parent($$); } }
  | statement_list statement                { $$ = $1;          if ($2 != nullptr) { $$->Append($2); $$->SetLocations({@1, @2}); $2->Parent($$); } }
;

loop_statement_list:
    statement                               { $$ = new ast_t(); if ($1 != nullptr) { $$->Append($1); $$->SetLocations({@1});     $1->Parent($$); } }
  | statement_list statement                { $$ = $1;          if ($2 != nullptr) { $$->Append($2); $$->SetLocations({@1, @2}); $2->Parent($$); } }
  | exit_statement                          { $$ = new ast_t(); if ($1 != nullptr) { $$->Append($1); $$->SetLocations({@1});     $1->Parent($$); } }
  | statement_list exit_statement           { $$ = $1;          if ($2 != nullptr) { $$->Append($2); $$->SetLocations({@1, @2}); $2->Parent($$); } }
;


statement:
    error ST_END                            { $$ = new ast_error_t();                            }
  | ST_END                                  { $$ = nullptr;                                      }
  | exit_statement                          { $$ = nullptr;                                      }
  | expression_statement ST_END             { $$ = $1;          $$->SetLocations({@1, @2});      }
  | if_statement         ST_END             { $$ = $1;          $$->SetLocations({@1, @2});      }
  | case_statement       ST_END             { $$ = $1;          $$->SetLocations({@1, @2});      }
  | for_statement        ST_END             { $$ = $1;          $$->SetLocations({@1, @2});      }
  | while_statement      ST_END             { $$ = $1;          $$->SetLocations({@1, @2});      }
  | repeat_statement     ST_END             { $$ = $1;          $$->SetLocations({@1, @2});      }
;

exit_statement:
    EXIT                 ST_END             { $$ = new ast_exit_t(); $$->SetLocations({@1, @2}); }
  | RETURN               ST_END             { $$ = new ast_exit_t(); $$->SetLocations({@1, @2}); }
;

expression_statement:
    expression                              { $$ = $1;          $$->SetLocations({@1});      }
;

expression:
    assign_expr                             { $$ = $1;          $$->SetLocations({@1});      }
;

assign_expr:
    or_expr                                 { $$ = new ast_return_t($1);  $$->SetLocations({@1});                                        $1->Parent($$);                                    }
  | IDENTIFIER ASSIGN or_expr               { $$ = new ast_set_t($1, $3); $$->SetLocations({@1, @2, @3}); $$->SetIdentifierLocation(@1); $3->Parent($$); symbols.AddSymbol(symbol($1, @1)); }
  | IDENTIFIER EQU or_expr                  { $$ = new ast_set_t($1, $3); $$->SetLocations({@1, @2, @3}); $$->SetIdentifierLocation(@1); $3->Parent($$); symbols.AddSymbol(symbol($1, @1)); }
;

or_expr:
    xor_expr                                { $$ = $1; $$->SetLocations({@1});                                                                     }
  | or_expr OR xor_expr                     { $$ = new ast_binary_t("or", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
;

xor_expr:
    and_expr                                { $$ = $1; $$->SetLocations({@1});                                                                      }
  | xor_expr XOR and_expr                   { $$ = new ast_binary_t("xor", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
;

and_expr:
    eql_expr                                { $$ = $1; $$->SetLocations({@1});                                                                      }
  | and_expr AND eql_expr                   { $$ = new ast_binary_t("and", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
;

eql_expr:
    cmp_expr                                { $$ = $1; $$->SetLocations({@1});                                                                      }
  | eql_expr EQU cmp_expr                   { $$ = new ast_binary_t("eq", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$);  }
  | eql_expr NEQU cmp_expr                  { $$ = new ast_binary_t("neq", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
;

cmp_expr:
    add_expr                                { $$ = $1; $$->SetLocations({@1});                                                                      }
  | cmp_expr LS add_expr                    { $$ = new ast_binary_t("ls", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$);  }
  | cmp_expr GR add_expr                    { $$ = new ast_binary_t("gr", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$);  }
  | cmp_expr LE add_expr                    { $$ = new ast_binary_t("le", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$);  }
  | cmp_expr GE add_expr                    { $$ = new ast_binary_t("ge", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$);  }
;

add_expr:
    mul_expr                                { $$ = $1; $$->SetLocations({@1});                                                                      }
  | add_expr SUM mul_expr                   { $$ = new ast_binary_t("sum", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
  | add_expr SUB mul_expr                   { $$ = new ast_binary_t("sub", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
;

mul_expr:
    pow_expr                                { $$ = $1; $$->SetLocations({@1});                                                                      }
  | mul_expr MUL pow_expr                   { $$ = new ast_binary_t("mul", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
  | mul_expr MOD pow_expr                   { $$ = new ast_binary_t("mod", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
  | mul_expr DIV pow_expr                   { $$ = new ast_binary_t("div", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
;

pow_expr:
    unary_expr                              { $$ = $1; $$->SetLocations({@1});                                                                      }
  | pow_expr POW unary_expr                 { $$ = new ast_binary_t("pow", $1, $3); $$->SetLocations({@1, @2, @3}); $1->Parent($$); $3->Parent($$); }
;

unary_expr:
    postfix_expr                            { $$ = $1; $$->SetLocations({@1});                                              }
  | NOT unary_expr                          { $$ = new ast_unary_t("not", $2 ); $$->SetLocations({@1, @2}); $2->Parent($$); }
  | "~" unary_expr                          { $$ = new ast_unary_t("not", $2 ); $$->SetLocations({@1, @2}); $2->Parent($$); }
  | SUM unary_expr                          { $$ = new ast_unary_t("sum", $2 ); $$->SetLocations({@1, @2}); $2->Parent($$); }
  | SUB unary_expr                          { $$ = new ast_unary_t("sub", $2 ); $$->SetLocations({@1, @2}); $2->Parent($$); }
;

postfix_expr:
    primary_expr                           { $$ = $1; $$->SetLocations({@1});                                                                                                                           }
  | IDENTIFIER BOPEN BCLOSE                { $$ = new ast_postfix_t($1, nullptr); $$->SetLocations({@1, @2, @3});     $$->SetIdentifierLocation(@1);                 symbols.AddSymbol(symbol($1, @1)); }
  | IDENTIFIER BOPEN argument_list BCLOSE  { $$ = new ast_postfix_t($1, $3);      $$->SetLocations({@1, @2, @3, @4}); $$->SetIdentifierLocation(@1); $3->Parent($$); symbols.AddSymbol(symbol($1, @1)); }
;

argument_list:
    or_expr                                 { $$ = new ast_arg_list_t(); $$->SetLocations({@1});         $$->Append($1); $1->Parent($$); }
  | argument_list COMMA or_expr             { $$ = $1;                   $$->SetLocations({@1, @2, @3}); $$->Append($3); $3->Parent($$); }
;

primary_expr:
    NUMBER                                  { $$ = new ast_number_t($1);     $$->SetLocations({@1});                                                                           }
  | NUMBER_STR                              { $$ = new ast_number_t($1);     $$->SetLocations({@1});                                                                           }
  | BOOLEAN                                 { $$ = new ast_boolean_t($1);    $$->SetLocations({@1});                                                                           }
  | IDENTIFIER                              { $$ = new ast_identifier_t($1); $$->SetLocations({@1});         $$->SetIdentifierLocation(@1); symbols.AddSymbol(symbol($1, @1)); }
  | BOPEN expression BCLOSE                 { $$ = $2;                       $$->SetLocations({@1, @2, @3});                                                                   }
;

elsif_statement:
    ELSIF or_expr THEN statement_list       { $$ = new ast_elsif_t($2, $4); $$->SetLocations({@1, @2, @3, @4});  $2->Parent($$); $4->Parent($$); }
  | ELSEIF or_expr THEN statement_list      { $$ = new ast_elsif_t($2, $4); $$->SetLocations({@1, @2, @3, @4});  $2->Parent($$); $4->Parent($$); }
;

elsif_statement_list:
    elsif_statement                         { $$ = new ast_t(); if ($1 != nullptr) { $$->Append($1); $$->SetLocations({@1});     $1->Parent($$); } }
  | elsif_statement_list elsif_statement    { $$ = $1;          if ($2 != nullptr) { $$->Append($2); $$->SetLocations({@1, @2}); $2->Parent($$); } }
;

if_statement:
    IF or_expr THEN statement_list END_IF                                            { $$ = new ast_if_t($2, $4);         $$->SetLocations({@1, @2, @3, @4, @5});             $2->Parent($$); $4->Parent($$); }
  | IF or_expr THEN statement_list ELSE statement_list END_IF                        { $$ = new ast_if_t($2, $4, $6);     $$->SetLocations({@1, @2, @3, @4, @5, @6, @7});     $2->Parent($$); $4->Parent($$); $6->Parent($$); }
  | IF or_expr THEN statement_list elsif_statement_list ELSE statement_list END_IF   { $$ = new ast_if_t($2, $4, $7, $5); $$->SetLocations({@1, @2, @3, @4, @5, @6, @7, @8}); $2->Parent($$); $4->Parent($$); $5->Parent($$); $7->Parent($$); }
;

case_enumeration_statement:
    NUMBER COLON statement_list                                                      { $$ = new ast_enumeration_t($1, $3); $$->SetLocations({@1, @2, @3}); $3->Parent($$); }
  | NUMBER_STR COLON statement_list                                                  { $$ = new ast_enumeration_t($1, $3); $$->SetLocations({@1, @2, @3}); $3->Parent($$); }
;

case_statement_list:
    case_enumeration_statement                                                       { $$ = new ast_t(); if ($1 != nullptr) { $$->Append($1); $$->SetLocations({@1});     $1->Parent($$); } }   
  | case_statement_list case_enumeration_statement                                   { $$ = $1;          if ($2 != nullptr) { $$->Append($2); $$->SetLocations({@1, @2}); $2->Parent($$); } }
;

case_statement:
    CASE or_expr OF case_statement_list END_CASE                                     { $$ = new ast_case_t($2, $4);     $$->SetLocations({@1, @2, @3, @4, @5});         $2->Parent($$); $4->Parent($$);                 }
  | CASE or_expr OF case_statement_list ELSE statement_list END_CASE                 { $$ = new ast_case_t($2, $4, $6); $$->SetLocations({@1, @2, @3, @4, @5, @6, @7}); $2->Parent($$); $4->Parent($$); $6->Parent($$); }
;

for_statement:
    FOR IDENTIFIER ASSIGN or_expr TO or_expr BY or_expr DO loop_statement_list END_FOR   { $$ = new ast_for_t($2, $4, $6, $10, $8);     $$->SetLocations({@1, @2, @3, @4, @5, @6, @7, @8, @9, @10, @11}); $$->SetIdentifierLocation(@2); symbols.AddSymbol(symbol($2, @2)); $4->Parent($$); $6->Parent($$); $8->Parent($$); $10->Parent($$); }
  | FOR IDENTIFIER ASSIGN or_expr TO or_expr DO loop_statement_list END_FOR              { $$ = new ast_for_t($2, $4, $6, $8, nullptr); $$->SetLocations({@1, @2, @3, @4, @5, @6, @7, @8, @9});           $$->SetIdentifierLocation(@2); symbols.AddSymbol(symbol($2, @2)); $4->Parent($$); $6->Parent($$); $8->Parent($$);                  }
;

while_statement:
    WHILE or_expr DO loop_statement_list END_WHILE      { $$ = new ast_while_t($2, $4);  $$->SetLocations({@1, @2, @3, @4, @5}); $2->Parent($$); $4->Parent($$); }
;

repeat_statement:
    REPEAT loop_statement_list UNTIL or_expr END_REPEAT { $$ = new ast_repeat_t($4, $2); $$->SetLocations({@1, @2, @3, @4, @5}); $2->Parent($$); $4->Parent($$); }
;

%%

const char* symbol_name(deci::parser_t::symbol_kind_type yysymbol)
{
    static const std::map<deci::parser_t::symbol_kind_type, const char*> yy_sname = {
      std::make_pair(deci::parser_t::symbol_kind_type::S_YYEOF, "文件末尾"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_YYerror, "错误"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_YYUNDEF, "未知的令牌"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_BOOLEAN, "BOOL值"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_NUMBER, "数字值"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_NUMBER_STR, "基底数数字值"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_IDENTIFIER, "标识符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_BOPEN, "("),
      std::make_pair(deci::parser_t::symbol_kind_type::S_BCLOSE, ")"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_COPEN, "["),
      std::make_pair(deci::parser_t::symbol_kind_type::S_CCLOSE, "]"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_SUM, "+"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_SUB, "-"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_MUL, "*"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_DIV, "/"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_MOD, "模"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_NOT, "NOT"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_ASSIGN, ":="),
      std::make_pair(deci::parser_t::symbol_kind_type::S_COMMA, ""),
      std::make_pair(deci::parser_t::symbol_kind_type::S_XOR, "XOR"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_OR, "OR"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_AND, "AND"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_EQU, "="),
      std::make_pair(deci::parser_t::symbol_kind_type::S_NEQU, "<>"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_GR, ">"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_LS, "<"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_GE, ">="),
      std::make_pair(deci::parser_t::symbol_kind_type::S_LE, "<="),
      std::make_pair(deci::parser_t::symbol_kind_type::S_POW, "**"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_ST_END, ";"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_COLON, ":"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_IF, "IF"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_THEN, "THEN"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_ELSIF, "ELSIF"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_ELSEIF, "ELSEIF"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_ELSE, "ELSE"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_END_IF, "END_IF"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_CASE, "CASE"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_OF, "OF"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_END_CASE, "END_CASE"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_FOR, "FOR"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_TO, "TO"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_BY, "BY"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_DO, "DO"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_END_FOR, "END_FOR"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_WHILE, "WHILE"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_END_WHILE, "END_WHILE"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_REPEAT, "REPEAT"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_UNTIL, "UNTIL"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_END_REPEAT, "END_REPEAT"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_EXIT, "EXIT"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_RETURN, "RETURN"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_argument_list, "参数列表"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_YYACCEPT, "$accept"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_entry, "入口"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_statement_list, "表达式列表"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_loop_statement_list, "表达式列表"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_statement, "statement"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_exit_statement, "EXIT 退出表达式"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_expression_statement, "expression_statement"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_expression, "expression"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_assign_expr, "赋值分隔符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_or_expr, "或分隔符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_xor_expr, "异或分隔符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_and_expr, "与分隔符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_eql_expr, "判等分隔符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_cmp_expr, "比较分隔符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_add_expr, "加号分隔符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_mul_expr, "减号分隔符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_pow_expr, "指数分隔符"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_unary_expr, "unary_expr"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_postfix_expr, "postfix_expr"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_argument_list, "参数列表"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_primary_expr, "primary_expr"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_if_statement, "IF 选择表达式"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_case_statement_list, "CASE 选择分支"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_case_statement, "CASE 选择表达式"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_for_statement, "FOR 循环表达式"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_while_statement, "WHILE 循环表达式"),
      std::make_pair(deci::parser_t::symbol_kind_type::S_repeat_statement, "REPEAT 循环表达式"),
    };

    if (yy_sname.find(yysymbol) != yy_sname.end())
    {
      return yy_sname.at(yysymbol);
    }
    return YY_NULLPTR;
}

void handle_error(std::vector<deci::SyntaxError>& errors, 
    const deci::location& loc, const std::string & msg)
{
    SyntaxError errorInfo;
    errorInfo.beginLine = loc.begin.line;
    errorInfo.beginColumn = loc.begin.column;
    errorInfo.endLine = loc.end.line;
    errorInfo.endColumn = loc.end.column;
    errorInfo.msg = msg;
    errorInfo.type = deci::SyntaxType::SyntaxError_Syntax;

    errors.push_back(errorInfo);
    // std::cout << loc << ": 语法错误:" <<  msg << std::endl;
}

// 产生错误处理
void deci::parser_t::error (const location_type& loc, const std::string& msg) 
{
    ::handle_error(errors, loc, msg);
}

// 错误信息
void deci::parser_t::report_syntax_error (const context& ctx) const
{
    std::string refMsg;
    // Report the tokens expected at this point.
    {
        enum { TOKENMAX = 5 };
        symbol_kind_type expected[TOKENMAX];
        int n = ctx.expected_tokens(expected, TOKENMAX);

        refMsg = refMsg + "异常发生在";
        for (int i = 0; i < n; ++i)
        {
            refMsg = refMsg + " '" + ::symbol_name(expected[i]) + "' ";
            if (i != (n - 1))
            {
                refMsg = refMsg + "或";
            }
        }
        refMsg = refMsg + "之后";
        
    }
    
    // Report the unexpected token.
    {
        symbol_kind_type lookahead = ctx.token ();
        if (lookahead != symbol_kind::S_YYEMPTY)
        {
            refMsg = refMsg + "在";
            refMsg = refMsg + " '" + ::symbol_name(lookahead) + "' ";
            refMsg = refMsg + "之前";
            
        }
    }

    ::handle_error(errors, ctx.location(), refMsg);
}