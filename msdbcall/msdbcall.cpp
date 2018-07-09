//====================================================================
// �ļ���: msdbcall.cpp
//
// ------------------------------------------------------------------
// ���ļ��ṩ����������ĸ��ֺ���������ͼ���˻��ӿڽ���ʹ��
// ------------------------------------------------------------------
//
// ʱ��: 2002.10.25
// ���:
// ------------------------------------------------------------------
// �޸�˵��(�밴��ʽ˵��)...
//====================================================================
//#pragma comment(lib, "sbmixdll.lib")

#include "iessbmix.h"
#include "dbdefine.h"
#include "msdb.h"
#include "msdbcall.h"
#include "iescommon.h"

//********************************************************************
//*
//*					ȡ�����������ຯ��
//*
//********************************************************************


CIILog		gCIILog_msdbcall;



//=============================================================================
// CMSData ���캯��
// Date: 2002.10.25
//=============================================================================

CMSData::CMSData()
{
	Jint16	ii;
	for (ii=0; ii<4; ii++)
		miaoshus[ii] = NULL;

	gCIILog_msdbcall.SetProcName("msdbcall");

	//----- ȡ���������ݺ���ָ�����鸳ֵ
	for (ii=0; ii<MAX_CALL_NUM; ii++)				// ȡ������
	{
		funGetMiaoShuData[ii] = &CMSData::NullData;
		funSetMiaoShuData[ii] = &CMSData::NullData;
	}

	funGetMiaoShuData[0] = &CMSData::Get_MingZi;	//��������������

	funGetMiaoShuData[2] = &CMSData::Get_MingZi;	//��վ����������
	

	funGetMiaoShuData[4] = &CMSData::Get_MingZi;	//ĸ�߲���������
	

	funGetMiaoShuData[6] = &CMSData::Get_MingZi;	//��·����������
	

	funGetMiaoShuData[8] = &CMSData::Get_MingZi;	//���ز���������
	funGetMiaoShuData[10] = &CMSData::Get_UsedTime;	//���ز�����Ͷ������
	funGetMiaoShuData[11] = &CMSData::Get_ProdType;	//���ز����ĳ�������
	
	funGetMiaoShuData[12] = &CMSData::Get_MingZi;	//��բ����������
	funGetMiaoShuData[14] = &CMSData::Get_UsedTime;	//��բ������Ͷ������
	funGetMiaoShuData[15] = &CMSData::Get_ProdType;	//��բ�����ĳ�������
	
	funGetMiaoShuData[16] = &CMSData::Get_MingZi;	//��������������
	
	funGetMiaoShuData[18] = &CMSData::Get_MingZi;	//��ѹ������������
	funGetMiaoShuData[20] = &CMSData::Get_UsedTime;	//��ѹ��������Ͷ������
	funGetMiaoShuData[21] = &CMSData::Get_ProdType;	//��ѹ�������ĳ�������
	
	funGetMiaoShuData[22] = &CMSData::Get_MingZi;	//���������������
	funGetMiaoShuData[24] = &CMSData::Get_UsedTime;	//�����������Ͷ������
	funGetMiaoShuData[25] = &CMSData::Get_ProdType;	//����������ĳ�������
	
	funGetMiaoShuData[26] = &CMSData::Get_MingZi;	//CT ����������
	funGetMiaoShuData[28] = &CMSData::Get_UsedTime;	//CT ������Ͷ������
	funGetMiaoShuData[29] = &CMSData::Get_ProdType;	//CT �����ĳ�������
	
	funGetMiaoShuData[30] = &CMSData::Get_MingZi;	//PT ����������
	funGetMiaoShuData[32] = &CMSData::Get_UsedTime;	//PT ������Ͷ������
	funGetMiaoShuData[33] = &CMSData::Get_ProdType;	//PT �����ĳ�������
	
	funGetMiaoShuData[34] = &CMSData::Get_MingZi;	//������·����������
	
	funGetMiaoShuData[36] = &CMSData::Get_MingZi;	//ע����·����������
	
	funGetMiaoShuData[38] = &CMSData::Get_MingZi;	//���������������
	funGetMiaoShuData[40] = &CMSData::Get_UsedTime;	//�����������Ͷ������
	funGetMiaoShuData[41] = &CMSData::Get_ProdType;	//����������ĳ�������
	
	funGetMiaoShuData[42] = &CMSData::Get_MingZi;	//��ֹ����������������
	funGetMiaoShuData[44] = &CMSData::Get_UsedTime;	//��ֹ������������Ͷ������
	funGetMiaoShuData[45] = &CMSData::Get_ProdType;	//��ֹ�����������ĳ�������
	
	funGetMiaoShuData[46] = &CMSData::Get_MingZi;	//�������ݲ���������������
	funGetMiaoShuData[48] = &CMSData::Get_UsedTime;	//�������ݲ�����������Ͷ������
	funGetMiaoShuData[49] = &CMSData::Get_ProdType;	//�������ݲ����������ĳ�������
	
	funGetMiaoShuData[50] = &CMSData::Get_MingZi;	//�����翹������������
	funGetMiaoShuData[52] = &CMSData::Get_UsedTime;	//�����翹��������Ͷ������
	funGetMiaoShuData[53] = &CMSData::Get_ProdType;	//�����翹�������ĳ�������
	
	funGetMiaoShuData[54] = &CMSData::Get_MingZi;	//���ⵥ��ģ��������������
	
	funGetMiaoShuData[56] = &CMSData::Get_MingZi;	//����˫��ģ��������������
	
	funGetMiaoShuData[58] = &CMSData::Get_MingZi;	//����״̬������������
	m_bLoadDBFromFile = false;//EMS-Mend: ����� 2006.11.30 �����Ƿ���ļ��������ݿ�	
}

//=============================================================================
// CMSData ��������
// Date: 2002.10.25
//=============================================================================
CMSData::~CMSData()
{
	ExitProc();
}

//=============================================================================
//  �������г�ʼ������ʱ����
//  Date : 2002.10.25
//=============================================================================
Juint8 CMSData::InitProc()
{
	return CreateConnection();
}

//=============================================================================
//  �����˳����г���ʱ����
//  Date : 2002.10.25
//=============================================================================

void CMSData::ExitProc()
{
	DisConnect();
	for (int i=0; i<4; i++)
	{
		if (miaoshus[i] != NULL)
		{
			delete miaoshus[i];
			miaoshus[i] = NULL;
		}
	}
}

//=============================================================================
void CMSData::BeginTrans()
{
	CIIOdbcDBI* miaoshu = GetDatabase();
	if (miaoshu)
		miaoshu->BeginTrans();
}
//=============================================================================
void CMSData::RollBack()
{
	CIIOdbcDBI* miaoshu = GetDatabase();
	if (miaoshu)
		miaoshu->Rollback();
}
//=============================================================================
void CMSData::Commit()
{
	CIIOdbcDBI* miaoshu = GetDatabase();
	if (miaoshu)
		miaoshu->Commit();
}


//=============================================================================
// ���������ͱ�(���캯������)
// Input : �ṹ����ָ��
// Date: 2002.10.25
//=============================================================================

Jint32	CMSData::GetBuJianLeiXing(ABuJianLeiXing* arBuJianLeiXing)
{
	
	CIIString	sql, filter;
	SBuJianLeiXing aBJLX;
	if (!arBuJianLeiXing)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	arBuJianLeiXing->clear();
	
	sql.Format("SELECT ID, MingZi FROM BuJianLeiXing Order by ID");	

	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &aBJLX.byID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, aBJLX.szMingZi);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arBuJianLeiXing->push_back(aBJLX);
	}
	miaoshu->CloseSQL();

	return arBuJianLeiXing->size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
	
}

Jint32	CMSData::GetBuJianLeiXing(MapBuJianLeiXing& mapBuJianLeiXing)
{
	CIIString	sql, filter;
	SBuJianLeiXing aBJLX;
	
	CONNECTMSDB();

	mapBuJianLeiXing.clear();

	sql.Format("SELECT ID, MingZi,BiaoMing FROM BuJianLeiXing");	

	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &aBJLX.byID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, aBJLX.szMingZi);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, aBJLX.szBiaoMing);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		mapBuJianLeiXing[aBJLX.byID] = aBJLX;
	}
	miaoshu->CloseSQL();

	return mapBuJianLeiXing.size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}


