// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// "%code top" blocks.
#line 19 "3rd/iec61131.y"

  #include "iec61131.y.hpp"
  #include <deci/scanner_t.hpp>

  #define yylex(SCANNER) SCANNER.get_next_token()

  using namespace deci;

#line 48 "3rd/iec61131.y.cpp"




#include "iec61131.y.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 10 "3rd/iec61131.y"
namespace deci {
#line 148 "3rd/iec61131.y.cpp"

  /// Build a parser object.
  parser_t::parser_t (deci_scanner_t& scanner_yyarg, std::shared_ptr<ast_t>& ast_yyarg, std::vector<SyntaxError>& errors_yyarg, symbol_table& symbols_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      ast (ast_yyarg),
      errors (errors_yyarg),
      symbols (symbols_yyarg)
  {}

  parser_t::~parser_t ()
  {}

  parser_t::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  parser_t::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser_t::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser_t::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser_t::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser_t::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser_t::symbol_kind_type
  parser_t::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser_t::stack_symbol_type::stack_symbol_type ()
  {}

  parser_t::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_52_argument_list_: // "argument list"
      case symbol_kind::S_argument_list: // argument_list
        value.YY_MOVE_OR_COPY< ast_arg_list_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exit_statement: // exit_statement
        value.YY_MOVE_OR_COPY< ast_exit_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_assign_expr: // assign_expr
      case symbol_kind::S_or_expr: // or_expr
      case symbol_kind::S_xor_expr: // xor_expr
      case symbol_kind::S_and_expr: // and_expr
      case symbol_kind::S_eql_expr: // eql_expr
      case symbol_kind::S_cmp_expr: // cmp_expr
      case symbol_kind::S_add_expr: // add_expr
      case symbol_kind::S_mul_expr: // mul_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_elsif_statement: // elsif_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_case_enumeration_statement: // case_enumeration_statement
      case symbol_kind::S_case_statement: // case_statement
      case symbol_kind::S_for_statement: // for_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_repeat_statement: // repeat_statement
        value.YY_MOVE_OR_COPY< ast_item_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_loop_statement_list: // loop_statement_list
      case symbol_kind::S_elsif_statement_list: // elsif_statement_list
      case symbol_kind::S_case_statement_list: // case_statement_list
        value.YY_MOVE_OR_COPY< ast_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER_STR: // "number_str"
      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser_t::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_52_argument_list_: // "argument list"
      case symbol_kind::S_argument_list: // argument_list
        value.move< ast_arg_list_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exit_statement: // exit_statement
        value.move< ast_exit_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_assign_expr: // assign_expr
      case symbol_kind::S_or_expr: // or_expr
      case symbol_kind::S_xor_expr: // xor_expr
      case symbol_kind::S_and_expr: // and_expr
      case symbol_kind::S_eql_expr: // eql_expr
      case symbol_kind::S_cmp_expr: // cmp_expr
      case symbol_kind::S_add_expr: // add_expr
      case symbol_kind::S_mul_expr: // mul_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_elsif_statement: // elsif_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_case_enumeration_statement: // case_enumeration_statement
      case symbol_kind::S_case_statement: // case_statement
      case symbol_kind::S_for_statement: // for_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_repeat_statement: // repeat_statement
        value.move< ast_item_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_loop_statement_list: // loop_statement_list
      case symbol_kind::S_elsif_statement_list: // elsif_statement_list
      case symbol_kind::S_case_statement_list: // case_statement_list
        value.move< ast_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER_STR: // "number_str"
      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser_t::stack_symbol_type&
  parser_t::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_52_argument_list_: // "argument list"
      case symbol_kind::S_argument_list: // argument_list
        value.copy< ast_arg_list_t* > (that.value);
        break;

      case symbol_kind::S_exit_statement: // exit_statement
        value.copy< ast_exit_t* > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_assign_expr: // assign_expr
      case symbol_kind::S_or_expr: // or_expr
      case symbol_kind::S_xor_expr: // xor_expr
      case symbol_kind::S_and_expr: // and_expr
      case symbol_kind::S_eql_expr: // eql_expr
      case symbol_kind::S_cmp_expr: // cmp_expr
      case symbol_kind::S_add_expr: // add_expr
      case symbol_kind::S_mul_expr: // mul_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_elsif_statement: // elsif_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_case_enumeration_statement: // case_enumeration_statement
      case symbol_kind::S_case_statement: // case_statement
      case symbol_kind::S_for_statement: // for_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_repeat_statement: // repeat_statement
        value.copy< ast_item_t* > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_loop_statement_list: // loop_statement_list
      case symbol_kind::S_elsif_statement_list: // elsif_statement_list
      case symbol_kind::S_case_statement_list: // case_statement_list
        value.copy< ast_t* > (that.value);
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_NUMBER_STR: // "number_str"
      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser_t::stack_symbol_type&
  parser_t::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_52_argument_list_: // "argument list"
      case symbol_kind::S_argument_list: // argument_list
        value.move< ast_arg_list_t* > (that.value);
        break;

      case symbol_kind::S_exit_statement: // exit_statement
        value.move< ast_exit_t* > (that.value);
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_assign_expr: // assign_expr
      case symbol_kind::S_or_expr: // or_expr
      case symbol_kind::S_xor_expr: // xor_expr
      case symbol_kind::S_and_expr: // and_expr
      case symbol_kind::S_eql_expr: // eql_expr
      case symbol_kind::S_cmp_expr: // cmp_expr
      case symbol_kind::S_add_expr: // add_expr
      case symbol_kind::S_mul_expr: // mul_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_elsif_statement: // elsif_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_case_enumeration_statement: // case_enumeration_statement
      case symbol_kind::S_case_statement: // case_statement
      case symbol_kind::S_for_statement: // for_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_repeat_statement: // repeat_statement
        value.move< ast_item_t* > (that.value);
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_loop_statement_list: // loop_statement_list
      case symbol_kind::S_elsif_statement_list: // elsif_statement_list
      case symbol_kind::S_case_statement_list: // case_statement_list
        value.move< ast_t* > (that.value);
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (that.value);
        break;

      case symbol_kind::S_NUMBER_STR: // "number_str"
      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser_t::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser_t::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser_t::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser_t::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser_t::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser_t::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser_t::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser_t::debug_level_type
  parser_t::debug_level () const
  {
    return yydebug_;
  }

  void
  parser_t::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser_t::state_type
  parser_t::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser_t::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser_t::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser_t::operator() ()
  {
    return parse ();
  }

  int
  parser_t::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_52_argument_list_: // "argument list"
      case symbol_kind::S_argument_list: // argument_list
        yylhs.value.emplace< ast_arg_list_t* > ();
        break;

      case symbol_kind::S_exit_statement: // exit_statement
        yylhs.value.emplace< ast_exit_t* > ();
        break;

      case symbol_kind::S_statement: // statement
      case symbol_kind::S_expression_statement: // expression_statement
      case symbol_kind::S_expression: // expression
      case symbol_kind::S_assign_expr: // assign_expr
      case symbol_kind::S_or_expr: // or_expr
      case symbol_kind::S_xor_expr: // xor_expr
      case symbol_kind::S_and_expr: // and_expr
      case symbol_kind::S_eql_expr: // eql_expr
      case symbol_kind::S_cmp_expr: // cmp_expr
      case symbol_kind::S_add_expr: // add_expr
      case symbol_kind::S_mul_expr: // mul_expr
      case symbol_kind::S_pow_expr: // pow_expr
      case symbol_kind::S_unary_expr: // unary_expr
      case symbol_kind::S_postfix_expr: // postfix_expr
      case symbol_kind::S_primary_expr: // primary_expr
      case symbol_kind::S_elsif_statement: // elsif_statement
      case symbol_kind::S_if_statement: // if_statement
      case symbol_kind::S_case_enumeration_statement: // case_enumeration_statement
      case symbol_kind::S_case_statement: // case_statement
      case symbol_kind::S_for_statement: // for_statement
      case symbol_kind::S_while_statement: // while_statement
      case symbol_kind::S_repeat_statement: // repeat_statement
        yylhs.value.emplace< ast_item_t* > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_loop_statement_list: // loop_statement_list
      case symbol_kind::S_elsif_statement_list: // elsif_statement_list
      case symbol_kind::S_case_statement_list: // case_statement_list
        yylhs.value.emplace< ast_t* > ();
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_NUMBER_STR: // "number_str"
      case symbol_kind::S_IDENTIFIER: // "identifier"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // entry: statement_list
#line 115 "3rd/iec61131.y"
                                            { ast->Append(yystack_[0].value.as < ast_t* > ());  ast->SetLocations({yystack_[0].location}); yystack_[0].value.as < ast_t* > ()->Parent(ast.get()); }
#line 815 "3rd/iec61131.y.cpp"
    break;

  case 3: // statement_list: statement
#line 119 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_t* > () = new ast_t(); if (yystack_[0].value.as < ast_item_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[0].location});     yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 821 "3rd/iec61131.y.cpp"
    break;

  case 4: // statement_list: statement_list statement
#line 120 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_t* > () = yystack_[1].value.as < ast_t* > ();          if (yystack_[0].value.as < ast_item_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 827 "3rd/iec61131.y.cpp"
    break;

  case 5: // loop_statement_list: statement
#line 124 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_t* > () = new ast_t(); if (yystack_[0].value.as < ast_item_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[0].location});     yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 833 "3rd/iec61131.y.cpp"
    break;

  case 6: // loop_statement_list: statement_list statement
#line 125 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_t* > () = yystack_[1].value.as < ast_t* > ();          if (yystack_[0].value.as < ast_item_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 839 "3rd/iec61131.y.cpp"
    break;

  case 7: // loop_statement_list: exit_statement
#line 126 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_t* > () = new ast_t(); if (yystack_[0].value.as < ast_exit_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_exit_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[0].location});     yystack_[0].value.as < ast_exit_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 845 "3rd/iec61131.y.cpp"
    break;

  case 8: // loop_statement_list: statement_list exit_statement
#line 127 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_t* > () = yystack_[1].value.as < ast_t* > ();          if (yystack_[0].value.as < ast_exit_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_exit_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_exit_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 851 "3rd/iec61131.y.cpp"
    break;

  case 9: // statement: error ";"
#line 132 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_error_t();                            }
#line 857 "3rd/iec61131.y.cpp"
    break;

  case 10: // statement: ";"
#line 133 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = nullptr;                                      }
#line 863 "3rd/iec61131.y.cpp"
    break;

  case 11: // statement: exit_statement
#line 134 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = nullptr;                                      }
#line 869 "3rd/iec61131.y.cpp"
    break;

  case 12: // statement: expression_statement ";"
#line 135 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[1].value.as < ast_item_t* > ();          yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location});      }
#line 875 "3rd/iec61131.y.cpp"
    break;

  case 13: // statement: if_statement ";"
#line 136 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[1].value.as < ast_item_t* > ();          yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location});      }
#line 881 "3rd/iec61131.y.cpp"
    break;

  case 14: // statement: case_statement ";"
#line 137 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[1].value.as < ast_item_t* > ();          yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location});      }
#line 887 "3rd/iec61131.y.cpp"
    break;

  case 15: // statement: for_statement ";"
#line 138 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[1].value.as < ast_item_t* > ();          yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location});      }
#line 893 "3rd/iec61131.y.cpp"
    break;

  case 16: // statement: while_statement ";"
#line 139 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[1].value.as < ast_item_t* > ();          yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location});      }
#line 899 "3rd/iec61131.y.cpp"
    break;

  case 17: // statement: repeat_statement ";"
#line 140 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[1].value.as < ast_item_t* > ();          yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location});      }
#line 905 "3rd/iec61131.y.cpp"
    break;

  case 18: // exit_statement: "EXIT" ";"
#line 144 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_exit_t* > () = new ast_exit_t(); yylhs.value.as < ast_exit_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); }
#line 911 "3rd/iec61131.y.cpp"
    break;

  case 19: // exit_statement: "RETURN" ";"
#line 145 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_exit_t* > () = new ast_exit_t(); yylhs.value.as < ast_exit_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); }
#line 917 "3rd/iec61131.y.cpp"
    break;

  case 20: // expression_statement: expression
#line 149 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > ();          yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});      }
#line 923 "3rd/iec61131.y.cpp"
    break;

  case 21: // expression: assign_expr
#line 153 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > ();          yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});      }
#line 929 "3rd/iec61131.y.cpp"
    break;

  case 22: // assign_expr: or_expr
#line 157 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_return_t(yystack_[0].value.as < ast_item_t* > ());  yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                        yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ());                                    }
#line 935 "3rd/iec61131.y.cpp"
    break;

  case 23: // assign_expr: "identifier" ":=" or_expr
#line 158 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_set_t(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yylhs.value.as < ast_item_t* > ()->SetIdentifierLocation(yystack_[2].location); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); symbols.AddSymbol(symbol(yystack_[2].value.as < std::string > (), yystack_[2].location)); }
#line 941 "3rd/iec61131.y.cpp"
    break;

  case 24: // assign_expr: "identifier" "=" or_expr
#line 159 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_set_t(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yylhs.value.as < ast_item_t* > ()->SetIdentifierLocation(yystack_[2].location); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); symbols.AddSymbol(symbol(yystack_[2].value.as < std::string > (), yystack_[2].location)); }
#line 947 "3rd/iec61131.y.cpp"
    break;

  case 25: // or_expr: xor_expr
#line 163 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                     }
#line 953 "3rd/iec61131.y.cpp"
    break;

  case 26: // or_expr: or_expr "OR" xor_expr
#line 164 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("or", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 959 "3rd/iec61131.y.cpp"
    break;

  case 27: // xor_expr: and_expr
#line 168 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                      }
#line 965 "3rd/iec61131.y.cpp"
    break;

  case 28: // xor_expr: xor_expr "XOR" and_expr
#line 169 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("xor", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 971 "3rd/iec61131.y.cpp"
    break;

  case 29: // and_expr: eql_expr
#line 173 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                      }
#line 977 "3rd/iec61131.y.cpp"
    break;

  case 30: // and_expr: and_expr "AND" eql_expr
#line 174 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("and", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 983 "3rd/iec61131.y.cpp"
    break;

  case 31: // eql_expr: cmp_expr
#line 178 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                      }
#line 989 "3rd/iec61131.y.cpp"
    break;

  case 32: // eql_expr: eql_expr "=" cmp_expr
#line 179 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("eq", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ());  }
#line 995 "3rd/iec61131.y.cpp"
    break;

  case 33: // eql_expr: eql_expr "<>" cmp_expr
#line 180 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("neq", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1001 "3rd/iec61131.y.cpp"
    break;

  case 34: // cmp_expr: add_expr
#line 184 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                      }
#line 1007 "3rd/iec61131.y.cpp"
    break;

  case 35: // cmp_expr: cmp_expr "<" add_expr
#line 185 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("ls", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ());  }
#line 1013 "3rd/iec61131.y.cpp"
    break;

  case 36: // cmp_expr: cmp_expr ">" add_expr
#line 186 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("gr", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ());  }
#line 1019 "3rd/iec61131.y.cpp"
    break;

  case 37: // cmp_expr: cmp_expr "<=" add_expr
#line 187 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("le", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ());  }
#line 1025 "3rd/iec61131.y.cpp"
    break;

  case 38: // cmp_expr: cmp_expr ">=" add_expr
#line 188 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("ge", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ());  }
#line 1031 "3rd/iec61131.y.cpp"
    break;

  case 39: // add_expr: mul_expr
#line 192 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                      }
#line 1037 "3rd/iec61131.y.cpp"
    break;

  case 40: // add_expr: add_expr "+" mul_expr
#line 193 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("sum", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1043 "3rd/iec61131.y.cpp"
    break;

  case 41: // add_expr: add_expr "-" mul_expr
#line 194 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("sub", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1049 "3rd/iec61131.y.cpp"
    break;

  case 42: // mul_expr: pow_expr
#line 198 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                      }
#line 1055 "3rd/iec61131.y.cpp"
    break;

  case 43: // mul_expr: mul_expr "*" pow_expr
#line 199 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("mul", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1061 "3rd/iec61131.y.cpp"
    break;

  case 44: // mul_expr: mul_expr "MOD" pow_expr
#line 200 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("mod", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1067 "3rd/iec61131.y.cpp"
    break;

  case 45: // mul_expr: mul_expr "/" pow_expr
#line 201 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("div", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1073 "3rd/iec61131.y.cpp"
    break;

  case 46: // pow_expr: unary_expr
#line 205 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                      }
#line 1079 "3rd/iec61131.y.cpp"
    break;

  case 47: // pow_expr: pow_expr "**" unary_expr
#line 206 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_binary_t("pow", yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1085 "3rd/iec61131.y.cpp"
    break;

  case 48: // unary_expr: postfix_expr
#line 210 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                              }
#line 1091 "3rd/iec61131.y.cpp"
    break;

  case 49: // unary_expr: "NOT" unary_expr
#line 211 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_unary_t("not", yystack_[0].value.as < ast_item_t* > () ); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1097 "3rd/iec61131.y.cpp"
    break;

  case 50: // unary_expr: "~" unary_expr
#line 212 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_unary_t("not", yystack_[0].value.as < ast_item_t* > () ); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1103 "3rd/iec61131.y.cpp"
    break;

  case 51: // unary_expr: "+" unary_expr
#line 213 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_unary_t("sum", yystack_[0].value.as < ast_item_t* > () ); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1109 "3rd/iec61131.y.cpp"
    break;

  case 52: // unary_expr: "-" unary_expr
#line 214 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_unary_t("sub", yystack_[0].value.as < ast_item_t* > () ); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1115 "3rd/iec61131.y.cpp"
    break;

  case 53: // postfix_expr: primary_expr
#line 218 "3rd/iec61131.y"
                                           { yylhs.value.as < ast_item_t* > () = yystack_[0].value.as < ast_item_t* > (); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                                                                           }
#line 1121 "3rd/iec61131.y.cpp"
    break;

  case 54: // postfix_expr: "identifier" "(" ")"
#line 219 "3rd/iec61131.y"
                                           { yylhs.value.as < ast_item_t* > () = new ast_postfix_t(yystack_[2].value.as < std::string > (), nullptr); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location});     yylhs.value.as < ast_item_t* > ()->SetIdentifierLocation(yystack_[2].location);                 symbols.AddSymbol(symbol(yystack_[2].value.as < std::string > (), yystack_[2].location)); }
