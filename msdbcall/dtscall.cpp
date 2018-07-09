///////////////////////////////////////////////////////////////////////////////
#include "iessbmix.h"
#include "dbdefine.h"
#include "msdbcall.h"

// ----------------------------------------------------------------------------
// 本文件提供访问描述库的各种常用函数，供绘图和人机接口界面使用
// ----------------------------------------------------------------------------
extern CIILog gCIILog_msdbcall;

void CMSData::BindDBCol(CIIOdbcDBI* msdb, CiESDBVariant &var, Jboolean bOut)
{
	if (bOut)
	{
		switch(var.GetVarType())
		{
		case IES_SQL_BOOL:
			msdb->BindCol(IES_SQL_BOOL, 0, &var.m_bVal);
			break;
		case IES_SQL_UTINYINT:
			msdb->BindCol(IES_SQL_UTINYINT, 0, &var.m_u1Val);
			break;
		case IES_SQL_SMALLINT:
			msdb->BindCol(IES_SQL_SMALLINT, 0, &var.m_i2Val);
			break;
		case IES_SQL_USMALLINT:
			msdb->BindCol(IES_SQL_USMALLINT, 0, &var.m_u2Val);
			break;
		case IES_SQL_INT:
			msdb->BindCol(IES_SQL_INT, 0, &var.m_i4Val);
			break;
		case IES_SQL_UINT:
			msdb->BindCol(IES_SQL_UINT, 0, &var.m_u4Val);
			break;
		case IES_SQL_FLOAT:
			msdb->BindCol(IES_SQL_FLOAT, 0, &var.m_fVal);
			break;
		case IES_SQL_DOUBLE:
			msdb->BindCol(IES_SQL_DOUBLE, 0, &var.m_dVal);
			break;
		case IES_SQL_TIMESTAMP:
			msdb->BindCol(IES_SQL_TIMESTAMP, 0, var.m_pTime);
			break;
		case IES_SQL_STRING:
			msdb->BindCol(IES_SQL_STRING, var.GetVarSize(), (void*)var.m_pString);
			break;
		case IES_SQL_BINARY:
			msdb->BindCol(IES_SQL_BINARY, var.GetVarSize(), (void*)var.m_pBinary);
			break;
		default:
			break;
		}
	}
	else
	{
		switch(var.GetVarType())
		{
		case IES_SQL_BOOL:
			msdb->BindPara(IES_SQL_BOOL, 0, &var.m_bVal);
			break;
		case IES_SQL_UTINYINT:
			msdb->BindPara(IES_SQL_UTINYINT, 0, &var.m_u1Val);
			break;
		case IES_SQL_SMALLINT:
			msdb->BindPara(IES_SQL_SMALLINT, 0, &var.m_i2Val);
			break;
		case IES_SQL_USMALLINT:
			msdb->BindPara(IES_SQL_USMALLINT, 0, &var.m_u2Val);
			break;
		case IES_SQL_INT:
			msdb->BindPara(IES_SQL_INT, 0, &var.m_i4Val);
			break;
		case IES_SQL_UINT:
			msdb->BindPara(IES_SQL_UINT, 0, &var.m_u4Val);
			break;
		case IES_SQL_FLOAT:
			msdb->BindPara(IES_SQL_FLOAT, 0, &var.m_fVal);
			break;
		case IES_SQL_DOUBLE:
			msdb->BindPara(IES_SQL_DOUBLE, 0, &var.m_dVal);
			break;
		case IES_SQL_TIMESTAMP:
			msdb->BindPara(IES_SQL_TIMESTAMP, 0, var.m_pTime);
			break;
		case IES_SQL_STRING:
			msdb->BindPara(IES_SQL_STRING, var.GetVarSize(), (void*)var.m_pString);
			break;
		case IES_SQL_BINARY:
			msdb->BindPara(IES_SQL_BINARY, var.GetVarSize(), (void*)var.m_pBinary);
			break;
		default:
			break;
		}
	}
}

CIIString CMSData::GetFilterString(CiESRecordVariant& FilterVar)
{
	CIIString strFilter, string;
	if (FilterVar.GetSize()<=0) return strFilter;

	for (Jint32 i=0; i<FilterVar.GetSize(); i++)
	{
		string.Empty();
		if (FilterVar.GetAt(i).IsNumeric()) {
			Jint32 iVal=0;
			FilterVar.GetAt(i).GetVarValue(iVal);
			string.Format("%s=%d", FilterVar.GetAt(i).m_strFieldName.GetBuf(), iVal);
		}
		else if (FilterVar.GetAt(i).GetVarType()==IES_SQL_STRING) {
			string.Format("%s='%s'", FilterVar.GetAt(i).m_strFieldName.GetBuf(), FilterVar.GetAt(i).m_pString);
		}
		else
			continue;

		strFilter += string;
		strFilter += " AND ";
	}

	if (strFilter.GetLength()>5)
		strFilter.RemoveAt(strFilter.GetLength()-5, 5);
	else
		strFilter = "";

	return strFilter;
}

