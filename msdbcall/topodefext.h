//本文件定义动态着色和图库合一功能中所需的网络拓扑的常量和变量定义
//
#ifndef	_TOPODEFEXT_H
#define	_TOPODEFEXT_H

#include "topodef.h"

//1. 微拓扑描述定义
static Juint16 TopoUnitOffset[] = {
	offsetof(TopoUnit, wFieldTypeID),
	offsetof(TopoUnit, szFieldName),
	
	offsetof(TopoUnit, byBranchNum),
	offsetof(TopoUnit, byCBNum),
	offsetof(TopoUnit, byDisNum),
	offsetof(TopoUnit, byGrdDisNum),
	offsetof(TopoUnit, byPortNum),
	offsetof(TopoUnit, byInPortNum),
	offsetof(TopoUnit, byExPortNum),
	offsetof(TopoUnit, byInNodeNum),
	offsetof(TopoUnit, byLineNum),
	offsetof(TopoUnit, byBusNum),
	offsetof(TopoUnit, byThreadNum),
	offsetof(TopoUnit, dwElcNum),
};

//2. 微拓扑中所包含的部件支路定义(主要指：开关，刀闸，地刀)
static Juint16 TopoBuJianOffset[] = {
	offsetof(TopoBuJian, wFieldTypeID),
	offsetof(TopoBuJian, byRecID),

	offsetof(TopoBuJian, szElementType),
	offsetof(TopoBuJian, szElementName),
	offsetof(TopoBuJian, byElementID),
	
	offsetof(TopoBuJian, byNode1ID),
	offsetof(TopoBuJian, byNode2ID),
	offsetof(TopoBuJian, byNode3ID),
	offsetof(TopoBuJian, szDisNo),
};

//3. 微拓扑域中端口定义
static Juint16 TopoPortOffset[] = {
	offsetof(TopoPort, wFieldTypeID),
	offsetof(TopoPort, byRecID),
	
	offsetof(TopoPort, szPortTag),
	offsetof(TopoPort, byPortNodeID),
	offsetof(TopoPort, byInPortFlag),
	offsetof(TopoPort, wCorBusID),
};

//4. 微拓扑连线定义
static Juint16 TopoLineOffset[] = {
	offsetof(TopoLine, wFieldTypeID),
	offsetof(TopoLine, byRecID),

	offsetof(TopoLine, szLineName),
	offsetof(TopoLine, byLineID),
	offsetof(TopoLine, byBusFlag),
	offsetof(TopoLine, byPortNode),
};

//5. 微拓扑域带电查询定义
static Juint16 TopoEQueryOffset[] = {
		offsetof(TopoEQuery, wFieldTypeID),
		offsetof(TopoEQuery, byRecID),
		
		offsetof(TopoEQuery, AllInputFlag),
		offsetof(TopoEQuery, AllLineFlag),
};

//6. 微拓扑域预处理存放定义
static Juint16 TopoPreDealOffset[] = {
	offsetof(TopoPreDeal, wFieldTypeID),
		
	offsetof(TopoPreDeal, NodeData),
	offsetof(TopoPreDeal, BranchData),
};


//1. 电网微拓扑描述
static Juint16 DWTopoUnitOffset[] = {
	offsetof(DWTopoUnit, wChangZhanID),
	offsetof(DWTopoUnit, wDianYaDengJiID),
	offsetof(DWTopoUnit, wFieldID),
	offsetof(DWTopoUnit, wFieldTypeID),
	
	offsetof(DWTopoUnit, szName),
	offsetof(DWTopoUnit, byInUseFlag),
};

//2. 电网微拓扑部件定义
static Juint16 DWTopoBuJianOffset[] = {
	offsetof(DWTopoBuJian, wChangZhanID),
	offsetof(DWTopoBuJian, wDianYaDengJiID),
	offsetof(DWTopoBuJian, wFieldID),
	offsetof(DWTopoBuJian, wFieldTypeID),
	
	offsetof(DWTopoBuJian, byRecID),
	offsetof(DWTopoBuJian, byComponentNo),
	offsetof(DWTopoBuJian, byComponentType),
	offsetof(DWTopoBuJian, wComponentID),
};

//3. 电网微拓扑端口定义
static Juint16 DWTopoPortOffset[] = {
	offsetof(DWTopoPort, wChangZhanID),
	offsetof(DWTopoPort, wDianYaDengJiID),
	offsetof(DWTopoPort, wFieldID),
	offsetof(DWTopoPort, wFieldTypeID),
	
	offsetof(DWTopoPort, byRecID),
	offsetof(DWTopoPort, szPortName),
	offsetof(DWTopoPort, byInPortFlag),
	offsetof(DWTopoPort, nPnodeID),
	offsetof(DWTopoPort, byNodeID),
};

/////////////////////////////////////////////////////////////////////////////////////
//绘图填库功能对电网描述部件的操作

//1. 电网
static Juint16 Offset_TK_DianWang[] = {
	offsetof(TK_DianWang, wID),
	offsetof(TK_DianWang, szMingZi),
	offsetof(TK_DianWang, wWAQTian),
	offsetof(TK_DianWang, wSAQTian),
	offsetof(TK_DianWang, byPDSrcNum),
	offsetof(TK_DianWang, byPDSrcUse),
	offsetof(TK_DianWang, byQDSrcNum),
	offsetof(TK_DianWang, byQDSrcUse),
	offsetof(TK_DianWang, dPDDCoef),
	offsetof(TK_DianWang, dQDDCoef),
	offsetof(TK_DianWang, dPDJFCoef),
	offsetof(TK_DianWang, dQDJFCoef),
	offsetof(TK_DianWang, byJiFenDL),
	offsetof(TK_DianWang, byPinLuYueXianRec),
	offsetof(TK_DianWang, byPinLuYueXianPrt),
	offsetof(TK_DianWang, byPinLuYueXianSG),
};

//2. 电压等级
static Juint16 Offset_TK_DianYaDengJi[] = {
	offsetof(TK_DianYaDengJi, byID),
	offsetof(TK_DianYaDengJi, szMingZi),
	offsetof(TK_DianYaDengJi, fDianYaZhi),
};

//3. 厂站
static Juint16 Offset_TK_ChangZhan[] = {
	offsetof(TK_ChangZhan, wID),
	offsetof(TK_ChangZhan, szMingZi),
	offsetof(TK_ChangZhan, byDianYaDengJi1ID),
	offsetof(TK_ChangZhan, byDianYaDengJi2ID),
	offsetof(TK_ChangZhan, byDianYaDengJi3ID),
	offsetof(TK_ChangZhan, byDianYaDengJi4ID),
	offsetof(TK_ChangZhan, byDianYaDengJi5ID),
	offsetof(TK_ChangZhan, wCZAQTian),
	offsetof(TK_ChangZhan, byPDSrcNum),
	offsetof(TK_ChangZhan, byPDSrcUse),
	offsetof(TK_ChangZhan, byQDSrcNum ),
	offsetof(TK_ChangZhan, byQDSrcUse),
	offsetof(TK_ChangZhan, dPDCoef),
	offsetof(TK_ChangZhan, dQDCoef),
	offsetof(TK_ChangZhan, dPJFDCoef),
	offsetof(TK_ChangZhan, dQJFDCoef),
	offsetof(TK_ChangZhan, byJiFenDL),
	offsetof(TK_ChangZhan, byNobodyOnDuty),
	
	offsetof(TK_ChangZhan, szAlarmGra),
	offsetof(TK_ChangZhan, byAlarmGraLayer),
	offsetof(TK_ChangZhan, nAlarmGraX),
	offsetof(TK_ChangZhan, nAlarmGraY),
};

