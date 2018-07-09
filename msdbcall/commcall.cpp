///////////////////////////////////////////////////////////////////////////////
#include <qdatetime.h>
#include <qsqlcursor.h>
#include "iessbmix.h"
#include "dbdefine.h"
#include "msdbcall.h"
#include "iescommon.h"//baizy�� 2008.8.12, �����Ʊ��޵��ƵĴ���

// ----------------------------------------------------------------------------
// ���ļ��ṩ����������ĸ��ֳ��ú���������ͼ���˻��ӿڽ���ʹ��
// ----------------------------------------------------------------------------
extern CIILog		gCIILog_msdbcall;

MapBJLX2BJCS CMSData::s_mapMsBjlx2Bjcs;
MapBJLX2BJCS CMSData::s_mapLsBjlx2Bjcs;
MapBuJianLeiXing CMSData::s_mapBjlx;
map<Juint8,map<DATAID_TYPE,SBjMs> > CMSData::s_mapBujian;

//=============================================================================
// ��������
//=============================================================================

Jint32 CMSData::GetSubNet(AChangZhan* arSubNet)
{
	if (arSubNet == NULL)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	miaoshu->PrepareSQL("SELECT ID, MingZi FROM SubNet_EMS ORDER BY MingZi");
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJian.wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJian.szMingZi);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arSubNet->push_back(m_stBuJian);
	}
	miaoshu->CloseSQL();
	
	return arSubNet->size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}

// EMS-Mend< ���»� 2007.5.30 14:42
//=============================================================================
// ������װ�����ͱ�
//=============================================================================
Jint32	CMSData::GetBHZZLeiXing(ABuJian* arZZLeiXing)
{
	if (arZZLeiXing == NULL)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	miaoshu->PrepareSQL("SELECT ID, MingZi FROM ZhuangZhiLeiXing ORDER BY ID");
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJian.wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJian.szMingZi);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arZZLeiXing->push_back(m_stBuJian);
	}
	miaoshu->CloseSQL();
	
	return arZZLeiXing->size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
} 
// EMS-Mend>

//=============================================================================
// ����վ��
// Input : �ṹ����ָ��
// Date: 2002.10.25
//=============================================================================
Jint32 CMSData::GetChangZhan(AChangZhan* arChangZhan, DATAID_TYPE nSubNet)
{
	if (arChangZhan == NULL)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	CIIString sql;
	if (nSubNet == 0)
		sql = "SELECT ID, MingZi FROM ChangZhan ORDER BY MingZi";
	else
		sql.Format("SELECT ID, MingZi FROM ChangZhan WHERE SubNetID=%d ORDER BY MingZi", nSubNet);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJian.wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJian.szMingZi);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arChangZhan->push_back(m_stBuJian);
	}
	miaoshu->CloseSQL();

	return arChangZhan->size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}


//=============================================================================
// ���ͺű�
// Input : �ṹ����ָ��
// Date: 2016.1.09
//=============================================================================
Jint32 CMSData::GetXingHao(AChangZhan* arXingHao)
{
	SBuJian			m_stBuJian;
	if (arXingHao == NULL)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	CIIString sql;
	sql = "SELECT ID, MingZi FROM XingHao ORDER BY MingZi";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJian.wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJian.szMingZi);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arXingHao->push_back(m_stBuJian);
	}
	miaoshu->CloseSQL();

	return arXingHao->size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}


//=============================================================================
// ������������
// Input : �ṹ����ָ��, ��������ID
// Date: 2002.10.25
//=============================================================================
Jint32 CMSData::GetBuJianCanShu(ABuJianCanShu* arBuJianCanShu, Juint8 byBuJianLeiXingID,Juint16 byRDType,bool validFlag, Juint8 byDType)
{
	CIIString	sql, filter;
	if (!arBuJianCanShu || INVALIDTYPE(byBuJianLeiXingID))
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	arBuJianCanShu->clear();
	sql = "SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=? ";
	if (byDType != 0)
	{
		sql += " and DType=? ";
	}
	if (byRDType != 0)
	{
		sql += " and RDType=? ";
	}
	if (validFlag)
	{
		sql += " and isValid = 1 ";
	}

	sql += " ORDER BY ID ";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &m_stBuJianCanShu.byID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, m_stBuJianCanShu.szMingZi);
	miaoshu->BindCol(IES_SQL_UTINYINT,0,&m_stBuJianCanShu.byDType);
	miaoshu->BindCol(IES_SQL_USMALLINT,0,&m_stBuJianCanShu.byRDType);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &m_stBuJianCanShu.isValid);
	
	miaoshu->BindPara(IES_SQL_UTINYINT,0,&byBuJianLeiXingID);
	if (byDType != 0)
	{
		miaoshu->BindPara(IES_SQL_UTINYINT,0,&byDType);
	}
	if (byRDType != 0)
	{
		miaoshu->BindPara(IES_SQL_USMALLINT,0,&byRDType);
	}
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arBuJianCanShu->push_back(m_stBuJianCanShu);
	}
	miaoshu->CloseSQL();
	
	return arBuJianCanShu->size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}



Jint32 CMSData::GetBuJianCanShu(int nMeaType,ABuJianCanShu* arBuJianCanShu, Juint8 byBuJianLeiXingID, bool validFlag)
{
	CIIString	sql, filter;
	if (!arBuJianCanShu || INVALIDTYPE(byBuJianLeiXingID))
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	arBuJianCanShu->clear();
	switch(nMeaType)
	{
	case ALL://ALL����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d ", 
			byBuJianLeiXingID);
		break;
	case YCCS://YC����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType = %d ", 
			byBuJianLeiXingID,RYC);
		break;
	case YXCS://YX����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType = %d ", 
			byBuJianLeiXingID,RYX);
		break;
	case DDCS://DD����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType IN (%d,%d,%d,%d) ", 
			byBuJianLeiXingID,RDDMIN,RDDHOUR,RDDDAY,RDDSD);
		break;
	case TJCS://TJ����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType IN (%d) ", 
			byBuJianLeiXingID,RTJ);
		break;
	case YCDD://YC��DD����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType IN (%d,%d,%d,%d,%d,%d) ", 
			byBuJianLeiXingID,RYC,RDDWIN,RDDMIN,RDDHOUR,RDDDAY,RDDSD);
		break;
	case ALLMEAS://ALLMEAS����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType IN (%d,%d,%d,%d,%d,%d,%d,%d,%d1,2,4,8,16,32,64,128,256) ", 
			byBuJianLeiXingID,RYC,RYX,RDDWIN,RDDMIN,RDDHOUR,RDDDAY,RDDSD,RJH,ROL);
		break;
	}

	if (validFlag)
	{
		sql += " AND isValid = 1 ";
	}

	sql += " ORDER BY ID ";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &m_stBuJianCanShu.byID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, m_stBuJianCanShu.szMingZi);
	miaoshu->BindCol(IES_SQL_UTINYINT,0,&m_stBuJianCanShu.byDType);
	miaoshu->BindCol(IES_SQL_USMALLINT,0,&m_stBuJianCanShu.byRDType);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &m_stBuJianCanShu.isValid);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arBuJianCanShu->push_back(m_stBuJianCanShu);
	}
	miaoshu->CloseSQL();

	return arBuJianCanShu->size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}



Jint32	CMSData::GetBuJianCanShu(MapBuJianCanShu& mapBuJianCanShu, Juint8 byBuJianLeiXingID, Juint16 byRDType, bool validFlag)
{
	CIIString	sql, filter;
	if (INVALIDTYPE(byBuJianLeiXingID))
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	mapBuJianCanShu.clear();
	if (byRDType == 0)
	{
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d ", 
			byBuJianLeiXingID);
	}
	else
	{
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType=%d ", 
			byBuJianLeiXingID, byRDType);
	}

	if (validFlag)
	{
		sql += " AND isValid = 1 ";
	}

	sql += " ORDER BY ID ";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &m_stBuJianCanShu.byID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, m_stBuJianCanShu.szMingZi);
	miaoshu->BindCol(IES_SQL_UTINYINT,0,&m_stBuJianCanShu.byDType);
	miaoshu->BindCol(IES_SQL_USMALLINT,0,&m_stBuJianCanShu.byRDType);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &m_stBuJianCanShu.isValid);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		mapBuJianCanShu[m_stBuJianCanShu.byID] = m_stBuJianCanShu;
	}
	miaoshu->CloseSQL();

	return mapBuJianCanShu.size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}


Jint32	CMSData::GetBuJianCanShu(int nMeaType,MapBuJianCanShu& mapBuJianCanShu, Juint8 byBuJianLeiXingID, bool validFlag)
{
	CIIString	sql, filter;
	if (INVALIDTYPE(byBuJianLeiXingID))
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	mapBuJianCanShu.clear();
	switch(nMeaType)
	{
	case ALL://ALL����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d ", 
			byBuJianLeiXingID);
		break;
	case YCCS://YC����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType = %d ", 
			byBuJianLeiXingID,RYC);
		break;
	case YXCS://YX����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType = %d ", 
			byBuJianLeiXingID,RYX);
		break;
	case DDCS://DD����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType IN (%d,%d,%d,%d,%d) ", 
			byBuJianLeiXingID,RDDMIN,RDDHOUR,RDDDAY,RDDSD);
		break;
	case TJCS://TJ����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType IN (%d,%d,%d,%d,%d) ", 
			byBuJianLeiXingID,RTJ);
		break;
	case YCDD://YC��DD����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType IN (%d,%d,%d,%d,%d,%d) ", 
			byBuJianLeiXingID,RYC,RDDWIN,RDDMIN,RDDHOUR,RDDDAY,RDDSD);
		break;
	case ALLMEAS://ALLMEAS����
		sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND RDType IN (%d,%d,%d,%d,%d,%d,%d,%d,%d1,2,4,8,16,32,64,128,256) ", 
			byBuJianLeiXingID,RYC,RYX,RDDWIN,RDDMIN,RDDHOUR,RDDDAY,RDDSD,RJH,ROL);
		break;
	}

	if (validFlag)
	{
		sql += " AND isValid = 1 ";
	}

	sql += " ORDER BY ID ";
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &m_stBuJianCanShu.byID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, m_stBuJianCanShu.szMingZi);
	miaoshu->BindCol(IES_SQL_UTINYINT,0,&m_stBuJianCanShu.byDType);
	miaoshu->BindCol(IES_SQL_USMALLINT,0,&m_stBuJianCanShu.byRDType);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &m_stBuJianCanShu.isValid);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		mapBuJianCanShu[m_stBuJianCanShu.byID] = m_stBuJianCanShu;
	}
	miaoshu->CloseSQL();

	return mapBuJianCanShu.size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}


//=============================================================================
// ������������
// Input : �ṹ����ָ��, ��������ID
// Date: 2002.10.25
//=============================================================================

Jint32 CMSData::GetBuJianCanShu2(ABuJianCanShu* arBuJianCanShu, Juint8 byBuJianLeiXingID, Juint16 byDType)
{
	CIIString	sql, filter;
	if (!arBuJianCanShu || INVALIDTYPE(byBuJianLeiXingID))
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	arBuJianCanShu->clear();
	
	sql.Format("SELECT ID, MingZi,DType,RDType,isValid FROM BuJianCanShu WHERE BJLXID=%d AND DType<>%d ORDER BY ID", 
			byBuJianLeiXingID, byDType);
	
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &m_stBuJianCanShu.byID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, m_stBuJianCanShu.szMingZi);
	miaoshu->BindCol(IES_SQL_UTINYINT,0,&m_stBuJianCanShu.byDType);
	miaoshu->BindCol(IES_SQL_USMALLINT,0,&m_stBuJianCanShu.byRDType);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &m_stBuJianCanShu.isValid);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arBuJianCanShu->push_back(m_stBuJianCanShu);
	}
	miaoshu->CloseSQL();

	return arBuJianCanShu->size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}

//=============================================================================
// ��ĳһ������
// Input : �ṹ����ָ��, ��������ID
// Date: 2002.10.25
//=============================================================================

Jint32 CMSData::GetBuJian(ABuJian* arBuJian, Juint8 byBuJianLeiXingID, DATAID_TYPE wChangZhanID, Juint8 byDianYaDengJiID)
{
	if (!arBuJian || INVALIDTYPE(byBuJianLeiXingID))
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	arBuJian->clear();
	CIIString	sql;
	CIIString   strBiaoMing = GetBiaoMing(byBuJianLeiXingID);
	
	if (byBuJianLeiXingID <= ChangZhan_ID)
	{
		sql.Format("SELECT ID, MingZi FROM %s ORDER BY MingZi", strBiaoMing.GetBuf());
	}
	else
	{
		if (wChangZhanID == 0)
		{
			if (byBuJianLeiXingID == CaiJiDanYuan_ID)
				sql.Format("SELECT wRTUID, strName FROM %s ORDER BY strName", strBiaoMing.GetBuf());
			else
				sql.Format("SELECT ID, MingZi FROM %s ORDER BY MingZi", strBiaoMing.GetBuf());
		}
		else
		{
			if (byDianYaDengJiID == 0)
			{
				if (byBuJianLeiXingID == XianLu_ID)
					sql.Format("SELECT ID, MingZi FROM %s WHERE QiChangZhanID=%d OR ZhChangZhanID=%d ORDER BY MingZi", 
						strBiaoMing.GetBuf(), wChangZhanID, wChangZhanID);
				else
					sql.Format("SELECT ID, MingZi FROM %s WHERE ChangZhanID=%d ORDER BY MingZi", 
						strBiaoMing.GetBuf(), wChangZhanID);
			}
			else
			{
				if (byBuJianLeiXingID == XianLu_ID)
					sql.Format("SELECT ID, MingZi FROM %s WHERE (QiChangZhanID=%d OR ZhChangZhanID=%d) AND DianYaDengJiID=%d ORDER BY MingZi", 
						strBiaoMing.GetBuf(), wChangZhanID, wChangZhanID, byDianYaDengJiID);
				else if(byBuJianLeiXingID == DMSTransformer_ID)
					sql.Format("SELECT ID, MingZi FROM %s WHERE ChangZhanID=%d AND %s=%d ORDER BY MingZi",
					strBiaoMing.GetBuf(), wChangZhanID,
					byBuJianLeiXingID == DMSTransformer_ID ? "GaoDianYaDengJiID":"DiDianYaDengJiID", byDianYaDengJiID);
				//wind-Mend<hujr 2012.06.05
				//else if(byBuJianLeiXingID == DongTaiBuChang_ID)
				//	sql.Format("SELECT ID, MingZi FROM %s WHERE ChangZhanID=%d AND DIANYADENGJIID=%d ORDER BY MingZi",
				//	strBiaoMing.GetBuf(), wChangZhanID, byDianYaDengJiID);
				//wind-Mend>hujr 2012.06.05
				else if(byBuJianLeiXingID == BianYaQi_ID)
					sql.Format("SELECT ID, MingZi FROM %s WHERE ChangZhanID=%d AND GaoYaCeDengJiID=%d ORDER BY MingZi", 
						strBiaoMing.GetBuf(), wChangZhanID,byDianYaDengJiID);
				else
					sql.Format("SELECT ID, MingZi FROM %s WHERE ChangZhanID=%d AND DianYaDengJiID=%d ORDER BY MingZi", 
					strBiaoMing.GetBuf(), wChangZhanID,byDianYaDengJiID);

			}
		}
	}
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJian.wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJian.szMingZi);
	miaoshu->Exec();
	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arBuJian->push_back(m_stBuJian);
	}
	miaoshu->CloseSQL();

	return arBuJian->size() ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ��Ӧ������ ID������
// ��ڣ��������������ӱ������ָ�롢��������
// ���ڣ�����������
// Date: 2002.10.30
//=============================================================================

Jint32 CMSData::GetBuJian(ABuJianPlus* arBuJianPlus, Juint8 byBuJianLeiXingID, DATAID_TYPE wChangZhanID, Juint8 byDianYaDengJiID)
{
	if (!arBuJianPlus || byBuJianLeiXingID <= ChangZhan_ID || byBuJianLeiXingID >= MaxBuJian_ID)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	arBuJianPlus->clear();
	CIIString	sql;
	CIIString   strBiaoMing = GetBiaoMing(byBuJianLeiXingID);
	

	if (wChangZhanID==0)
		sql.Format("SELECT ID, BianHao, MingZi FROM %s ORDER BY %s", strBiaoMing.GetBuf(),
			byBuJianLeiXingID == XianLu_ID ? "QiChangZhanID":"ChangZhanID");
	else if (byDianYaDengJiID==0)
		sql.Format("SELECT ID, BianHao, MingZi FROM %s WHERE %s=%d ORDER BY BianHao", strBiaoMing.GetBuf(),
			byBuJianLeiXingID == XianLu_ID ? "QiChangZhanID":"ChangZhanID", wChangZhanID);
	else
		sql.Format("SELECT ID, BianHao, MingZi FROM %s WHERE %s=%d AND %s=%d ORDER BY BianHao", strBiaoMing.GetBuf(),
			byBuJianLeiXingID == XianLu_ID ? "QiChangZhanID":"ChangZhanID", wChangZhanID,
			byBuJianLeiXingID == BianYaQi_ID ? "GaoYaCeDengJiID":"DianYaDengJiID", byDianYaDengJiID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJianPlus.wID);
	miaoshu->BindCol(IES_SQL_STRING, BIANHAOLEN, m_stBuJianPlus.szBianHao);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJianPlus.szMingZi);
	miaoshu->Exec();
	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arBuJianPlus->push_back(m_stBuJianPlus);
	}
	miaoshu->CloseSQL();
	
	return arBuJianPlus->size() ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//===============================================================================================
// ȡ��Ӧ������ ID�����֡�רΪң��ʱ������������ʱʹ�á����Ӹ���ң�ؿɿ���ѡ��(0=���ɿ�; 1���ɿ�)
// Date: 2005.10.21
// �㶫�ݶ�
//===============================================================================================
Jint32	CMSData::GetKeKongBuJian(ABuJian* arBuJian, Juint8 byBuJianLeiXingID, Juint8 byKeKong, DATAID_TYPE wChangZhanID, Juint8 byDianYaDengJiID)
{
	if (!arBuJian || INVALIDTYPE(byBuJianLeiXingID))
		return DB_INVALID_PARAM;
	CONNECTMSDB();
	
	arBuJian->clear();
	CIIString	sql;
	CIIString   strBiaoMing = GetBiaoMing(byBuJianLeiXingID);
	

	if (byBuJianLeiXingID != KaiGuan_ID && byBuJianLeiXingID != DaoZha_ID
		&& byBuJianLeiXingID != BaoHu_ID && byBuJianLeiXingID != BianYaQi_ID
		&& byBuJianLeiXingID != XuNiZHTLiang_ID)
	{
		return DB_NO_DATA_FOUND;
	}
	if (wChangZhanID == 0)
	{
		//sql.Format("SELECT ID, MingZi FROM %s WHERE KeKong=%d ORDER BY MingZi", //EMS-Mend< wgc 2007.10.11 ����ʱ���������,���Ҹ����� 
		sql.Format("SELECT ID, MingZi FROM %s WHERE KeKong=%d ORDER BY bianhao", 
			strBiaoMing.GetBuf(), byKeKong);
	}
	else
	{
		if (byDianYaDengJiID == 0)
		{
			//sql.Format("SELECT ID, MingZi FROM %s WHERE ChangZhanID=%d and KeKong=%d ORDER BY MingZi", //EMS-Mend< wgc 2007.10.11 ����ʱ���������,���Ҹ����� 
			sql.Format("SELECT ID, MingZi FROM %s WHERE ChangZhanID=%d and KeKong=%d ORDER BY bianhao", 
				strBiaoMing.GetBuf(), wChangZhanID, byKeKong);
		}
		else
		{
			//sql.Format("SELECT ID, MingZi FROM %s WHERE ChangZhanID=%d AND %s=%d AND KeKong=%d ORDER BY MingZi", //EMS-Mend< wgc 2007.10.11 ����ʱ���������,���Ҹ����� 
			sql.Format("SELECT ID, MingZi FROM %s WHERE ChangZhanID=%d AND %s=%d AND KeKong=%d ORDER BY bianhao", 
				strBiaoMing.GetBuf(),
				wChangZhanID,
				byBuJianLeiXingID == BianYaQi_ID ? "GaoYaCeDengJiID":"DianYaDengJiID", byDianYaDengJiID,
				byKeKong);
		}
	}
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJian.wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJian.szMingZi);
	miaoshu->Exec();
	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arBuJian->push_back(m_stBuJian);
	}
	miaoshu->CloseSQL();
	
	return arBuJian->size() ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ����ʷ�������ͱ�
// Date: 2002.10.25
//=============================================================================

Jint32 CMSData::GetLiShiLeiXing(ALiShiLeiXing* arLiShiLeiXing)
{
	if (!arLiShiLeiXing)	return DB_INVALID_PARAM;
	CONNECTMSDB();

	arLiShiLeiXing->clear();
	miaoshu->PrepareSQL("SELECT ID, MingZi FROM LiShiLeiXing");
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &m_stLiShiLeiXing.byID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, m_stLiShiLeiXing.szMingZi);
	miaoshu->Exec();
	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arLiShiLeiXing->push_back(m_stLiShiLeiXing);
	}
	miaoshu->CloseSQL();
	
	return arLiShiLeiXing->size() ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ����ʷ���ݲ�����
// Date: 2002.10.25
//=============================================================================

Jint32 CMSData::GetLiShiCanShu(ALiShiCanShu* arLiShiCanShu, Juint8 byLiShiLeiXingID)
{
	if (!arLiShiCanShu)	return DB_INVALID_PARAM;
	CONNECTMSDB();

	arLiShiCanShu->clear();
	CIIString	sql;
	sql.Format("SELECT ID, MingZi FROM LiShiCanShu WHERE lslxID=%d", byLiShiLeiXingID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &m_stLiShiCanShu.byID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, m_stLiShiCanShu.szMingZi);
	miaoshu->Exec();
	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arLiShiCanShu->push_back(m_stLiShiCanShu);
	}
	miaoshu->CloseSQL();
	
	return arLiShiCanShu->size() ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//********************************************************************
//*
//*					ȡ�����������ຯ��
//*
//********************************************************************

// ���������ݷ��ʱ� (���֡���Ҫ˵����Ͷ�����ڡ���������)

SCallParam	CallParam[MAX_CALL_NUM] =
{
	{DianWang_ID, DW_MingZi},					//��������������
	{DianWang_ID, DW_ShuoMing},					//����������˵������

	{ChangZhan_ID, CZ_MingZi},					//��վ������˵������
	{ChangZhan_ID, CZ_ShuoMing},				//��վ������˵������

	{MuXian_ID, MX_MingZi},						//ĸ�߲���������
	{MuXian_ID, MX_ShuoMing},					//ĸ�߲�����˵������

	{XianLu_ID, XL_MingZi},						//��·����������
	{XianLu_ID, XL_ShuoMing},					//��·������˵������

	{KaiGuan_ID, KG_MingZi},					//���ز���������
	{KaiGuan_ID, KG_ShuoMing},					//���ز�����˵������
	{KaiGuan_ID, KG_UsedTime},					//���ز�����Ͷ������
	{KaiGuan_ID, KG_ProdType},					//���ز����ĳ�������

	{DaoZha_ID, DZ_MingZi},						//��բ����������
	{DaoZha_ID, DZ_ShuoMing},					//��բ������˵������
	{DaoZha_ID, DZ_UsedTime},					//��բ������Ͷ������
	{DaoZha_ID, DZ_ProdType},					//��բ�����ĳ�������

	{BaoHu_ID, BH_MingZi},						//��������������
	{BaoHu_ID, BH_ShuoMing},					//����������˵������

	{BianYaQi_ID, BYQ_MingZi},					//��ѹ������������
	{BianYaQi_ID, BYQ_ShuoMing},				//��ѹ��������˵������
	{BianYaQi_ID, BYQ_UsedTime},				//��ѹ��������Ͷ������
	{BianYaQi_ID, BYQ_ProdType},				//��ѹ�������ĳ�������

	{FaDianJi_ID, FDJ_MingZi},					//���������������
	{FaDianJi_ID, FDJ_ShuoMing},				//�����������˵������
	{FaDianJi_ID, FDJ_UsedTime},				//�����������Ͷ������
	{FaDianJi_ID, FDJ_ProdType},				//����������ĳ�������

	{CT_ID, CT_MingZi},							//CT ����������
	{CT_ID, CT_ShuoMing},						//CT ������˵������
	{CT_ID, CT_UsedTime},						//CT ������Ͷ������
	{CT_ID, CT_ProdType},						//CT �����ĳ�������

	{PT_ID, PT_MingZi},							//PT ����������
	{PT_ID, PT_ShuoMing},						//PT ������˵������
	{PT_ID, PT_UsedTime},						//PT ������Ͷ������
	{PT_ID, PT_ProdType},						//PT �����ĳ�������

	{FuHe_ID, FH_MingZi},						//������·����������
	{FuHe_ID, FH_ShuoMing},						//������·������˵������

	{ZhuRu_ID, ZR_MingZi},						//ע����·����������
	{ZhuRu_ID, ZR_ShuoMing},					//ע����·������˵������

	{TiaoXiang_ID, TXJ_MingZi},					//���������������
	{TiaoXiang_ID, TXJ_ShuoMing},				//�����������˵������
	{TiaoXiang_ID, TXJ_UsedTime},				//�����������Ͷ������
	{TiaoXiang_ID, TXJ_ProdType},				//����������ĳ�������

	{JingZhiBuChang_ID, JZBC_MingZi},			//��ֹ����������������
	{JingZhiBuChang_ID, JZBC_ShuoMing},			//��ֹ������������˵������
	{JingZhiBuChang_ID, JZBC_UsedTime},			//��ֹ������������Ͷ������
	{JingZhiBuChang_ID, JZBC_ProdType},			//��ֹ�����������ĳ�������

	{BingLianDianRong_ID, BLDR_MingZi},			//�������ݲ���������������
	{BingLianDianRong_ID, BLDR_ShuoMing},		//�������ݲ�����������˵������
	{BingLianDianRong_ID, BLDR_UsedTime},		//�������ݲ�����������Ͷ������
	{BingLianDianRong_ID, BLDR_ProdType},		//�������ݲ����������ĳ�������

	{ChuanLianDianKang_ID, CLDK_MingZi},		//�����翹������������
	{ChuanLianDianKang_ID, CLDK_ShuoMing},		//�����翹��������˵������
	{ChuanLianDianKang_ID, CLDK_UsedTime},		//�����翹��������Ͷ������
	{ChuanLianDianKang_ID, CLDK_ProdType},		//�����翹�������ĳ�������

	{XuNiDMNLiang_ID, XN_MingZi},				//���ⵥ��ģ��������������
	{XuNiDMNLiang_ID, XN_ShuoMing},				//���ⵥ��ģ����������˵������

	{XuNiSMNLiang_ID, SJXN_MingZi},				//����˫��ģ��������������
	{XuNiSMNLiang_ID, SJXN_ShuoMing},			//����˫��ģ����������˵������

	{XuNiZHTLiang_ID, XNZT_MingZi},				//����״̬������������
	{XuNiZHTLiang_ID, XNZT_ShuoMing},			//����״̬��������˵������
};

//=============================================================================
// ��������ȡ����
// Date : 2002.10.25
//=============================================================================

