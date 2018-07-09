///////////////////////////////////////////////////////////////////////////////
#include "iessbmix.h"
#include "iescommon.h"
#include "dbdefine.h"
#include "msdbcall.h"
#include "dataid.h"// DMS-MEND baizy, 2008.10.25 12:56，改变前置量测标字段结构

// ----------------------------------------------------------------------------
// 本文件提供访问描述库RTU的各种函数，供绘图和人机接口界面使用
// ----------------------------------------------------------------------------

//*****************************************************************************
// 以下是关于前置通信的数据表的读取和填写
//*****************************************************************************
//=============================================================================
// 1. 获取数据服务器描述(ComDataServer)
// 入口：主机名、数据服务器ID
// 出口：操作返回码、数据服务器名字
// Date: 2002.11.7
//=============================================================================
// 数据表名
const char* ComDataTableNames[RDT_Num] =
{ "", "ComByteData", "ComShortData", "ComIntData", "ComFloatData", "ComDoubleData" };


/////////////////////////////////////////////////////////////////
Jint32 CMSData::GetComDataServer(Juint8 byID, Jchar* cServerName)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 获取数据服务器描述(ComDataServer)
// 入口：主机名、数据服务器数组信息指针
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComDataServer(vector<TK_ComDataServer>* parComDataServer)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置数据服务器描述
// 入口：主机名、数据服务器ID、数据服务器名字
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComDataServer(Juint8 byID, Jchar* cServerName, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 2. 获取通信服务器描述(ComServer)
// 入口：主机名、计算机名、服务器组号
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComServer(Jchar* cComputerName, Juint8& byServerNumber)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 获取通信服务器描述(ComServer)
// 入口：主机名、通信服务器数组信息指针
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComServer(vector<TK_ComServer>* parComServer)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置通信服务器描述(ComServer)
// 入口：主机名、计算机名、服务器组号、操作类型
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComServer(Jchar* cComputerName, Juint8 byServerNumber,
											Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 3. 获取串行通道端口组描述(ComSerial)[服务器组号、组内串行通道号]
// 入口：主机名、服务器组号、组内串行通道号、串行通道端口信息指针
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComSerial(Juint8 byServerNumber,
					DATAID_TYPE bySerialChannelID, TK_ComSerial* pComSerial)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 获取串行通道端口组描述(ComSerial)[服务器组号、组内串行通道号]
// 入口：主机名、串行通道端口数组信息指针
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComSerial(vector<TK_ComSerial>* parComSerial)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置串行通道端口组描述(ComSerial)
// 入口：主机名、服务器组号、组内串行通道号、串行通道端口信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComSerial(Juint8 byServerNumber, DATAID_TYPE bySerialChannelID,
					TK_ComSerial* pComSerial, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 4. 获取终端描述(ComRTU)
// 入口：主机名、RTUID、终端描述信息指针
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComRTU(DATAID_TYPE wRTUID, TK_ComRTU* pComRTU)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 4. 获取终端描述(ComRTU)
// 入口：主机名、终端数组信息指针
// 出口：操作返回码
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
// 设置终端描述
// 入口：主机名、RTUID、终端描述信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComRTU(DATAID_TYPE wRTUID, TK_ComRTU* pComRTU,
											Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 获取某数据所属的RTU及点号
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
// 5. 获取字节数据顺序表（ComByteData）(遥信数据属于此类型)
// 入口：主机名、RTUID、数据类型、序号、字节型数据指针
// 出口：操作返回码、字节型数据
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComByteData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComByteData* pComByteData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置字节数据顺序表
// 入口：主机名、RTUID、数据类型、序号、字节型数据指针、操作类型
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComByteData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
							TK_ComByteData* pComByteData, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 6. 获取短整型数据顺序表（ComShortData）
// 入口：主机名、RTUID、数据类型、序号、短整型数据指针
// 出口：操作返回码、短整型数据
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::GetComShortData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComShortData* pComShortData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置短整型数据顺序表
// 入口：主机名、RTUID、数据类型、序号、短整型数据指针、操作类型
// 出口：操作返回码
// Date: 2002.11.7
//=============================================================================
Jint32 CMSData::SetComShortData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
						TK_ComShortData* pComShortData, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 7. 获取长整型数据顺序表（ComIntData）
// 入口：主机名、RTUID、数据类型、序号、长整型数据指针
// 出口：操作返回码、长整型数据
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComIntData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComIntData* pComIntData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置长整型数据顺序表
// 入口：主机名、RTUID、数据类型、序号、长整型数据指针、操作类型
// 出口：操作返回码
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComIntData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
						TK_ComIntData* pComIntData, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 8. 获取浮点型数据顺序表(ComFloatData)(遥测属于此类数据)
// 入口：主机名、RTUID、数据类型、序号、浮点型数据指针
// 出口：操作返回码、浮点型数据
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComFloatData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComFloatData* pComFloatData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置浮点型数据顺序表
// 入口：主机名、RTUID、数据类型、序号、浮点型数据指针、操作类型
// 出口：操作返回码
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComFloatData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
						TK_ComFloatData* pComFloatData, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 9. 获取双精度数据顺序表(ComDoubleData)(总加遥测以及电度等属于此类数据)
// 入口：主机名、RTUID、数据类型、序号、双精度数据指针
// 出口：操作返回码、双精度数据
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComDoubleData(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComDoubleData* pComDoubleData)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置双精度数据顺序表
// 入口：主机名、RTUID、数据类型、序号、双精度数据指针、操作类型
// 出口：操作返回码
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComDoubleData(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
						TK_ComDoubleData* pComDoubleData, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 10. 获取遥控（ComYK）/遥调描述表
// 入口：主机名、RTUID、数据类型、遥控序号、遥控/遥调数据指针
// 出口：操作返回码、遥控/遥调数据
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComYK(DATAID_TYPE wRTUID, Juint8 byType,
							Jint16 wOrder, TK_ComYK* pComYK)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置遥控（ComYK）/遥调描述表
// 入口：主机名、RTUID、数据类型、遥控序号、遥控/遥调数据指针、操作类型
// 出口：操作返回码
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComYK(DATAID_TYPE wRTUID, Juint8 byType, Jint16 wOrder,
							TK_ComYK* pComYK, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 11. 获取微机保护点描述(ComWJBH)
// 入口：主机名、RTUID、序号、微机保护数据指针
// 出口：操作返回码、微机保护数据
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComWJBH(DATAID_TYPE wRTUID,
							Jint16 wOrder, TK_ComWJBH* pComWJBH)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置微机保护点描述
// 入口：主机名、RTUID、序号、微机保护数据指针、操作类型
// 出口：操作返回码
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComWJBH(DATAID_TYPE wRTUID, Jint16 wOrder,
							TK_ComWJBH* pComWJBH, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 12. 获取RTU通道参数表(ComRTUChParam)
// 入口：主机名、RTUID、类型、RTU通道参数数据指针
// 出口：操作返回码、RTU通道参数数据
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetComRTUChParam(DATAID_TYPE wRTUID, Juint8 byType,
							TK_ComRTUChParam* pComRTUChParam)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 设置RTU通道参数表
// 入口：主机名、RTUID、类型、RTU通道参数数据指针、操作类型
// 出口：操作返回码
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::SetComRTUChParam(DATAID_TYPE wRTUID, Juint8 byType,
						TK_ComRTUChParam* pComRTUChParam, Juint8 byOpType)	//0=增加/修改；1=删除
{
	Jint32	retcode = DB_ERROR;
	return retcode;
}

//=============================================================================
// 13. 获取规约字典表(ProtcolDes)
// 入口：主机名、ID、规约字典数据指针
// 出口：操作返回码、规约字典数据
// Date: 2002.11.8
//=============================================================================
Jint32 CMSData::GetProtocolDes(Jint16 wID, TK_ProtocolDes* pProtocolDes)
{
	Jint32 retcode = DB_ERROR;
	return retcode;
}

ComDataID CMSData::translateComDataID(Juint16 iNo, const char* pDataID)						//字节转换
{

	ComDataID ret;
	//DMS-Mend<wugc 2008.10.22 19:28 ID扩充(2字节->4字节)
	unsigned short offset = 0;
	//部件类型
	memcpy(&ret.byBjType, pDataID+offset, sizeof(Juint8));
	offset += sizeof(Juint8);

	//部件ID
	memcpy(&ret.nBjID, pDataID+offset, DATAID_SIZE);
	ret.nBjID = networktohost(ret.nBjID);
	offset += DATAID_SIZE;

	//部件参数
	memcpy(&ret.byCShType, pDataID+offset, sizeof(Juint8));
	offset += sizeof(Juint8);

	//预留
	offset += sizeof(unsigned short);

	//厂站
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

