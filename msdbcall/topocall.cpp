///////////////////////////////////////////////////////////////////////////////
#include "iessbmix.h"
#include "dbdefine.h"
#include "msdbcall.h"
#include "topodefext.h"

#include "table_info_ms.h"


#include "pnetcall.cpp"

// ----------------------------------------------------------------------------
// ���ļ��ṩ�������������˵ĸ��ֺ���������ͼ���˻��ӿڽ���ʹ��
// ----------------------------------------------------------------------------

//*****************************************************************************
// ����Ϊ��ͼ��⡢��̬��ɫר�ú���
//*****************************************************************************

//=============================================================================
// ��ȡ΢��������
// ��ڣ�����������������š����˵�Ԫ�ĵ�ַ
// ���ڣ����������롢���˵�Ԫ��Ϣ
// Date: 2002.10.29
//=============================================================================
Jint32 CMSData::GetTopo(Jint16 wFieldID, TopoUnit* pTopoUnit)
{
	CHECKPARAM(wFieldID, pTopoUnit, aDWTopo_Table[0], TopoUnitOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("FieldTypeID=%d", wFieldID);

	return GetDBValue(miaoshu, &aDWTopo_Table[0], filter.GetBuf(), (Juint8*)pTopoUnit, TopoUnitOffset);
}

//=============================================================================
// ��ȡ����΢������˿�
// ��ڣ���վid
// ���ڣ����������롢����΢������˿�
// Date: 2007.03.20
//=============================================================================
// DMS-MEND< ningfg, 2008.10.15 11:19
// �޸�ԭ��ȡ����ID�ӿ�������Ҫ�˿ڸ��������ؿ��ö˿��б�
Jint32	CMSData:: GetTopoPortId(DATAID_TYPE wStationID, vector<Juint32>&aPort,	Juint8 wPortNum)
{
	CONNECTMSDB_2();

	int control = 0;
	Juint32 pnodeid = 0;
	char strSQL[128];
	vector<Juint32> vTmp;

	sprintf(strSQL,"select pnodeid from DWTOPOPORT where CHANGZHANID=%d order by pnodeid",wStationID);
	miaoshu->PrepareSQL(strSQL);
	miaoshu->BindCol(IES_SQL_UINT,0,&pnodeid);
	control = miaoshu->Exec();
	if(control == -1) return DB_ERROR;
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		vTmp.push_back(pnodeid);
	}
	miaoshu->CloseSQL();

	Juint32 num;
	for(num = 1; num<100000; num++)
	{
		Juint32 i;
		for(i = 0; i<vTmp.size(); i++)
		{
			if(num == (vTmp[i]/100000))			//�ö˿ں��ѱ�ʹ��
				break;
		}
		if(i == vTmp.size())
		{
			if(aPort.size() == wPortNum)		//�ѻ�ȡwPortNum��δ�ö˿ں�
				return DB_SUCCESS;
			else
				aPort.push_back(num);
		}
	}

	if(num == 100000)
		return DB_NO_DATA_FOUND;
}
// DMS-MEND>


//=============================================================================
// ����΢��������
// ��ڣ������������������˵�Ԫ��Ϣָ�롢��������
// ���ڣ�����������
// Date: 2002.10.29
//=============================================================================

Jint32 CMSData::SetTopo(Jint16 wFieldID, TopoUnit* pTopoUnit, 
						Juint8 byOpType)					//0=����/�޸ģ�1=ɾ��  						
{
	CHECKSETPARAM(wFieldID, pTopoUnit, aDWTopo_Table[0], TopoUnitOffset, byOpType);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("FieldTypeID=%d", wFieldID);

	return OpereDBParam(miaoshu, &aDWTopo_Table[0], (Juint8*)pTopoUnit, TopoUnitOffset, filter.GetBuf(), byOpType);
}

//=============================================================================
// ��ȡ΢���˲�������
// ��ڣ�����������������š����˲��������ַ
// ���ڣ����������롢���˲�������
// Date: 2002.10.29
//=============================================================================