Jint32 CMSData::GetMiaoShuData(SMiaoShuParam* pMSParam, void* pLSData)
{
	if (!pMSParam) 	return DB_INVALID_PARAM;

	for (Juint16 i=0; i<sizeof(CallParam)/sizeof(SCallParam); i++)
	{
		if (pMSParam->byBuJianLeiXingID==CallParam[i].byBuJianLeiXingID &&
			pMSParam->byBuJianCanShuID==CallParam[i].byBuJianCanShuID)
		{
			CONNECTMSDB();
			return (this->*funGetMiaoShuData[i])(pMSParam, pLSData);
		}
	}

	return DB_INVALID_PARAM;
}

//=============================================================================
// ���ؿ�����
// Date : 2002.10.25
//=============================================================================

Jint32 CMSData::NullData(SMiaoShuParam* pMSParam, void*)
{
	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ�������¼��˵������
// Date : 2002.10.25
//=============================================================================
Jint32 CMSData::Get_ShuoMing(SMiaoShuParam* pMSParam, char* outShuoming)
{
	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT ShuoMing FROM bujianshuoming where bujiantype = %d and bujianid = %d", 
		pMSParam->byBuJianLeiXingID, 
		pMSParam->wBuJianID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, SHUOMINGLEN, outShuoming);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

Jint32 CMSData::Get_ShuoMing_Brand(SMiaoShuParam* pMSParam,char* nBrandcode, char* outShuoming)
{
	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT ShuoMing FROM bujianshuoming where bujiantype = %d and bujianid = %d and brandflag = '%s'", 
		pMSParam->byBuJianLeiXingID, 
		pMSParam->wBuJianID,
		nBrandcode);

	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, SHUOMINGLEN, outShuoming);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ�������¼������
// Date : 2002.10.25
//=============================================================================

Jint32 CMSData::Get_MingZi(SMiaoShuParam* pMSParam, void* pMSData)
{
	CONNECTMSDB();

	CIIString	sql;
	CIIString   strBiaoMing  = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	
	sql.Format("SELECT MingZi FROM %s WHERE ID=%d",
		strBiaoMing.GetBuf(), pMSParam->wBuJianID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pMSData);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

CIIString CMSData::GetBiaoMing(Juint8 byBuJianLeiXingID)
{
	CIIString   strBiaoMing = "";
	if(s_mapBjlx.empty())
	{
		GetBuJianLeiXing(s_mapBjlx);
	}

	MapBuJianLeiXing::iterator it = s_mapBjlx.find(byBuJianLeiXingID);
	if( it != s_mapBjlx.end())
		strBiaoMing = (*it).second.szBiaoMing;

	return strBiaoMing;		
}

//=============================================================================
// ȡ�����豸��Ͷ������
// Date : 2002.10.25
//=============================================================================

Jint32 CMSData::Get_UsedTime(SMiaoShuParam* pMSParam, void* pMSData)
{
	CONNECTMSDB();
	STimeInfo t;// = {1970, 1, 1, 0, 0, 0, 8};
	t.nYear = 1970;
	t.nMonth = 1;
	t.nDay = 1;
	t.nHour = 0;
	t.nMinute = 0;
	t.nSecond = 0;
	t.nFraction = 8;
	memcpy(pMSData, &t, sizeof(STimeInfo));
	CIIString	sql;
	CIIString strBiaoMing = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	sql.Format("SELECT UsedTime FROM %s WHERE ID=%d",
		strBiaoMing.GetBuf(), pMSParam->wBuJianID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, pMSData);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ�����豸�ĳ�������
// Date : 2002.10.27
//=============================================================================

Jint32 CMSData::Get_ProdType(SMiaoShuParam* pMSParam, void* pMSData)
{
	CONNECTMSDB();

	CIIString	sql;
	CIIString strBiaoMing = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	sql.Format("SELECT ProdType FROM %s WHERE ID=%d",
		strBiaoMing.GetBuf(), pMSParam->wBuJianID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, PRODTYPELEN+1, pMSData);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}


//=============================================================================
// ��������д����
// Date : 2003.12.15
//=============================================================================

Jint32 CMSData::SetMiaoShuData(SMiaoShuParam* pMSParam, void* pLSData)
{
	if (!pMSParam) 	return DB_INVALID_PARAM;

	for (Juint16 i=0; i<sizeof(CallParam)/sizeof(SCallParam); i++)
	{
		if (pMSParam->byBuJianLeiXingID==CallParam[i].byBuJianLeiXingID &&
			pMSParam->byBuJianCanShuID==CallParam[i].byBuJianCanShuID)
		{
			CONNECTMSDB();
			return (this->*funSetMiaoShuData[i])(pMSParam, pLSData);
		}
	}

	return DB_INVALID_PARAM;
}

//=============================================================================
// ���ò������¼��˵������
// Date : 2003.12.15
//=============================================================================
//���õ���Աע��
Jint32 CMSData::Set_ShuoMing_Note(SShuoMingParam* pMSParam)
{
    CONNECTMSDB();
    Jint32		retcode;
    CIIString	sql;
    Juint8		byBJType;
    sql.Format("delete from bujianshuoming where bujiantype = %d and bujianid = %d", pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID);
    miaoshu->PrepareSQL(sql.GetBuf());
    retcode = miaoshu->Exec() > 0 ? DB_SUCCESS : DB_ERROR;
    if( pMSParam->szShuoMing[0] == '\0' )
        return DB_SUCCESS;
    sql = "insert into bujianshuoming(bujiantype,bujianid, changzhanid, shuomingtime, opreatename, brandflag, shuoming) values(?,?,?,?,?,?,?)";
    miaoshu->PrepareSQL(sql.GetBuf());
    miaoshu->BindPara(IES_SQL_UTINYINT,	 0,	&pMSParam->byBuJianLeiXingID);
    miaoshu->BindPara(SQL_DATAID_TYPE, 0,	&pMSParam->wBuJianID);
    miaoshu->BindPara(SQL_DATAID_TYPE, 0,	&pMSParam->wChangZhanID);
    miaoshu->BindPara(IES_SQL_TIMESTAMP, 0,	&pMSParam->tTime);	
    miaoshu->BindPara(IES_SQL_STRING,	MINGZILEN,	pMSParam->OpName);	
    miaoshu->BindPara(IES_SQL_STRING,	48,	pMSParam->brandFlag);	
    miaoshu->BindPara(IES_SQL_STRING,	SHUOMINGLEN, pMSParam->szShuoMing);	
    retcode = miaoshu->Exec() > 0 ? DB_SUCCESS : DB_ERROR;
    miaoshu->CloseSQL();
    return retcode;
}

//=============================================================================
// ���ò������¼��˵������
// Date : 2003.12.15
//=============================================================================
//���ù�����Ϣ
Jint32 CMSData::Set_ShuoMing_Brand(SShuoMingParam* pMSParam,bool bOnlyDelete)
{
    CONNECTMSDB();

    Jint32		retcode;
    CIIString	sql;
    Juint8		byBJType;
    sql.Format("delete from bujianshuoming where bujiantype = %d and bujianid = %d and brandflag = '%s'", 
        pMSParam->byBuJianLeiXingID, 
        pMSParam->wBuJianID,
        pMSParam->brandFlag);
    miaoshu->PrepareSQL(sql.GetBuf());
    retcode = miaoshu->Exec() > 0 ? DB_SUCCESS : DB_ERROR;
    if( bOnlyDelete )
        return DB_SUCCESS;

    if ( pMSParam->brandFlag[0] == '\0' )
        strcpy(pMSParam->brandFlag," ");
    if( pMSParam->szShuoMing[0] == '\0' )
        strcpy(pMSParam->szShuoMing," ");

    sql = "insert into bujianshuoming(bujiantype,bujianid, changzhanid, shuomingtime, opreatename, brandflag, shuoming) values(?,?,?,?,?,?,?)";
    miaoshu->PrepareSQL(sql.GetBuf());
    miaoshu->BindPara(IES_SQL_UTINYINT,	 0,	&pMSParam->byBuJianLeiXingID);
    miaoshu->BindPara(SQL_DATAID_TYPE, 0,	&pMSParam->wBuJianID);
    miaoshu->BindPara(SQL_DATAID_TYPE, 0,	&pMSParam->wChangZhanID);
    miaoshu->BindPara(IES_SQL_TIMESTAMP, 0,	&pMSParam->tTime);	
    miaoshu->BindPara(IES_SQL_STRING,	MINGZILEN,	pMSParam->OpName);	
    miaoshu->BindPara(IES_SQL_STRING,	48,	pMSParam->brandFlag);	
    miaoshu->BindPara(IES_SQL_STRING,	SHUOMINGLEN, pMSParam->szShuoMing);	
    retcode = miaoshu->Exec() > 0 ? DB_SUCCESS : DB_ERROR;

    miaoshu->CloseSQL();
    return retcode;
}
//=============================================================================
// ���ݲ������ͺͲ�������IDȡ��������������
// Date : 2002.10.27
// ��������
//=============================================================================
CIIString CMSData::GetBuJianCanShuName(Juint8 bjlxID, Juint16 bjcsID, bool blishi)
{
	CIIString	strName;
	Jchar	name[MINGZILEN+1]={'\0'};
	if (GetBuJianCanShuName(bjlxID, bjcsID, name, blishi)==DB_SUCCESS)
		strName = name;
	return strName;
}

Jint32 CMSData::GetBuJianCanShuName(Juint8 bjlxID, Juint16 bjcsID, Jchar* pszMingZi, bool blishi)
{

	if(blishi)
	{
		if (INVALIDLSTYPE(bjlxID) || bjcsID<=0 || !pszMingZi)			
			return DB_INVALID_HANDLE;
	}
	else
	{
		if (INVALIDTYPE(bjlxID) || bjcsID<=0 || !pszMingZi)			
			return DB_INVALID_HANDLE;
	}

	CONNECTMSDB();

	CIIString	sql;
	SBuJianCanShu sbjcs;
	memset(&sbjcs,0,sizeof(sbjcs));
	Juint8 nTmpBjlx = 0;
	MapBJLX2BJCS * pMapBJLX2BJCS = NULL;
	if(blishi)
	{
		if( s_mapLsBjlx2Bjcs.empty() )
		{
			sql = "SELECT lslxID,ID,MingZi FROM lishicanshu";
			miaoshu->PrepareSQL(sql.GetBuf());
			miaoshu->BindCol(IES_SQL_UTINYINT, 0, &nTmpBjlx);
			miaoshu->BindCol(IES_SQL_UTINYINT, 0, &(sbjcs.byID));
			miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, sbjcs.szMingZi);
			miaoshu->Exec();
			while ( miaoshu->Fetch() && !miaoshu->IsEnd() )
			{
				s_mapLsBjlx2Bjcs[nTmpBjlx][sbjcs.byID] = sbjcs;
				memset(&sbjcs,0,sizeof(sbjcs));
				nTmpBjlx = 0;
			}
			miaoshu->CloseSQL();
		}
		pMapBJLX2BJCS = &s_mapLsBjlx2Bjcs;
	}
	else
	{
		if( s_mapMsBjlx2Bjcs.empty() )
		{
			sql = "SELECT bjlxID,ID,MingZi FROM BuJianCanShu";
			miaoshu->PrepareSQL(sql.GetBuf());
			miaoshu->BindCol(IES_SQL_UTINYINT, 0, &nTmpBjlx);
			miaoshu->BindCol(IES_SQL_USMALLINT, 0, &(sbjcs.byID));
			miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, sbjcs.szMingZi);
			miaoshu->Exec();
			while ( miaoshu->Fetch() && !miaoshu->IsEnd() )
			{
				s_mapMsBjlx2Bjcs[nTmpBjlx][sbjcs.byID] = sbjcs;
				memset(&sbjcs,0,sizeof(sbjcs));
				nTmpBjlx = 0;
			}
			miaoshu->CloseSQL();
		}
		pMapBJLX2BJCS = &s_mapMsBjlx2Bjcs;
	}

	MapBJLX2BJCS::iterator it = pMapBJLX2BJCS->find(bjlxID);
	if (it != pMapBJLX2BJCS->end())
	{
		MapBuJianCanShu& tmpBJCSMap = it->second;
		MapBuJianCanShu::iterator jt = tmpBJCSMap.find(bjcsID);
		if (jt != tmpBJCSMap.end())
		{
			strcpy(pszMingZi,(jt->second).szMingZi);
			return DB_SUCCESS;
		}
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ���ݲ������ͻ�ȡ����
//=============================================================================
Jchar* CMSData::GetBuJianTabName(Juint8 ibjlx)
{
	CIIString strBiaoMing =  GetBiaoMing(ibjlx);
	if(strBiaoMing != "")
		return (Jchar*)strBiaoMing.GetBuf();
	else
		return NULL;
	/*if (ibjlx <= XuNiZHTLiang_ID && ibjlx >= DianWang_ID)
		return BJLXParam[ibjlx].pcBiaoMing;
	else
		return NULL;*/
	
}

//=============================================================================
// ���ݲ������ͺͲ���IDȡ�������֣�1��
// ���: �������͡�����ID
// ���ڣ���������
// Date: 2002.10.27
//=============================================================================

CIIString	CMSData::GetBuJianName(Juint8 bjlxID, DATAID_TYPE bjID)
{
	CIIString	strName;
	Jchar	name[NAMELEN+1];
	if (GetBuJianName(bjlxID, bjID, name)==DB_SUCCESS)
		strName = name;

	return strName;
}

//=============================================================================
// ���ݲ������ͺͲ���IDȡ�������֣�2��
// ���: �������͡�����ID������������ָ��
// ���ڣ����������롢��������ָ��
// Date: 2002.10.27
//=============================================================================

Jint32 CMSData::GetBuJianName(Juint8 bjlxID, DATAID_TYPE bjID, Jchar* pszMingZi)
{
	if (INVALIDTYPE(bjlxID) || bjID<=0 || !pszMingZi)			return DB_INVALID_HANDLE;

	if( !s_mapBujian.empty() )
	{
		map<DATAID_TYPE,SBjMs>::iterator it = s_mapBujian[bjlxID].find(bjID);
		if ( it != s_mapBujian[bjlxID].end() )
		{
			strcpy(pszMingZi,(*it).second.strName.GetBuf());
			return DB_SUCCESS;
		}
	}

	CONNECTMSDB();
	
	CIIString	sql;
	CIIString strBiaoMing = GetBiaoMing(bjlxID);
	if ( bjlxID == CaiJiDanYuan_ID )
	{
		sql.Format("SELECT strname FROM %s WHERE wrtuid=%d", strBiaoMing.GetBuf(), bjID);
	}
	else
	{
		sql.Format("SELECT MingZi FROM %s WHERE ID=%d", strBiaoMing.GetBuf(), bjID);
	}
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pszMingZi);
	miaoshu->Exec();
	if( (miaoshu->Fetch() && !miaoshu->IsEnd()) )
	{
		return DB_SUCCESS;
	}
	else
	{
		return DB_NO_DATA_FOUND;
	}
}

SBjMs CMSData::getBuJianInfo(Juint8 bjlxID, DATAID_TYPE bjID)
{
	if( s_mapBujian.empty() )
		mapAllDevice();
	SBjMs bjms;
	if( !s_mapBujian.empty() )
	{
		map<DATAID_TYPE,SBjMs>::iterator it = s_mapBujian[bjlxID].find(bjID);
		if ( it != s_mapBujian[bjlxID].end() )
		{
			bjms = (*it).second;
		}
	}
	return bjms;
}

Jint32 CMSData::mapAllDevice()
{
	if( s_mapBujian.empty() )
	{
		CONNECTMSDB();
		char szName[NAMELEN];
		char szSQL[512+NAMELEN];
		SBjMs bjms;
		map<DATAID_TYPE,SBjMs> mapBjms;
		Juint8 i = 0;
		Jchar szBiaoMing[NAMELEN+1];
		for( i = DianWang_ID; i< MaxBuJian_ID; i++ )
		{
			mapBjms.clear();
			bjms.initValue();
			Juint8 byBiaoType = i;
			strcpy(szBiaoMing,GetBiaoMing(i).GetBuf());
			if( byBiaoType <= ChangZhan_ID )
			{
				sprintf(szSQL, "SELECT ID,MINGZI FROM %s",szBiaoMing);
				miaoshu->PrepareSQL(szSQL);
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &bjms.nID);
				miaoshu->BindCol(IES_SQL_STRING, NAMELEN, szName);
				miaoshu->Exec();
			}
			else if( byBiaoType == XuNiDMNLiang_ID || byBiaoType == XuNiZHTLiang_ID || byBiaoType == XuNiSMNLiang_ID)
			{
				sprintf(szSQL, "SELECT ID,MINGZI,CHANGZHANID,DYBJType,DYBJID,DYBJParam FROM %s",szBiaoMing);
				miaoshu->PrepareSQL(szSQL);
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &bjms.nID);
				miaoshu->BindCol(IES_SQL_STRING, NAMELEN, szName);
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &bjms.nChangZhanID);
				miaoshu->BindCol(IES_SQL_UTINYINT, 0, &bjms.byBayType);
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &bjms.nBayID);
				miaoshu->BindCol(IES_SQL_USMALLINT, 0, &bjms.byBayParam);
				miaoshu->Exec();
			}
			else
			{
				if ( i == CaiJiDanYuan_ID )
					sprintf(szSQL, "SELECT wrtuid,strname,wChangZhanID FROM %s",szBiaoMing);
				else
					sprintf(szSQL, "SELECT ID,MINGZI,CHANGZHANID FROM %s",szBiaoMing);
				miaoshu->PrepareSQL(szSQL);
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &bjms.nID);
				miaoshu->BindCol(IES_SQL_STRING, NAMELEN, szName);
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &bjms.nChangZhanID);
				miaoshu->Exec();
			}

			while(miaoshu->Fetch() && !miaoshu->IsEnd())
			{
				bjms.strName = szName;
				mapBjms[bjms.nID] = bjms;
				szName[0] = '\0';
				bjms.initValue();
			}
			miaoshu->CloseSQL();
			s_mapBujian[byBiaoType] = mapBjms;
		}
	}
}

SBuJianLeiXing CMSData::getBuJianLeiXing(Juint8 bjlxID)
{

	SBuJianLeiXing bjlx;
	if(s_mapBjlx.empty())
	{
		GetBuJianLeiXing(s_mapBjlx);
	}

	MapBuJianLeiXing::iterator it = s_mapBjlx.find(bjlxID);
	if( it != s_mapBjlx.end())
		bjlx = (*it).second;
	return bjlx;
}
//=============================================================================
// ���ݲ������ͺͲ���IDȡ�������
// ��ڲ���: �������͡�����ID
// Date: 2002.10.27
//=============================================================================

CIIString	CMSData::GetBuJianBianHao(Juint8 bjlxID,DATAID_TYPE bjID)
{
	CIIString	strName;
	Jchar	name[BIANHAOLEN+1];
	if (GetBuJianBianHao(bjlxID, bjID, name)==DB_SUCCESS)
		strName = name;

	return strName;
}

Jint32 CMSData::GetBuJianBianHao(Juint8 bjlxID, DATAID_TYPE bjID, Jchar* pszMingZi)
{
	//	if (INVALIDTYPE(bjlxID) && bjID>0 && pszMingZi)			return DB_INVALID_HANDLE;		//EMS-MEND zhaoxuechen change to next line 2010.5.22 
	if (INVALIDTYPE(bjlxID) || bjID<=0 || !pszMingZi)			return DB_INVALID_HANDLE;

	CONNECTMSDB();

	CIIString	sql;
	CIIString strBiaoMing = GetBiaoMing(bjlxID);
	sql.Format("SELECT BianHao FROM %s WHERE ID=%d", strBiaoMing.GetBuf(), bjID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, BIANHAOLEN+1, pszMingZi);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//EMS-Mend<
//���ѽ� 2006.4.17 ȡ�����������
DATAID_TYPE CMSData::GetComponentNo(Juint8 bjlxID, DATAID_TYPE bjID)
{
	DATAID_TYPE wComponentNo = 0;
	GetComponentNo(bjlxID, bjID, &wComponentNo);	
	return wComponentNo;
}
Jint32 CMSData::GetComponentNo(Juint8 bjlxID, DATAID_TYPE bjID, DATAID_TYPE* ComponentNo)
{
	//	if (INVALIDTYPE(bjlxID) && bjID>0 )			return DB_INVALID_HANDLE;		//EMS-MEND zhaoxuechen change to next line 2010.5.22 
	if (INVALIDTYPE(bjlxID) || bjID<=0)			return DB_INVALID_HANDLE;
	
	CONNECTMSDB();
	
	CIIString	sql;
	sql.Format("SELECT ComponentNo FROM dwtopobujian WHERE ComponentID=%d AND ComponentType=%d", bjID,bjlxID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, ComponentNo);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}
//EMS-Mend>

Jint32 CMSData::GetCompentXNDJDataID(DATAID dataid, DATAID& retDataID )
{
	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT  ID FROM xunidmnliang WHERE DYBJType=%d AND DYBJID=%d AND DYBJParam=%d",
							dataid.byBJType, dataid.wIDValue, dataid.byCSHType);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &retDataID.wIDValue);
	miaoshu->Exec();
	if (miaoshu->Fetch() && !miaoshu->IsEnd()) 
	{
		retDataID.byBJType = XuNiDMNLiang_ID;
		retDataID.byCSHType = XN_XNValue;

		return DB_SUCCESS;
	}
	
	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ�������͵�����
// Date : 2002.10.27
//=============================================================================

CIIString CMSData::GetBaoHuLeiXingMing(Juint16 zzlx, DATAID_TYPE wID)
{
	CIIString	strName;
	Juint8 byDType;
	Jchar	name[NAMELEN+1];
	if (GetBaoHuLeiXingMing(zzlx, wID, name, &byDType)==DB_SUCCESS)
		strName = name;

	return strName;
}