Jint32	CMSData::GetBJLX2BJCS(MapBJLX2BJCS& mapBJLX2BJCS,Juint8 RDType)
{
	CIIString	sql, filter;
	SBuJianLeiXing aBJLX;

	CONNECTMSDB();

	mapBJLX2BJCS.clear();
	MapBuJianLeiXing mapBJLX;
	int ret = GetBuJianLeiXing(mapBJLX);
	if (ret || mapBJLX.empty())
		return DB_NO_DATA_FOUND;

	for (MapBuJianLeiXing::iterator it = mapBJLX.begin(); it != mapBJLX.end(); it ++)
	{
		MapBuJianCanShu mapBuJianCanShu;
		ret = GetBuJianCanShu(mapBuJianCanShu,it->first,RDType);
		if (ret != DB_SUCCESS)
			continue;
		mapBJLX2BJCS[it->first] = mapBuJianCanShu;
	}
	
	return mapBJLX2BJCS.size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}



//=============================================================================
//�������������ݿ���פ�����������������ӣ�����iiNetS���ص������ݿ������
//�������������߲���
//���ӳɹ�����1�����򷵻�0
//Date : 2002.10.25
//=============================================================================

Jboolean CMSData::CreateConnection(Jboolean bReopen)
{
	//��ԭ�������ݿ����Ӳ�һ��, ��ر�ԭ�������ӣ����½����µ�����.
	try
	{
		CIIOdbcDBI* miaoshu = GetDatabase();
		if (miaoshu->IsOpen())	// �Ѿ���
		{
			// �ж��Ƿ�һ��
			if (bReopen)
			{
				miaoshu->Close();
				return GetDatabase()->IsOpen();
			}
			return JTRUE;
		}
	}
	catch (...)
	{}
	return JFALSE;
}
//=============================================================================
// ǿ�ƶϿ������ݿ������
// Date: 2002.11.9
//=============================================================================

Jboolean CMSData::DisConnect()
{
	try
	{
		for (int i=0; i<4; i++)
		{
			if (miaoshus[i] != NULL && miaoshus[i]->IsOpen())
				miaoshus[i]->Close();
		}
	}
	catch (...)
	{}
	return JTRUE;
}

// ��ȡ����Դ, �ڲ��Զ�����
// bCheckNet = true  �����������״��
//           = false ÿ3����һ��
CIIOdbcDBI* CMSData::GetDatabase(bool bCheckNet)
{
	char chTmp[128];
	static char		s_oldSID[16] = "a_ms_1";
	static time_t	s_CheckTime = 0;
	// ��ȡ������Դ
	char		sid[16], uid[16], pwd[16];
	Juint16		nlen, ulen, plen;
	time_t		now = time(NULL);
	if (now - s_CheckTime > 5 || bCheckNet)
	{
		s_CheckTime = now;
		bCheckNet = true;
	}
	if (bCheckNet)
	{
		GetMainDataSource(sid, nlen, true);

		if (strcmp(s_oldSID, sid) != 0)
		{	
			// �������Դ�ı䣬�ر�ԭ�������ݿ�
			nlen = strlen(s_oldSID);
			ulen = 0;
			if (nlen > 2)
			{
				if (s_oldSID[0] == 'b' || s_oldSID[0] == 'B' )
				{
					if (s_oldSID[nlen-1] == '2')	// b_ms_2
						ulen = 3;
					else							// b_ms_1
						ulen = 2;
				}
				else
				{
					if (s_oldSID[nlen-1] == '2')	// a_ms_2
						ulen = 1;
					else							// a_ms_1
						ulen = 0;
				}
			}
			if (miaoshus[ulen] != NULL && miaoshus[ulen]->IsOpen())
			{
				if (CheckDataSourceIPActive(s_oldSID))
				{
					sprintf(chTmp, "�������Դ%sIP����", s_oldSID);
					gCIILog_msdbcall.Add(chTmp);

					miaoshus[ulen]->Close();
				}
				else
				{
					sprintf(chTmp, "�������Դ%sIP������", s_oldSID);
					gCIILog_msdbcall.Add(chTmp);

					miaoshus[ulen]->Close(false);
					sprintf(chTmp, "�ر�%s", s_oldSID);
					gCIILog_msdbcall.Add(chTmp);
				}
			}
		}
		strcpy(s_oldSID, sid);
	}
	GetDBAccessParam(uid, ulen, pwd, plen, true);
	// a_ms_1	: 0
	// a_ms_2	: 1
	// b_ms_1	: 2
	// b_ms_2	: 3
	nlen = strlen(s_oldSID);
	ulen = 0;
	if (nlen > 2)
	{
		if (s_oldSID[0] == 'b' ||s_oldSID[0] == 'B' )
		{
			if (s_oldSID[nlen-1] == '2')	// b_ms_2
				ulen = 3;
			else					// b_ms_1
				ulen = 2;
		}
		else
		{
			if (s_oldSID[nlen-1] == '2')	// a_ms_2
				ulen = 1;
			else					// a_ms_1
				ulen = 0;
		}
	}
	try
	{
		if (miaoshus[ulen] == NULL)
			miaoshus[ulen] = new CIIOdbcDBI();
	
		//EMS-Mend: ����� 2006.11.30
		//�޸�ԭ��: �����Ƿ���ļ��������ݿ�
		//EMS-Mend<
		miaoshus[ulen]->SetFromFileDB(m_bLoadDBFromFile);
		//EMS-Mend>

		if (!miaoshus[ulen]->IsOpen())
		//	miaoshus[ulen]->Open(s_oldSID, uid, pwd);
		{
			bool	bOK = miaoshus[ulen]->Open(s_oldSID, uid, pwd);
			if(!bOK)
			{
				s_oldSID[nlen-1] = (s_oldSID[nlen-1] == '1' ? '2':'1');
				bOK = miaoshus[ulen]->Open(s_oldSID, uid, pwd);
			}
		}
		return miaoshus[ulen];
	}
	catch (...)
	{}
	return miaoshus[0];
}
//=============================================================================
// ��ȡû��ʹ�õ�ID��
// ��ڣ�ID����ָ�롢���ص�ID�š�ID������
// ���ڣ�����������
// Date: 2002.11.1
//=============================================================================
Jboolean CMSData::GetFreeID(vector<DATAID_TYPE>* parID, DATAID_TYPE& wID, DATAID_TYPE wIDUpLimit)
{
	if (parID == NULL)			return JFALSE;

	Juint16 ItemNum = parID->size();
	if (ItemNum>=wIDUpLimit)	return JFALSE;

	if (ItemNum>0 && (*parID)[ItemNum-1] < wIDUpLimit)
		wID = (*parID)[ItemNum-1]+1;
	else
	{
		wID = 1;
		for (Juint16 i=0; i<ItemNum; i++, wID++)
		{
			if (wID != (*parID)[i])	break;
		}
	}

	return JTRUE;
}

//=============================================================================
// ��ȡĳվ��û��ʹ�õ���С����� DWTopo
// ��ڣ�����������վ�������
// ���ڣ����������롢�����ֵ
// Date: 2002.11.6
//=============================================================================

Jint32 CMSData::GetMinFieldNoUseInStation(DATAID_TYPE wStationID, Juint16& wFieldNo)
{
	if (wStationID < 1)		return DB_INVALID_PARAM;
	CONNECTMSDB();

	Juint16	tmpFieldID=0;
	CIIString sql;
	sql.Format("SELECT FieldID FROM DWTopo WHERE ChangZhanID=%d ORDER BY FieldID", wStationID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &tmpFieldID);
	miaoshu->Exec();

	wFieldNo = 1;
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		if (wFieldNo != tmpFieldID)
			break;
		wFieldNo++;
	}

	return DB_SUCCESS;
}

//=============================================================================
// ��ȡÿһ����ļ�¼���ܸ���(��ǰ�༭�ı��ID��־ֵ)
// ��ڣ������������ݱ�ID����¼����ָ��
// ���ڣ�����������
// Date: 2002.11.6
//=============================================================================
Jint32 CMSData::GetRecordCount(Juint8 byTableID, Juint16& wRecCount)
{
	if (INVALIDTYPE(byTableID)) 	return DB_INVALID_PARAM;
	CONNECTMSDB();

	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(byTableID);
	sql.Format("SELECT count(*) FROM %s", strBiaoMing.GetBuf());
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &wRecCount);
	miaoshu->Exec();

	return  (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_ERROR;
}


