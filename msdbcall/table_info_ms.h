//====================================================================
// 文件名: msdb_table_info.h
//
// 文件描述:
// ------------------------------------------------------------------
// 描述库表结构数组定义
// ------------------------------------------------------------------
// 时间: 2002.9
// 编程: 喻宜
// ------------------------------------------------------------------
// 修改说明(请按格式说明)...
//====================================================================

//=================================================================
// 电网部件组
//-----------------------------------------------------------------
//电网
;
static SClmInfo aDianWang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ IES_SQL_STRING, NAMELEN, "MingZi" },						//名字
	{ IES_SQL_USMALLINT, 0, "WAQTian" },						//网安全天
	{ IES_SQL_USMALLINT, 0, "SAQTian" },						//所安全天
	{ IES_SQL_UTINYINT, 0, "PDSrcNum" },						//P 数据源个数
	{ IES_SQL_UTINYINT, 0, "PDSrcUse" },						//P 当前使用数据源
	{ IES_SQL_UTINYINT, 0, "QDSrcNum" },						//Q 数据源个数
	{ IES_SQL_UTINYINT, 0, "QDSrcUse" },						//Q 当前使用数据源
	{ IES_SQL_DOUBLE, 0, "PDDCoef" },							//PKWH 系数
	{ IES_SQL_DOUBLE, 0, "QDDCoef" },							//QKWH 系数
	{ IES_SQL_DOUBLE, 0, "PDJFCoef" },							//有功积分电量系数
	{ IES_SQL_DOUBLE, 0, "QDJFCoef" },							//无功积分电量系数
	{ IES_SQL_BOOL, 0, "JiFenDL" },								//计算积分电量标志
	{ IES_SQL_BOOL, 0, "PinLuYueXianRec" },						//频率越限记录
	{ IES_SQL_BOOL, 0, "PinLuYueXianPrt" },						//频率越限打印
	{ IES_SQL_BOOL, 0, "PinLuYueXianSG" },						//频率越限报警
};

//电压等级
static SClmInfo aDianYaDengJi_Col[] =
{
	{ IES_SQL_USMALLINT, 0, "ID" },								//ID
	{ IES_SQL_STRING, NAMELEN, "MingZi" },						//名字
	{ IES_SQL_FLOAT, 0, "DianYaZhi" },							//额定值
} ;

//厂站
static SClmInfo aChangZhan_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi1ID" },					//电压等级1
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi2ID" },					//电压等级2
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi3ID" },					//电压等级3
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi4ID" },					//电压等级4
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi5ID" },					//电压等级5
	// DMS-MEND>
	{ IES_SQL_USMALLINT, 0, "CZAQTian" },						//厂安全天
	{ IES_SQL_UTINYINT, 0, "PDSrcNum" },						//P 数据源个数
	{ IES_SQL_UTINYINT, 0, "PDSrcUse" },						//P 当前使用数据源
	{ IES_SQL_UTINYINT, 0, "QDSrcNum" },						//Q 数据源个数
	{ IES_SQL_UTINYINT, 0, "QDSrcUse" },						//Q 当前使用数据源
	{ IES_SQL_DOUBLE, 0, "PDCoef" },							//PKWH 系数
	{ IES_SQL_DOUBLE, 0, "QDCoef" },							//QKWH 系数
	{ IES_SQL_DOUBLE, 0, "PJFDCoef" },							//有功积分电量系数
	{ IES_SQL_DOUBLE, 0, "QJFDCoef" },							//无功积分电量系数
	{ IES_SQL_BOOL, 0, "JiFenDL" },								//计算积分电量标志
	{ IES_SQL_BOOL, 0, "NobodyOnDuty" },						//无人值守"

	{ IES_SQL_STRING, 32, "AlarmGra" },							//图形名
	{ IES_SQL_UTINYINT, 0, "AlarmGraLayer" },					//层
	{ IES_SQL_UINT, 0, "AlarmGraX" },							//X坐标
	{ IES_SQL_UINT, 0, "AlarmGraY" },							//Y坐标
} ;
//EMS-Mend<
//李友金 2006.4.19 根据厂站表实际字段定义新的结构，实现iesdraw添加删除厂站功能
static SClmInfo aChangZhan_Col_NEW[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
	{ SQL_DATAID_TYPE, 0, "NETID" },	                        //所属电网(新增)	
	{ SQL_DATAID_TYPE, 0, "POWERCORPID" },	                //所属发电公司(新增)	
	{ SQL_DATAID_TYPE, 0, "SUBNETID" },						//所属分区(新增)	
	{ IES_SQL_UTINYINT , 0 ,"STATIONTYPE" },					//厂站类型(新增)
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi1ID" },					//电压等级1
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi2ID" },					//电压等级2
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi3ID" },					//电压等级3
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi4ID" },					//电压等级4
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi5ID" },					//电压等级5
	// DMS-MEND>
	{ IES_SQL_USMALLINT, 0, "CZAQTian" },						//厂安全天
	{ IES_SQL_UTINYINT, 0, "PDSrcNum" },						//P 数据源个数
	{ IES_SQL_UTINYINT, 0, "PDSrcUse" },						//P 当前使用数据源
	{ IES_SQL_UTINYINT, 0, "QDSrcNum" },						//Q 数据源个数
	{ IES_SQL_UTINYINT, 0, "QDSrcUse" },						//Q 当前使用数据源
	{ IES_SQL_DOUBLE, 0, "PDCoef" },							//PKWH 系数
	{ IES_SQL_DOUBLE, 0, "QDCoef" },							//QKWH 系数
	{ IES_SQL_DOUBLE, 0, "PJFDCoef" },							//有功积分电量系数
	{ IES_SQL_DOUBLE, 0, "QJFDCoef" },							//无功积分电量系数
	{ IES_SQL_BOOL, 0, "JiFenDL" },								//计算积分电量标志
	{ IES_SQL_BOOL, 0, "NobodyOnDuty" },						//无人值守"
	{ IES_SQL_BOOL, 0, "BrandFlag" },							//挂牌标志(新增)	
	
	{ IES_SQL_STRING, 32, "AlarmGra" },							//图形名
	{ IES_SQL_UTINYINT, 0, "AlarmGraLayer" },					//层
	{ IES_SQL_UINT, 0, "AlarmGraX" },							//X坐标
	{ IES_SQL_UINT, 0, "AlarmGraY" },							//Y坐标
	
	{ IES_SQL_DOUBLE, 0, "FREQUENCY" },							//频率(新增)		
	{ IES_SQL_BOOL, 0, "PASFLAG" },								//PAS标志(新增)		
	{ IES_SQL_BOOL, 0, "DTSFLAG" },								//DTS标志(新增)		
	{ IES_SQL_UTINYINT, 0, "EXSTATIONFLAG" },					//外网厂站标志(新增)		
	{ IES_SQL_UTINYINT, 0, "YCUSEDFLAG" },						//参加计算标志(新增)		
	{ IES_SQL_UTINYINT, 0, "PLOSSFLAG" },						//网损计算标志(新增)		
	{ IES_SQL_DOUBLE, 0, "PCoef" },								//有功系数(新增)		
	{ IES_SQL_DOUBLE, 0, "QCoef" },								//无功系数(新增)		
	{ IES_SQL_FLOAT, 0, "FUELSTORAGE" },						//储煤量(新增)		
	{ IES_SQL_FLOAT, 0, "WATERSTORAGE" },						//储水量(新增)		
	{ IES_SQL_BOOL, 0, "VarFlag" },								//参与AVQC控制标志(新增)		
	{ IES_SQL_UTINYINT, 0, "WorkMode" },						//AVQC方案执行模式(新增)		
	{ IES_SQL_BINARY, 40, "CosUpLmt" },							//AVQC功率因数上限(新增)
	{ IES_SQL_BINARY, 40, "CosDnLmt" },							//AVQC功率因数下限(新增)
	{ IES_SQL_USMALLINT, 0, "BaoHuID" },						//保护动作指示部件ID(新增)	
	{ IES_SQL_USMALLINT, 0, "LoadID" },							//厂站负荷对应的曲线ID(新增)	
	
	
} ;
//EMS-Mend>
//EMS-Mend<
//李友金 2006.4.19 定义分区和发电公司结构，实现iesdraw添加删除厂站功能
// 分区
static SClmInfo aFenQu_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
};
// 发电公司
static SClmInfo aFaDianGongSi_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字	
};
//EMS-Mend>