Jint32 CMSData::GetBaoHuLeiXingMing(Juint16 zzlx, DATAID_TYPE wID, Jchar* pszMingZi, Juint8* pbyDType)
{
	if (!pszMingZi || !pbyDType)	return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT MingZi, DType FROM BaoHuLeiXing WHERE zzlx = %d and ID=%d", zzlx, wID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pszMingZi);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ��ֵ���͵�����
// Date : 2002.10.27
//=============================================================================

CIIString CMSData::GetDingZhiLeiXingMing(Juint16 wID )
{
	CIIString	strName;
	Jchar	name[NAMELEN+1];
	if (GetDingZhiLeiXingMing(wID, name)==DB_SUCCESS)
		strName = name;

	return strName;
}

Jint32 CMSData::GetDingZhiLeiXingMing(Juint16 wID, Jchar* pszMingZi )
{
	if (!pszMingZi)	return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT MingZi FROM DingZhiLeiXing WHERE ID=%d", wID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pszMingZi);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ΢�������������͵�����
// Date : 2002.10.27
//=============================================================================

CIIString CMSData::GetGuZhangLeiXingMing(Juint16 wID )
{
	CIIString	strName;
	Jchar	name[NAMELEN+1];
	if (GetGuZhangLeiXingMing(wID, name)==DB_SUCCESS)
		strName = name;

	return strName;
}

Jint32 CMSData::GetGuZhangLeiXingMing(Juint16 wID, Jchar* pszMingZi )
{
	if (!pszMingZi)	return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT MingZi FROM GuZhangLeiXing WHERE ID=%d", wID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pszMingZi);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ΢����������ֵ���͵�����
// Date : 2002.10.27
//=============================================================================

CIIString CMSData::GetYCZhiLeiXingMing(Juint16 wID )
{
	CIIString	strName;
	Jchar	name[NAMELEN+1];
	if (GetYCZhiLeiXingMing(wID, name)==DB_SUCCESS)
		strName = name;

	return strName;
}

Jint32 CMSData::GetYCZhiLeiXingMing(Juint16 wID, Jchar* pszMingZi )
{
	if (!pszMingZi)	return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT MingZi FROM YCZhiLeiXing WHERE ID=%d", wID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pszMingZi);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ΢�������������͵����� WJBHKGLeiXing
// Date : 2002.10.27
//=============================================================================

CIIString CMSData::GetWJBHKGLeiXingMing(Juint16 wID )
{
	CIIString	strName;
	Jchar	name[NAMELEN+1];
	if (GetWJBHKGLeiXingMing(wID, name)==DB_SUCCESS)
		strName = name;

	return strName;
}

Jint32 CMSData::GetWJBHKGLeiXingMing(Juint16 wID, Jchar* pszMingZi )
{
	if (!pszMingZi)	return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT MingZi FROM WJBHKGLeiXing WHERE ID=%d", wID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pszMingZi);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ΢��������������� ComWJBH
// Date : 2002.10.27
//=============================================================================

CIIString CMSData::GetWJBHObj(DATAID_TYPE wRTUID, Juint8 byCabinetID, Juint8 byUnitID)
{
	CIIString	strName;
	Jchar	name[NAMELEN+1];
	if (GetWJBHObj(wRTUID, byCabinetID, byUnitID)==DB_SUCCESS)
		strName = name;

	return strName;
}

Jint32 CMSData::GetWJBHObj(DATAID_TYPE wRTUID, Juint8 byCabinetID, Juint8 byUnitID, Jchar* pszMingZi)
{
	if (!pszMingZi)	return DB_INVALID_PARAM;

	CONNECTMSDB();
	CIIString	sql;
	sql.Format("SELECT MingZi FROM WJBHKGLeiXing WHERE wRTUID=%d AND byCabinetID=%d AND byUnitID=%d", wRTUID, byCabinetID, byUnitID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pszMingZi);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ����ĳ���ո��ɼƻ�ֵ����Ҫ��FuHeJiHua��FuHeJiHuaZhi������
// ��ڣ�����ʽ������
// ������������������¼ƻ�ֵ/������ֵ�����ش���
// Date : 2002.10.27
//=============================================================================
bool CMSData::SetFHJiHuaDensity(SMiaoShuParam* pMSParam, Jint32 m_density)
{
	if(m_density !=15 && m_density !=60)
		m_density =5;
	Jint32 nDensity =0;
	nDensity=GetFHJiHuaDensity(pMSParam, JTRUE);
	if(nDensity ==m_density)
		return true;
	else if (nDensity > 0 && nDensity !=m_density)
	{
		CONNECTMSDB();
		char	sql[128];
		sprintf(sql, "UPDATE FuheJiHua SET Density=%d WHERE BJType=%d and BJID=%d and BJCanShu=%d and ChangZhanID=%d",
			m_density,pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID, pMSParam->wChangZhanID);
		if (miaoshu->ExecuteSQL(sql))
			return true;
	}
	else
		return false;
}
Jint32 CMSData::GetFHJiHuaDensity(SMiaoShuParam* pMSParam, Jboolean bCreate)
{
	if (pMSParam == NULL || INVALIDTYPE(pMSParam->byBuJianLeiXingID))
		return -1;

	CONNECTMSDB();

	Juint8	nDensity = 0;
	char	sql[128],sqltrigger[128];
	sprintf(sql, "SELECT Density FROM FuHeJiHua WHERE BJType=%d AND BJID=%d AND BJCanShu=%d",
		pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID);
	if (miaoshu->PrepareSQL(sql)
		&& miaoshu->BindCol(IES_SQL_UTINYINT, 0, &nDensity)
		&& miaoshu->Exec() > 0)
	{
		if (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			return nDensity;
		}
		else if (bCreate)		// ����Ϊ�գ�����
		{
			sprintf(sql, "INSERT INTO FuheJiHua (BJType,BJID,BJCanShu,ChangZhanID,Density) VALUES (%d,%d,%d,%d,5)",
				pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID, pMSParam->wChangZhanID);
			if (!miaoshu->ExecuteSQL(sql))
				return -1;

			if (miaoshu->GetDBType() == IES_DB_SQLITE)
			{
				if (pMSParam->byBuJianLeiXingID == MuXian_ID)
				{
					int j = 0;
					for (int i = 0; i < 12; i++)
					{
						sprintf(sqltrigger,"INSERT INTO FuHeJiHuaZhi (BJType,BJID,BJCanShu,ChangZhanID,Minute) values(%d,%d,%d,%d,%d)",
							pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID, pMSParam->wChangZhanID, j);
						if (!miaoshu->ExecuteSQL(sqltrigger))
							return -1;
						j += 5;
					}
				}
				else
				{
					for (int k = 0; k < 7; k++)
					{
						int j = 0;
						for (int i = 0; i < 12; i++)
						{
							sprintf(sqltrigger,"INSERT INTO FuHeJiHuaZhi (BJType,BJID,BJCanShu,ChangZhanID,Week,Minute) values(%d,%d,%d,%d,%d,%d)",
								pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID, pMSParam->wChangZhanID, k, j);
							if (!miaoshu->ExecuteSQL(sqltrigger))
								return -1;
							j += 5;
						}
					}
				}
			} 
			
			return 5;
		}
	}

	return -1;
}

//=============================================================================
// ȡ����ĳ���ո��ɼƻ�ֵ����Ҫ��FuHeJiHua��FuHeJiHuaZhi������
// ��ڣ�����ʽ������
// ������������������¼ƻ�ֵ/������ֵ�����ش���
// Date : 2002.10.27
//=============================================================================

Jint32 CMSData::GetFHJiHuaOfWeek(SMiaoShuParam* pMSParam, Juint16 wWeek, void* pUpVal, void* pDnVal,time_t* pJHEndTime)
{
	if (pMSParam == NULL || (pUpVal == NULL && pDnVal == NULL) || INVALIDTYPE(pMSParam->byBuJianLeiXingID) || wWeek > 6)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	Juint8 attr, minute, om1, om2, oldminute;
	Juint16 i=0, j=0;
	Jfloat value[24], *pDatas;

	CIIString sql, field, fieldHour;
	field = "Attribute, Minute";
	for (i=0; i<24; i++)
	{
		fieldHour.Format(", H%d", i);
		field += fieldHour;
	}
	STimeInfo tInfo;
	if (pJHEndTime != NULL)
	{
		*pJHEndTime = 0;
		field += ",JHEndTime";
	}
	sql.Format("SELECT %s FROM FuHeJiHuaZhi WHERE BJType=%d AND BJID=%d AND BJCanShu=%d AND Week=%d",
		field.GetBuf(), pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID, wWeek);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &attr);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &minute);
	for (i=0; i<24; i++)
		miaoshu->BindCol(IES_SQL_FLOAT, 0, value+i);

	if (pJHEndTime != NULL)
	{
		miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, &tInfo);
	}
	miaoshu->Exec();

	om1 = om2 = 0;
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		if (attr == 0)
		{
			pDatas = (Jfloat*)pUpVal;
			oldminute = om1;

			//��ȡ�ƻ���ֹʱ��
			if (pJHEndTime != NULL && *pJHEndTime == 0)
			{
				CIITime tTime;
				tTime.SetTime(tInfo.nYear,tInfo.nMonth,tInfo.nDay,tInfo.nHour,tInfo.nMinute,tInfo.nSecond);
				*pJHEndTime = tTime.GetTime();
			}
		}
		else
		{
			pDatas = (Jfloat*)pDnVal;
			oldminute = om2;
		}
		if (minute%5==0 && pDatas)
		{
			minute /= 5;
			for (i=0; i<24; i++)
			{
				for (j=oldminute+1; j<minute; j++)
					pDatas[i*12 + j] = pDatas[i*12 + oldminute];
				pDatas[i*12 + minute] = value[i];
			}
			if (attr == 0)
				om1 = minute;
			else
				om2 = minute;
		}
	}
	if (pUpVal)
	{
		pDatas = (Jfloat*)pUpVal;
		for (i=0; i<24; i++)
		{
			for (j=om1+1; j<12; j++)
				pDatas[i*12 + j] = pDatas[i*12 + om1];
		}
		pDatas[288] = pDatas[287];	// 289����
	}
	if (pDnVal)
	{
		pDatas = (Jfloat*)pDnVal;
		for (i=0; i<24; i++)
		{
			for (j=om2+1; j<12; j++)
				pDatas[i*12 + j] = pDatas[i*12 + om2];
		}
		pDatas[288] = pDatas[287];	// 289����
	}

	return DB_SUCCESS;
}

//=============================================================================
// ȡ���ո��ɼƻ�ֵ/������ֵ
// ��ڣ�����ʽ
// ������������������¼ƻ�ֵ/������ֵ�����ش���
// Date : 2002.10.28
//=============================================================================

Jint32 CMSData::GetFHJiHua(SMiaoShuParam* pMSParam, void* pUpVal, void* pDnVal,time_t* pJHEndTime /*= NULL*/)//ͬʱ��ȡ�ƻ���ֹʱ��
{
	QDate date = QDate::currentDate();
	return GetFHJiHuaOfWeek(pMSParam, date.dayOfWeek()%7, pUpVal, pDnVal,pJHEndTime);
}

//��ȡ�ƻ���ֹʱ��
Jint32 CMSData::GetJHEndTime(SMiaoShuParam* pMSParam, Juint16 wWeek, Juint16 nAttr,time_t& endtime)
{
	if (pMSParam == NULL || INVALIDTYPE(pMSParam->byBuJianLeiXingID))
		return -1;

	CONNECTMSDB();

	STimeInfo tInfo;
	char	sql[128];
	sprintf(sql, "SELECT JHEndTime FROM FuHeJiHuaZhi WHERE BJType=%d AND BJID=%d AND BJCanShu=%d AND Week=%d AND Attribute=%d",
		pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID, wWeek, nAttr);
	if (miaoshu->PrepareSQL(sql)
		&& miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, &tInfo)
		&& miaoshu->Exec() > 0)
	{
		if (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			CIITime tTime;
			tTime.SetTime(tInfo.nYear,tInfo.nMonth,tInfo.nDay,tInfo.nHour,tInfo.nMinute,tInfo.nSecond);
			endtime =  tTime.GetTime();
			return 0;
		}
		
	}

	return -1;
}

//=============================================================================
// ���ø��ɼƻ�ֵ/������ֵ
// ��ڣ�����ʽ����վ�����ڡ�Ҫд����ֵ
// ���ڣ��Ƿ�д��ɹ��Ĵ���
// Date : 2002.10.28
//=============================================================================
//Wind-Mend<mayan 2012.8.24 ���ɼƻ�ʱ�䴦��,���Ӽƻ���ֹʱ��
//Jint32 CMSData::SetFHJiHuaZhi(SMiaoShuParam* pMSParam, Juint16 wWeek, Juint16 nAttr, void* pVal)
Jint32 CMSData::SetFHJiHuaZhi(SMiaoShuParam* pMSParam, Juint16 wWeek, Juint16 nAttr, void* pVal,time_t endtime)
{
	//ֻ�����ϼƻ�
	if (nAttr == 0)
	{
		time_t oldendtime;
		//��ȡ����ԭ���ļƻ���ֹʱ��
		Jint32 ret = GetJHEndTime(pMSParam,wWeek,nAttr,oldendtime);
		//�����мƻ���ֹʱ������endtime���򲻸��¿��еļƻ���ֹʱ��
		if (ret == 0 && oldendtime > endtime)
		{
			endtime = 0;
		}
	}
	CONNECTMSDB();
	Jint32		retcode = DB_ERROR;
	Juint8		nDataDensity = GetFHJiHuaDensity(pMSParam, JTRUE);
	if (nDataDensity <= 0)			return retcode;

	Jint32	i;
	Juint8	minute;
	Jfloat* pDatas = (Jfloat*)pVal;

	char sql[512], sqlUpdate[300], sqlCol[16], sqlWhere[200], sqlMinute[32];
	strcpy (sqlUpdate, "UPDATE FuHeJiHuaZhi SET ");
	sprintf(sqlWhere, " WHERE BJType=%d AND BJID=%d AND BJCanShu=%d AND Week=%d AND Attribute=%d",
		pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID, wWeek, nAttr);
	sqlCol[0] = '\0';
	for (i=0; i<24; i++)
	{
		sprintf(sqlCol, "H%d=?,", i);
		strcat(sqlUpdate, sqlCol);
	}
	//Wind-Mend<mayan 2012.8.24 ���ɼƻ�ʱ�䴦��
	STimeInfo stEndTime;
	
	if (endtime != 0)
	{
		stEndTime = ii_localtime(&endtime);
		CIIString tmpField;
		tmpField = " JHEndTime=? ";
		strcat(sqlUpdate,tmpField.GetBuf());
	}
	//Wind-Mend<mayan 2012.8.24
	sqlUpdate[strlen(sqlUpdate) - 1] = '\0';	// ������,��

	for (minute=0; minute<60; minute+=nDataDensity)
	{
		sprintf(sqlMinute, " AND Minute=%d", minute);
		sql[0] = '\0';
		strcat(sql, sqlUpdate);
		strcat(sql, sqlWhere);
		strcat(sql, sqlMinute);

		if (miaoshu->PrepareSQL(sql))
		{
			for (i=0; i<24; i++)
				miaoshu->BindPara(IES_SQL_FLOAT, 0, &pDatas[i*12 + minute/5]);
			//Wind-Mend<mayan 2012.8.24 ���ɼƻ�ʱ�䴦��
			if (endtime != 0)
			{
				miaoshu->BindPara(IES_SQL_TIMESTAMP, 0, &stEndTime);
			}
			//Wind-Mend<mayan 2012.8.24
			retcode = miaoshu->Exec() > 0 ? DB_SUCCESS : DB_ERROR;
		}
		miaoshu->CloseSQL();
	}

	return retcode;
}
//=============================================================================
// ���ø��ɼƻ�ֵ/������ֵ(����)
// ��ڣ�����ʽ����վ�����ڡ�Ҫд����ֵ
// ���ڣ��Ƿ�д��ɹ��Ĵ���
// Date : 2002.10.28
//=============================================================================

//Jint32 CMSData::SetFHJiHua1(SMiaoShuParam* pMSParam, Juint16 wWeek, void* pVal,time_t endtime)
//{
//	return SetFHJiHuaZhi(pMSParam, wWeek, 0, pVal,endtime);
//}

//=============================================================================
// ���ø��ɼƻ�ֵ/������ֵ(����)
// ��ڣ�����ʽ����վ�����ڡ�Ҫд����ֵ
// ���ڣ��Ƿ�д��ɹ��Ĵ���
// Date : 2002.10.28
//=============================================================================

//Jint32 CMSData::SetFHJiHua2(SMiaoShuParam* pMSParam, Juint16 wWeek, void* pVal,time_t validtime)
//{
//	return SetFHJiHuaZhi(pMSParam, wWeek, 1, pVal,validtime);
//}

//=============================================================================
// ȡ����������ֵ���ܶ�
// ��ڣ�����ʽ
//=============================================================================
Jint32 CMSData::GetOverLimitCurve(SMiaoShuParam* pMSParam, void* pVal)
{
	if (pMSParam == NULL || pVal == NULL || INVALIDTYPE(pMSParam->byBuJianLeiXingID))
		return DB_INVALID_PARAM;
	
	Jint32 retcode = DB_ERROR;
	Juint8 minute;
	Juint16 i=0;
	Jfloat value[24], *pDatas = (Jfloat*)pVal;
	
	CONNECTMSDB();
	CIIString sql, field, fieldHour;
	field = "Minute";
	for (i=0; i<24; i++)
	{
		fieldHour.Format(", H%d", i);
		field += fieldHour;
	}
	sql.Format("SELECT %s FROM OverLimitValue WHERE BJType=%d AND BJID=%d AND BJCanShu=%d",
		field.GetBuf(), pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &minute);
	for (i=0; i<24; i++)
		miaoshu->BindCol(IES_SQL_FLOAT, 0, value+i);
	if (miaoshu->Exec() > 0)
	{
		while (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			if (minute%5 == 0)
			{
				for (i=0; i<24; i++)
					pDatas[i*12 + minute/5] = value[i];
			}
			retcode = DB_SUCCESS;
		}
		pDatas[288] = pDatas[287];	// 289����
	}
	
	return retcode;
}

//=============================================================================
// ȡ����������ֵ���ܶ�
// ��ڣ�����ʽ
//=============================================================================
Jint32 CMSData::GetOverLimitCurveDensity(SMiaoShuParam* pMSParam, Jboolean bCreate)
{
	Jint32		nDensity = -1;
	if (pMSParam == NULL || INVALIDTYPE(pMSParam->byBuJianLeiXingID))	return nDensity;
	
	
	CONNECTMSDB();
	
	char sql[512];
	sprintf(sql, "SELECT Density FROM OverLimit WHERE BJType=%d AND BJID=%d AND BJCanShu=%d",
		pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID);
	if (miaoshu->PrepareSQL(sql)
		&& miaoshu->BindCol(IES_SQL_UTINYINT, 0, &nDensity)
		&& miaoshu->Exec() > 0)
	{
		if (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			return nDensity;
		}
		else if (bCreate)		// ����Ϊ�գ�����
		{
			sprintf(sql, "INSERT INTO OverLimit (BJType,BJID,BJCanShu,ChangZhanID,Density) VALUES (%d,%d,%d,%d,5)",
				pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID, pMSParam->wChangZhanID);
			if (miaoshu->ExecuteSQL(sql))
				return 5;
		}
	}
	
	return nDensity;
}
//=============================================================================
// ���ñ���������ֵ
// ��ڣ�����ʽ����վ��Ҫд����ֵ
// ���ڣ��Ƿ�д��ɹ��Ĵ���
//=============================================================================
Jint32 CMSData::SetOverLimitCurveZhi(SMiaoShuParam* pMSParam, void* pVal)
{
	CONNECTMSDB();
	Jint32		retcode = DB_ERROR;
	Juint8		nDataDensity = GetOverLimitCurveDensity(pMSParam, JTRUE);
	if (nDataDensity <= 0)
		return retcode;
	
	Jint32	i;
	Juint8	minute;
	Jfloat* pDatas = (Jfloat*)pVal;
	
	char sql[512], sqlUpdate[300], sqlCol[16], sqlWhere[200], sqlMinute[32];
	strcpy (sqlUpdate, "UPDATE OverLimitValue SET ");
	sprintf(sqlWhere, " WHERE BJType=%d AND BJID=%d AND BJCanShu=%d",
		pMSParam->byBuJianLeiXingID, pMSParam->wBuJianID, pMSParam->byBuJianCanShuID);
	sqlCol[0] = '\0';
	for (i=0; i<24; i++)
	{
		sprintf(sqlCol, "H%d=?,", i);
		strcat(sqlUpdate, sqlCol);
	}
	sqlUpdate[strlen(sqlUpdate) - 1] = '\0';	// ������,��
	
	for (minute=0; minute<60; minute+=nDataDensity)
	{
		sprintf(sqlMinute, " AND Minute=%d", minute);
		sql[0] = '\0';
		strcat(sql, sqlUpdate);
		strcat(sql, sqlWhere);
		strcat(sql, sqlMinute);
		
		if (miaoshu->PrepareSQL(sql))
		{
			for (i=0; i<24; i++)
				miaoshu->BindPara(IES_SQL_FLOAT, 0, &pDatas[i * 60/nDataDensity + minute/nDataDensity]);
			retcode = miaoshu->Exec() > 0 ? DB_SUCCESS : DB_ERROR;
			miaoshu->CloseSQL();
		}
	}
	
	return retcode;
}

//=============================================================================
// ������������
//=============================================================================
// ����ֵ������ֵ
Jint32	CMSData::GetOverLimitPoint(SMiaoShuParam* pMSParam, SOverLimit* pOLValue)
{
	if (pMSParam == NULL && pOLValue == NULL)
		return DB_INVALID_PARAM;

	CONNECTMSDB();

	Jint32 retcode = DB_ERROR;
	char sql[256];
	Juint8	bjType		= pMSParam->byBuJianLeiXingID;
	Juint16	bjCanShu	= pMSParam->byBuJianCanShuID;
	DATAID_TYPE	bjID		= pMSParam->wBuJianID;
	GetCorrComp(bjType, bjID, bjCanShu);

	sprintf(sql, "SELECT Limit1Up,Limit1Dn,Limit2Up,Limit2Dn,Limit3Up,Limit3Dn,"
				 "ChRateVal,BJHuiFuQu,OLRec,OLAlarm,OLPrint,OLScr,AlarmDelay "
				 "FROM OverLimit WHERE BJType=%d AND BJID=%d AND BJCanShu=%d",
				 bjType, bjID, bjCanShu);
	
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pOLValue->fOverLimitUp1);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pOLValue->fOverLimitDn1);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pOLValue->fOverLimitUp2);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pOLValue->fOverLimitDn2);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pOLValue->fOverLimitUp3);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pOLValue->fOverLimitDn3);

	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pOLValue->fChRateVal);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pOLValue->fHuiFuQu);

	miaoshu->BindCol(IES_SQL_BOOL, 0, &pOLValue->bOLRec);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &pOLValue->bOLAlarm);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &pOLValue->bOLPrint);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &pOLValue->bOLScr);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &pOLValue->wAlarmDelay);

	if (miaoshu->Exec() > 0)
	{
		retcode = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
		miaoshu->CloseSQL();
	}

	return retcode;
}
Jint32	CMSData::SetOverLimitPoint(SMiaoShuParam* pMSParam, SOverLimit* pOLValue)
{
	if (pMSParam == NULL && pOLValue == NULL)
		return DB_INVALID_PARAM;

	CONNECTMSDB();
	
	Jint32 retcode = DB_ERROR;
	char sql[512];
	Juint8	bjType		= pMSParam->byBuJianLeiXingID;
	Juint16	bjCanShu	= pMSParam->byBuJianCanShuID;
	DATAID_TYPE	bjID		= pMSParam->wBuJianID;
	GetCorrComp(bjType, bjID, bjCanShu);

	sprintf(sql, "Update OverLimit SET Limit1Up=%.3f,Limit1Dn=%.3f,Limit2Up=%.3f,"
				 "Limit2Dn=%.3f,Limit3Up=%.3f,Limit3Dn=%.3f,ChRateVal=%.3f,BJHuiFuQu=%.3f,"
				 "OLRec=%d,OLAlarm=%d,OLPrint=%d,OLScr=%d,AlarmDelay=%d "
				 "WHERE BJType=%d AND BJID=%d AND BJCanShu=%d",
				 pOLValue->fOverLimitUp1, pOLValue->fOverLimitDn1, pOLValue->fOverLimitUp2,
				 pOLValue->fOverLimitDn2, pOLValue->fOverLimitUp3, pOLValue->fOverLimitDn3,
				 pOLValue->fChRateVal, pOLValue->fHuiFuQu, pOLValue->bOLRec, pOLValue->bOLAlarm,
				 pOLValue->bOLPrint, pOLValue->bOLScr, pOLValue->wAlarmDelay,
				 bjType, bjID, bjCanShu );
	miaoshu->PrepareSQL(sql);
	if (miaoshu->Exec() > 0)
	{
		retcode = DB_SUCCESS;
		miaoshu->CloseSQL();
	}
	else	// ���ܲ����ڣ��� insert
	{
		sprintf(sql, "INSERT INTO OverLimit (BJType,BJID,BJCanShu,ChangZhanID,"
					 "Limit1Up,Limit1Dn,Limit2Up,Limit2Dn,Limit3Up,Limit3Dn,"
					 "ChRateVal,BJHuiFuQu,OLRec,OLAlarm,OLPrint,OLScr,AlarmDelay)"
					 " VALUES (%d,%d,%d,%d, %.3f,%.3f,%.3f,%.3f,%.3f,%.3f,"
					 "%.3f,%.3f, %d,%d,%d,%d,%d)",
					 bjType, bjID, bjCanShu, pMSParam->wChangZhanID,
					 pOLValue->fOverLimitUp1, pOLValue->fOverLimitDn1, pOLValue->fOverLimitUp2,
					 pOLValue->fOverLimitDn2, pOLValue->fOverLimitUp3, pOLValue->fOverLimitDn3,
					 pOLValue->fChRateVal, pOLValue->fHuiFuQu, pOLValue->bOLRec, pOLValue->bOLAlarm,
					 pOLValue->bOLPrint, pOLValue->bOLScr, pOLValue->wAlarmDelay );
		if (miaoshu->PrepareSQL(sql) && miaoshu->Exec() > 0)
		{
			retcode = DB_SUCCESS;
		}
		miaoshu->CloseSQL();
	}
	
	return retcode;
}


// ��������ֵĳ��վ������¼
Jint32	CMSData::GetOverLimitPoint(SMiaoShuParam* pMSParam, Juint8& nYCRec)
{
	if (pMSParam == NULL)
		return DB_INVALID_PARAM;
	
	CONNECTMSDB();
	
	Jint32 retcode = DB_ERROR;
	char sql[256];

	int nCount = 0;
	sprintf(sql, "SELECT count(*) FROM OverLimit WHERE OLRec=1 AND ChangZhanID=%d",
			pMSParam->wBuJianID);
	
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(IES_SQL_INT, 0, &nCount);

	if (miaoshu->Exec() > 0)
	{
		retcode = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
		miaoshu->CloseSQL();
	}
	
	if(nCount > 0)
		nYCRec = 1;
	return retcode;
	
}

Jint32	CMSData::SetOverLimitPoint(SMiaoShuParam* pMSParam, Juint8& nYCRec)
{
	if (pMSParam == NULL)
		return DB_INVALID_PARAM;
	
	CONNECTMSDB();
	
	Jint32 retcode = DB_ERROR;
	char sql[256];
	
	sprintf(sql, "UPDATE OverLimit SET OLRec=%d WHERE ChangZhanID=%d",
		nYCRec, pMSParam->wBuJianID);
	
	if (miaoshu->PrepareSQL(sql) && miaoshu->Exec() > 0)
	{
		retcode = DB_SUCCESS;
	}
	miaoshu->CloseSQL();
	
	return retcode;
}

//=============================================================================
// ����ң�ű�������
// ������������
//=============================================================================
Jint32 CMSData::GetWarnParam(SMiaoShuParam* pMSParam, SWarnParam* pParam)
{
	if (pMSParam == NULL && pParam == NULL)
		return DB_INVALID_PARAM;
	
	CONNECTMSDB();
	Jint32 retcode = DB_ERROR;
	char sql[256];
	CIIString strBiaoMing = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	
	switch (pMSParam->byBuJianLeiXingID)
	{
	case KaiGuan_ID:
	case DaoZha_ID:
	case BaoHu_ID:
		sprintf(sql, "SELECT YXChRec,YXChAlarm,YXChPrint,YXChScr,DelayTime FROM %s WHERE ID=%d", 
			strBiaoMing.GetBuf(), pMSParam->wBuJianID);
		break;
	case XuNiZHTLiang_ID:
		sprintf(sql, "SELECT ChRec,ChAlarm,ChPrint,ChScr,DelayTime FROM %s WHERE ID=%d", 
			strBiaoMing.GetBuf(), pMSParam->wBuJianID);
		break;
	default:
		return DB_INVALID_PARAM;
		break;
	}
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &pParam->bWarnRec);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &pParam->bWarnAlarm);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &pParam->bWarnPrint);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &pParam->bWarnGraph);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &pParam->fWarnDelay);
	if (miaoshu->Exec() > 0)
	{
		retcode = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
		miaoshu->CloseSQL();
	}
	
	return retcode;
}
Jint32 CMSData::SetWarnParam(SMiaoShuParam* pMSParam, SWarnParam* pParam)
{
	if (pMSParam == NULL && pParam == NULL)
		return DB_INVALID_PARAM;
	
	CONNECTMSDB();
	Jint32 retcode = DB_ERROR;
	char sql[256];
	CIIString strBiaoMing = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	switch (pMSParam->byBuJianLeiXingID)
	{
	case KaiGuan_ID:
	case DaoZha_ID:
	case BaoHu_ID:
		sprintf(sql, "UPDATE %s SET YXChRec=%d,YXChAlarm=%d,YXChPrint=%d,YXChScr=%d,DelayTime=%.3f WHERE ID=%d", 
			strBiaoMing.GetBuf(), 
			pParam->bWarnRec, pParam->bWarnAlarm, pParam->bWarnPrint, pParam->bWarnGraph, 
			pParam->fWarnDelay, pMSParam->wBuJianID);
		break;
	case XuNiZHTLiang_ID:
		sprintf(sql, "UPDATE %s SET ChRec=%d,ChAlarm=%d,ChPrint=%d,ChScr=%d,DelayTime=%.3f WHERE ID=%d", 
			strBiaoMing.GetBuf(), 
			pParam->bWarnRec, pParam->bWarnAlarm, pParam->bWarnPrint, pParam->bWarnGraph, 
			pParam->fWarnDelay, pMSParam->wBuJianID);
		break;
	default:
		return DB_INVALID_PARAM;
		break;
	}
	miaoshu->PrepareSQL(sql);
	retcode = miaoshu->Exec();
	miaoshu->CloseSQL();	
	retcode = retcode > 0  ? DB_SUCCESS : DB_ERROR;
	
	return retcode;
}
// ��ĳ��վ�Ĳ���������������
Jint32	CMSData::GetWarnParam(SMiaoShuParam* pMSParam, Juint8& nYXChRec)
{
	if (pMSParam == NULL)
		return DB_INVALID_PARAM; 
	
	CONNECTMSDB();
	Jint32 retcode = DB_ERROR;
	char sql[256];
	CIIString strBiaoMing = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	int nCount = 0;
	sprintf(sql, "SELECT count(*) FROM %s WHERE YXChRec=1 AND ChangZhanID=%d", 
		strBiaoMing.GetBuf(), pMSParam->wBuJianID);
	
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &nCount);
	if (miaoshu->Exec() > 0)
	{
		retcode = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
	}
	miaoshu->CloseSQL();
	if( retcode == DB_SUCCESS && nCount > 0)
	{
		nYXChRec = 1;
		return DB_SUCCESS;
	}
	
	sprintf(sql, "SELECT count(*) FROM %s WHERE YXChRec=1 AND ChangZhanID=%d", 
		strBiaoMing.GetBuf(), pMSParam->wBuJianID);
	
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &nCount);
	if (miaoshu->Exec() > 0)
	{
		retcode = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
	}
	miaoshu->CloseSQL();
	if( retcode == DB_SUCCESS && nCount > 0)
	{
		nYXChRec = 1;
		return DB_SUCCESS;
	}
	
	sprintf(sql, "SELECT count(*) FROM %s WHERE YXChRec=1 AND ChangZhanID=%d", 
		strBiaoMing.GetBuf(), pMSParam->wBuJianID);
	
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &nCount);
	if (miaoshu->Exec() > 0)
	{
		retcode = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
		miaoshu->CloseSQL();
	}
	if( retcode == DB_SUCCESS && nCount > 0)
	{
		nYXChRec = 1;
		return DB_SUCCESS;
	}
	
	sprintf(sql, "SELECT count(*) FROM %s WHERE ChRec=1 AND ChangZhanID=%d", 
		strBiaoMing.GetBuf(), pMSParam->wBuJianID);
	
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &nCount);
	if (miaoshu->Exec() > 0)
	{
		retcode = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
		miaoshu->CloseSQL();
	}
	if( retcode == DB_SUCCESS && nCount > 0)
	{
		nYXChRec = 1;
		return DB_SUCCESS;
	}
	
	nYXChRec = 0;
	return DB_SUCCESS;
}