//=============================================================================
// ȡ������Ա�б�(��š����֡����롢Ȩ�ޡ�����)/��iiNetS��ȡ
// ���: ��Ա����ָ��
// ����: ����������
// date: 2003.2.27
//=============================================================================
Jint32 CMSData::GetRenYuan(ARenYuan* parRenYuan)
{
	if (parRenYuan == NULL)
		return DB_INVALID_PARAM;
	parRenYuan->clear();

	CONNECTMSDB();
	SRenYuan	ren;
	memset(&ren, 0, sizeof(SRenYuan));

	miaoshu->PrepareSQL("SELECT BianHao,Name,MiMa,RenYuanType,QuanXian, zhiwu, CtrlArea FROM RenYuan ORDER BY Name");
	miaoshu->BindCol(IES_SQL_UTINYINT,	0, &ren.byID);
	miaoshu->BindCol(IES_SQL_STRING,	MINGZILEN, ren.szMingZi);
	miaoshu->BindCol(IES_SQL_UINT,		0, &ren.nMiMa);
	miaoshu->BindCol(IES_SQL_UTINYINT,	0, &ren.byType);
	miaoshu->BindCol(IES_SQL_UINT,	0, &ren.wQuanXian);
	miaoshu->BindCol(IES_SQL_STRING,	16, ren.szZhiWu);
	miaoshu->BindCol(IES_SQL_USMALLINT,	0, &ren.wAreaID);
	miaoshu->Exec();
	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		parRenYuan->push_back(ren);
	}
	miaoshu->CloseSQL();
	return parRenYuan->size()>0 ? DB_SUCCESS:DB_ERROR;
}

//=============================================================================
// ������Ա���֣�ȡ����Ա�������Ϣ(��š����֡����롢Ȩ�ޡ�����)
// ���: ��Ա���֡���Ա��Ϣָ��
// ����: ����������
// date: 2003.2.27
//=============================================================================
Jint32 CMSData::GetOneRenYuan(char* renMingZi, SRenYuan* pRenYuan)
{
	if (renMingZi == NULL || strlen(renMingZi) == 0 || pRenYuan == NULL)
		return DB_INVALID_PARAM;

	CONNECTMSDB();

	strcpy(pRenYuan->szMingZi, renMingZi);
	CIIString sql;
	sql.Format("SELECT BianHao,MiMa,RenYuanType,QuanXian FROM RenYuan WHERE Name='%s'", renMingZi);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT,	0, &pRenYuan->byID);
	miaoshu->BindCol(IES_SQL_UINT,		0, &pRenYuan->nMiMa);
	miaoshu->BindCol(IES_SQL_UTINYINT,	0, &pRenYuan->byType);
	miaoshu->BindCol(IES_SQL_UINT,		0, &pRenYuan->wQuanXian);// DMS-MEND< baizy,����Ʊ����,2011.09.14//baizy,Т��˳����Ŀ-���Գ�,2011.10.21,IES_SQL_USMALLINT
	miaoshu->Exec();
	bool bRet = (miaoshu->Fetch() && !miaoshu->IsEnd());
	miaoshu->CloseSQL();
	if ( bRet )
		return DB_SUCCESS;
	else
		return DB_ERROR;
}

//EMS-Mend<���»� 2009.3.18
//�޸�ԭ������ͼ�����ù�����
	//������Ա���֣�ȡ����Ա�������Ϣ
Jint32 CMSData::GetRenYuanName(Juint16 nID, char* pRenYuanName)
{
	if (pRenYuanName == NULL)
		return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString sql;
	sql.Format("SELECT Name FROM RenYuan WHERE BianHao='%d'", nID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING,	MINGZILEN, pRenYuanName);
	miaoshu->Exec();

	int nRet = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_ERROR;
	miaoshu->CloseSQL();
	return nRet;
}
//EMS-Mend>

// ��ò������ݿ�Ļ������
CIIString CMSData::GetSelectSQL(STblInfo* table, const char* filter, const char* order)
{
	CIIString sql;
	sql = "SELECT ";
	for (Jint16 i =0; i<table->nColCount; i++)
	{
		sql += table->pColInfo[i].szColName;
		sql += ",";
	}
	sql[sql.GetLength() -1] = ' ';
	sql += "FROM ";
	sql += table->szTableName;
	if (filter!=NULL && strlen(filter)>0)
	{
		sql += " WHERE ";
		sql += filter;
	}
	if (order!=NULL && strlen(order)>0)
	{
		sql += " ORDER BY ";
		sql += order;
	}

	return sql;
}

CIIString CMSData::GetUpdateSQL(STblInfo* table, const char* filter)
{
	CIIString sql;
	sql = "update ";
	sql += table->szTableName;
	sql += " set ";
	for (Jint16 i =0; i<table->nColCount; i++)
	{
		sql += table->pColInfo[i].szColName;
		sql += "=?,";
	}
	sql[sql.GetLength()-1] = ' ';
	if (filter!=NULL && strlen(filter)>0)
	{
		sql += " WHERE ";
		sql += filter;
	}

	return sql;
}

CIIString CMSData::GetDeleteSQL(STblInfo* table, const char* filter)
{
	CIIString sql;
	sql = "delete from ";
	sql += table->szTableName;
	if (filter!=NULL && strlen(filter)>0)
	{
		sql += " WHERE ";
		sql += filter;
	}

	return sql;
}

CIIString CMSData::GetInsertSQL(STblInfo* table)
{
	CIIString sql;

	sql =  "insert into ";
	sql += table->szTableName;
	sql += " (";
	Jint16 i=0;
	for (i =0; i<table->nColCount; i++)
	{
		sql += table->pColInfo[i].szColName;
		sql += ",";
	}
	sql[sql.GetLength()-1] = ')';
	sql += " values (";
	for (i=0; i<table->nColCount; i++)
	{
		sql += "?,";
	}
	sql[sql.GetLength()-1] = ')';

	return sql;
}

void CMSData::BindDBCol(CIIOdbcDBI* msdb, STblInfo* table, Juint8* base, Juint16* offset, Jboolean bOut)
{
	if (bOut)
	{
		for (Jint16 i=0; i<table->nColCount; i++)
			msdb->BindCol(table->pColInfo[i].nColType, table->pColInfo[i].nColSize, base+offset[i]);
	}
	else
	{
		for (Jint16 i=0; i<table->nColCount; i++)
			msdb->BindPara(table->pColInfo[i].nColType, table->pColInfo[i].nColSize, base+offset[i]);
	}

}

Jboolean CMSData::IsRecordExist(CIIOdbcDBI* msdb, const char* szTableName, const char* filter)
{
	CIIString sql;
	Juint32 count=0;
	sql.Format("SELECT COUNT(*) FROM %s WHERE %s", szTableName, filter);
	msdb->PrepareSQL(sql.GetBuf());
	msdb->BindCol(IES_SQL_UINT, 0, &count);
	msdb->Exec();
	msdb->Fetch();

	return count>0;
}

DATAID_TYPE CMSData::GetUsableID(CIIOdbcDBI* msdb, const char* szTableName,  const char* szColumnName, DATAID_TYPE value, DATAID_TYPE wIDUpLimit)
{
	DATAID_TYPE UsableID=0, uValue=0;
	CIIString sql, filter;
	Jboolean bFind=JFALSE;
	filter.Format("%s=%d", szColumnName, value);
	if (value!=0)
	{
		if (IsRecordExist(msdb, szTableName, filter.GetBuf()))
			UsableID = value;
	}

	if (UsableID==0)
	{
		uValue = 0;
		sql = "select count(*) from ";
		sql += szTableName;
		msdb->PrepareSQL(sql.GetBuf());
		msdb->BindCol(SQL_DATAID_TYPE, 0, &uValue);
		msdb->Exec();
		if (!msdb->Fetch() || msdb->IsEnd() || uValue == 0)
		{
			UsableID =1;
			return UsableID;
		}
		 
		sql = "SELECT MAX(";
		sql += szColumnName;
		sql += ") FROM ";
		sql += szTableName;
//EMS-Mend<
//���ѽ� 2006.4.19 ʵ��iesdraw���ɾ����վ����
		//����վ������С��60001�����id
		if(strcmp(szTableName,"changzhan") == 0)
		{
			//EMS_MEND<yuecaijuan 2008-10-09 ��·վID
			CIIString tmp;
			//EMS_MEND<pengxiaoyan 2010-7-1,����³�վ��IDС����·վid�����ڹ���ƽ̨����վ��IDΪ��·վID+1
			//strWhere.Format(" where id != %d", XIANLUZHANID);
			//tmp.Format(" WHERE id != %d",XIANLUZHANID);
			tmp.Format(" where id < %d", XIANLUZHANID);			
			sql += tmp;
			//>EMS_MEND
		}
//EMS-Mend>
		msdb->PrepareSQL(sql.GetBuf());
		msdb->BindCol(SQL_DATAID_TYPE, 0, &uValue);
		msdb->Exec();
		if (!msdb->Fetch() || msdb->IsEnd())
			UsableID =1;
		else if (uValue<wIDUpLimit)
			UsableID = uValue+1;
		else 
		{
			sql = "SELECT ";
			sql += szColumnName;
			sql += " FROM ";
			sql += szTableName;
			sql += " ORDER BY ";
			sql += szColumnName;
			
			msdb->PrepareSQL(sql.GetBuf());
			msdb->BindCol(SQL_DATAID_TYPE, 0, &uValue);
			msdb->Exec();

			UsableID = 0;
			while (msdb->Fetch() && !msdb->IsEnd())
			{
				UsableID++;
				if (UsableID != uValue)
				{
					bFind = JTRUE;
					break;
				}
			}
			if (!bFind)
				UsableID = 0;
		}
	}
	return UsableID;
}