#line 1127 "3rd/iec61131.y.cpp"
    break;

  case 55: // postfix_expr: "identifier" "(" argument_list ")"
#line 220 "3rd/iec61131.y"
                                           { yylhs.value.as < ast_item_t* > () = new ast_postfix_t(yystack_[3].value.as < std::string > (), yystack_[1].value.as < ast_arg_list_t* > ());      yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location}); yylhs.value.as < ast_item_t* > ()->SetIdentifierLocation(yystack_[3].location); yystack_[1].value.as < ast_arg_list_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); symbols.AddSymbol(symbol(yystack_[3].value.as < std::string > (), yystack_[3].location)); }
#line 1133 "3rd/iec61131.y.cpp"
    break;

  case 56: // argument_list: or_expr
#line 224 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_arg_list_t* > () = new ast_arg_list_t(); yylhs.value.as < ast_arg_list_t* > ()->SetLocations({yystack_[0].location});         yylhs.value.as < ast_arg_list_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_arg_list_t* > ()); }
#line 1139 "3rd/iec61131.y.cpp"
    break;

  case 57: // argument_list: argument_list "," or_expr
#line 225 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_arg_list_t* > () = yystack_[2].value.as < ast_arg_list_t* > ();                   yylhs.value.as < ast_arg_list_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yylhs.value.as < ast_arg_list_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_arg_list_t* > ()); }
#line 1145 "3rd/iec61131.y.cpp"
    break;

  case 58: // primary_expr: "number"
