#include <sstream>
#include <iostream>
#include <iomanip>
#include <deci/symbol_table.hpp>

namespace deci
{

void symbol::initialize(void)
{
    m_nType = AstSymbolType::AstSymbolType_UNKNOWN;
    m_strName = "";
    m_location.initialize();
    m_nRWType = symbol_rw::symbol_readwrite;
}

symbol::symbol(void)
{
    this->initialize();
}

symbol::symbol(const std::string& name)
{
    this->initialize();
    m_strName = name;
}

symbol::symbol(const AstSymbolType type)
{
    this->initialize();
    m_nType = type;
}

symbol::symbol(const AstSymbolType type, const std::string& name)
{
    this->initialize();
    m_nType = type;
    m_strName = name;
}

symbol::symbol(const std::string& name, const location& location)
{
    this->initialize();
    m_strName = name;
    m_location = location;
}

symbol::symbol(const std::string& type, const std::string& name, const location& location)
{
    this->initialize();
    this->SetType(type);
    m_strName = name;
    m_location = location;
}

symbol::symbol(const AstSymbolType type, const std::string& name, const symbol_rw rwType)
{
    this->initialize();
    m_nType = type;
    m_nRWType = rwType;
    m_strName = name;
}

symbol::symbol(const AstSymbolType type, const std::string& name, const location& location)
{
    this->initialize();
    m_nType = type;
    m_strName = name;
    m_location = location;
}

symbol::~symbol(void)
{
}

void symbol::SetType(const AstSymbolType type)
{
    m_nType = type;
}

void symbol::SetType(const std::string& type)
{
    if (AST_SYMBOL_MAP.find(type) != AST_SYMBOL_MAP.end())
    {
        m_nType = AST_SYMBOL_MAP.at(type);
    }
}

void symbol::SetName(const std::string& name)
{
    m_strName = name;
}

void symbol::SetLocation(const location& location)
{
    m_location = location;
}

AstSymbolType symbol::GetType(void)
{
	return m_nType;
}

std::string symbol::GetName(void) const
{
	return m_strName;
}

location symbol::GetLocation(void)
{
	return m_location;
}

symbol_rw symbol::GetRWType(void)
{
    return m_nRWType;
}

std::string symbol::ToString(void) const
{
    std::stringstream sStream;
    sStream << std::setw(3) << m_location.begin.line << "."
			<< std::setw(3) << m_location.begin.column << ":"
			<< std::setw(3) << m_location.end.line << "."
			<< std::setw(3) << m_location.end.column << " ["
			<< std::to_string((double)m_nType) << "] : "
            << m_strName;
    return sStream.str();
}

void symbol_table::initialize(void)
{
    m_identifiers.clear();
    m_identifiersMap.clear();
    m_identifiersFlag.clear();
}

symbol_table::symbol_table(void)
{
    this->initialize();
}

symbol_table::~symbol_table(void)
{
    this->initialize();
}

void symbol_table::AddSymbol(const symbol& symbol)
{
    if (m_identifiersFlag.find(symbol.ToString()) == m_identifiersFlag.end())
    {
        m_identifiers.push_back(symbol);
        m_identifiersFlag[symbol.ToString()] = nullptr;
        m_identifiersMap[symbol.GetName()].push_back(symbol);
    }
}

void symbol_table::AddSymbol(const std::vector<symbol>& symbols)
{
    for (auto iter : symbols)
    {
        this->AddSymbol(iter);
    }
}

symbol symbol_table::GetSymbol(const int nIndex)
{
    if (m_identifiers.size() <= (size_t)nIndex)
    {
        return symbol();
    }
	
    return m_identifiers[nIndex];
}

std::vector<symbol> symbol_table::GetSymbol(const std::string& name)
{
    if (m_identifiersMap.find(name) != m_identifiersMap.end())
    {
        return m_identifiersMap.at(name);
    }
	return std::vector<symbol>();
}

std::vector<symbol> symbol_table::GetSymbol(void)
{
	return m_identifiers;
}

std::map<std::string, std::vector<symbol>> symbol_table::GetSymbolMap(void)
{
    return m_identifiersMap;
}

bool symbol_table::SymbolExist(const std::string& name)
{
    return m_identifiersMap.find(name) != m_identifiersMap.end();
}

void symbol_table::clear(void)
{
    this->initialize();
}

symbol_table symbol_table::operator+(const symbol_table& secTable)
{
    for (auto mapIter : secTable.m_identifiersMap)
    {
        std::vector<symbol> symbols = mapIter.second;
        if (m_identifiersMap.find(mapIter.first) != m_identifiersMap.end())
        {
            std::vector<symbol> unrepeatSymbols;
            for (auto iter : symbols)
            {
                if (m_identifiersFlag.find(iter.ToString()) == m_identifiersFlag.end())
                {
                    unrepeatSymbols.push_back(iter);
                }
            }

            symbols = unrepeatSymbols;
        }
        
        for (auto symbol : symbols)
        {
            m_identifiers.push_back(symbol);
            m_identifiersFlag[symbol.ToString()] = nullptr;
            m_identifiersMap[symbol.GetName()].push_back(symbol);
        }
    }

    return *this;
}


void function_table::initialize(void)
{
    m_argumentMap.clear();
    m_coverIdentifierMap.clear();
}

function_table::function_table(void)
{
    this->initialize();
}

function_table::~function_table(void)
{
    this->initialize();
}

void function_table::AddFunction(const symbol& identifier, std::vector<symbol>& argument)
{
    this->AddSymbol(identifier);
    m_argumentMap[identifier.GetName()] = argument;
}

void function_table::AddFunction(const symbol& identifier, std::vector<symbol>& argument, std::string& coverIdentifier)
{
    this->AddFunction(identifier, argument);
    m_coverIdentifierMap[identifier.GetName()] = coverIdentifier;
}

std::vector<symbol> function_table::GetArguments(const std::string& identifier)
{
    if (m_argumentMap.find(identifier) != m_argumentMap.end())
    {
        return m_argumentMap.at(identifier);
    }

    return std::vector<symbol>();
}

std::string function_table::GetCoverIdentifier(const std::string& identifier)
{
    if (m_coverIdentifierMap.find(identifier) != m_coverIdentifierMap.end())
    {
        return m_coverIdentifierMap.at(identifier);
    }

    return std::string();
}

void function_table::clear(void)
{
    symbol_table::clear();
    this->initialize();
}

}