// ��ȡ���ݿ�һ����¼
Jint32 CMSData::GetDBValue(CIIOdbcDBI* msdb, STblInfo* table, const char* filter, Juint8* base, Juint16* offset, const char* order)
{
	CIIString sql = GetSelectSQL(table, filter, order);

	msdb->PrepareSQL(sql.GetBuf());
	BindDBCol(msdb, table, base, offset);
	msdb->Exec();

	Jint32 ret = (msdb->Fetch() && !msdb->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
	if (ret != DB_SUCCESS) 
	{
		char strErr[255];
		const char *szErr = msdb->GetErrorStr();
		sprintf(strErr, "%s:%s", table->szTableName, szErr);
		gCIILog_msdbcall.Add(strErr);
	}
	return ret;
}

// �������ݿ���� byOpType =1 ɾ��, 0 �������޸� ���������Ӽ�¼(ID������)
Jint32 CMSData::OpereDBComp(CIIOdbcDBI* msdb, STblInfo* table, Juint8* base, Juint16* offset, DATAID_TYPE value, Juint8 type)
{
	CIIString sql, filter;
	filter.Format("ID=%d", value);
	if (type == 1)							//ɾ��
	{
		sql = GetDeleteSQL(table, filter.GetBuf());
		return msdb->ExecuteSQL(sql.GetBuf());
	}
	else if (type == 0)
	{
		DATAID_TYPE tmp_value=1;
		tmp_value = GetUsableID(msdb, table->szTableName, "ID", value);
		if (tmp_value == 0)
			return DB_NOID_TO_USE;
		else if (tmp_value == value)
		{
			sql = GetUpdateSQL(table, filter.GetBuf());
			msdb->PrepareSQL(sql.GetBuf());
		}
		else
		{
			memcpy(base, &tmp_value, sizeof(DATAID_TYPE));  // ID ���ڲ����ĵ�һ���ֶ�
			sql = GetInsertSQL(table);
			msdb->PrepareSQL(sql.GetBuf());
		}
		BindDBCol(msdb, table, base, offset, JFALSE);
	}

	Jint32 ret = msdb->Exec()>0 ? DB_SUCCESS : DB_ERROR;
	if (ret != DB_SUCCESS) 
	{
		char strErr[255];
		const char *szErr = msdb->GetErrorStr();
		sprintf(strErr, "%s:%s", table->szTableName, szErr);
		gCIILog_msdbcall.Add(strErr);
	}
	msdb->CloseSQL();
	return ret;
}

// ���ݿ���� byOpType =1 ɾ��, 0 �������޸� ���������Ӽ�¼
Jint32 CMSData::OpereDBParam(CIIOdbcDBI* msdb, STblInfo* table, Juint8* base, Juint16* offset, const char* filter, Juint8 type)
{
	CIIString sql;
	if (type == 1)							//ɾ��
	{
		sql = GetDeleteSQL(table, filter);
		return msdb->ExecuteSQL(sql.GetBuf());
	}
	else if (type == 0)
	{
		if (IsRecordExist(msdb, table->szTableName, filter))
		{
			sql = GetUpdateSQL(table, filter);
			msdb->PrepareSQL(sql.GetBuf());
		}
		else
		{
			sql = GetInsertSQL(table);
			msdb->PrepareSQL(sql.GetBuf());
		}
		BindDBCol(msdb, table, base, offset, JFALSE);
	}

	Jint32 ret = msdb->Exec()>0 ? DB_SUCCESS : DB_ERROR;
	if (ret != DB_SUCCESS) 
	{
		char strErr[255];
		const char *szErr = msdb->GetErrorStr();
		sprintf(strErr, "%s:%s", table->szTableName, szErr);
		gCIILog_msdbcall.Add(strErr);
	}
	msdb->CloseSQL();
	return ret;
}
//EMS-Mend<
//���ѽ� 2006.5.19 �Զ����ɶ����������
//��ȡĳվ��û��ʹ�õĲ�����ָ��ֵ����С����� DWTopo 2006.5.19
Jint32 CMSData::GetMinFieldNoUseInStationExceptSome(DATAID_TYPE wStationID, Juint16& wFieldNo,vector<Jint16>* pFieldIDInUse)
{
	if (wStationID < 1)		return DB_INVALID_PARAM;
	CONNECTMSDB();	
	
	Juint16	tmpFieldID=0;
	Jboolean bInUse = 1;
	CIIString sql;
	sql.Format("SELECT FieldID FROM DWTopo WHERE ChangZhanID=%d ORDER BY FieldID", wStationID);

	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &tmpFieldID);
	miaoshu->Exec();
	
	wFieldNo = 1;		
	
	if(!pFieldIDInUse->size())
	{
		while (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			if (wFieldNo != tmpFieldID)
				break;
			wFieldNo++;
		}

	}
	else
	{
		Jint32 i=0;
		while (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			if (wFieldNo != tmpFieldID)
			{
				for(i=0; i<pFieldIDInUse->size();i++)
				{
					Jint16 m_nIDinUse = (*pFieldIDInUse)[i];
					if(wFieldNo == m_nIDinUse)
					{
						bInUse = 1;
						wFieldNo++;
						if(wFieldNo >= tmpFieldID)
							break;
						else
							i = 0;
					}
					else
						bInUse = 0;
				}
				if(!bInUse)
					break;
			}
						
			wFieldNo++;
		}
		for(i=0; i<pFieldIDInUse->size(); i++)
		{
			if(wFieldNo == (*pFieldIDInUse)[i])
			{
				wFieldNo++;
				i = -1;
			}
			
		}
	}
	
	return DB_SUCCESS;
}
//EMS-Mend>
//EMS-Mend<���»� 2009.3.18
//�޸�ԭ������ͼ�����ù�����
Jint32 CMSData::GetGraLib(vector<sGraLibrary>* parGraLib)						 //����ͼ�ε���Ϣ
{
	if (parGraLib == NULL)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	CIITime	tmpTime;
	sGraLibrary	gra;
	memset(&gra, 0, sizeof(sGraLibrary));
	STimeInfo gratime, gralasttime;
	memset(&gratime, 0, sizeof(STimeInfo));
	memset(&gralasttime, 0, sizeof(STimeInfo));
	parGraLib->clear();

	miaoshu->PrepareSQL("SELECT graname,machine,renyuan,state,timemark, lastmachine, lastrenyuan, lasttimemark FROM gralibrary ORDER BY graname");
	miaoshu->BindCol(IES_SQL_STRING,	128, gra.graname);
	miaoshu->BindCol(IES_SQL_STRING,	MINGZILEN, gra.machine);
	miaoshu->BindCol(IES_SQL_USMALLINT,	0, &gra.renyuan);
	miaoshu->BindCol(IES_SQL_BOOL,		0, &gra.state);
	miaoshu->BindCol(IES_SQL_TIMESTAMP,	0, &gratime);
	miaoshu->BindCol(IES_SQL_STRING,	MINGZILEN, gra.lastmachine);
	miaoshu->BindCol(IES_SQL_USMALLINT,	0, &gra.lastrenyuan);
	miaoshu->BindCol(IES_SQL_TIMESTAMP,	0, &gralasttime);

	if( miaoshu->Exec() <= 0 )
	{
		miaoshu->CloseSQL();
		return DB_DATASOURCE_ERROR;
	}

	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		tmpTime.SetTime(gratime.nYear,gratime.nMonth,gratime.nDay, gratime.nHour,gratime.nMinute,gratime.nSecond);
		gra.timemark = tmpTime.GetTime();
		tmpTime.SetTime(gralasttime.nYear,gralasttime.nMonth,gralasttime.nDay, gralasttime.nHour,gralasttime.nMinute,gralasttime.nSecond);
		gra.lasttimemark = tmpTime.GetTime();
		parGraLib->push_back(gra);
	}
	miaoshu->CloseSQL();
	return DB_SUCCESS;
}