Jint32 CMSData::GetTopoBuJian(Jint16 wFieldTypeID, vector<TopoBuJian>* parTopoBuJian)
{//����������ȡ����������в���
	CHECKPARAM(wFieldTypeID, parTopoBuJian, aDWTopo_Table[1], TopoBuJianOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("FieldTypeID=%d", wFieldTypeID);
	char* order = "FieldTypeID,RecID";
	TopoBuJian tmpTopoBuJian;
	
	parTopoBuJian->clear();
	if (GetDBValue(miaoshu, &aDWTopo_Table[1], filter.GetBuf(), (Juint8*)&tmpTopoBuJian, TopoBuJianOffset, order)==DB_SUCCESS)
	{
		parTopoBuJian->push_back(tmpTopoBuJian);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parTopoBuJian->push_back(tmpTopoBuJian);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ����΢���˲�������
// ��ڣ������������������͡����˲��������ַ
// ���ڣ�����������
// Date: 2002.10.29
//=============================================================================
Jint32 CMSData::SetTopoBuJian(Jint16 wFieldTypeID, vector<TopoBuJian>* parTopoBuJian, 
					  Juint8 byOpType)				//0=����/�޸ģ�1=ɾ��
{//������ڸ������ͣ����޸ĸü�¼���������ӡ�
	
	CHECKSETPARAM(wFieldTypeID, parTopoBuJian, aDWTopo_Table[1], TopoBuJianOffset, byOpType);
	CONNECTMSDB_2();

	Jint32	retcode = DB_ERROR;
	TopoBuJian tmpTopoBuJian;

	CIIString filter;
	if (byOpType==1) 
	{
		filter.Format("FieldTypeID=%d", wFieldTypeID);
		retcode = OpereDBParam(miaoshu, &aDWTopo_Table[1], (Juint8*)(&tmpTopoBuJian), TopoBuJianOffset, filter.GetBuf(), byOpType);
	}	
	else if (byOpType==0)
	{
		for (Jint16 i=1; i<=parTopoBuJian->size(); i++)
		{
			tmpTopoBuJian = (*parTopoBuJian)[i-1];
			tmpTopoBuJian.wFieldTypeID = wFieldTypeID;
			tmpTopoBuJian.byRecID = i;
			filter.Format("FieldTypeID=%d AND RecID=%d", wFieldTypeID, i);			
			retcode = OpereDBParam(miaoshu, &aDWTopo_Table[1], (Juint8*)(&tmpTopoBuJian), TopoBuJianOffset, filter.GetBuf(), byOpType);
		}
	}

	return retcode;
}

//=============================================================================
// ��ȡ΢���˶˿ڶ���
// ��ڣ�����������������š����˶˿������ַ
// ���ڣ����������롢���˶˿�����
// Date: 2002.10.29
//=============================================================================
Jint32 CMSData::GetTopoPort(Jint16 wFieldTypeID, vector<TopoPort>* parTopoPort)
{//����������ȡ����������ж˿�

	CHECKPARAM(wFieldTypeID, parTopoPort, aDWTopo_Table[2], TopoPortOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("FieldTypeID=%d", wFieldTypeID);
	char* order = "FieldTypeID,RecID";
	TopoPort tmpTopoPort;
	
	parTopoPort->clear();
	if (GetDBValue(miaoshu, &aDWTopo_Table[2], filter.GetBuf(), (Juint8*)(&tmpTopoPort), TopoPortOffset, order)==DB_SUCCESS)
	{
		parTopoPort->push_back(tmpTopoPort);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parTopoPort->push_back(tmpTopoPort);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ����΢���˶˿ڶ���
// ��ڣ���������������������š����˶˿������ַ���������ʹ���
// ���ڣ�����������
// Date: 2002.10.29
//=============================================================================

Jint32 CMSData::SetTopoPort(Jint16 wFieldTypeID, vector<TopoPort>* parTopoPort, 
					  Juint8 byOpType)				//0=����/�޸ģ�1=ɾ��
{//������ڸ������ͣ����޸ĸü�¼����������.
	
	CHECKSETPARAM(wFieldTypeID, parTopoPort, aDWTopo_Table[2], TopoPortOffset, byOpType);
	CONNECTMSDB_2();

	Jint32	retcode = DB_ERROR;
	TopoPort tmpTopoPort;

	CIIString filter;
	if (byOpType==1) 
	{
		filter.Format("FieldTypeID=%d", wFieldTypeID);
		retcode = OpereDBParam(miaoshu, &aDWTopo_Table[2], (Juint8*)(&tmpTopoPort), TopoPortOffset, filter.GetBuf(), byOpType);
	}	
	else if (byOpType==0)
	{
		for (Jint16 i=1; i<=parTopoPort->size(); i++)
		{
			tmpTopoPort = (*parTopoPort)[i-1];
			tmpTopoPort.wFieldTypeID = wFieldTypeID;
			tmpTopoPort.byRecID = i;
			filter.Format("FieldTypeID=%d AND RecID=%d", wFieldTypeID, i);
			retcode = OpereDBParam(miaoshu, &aDWTopo_Table[2], (Juint8*)(&tmpTopoPort), TopoPortOffset, filter.GetBuf(), byOpType);
		}
	}

	return retcode;
}

//=============================================================================
// ��ȡ΢�������߶���
// ��ڣ���������������������š�������������ָ��
// ���ڣ����������롢��д������������ָ��
// Date: 2002.10.30
//=============================================================================

Jint32 CMSData::GetTopoLine(Jint16 wFieldTypeID, vector<TopoLine>* parTopoLine)
{//����������ȡ����������в���

	CHECKPARAM(wFieldTypeID, parTopoLine, aDWTopo_Table[3], TopoLineOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("FieldTypeID=%d", wFieldTypeID);
	char* order = "FieldTypeID,RecID";
	TopoLine tmpTopoLine;
	
	parTopoLine->clear();
	if (GetDBValue(miaoshu, &aDWTopo_Table[3], filter.GetBuf(), (Juint8*)&tmpTopoLine, TopoLineOffset, order)==DB_SUCCESS)
	{
		parTopoLine->push_back(tmpTopoLine);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parTopoLine->push_back(tmpTopoLine);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ����΢�������߶���
// ��ڣ���������������������š�������������ָ�롢�������ʹ���
// ���ڣ�����������
// Date: 2002.10.30
//=============================================================================
Jint32 CMSData::SetTopoLine(Jint16 wFieldTypeID, vector<TopoLine>* parTopoLine, 
						Juint8 byOpType)				//0=����/�޸ģ�1=ɾ��
{//������ڸ������ͣ����޸ĸü�¼����������.

	CHECKSETPARAM(wFieldTypeID, parTopoLine, aDWTopo_Table[3], TopoLineOffset, byOpType);
	CONNECTMSDB_2();

	Jint32	retcode = DB_ERROR;
	TopoLine tmpTopoLine;

	CIIString filter;
	if (byOpType==1) 
	{
		filter.Format("FieldTypeID=%d", wFieldTypeID);
		retcode = OpereDBParam(miaoshu, &aDWTopo_Table[3], (Juint8*)&tmpTopoLine, TopoLineOffset, filter.GetBuf(), byOpType);
	}	
	else if (byOpType==0)
	{
		for (Jint16 i=1; i<=parTopoLine->size(); i++)
		{
			tmpTopoLine = (*parTopoLine)[i-1];
			tmpTopoLine.wFieldTypeID = wFieldTypeID;
			tmpTopoLine.byRecID = i;
			filter.Format("FieldTypeID=%d AND RecID=%d", wFieldTypeID, i);
			retcode = OpereDBParam(miaoshu, &aDWTopo_Table[3], (Juint8*)&tmpTopoLine, TopoLineOffset, filter.GetBuf(), byOpType);
		}
	}

	return retcode;
}

//=============================================================================
// ��ȡ΢���˴����ѯ����
// ��ڣ���������������������š����˴�������ָ��
// ���ڣ����������롢���˴�����Ϣ
// Date: 2002.10.30
//=============================================================================

Jint32 CMSData::GetTopoEQuery(Jint16 wFieldTypeID, vector<TopoEQuery>* parTopoEQuery)
{

	CHECKPARAM(wFieldTypeID, parTopoEQuery, aDWTopo_Table[4], TopoEQueryOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("FieldTypeID=%d", wFieldTypeID);
	char* order = "FieldTypeID,RecID";
	TopoEQuery tmpTopoEQuery;
	
	parTopoEQuery->clear();
	if (GetDBValue(miaoshu, &aDWTopo_Table[4], filter.GetBuf(), (Juint8*)&tmpTopoEQuery, TopoEQueryOffset, order)==DB_SUCCESS)
	{
		parTopoEQuery->push_back(tmpTopoEQuery);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parTopoEQuery->push_back(tmpTopoEQuery);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ����΢���˴����ѯ����
// ��ڣ���������������������š����˴�������ָ�롢�������ʹ���
// ���ڣ�����������
// Date: 2002.10.30
//=============================================================================

Jint32 CMSData::SetTopoEQuery(Jint16 wFieldTypeID, vector<TopoEQuery>* parTopoEQuery,
					  Juint8 byOpType)				//0=����/�޸ģ�1=ɾ��
{//������ڸ������ͣ����޸ĸü�¼����������.

	CHECKSETPARAM(wFieldTypeID, parTopoEQuery, aDWTopo_Table[4], TopoEQueryOffset, byOpType);
	CONNECTMSDB_2();

	Jint32	retcode = DB_ERROR;
	TopoEQuery tmpTopoEQuery;
	Jint32 tsize=0;

	CIIString filter;
	if (byOpType==1) 
	{
		filter.Format("FieldTypeID=%d", wFieldTypeID);
		retcode = OpereDBParam(miaoshu, &aDWTopo_Table[4], (Juint8*)&tmpTopoEQuery, TopoEQueryOffset, filter.GetBuf(), byOpType);
	}	
	else if (byOpType==0)
	{
		tsize = parTopoEQuery->size();
		//for (Jint16 i=1; i<=tsize; i++) // baizy refer to linfen, 2008.4.10
		for (Jint32 i=1; i<=tsize; i++)
		{
			tmpTopoEQuery = (*parTopoEQuery)[i-1];
			tmpTopoEQuery.wFieldTypeID = wFieldTypeID;
			tmpTopoEQuery.byRecID = i;
			filter.Format("FieldTypeID=%d AND RecID=%d", wFieldTypeID, i);
			retcode = OpereDBParam(miaoshu, &aDWTopo_Table[4], (Juint8*)&tmpTopoEQuery, TopoEQueryOffset, filter.GetBuf(), byOpType);
		}
	}

	return retcode;
}

//=============================================================================
// ��ȡ΢����Ԥ�����Ŷ���
// ��ڣ���������������������š�Ҫд�������Ԥ������Ϣָ��
// ���ڣ����������롢����Ԥ������Ϣ
// Date: 2002.10.30
//=============================================================================
Jint32 CMSData::GetTopoPreDeal(Jint16 wFieldTypeID, TopoPreDeal* pTopoPreDeal)
{
	CHECKPARAM(wFieldTypeID, pTopoPreDeal, aDWTopo_Table[5], TopoPreDealOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("FieldTypeID=%d", wFieldTypeID);
	
	return GetDBValue(miaoshu, &aDWTopo_Table[5], filter.GetBuf(), (Juint8*)pTopoPreDeal, TopoPreDealOffset);
}

//=============================================================================
// ����΢����Ԥ�����Ŷ���
// ��ڣ���������������������š�����Ԥ����ָ�롢�������ʹ���
// ���ڣ�����������
// Date: 2002.10.30
//=============================================================================

Jint32 CMSData::SetTopoPreDeal(Jint16 wFieldTypeID, TopoPreDeal* pTopoPreDeal, 
						Juint8 byOpType)			//0=����/�޸ģ�1=ɾ��
{//������ڸ������ͣ����޸ĸü�¼����������.

	CHECKSETPARAM(wFieldTypeID, pTopoPreDeal, aDWTopo_Table[5], TopoPreDealOffset, byOpType);
	CONNECTMSDB_2();


	CIIString filter;
	filter.Format("FieldTypeID=%d", wFieldTypeID);

	return OpereDBParam(miaoshu, &aDWTopo_Table[5], (Juint8*)pTopoPreDeal, TopoPreDealOffset, filter.GetBuf(), byOpType);
}

//=============================================================================
// ��ȡ���ء���բ����ѹ������������Ϣ
// ��ڣ�������������ID
// ���ڣ����������롢�����͡�վ������š�����Ԫ�����
// Date: 2002.10.30
//=============================================================================
Jint32 CMSData::GetTopoKGDZBYQ(Juint8 bybjlx, DATAID_TYPE wbjID, Jint16& wFieldType, Jint16& wStaFieldID, DATAID_TYPE& wComponentID)
{
	if (wbjID<1)		return DB_INVALID_PARAM;
	if (bybjlx != KaiGuan_ID && bybjlx != DaoZha_ID && bybjlx != BianYaQi_ID && bybjlx != DMSTransformer_ID && bybjlx != DMSFeederSection_ID )	{
		wFieldType = 0;
		return DB_INVALID_PARAM;
	}
	CONNECTMSDB_2();

	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(bybjlx);
	sql.Format("SELECT FieldType, StaFieldID, ComponentID FROM %s WHERE ID=%d", strBiaoMing.GetBuf(), wbjID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_SMALLINT, 0, &wFieldType);
	miaoshu->BindCol(IES_SQL_SMALLINT, 0, &wStaFieldID);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wComponentID);
	miaoshu->Exec();
	if (miaoshu->Fetch() && !miaoshu->IsEnd())	return DB_SUCCESS;

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ���ÿ��ء���բ����ѹ������������Ϣ
// ��ڣ�������������ID�������͡�վ������š�����Ԫ�����
// ���ڣ�����������
// Date: 2002.10.30
//=============================================================================

Jint32 CMSData::SetTopoKGDZBYQ(Juint8 bybjlx, DATAID_TYPE wbjID, Jint16 wFieldType, Jint16 wStaFieldID, DATAID_TYPE wComponentID)
{
	if (wbjID<1)		return DB_INVALID_PARAM;
	if (bybjlx != KaiGuan_ID && bybjlx != DaoZha_ID && bybjlx != BianYaQi_ID && bybjlx != DMSTransformer_ID && bybjlx != DMSFeederSection_ID)

	{
		wFieldType = 0;
		return DB_INVALID_PARAM;
	}
	CONNECTMSDB_2();

	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(bybjlx);
	sql.Format("update %s set FieldType=?, StaFieldID=?, ComponentID=? WHERE ID=%d", strBiaoMing.GetBuf(), wbjID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_SMALLINT, 0, &wFieldType);
	miaoshu->BindCol(IES_SQL_SMALLINT, 0, &wStaFieldID);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wComponentID);

	Jint32 ret = miaoshu->Exec()>0 ? DB_SUCCESS : DB_ERROR;
	miaoshu->CloseSQL();
	return ret;
}

//=============================================================================
// ��ȡ������������Ϣ
// ��ڣ�����������վID��վ������š��������˵�Ԫָ��
// ���ڣ����������롢�������˵�Ԫ��Ϣ
// Date: 2002.10.30
//=============================================================================

Jint32 CMSData::GetDWTopo(DATAID_TYPE wStationID, Jint16 wStaFieldID, DWTopoUnit* pDWTopoUnit)
{
	CHECKPARAM(wStationID, pDWTopoUnit, aDWTopo_Table[6], DWTopoUnitOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("ChangZhanID=%d AND FieldID=%d", wStationID, wStaFieldID);

	return GetDBValue(miaoshu, &aDWTopo_Table[6], filter.GetBuf(), (Juint8*)pDWTopoUnit, DWTopoUnitOffset);
}

//=============================================================================
// ���ݳ�վ�Ż�ȡȫվ������������Ϣ
// ��ڣ�����������վID���������˵�Ԫ����ָ��
// ���ڣ����������롢�������˵�Ԫ������Ϣ
// Date: 2002.10.30
//=============================================================================

Jint32 CMSData::GetDWTopo(DATAID_TYPE wStationID, vector<DWTopoUnit>* parDWTopoUnit)
{
	CHECKPARAM(wStationID, parDWTopoUnit, aDWTopo_Table[6], DWTopoUnitOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("ChangZhanID=%d", wStationID);

	char* order = "FieldTypeID";
	DWTopoUnit tmpDWTopoUnit;
	
	parDWTopoUnit->clear();
	if (GetDBValue(miaoshu, &aDWTopo_Table[6], filter.GetBuf(), (Juint8*)&tmpDWTopoUnit, DWTopoUnitOffset, order)==DB_SUCCESS)
	{
		parDWTopoUnit->push_back(tmpDWTopoUnit);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parDWTopoUnit->push_back(tmpDWTopoUnit);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ���õ�����������Ϣ
// ��ڣ�����������վID��վ������š��������˵�Ԫ��Ϣָ�롢��������
// ���ڣ�����������
// Date: 2002.10.30
//=============================================================================
Jint32 CMSData::SetDWTopo(DATAID_TYPE wStationID, Jint16 wStaFieldID, DWTopoUnit* pDWTopoUnit, 
					 Juint8 byOpType)					//0=����/�޸ģ�1=ɾ��
{//������ڸ��򣬾��޸ĸü�¼����������.
	CHECKSETPARAM(wStationID, pDWTopoUnit, aDWTopo_Table[6], DWTopoUnitOffset, byOpType);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("ChangZhanID=%d AND FieldID=%d", wStationID, wStaFieldID);

	return OpereDBParam(miaoshu, &aDWTopo_Table[6], (Juint8*)pDWTopoUnit, DWTopoUnitOffset, filter.GetBuf(), byOpType);
}

//=============================================================================
// ��ȡ����΢���˲�����Ϣ
// ��ڣ�����������վID��վ������š��������˲�������ָ��
// ���ڣ����������롢�������˲�����Ϣ
// Date: 2002.10.30
//=============================================================================

Jint32 CMSData::GetDWTopoBuJian(DATAID_TYPE wStationID, Jint16 wStaFieldID, vector<DWTopoBuJian>* parDWTopoBuJian)
{
	CHECKPARAM(wStationID, parDWTopoBuJian, aDWTopo_Table[7], DWTopoBuJianOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("ChangZhanID=%d AND FieldID=%d", wStationID, wStaFieldID);
	Jchar* order = "ChangZhanID,FieldID,RecID";
	DWTopoBuJian tmpDWTopoBuJian;
	
	parDWTopoBuJian->clear();
	if (GetDBValue(miaoshu, &aDWTopo_Table[7], filter.GetBuf(), (Juint8*)&tmpDWTopoBuJian, DWTopoBuJianOffset, order)==DB_SUCCESS)
	{
		parDWTopoBuJian->push_back(tmpDWTopoBuJian);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parDWTopoBuJian->push_back(tmpDWTopoBuJian);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ���ݲ������͡���վ�ͱ�ŴӲ������л��ID, Ȼ��ȡ����Ӧ�ĵ������˲�������Ϣ
// ��ڣ����������������͡���վ��������š��������˲���ָ��
// ���ڣ����������롢�������˲�����Ϣ
// Date: 2002.10.30
//=============================================================================
Jint32 CMSData::GetDWTopoBuJian(Juint8 bybjlx, DATAID_TYPE wStationID, char* pcBJBH, DWTopoBuJian* pDWTopoBuJian, Jboolean isUseBH)
{
	CHECKPARAM(wStationID, pDWTopoBuJian, aDWTopo_Table[7], DWTopoBuJianOffset);
	if (!pcBJBH || (bybjlx < 4 && bybjlx > 24))		return DB_INVALID_PARAM;
	CONNECTMSDB_2();

	DATAID_TYPE wBJID=0;
	CIIString sql, filter;
	CIIString strBiaoMing = GetBiaoMing(bybjlx);
	if (bybjlx == XianLu_ID)
		filter.Format("BianHao='%s'", pcBJBH);
// DMS-MEND< zhangjq, 2010.3.13 16:18
// �޸�ԭ����Ա�Ż����ֱַ��ѯ
	else if(isUseBH)
		filter.Format("ChangZhanID=%d AND BianHao='%s'", wStationID, pcBJBH);
	else
		filter.Format("ChangZhanID=%d AND MingZi='%s'", wStationID, pcBJBH);

// DMS-MEND>
	sql.Format("SELECT ID FROM %s WHERE %s",strBiaoMing.GetBuf(), filter.GetBuf());
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wBJID);
	miaoshu->Exec();
	if (!miaoshu->Fetch() || miaoshu->IsEnd())	return DB_NO_DATA_FOUND;

	filter.Format("ComponentType=%d AND ComponentID=%d", bybjlx, wBJID);

	return GetDBValue(miaoshu, &aDWTopo_Table[7], filter.GetBuf(), (Juint8*)pDWTopoBuJian, DWTopoBuJianOffset);
}
//=============================================================================
// ���ݳ�վ�ź�վ������ŵõ����еĲ���(���ء���բ�Ϳ�������Ӧ��CT)
// ��ڣ�����������վ��վ������š���������ָ�롢��բ����ָ�롢CT����ָ��
// ���ڣ����������롢���ء���բ�Ϳ�������Ӧ��CT����
// Date: 2002.10.31
//=============================================================================
//EMS->Mend< ningfg 2008.10.7
//�޸�ԭ��ȡ���߶κ�����ѹ����Ϣ
Jint32 CMSData::GetDWTopoBuJian(vector<DWTopoBuJian>* parDWTopoBuJian,
								vector<TK_MuXian>* parMuXian,
								vector<TK_PT>* parPT,
								vector<TK_XianLu>* parXianLu,
								vector<TK_KaiGuan>* parKaiGuan,
								vector<TK_CT>* parCT,
								vector<TK_DaoZha>* parDaoZha,
								vector<TK_BianYaQi>* parBianYaQi,
								vector<TK_FaDianJi>* parFaDianJi,
								vector<TK_FuHe>* parFuHe,
								vector<TK_ZhuRu>* parZhuRu,
								vector<TK_BingLianDianRong>* parBLDR,
								vector<TK_ChuanLianDianKang>* parCLDK,
								vector<TK_KuiXianDuan>* parKuiXianDuan,
								vector<TK_PBBianYaQi>* parPBBianYaQi)
{
	if (parDWTopoBuJian==NULL)	return DB_INVALID_PARAM;

	for (Jint16 i=0; i<parDWTopoBuJian->size(); i++)
	{
		if ((*parDWTopoBuJian)[i].byComponentType == KaiGuan_ID)
		{//����
			if (parKaiGuan)
			{
				TK_KaiGuan tmpKaiGuan;
				GetKaiGuan((*parDWTopoBuJian)[i].wComponentID, &tmpKaiGuan);
				parKaiGuan->push_back(tmpKaiGuan);
				if (parCT)
				{
					TK_CT tmpCT;
					GetCT(tmpKaiGuan.wCTID, &tmpCT);
					parCT->push_back(tmpCT);
				}
			}
		}
		else if((*parDWTopoBuJian)[i].byComponentType == DaoZha_ID)
		{//��բ
			if (parDaoZha)
			{
				TK_DaoZha tmpDaoZha;
				GetDaoZha((*parDWTopoBuJian)[i].wComponentID, &tmpDaoZha);
				parDaoZha->push_back(tmpDaoZha);
			}
		}
		else if ((*parDWTopoBuJian)[i].byComponentType == MuXian_ID)
		{//ĸ��
			if (parMuXian)
			{
				TK_MuXian tmpMuXian;
				GetMuXian((*parDWTopoBuJian)[i].wComponentID, &tmpMuXian);
				parMuXian->push_back(tmpMuXian);
				if (parPT)
				{
					TK_PT tmpPT;
					GetPT(tmpMuXian.wDYPTID, &tmpPT);
					parPT->push_back(tmpPT);
				}
			}
		}
		else if ((*parDWTopoBuJian)[i].byComponentType == XianLu_ID)
		{//��·
			if (parXianLu)
			{
				TK_XianLu tmpXianLu;
				GetXianLu((*parDWTopoBuJian)[i].wComponentID, &tmpXianLu);
				parXianLu->push_back(tmpXianLu);
			}
		}
		else if ((*parDWTopoBuJian)[i].byComponentType == BianYaQi_ID)
		{//��ѹ��
			if (parBianYaQi)
			{
				TK_BianYaQi tmpBianYaQi;
				GetBianYaQi((*parDWTopoBuJian)[i].wComponentID, &tmpBianYaQi);
				parBianYaQi->push_back(tmpBianYaQi);
			}
		}
		else if ((*parDWTopoBuJian)[i].byComponentType == FaDianJi_ID)
		{//�����
			if (parFaDianJi)
			{
				TK_FaDianJi tmpFaDianJi;
				GetFaDianJi((*parDWTopoBuJian)[i].wComponentID, &tmpFaDianJi);
				parFaDianJi->push_back(tmpFaDianJi);
			}
		}
		else if ((*parDWTopoBuJian)[i].byComponentType == FuHe_ID)
		{//����
			if (parFuHe)
			{
				TK_FuHe tmpFuHe;
				GetFuHe((*parDWTopoBuJian)[i].wComponentID, &tmpFuHe);
				parFuHe->push_back(tmpFuHe);
			}
		}
		else if ((*parDWTopoBuJian)[i].byComponentType == ZhuRu_ID)
		{//ע��
			if (parZhuRu)
			{
				TK_ZhuRu tmpZhuRu;
				GetZhuRu((*parDWTopoBuJian)[i].wComponentID, &tmpZhuRu);
				parZhuRu->push_back(tmpZhuRu);
			}
		}
		else if ((*parDWTopoBuJian)[i].byComponentType == BingLianDianRong_ID)
		{//��������
			if (parBLDR)
			{
				TK_BingLianDianRong tmpBLDR;
				GetBingLianDianRong((*parDWTopoBuJian)[i].wComponentID, &tmpBLDR);
				parBLDR->push_back(tmpBLDR);
			}
		}
		else if ((*parDWTopoBuJian)[i].byComponentType == ChuanLianDianKang_ID)
		{//�����翹
			if (parCLDK)
			{
				TK_ChuanLianDianKang tmpCLDK;
				GetChuanLianDianKang((*parDWTopoBuJian)[i].wComponentID, &tmpCLDK);
				parCLDK->push_back(tmpCLDK);
			}
		}
		else if((*parDWTopoBuJian)[i].byComponentType == DMSFeederSection_ID)
		{
			if (parKuiXianDuan)
			{
				TK_KuiXianDuan tmpKuiXianDuan;
				GetKuiXianDuan((*parDWTopoBuJian)[i].wComponentID, &tmpKuiXianDuan);
				parKuiXianDuan->push_back(tmpKuiXianDuan);
			}
		}
		else if((*parDWTopoBuJian)[i].byComponentType == DMSTransformer_ID)
		{
			if (parPBBianYaQi)
			{
				TK_PBBianYaQi tmpPBBianYaQi;
				GetPBBianYaQi((*parDWTopoBuJian)[i].wComponentID, &tmpPBBianYaQi);
				parPBBianYaQi->push_back(tmpPBBianYaQi);
			}
		}
	}

	return DB_SUCCESS;
}

// DMS-MEND< zhangjq, 2009.12.7 15:41
// �޸�ԭ��ԭ�к�����ѯ�ٶȽ�������д�º���
Jint32 CMSData::GetDWTopoBuJian(DATAID_TYPE changzhanID, Jint16 fieldTypeID, Juint8 bjlx,
					   vector<TK_MuXian>* parMuXian,
					   vector<TK_PT>* parPT,
					   vector<TK_XianLu>* parXianLu,
					   vector<TK_KaiGuan>* parKaiGuan,
					   vector<TK_CT>* parCT,
					   vector<TK_DaoZha>* parDaoZha,
					   vector<TK_BianYaQi>* parBianYaQi,
					   vector<TK_FaDianJi>* parFaDianJi,
					   vector<TK_FuHe>* parFuHe,
					   vector<TK_ZhuRu>* parZhuRu,
					   vector<TK_BingLianDianRong>* parBLDR,
					   vector<TK_ChuanLianDianKang>* parCLDK,
					   vector<TK_KuiXianDuan>* parKuiXianDuan,
					   vector<TK_PBBianYaQi>* parPBBianYaQi)
{
	bool testbl;
	CIIOdbcDBI* miaoshu=GetDatabase(false); 
	if (miaoshu==NULL || !miaoshu->IsOpen()) 
		return 0;

	CIIString tempStr;
	tempStr.Format("dwtopobujian a where a.ComponentID=b.id and a.ComponentNo=1 and a.ChangZhanID=%d and a.FieldTypeID=%d and a.ComponentType=%d",changzhanID,fieldTypeID,bjlx);

	STblInfo* selTable = NULL;
	Juint8* pTmp;
	Juint16* offSet;
	TK_PBBianYaQi tmpPB;
	TK_KuiXianDuan tmpKXD;
	TK_KaiGuan tmpKG;
	TK_DaoZha tmpDZ;

	switch (bjlx)
	{
	case KaiGuan_ID:
		selTable = &aDWBuJian_Table[5];
		pTmp = (Juint8*)&(tmpKG);
		offSet = Offset_TK_KaiGuan;
		break;
	case DaoZha_ID:
		selTable = &aDWBuJian_Table[6];
		pTmp = (Juint8*)&(tmpDZ);
		offSet = Offset_TK_DaoZha;
		break;
	case DMSFeederSection_ID:
		selTable = &aDWBuJian_Table[23];
		pTmp = (Juint8*)&(tmpKXD);
		offSet = Offset_TK_KuiXianDuan;
		break;
	case DMSTransformer_ID:
		selTable = &aDWBuJian_Table[22];
		pTmp = (Juint8*)&(tmpPB);
		offSet = Offset_TK_PBBianYaQi;
		break;
	default:
		break;
	}

	if (NULL == selTable)
	{
		return 0;
	}

	CIIString sql;
	if (NULL != selTable)
	{
		sql = "SELECT ";
		for (Jint16 i =0; i<selTable->nColCount; i++)
		{
			sql += "b.";
			sql += selTable->pColInfo[i].szColName;
			sql += ",";
		}
		sql[sql.GetLength() -1] = ' ';
		sql += "FROM ";
		sql += selTable->szTableName;
		sql += " b,";
		sql += tempStr;
		bool t = miaoshu->PrepareSQL(sql.GetBuf());


		for (Jint16 i=0; i<selTable->nColCount; i++)
			testbl = miaoshu->BindCol(selTable->pColInfo[i].nColType, selTable->pColInfo[i].nColSize,  pTmp+offSet[i]);
		miaoshu->Exec();

		while( miaoshu->Fetch() && !miaoshu->IsEnd() )
		{
			switch (bjlx)
			{
			case KaiGuan_ID:
				parKaiGuan->push_back(tmpKG);
				break;
			case DaoZha_ID:
				parDaoZha->push_back(tmpDZ);
				break;
			case DMSFeederSection_ID:
				parKuiXianDuan->push_back(tmpKXD);
				break;
			case DMSTransformer_ID:
				parPBBianYaQi->push_back(tmpPB);
				break;
			default:
				break;
			}
		}
		miaoshu->CloseSQL();
	}

	return DB_SUCCESS;
}


//wugc<2009.11.13�ӵ������˶˿ڱ��л�ȡԪ�ڵ�Ŷ�Ӧ�ĵ�ѹ�ȼ�
Juint8 CMSData::GetDWTopoPortVoltageLevel( Juint32 nPNodeID )
{
	CIIOdbcDBI* miaoshu=GetDatabase(false); 
	if (miaoshu==NULL || !miaoshu->IsOpen()) 
		return 0;


	char strSQL[128];
	Juint16 nVoltage = 0;
	sprintf(strSQL,"select DianYaDengJiID from DWTopoPort where pnodeid=%d",nPNodeID);
	miaoshu->PrepareSQL(strSQL);
	miaoshu->BindCol(IES_SQL_USMALLINT,0, &nVoltage);
	int control = miaoshu->Exec();
	if(control == -1) 
	{
		miaoshu->CloseSQL();
		return 0;
	}
	miaoshu->Fetch();
	miaoshu->CloseSQL();
	return nVoltage;
}
//wugc>

//=============================================================================
// ���ݳ�վ��ȡ��վ���������������(���ڲ���=1)
// ��ڣ�����������վ�����ء���բ��ĸ������ָ��
// ���ڣ����������롢���ء���բ��ĸ��������Ϣ
// Date: 2002.10.31
//=============================================================================
//zhangjq
//Jint32 CMSData::GetDWTopoMainBuJian(DATAID_TYPE wStationID, vector<DWTopoBuJian>* parDWTopoBuJian)
Jint32 CMSData::GetDWTopoMainBuJian(DATAID_TYPE wStationID, vector<DWTopoBuJian>* parDWTopoBuJian, Juint16 fieldType)
{
	CHECKPARAM(wStationID, parDWTopoBuJian, aDWTopo_Table[7], DWTopoBuJianOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("ChangZhanID=%d AND ComponentNo=1 and FieldTypeID=%d", wStationID, fieldType);//zhangjq
	Jchar* order = "ChangZhanID,FieldID,RecID";
	DWTopoBuJian tmpDWTopoBuJian;
	
	parDWTopoBuJian->clear();
	if (GetDBValue(miaoshu, &aDWTopo_Table[7], filter.GetBuf(), (Juint8*)&tmpDWTopoBuJian, DWTopoBuJianOffset, order)==DB_SUCCESS)
	{
		parDWTopoBuJian->push_back(tmpDWTopoBuJian);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parDWTopoBuJian->push_back(tmpDWTopoBuJian);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ���õ���΢���˲�����Ϣ
// ��ڣ�����������վ��վ������š�Ҫд��ĵ�����������ָ�롢�������ʹ���
// ���ڣ�����������
// Date: 2002.10.31
//=============================================================================

Jint32 CMSData::SetDWTopoBuJian(DATAID_TYPE wStationID, Jint16 wStaFieldID,
								vector<DWTopoBuJian>* parDWTopoBuJian, 
								Juint8 byOpType)			//0=����/�޸ģ���1=ɾ��
{//������ڸ������ͣ����޸ĸü�¼����������.
	CHECKSETPARAM(wStationID, parDWTopoBuJian, aDWTopo_Table[7], DWTopoBuJianOffset, byOpType);
	CONNECTMSDB_2();

	Jint32	retcode = DB_ERROR;
	DWTopoBuJian tmpDWTopoBuJian;

	CIIString filter;
	if (byOpType==1) 
	{
		filter.Format("ChangZhanID=%d AND FieldID=%d", wStationID, wStaFieldID);
		retcode = OpereDBParam(miaoshu, &aDWTopo_Table[7], (Juint8*)(&tmpDWTopoBuJian), DWTopoBuJianOffset, filter.GetBuf(), byOpType);
	}	
	else if (byOpType==0)
	{
		for (Jint16 i=0; i<parDWTopoBuJian->size(); i++)
		{
			tmpDWTopoBuJian = (*parDWTopoBuJian)[i];
			tmpDWTopoBuJian.wChangZhanID = wStationID;
			tmpDWTopoBuJian.wFieldID = wStaFieldID;
			tmpDWTopoBuJian.byRecID = i+1;
			filter.Format("ChangZhanID=%d AND FieldID=%d AND RecID=%d" , wStationID, wStaFieldID, i+1);
			retcode = OpereDBParam(miaoshu, &aDWTopo_Table[7], (Juint8*)(&tmpDWTopoBuJian), DWTopoBuJianOffset, filter.GetBuf(), byOpType);
		}
	}

	return retcode;
}

//=============================================================================
// ��ȡ����΢���˶˿ڶ���
// ��ڣ�����������վ��վ������š��������˶˿�����ָ��
// ���ڣ����������롢�������˶˿���Ϣ
// Date: 2002.10.31
//=============================================================================
Jint32 CMSData::GetDWTopoPort(DATAID_TYPE wStationID, 
							  Jint16 wStaFieldID, vector<DWTopoPort>* parDWTopoPort)
{
	CHECKPARAM(wStationID, parDWTopoPort, aDWTopo_Table[8], DWTopoPortOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("ChangZhanID=%d AND FieldID=%d", wStationID, wStaFieldID);
	Jchar* order = "ChangZhanID,FieldID,RecID";
	DWTopoPort tmpDWTopoPort;
	
	parDWTopoPort->clear();
	if (GetDBValue(miaoshu, &aDWTopo_Table[8], filter.GetBuf(), (Juint8*)&tmpDWTopoPort, DWTopoPortOffset, order)==DB_SUCCESS)
	{
		parDWTopoPort->push_back(tmpDWTopoPort);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parDWTopoPort->push_back(tmpDWTopoPort);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ����Ԫ�ڵ��ȡ����Ӧ�ĵ������˶˿ڵ���Ϣ
// ��ڣ���������Ԫ�ڵ�š��������˶˿�����ָ��
// ���ڣ����������롢�������˶˿���Ϣ
// Date: 2002.10.31
//=============================================================================

Jint32 CMSData::GetDWTopoPort(Juint32 nPNodeID, vector<DWTopoPort>* parDWTopoPort)
{
	CHECKPARAM(nPNodeID, parDWTopoPort, aDWTopo_Table[8], DWTopoPortOffset);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("PnodeID=%d", nPNodeID);
	Jchar* order = "ChangZhanID,FieldID,RecID";
	DWTopoPort tmpDWTopoPort;
	
	parDWTopoPort->clear();
	if (GetDBValue(miaoshu, &aDWTopo_Table[8], filter.GetBuf(), (Juint8*)&tmpDWTopoPort, DWTopoPortOffset, order)==DB_SUCCESS)
	{
		parDWTopoPort->push_back(tmpDWTopoPort);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parDWTopoPort->push_back(tmpDWTopoPort);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ����΢���˶˿ڶ���
// ��ڣ�����������վ��վ������š��������˶˿���Ϣ����ָ�롢�������ʹ���
// ���ڣ����������롢�������˶˿���Ϣ
// Date:2002.10.31
//=============================================================================

Jint32 CMSData::SetDWTopoPort(DATAID_TYPE wStationID, Jint16 wStaFieldID,
								vector<DWTopoPort>* parDWTopoPort, 
								Juint8 byOpType)			//0=����/�޸ģ�1=ɾ��
{//������ڸ������ͣ����޸ĸü�¼����������.
	CHECKSETPARAM(wStationID, parDWTopoPort, aDWTopo_Table[8], DWTopoPortOffset, byOpType);
	CONNECTMSDB_2();

	Jint32	retcode = DB_ERROR;
	DWTopoPort tmpDWTopoPort;

	CIIString filter;
	if (byOpType==1) 
	{
		filter.Format("ChangZhanID=%d AND FieldID=%d", wStationID, wStaFieldID);
		retcode = OpereDBParam(miaoshu, &aDWTopo_Table[8], (Juint8*)(&tmpDWTopoPort), DWTopoPortOffset, filter.GetBuf(), byOpType);
	}	
	else if (byOpType==0)
	{
		for (Jint16 i=0; i<parDWTopoPort->size(); i++)
		{
			tmpDWTopoPort = (*parDWTopoPort)[i];
			tmpDWTopoPort.wChangZhanID = wStationID;
			tmpDWTopoPort.wFieldID = wStaFieldID;
			tmpDWTopoPort.byRecID = i+1;
			filter.Format("ChangZhanID=%d AND FieldID=%d AND RecID=%d" , wStationID, wStaFieldID, i+1);
			retcode = OpereDBParam(miaoshu, &aDWTopo_Table[8], (Juint8*)(&tmpDWTopoPort), DWTopoPortOffset, filter.GetBuf(), byOpType);
		}
	}

	return retcode;
}
//=============================================================================
// ���ݲ������ͺͲ����������ȡ�ò�����ȫ����Ϣ
// ������������(ĸ�ߡ���·�����ء���բ����ѹ�����������CT��PT�����ɡ�ע�롢�������ݡ������翹)
// ��ڣ�����������վ���������͡�������š���ȡ��Ϣָ��
// ���ڣ�
// Date: 2002.10.31
//=============================================================================
Jint32 CMSData::GetBuJianInfo(DATAID_TYPE wStationID, Juint8 byBJLX, 
							   const char* szBJBH, void* pBuJianInfo)
{
	Jint32	retcode = DB_NO_DATA_FOUND;
	DATAID_TYPE	wBJID = 0;

//	if (wStationID < 1 || !pBuJianInfo || byBJLX<4 || byBJLX>18)		return DB_INVALID_PARAM;
	if (wStationID < 1 || !pBuJianInfo || byBJLX<MuXian_ID || byBJLX>PT_ID)		return DB_INVALID_PARAM; 
	CONNECTMSDB_2();

	CIIString sql, filter;
	CIIString strBiaoMing = GetBiaoMing(byBJLX);
	//EMS-Mend<
	//���ѽ� 2006.7.6 BUG	
//	if (byBJLX == XianLu_ID) filter.Format("Biaohao='%s'", szBJBH);
//	else filter.Format("ChangZhanID=%d AND Biaohao='%s'", wStationID, szBJBH);
	if (byBJLX == XianLu_ID) filter.Format("BianHao='%s'", szBJBH);
	else filter.Format("ChangZhanID=%d AND BianHao='%s'", wStationID, szBJBH);	
	//EMS-Mend>
	sql.Format("SELECT ID FROM %s WHERE %s",strBiaoMing.GetBuf(), filter.GetBuf());
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wBJID);
	miaoshu->Exec();
	if (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		switch(byBJLX)
		{
			case MuXian_ID:
				retcode = GetMuXian(wBJID, (TK_MuXian*)pBuJianInfo);
				break;
			case XianLu_ID:
				retcode = GetXianLu(wBJID, (TK_XianLu*)pBuJianInfo);
				break;
			case KaiGuan_ID:
				retcode = GetKaiGuan(wBJID, (TK_KaiGuan*)pBuJianInfo);
				break;
			case DaoZha_ID:
				retcode = GetDaoZha(wBJID, (TK_DaoZha*)pBuJianInfo);
				break;
			case CT_ID:
				retcode = GetCT(wBJID, (TK_CT*)pBuJianInfo);
				break;
			case PT_ID:
				retcode = GetPT(wBJID, (TK_PT*)pBuJianInfo);
				break;
			case BianYaQi_ID:
				retcode = GetBianYaQi(wBJID, (TK_BianYaQi*)pBuJianInfo);
				break;
			case FaDianJi_ID:
				retcode = GetFaDianJi(wBJID, (TK_FaDianJi*)pBuJianInfo);
				break;
			case FuHe_ID:
				retcode = GetFuHe(wBJID, (TK_FuHe*)pBuJianInfo);
				break;
			case ZhuRu_ID:
				retcode = GetZhuRu(wBJID, (TK_ZhuRu*)pBuJianInfo);
				break;
			case BingLianDianRong_ID:
				retcode = GetBingLianDianRong(wBJID, (TK_BingLianDianRong*)pBuJianInfo);
				break;
			case ChuanLianDianKang_ID:
				retcode = GetChuanLianDianKang(wBJID, (TK_ChuanLianDianKang*)pBuJianInfo);
				break;
			default:
				break;
		}
	}

	return retcode;
}

// EMS-Mend< ��� 2008.1.7 10:25
// �޸�ԭ��:Ϊ�Զ����ɼ��ͼ����
//=============================================================================
// ���ݲ������ͺͲ����������ȡ�ò�����ȫ����Ϣ
// ������������(ĸ�ߡ���·�����ء���բ����ѹ�����������CT��PT�����ɡ�ע�롢�������ݡ������翹)
// ��ڣ�����������վ���������͡�������š���ȡ��Ϣָ��
// ���ڣ�
// Date: 2008.1.7
//=============================================================================
Jint32 CMSData::GetBuJianInfo(DATAID_TYPE wStationID, Juint8 byBJLX, 
							   DATAID_TYPE wID, void* pBuJianInfo)
{
	Jint32	retcode = DB_NO_DATA_FOUND;
	DATAID_TYPE	wBJID = 0;

	if (wStationID < 1 || !pBuJianInfo || byBJLX < MuXian_ID || byBJLX > PT_ID)		return DB_INVALID_PARAM; 
	CONNECTMSDB_2();

	switch(byBJLX)
	{
		case MuXian_ID:
			retcode = GetMuXian(wID, (TK_MuXian*)pBuJianInfo);
			break;
		case XianLu_ID:
			retcode = GetXianLu(wID, (TK_XianLu*)pBuJianInfo);
			break;
		case KaiGuan_ID:
			retcode = GetKaiGuan(wID, (TK_KaiGuan*)pBuJianInfo);
			break;
		case DaoZha_ID:
			retcode = GetDaoZha(wID, (TK_DaoZha*)pBuJianInfo);
			break;
		case CT_ID:
			retcode = GetCT(wID, (TK_CT*)pBuJianInfo);
			break;
		case PT_ID:
			retcode = GetPT(wID, (TK_PT*)pBuJianInfo);
			break;
		case BianYaQi_ID:
			retcode = GetBianYaQi(wID, (TK_BianYaQi*)pBuJianInfo);
			break;
		case FaDianJi_ID:
			retcode = GetFaDianJi(wID, (TK_FaDianJi*)pBuJianInfo);
			break;
		case FuHe_ID:
			retcode = GetFuHe(wID, (TK_FuHe*)pBuJianInfo);
			break;
		case ZhuRu_ID:
			retcode = GetZhuRu(wID, (TK_ZhuRu*)pBuJianInfo);
			break;
		case BingLianDianRong_ID:
			retcode = GetBingLianDianRong(wID, (TK_BingLianDianRong*)pBuJianInfo);
			break;
		case ChuanLianDianKang_ID:
			retcode = GetChuanLianDianKang(wID, (TK_ChuanLianDianKang*)pBuJianInfo);
			break;
		default:
			break;
	}

	return retcode;
} 
// EMS-Mend>

// EMS-Mend< ��� 2008.2.2 8:52
// �޸�ԭ��:Ϊ�Զ����ɼ��ͼ����
//=============================================================================
// ���ݲ������ͺͲ����������ȡ�ò��������������Ϣ
// ������վID����ѹ�ȼ�ID�������͡�վ�������
// ��ڣ��������͡�������š���ȡ��Ϣָ��
// ���ڣ�
// Date: 2008.2.2
//=============================================================================
Jint32 CMSData::GetDeviceTopoMiaoShu(Juint8 bybjlx, DATAID_TYPE wbjID, DATAID_TYPE &m_wStationId, Juint8 &m_byVoltageLevelId, Juint16 &m_wStationFieldId, Juint16 &m_wFieldType)
{
	Jint32	retcode = DB_NO_DATA_FOUND;
	DATAID_TYPE	wBJID = 0;

	CONNECTMSDB_2();

	CIIString strSql;

	switch(bybjlx)
	{
		case MuXian_ID:
			strSql = "select changzhanid, dianyadengjiid, stafieldid, fieldtype from muxian where id = ?";
			break;
		case KaiGuan_ID:
			strSql = "select changzhanid, dianyadengjiid, stafieldid, fieldtype from kaiguan where id = ?";
			break;
		case BianYaQi_ID:
			strSql = "select changzhanid, GaoYaCeDengJiID, stafieldid, fieldtype from bianyaqi where id = ?";
			break;
		default:
			return retcode;
	}

	miaoshu->PrepareSQL(strSql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_wStationId);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &m_byVoltageLevelId);	//���»� 2009.11.19 IES_SQL_USMALLINT->IES_SQL_UTINYINT
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &m_wStationFieldId);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &m_wFieldType);
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wbjID);
	miaoshu->Exec();

	Jint32 ret = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;

	miaoshu->CloseSQL();
	
	return retcode;
}
// EMS-Mend>