Jint32	CMSData::SetWarnParam(SMiaoShuParam* pMSParam, Juint8& nYXChRec)
{
	if (pMSParam == NULL)
		return DB_INVALID_PARAM;
	
	CONNECTMSDB();
	Jint32 retcode = DB_ERROR;
	char sql[256];
	CIIString strBiaoMing = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	sprintf(sql, "UPDATE %s SET YXChRec=%d WHERE ChangZhanID=%d",
		strBiaoMing.GetBuf(), nYXChRec, pMSParam->wBuJianID);
	miaoshu->PrepareSQL(sql);
	retcode = (miaoshu->Exec() > 0) ? DB_SUCCESS : DB_ERROR;
	miaoshu->CloseSQL();	
	if(retcode != DB_SUCCESS)
		return retcode;
	
	sprintf(sql, "UPDATE %s SET YXChRec=%d WHERE ChangZhanID=%d",
		strBiaoMing.GetBuf(), nYXChRec, pMSParam->wBuJianID);
	miaoshu->PrepareSQL(sql);
	retcode = (miaoshu->Exec() > 0) ? DB_SUCCESS : DB_ERROR;
	miaoshu->CloseSQL();	
	if(retcode != DB_SUCCESS)
		return retcode;
	
	sprintf(sql, "UPDATE %s SET YXChRec=%d WHERE ChangZhanID=%d",
		strBiaoMing.GetBuf(), nYXChRec, pMSParam->wBuJianID);
	miaoshu->PrepareSQL(sql);
	retcode = (miaoshu->Exec() > 0) ? DB_SUCCESS : DB_ERROR;
	miaoshu->CloseSQL();	
	
	sprintf(sql, "UPDATE %s SET ChRec=%d WHERE ChangZhanID=%d",
		strBiaoMing.GetBuf(), nYXChRec, pMSParam->wBuJianID);
	miaoshu->PrepareSQL(sql);
	retcode = (miaoshu->Exec() > 0) ? DB_SUCCESS : DB_ERROR;
	miaoshu->CloseSQL();	
	
	return DB_SUCCESS;
}

//=============================================================================
// ����������Ϣ
//=============================================================================
Jint32 CMSData::GetBrandFlag(SMiaoShuParam* pMSParam, BrandFlag* brandFlag)
{
	if (pMSParam == NULL && brandFlag == NULL)
		return DB_INVALID_PARAM;
	
	CONNECTMSDB();
	Jint32 retcode = DB_ERROR;
	char sql[256];
	CIIString strBiaoMing = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	switch (pMSParam->byBuJianLeiXingID)
	{
	case ChangZhan_ID:						// 5 ��վ��
	case MuXian_ID:							// 6 ĸ�߱�
	case XianLu_ID:							// 7 ��·��
	case KaiGuan_ID:						// 8 ���ر�
	case DaoZha_ID:							// 9 ��բ��
	case BaoHu_ID:							// 10 ������
	case BianYaQi_ID:						// 11 ��ѹ����
	case FaDianJi_ID:						// 12 �������
	case FuHe_ID:							// 13 ���ɱ�
	case TiaoXiang_ID:						// 15 �����
	case JingZhiBuChang_ID:					// 16 ��ֹ������
	case BingLianDianRong_ID:				// 17 �������ݲ�����
	case ChuanLianDianKang_ID:				// 18 �����翹
	case CT_ID:								// 19 CT ��
	case PT_ID:								// 20 PT ��
		sprintf(sql, "SELECT BrandFlag FROM %s WHERE ID=%d", 
			strBiaoMing.GetBuf(), pMSParam->wBuJianID);
		break;
	default:
		return DB_INVALID_PARAM;
		break;
	}
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, brandFlag);
	if (miaoshu->Exec() > 0)
	{
		retcode = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
		miaoshu->CloseSQL();
	}
	
	return retcode;
}

//ȡ��������
Jint32 CMSData::GetCtrlArea(ControlArea&		ctrlarea)				// ȡ�ÿ�������, ����IDȡ�ÿ�����������
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	char sql[256];
	memset(sql, 0, sizeof(char)*256);
	sprintf(sql, "select CtrlAreaName FROM CtrlArea where CtrlAreaID = %d", ctrlarea.wAreaID);
	if (miaoshu->PrepareSQL(sql))
	{
		if (   miaoshu->BindCol(IES_SQL_STRING,	32,	ctrlarea.szMingZi)
			&& miaoshu->Exec() != 0
			&& miaoshu->Fetch() 
			&& !miaoshu->IsEnd())
		{
			retcode = DB_SUCCESS;
		}

		miaoshu->CloseSQL();
	}

	return retcode;
}
Jint32 CMSData::SetCtrlArea(ControlArea	ctrlarea, eDBOPType OpType)	// ���ÿ�������
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	char sql[256];
	memset(sql, 0, sizeof(char)*256);
	if (OpType == eAdd)
	{
		ctrlarea.wAreaID = GetIDFromDB("CtrlArea", "CtrlAreaID", 0);			
		sprintf(sql, "insert into CtrlArea(CtrlAreaID, CtrlAreaName) values(?, ?)");
		if (miaoshu->PrepareSQL(sql))
		{
			if (   miaoshu->BindPara(IES_SQL_USMALLINT,	0,	&ctrlarea.wAreaID)
				&& miaoshu->BindPara(IES_SQL_STRING,	32,	ctrlarea.szMingZi)
				&& miaoshu->Exec() != 0	)
			{
				retcode = DB_SUCCESS;
			}

			miaoshu->CloseSQL();
		}
	}
	else if (OpType == eModify)
	{
		sprintf(sql, "update CtrlArea set CtrlAreaName = ? where CtrlAreaID = %d", ctrlarea.wAreaID);
		if (	miaoshu->PrepareSQL(sql)
			&&	miaoshu->BindPara(IES_SQL_STRING,	32,	ctrlarea.szMingZi))
		{			
			if( !miaoshu->Exec() )
			{
				CIIString strError = "** ��ȡ����Ϣִ��SQL������,��������:";
				strError += miaoshu->GetErrorStr();
				miaoshu->CloseSQL();
				return DB_ERROR;
			}
			
			retcode = DB_SUCCESS;
			
			miaoshu->CloseSQL();
		}
	}
	else if (OpType == eDel)
	{
		sprintf(sql, "delete from  CtrlArea where CtrlAreaID = %d", ctrlarea.wAreaID);
		if (miaoshu->PrepareSQL(sql) && miaoshu->Exec() != 0	)
		{
			retcode = DB_SUCCESS;			
		}
		//EMS-Mend: ��㳬 2006.9.14
		//�޸�ԭ��:�ڿ��������������ɾ���������������ĸ�����
		//EMS-Mend<
		sprintf(sql, "delete from  CtrlAreaParam where CtrlAreaID = %d",ctrlarea.wAreaID);
		if (miaoshu->PrepareSQL(sql) && miaoshu->Exec() != 0	)
		{
			retcode = DB_SUCCESS;			
		}
		else
		{
			retcode = DB_ERROR;	
		}
		//EMS-Mend>		
		miaoshu->CloseSQL();
	}
	else
		retcode = DB_ERROR;

	return retcode;
}

//wugc<ȡ����ͼ������
Jint32 CMSData::GetIndexGra(AIndexGra&	aIndexGra)
{
	CONNECTMSDB();
	aIndexGra.clear();
	SIndexGra tmpIndexGra;
	char* sql = "select id, name from indexgra order by id";
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &tmpIndexGra.byID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN,tmpIndexGra.szMingZi);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		aIndexGra.push_back(tmpIndexGra);
	}
	miaoshu->CloseSQL();
	return aIndexGra.size() ? DB_SUCCESS:DB_NO_DATA_FOUND;
}
//wugc>

//jiaofangxin<��ȡGRAͼ������
Jint32 CMSData::GetGraLayer(AGraLayer& aGraLayer)
{
	CONNECTMSDB();
	aGraLayer.clear();
	SGraLayer tmpIndexGra;
	char* sql = "select id, name from gralayer order by id";
	miaoshu->PrepareSQL(sql);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &tmpIndexGra.byID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN,tmpIndexGra.szMingZi);
	miaoshu->Exec();
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		aGraLayer.push_back(tmpIndexGra);
	}
	miaoshu->CloseSQL();
	return aGraLayer.size() ? DB_SUCCESS:DB_NO_DATA_FOUND;
}
//jiaofangxin>

Jint32 CMSData::GetAllCtrlArea(AControlArea&		actrlarea)					// ȡ�����п�������
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	
	actrlarea.clear();
	ControlArea ctrlarea;
	char sql[256];
	memset(sql, 0, sizeof(char)*256);
	sprintf(sql, "select CtrlAreaID, CtrlAreaName FROM CtrlArea order by CtrlAreaName");
	if (miaoshu->PrepareSQL(sql))
	{
		if (   miaoshu->BindCol(IES_SQL_USMALLINT,	0,	&ctrlarea.wAreaID)
			&& miaoshu->BindCol(IES_SQL_STRING,		32,	ctrlarea.szMingZi)
			&& miaoshu->Exec() != 0)
		{
			while (miaoshu->Fetch() && !miaoshu->IsEnd())
			{
				actrlarea.push_back(ctrlarea);
			}

			retcode = DB_SUCCESS;
		}

		miaoshu->CloseSQL();
	}

	return retcode;	
}

Jint32 CMSData::getNodeRecords(sNodePortVal npVal, vector<sNodeRecord>& vNodeRecs)
{
 	Jint32 retcode = DB_ERROR;
    sNodeRecord nr;

	CONNECTMSDB();
    nr.nNodeID = 0;
    char sql[1024] = {0};
    sprintf(sql, "select nNodeID,station1,wFieldID1,byPortNo1,byLineSide1,station2,wFieldID2,byPortNo2,byLineSide2  from noderecords where (station1 =%d and wFieldID1=%d and byPortNo1=%d ) or (station2 =%d and wFieldID2=%d and byPortNo2=%d)",
                npVal.station,npVal.wFieldID,npVal.byPortNo,npVal.station,npVal.wFieldID,npVal.byPortNo);
    miaoshu->PrepareSQL(sql);
    miaoshu->BindCol(IES_SQL_UINT,      0,  &nr.nNodeID);
    miaoshu->BindCol(SQL_DATAID_TYPE,   0,  &nr.p1.station);
    miaoshu->BindCol(IES_SQL_USMALLINT, 0,  &nr.p1.wFieldID);
    miaoshu->BindCol(IES_SQL_UTINYINT,  0,  &nr.p1.byPortNo);
    miaoshu->BindCol(IES_SQL_UTINYINT,  0,  &nr.p1.byLineSide);
    miaoshu->BindCol(SQL_DATAID_TYPE,   0,  &nr.p2.station);
    miaoshu->BindCol(IES_SQL_USMALLINT, 0,  &nr.p2.wFieldID);
    miaoshu->BindCol(IES_SQL_UTINYINT,  0,  &nr.p2.byPortNo);
    miaoshu->BindCol(IES_SQL_UTINYINT,  0,  &nr.p2.byLineSide);
    miaoshu->Exec();
    while (miaoshu->Fetch() && !miaoshu->IsEnd())
    {
        vNodeRecs.push_back(nr);
    }
    if (vNodeRecs.size() > 0)
        retcode = DB_SUCCESS;
    return retcode;
}
Jint32 CMSData::getNodeRecords(sNodePortVal npVal1, sNodePortVal npVal2, vector<sNodeRecord>& vNodeRecs)
{
 	Jint32 retcode = DB_ERROR;
    sNodeRecord nr;
	CONNECTMSDB();
    nr.nNodeID = 0;
    char sql[1024] = {0};
    memset(sql, 0, 1024);
    sprintf(sql, "select nNodeID,station1,wFieldID1,byPortNo1,byLineSide1,station2,wFieldID2,byPortNo2,byLineSide2 from noderecords where (station1 =%d and wFieldID1=%d and byPortNo1=%d and station2 =%d and wFieldID2=%d and byPortNo2=%d)  or (station1 =%d and wFieldID1=%d and byPortNo1=%d and station2 =%d and wFieldID2=%d and byPortNo2=%d)",
                npVal1.station,npVal1.wFieldID,npVal1.byPortNo,npVal2.station,npVal2.wFieldID,npVal2.byPortNo,
                npVal2.station,npVal2.wFieldID,npVal2.byPortNo,npVal1.station,npVal1.wFieldID,npVal1.byPortNo);
    miaoshu->PrepareSQL(sql);
    miaoshu->BindCol(IES_SQL_UINT,      0,  &nr.nNodeID);
    miaoshu->BindCol(SQL_DATAID_TYPE,   0,  &nr.p1.station);
    miaoshu->BindCol(IES_SQL_USMALLINT, 0,  &nr.p1.wFieldID);
    miaoshu->BindCol(IES_SQL_UTINYINT,  0,  &nr.p1.byPortNo);
    miaoshu->BindCol(IES_SQL_UTINYINT,  0,  &nr.p1.byLineSide);
    miaoshu->BindCol(SQL_DATAID_TYPE,   0,  &nr.p2.station);
    miaoshu->BindCol(IES_SQL_USMALLINT, 0,  &nr.p2.wFieldID);
    miaoshu->BindCol(IES_SQL_UTINYINT,  0,  &nr.p2.byPortNo);
    miaoshu->BindCol(IES_SQL_UTINYINT,  0,  &nr.p2.byLineSide);
    miaoshu->Exec();
    while (miaoshu->Fetch() && !miaoshu->IsEnd())
    {
        vNodeRecs.push_back(nr);
    }
    if (vNodeRecs.size() > 0)
        retcode = DB_SUCCESS;
    return retcode;
}

Jint32 CMSData::setNodeRecord(sNodeRecord nr)
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
    sNodePortVal npVal1;
    sNodePortVal npVal2;
    npVal1 = nr.p1;
    npVal2 = nr.p2;
    vector<sNodeRecord> vAllNodeRecs;
    getNodeRecords(npVal1, npVal2, vAllNodeRecs);
    if (vAllNodeRecs.size() > 0)
        return DB_SUCCESS;
    char sql[256] = {0};
	sprintf(sql, "insert into noderecords(nNodeID,station1,wFieldID1,byPortNo1,byLineSide1,station2,wFieldID2,byPortNo2,byLineSide2)    \
        values(%d,%d,%d,%d,%d,%d,%d,%d,%d)",
        nr.nNodeID,nr.p1.station,nr.p1.wFieldID,nr.p1.byPortNo,nr.p1.byLineSide,nr.p2.station,nr.p2.wFieldID,nr.p2.byPortNo,nr.p2.byLineSide);
    retcode = miaoshu->ExecuteSQL(sql);
    return retcode;
}
Jint32 CMSData::delNodeRec(sNodeRecord nr)
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();

    char sql[256] = {0};
	sprintf(sql, "delete from noderecords where (station1 =%d and wFieldID1=%d and byPortNo1=%d and station2 =%d and wFieldID2=%d and byPortNo2=%d)  or (station1 =%d and wFieldID1=%d and byPortNo1=%d and station2 =%d and wFieldID2=%d and byPortNo2=%d)",
                nr.p1.station,nr.p1.wFieldID,nr.p1.byPortNo,nr.p2.station,nr.p2.wFieldID,nr.p2.byPortNo,
                nr.p2.station,nr.p2.wFieldID,nr.p2.byPortNo,nr.p1.station,nr.p1.wFieldID,nr.p1.byPortNo);
    retcode = miaoshu->ExecuteSQL(sql);
    return retcode;
}
Jint32 CMSData::delNodeRec(DATAID_TYPE stationid, Juint16 wStaFieldID)
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();

    char sql[256] = {0};
	sprintf(sql, "delete from noderecords where (station1 =%d and wFieldID1=%d)  or (station2 =%d and wFieldID2=%d)",
                stationid, wStaFieldID,stationid, wStaFieldID);
    retcode = miaoshu->ExecuteSQL(sql);
    return retcode;
}
// majian modify begin 2009.6.1
// �޸�ԭ��������������Ƶ����������ʾ���������һ������byType
Jint32 CMSData::GetCtrlAreaParam(Juint16 wAreaID, AControlAreaParam& actrlareaparam,Juint8 byType)	// ����wAreaIDȡ�����������
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	actrlareaparam.clear();
	ControlAreaParam ctrlareapara;
	ctrlareapara.wAreaID = wAreaID;
	char sql[256];
	memset(sql, 0, sizeof(char)*256);
	if (0 == byType)
	{
		sprintf(sql, "select ChangZhanID, DianYaDengJiID FROM CtrlAreaParam where CtrlAreaID=%d order by ChangZhanID, DianYaDengJiID", wAreaID);
		if (miaoshu->PrepareSQL(sql))
		{
			if ( miaoshu->BindCol(SQL_DATAID_TYPE,	0,	&ctrlareapara.wChangZhanID)
				&& miaoshu->BindCol(IES_SQL_USMALLINT,	0,	&ctrlareapara.wDianYaDengJi)
				&& miaoshu->Exec() != 0)
			{
				while (miaoshu->Fetch() && !miaoshu->IsEnd() )
				{
					actrlareaparam.push_back(ctrlareapara);
				}

				retcode = DB_SUCCESS;
			}

			miaoshu->CloseSQL();
		}
	}
	else if (CA_FEEDER == byType)
	{// ֻѡ������
		ctrlareapara.byBJType = DMSFeeder_ID;
		sprintf(sql, "select bjid FROM CtrlAreaParam where CtrlAreaID=%d and bjtype=%d", wAreaID,DMSFeeder_ID);
		if (miaoshu->PrepareSQL(sql))
		{
			if ( miaoshu->BindCol(SQL_DATAID_TYPE,	0,	&ctrlareapara.wBJID)
				&& miaoshu->Exec() != 0)
			{
				while (miaoshu->Fetch() && !miaoshu->IsEnd() )
				{
					actrlareaparam.push_back(ctrlareapara);
				}

				retcode = DB_SUCCESS;
			}

			miaoshu->CloseSQL();
		}
	}
	else if (CA_STATION == byType)
	{// ֻѡ��վ
        sprintf(sql, "select changzhanid, DIANYADENGJIID FROM CtrlAreaParam where CtrlAreaID=%d and changzhanid <> 0 and bjtype = 5 and bjid = 0", wAreaID);
		if (miaoshu->PrepareSQL(sql))
		{
			if ( miaoshu->BindCol(SQL_DATAID_TYPE, 0,	&ctrlareapara.wChangZhanID)
				&& miaoshu->BindCol(IES_SQL_UTINYINT, 0 , &ctrlareapara.wDianYaDengJi)
				&& miaoshu->Exec() != 0)
			{
				while (miaoshu->Fetch() && !miaoshu->IsEnd() )
				{
					ctrlareapara.byBJType = 5;
					actrlareaparam.push_back(ctrlareapara);
				}

				retcode = DB_SUCCESS;
			}

			miaoshu->CloseSQL();
		}
	}
	else if (CA_DEVICE == byType)
	{// ֻѡ���豸
		sprintf(sql, "select changzhanid, dianyadengjiid,bjtype, bjid FROM CtrlAreaParam where CtrlAreaID=%d and bjtype <> 0 and bjtype <> %d and bjid <> 0 order by changzhanid, bjtype, bjid", wAreaID, MaxBuJian_ID);
		
		if (miaoshu->PrepareSQL(sql))
		{
			if ( miaoshu->BindCol(SQL_DATAID_TYPE,	0,	&ctrlareapara.wChangZhanID)
				&& miaoshu->BindCol(IES_SQL_UTINYINT, 0,&ctrlareapara.wDianYaDengJi)
				&& miaoshu->BindCol(IES_SQL_UTINYINT,	0,	&ctrlareapara.byBJType)
				&& miaoshu->BindCol(SQL_DATAID_TYPE, 0,	&ctrlareapara.wBJID)
				&& miaoshu->Exec() != 0)
			{
				while (miaoshu->Fetch() && !miaoshu->IsEnd() )
				{
					actrlareaparam.push_back(ctrlareapara);
				}

				retcode = DB_SUCCESS;
			}

			miaoshu->CloseSQL();
		}
	}

	return retcode;	

}
// majian modify end 2009.6.1


Jint32 CMSData::SetCtrlAreaParam(ControlAreaParam	oldval, ControlAreaParam newval, eDBOPType OpType)// ���ÿ����������
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	char sql[256];
	memset(sql, 0, sizeof(char)*256);

	if (OpType == eAdd)
	{
		sprintf(sql, "insert into CtrlAreaParam(CtrlAreaID, ChangZhanID, DianYaDengJiID,BJType, BJID) values(?,?,?,?,?)");
		if (miaoshu->PrepareSQL(sql))
		{
			if (   miaoshu->BindPara(IES_SQL_USMALLINT,	0,	&newval.wAreaID)
				&& miaoshu->BindPara(SQL_DATAID_TYPE,	0,	&newval.wChangZhanID)
				&& miaoshu->BindPara(IES_SQL_UTINYINT,	0,	&newval.wDianYaDengJi)
				&& miaoshu->BindPara(IES_SQL_UTINYINT,	0,	&newval.byBJType)
				&& miaoshu->BindPara(SQL_DATAID_TYPE,	0,	&newval.wBJID)
				&& miaoshu->Exec() != 0	)
			{
				retcode = DB_SUCCESS;
			}
			
			CIIString error = miaoshu->GetErrorStr();//ningfanggang 2008.11.6 ���ش�����
			miaoshu->CloseSQL();
		}
	}
	else if (OpType == eModify)
	{
		sprintf(sql, "update CtrlAreaParam set ChangZhanID = %d, DianYaDengJiID=%d,BJType=%d, BJID=%d where CtrlAreaID=%d and ChangZhanID=%d and DianYaDengJiID=%d and BJType=%d and BJID=%d", 
			newval.wChangZhanID,
			newval.wDianYaDengJi,
			newval.byBJType,
			newval.wBJID,
			oldval.wAreaID,
			oldval.wChangZhanID,
			oldval.wDianYaDengJi,
			oldval.byBJType,
			oldval.wBJID);
		if (	miaoshu->PrepareSQL(sql)
			 && miaoshu->Exec() )
		{
			retcode = DB_SUCCESS;

		}
		miaoshu->CloseSQL();
	}
	else if (OpType == eDel)
	{
		sprintf(sql, "delete from  CtrlAreaParam where CtrlAreaID = %d and ChangZhanID = %d and DianYaDengJiID=%d and BJType=%d and BJID=%d",
			oldval.wAreaID,
			oldval.wChangZhanID,
			oldval.wDianYaDengJi,
			oldval.byBJType,
			oldval.wBJID);
		if (miaoshu->PrepareSQL(sql) && miaoshu->Exec() != 0	)
		{
			retcode = DB_SUCCESS;			
		}
		miaoshu->CloseSQL();
	}
	else
		retcode = DB_ERROR;

	return retcode;

}
Jint32 CMSData::GetAllCtrlAreaParam(AControlAreaParam& actrlareaparam)			// ȡ���п����������
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	actrlareaparam.clear();
	ControlAreaParam ctrlareapara;
	char sql[256];
	memset(sql, 0, sizeof(char)*256);
	//EMS-Mend:hujr 2009.11.17
	//Reason:
	//EMS-Mend<
	//sprintf(sql, "select CtrlAreaID, ChangZhanID, DianYaDengJiID FROM CtrlAreaParam order by CtrlAreaID, ChangZhanID, DianYaDengJiID");
	sprintf(sql, "select CtrlAreaID, ChangZhanID, DianYaDengJiID, bjtype, bjid FROM CtrlAreaParam order by CtrlAreaID, ChangZhanID, DianYaDengJiID , bjtype ,bjid");
	//EMS-Mend>	

	
	if (miaoshu->PrepareSQL(sql))
	{
		if (   miaoshu->BindCol(IES_SQL_USMALLINT,	0,	&ctrlareapara.wAreaID)
			&& miaoshu->BindCol(SQL_DATAID_TYPE,	0,	&ctrlareapara.wChangZhanID)
			&& miaoshu->BindCol(IES_SQL_USMALLINT,	0,	&ctrlareapara.wDianYaDengJi)
			//EMS-Mend:hujr 2009.11.17
			//Reason:
			//EMS-Mend<
			&& miaoshu->BindCol(IES_SQL_UTINYINT,	0,	&ctrlareapara.byBJType )
			&& miaoshu->BindCol(SQL_DATAID_TYPE, 0, &ctrlareapara.wBJID)
			//EMS-Mend>	
			&& miaoshu->Exec() != 0)
		{
			while (miaoshu->Fetch() && !miaoshu->IsEnd() )
			{
				actrlareaparam.push_back(ctrlareapara);
			}

			retcode = DB_SUCCESS;
		}

		miaoshu->CloseSQL();
	}

	return retcode;	
}


//Jint32 CMSData::SetBrandFlag(SMiaoShuParam* pMSParam, BrandFlag* brandFlag)
Jint32 CMSData::SetBrandFlag(SMiaoShuParam* pMSParam, BrandFlag* brandFlag, Jboolean bAll)
{
	networktohost(brandFlag,sizeof(BrandFlag));//baizy�� 2008.8.12, �����Ʊ��޵��ƵĴ���
	Juint16 data = 0 ;
	if (pMSParam == NULL && brandFlag == NULL)
		return DB_INVALID_PARAM;
	//���Ʋ���ת������Ӧ������״̬��
	GetCorrComp(pMSParam->byBuJianLeiXingID,pMSParam->wBuJianID,pMSParam->byBuJianCanShuID);
	
	CONNECTMSDB();
	Jint32 retcode = DB_ERROR;
	char sql[256];
	CIIString strBiaoMing = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	switch (pMSParam->byBuJianLeiXingID)
	{
	case ChangZhan_ID:						// 5 ��վ��
	case MuXian_ID:							// 6 ĸ�߱�
	case XianLu_ID:							// 7 ��·��
	case KaiGuan_ID:						// 8 ���ر�
	case DaoZha_ID:							// 9 ��բ��
	case BaoHu_ID:							// 10 ������
	case BianYaQi_ID:						// 11 ��ѹ����
	case FaDianJi_ID:						// 12 �������
	case FuHe_ID:							// 13 ���ɱ�
	case TiaoXiang_ID:						// 15 �����
	case JingZhiBuChang_ID:					// 16 ��ֹ������
	case BingLianDianRong_ID:				// 17 �������ݲ�����
	case ChuanLianDianKang_ID:				// 18 �����翹
	case CT_ID:								// 19 CT ��
	case PT_ID:								// 20 PT ��
	//wugc<2010.8.23���ع������ݿ⼰�ṹ��չ
	case XuNiZHTLiang_ID:					// 23 ����״̬��
	//wugc>
	case DMSFeederSection_ID:
	case DMSTransformer_ID:
	case FengJi_ID:
		{
			memcpy(&data, brandFlag, sizeof(BrandFlag));
			sprintf(sql, "UPDATE %s SET BrandFlag=%d WHERE ID=%d", 
				strBiaoMing.GetBuf(), data, pMSParam->wBuJianID);
		}
		break;
	default:
		return DB_INVALID_PARAM;
		break;
	}
	
	miaoshu->PrepareSQL(sql);
	retcode = miaoshu->Exec();
	// EMS-Mend< baizy 2007.8.16 16:39
	// �޸�ԭ��:����ĵ�բ������ҲҪ��������
	retcode = (retcode > 0) ? 1 : 0;
	if (bAll)
	{
		// ���¼���ĵ�բ�Ĺ��Ʊ�־
		sprintf(sql, "UPDATE daozha SET BrandFlag=%d WHERE DYBJTYPE=%d and DYBJID=%d", data, pMSParam->byBuJianLeiXingID,pMSParam->wBuJianID);
		miaoshu->PrepareSQL(sql);
		retcode = miaoshu->Exec();
		retcode = (retcode > 0) ? 1 : 0;
		
		// ���¼���ı����Ĺ��Ʊ�־
		sprintf(sql, "UPDATE baohu SET BrandFlag=%d WHERE bujianleixingid=%d and bujianid=%d", data, pMSParam->byBuJianLeiXingID,pMSParam->wBuJianID);
		miaoshu->PrepareSQL(sql);
		retcode = miaoshu->Exec();
		retcode = (retcode > 0) ? 1 : 0;
	}
	// EMS-Mend>
	
	miaoshu->CloseSQL();
	retcode = (retcode > 0) ? DB_SUCCESS : DB_ERROR;
	
	return retcode;
}

