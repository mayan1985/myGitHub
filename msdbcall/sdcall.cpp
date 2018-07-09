///////////////////////////////////////////////////////////////////////////////
#include "iessbmix.h"
#include "dbdefine.h"
#include "msdbcall.h"

// ----------------------------------------------------------------------------
// ���ļ��ṩ������������̵ĸ��ֺ���������ͼ���˻��ӿڽ���ʹ��
// ----------------------------------------------------------------------------

//*****************************************************************************
//����Ϊ��ͼ���ר�ú���, �ṩ��д����������ĺ���
//*****************************************************************************
//=============================================================================
// ��ȡң�������Ϣ
// ��ڣ����������������͡�ID��������ң�������Ϣָ��
// ���ڣ�����������
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetYCSaveMSH(Juint8 byBJLX, DATAID_TYPE wBJID, 
							Juint16 byBJCS, Juint8& bySaveFlag)
{
	if (byBJLX == 0 || byBJLX >= MaxBuJian_ID || wBJID == 0 || byBJCS == 0)
		return DB_INVALID_PARAM;

	CONNECTMSDB();
	
	CIIString sql;
	GetCorrComp(byBJLX, wBJID, byBJCS);

	sql.Format("SELECT SaveFlag FROM ycsavemsh WHERE BuJianLeiXingID=%d AND BuJianID=%d AND BuJianCanShuID=%d",
				byBJLX, wBJID, byBJCS );
	miaoshu->PrepareSQL(sql.GetBuf());
	miaoshu->BindCol(IES_SQL_UTINYINT, 0, &bySaveFlag);

	if ( !miaoshu->Exec() )
		return DB_ERROR;
	if (miaoshu->Fetch() && !miaoshu->IsEnd())
		return DB_SUCCESS;
	
	return DB_NO_DATA_FOUND;
}