//EMS-Mend<
//李友金 2006.4.19 根据厂站表实际字段定义新的结构，实现iesdraw添加删除厂站功能
static Juint16 Offset_TK_ChangZhan_NEW[] = {
	offsetof(TK_ChangZhan_NEW, wID),
		offsetof(TK_ChangZhan_NEW, szMingZi),
		offsetof(TK_ChangZhan_NEW, wNetID),						//3		所属电网(新增)
		offsetof(TK_ChangZhan_NEW, wPowerCorpID),				//4		所属发电公司(新增)
		offsetof(TK_ChangZhan_NEW, wSubNetID),					//5		所属分区(新增)
		offsetof(TK_ChangZhan_NEW, byStationType),				//6		厂站类型(新增)
		
		offsetof(TK_ChangZhan_NEW, byDianYaDengJi1ID),
		offsetof(TK_ChangZhan_NEW, byDianYaDengJi2ID),
		offsetof(TK_ChangZhan_NEW, byDianYaDengJi3ID),
		offsetof(TK_ChangZhan_NEW, byDianYaDengJi4ID),
		offsetof(TK_ChangZhan_NEW, byDianYaDengJi5ID),
		offsetof(TK_ChangZhan_NEW, wCZAQTian),
		offsetof(TK_ChangZhan_NEW, byPDSrcNum),
		offsetof(TK_ChangZhan_NEW, byPDSrcUse),
		offsetof(TK_ChangZhan_NEW, byQDSrcNum ),
		offsetof(TK_ChangZhan_NEW, byQDSrcUse),
		offsetof(TK_ChangZhan_NEW, dPDCoef),
		offsetof(TK_ChangZhan_NEW, dQDCoef),
		offsetof(TK_ChangZhan_NEW, dPJFDCoef),
		offsetof(TK_ChangZhan_NEW, dQJFDCoef),
		offsetof(TK_ChangZhan_NEW, byJiFenDL),
		offsetof(TK_ChangZhan_NEW, byNobodyOnDuty),
		
		offsetof(TK_ChangZhan_NEW, byBrandFlag),		//23	挂牌标志(新增)
		offsetof(TK_ChangZhan_NEW, szAlarmGra),
		offsetof(TK_ChangZhan_NEW, byAlarmGraLayer),
		offsetof(TK_ChangZhan_NEW, nAlarmGraX),
		offsetof(TK_ChangZhan_NEW, nAlarmGraY),
		
		offsetof(TK_ChangZhan_NEW, FREQUENCY),					//28	频率(新增)
		offsetof(TK_ChangZhan_NEW, PASFLAG),  					//29	PAS标志(新增)
		offsetof(TK_ChangZhan_NEW, DTSFLAG),	 				//30	DTS标志(新增)	
		offsetof(TK_ChangZhan_NEW, EXSTATIONFLAG),				//31	外网厂站标志(新增)	
		offsetof(TK_ChangZhan_NEW, YCUSEDFLAG),	 				//32	参加计算标志(新增)	
		offsetof(TK_ChangZhan_NEW, PLOSSFLAG),	 				//33	网损计算标志(新增)	
		offsetof(TK_ChangZhan_NEW, PCoef),	 					//34	有功系数(新增)	
		offsetof(TK_ChangZhan_NEW, QCoef),	 					//35	无功系数(新增)	
		offsetof(TK_ChangZhan_NEW, FUELSTORAGE),				//36	储煤量(新增)	
		offsetof(TK_ChangZhan_NEW, WATERSTORAGE),				//37	储水量(新增)	
		offsetof(TK_ChangZhan_NEW, VarFlag),					//38	参与AVQC控制标志(新增)	
		offsetof(TK_ChangZhan_NEW, WorkMode),					//39	AVQC方案执行模式(新增)	
		offsetof(TK_ChangZhan_NEW, CosUpLmt),				//40	AVQC功率因数上限(新增)
		offsetof(TK_ChangZhan_NEW, CosDnLmt),				//41	AVQC功率因数下限(新增)
		offsetof(TK_ChangZhan_NEW, BaoHuID),					//42	保护动作指示部件ID(新增)
		offsetof(TK_ChangZhan_NEW, LoadID),						//43	厂站负荷对应的曲线ID(新增)
};
//EMS-Mend>
//EMS-Mend<
//李友金 2006.4.19 定义分区和发电公司结构，实现iesdraw添加删除厂站功能
// 分区
static Juint16 Offset_TK_FenQu[] = {
	offsetof(TK_FenQu, wID),
		offsetof(TK_FenQu, szMingZi),
};
// 发电公司
static Juint16 Offset_TK_FaDianGongSi[] = {
	offsetof(TK_FenQu, wID),
		offsetof(TK_FenQu, szMingZi),
};
//EMS-Mend>

////////////////////////////////////////////////