//母线
//#define dbMuxianLen 17
#define dbMuxianLen 18 //旁母识别
static SClmInfo aMuXian_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
	{ IES_SQL_STRING, 32, "ProdType" },							//产品类型
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//投运日期

	{ SQL_DATAID_TYPE, 0, "DYPTID" },							//对应PT
	{ IES_SQL_USMALLINT, 0, "PTPhase" },						//对应PT相
	{ IES_SQL_UTINYINT, 0, "SEFlag" },							//状态估计测点属性
	{ IES_SQL_FLOAT, 0, "SERCoef" },							//状态估计加权因子
	{ SQL_DATAID_TYPE, 0, "PanMuKaiGuanZuID" },				//旁母所接开关

	{ IES_SQL_UTINYINT, 0, "TJWay" },							//统计方式
	{ IES_SQL_BOOL, 0, "AvVal" },								//计算平均值标志

	//动态着色 99.8
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
	{ IES_SQL_USMALLINT, 0, "SUBTYPE"},							//旁母识别
} ;

//线路
#define dbXianluLen 54
static SClmInfo aXianLu_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ IES_SQL_STRING, 16, "BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS_MEND>
	{ SQL_DATAID_TYPE, 0, "QiChangZhanID" },					//S 侧厂站
	{ SQL_DATAID_TYPE, 0, "ZhChangZhanID" },					//E 侧厂站
	{ IES_SQL_STRING, 32, "ProdType" },							//产品类型
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//投运日期
	{ IES_SQL_FLOAT, 0, "R" },									//电阻R
	{ IES_SQL_FLOAT, 0, "X" },									//电抗X
	{ IES_SQL_FLOAT, 0, "B" },									//电钠B

	{ IES_SQL_UTINYINT, 0, "QiBJType" },						//S侧对应部件类型
	{ SQL_DATAID_TYPE, 0, "QiDY1ID" },						//S侧对应部件(P)
	{ SQL_DATAID_TYPE, 0, "QiDY2ID" },						//S侧对应部件(Q)
	{ SQL_DATAID_TYPE, 0, "QiDY3ID" },						//S侧对应部件(I)
	{ SQL_DATAID_TYPE, 0, "QiDY4ID" },						//S侧对应部件(PKWH)
	{ SQL_DATAID_TYPE, 0, "QiDY5ID" },						//S侧对应部件(QKWH)
	{ SQL_DATAID_TYPE, 0, "FQiDY4ID" },						//S侧(反向PKWH)部件
	{ SQL_DATAID_TYPE, 0, "FQiDY5ID" },						//S侧(反向QKWH)部件

	{ IES_SQL_UTINYINT, 0, "ZhBJType" },						//E 侧对应部件类型
	{ SQL_DATAID_TYPE, 0, "ZhDY1ID" },						//E侧对应部件(P)
	{ SQL_DATAID_TYPE, 0, "ZhDY2ID" },						//E侧对应部件(Q)
	{ SQL_DATAID_TYPE, 0, "ZhDY3ID" },						//E侧对应部件(I)
	{ SQL_DATAID_TYPE, 0, "ZhDY4ID" },						//E侧对应部件(PKWH)
	{ SQL_DATAID_TYPE, 0, "ZhDY5ID" },						//E侧对应部件(QKWH)
	{ SQL_DATAID_TYPE, 0, "FZhDY4ID" },						//E侧(反向PKWH)部件
	{ SQL_DATAID_TYPE, 0, "FZhDY5ID" },						//E侧(反向QKWH)部件

	{ SQL_DATAID_TYPE, 0, "QiPJHDDId" },						//S侧有功积分存放点
	{ SQL_DATAID_TYPE, 0, "QiQJHDDId" },						//S侧无功积分存放点
	{ SQL_DATAID_TYPE, 0, "FQiPJHDDId" },						//S侧反向有功积分存放点
	{ SQL_DATAID_TYPE, 0, "FQiQJHDDId" },						//S侧反向无功积分存放点
	{ SQL_DATAID_TYPE, 0, "ZhPJHDDId" },						//E侧有功积分存放点
	{ SQL_DATAID_TYPE, 0, "ZhQJHDDId" },						//E侧无功积分存放点
	{ SQL_DATAID_TYPE, 0, "FZhPJHDDId" },						//E侧反向有功积分存放点
	{ SQL_DATAID_TYPE, 0, "FZhQJHDDId" },						//E侧反向无功积分存放点

	{ IES_SQL_UTINYINT, 0, "QiPSEFlag" },						//S侧P状态估计测点属性
	{ IES_SQL_FLOAT, 0, "QiPSERCoef" },							//S侧P状态估计加权因子
	{ IES_SQL_UTINYINT, 0, "QiQSEFlag" },						//S侧Q状态估计测点属性
	{ IES_SQL_FLOAT, 0, "QiQSERCoef" },							//S侧Q状态估计加权因子
	{ IES_SQL_UTINYINT, 0, "QiISEFlag" },						//S侧I状态估计测点属性
	{ IES_SQL_FLOAT, 0, "QiISERCoef" },							//S侧I状态估计加权因子
	{ IES_SQL_UTINYINT, 0, "ZhPSEFlag" },						//E侧P状态估计测点属性
	{ IES_SQL_FLOAT, 0, "ZhPSERCoef" },							//E侧P状态估计加权因子
	{ IES_SQL_UTINYINT, 0, "ZhQSEFlag" },						//E侧Q状态估计测点属性
	{ IES_SQL_FLOAT, 0, "ZhQSERCoef" },							//E侧Q状态估计加权因子
	{ IES_SQL_UTINYINT, 0, "ZhISEFlag" },						//E侧I状态估计测点属性
	{ IES_SQL_FLOAT, 0, "ZhISERCoef" },							//E侧I状态估计加权因子

	{ IES_SQL_BOOL, 0, "QiPJHFlag" },							//S 侧P积分标志
	{ IES_SQL_BOOL, 0, "QiQJHFlag" },							//S 侧Q积分标志
	{ IES_SQL_BOOL, 0, "ZhPJHFlag" },							//E 侧P积分标志
	{ IES_SQL_BOOL, 0, "ZhQJHFlag" },							//E 侧Q积分标志

	//动态着色 99.8
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
} ;

//开关
#define dbKaiguanLen 30
static SClmInfo aKaiGuan_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, BIANHAOLEN, "BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
	{ IES_SQL_STRING, PRODTYPELEN, "ProdType" },							//产品类型

	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//投运日期

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//数据源个数
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//当前使用数据源

	{ IES_SQL_UINT, 0, "DZCount" },								//动作次数
	{ IES_SQL_UINT, 0, "DZLimit" },								//动作次数报警上限
	{ IES_SQL_UINT, 0, "YKCount" },								//遥控次数
	{ IES_SQL_UINT, 0, "YKSuccessCount" },						//遥控成功次数
	{ IES_SQL_UINT, 0, "SGDZCount" },							//事故动作次数
	{ SQL_DATAID_TYPE, 0, "CTID" },							//对应CT
	{ SQL_DATAID_TYPE, 0, "PTIDBegin" },						//开关测量量对应的首端PT标示号
	{ SQL_DATAID_TYPE, 0, "PTIDEnd" },							//开关测量量对应的末端PT标示号

	{ SQL_DATAID_TYPE, 0, "SGZID" },							//对应事故总/保护

	{ IES_SQL_BOOL, 0, "KeKong" },								//可遥控标志
	{ IES_SQL_UTINYINT, 0, "CZJiBie" },							//遥控操作级别

	{ IES_SQL_UTINYINT, 0, "YXCMode" },							//遥信连接方式
	{ IES_SQL_BOOL, 0, "SheZhiF" },								//人工设置标志
	{ IES_SQL_BOOL, 0, "YXValue0" },							//置入状态值0
	{ IES_SQL_BOOL, 0, "YXValue1" },							//置入状态值1

	{ IES_SQL_BOOL, 0, "YXChRec" },								//变位报警
	{ IES_SQL_BOOL, 0, "YXChAlarm" },							//变位声音
	{ IES_SQL_BOOL, 0, "YXChPrint" },							//变位打印
	{ IES_SQL_BOOL, 0, "YXChScr" },								//变位推图
	{ IES_SQL_BOOL, 0, "SGPDFlag" },							//事故判断标志

	//动态着色 99.8
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
} ;

//刀闸
#define dbDaozhaLen 28
static SClmInfo aDaoZha_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
	{ IES_SQL_STRING, 32, "ProdType" },							//产品类型
	{ IES_SQL_UTINYINT, 0, "LeiXingID" },						//类型号
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//投运日期

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//数据源个数
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//当前使用数据源

	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//对应部件类型
	{ SQL_DATAID_TYPE, 0, "DYBJID" },							//对应部件
	{ IES_SQL_UINT, 0, "YKCount" },								//遥控次数
	{ IES_SQL_UINT, 0, "YKSuccessCount" },						//遥控成功次数
	{ IES_SQL_BOOL, 0, "KeKong" },								//可遥控标志
	{ IES_SQL_UTINYINT, 0, "CZJiBie" },							//遥控操作级别
	{ IES_SQL_BOOL, 0, "YXValue0" },							//遥信状态值0
	{ IES_SQL_BOOL, 0, "YXValue1" },							//遥信状态值1
	{ IES_SQL_BOOL, 0, "SheZhiF" },								//人工设置标志
	{ IES_SQL_BOOL, 0, "YXChRec" },								//变位报警
	{ IES_SQL_BOOL, 0, "YXChAlarm" },							//变位声音
	{ IES_SQL_BOOL, 0, "YXChPrint" },							//变位打印
	{ IES_SQL_BOOL, 0, "YXChScr" },								//变位推图

	{ SQL_DATAID_TYPE, 0, "DYPLKaiGuanID" },					//对应旁路开关
	//动态着色 99.8
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
} ;

