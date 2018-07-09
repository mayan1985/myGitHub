///////////////////////////////////////////////////////////////////////////////
#include <qdatetime.h>
#include <qsqlcursor.h>
#include "iessbmix.h"
#include "dbdefine.h"
#include "msdbcall.h"


#define	MACRO_FUNC_GETCOMPONENT(COMPNAME, NUM)												\
Jint32 CMSData::Get##COMPNAME(DATAID_TYPE wID, TK_##COMPNAME* p##COMPNAME)						\
{																							\
	CHECKPARAM(wID, p##COMPNAME, aDWBuJian_Table[NUM], Offset_TK_##COMPNAME);				\
	CONNECTMSDB_2();																			\
	CIIString filter;																		\
	filter.Format("ID=%d", wID);															\
	return GetDBValue(miaoshu, &aDWBuJian_Table[NUM], filter.GetBuf(), (Juint8*)p##COMPNAME, Offset_TK_##COMPNAME);	\
};

#define	MACRO_FUNC_SETCOMPONENT(COMPNAME, NUM)														\
Jint32 CMSData::Set##COMPNAME(DATAID_TYPE wID, TK_##COMPNAME* p##COMPNAME, Juint8 byOpType)				\
{																									\
	if (byOpType==1 && wID==0) 	return DB_INVALID_PARAM;											\
	if (byOpType!=1) {CHECKPARAM(1, p##COMPNAME, aDWBuJian_Table[NUM], Offset_TK_##COMPNAME);}		\
	CONNECTMSDB_2();																					\
	return OpereDBComp(miaoshu, &aDWBuJian_Table[NUM], (Juint8*)p##COMPNAME, Offset_TK_##COMPNAME, wID, byOpType);	\
};

// EMS-Mend<yuecaijuan 2010.11.23 调配一体化开发I期
// 参考获取和设置宏，添加上关于删除的宏
#define	MACRO_FUNC_DELCOMPONENT(COMPNAME, NUM)														\
	Jint32 CMSData::Del##COMPNAME(DATAID_TYPE wID, TK_##COMPNAME* p##COMPNAME, Juint8 byOpType)				\
{																									\
	if (byOpType==1 && wID==0) 	return DB_INVALID_PARAM;											\
	if (byOpType!=1) {CHECKPARAM(1, p##COMPNAME, aDWBuJian_Table[NUM], Offset_TK_##COMPNAME);}		\
	CONNECTMSDB_2();																					\
	return OpereDBComp(miaoshu, &aDWBuJian_Table[NUM], (Juint8*)p##COMPNAME, Offset_TK_##COMPNAME, wID, byOpType);	\
};

// ----------------------------------------------------------------------------
// 本文件提供访问描述库电网部件的各种函数，供绘图和人机接口界面使用
// ----------------------------------------------------------------------------

//*****************************************************************************
//以下为绘图填库专用函数, 提供填写电网描述表的函数
//*****************************************************************************

//=============================================================================
// 获取电网信息
// 入口：主机名、电网结构指针
// 出口：操作返回码
// Date: 2002.10.31
//=============================================================================
Jint32 CMSData::GetDianWang(TK_DianWang* pDianWang)
{
	CHECKPARAM(1, pDianWang, aDWBuJian_Table[0], Offset_TK_DianWang);
	CONNECTMSDB_2();

	CIIString filter;
	filter.Format("ID=%d", 1);

	return GetDBValue(miaoshu, &aDWBuJian_Table[0], filter.GetBuf(), (Juint8*)pDianWang, Offset_TK_DianWang);
}

//=============================================================================
// 设置电网信息
// 入口：主机名、电网信息指针、操作代码
// 出口：操作返回码
// Date: 2002.10.31
//=============================================================================
//	Jint32 SetDianWang(Juint16 wID=1, TK_DianWang* pDianWang,	Juint8 byOpType);	//0=增加/修改 1=删除

MACRO_FUNC_SETCOMPONENT(DianWang, 0);

//=============================================================================
// 获取电压等级
// 入口：主机名、电压等级数组
// 出口：操作返回码
// Date: 2002.11.6
//=============================================================================

Jint32 CMSData::GetDianYaDengJi(vector<TK_DianYaDengJi>* parDianYaDengJi)
{
	CHECKPARAM(1, parDianYaDengJi, aDWBuJian_Table[1], Offset_TK_DianYaDengJi);
	CONNECTMSDB_2();

	char* order = "ID";
	TK_DianYaDengJi tmpDianYaDengJi;
	
	parDianYaDengJi->clear();
	if (GetDBValue(miaoshu, &aDWBuJian_Table[1], NULL, (Juint8*)&tmpDianYaDengJi, Offset_TK_DianYaDengJi, order)==DB_SUCCESS)
	{
		parDianYaDengJi->push_back(tmpDianYaDengJi);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parDianYaDengJi->push_back(tmpDianYaDengJi);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// 设置电压等级
// 入口：主机名、部件ID、电压等级信息指针
// 出口：操作返回码
// Date: 2002.11.6
//=============================================================================

MACRO_FUNC_SETCOMPONENT(DianYaDengJi, 1);
//Jint32 CMSData::SetDianYaDengJi(Juint8 byID, TK_DianYaDengJi* pDianYaDengJi,	Juint8 byOpType)

//=============================================================================
// 获得所有厂站信息
// 入口：主机名、厂站信息数组指针
// 出口：操作返回码
// Date: 2002.11.1
//=============================================================================
Jint32 CMSData::GetChangZhan(vector<TK_ChangZhan>* parChangZhan)
{
	CHECKPARAM(1, parChangZhan, aDWBuJian_Table[2], Offset_TK_ChangZhan);
	CONNECTMSDB_2();

	char* order = "ID";
	TK_ChangZhan tmpChangZhan;
	
	parChangZhan->clear();
	if (GetDBValue(miaoshu, &aDWBuJian_Table[2], NULL, (Juint8*)&tmpChangZhan, Offset_TK_ChangZhan, order)==DB_SUCCESS)
	{
		parChangZhan->push_back(tmpChangZhan);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parChangZhan->push_back(tmpChangZhan);
		}
		return DB_SUCCESS;
	}

	return DB_NO_DATA_FOUND;
}

//=============================================================================
// 获得单个厂站信息
// 入口：主机名、厂站信息指针
// 出口：操作返回码
// Date: 2002.11.1
//=============================================================================
MACRO_FUNC_GETCOMPONENT(ChangZhan, 2);

//=============================================================================
// 设置厂站信息
// 入口：主机名、部件ID、厂站信息指针、操作类型代码
// 出口：操作返回码
// Date: 2002.11.1
//=============================================================================
MACRO_FUNC_SETCOMPONENT(ChangZhan, 2);
//Jint32 CMSData::SetChangZhan(Juint16 wID, TK_ChangZhan* pChangZhan, Juint8 byOpType)			//0=增加/修改；1=删除

//=============================================================================
// 获取母线信息(连接数据库已完成)
// 入口：部件ID、母线信息指针
// 出口：操作返回码、母线信息
// Date: 2002.11.1
//=============================================================================
MACRO_FUNC_GETCOMPONENT(MuXian, 3);
//Jint32 CMSData::GetMuXian(Juint16 wID, TK_MuXian* pMuXian)

//=============================================================================
// 设置母线信息
// 入口：主机名、部件ID、母线信息指针、操作类型代码
// 出口：操作返回码
// Date: 2002.11.3
//=============================================================================
MACRO_FUNC_SETCOMPONENT(MuXian, 3);
//Jint32 CMSData::SetMuXian(Juint16 wID, TK_MuXian* pMuXian, Juint8 byOpType)			//0=增加/修改；1=删除

//=============================================================================
// 获取线路信息(连接数据库已完成)
// 入口：部件ID、线路信息指针
// 出口：操作返回码
// Date: 2002.11.3
//=============================================================================
MACRO_FUNC_GETCOMPONENT(XianLu, 4)
// Jint32 CMSData::GetXianLu(Juint16 wID, TK_XianLu* pXianLu)

//=============================================================================
// 设置线路信息
// 入口：主机名、部件ID、线路信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.3
//=============================================================================
MACRO_FUNC_SETCOMPONENT(XianLu, 4);
//Jint32 CMSData::SetXianLu(Juint16 wID, TK_XianLu* pXianLu, Juint8 byOpType)		//0=增加/修改 1=删除

//=============================================================================
// 获取开关信息(连接数据库已完成)
// 入口：部件ID、开关信息指针
// 出口：操作返回码
// Date: 2002.11.4
//=============================================================================
MACRO_FUNC_GETCOMPONENT(KaiGuan, 5);
// Jint32 CMSData::GetKaiGuan(Juint16 wID, TK_KaiGuan* pKaiGuan)

//=============================================================================
// 设置开关信息
// 入口：主机名、部件ID、开关信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.4
//=============================================================================
MACRO_FUNC_SETCOMPONENT(KaiGuan, 5);
//Jint32 CMSData::SetKaiGuan(Juint16 wID, TK_KaiGuan* pKaiGuan, Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获取刀闸信息(连接数据库已完成)
// 入口：部件ID、刀闸信息指针
// 出口：操作返回码
// Date: 2002.11.4
//=============================================================================
MACRO_FUNC_GETCOMPONENT(DaoZha, 6);
//Jint32 CMSData::GetDaoZha(Juint16 wID, TK_DaoZha* pDaoZha)

//=============================================================================
// 设置刀闸信息
// 入口：主机名、部件ID、刀闸信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.4
//=============================================================================
MACRO_FUNC_SETCOMPONENT(DaoZha, 6);
//Jint32 CMSData::SetDaoZha(Juint16 wID, TK_DaoZha* pDaoZha, Juint8 byOpType)		//0=增加/修改 1=删除

//=============================================================================
// 获取刀闸信息(连接数据库已完成)
// 入口：部件ID、保护信息指针
// 出口：操作返回码
// Date: 2002.11.4
//=============================================================================
MACRO_FUNC_GETCOMPONENT(BaoHu, 7);
//Jint32 CMSData::GetBaoHu(Juint16 wID, TK_BaoHu* pBaoHu)

//=============================================================================
// 设置保护信息
// 入口：主机名、部件ID、保护信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.4
//=============================================================================
MACRO_FUNC_SETCOMPONENT(BaoHu, 7);
// Jint32 CMSData::SetBaoHu(Juint16 wID, TK_BaoHu* pBaoHu,  Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获得变压器信息(连接数据库已完成)
// 入口：部件ID、变压器信息指针
// 出口：操作返回码
// Date: 2002.11.4
//=============================================================================
MACRO_FUNC_GETCOMPONENT(BianYaQi, 8)
//Jint32 CMSData::GetBianYaQi(Juint16 wID, TK_BianYaQi* pBianYaQi)

//=============================================================================
// 设置变压器信息
// 入口：主机名、部件ID、变压器信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.4
//=============================================================================
MACRO_FUNC_SETCOMPONENT(BianYaQi, 8);
// Jint32 CMSData::SetBianYaQi(Juint16 wID, TK_BianYaQi* pBianYaQi, Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获得发电机信息(连接数据库已完成)
// 入口：部件ID、发电机信息指针
// 出口：操作返回码
// Date: 2002.11.4
//=============================================================================
MACRO_FUNC_GETCOMPONENT(FaDianJi, 9);
//Jint32 CMSData::GetFaDianJi(Juint16 wID, TK_FaDianJi* pFaDianJi)

//=============================================================================
// 设置发电机信息
// 入口：主机名、部件ID、发电机信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(FaDianJi, 9);
//Jint32 CMSData::SetFaDianJi(Juint16 wID, TK_FaDianJi* pFaDianJi,	Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获取CT信息(连接数据库已完成)
// 入口：部件ID、CT信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(CT, 10);
//Jint32 CMSData::GetCT(Juint16 wID, TK_CT* pCT)


//=============================================================================
// 设置CT信息
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(CT, 10);
//Jint32 CMSData::SetCT(Juint16 wID, TK_CT* pCT, Juint8 byOpType)			//0=增加/修改；1=删除

//=============================================================================
// 获取PT信息(连接数据库已完成)
// 入口：部件ID、PT信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(PT, 11);
//Jint32 CMSData::GetPT(Juint16 wID, TK_PT* pPT)

//=============================================================================
// 设置PT信息
// 入口：主机名、部件ID、PT信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(PT, 11);
//Jint32 CMSData::SetPT(Juint16 wID, TK_PT* pPT, Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获取负荷信息(连接数据库已完成)
// 入口：部件ID、负荷信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(FuHe, 12)
//Jint32 CMSData::GetFuHe(Juint16 wID, TK_FuHe* pFuHe);

//=============================================================================
// 设置负荷信息
// 入口：主机名、部件ID、负荷信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(FuHe, 12);
//Jint32 CMSData::SetFuHe(Juint16 wID, TK_FuHe* pFuHe, Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获取注入信息(连接数据库已完成)
// 入口：部件ID、注入信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(ZhuRu, 13);
//Jint32 CMSData::GetZhuRu(Juint16 wID, TK_ZhuRu* pZhuRu)

//=============================================================================
// 设置注入信息
// 入口：主机名、部件ID、注入信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(ZhuRu, 13);
//Jint32 CMSData::SetZhuRu(Juint16 wID, TK_ZhuRu* pZhuRu, Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获取调相机信息(连接数据库已完成)
// 入口：部件ID、调相机信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(TiaoXiangJi, 14);
//Jint32 CMSData::GetTiaoXiangJi(Juint16 wID, TK_TXJ* pTxj)

//=============================================================================
// 设置调相机信息
// 入口：主机名、部件ID、调相机信息、操作类型
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(TiaoXiangJi, 14);

//=============================================================================
// 获取静止补偿信息(连接数据库已完成)
// 入口：部件ID、静止补偿信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(JingZhiBuChang, 15);
//Jint32 CMSData::GetJingZhiBuChang(Juint16 wID, TK_JingZhiBuChang* pJZBC)

//=============================================================================
// 设置静止补偿信息
// 入口：主机名、部件ID、静止补偿信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(JingZhiBuChang, 15);
//Jint32 CMSData::SetJingZhiBuChang(Juint16 wID, TK_JingZhiBuChang* pJZBC, Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获取并联电容信息(连接数据库已完成)
// 入口：部件ID、并联电容信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(BingLianDianRong, 16);
//Jint32 CMSData::GetBingLianDianRong(Juint16 wID, TK_BingLianDianRong* pBLDR)

//=============================================================================
// 设置并联电容信息
// 入口：主机名、部件ID、并联电容信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(BingLianDianRong, 16);
//Jint32 CMSData::SetBingLianDianRong(Juint16 wID, TK_BingLianDianRong* pBLDR, Juint8 byOpType)	//0=增加/修改；1=删除

//=============================================================================
// 获取串联电抗信息(连接数据库已完成)
// 入口：部件ID、串联电抗信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(ChuanLianDianKang, 17);
//Jint32 CMSData::GetChuanLianDianKang(Juint16 wID, TK_ChuanLianDianKang* pCLDK)

//=============================================================================
// 设置串联电抗信息
// 入口：主机名、部件ID、串联电抗信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(ChuanLianDianKang, 17);
//Jint32 CMSData::SetChuanLianDianKang(Juint16 wID, TK_ChuanLianDianKang* pCLDK, Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获取串联电抗信息(连接数据库已完成)
// 入口：部件ID、虚拟遥测信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(XuNiDMNLiang, 18);
//Jint32 CMSData::GetXuNiDMNLiang(Juint16 wID, TK_XuNiDMNLiang* pXuNiDMNLiang)

//=============================================================================
// 设置虚拟单精模拟量信息
// 入口：主机名、部件ID、虚拟遥测信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_SETCOMPONENT(XuNiDMNLiang, 18);
//Jint32 CMSData::SetXuNiDMNLiang(Juint16 wID, TK_XuNiDMNLiang* pXNDMNLiang, Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获取串联电抗信息(连接数据库已完成)
// 入口：部件ID、虚拟脉冲信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(XuNiSMNLiang, 19);
//Jint32 CMSData::GetXuNiSMNLiang(Juint16 wID, TK_XuNiSMNLiang* pXNSMNLiang)

//=============================================================================
// 设置虚拟双精模拟量信息
// 入口：主机名、部件ID、虚拟脉冲信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.6
//=============================================================================
MACRO_FUNC_SETCOMPONENT(XuNiSMNLiang, 19);
//Jint32 CMSData::SetXuNiSMNLiang(Juint16 wID, TK_XuNiSMNLiang* pXNSMNLiang, Juint8 byOpType)		//0=增加/修改；1=删除

//=============================================================================
// 获取串联电抗信息(连接数据库已完成)
// 入口：部件ID、虚拟脉冲信息指针
// 出口：操作返回码
// Date: 2002.11.5
//=============================================================================
MACRO_FUNC_GETCOMPONENT(XuNiZHTLiang, 20);
//Jint32 CMSData::GetXuNiZHTLiang(Juint16 wID, TK_XuNiZHTLiang* pXuNiZHTLiang)

//=============================================================================
// 设置虚拟状态量信息
// 入口：主机名、部件ID、虚拟遥信信息指针、操作类型
// 出口：操作返回码
// Date: 2002.11.6
//=============================================================================
MACRO_FUNC_SETCOMPONENT(XuNiZHTLiang, 20);
//Jint32 CMSData::SetXuNiZHTLiang(Juint16 wID, TK_XuNiZHTLiang* pXuNiZHTLiang, Juint8 byOpType)		//0=增加/修改；1=删除

MACRO_FUNC_GETCOMPONENT(Feeder, 21);// EMS-Mend<yuecaijuan 2010.11.18 调配一体化开发I期
MACRO_FUNC_SETCOMPONENT(Feeder, 21);
MACRO_FUNC_DELCOMPONENT(Feeder, 21);
MACRO_FUNC_GETCOMPONENT(PBBianYaQi, 22);
MACRO_FUNC_SETCOMPONENT(PBBianYaQi, 22);
MACRO_FUNC_GETCOMPONENT(KuiXianDuan, 23);
MACRO_FUNC_SETCOMPONENT(KuiXianDuan, 23);

//EMS-Mend<
//李友金 2006.4.19 定义相关数据库访问接口，实现iesdraw添加删除厂站功能
//获得厂站信息
Jint32 CMSData::GetChangZhanNew(vector<TK_ChangZhan_NEW>* parChangZhan)
{
	
	CHECKPARAM(1, parChangZhan, aChangZhan_Table, Offset_TK_ChangZhan_NEW);
	CONNECTMSDB_2();
	char* order = "ID";
	TK_ChangZhan_NEW tmpChangZhan;
	
	parChangZhan->clear();
	
	if (GetDBValue(miaoshu, &aChangZhan_Table,   NULL, (Juint8*)&tmpChangZhan, Offset_TK_ChangZhan_NEW, order)==DB_SUCCESS)
	{
		parChangZhan->push_back(tmpChangZhan);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parChangZhan->push_back(tmpChangZhan);
		}
	
		return DB_SUCCESS;
	}
	
	
	return DB_NO_DATA_FOUND;
}
//////////////////////////////////////////////////////////////////////////
//李友金 2006.4.19
Jint32 CMSData::GetChangZhanNew(DATAID_TYPE wID, TK_ChangZhan_NEW* pChangZhan)
{
	return 0;
}
//////////////////////////////////////////////////////////////////////////
//李友金 2006.4.19
//增加或修改厂站记录
//部件数据库操作 byOpType = 0 若存在修改 不存在增加纪录(ID自增长)
Jint32 CMSData::SetChangZhanNew(DATAID_TYPE wID, TK_ChangZhan_NEW* pChangZhan, Juint8 byOpType)
{
	if (byOpType==1) 	return DB_INVALID_PARAM;	
	if (byOpType!=1)
	{
		CHECKPARAM(1, pChangZhan, aChangZhan_Table, Offset_TK_ChangZhan_NEW);
	}
	CONNECTMSDB_2();
	return OpereDBComp(miaoshu, &aChangZhan_Table, (Juint8*)pChangZhan, Offset_TK_ChangZhan_NEW, wID, byOpType);
	
}
//////////////////////////////////////////////////////////////////////////
//李友金 2006.4.19
//删除厂站记录
//部件数据库操作 byOpType = 0 若存在修改 不存在增加纪录(ID自增长)
Jint32 CMSData::DelChangZhanNew(DATAID_TYPE wID, TK_ChangZhan_NEW* pChangZhan, Juint8 byOpType)
{
	if (byOpType!=1||wID==0) 	return DB_INVALID_PARAM;	
	CONNECTMSDB_2();
	return OpereDBComp(miaoshu, &aChangZhan_Table, (Juint8*)pChangZhan, Offset_TK_ChangZhan_NEW, wID, byOpType);
	
}
//////////////////////////////////////////////////////////////////////////
//李友金 2006.4.19
//获取电网信息
Jint32 CMSData::GetDianWang(vector<TK_DianWang>* parDianWang)
{
	CHECKPARAM(1, parDianWang, aDWBuJian_Table[0], Offset_TK_DianWang);
	CONNECTMSDB_2();
	char* order = "ID";
	TK_DianWang tmpDianWang;
	
	parDianWang->clear();
	
	if (GetDBValue(miaoshu, &aDWBuJian_Table[0],   NULL, (Juint8*)&tmpDianWang, Offset_TK_DianWang, order)==DB_SUCCESS)
	{
		parDianWang->push_back(tmpDianWang);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parDianWang->push_back(tmpDianWang);
		}	
		return DB_SUCCESS;
	}	
	return DB_NO_DATA_FOUND;
}
//////////////////////////////////////////////////////////////////////////
//李友金 2006.4.19
//获取分区信息
Jint32 CMSData::GetFenQu(vector<TK_FenQu>* parFenQu)
{
	CHECKPARAM(1, parFenQu, aFenQu_Table, Offset_TK_FenQu);
	CONNECTMSDB_2();
	char* order = "ID";
	TK_FenQu tmpFenQu;
	
	parFenQu->clear();
	
	if (GetDBValue(miaoshu, &aFenQu_Table,   NULL, (Juint8*)&tmpFenQu, Offset_TK_FenQu, order)==DB_SUCCESS)
	{
		parFenQu->push_back(tmpFenQu);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parFenQu->push_back(tmpFenQu);
		}	
		return DB_SUCCESS;
	}	
	return DB_NO_DATA_FOUND;
}
////////////////////////////////////////////////////////////////////////
//李友金 2006.4.19
//获取发电公司信息
Jint32 CMSData::GetFaDianGongSi(vector<TK_FaDianGongSi>* parFaDianGongSi)
{
	CHECKPARAM(1, parFaDianGongSi, aFaDianGongSi_Table, Offset_TK_FaDianGongSi);
	CONNECTMSDB_2();
	char* order = "ID";
	TK_FaDianGongSi tmpFaDianGongSi;
	
	parFaDianGongSi->clear();
	
	if (GetDBValue(miaoshu, &aFaDianGongSi_Table,   NULL, (Juint8*)&tmpFaDianGongSi, Offset_TK_FaDianGongSi, order)==DB_SUCCESS)
	{
		parFaDianGongSi->push_back(tmpFaDianGongSi);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parFaDianGongSi->push_back(tmpFaDianGongSi);
		}	
		return DB_SUCCESS;
	}	
	return DB_NO_DATA_FOUND;
}
//EMS-Mend>

// EMS-Mend<yuecaijuan 2010.11.17 调配一体化开发I期
// 修改原因：添加获取、修改、删除馈线函数
// 获取馈线信息
Jint32 CMSData::GetFeeder(vector<TK_Feeder>* parFeeder)
{
	CHECKPARAM(1, parFeeder, aDWBuJian_Table[21], Offset_TK_Feeder);
	CONNECTMSDB_2();
	char* order = "ID";
	TK_Feeder tmpFeeder;

	parFeeder->clear();

	if (GetDBValue(miaoshu, &aDWBuJian_Table[21],   NULL, (Juint8*)&tmpFeeder, Offset_TK_Feeder, order)==DB_SUCCESS)
	{
		parFeeder->push_back(tmpFeeder);
		while(miaoshu->Fetch() && !miaoshu->IsEnd())
		{
			parFeeder->push_back(tmpFeeder);
		}

		return DB_SUCCESS;
	}
	return DB_NO_DATA_FOUND;
}
// EMS-Mend>