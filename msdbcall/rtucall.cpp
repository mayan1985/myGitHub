///////////////////////////////////////////////////////////////////////////////
#include "iessbmix.h"
#include "iescommon.h"
#include "dbdefine.h"
#include "msdbcall.h"
#include "dataid.h"// DMS-MEND baizy, 2008.10.25 12:56���ı�ǰ��������ֶνṹ

// ----------------------------------------------------------------------------
// ���ļ��ṩ����������RTU�ĸ��ֺ���������ͼ���˻��ӿڽ���ʹ��
// ----------------------------------------------------------------------------

//*****************************************************************************
// �����ǹ���ǰ��ͨ�ŵ����ݱ�Ķ�ȡ����д
//*****************************************************************************
//=============================================================================
// 1. ��ȡ���ݷ���������(ComDataServer)
// ��ڣ������������ݷ�����ID
// ���ڣ����������롢���ݷ���������
// Date: 2002.11.7
//=============================================================================
// ���ݱ���
const char* ComDataTableNames[RDT_Num] =
{ "", "ComByteData", "ComShortData", "ComIntData", "ComFloatData", "ComDoubleData" };


/////////////////////////////////////////////////////////////////
Jint32 CMSData::GetComDataServer(Juint8 byID, Jchar* cServerName)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ��ȡ���ݷ���������(ComDataServer)
// ��ڣ������������ݷ�����������Ϣָ��
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComDataServer(vector<TK_ComDataServer>* parComDataServer)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// �������ݷ���������
// ��ڣ������������ݷ�����ID�����ݷ���������
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComDataServer(Juint8 byID, Jchar* cServerName, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 2. ��ȡͨ�ŷ���������(ComServer)
// ��ڣ���������������������������
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComServer(Jchar* cComputerName, Juint8& byServerNumber)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ��ȡͨ�ŷ���������(ComServer)
// ��ڣ���������ͨ�ŷ�����������Ϣָ��
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComServer(vector<TK_ComServer>* parComServer)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ����ͨ�ŷ���������(ComServer)
// ��ڣ��������������������������š���������
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComServer(Jchar* cComputerName, Juint8 byServerNumber,
											Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 3. ��ȡ����ͨ���˿�������(ComSerial)[��������š����ڴ���ͨ����]
// ��ڣ�����������������š����ڴ���ͨ���š�����ͨ���˿���Ϣָ��
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComSerial(Juint8 byServerNumber,
					DATAID_TYPE bySerialChannelID, TK_ComSerial* pComSerial)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ��ȡ����ͨ���˿�������(ComSerial)[��������š����ڴ���ͨ����]
// ��ڣ�������������ͨ���˿�������Ϣָ��
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComSerial(vector<TK_ComSerial>* parComSerial)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ���ô���ͨ���˿�������(ComSerial)
// ��ڣ�����������������š����ڴ���ͨ���š�����ͨ���˿���Ϣָ�롢��������
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComSerial(Juint8 byServerNumber, DATAID_TYPE bySerialChannelID,
					TK_ComSerial* pComSerial, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 4. ��ȡ�ն�����(ComRTU)
// ��ڣ���������RTUID���ն�������Ϣָ��
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComRTU(DATAID_TYPE wRTUID, TK_ComRTU* pComRTU)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 4. ��ȡ�ն�����(ComRTU)
// ��ڣ����������ն�������Ϣָ��
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComRTU(vector<TK_ComRTU>* parComRTU)
{
	Jint32 retcode = DB_ERROR;

	CONNECTMSDB_2();
	if (!parComRTU)
		return DB_INVALID_PARAM;

	parComRTU->clear();
	return retcode;
}

//=============================================================================
// �����ն�����
// ��ڣ���������RTUID���ն�������Ϣָ�롢��������
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComRTU(DATAID_TYPE wRTUID, TK_ComRTU* pComRTU,
											Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ��ȡĳ����������RTU�����
//=============================================================================
Jint32 CMSData::GetComDataWhere(SMiaoShuParam* sParam, AComDataWhere* pADataWhere, Juint8 dataType, Juint8 rtuType)
{
	if (sParam == NULL || pADataWhere == NULL || dataType >= RDT_Num)
		return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString		sql;
	SComDataWhere	dataWhere;

	memset(&dataWhere, 0, sizeof(SComDataWhere));
	s_BJMS bjms;
	bjms.byBJType	= sParam->byBuJianLeiXingID;
	bjms.wBJID		= sParam->wBuJianID;
	bjms.byBJParam	= sParam->byBuJianCanShuID;
	bjms.wReserved	= 0;
	bjms.wCZID		= sParam->wChangZhanID;
	Juint8 dt = 0;
	for (dt = RDT_Byte; dt < RDT_Num; dt++)
	{
		if (dt == dataType || dataType == RDT_All)
		{
			if (rtuType == RTU_Receive)
			{
				if (dt == RDT_Byte)
					sql.Format( "SELECT a.wRTUID, a.Worder, b.byRTUType, b.strName  FROM %s a, ComRTU b "
					"WHERE a.bjlx=? and a.bjid =? and a.bjcs =? AND a.wRTUID=b.wRTUID AND b.byRTUType=0 AND b.byDataSourceNO=0 order by wobject1 desc",
					ComDataTableNames[dt]); 
				else
					sql.Format( "SELECT a.wRTUID, a.Worder, b.byRTUType, b.strName  FROM %s a, ComRTU b "
					"WHERE a.bjlx=? and a.bjid =? and a.bjcs =? AND a.wRTUID=b.wRTUID AND b.byRTUType=0 AND b.byDataSourceNO=0",
					ComDataTableNames[dt]);
				
			}
			else if (rtuType == RTU_Send)
			{
				sql.Format( "SELECT a.wRTUID, a.Worder, b.byRTUType, b.strName FROM %s a, ComRTU b "
					"WHERE a.bjlx=? and a.bjid =? and a.bjcs =? AND a.wRTUID=b.wRTUID AND b.byRTUType=1",
					ComDataTableNames[dt]);
			}
			else
			{
				sql.Format( "SELECT a.wRTUID, a.Worder, b.byRTUType, b.strName FROM %s a, ComRTU b "
					"WHERE a.bjlx=? and a.bjid =? and a.bjcs =? AND a.wRTUID=b.wRTUID",
					ComDataTableNames[dt]);
			}
			
			miaoshu->PrepareSQL(sql.GetBuf());
			miaoshu->BindCol(SQL_DATAID_TYPE,   0, &dataWhere.wRTUID);
			miaoshu->BindCol(IES_SQL_USMALLINT, 0, &dataWhere.wPoint);
			miaoshu->BindCol(IES_SQL_UTINYINT,  0, &dataWhere.byRTUType);
			miaoshu->BindCol(IES_SQL_STRING,    48, dataWhere.szRTUName);

			miaoshu->BindPara(IES_SQL_UTINYINT, 0, &bjms.byBJType);
			miaoshu->BindPara(SQL_DATAID_TYPE, 0, &bjms.wBJID);
			miaoshu->BindPara(IES_SQL_USMALLINT, 0, &bjms.byBJParam);
			miaoshu->Exec();
			while (miaoshu->Fetch() && !miaoshu->IsEnd())
			{

				pADataWhere->push_back(dataWhere);
			}
			if(pADataWhere->size() <= 0)
			{
				CIIString aa = miaoshu->GetErrorStr();
			}
		}
	}

	return pADataWhere->size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}



//=============================================================================
// 5. ��ȡ�ֽ�����˳���ComByteData��(ң���������ڴ�����)
// ��ڣ���������RTUID���������͡���š��ֽ�������ָ��
// ���ڣ����������롢�ֽ�������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComByteData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComByteData* pComByteData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// �����ֽ�����˳���
// ��ڣ���������RTUID���������͡���š��ֽ�������ָ�롢��������
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComByteData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
							TK_ComByteData* pComByteData, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 6. ��ȡ����������˳���ComShortData��
// ��ڣ���������RTUID���������͡���š�����������ָ��
// ���ڣ����������롢����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComShortData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComShortData* pComShortData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ���ö���������˳���
// ��ڣ���������RTUID���������͡���š�����������ָ�롢��������
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComShortData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
						TK_ComShortData* pComShortData, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 7. ��ȡ����������˳���ComIntData��
// ��ڣ���������RTUID���������͡���š�����������ָ��
// ���ڣ����������롢����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComIntData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComIntData* pComIntData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ���ó���������˳���
// ��ڣ���������RTUID���������͡���š�����������ָ�롢��������
// ���ڣ�����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComIntData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
						TK_ComIntData* pComIntData, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 8. ��ȡ����������˳���(ComFloatData)(ң�����ڴ�������)
// ��ڣ���������RTUID���������͡���š�����������ָ��
// ���ڣ����������롢����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComFloatData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComFloatData* pComFloatData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ���ø���������˳���
// ��ڣ���������RTUID���������͡���š�����������ָ�롢��������
// ���ڣ�����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComFloatData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
						TK_ComFloatData* pComFloatData, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 9. ��ȡ˫��������˳���(ComDoubleData)(�ܼ�ң���Լ���ȵ����ڴ�������)
// ��ڣ���������RTUID���������͡���š�˫��������ָ��
// ���ڣ����������롢˫��������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComDoubleData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComDoubleData* pComDoubleData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ����˫��������˳���
// ��ڣ���������RTUID���������͡���š�˫��������ָ�롢��������
// ���ڣ�����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComDoubleData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
						TK_ComDoubleData* pComDoubleData, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 10. ��ȡң�أ�ComYK��/ң��������
// ��ڣ���������RTUID���������͡�ң����š�ң��/ң������ָ��
// ���ڣ����������롢ң��/ң������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComYK(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComYK* pComYK)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ����ң�أ�ComYK��/ң��������
// ��ڣ���������RTUID���������͡�ң����š�ң��/ң������ָ�롢��������
// ���ڣ�����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComYK(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
							TK_ComYK* pComYK, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 11. ��ȡ΢������������(ComWJBH)
// ��ڣ���������RTUID����š�΢����������ָ��
// ���ڣ����������롢΢����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComWJBH(DATAID_TYPE wRTUID,
							Jint16 wOrder, TK_ComWJBH* pComWJBH)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ����΢������������
// ��ڣ���������RTUID����š�΢����������ָ�롢��������
// ���ڣ�����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComWJBH(DATAID_TYPE wRTUID, Jint16 wOrder,
							TK_ComWJBH* pComWJBH, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 12. ��ȡRTUͨ��������(ComRTUChParam)
// ��ڣ���������RTUID�����͡�RTUͨ����������ָ��
// ���ڣ����������롢RTUͨ����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComRTUChParam(DATAID_TYPE wRTUID, Juint8 byType,
							TK_ComRTUChParam* pComRTUChParam)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// ����RTUͨ��������
// ��ڣ���������RTUID�����͡�RTUͨ����������ָ�롢��������
// ���ڣ�����������
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComRTUChParam(DATAID_TYPE wRTUID, Juint8 byType,
						TK_ComRTUChParam* pComRTUChParam, Juint8 byOpType)	//0=����/�޸ģ�1=ɾ��
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 13. ��ȡ��Լ�ֵ��(ProtcolDes)
// ��ڣ���������ID����Լ�ֵ�����ָ��
// ���ڣ����������롢��Լ�ֵ�����
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetProtocolDes(Jint16 wID, TK_ProtocolDes* pProtocolDes)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

ComDataID CMSData::translateComDataID(Juint16 iNo, const char* pDataID)						//�ֽ�ת��
{

	ComDataID ret;
	//DMS-Mend<wugc 2008.10.22 19:28 ID����(2�ֽ�->4�ֽ�)
	unsigned short offset = 0;
	//��������
	memcpy(&ret.byBjType, pDataID+offset, sizeof(Juint8));
	offset += sizeof(Juint8);

	//����ID
	memcpy(&ret.nBjID, pDataID+offset, DATAID_SIZE);
	ret.nBjID = networktohost(ret.nBjID);
	offset += DATAID_SIZE;

	//��������
	memcpy(&ret.byCShType, pDataID+offset, sizeof(Juint8));
	offset += sizeof(Juint8);

	//Ԥ��
	offset += sizeof(unsigned short);

	//��վ
	memcpy(&ret.wCZID, pDataID+offset, DATAID_SIZE);
	ret.wCZID = networktohost(ret.wCZID);
	ret.wNo = iNo;

	//DMS-Mend>

	return ret;
}

Jint32 CMSData::GetComDataID(DATAID_TYPE wRTUID, Jchar* szTableName, vector<ComDataID>* parComData)
{
	char	  chDataID[8];
	CIIString strSQL;
	ComDataID aDataID;
	Juint16   wNo;

	CONNECTMSDB();
	s_BJMS bjms;
	strSQL = "SELECT WORDER, bjlx,bjid,bjcs,changzhanid FROM ";
	strSQL += szTableName;
	strSQL += " WHERE WRTUID=? ORDER BY WORDER";

	miaoshu->PrepareSQL(strSQL.GetBuf());

	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &wNo);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &bjms.byBJType);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &bjms.wBJID);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &bjms.byBJParam);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &bjms.wCZID);
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wRTUID);
	if (!miaoshu->Exec())
	{
		CIIString tError = miaoshu->GetErrorStr();
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

	int nIndex = 0;
	while (miaoshu->Fetch()  && !miaoshu->IsEnd())
	{
		nIndex++;
		aDataID.byBjType	= bjms.byBJType;
		aDataID.nBjID		= bjms.wBJID;
		aDataID.byCShType	= bjms.byBJParam;
		aDataID.wCZID		= bjms.wCZID;
		aDataID.wNo			= wNo;
		if(aDataID.byBjType > 0 && aDataID.nBjID > 0 && aDataID.byCShType > 0)
			parComData->push_back(aDataID);
		memset(chDataID, 0, 8*sizeof(char));
	}
	if(nIndex == 0)
	{
		CIIString tError = miaoshu->GetErrorStr();
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

	return DB_SUCCESS;
}

