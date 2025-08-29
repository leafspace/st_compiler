// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file 3rd/iec61131.y.hpp
 ** Define the deci::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_3RD_IEC61131_Y_HPP_INCLUDED
# define YY_YY_3RD_IEC61131_Y_HPP_INCLUDED
// "%code requires" blocks.
#line 12 "3rd/iec61131.y"

  #include <deci.hpp>

  class deci_scanner_t;

#line 55 "3rd/iec61131.y.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 10 "3rd/iec61131.y"
namespace deci {
#line 190 "3rd/iec61131.y.hpp"




  /// A Bison parser.
  class parser_t
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // "argument list"
      // argument_list
      char dummy1[sizeof (ast_arg_list_t*)];

      // exit_statement
      char dummy2[sizeof (ast_exit_t*)];

      // statement
      // expression_statement
      // expression
      // assign_expr
      // or_expr
      // xor_expr
      // and_expr
      // eql_expr
      // cmp_expr
      // add_expr
      // mul_expr
      // pow_expr
      // unary_expr
      // postfix_expr
      // primary_expr
      // elsif_statement
      // if_statement
      // case_enumeration_statement
      // case_statement
      // for_statement
      // while_statement
      // repeat_statement
      char dummy3[sizeof (ast_item_t*)];

      // statement_list
      // loop_statement_list
      // elsif_statement_list
      // case_statement_list
      char dummy4[sizeof (ast_t*)];

      // "boolean"
      char dummy5[sizeof (bool)];

      // "number"
      char dummy6[sizeof (double)];