//=============================================================================
// ����ң��Ͷ��״̬
// ��ڣ�ָ������������������ʽ��Ͷ���־��˳��ţ�0��YX 1:YXBJ 2:YC 3:YCBJ 4:YXYK
// ���ڣ������Ƿ�ɹ��ķ�����
// Date : 2002.10.28 ????????????????????
//=============================================================================

Jint32 CMSData::SetTouTui(SMiaoShuParam* pMSParam, Juint8 bTouTuiState, Juint8 byNum)
{
	if (INVALIDTYPE(pMSParam->byBuJianLeiXingID) || byNum < 0 || byNum >4)
		return DB_INVALID_PARAM;

	return DB_SUCCESS;
}

//=============================================================================
//��ȡRTUͶ������
// ��ڣ�
// ���ڣ������Ƿ�ɹ��ķ�����
Jint32 CMSData::GetRTUTouTui(DATAID_TYPE	nRTUID, Juint8& byTouTuiAttr)
{
	CONNECTMSDB();
	Juint32 nRet = DB_ERROR;
	CIIString		strSQL;
	CIIString		strWhere;
	
	byTouTuiAttr = 0;
	strSQL.Format("select ByRTUTouTuiFlag from  comrtu  where WRTUID = %d", nRTUID);
	miaoshu->PrepareSQL(strSQL.GetBuf());
//	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &byTouTuiAttr);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &byTouTuiAttr);	//xuwb add 2007.04.18
	miaoshu->Exec();
	if (miaoshu->Fetch() && !miaoshu->IsEnd())
		nRet = DB_SUCCESS;

	miaoshu->CloseSQL();
	return nRet;	 
}

//=============================================================================
//����RTUͶ������
// ��ڣ�
// ���ڣ������Ƿ�ɹ��ķ�����
Jint32 CMSData::SetRTUTouTui(DATAID_TYPE	nRTUID, Juint8& byTouTuiAttr)
{
	CONNECTMSDB();

	CIIString		strSQL;
	CIIString		strWhere;

	strSQL.Format("update comrtu set ByRTUTouTuiFlag =%d where WRTUID = %d", byTouTuiAttr, nRTUID);
	miaoshu->PrepareSQL(strSQL.GetBuf());
	Jint32 nRet = miaoshu->Exec();
	if (nRet == DB_SUCCESS_WITH_INFO) nRet = DB_SUCCESS;
	miaoshu->CloseSQL();
	return nRet;	 
}

//EMS-Mend< pengxiaoyan 2007.8.13 14:27
//�޸�ԭ��:��ȡͶ��RTU�б�
//=============================================================================
//��ȡͶ��RTU�б�
// ��ڣ�
// ���ڣ������Ƿ�ɹ��ķ�����
Jint32 CMSData::GetTouTuiRTUList(ARTUChannel* arRTUCH)
{
	CONNECTMSDB();
	Juint32 nRet = DB_ERROR;
	CIIString		strSQL;
	CIIString		strWhere;	

	SRTUChannel	rtuch;
	strSQL.Format("select WRTUID, StrName from  comrtu  where ByRTUTouTuiFlag=0");
	miaoshu->PrepareSQL(strSQL.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &rtuch.wCZID);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, &rtuch.szMingZi);
	if (!miaoshu->Exec())
		return DB_ERROR;
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arRTUCH->push_back(rtuch);		
	}
	nRet = DB_SUCCESS;
	miaoshu->CloseSQL();
	return nRet;	
}
//EMS-Mend>

//=============================================================================
//��ȡ����Ͷ������
// ��ڣ�byType: 0--ң��, 1--ң��, byTouTuiAttr: 0--��, 1--Ͷ
// ���ڣ������Ƿ�ɹ��ķ�����
Jint32 CMSData::GetBuJianTouTui(Juint8 byType, DATAID_TYPE	nRTUID, Juint16 nOrder, Juint8& byTouTuiAttr)
{
	if (byType > 1) return DB_INVALID_PARAM;
	CONNECTMSDB();
	Juint32 nRet = DB_ERROR;

	CIIString		strSQL;
	byTouTuiAttr = 0;
	if (byType == 0)
	{
		strSQL.Format("select byValidFlag from  comfloatdata  where WRTUID = %d and bytype = 0 and worder = %d", nRTUID, nOrder);
	}
	else
	{
		strSQL.Format("select byValidFlag from  combytedata  where WRTUID = %d and bytype = 0 and worder = %d", nRTUID, nOrder);
	}
	miaoshu->PrepareSQL(strSQL.GetBuf());
//	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &byTouTuiAttr);
	miaoshu->BindCol(IES_SQL_BOOL, 0, &byTouTuiAttr);	//xuwb add 2007.04.18
	miaoshu->Exec();
	if (miaoshu->Fetch() && !miaoshu->IsEnd())
		nRet = DB_SUCCESS;

	miaoshu->CloseSQL();	
	return nRet;
 
}

//=============================================================================
//���ò���Ͷ������
// ��ڣ�byType: 0--ң��, 1--ң��, byTouTuiAttr: 0--��, 1--Ͷ
// ���ڣ������Ƿ�ɹ��ķ�����
Jint32 CMSData::SetBuJianTouTui(Juint8 byType, DATAID_TYPE	nRTUID, Juint16 nOrder, Juint8 byTouTuiAttr)
{
	if (byType > 1) return DB_INVALID_PARAM; 
	CONNECTMSDB();

	Jint32 nRet = DB_ERROR;
	CIIString		strSQL;
	if (byType == 0)
	{
		strSQL.Format("update comfloatdata set byValidFlag =%d where WRTUID = %d and bytype = 0 and worder = %d", byTouTuiAttr, nRTUID, nOrder);
	}
	else
	{
		strSQL.Format("update combytedata set byValidFlag =%d where WRTUID = %d and bytype = 0 and worder = %d", byTouTuiAttr, nRTUID, nOrder);
	}

	miaoshu->PrepareSQL(strSQL.GetBuf());
	nRet = miaoshu->Exec();
	miaoshu->CloseSQL();
	if (nRet == DB_SUCCESS_WITH_INFO) nRet = DB_SUCCESS;
	return nRet;	 
}

//=============================================================================
//��ȡң����Ч��ֵ
// ��ڣ�wRTUID, wOrder, fMaxPositiveValue, fMinPositiveValue, fMaxNegativeValue, fMinNegativeValue
// ���ڣ������Ƿ�ɹ��ķ�����
Jint32 CMSData::GetValidLmt(TK_ComFloatData& tkfloatdata)
{
	CONNECTMSDB();

	CIIString		strSQL;
	CIIString		strWhere;
	
// EMS-Mend< majian 2007.12.8 15:14
// �޸�ԭ��: ����˾䣬��Ϊ�������л������ݣ��������㣬�����޷���ȷ��ȡ��Ч��ֵ
//	memset(&tkfloatdata, 0, sizeof(tkfloatdata));// EMS-Mend< baizy 2007.7.11
// EMS-Mend> majian 2007.12.8 15:14

	strSQL = "select fMaxPositiveValue, fMinPositiveValue, fMaxNegativeValue, fMinNegativeValue, wDeadValue FROM comfloatdata ";
	strWhere.Format(" where wRTUID = %d and byType = 0 and wOrder = %d", tkfloatdata.wRTUID, tkfloatdata.wOrder);
	strSQL += strWhere;
	if( !miaoshu->PrepareSQL(strSQL.GetBuf()) )
	{
		CIIString strError = "** ��ȡ����ϢPrepareSQL����,��������:";
		strError += miaoshu->GetErrorStr();
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

	miaoshu->BindCol(IES_SQL_FLOAT, 0, &tkfloatdata.fMaxPositiveValue);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &tkfloatdata.fMinPositiveValue);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &tkfloatdata.fMaxNegativeValue);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &tkfloatdata.fMinNegativeValue);
	miaoshu->BindCol(IES_SQL_UINT, 0, &tkfloatdata.wDeadValue);

	if( !miaoshu->Exec() )
	{
		CIIString strError = "** ��ȡ����Ϣִ��SQL������,��������:";
		strError += miaoshu->GetErrorStr();
		miaoshu->CloseSQL();
		return DB_ERROR;
	}
	
	if ( miaoshu->Fetch() && !miaoshu->IsEnd() )
	{
		miaoshu->CloseSQL();
		return DB_SUCCESS;
	}
	else
	{
		miaoshu->CloseSQL();
		return DB_NO_DATA_FOUND;
	}
}

//=============================================================================
//����ң����Ч��ֵ
// ��ڣ�wRTUID, wOrder, fMaxPositiveValue, fMinPositiveValue, fMaxNegativeValue, fMinNegativeValue
// ���ڣ������Ƿ�ɹ��ķ�����
Jint32 CMSData::SetValidLmt(TK_ComFloatData& tkfloatdata)
{
	CONNECTMSDB();

	CIIString		strSQL;
	CIIString		strWhere;
	
//	strSQL = "update comfloatdata set fMaxPositiveValue =?, fMinPositiveValue = ?, fMaxNegativeValue=?, fMinNegativeValue=?, wDeadValue=?";// EMS-Mend< baizy 2007.7.11,������
	strSQL.Format("update comfloatdata set fMaxPositiveValue =%f, fMinPositiveValue = %f, fMaxNegativeValue=%f, fMinNegativeValue=%f, wDeadValue=%d",
		tkfloatdata.fMaxPositiveValue,tkfloatdata.fMinPositiveValue,tkfloatdata.fMaxNegativeValue,tkfloatdata.fMinNegativeValue,
		tkfloatdata.wDeadValue);
	strWhere.Format(" where wRTUID = %d and byType = 0 and wOrder = %d", tkfloatdata.wRTUID, tkfloatdata.wOrder);
	strSQL += strWhere;
	if( !miaoshu->PrepareSQL(strSQL.GetBuf()) )
	{
		CIIString strError = "** ��ȡ����ϢPrepareSQL����,��������:";
		strError += miaoshu->GetErrorStr();
		miaoshu->CloseSQL();
		return DB_ERROR;
	}

//	miaoshu->BindPara(IES_SQL_FLOAT, 0, &tkfloatdata.fMaxPositiveValue);
//	miaoshu->BindPara(IES_SQL_FLOAT, 0, &tkfloatdata.fMinPositiveValue);
//	miaoshu->BindPara(IES_SQL_FLOAT, 0, &tkfloatdata.fMaxNegativeValue);
//	miaoshu->BindPara(IES_SQL_FLOAT, 0, &tkfloatdata.fMinNegativeValue);
//	miaoshu->BindPara(IES_SQL_UINT, 0, &tkfloatdata.wDeadValue);
//
	if( !miaoshu->Exec() )
	{
		CIIString strError = "** ��ȡ����Ϣִ��SQL������,��������:";
		strError += miaoshu->GetErrorStr();
		miaoshu->CloseSQL();
		return DB_ERROR;
	}
	
	miaoshu->CloseSQL();
	return DB_SUCCESS;
}

//=============================================================================
//  ȡĳһ��վ΢����������
//  Date : 2002.10.28
//=============================================================================

Jint32 CMSData::GetWJBHCanShu(DATAID_TYPE wCZID, AWJBHCanShu* parWJBHCanShu)
{
	if (!parWJBHCanShu)	return DB_INVALID_PARAM;

	CONNECTMSDB();
	parWJBHCanShu->clear();

	SWJBHCanShu	WJBHCanShu;
	CIIString	sql;
	sql.Format("SELECT wRTUID FROM ComRTU WHERE wChangZhanID=%d", wCZID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &WJBHCanShu.wRTUID);
	miaoshu->Exec();
	if (!miaoshu->Fetch() || miaoshu->IsEnd()) return DB_NO_DATA_FOUND;

	sql.Format("SELECT wOrder,strName,byCabinetID,byUnitID,nType,byProtocolType,nDZhAreaNum,nBaoHuFangAn FROM ComRTU WHERE wRTUID=%d", WJBHCanShu.wRTUID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &WJBHCanShu.wOrder);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, WJBHCanShu.szName);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &WJBHCanShu.byCabinetID);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &WJBHCanShu.byUnitID);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &WJBHCanShu.wType);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &WJBHCanShu.byProtocolType);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &WJBHCanShu.wDZhAreaNum);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &WJBHCanShu.wBaoHuFangAn);
	miaoshu->Exec();

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		parWJBHCanShu->push_back(WJBHCanShu);
	}

	return parWJBHCanShu->size()>0 ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
//  ȡͨѶ������ ID
//  Date : 2002.10.28
//=============================================================================

Juint8 CMSData::GetComServerID(DATAID_TYPE wRTUID)
{
	Juint8	byComID = 0;
	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT byServerNumber FROM ComRTU WHERE wRTUID=%d", wRTUID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byComID);
	miaoshu->Exec();
	miaoshu->Fetch();

	return byComID;
}

//=============================================================================
// ���� RTUID, ȡ������Ӧ�ĳ�վ ID
// ��ڣ�RTU��ID
// ���ڣ���վ��ID
// Date: 2002.10.28
//=============================================================================

Juint16 CMSData::GetRTUCZID(DATAID_TYPE wRTUID)
{
	DATAID_TYPE	wczID = 0;
	CONNECTMSDB();

	CIIString	sql;
	sql.Format("SELECT wChangZhanID FROM ComRTU WHERE wRTUID=%d", wRTUID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wczID);
	miaoshu->Exec();
	miaoshu->Fetch();

	return wczID;
}

//=============================================================================
// ȡָ����վ������
// ��ڣ�ָ����վ��ID����ų�վ���ֵ��ַ���ָ��
// ���ڣ����������롢��վ���ֵ��ַ���
// Date��2002.10.28
//=============================================================================

Jint32 CMSData::GetCZName(DATAID_TYPE wczID, CIIString* pszMingZi )
{
	*pszMingZi = GetBuJianName(ChangZhan_ID, wczID);

	return pszMingZi->IsEmpty() ? DB_NO_DATA_FOUND:DB_SUCCESS;
}

//=============================================================================
// ȡң�ز�����������
// ��ڣ���ȡ���ݵĵ�ַָ��
// ���ڣ���ȡ���ݵĵ�ַָ��
// Date : 2002.10.28
//=============================================================================

Jint32 CMSData::GetYKGLData(SYKGLParam* pGLParam)
{
	if(!pGLParam)		return DB_INVALID_PARAM;

	CONNECTMSDB();
	CIIString sql, filter;
	sql = "SELECT GLBJType1,GLID1,GLHType1,GLCon1,GLMing1,GLBJType2,GLID2,GLHType2,GLCon2,GLMing2";
	sql += "GLBJType3, GLID3, GLHType3, GLCon3, GLMing3, GLBJType4, GLID4, GLHType4, GLCon4, GLMing4 ";
	sql += "FROM YKCondition WHERE ";
	filter.Format("BJType=%d AND BJID=%d AND CSHType=%d AND DZState=%d",
		pGLParam->CZObj.byBJType, pGLParam->CZObj.wBJID, pGLParam->CZObj.byCSHType, pGLParam->CZObj.byDZState);
	sql += filter;
	miaoshu->PrepareSQL(sql.GetBuf());
	for (Jint16 i=0; i<4; i++)
	{
		miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pGLParam->GLObj[i].byBJType);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &pGLParam->GLObj[i].wBJID);
		miaoshu->BindCol(IES_SQL_USMALLINT, 0, &pGLParam->GLObj[i].byCSHType);
		miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pGLParam->GLObj[i].byDZState);
		miaoshu->BindCol(IES_SQL_STRING, NAMELEN, pGLParam->GLObj[i].szMingZi);
	}

	miaoshu->Exec();
	miaoshu->Fetch();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ���������ı���ID, ���֣���������ID���ݽṹ
// ��ڣ������ࡢ����ID
// ���ڣ������롢������Ϣ����
// Date : 2002.10.28
//=============================================================================

Jint32 CMSData::GetBHInfo(Juint8 bjlxID, DATAID_TYPE bjID, ABHInfo* arBHInfo)
{
	if(INVALIDTYPE(bjlxID) || !arBHInfo)		return DB_INVALID_PARAM;

	CONNECTMSDB();
	arBHInfo->clear();
	SBHInfo	stBHInfo;
	CIIString sql, filter;
	sql.Format( "SELECT ID, MingZi, BaoHuLeiXingID, BHDingZhi1 FROM BaoHu "
				"WHERE BuJianLeiXingID=%d AND BuJianID=%d ORDER BY MingZi", bjlxID, bjID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &stBHInfo.wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, stBHInfo.szMingZi);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &stBHInfo.wBaoHuLeiXingID);
	miaoshu->BindCol(IES_SQL_FLOAT, 0, &stBHInfo.fDZVal);
	miaoshu->Exec();

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arBHInfo->push_back(stBHInfo);
	}

	return arBHInfo->size()>0 ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ���������ı���ID, ����,��վID,��ѹ�ȼ�ID���ݽṹ
// ��ڣ������ࡢ����ID
// ���ڣ������롢������Ϣ����
// Date : 2002.10.28
// lit 2007.8.15
//=============================================================================

Jint32 CMSData::GetBJBHInfo(Juint8 bjlxID, DATAID_TYPE bjID, ABJBHInfo* arBJBHInfo)
{
	if(INVALIDTYPE(bjlxID) || !arBJBHInfo)		return DB_INVALID_PARAM;
	
	CONNECTMSDB();
	arBJBHInfo->clear();
	SBJBHInfo	stBJBHInfo;
	CIIString sql, filter;
	sql.Format( "SELECT ID, MingZi, ChangZhanID, DianYaDengJiID FROM BaoHu "
		"WHERE BuJianLeiXingID=%d AND BuJianID=%d ORDER BY MingZi", bjlxID, bjID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &stBJBHInfo.wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, stBJBHInfo.szMingZi);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &stBJBHInfo.wChangZhanID);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &stBJBHInfo.wDianYaDengJi);
	miaoshu->Exec();
	
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arBJBHInfo->push_back(stBJBHInfo);
	}
	
	return arBJBHInfo->size()>0 ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ���ݱ���ID, ȡ���֣���������ID���ݽṹ
// ��ڣ�����ID����������ID���ݽṹָ��
// ���ڣ����������롢��������ID���ݽṹ
// Date : 2002.10.28
//=============================================================================

Jint32 CMSData::GetBHIDInfo(DATAID_TYPE bjID, SBHInfo* BHInfo)
{
	if(!BHInfo)		return DB_INVALID_PARAM;

	CONNECTMSDB();
	CIIString sql, filter;
	sql.Format("SELECT ID, MingZi, BaoHuLeiXingID, BHDingZhi1 FROM BaoHu WHERE ID=%d", bjID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &BHInfo->wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, BHInfo->szMingZi);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &BHInfo->wBaoHuLeiXingID);
	miaoshu->BindCol(IES_SQL_FLOAT,		0, &BHInfo->fDZVal);
	miaoshu->Exec();

	if (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡCT����KWH����ֵϵ��
// ��ڣ���������ʽ��ϵ��ָ��
// ���ڣ����������롢ϵ��ֵ
// Date : 2002.10.28
//=============================================================================

static SGetKWHCoef	KWHCoefParam[4] =
{
	{CT_ID, CT_ZPDWVal, "ZPDDCoef"},
	{CT_ID, CT_ZQDWVal, "ZQDDCoef"},
	{CT_ID, CT_FPDWVal, "FPDDCoef"},
	{CT_ID, CT_FQDWVal, "FQDDCoef"},
};

Jint32 CMSData::GetKWHCoef(SMiaoShuParam* pMSParam, Jdouble* pValcoef)
{
	if(!pMSParam || !pValcoef)	return DB_INVALID_PARAM;
	Juint16 i=0;
	for (i=0; i<sizeof(KWHCoefParam)/sizeof(SGetKWHCoef); i++)
	{
		if (pMSParam->byBuJianLeiXingID==KWHCoefParam[i].byBuJianLeiXingID &&
			pMSParam->byBuJianCanShuID==KWHCoefParam[i].byBuJianCanShuID)
			break;
		else
			return DB_INVALID_PARAM;
	}

	CONNECTMSDB();
	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(pMSParam->byBuJianLeiXingID);
	sql.Format("SELECT %s FROM %s WHERE ID=%d", KWHCoefParam[i].szCoefMZ, strBiaoMing.GetBuf(), pMSParam->wBuJianID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_DOUBLE, 0, pValcoef);
	miaoshu->Exec();

	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ���أ���բ������Ӧ�Ĳ�������
// ��ڣ��������͡�����ID����������ָ��
// ���ڣ����������롢��������
// Date:  2002.10.28
//=============================================================================

Jint32 CMSData::GetCZJiBie(Juint8 byBuJianLeiXing, DATAID_TYPE wBuJianID, Juint8* pbyCzBie)
{
	if (!pbyCzBie || (byBuJianLeiXing!=KaiGuan_ID && byBuJianLeiXing!=DaoZha_ID && byBuJianLeiXing!=BaoHu_ID && byBuJianLeiXing!=BianYaQi_ID))
		return DB_INVALID_PARAM;

	CONNECTMSDB();
	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(byBuJianLeiXing);
	sql.Format("SELECT CZJiBie FROM %s WHERE ID=%d", strBiaoMing.GetBuf(), wBuJianID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, pbyCzBie);
	miaoshu->Exec();

	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
}
//wugc<2010.8.23���ع������ݿ⼰�ṹ��չ
//wugc<2010.6.30
Jint32 CMSData::GetWarnLevel(Juint8 byBuJianLeiXing, DATAID_TYPE wBuJianID, Juint8& byWarnLevel)
{
	if ( byBuJianLeiXing!=KaiGuan_ID && byBuJianLeiXing!=DaoZha_ID && byBuJianLeiXing!=BaoHu_ID && byBuJianLeiXing!=BianYaQi_ID )
		return DB_INVALID_PARAM;

	CONNECTMSDB();
	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(byBuJianLeiXing);
	sql.Format("SELECT ALARMLEVEL FROM %s WHERE ID=%d", strBiaoMing.GetBuf(), wBuJianID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byWarnLevel);
	miaoshu->Exec();

	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
}
//wugc>
//=============================================================================
// ͨ�������ID����ȡ��������Ӳ��� fadianji
// ��ڣ��������ID�����Ӳ���ָ��
// ���ڣ����������롢���Ӳ���
// Date: 2002.10.29
//=============================================================================

Jint32 CMSData::GetFDJChainUnit(DATAID_TYPE wFaDianJiID, SMiaoShuParam* pFDJChainUnit)
{
	if (!pFDJChainUnit)		return DB_INVALID_PARAM;

	CONNECTMSDB();
	CIIString sql;
	sql.Format("SELECT BJType1ID, BJ1ID FROM FaDianJi WHERE ID=%d", wFaDianJiID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pFDJChainUnit->byBuJianLeiXingID);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &pFDJChainUnit->wBuJianID);
	pFDJChainUnit->byBuJianCanShuID = 1;		//����ȱʡ��Ϊ1 ���
	miaoshu->Exec();

	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ�ӵص�բ�� ID�����֣�ͨ����վ���ⲿ�������ڲ����ϵ�բ����
//
// Date: 2002.10.29
// majian 2008.1.25 �޸ĵڶ������������س�վID 
//=============================================================================
Jint32 CMSData::GetJDDaoZha(DATAID_TYPE wChangZhanID, ABuJianPlusType* arBuJianPlusType)
{
	if (!arBuJianPlusType)
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	arBuJianPlusType->clear();
	CIIString sql;
	if (wChangZhanID == 0)
		sql = "SELECT ID, CHANGZHANID, MingZi FROM DaoZha WHERE LeiXingID=5 ORDER BY MingZi";
	else
		sql.Format("SELECT ID, CHANGZHANID, MingZi FROM DaoZha WHERE ChangZhanID=%d AND LeiXingID=5 ORDER BY MingZi", wChangZhanID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJianPlusType.wID);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJianPlusType.wChangZhan);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJianPlusType.szMingZi);
	miaoshu->Exec();

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
		arBuJianPlusType->push_back(m_stBuJianPlusType);

// EMS-Mend< baizy 2008.5.19 10:58
// �޸�ԭ��:�޸Ľӵص�բͳ�Ʋ���
	ABuJianPlusType arBJ;
	int i = 0;
	int nSize = arBuJianPlusType->size();
	for (i=0; i<nSize; i++)
	{
		m_stBuJianPlusType = (*arBuJianPlusType)[i];
		arBJ.push_back(m_stBuJianPlusType);
	}
	// ��ռ�¼
	arBuJianPlusType->clear();	
	Juint16 nfieldtypeid=0;
	Juint16 nstafieldid=0;
	DATAID_TYPE ncomponentid=0;
	Juint32 npnodeid=0;
	vector<DWTopoPort> arDWTopoPort;
	DWTopoPort dwPort;
	bool	   bRepeat=false;
	for (i=0; i<nSize; i++)
	{
		bRepeat = false;
		// �������բ�Ķ˿ں��б�Ĳ��������ӣ���Ҫ��ʾ����
		m_stBuJianPlusType = arBJ[i];
		// ȡ��բ������,վ�������,����Ԫ�����
		nfieldtypeid = 0;
		nstafieldid = 0;
		ncomponentid = 0;
		sql.Format("select FIELDTYPE, STAFIELDID, COMPONENTID from daozha where id=%d", m_stBuJianPlusType.wID);
		miaoshu->PrepareSQL(sql.GetBuf());
		miaoshu->BindCol(IES_SQL_USMALLINT, 0, &nfieldtypeid);
		miaoshu->BindCol(IES_SQL_USMALLINT, 0, &nstafieldid);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &ncomponentid);
		miaoshu->Exec();
		if(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			// ���ݵ�բ��վid,������,վ�������,����Ԫ����Ŷ�λ��բ�˿ں�
			npnodeid = 0;
			sql.Format("select pnodeid from dwtopoport where changzhanid=%d and FIELDTYPEID=%d and FIELDID=%d ", 
				m_stBuJianPlusType.wChangZhan,nfieldtypeid,nstafieldid);
			miaoshu->PrepareSQL(sql.GetBuf());
			miaoshu->BindCol(IES_SQL_UINT, 0, &npnodeid);
			miaoshu->Exec();
			while(miaoshu->Fetch() && !miaoshu->IsEnd())
			{
				// �����˶˿ں��Ƿ�������������
				arDWTopoPort.clear();
				GetDWTopoPort(npnodeid, &arDWTopoPort);
				int j = 0;
				for (j=0; j<arDWTopoPort.size(); j++) 
				{
					dwPort = arDWTopoPort[j];
					if (dwPort.wChangZhanID != m_stBuJianPlusType.wChangZhan 
						||dwPort.wFieldTypeID != nfieldtypeid
						||dwPort.wFieldID != nstafieldid)
					{
						bRepeat = true;
						break;
					}
				}
			}	
		}
		if (bRepeat)
		{
			arBuJianPlusType->push_back(m_stBuJianPlusType);
		}
	}
