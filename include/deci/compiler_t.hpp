#pragma once
#ifndef __DECI_COMPILER_HEADER__
#define __DECI_COMPILER_HEADER__

#include "deci/SyntaxError.hpp"
#include "deci/symbol_table.hpp"

namespace deci
{

/* @Name: compiler_mode
*  @Comment: 编译器警告模式
*/
enum class compiler_mode
{
	normal,                                              // 正常 （忽略警告）
	strict,                                              // 严格 （不忽略警告）
};


/* @Name: compiler_t
*  @Comment: 编译器
*/
class compiler_t
{
public:
	compiler_t(void);
	compiler_t(std::string&, std::istream&, bool = false);
	compiler_t(std::string&, std::string&, bool = false);
	~compiler_t(void);

	void SetMode(compiler_mode);

	void SetSource(std::string&, std::istream&, bool = false);
	void SetSource(std::string&, std::string&, bool = false);

	void SetOuterVariant(variant_table&);

	void SetCheckCtrlIsCondition(bool);

	std::vector<SyntaxError> GetSyntaxErrors(void);
	std::vector<SyntaxError> GetSemanticErrors(void);
	std::vector<SyntaxError> GetErrors(void);

	/* @Name: SyntaxCheck
	*  @Comment: 语法检查 | 类型检查 | 声明检查
	*  @Param (IN) : std::vector<symbol>& 已经定义的参数
	*  @Return bool isCompiled
	*/
	bool SyntaxCheck(void);

	/* @Name: SyntaxTranslation
	*  @Comment: 语法转译 （将BNF语法树转为C++语法）
	*  @Return void
	*/
	std::string SyntaxTranslation(void);

	/* @Name: IsCompiled
	*  @Comment: 是否通过编译
	*  @Return bool isCompiled
	*/
	bool IsCompiled(void);

	static void PrintSyntaxError(std::vector<SyntaxError>&);

private:
	void initialize(void);
	void SyntaxInitalize(void);
	void FunctionInitalize(void);

	/* @Name: CreateSyntaxTree
	*  @Comment: 调用语法分析器分析出语法树
	*  @Return deci::ast_t BNF语法树
	*/
	void CreateSyntaxTree(void);

	/* @Name: SyntaxCheckDeclare
	*  @Comment: 声明与定义语义检查
	*            例如变量未声明或声明了但未使用
	*  @Return SyntaxErrors 语法错误
	*/
	void SyntaxCheckDeclare(void);

	/* @Name: SyntaxCheckIdentifierType
	*  @Comment: 标识符类型检查
	*            例如将一个整数值赋值给了BOOL值 （警告）
	*  @Return SyntaxErrors 语法错误
	*/
	void SyntaxCheckIdentifierType(void);

	/* @Name: SyntaxCheckUniqueness
	*  @Comment: 唯一性检查
	*            例如switch语句中的标识符只能出现一次
	*            使用树的内部递归SyntaxCheck检查
	*  @Return SyntaxErrors 语法错误
	*/
	//void SyntaxCheckUniqueness(void);

	/* @Name: FillSyntaxErrorMsg
	*  @Comment: 填充未存在错误信息的错误
	*  @Return SyntaxErrors 语法错误
	*/
	void FillSyntaxErrorMsg(void);

private:
	compiler_mode m_nCompilerMode;                        // 编译等级

	std::vector<SyntaxError> m_syntaxErrors;              // 当前编译过程中的语法错误
	std::vector<SyntaxError> m_semanticErrors;            // 当前编译过程中的语义错误
	symbol_table m_innerIdentifierTable;                  // 当前由代码内部定义的标识符
	symbol_table m_outerIdentifierTable;                  // 当前由外部引脚定义的标识符
	symbol_table m_usedIdentifierTable;                   // 内部使用的标识符
	function_table m_innerFunctionTable;                  // 系统内置的函数列表

	ast_check_ctrl m_checkCtrl;                           // 控制检查的开关

	std::string m_sourceName;                             // 文件或模块名称
	std::string m_sourceString;                           // 文件或模块数据
	std::istream* m_pSourceStream;                        // 文件或模块串流数据
	bool m_bInteractive;                                  // 实时模式

	std::shared_ptr<ast_t> m_syntaxTree;                  // 语法树
};
} // namespace deci

#endif /* __DECI_COMPILER_HEADER__ */