// 根据过滤条件(FilterVar) 读取一条记录放到RecVar 要求使用本函数前RecVar已经初始化好
Jint32 CMSData::GetDBTableValue(Jchar* szTableName, CiESRecordVariant& FilterVar, CiESRecordVariant& RecVar, Jchar* szOrder)
{
	CONNECTMSDB();
	Jint32	FieldNum=RecVar.GetSize();
	if (FieldNum<=0) return DB_INVALID_PARAM;

	Jint32 i=0;	
	CIIString strFieldName, strSQL, strFilter;
	for (i=0; i<FieldNum; i++)
	{
		RecVar.GetAt(i).initData();
		strFieldName += RecVar.GetAt(i).m_strFieldName;
		strFieldName += ",";
	}
	strFieldName.RemoveAt(strFieldName.GetLength()-1, 1);
	strFilter = GetFilterString(FilterVar);

	strSQL = "SELECT ";
	strSQL += strFieldName;
	strSQL += " FROM ";
	strSQL += szTableName;
	if (!strFilter.IsEmpty())
	{
		strSQL += " WHERE ";
		strSQL += strFilter;
	}
	if (szOrder!=NULL && strlen(szOrder)>0)
	{
		strSQL += " order by ";
		strSQL += szOrder;
	}
	
	miaoshu->PrepareSQL(strSQL.GetBuf());

	for (i=0; i<FieldNum; i++)
	{
		BindDBCol(miaoshu, RecVar.GetAt(i));	
	}
	miaoshu->Exec();

	Jint32 ret = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
	if (ret != DB_SUCCESS) 
	{
		char strErr[255];
		const char *szErr = miaoshu->GetErrorStr();
		sprintf(strErr, "%s:%s", szTableName, szErr);
		gCIILog_msdbcall.Add(strErr);
	}
	return ret;
}

Jint32 CMSData::SetDBTableValue(Jchar* szTableName, CiESRecordVariant& FilterVar, CiESRecordVariant& RecVar, Juint8 byOpType)
{
	CONNECTMSDB();
	Jint32	FieldNum=RecVar.GetSize();
	if (FieldNum<=0 && byOpType == 0) return DB_INVALID_PARAM;
	
	Jint32 i=0;
	CIIString	strFilter, strSQL;
	strFilter = GetFilterString(FilterVar);

	if (byOpType == 0)
	{
		if (strFilter.IsEmpty() || !IsRecordExist(miaoshu, szTableName, strFilter.GetBuf()))
		{
			strSQL = "INSERT INTO ";
			strSQL += szTableName;
			strSQL += " (";
			for (i=0; i<RecVar.GetSize(); i++)
			{
				strSQL += RecVar[i].m_strFieldName;
				strSQL += ",";
			}
			strSQL.ReplaceAt(strSQL.GetLength()-1, 1, ")");
			strSQL += " VALUES (";
			for (i=0; i<RecVar.GetSize(); i++)
			{
				strSQL += "?,";
			}
			strSQL.ReplaceAt(strSQL.GetLength()-1, 1, ")");
		}
		else
		{
			strSQL = "UPDATE ";
			strSQL += szTableName;
			strSQL += " SET ";
			for (i=0; i<RecVar.GetSize(); i++)
			{
				strSQL += RecVar[i].m_strFieldName;
				strSQL += "=?,";
			}
			strSQL.ReplaceAt(strSQL.GetLength()-1, 1, " ");
			if (!strFilter.IsEmpty()) {
				strSQL += " WHERE ";
				strSQL += strFilter;
			}
		}
		miaoshu->PrepareSQL(strSQL.GetBuf());
		
		for (i=0; i<FieldNum; i++)
		{
			BindDBCol(miaoshu, RecVar.GetAt(i), 0);	
		}
	}
	else if(byOpType == 1)	// 删除		
	{
		strSQL = "DELETE FROM ";
		strSQL += szTableName;
		if (!strFilter.IsEmpty()) {
			strSQL += " WHERE ";
			strSQL += strFilter;
		}
		miaoshu->PrepareSQL(strSQL.GetBuf());
	}

	Jint32 ret = miaoshu->Exec()>0 ? DB_SUCCESS : DB_ERROR;
	if (ret != DB_SUCCESS) 
	{
		char strErr[255];
		const char *szErr = miaoshu->GetErrorStr();
		sprintf(strErr, "%s:%s", szTableName, szErr);
		gCIILog_msdbcall.Add(strErr);
	}
	miaoshu->CloseSQL();
	return ret;
}