#line 229 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_number_t(yystack_[0].value.as < double > ());     yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                           }
#line 1151 "3rd/iec61131.y.cpp"
    break;

  case 59: // primary_expr: "number_str"
#line 230 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_number_t(yystack_[0].value.as < std::string > ());     yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                           }
#line 1157 "3rd/iec61131.y.cpp"
    break;

  case 60: // primary_expr: "boolean"
#line 231 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_boolean_t(yystack_[0].value.as < bool > ());    yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});                                                                           }
#line 1163 "3rd/iec61131.y.cpp"
    break;

  case 61: // primary_expr: "identifier"
#line 232 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_identifier_t(yystack_[0].value.as < std::string > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[0].location});         yylhs.value.as < ast_item_t* > ()->SetIdentifierLocation(yystack_[0].location); symbols.AddSymbol(symbol(yystack_[0].value.as < std::string > (), yystack_[0].location)); }
#line 1169 "3rd/iec61131.y.cpp"
    break;

  case 62: // primary_expr: "(" expression ")"
#line 233 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = yystack_[1].value.as < ast_item_t* > ();                       yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location});                                                                   }
#line 1175 "3rd/iec61131.y.cpp"
    break;

  case 63: // elsif_statement: "ELSIF" or_expr "THEN" statement_list
