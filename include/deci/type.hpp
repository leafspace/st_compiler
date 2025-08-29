#pragma once

/**************************************************************************
*	Copyright (c) 2022,SUPCON
*
*	文件名称： 	type.hpp
*	作    者：	zhanglifei
*	创建日期：	2022/08/29
*	摘    要：	语言中的变量类型
*
***************************************************************************/

#include <map>
#include <iostream>

namespace deci
{

#define ASTSYMBOL_TYPE_SINT   "SINT"
#define ASTSYMBOL_TYPE_INT    "INT"
#define ASTSYMBOL_TYPE_DINT   "DINT"
#define ASTSYMBOL_TYPE_USINT  "USINT"
#define ASTSYMBOL_TYPE_UINT   "UINT"
#define ASTSYMBOL_TYPE_UDINT  "UDINT"
#define ASTSYMBOL_TYPE_REAL   "REAL"
#define ASTSYMBOL_TYPE_BOOL   "BOOL"
#define ASTSYMBOL_TYPE_STRING "STRING"

enum class AstSymbolType
{
	AstSymbolType_UNUSE,         // 无用的，相当于void
	AstSymbolType_UNKNOWN,       // 未知的，相当于错误
	AstSymbolType_CAST,          // 强制类型转换
	AstSymbolType_NUMBER_BEGIN,
	AstSymbolType_SINT,
	AstSymbolType_INT,
	AstSymbolType_DINT,
	AstSymbolType_USINT,
	AstSymbolType_UINT,
	AstSymbolType_UDINT,
	AstSymbolType_REAL,
	AstSymbolType_NUMBER_END,
	AstSymbolType_BOOL,
	AstSymbolType_STRING,
};

static const std::map<std::string, AstSymbolType> AST_SYMBOL_MAP = {
	std::make_pair(ASTSYMBOL_TYPE_SINT,    AstSymbolType::AstSymbolType_SINT),
	std::make_pair(ASTSYMBOL_TYPE_INT,     AstSymbolType::AstSymbolType_INT),
	std::make_pair(ASTSYMBOL_TYPE_DINT,    AstSymbolType::AstSymbolType_DINT),
	std::make_pair(ASTSYMBOL_TYPE_USINT,   AstSymbolType::AstSymbolType_USINT),
	std::make_pair(ASTSYMBOL_TYPE_UINT,    AstSymbolType::AstSymbolType_UINT),
	std::make_pair(ASTSYMBOL_TYPE_UDINT,   AstSymbolType::AstSymbolType_UDINT),
	std::make_pair(ASTSYMBOL_TYPE_REAL,    AstSymbolType::AstSymbolType_REAL),
	std::make_pair(ASTSYMBOL_TYPE_BOOL,    AstSymbolType::AstSymbolType_BOOL),
	std::make_pair(ASTSYMBOL_TYPE_STRING,  AstSymbolType::AstSymbolType_STRING),
};

enum class Identifier_Type
{
	Identifier_Constant,
	Identifier_Variant,
	Identifier_Function,
};

inline AstSymbolType UpgradeType(AstSymbolType oldType, AstSymbolType newType)
{
	static std::map<AstSymbolType, std::map<AstSymbolType, AstSymbolType>> typeMap = {
		std::make_pair(AstSymbolType::AstSymbolType_SINT,
			std::map<AstSymbolType, AstSymbolType> {
				std::make_pair(AstSymbolType::AstSymbolType_SINT, AstSymbolType::AstSymbolType_SINT),
				std::make_pair(AstSymbolType::AstSymbolType_INT, AstSymbolType::AstSymbolType_INT),
				std::make_pair(AstSymbolType::AstSymbolType_DINT, AstSymbolType::AstSymbolType_DINT),
				std::make_pair(AstSymbolType::AstSymbolType_USINT, AstSymbolType::AstSymbolType_USINT),
				std::make_pair(AstSymbolType::AstSymbolType_UINT, AstSymbolType::AstSymbolType_UINT),
				std::make_pair(AstSymbolType::AstSymbolType_UDINT, AstSymbolType::AstSymbolType_UDINT),
				std::make_pair(AstSymbolType::AstSymbolType_REAL, AstSymbolType::AstSymbolType_REAL),
				std::make_pair(AstSymbolType::AstSymbolType_BOOL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_STRING, AstSymbolType::AstSymbolType_UNKNOWN),
			}
		),
		std::make_pair(AstSymbolType::AstSymbolType_INT,
			std::map<AstSymbolType, AstSymbolType> {
				std::make_pair(AstSymbolType::AstSymbolType_SINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_INT, AstSymbolType::AstSymbolType_INT),
				std::make_pair(AstSymbolType::AstSymbolType_DINT, AstSymbolType::AstSymbolType_DINT),
				std::make_pair(AstSymbolType::AstSymbolType_USINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_UINT, AstSymbolType::AstSymbolType_UINT),
				std::make_pair(AstSymbolType::AstSymbolType_UDINT, AstSymbolType::AstSymbolType_UDINT),
				std::make_pair(AstSymbolType::AstSymbolType_REAL, AstSymbolType::AstSymbolType_REAL),
				std::make_pair(AstSymbolType::AstSymbolType_BOOL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_STRING, AstSymbolType::AstSymbolType_UNKNOWN),
			}
		),
		std::make_pair(AstSymbolType::AstSymbolType_DINT,
			std::map<AstSymbolType, AstSymbolType> {
				std::make_pair(AstSymbolType::AstSymbolType_SINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_INT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_DINT, AstSymbolType::AstSymbolType_DINT),
				std::make_pair(AstSymbolType::AstSymbolType_USINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_UINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_UDINT, AstSymbolType::AstSymbolType_UDINT),
				std::make_pair(AstSymbolType::AstSymbolType_REAL, AstSymbolType::AstSymbolType_REAL),
				std::make_pair(AstSymbolType::AstSymbolType_BOOL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_STRING, AstSymbolType::AstSymbolType_UNKNOWN),
			}
		),
		std::make_pair(AstSymbolType::AstSymbolType_USINT,
			std::map<AstSymbolType, AstSymbolType> {
				std::make_pair(AstSymbolType::AstSymbolType_SINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_INT, AstSymbolType::AstSymbolType_INT),
				std::make_pair(AstSymbolType::AstSymbolType_DINT, AstSymbolType::AstSymbolType_DINT),
				std::make_pair(AstSymbolType::AstSymbolType_USINT, AstSymbolType::AstSymbolType_USINT),
				std::make_pair(AstSymbolType::AstSymbolType_UINT, AstSymbolType::AstSymbolType_UINT),
				std::make_pair(AstSymbolType::AstSymbolType_UDINT, AstSymbolType::AstSymbolType_UDINT),
				std::make_pair(AstSymbolType::AstSymbolType_REAL, AstSymbolType::AstSymbolType_REAL),
				std::make_pair(AstSymbolType::AstSymbolType_BOOL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_STRING, AstSymbolType::AstSymbolType_UNKNOWN),
			}
		),
		std::make_pair(AstSymbolType::AstSymbolType_UINT,
			std::map<AstSymbolType, AstSymbolType> {
				std::make_pair(AstSymbolType::AstSymbolType_SINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_INT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_DINT, AstSymbolType::AstSymbolType_DINT),
				std::make_pair(AstSymbolType::AstSymbolType_USINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_UINT, AstSymbolType::AstSymbolType_UINT),
				std::make_pair(AstSymbolType::AstSymbolType_UDINT, AstSymbolType::AstSymbolType_UDINT),
				std::make_pair(AstSymbolType::AstSymbolType_REAL, AstSymbolType::AstSymbolType_REAL),
				std::make_pair(AstSymbolType::AstSymbolType_BOOL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_STRING, AstSymbolType::AstSymbolType_UNKNOWN),
			}
		),
		std::make_pair(AstSymbolType::AstSymbolType_UDINT,
			std::map<AstSymbolType, AstSymbolType> {
				std::make_pair(AstSymbolType::AstSymbolType_SINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_INT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_DINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_USINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_UINT, AstSymbolType::AstSymbolType_CAST),
				std::make_pair(AstSymbolType::AstSymbolType_UDINT, AstSymbolType::AstSymbolType_UDINT),
				std::make_pair(AstSymbolType::AstSymbolType_REAL, AstSymbolType::AstSymbolType_REAL),
				std::make_pair(AstSymbolType::AstSymbolType_BOOL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_STRING, AstSymbolType::AstSymbolType_UNKNOWN),
			}
		),
		std::make_pair(AstSymbolType::AstSymbolType_REAL,
			std::map<AstSymbolType, AstSymbolType> {
				std::make_pair(AstSymbolType::AstSymbolType_SINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_INT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_DINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_USINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_UINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_UDINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_REAL, AstSymbolType::AstSymbolType_REAL),
				std::make_pair(AstSymbolType::AstSymbolType_BOOL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_STRING, AstSymbolType::AstSymbolType_UNKNOWN),
			}
		),
		std::make_pair(AstSymbolType::AstSymbolType_BOOL,
			std::map<AstSymbolType, AstSymbolType> {
				std::make_pair(AstSymbolType::AstSymbolType_SINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_INT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_DINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_USINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_UINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_UDINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_REAL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_BOOL, AstSymbolType::AstSymbolType_BOOL),
				std::make_pair(AstSymbolType::AstSymbolType_STRING, AstSymbolType::AstSymbolType_UNKNOWN),
			}
		),
		std::make_pair(AstSymbolType::AstSymbolType_STRING,
			std::map<AstSymbolType, AstSymbolType> {
				std::make_pair(AstSymbolType::AstSymbolType_SINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_INT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_DINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_USINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_UINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_UDINT, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_REAL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_BOOL, AstSymbolType::AstSymbolType_UNKNOWN),
				std::make_pair(AstSymbolType::AstSymbolType_STRING, AstSymbolType::AstSymbolType_UNKNOWN),
			}
		),
	};

	if (typeMap.find(oldType) != typeMap.end())
	{
		auto tmpMap = typeMap.at(oldType);
		if (tmpMap.find(newType) != tmpMap.end())
		{
			return tmpMap.at(newType);
		}
	}

	return AstSymbolType::AstSymbolType_UNKNOWN;
}

inline bool IsDigit(AstSymbolType type)
{
	return type > AstSymbolType::AstSymbolType_NUMBER_BEGIN && type < AstSymbolType::AstSymbolType_NUMBER_END;
}

}