//4. 母线
static Juint16 Offset_TK_MuXian[] = {
	offsetof(TK_MuXian, wID),
	offsetof(TK_MuXian, wChangZhanID),
	offsetof(TK_MuXian, byDianYaDengJiID),
	offsetof(TK_MuXian, szBianHao),
	offsetof(TK_MuXian, szMingZi),
	offsetof(TK_MuXian, szProdType),
	offsetof(TK_MuXian, UsedTime),
	
	offsetof(TK_MuXian, wDYPTID),
	offsetof(TK_MuXian, wPTPhase),
	offsetof(TK_MuXian, bySEFlag),
	offsetof(TK_MuXian, fSERCoef),
	offsetof(TK_MuXian, wPanMuKaiGuanZuID),
	
	offsetof(TK_MuXian, byTJWay),
	offsetof(TK_MuXian, byAvVal),
	
	offsetof(TK_MuXian, wFieldType),
	offsetof(TK_MuXian, wStaFieldID),
	offsetof(TK_MuXian, wComponentID),
	offsetof(TK_MuXian, wMuXianType),//旁母识别
};
//5. 线路
static Juint16 Offset_TK_XianLu[] = {
	offsetof(TK_XianLu, wID),
	offsetof(TK_XianLu, szBianHao),
	offsetof(TK_XianLu, szMingZi),
	offsetof(TK_XianLu, byDianYaDengJiID),
	offsetof(TK_XianLu, wQiChangZhanID),
	offsetof(TK_XianLu, wZhChangZhanID),
	offsetof(TK_XianLu, szProdType),
	offsetof(TK_XianLu, UsedTime),
	offsetof(TK_XianLu, fR),
	offsetof(TK_XianLu, fX),
	offsetof(TK_XianLu, fB),

	offsetof(TK_XianLu, byQiBJType),
	offsetof(TK_XianLu, wQiDY1ID),
	offsetof(TK_XianLu, wQiDY2ID),
	offsetof(TK_XianLu, wQiDY3ID),
	offsetof(TK_XianLu, wQiDY4ID),
	offsetof(TK_XianLu, wQiDY5ID),
	offsetof(TK_XianLu, wFQiDY4ID),
	offsetof(TK_XianLu, wFQiDY5ID),

	offsetof(TK_XianLu, byZhBJType),
	offsetof(TK_XianLu, wZhDY1ID),
	offsetof(TK_XianLu, wZhDY2ID),
	offsetof(TK_XianLu, wZhDY3ID),
	offsetof(TK_XianLu, wZhDY4ID),
	offsetof(TK_XianLu, wZhDY5ID),
	offsetof(TK_XianLu, wFZhDY4ID),
	offsetof(TK_XianLu, wFZhDY5ID),
	
	offsetof(TK_XianLu, wQiPJHDDId),
	offsetof(TK_XianLu, wQiQJHDDId),
	offsetof(TK_XianLu, wFQiPJHDDId),
	offsetof(TK_XianLu, wFQiQJHDDId),
	offsetof(TK_XianLu, wZhPJHDDId),
	offsetof(TK_XianLu, wZhQJHDDId),
	offsetof(TK_XianLu, wFZhPJHDDId),
	offsetof(TK_XianLu, wFZhQJHDDId),
	
	offsetof(TK_XianLu, byQiPSEFlag),
	offsetof(TK_XianLu, fQiPSERCoef),
	offsetof(TK_XianLu, byQiQSEFlag),
	offsetof(TK_XianLu, fQiQSERCoef),
	offsetof(TK_XianLu, byQiISEFlag),
	offsetof(TK_XianLu, fQiISERCoef),
	offsetof(TK_XianLu, byZhPSEFlag),
	offsetof(TK_XianLu, fZhPSERCoef),
	offsetof(TK_XianLu, byZhQSEFlag),
	offsetof(TK_XianLu, fZhQSERCoef),
	offsetof(TK_XianLu, byZhISEFlag),
	offsetof(TK_XianLu, fZhISERCoef),
	
	offsetof(TK_XianLu, byQiPJHFlag),
	offsetof(TK_XianLu, byQiQJHFlag),
	offsetof(TK_XianLu, byZhPJHFlag),
	offsetof(TK_XianLu, byZhQJHFlag),
	
	offsetof(TK_XianLu, wFieldType),
	offsetof(TK_XianLu, wStaFieldID),
	offsetof(TK_XianLu, wComponentID),
};

//6. 开关
static Juint16 Offset_TK_KaiGuan[] = {
	offsetof(TK_KaiGuan, wID),
	offsetof(TK_KaiGuan, wChangZhanID),
	offsetof(TK_KaiGuan, byDianYaDengJiID),
	offsetof(TK_KaiGuan, szBianHao),
	offsetof(TK_KaiGuan, szMingZi),
	offsetof(TK_KaiGuan, szProdType),
	offsetof(TK_KaiGuan, UsedTime),

	offsetof(TK_KaiGuan, byDSrcNum),
	offsetof(TK_KaiGuan, byDSrcUse),
	
	offsetof(TK_KaiGuan, nDZCount),
	offsetof(TK_KaiGuan, nDZLimit),
	offsetof(TK_KaiGuan, nYKCount),
	offsetof(TK_KaiGuan, nYKSuccessCount),
	offsetof(TK_KaiGuan, nSGDZCount),
	offsetof(TK_KaiGuan, wCTID),
	offsetof(TK_KaiGuan, wPTIDBegin), 			//开关测量量对应的首端PT标示号
	offsetof(TK_KaiGuan, wPTIDEnd),             //开关测量量对应的末端PT标示号
	offsetof(TK_KaiGuan, wSGZID),
	
	offsetof(TK_KaiGuan, byKeKong),
	offsetof(TK_KaiGuan, byCZJiBie),
	
	offsetof(TK_KaiGuan, byYXCMode),
	offsetof(TK_KaiGuan, bySheZhiF),
	offsetof(TK_KaiGuan, byYXValue0),
	offsetof(TK_KaiGuan, byYXValue1),
	
	offsetof(TK_KaiGuan, byYXChRec),
	offsetof(TK_KaiGuan, byYXChAlarm),
	offsetof(TK_KaiGuan, byYXChPrint),
	offsetof(TK_KaiGuan, byYXChScr),
	offsetof(TK_KaiGuan, bySGPDFlag),
	
	offsetof(TK_KaiGuan, wFieldType),
	offsetof(TK_KaiGuan, wStaFieldID),
	offsetof(TK_KaiGuan, wComponentID),
};

//7. 刀闸
static Juint16 Offset_TK_DaoZha[] = {
	offsetof(TK_DaoZha, wID),
	offsetof(TK_DaoZha, wChangZhanID),
	offsetof(TK_DaoZha, byDianYaDengJiID),
	offsetof(TK_DaoZha, szBianHao),
	offsetof(TK_DaoZha, szMingZi),
	offsetof(TK_DaoZha, szProdType),
	offsetof(TK_DaoZha, byLeiXingID),
	offsetof(TK_DaoZha, UsedTime),
	
	offsetof(TK_DaoZha, byDSrcNum),
	offsetof(TK_DaoZha, byDSrcUse),
	
	offsetof(TK_DaoZha, byDYBJType),
	offsetof(TK_DaoZha, wDYBJID),
	offsetof(TK_DaoZha, nYKCount),
	offsetof(TK_DaoZha, nYKSuccessCount),
	offsetof(TK_DaoZha, byKeKong),
	offsetof(TK_DaoZha, byCZJiBie),
	offsetof(TK_DaoZha, byYXValue0),
	offsetof(TK_DaoZha, byYXValue1),
	offsetof(TK_DaoZha, bySheZhiF),
	offsetof(TK_DaoZha, byYXChRec),
	offsetof(TK_DaoZha, byYXChAlarm),
	offsetof(TK_DaoZha, byYXChPrint),
	offsetof(TK_DaoZha, byYXChScr),

	offsetof(TK_DaoZha, wDYPLKaiGuanID),
	
	offsetof(TK_DaoZha, wFieldType),
	offsetof(TK_DaoZha, wStaFieldID),
	offsetof(TK_DaoZha, wComponentID),
};
//8. 保护
static Juint16 Offset_TK_BaoHu[] = {
	offsetof(TK_BaoHu, wID),
	offsetof(TK_BaoHu, wChangZhanID),
	offsetof(TK_BaoHu, byDianYaDengJiID),
	offsetof(TK_BaoHu, szBianHao),
	offsetof(TK_BaoHu, szMingZi),
	
	offsetof(TK_BaoHu, byBuJianLeiXingID),
	offsetof(TK_BaoHu, wBuJianID),
	
	offsetof(TK_BaoHu, byDSrcNum),
	offsetof(TK_BaoHu, byDSrcUse),

	offsetof(TK_BaoHu, wBaoHuLeiXingID),
	
	offsetof(TK_BaoHu, wDZ1TypeID),
	offsetof(TK_BaoHu, wDZ2TypeID),
	offsetof(TK_BaoHu, wDZ3TypeID),
	offsetof(TK_BaoHu, wDZ4TypeID),
	offsetof(TK_BaoHu, wDZ5TypeID),
	offsetof(TK_BaoHu, wDZ6TypeID),
	offsetof(TK_BaoHu, wDZ7TypeID),
	offsetof(TK_BaoHu, wDZ8TypeID),

	offsetof(TK_BaoHu, fBHDingZhi1),
	offsetof(TK_BaoHu, fBHDingZhi2),
	offsetof(TK_BaoHu, fBHDingZhi3),
	offsetof(TK_BaoHu, fBHDingZhi4),
	offsetof(TK_BaoHu, fBHDingZhi5),
	offsetof(TK_BaoHu, fBHDingZhi6),
	offsetof(TK_BaoHu, fBHDingZhi7),
	offsetof(TK_BaoHu, fBHDingZhi8),
	
	offsetof(TK_BaoHu, byYXChRec),
	offsetof(TK_BaoHu, byYXChAlarm),
	offsetof(TK_BaoHu, byYXChPrint),
	offsetof(TK_BaoHu, byYXChScr),

	offsetof(TK_BaoHu, byKeKong),
	offsetof(TK_BaoHu, byDZhSheZhi),
	offsetof(TK_BaoHu, wSGZID),
	offsetof(TK_BaoHu, bySheZhiF),
	offsetof(TK_BaoHu, bySTValue),
	offsetof(TK_BaoHu, byKGSGFlag),
	//wugc<2010.8.23集控功能数据库及结构扩展
	offsetof(TK_BaoHu, byEvtLevel),
//DMS-MEND<wugc 2010.3.10 调控一体化研发.光字牌及保护分类显示
	offsetof(TK_BaoHu, byGZFlag),
	offsetof(TK_BaoHu, byRealYX),
	offsetof(TK_BaoHu, wZzlx),
////DMS-MEND>
    //wugc>
};