//保护
#define dbBaohuLen 36
static SClmInfo aBaoHu_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字

	{ IES_SQL_UTINYINT, 0, "BuJianLeiXingID" },					//所属部件类型
	{ SQL_DATAID_TYPE, 0, "BuJianID" },						//所属部件

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//数据源个数
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//当前使用数据源

	{ IES_SQL_USMALLINT, 0, "BaoHuLeiXingID" },					//保护类型

	{ IES_SQL_USMALLINT, 0, "DZ1TypeID" },						//定值1类型
	{ IES_SQL_USMALLINT, 0, "DZ2TypeID" },						//定值2类型
	{ IES_SQL_USMALLINT, 0, "DZ3TypeID" },						//定值3类型
	{ IES_SQL_USMALLINT, 0, "DZ4TypeID" },						//定值4类型
	{ IES_SQL_USMALLINT, 0, "DZ5TypeID" },						//定值5类型
	{ IES_SQL_USMALLINT, 0, "DZ6TypeID" },						//定值6类型
	{ IES_SQL_USMALLINT, 0, "DZ7TypeID" },						//定值7类型
	{ IES_SQL_USMALLINT, 0, "DZ8TypeID" },						//定值8类型

	{ IES_SQL_FLOAT, 0, "BHDingZhi1" },							//定值1
	{ IES_SQL_FLOAT, 0, "BHDingZhi2" },							//定值2
	{ IES_SQL_FLOAT, 0, "BHDingZhi3" },							//定值3
	{ IES_SQL_FLOAT, 0, "BHDingZhi4" },							//定值4
	{ IES_SQL_FLOAT, 0, "BHDingZhi5" },							//定值5
	{ IES_SQL_FLOAT, 0, "BHDingZhi6" },							//定值6
	{ IES_SQL_FLOAT, 0, "BHDingZhi7" },							//定值7
	{ IES_SQL_FLOAT, 0, "BHDingZhi8" },							//定值8

	{ IES_SQL_BOOL, 0, "YXChRec" },								//动作报警
	{ IES_SQL_BOOL, 0, "YXChAlarm" },							//动作声音
	{ IES_SQL_BOOL, 0, "YXChPrint" },							//动作打印
	{ IES_SQL_BOOL, 0, "YXChScr" },								//动作推图

	{ IES_SQL_BOOL, 0, "KeKong" },								//可远方启停标志
	{ IES_SQL_BOOL, 0, "DZhSheZhi" },							//定值人工设置标志
	{ IES_SQL_USMALLINT, 0, "SGZID" },							//对应事故总/保护
	{ IES_SQL_BOOL, 0, "SheZhiF" },								//人工置入标志
	{ IES_SQL_BOOL, 0, "STValue" },								//状态值
	{ IES_SQL_BOOL, 0, "KGSGFlag" },							//对应开关判事故标志
	//wugc<2010.8.23集控功能数据库及结构扩展
	{IES_SQL_UTINYINT,0,"AlarmLevel"},							//告警级别
	{IES_SQL_BOOL,		0,	"GZFlag"},							//光字标志
	{IES_SQL_BOOL,		0,	"RealYX"},							//硬接点
	{IES_SQL_USMALLINT,	0,	"zzlx"},							//装置类型
} ;

//变压器
//EMS-Mend dingjide 2009.4.22
//修改原因:短路电流中变压器中性点接地刀闸的问题
//EMS-Mend<
#define dbBianyaqiLen 72		//70
//EMS-Mend>
static SClmInfo aBianYaQi_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	{ IES_SQL_STRING, 16, "BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
	{ IES_SQL_STRING, 32, "ProdType" },							//产品类型
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//投运日期
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将SQL_DATAID_TYPE类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "GaoYaCeDengJiID" },					//Ｇ测电压等级	
	{ IES_SQL_UTINYINT, 0, "ZhongYaCeDengJiID" },				//Ｚ测电压等级	
	{ IES_SQL_UTINYINT, 0, "DiYaCeDengJiID" },					//Ｄ测电压等级
	// DMS-MEND>
	{ IES_SQL_FLOAT, 0, "SN"},									//额定容量(MVA)		//dtt add	
	{ IES_SQL_FLOAT, 0, "PN"},									//有功额定容量(MW)
	
	{ IES_SQL_FLOAT, 0, "RH" },									//Ｇ测电阻
	{ IES_SQL_FLOAT, 0, "RM" },									//Ｚ测电阻
	{ IES_SQL_FLOAT, 0, "RL" },									//Ｄ测电阻
	{ IES_SQL_FLOAT, 0, "XH" },									//Ｇ测电抗
	{ IES_SQL_FLOAT, 0, "XM" },									//Ｚ测电抗
	{ IES_SQL_FLOAT, 0, "XL" },									//Ｄ测电抗
	{ IES_SQL_FLOAT, 0, "KHM"},									//高/中变比		//dtt add
	{ IES_SQL_FLOAT, 0, "KML"},									//中/低变比
	{ IES_SQL_FLOAT, 0, "KHL"},									//高/低变比

	{ IES_SQL_UTINYINT, 0, "GaoBJ1Type" },						//Ｇ测连接部件1 类型
	{ SQL_DATAID_TYPE, 0, "GaoBJ1ID" },						//Ｇ测连接部件1
	{ IES_SQL_UTINYINT, 0, "GaoBJ2Type" },						//Ｇ测连接部件2 类型
	{ SQL_DATAID_TYPE, 0, "GaoBJ2ID" },						//Ｇ测连接部件2
	{ IES_SQL_UTINYINT, 0, "ZhongBJ1Type" },					//Ｚ测连接部件1 类型
	{ SQL_DATAID_TYPE, 0, "ZhongBJ1ID" },						//Ｚ测连接部件1
	{ IES_SQL_UTINYINT, 0, "ZhongBJ2Type" },					//Ｚ测连接部件2 类型
	{ SQL_DATAID_TYPE, 0, "ZhongBJ2ID" },						//Ｚ测连接部件2
	{ IES_SQL_UTINYINT, 0, "DiBJ1Type" },						//Ｄ测连接部件1 类型
	{ SQL_DATAID_TYPE, 0, "DiBJ1ID" },						//Ｄ测连接部件1
	{ IES_SQL_UTINYINT, 0, "DiBJ2Type" },						//Ｄ测连接部件2 类型
	{ SQL_DATAID_TYPE, 0, "DiBJ2ID" },						//Ｄ测连接部件2

	{ IES_SQL_UTINYINT, 0, "GPSEFlag" },						//G侧P估计属性
	{ IES_SQL_FLOAT, 0, "GPSERCoef" },							//G侧P估计加权因子
	{ IES_SQL_UTINYINT, 0, "GQSEFlag" },						//G侧Q估计属性
	{ IES_SQL_FLOAT, 0, "GQSERCoef" },							//G侧Q估计加权因子
	{ IES_SQL_UTINYINT, 0, "GISEFlag" },						//G侧I估计属性
	{ IES_SQL_FLOAT, 0, "GISERCoef" },							//G侧I估计加权因子
	{ IES_SQL_UTINYINT, 0, "ZPSEFlag" },						//Z侧P估计属性
	{ IES_SQL_FLOAT, 0, "ZPSERCoef" },							//Z侧P估计加权因子
	{ IES_SQL_UTINYINT, 0, "ZQSEFlag" },						//Z侧Q估计属性
	{ IES_SQL_FLOAT, 0, "ZQSERCoef" },							//Z侧Q估计加权因子
	{ IES_SQL_UTINYINT, 0, "ZISEFlag" },						//Z侧I估计属性
	{ IES_SQL_FLOAT, 0, "ZISERCoef" },							//Z侧I估计加权因子
	{ IES_SQL_UTINYINT, 0, "DPSEFlag" },						//D侧P估计属性
	{ IES_SQL_FLOAT, 0, "DPSERCoef" },							//D侧P估计加权因子
	{ IES_SQL_UTINYINT, 0, "DQSEFlag" },						//D侧Q估计属性
	{ IES_SQL_FLOAT, 0, "DQSERCoef" },							//D侧Q估计加权因子
	{ IES_SQL_UTINYINT, 0, "DISEFlag" },						//D侧I估计属性
	{ IES_SQL_FLOAT, 0, "DISERCoef" },							//D侧I估计加权因子

	{ IES_SQL_UTINYINT, 0, "FJTWeiZhiShu" },					//分接头位置个数
	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//数据源个数
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//当前使用数据源
	{ IES_SQL_UTINYINT, 0, "DWCoef" },							//档位转换系数
	{ IES_SQL_BOOL, 0, "DWMFlag" },								//人工置入档位标志
	{ IES_SQL_UINT, 0, "DWMVal" },								//人工置入档位值

	{ IES_SQL_BOOL, 0, "KeKong" },								//调压(升降)可控标志
	{ IES_SQL_BOOL, 0, "CZJiBie" },								//调压(升降)操作级别
	{ IES_SQL_UTINYINT, 0, "DYMode" },							//调压方式

	{ IES_SQL_UTINYINT, 0, "TDSrcNum" },						//温度数据源个数
	{ IES_SQL_UTINYINT, 0, "TDSrcUse" },						//温度当前使用数据源
	{ IES_SQL_BOOL, 0, "TMFlag" },								//人工置入温度标志
	{ IES_SQL_FLOAT, 0, "TMVal" },								//人工置入温度值

	{ IES_SQL_USMALLINT, 0, "SJTimeLimit" },					//升降次数上限
	{ IES_SQL_USMALLINT, 0, "SJTimes" },						//总升降次数
	{ IES_SQL_USMALLINT, 0, "DSJTimeLimit" },					//日升降次数上限
	{ IES_SQL_USMALLINT, 0, "DSJTimes" },						//日升降次数

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//元件域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
	//EMS-Mend dingjide 2009.4.22
	//修改原因:短路电流中变压器中性点接地刀闸的问题
	//EMS-Mend<
	{ SQL_DATAID_TYPE, 0, "HEDAOZHAID" },	
	{ SQL_DATAID_TYPE, 0, "MEDAOZHAID" },	
	//EMS-Mend>
};

