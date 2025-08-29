#pragma once

/**************************************************************************
*	Copyright (c) 2022,SUPCON
*
*	文件名称： 	SyntaxError.hpp
*	作    者：	zhanglifei
*	创建日期：	2022/08/23
*	摘    要：	语法错误相关定义
*
***************************************************************************/

#include "location.hh"

#include <map>

namespace deci
{

// 语法错误等级
enum class SyntaxLevel
{
	SyntaxLevel_Info,                         // 信息
	SyntaxLevel_Warning,                      // 警告
	SyntaxLevel_Error,                        // 错误
};

// 语法错误类型
enum class SyntaxType
{
	SyntaxError_None = 0,                     // 无错误

	SyntaxWarning_Begin,
	// 语义错误
	SyntaxWarning_UnuseParam,                 // 未使用的参数
	SyntaxWarning_NumberChange,               // 数字类型被强制修改了类型
	SyntaxWarning_End,

	SyntaxError_Begin,
	// 语法错误
	SyntaxError_Syntax,                       // 基本语法错误
	SyntexError_NumberBasal,                  // 错误的数字类型（基底数类型）
	SyntexError_NumberType,                   // 错误的数字类型（类型数类型）

	// 语义错误
	SyntaxError_Semantic,                     // 基本语义错误
	SyntaxError_Declaration,                  // 未定义的标识符
	SyntexError_CaseNumberInteger,            // CASE 语句的数值必须是整数
	SyntexError_CaseNumberRepeat,             // CASE 语句的数值必须不能重复
	SyntexError_FunctionParamUnpair,          // 没有与参数列表匹配的函数
	SyntexError_FunctionParamTypeUnpair,      // 函数参数类型不匹配
	SyntexError_BinaryCountUnpair,            // 二元操作符操作数数量不匹配
	SyntexError_BinaryTypeUnpair,             // 二元操作符操作数类型不匹配
	SyntexError_UnaryCountUnpair,             // 取非表达式操作数数量不匹配
	SyntexError_UnaryTypeUnpair,              // 取非表达式操作数类型不匹配
	SyntexError_ConditionCountUnpair,         // 条件表达式操作数数量不匹配
	SyntexError_ConditionTypeUnpair,          // 条件表达式操作数类型不匹配
	SyntexError_EnumerationCountUnpair,       // 枚举数据操作数数量不匹配
	SyntexError_EnumerationTypeUnpair,        // 枚举数据操作数类型不匹配
	SyntexError_LoopForCountUnpair,           // for循环元素操作数数量不匹配
	SyntexError_LoopForTypeUnpair,            // for循环元素类型不兼容
	SyntexError_LoopWhileCountUnpair,         // while循环元素操作数数量不匹配
	SyntexError_LoopWhileTypeUnpair,          // while循环元素类型不兼容
	SyntexError_LoopRepeatCountUnpair,        // repeat循环元素操作数数量不匹配
	SyntexError_LoopRepeatTypeUnpair,         // repeat循环元素类型不兼容
	SyntexError_IdentifierReadOnly,           // 标识符是只读的，不可写入
	SyntexError_NotStatement,                 // 不是一个可用的表达式
	SyntexError_ShouldBeCondition,            // 检查条件时必须是一个条件
	SyntexError_ShouldOnlyOne,                // 检查条件时必须最多只能有一个条件
	
