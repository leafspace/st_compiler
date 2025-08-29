#pragma once
#ifndef __DECI_AST_HEADER__
#define __DECI_AST_HEADER__

#include <fstream>
#include <vector>
#include <queue>
#include <map>

#include "location.hh"
#include "SyntaxError.hpp"
#include "ast_number_t.hpp"
#include "symbol_table.hpp"

namespace deci
{

/* @Name: Class ast_symbol_table
*  @Comment: 语法树由外部传入的参数列表或函数列表
*/
class ast_symbol_table 
{
private:
	symbol_table m_variant;
	symbol_table m_constant;
	function_table m_function;

	void SplitVariantAndConstant(symbol_table&);

public:
	ast_symbol_table(void);
	ast_symbol_table(const symbol_table&, const function_table&);
	ast_symbol_table(const symbol_table&, const symbol_table&, const function_table&);
	~ast_symbol_table(void);

	void SetVariant(const symbol_table&);
	void SetConstant(const symbol_table&);
	void SetFunction(const function_table&);

	symbol_table GetVariant(void) const;
	symbol_table GetConstant(void) const;
	function_table GetFunction(void) const;
};

/* @Name: Class ast_check_ctrl
*  @Comment: 语法树检查控制参数
*/
class ast_check_ctrl
{
private:
	bool m_bConditon;

public:
	void SetIsCondition(const bool bCondition);

	bool GetIsCondition(void);
};

/* @Name: Class ast_item_t
*  @Comment: BNF树节点
*/
class ast_item_t {
private:
	ast_item_t* m_pParent;

protected:
	int m_nType;                                             // BNF 树类型
	std::vector<SyntaxError> m_errors;                       // BNF 树语义错误
	std::vector<location> m_locations;                       // BNF 语法位置

	location m_identifierLocation;                           // 标识符位置

	void init();

public:
	ast_item_t* Parent() const {
		return this->m_pParent;
	}

	void Parent(ast_item_t* pParent) {
		this->m_pParent = pParent;
	}

	static std::string GetIndent(int);                      // 根据层级在语法转译时提供缩进

public:
	//virtual int Translation(std::string&, int) const;       // 语法转译
	virtual int Translation(std::string&, int, ast_symbol_table&) const;
	virtual int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&); // 语法检查
	virtual int GetType(void) const;                        // 获取语法类型
	virtual std::string GetValue(void) const;               // 获取值
	virtual std::vector<symbol> GetIdentifiers(void);       // 获取标识符列表
	virtual std::vector<SyntaxError> GetSyntaxErrors(void); // 获取语法错误列表
	virtual void SetLocations(std::vector<location>);       // 设置当前数据范围
	virtual void SetIdentifierLocation(location&);          // 设置当前标识符位置
	virtual location GetLocation(void);                     // 获取当前数据范围
	virtual location GetIdentifierLocation(void);           // 获取当前标识符位置
public:
	ast_item_t();
	virtual ~ast_item_t() = 0;
};

/* @Name: Class ast_set_t
*  @Comment: BNF树节点（表达式列表 类型）
*/
class ast_t final : public ast_item_t {
private:
	std::vector<ast_item_t*> m_statements;

protected:
	void init();

public:
	void Append(ast_item_t* item);
	std::vector<ast_item_t*> GetStatements(void);

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_t();
	~ast_t();
};

/* @Name: Class ast_boolean_t
*  @Comment: BNF树节点（bool 类型）
*/
class ast_boolean_t final : public ast_item_t {
private:
	bool value;

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::string GetValue(void) const;

public:
	ast_boolean_t(bool);
	~ast_boolean_t();
};

/* @Name: Class ast_number_t
*  @Comment: BNF树节点（数值 类型）
*  @Comment: 数值类型的表现形式：123、123.4、INT#1234、16#FFFF_FFFF
*/
class ast_number_t final : public ast_item_t {
private:
	double m_dbValue;
	std::string m_strValue;

	void init(void);
	SyntaxType SyntaxCheckBasalStrValueValid(ast_basal_number&) const;
	SyntaxType SyntaxCheckTypeStrValueValid(ast_type_number&) const;

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::string GetValue(void) const;

public:
	ast_number_t(double);
	ast_number_t(std::string&);
	~ast_number_t();
};

/* @Name: Class ast_number_t
*  @Comment: BNF树节点（标识符/变量 类型）
*/
class ast_identifier_t final : public ast_item_t {
private:
	Identifier_Type m_nIdentifierType;
	std::string value;

public:
	symbol_rw GetIdentifierRWType();

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::string GetValue(void) const;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_identifier_t(const std::string&);
	ast_identifier_t(const std::string&, const Identifier_Type);
	~ast_identifier_t();
};

/* @Name: Class ast_arg_list_t
*  @Comment: BNF树节点（参数列表 类型）
*/
class ast_arg_list_t final : public ast_item_t {
private:
	std::vector<ast_item_t*> args;

protected:
	void init();

public:
	void Append(ast_item_t*);

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_arg_list_t();
	~ast_arg_list_t();
};

/* @Name: Class ast_postfix_t
*  @Comment: BNF树节点（后缀表达式 类型）
*/
class ast_postfix_t final : public ast_item_t {
private:
	ast_arg_list_t* arglist;
	ast_item_t* identifier;

protected:
	void init();

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_postfix_t(const std::string&, ast_arg_list_t*);
	~ast_postfix_t();
};