//发电机
#define dbFadianjiLen 21
static SClmInfo aFaDianJi_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站	
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
 	{ IES_SQL_STRING, 32, "ProdType" },							//产品类型	
	{ IES_SQL_FLOAT, 0, "JiZuRongLiang" },						//发电机组容量(MW)

	{ IES_SQL_UTINYINT, 0, "BJType1ID" },						//连接部件1 类型
	{ SQL_DATAID_TYPE, 0, "BJ1ID" },							//连接部件1
	{ IES_SQL_UTINYINT, 0, "BJType2ID" },						//连接部件2 类型
	{ SQL_DATAID_TYPE, 0, "BJ2ID" },							//连接部件2

	{ IES_SQL_UTINYINT, 0, "PSEFlag" },							//P 估计属性
	{ IES_SQL_FLOAT, 0, "PSERCoef" },							//P 估计加权因子
	{ IES_SQL_UTINYINT, 0, "QSEFlag" },							//Q 估计属性
	{ IES_SQL_FLOAT, 0, "QSERCoef" },							//Q 估计加权因子
	{ IES_SQL_UTINYINT, 0, "ISEFlag" },							//I 估计属性
	{ IES_SQL_FLOAT, 0, "ISERCoef" },							//I 估计加权因子

	{ IES_SQL_BOOL, 0, "TingYunShiJian" },						//统计日停运时间标志

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//元件域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
};

//CT
#define dbCtLen 69
static SClmInfo aCT_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级
	// DMS_MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
	{ IES_SQL_STRING, 32, "ProdType" },							//产品类型
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//投运日期
	{ IES_SQL_STRING, 16, "TranRate" },							//变比
	{ IES_SQL_USMALLINT, 0, "PTAddID" },						//对应PT
	{ IES_SQL_UTINYINT, 0, "PTPhase" },							//对应PT相

	{ IES_SQL_UTINYINT, 0, "PDSrcNum" },						//P 数据源个数
	{ IES_SQL_UTINYINT, 0, "PDSrcUse" },						//P 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "QDSrcNum" },						//Q 数据源个数
	{ IES_SQL_UTINYINT, 0, "QDSrcUse" },						//Q 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "IaDSrcNum" },						//Ia 数据源个数
	{ IES_SQL_UTINYINT, 0, "IaDSrcUse" },						//Ia 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "IbDSrcNum" },						//Ib数据源个数
	{ IES_SQL_UTINYINT, 0, "IbDSrcUse" },						//Ib当前使用数据源

	{ IES_SQL_UTINYINT, 0, "IcDSrcNum" },						//Ic 数据源个数
	{ IES_SQL_UTINYINT, 0, "IcDSrcUse" },						//Ic 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "IoDSrcNum" },						//Io 数据源个数
	{ IES_SQL_UTINYINT, 0, "IoDSrcUse" },						//Io 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "IhDSrcNum" },						//Ih 数据源个数
	{ IES_SQL_UTINYINT, 0, "IhDSrcUse" },						//Ih 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "SDSrcNum" },						//S 数据源个数
	{ IES_SQL_UTINYINT, 0, "SDSrcUse" },						//S 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "CosDSrcNum" },						//Cos 数据源个数
	{ IES_SQL_UTINYINT, 0, "CosDSrcUse" },						//Cos 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "FDSrcNum" },						//F 数据源个数
	{ IES_SQL_UTINYINT, 0, "FDSrcUse" },						//F 当前使用数据源

	{ IES_SQL_DOUBLE, 0, "ZPDDCoef" },							//正向PKWH窗口系数
	{ IES_SQL_DOUBLE, 0, "ZQDDCoef" },							//正向QKWH窗口系数
	{ IES_SQL_DOUBLE, 0, "FPDDCoef" },							//反向PKWH窗口系数
	{ IES_SQL_DOUBLE, 0, "FQDDCoef" },							//反向QKWH窗口系数
	{ IES_SQL_DOUBLE, 0, "PDCoef" },							//正向积分PKWH系数
	{ IES_SQL_DOUBLE, 0, "QDCoef" },							//正向积分QKWH系数
	{ IES_SQL_DOUBLE, 0, "FPDCoef" },							//反向积分PKWH系数
	{ IES_SQL_DOUBLE, 0, "FQDCoef" },							//反向积分QKWH系数
	{ IES_SQL_UTINYINT, 0, "DDMode" },							//电度模类型
	{ IES_SQL_UTINYINT, 0, "DDClear" },							//电度清零方式

	{ IES_SQL_BOOL, 0, "PCFlag" },								//公式计算 P
	{ IES_SQL_BOOL, 0, "QCFlag" },								//公式计算 Q
	{ IES_SQL_BOOL, 0, "IaCFlag" },								//公式计算 I

	{ IES_SQL_BOOL, 0, "PMFlag" },								//P 置入标志
	{ IES_SQL_FLOAT, 0, "PMVal" },								//P 置入值

	{ IES_SQL_BOOL, 0, "QMFlag" },								//Q 置入标志
	{ IES_SQL_FLOAT, 0, "QMVal" },								//Q 置入值

	{ IES_SQL_BOOL, 0, "IaMFlag" },								//Ia 置入标志
	{ IES_SQL_FLOAT, 0, "IaMVal" },								//Ia 人工值

	{ IES_SQL_BOOL, 0, "IbMFlag" },								//Ib 置入标志
	{ IES_SQL_FLOAT, 0, "IbMVal" },								//Ib 置入值

	{ IES_SQL_BOOL, 0, "IcMFlag" },								//Ic 置入标志
	{ IES_SQL_FLOAT, 0, "IcMVal" },								//Ic 置入值

	{ IES_SQL_BOOL, 0, "IoMFlag" },								//Io 置入标志
	{ IES_SQL_FLOAT, 0, "IoMVal" },								//Io 置入值

	{ IES_SQL_BOOL, 0, "IhMFlag" },								//Ih 置入标志
	{ IES_SQL_FLOAT, 0, "IhMVal" },								//Ih 置入值

	{ IES_SQL_BOOL, 0, "SMFlag" },								//S 置入标志
	{ IES_SQL_FLOAT, 0, "SMVal" },								//S 置入值

	{ IES_SQL_BOOL, 0, "CosMFlag" },							//Cos 置入标志
	{ IES_SQL_FLOAT, 0, "CosMVal" },							//Cos 置入值

	{ IES_SQL_BOOL, 0, "FMFlag" },								//F 置入标志
	{ IES_SQL_FLOAT, 0, "FMVal" },								//F 置入值

	{ IES_SQL_BOOL, 0, "PRmtW" },								//正向PKWH窗口值
	{ IES_SQL_BOOL, 0, "PFRmtW" },								//反向PKWH窗口值
	{ IES_SQL_BOOL, 0, "QRmtW" },								//正向QKWH窗口值
	{ IES_SQL_BOOL, 0, "QFRmtW" },								//反向QKWH窗口值

	{ IES_SQL_BOOL, 0, "PJFFlag" },								//P 积分
	{ IES_SQL_BOOL, 0, "QJFFlag" },								//Q 积分
};