// EMS-Mend>
	
	return arBuJianPlusType->size()>0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ������վ�ı���ID�����֣���������ID�������������ͣ���������ID���ݽṹ baohu
// (����վID�������������������ͣ���������ID����)
// ��ڣ���վID����վ��������ָ��
// ���ڣ����������롢��վ��������
// Date: 2002.10.29
//=============================================================================
Jint32 CMSData::GetCZBHInfo(DATAID_TYPE wChangZhanID, ACZBHInfo* arCZBHInfo)
{
	if (!arCZBHInfo)		return DB_INVALID_PARAM;

	CONNECTMSDB();
	arCZBHInfo->clear();
	SCZBHInfo	stCZBHInfo;
	CIIString sql;
	sql.Format( "SELECT ID, MingZi, BaoHuLeiXingID, BuJianLeiXingID, BuJianID FROM BaoHu "
				"WHERE ChangZhanID=%d ORDER BY BuJianLeiXingID,BuJianID", wChangZhanID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &stCZBHInfo.wID);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, stCZBHInfo.szMingZi);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &stCZBHInfo.wBaoHuLeiXingID);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &stCZBHInfo.byBuJianLeiXingID);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &stCZBHInfo.wBuJianID);
//	miaoshu->BindCol(IES_SQL_STRING, SHUOMINGLEN, stCZBHInfo.szShuoMing);
	miaoshu->Exec();

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		arCZBHInfo->push_back(stCZBHInfo);
	}

	return arCZBHInfo->size()>0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}
//=============================================================================
// ȡ����ʱ�θ�������ʼʱ��
// ��ڣ�ʱ�θ�������ֹʱ��ṹָ��
// ���ڣ����������롢ʱ�θ�������ֹʱ��
// Date: 2002.10.29
//=============================================================================

Jint32 CMSData::GetKHShiDuan(Juint8& bySDNum, STimeInfo* pSDV)
{
	if (!pSDV)		return DB_INVALID_PARAM;

	CONNECTMSDB();
	miaoshu->PrepareSQL("SELECT VSDNum, VKH0, VKH1, VKH2, VKH3, VKH4, VKH5, VKH6, VKH7 FROM YunXingCanShu");
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &bySDNum);
	for (Jint16 i=0; i<8; i++)
		miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, pSDV+i);
	miaoshu->Exec();

	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ��ѹ����������ֵ(���ޡ����ޣ���289��)����ܶ�Ϊ1����һ��
// �Ӹ��ɼƻ����л�ȡ["Week"ȱʡΪ0] �븺�ɼƻ����ݵ���������ֻ��һ��Ŀ���ֵ
// ��ڣ���������ʽ������������ָ��
// ���ڣ����������롢����������ֵ
// Date: 2003.3.10
//=============================================================================
Jint32	CMSData::GetDYKaoHeXian(SMiaoShuParam* pMSParam, Jfloat* pUpVal, Jfloat* pDnVal)
{
	return GetFHJiHuaOfWeek(pMSParam, 0, pUpVal, pDnVal);
}


//=============================================================================
// ���ݲ������ͺͲ�����Ż�ȡң�����Ŀɿ�����
// ��ڣ��������͡�����ID��ң�����Ե�ַ
// ���ڣ����������롢ң������
// Date: 2002.10.29
//=============================================================================
Jint32 CMSData::GetBuJianKeKong(Juint8 byBJType, DATAID_TYPE wIDValue, Juint8& byYKAttr)
{
	if (   byBJType != KaiGuan_ID && byBJType != DaoZha_ID
		&& byBJType != BaoHu_ID && byBJType != BianYaQi_ID
		&& byBJType != XuNiZHTLiang_ID )
		return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(byBJType);
	sql.Format("SELECT KeKong FROM %s WHERE ID=%d", strBiaoMing.GetBuf(), wIDValue);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byYKAttr);
	miaoshu->Exec();
	int ret = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
	miaoshu->CloseSQL();
//EMS-Mend<���»� 2007.12.17 19:48
//�޸�ԭ�򣺻�ȡǰ�õ�ң�������־
	if( ret != DB_SUCCESS )
		return ret;

	TK_KaiGuan KaiGuan;
	TK_DaoZha Daozha;
	TK_BaoHu BaoHu;
	TK_BianYaQi BianYaQi;
	TK_XuNiZHTLiang XuNiZHTLiang;
	DATAID_TYPE m_wStation = 0;
	int nret1 = 1;
	int nret2 = 1;

	switch(byBJType) 
	{
	case KaiGuan_ID:		
		GetKaiGuan(wIDValue, &KaiGuan);
		m_wStation = KaiGuan.wChangZhanID;
		break;
	case DaoZha_ID:	
		GetDaoZha(wIDValue, &Daozha);
		m_wStation = Daozha.wChangZhanID;
		break;
	case BaoHu_ID:		
		GetBaoHu(wIDValue, &BaoHu);
		m_wStation = BaoHu.wChangZhanID;
		break;
	case BianYaQi_ID:
		GetBianYaQi(wIDValue, &BianYaQi);
		m_wStation = BianYaQi.wChangZhanID;
		break;
	case XuNiZHTLiang_ID:
		CMSData::GetXuNiZHTLiang(wIDValue, &XuNiZHTLiang);
		m_wStation = XuNiZHTLiang.wChangZhanID;
		break;
	default:
		break;
	}

	SMiaoShuParam param = { byBJType, KG_RTUYX1, wIDValue, m_wStation };//Ĭ��Ϊ����	

	switch(byBJType) 
	{
	case DaoZha_ID:	
		param.byBuJianCanShuID = DZ_RTUYX1;
		break;
	case BaoHu_ID:		
		param.byBuJianCanShuID = BH_BHState;
		break;
	case BianYaQi_ID:
		param.byBuJianCanShuID = BYQ_ShengJiang;
		break;
	case XuNiZHTLiang_ID:
		param.byBuJianCanShuID = XNZT_XNState;
		break;
	default:
		break;
	}

	AComDataWhere aDataWhere;
	Jint32 retcode = GetComDataWhere(&param, &aDataWhere, RDT_Byte, RTU_Receive);
	Juint8 byCcmYKAttr = 0 ;
	if (aDataWhere.size() > 0)
	{
		sql.Format("SELECT BYYKVALIDFLAG FROM COMBYTEDATA WHERE WRTUID=%d AND WORDER=%d AND BYTYPE=0", aDataWhere[0].wRTUID, aDataWhere[0].wPoint);
		miaoshu->PrepareSQL(sql.GetBuf());
		miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byCcmYKAttr);
		miaoshu->Exec();
		ret = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
		if( ret == DB_SUCCESS )
			byYKAttr = byYKAttr * byCcmYKAttr;
	}
	miaoshu->CloseSQL();
//EMS-Mend>
	return ret;
}

Jint32 CMSData::SetBuJianKeKong(Juint8 byBJType, DATAID_TYPE wIDValue, Juint8 byYKAttr)
{
	if (   byBJType != KaiGuan_ID && byBJType != DaoZha_ID
		&& byBJType != BaoHu_ID && byBJType != BianYaQi_ID
		&& byBJType != XuNiZHTLiang_ID )
		return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString sql;
	//sunxiaofeng  2007.01.09  begin
	TK_KaiGuan KaiGuan;
	TK_DaoZha Daozha;
	TK_BaoHu BaoHu;
	TK_BianYaQi BianYaQi;
	TK_XuNiZHTLiang XuNiZHTLiang;
	DATAID_TYPE m_wStation = 0;
	int nret1 = 1;
	int nret2 = 1;


	switch(byBJType) 
	{
	case KaiGuan_ID:		
		GetKaiGuan(wIDValue, &KaiGuan);
		m_wStation = KaiGuan.wChangZhanID;
		break;
	case DaoZha_ID:	
		GetDaoZha(wIDValue, &Daozha);
		m_wStation = Daozha.wChangZhanID;
		break;
	case BaoHu_ID:		
		GetBaoHu(wIDValue, &BaoHu);
		m_wStation = BaoHu.wChangZhanID;
		break;
	case BianYaQi_ID:
		GetBianYaQi(wIDValue, &BianYaQi);
		m_wStation = BianYaQi.wChangZhanID;
		break;
	case XuNiZHTLiang_ID:
		CMSData::GetXuNiZHTLiang(wIDValue, &XuNiZHTLiang);
		m_wStation = XuNiZHTLiang.wChangZhanID;
		break;
	default:
		break;
	}

	SMiaoShuParam param = { byBJType, KG_RTUYX1, wIDValue, m_wStation };//Ĭ��Ϊ����	
//EMS-Mend<���»� 2007.12.17 19:22
//�޸�ԭ�򣺲������Ͳ�ͬ����������Ҳ��ͬ
//	//EMS-Mend< ��㳬 2007.10.11 ����ǵ�բ,����Ĳ�������
//	if( byBJType == DaoZha_ID )
//		param.byBuJianCanShuID = DZ_RTUYX1;
//	//EMS-Mend>
	switch(byBJType) 
	{
	case DaoZha_ID:	
		param.byBuJianCanShuID = DZ_RTUYX1;
		break;
	case BaoHu_ID:		
		param.byBuJianCanShuID = BH_BHState;
		break;
	case BianYaQi_ID:
		param.byBuJianCanShuID = BYQ_ShengJiang;
		break;
	case XuNiZHTLiang_ID:
		param.byBuJianCanShuID = XNZT_XNState;
		break;
	default:
		break;
	}
//EMS-Mend>

	AComDataWhere aDataWhere;
	Jint32 retcode = GetComDataWhere(&param, &aDataWhere, RDT_Byte, RTU_Receive);

	if (aDataWhere.size() > 0)
	{
		sql.Format("UPDATE COMBYTEDATA SET BYYKVALIDFLAG=%d WHERE WRTUID=%d AND WORDER=%d AND BYTYPE=0", byYKAttr, aDataWhere[0].wRTUID, aDataWhere[0].wPoint);
		miaoshu->PrepareSQL(sql.GetBuf());
		nret1 = miaoshu->Exec();
		miaoshu->CloseSQL();	
	}

	//sunxiaofeng  2007.01.09  end
	
	CIIString strBiaoMing = GetBiaoMing(byBJType);
	sql.Format("UPDATE %s SET KeKong=%d WHERE ID=%d", strBiaoMing.GetBuf(), byYKAttr, wIDValue);
	miaoshu->PrepareSQL(sql.GetBuf());
	nret2 = miaoshu->Exec();
	miaoshu->CloseSQL();
	return (nret1 > 0 && nret2 > 0) ? DB_SUCCESS : DB_ERROR;
}

//EMS-Mend< ��㳬 2007.7.26 11:43
//�޸�ԭ��:��ȡ/���ÿ��ص�ң�ظ�������
Jint32 CMSData::GetBuJianYkFushu(Juint8 byBJType, DATAID_TYPE wIDValue, Juint8& byYKAttr)
{
	byYKAttr = 1;	// EMS-Mend< baizy 2008.5.21, Ĭ��Ϊ��Ҫ����
	if (   byBJType != KaiGuan_ID && byBJType != DaoZha_ID
		&& byBJType != BaoHu_ID && byBJType != BianYaQi_ID
		&& byBJType != XuNiZHTLiang_ID )
		return DB_INVALID_PARAM;
	CONNECTMSDB();

	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(byBJType);
	sql.Format("SELECT REPEAT FROM %s WHERE ID=%d", strBiaoMing.GetBuf(), wIDValue);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byYKAttr);
	miaoshu->Exec();
	int ret = (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
	miaoshu->CloseSQL();

	return ret;
}
Jint32 CMSData::SetBuJianYkFushu(Juint8 byBJType, DATAID_TYPE wIDValue, Juint8 byYKAttr)
{
	if (   byBJType != KaiGuan_ID && byBJType != DaoZha_ID
		&& byBJType != BaoHu_ID && byBJType != BianYaQi_ID
		&& byBJType != XuNiZHTLiang_ID )
		return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(byBJType);
	sql.Format("UPDATE %s SET REPEAT=%d WHERE ID=%d",strBiaoMing.GetBuf(), byYKAttr, wIDValue);
	miaoshu->PrepareSQL(sql.GetBuf());
	int ret = miaoshu->Exec();
	miaoshu->CloseSQL();
	return ( ret > 0 ) ? DB_SUCCESS : DB_ERROR;
}
//EMS-Mend>


//=============================================================================
// ��ȡ��·����ʼ��վ����ֹ��վ
// ��ڣ��������͡�����ID����ֹ��վ������
// ���ڣ����������롢��ֹ��վID
// Date: 2002.10.29
//=============================================================================

Jint32 CMSData::GetXLChangzhan(Juint8 byBJType, DATAID_TYPE wIDValue, DATAID_TYPE& wQiCZID, DATAID_TYPE& wZhiCZID)
{
	if (byBJType != XianLu_ID)		return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString sql;
	sql.Format("SELECT QiChangZhanID, ZhChangZhanID FROM XianLu WHERE ID=%d", wIDValue);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wQiCZID);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wZhiCZID);
	miaoshu->Exec();

	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
}
//=============================================================================
// �ж�ĳ��վ�Ƿ�߱�˫ͨ�� ComJshRTU
// ��ڣ�
// ���ڣ�
// Date: 2002.10.29 ???????????????
//=============================================================================

Jint32 CMSData::GetChangZhanChannel(DATAID_TYPE wCZID, ARTUChannel* pArRTUChannel)
{
	if (pArRTUChannel == NULL)		return DB_INVALID_PARAM;
	CONNECTMSDB();
	pArRTUChannel->clear();

	SRTUChannel	rtuch;
	Juint8	Channel[4];
	CIIString sql;
	if (wCZID>0)
		sql.Format("SELECT wChangZhanID,wRTUID,strName,byMainChPtlType,byMainChType,bySlaveChPtlType,bySlaveChType FROM ComRTU WHERE wChangZhanID=%d ORDER BY strName", wCZID);
	else
		sql.Format("SELECT wChangZhanID,wRTUID,strName,byMainChPtlType,byMainChType,bySlaveChPtlType,bySlaveChType FROM ComRTU ORDER BY wChangZhanID, strName");

	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &rtuch.wCZID);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &rtuch.wRTUNum);
	miaoshu->BindCol(IES_SQL_STRING, MINGZILEN, rtuch.szMingZi);
	for (Jint16 i=0; i<4; i++)
		miaoshu->BindCol(IES_SQL_UTINYINT, 0, Channel+i);
	miaoshu->Exec();

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		rtuch.byChNum = (Channel[0]==0 || Channel[1]==0) ? 0:1;
		rtuch.byChNum += (Channel[2]==0 || Channel[3]==0) ? 0:1;
		pArRTUChannel->push_back(rtuch);
	}

	return (pArRTUChannel->size()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ��·����ѹ��������������ɡ�ע������Ӧ�Ŀ��ػ�CT
// ��ڣ��������͡�����ID����������
// ���ڣ��������͡�����ID����������������������
// Date: 2002.11.7
//=============================================================================

Jint32 CMSData::GetKaiGuanOrCT(Juint8& byBJLX, DATAID_TYPE& wBJID, Juint16& byBJCS)
{
	struct tagRelation {
		Juint8	CompType, CompParam, RelComp1Type, RelComp1Param, RelComp2Type, RelComp2Param;
		Jchar	*FieldName;
	};
	static struct tagRelation Relation[] = {
		{ XianLu_ID, XL_QiP, KaiGuan_ID, KG_P, CT_ID, CT_P,		"QiBJType, QiDY1ID", },
		{ XianLu_ID, XL_QiQ, KaiGuan_ID, KG_Q, CT_ID, CT_Q,		"QiBJType, QiDY1ID", },
		{ XianLu_ID, XL_QiI, KaiGuan_ID, KG_Ia, CT_Ia, CT_Ia,	"QiBJType, QiDY1ID", },
		{ XianLu_ID, XL_ZhP, KaiGuan_ID, KG_P, CT_ID, CT_P,		"ZhBJType, ZhDY1ID", },
		{ XianLu_ID, XL_ZhQ, KaiGuan_ID, KG_Q, CT_ID, CT_Q,		"ZhBJType, ZhDY1ID", },
		{ XianLu_ID, XL_ZhI, KaiGuan_ID, KG_Ia, CT_Ia, CT_Ia,	"ZhBJType, ZhDY1ID", },

		{ BianYaQi_ID, BYQ_PGao, KaiGuan_ID, KG_P, CT_ID, CT_P,		"GaoBJ1Type, GaoBJ1ID", },
		{ BianYaQi_ID, BYQ_QGao, KaiGuan_ID, KG_Q, CT_ID, CT_Q,		"GaoBJ1Type, GaoBJ1ID", },
		{ BianYaQi_ID, BYQ_IGao, KaiGuan_ID, KG_Ia, CT_ID, CT_Ia,	"GaoBJ1Type, GaoBJ1ID", },
		{ BianYaQi_ID, BYQ_PZhong, KaiGuan_ID, KG_P, CT_ID, CT_P,	"ZhongBJ1Type, ZhongBJ1ID", },
		{ BianYaQi_ID, BYQ_QZhong, KaiGuan_ID, KG_Q, CT_ID, CT_Q,	"ZhongBJ1Type, ZhongBJ1ID", },
		{ BianYaQi_ID, BYQ_IZhong, KaiGuan_ID, KG_Ia, CT_ID, CT_Ia,	"ZhongBJ1Type, ZhongBJ1ID", },
		{ BianYaQi_ID, BYQ_PDi, KaiGuan_ID, KG_P, CT_ID, CT_P,		"DiBJ1Type, DiBJ1ID", },
		{ BianYaQi_ID, BYQ_QDi, KaiGuan_ID, KG_Q, CT_ID, CT_Q,		"DiBJ1Type, DiBJ1ID", },
		{ BianYaQi_ID, BYQ_IDi, KaiGuan_ID, KG_Ia, CT_ID, CT_Ia,	"DiBJ1Type, DiBJ1ID", },

		{ FuHe_ID, FH_P, KaiGuan_ID, KG_P, CT_ID, CT_P,		"LJBJType, BJ1ID", },
		{ FuHe_ID, FH_Q, KaiGuan_ID, KG_Q, CT_ID, CT_Q,		"LJBJType, BJ1ID", },
		{ FuHe_ID, FH_I, KaiGuan_ID, KG_Ia, CT_ID, CT_Ia,	"LJBJType, BJ1ID", },

		{ ZhuRu_ID, ZR_P, KaiGuan_ID, KG_P, CT_ID, CT_P,	"DYBJId, PId", },
		{ ZhuRu_ID, ZR_Q, KaiGuan_ID, KG_Q, CT_ID, CT_Q,	"DYBJId, PId", },
		{ ZhuRu_ID, ZR_I, KaiGuan_ID, KG_Ia, CT_ID, CT_Ia,	"DYBJId, PId", },

	};

	Juint16 k;
	for (k=0; k<sizeof(Relation)/sizeof(Relation[0]); k++)
	{
		if (byBJLX==Relation[k].CompType && byBJLX==Relation[k].CompParam)
			break;
	}
	if (k>=sizeof(Relation)/sizeof(Relation[0]))		return DB_INVALID_PARAM;

	CONNECTMSDB();

	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(byBJLX);
	sql.Format("SELECT %s FROM %s WHERE ID=%d", Relation[k].FieldName,
		strBiaoMing.GetBuf(), wBJID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byBJLX);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wBJID);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &byBJCS);
	miaoshu->Exec();

	if (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		if (byBJLX==Relation[k].RelComp1Type)
			byBJCS = Relation[k].RelComp1Param;
		else if (byBJLX==Relation[k].RelComp2Type)
			byBJCS = Relation[k].RelComp2Param;

		return DB_SUCCESS;
	}
	else
		return DB_NO_DATA_FOUND;
}