//9. 变压器
static Juint16 Offset_TK_BianYaQi[] = {
	offsetof(TK_BianYaQi, wID),
	offsetof(TK_BianYaQi, wChangZhanID),
	offsetof(TK_BianYaQi, szBianHao),
	offsetof(TK_BianYaQi, szMingZi),
	offsetof(TK_BianYaQi, szProdType),
	offsetof(TK_BianYaQi, UsedTime),
	offsetof(TK_BianYaQi, byGaoYaCeDengJiID),
	offsetof(TK_BianYaQi, byZhongYaCeDengJiID),
	offsetof(TK_BianYaQi, byDiYaCeDengJiID),

	offsetof(TK_BianYaQi, fSN),			//dtt add
	offsetof(TK_BianYaQi, fMVA),
	offsetof(TK_BianYaQi, fRH),
	offsetof(TK_BianYaQi, fRM),
	offsetof(TK_BianYaQi, fRL),
	offsetof(TK_BianYaQi, fXH),
	offsetof(TK_BianYaQi, fXM),
	offsetof(TK_BianYaQi, fXL),
	offsetof(TK_BianYaQi, fKHM),
	offsetof(TK_BianYaQi, fKML),		//dtt add
	offsetof(TK_BianYaQi, fKHL),
	
	offsetof(TK_BianYaQi, byGaoBJ1Type),
	offsetof(TK_BianYaQi, wGaoBJ1ID),
	offsetof(TK_BianYaQi, byGaoBJ2Type),
	offsetof(TK_BianYaQi, wGaoBJ2ID),
	offsetof(TK_BianYaQi, byZhongBJ1Type),
	offsetof(TK_BianYaQi, wZhongBJ1ID),
	offsetof(TK_BianYaQi, byZhongBJ2Type),
	offsetof(TK_BianYaQi, wZhongBJ2ID),
	offsetof(TK_BianYaQi, byDiBJ1Type),
	offsetof(TK_BianYaQi, wDiBJ1ID),
	offsetof(TK_BianYaQi, byDiBJ2Type),
	offsetof(TK_BianYaQi, wDiBJ2ID),
	
	offsetof(TK_BianYaQi, byGPSEFlag),
	offsetof(TK_BianYaQi, fGPSERCoef),
	offsetof(TK_BianYaQi, byGQSEFlag),
	offsetof(TK_BianYaQi, fGQSERCoef),
	offsetof(TK_BianYaQi, byGISEFlag),
	offsetof(TK_BianYaQi, fGISERCoef),
	offsetof(TK_BianYaQi, byZPSEFlag),
	offsetof(TK_BianYaQi, fZPSERCoef),
	offsetof(TK_BianYaQi, byZQSEFlag),
	offsetof(TK_BianYaQi, fZQSERCoef),
	offsetof(TK_BianYaQi, byZISEFlag),
	offsetof(TK_BianYaQi, fZISERCoef),
	offsetof(TK_BianYaQi, byDPSEFlag),
	offsetof(TK_BianYaQi, fDPSERCoef),
	offsetof(TK_BianYaQi, byDQSEFlag),
	offsetof(TK_BianYaQi, fDQSERCoef),
	offsetof(TK_BianYaQi, byDISEFlag),
	offsetof(TK_BianYaQi, fDISERCoef),
	
	offsetof(TK_BianYaQi, byFJTWeiZhiShu),
	offsetof(TK_BianYaQi, byDWDSrcNum),
	offsetof(TK_BianYaQi, byDWDSrcUse),
	offsetof(TK_BianYaQi, byDWRevWay),
	offsetof(TK_BianYaQi, byDWMFlag),
	offsetof(TK_BianYaQi, nDWMVal),
	
	offsetof(TK_BianYaQi, byKeKong),
	offsetof(TK_BianYaQi, byCZJiBie),
	offsetof(TK_BianYaQi, byDYMode),
	
	offsetof(TK_BianYaQi, byTDSrcNum),
	offsetof(TK_BianYaQi, byTDSrcUse),	
	offsetof(TK_BianYaQi, byTMFlag),
	offsetof(TK_BianYaQi, fTMVal),
	
	offsetof(TK_BianYaQi, wSJTimeLimit),
	offsetof(TK_BianYaQi, wSJTimes),
	offsetof(TK_BianYaQi, wDSJTimeLimit),
	offsetof(TK_BianYaQi, wDSJTimes),
	
	offsetof(TK_BianYaQi, wFieldType),
	offsetof(TK_BianYaQi, wStaFieldID),
	offsetof(TK_BianYaQi, wComponentID),
	//EMS-Mend dingjide 2009.4.22
	//修改原因:短路电流中变压器中性点接地刀闸的问题
	//EMS-Mend<
	offsetof(TK_BianYaQi, wGaoZxdDdID),
	offsetof(TK_BianYaQi, wZhongZxdDdID),
	//EMS-Mend<
};
//10. 发电机
static Juint16 Offset_TK_FaDianJi[] = {
	offsetof(TK_FaDianJi, wID),
	offsetof(TK_FaDianJi, wChangZhanID),
	offsetof(TK_FaDianJi, byDianYaDengJiID),
	offsetof(TK_FaDianJi, szBianHao),
	offsetof(TK_FaDianJi, szMingZi),
	offsetof(TK_FaDianJi, szProdType),
	offsetof(TK_FaDianJi, fJiZuRongLiang),

	offsetof(TK_FaDianJi, byBJType1ID),
	offsetof(TK_FaDianJi, wBJ1ID),
	offsetof(TK_FaDianJi, byBJType2ID),
	offsetof(TK_FaDianJi, wBJ2ID),
	
	offsetof(TK_FaDianJi, byPSEFlag),
	offsetof(TK_FaDianJi, fPSERCoef),
	offsetof(TK_FaDianJi, byQSEFlag),
	offsetof(TK_FaDianJi, fQSERCoef),
	offsetof(TK_FaDianJi, byISEFlag),
	offsetof(TK_FaDianJi, fISERCoef),

	offsetof(TK_FaDianJi, byTingYunShiJian),

	offsetof(TK_FaDianJi, wFieldType),
	offsetof(TK_FaDianJi, wStaFieldID),
	offsetof(TK_FaDianJi, wComponentID),
};
//11. CT
static Juint16 Offset_TK_CT[] = {
	offsetof(TK_CT, wID),
	offsetof(TK_CT, wChangZhanID),
	offsetof(TK_CT, byDianYaDengJiID),
	offsetof(TK_CT, szBianHao),
	offsetof(TK_CT, szMingZi),
	offsetof(TK_CT, szProdType),
	offsetof(TK_CT, UsedTime),
	offsetof(TK_CT, szTranRate),
	offsetof(TK_CT, wPTAddID),
	offsetof(TK_CT, byPTPhase),

	offsetof(TK_CT, byPDSrcNum),
	offsetof(TK_CT, byPDSrcUse),

	offsetof(TK_CT, byQDSrcNum),
	offsetof(TK_CT, byQDSrcUse),

	offsetof(TK_CT, byIaDSrcNum),
	offsetof(TK_CT, byIaDSrcUse),
	
	offsetof(TK_CT, byIbDSrcNum),
	offsetof(TK_CT, byIbDSrcUse),
	
	offsetof(TK_CT, byIcDSrcNum),
	offsetof(TK_CT, byIcDSrcUse),

	offsetof(TK_CT, byIoDSrcNum),
	offsetof(TK_CT, byIoDSrcUse),
	
	offsetof(TK_CT, byIhDSrcNum),
	offsetof(TK_CT, byIhDSrcUse),

	offsetof(TK_CT, bySDSrcNum),
	offsetof(TK_CT, bySDSrcUse),
	
	offsetof(TK_CT, byCosDSrcNum),
	offsetof(TK_CT, byCosDSrcUse),

	offsetof(TK_CT, byFDSrcNum),
	offsetof(TK_CT, byFDSrcUse),

	offsetof(TK_CT, dZPDDCoef),
	offsetof(TK_CT, dZQDDCoef),
	offsetof(TK_CT, dFPDDCoef),
	offsetof(TK_CT, dFQDDCoef),
	offsetof(TK_CT, dPDCoef),
	offsetof(TK_CT, dQDCoef),
	offsetof(TK_CT, dFPDCoef),
	offsetof(TK_CT, dFQDCoef),
	offsetof(TK_CT, byDDMode),
	offsetof(TK_CT, byDDClear),
	
	offsetof(TK_CT, byPCFlag),
	offsetof(TK_CT, byQCFlag),
	offsetof(TK_CT, byIaCFlag),

	offsetof(TK_CT, byPMFlag),
	offsetof(TK_CT, fPMVal),

	offsetof(TK_CT, byQMFlag),
	offsetof(TK_CT, fQMVal),

	offsetof(TK_CT, byIaMFlag),
	offsetof(TK_CT, fIaMVal),

	offsetof(TK_CT, byIbMFlag),
	offsetof(TK_CT, fIbMVal),

	offsetof(TK_CT, byIcMFlag),
	offsetof(TK_CT, fIcMVal),

	offsetof(TK_CT, byIoMFlag),
	offsetof(TK_CT, fIoMVal),

	offsetof(TK_CT, byIhMFlag),
	offsetof(TK_CT, fIhMVal),

	offsetof(TK_CT, bySMFlag),
	offsetof(TK_CT, fSMVal),

	offsetof(TK_CT, byCosMFlag),
	offsetof(TK_CT, fCosMVal),

	offsetof(TK_CT, byFMFlag),
	offsetof(TK_CT, fFMVal),
	
	offsetof(TK_CT, byPRmtW),
	offsetof(TK_CT, byPFRmtW),
	offsetof(TK_CT, byQRmtW),
	offsetof(TK_CT, byQFRmtW),

	offsetof(TK_CT, byPJFFlag),
	offsetof(TK_CT, byQJFFlag),
};