/* @Name: Class ast_binary_t
*  @Comment: BNF树节点（逻辑表达式 类型）
* （| OR | XOR | AND | = | <> | < | > | <= | >= |）
* （| + | - | * | mod | / | ** |）
*/
class ast_binary_t final : public ast_item_t {
private:
	std::string identifier;
	ast_item_t* a;
	ast_item_t* b;

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_binary_t(const std::string&, ast_item_t*, ast_item_t*);
	~ast_binary_t();
};

/* @Name: Class ast_unary_t
*  @Comment: BNF树节点（取非表达式 类型）
* （| not | - |）
*/
class ast_unary_t final : public ast_item_t {
private:
	std::string identifier;
	ast_item_t* chain;

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_unary_t(const std::string&, ast_item_t*);
	~ast_unary_t();
};

/* @Name: Class ast_return_t
*  @Comment: BNF树节点（ 类型）
*/
class ast_return_t final : public ast_item_t {
private:
	ast_item_t* chain;

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_return_t(ast_item_t*);
	~ast_return_t();
};

/* @Name: Class ast_set_t
*  @Comment: BNF树节点（赋值表达式 类型）
*/
class ast_set_t final : public ast_item_t {
private:
	ast_item_t* identifier;
	ast_item_t* chain;

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::string GetValue(void) const;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_set_t(const std::string&, ast_item_t*);
	~ast_set_t();
};

/* @Name: Class ast_exit_t
*  @Comment: BNF树节点（退出表达式 类型）
*/
class ast_exit_t final : public ast_item_t
{
public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
public:
	ast_exit_t();
	~ast_exit_t();
};

/* @Name: Class ast_if_t
*  @Comment: BNF树节点（判断表达式 类型）
*/
class ast_if_t final : public ast_item_t {
private:
	ast_item_t* condition;
	ast_t* true_path;
	ast_t* else_path;
	ast_t* elseif_path;

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_if_t(ast_item_t*, ast_t*, ast_t* = nullptr, ast_t* = nullptr);
	~ast_if_t();
};

/* @Name: Class ast_elseif_t
*  @Comment: BNF树节点（判断表达式ELSEIF分段 类型）
*/
class ast_elsif_t final : public ast_item_t {
private:
	ast_item_t* condition;
	ast_t* path;

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_elsif_t(ast_item_t*, ast_t*);
	~ast_elsif_t();
};

/* @Name: Class ast_enumeration_t
*  @Comment: BNF树节点（多分支表达式枚举项 类型）
*/
class ast_enumeration_t final : public ast_item_t {
private:
	ast_item_t* number;
	ast_t* case_path;

public:
	double GetNumber(void);

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_enumeration_t(ast_item_t*, ast_t*);
	ast_enumeration_t(double, ast_t*);
	ast_enumeration_t(std::string&, ast_t*);
	~ast_enumeration_t();
};

/* @Name: Class ast_case_t
*  @Comment: BNF树节点（多分支表达式 类型）
*/
class ast_case_t final : public ast_item_t {
private:
	ast_item_t* enumeration;
	ast_t* branchs;
	ast_t* else_path;

	int SyntaxCheckUniqueness(void);

public:
	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_case_t(ast_item_t*, ast_t*, ast_t* = nullptr);
	~ast_case_t();
};

/* @Name: Class ast_loop_t
*  @Comment: BNF树节点（循环表达式 类型）
*/
class ast_loop_t : public ast_item_t {
protected:
	mutable int end_loc_pos;

public:
	ast_loop_t();
	~ast_loop_t();
};

/* @Name: Class ast_for_t
*  @Comment: BNF树节点（for循环表达式 类型）
*/
class ast_for_t final : public ast_loop_t {
private:
	ast_item_t* identifier;
	ast_item_t* start;
	ast_item_t* finish;
	ast_t* loop;
	ast_item_t* step;

	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_for_t(const std::string&, ast_item_t*, ast_item_t*, ast_t*, ast_item_t*);
	~ast_for_t();
};

/* @Name: Class ast_while_t
*  @Comment: BNF树节点（while循环表达式 类型）
*/
class ast_while_t final : public ast_loop_t {
private:
	ast_item_t* condition;
	ast_t* loop;

	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_while_t(ast_item_t*, ast_t*);
	~ast_while_t();
};

/* @Name: Class ast_repeat_t
*  @Comment: BNF树节点（repeat循环表达式 类型）
*/
class ast_repeat_t final : public ast_loop_t {
private:
	ast_item_t* condition;
	ast_t* loop;

	int Translation(std::string&, int, ast_symbol_table&) const override;
	int SyntaxCheck(std::queue<AstSymbolType>&, ast_symbol_table&, ast_check_ctrl&) override;
	std::vector<symbol> GetIdentifiers(void) override;

public:
	ast_repeat_t(ast_item_t*, ast_t*);
	~ast_repeat_t();
};

/* @Name: Class ast_exit_t
*  @Comment: BNF树节点（退出表达式 类型）
*/
class ast_error_t final : public ast_item_t
{
public:
	ast_error_t();
	~ast_error_t();
};

} // namespace deci
#endif