Jint32 CMSData::GetDBTableValue(Jchar* szTableName, CiESRecordVariant& FilterVar, CiESTableVariant &TabVar, Jchar* szOrder)
{
	CONNECTMSDB();
	CiESRecordVariant RecVar = TabVar.GetAt(0);
	TabVar.SetSize(0);
	if (GetDBTableValue(szTableName, FilterVar, RecVar, szOrder)==DB_SUCCESS)
	{
		TabVar.AddLast(RecVar);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			TabVar.AddLast(RecVar);
		}
		return DB_SUCCESS;
	}
	return DB_NO_DATA_FOUND;	
}

Jint32 CMSData::AddDBTableValue(Jchar* szTableName, CiESTableVariant& TabVar)
{
	CONNECTMSDB();
	Jint32	RecordNum=TabVar.GetNum();
	if (RecordNum<=0) return DB_INVALID_PARAM;
	CiESRecordVariant RecVar = TabVar.GetAt(0);
	Jint32	FieldNum=RecVar.GetNum();
	if (FieldNum<=0) return DB_INVALID_PARAM;
	
	
	Jint32 i=0, j=0;
	Jint32 ret=0;
	CIIString	strSQL;
	
	strSQL = "INSERT INTO ";
	strSQL += szTableName;
	strSQL += " (";
	for (i=0; i<FieldNum; i++)
	{
		for (j=0; i<RecVar.GetSize(); i++)
		{
			strSQL += RecVar[i].m_strFieldName;
			strSQL += ",";
		}
	}
	strSQL.ReplaceAt(strSQL.GetLength()-1, 1, ")");
	strSQL += " VALUES (";
	for (i=0; i<RecVar.GetNum(); i++)
	{
		strSQL += "?,";
	}
	strSQL.ReplaceAt(strSQL.GetLength()-1, 1, ")");
	
	miaoshu->PrepareSQL(strSQL.GetBuf());	
	for (j=0; j<FieldNum; j++)
	{
		BindDBCol(miaoshu, RecVar.GetAt(j), 0);	
	}
	ret = miaoshu->Exec()>0 ? DB_SUCCESS : DB_ERROR;
	miaoshu->CloseSQL();
	
	for (i=1; i<RecordNum; i++)
	{
		miaoshu->PrepareSQL(strSQL.GetBuf());
		RecVar.SetSize(0);
		RecVar = TabVar.GetAt(i);
		for (j=0; j<FieldNum; j++)
		{
			BindDBCol(miaoshu, RecVar.GetAt(j), 0);	
		}
		ret = miaoshu->Exec()>0 ? DB_SUCCESS : DB_ERROR;
	}
	
	miaoshu->CloseSQL();
	return ret;
}

DATAID_TYPE CMSData::GetIDFromDB(const char* szTableName, const char* szColumnName, DATAID_TYPE value)
{
	CONNECTMSDB();
	return GetUsableID(miaoshu, szTableName, szColumnName, value);
}

Jboolean CMSData::IsRecordInDB(Jchar* szTableName, CiESRecordVariant& FilterVar)
{
	CIIString strFilter;
	Jboolean bInDB=JFALSE;
	CONNECTMSDB();
	
	strFilter = GetFilterString(FilterVar);

	bInDB = IsRecordExist(miaoshu, szTableName, strFilter.GetBuf());
	return bInDB;
}