#line 237 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_elsif_t(yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location});  yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1181 "3rd/iec61131.y.cpp"
    break;

  case 64: // elsif_statement: "ELSEIF" or_expr "THEN" statement_list
#line 238 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_item_t* > () = new ast_elsif_t(yystack_[2].value.as < ast_item_t* > (), yystack_[0].value.as < ast_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location});  yystack_[2].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[0].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1187 "3rd/iec61131.y.cpp"
    break;

  case 65: // elsif_statement_list: elsif_statement
#line 242 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_t* > () = new ast_t(); if (yystack_[0].value.as < ast_item_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[0].location});     yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 1193 "3rd/iec61131.y.cpp"
    break;

  case 66: // elsif_statement_list: elsif_statement_list elsif_statement
#line 243 "3rd/iec61131.y"
                                            { yylhs.value.as < ast_t* > () = yystack_[1].value.as < ast_t* > ();          if (yystack_[0].value.as < ast_item_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 1199 "3rd/iec61131.y.cpp"
    break;

  case 67: // if_statement: "IF" or_expr "THEN" statement_list "END_IF"
#line 247 "3rd/iec61131.y"
                                                                                     { yylhs.value.as < ast_item_t* > () = new ast_if_t(yystack_[3].value.as < ast_item_t* > (), yystack_[1].value.as < ast_t* > ());         yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[4].location, yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location});             yystack_[3].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[1].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1205 "3rd/iec61131.y.cpp"
    break;

  case 68: // if_statement: "IF" or_expr "THEN" statement_list "ELSE" statement_list "END_IF"
#line 248 "3rd/iec61131.y"
                                                                                     { yylhs.value.as < ast_item_t* > () = new ast_if_t(yystack_[5].value.as < ast_item_t* > (), yystack_[3].value.as < ast_t* > (), yystack_[1].value.as < ast_t* > ());     yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[6].location, yystack_[5].location, yystack_[4].location, yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location});     yystack_[5].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[3].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[1].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1211 "3rd/iec61131.y.cpp"
    break;

  case 69: // if_statement: "IF" or_expr "THEN" statement_list elsif_statement_list "ELSE" statement_list "END_IF"