//PT
#define dbPtLen 40
static SClmInfo aPT_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//名字
	{ IES_SQL_STRING, 32, "ProdType" },							//产品类型
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//投运日期
	{ IES_SQL_STRING, 16, "TranRate" },							//变比

	{ IES_SQL_UTINYINT, 0, "UaDSrcNum" },						//Ua 数据源个数
	{ IES_SQL_UTINYINT, 0, "UaDSrcUse" },						//Ua 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "UbDSrcNum" },						//Ub 数据源个数
	{ IES_SQL_UTINYINT, 0, "UbDSrcUse" },						//Ub 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "UcDSrcNum" },						//Uc 数据源个数
	{ IES_SQL_UTINYINT, 0, "UcDSrcUse" },						//Uc 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "UabxDSrcNum" },						//Uabx 数据源个数
	{ IES_SQL_UTINYINT, 0, "UabxDSrcUse" },						//Uabx 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "UbcxDSrcNum" },						//Ubcx 数据源个数
	{ IES_SQL_UTINYINT, 0, "UbcxDSrcUse" },						//Ubcx 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "UcaxDSrcNum" },						//Ucax 数据源个数
	{ IES_SQL_UTINYINT, 0, "UcaxDSrcUse" },						//Ucax 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "UoDSrcNum" },						//Uo 数据源个数
	{ IES_SQL_UTINYINT, 0, "UoDSrcUse" },						//Uo 当前使用数据源

	{ IES_SQL_UTINYINT, 0, "UangDSrcNum" },						//相角数据源个数
	{ IES_SQL_UTINYINT, 0, "UangDSrcUse" },						//相角当前使用数据源

	{ IES_SQL_BOOL, 0, "UaMFlag" },								//Ua 置入标志
	{ IES_SQL_FLOAT, 0, "UaMVal" },								//Ua 置入值

	{ IES_SQL_BOOL, 0, "UbMFlag" },								//Ub 置入标志
	{ IES_SQL_FLOAT, 0, "UbMVal" },								//Ub 置入值

	{ IES_SQL_BOOL, 0, "UcMFlag" },								//Uc 置入标志
	{ IES_SQL_FLOAT, 0, "UcMVal" },								//Uc 置入值

	{ IES_SQL_BOOL, 0, "UabxMFlag" },							//Uabx 置入标志
	{ IES_SQL_FLOAT, 0, "UabxMVal" },							//Uabx 置入值

	{ IES_SQL_BOOL, 0, "UbcxMFlag" },							//Ubcx 置入标志
	{ IES_SQL_FLOAT, 0, "UbcxMVal" },							//Ubcx 置入值

	{ IES_SQL_BOOL, 0, "UcaxMFlag" },							//Ucax 置入标志
	{ IES_SQL_FLOAT, 0, "UcaxMVal" },							//Ucax 置入值

	{ IES_SQL_BOOL, 0, "UoMFlag" },								//Uo 置入标志	
	{ IES_SQL_FLOAT, 0, "UoMVal" },								//Uo 置入值

	{ IES_SQL_BOOL, 0, "UangMFlag" },							//相角置入标志	
	{ IES_SQL_FLOAT, 0, "UangMVal" },							//相角置入值
};

//负荷
#define dbFuheLen 30
static SClmInfo aFuHe_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0,"DianYaDengJiID"},					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//名字
	{ IES_SQL_UTINYINT, 0, "FHJiBie" },							//负荷级别

	{ IES_SQL_UTINYINT, 0, "LJBJType" },						//对应部件类型
	{ SQL_DATAID_TYPE,  0, "LJDY1ID" },						//对应部件(P)
	{ SQL_DATAID_TYPE,  0, "LJDY2ID" },						//对应部件(Q)
	{ SQL_DATAID_TYPE,  0, "LJDY3ID" },						//对应部件(I)
	{ SQL_DATAID_TYPE,  0, "LJDY4ID" },						//对应部件(PKWH)
	{ SQL_DATAID_TYPE,  0, "LJDY5ID" },						//对应部件(QKWH)
	{ SQL_DATAID_TYPE,  0, "FLJDY4ID" },						//对应部件(反向PKWH)
	{ SQL_DATAID_TYPE,  0, "FLJDY5ID" },						//对应部件(反向QKWH)

	{ IES_SQL_BOOL, 0, "PJHFlag" },								//P 积分标志
	{ IES_SQL_BOOL, 0, "QJHFlag" },								//Q 积分标志
	{ SQL_DATAID_TYPE,  0, "PJHDDId" },						//有功积分存放点
	{ SQL_DATAID_TYPE,  0, "QJHDDId" },						//无功积分存放点
	{ SQL_DATAID_TYPE,  0, "FPJHDDId" },						//反向有功积分存放点
	{ SQL_DATAID_TYPE,  0, "FQJHDDId" },						//反向无功积分存放点

	{ IES_SQL_UTINYINT, 0, "PSEFlag" },							//P 估计属性
	{ IES_SQL_FLOAT, 0, "PSERCoef" },							//P 估计加权因子
	{ IES_SQL_UTINYINT, 0, "QSEFlag" },							//Q 估计属性
	{ IES_SQL_FLOAT, 0, "QSERCoef" },							//Q 估计加权因子
	{ IES_SQL_UTINYINT, 0, "ISEFlag" },							//I 估计属性
	{ IES_SQL_FLOAT, 0, "ISERCoef" },							//I 估计加权因子

	{ IES_SQL_FLOAT, 0, "TopoCoef" },							//负荷拓扑系数
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//元件域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
};

//注入
#define dbZhuruLen 22
static SClmInfo aZhuRu_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//名字

	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//对应部件类型
	{ SQL_DATAID_TYPE, 0, "PId" },							//对应部件P
	{ SQL_DATAID_TYPE, 0, "QId" },							//对应部件Q
	{ SQL_DATAID_TYPE, 0, "IId" },							//对应部件I
		
	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//连接部件类型
	{ SQL_DATAID_TYPE,  0, "LJBJ1ID" },						//连接部件
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//连接部件参数

	{ IES_SQL_UTINYINT, 0, "PSEFlag" },							//P 估计属性
	{ IES_SQL_FLOAT, 0, "PSERCoef" },							//P 估计加权因子
	{ IES_SQL_UTINYINT, 0, "QSEFlag" },							//Q 估计属性
	{ IES_SQL_FLOAT, 0, "QSERCoef" },							//Q 估计加权因子
	{ IES_SQL_UTINYINT, 0, "ISEFlag" },							//I 估计属性
	{ IES_SQL_FLOAT, 0, "ISERCoef" },							//I 估计加权因子

	{ IES_SQL_FLOAT, 0, "TopoCoef" },							//注入拓扑系数	
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//元件域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
};

//调相机
#define dbTiaoxiangLen 21
static SClmInfo aTiaoXiang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//名字
	{ IES_SQL_STRING, 32 ,"ProdType" },							//产品类型
	{ IES_SQL_TIMESTAMP,  0, "UsedTime" },						//投运日期
	{ IES_SQL_USMALLINT,  0, "TouQieKGID" },					//投切开关
	{ IES_SQL_FLOAT, 0, "R" },									//等效电阻
	{ IES_SQL_FLOAT, 0, "X" },									//等效电抗
	{ IES_SQL_FLOAT, 0, "B" },									//等效电纳

	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//连接部件1 类型
	{ SQL_DATAID_TYPE,  0, "LJBJ1ID" },						//连接部件1
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//连接部件1 参数
	{ IES_SQL_UTINYINT, 0, "LJBJType2" },						//连接部件2 类型
	{ SQL_DATAID_TYPE,  0, "LJBJ2ID" },						//连接部件2
	{ IES_SQL_USMALLINT, 0, "LJBJ2CS" },							//连接部件2 参数

	{ IES_SQL_BOOL, 0, "TouQieTimeF" },							//统计投切时间标志
	
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//元件域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
};

//静止补偿器
#define dbJingzhibuchangLen 21
static SClmInfo aJingZhiBuChang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//名字
	{ IES_SQL_STRING, 32 ,"ProdType" },							//产品类型
	{ IES_SQL_TIMESTAMP,  0, "UsedTime" },						//投运日期
	{ IES_SQL_USMALLINT,  0, "TouQieKGID" },					//投切开关
	{ IES_SQL_FLOAT, 0, "R" },									//等效电阻
	{ IES_SQL_FLOAT, 0, "X" },									//等效电抗
	{ IES_SQL_FLOAT, 0, "B" },									//等效电纳

	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//连接部件1 类型
	{ SQL_DATAID_TYPE,  0, "LJBJ1ID" },						//连接部件1
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//连接部件1 参数
	{ IES_SQL_UTINYINT, 0, "LJBJType2" },						//连接部件2 类型
	{ SQL_DATAID_TYPE,  0, "LJBJ2ID" },						//连接部件2
	{ IES_SQL_USMALLINT, 0, "LJBJ2CS" },							//连接部件2 参数

	{ IES_SQL_BOOL, 0, "TouQieTimeF" },							//统计投切时间标志

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//元件域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
};

