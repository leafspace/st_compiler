#pragma once

/**************************************************************************
*	Copyright (c) 2022,SUPCON
*
*	文件名称： 	symbol_table.hpp
*	作    者：	zhanglifei
*	创建日期：	2022/08/29
*	摘    要：	符号表头文件（包含了常量表、变量表、函数表）
*
***************************************************************************/

#include <map>
#include <vector>

#include "type.hpp"
#include "location.hh"

namespace deci
{

/* @Name: symbol_rw
*  @Comment: 符号变量可读写的标志（仅限变量或常量）
*/
enum class symbol_rw
{
    symbol_read,
    symbol_readwrite,
};

/* @Name: symbol
*  @Comment: 符号标识，可以是变量、常量或者函数名称
*/
class symbol
{
private:
    AstSymbolType m_nType;      // 符号类型
    std::string m_strName;       // 符号名称
    location m_location;         // 符号出现的位置
    symbol_rw m_nRWType;         // 符号读写类型

    void initialize(void);

public:
    symbol(void);
    symbol(const std::string&);
    symbol(const AstSymbolType);
    symbol(const AstSymbolType, const std::string&);
    symbol(const std::string&, const location&);
    symbol(const std::string&, const std::string&, const location&);
    symbol(const AstSymbolType, const std::string&, const symbol_rw);
    symbol(const AstSymbolType, const std::string&, const location&);
    ~symbol(void);

    void SetType(const AstSymbolType);
    void SetType(const std::string&);
    void SetName(const std::string&);
    void SetLocation(const location&);

    AstSymbolType GetType(void);
    std::string GetName(void) const;
    location GetLocation(void);
    symbol_rw GetRWType(void);

    std::string ToString(void) const;
};

/* @Name: symbol_table
*  @Comment: 符号表基类
*/
class symbol_table
{
protected:
    std::vector<symbol> m_identifiers;                           // 标识符列表
    std::map<std::string, std::vector<symbol>> m_identifiersMap; // 以标识符名称分类的标识符列表
    std::map<std::string, void*> m_identifiersFlag;              // 保证同一标识符同一位置唯一

    void initialize(void);

public:
    symbol_table(void);
    ~symbol_table(void);

    void AddSymbol(const symbol&);
    void AddSymbol(const std::vector<symbol>&);
    symbol GetSymbol(const int);
    std::vector<symbol> GetSymbol(const std::string&);
    std::vector<symbol> GetSymbol(void);
    std::map<std::string, std::vector<symbol>> GetSymbolMap(void);
    bool SymbolExist(const std::string&);

    virtual void clear(void);

    symbol_table operator+(const symbol_table&);
};

/* @Name: constant_table
*  @Comment: 常量表
*/
class constant_table : public symbol_table
{
};

/* @Name: variant_table
*  @Comment: 变量表
*/
class variant_table : public symbol_table
{
};

/* @Name: function_table
*  @Comment: 函数表
*/
class function_table : public symbol_table
{
private:
    std::map<std::string, std::vector<symbol>> m_argumentMap;  // 函数名所对应的参数列表（不支持重载）
    std::map<std::string, std::string> m_coverIdentifierMap;   // 由A函数名转为B函数名

    void initialize(void);

public:
    function_table(void);
    ~function_table(void);

    void AddFunction(const symbol&, std::vector<symbol>&);     // 新增一个内部函数
    void AddFunction(const symbol&, std::vector<symbol>&, std::string&);     // 新增一个内部函数

    std::vector<symbol> GetArguments(const std::string&);      // 获取函数的参数列表
    std::string GetCoverIdentifier(const std::string&);        // 获取覆盖的新函数名

    void clear(void) override;
};

}