//12. PT
static Juint16 Offset_TK_PT[] = {
	offsetof(TK_PT, wID),
	offsetof(TK_PT, wChangZhanID),
	offsetof(TK_PT, byDianYaDengJiID),
	offsetof(TK_PT, szBianHao),
	offsetof(TK_PT, szMingZi),
	offsetof(TK_PT, szProdType),
	offsetof(TK_PT, UsedTime),
	offsetof(TK_PT, szTranRate),

	offsetof(TK_PT, byUaDSrcNum),
	offsetof(TK_PT, byUaDSrcUse),

	offsetof(TK_PT, byUbDSrcNum),
	offsetof(TK_PT, byUbDSrcUse),

	offsetof(TK_PT, byUcDSrcNum),
	offsetof(TK_PT, byUcDSrcUse),

	offsetof(TK_PT, byUabxDSrcNum),
	offsetof(TK_PT, byUabxDSrcUse),

	offsetof(TK_PT, byUbcxDSrcNum),
	offsetof(TK_PT, byUbcxDSrcUse),

	offsetof(TK_PT, byUcaxDSrcNum),
	offsetof(TK_PT, byUcaxDSrcUse),

	offsetof(TK_PT, byUoDSrcNum),
	offsetof(TK_PT, byUoDSrcUse),

	offsetof(TK_PT, byUangDSrcNum),
	offsetof(TK_PT, byUangDSrcUse),
	
	offsetof(TK_PT, byUaMFlag),
	offsetof(TK_PT, fUaMVal),

	offsetof(TK_PT, byUbMFlag),
	offsetof(TK_PT, fUbMVal),

	offsetof(TK_PT, byUcMFlag),
	offsetof(TK_PT, fUcMVal),

	offsetof(TK_PT, byUabxMFlag),
	offsetof(TK_PT, fUabxMVal),

	offsetof(TK_PT, byUbcxMFlag),
	offsetof(TK_PT, fUbcxMVal),

	offsetof(TK_PT, byUcaxMFlag),
	offsetof(TK_PT, fUcaxMVal),

	offsetof(TK_PT, byUoMFlag),
	offsetof(TK_PT, fUoMVal),

	offsetof(TK_PT, byUangMFlag),
	offsetof(TK_PT, fUangMVal),
};