      // "number_str"
      // "identifier"
      char dummy7[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TOK_YYEMPTY = -2,
    TOK_END = 0,                   // "end of file"
    TOK_YYerror = 256,             // error
    TOK_YYUNDEF = 257,             // "invalid token"
    TOK_BOOLEAN = 258,             // "boolean"
    TOK_NUMBER = 259,              // "number"
    TOK_NUMBER_STR = 260,          // "number_str"
    TOK_IDENTIFIER = 261,          // "identifier"
    TOK_BOPEN = 262,               // "("
    TOK_BCLOSE = 263,              // ")"
    TOK_COPEN = 264,               // "["
    TOK_CCLOSE = 265,              // "]"
    TOK_SUM = 266,                 // "+"
    TOK_SUB = 267,                 // "-"
    TOK_MUL = 268,                 // "*"
    TOK_DIV = 269,                 // "/"
    TOK_MOD = 270,                 // "MOD"
    TOK_NOT = 271,                 // "NOT"
    TOK_ASSIGN = 272,              // ":="
    TOK_COMMA = 273,               // ","
    TOK_XOR = 274,                 // "XOR"
    TOK_OR = 275,                  // "OR"
    TOK_AND = 276,                 // "AND"
    TOK_EQU = 277,                 // "="
    TOK_NEQU = 278,                // "<>"
    TOK_GR = 279,                  // ">"
    TOK_LS = 280,                  // "<"
    TOK_GE = 281,                  // ">="
    TOK_LE = 282,                  // "<="
    TOK_POW = 283,                 // "**"
    TOK_ST_END = 284,              // ";"
    TOK_COLON = 285,               // ":"
    TOK_IF = 286,                  // "IF"
    TOK_THEN = 287,                // "THEN"
    TOK_ELSIF = 288,               // "ELSIF"
    TOK_ELSEIF = 289,              // "ELSEIF"
    TOK_ELSE = 290,                // "ELSE"
    TOK_END_IF = 291,              // "END_IF"
    TOK_CASE = 292,                // "CASE"
    TOK_OF = 293,                  // "OF"
    TOK_END_CASE = 294,            // "END_CASE"
    TOK_FOR = 295,                 // "FOR"
    TOK_TO = 296,                  // "TO"
    TOK_BY = 297,                  // "BY"
    TOK_DO = 298,                  // "DO"
    TOK_END_FOR = 299,             // "END_FOR"
    TOK_WHILE = 300,               // "WHILE"
    TOK_END_WHILE = 301,           // "END_WHILE"
    TOK_REPEAT = 302,              // "REPEAT"
    TOK_UNTIL = 303,               // "UNTIL"
    TOK_END_REPEAT = 304,          // "END_REPEAT"
    TOK_EXIT = 305,                // "EXIT"
    TOK_RETURN = 306               // "RETURN"
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 54, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_BOOLEAN = 3,                           // "boolean"
        S_NUMBER = 4,                            // "number"
        S_NUMBER_STR = 5,                        // "number_str"
        S_IDENTIFIER = 6,                        // "identifier"
        S_BOPEN = 7,                             // "("
        S_BCLOSE = 8,                            // ")"
        S_COPEN = 9,                             // "["
        S_CCLOSE = 10,                           // "]"
        S_SUM = 11,                              // "+"
        S_SUB = 12,                              // "-"
        S_MUL = 13,                              // "*"
        S_DIV = 14,                              // "/"
        S_MOD = 15,                              // "MOD"
        S_NOT = 16,                              // "NOT"
        S_ASSIGN = 17,                           // ":="
        S_COMMA = 18,                            // ","
        S_XOR = 19,                              // "XOR"
        S_OR = 20,                               // "OR"
        S_AND = 21,                              // "AND"
        S_EQU = 22,                              // "="
        S_NEQU = 23,                             // "<>"
        S_GR = 24,                               // ">"
        S_LS = 25,                               // "<"
        S_GE = 26,                               // ">="
        S_LE = 27,                               // "<="
        S_POW = 28,                              // "**"
        S_ST_END = 29,                           // ";"
        S_COLON = 30,                            // ":"
        S_IF = 31,                               // "IF"
        S_THEN = 32,                             // "THEN"
        S_ELSIF = 33,                            // "ELSIF"
        S_ELSEIF = 34,                           // "ELSEIF"
        S_ELSE = 35,                             // "ELSE"
        S_END_IF = 36,                           // "END_IF"
        S_CASE = 37,                             // "CASE"
        S_OF = 38,                               // "OF"
        S_END_CASE = 39,                         // "END_CASE"
        S_FOR = 40,                              // "FOR"
        S_TO = 41,                               // "TO"
        S_BY = 42,                               // "BY"
        S_DO = 43,                               // "DO"
        S_END_FOR = 44,                          // "END_FOR"
        S_WHILE = 45,                            // "WHILE"
        S_END_WHILE = 46,                        // "END_WHILE"
        S_REPEAT = 47,                           // "REPEAT"
        S_UNTIL = 48,                            // "UNTIL"
        S_END_REPEAT = 49,                       // "END_REPEAT"
        S_EXIT = 50,                             // "EXIT"
        S_RETURN = 51,                           // "RETURN"
        S_52_argument_list_ = 52,                // "argument list"
        S_53_ = 53,                              // "~"
        S_YYACCEPT = 54,                         // $accept
        S_entry = 55,                            // entry
        S_statement_list = 56,                   // statement_list
        S_loop_statement_list = 57,              // loop_statement_list
        S_statement = 58,                        // statement
        S_exit_statement = 59,                   // exit_statement
        S_expression_statement = 60,             // expression_statement
        S_expression = 61,                       // expression
        S_assign_expr = 62,                      // assign_expr
        S_or_expr = 63,                          // or_expr
        S_xor_expr = 64,                         // xor_expr
        S_and_expr = 65,                         // and_expr
        S_eql_expr = 66,                         // eql_expr
        S_cmp_expr = 67,                         // cmp_expr
        S_add_expr = 68,                         // add_expr
        S_mul_expr = 69,                         // mul_expr
        S_pow_expr = 70,                         // pow_expr
        S_unary_expr = 71,                       // unary_expr
        S_postfix_expr = 72,                     // postfix_expr
        S_argument_list = 73,                    // argument_list
        S_primary_expr = 74,                     // primary_expr
        S_elsif_statement = 75,                  // elsif_statement
        S_elsif_statement_list = 76,             // elsif_statement_list
        S_if_statement = 77,                     // if_statement
        S_case_enumeration_statement = 78,       // case_enumeration_statement
        S_case_statement_list = 79,              // case_statement_list
        S_case_statement = 80,                   // case_statement
        S_for_statement = 81,                    // for_statement
        S_while_statement = 82,                  // while_statement
        S_repeat_statement = 83                  // repeat_statement
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_52_argument_list_: // "argument list"
      case symbol_kind::S_argument_list: // argument_list
        value.move< ast_arg_list_t* > (std::move (that.value));
        break;

      case symbol_kind::S_exit_statement: // exit_statement
        value.move< ast_exit_t* > (std::move (that.value));
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
        value.move< ast_item_t* > (std::move (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_loop_statement_list: // loop_statement_list
      case symbol_kind::S_elsif_statement_list: // elsif_statement_list
      case symbol_kind::S_case_statement_list: // case_statement_list
        value.move< ast_t* > (std::move (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_NUMBER_STR: // "number_str"
      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast_arg_list_t*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast_arg_list_t*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast_exit_t*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast_exit_t*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast_item_t*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast_item_t*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ast_t*&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ast_t*& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_52_argument_list_: // "argument list"
      case symbol_kind::S_argument_list: // argument_list
        value.template destroy< ast_arg_list_t* > ();
        break;

      case symbol_kind::S_exit_statement: // exit_statement
        value.template destroy< ast_exit_t* > ();
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
        value.template destroy< ast_item_t* > ();
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_loop_statement_list: // loop_statement_list
      case symbol_kind::S_elsif_statement_list: // elsif_statement_list
      case symbol_kind::S_case_statement_list: // case_statement_list
        value.template destroy< ast_t* > ();
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.template destroy< double > ();
        break;

      case symbol_kind::S_NUMBER_STR: // "number_str"
      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser_t::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
#endif
      {
        YY_ASSERT (tok == token::TOK_END
                   || (token::TOK_YYerror <= tok && tok <= token::TOK_YYUNDEF)
                   || (token::TOK_BOPEN <= tok && tok <= token::TOK_RETURN)
                   || tok == 308);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, ast_arg_list_t* v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const ast_arg_list_t*& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT (tok == 307);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT (tok == token::TOK_BOOLEAN);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT (tok == token::TOK_NUMBER);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT ((token::TOK_NUMBER_STR <= tok && tok <= token::TOK_IDENTIFIER));
      }
    };

    /// Build a parser object.
    parser_t (deci_scanner_t& scanner_yyarg, std::shared_ptr<ast_t>& ast_yyarg, std::vector<SyntaxError>& errors_yyarg, symbol_table& symbols_yyarg);
    virtual ~parser_t ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser_t (const parser_t&) = delete;
    /// Non copyable.
    parser_t& operator= (const parser_t&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::TOK_END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::TOK_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::TOK_YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::TOK_YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::TOK_YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::TOK_YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOLEAN (bool v, location_type l)
      {
        return symbol_type (token::TOK_BOOLEAN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BOOLEAN (const bool& v, const location_type& l)
      {
        return symbol_type (token::TOK_BOOLEAN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NUMBER (double v, location_type l)
      {
        return symbol_type (token::TOK_NUMBER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NUMBER (const double& v, const location_type& l)
      {
        return symbol_type (token::TOK_NUMBER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NUMBER_STR (std::string v, location_type l)
      {
        return symbol_type (token::TOK_NUMBER_STR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NUMBER_STR (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_NUMBER_STR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::TOK_IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOK_IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOPEN (location_type l)
      {
        return symbol_type (token::TOK_BOPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_BOPEN (const location_type& l)
      {
        return symbol_type (token::TOK_BOPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BCLOSE (location_type l)
      {
        return symbol_type (token::TOK_BCLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_BCLOSE (const location_type& l)
      {
        return symbol_type (token::TOK_BCLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COPEN (location_type l)
      {
        return symbol_type (token::TOK_COPEN, std::move (l));
      }
#else
      static
      symbol_type
      make_COPEN (const location_type& l)
      {
        return symbol_type (token::TOK_COPEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CCLOSE (location_type l)
      {
        return symbol_type (token::TOK_CCLOSE, std::move (l));
      }
#else
      static
      symbol_type
      make_CCLOSE (const location_type& l)
      {
        return symbol_type (token::TOK_CCLOSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUM (location_type l)
      {
        return symbol_type (token::TOK_SUM, std::move (l));
      }
#else
      static
      symbol_type
      make_SUM (const location_type& l)
      {
        return symbol_type (token::TOK_SUM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SUB (location_type l)
      {
        return symbol_type (token::TOK_SUB, std::move (l));
      }
#else
      static
      symbol_type
      make_SUB (const location_type& l)
      {
        return symbol_type (token::TOK_SUB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MUL (location_type l)
      {
        return symbol_type (token::TOK_MUL, std::move (l));
      }
#else
      static
      symbol_type
      make_MUL (const location_type& l)
      {
        return symbol_type (token::TOK_MUL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DIV (location_type l)
      {
        return symbol_type (token::TOK_DIV, std::move (l));
      }
#else
      static
      symbol_type
      make_DIV (const location_type& l)
      {
        return symbol_type (token::TOK_DIV, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MOD (location_type l)
      {
        return symbol_type (token::TOK_MOD, std::move (l));
      }
#else
      static
      symbol_type
      make_MOD (const location_type& l)
      {
        return symbol_type (token::TOK_MOD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (location_type l)
      {
        return symbol_type (token::TOK_NOT, std::move (l));
      }
#else
      static
      symbol_type
      make_NOT (const location_type& l)
      {
        return symbol_type (token::TOK_NOT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (location_type l)
      {
        return symbol_type (token::TOK_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOK_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::TOK_COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::TOK_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_XOR (location_type l)
      {
        return symbol_type (token::TOK_XOR, std::move (l));
      }
#else
      static
      symbol_type
      make_XOR (const location_type& l)
      {
        return symbol_type (token::TOK_XOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (location_type l)
      {
        return symbol_type (token::TOK_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_OR (const location_type& l)
      {
        return symbol_type (token::TOK_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (location_type l)
      {
        return symbol_type (token::TOK_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const location_type& l)
      {
        return symbol_type (token::TOK_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQU (location_type l)
      {
        return symbol_type (token::TOK_EQU, std::move (l));
      }
#else
      static
      symbol_type
      make_EQU (const location_type& l)
      {
        return symbol_type (token::TOK_EQU, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEQU (location_type l)
      {
        return symbol_type (token::TOK_NEQU, std::move (l));
      }
#else
      static
      symbol_type
      make_NEQU (const location_type& l)
      {
        return symbol_type (token::TOK_NEQU, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GR (location_type l)
      {
        return symbol_type (token::TOK_GR, std::move (l));
      }
#else
      static
      symbol_type
      make_GR (const location_type& l)
      {
        return symbol_type (token::TOK_GR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LS (location_type l)
      {
        return symbol_type (token::TOK_LS, std::move (l));
      }
#else
      static
      symbol_type
      make_LS (const location_type& l)
      {
        return symbol_type (token::TOK_LS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GE (location_type l)
      {
        return symbol_type (token::TOK_GE, std::move (l));
      }
#else
      static
      symbol_type
      make_GE (const location_type& l)
      {
        return symbol_type (token::TOK_GE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LE (location_type l)
      {
        return symbol_type (token::TOK_LE, std::move (l));
      }
#else
      static
      symbol_type
      make_LE (const location_type& l)
      {
        return symbol_type (token::TOK_LE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POW (location_type l)
      {
        return symbol_type (token::TOK_POW, std::move (l));
      }
#else
      static
      symbol_type
      make_POW (const location_type& l)
      {
        return symbol_type (token::TOK_POW, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ST_END (location_type l)
      {
        return symbol_type (token::TOK_ST_END, std::move (l));
      }
#else
      static
      symbol_type
      make_ST_END (const location_type& l)
      {
        return symbol_type (token::TOK_ST_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::TOK_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::TOK_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (location_type l)
      {
        return symbol_type (token::TOK_IF, std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const location_type& l)
      {
        return symbol_type (token::TOK_IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THEN (location_type l)
      {
        return symbol_type (token::TOK_THEN, std::move (l));
      }
#else
      static
      symbol_type
      make_THEN (const location_type& l)
      {
        return symbol_type (token::TOK_THEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSIF (location_type l)
      {
        return symbol_type (token::TOK_ELSIF, std::move (l));
      }
#else
      static
      symbol_type
      make_ELSIF (const location_type& l)
      {
        return symbol_type (token::TOK_ELSIF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSEIF (location_type l)
      {
        return symbol_type (token::TOK_ELSEIF, std::move (l));
      }
#else
      static
      symbol_type
      make_ELSEIF (const location_type& l)
      {
        return symbol_type (token::TOK_ELSEIF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (location_type l)
      {
        return symbol_type (token::TOK_ELSE, std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const location_type& l)
      {
        return symbol_type (token::TOK_ELSE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END_IF (location_type l)
      {
        return symbol_type (token::TOK_END_IF, std::move (l));
      }
#else
      static
      symbol_type
      make_END_IF (const location_type& l)
      {
        return symbol_type (token::TOK_END_IF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE (location_type l)
      {
        return symbol_type (token::TOK_CASE, std::move (l));
      }
#else
      static
      symbol_type
      make_CASE (const location_type& l)
      {
        return symbol_type (token::TOK_CASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OF (location_type l)
      {
        return symbol_type (token::TOK_OF, std::move (l));
      }
#else
      static
      symbol_type
      make_OF (const location_type& l)
      {
        return symbol_type (token::TOK_OF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END_CASE (location_type l)
      {
        return symbol_type (token::TOK_END_CASE, std::move (l));
      }
#else
      static
      symbol_type
      make_END_CASE (const location_type& l)
      {
        return symbol_type (token::TOK_END_CASE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR (location_type l)
      {
        return symbol_type (token::TOK_FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_FOR (const location_type& l)
      {
        return symbol_type (token::TOK_FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TO (location_type l)
      {
        return symbol_type (token::TOK_TO, std::move (l));
      }
#else
      static
      symbol_type
      make_TO (const location_type& l)
      {
        return symbol_type (token::TOK_TO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BY (location_type l)
      {
        return symbol_type (token::TOK_BY, std::move (l));
      }
#else
      static
      symbol_type
      make_BY (const location_type& l)
      {
        return symbol_type (token::TOK_BY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO (location_type l)
      {
        return symbol_type (token::TOK_DO, std::move (l));
      }
#else
      static
      symbol_type
      make_DO (const location_type& l)
      {
        return symbol_type (token::TOK_DO, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END_FOR (location_type l)
      {
        return symbol_type (token::TOK_END_FOR, std::move (l));
      }
#else
      static
      symbol_type
      make_END_FOR (const location_type& l)
      {
        return symbol_type (token::TOK_END_FOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (location_type l)
      {
        return symbol_type (token::TOK_WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const location_type& l)
      {
        return symbol_type (token::TOK_WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END_WHILE (location_type l)
      {
        return symbol_type (token::TOK_END_WHILE, std::move (l));
      }
#else
      static
      symbol_type
      make_END_WHILE (const location_type& l)
      {
        return symbol_type (token::TOK_END_WHILE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REPEAT (location_type l)
      {
        return symbol_type (token::TOK_REPEAT, std::move (l));
      }
#else
      static
      symbol_type
      make_REPEAT (const location_type& l)
      {
        return symbol_type (token::TOK_REPEAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNTIL (location_type l)
      {
        return symbol_type (token::TOK_UNTIL, std::move (l));
      }
#else
      static
      symbol_type
      make_UNTIL (const location_type& l)
      {
        return symbol_type (token::TOK_UNTIL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END_REPEAT (location_type l)
      {
        return symbol_type (token::TOK_END_REPEAT, std::move (l));
      }
#else
      static
      symbol_type
      make_END_REPEAT (const location_type& l)
      {
        return symbol_type (token::TOK_END_REPEAT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXIT (location_type l)
      {
        return symbol_type (token::TOK_EXIT, std::move (l));
      }
#else
      static
      symbol_type
      make_EXIT (const location_type& l)
      {
        return symbol_type (token::TOK_EXIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (location_type l)
      {
        return symbol_type (token::TOK_RETURN, std::move (l));
      }
#else
      static
      symbol_type
      make_RETURN (const location_type& l)
      {
        return symbol_type (token::TOK_RETURN, l);
      }
#endif


    class context
    {
    public:
      context (const parser_t& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser_t& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser_t (const parser_t&);
    /// Non copyable.
    parser_t& operator= (const parser_t&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// Report a syntax error
    /// \param yyctx     the context in which the error occurred.
    void report_syntax_error (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);



    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const unsigned char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 617,     ///< Last index in yytable_.
      yynnts_ = 30,  ///< Number of nonterminal symbols.
      yyfinal_ = 62 ///< Termination state number.
    };


    // User arguments.
    deci_scanner_t& scanner;
    std::shared_ptr<ast_t>& ast;
    std::vector<SyntaxError>& errors;
    symbol_table& symbols;

  };

  inline
  parser_t::symbol_kind_type
  parser_t::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
    };
    // Last valid token kind.
    const int code_max = 308;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  parser_t::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_52_argument_list_: // "argument list"
      case symbol_kind::S_argument_list: // argument_list
        value.copy< ast_arg_list_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exit_statement: // exit_statement
        value.copy< ast_exit_t* > (YY_MOVE (that.value));
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
        value.copy< ast_item_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_loop_statement_list: // loop_statement_list
      case symbol_kind::S_elsif_statement_list: // elsif_statement_list
      case symbol_kind::S_case_statement_list: // case_statement_list
        value.copy< ast_t* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER_STR: // "number_str"
      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  parser_t::symbol_kind_type
  parser_t::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  parser_t::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser_t::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_52_argument_list_: // "argument list"
      case symbol_kind::S_argument_list: // argument_list
        value.move< ast_arg_list_t* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_exit_statement: // exit_statement
        value.move< ast_exit_t* > (YY_MOVE (s.value));
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
        value.move< ast_item_t* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_statement_list: // statement_list
      case symbol_kind::S_loop_statement_list: // loop_statement_list
      case symbol_kind::S_elsif_statement_list: // elsif_statement_list
      case symbol_kind::S_case_statement_list: // case_statement_list
        value.move< ast_t* > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NUMBER_STR: // "number_str"
      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  parser_t::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser_t::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser_t::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  parser_t::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  parser_t::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser_t::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser_t::symbol_kind_type
  parser_t::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  parser_t::symbol_kind_type
  parser_t::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

#line 10 "3rd/iec61131.y"
} // deci
#line 2503 "3rd/iec61131.y.hpp"




#endif // !YY_YY_3RD_IEC61131_Y_HPP_INCLUDED