	SyntaxError_End,
};

#define SYNTAXLEVEL_WARNING "警告"
#define SYNTAXLEVEL_ERROR   "错误"
#define SYNTAXLEVEL_INFO    "信息"

static const std::map<unsigned int, std::string> ERROR_ST_SYNTAX_MAP = {
	std::make_pair((unsigned int)deci::SyntaxType::SyntaxWarning_UnuseParam,             std::string("未使用的参数")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntaxWarning_NumberChange,           std::string("类型强制转换")),

	std::make_pair((unsigned int)deci::SyntaxType::SyntaxError_Syntax,                   std::string("语法错误")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_NumberBasal,              std::string("错误的数字类型（基底数类型）")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_NumberType,               std::string("错误的数字类型（类型数类型）")),

	std::make_pair((unsigned int)deci::SyntaxType::SyntaxError_Semantic,                 std::string("语义错误")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntaxError_Declaration,              std::string("未定义的标识符")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_CaseNumberInteger,        std::string("CASE枚举必须是整数")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_CaseNumberRepeat,         std::string("CASE枚举不允许重复")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_FunctionParamUnpair,      std::string("没有与参数列表匹配的函数")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_FunctionParamTypeUnpair,  std::string("函数参数类型不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_BinaryCountUnpair,        std::string("二元操作符操作数量不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_BinaryTypeUnpair,         std::string("二元操作符操作类型不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_UnaryCountUnpair,         std::string("操作符操作数量不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_UnaryTypeUnpair,          std::string("操作符操作类型不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_ConditionCountUnpair,     std::string("条件操作数量不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_ConditionTypeUnpair,      std::string("条件操作数类型必须使用布尔型")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_EnumerationCountUnpair,   std::string("枚举操作数量不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_EnumerationTypeUnpair,    std::string("枚举操作数类型必须使用整数型")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_LoopForCountUnpair,       std::string("For循环操作数不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_LoopForTypeUnpair,        std::string("For循环操作数类型必须相互兼容")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_LoopWhileCountUnpair,     std::string("While循环操作数不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_LoopWhileTypeUnpair,      std::string("While循环操作数类型必须相互兼容")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_LoopRepeatCountUnpair,    std::string("Repeat循环操作数不匹配")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_LoopRepeatTypeUnpair,     std::string("Repeat循环操作数类型必须相互兼容")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_IdentifierReadOnly,       std::string("只读标识符不允许写入")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_NotStatement,             std::string("不是一个表达式（赋值语句、条件语句、循环语句）")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_ShouldBeCondition,        std::string("必须是一个布尔值表达式")),
	std::make_pair((unsigned int)deci::SyntaxType::SyntexError_ShouldOnlyOne,            std::string("必须有且只有一条条件表达式")),
};

typedef struct SyntaxError
{
	unsigned int beginLine;
	unsigned int beginColumn;
	unsigned int endLine;
	unsigned int endColumn;
	std::string msg;
	std::string level;
	SyntaxType type;
	//SyntaxLevel level;

	inline SyntaxError(SyntaxType errorType = SyntaxType::SyntaxError_Syntax)
	{
		beginLine = 0;
		beginColumn = 0;
		endLine = 0;
		endColumn = 0;
		msg = "";
		level = "";
		type = errorType;
	}

	inline SyntaxError(location errorLocation, SyntaxType errorType = SyntaxType::SyntaxError_Syntax)
	{
		beginLine = errorLocation.begin.line;
		beginColumn = errorLocation.begin.column;
		endLine = errorLocation.end.line;
		endColumn = errorLocation.end.column;
		msg = "";
		level = "";
		type = errorType;
	}

	inline std::string GetType(void)
	{
		if (type > deci::SyntaxType::SyntaxError_Syntax && type < deci::SyntaxType::SyntaxError_Semantic)
		{
			return ERROR_ST_SYNTAX_MAP.at((unsigned int)deci::SyntaxType::SyntaxError_Syntax);
		}

		if (type > deci::SyntaxType::SyntaxError_Semantic && type < deci::SyntaxType::SyntaxError_End)
		{
			return ERROR_ST_SYNTAX_MAP.at((unsigned int)deci::SyntaxType::SyntaxError_Semantic);
		}

		// 从RC文件中根据错误码code获得错误提示文本msg
		if (ERROR_ST_SYNTAX_MAP.find((unsigned int)type) != ERROR_ST_SYNTAX_MAP.end())
		{
			return ERROR_ST_SYNTAX_MAP.at((unsigned int)type);
		}

		return std::string();
	}

	inline SyntaxLevel GetLevel(void)
	{
		if (type >= SyntaxType::SyntaxWarning_Begin && type <= SyntaxType::SyntaxWarning_End)
		{
			return SyntaxLevel::SyntaxLevel_Warning;
		}
		else if (type >= SyntaxType::SyntaxError_Begin && type <= SyntaxType::SyntaxError_End)
		{
			return SyntaxLevel::SyntaxLevel_Error;
		}

		return SyntaxLevel::SyntaxLevel_Info;
	}

	inline void FillErrorMsg(void)
	{
		if (msg.size() == 0)
		{
			// 从RC文件中根据错误码code获得错误提示文本msg
			if (ERROR_ST_SYNTAX_MAP.find((unsigned int)type) != ERROR_ST_SYNTAX_MAP.end())
			{
				msg = ERROR_ST_SYNTAX_MAP.at((unsigned int)type);
			}
		}

		switch (GetLevel())
		{
		case SyntaxLevel::SyntaxLevel_Info:
			level = SYNTAXLEVEL_INFO;
		break;
		case SyntaxLevel::SyntaxLevel_Warning:
			level = SYNTAXLEVEL_WARNING;
		break;
		case SyntaxLevel::SyntaxLevel_Error:
			level = SYNTAXLEVEL_ERROR;
		break;
		default:
			level = SYNTAXLEVEL_INFO;
			break;
		}
	}
} SyntaxError;

}