//13. 负荷
static Juint16 Offset_TK_FuHe[] = {
	offsetof(TK_FuHe, wID),
	offsetof(TK_FuHe, wChangZhanID),
	offsetof(TK_FuHe, byDianYaDengJiID),
	offsetof(TK_FuHe, szBianHao),
	offsetof(TK_FuHe, szMingZi),
	offsetof(TK_FuHe, byFHJiBie),

	offsetof(TK_FuHe, byLJBJType),
	offsetof(TK_FuHe, wLJDY1ID),
	offsetof(TK_FuHe, wLJDY2ID),
	offsetof(TK_FuHe, wLJDY3ID),
	offsetof(TK_FuHe, wLJDY4ID),
	offsetof(TK_FuHe, wLJDY5ID),
	offsetof(TK_FuHe, wFLJDY4ID),
	offsetof(TK_FuHe, wFLJDY5ID),
	
	offsetof(TK_FuHe, byPJHFlag),
	offsetof(TK_FuHe, byQJHFlag),
	offsetof(TK_FuHe, wPJHDDId),
	offsetof(TK_FuHe, wQJHDDId),
	offsetof(TK_FuHe, wFPJHDDId),
	offsetof(TK_FuHe, wFQJHDDId),

	offsetof(TK_FuHe, byPSEFlag),
	offsetof(TK_FuHe, fPSERCoef),
	offsetof(TK_FuHe, byQSEFlag),
	offsetof(TK_FuHe, fQSERCoef),
	offsetof(TK_FuHe, byISEFlag),
	offsetof(TK_FuHe, fISERCoef),
	
	offsetof(TK_FuHe, fTopoCoef),
	offsetof(TK_FuHe, wFieldType),
	offsetof(TK_FuHe, wStaFieldID),
	offsetof(TK_FuHe, wComponentID),
};

//14. 注入
static Juint16 Offset_TK_ZhuRu[] = {
	offsetof(TK_ZhuRu, wID),
	offsetof(TK_ZhuRu, wChangZhanID),
	offsetof(TK_ZhuRu, byDianYaDengJiID),
	offsetof(TK_ZhuRu, szBianHao),
	offsetof(TK_ZhuRu, szMingZi),

	offsetof(TK_ZhuRu, byDYBJType),
	offsetof(TK_ZhuRu, wPId),
	offsetof(TK_ZhuRu, wQId),
	offsetof(TK_ZhuRu, wIId),
	
	offsetof(TK_ZhuRu, byLJBJType1),
	offsetof(TK_ZhuRu, wLJBJ1ID),
	offsetof(TK_ZhuRu, byLJBJ1CS),
	
	offsetof(TK_ZhuRu, byPSEFlag),
	offsetof(TK_ZhuRu, fPSERCoef),
	offsetof(TK_ZhuRu, byQSEFlag),
	offsetof(TK_ZhuRu, fQSERCoef),
	offsetof(TK_ZhuRu, byISEFlag),
	offsetof(TK_ZhuRu, fISERCoef),
	
	offsetof(TK_ZhuRu, fTopoCoef),
	offsetof(TK_ZhuRu, wFieldType),
	offsetof(TK_ZhuRu, wStaFieldID),
	offsetof(TK_ZhuRu, wComponentID),
};

//15. 调相机
static Juint16 Offset_TK_TiaoXiangJi[] = {
	offsetof(TK_TiaoXiangJi, wID),
	offsetof(TK_TiaoXiangJi, wChangZhanID),
	offsetof(TK_TiaoXiangJi, byDianYaDengJiID),
	offsetof(TK_TiaoXiangJi, szBianHao),
	offsetof(TK_TiaoXiangJi, szMingZi),
	offsetof(TK_TiaoXiangJi, szProdType),
	offsetof(TK_TiaoXiangJi, UsedTime),
	offsetof(TK_TiaoXiangJi, wTouQieKGID),
	offsetof(TK_TiaoXiangJi, fR),
	offsetof(TK_TiaoXiangJi, fX),
	offsetof(TK_TiaoXiangJi, fB),
	
	offsetof(TK_TiaoXiangJi, byLJBJType1),
	offsetof(TK_TiaoXiangJi, wLJBJ1ID),
	offsetof(TK_TiaoXiangJi, byLJBJ1CS),
	offsetof(TK_TiaoXiangJi, byLJBJType2),
	offsetof(TK_TiaoXiangJi, wLJBJ2ID),
	offsetof(TK_TiaoXiangJi, byLJBJ2CS),

	offsetof(TK_TiaoXiangJi, byTouQieTimeF),

	offsetof(TK_TiaoXiangJi, wFieldType),
	offsetof(TK_TiaoXiangJi, wStaFieldID),
	offsetof(TK_TiaoXiangJi, wComponentID),
};