//EMS-Mend: 翟玉广 2006.10.20
//修改原因: 增加用显式WHERE语句读写数据库记录功能
//EMS-Mend<
// 根据过滤条件(szFilter) 读取一条记录放到RecVar 要求使用本函数前RecVar已经初始化好
Jint32 CMSData::GetDBTableValue(Jchar* szTableName, Jchar* szFilter, CiESRecordVariant& RecVar, Jchar* szOrder)
{
	CONNECTMSDB();
	Jint32	FieldNum=RecVar.GetSize();
	if (FieldNum<=0) return DB_INVALID_PARAM;
	
	Jint32 i=0;	
	CIIString strFieldName, strSQL, strFilter;
	for (i=0; i<FieldNum; i++)
	{
		RecVar.GetAt(i).initData();
		strFieldName += RecVar.GetAt(i).m_strFieldName;
		strFieldName += ",";
	}
	strFieldName.RemoveAt(strFieldName.GetLength()-1, 1);
	strFilter = szFilter;//GetFilterString(FilterVar);
	
	strSQL = "SELECT ";
	strSQL += strFieldName;
	strSQL += " FROM ";
	strSQL += szTableName;
	if (!strFilter.IsEmpty())
	{
		strSQL += " WHERE ";
		strSQL += strFilter;
	}
	if (szOrder!=NULL && strlen(szOrder)>0)
	{
		strSQL += " order by ";
		strSQL += szOrder;
	}
	
	miaoshu->PrepareSQL(strSQL.GetBuf());
	
	for (i=0; i<FieldNum; i++)
	{
		BindDBCol(miaoshu, RecVar.GetAt(i));	
	}
	miaoshu->Exec();
	
	Jint32 ret = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
	if (ret != DB_SUCCESS) 
	{
		char strErr[255];
		const char *szErr = miaoshu->GetErrorStr();
		sprintf(strErr, "%s:%s", szTableName, szErr);
		gCIILog_msdbcall.Add(strErr);
	}
	return ret;
}

// 读取多条记录
Jint32 CMSData::GetDBTableValue(Jchar* szTableName, Jchar* szFilter, CiESTableVariant &TabVar, Jchar* szOrder)
{
	CONNECTMSDB();
	CiESRecordVariant RecVar = TabVar.GetAt(0);
	TabVar.SetSize(0);
	if (GetDBTableValue(szTableName, szFilter, RecVar, szOrder)==DB_SUCCESS)
	{
		TabVar.AddLast(RecVar);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			TabVar.AddLast(RecVar);
		}
		return DB_SUCCESS;
	}
	return DB_NO_DATA_FOUND;	
}

Jint32 CMSData::SetDBTableValue(Jchar* szTableName, Jchar* szFilter, CiESRecordVariant& RecVar, Juint8 byOpType)
{
	CONNECTMSDB();
	Jint32	FieldNum=RecVar.GetSize();
	if (FieldNum<=0 && byOpType == 0) return DB_INVALID_PARAM;
	
	Jint32 i=0;
	CIIString	strFilter, strSQL;
	strFilter = szFilter;//GetFilterString(FilterVar);
	
	if (byOpType == 0)
	{
		if (strFilter.IsEmpty() || !IsRecordExist(miaoshu, szTableName, strFilter.GetBuf()))
		{
			strSQL = "INSERT INTO ";
			strSQL += szTableName;
			strSQL += " (";
			for (i=0; i<RecVar.GetSize(); i++)
			{
				strSQL += RecVar[i].m_strFieldName;
				strSQL += ",";
			}
			strSQL.ReplaceAt(strSQL.GetLength()-1, 1, ")");
			strSQL += " VALUES (";
			for (i=0; i<RecVar.GetSize(); i++)
			{
				strSQL += "?,";
			}
			strSQL.ReplaceAt(strSQL.GetLength()-1, 1, ")");
		}
		else
		{
			strSQL = "UPDATE ";
			strSQL += szTableName;
			strSQL += " SET ";
			for (i=0; i<RecVar.GetSize(); i++)
			{
				strSQL += RecVar[i].m_strFieldName;
				strSQL += "=?,";
			}
			strSQL.ReplaceAt(strSQL.GetLength()-1, 1, " ");
			if (!strFilter.IsEmpty()) {
				strSQL += " WHERE ";
				strSQL += strFilter;
			}
		}
		miaoshu->PrepareSQL(strSQL.GetBuf());
		
		for (i=0; i<FieldNum; i++)
		{
			BindDBCol(miaoshu, RecVar.GetAt(i), 0);	
		}
	}
	else if(byOpType == 1)	// 删除		
	{
		strSQL = "DELETE FROM ";
		strSQL += szTableName;
		if (!strFilter.IsEmpty()) {
			strSQL += " WHERE ";
			strSQL += strFilter;
		}
		miaoshu->PrepareSQL(strSQL.GetBuf());
	}
	
	Jint32 ret = miaoshu->Exec()>0 ? DB_SUCCESS : DB_ERROR;
	if (ret != DB_SUCCESS) 
	{
		char strErr[255];
		const char *szErr = miaoshu->GetErrorStr();
		sprintf(strErr, "%s:%s", szTableName, szErr);
		gCIILog_msdbcall.Add(strErr);
	}
	miaoshu->CloseSQL();
	return ret;
}
//EMS-Mend>