//=============================================================================
// ȡ���ض�ӦCT, ĸ�߶�ӦPT (һ��ң��)
// ��ڣ��������͡�����ID����������
// ���ڣ��������͡�����ID����������������������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetCorrComp(Juint8& byBJLX, DATAID_TYPE& wBJID, Juint16& byBJCS)
{
	if (byBJLX == CT_ID || byBJLX == PT_ID)
		return DB_SUCCESS;
	CONNECTMSDB();

	static Juint8 KaiGuanParam[] = {KG_P, KG_Q, KG_Ia, KG_Ib, KG_Ic, KG_Io,	KG_Ih, KG_S, KG_Cos, KG_F};
	//EMS-Mend<�����䣬2008-06-13
//	static Juint8 CTParam[]      = {CT_P, CT_Q, CT_Ia};
	static Juint8 CTParam[]      = {CT_P, CT_Q, CT_Ia, CT_Ib, CT_Ic, CT_Io, CT_Ih, CT_S, CT_Cos, CT_F};
	if(byBJLX == KaiGuan_ID)
	{
		if(byBJCS >= KG_PMax && byBJCS <= KG_FMinTime)
		{
			byBJCS = KaiGuanParam[(byBJCS - KG_PMax)/4];
		}
		else if (byBJCS >= KG_PMMax && byBJCS <= KG_SHHgl)
		{
			byBJCS = KaiGuanParam[(byBJCS - KG_PMMax)/14];
		}
	}
	//if(byBJLX == ChangZhan_ID)
	//{
	//	if(byBJCS >= CZ_PMMax && byBJCS <= CZ_QHHgl)
	//	{
	//		byBJCS = (byBJCS - CZ_PMMax)/14 + CZ_P;
	//	}
	//}
	//EMS-Mend>

	Juint16 k=0;
	DATAID DataID;
	CIIString sql;
	DATAID_TYPE wIDValue = 0;

	//wugc<2012.4.23	
	//������״̬����
	sql.Format("SELECT id FROM xunizhtliang WHERE DYBJTYPE=%d and DYBJID=%d and DYBJPARAM=%d", 
		byBJLX,wBJID,byBJCS);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &(*((DATAID_TYPE*)&(wIDValue))));
	if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		byBJLX = XuNiZHTLiang_ID;
		wBJID = wIDValue;
		byBJCS = XNZT_XNState;
		miaoshu->CloseSQL();
		return DB_SUCCESS;
	}
	miaoshu->CloseSQL();
	//�����ⵥ������
	sql.Format("SELECT id FROM XuNiDMNLiang WHERE DYBJTYPE=%d and DYBJID=%d and DYBJPARAM=%d", 
		byBJLX,wBJID,byBJCS);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &(*((DATAID_TYPE*)&(wIDValue))));
	if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		byBJLX = XuNiDMNLiang_ID;
		wBJID = wIDValue;
		byBJCS = XN_XNValue;
		miaoshu->CloseSQL();
		return DB_SUCCESS;
	}
	miaoshu->CloseSQL();

	//������˫������
	sql.Format("SELECT id FROM xunismnliang WHERE DYBJType=%d and DYBJID=%d and DYBJParam=%d", 
		byBJLX,wBJID,byBJCS);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &(*((DATAID_TYPE*)&(wIDValue))));
	if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		byBJLX = XuNiSMNLiang_ID;
		wBJID = wIDValue;
		byBJCS = SJXN_XNValue;
		miaoshu->CloseSQL();
		return DB_SUCCESS;
	}
	miaoshu->CloseSQL();
	//wugc>

	switch (byBJLX)
	{
	// ���� ///////////////////////////
	case KaiGuan_ID:
		for (k=0; k<countof(KaiGuanParam); k++)
		{
			if (byBJCS == KaiGuanParam[k])
				break;
		}
		if (k >= countof(KaiGuanParam))	// not meet
			break;

		DataID.byBJType  = CT_ID;
		DataID.byCSHType = CT_P + k;	// offset + k
		sql.Format("SELECT CTID FROM KaiGuan WHERE ID=%d", wBJID);
		miaoshu->PrepareSQL(sql.GetBuf());
		wIDValue = DataID.wIDValue;
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &(*((DATAID_TYPE*)&(wIDValue))));	
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			DataID.wIDValue = wIDValue;
			byBJLX	= DataID.byBJType;
			wBJID	= DataID.wIDValue;
			byBJCS	= DataID.byCSHType;
			return DB_SUCCESS;
		}
		break;

	// ĸ�� ///////////////////////////
	//	static Juint8 MuXianParam[]  = {MX_UValue};
	case MuXian_ID:
		{
			DataID.byBJType  = PT_ID;
			sql.Format("SELECT DYPTID, PTPhase FROM MuXian WHERE ID=%d", wBJID);
			miaoshu->PrepareSQL(sql.GetBuf());
			wIDValue = DataID.wIDValue;
			miaoshu->BindCol(SQL_DATAID_TYPE, 0, &(*((DATAID_TYPE*)&(wIDValue))));
			miaoshu->BindCol(IES_SQL_USMALLINT, 0,  &(*(&(DataID.byCSHType))));			
			if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
			{
				DataID.wIDValue = wIDValue;
				byBJLX	= DataID.byBJType;
				wBJID	= DataID.wIDValue;
				byBJCS	= PT_VA + DataID.byCSHType;
				return DB_SUCCESS;
			}
		}
		break;

	// ��· ///////////////////////////
	//	XianLuParam[] = {XL_QiP, XL_QiQ, XL_QiI, XL_ZhP, XL_ZhQ, XL_ZhI};
	case XianLu_ID:
		switch (byBJCS)
		{
		case XL_QiP:
		case XL_QiQ:
		case XL_QiI:
			sql.Format("SELECT QiBJType, QiDY1ID FROM XianLu WHERE ID=%d", wBJID);
			break;
			
		case XL_ZhP:
		case XL_ZhQ:
		case XL_ZhI:
			sql.Format("SELECT ZhBJType, ZhDY1ID FROM XianLu WHERE ID=%d", wBJID);
			break;

		default:
			return DB_INVALID_PARAM;
		}
		miaoshu->PrepareSQL(sql.GetBuf());  
		DataID.wIDValue = wIDValue;
		miaoshu->BindCol(IES_SQL_UTINYINT,  0, &(*((Juint8*)&(DataID.byBJType))));
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &(*((DATAID_TYPE*)&(wIDValue))));
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			DataID.wIDValue = wIDValue;

			// �ɹ����жϲ�������
			if (DataID.byBJType == KaiGuan_ID)
			{
				if (byBJCS < XL_ZhP)	// ���
					DataID.byCSHType = KaiGuanParam[byBJCS - XL_QiP];
				else					// �ղ�
					DataID.byCSHType = KaiGuanParam[byBJCS - XL_ZhP];
				// ����Ҫ�ڹ���øú���
				Jint32 code = GetCorrComp(*((Juint8*)&(DataID.byBJType)), *((DATAID_TYPE*)&(wIDValue)), *((Juint16*)&(DataID.byCSHType)));
				DataID.wIDValue = wIDValue;
				if (code == DB_SUCCESS)
				{
					byBJLX	= DataID.byBJType;
					wBJID	= DataID.wIDValue;
					byBJCS	= DataID.byCSHType;
				}
				return code;
			}
			else if (DataID.byBJType == CT_ID)
			{
				byBJLX	= DataID.byBJType;
				wBJID	= DataID.wIDValue;
				if (byBJCS < XL_ZhP)	// ���
					DataID.byCSHType = CTParam[byBJCS - XL_QiP];
				else					// �ղ�
					DataID.byCSHType = CTParam[byBJCS - XL_ZhP];

				byBJCS	= DataID.byCSHType;
				return DB_SUCCESS;
			}
			else
			{
				return DB_INVALID_PARAM;
			}
		}
		break;

	// ��ѹ�� ///////////////////////////
	//static Juint8 BianYaQiParam1[] = {BYQ_PGao, BYQ_QGao, BYQ_IGao};
	//static Juint8 BianYaQiParam2[] = {BYQ_PZhong, BYQ_QZhong, BYQ_IZhong};
	//static Juint8 BianYaQiParam3[] = {BYQ_PDi, BYQ_QDi, BYQ_IDi};
	case BianYaQi_ID:
		switch (byBJCS)
		{
		case BYQ_PGao:
		case BYQ_QGao:
		case BYQ_IGao:
			sql.Format("SELECT GaoBJ1Type, GaoBJ1ID FROM BianYaQi WHERE ID=%d", wBJID);
			break;

		case BYQ_PZhong:
		case BYQ_QZhong:
		case BYQ_IZhong:
			sql.Format("SELECT ZhongBJ1Type, ZhongBJ1ID FROM BianYaQi WHERE ID=%d", wBJID);
			break;
			
		case BYQ_PDi:
		case BYQ_QDi:
		case BYQ_IDi:
			sql.Format("SELECT DiBJ1Type, DiBJ1ID FROM BianYaQi WHERE ID=%d", wBJID);
			break;
			
		default:
			return DB_INVALID_PARAM;
		}
		miaoshu->PrepareSQL(sql.GetBuf());
		miaoshu->BindCol(IES_SQL_UTINYINT,  0, &(*((Juint8*)&(DataID.byBJType))));
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &(*((DATAID_TYPE*)&(wIDValue))));
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			DataID.wIDValue = wIDValue;
			// �ɹ����жϲ�������
			if (DataID.byBJType == KaiGuan_ID)
			{
				if (byBJCS < BYQ_PZhong)		// �߲�
					DataID.byCSHType = KaiGuanParam[byBJCS - BYQ_PGao];
				else if (byBJCS >= BYQ_PDi)		// �Ͳ�
					DataID.byCSHType = KaiGuanParam[byBJCS - BYQ_PDi];
				else							// �в�
					DataID.byCSHType = KaiGuanParam[byBJCS - BYQ_PZhong];
				wIDValue = DataID.wIDValue;
				Jint32 code = GetCorrComp(*((Juint8*)&(DataID.byBJType)), *((DATAID_TYPE*)&(wIDValue)), *((Juint16*)&(DataID.byCSHType)));
				DataID.wIDValue = wIDValue;
				if (code == DB_SUCCESS)
				{
					byBJLX	= DataID.byBJType;
					wBJID	= DataID.wIDValue;
					byBJCS	= DataID.byCSHType;
				}
				return code;
			}
			else if (DataID.byBJType == CT_ID)
			{
				byBJLX	= DataID.byBJType;
				wBJID	= DataID.wIDValue;
				if (byBJCS < BYQ_PZhong)		// �߲�
					DataID.byCSHType = CTParam[byBJCS - BYQ_PGao];
				else if (byBJCS >= BYQ_PDi)		// �Ͳ�
					DataID.byCSHType = CTParam[byBJCS - BYQ_PDi];
				else							// �в�
					DataID.byCSHType = CTParam[byBJCS - BYQ_PZhong];
				
				byBJCS	= DataID.byCSHType;
				return DB_SUCCESS;
			}
			else
			{
				return DB_INVALID_PARAM;
			}
		}
		break;
		
	// ����� ///////////////////////////
	case FaDianJi_ID:
	case ChangZhan_ID:
		break;
		
	// ���� ///////////////////////////
	//static Juint8 FuHeParam[] = {FH_P, FH_Q, FH_I};
	case FuHe_ID:
		switch (byBJCS)
		{
		case FH_P:
		case FH_Q:
		case FH_I:
			sql.Format("SELECT LJBJType, LJDY1ID FROM FuHe WHERE ID=%d", wBJID);
			break;
		default:
			return DB_INVALID_PARAM;
			break;
		}
		miaoshu->PrepareSQL(sql.GetBuf());
		wIDValue = DataID.wIDValue;
		miaoshu->BindCol(IES_SQL_UTINYINT,  0, &(*((Juint8*)&(DataID.byBJType))));
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &(*((DATAID_TYPE*)&(wIDValue))));
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			DataID.wIDValue = wIDValue;
			// �ɹ����жϲ�������
			if (DataID.byBJType == KaiGuan_ID)
			{
				DataID.byCSHType = KaiGuanParam[byBJCS - FH_P];
				// ����Ҫ�ڹ���øú���
				Jint32 code = GetCorrComp(*((Juint8*)&(DataID.byBJType)), *((DATAID_TYPE*)&(wIDValue)),*((Juint16*)&( DataID.byCSHType)));
				DataID.wIDValue = wIDValue;
				if (code == DB_SUCCESS)
				{
					byBJLX	= DataID.byBJType;
					wBJID	= DataID.wIDValue;
					byBJCS	= DataID.byCSHType;
				}
				return code;
			}
			else if (DataID.byBJType == CT_ID)
			{
				byBJLX	= DataID.byBJType;
				wBJID	= DataID.wIDValue;
				DataID.byCSHType = CTParam[byBJCS - FH_P];
				
				byBJCS	= DataID.byCSHType;
				return DB_SUCCESS;
			}
			else
			{
				return DB_INVALID_PARAM;
			}
		}
		break;
		
	// ע�� ///////////////////////////
	//static Juint8 ZhuRuParam[] = {ZR_P, ZR_Q, ZR_I};
	case ZhuRu_ID:
		switch (byBJCS)
		{
		case ZR_P:
		case ZR_Q:
		case ZR_I:
			sql.Format("SELECT DYBJType, PId FROM ZhuRu WHERE ID=%d", wBJID);
			break;
		default:
			return DB_INVALID_PARAM;
			break;
		}
		miaoshu->PrepareSQL(sql.GetBuf());
		wIDValue = DataID.wIDValue;
		miaoshu->BindCol(IES_SQL_UTINYINT,  0, &(*((Juint8*)&(DataID.byBJType))));
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &(*((DATAID_TYPE*)&(wIDValue))));
		//EMS-Mend>
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			DataID.wIDValue = wIDValue;

			// �ɹ����жϲ�������
			if (DataID.byBJType == KaiGuan_ID)
			{
				DataID.byCSHType = KaiGuanParam[byBJCS - ZR_P];
				Jint32 code = GetCorrComp(*((Juint8*)&(DataID.byBJType)), *((DATAID_TYPE*)&(wIDValue)), *((Juint16*)&(DataID.byCSHType)));
				DataID.wIDValue = wIDValue;
				if (code == DB_SUCCESS)
				{
					byBJLX	= DataID.byBJType;
					wBJID	= DataID.wIDValue;
					byBJCS	= DataID.byCSHType;
				}
				return code;
			}
			else if (DataID.byBJType == CT_ID)
			{
				byBJLX	= DataID.byBJType;
				wBJID	= DataID.wIDValue;
				DataID.byCSHType = CTParam[byBJCS - ZR_P];
				
				byBJCS	= DataID.byCSHType;
				return DB_SUCCESS;
			}
			else
			{
				return DB_INVALID_PARAM;
			}
		}
		break;
		
	default:
		break;
	}

	return DB_INVALID_PARAM;
}

//ȡ��ӦCT��˫���������벿�����ڹ���� (���ר��)
// ��һ�鷵��CT�����ڶ��鷵�ػ�������ŵ�˫����
Jint32 CMSData::GetCorrCompDD(Juint8& byBJLX, DATAID_TYPE& wBJID, Juint16 byBJCS, 
							  DATAID_TYPE* wIDP1, DATAID_TYPE* wIDQ1, DATAID_TYPE* wIDP2, DATAID_TYPE* wIDQ2)
{
	switch (byBJLX)
	{
	case DianWang_ID:
	case ChangZhan_ID:
	case CT_ID:
	case XuNiSMNLiang_ID:
	case DianDuBiao_ID:
		return DB_SUCCESS;
		break;

	default:
		break;
	}

	CONNECTMSDB();

	Juint8	midBJLX = byBJLX;
	DATAID_TYPE	midBJID = wBJID;
	DATAID_TYPE midP1, midQ1, midP2, midQ2;
	CIIString sql;
	switch (byBJLX)
	{
	// ���� ///////////////////////////
	case KaiGuan_ID:
		sql.Format("SELECT CTID FROM KaiGuan WHERE ID=%d", wBJID);
		miaoshu->PrepareSQL(sql.GetBuf());
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			byBJLX	= CT_ID;
			wBJID	= midBJID;
			return DB_SUCCESS;
		}
		break;

	// ��· ///////////////////////////
	case XianLu_ID:
		if ( (byBJCS >= XL_QiP && byBJCS <= XL_QiI)		// ����
			|| (byBJCS >= XL_QiDKWHP && byBJCS <= XL_QiMJFKWHQ)
			|| (byBJCS >= XL_FQiDKWHP && byBJCS <= XL_FQiMJFKWHQ) )
		{
			sql.Format("SELECT QiBJType,QiDY1ID,QiPJHDDId,QiQJHDDId,FQiPJHDDId,FQiQJHDDId FROM XianLu WHERE ID=%d", wBJID);
		}
		else if ( (byBJCS >= XL_ZhP && byBJCS <= XL_ZhI)	// �յ��
			|| (byBJCS >= XL_ZhDKWHP && byBJCS <= XL_ZhMJFKWHQ)
			|| (byBJCS >= XL_FZhDKWHP && byBJCS <= XL_FZhMJFKWHQ) )
		{
			sql.Format("SELECT ZhBJType,ZhDY1ID,ZhPJHDDId,ZhQJHDDId,FZhPJHDDId,FZhQJHDDId FROM XianLu WHERE ID=%d", wBJID);
		}
		else
		{
			return DB_INVALID_PARAM;
		}
		miaoshu->PrepareSQL(sql.GetBuf());
		miaoshu->BindCol(IES_SQL_UTINYINT,  0, &midBJLX);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midP1);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midQ1);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midP2);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midQ2);
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			if (midBJLX == KaiGuan_ID)
			{
				sql.Format("SELECT CTID FROM KaiGuan WHERE ID=%d", midBJID);
				miaoshu->PrepareSQL(sql.GetBuf());
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
				if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
				{
					midBJLX	= CT_ID;
				}
			}
			if (midBJLX == CT_ID)
			{
				byBJLX	= CT_ID;
				wBJID	= midBJID;
				if (wIDP1)		*wIDP1 = midP1;
				if (wIDQ1)		*wIDQ1 = midQ1;
				if (wIDP2)		*wIDP2 = midP2;
				if (wIDQ2)		*wIDQ2 = midQ2;
				return DB_SUCCESS;
			}
			else
			{
				return DB_INVALID_PARAM;
			}
		}
		break;

	// ��ѹ�� ///////////////////////////
	case BianYaQi_ID:
		switch (byBJCS)
		{
		case BYQ_PGao:
		case BYQ_QGao:
		case BYQ_IGao:
			sql.Format("SELECT GaoBJ1Type, GaoBJ1ID FROM BianYaQi WHERE ID=%d", wBJID);
			break;
			
		case BYQ_PZhong:
		case BYQ_QZhong:
		case BYQ_IZhong:
			sql.Format("SELECT ZhongBJ1Type, ZhongBJ1ID FROM BianYaQi WHERE ID=%d", wBJID);
			break;
			
		case BYQ_PDi:
		case BYQ_QDi:
		case BYQ_IDi:
			sql.Format("SELECT DiBJ1Type, DiBJ1ID FROM BianYaQi WHERE ID=%d", wBJID);
			break;
			
		default:
			return DB_INVALID_PARAM;
		}
		miaoshu->PrepareSQL(sql.GetBuf());
		miaoshu->BindCol(IES_SQL_UTINYINT,  0, &midBJLX);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			if (midBJLX == KaiGuan_ID)
			{
				sql.Format("SELECT CTID FROM KaiGuan WHERE ID=%d", midBJID);
				miaoshu->PrepareSQL(sql.GetBuf());
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
				if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
				{
					midBJLX	= CT_ID;
				}
			}
			if (midBJLX == CT_ID)
			{
				byBJLX	= CT_ID;
				wBJID	= midBJID;
				return DB_SUCCESS;
			}
			else
			{
				return DB_INVALID_PARAM;
			}
		}
		break;

	// ����� ///////////////////////////
	case FaDianJi_ID:
		sql.Format("SELECT BJType1ID, BJ1ID FROM FaDianJi WHERE ID=%d", wBJID);
		miaoshu->PrepareSQL(sql.GetBuf());
		miaoshu->BindCol(IES_SQL_UTINYINT,  0, &midBJLX);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			if (midBJLX == KaiGuan_ID)
			{
				sql.Format("SELECT CTID FROM KaiGuan WHERE ID=%d", midBJID);
				miaoshu->PrepareSQL(sql.GetBuf());
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
				if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
				{
					midBJLX	= CT_ID;
				}
			}
			if (midBJLX == CT_ID)
			{
				byBJLX	= CT_ID;
				wBJID	= midBJID;
				return DB_SUCCESS;
			}
			else
			{
				return DB_INVALID_PARAM;
			}
		}
		break;
		
	// ���� ///////////////////////////
	case FuHe_ID:
		sql.Format("SELECT LJBJType,LJDY1ID,PJHDDId,QJHDDId,FPJHDDId,FQJHDDId FROM FuHe WHERE ID=%d", wBJID);
		miaoshu->PrepareSQL(sql.GetBuf());
		miaoshu->BindCol(IES_SQL_UTINYINT,  0, &midBJLX);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midP1);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midQ1);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midP2);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midQ2);
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			if (midBJLX == KaiGuan_ID)
			{
				sql.Format("SELECT CTID FROM KaiGuan WHERE ID=%d", midBJID);
				miaoshu->PrepareSQL(sql.GetBuf());
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
				if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
				{
					midBJLX	= CT_ID;
				}
			}
			if (midBJLX == CT_ID)
			{
				byBJLX	= CT_ID;
				wBJID	= midBJID;
				if (wIDP1)		*wIDP1 = midP1;
				if (wIDQ1)		*wIDQ1 = midQ1;
				if (wIDP2)		*wIDP2 = midP2;
				if (wIDQ2)		*wIDQ2 = midQ2;
				return DB_SUCCESS;
			}
			else
			{
				return DB_INVALID_PARAM;
			}
		}
		break;
		
	// ע�� ///////////////////////////
	case ZhuRu_ID:
		sql.Format("SELECT DYBJType, PId FROM ZhuRu WHERE ID=%d", wBJID);
		miaoshu->PrepareSQL(sql.GetBuf());
		miaoshu->BindCol(IES_SQL_UTINYINT,  0, &midBJLX);
		miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
		if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
		{
			if (midBJLX == KaiGuan_ID)
			{
				sql.Format("SELECT CTID FROM KaiGuan WHERE ID=%d", midBJID);
				miaoshu->PrepareSQL(sql.GetBuf());
				miaoshu->BindCol(SQL_DATAID_TYPE, 0, &midBJID);
				if (miaoshu->Exec() > 0 && miaoshu->Fetch() && !miaoshu->IsEnd())	// meet ID
				{
					midBJLX	= CT_ID;
				}
			}
			if (midBJLX == CT_ID)
			{
				byBJLX	= CT_ID;
				wBJID	= midBJID;
				return DB_SUCCESS;
			}
			else
			{
				return DB_INVALID_PARAM;
			}
		}
		break;
		
	default:
		break;
	}

	return DB_INVALID_PARAM;
}

///////////////////////////////////////////////////////////
// ��ȡ��·��Ӧ����һ�����ػ�CT, ��������һ�����ػ�CT
Jint32 CMSData::GetXLKaiGuan2(Juint8 byBJLX1, DATAID_TYPE wBJID1, Juint8& byBJLX2, DATAID_TYPE& wBJID2)
{
	CONNECTMSDB();

	Jint32 retcode = DB_ERROR;

	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(XianLu_ID);
	sql.Format( "SELECT QiBJType,QiDY1ID,ZhBJType,ZhDY1ID FROM %s WHERE "
				"(QiBJType=%d AND QiDY1ID=%d) OR (ZhBJType=%d AND ZhDY1ID=%d)",
				strBiaoMing.GetBuf(), byBJLX1, wBJID1, byBJLX1, wBJID1);

	Juint8	lx1, lx2;
	DATAID_TYPE	id1, id2;
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT,  0, &lx1);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &id1);
	miaoshu->BindCol(IES_SQL_UTINYINT,  0, &lx2);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &id2);

	if (miaoshu->Exec() > 0)
	{
		if (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			if (lx1 == byBJLX1 && id1 == wBJID1)
			{
				byBJLX2	= lx2;
				wBJID2	= id2;
				retcode = DB_SUCCESS;
			}
			else if (lx2 == byBJLX1 && id2 == wBJID1)
			{
				byBJLX2	= lx1;
				wBJID2	= id1;
				retcode = DB_SUCCESS;
			}
		}
		else
		{
			retcode = DB_NO_DATA_FOUND;
		}
	}
	return retcode;
}

// ��ȡ��·��Ӧ����һ�����ػ�CT, ������·����
Jint32 CMSData::GetXLKaiGuan2(DATAID_TYPE xlID, Juint16 xlCS, Juint8& byBJLX2, DATAID_TYPE& wBJID2, Juint16& byBJCS2)
{
	CONNECTMSDB();
	
	Jint32 retcode = DB_ERROR;
	
	CIIString sql;
	CIIString strBiaoMing = GetBiaoMing(XianLu_ID);
	switch (xlCS)
	{
	case XL_QiP:
	case XL_QiQ:
	case XL_QiI:
		sql.Format("SELECT ZhBJType,ZhDY1ID FROM %s WHERE ID=%d", strBiaoMing.GetBuf(), xlID);
		break;
	case XL_ZhP:
	case XL_ZhQ:
	case XL_ZhI:
		sql.Format("SELECT QiBJType,QiDY1ID FROM %s WHERE ID=%d", strBiaoMing.GetBuf(), xlID);
		break;
	default:
		return DB_INVALID_PARAM;
		break;
	}

	Juint8	lx;
	DATAID_TYPE	id;
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT,  0, &lx);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &id);
	
	if (miaoshu->Exec() > 0)
	{
		if (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			byBJLX2	= lx;
			wBJID2	= id;
			retcode = DB_SUCCESS;
			switch (xlCS)
			{
			case XL_QiP:
			case XL_ZhP:
				if (lx == KaiGuan_ID)
					byBJCS2 = KG_P;
				else if (lx == CT_ID)
					byBJCS2 = CT_P;
				else
					return DB_INVALID_PARAM;
				break;
			case XL_QiQ:
			case XL_ZhQ:
				if (lx == KaiGuan_ID)
					byBJCS2 = KG_Q;
				else if (lx == CT_ID)
					byBJCS2 = CT_Q;
				else
					return DB_INVALID_PARAM;
				break;
			case XL_QiI:
			case XL_ZhI:
				if (lx == KaiGuan_ID)
					byBJCS2 = KG_Ia;
				else if (lx == CT_ID)
					byBJCS2 = CT_Ia;
				else
					return DB_INVALID_PARAM;
				break;
			}
		}
		else
		{
			retcode = DB_NO_DATA_FOUND;
		}
	}
	return retcode;
}


//=============================================================================
// ȡϵͳ�����в���(������ʱ�Ρ������߷�ʱ�εĻ����Լ����ֲɼ�����)
// ��ڣ������������в���ָ��
// ���ڣ����в�������
// Date: 2003.1.7
//=============================================================================

Jint32 CMSData::GetSysYunXingCanShu(YunXingCanShu* pYXCanShu)
{
	if (!pYXCanShu)		return DB_INVALID_PARAM;

	CONNECTMSDB();

	STimeInfo t[64];
	CIIString sql, fields, field_one;
	fields = "TestMode,BanNo";
	Juint16 i;
	for (i=1; i<7; i++)
	{
		field_one.Format(",BanS%d", i);
		fields += field_one;
	}
	fields += ",DDCyc,ZYStart,ZYCyc,ZYQDNum,ZYHDNum,DLSDNum";
	for (i=1; i<9; i++)
	{
		field_one.Format(",DLQi%d,DLZh%d,DLSD%d", i, i, i);
		fields += field_one;
	}
	fields += ",FHZFQi,FHZFZh,FHWFQi,FHWFZh,FHRiSDNum";
	for (i=1; i<9; i++)
	{
		field_one.Format(",FHRQi%d,FHRZh%d,FHRSD%d", i, i, i);
		fields += field_one;
	}
	fields += ",VSDNum";
	for (i=0; i<8; i++)
	{
		field_one.Format(",VKH%d", i);
		fields += field_one;
	}
	fields += ",DXRiNum";
	for (i=1; i<7; i++)
	{
		field_one.Format(",DXRi%d", i);
		fields += field_one;
	}
	fields += ",DXShiNum";
	for (i=1; i<7; i++)
	{
		field_one.Format(",DXShi%d", i);
		fields += field_one;
	}
	fields += ",YXFlashResetTime";

	sql.Format("SELECT %s FROM YunXingCanShu", fields.GetBuf());
	miaoshu->PrepareSQL(sql.GetBuf());
	Juint16 k=0;
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byTestMode);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byBanNo);
	for (i=0; i<6; i++)
		miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));

	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byDDCyc);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byPDRStart);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byPDRCyc);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &pYXCanShu->wQDNum);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &pYXCanShu->wHDNum);

	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byDLSDNum);
	for (i=0; i<8; i++)
	{
		miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));
		miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));
		miaoshu->BindCol(IES_SQL_UTINYINT, 0, pYXCanShu->DLSDAttr+i);
	}

	miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));
	miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));
	miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));
	miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));

	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byFHRiSDNum);
	for (i=0; i<8; i++)
	{
		miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));
		miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));
		miaoshu->BindCol(IES_SQL_UTINYINT, 0, pYXCanShu->FHSDAttr+i);
	}

	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byVSDNum);
	for (i=0; i<8; i++)
		miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, t+(k++));

	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byDXRiNum);
	for (i=0; i<6; i++)
		miaoshu->BindCol(IES_SQL_UTINYINT, 0, pYXCanShu->DXRi+i);

	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byDXShiNum);
	for (i=0; i<6; i++)
		miaoshu->BindCol(IES_SQL_UTINYINT, 0, pYXCanShu->DXShi+i);

	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &pYXCanShu->byYXResetTime);

	miaoshu->Exec();
	if (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		k=0;
		for (i=0; i<6; i++, k++)
		{
			pYXCanShu->BanS[i].byHour = t[k].nHour;
			pYXCanShu->BanS[i].byMinute = t[k].nMinute;
		}

		for (i=0; i<8; i++, k++)
		{
			pYXCanShu->DLQi[i].byHour = t[k].nHour;
			pYXCanShu->DLQi[i].byMinute = t[k].nMinute;
			k++;
			pYXCanShu->DLZh[i].byHour = t[k].nHour;
			pYXCanShu->DLZh[i].byMinute = t[k].nMinute;
		}
		pYXCanShu->FHZFQi.byHour = t[k].nHour;
		pYXCanShu->FHZFQi.byMinute = t[k].nMinute;
		k++;
		pYXCanShu->FHZFZh.byHour = t[k].nHour;
		pYXCanShu->FHZFZh.byMinute = t[k].nMinute;
		k++;
		pYXCanShu->FHWFQi.byHour = t[k].nHour;
		pYXCanShu->FHWFQi.byMinute = t[k].nMinute;
		k++;
		pYXCanShu->FHWFZh.byHour = t[k].nHour;
		pYXCanShu->FHWFZh.byMinute = t[k].nMinute;
		k++;

		for (i=0; i<8; i++, k++)
		{
			pYXCanShu->FHRQi[i].byHour = t[k].nHour;
			pYXCanShu->FHRQi[i].byMinute = t[k].nMinute;
			k++;
			pYXCanShu->FHRZh[i].byHour = t[k].nHour;
			pYXCanShu->FHRZh[i].byMinute = t[k].nMinute;
		}

		for (i=0; i<8; i++, k++)
		{
			pYXCanShu->VKH[i].byHour = t[k].nHour;
			pYXCanShu->VKH[i].byMinute = t[k].nMinute;
		}

		return DB_SUCCESS;
	}
	else
		return DB_NO_DATA_FOUND;
}