Jint32 CMSData::GetServerGraLib(vector<sServerGraLib>* parGraLib)						 //���з�����ͼ�ε���Ϣ
{
	if (parGraLib == NULL)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	CIITime	tmpTime;
	sServerGraLib	gra;
	memset(&gra, 0, sizeof(sServerGraLib));
	STimeInfo gratime;
	memset(&gratime, 0, sizeof(STimeInfo));
	parGraLib->clear();

	miaoshu->PrepareSQL("SELECT graname,machine,renyuan,state,timemark FROM gralibrary ORDER BY graname");
	miaoshu->BindCol(IES_SQL_STRING,	128, gra.graname);
	miaoshu->BindCol(IES_SQL_STRING,	MINGZILEN, gra.machine);
	miaoshu->BindCol(IES_SQL_USMALLINT,	0, &gra.renyuan);
	miaoshu->BindCol(IES_SQL_BOOL,		0, &gra.state);
	miaoshu->BindCol(IES_SQL_TIMESTAMP,	0, &gratime);

	if( miaoshu->Exec() <= 0 )
	{
		miaoshu->CloseSQL();
		return DB_DATASOURCE_ERROR;
	}

	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		tmpTime.SetTime(gratime.nYear,gratime.nMonth,gratime.nDay, gratime.nHour,gratime.nMinute,gratime.nSecond);
		gra.timemark = tmpTime.GetTime();
		parGraLib->push_back(gra);
	}
	miaoshu->CloseSQL();
	return DB_SUCCESS;
}

//��ȡָ��ͼ�ε�ʱ��
Jint32 CMSData::GetSingleGraLib(Jchar* graname, sGraLibrary *graLib)						//ָ��ͼ�ε�ʱ�� 
{
	if (graname == NULL || graLib == NULL )
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	CIITime	tmpTime;
	STimeInfo gratime, gralasttime;
	memset(&gratime, 0, sizeof(STimeInfo));
	memset(&gralasttime, 0, sizeof(STimeInfo));

	miaoshu->PrepareSQL("SELECT graname,machine,renyuan,state,timemark,lastmachine,lastrenyuan,lasttimemark FROM gralibrary where graname=?");
	miaoshu->BindCol(IES_SQL_STRING,	128, graLib->graname);
	miaoshu->BindCol(IES_SQL_STRING,	MINGZILEN, graLib->machine);
	miaoshu->BindCol(IES_SQL_USMALLINT,	0, &graLib->renyuan);
	miaoshu->BindCol(IES_SQL_BOOL,		0, &graLib->state);
	miaoshu->BindCol(IES_SQL_TIMESTAMP,	0, &gratime);
	miaoshu->BindCol(IES_SQL_STRING,	MINGZILEN, graLib->lastmachine);
	miaoshu->BindCol(IES_SQL_USMALLINT,	0, &graLib->lastrenyuan);
	miaoshu->BindCol(IES_SQL_TIMESTAMP,	0, &gralasttime);
	miaoshu->BindPara(IES_SQL_STRING,	128, graname);
	miaoshu->Exec();
	Jint32 ret = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
	if (ret != DB_SUCCESS) 
	{
		char strErr[255];
		const char *szErr = miaoshu->GetErrorStr();
		sprintf(strErr, "gralibrary:%s", szErr);
		gCIILog_msdbcall.Add(strErr);
	}
	else
	{
		tmpTime.SetTime(gratime.nYear,gratime.nMonth,gratime.nDay, gratime.nHour,gratime.nMinute,gratime.nSecond);
		graLib->timemark = tmpTime.GetTime();
		tmpTime.SetTime(gralasttime.nYear,gralasttime.nMonth,gralasttime.nDay, gralasttime.nHour,gralasttime.nMinute,gralasttime.nSecond);
		graLib->lasttimemark = tmpTime.GetTime();
	}
	miaoshu->CloseSQL();
	return ret;
}