//16. 静止补偿器
static Juint16 Offset_TK_JingZhiBuChang[] = {
	offsetof(TK_JingZhiBuChang, wID),
	offsetof(TK_JingZhiBuChang, wChangZhanID),
	offsetof(TK_JingZhiBuChang, byDianYaDengJiID),
	offsetof(TK_JingZhiBuChang, szBianHao),
	offsetof(TK_JingZhiBuChang, szMingZi),
	offsetof(TK_JingZhiBuChang, szProdType),
	offsetof(TK_JingZhiBuChang, UsedTime),
	offsetof(TK_JingZhiBuChang, wTouQieKGID),	
	offsetof(TK_JingZhiBuChang, fR),
	offsetof(TK_JingZhiBuChang, fX),
	offsetof(TK_JingZhiBuChang, fB),
	
	offsetof(TK_JingZhiBuChang, byLJBJType1),
	offsetof(TK_JingZhiBuChang, wLJBJ1ID),
	offsetof(TK_JingZhiBuChang, byLJBJ1CS),
	offsetof(TK_JingZhiBuChang, byLJBJType2),
	offsetof(TK_JingZhiBuChang, wLJBJ2ID),
	offsetof(TK_JingZhiBuChang, byLJBJ2CS),

	offsetof(TK_JingZhiBuChang, byTouQieTimeF),
	
	offsetof(TK_JingZhiBuChang, wFieldType),
	offsetof(TK_JingZhiBuChang, wStaFieldID),
	offsetof(TK_JingZhiBuChang, wComponentID),
};
//17. 并联电容补偿器
static Juint16 Offset_TK_BingLianDianRong[] = {
	offsetof(TK_BingLianDianRong, wID),
	offsetof(TK_BingLianDianRong, wChangZhanID),
	offsetof(TK_BingLianDianRong, byDianYaDengJiID),
	offsetof(TK_BingLianDianRong, szBianHao),
	offsetof(TK_BingLianDianRong, szMingZi),
	offsetof(TK_BingLianDianRong, szProdType),
	offsetof(TK_BingLianDianRong, UsedTime),
	offsetof(TK_BingLianDianRong, wTouQieKGID),
	offsetof(TK_BingLianDianRong, fC),
	offsetof(TK_BingLianDianRong, fR),
	offsetof(TK_BingLianDianRong, fX),
	offsetof(TK_BingLianDianRong, fB),
	
	offsetof(TK_BingLianDianRong, byLJBJType1),
	offsetof(TK_BingLianDianRong, wLJBJ1ID),
	offsetof(TK_BingLianDianRong, byLJBJ1CS),
	offsetof(TK_BingLianDianRong, byLJBJType2),
	offsetof(TK_BingLianDianRong, wLJBJ2ID),
	offsetof(TK_BingLianDianRong, byLJBJ2CS),

	offsetof(TK_BingLianDianRong, byTouQieTimeF),

	offsetof(TK_BingLianDianRong, wFieldType),
	offsetof(TK_BingLianDianRong, wStaFieldID),
	offsetof(TK_BingLianDianRong, wComponentID),
};
//18. 串联电抗
static Juint16 Offset_TK_ChuanLianDianKang[] = {
	offsetof(TK_ChuanLianDianKang, wID),
	offsetof(TK_ChuanLianDianKang, wChangZhanID),
	offsetof(TK_ChuanLianDianKang, byDianYaDengJiID),
	offsetof(TK_ChuanLianDianKang, szBianHao),
	offsetof(TK_ChuanLianDianKang, szMingZi),
	offsetof(TK_ChuanLianDianKang, szProdType),
	offsetof(TK_ChuanLianDianKang, UsedTime),
	offsetof(TK_ChuanLianDianKang, wDYDianRongID),

	offsetof(TK_ChuanLianDianKang, fX1),
	offsetof(TK_ChuanLianDianKang, fR1),
	offsetof(TK_ChuanLianDianKang, fM),
	offsetof(TK_ChuanLianDianKang, fX2),
	offsetof(TK_ChuanLianDianKang, fR2),
	
	offsetof(TK_ChuanLianDianKang, byLJBJType1),
	offsetof(TK_ChuanLianDianKang, wLJBJ1ID),
	offsetof(TK_ChuanLianDianKang, byLJBJ1CS),
	offsetof(TK_ChuanLianDianKang, byLJBJType2),
	offsetof(TK_ChuanLianDianKang, wLJBJ2ID),
	offsetof(TK_ChuanLianDianKang, byLJBJ2CS),
	offsetof(TK_ChuanLianDianKang, byLJBJType3),
	offsetof(TK_ChuanLianDianKang, wLJBJ3ID),
	offsetof(TK_ChuanLianDianKang, byLJBJ3CS),

	offsetof(TK_ChuanLianDianKang, byLJType),
	offsetof(TK_ChuanLianDianKang, byTouQieTimeF),
	
	offsetof(TK_ChuanLianDianKang, wFieldType),
	offsetof(TK_ChuanLianDianKang, wStaFieldID),
	offsetof(TK_ChuanLianDianKang, wComponentID),
};

//21. 虚拟模拟量
static Juint16 Offset_TK_XuNiDMNLiang[] = {
	offsetof(TK_XuNiDMNLiang, wID),
	offsetof(TK_XuNiDMNLiang, wChangZhanID),
	offsetof(TK_XuNiDMNLiang, szBianHao),
	offsetof(TK_XuNiDMNLiang, szMingZi),
	offsetof(TK_XuNiDMNLiang, byXNType),
	offsetof(TK_XuNiDMNLiang, byDYBJType),
	offsetof(TK_XuNiDMNLiang, wDYBJID),
	
	offsetof(TK_XuNiDMNLiang, byDSrcNum),
	offsetof(TK_XuNiDMNLiang, byDSrcUse),

	offsetof(TK_XuNiDMNLiang, byMFlag),
	offsetof(TK_XuNiDMNLiang, fMVal),
};
//23. 虚拟电度量
static Juint16 Offset_TK_XuNiSMNLiang[] = {
	offsetof(TK_XuNiSMNLiang, wID),
	offsetof(TK_XuNiSMNLiang, wChangZhanID),
	offsetof(TK_XuNiSMNLiang, szBianHao),
	offsetof(TK_XuNiSMNLiang, szMingZi),
	offsetof(TK_XuNiSMNLiang, byXNType),
	offsetof(TK_XuNiSMNLiang, byDYBJType),
	offsetof(TK_XuNiSMNLiang, wDYBJID),
	
	offsetof(TK_XuNiSMNLiang, byDSrcNum),
	offsetof(TK_XuNiSMNLiang, byDSrcUse),

	offsetof(TK_XuNiSMNLiang, dCoef),

	offsetof(TK_XuNiSMNLiang, byRemoteF),
	offsetof(TK_XuNiSMNLiang, byJFFlag),
};
//24. 虚拟状态量
static Juint16 Offset_TK_XuNiZHTLiang[] = {
	offsetof(TK_XuNiZHTLiang, wID),
	offsetof(TK_XuNiZHTLiang, wChangZhanID),
	offsetof(TK_XuNiZHTLiang, szBianHao),
	offsetof(TK_XuNiZHTLiang, szMingZi),
	offsetof(TK_XuNiZHTLiang, byXNType),
	offsetof(TK_XuNiZHTLiang, byDYBJType),
	offsetof(TK_XuNiZHTLiang, wDYBJID),

	offsetof(TK_XuNiZHTLiang, nDZCount),

	offsetof(TK_XuNiZHTLiang, byDSrcNum),
	offsetof(TK_XuNiZHTLiang, byDSrcUse),

	offsetof(TK_XuNiZHTLiang, bySheZhiF),
	offsetof(TK_XuNiZHTLiang, bySTValue),
	offsetof(TK_XuNiZHTLiang, byTJTouQie),
	offsetof(TK_XuNiZHTLiang, byKeKong),
	offsetof(TK_XuNiZHTLiang, byCZJiBie),
	offsetof(TK_XuNiZHTLiang, byChRec),
	offsetof(TK_XuNiZHTLiang, byChAlarm),
	offsetof(TK_XuNiZHTLiang, byChPrint),
	offsetof(TK_XuNiZHTLiang, byChScr),
};