//���ò����ı�־�������룬�ӵأ��ɿص�
//�����������־�ģ�bFlag��ʾ���뻹�ǽ��������bFlag��ʾ״̬
Jint32 CMSData::SetBujianFlag(Juint8 byBJType, DATAID_TYPE nBJID, Juint16 byCSType,
							  Jboolean bFlag, void* pValue)
{
	if (byBJType == 0 || nBJID == 0 || byCSType == 0)
		return DB_INVALID_PARAM;
	CONNECTMSDB();
	
	struct tagParam
	{
		Juint8	CompType;
		Juint8	CompParam;
		char*	FieldName;
	};

	//	if (bFlag && pValue) " SET DZState=%d,SheZhiF=1", byValue); SET SheZhiF=0
	static struct tagParam ParamYX[] =
	{
		{ KaiGuan_ID,		KG_KGState,		"", },
		{ DaoZha_ID,		DZ_DZState,		"", },
		{ BaoHu_ID,			BH_BHState,		"STValue", },
		{ XuNiZHTLiang_ID,	XNZT_XNState,	"STValue", },
	};

	//"PMVal", "PMFlag"
	//EMS-Mend<
	//���ѽ� 2006.4.27 ��ѹ����ѹ��ֽ�ͷ
//	static struct tagParam ParamYC[] = {
//
//		{ BianYaQi_ID, BYQ_FenJieTouYC, "DW", },	{ BianYaQi_ID, BYQ_T, "T", },
//		{ CT_ID, CT_P,  "P", },		{ CT_ID, CT_Q,  "Q", },		{ CT_ID, CT_Ia,  "Ia", },
//		{ CT_ID, CT_Ib, "Ib", },	{ CT_ID, CT_Ic, "Ic", },	{ CT_ID, CT_Io,  "Io", },
//		{ CT_ID, CT_Ih, "Ih", },	{ CT_ID, CT_S,	"S", },		{ CT_ID, CT_Cos, "Cos", },
//		{ CT_ID, CT_F,  "F" },
//		{ PT_ID, PT_VA,   "Ua", },		{ PT_ID, PT_VB,   "Ub", },		{ PT_ID, PT_VC,   "Uc", },
//		{ PT_ID, PT_VabX, "UabX", },	{ PT_ID, PT_VbcX, "UbcX", },	{ PT_ID, PT_VcaX, "UcaX", },
//		{ PT_ID, PT_VO,   "Uo", },		{ PT_ID, PT_VAng, "Uang", },
//		{ XuNiDMNLiang_ID, XN_XNValue, "", },
//	};
	static struct tagParam ParamYC[] = {
		
		{ BianYaQi_ID, BYQ_FenJieTouYC, "DW", },	{ BianYaQi_ID, BYQ_T, "T", },	{ BianYaQi_ID, BYQ_ZHNFenJieTouYC, "ZDW", },
		{ CT_ID, CT_P,  "P", },		{ CT_ID, CT_Q,  "Q", },		{ CT_ID, CT_Ia,  "Ia", },
		{ CT_ID, CT_Ib, "Ib", },	{ CT_ID, CT_Ic, "Ic", },	{ CT_ID, CT_Io,  "Io", },
		{ CT_ID, CT_Ih, "Ih", },	{ CT_ID, CT_S,	"S", },		{ CT_ID, CT_Cos, "Cos", },
		{ CT_ID, CT_F,  "F" },
		{ PT_ID, PT_VA,   "Ua", },		{ PT_ID, PT_VB,   "Ub", },		{ PT_ID, PT_VC,   "Uc", },
		{ PT_ID, PT_VabX, "UabX", },	{ PT_ID, PT_VbcX, "UbcX", },	{ PT_ID, PT_VcaX, "UcaX", },
		{ PT_ID, PT_VO,   "Uo", },		{ PT_ID, PT_VAng, "Uang", },
		{ XuNiDMNLiang_ID, XN_XNValue, "", },
	};
	//EMS-Mend>

	struct tagParam *Param[] = { ParamYX, ParamYC };
	int ParamCount[] = { countof(ParamYX), countof(ParamYC) };

	// ����ʽת�� // �Ѿ��������ݿ�
	GetCorrComp(byBJType, nBJID, byCSType);

	int	k, l;
	for (k=0; k<countof(ParamCount); k++)
	{
		for (l=0; l<ParamCount[k]; l++)
		{
			if (byBJType == Param[k][l].CompType 
				&& byCSType == Param[k][l].CompParam)	// meet
				break;
		}
		if (l < ParamCount[k])
			break;
	}

	if (k >= countof(ParamCount) || l >= ParamCount[k])	// not meet
		return DB_INVALID_PARAM;

	CIIString sql, fields;
	Juint8 byFlag = bFlag ? 1 : 0;
	Juint8 byValue = 0;
	Jfloat fValue = 0.0f;
	CIIString strBiaoMing = GetBiaoMing(Param[k][l].CompType);

	switch (k)
	{
	case 0:		// YX״̬
		if (!bFlag)	// ��������־
		{
			sql.Format("UPDATE %s SET SheZhiF=0 WHERE ID=%d", strBiaoMing.GetBuf(), nBJID);
		}
		else
		{
			if (pValue)
				memcpy(&byValue, pValue, sizeof(Juint8));
			byValue &= 1;
			if (Param[k][l].CompType == KaiGuan_ID && Param[k][l].CompParam == KG_KGState)
			{
				Juint8 byValue2 = byValue > 0 ? 0 : 1;
				sql.Format("UPDATE %s SET YXValue0=%d,YXValue1=%d,SheZhiF=1 WHERE ID=%d",
					strBiaoMing.GetBuf(), byValue, byValue2, nBJID);
			}
			else if(Param[k][l].CompType == DaoZha_ID && Param[k][l].CompParam == DZ_DZState)
			{
				Juint8 byValue2 = byValue > 0 ? 0 : 1;
				sql.Format("UPDATE %s SET YXValue0=%d,YXValue1=%d,SheZhiF=1 WHERE ID=%d",
					strBiaoMing.GetBuf(), byValue, byValue2, nBJID);
			} 
			else
			{
				sql.Format("UPDATE %s SET %s=%d,SheZhiF=1 WHERE ID=%d",
					strBiaoMing.GetBuf(), Param[k][l].FieldName, byValue, nBJID);
			}
		}
		break;
	case 1:		// YC ֵ
		if (!bFlag)	// ��������־
		{
			sql.Format("UPDATE %s SET %sMFlag=0 WHERE ID=%d", strBiaoMing.GetBuf(),
				Param[k][l].FieldName, nBJID);
		}
		else
		{
			if (Param[k][l].CompType == BianYaQi_ID && Param[k][l].CompParam == BYQ_FenJieTouYC)
			{
				if (pValue)
					memcpy(&byValue, pValue, sizeof(Juint8));
				sql.Format("UPDATE %s SET %sMVal=%d,%sMFlag=1 WHERE ID=%d",
					strBiaoMing.GetBuf(), Param[k][l].FieldName, 
					byValue, Param[k][l].FieldName, nBJID);
			}
			//EMS-Mend<
			//���ѽ� 2006.4.27 ��ѹ����ѹ��ֽ�ͷ
			else if (Param[k][l].CompType == BianYaQi_ID && Param[k][l].CompParam == BYQ_ZHNFenJieTouYC)
			{
				if (pValue)
					memcpy(&byValue, pValue, sizeof(Juint8));
				sql.Format("UPDATE %s SET %sMVal=%d,%sMFlag=1 WHERE ID=%d",
					strBiaoMing.GetBuf(), Param[k][l].FieldName, 
					byValue, Param[k][l].FieldName, nBJID);
			}
			//EMS-Mend>
			else
			{
				if (pValue)
					memcpy(&fValue, pValue, sizeof(Jfloat));
				sql.Format("UPDATE %s SET %sMVal=%f,%sMFlag=1 WHERE ID=%d",
					strBiaoMing.GetBuf(), Param[k][l].FieldName, 
					fValue, Param[k][l].FieldName, nBJID);
			}
		}
		break;
	default:	// δ֪����
		return DB_INVALID_PARAM;
		break;
	}

	Jint32 ret = miaoshu->ExecuteSQL(sql.GetBuf()) ? DB_SUCCESS : DB_ERROR;
	miaoshu->CloseSQL();
	return ret;
}

//EMS-Mend <<< majian 2007.6.1
//�޸�ԭ�򣺰��յ�ѹ�ȼ��ɸߵ��͵�˳���ȡĳ����վ��ȫ��ĸ��id����ȥ��ĸ�� 
Jint32 CMSData::GetMuXianOfChangZhan(DATAID_TYPE wChangZhanID, vector<SMiaoShuParam> *parMuXianInfo)
{
	CIIString strSQL;
	Juint16	nIndex = 0;
	DATAID_TYPE wID = 0;
	Juint8 byDYDJID = 0;
	SMiaoShuParam tmpMXParam;

	CONNECTMSDB();

	strSQL = "SELECT ID, DIANYADENGJIID FROM MUXIAN WHERE ChangZhanID=? AND BIANHAO not like '%��%' ORDER BY DIANYADENGJIID";

	miaoshu->PrepareSQL(strSQL.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wID);
    miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byDYDJID);// DMS-MEND baizy, 2009.11.17 13:41,IES_SQL_USMALLINT
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wChangZhanID);

	if( !miaoshu->Exec() )
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);		
		return DB_NO_DATA_FOUND;
	}

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		tmpMXParam.byBuJianCanShuID = byDYDJID;		// ��������ֶδ�ŵ�ѹ�ȼ�
		tmpMXParam.wBuJianID = wID;
		tmpMXParam.wChangZhanID = 0;
		parMuXianInfo->push_back(tmpMXParam);
	}
	
	if(nIndex == 0)
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);
		return DB_NO_DATA_FOUND;
	}
	
	return DB_SUCCESS;
}
//EMS-Mend >>> majian 2007.6.1

// EMS-Mend< ��� 2007.12.28 17:10
// �޸�ԭ��:��ȡĳ����վ��ȫ������Id
Jint32 CMSData::GetKaiGuanOfChangZhan(DATAID_TYPE wChangZhanID, vector<SMiaoShuParam> *parKaiGuanInfo)
{
	CIIString strSQL;
	Juint16	nIndex = 0;
	DATAID_TYPE wID = 0;
	Juint8 byDYDJID = 0;
	SMiaoShuParam tmpKGParam;
	memset(&tmpKGParam, 0, sizeof(SMiaoShuParam));

	CONNECTMSDB();

	strSQL = "SELECT ID, DIANYADENGJIID FROM KaiGuan WHERE ChangZhanID=? ORDER BY ID";

	miaoshu->PrepareSQL(strSQL.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wID);
    miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byDYDJID);// DMS-MEND baizy, 2009.11.17 13:41,IES_SQL_USMALLINT
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wChangZhanID);

	if( !miaoshu->Exec() )
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);		
		return DB_NO_DATA_FOUND;
	}

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		tmpKGParam.byBuJianCanShuID = byDYDJID;		// ��������ֶδ�ŵ�ѹ�ȼ�
		tmpKGParam.wBuJianID = wID;
		tmpKGParam.wChangZhanID = wChangZhanID;
		parKaiGuanInfo->push_back(tmpKGParam);
	}
	
	if(nIndex == 0)
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);
		return DB_NO_DATA_FOUND;
	}
	
	return DB_SUCCESS;
}

Jint32 CMSData::GetBianYaQiOfChangZhan(DATAID_TYPE wChangZhanID, vector<SMiaoShuParam> *parBianYaQiInfo)
{
	CIIString strSQL;
	Juint16	nIndex = 0;
	DATAID_TYPE wID = 0;
	Juint8 byDYDJID = 0;
	SMiaoShuParam tmpBYQParam;

	CONNECTMSDB();

	strSQL = "SELECT ID, GaoYaCeDengJiID FROM BianYaQi WHERE ChangZhanID=? ORDER BY ID";

	miaoshu->PrepareSQL(strSQL.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wID);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byDYDJID);// DMS-MEND baizy, 2009.11.17 13:41,IES_SQL_USMALLINT
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wChangZhanID);

	if( !miaoshu->Exec() )
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);		
		return DB_NO_DATA_FOUND;
	}

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		tmpBYQParam.byBuJianCanShuID = byDYDJID;		// ��������ֶδ�ŵ�ѹ�ȼ�
		tmpBYQParam.wBuJianID = wID;
		tmpBYQParam.wChangZhanID = wChangZhanID;
		parBianYaQiInfo->push_back(tmpBYQParam);
	}
	
	if(nIndex == 0)
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);
		return DB_NO_DATA_FOUND;
	}
	
	return DB_SUCCESS;
}

Jint32 CMSData::GetFaDianJiOfChangZhan(DATAID_TYPE wChangZhanID, vector<SMiaoShuParam> *parFaDianJiInfo)
{
	CIIString strSQL;
	Juint16	nIndex = 0;
	DATAID_TYPE wID = 0;
	Juint8 byDYDJID = 0;
	SMiaoShuParam tmpFDJParam;

	CONNECTMSDB();

	strSQL = "SELECT ID, DianYaDengJiID FROM FaDianJi WHERE ChangZhanID=? ORDER BY ID";

	miaoshu->PrepareSQL(strSQL.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &wID);
    miaoshu->BindCol(IES_SQL_UTINYINT, 0, &byDYDJID);// DMS-MEND baizy, 2009.11.17 13:41,IES_SQL_USMALLINT
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wChangZhanID);

	if( !miaoshu->Exec() )
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);		
		return DB_NO_DATA_FOUND;
	}

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		tmpFDJParam.byBuJianCanShuID = byDYDJID;		// ��������ֶδ�ŵ�ѹ�ȼ�
		tmpFDJParam.wBuJianID = wID;
		tmpFDJParam.wChangZhanID = wChangZhanID;
		parFaDianJiInfo->push_back(tmpFDJParam);
	}
	
	if(nIndex == 0)
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);
		return DB_NO_DATA_FOUND;
	}
	
	return DB_SUCCESS;
}
// EMS-Mend>

//���ݿ���ID���ж����Ӧĸ���Ƿ���ƣ��ӵأ�������ȷ���������Ƿ����ң��
//�ڵ������˲������п��غͱ�վĸ�ߣ��ڵ������˶˿ڱ���ȡ�����غ�ĸ������Ӧ�Ķ˿�.�������ڶ˿ڡ�
//�ڿ��غ�ĸ�߶˿��������ҳ��Ϳ�����Ԫ�ڵ���ͬ��Ԫ�ڵ��Ӧ��ĸ�����վ������ţ�Ȼ�����ڵ������˲�������
//���ҳ����Ӧ��ĸ��ID

// ���ܣ�����������Ϣ���Ҳ�������Ӧ��ĸ��
// ��ڲ�������������,����ID,ĸ��ID����,��վID
// ���ڲ�����ĸ��ID����
// ����ֵ: 0=�ɹ� 
// ʱ�䣺

Jint32 CMSData::GetMuXianOfBuJian(Juint8 byBuJianType, DATAID_TYPE wBuJianID, vector<DATAID_TYPE> *parMuXianID, DATAID_TYPE wChangZhanID)
{
	CIIString strSQL;
	Juint16	nIndex =0;
	STopoBuJian	sParam;
	vector<STopoBuJian> vParam;
	Juint16		nFieldID;
	vector<Juint16> vFieldID;
	CONNECTMSDB();

	// ѡȡ�ó�վ������ĸ�߼����벿������Ϣ
	strSQL = "SELECT FieldID,ComponentID,FieldTypeID,ComponentType FROM dwtopobujian"
			" WHERE (ChangZhanID=? AND ComponentType=6) OR (ComponentID=? AND ComponentType=?)";

	miaoshu->PrepareSQL(strSQL.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &sParam.nFieldid);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &sParam.nComponentID);
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &sParam.nFieldTypeID);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &sParam.byComponentType);
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wChangZhanID);
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wBuJianID);
	miaoshu->BindPara(IES_SQL_UTINYINT, 0, &byBuJianType);
	
	if( !miaoshu->Exec() )
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);		
		return DB_NO_DATA_FOUND;
	}

	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		nIndex++;
		vParam.push_back(sParam);
	}
	
	if(nIndex == 0)
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);
		return DB_NO_DATA_FOUND;
	}
	
	// ȡ�봫�벿������ӵ�ĸ�ߵ������
	strSQL = "SELECT FieldID FROM DwtopoPort a where a.ChangZhanID=? AND a.FieldTypeID=6001 AND"
			" (a.pnodeid IN (SELECT PnodeID FROM dwtopoport b where b.changzhanid=? and b.fieldid=?))";

	miaoshu->PrepareSQL(strSQL.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT, 0, &nFieldID);
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wChangZhanID);
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &wChangZhanID);

	bool bFind = false;
	for(int i=0; i<vParam.size(); i++)
	{
		if(vParam[i].byComponentType != 6)
		{
			miaoshu->BindPara(IES_SQL_USMALLINT, 0, &vParam[i].nFieldid);
			bFind = true;
			break;
		}
	}

	if(!bFind)
		return DB_NO_DATA_FOUND;
	
	if( !miaoshu->Exec() )
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);		
		return DB_NO_DATA_FOUND;
	}
	
	nIndex = 0;
	while (miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		nIndex++;
		vFieldID.push_back(nFieldID);
	}
	
	if(nIndex == 0)
	{
		const char *szErr = miaoshu->GetErrorStr();
		gCIILog_msdbcall.Add(szErr);
		return DB_NO_DATA_FOUND;
	}
	
	for(int j=0; j<vParam.size(); j++)
	{
		for(int k=0; k<vFieldID.size(); k++)
		{
			if(vParam[j].byComponentType == 6 && vParam[j].nFieldid == vFieldID[k])
			{
				parMuXianID->push_back(vParam[j].nComponentID);
			}
		}
	}
	
	return DB_SUCCESS;
}

// ��ȡ����ֵ��ʱ���б�, baizy, 2005.10.21
Juint32	CMSData::GetDDZhiBanTimeList(ATimeInfo& aTmInfo)
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	STimeInfo	tmInfo;
	char sql[256];
	memset(sql, 0, sizeof(char)*256);
	sprintf(sql, "select BQiShi FROM ddzhiban order by BQiShi");

	aTmInfo.clear();
	if (miaoshu->PrepareSQL(sql))
	{
		miaoshu->BindCol(IES_SQL_TIMESTAMP, 0, &tmInfo);
		miaoshu->Exec();		
		while (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			aTmInfo.push_back(tmInfo);
		}
	}	
	
	miaoshu->CloseSQL();	
	return aTmInfo.size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;
}

// ��ȡȫ��������Ŀ��غ͵�բ sun 2006.4.3
Juint32 CMSData::GetSetKaiGuanAndDaoZha(ABuJianPlusType* arBuJian)
{
	Juint32 nCount = 0;
	if (!arBuJian) 	return DB_INVALID_PARAM;
	CONNECTMSDB();
	
	arBuJian->clear();
	CIIString	sql;
	
	sql.Format("SELECT ID, ChangZhanID, MingZi FROM KaiGuan where SheZhiF=1 ORDER BY ChangZhanID, MingZi");
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJianPlusType.wID);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJianPlusType.wChangZhan);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJianPlusType.szMingZi);
	miaoshu->Exec();
	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		m_stBuJianPlusType.byBuJianLeiXing = KaiGuan_ID;
		m_stBuJianPlusType.byBuJianCanShu = KG_KGState;
		arBuJian->push_back(m_stBuJianPlusType);
		nCount++;
	}
	miaoshu->CloseSQL();
	
	sql.Format("SELECT ID, ChangZhanID, MingZi FROM DaoZha where SheZhiF=1 ORDER BY ChangZhanID, MingZi");
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJianPlusType.wID);
	miaoshu->BindCol(SQL_DATAID_TYPE, 0, &m_stBuJianPlusType.wChangZhan);
	miaoshu->BindCol(IES_SQL_STRING, NAMELEN, m_stBuJianPlusType.szMingZi);
	miaoshu->Exec();
	while(miaoshu->Fetch() && !miaoshu->IsEnd())
	{
		m_stBuJianPlusType.byBuJianLeiXing = DaoZha_ID;
		m_stBuJianPlusType.byBuJianCanShu = DZ_DZState;
		arBuJian->push_back(m_stBuJianPlusType);
		nCount++;
	}
	miaoshu->CloseSQL();
	
	return nCount;
}

// ��ò�����Ӧ�ĵ���������¼, baizy, 2005.10.21
Juint32	CMSData::GetBuJianDictionary(Juint8 byBJType, DATAID_TYPE nBJID, ADictItems& aItems)
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	aItems.clear();
	
	DictItem	item;
	char sql[256];
	memset(sql, 0, sizeof(char)*256);
	sprintf(sql, "select devinfo from powerdevinfo where bjtype = %d and bjid =%d order by devinfo", byBJType, nBJID);
	if (miaoshu->PrepareSQL(sql))
	{
		miaoshu->BindCol(IES_SQL_STRING, DICTITEMLEN, item.szMingzi);
		miaoshu->Exec();		
		while (miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			aItems.push_back(item);
		}
	}	
	
	miaoshu->CloseSQL();	
	return aItems.size() > 0 ? DB_SUCCESS : DB_NO_DATA_FOUND;

}

// ����ĳ������һ������������¼
Juint32	CMSData::AddBuJianDictionaryItem(Juint8 byBJType, DATAID_TYPE nBJID, char* szTxt)
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();

	if (szTxt == NULL)
		return DB_INVALID_PARAM;
	
	szTxt[DICTITEMLEN-1] = '\0';

	char		sql[256];
	memset(sql, 0, sizeof(char)*256);
	sprintf(sql, "insert into powerdevinfo(bjtype, bjid, devinfo) values(?, ?, ?)");
	if (miaoshu->PrepareSQL(sql))
	{
		miaoshu->BindPara(IES_SQL_UTINYINT,		0,				&byBJType);
		miaoshu->BindPara(SQL_DATAID_TYPE,	0,				&nBJID);
		miaoshu->BindPara(IES_SQL_STRING,		DICTITEMLEN,	szTxt);
		retcode = miaoshu->Exec();
		miaoshu->CloseSQL();		
		CIIString strError = "** ��ȡ����Ϣִ��SQL������,��������:";
		strError += miaoshu->GetErrorStr();
		retcode = retcode > 0 ? DB_SUCCESS : DB_ERROR;
	}

	return retcode;
}

// �޸�ĳ������һ������������¼
Juint32	CMSData::ModBuJianDictionaryItem(Juint8 byBJType, DATAID_TYPE nBJID, char* szOldTxt, char* szTxt)
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	
	if (szTxt == NULL)
		return DB_INVALID_PARAM;
	
	//EMS-Mend ��㳬 2007.1.15
	//�޸�ԭ��:д�����ԣ��п���szTxt����<DICTITEMLEN-1.
	//EMS-Mend<
	//szTxt[DICTITEMLEN-1] = '\0';
	char szNewTxt[DICTITEMLEN];
	szNewTxt[0] = '\0';
	memset(szNewTxt, 0, sizeof(char)*DICTITEMLEN);
	memcpy(szNewTxt,szTxt,DICTITEMLEN);
	szNewTxt[DICTITEMLEN-1] = '\0';
	//EMS-Mend>
	
	char		sql[512];
	memset(sql, 0, sizeof(char)*512);
	//EMS-Mend ��㳬 2007.1.15
	//�޸�ԭ��:
	//EMS-Mend<
	//sprintf(sql, "update powerdevinfo set devinfo = \'%s\' where bjtype = %d and bjid = %d and devinfo = \'%s\'", szTxt, byBJType, nBJID, szOldTxt);
	sprintf(sql, "update powerdevinfo set devinfo = \'%s\' where bjtype = %d and bjid = %d and devinfo = \'%s\'", szNewTxt, byBJType, nBJID, szOldTxt);
	//EMS-Mend>
	if (miaoshu->PrepareSQL(sql))
	{		
		retcode = miaoshu->Exec();
		miaoshu->CloseSQL();		
		retcode = retcode > 0 ? DB_SUCCESS : DB_ERROR;
	}	
	return retcode;
}

// ɾ��ĳ������һ������������¼
Juint32	CMSData::DelBuJianDictionaryItem(Juint8 byBJType, DATAID_TYPE nBJID, char* szTxt)
{
	Jint32 retcode = DB_ERROR;
	CONNECTMSDB();
	
	if (szTxt == NULL)
		return DB_INVALID_PARAM;
	
	szTxt[DICTITEMLEN-1] = '\0';
	
	char		sql[256];
	memset(sql, 0, sizeof(char)*256);
	sprintf(sql, "delete from powerdevinfo where bjtype = %d and bjid = %d and devinfo = \'%s\'", byBJType, nBJID, szTxt);
	if (miaoshu->PrepareSQL(sql))
	{		
		retcode = miaoshu->Exec();
		miaoshu->CloseSQL();		
		retcode = retcode > 0 ? DB_SUCCESS : DB_ERROR;
	}
	
	return retcode;
}

//EMS_mend< hujr 2007.4.30    
//�޸�ԭ��:ȡ���ⵥ��������������
Juint32	CMSData::GetXuNiDMNLiangXNType(DATAID_TYPE wXuNiDMNLiangID,Juint16* nXNType)
{
	CONNECTMSDB();

	CIIString	sql;
	sql.Format("select XNType from xunidmnliang where id = %d", wXuNiDMNLiangID);
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_USMALLINT,0, nXNType);
	miaoshu->Exec();
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS:DB_NO_DATA_FOUND;

}
//EMS_mend> 

// EMS-Mend< ��㳬 2007.5.30 11:14
//=============================================================================
// ��ȡĳ����վ�ĵ�ѹ�ȼ�
// ��ڣ���վID����ѹ�ȼ�����
// ���ڣ�����������
// Date: 2007.5.30 11:03
//=============================================================================
Jint32 CMSData::GetDianYaDengJi(DATAID_TYPE nChangZhanID,ABuJian* parDianYaDengJi)
{
	if ( parDianYaDengJi == NULL)
		return DB_INVALID_PARAM;
	CONNECTMSDB();
	parDianYaDengJi->clear();

	SBuJian tIDString;
	Juint8	nDianYaDengJiID[5]; // DATAID_TYPE -> Juint8, yuecaijuan, 2011.05.18
	memset(nDianYaDengJiID,0,sizeof(nDianYaDengJiID)/sizeof(nDianYaDengJiID[0]));//yuecaijuan,Ӧ�������ó�ֵ������վID�Ƿ���ʱ���ѹ�ȼ���������ֵ��
	CIIString strSql ="SELECT DianYaDengJi1ID,DianYaDengJi2ID,DianYaDengJi3ID,DianYaDengJi4ID,"
			"DianYaDengJi5ID FROM ChangZhan WHERE id=?";
	miaoshu->PrepareSQL(strSql.GetBuf());
	
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &nDianYaDengJiID[0]);// EMS-Mend< baizy 2008.11.30 14:23 ʹ���������ݿ��ֶα���һ��
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &nDianYaDengJiID[1]);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &nDianYaDengJiID[2]);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &nDianYaDengJiID[3]);
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &nDianYaDengJiID[4]);
	miaoshu->BindPara(SQL_DATAID_TYPE, 0, &nChangZhanID);
	if (!miaoshu->Exec())
	{
		miaoshu->CloseSQL();
		return DB_QUERY_FAIL;
	}
	if ( !miaoshu->Fetch() )
	{
		miaoshu->CloseSQL();
		return DB_QUERY_FAIL;
	}
	miaoshu->CloseSQL();


	strSql = "SELECT MingZi FROM DianYaDengJi WHERE id=?";
	for(int i=0; i<5; i++)
	{
		tIDString.szMingZi[0] = 0;
		tIDString.wID = nDianYaDengJiID[i];
		miaoshu->PrepareSQL( strSql.GetBuf() );
		miaoshu->BindCol(IES_SQL_STRING, NAMELEN, tIDString.szMingZi);
		miaoshu->BindPara(SQL_DATAID_TYPE, 0, &tIDString.wID);
		if (!miaoshu->Exec())
		{
			miaoshu->CloseSQL();
			continue;
		}
		
		if( miaoshu->Fetch())
		{
			if(strlen(tIDString.szMingZi) > 0)
				parDianYaDengJi->push_back(tIDString);
		}
		miaoshu->CloseSQL();
	}
	return (parDianYaDengJi->size()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
}
// EMS-Mend>
// EMS-Mend< ��㳬 2007.6.1 14:01
// ��ñ�ѹ����������
Jint32 CMSData::GetBianYaQiRatedCapacity(DATAID_TYPE wID, Jdouble &fH_MW,Jdouble &fM_MW,Jdouble &fL_MW )
{
	CONNECTMSDB();

	char sql[256];
	memset(sql, 0, sizeof(char)*256);
	sprintf(sql, "select h_mw,m_mw,l_mw from transpara_ems where id = %d", wID);
	miaoshu->PrepareSQL(sql);
	
	miaoshu->BindCol(IES_SQL_DOUBLE, 0, &fH_MW);
	miaoshu->BindCol(IES_SQL_DOUBLE, 0, &fM_MW);
	miaoshu->BindCol(IES_SQL_DOUBLE, 0, &fL_MW);
	miaoshu->Exec();		
	return (miaoshu->Fetch() && !miaoshu->IsEnd()) ? DB_SUCCESS : DB_NO_DATA_FOUND;
}

// EMS-Mend>