#line 249 "3rd/iec61131.y"
                                                                                     { yylhs.value.as < ast_item_t* > () = new ast_if_t(yystack_[6].value.as < ast_item_t* > (), yystack_[4].value.as < ast_t* > (), yystack_[1].value.as < ast_t* > (), yystack_[3].value.as < ast_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[7].location, yystack_[6].location, yystack_[5].location, yystack_[4].location, yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[6].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[4].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[3].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[1].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1217 "3rd/iec61131.y.cpp"
    break;

  case 70: // case_enumeration_statement: "number" ":" statement_list
#line 253 "3rd/iec61131.y"
                                                                                     { yylhs.value.as < ast_item_t* > () = new ast_enumeration_t(yystack_[2].value.as < double > (), yystack_[0].value.as < ast_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1223 "3rd/iec61131.y.cpp"
    break;

  case 71: // case_enumeration_statement: "number_str" ":" statement_list
#line 254 "3rd/iec61131.y"
                                                                                     { yylhs.value.as < ast_item_t* > () = new ast_enumeration_t(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ast_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1229 "3rd/iec61131.y.cpp"
    break;

  case 72: // case_statement_list: case_enumeration_statement
#line 258 "3rd/iec61131.y"
                                                                                     { yylhs.value.as < ast_t* > () = new ast_t(); if (yystack_[0].value.as < ast_item_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[0].location});     yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 1235 "3rd/iec61131.y.cpp"
    break;

  case 73: // case_statement_list: case_statement_list case_enumeration_statement
#line 259 "3rd/iec61131.y"
                                                                                     { yylhs.value.as < ast_t* > () = yystack_[1].value.as < ast_t* > ();          if (yystack_[0].value.as < ast_item_t* > () != nullptr) { yylhs.value.as < ast_t* > ()->Append(yystack_[0].value.as < ast_item_t* > ()); yylhs.value.as < ast_t* > ()->SetLocations({yystack_[1].location, yystack_[0].location}); yystack_[0].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_t* > ()); } }
#line 1241 "3rd/iec61131.y.cpp"
    break;

  case 74: // case_statement: "CASE" or_expr "OF" case_statement_list "END_CASE"
#line 263 "3rd/iec61131.y"
                                                                                     { yylhs.value.as < ast_item_t* > () = new ast_case_t(yystack_[3].value.as < ast_item_t* > (), yystack_[1].value.as < ast_t* > ());     yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[4].location, yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location});         yystack_[3].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[1].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ());                 }
#line 1247 "3rd/iec61131.y.cpp"
    break;

  case 75: // case_statement: "CASE" or_expr "OF" case_statement_list "ELSE" statement_list "END_CASE"
#line 264 "3rd/iec61131.y"
                                                                                     { yylhs.value.as < ast_item_t* > () = new ast_case_t(yystack_[5].value.as < ast_item_t* > (), yystack_[3].value.as < ast_t* > (), yystack_[1].value.as < ast_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[6].location, yystack_[5].location, yystack_[4].location, yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[5].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[3].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[1].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1253 "3rd/iec61131.y.cpp"
    break;

  case 76: // for_statement: "FOR" "identifier" ":=" or_expr "TO" or_expr "BY" or_expr "DO" loop_statement_list "END_FOR"
#line 268 "3rd/iec61131.y"
                                                                                         { yylhs.value.as < ast_item_t* > () = new ast_for_t(yystack_[9].value.as < std::string > (), yystack_[7].value.as < ast_item_t* > (), yystack_[5].value.as < ast_item_t* > (), yystack_[1].value.as < ast_t* > (), yystack_[3].value.as < ast_item_t* > ());     yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[10].location, yystack_[9].location, yystack_[8].location, yystack_[7].location, yystack_[6].location, yystack_[5].location, yystack_[4].location, yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location}); yylhs.value.as < ast_item_t* > ()->SetIdentifierLocation(yystack_[9].location); symbols.AddSymbol(symbol(yystack_[9].value.as < std::string > (), yystack_[9].location)); yystack_[7].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[5].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[3].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[1].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1259 "3rd/iec61131.y.cpp"
    break;

  case 77: // for_statement: "FOR" "identifier" ":=" or_expr "TO" or_expr "DO" loop_statement_list "END_FOR"
#line 269 "3rd/iec61131.y"
                                                                                         { yylhs.value.as < ast_item_t* > () = new ast_for_t(yystack_[7].value.as < std::string > (), yystack_[5].value.as < ast_item_t* > (), yystack_[3].value.as < ast_item_t* > (), yystack_[1].value.as < ast_t* > (), nullptr); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[8].location, yystack_[7].location, yystack_[6].location, yystack_[5].location, yystack_[4].location, yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location});           yylhs.value.as < ast_item_t* > ()->SetIdentifierLocation(yystack_[7].location); symbols.AddSymbol(symbol(yystack_[7].value.as < std::string > (), yystack_[7].location)); yystack_[5].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[3].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[1].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ());                  }