//并联电容
#define dbDianrongLen 22
static SClmInfo aBingLianDianRong_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//名字
	{ IES_SQL_STRING, 32 ,"ProdType" },							//产品类型
	{ IES_SQL_TIMESTAMP,  0, "UsedTime" },						//投运日期
	{ IES_SQL_USMALLINT,  0, "TouQieKGID" },					//投切开关
	{ IES_SQL_FLOAT, 0, "C" },									//电容组容量(uf)
	{ IES_SQL_FLOAT, 0, "R" },									//等效电阻
	{ IES_SQL_FLOAT, 0, "X" },									//等效电抗
	{ IES_SQL_FLOAT, 0, "B" },									//等效电纳

	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//连接部件1 类型
	{ SQL_DATAID_TYPE,  0, "LJBJ1ID" },						//连接部件1
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//连接部件1 参数
	{ IES_SQL_UTINYINT, 0, "LJBJType2" },						//连接部件2 类型
	{ SQL_DATAID_TYPE,  0, "LJBJ2ID" },						//连接部件2
	{ IES_SQL_USMALLINT, 0, "LJBJ2CS" },							//连接部件2 参数

	{ IES_SQL_BOOL, 0, "TouQieTimeF" },							//统计投切时间标志

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//元件域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
};

//串连电抗
#define dbDiankangLen 27
static SClmInfo aChuanLianDianKang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//电压等级	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//名字
	{ IES_SQL_STRING, 32 ,"ProdType" },							//产品类型
	{ IES_SQL_TIMESTAMP,  0, "UsedTime" },						//投运日期
	{ SQL_DATAID_TYPE,  0, "DYDianRongID" },					//对应电容器组

	{ IES_SQL_FLOAT, 0, "X1" },									//电抗值
	{ IES_SQL_FLOAT, 0, "R1" },									//电阻值
	{ IES_SQL_FLOAT, 0, "M" },									//三端互感值
	{ IES_SQL_FLOAT, 0, "X2" },									//三端电抗值
	{ IES_SQL_FLOAT, 0, "R2" },									//三端电阻值

	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//连接部件1类型
	{ SQL_DATAID_TYPE, 0, "LJBJ1ID" },						//连接部件1
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//连接部件1 参数
	{ IES_SQL_UTINYINT, 0, "LJBJType2" },						//连接部件2类型
	{ SQL_DATAID_TYPE, 0, "LJBJ2ID" },						//连接部件2
	{ IES_SQL_USMALLINT, 0, "LJBJ2CS" },							//连接部件2参数
	{ IES_SQL_UTINYINT, 0, "LJBJType3" },						//连接部件3类型
	{ SQL_DATAID_TYPE, 0, "LJBJ3ID" },						//连接部件3
	{ IES_SQL_USMALLINT, 0, "LJBJ3CS" },							//连接部件3参数

	{ IES_SQL_UTINYINT, 0, "LJType" },							//连接类型
	{ IES_SQL_BOOL, 0, "TouQieTimeF" },							//统计投切时间标志

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//元件域类型
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//站内域序号
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//域内元件序号
};

//虚拟单精模拟量
#define dbYaoceLen 11
static SClmInfo aXuNiDMNLiang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	{ IES_SQL_STRING, 16 ,"BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//名字
	{ IES_SQL_UTINYINT, 0, "XNType" },							//虚拟类型
	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//对应部件类型(保留)
	{ SQL_DATAID_TYPE, 0, "DYBJID" },							//对应部件(保留)

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//数据源个数
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//当前使用数据源

	{ IES_SQL_BOOL, 0, "MFlag" },								//置入标志
	{ IES_SQL_FLOAT, 0, "MVal" },								//置入值
};

//虚拟双精模拟量
#define dbDianduLen 12
static SClmInfo aXuNiSMNLiang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	{ IES_SQL_STRING, 16 ,"BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//名字
	{ IES_SQL_UTINYINT, 0, "XNType" },							//虚拟类型
	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//对应部件类型(保留)
	{ SQL_DATAID_TYPE, 0, "DYBJID" },							//对应部件(保留)

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//数据源个数
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//当前使用数据源

	{ IES_SQL_DOUBLE, 0, "Coef" },								//系数

	{ IES_SQL_BOOL, 0, "RemoteF" },								//遥传标志
	{ IES_SQL_BOOL, 0, "JFFlag" },								//积分标志
};

//虚拟状态量
#define dbYaoxinLen 19
static SClmInfo aXuNiZHTLiang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//厂站
	{ IES_SQL_STRING, 16 ,"BianHao" },							//编号
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//名字
	{ IES_SQL_UTINYINT, 0, "XNType" },							//虚拟类型
	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//对应部件类型(保留)
	{ SQL_DATAID_TYPE, 0, "DYBJID" },							//对应部件(保留)

	{ IES_SQL_UINT , 0, "DZCount" },							//状态变化累计次数

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//数据源个数		//0-4
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//当前使用数据源	//0-4

	{ IES_SQL_BOOL, 0, "SheZhiF" },								//置入标志
	{ IES_SQL_BOOL, 0, "STValue" },								//状态值
	{ IES_SQL_BOOL, 0, "TJTouQie" },							//统计日投切时间
	{ IES_SQL_BOOL, 0, "KeKong" },								//可控
	{ IES_SQL_UTINYINT, 0, "CZJiBie" },							//控制级别
	{ IES_SQL_BOOL, 0, "ChRec" },								//变位记录
	{ IES_SQL_BOOL, 0, "ChAlarm" },								//变位报警
	{ IES_SQL_BOOL, 0, "ChPrint" },								//变位打印
	{ IES_SQL_BOOL, 0, "ChScr" },								//变位推图
};

// EMS-Mend<yuecaijuan 2010.11.17 调配一体化开发I期
// 修改原因：馈线信息
#define dbFeederLen 6
static SClmInfo aFeeder_Col[] =
{
	{SQL_DATAID_TYPE,	0,	"ID"},				
	{IES_SQL_STRING,	16,	"BianHao"},			
	{IES_SQL_STRING,	NAMELEN,	"MingZi"},				
	{IES_SQL_STRING,	16,	"NO"},		
	{SQL_DATAID_TYPE,	0,	"ChangZhanID"},
	{IES_SQL_UTINYINT,	0,	"DianYaDengJiID"},
};
#define dbKuiXianDuanLen 25
static SClmInfo aKuiXianDuan_Col[] =
{
	{SQL_DATAID_TYPE,	0,	"ID"},				
	{IES_SQL_STRING,	16,	"BianHao"},			
	{IES_SQL_STRING,	NAMELEN,	"MingZi"},				
	{IES_SQL_STRING,	16,	"NO"},				
	{IES_SQL_STRING,	NAMELEN,	"ALIAS"},			
	{SQL_DATAID_TYPE,	0,	"ChangZhanID"},		
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{IES_SQL_UTINYINT,	0,	"DianYaDengJiID"},	
	// DMS-MEND
	{IES_SQL_UTINYINT,	0,	"BJType"},			
	{SQL_DATAID_TYPE,	0,	"BJID"},				
	{SQL_DATAID_TYPE,	0,	"FEEDERID"},			
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将SQL_DATAID_TYPE类型改为IES_SQL_UINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{IES_SQL_UINT,		0,	"SNODEID"},			
	{IES_SQL_STRING,	16,	"SNODE"},			
	{IES_SQL_UINT,		0,	"ENODEID"},			
	{IES_SQL_STRING,	16,	"ENODE"},
	// DMS-MEND>
	{IES_SQL_DOUBLE,	0,	"CABLELEN"},			
	{IES_SQL_UTINYINT,	0,	"DFEEDERSECTIONTYPE"},
	{IES_SQL_STRING,	NAMELEN,	"TBAKEP1"},			
	{IES_SQL_STRING,	NAMELEN,	"TBAKEP2"},			
	{IES_SQL_UTINYINT,	0,	"RUNSTATE"},	
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将SQL_DATAID_TYPE类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{IES_SQL_UTINYINT,	0,	"TOPOLEVEL"},
	// DMS-MEND>
	{IES_SQL_STRING,	48,	"DESCRIPTION"},		
	{IES_SQL_USMALLINT,	0,	"FieldType"},		
	{IES_SQL_USMALLINT,	0,	"StaFieldID"},		
	{IES_SQL_USMALLINT,	0,	"ComponentID"},		
	{IES_SQL_STRING,	32,	"EXID"},				
};

