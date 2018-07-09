///////////////////////////////////////////////////////////////////////////////
#include "ies_std.h"
#include "msdbcall.h"

//////////////////////////////////////////////////////////////////////////////
// CiESDBVariant

CiESDBVariant::CiESDBVariant()
{
	m_nDataType = IES_SQL_INT;
	m_nDataSize = 0;
	m_strFieldName = "";
	memset(m_data, 0, sizeof(m_data));
}

CiESDBVariant::CiESDBVariant(Jint32 nDataType, Jint32 nDataSize)
{
	m_nDataType = IES_SQL_INT;
	m_nDataSize = 0;
	m_strFieldName = "";

	SetVarType(nDataType, nDataSize);
}


CiESDBVariant::~CiESDBVariant()
{
	Clear();
}

void CiESDBVariant::Clear()
{
	if (m_nDataType == IES_SQL_TIMESTAMP)
		delete m_pTime;
	else if (m_nDataType == IES_SQL_STRING)
		delete[] m_pString;
	else if (m_nDataType == IES_SQL_BINARY)
		delete[] m_pBinary;

	m_nDataType = IES_SQL_INT;
	m_nDataSize = 0;
	memset(m_data, 0, sizeof(m_data));
}

void CiESDBVariant::initData()
{
	switch(m_nDataType) {
	case IES_SQL_TIMESTAMP:
		m_pTime->nYear = 2000;
		m_pTime->nMonth = 1;
		m_pTime->nDay = 1;
		m_pTime->nHour = 0;
		m_pTime->nMinute = 0;
		m_pTime->nSecond = 0;
		m_pTime->nFraction = 0;
		break;
	case IES_SQL_STRING:
		memset(m_pString, 0, m_nDataSize+1);
		m_pString[0] = ' ';
		break;
	case IES_SQL_BINARY:
		memset(m_pBinary, 0, m_nDataSize);
		break;
	default:
		memset(m_data, 0, sizeof(m_data));
		break;
	}
}

void CiESDBVariant::SetVarType(Jint32 nDataType, Jint32 nDataSize)
{
	nDataSize = nDataSize>0 ? nDataSize : 0;
	if (m_nDataType != nDataType)
	{
		Clear();
		m_nDataType = nDataType;
		m_nDataSize = nDataSize;

		if (m_nDataType == IES_SQL_TIMESTAMP)
			m_pTime = new STimeInfo;
		else if (m_nDataType == IES_SQL_STRING)
			m_pString = new Jchar[m_nDataSize+1];
		else if (m_nDataType == IES_SQL_BINARY)
			m_pBinary = new Juint8[m_nDataSize];

		initData();
	}
	else
	{
		SetVarSize(nDataSize);
	}

}

void CiESDBVariant::SetVarSize(Jint32 nDataSize)
{
	nDataSize = nDataSize>0 ? nDataSize : 0;
	switch(m_nDataType)
	{
	case IES_SQL_STRING:
		if (m_nDataSize != nDataSize) {
			delete[] m_pString;
			m_nDataSize = nDataSize;
			m_pString = new Jchar[m_nDataSize+1];
		}
		break;
	case IES_SQL_BINARY:
		if (m_nDataSize != nDataSize) {
			delete[] m_pBinary;
			m_nDataSize = nDataSize;
			m_pBinary = new Juint8[m_nDataSize];
		}
		break;
	default:
		m_nDataSize = 0;
	}
	initData();
}

void CiESDBVariant::GetVarValue(Jint32& iData)
{
	switch(m_nDataType)
	{
	case IES_SQL_BOOL:
		iData = m_bVal;
		break;
	case IES_SQL_UTINYINT:
		iData = m_u1Val;
		break;
	case IES_SQL_SMALLINT:
		iData = m_i2Val;
		break;
	case IES_SQL_USMALLINT:
		iData = m_u2Val;
		break;
	case IES_SQL_INT:
		iData = m_i4Val;
		break;
	case IES_SQL_UINT:
		iData = m_u4Val;
		break;
	case IES_SQL_FLOAT:
		iData = m_fVal;
		break;
	case IES_SQL_DOUBLE:
		iData = m_dVal;
		break;
	default:
		iData = 0;
	}
}

const CiESDBVariant& CiESDBVariant::operator=(const CiESDBVariant& varSrc)
{

	if (m_nDataType != varSrc.m_nDataType || m_nDataSize != varSrc.m_nDataSize)
		SetVarType(varSrc.m_nDataType, varSrc.m_nDataSize);

	m_strFieldName = varSrc.m_strFieldName;
	switch(m_nDataType)
	{
	case IES_SQL_BOOL:
	case IES_SQL_UTINYINT:
	case IES_SQL_SMALLINT:
	case IES_SQL_USMALLINT:
	case IES_SQL_INT:
	case IES_SQL_UINT:
	case IES_SQL_FLOAT:
	case IES_SQL_DOUBLE:
		memcpy(m_data, varSrc.m_data, sizeof(m_data));
		m_nDataSize = 0;
		break;
	case IES_SQL_TIMESTAMP:
		*m_pTime = *varSrc.m_pTime;
		m_nDataSize = 0;
		break;
	case IES_SQL_STRING:
		ii_strncpy(m_pString, varSrc.m_pString, m_nDataSize);
		break;
	case IES_SQL_BINARY:
		memcpy(m_pBinary, varSrc.m_pBinary, m_nDataSize*sizeof(Juint8));
		break;
	}

	return *this;
}