#line 1265 "3rd/iec61131.y.cpp"
    break;

  case 78: // while_statement: "WHILE" or_expr "DO" loop_statement_list "END_WHILE"
#line 273 "3rd/iec61131.y"
                                                        { yylhs.value.as < ast_item_t* > () = new ast_while_t(yystack_[3].value.as < ast_item_t* > (), yystack_[1].value.as < ast_t* > ());  yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[4].location, yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[3].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[1].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1271 "3rd/iec61131.y.cpp"
    break;

  case 79: // repeat_statement: "REPEAT" loop_statement_list "UNTIL" or_expr "END_REPEAT"
#line 277 "3rd/iec61131.y"
                                                        { yylhs.value.as < ast_item_t* > () = new ast_repeat_t(yystack_[1].value.as < ast_item_t* > (), yystack_[3].value.as < ast_t* > ()); yylhs.value.as < ast_item_t* > ()->SetLocations({yystack_[4].location, yystack_[3].location, yystack_[2].location, yystack_[1].location, yystack_[0].location}); yystack_[3].value.as < ast_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); yystack_[1].value.as < ast_item_t* > ()->Parent(yylhs.value.as < ast_item_t* > ()); }
#line 1277 "3rd/iec61131.y.cpp"
    break;


#line 1281 "3rd/iec61131.y.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        report_syntax_error (yyctx);
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser_t::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser_t::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "boolean", "number",
  "number_str", "identifier", "(", ")", "[", "]", "+", "-", "*", "/",
  "MOD", "NOT", ":=", ",", "XOR", "OR", "AND", "=", "<>", ">", "<", ">=",
  "<=", "**", ";", ":", "IF", "THEN", "ELSIF", "ELSEIF", "ELSE", "END_IF",
  "CASE", "OF", "END_CASE", "FOR", "TO", "BY", "DO", "END_FOR", "WHILE",
  "END_WHILE", "REPEAT", "UNTIL", "END_REPEAT", "EXIT", "RETURN",
  "argument list", "~", "$accept", "entry", "statement_list",
  "loop_statement_list", "statement", "exit_statement",
  "expression_statement", "expression", "assign_expr", "or_expr",
  "xor_expr", "and_expr", "eql_expr", "cmp_expr", "add_expr", "mul_expr",
  "pow_expr", "unary_expr", "postfix_expr", "argument_list",
  "primary_expr", "elsif_statement", "elsif_statement_list",
  "if_statement", "case_enumeration_statement", "case_statement_list",
  "case_statement", "for_statement", "while_statement", "repeat_statement", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser_t::context.
  parser_t::context::context (const parser_t& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser_t::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }




  const signed char parser_t::yypact_ninf_ = -94;

  const signed char parser_t::yytable_ninf_ = -72;

  const short
  parser_t::yypact_[] =
  {
     564,   -16,   -94,   -94,   -94,    93,    41,    72,    72,    72,
     -94,    72,    72,    10,    72,   564,    -9,    38,    72,    71,
      58,   -94,   -94,    68,   -94,   -94,    84,    80,   106,    79,
     149,   101,   151,   143,   -94,   -94,   -94,   100,   155,   157,
     159,   165,   -94,    19,    72,    72,   108,   188,   -94,   -94,
     -94,    36,    -5,   180,    -3,   564,   150,    75,    76,   -94,
     -94,   -94,   -94,   -94,   -94,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
     -94,   -94,   -94,   -94,   -94,   -94,    84,    88,    84,    84,
     -94,   564,   146,    72,   564,    89,    90,    72,    80,   106,
      79,   149,   149,   101,   101,   101,   101,   151,   151,   143,
     143,   143,   -94,   -94,    72,   156,   169,   170,   -94,     4,
      14,   158,   -17,    84,    72,    72,   564,   -94,   -94,    16,
     564,   564,   564,   -94,   -94,    72,   -94,   -94,    53,    60,
     411,   564,   -94,   309,   360,   462,   -14,   564,   564,   -94,
     513,   -94,    72,   564,   207,   258,   -94,    -2,   161,   564,
     -94,   171,   -94
  };

  const signed char
  parser_t::yydefact_[] =
  {
       0,     0,    60,    58,    59,    61,     0,     0,     0,     0,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,    11,     0,    20,    21,    22,    25,    27,    29,
      31,    34,    39,    42,    46,    48,    53,     0,     0,     0,
       0,     0,     9,     0,     0,     0,     0,    61,    51,    52,
      49,     0,     0,     0,     0,     0,     0,     3,    11,    18,
      19,    50,     1,     4,    12,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      13,    14,    15,    16,    17,    54,    56,     0,    23,    24,
      62,     0,     0,     0,     0,     4,    11,     0,    26,    28,
      30,    32,    33,    36,    35,    38,    37,    40,    41,    43,
      45,    44,    47,    55,     0,     0,     0,     0,    72,     0,
       0,     0,     0,    57,     0,     0,     0,    67,    65,     0,
       0,     0,     0,    74,    73,     0,    78,    79,     0,     0,
       0,     0,    66,     0,     0,     0,     0,     0,     0,    68,
       0,    75,     0,     0,     0,     0,    69,     0,     0,     0,
      77,     0,    76
  };

  const short
  parser_t::yypgoto_[] =
  {
     -94,   -94,     0,   -93,    -1,   -13,   -94,   196,   -94,    -7,
     152,   154,   160,    87,   107,    95,   105,     3,   -94,   -94,
     -94,    92,   -94,   -94,    97,   -94,   -94,   -94,   -94,   -94
  };

  const unsigned char
  parser_t::yydefgoto_[] =
  {
       0,    19,    55,    56,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    87,
      36,   128,   129,    37,   118,   119,    38,    39,    40,    41
  };

  const short
  parser_t::yytable_[] =
  {
      20,   121,    58,    65,    51,    52,    65,    54,   116,   117,
      48,    49,    50,    42,    57,    65,    53,    65,    65,    63,
      59,    61,     2,     3,     4,    47,     6,    85,   152,   153,
       7,     8,   137,    92,    65,     9,    86,    88,    89,   132,
      94,   159,    96,   133,     2,     3,     4,     5,     6,   124,
     125,   141,     7,     8,    95,   135,    65,     9,    -2,     1,
     158,     2,     3,     4,     5,     6,   161,    60,    91,     7,
       8,    62,    18,    65,     9,     2,     3,     4,    47,     6,
      65,    58,   112,     7,     8,   147,   120,    10,     9,    11,
     122,   115,   148,    57,    18,    12,   113,    64,    13,    66,
      43,    68,    69,    14,    65,    15,   114,   123,    16,    17,
      44,    18,    74,    75,    63,    45,    90,   138,   139,    -5,
      -7,    -5,    -7,    -5,    -7,    18,   140,    67,   146,    80,
     143,   144,   145,    -6,    -8,    -6,    -8,    -6,    -8,    63,
      58,   150,    63,    63,    63,   157,    58,   154,   155,    63,
     116,   117,    57,    63,    63,   101,   102,     1,    57,     2,
       3,     4,     5,     6,    76,    77,    78,     7,     8,   107,
     108,    79,     9,    70,    71,    72,    73,   103,   104,   105,
     106,   109,   110,   111,    81,    10,    82,    11,    83,   124,
     125,   126,   127,    12,    84,    43,    13,    93,    97,   130,
     131,    14,    46,    15,   136,   160,    16,    17,     1,    18,
       2,     3,     4,     5,     6,   162,   134,    98,     7,     8,
      99,   142,     0,     9,     0,     0,     0,   100,     0,     0,
       0,     0,     0,     0,     0,     0,    10,     0,    11,     0,
     -63,   -63,   -63,     0,    12,     0,     0,    13,     0,     0,
       0,     0,    14,     0,    15,     0,     0,    16,    17,     1,
      18,     2,     3,     4,     5,     6,     0,     0,     0,     7,
       8,     0,     0,     0,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    10,     0,    11,
       0,   -64,   -64,   -64,     0,    12,     0,     0,    13,     0,
       0,     0,     0,    14,     0,    15,     0,     0,    16,    17,
       1,    18,     2,   -70,   -70,     5,     6,     0,     0,     0,
       7,     8,     0,     0,     0,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,     0,
      11,     0,     0,     0,   -70,     0,    12,     0,   -70,    13,
       0,     0,     0,     0,    14,     0,    15,     0,     0,    16,
      17,     1,    18,     2,   -71,   -71,     5,     6,     0,     0,
       0,     7,     8,     0,     0,     0,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    10,
       0,    11,     0,     0,     0,   -71,     0,    12,     0,   -71,
      13,     0,     0,     0,     0,    14,     0,    15,     0,     0,
      16,    17,     1,    18,     2,     3,     4,     5,     6,     0,
       0,     0,     7,     8,     0,     0,     0,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      10,     0,    11,     0,     0,     0,     0,   149,    12,     0,
       0,    13,     0,     0,     0,     0,    14,     0,    15,     0,
       0,    16,    17,     1,    18,     2,     3,     4,     5,     6,
       0,     0,     0,     7,     8,     0,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,    11,     0,     0,     0,     0,     0,    12,
       0,   151,    13,     0,     0,     0,     0,    14,     0,    15,
       0,     0,    16,    17,     1,    18,     2,     3,     4,     5,
       6,     0,     0,     0,     7,     8,     0,     0,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    10,     0,    11,     0,     0,     0,     0,   156,
      12,     0,     0,    13,     0,     0,     0,     0,    14,     0,
      15,     0,     0,    16,    17,     1,    18,     2,     3,     4,
       5,     6,     0,     0,     0,     7,     8,     0,     0,     0,
       9,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    10,     0,    11,     0,     0,     0,     0,
       0,    12,     0,     0,    13,     0,     0,     0,     0,    14,
       0,    15,     0,     0,    16,    17,     0,    18
  };

  const short
  parser_t::yycheck_[] =
  {
       0,    94,    15,    20,    11,    12,    20,    14,     4,     5,
       7,     8,     9,    29,    15,    20,     6,    20,    20,    20,
      29,    18,     3,     4,     5,     6,     7,     8,    42,    43,
      11,    12,    49,    38,    20,    16,    43,    44,    45,    35,
      43,    43,    55,    39,     3,     4,     5,     6,     7,    33,
      34,    35,    11,    12,    55,    41,    20,    16,     0,     1,
     153,     3,     4,     5,     6,     7,   159,    29,    32,    11,
      12,     0,    53,    20,    16,     3,     4,     5,     6,     7,
      20,    94,    79,    11,    12,    32,    93,    29,    16,    31,
      97,    91,    32,    94,    53,    37,     8,    29,    40,    19,
       7,    22,    23,    45,    20,    47,    18,   114,    50,    51,
      17,    53,    11,    12,   115,    22,     8,   124,   125,    44,
      44,    46,    46,    48,    48,    53,   126,    21,   135,    29,
     130,   131,   132,    44,    44,    46,    46,    48,    48,   140,
     153,   141,   143,   144,   145,   152,   159,   147,   148,   150,
       4,     5,   153,   154,   155,    68,    69,     1,   159,     3,
       4,     5,     6,     7,    13,    14,    15,    11,    12,    74,
      75,    28,    16,    24,    25,    26,    27,    70,    71,    72,
      73,    76,    77,    78,    29,    29,    29,    31,    29,    33,
      34,    35,    36,    37,    29,     7,    40,    17,    48,    30,
      30,    45,     6,    47,    46,    44,    50,    51,     1,    53,
       3,     4,     5,     6,     7,    44,   119,    65,    11,    12,
      66,   129,    -1,    16,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    34,    35,    -1,    37,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    45,    -1,    47,    -1,    -1,    50,    51,     1,
      53,     3,     4,     5,     6,     7,    -1,    -1,    -1,    11,
      12,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    33,    34,    35,    -1,    37,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    45,    -1,    47,    -1,    -1,    50,    51,
       1,    53,     3,     4,     5,     6,     7,    -1,    -1,    -1,
      11,    12,    -1,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      31,    -1,    -1,    -1,    35,    -1,    37,    -1,    39,    40,
      -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    -1,    50,
      51,     1,    53,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    11,    12,    -1,    -1,    -1,    16,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,    -1,    -1,    -1,    35,    -1,    37,    -1,    39,
      40,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,    -1,
      50,    51,     1,    53,     3,     4,     5,     6,     7,    -1,
      -1,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    31,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    40,    -1,    -1,    -1,    -1,    45,    -1,    47,    -1,
      -1,    50,    51,     1,    53,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    39,    40,    -1,    -1,    -1,    -1,    45,    -1,    47,
      -1,    -1,    50,    51,     1,    53,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    31,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    45,    -1,
      47,    -1,    -1,    50,    51,     1,    53,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    -1,    40,    -1,    -1,    -1,    -1,    45,
      -1,    47,    -1,    -1,    50,    51,    -1,    53
  };

  const signed char
  parser_t::yystos_[] =
  {
       0,     1,     3,     4,     5,     6,     7,    11,    12,    16,
      29,    31,    37,    40,    45,    47,    50,    51,    53,    55,
      56,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    74,    77,    80,    81,
      82,    83,    29,     7,    17,    22,    61,     6,    71,    71,
      71,    63,    63,     6,    63,    56,    57,    58,    59,    29,
      29,    71,     0,    58,    29,    20,    19,    21,    22,    23,
      24,    25,    26,    27,    11,    12,    13,    14,    15,    28,
      29,    29,    29,    29,    29,     8,    63,    73,    63,    63,
       8,    32,    38,    17,    43,    58,    59,    48,    64,    65,
      66,    67,    67,    68,    68,    68,    68,    69,    69,    70,
      70,    70,    71,     8,    18,    56,     4,     5,    78,    79,
      63,    57,    63,    63,    33,    34,    35,    36,    75,    76,
      30,    30,    35,    39,    78,    41,    46,    49,    63,    63,
      56,    35,    75,    56,    56,    56,    63,    32,    32,    36,
      56,    39,    42,    43,    56,    56,    36,    63,    57,    43,
      44,    57,    44
  };

  const signed char
  parser_t::yyr1_[] =
  {
       0,    54,    55,    56,    56,    57,    57,    57,    57,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    59,    59,
      60,    61,    62,    62,    62,    63,    63,    64,    64,    65,
      65,    66,    66,    66,    67,    67,    67,    67,    67,    68,
      68,    68,    69,    69,    69,    69,    70,    70,    71,    71,
      71,    71,    71,    72,    72,    72,    73,    73,    74,    74,
      74,    74,    74,    75,    75,    76,    76,    77,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    83
  };

  const signed char
  parser_t::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     2,     1,     2,     2,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     3,     1,     2,
       2,     2,     2,     1,     3,     4,     1,     3,     1,     1,
       1,     1,     3,     4,     4,     1,     2,     5,     7,     8,
       3,     3,     1,     2,     5,     7,    11,     9,     5,     5
  };




#if YYDEBUG
  const short
  parser_t::yyrline_[] =
  {
       0,   115,   115,   119,   120,   124,   125,   126,   127,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   144,   145,
     149,   153,   157,   158,   159,   163,   164,   168,   169,   173,
     174,   178,   179,   180,   184,   185,   186,   187,   188,   192,
     193,   194,   198,   199,   200,   201,   205,   206,   210,   211,
     212,   213,   214,   218,   219,   220,   224,   225,   229,   230,
     231,   232,   233,   237,   238,   242,   243,   247,   248,   249,
     253,   254,   258,   259,   263,   264,   268,   269,   273,   277
  };

  void
  parser_t::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser_t::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 10 "3rd/iec61131.y"
} // deci
#line 1819 "3rd/iec61131.y.cpp"

#line 280 "3rd/iec61131.y"


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
