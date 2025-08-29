#include <deci/type.hpp>
#include <deci/ast_number_t.hpp>

namespace deci
{

ast_basal_number::ast_basal_number(void)
{
	m_nHex = 0;
	m_strValue = "";
}

ast_basal_number::ast_basal_number(const unsigned short nHex, const std::string strValue)
	:m_nHex(nHex), m_strValue(strValue)
{
}

double ast_basal_number::ConvertValue(void)
{
	double dbValue = 0.0;

	for (std::string::iterator iter = this->m_strValue.begin();
		iter != this->m_strValue.end(); ++iter)
	{
		int nBit = toupper(*iter);
		if (isdigit(nBit)) nBit = nBit - '0';
		if (isalpha(nBit)) nBit = nBit - 'A' + 10;

		dbValue = dbValue * m_nHex + nBit;
	}

	return dbValue;
}

ast_type_number::ast_type_number(void)
{
	m_strType = "";
	m_dbValue = 0.0;
}

ast_type_number::ast_type_number(const std::string& strType, const double dbValue)
	:m_strType(strType), m_dbValue(dbValue)
{
}

double ast_type_number::ConvertValue(void)
{

	if (AST_SYMBOL_MAP.find(this->m_strType) != AST_SYMBOL_MAP.end())
	{
		AstSymbolType numberType = AST_SYMBOL_MAP.at(this->m_strType);
		switch (numberType)
		{
		case AstSymbolType::AstSymbolType_SINT:
			return (char)(this->m_dbValue);
		case AstSymbolType::AstSymbolType_INT:
			return (short)(this->m_dbValue);
		case AstSymbolType::AstSymbolType_DINT:
			return (long int)(this->m_dbValue);
		case AstSymbolType::AstSymbolType_USINT:
			return (unsigned char)(this->m_dbValue);
		case AstSymbolType::AstSymbolType_UINT:
			return (unsigned short)(this->m_dbValue);
		case AstSymbolType::AstSymbolType_UDINT:
			return (unsigned long int)(this->m_dbValue);
		default:
			break;
		}
	}

	return this->m_dbValue;
}

}