/*===================================================================
* ��������:	����ͼ��
*
* �������: ͼ�ο�ṹsGraLibrary
*
* �������: ��
*
* ����ֵ : �ɹ�����TRUE,ʧ�ܷ���FALSE
*
* ��������: �޸�ͼ�ο��
===================================================================*/
Jint32 CMSData::CheckInGra(sGraLibrary *graLib)
{
	if (graLib == NULL)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	STimeInfo gratime = ConvertTime(graLib->timemark);

	CIIString strSql;
	strSql.Format("where graname='%s'", graLib->graname);

	Jint32 nFetchData = IsRecordExist("gralibrary", strSql.GetBuf());
	if( nFetchData != DB_SUCCESS )
	{
		CIIString strError;
		strError.Format("ͼ��%sû�м��,��˲��ܼ��룡",graLib->graname);
		gCIILog_msdbcall.Add(strError.GetBuf());
		return DB_NO_DATA_FOUND;
	}
	else
	{
		strSql = "UPDATE GRALIBRARY SET machine=?, renyuan=?,state=?,timemark=?,lastmachine=?,lastrenyuan=?,lasttimemark=? where graname=?";

		miaoshu->PrepareSQL(strSql.GetBuf());
		miaoshu->BindPara(IES_SQL_STRING, 48, graLib->machine);
		miaoshu->BindPara(IES_SQL_USMALLINT, 0, &graLib->renyuan);
		miaoshu->BindPara(IES_SQL_BOOL, 0,		&graLib->state);
		miaoshu->BindPara(IES_SQL_TIMESTAMP, 0, &gratime);
		miaoshu->BindPara(IES_SQL_STRING, 48, graLib->machine);
		miaoshu->BindPara(IES_SQL_USMALLINT, 0, &graLib->renyuan);
		miaoshu->BindPara(IES_SQL_TIMESTAMP, 0, &gratime);
		miaoshu->BindPara(IES_SQL_STRING, 128, graLib->graname);
	}

	if (!miaoshu->Exec())
	{
		CIIString tError = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(tError.GetBuf());
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

	miaoshu->CloseSQL();
	return DB_SUCCESS;
}

/*===================================================================
* ��������:	���ͼ��
*
* �������: ͼ�ο�ṹsGraLibrary
*
* �������: ��
*
* ����ֵ : �ɹ�����TRUE,ʧ�ܷ���FALSE
*
* ��������: �޸�ͼ�ο��
===================================================================*/
Jint32 CMSData::CheckOutGra(sGraLibrary *graLib, bool &bUpdate/*true*/)
{
	CONNECTMSDB();

	if( graLib == NULL )
		return DB_INVALID_PARAM;

	STimeInfo gratime = ConvertTime(graLib->timemark);

	CIIString strSql;
	strSql.Format("where graname='%s'", graLib->graname);

	Jint32 nFetchData = IsRecordExist("gralibrary", strSql.GetBuf());
	if( nFetchData != DB_SUCCESS )
	{
		strSql = "INSERT INTO GRALIBRARY(graname,machine,renyuan,state,timemark,lastmachine,lastrenyuan,lasttimemark) VALUES (?,?,?,?,?,?,?,?)";

		miaoshu->PrepareSQL(strSql.GetBuf());
		miaoshu->BindPara(IES_SQL_STRING, 128, graLib->graname);
		miaoshu->BindPara(IES_SQL_STRING, 48, graLib->machine);
		miaoshu->BindPara(IES_SQL_USMALLINT, 0, &graLib->renyuan);
		miaoshu->BindPara(IES_SQL_BOOL, 0,&graLib->state);
		miaoshu->BindPara(IES_SQL_TIMESTAMP, 0, &gratime);
		miaoshu->BindPara(IES_SQL_STRING, 48, graLib->machine);		//������ͼ�Σ����������ֶ���ǰ���ֶ�������д
		miaoshu->BindPara(IES_SQL_USMALLINT, 0, &graLib->renyuan);
		miaoshu->BindPara(IES_SQL_TIMESTAMP, 0, &gratime);
		bUpdate =false;
	}
	else
	{
		strSql = "UPDATE GRALIBRARY SET machine=?, renyuan=?,state=?,timemark=? where graname=?";

		miaoshu->PrepareSQL(strSql.GetBuf());
		miaoshu->BindPara(IES_SQL_STRING, 48, graLib->machine);		//�Ѿ�����ͼ�Σ����ǰ���������ֶκ�ǰ���ֶ�������һ�µ�
		miaoshu->BindPara(IES_SQL_USMALLINT, 0, &graLib->renyuan);	//ֻ��Ҫ����ǰ����ֶ�
		miaoshu->BindPara(IES_SQL_BOOL, 0,		&graLib->state);
		miaoshu->BindPara(IES_SQL_TIMESTAMP, 0, &gratime);
		miaoshu->BindPara(IES_SQL_STRING, 128, graLib->graname);
	}

	if (!miaoshu->Exec())
	{
		CIIString tError = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(tError.GetBuf());
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

	miaoshu->CloseSQL();
	return DB_SUCCESS;
}

/*===================================================================
* ��������:	�������ͼ��
*
* �������: ͼ�ο�ṹsGraLibrary
*
* �������: ��
*
* ����ֵ : �ɹ�����TRUE,ʧ�ܷ���FALSE
*
* ��������: �޸�ͼ�ο��
===================================================================*/
Jint32 CMSData::unCheckOutGra(sGraLibrary *graLib)
{
	CONNECTMSDB();

	if( graLib == NULL )
		return DB_INVALID_PARAM;

	STimeInfo gratime = ConvertTime(graLib->lasttimemark);

	CIIString strSql;
	strSql.Format("where graname='%s'", graLib->graname);	

	Jint32 nFetchData = IsRecordExist("gralibrary", strSql.GetBuf());
	if( nFetchData != DB_SUCCESS )
	{
		CIIString  strError;
		strError.Format("gralibrary������ͼ��%s��",graLib->graname);
		gCIILog_msdbcall.Add(strError.GetBuf());
		return DB_NO_DATA_FOUND;
	}
	else
	{
		strSql = "UPDATE GRALIBRARY SET machine=?, renyuan=?,state=0,timemark=? where graname=?";

		miaoshu->PrepareSQL(strSql.GetBuf());
		miaoshu->BindPara(IES_SQL_STRING, 48, graLib->lastmachine);
		miaoshu->BindPara(IES_SQL_USMALLINT, 0, &graLib->lastrenyuan);
		miaoshu->BindPara(IES_SQL_TIMESTAMP, 0, &gratime);
		miaoshu->BindPara(IES_SQL_STRING, 128, graLib->graname);
	}

	if (!miaoshu->Exec())
	{
		CIIString tError = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(tError.GetBuf());
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

	miaoshu->CloseSQL();
	return DB_SUCCESS;
}

/*===================================================================
* ��������:	ɾ��ָ��ͼ�ε���Ϣ
*
* �������: char* graname
*
* �������: ��
*
* ����ֵ : �ɹ�����TRUE,ʧ�ܷ���FALSE
*
* ��������: �޸�ͼ�ο��
===================================================================*/
Jint32 CMSData::DelGra(const char *graname)
{
	CONNECTMSDB();

	if( graname == NULL )
		return DB_INVALID_PARAM;

	CIIString strSql;
	strSql.Format("WHERE GRANAME='%s'", graname);	

	Jint32 nFetchData = IsRecordExist("gralibrary", strSql.GetBuf());
	if( nFetchData != DB_SUCCESS )
	{
		return DB_SUCCESS;
	}
	else
	{
		strSql.Format("DELETE FROM GRALIBRARY WHERE GRANAME='%s'",graname);
		miaoshu->PrepareSQL(strSql.GetBuf());
	}

	if (!miaoshu->Exec())
	{
		CIIString tError = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(tError.GetBuf());
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

	miaoshu->CloseSQL();
	return DB_SUCCESS;
}

/*===================================================================
* ��������:	����¼�Ƿ����
*
* �������: ��
*
* �������: ��
*
* ����ֵ : �ɹ�����TRUE,ʧ�ܷ���FALSE
*
* ��������: �鿴ĳ�ű��ڸ����������Ƿ���ڼ�¼
===================================================================*/
Jint32 CMSData::IsRecordExist(const char* szTableName, const char* filter)
{
	CONNECTMSDB();

	CIIString sql;
	Juint32 count=0;
	sql.Format("SELECT COUNT(*) FROM %s %s", szTableName, filter);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UINT, 0, &count);
	//EMS-Mend< dingjide 2009.07.06
	//�޸�ԭ��:�ж�Exec() Fetch()�Ƿ�ɹ�
	//miaoshu->Exec();
	//miaoshu->Fetch();
	if( miaoshu->Exec() <= 0 )
	{
		miaoshu->CloseSQL();
		return DB_DATASOURCE_ERROR;
	}
	if(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		
	}
	else
	{
		miaoshu->CloseSQL();
		return DB_ERROR;
	}
	//EMS-Mend>
	miaoshu->CloseSQL();

	if( count>0 )
		return DB_SUCCESS;
	else
		return DB_NO_DATA_FOUND;
}

/*===================================================================
* ��������:	��time_tת��ΪSTimeInfo
*
* �������: time_t
*
* �������:	�� 
*
* ����ֵ : STimeInfo
*
* ��������: ��time_tת��ΪSTimeInfo
===================================================================*/
STimeInfo CMSData::ConvertTime(const time_t& timemark)
{
	CIITime atime;
	STimeInfo gratime;

	memset(&gratime, 0, sizeof(gratime));
	atime.SetTime(timemark);

	gratime.nYear = atime.GetYear();
	gratime.nMonth = atime.GetMonth();
	gratime.nDay = atime.GetDay();
	gratime.nHour = atime.GetHour();
	gratime.nMinute = atime.GetMinute();
	gratime.nSecond = atime.GetSecond();

	return gratime;
}
//EMS-Mend>


//EMS-Mend<ningfg 2009.12.3
//�������Ʋ���
Jint32 CMSData::SetDMSDeviceParam(const char* tablename, SDeviceParam* pDeviceParam, Jboolean isUpdate)
{
	if( pDeviceParam == NULL )
		return DB_INVALID_PARAM;

	CONNECTMSDB();
	CIIString sql;
	if (isUpdate)
	{
		sql = "update ";
		sql += tablename;
		sql += " set ChangZhanID=?,ProdType=?,GBType=?,Length=?,EDFreq=?,Changjia=?,ShebeiZhuren=?,AnZhuangDidian=?,TouYunDate=?,ShebeiZhaopian = ? where id=?";
	}
	else
	{
		sql = "insert into ";
		sql += tablename;
		sql += "(ChangZhanID,ProdType,GBType,Length,EDFreq,Changjia,ShebeiZhuren,AnZhuangDidian,TouYunDate,ShebeiZhaopian,ID) VALUES(?,?,?,?,?,?,?,?,?,?,?)";
	}
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindPara(SQL_DATAID_TYPE,0,&pDeviceParam->changzhanID);
	miaoshu->BindPara(IES_SQL_STRING,NAMELEN,pDeviceParam->szProdName);
	miaoshu->BindPara(IES_SQL_STRING,48,pDeviceParam->szProdType);
	miaoshu->BindPara(IES_SQL_FLOAT,0,&pDeviceParam->fLength);
	miaoshu->BindPara(IES_SQL_FLOAT,0,&pDeviceParam->fCapacity);
	miaoshu->BindPara(IES_SQL_STRING,48,pDeviceParam->szChangjia);
	miaoshu->BindPara(IES_SQL_STRING,48,pDeviceParam->szShebeizhuren);
	miaoshu->BindPara(IES_SQL_STRING,48,pDeviceParam->szAnzhuangdidian);
	miaoshu->BindPara(IES_SQL_TIMESTAMP,0,&pDeviceParam->tTouyunriqi);
	miaoshu->BindPara(IES_SQL_BINARY,2000,pDeviceParam->sShebeiPicture);
	miaoshu->BindPara(SQL_DATAID_TYPE,0,&pDeviceParam->wID);
	
	int ret = miaoshu->Exec();
	ret = miaoshu->GetErrorNo();
	sql = miaoshu->GetErrorStr();
	miaoshu->CloseSQL();
	return ret;
}

// ��ȡ�б��IDSTRING��Ϣ
bool CMSData::GetStaticListInfo(Juint16 nType, map<Juint16,CIIString> &mapIDString)
{
	CONNECTMSDB();
	CIIString sql = "SELECT ID, Explain FROM StaticListInfo WHERE ListID = ? ORDER BY ID";
	Juint16 nID;
	char szMingZi[48];
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &nID);
	miaoshu->BindCol(IES_SQL_STRING, 48, szMingZi);
	miaoshu->BindPara(IES_SQL_USMALLINT, 0, &nType);	

	if ( !miaoshu->Exec() )
	{
		CIIString strError = miaoshu->GetErrorStr();
		miaoshu->CloseSQL();
		return false;
	}
	mapIDString.clear();
	while ( miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		mapIDString[nID] = CIIString(szMingZi);
	}
	
	miaoshu->CloseSQL();
	return true;
}

Jint32 CMSData::GetDeviceParam( const Jchar* tabName, SDeviceParam* pdeviceParam )
{
	if(tabName == NULL)
	{
		return DB_ERROR;
	}

	CONNECTMSDB();

	CIIString sql;
	Juint32 ret=0;
	sql.Format("SELECT ChangZhanID,ProdType,GBType,Length,EDFreq,Changjia,ShebeiZhuren,AnZhuangDidian,\
			   TouYunDate,ShebeiZhaopian FROM %s where ID = %d", tabName, pdeviceParam->wID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &pdeviceParam->changzhanID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pdeviceParam->szProdName);
	miaoshu->BindCol(IES_SQL_STRING, 48, pdeviceParam->szProdType);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pdeviceParam->fLength);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pdeviceParam->fCapacity);
	miaoshu->BindCol(IES_SQL_STRING, 48, &pdeviceParam->szChangjia);
	miaoshu->BindCol(IES_SQL_STRING, 48, &pdeviceParam->szShebeizhuren);
	miaoshu->BindCol(IES_SQL_STRING, 48, &pdeviceParam->szAnzhuangdidian);
	miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, &pdeviceParam->tTouyunriqi);
	miaoshu->BindCol(IES_SQL_BINARY, 2000, pdeviceParam->sShebeiPicture);

	if( miaoshu->Exec() <= 0 )
	{
		miaoshu->CloseSQL();
		return DB_DATASOURCE_ERROR;
	}
	if(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		ret = 1;
	}
	else
	{
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

	miaoshu->CloseSQL();

	if( 1 == ret )
		return DB_SUCCESS;
	else
		return DB_NO_DATA_FOUND;
}

