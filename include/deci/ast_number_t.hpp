#pragma once

/**************************************************************************
*	Copyright (c) 2022,SUPCON
*
*	文件名称： 	ast_number_t.h
*	作    者：	zhanglifei
*	创建日期：	2022/08/23
*	摘    要：	BNF树数值类型
*
***************************************************************************/

#include <iostream>

namespace deci
{

class ast_basal_number
{
public:
	unsigned int m_nHex;              // 底数，标识x进制
	std::string m_strValue;           // 进制下的值

public:
	ast_basal_number(void);
	ast_basal_number(const unsigned short, const std::string);
	double ConvertValue(void);
};

class ast_type_number
{
public:
	std::string m_strType;            // 数值类型
	double m_dbValue;                 // 原始数据值
public:
	ast_type_number(void);
	ast_type_number(const std::string&, const double);
	double ConvertValue(void);
};

}