// EMS-Mend<yuecaijuan 2010.11.17 调配一体化开发I期
// 修改原因：馈线
static Juint16 Offset_TK_Feeder[] = {
	offsetof(TK_Feeder,wID),
	offsetof(TK_Feeder,szBianHao),
	offsetof(TK_Feeder,szName),
	offsetof(TK_Feeder,szNO),
	offsetof(TK_Feeder,wChangZhanID),
	offsetof(TK_Feeder,byDianYaDengJiID),
};
// EMS-Mend>
static Juint16 Offset_TK_KuiXianDuan[] = {
	offsetof(TK_KuiXianDuan,wID),
	offsetof(TK_KuiXianDuan,szBianHao),
	offsetof(TK_KuiXianDuan,szName),
	offsetof(TK_KuiXianDuan,szNO),
	offsetof(TK_KuiXianDuan,szALIAS),
	offsetof(TK_KuiXianDuan,wChangZhanID),
	offsetof(TK_KuiXianDuan,byDianYaDengJiID),
	offsetof(TK_KuiXianDuan,byBJType),
	offsetof(TK_KuiXianDuan,wBJID),
	offsetof(TK_KuiXianDuan,wFEEDERID),
	offsetof(TK_KuiXianDuan,nSNODEID),
	offsetof(TK_KuiXianDuan,szSNODE),
	offsetof(TK_KuiXianDuan,nENODEID),
	offsetof(TK_KuiXianDuan,szENODE),
	offsetof(TK_KuiXianDuan,fCABLELEN),
	offsetof(TK_KuiXianDuan,byDFEEDERSECTIONTYPE),
	offsetof(TK_KuiXianDuan,szTBAKEP1),
	offsetof(TK_KuiXianDuan,szTBAKEP2),
	offsetof(TK_KuiXianDuan,byRUNSTATE),
	offsetof(TK_KuiXianDuan,byTOPOLEVEL),
	offsetof(TK_KuiXianDuan,szDESCRIPTION),
	offsetof(TK_KuiXianDuan,wFieldType),
	offsetof(TK_KuiXianDuan,wStaFieldID),
	offsetof(TK_KuiXianDuan,wComponentID),
	offsetof(TK_KuiXianDuan,szEXID),
};

static Juint16 Offset_TK_PBBianYaQi[] = 
{
	offsetof(TK_PBBianYaQi,wID),
	offsetof(TK_PBBianYaQi,szBianHao),
	offsetof(TK_PBBianYaQi,szName),
	offsetof(TK_PBBianYaQi,szNO),
	offsetof(TK_PBBianYaQi,wChangZhanID),
	offsetof(TK_PBBianYaQi,byGaoDianYaDengJiID),
	offsetof(TK_PBBianYaQi,byDiDianYaDengJiID),
	offsetof(TK_PBBianYaQi,byGaoBJType),
	offsetof(TK_PBBianYaQi,wGaoBJID),
	offsetof(TK_PBBianYaQi,byDiBJType),
	offsetof(TK_PBBianYaQi,wDiBJID),
	offsetof(TK_PBBianYaQi,wFEEDERID),
	offsetof(TK_PBBianYaQi,wBCUSTOMERID),
	offsetof(TK_PBBianYaQi,wNODEID),
	offsetof(TK_PBBianYaQi,szNODE),
	offsetof(TK_PBBianYaQi,fCAPACITY),
	offsetof(TK_PBBianYaQi,byRUNSTATE),
	offsetof(TK_PBBianYaQi,byPON),
	offsetof(TK_PBBianYaQi,byPAON),
	offsetof(TK_PBBianYaQi,byPBON),
	offsetof(TK_PBBianYaQi,byPCON),
	offsetof(TK_PBBianYaQi,byQON),
	offsetof(TK_PBBianYaQi,byQAON),
	offsetof(TK_PBBianYaQi,byQBON),
	offsetof(TK_PBBianYaQi,byQCON),
	offsetof(TK_PBBianYaQi,byIAON),
	offsetof(TK_PBBianYaQi,byIBON),
	offsetof(TK_PBBianYaQi,byICON),
	offsetof(TK_PBBianYaQi,byI0ON),
	offsetof(TK_PBBianYaQi,byPFON),
	offsetof(TK_PBBianYaQi,byPFAON),
	offsetof(TK_PBBianYaQi,byPFBON),
	offsetof(TK_PBBianYaQi,byPFCON),
	offsetof(TK_PBBianYaQi,byPDLON),
	offsetof(TK_PBBianYaQi,byPDLAON),
	offsetof(TK_PBBianYaQi,byPDLBON),
	offsetof(TK_PBBianYaQi,byPDLCON),
	offsetof(TK_PBBianYaQi,byQDLON),
	offsetof(TK_PBBianYaQi,byQDLAON),
	offsetof(TK_PBBianYaQi,byQDLBON),
	offsetof(TK_PBBianYaQi,byQDLCON),
	offsetof(TK_PBBianYaQi,byREVPDLON),
	offsetof(TK_PBBianYaQi,byREVPDLAON),
	offsetof(TK_PBBianYaQi,byREVPDLBON),
	offsetof(TK_PBBianYaQi,byREVPDLCON),
	offsetof(TK_PBBianYaQi,byREVQDLON),
	offsetof(TK_PBBianYaQi,byREVQDLAON),
	offsetof(TK_PBBianYaQi,byREVQDLBON),
	offsetof(TK_PBBianYaQi,byREVQDLCON),
	offsetof(TK_PBBianYaQi,byVA1ON),
	offsetof(TK_PBBianYaQi,byVB1ON),
	offsetof(TK_PBBianYaQi,byVC1ON),
	offsetof(TK_PBBianYaQi,byVAB1ON),
	offsetof(TK_PBBianYaQi,byVBC1O),
	offsetof(TK_PBBianYaQi,byVCA1ON),
	offsetof(TK_PBBianYaQi,byV01ON),
	offsetof(TK_PBBianYaQi,byAPSEFLAG),
	offsetof(TK_PBBianYaQi,fAPSERCOEF),
	offsetof(TK_PBBianYaQi,byAQSEFLAG),
	offsetof(TK_PBBianYaQi,fAQSERCOEF),
	offsetof(TK_PBBianYaQi,byAISEFLAG),
	offsetof(TK_PBBianYaQi,fAISERCOEF),
	offsetof(TK_PBBianYaQi,byBPSEFLAG),
	offsetof(TK_PBBianYaQi,fBPSERCOEF),
	offsetof(TK_PBBianYaQi,byBQSEFLAG),
	offsetof(TK_PBBianYaQi,fBQSERCOEF),
	offsetof(TK_PBBianYaQi,byBISEFLAG),
	offsetof(TK_PBBianYaQi,fBISERCOEF),
	offsetof(TK_PBBianYaQi,byCPSEFLAG),
	offsetof(TK_PBBianYaQi,fCPSERCOEF),
	offsetof(TK_PBBianYaQi,byCQSEFLAG),
	offsetof(TK_PBBianYaQi,fCQSERCOEF),
	offsetof(TK_PBBianYaQi,byCISEFLAG),
	offsetof(TK_PBBianYaQi,fCISERCOEF),
	offsetof(TK_PBBianYaQi,byHADJUSTMODE),
	offsetof(TK_PBBianYaQi,byHCANBEYK),
	offsetof(TK_PBBianYaQi,byINSTATIONFLAG),
	offsetof(TK_PBBianYaQi,wHYKTIMESLMT),
	offsetof(TK_PBBianYaQi,wHYKTIMES),
	offsetof(TK_PBBianYaQi,szDESCRIPTION),
	offsetof(TK_PBBianYaQi,wFieldType),
	offsetof(TK_PBBianYaQi,wStaFieldID),
	offsetof(TK_PBBianYaQi,wComponentID),
	offsetof(TK_PBBianYaQi,szEXID),
}
#endif
//===================================================================
//