Jint32 CMSData::DeleteDeviceParam( const Jchar* tabName, SDeviceParam* pdeviceParam )
{
	if(tabName == NULL)
	{
		return DB_SUCCESS;
	}

	CONNECTMSDB();
	CIIString sql;
	CIIString sqlWhere;
	sql = "delete from ";
	sql += tabName;
	sqlWhere.Format(" where ID = %d",pdeviceParam->wID);
	sql += sqlWhere;
	miaoshu->PrepareSQL(sql.GetBuf());
	int ret = miaoshu->Exec();
	miaoshu->CloseSQL();
	return (ret > 0 ? DB_SUCCESS : DB_ERROR);
}

// DMS-MEND< zhangjq, 2010.3.17 17:06
// �޸�ԭ�򣺻�ȡ��������������Ϣ�����벿�����ͺͲ���ID����������������Ϣ
Jint32 CMSData::GetFeederInfo(Juint8 byBJLX, DATAID_TYPE wBJID, FeederParam* pFeederParam)
{
	if( byBJLX <= 0 || wBJID <= 0 )
	{
		return DB_ERROR;
	}
	Jchar* tabName  = NULL;
	// ����������Ӷ������豸���͵Ĵ���
	switch ( byBJLX )
	{
	case DMSTransformer_ID:          //����ѹ��
		tabName = "transformer";
		break;
	}
	if ( NULL == tabName )
	{
		return DB_ERROR;
	}

	CONNECTMSDB();
	CIIString sql;
	Juint32 ret=0;

	sql.Format("SELECT a.ID,a.MingZi,a.ChangZhanID \
			   FROM feeder a,%s b where a.ID = b.feederID and b.ID=%d", tabName, wBJID );
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &pFeederParam->wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pFeederParam->szFeederName);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &pFeederParam->changzhanID);
	if( miaoshu->Exec() <= 0 )
	{
		miaoshu->CloseSQL();
		return DB_DATASOURCE_ERROR;
	}
	if(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		ret = 1;
	}
	else
	{
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

	miaoshu->CloseSQL();

	if( 1 == ret )
		return DB_SUCCESS;
	else
		return DB_NO_DATA_FOUND;
}
// DMS-MEND>

// EMS-MEND< ningfg, 2010.3.8 9:51
// �޸�ԭ��ע����뱻ע���
Jint32 CMSData::SetInjectionNodeInfo(SInjectionNodeInfo* pNodeInfo)
{
	CONNECTMSDB();
	CIIString sql;
	sql = "insert into InjectionInfo(ChangZhanID,FieldTypeID,FieldID,PortNo,LineSide,Name,PortNode) VALUES(?,?,?,?,?,?,?)";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindPara(SQL_DATAID_TYPE,0,&pNodeInfo->wChangZhanID);
	miaoshu->BindPara(IES_SQL_USMALLINT,0,&pNodeInfo->nFieldTypeID);
	miaoshu->BindPara(IES_SQL_USMALLINT,0,&pNodeInfo->nFieldID);
	miaoshu->BindPara(IES_SQL_UTINYINT,0,&pNodeInfo->nPortNo);
	miaoshu->BindPara(IES_SQL_USMALLINT,0,&pNodeInfo->lineSide);
	miaoshu->BindPara(IES_SQL_STRING,NAMELEN,pNodeInfo->szMingZi);
	miaoshu->BindPara(SQL_DATAID_TYPE,0,&pNodeInfo->nPortNode);
	int ret = miaoshu->Exec();
	miaoshu->CloseSQL();
	return ret;
}

Jint32 CMSData::GetInjectionNodeInfo(SInjectionNodeInfo* pNodeInfo)
{
	CONNECTMSDB();
	CIIString sql;
	sql = " ";
	sql.Format("select PortNode from InjectionInfo where ChangZhanID=%d and FieldTypeID=%d and FieldID=%d and PortNo=%d and LineSide=%d",pNodeInfo->wChangZhanID,pNodeInfo->nFieldTypeID,pNodeInfo->nFieldID,pNodeInfo->nPortNo,pNodeInfo->lineSide);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE,0,&pNodeInfo->nPortNo);
	miaoshu->Exec();
	Jint32 ret = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
	if(ret != DB_SUCCESS)
	{
		CIIString error = miaoshu->GetErrorStr();
	}	
	miaoshu->CloseSQL();
	return ret;
}

Jint32 CMSData::DelInjectionNodeInfo(SInjectionNodeInfo* pNodeInfo)
{
	Jint32 ret = DB_ERROR;
	CONNECTMSDB();
	CIIString sql;
	sql.Format("delete from InjectionInfo where ChangZhanID=%d and FieldTypeID=%d and FieldID=%d and PORTNO = %d and LINESIDE = %d",pNodeInfo->wChangZhanID,pNodeInfo->nFieldTypeID,pNodeInfo->nFieldID,pNodeInfo->nPortNo,pNodeInfo->lineSide);
	if(miaoshu->PrepareSQL(sql.GetBuf()))
	{
		ret = miaoshu->Exec();
		miaoshu->CloseSQL();
		ret = ret > 0 ? DB_SUCCESS : DB_ERROR;
	}
	return ret;
}