#define dbPBBianYaQiLen 84
static SClmInfo aPBBianYaQi_Col[] =
{
	{SQL_DATAID_TYPE,	0,	"ID"},				
	{IES_SQL_STRING,	16,	"BianHao"},			
	{IES_SQL_STRING,	NAMELEN,	"MingZi"},				
	{IES_SQL_STRING,	16,	"NO"},				
	{SQL_DATAID_TYPE,	0,	"ChangZhanID"},		
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{IES_SQL_UTINYINT,	0,	"GaoDianYaDengJiID"},
	{IES_SQL_UTINYINT,	0,	"DiDianYaDengJiID"},	
	// DMS-MEND>
	{IES_SQL_UTINYINT,	0,	"GaoBJType"},		
	{SQL_DATAID_TYPE,	0,	"GaoBJID"},			
	{IES_SQL_UTINYINT,	0,	"DiBJType"},			
	{SQL_DATAID_TYPE,	0,	"DiBJID"},			
	{SQL_DATAID_TYPE,	0,	"FEEDERID"},			
	{SQL_DATAID_TYPE,	0,	"BCUSTOMERID"},		
	{SQL_DATAID_TYPE,	0,	"NODEID"},			
	{IES_SQL_STRING ,	16,	"NODE"},				
	{IES_SQL_FLOAT,		0,	"CAPACITY"},			
	{IES_SQL_BOOL,		0,	"RUNSTATE"},			
	{IES_SQL_BOOL,		0,	"PON"},				
	{IES_SQL_BOOL,		0,	"PAON"},				
	{IES_SQL_BOOL,		0,	"PBON"},				
	{IES_SQL_BOOL,		0,	"PCON"},				
	{IES_SQL_BOOL,		0,	"QON"},				
	{IES_SQL_BOOL,		0,	"QAON"},				
	{IES_SQL_BOOL,		0,	"QBON"},				
	{IES_SQL_BOOL,		0,	"QCON"},				
	{IES_SQL_BOOL,		0,	"IAON"},				
	{IES_SQL_BOOL,		0,	"IBON"},				
	{IES_SQL_BOOL,		0,	"ICON"},				
	{IES_SQL_BOOL,		0,	"I0ON"},				
	{IES_SQL_BOOL,		0,	"PFON"},				
	{IES_SQL_BOOL,		0,	"PFAON"},			
	{IES_SQL_BOOL,		0,	"PFBON"},			
	{IES_SQL_BOOL,		0,	"PFCON"},			
	{IES_SQL_BOOL,		0,	"PDLON"},			
	{IES_SQL_BOOL,		0,	"PDLAON"},			
	{IES_SQL_BOOL,		0,	"PDLBON"},			
	{IES_SQL_BOOL,		0,	"PDLCON"},			
	{IES_SQL_BOOL,		0,	"QDLON"},			
	{IES_SQL_BOOL,		0,	"QDLAON"},			
	{IES_SQL_BOOL,		0,	"QDLBON"},			
	{IES_SQL_BOOL,		0,	"QDLCON"},			
	{IES_SQL_BOOL,		0,	"REVPDLON"},			
	{IES_SQL_BOOL,		0,	"REVPDLAON"},		
	{IES_SQL_BOOL,		0,	"REVPDLBON"},		
	{IES_SQL_BOOL,		0,	"REVPDLCON"},		
	{IES_SQL_BOOL,		0,	"REVQDLON"},			
	{IES_SQL_BOOL,		0,	"REVQDLAON"},		
	{IES_SQL_BOOL,		0,	"REVQDLBON"},		
	{IES_SQL_BOOL,		0,	"REVQDLCON"},		
	{IES_SQL_BOOL,		0,	"VA1ON"},			
	{IES_SQL_BOOL,		0,	"VB1ON"},			
	{IES_SQL_BOOL,		0,	"VC1ON"},			
	{IES_SQL_BOOL,		0,	"VAB1ON"},			
	{IES_SQL_BOOL,		0,	"VBC1ON"},			
	{IES_SQL_BOOL,		0,	"VCA1ON"},			
	{IES_SQL_BOOL ,		0,	"V01ON"},			
	{IES_SQL_UTINYINT,	0,	"APSEFLAG"},			
	{IES_SQL_FLOAT,		0,	"APSERCOEF"},		
	{IES_SQL_UTINYINT,	0,	"AQSEFLAG"},			
	{IES_SQL_FLOAT,		0,	"AQSERCOEF"},		
	{IES_SQL_UTINYINT,	0,	"AISEFLAG"},			
	{IES_SQL_FLOAT,		0,	"AISERCOEF"},		
	{IES_SQL_UTINYINT,	0,	"BPSEFLAG"},			
	{IES_SQL_FLOAT,		0,	"BPSERCOEF"},		
	{IES_SQL_UTINYINT,	0,	"BQSEFLAG"},			
	{IES_SQL_FLOAT,		0,	"BQSERCOEF"},		
	{IES_SQL_UTINYINT,	0,	"BISEFLAG"},			
	{IES_SQL_FLOAT,		0,	"BISERCOEF"},		
	{IES_SQL_UTINYINT,	0,	"CPSEFLAG"},			
	{IES_SQL_FLOAT,		0,	"CPSERCOEF"},		
	{IES_SQL_UTINYINT,	0,	"CQSEFLAG"},			
	{IES_SQL_FLOAT,		0,	"CQSERCOEF"},		
	{IES_SQL_UTINYINT,	0,	"CISEFLAG"},			
	{IES_SQL_FLOAT,		0,	"CISERCOEF"},		
	{IES_SQL_UTINYINT,	0,	"HADJUSTMODE"},		
	{IES_SQL_BOOL,		0,	"HCANBEYK"},			
	{IES_SQL_BOOL,		0,	"INSTATIONFLAG"},	
	{IES_SQL_USMALLINT,	0,	"HYKTIMESLMT"},		
	{IES_SQL_USMALLINT,	0,	"HYKTIMES"},			
	{IES_SQL_STRING,	200,"DESCRIPTION"},		
	{IES_SQL_USMALLINT,	0,	"FieldType"},		
	{IES_SQL_USMALLINT,	0,	"StaFieldID"},		
	{IES_SQL_USMALLINT,	0,	"ComponentID"},		
	{IES_SQL_STRING,	32,	"EXID"},
};
//===========================================================================
//电网部件表
static STblInfo aDWBuJian_Table[] =
{
	{ sizeof(aDianWang_Col)/sizeof(SClmInfo), "dianwang", MingZi_DianWangID, 1, aDianWang_Col },
	{ sizeof(aDianYaDengJi_Col)/sizeof(SClmInfo), "dianyadengji", "电压等级", 1, aDianYaDengJi_Col },
	{ sizeof(aChangZhan_Col)/sizeof(SClmInfo), "changzhan", MingZi_ChangZhanID, 1, aChangZhan_Col },
	{ sizeof(aMuXian_Col)/sizeof(SClmInfo), "muxian", "母线", 1, aMuXian_Col },
	{ sizeof(aXianLu_Col)/sizeof(SClmInfo), "xianlu", "线路", 1, aXianLu_Col },
	{ sizeof(aKaiGuan_Col)/sizeof(SClmInfo), "kaiguan", "开关", 1, aKaiGuan_Col },
	{ sizeof(aDaoZha_Col)/sizeof(SClmInfo), "daozha", "刀闸", 1, aDaoZha_Col },
	{ sizeof(aBaoHu_Col)/sizeof(SClmInfo), "baohu", "保护", 1, aBaoHu_Col },
	{ sizeof(aBianYaQi_Col)/sizeof(SClmInfo), "bianyaqi", "变压器", 1, aBianYaQi_Col },
	{ sizeof(aFaDianJi_Col)/sizeof(SClmInfo), "fadianji", "发电机", 1, aFaDianJi_Col },
	{ sizeof(aCT_Col)/sizeof(SClmInfo), "ct", "CT", 1, aCT_Col },
	{ sizeof(aPT_Col)/sizeof(SClmInfo), "pt", "PT", 1, aPT_Col },
	{ sizeof(aFuHe_Col)/sizeof(SClmInfo), "fuhe", "负荷", 1, aFuHe_Col },
	{ sizeof(aZhuRu_Col)/sizeof(SClmInfo), "zhuru", "注入", 1, aZhuRu_Col },
	{ sizeof(aTiaoXiang_Col)/sizeof(SClmInfo), "tiaoxiang", "调相机", 1, aTiaoXiang_Col },
	{ sizeof(aJingZhiBuChang_Col)/sizeof(SClmInfo), "jingzhibuchang", "静止补偿器", 1, aJingZhiBuChang_Col },
	{ sizeof(aBingLianDianRong_Col)/sizeof(SClmInfo), "bingliandianrong", "并联补偿电容", 1, aBingLianDianRong_Col },
	{ sizeof(aChuanLianDianKang_Col)/sizeof(SClmInfo), "chuanliandiankang", "串联电抗", 1, aChuanLianDianKang_Col },
	{ sizeof(aXuNiDMNLiang_Col)/sizeof(SClmInfo), "xunidmnliang", "虚拟单精模拟量", 1, aXuNiDMNLiang_Col },
	{ sizeof(aXuNiSMNLiang_Col)/sizeof(SClmInfo), "xunismnliang", "虚拟双精模拟量", 1, aXuNiSMNLiang_Col },
	{ sizeof(aXuNiZHTLiang_Col)/sizeof(SClmInfo), "xunizhtliang", "虚拟状态量", 1, aXuNiZHTLiang_Col },
	{ sizeof(aFeeder_Col)/sizeof(SClmInfo),  "feeder", "馈线",1,aFeeder_Col},// EMS-Mend<yuecaijuan 2010.11.17 调配一体化开发I期
	{ sizeof(aPBBianYaQi_Col)/sizeof(SClmInfo),	  "transformer",	"配变变压器",1,aPBBianYaQi_Col},
	{ sizeof(aKuiXianDuan_Col)/sizeof(SClmInfo),  "feedersection", "馈线段",1,aKuiXianDuan_Col},
};

