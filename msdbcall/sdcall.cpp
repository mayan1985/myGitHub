///////////////////////////////////////////////////////////////////////////////
#include "iessbmix.h"
#include "dbdefine.h"
#include "msdbcall.h"

// ----------------------------------------------------------------------------
// 本文件提供访问描述库存盘的各种函数，供绘图和人机接口界面使用
// ----------------------------------------------------------------------------

//*****************************************************************************
//以下为绘图填库专用函数, 提供填写存盘描述表的函数
//*****************************************************************************
//=============================================================================
// 获取遥测存盘信息
// 入口：主机名、部件类型、ID、参数、遥测存盘信息指针
// 出口：操作返回码
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