Jint32 CMSData::UpdateInjectionNodeName(SInjectionNodeInfo* pNodeInfo)
{
	CONNECTMSDB();
	CIIString sql = "update InjectionInfo set NAME = ? where CHANGZHANID = ? and FIELDTYPEID = ? and FIELDID = ? and PORTNO = ? and LINESIDE = ?";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindPara(IES_SQL_STRING,NAMELEN,pNodeInfo->szMingZi);
	miaoshu->BindPara(SQL_DATAID_TYPE,0,&pNodeInfo->wChangZhanID);
	miaoshu->BindPara(IES_SQL_USMALLINT,0,&pNodeInfo->nFieldTypeID);
	miaoshu->BindPara(IES_SQL_USMALLINT,0,&pNodeInfo->nFieldID);
	miaoshu->BindPara(IES_SQL_UTINYINT,0,&pNodeInfo->nPortNo);
	miaoshu->BindPara(IES_SQL_USMALLINT,0,&pNodeInfo->lineSide);
	int ret = miaoshu->Exec();
	miaoshu->CloseSQL();
	return ret;
}

Jint32 CMSData::updateDWTopoPort(DATAID_TYPE changzhanid, Juint16 fieldtype, Juint16 fieldid, Juint8 portid, Juint32 portnum)
{
	CONNECTMSDB();
	CIIString sql = "update dwtopoport set PNODEID = ? where CHANGZHANID = ? and FIELDTYPEID = ? and FIELDID = ? and NODEID = ?";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindPara(IES_SQL_INT,0,&portnum);
	miaoshu->BindPara(SQL_DATAID_TYPE,0,&changzhanid);
	miaoshu->BindPara(IES_SQL_USMALLINT,0,&fieldtype);
	miaoshu->BindPara(IES_SQL_USMALLINT,0,&fieldid);
	miaoshu->BindPara(IES_SQL_UTINYINT,0,&portid);
	int ret = miaoshu->Exec();
	CIIString error = miaoshu->GetErrorStr();
	miaoshu->CloseSQL();
	return ret;
}
// EMS-MEND>

Jint32 CMSData::updateBaoDianTime(DATAID_TYPE bjid,STimeInfo* tmpTime)
{
	CONNECTMSDB();
	CIIString sql = "update transformer set BDTime = ? where ID = ?";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindPara(IES_SQL_TIMESTAMP, 0,	tmpTime);	
	miaoshu->BindPara(SQL_DATAID_TYPE,0,&bjid);
	int ret = miaoshu->Exec();
	miaoshu->CloseSQL();
	return ret;
}

// EMS-MEND< baizy, 2010.7.13 // �޸�ԭ���Զ���������ID
Jint32 CMSData::GetFeederID(Juint8 byBJLX, DATAID_TYPE wBJID, DATAID_TYPE& nFeederID)
{
	CONNECTMSDB();
	CIIString sql;
	nFeederID = 0;
	switch(byBJLX)
	{
	case KaiGuan_ID:
		sql.Format("select FeederID from kaiguan where ID = %d", wBJID);
		break;
	case DaoZha_ID:
		sql.Format("select FeederID from daozha where ID = %d", wBJID);
		break;
	case DMSTransformer_ID:
		sql.Format("select FeederID from transformer where ID = %d", wBJID);
		break;
	case DMSFeederSection_ID:
		sql.Format("select FeederID from feedersection where ID = %d", wBJID);
		break;
	default:
		return DB_INVALID_PARAM;
	}
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE,0,&nFeederID);
	int ret = miaoshu->Exec();
	ret = miaoshu->Fetch();
	miaoshu->CloseSQL();
	return ret;
}
Jint32 CMSData::SetFeederID(Juint8 byBJLX, DATAID_TYPE wBJID, DATAID_TYPE nFeederID)
{
	CONNECTMSDB();
	CIIString sql;
	switch(byBJLX)
	{
	case KaiGuan_ID:
		sql.Format("update kaiguan set FeederID = ? where ID = %d", wBJID);
		break;
	case DaoZha_ID:
		sql.Format("update daozha set FeederID = ? where ID = %d", wBJID);
		break;
	case DMSTransformer_ID:
		sql.Format("update transformer set FeederID = ? where ID = %d", wBJID);
		break;
	case DMSFeederSection_ID:
		sql.Format("update feedersection set FeederID = ? where ID = %d", wBJID);
		break;
	default:
		return DB_INVALID_PARAM;
	}
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindPara(SQL_DATAID_TYPE,0,&nFeederID);
	int ret = miaoshu->Exec();
	miaoshu->CloseSQL();
	return ret;
}
//EMS-Mend>

//��ȡ���Ʋ�����Ϣ
Jint32 CMSData::getControlParam(Juint32 ID,std::vector<SDevCtrlInfo>& aControlParam)
{
	CONNECTMSDB();
	SDevCtrlInfo tmpFJCtrl;
	CIIString sql = "select a.BJParam,a.ParamAlias,a.SetValue,a.GroupNo from controlparam a,fengji b where b.fjtypeid = a.fjtypeid and b.id = ?";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &tmpFJCtrl.BJParam);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, tmpFJCtrl.ParamAlias);
	miaoshu->BindCol(IES_SQL_STRING, 16, tmpFJCtrl.strCmdValue);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &tmpFJCtrl.GroupNo);
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &ID);
	tmpFJCtrl.ID = ID;
	if (!miaoshu->Exec())
	{
		miaoshu->CloseSQL();
		return DB_SUCCESS;
	}
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		aControlParam.push_back(tmpFJCtrl);
	}
	miaoshu->CloseSQL();
	return DB_SUCCESS;
}
//��ȡ����ʽ��Ӧ��RTUID�Ͷ�ֵ�����
Jint32 CMSData::getRTUInfo(Juint8 byBJType,Juint16 byBJCS,Juint32 wBJID,Juint32& wRTUID,Juint16& dzOrder)
{
	CONNECTMSDB();
	CIIString	sql;
	//sql.Format("SELECT ID, ChangZhanID,BianHao,FenQi,JiDianXianID FROM FengJi Order by ChangZhanID,ID");

	sql.Format("select wRTUID,wSVGOrder from comfloatdata  where bjlx=%d and bjid=%d and bjcs=%d and wrtuid in (select wrtuid from comrtu where byrtutype=0)",
		byBJType,wBJID,byBJCS);

	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UINT, 0, &wRTUID);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &dzOrder);

	miaoshu->Exec();
	miaoshu->Fetch();
	miaoshu->CloseSQL();

	return DB_SUCCESS;
}

//��ȡ���״̬��ɫ���� 
Jint32 CMSData::GetFJStateColor(Juint16 byTypeID,map<Juint16,QColor>& ColorMap)
{
	CONNECTMSDB();
	CIIString	sql;
	Juint16 nID;
	Jchar strColor[16];

	sql.Format("select ID,ShowColor from FJStateParam  where TypeID=%d",byTypeID);

	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &nID);
	miaoshu->BindCol(IES_SQL_STRING, 16, &strColor);

	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		QColor color;
		color.setNamedColor(QString(strColor));
		ColorMap[nID] = color;
	}
	miaoshu->CloseSQL();

	return DB_SUCCESS;
}


//���÷��״̬��ɫ���� 
Jint32 CMSData::SetFJStateColor(Juint16 byTypeID,map<Juint16,QColor>& ColorMap)
{
	CONNECTMSDB();
	CIIString	strInsertSql,strUpdateSql;
	Juint16 nID;
	Jchar strColor[16];
	std::map<Juint16,QColor>::iterator it;
	for (it = ColorMap.begin(); it != ColorMap.end(); ++it)
	{
		nID = it->first;
		strcpy(strColor,it->second.name().local8Bit().data());
		strInsertSql = "Insert Into FJStateParam(TypeID,ID,ShowColor) Values(?,?,?)";

		miaoshu->PrepareSQL(strInsertSql.GetBuf());
		miaoshu->BindPara(IES_SQL_UTINYINT, 0, &byTypeID);
		miaoshu->BindPara(IES_SQL_USMALLINT, 0, &nID);
		miaoshu->BindPara(IES_SQL_STRING, 16, &strColor);

		if (!miaoshu->Exec())
		{
			miaoshu->CloseSQL();
			strUpdateSql = "Update FJStateParam Set ShowColor = ? Where TypeID = ? and ID = ?";

			miaoshu->PrepareSQL(strUpdateSql.GetBuf());
			miaoshu->BindPara(IES_SQL_STRING, 16, strColor);
			miaoshu->BindPara(IES_SQL_UTINYINT, 0, &byTypeID);
			miaoshu->BindPara(IES_SQL_USMALLINT, 0, &nID);

			if (!miaoshu->Exec())
			{
				miaoshu->CloseSQL();
				return DB_ERROR;
			}	
		}
	}
	return DB_SUCCESS;
}