//EMS-Mend<
//李友金 2006.4.19 实现iesdraw添加删除厂站功能
//厂站表描述结构
static STblInfo  aChangZhan_Table = { sizeof(aChangZhan_Col_NEW)/sizeof(SClmInfo), "changzhan", MingZi_ChangZhanID, 1, aChangZhan_Col_NEW };
//分区表描述结构
static STblInfo  aFenQu_Table = { sizeof(aFenQu_Col)/sizeof(SClmInfo), "SubNet_EMS", "分区", 1, aFenQu_Col };
//发电公司表描述结构
static STblInfo  aFaDianGongSi_Table = { sizeof(aFaDianGongSi_Col)/sizeof(SClmInfo), "powercorp", "发电公司", 1, aFaDianGongSi_Col };
//EMS-Mend>

//================================================================
//微拓扑描述表  99.8
//----------------------------------------------------------------
//Topo
static SClmInfo aTopo_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },
	{ IES_SQL_STRING, 32, "FieldName" },

	{ IES_SQL_UTINYINT, 0, "BranchNum" },
	{ IES_SQL_UTINYINT, 0, "CBNum" },
	{ IES_SQL_UTINYINT, 0, "DisNum" },
	{ IES_SQL_UTINYINT, 0, "GrdDisNum" },
	{ IES_SQL_UTINYINT, 0, "PortNum" },
	{ IES_SQL_UTINYINT, 0, "InPortNum" },
	{ IES_SQL_UTINYINT, 0, "ExPortNum" },
	{ IES_SQL_UTINYINT, 0, "InNodeNum" },
	{ IES_SQL_UTINYINT, 0, "LineNum" },
	{ IES_SQL_UTINYINT, 0, "BusNum" },
	{ IES_SQL_UTINYINT, 0, "ThreadNum" },
	{ IES_SQL_UINT, 0, "ElcNum" },
};

//微拓扑部件描述表  99.8
static SClmInfo aTopoBuJian_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID", },
	{ IES_SQL_UTINYINT, 0, "RecID" },

	{ IES_SQL_STRING, 32 , "ElementType" },
	{ IES_SQL_STRING, 32 , "ElementName" },
	{ IES_SQL_UTINYINT, 0, "ElementID" },

	{ IES_SQL_UTINYINT, 0, "Node1ID" },
	{ IES_SQL_UTINYINT, 0, "Node2ID" },
	{ IES_SQL_UTINYINT, 0, "Node3ID" },
	{ IES_SQL_STRING,  8, "DisNo" },
};

//微拓扑端口描述表 99.8
static SClmInfo aTopoPort_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },
	{ IES_SQL_UTINYINT, 0, "RecID" },

	{ IES_SQL_STRING,  16 , "PortTag" },
	{ IES_SQL_UTINYINT, 0, "PortNodeID" },
	{ IES_SQL_BOOL, 0, "InPortFlag" },
	{ IES_SQL_USMALLINT, 0, "CorBusID" },
};

//微拓扑连线描述表 99.8
static SClmInfo aTopoLine_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },
	{ IES_SQL_UTINYINT, 0, "RecID" },

	{ IES_SQL_STRING,  16, "LineName" },
	{ IES_SQL_UTINYINT, 0, "LineID" },
	{ IES_SQL_BOOL, 0, "BusFlag" },
	{ IES_SQL_UTINYINT, 0, "PortNode" },
};

//微拓扑带电查询描述表 99.8
static SClmInfo aTopoElectronicQuery_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },
	{ IES_SQL_UINT, 0, "RecID" },

//	{ IES_SQL_BINARY, 8, "AllInputFlag" },		//dtt locked for debug
	{ IES_SQL_BINARY, 10, "AllInputFlag" },	
	{ IES_SQL_BINARY, 16, "AllLineFlag" },	
};

//微拓扑预处理存放描述表 99.12.6
static SClmInfo aTopoPreDeal_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },

	{ IES_SQL_BINARY, 193, "NodeData" },
	{ IES_SQL_BINARY, 33, "BranchData" },
};

//电网微拓扑描述表  99.8
static SClmInfo aDWTopo_Col[] = 
{
	{ SQL_DATAID_TYPE,	0, "ChangZhanID" },
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },	
	// DMS-MEND>
	{ IES_SQL_USMALLINT, 0, "FieldID" },
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },

	{ IES_SQL_STRING, NAMELEN ,"Name" },
	{ IES_SQL_BOOL, 0, "InUseFlag" },
};

//电网微拓扑部件描述表  99.8
static SClmInfo aDWTopoBuJian_Col[] = 
{
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },	
	// DMS-MEND>
	{ IES_SQL_USMALLINT, 0, "FieldID" },
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },

	{ IES_SQL_UTINYINT, 0, "RecID" },
	{ IES_SQL_UTINYINT, 0, "ComponentNo" },
	{ IES_SQL_UTINYINT, 0, "ComponentType" },
	{ SQL_DATAID_TYPE, 0, "ComponentID" },
};

//电网微拓扑端口描述表  99.8
static SClmInfo aDWTopoPort_Col[] = 
{
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// 修改原因：将IES_SQL_USMALLINT类型改为IES_SQL_UTINYINT类型，原因是
	// 在置拓扑信息时会提示ORA-01438: 值大于此列指定的允许精度。精度有问题
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },	
	// DMS-MEND>
	{ IES_SQL_USMALLINT, 0, "FieldID" },
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },

	{ IES_SQL_UTINYINT, 0, "RecID" },
	{ IES_SQL_STRING, 16, "PortName" },
	{ IES_SQL_BOOL, 0, "InPortFlag" },
	{ IES_SQL_UINT, 0, "PnodeID" },
	{ IES_SQL_UTINYINT, 0, "NodeID" },
};

static STblInfo aDWTopo_Table[] =
{
	{ sizeof(aTopo_Col)/sizeof(SClmInfo), "Topo", "拓扑", 1, aTopo_Col },
	{ sizeof(aTopoBuJian_Col)/sizeof(SClmInfo), "TopoBuJian", "拓扑部件", 1, aTopoBuJian_Col },
	{ sizeof(aTopoPort_Col)/sizeof(SClmInfo), "TopoPort", "拓扑端口", 1, aTopoPort_Col },
	{ sizeof(aTopoLine_Col)/sizeof(SClmInfo), "TopoLine", "拓扑连线", 1, aTopoLine_Col },
	{ sizeof(aTopoElectronicQuery_Col)/sizeof(SClmInfo), "TopoEquery", "带电状态查询", 1, aTopoElectronicQuery_Col },
	{ sizeof(aTopoPreDeal_Col)/sizeof(SClmInfo), "TopoPredeal", "预处理存放", 1, aTopoPreDeal_Col },
	{ sizeof(aDWTopo_Col)/sizeof(SClmInfo), "DWTopo", iES_Conn(MingZi_DianWangID,微拓扑), 1, aDWTopo_Col },
	{ sizeof(aDWTopoBuJian_Col)/sizeof(SClmInfo), "DWTopoBuJian", iES_Conn(MingZi_DianWangID,微拓扑部件), 1, aDWTopoBuJian_Col },
	{ sizeof(aDWTopoPort_Col)/sizeof(SClmInfo), "DWTopoPort", iES_Conn(MingZi_DianWangID,微拓扑端口), 1, aDWTopoPort_Col },
};