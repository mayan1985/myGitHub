//====================================================================
// �ļ���: msdb_table_info.h
//
// �ļ�����:
// ------------------------------------------------------------------
// �������ṹ���鶨��
// ------------------------------------------------------------------
// ʱ��: 2002.9
// ���: ����
// ------------------------------------------------------------------
// �޸�˵��(�밴��ʽ˵��)...
//====================================================================

//=================================================================
// ����������
//-----------------------------------------------------------------
//����
;
static SClmInfo aDianWang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ IES_SQL_STRING, NAMELEN, "MingZi" },						//����
	{ IES_SQL_USMALLINT, 0, "WAQTian" },						//����ȫ��
	{ IES_SQL_USMALLINT, 0, "SAQTian" },						//����ȫ��
	{ IES_SQL_UTINYINT, 0, "PDSrcNum" },						//P ����Դ����
	{ IES_SQL_UTINYINT, 0, "PDSrcUse" },						//P ��ǰʹ������Դ
	{ IES_SQL_UTINYINT, 0, "QDSrcNum" },						//Q ����Դ����
	{ IES_SQL_UTINYINT, 0, "QDSrcUse" },						//Q ��ǰʹ������Դ
	{ IES_SQL_DOUBLE, 0, "PDDCoef" },							//PKWH ϵ��
	{ IES_SQL_DOUBLE, 0, "QDDCoef" },							//QKWH ϵ��
	{ IES_SQL_DOUBLE, 0, "PDJFCoef" },							//�й����ֵ���ϵ��
	{ IES_SQL_DOUBLE, 0, "QDJFCoef" },							//�޹����ֵ���ϵ��
	{ IES_SQL_BOOL, 0, "JiFenDL" },								//������ֵ�����־
	{ IES_SQL_BOOL, 0, "PinLuYueXianRec" },						//Ƶ��Խ�޼�¼
	{ IES_SQL_BOOL, 0, "PinLuYueXianPrt" },						//Ƶ��Խ�޴�ӡ
	{ IES_SQL_BOOL, 0, "PinLuYueXianSG" },						//Ƶ��Խ�ޱ���
};

//��ѹ�ȼ�
static SClmInfo aDianYaDengJi_Col[] =
{
	{ IES_SQL_USMALLINT, 0, "ID" },								//ID
	{ IES_SQL_STRING, NAMELEN, "MingZi" },						//����
	{ IES_SQL_FLOAT, 0, "DianYaZhi" },							//�ֵ
} ;

//��վ
static SClmInfo aChangZhan_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi1ID" },					//��ѹ�ȼ�1
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi2ID" },					//��ѹ�ȼ�2
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi3ID" },					//��ѹ�ȼ�3
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi4ID" },					//��ѹ�ȼ�4
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi5ID" },					//��ѹ�ȼ�5
	// DMS-MEND>
	{ IES_SQL_USMALLINT, 0, "CZAQTian" },						//����ȫ��
	{ IES_SQL_UTINYINT, 0, "PDSrcNum" },						//P ����Դ����
	{ IES_SQL_UTINYINT, 0, "PDSrcUse" },						//P ��ǰʹ������Դ
	{ IES_SQL_UTINYINT, 0, "QDSrcNum" },						//Q ����Դ����
	{ IES_SQL_UTINYINT, 0, "QDSrcUse" },						//Q ��ǰʹ������Դ
	{ IES_SQL_DOUBLE, 0, "PDCoef" },							//PKWH ϵ��
	{ IES_SQL_DOUBLE, 0, "QDCoef" },							//QKWH ϵ��
	{ IES_SQL_DOUBLE, 0, "PJFDCoef" },							//�й����ֵ���ϵ��
	{ IES_SQL_DOUBLE, 0, "QJFDCoef" },							//�޹����ֵ���ϵ��
	{ IES_SQL_BOOL, 0, "JiFenDL" },								//������ֵ�����־
	{ IES_SQL_BOOL, 0, "NobodyOnDuty" },						//����ֵ��"

	{ IES_SQL_STRING, 32, "AlarmGra" },							//ͼ����
	{ IES_SQL_UTINYINT, 0, "AlarmGraLayer" },					//��
	{ IES_SQL_UINT, 0, "AlarmGraX" },							//X����
	{ IES_SQL_UINT, 0, "AlarmGraY" },							//Y����
} ;
//EMS-Mend<
//���ѽ� 2006.4.19 ���ݳ�վ��ʵ���ֶζ����µĽṹ��ʵ��iesdraw���ɾ����վ����
static SClmInfo aChangZhan_Col_NEW[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
	{ SQL_DATAID_TYPE, 0, "NETID" },	                        //��������(����)	
	{ SQL_DATAID_TYPE, 0, "POWERCORPID" },	                //�������繫˾(����)	
	{ SQL_DATAID_TYPE, 0, "SUBNETID" },						//��������(����)	
	{ IES_SQL_UTINYINT , 0 ,"STATIONTYPE" },					//��վ����(����)
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi1ID" },					//��ѹ�ȼ�1
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi2ID" },					//��ѹ�ȼ�2
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi3ID" },					//��ѹ�ȼ�3
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi4ID" },					//��ѹ�ȼ�4
	{ IES_SQL_UTINYINT, 0, "DianYaDengJi5ID" },					//��ѹ�ȼ�5
	// DMS-MEND>
	{ IES_SQL_USMALLINT, 0, "CZAQTian" },						//����ȫ��
	{ IES_SQL_UTINYINT, 0, "PDSrcNum" },						//P ����Դ����
	{ IES_SQL_UTINYINT, 0, "PDSrcUse" },						//P ��ǰʹ������Դ
	{ IES_SQL_UTINYINT, 0, "QDSrcNum" },						//Q ����Դ����
	{ IES_SQL_UTINYINT, 0, "QDSrcUse" },						//Q ��ǰʹ������Դ
	{ IES_SQL_DOUBLE, 0, "PDCoef" },							//PKWH ϵ��
	{ IES_SQL_DOUBLE, 0, "QDCoef" },							//QKWH ϵ��
	{ IES_SQL_DOUBLE, 0, "PJFDCoef" },							//�й����ֵ���ϵ��
	{ IES_SQL_DOUBLE, 0, "QJFDCoef" },							//�޹����ֵ���ϵ��
	{ IES_SQL_BOOL, 0, "JiFenDL" },								//������ֵ�����־
	{ IES_SQL_BOOL, 0, "NobodyOnDuty" },						//����ֵ��"
	{ IES_SQL_BOOL, 0, "BrandFlag" },							//���Ʊ�־(����)	
	
	{ IES_SQL_STRING, 32, "AlarmGra" },							//ͼ����
	{ IES_SQL_UTINYINT, 0, "AlarmGraLayer" },					//��
	{ IES_SQL_UINT, 0, "AlarmGraX" },							//X����
	{ IES_SQL_UINT, 0, "AlarmGraY" },							//Y����
	
	{ IES_SQL_DOUBLE, 0, "FREQUENCY" },							//Ƶ��(����)		
	{ IES_SQL_BOOL, 0, "PASFLAG" },								//PAS��־(����)		
	{ IES_SQL_BOOL, 0, "DTSFLAG" },								//DTS��־(����)		
	{ IES_SQL_UTINYINT, 0, "EXSTATIONFLAG" },					//������վ��־(����)		
	{ IES_SQL_UTINYINT, 0, "YCUSEDFLAG" },						//�μӼ����־(����)		
	{ IES_SQL_UTINYINT, 0, "PLOSSFLAG" },						//��������־(����)		
	{ IES_SQL_DOUBLE, 0, "PCoef" },								//�й�ϵ��(����)		
	{ IES_SQL_DOUBLE, 0, "QCoef" },								//�޹�ϵ��(����)		
	{ IES_SQL_FLOAT, 0, "FUELSTORAGE" },						//��ú��(����)		
	{ IES_SQL_FLOAT, 0, "WATERSTORAGE" },						//��ˮ��(����)		
	{ IES_SQL_BOOL, 0, "VarFlag" },								//����AVQC���Ʊ�־(����)		
	{ IES_SQL_UTINYINT, 0, "WorkMode" },						//AVQC����ִ��ģʽ(����)		
	{ IES_SQL_BINARY, 40, "CosUpLmt" },							//AVQC������������(����)
	{ IES_SQL_BINARY, 40, "CosDnLmt" },							//AVQC������������(����)
	{ IES_SQL_USMALLINT, 0, "BaoHuID" },						//��������ָʾ����ID(����)	
	{ IES_SQL_USMALLINT, 0, "LoadID" },							//��վ���ɶ�Ӧ������ID(����)	
	
	
} ;
//EMS-Mend>
//EMS-Mend<
//���ѽ� 2006.4.19 ��������ͷ��繫˾�ṹ��ʵ��iesdraw���ɾ����վ����
// ����
static SClmInfo aFenQu_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
};
// ���繫˾
static SClmInfo aFaDianGongSi_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����	
};
//EMS-Mend>

//ĸ��
//#define dbMuxianLen 17
#define dbMuxianLen 18 //��ĸʶ��
static SClmInfo aMuXian_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
	{ IES_SQL_STRING, 32, "ProdType" },							//��Ʒ����
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//Ͷ������

	{ SQL_DATAID_TYPE, 0, "DYPTID" },							//��ӦPT
	{ IES_SQL_USMALLINT, 0, "PTPhase" },						//��ӦPT��
	{ IES_SQL_UTINYINT, 0, "SEFlag" },							//״̬���Ʋ������
	{ IES_SQL_FLOAT, 0, "SERCoef" },							//״̬���Ƽ�Ȩ����
	{ SQL_DATAID_TYPE, 0, "PanMuKaiGuanZuID" },				//��ĸ���ӿ���

	{ IES_SQL_UTINYINT, 0, "TJWay" },							//ͳ�Ʒ�ʽ
	{ IES_SQL_BOOL, 0, "AvVal" },								//����ƽ��ֵ��־

	//��̬��ɫ 99.8
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
	{ IES_SQL_USMALLINT, 0, "SUBTYPE"},							//��ĸʶ��
} ;

//��·
#define dbXianluLen 54
static SClmInfo aXianLu_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ IES_SQL_STRING, 16, "BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS_MEND>
	{ SQL_DATAID_TYPE, 0, "QiChangZhanID" },					//S �೧վ
	{ SQL_DATAID_TYPE, 0, "ZhChangZhanID" },					//E �೧վ
	{ IES_SQL_STRING, 32, "ProdType" },							//��Ʒ����
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//Ͷ������
	{ IES_SQL_FLOAT, 0, "R" },									//����R
	{ IES_SQL_FLOAT, 0, "X" },									//�翹X
	{ IES_SQL_FLOAT, 0, "B" },									//����B

	{ IES_SQL_UTINYINT, 0, "QiBJType" },						//S���Ӧ��������
	{ SQL_DATAID_TYPE, 0, "QiDY1ID" },						//S���Ӧ����(P)
	{ SQL_DATAID_TYPE, 0, "QiDY2ID" },						//S���Ӧ����(Q)
	{ SQL_DATAID_TYPE, 0, "QiDY3ID" },						//S���Ӧ����(I)
	{ SQL_DATAID_TYPE, 0, "QiDY4ID" },						//S���Ӧ����(PKWH)
	{ SQL_DATAID_TYPE, 0, "QiDY5ID" },						//S���Ӧ����(QKWH)
	{ SQL_DATAID_TYPE, 0, "FQiDY4ID" },						//S��(����PKWH)����
	{ SQL_DATAID_TYPE, 0, "FQiDY5ID" },						//S��(����QKWH)����

	{ IES_SQL_UTINYINT, 0, "ZhBJType" },						//E ���Ӧ��������
	{ SQL_DATAID_TYPE, 0, "ZhDY1ID" },						//E���Ӧ����(P)
	{ SQL_DATAID_TYPE, 0, "ZhDY2ID" },						//E���Ӧ����(Q)
	{ SQL_DATAID_TYPE, 0, "ZhDY3ID" },						//E���Ӧ����(I)
	{ SQL_DATAID_TYPE, 0, "ZhDY4ID" },						//E���Ӧ����(PKWH)
	{ SQL_DATAID_TYPE, 0, "ZhDY5ID" },						//E���Ӧ����(QKWH)
	{ SQL_DATAID_TYPE, 0, "FZhDY4ID" },						//E��(����PKWH)����
	{ SQL_DATAID_TYPE, 0, "FZhDY5ID" },						//E��(����QKWH)����

	{ SQL_DATAID_TYPE, 0, "QiPJHDDId" },						//S���й����ִ�ŵ�
	{ SQL_DATAID_TYPE, 0, "QiQJHDDId" },						//S���޹����ִ�ŵ�
	{ SQL_DATAID_TYPE, 0, "FQiPJHDDId" },						//S�෴���й����ִ�ŵ�
	{ SQL_DATAID_TYPE, 0, "FQiQJHDDId" },						//S�෴���޹����ִ�ŵ�
	{ SQL_DATAID_TYPE, 0, "ZhPJHDDId" },						//E���й����ִ�ŵ�
	{ SQL_DATAID_TYPE, 0, "ZhQJHDDId" },						//E���޹����ִ�ŵ�
	{ SQL_DATAID_TYPE, 0, "FZhPJHDDId" },						//E�෴���й����ִ�ŵ�
	{ SQL_DATAID_TYPE, 0, "FZhQJHDDId" },						//E�෴���޹����ִ�ŵ�

	{ IES_SQL_UTINYINT, 0, "QiPSEFlag" },						//S��P״̬���Ʋ������
	{ IES_SQL_FLOAT, 0, "QiPSERCoef" },							//S��P״̬���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "QiQSEFlag" },						//S��Q״̬���Ʋ������
	{ IES_SQL_FLOAT, 0, "QiQSERCoef" },							//S��Q״̬���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "QiISEFlag" },						//S��I״̬���Ʋ������
	{ IES_SQL_FLOAT, 0, "QiISERCoef" },							//S��I״̬���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "ZhPSEFlag" },						//E��P״̬���Ʋ������
	{ IES_SQL_FLOAT, 0, "ZhPSERCoef" },							//E��P״̬���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "ZhQSEFlag" },						//E��Q״̬���Ʋ������
	{ IES_SQL_FLOAT, 0, "ZhQSERCoef" },							//E��Q״̬���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "ZhISEFlag" },						//E��I״̬���Ʋ������
	{ IES_SQL_FLOAT, 0, "ZhISERCoef" },							//E��I״̬���Ƽ�Ȩ����

	{ IES_SQL_BOOL, 0, "QiPJHFlag" },							//S ��P���ֱ�־
	{ IES_SQL_BOOL, 0, "QiQJHFlag" },							//S ��Q���ֱ�־
	{ IES_SQL_BOOL, 0, "ZhPJHFlag" },							//E ��P���ֱ�־
	{ IES_SQL_BOOL, 0, "ZhQJHFlag" },							//E ��Q���ֱ�־

	//��̬��ɫ 99.8
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
} ;

//����
#define dbKaiguanLen 30
static SClmInfo aKaiGuan_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, BIANHAOLEN, "BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
	{ IES_SQL_STRING, PRODTYPELEN, "ProdType" },							//��Ʒ����

	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//Ͷ������

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//����Դ����
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//��ǰʹ������Դ

	{ IES_SQL_UINT, 0, "DZCount" },								//��������
	{ IES_SQL_UINT, 0, "DZLimit" },								//����������������
	{ IES_SQL_UINT, 0, "YKCount" },								//ң�ش���
	{ IES_SQL_UINT, 0, "YKSuccessCount" },						//ң�سɹ�����
	{ IES_SQL_UINT, 0, "SGDZCount" },							//�¹ʶ�������
	{ SQL_DATAID_TYPE, 0, "CTID" },							//��ӦCT
	{ SQL_DATAID_TYPE, 0, "PTIDBegin" },						//���ز�������Ӧ���׶�PT��ʾ��
	{ SQL_DATAID_TYPE, 0, "PTIDEnd" },							//���ز�������Ӧ��ĩ��PT��ʾ��

	{ SQL_DATAID_TYPE, 0, "SGZID" },							//��Ӧ�¹���/����

	{ IES_SQL_BOOL, 0, "KeKong" },								//��ң�ر�־
	{ IES_SQL_UTINYINT, 0, "CZJiBie" },							//ң�ز�������

	{ IES_SQL_UTINYINT, 0, "YXCMode" },							//ң�����ӷ�ʽ
	{ IES_SQL_BOOL, 0, "SheZhiF" },								//�˹����ñ�־
	{ IES_SQL_BOOL, 0, "YXValue0" },							//����״ֵ̬0
	{ IES_SQL_BOOL, 0, "YXValue1" },							//����״ֵ̬1

	{ IES_SQL_BOOL, 0, "YXChRec" },								//��λ����
	{ IES_SQL_BOOL, 0, "YXChAlarm" },							//��λ����
	{ IES_SQL_BOOL, 0, "YXChPrint" },							//��λ��ӡ
	{ IES_SQL_BOOL, 0, "YXChScr" },								//��λ��ͼ
	{ IES_SQL_BOOL, 0, "SGPDFlag" },							//�¹��жϱ�־

	//��̬��ɫ 99.8
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
} ;

//��բ
#define dbDaozhaLen 28
static SClmInfo aDaoZha_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
	{ IES_SQL_STRING, 32, "ProdType" },							//��Ʒ����
	{ IES_SQL_UTINYINT, 0, "LeiXingID" },						//���ͺ�
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//Ͷ������

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//����Դ����
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//��Ӧ��������
	{ SQL_DATAID_TYPE, 0, "DYBJID" },							//��Ӧ����
	{ IES_SQL_UINT, 0, "YKCount" },								//ң�ش���
	{ IES_SQL_UINT, 0, "YKSuccessCount" },						//ң�سɹ�����
	{ IES_SQL_BOOL, 0, "KeKong" },								//��ң�ر�־
	{ IES_SQL_UTINYINT, 0, "CZJiBie" },							//ң�ز�������
	{ IES_SQL_BOOL, 0, "YXValue0" },							//ң��״ֵ̬0
	{ IES_SQL_BOOL, 0, "YXValue1" },							//ң��״ֵ̬1
	{ IES_SQL_BOOL, 0, "SheZhiF" },								//�˹����ñ�־
	{ IES_SQL_BOOL, 0, "YXChRec" },								//��λ����
	{ IES_SQL_BOOL, 0, "YXChAlarm" },							//��λ����
	{ IES_SQL_BOOL, 0, "YXChPrint" },							//��λ��ӡ
	{ IES_SQL_BOOL, 0, "YXChScr" },								//��λ��ͼ

	{ SQL_DATAID_TYPE, 0, "DYPLKaiGuanID" },					//��Ӧ��·����
	//��̬��ɫ 99.8
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
} ;

//����
#define dbBaohuLen 36
static SClmInfo aBaoHu_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����

	{ IES_SQL_UTINYINT, 0, "BuJianLeiXingID" },					//������������
	{ SQL_DATAID_TYPE, 0, "BuJianID" },						//��������

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//����Դ����
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//��ǰʹ������Դ

	{ IES_SQL_USMALLINT, 0, "BaoHuLeiXingID" },					//��������

	{ IES_SQL_USMALLINT, 0, "DZ1TypeID" },						//��ֵ1����
	{ IES_SQL_USMALLINT, 0, "DZ2TypeID" },						//��ֵ2����
	{ IES_SQL_USMALLINT, 0, "DZ3TypeID" },						//��ֵ3����
	{ IES_SQL_USMALLINT, 0, "DZ4TypeID" },						//��ֵ4����
	{ IES_SQL_USMALLINT, 0, "DZ5TypeID" },						//��ֵ5����
	{ IES_SQL_USMALLINT, 0, "DZ6TypeID" },						//��ֵ6����
	{ IES_SQL_USMALLINT, 0, "DZ7TypeID" },						//��ֵ7����
	{ IES_SQL_USMALLINT, 0, "DZ8TypeID" },						//��ֵ8����

	{ IES_SQL_FLOAT, 0, "BHDingZhi1" },							//��ֵ1
	{ IES_SQL_FLOAT, 0, "BHDingZhi2" },							//��ֵ2
	{ IES_SQL_FLOAT, 0, "BHDingZhi3" },							//��ֵ3
	{ IES_SQL_FLOAT, 0, "BHDingZhi4" },							//��ֵ4
	{ IES_SQL_FLOAT, 0, "BHDingZhi5" },							//��ֵ5
	{ IES_SQL_FLOAT, 0, "BHDingZhi6" },							//��ֵ6
	{ IES_SQL_FLOAT, 0, "BHDingZhi7" },							//��ֵ7
	{ IES_SQL_FLOAT, 0, "BHDingZhi8" },							//��ֵ8

	{ IES_SQL_BOOL, 0, "YXChRec" },								//��������
	{ IES_SQL_BOOL, 0, "YXChAlarm" },							//��������
	{ IES_SQL_BOOL, 0, "YXChPrint" },							//������ӡ
	{ IES_SQL_BOOL, 0, "YXChScr" },								//������ͼ

	{ IES_SQL_BOOL, 0, "KeKong" },								//��Զ����ͣ��־
	{ IES_SQL_BOOL, 0, "DZhSheZhi" },							//��ֵ�˹����ñ�־
	{ IES_SQL_USMALLINT, 0, "SGZID" },							//��Ӧ�¹���/����
	{ IES_SQL_BOOL, 0, "SheZhiF" },								//�˹������־
	{ IES_SQL_BOOL, 0, "STValue" },								//״ֵ̬
	{ IES_SQL_BOOL, 0, "KGSGFlag" },							//��Ӧ�������¹ʱ�־
	//wugc<2010.8.23���ع������ݿ⼰�ṹ��չ
	{IES_SQL_UTINYINT,0,"AlarmLevel"},							//�澯����
	{IES_SQL_BOOL,		0,	"GZFlag"},							//���ֱ�־
	{IES_SQL_BOOL,		0,	"RealYX"},							//Ӳ�ӵ�
	{IES_SQL_USMALLINT,	0,	"zzlx"},							//װ������
} ;

//��ѹ��
//EMS-Mend dingjide 2009.4.22
//�޸�ԭ��:��·�����б�ѹ�����Ե�ӵص�բ������
//EMS-Mend<
#define dbBianyaqiLen 72		//70
//EMS-Mend>
static SClmInfo aBianYaQi_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	{ IES_SQL_STRING, 16, "BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
	{ IES_SQL_STRING, 32, "ProdType" },							//��Ʒ����
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//Ͷ������
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�SQL_DATAID_TYPE���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "GaoYaCeDengJiID" },					//�ǲ��ѹ�ȼ�	
	{ IES_SQL_UTINYINT, 0, "ZhongYaCeDengJiID" },				//�ڲ��ѹ�ȼ�	
	{ IES_SQL_UTINYINT, 0, "DiYaCeDengJiID" },					//�Ĳ��ѹ�ȼ�
	// DMS-MEND>
	{ IES_SQL_FLOAT, 0, "SN"},									//�����(MVA)		//dtt add	
	{ IES_SQL_FLOAT, 0, "PN"},									//�й������(MW)
	
	{ IES_SQL_FLOAT, 0, "RH" },									//�ǲ����
	{ IES_SQL_FLOAT, 0, "RM" },									//�ڲ����
	{ IES_SQL_FLOAT, 0, "RL" },									//�Ĳ����
	{ IES_SQL_FLOAT, 0, "XH" },									//�ǲ�翹
	{ IES_SQL_FLOAT, 0, "XM" },									//�ڲ�翹
	{ IES_SQL_FLOAT, 0, "XL" },									//�Ĳ�翹
	{ IES_SQL_FLOAT, 0, "KHM"},									//��/�б��		//dtt add
	{ IES_SQL_FLOAT, 0, "KML"},									//��/�ͱ��
	{ IES_SQL_FLOAT, 0, "KHL"},									//��/�ͱ��

	{ IES_SQL_UTINYINT, 0, "GaoBJ1Type" },						//�ǲ����Ӳ���1 ����
	{ SQL_DATAID_TYPE, 0, "GaoBJ1ID" },						//�ǲ����Ӳ���1
	{ IES_SQL_UTINYINT, 0, "GaoBJ2Type" },						//�ǲ����Ӳ���2 ����
	{ SQL_DATAID_TYPE, 0, "GaoBJ2ID" },						//�ǲ����Ӳ���2
	{ IES_SQL_UTINYINT, 0, "ZhongBJ1Type" },					//�ڲ����Ӳ���1 ����
	{ SQL_DATAID_TYPE, 0, "ZhongBJ1ID" },						//�ڲ����Ӳ���1
	{ IES_SQL_UTINYINT, 0, "ZhongBJ2Type" },					//�ڲ����Ӳ���2 ����
	{ SQL_DATAID_TYPE, 0, "ZhongBJ2ID" },						//�ڲ����Ӳ���2
	{ IES_SQL_UTINYINT, 0, "DiBJ1Type" },						//�Ĳ����Ӳ���1 ����
	{ SQL_DATAID_TYPE, 0, "DiBJ1ID" },						//�Ĳ����Ӳ���1
	{ IES_SQL_UTINYINT, 0, "DiBJ2Type" },						//�Ĳ����Ӳ���2 ����
	{ SQL_DATAID_TYPE, 0, "DiBJ2ID" },						//�Ĳ����Ӳ���2

	{ IES_SQL_UTINYINT, 0, "GPSEFlag" },						//G��P��������
	{ IES_SQL_FLOAT, 0, "GPSERCoef" },							//G��P���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "GQSEFlag" },						//G��Q��������
	{ IES_SQL_FLOAT, 0, "GQSERCoef" },							//G��Q���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "GISEFlag" },						//G��I��������
	{ IES_SQL_FLOAT, 0, "GISERCoef" },							//G��I���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "ZPSEFlag" },						//Z��P��������
	{ IES_SQL_FLOAT, 0, "ZPSERCoef" },							//Z��P���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "ZQSEFlag" },						//Z��Q��������
	{ IES_SQL_FLOAT, 0, "ZQSERCoef" },							//Z��Q���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "ZISEFlag" },						//Z��I��������
	{ IES_SQL_FLOAT, 0, "ZISERCoef" },							//Z��I���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "DPSEFlag" },						//D��P��������
	{ IES_SQL_FLOAT, 0, "DPSERCoef" },							//D��P���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "DQSEFlag" },						//D��Q��������
	{ IES_SQL_FLOAT, 0, "DQSERCoef" },							//D��Q���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "DISEFlag" },						//D��I��������
	{ IES_SQL_FLOAT, 0, "DISERCoef" },							//D��I���Ƽ�Ȩ����

	{ IES_SQL_UTINYINT, 0, "FJTWeiZhiShu" },					//�ֽ�ͷλ�ø���
	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//����Դ����
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//��ǰʹ������Դ
	{ IES_SQL_UTINYINT, 0, "DWCoef" },							//��λת��ϵ��
	{ IES_SQL_BOOL, 0, "DWMFlag" },								//�˹����뵵λ��־
	{ IES_SQL_UINT, 0, "DWMVal" },								//�˹����뵵λֵ

	{ IES_SQL_BOOL, 0, "KeKong" },								//��ѹ(����)�ɿر�־
	{ IES_SQL_BOOL, 0, "CZJiBie" },								//��ѹ(����)��������
	{ IES_SQL_UTINYINT, 0, "DYMode" },							//��ѹ��ʽ

	{ IES_SQL_UTINYINT, 0, "TDSrcNum" },						//�¶�����Դ����
	{ IES_SQL_UTINYINT, 0, "TDSrcUse" },						//�¶ȵ�ǰʹ������Դ
	{ IES_SQL_BOOL, 0, "TMFlag" },								//�˹������¶ȱ�־
	{ IES_SQL_FLOAT, 0, "TMVal" },								//�˹������¶�ֵ

	{ IES_SQL_USMALLINT, 0, "SJTimeLimit" },					//������������
	{ IES_SQL_USMALLINT, 0, "SJTimes" },						//����������
	{ IES_SQL_USMALLINT, 0, "DSJTimeLimit" },					//��������������
	{ IES_SQL_USMALLINT, 0, "DSJTimes" },						//����������

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//Ԫ��������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
	//EMS-Mend dingjide 2009.4.22
	//�޸�ԭ��:��·�����б�ѹ�����Ե�ӵص�բ������
	//EMS-Mend<
	{ SQL_DATAID_TYPE, 0, "HEDAOZHAID" },	
	{ SQL_DATAID_TYPE, 0, "MEDAOZHAID" },	
	//EMS-Mend>
};

//�����
#define dbFadianjiLen 21
static SClmInfo aFaDianJi_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ	
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
 	{ IES_SQL_STRING, 32, "ProdType" },							//��Ʒ����	
	{ IES_SQL_FLOAT, 0, "JiZuRongLiang" },						//�����������(MW)

	{ IES_SQL_UTINYINT, 0, "BJType1ID" },						//���Ӳ���1 ����
	{ SQL_DATAID_TYPE, 0, "BJ1ID" },							//���Ӳ���1
	{ IES_SQL_UTINYINT, 0, "BJType2ID" },						//���Ӳ���2 ����
	{ SQL_DATAID_TYPE, 0, "BJ2ID" },							//���Ӳ���2

	{ IES_SQL_UTINYINT, 0, "PSEFlag" },							//P ��������
	{ IES_SQL_FLOAT, 0, "PSERCoef" },							//P ���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "QSEFlag" },							//Q ��������
	{ IES_SQL_FLOAT, 0, "QSERCoef" },							//Q ���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "ISEFlag" },							//I ��������
	{ IES_SQL_FLOAT, 0, "ISERCoef" },							//I ���Ƽ�Ȩ����

	{ IES_SQL_BOOL, 0, "TingYunShiJian" },						//ͳ����ͣ��ʱ���־

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//Ԫ��������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
};

//CT
#define dbCtLen 69
static SClmInfo aCT_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�
	// DMS_MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
	{ IES_SQL_STRING, 32, "ProdType" },							//��Ʒ����
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//Ͷ������
	{ IES_SQL_STRING, 16, "TranRate" },							//���
	{ IES_SQL_USMALLINT, 0, "PTAddID" },						//��ӦPT
	{ IES_SQL_UTINYINT, 0, "PTPhase" },							//��ӦPT��

	{ IES_SQL_UTINYINT, 0, "PDSrcNum" },						//P ����Դ����
	{ IES_SQL_UTINYINT, 0, "PDSrcUse" },						//P ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "QDSrcNum" },						//Q ����Դ����
	{ IES_SQL_UTINYINT, 0, "QDSrcUse" },						//Q ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "IaDSrcNum" },						//Ia ����Դ����
	{ IES_SQL_UTINYINT, 0, "IaDSrcUse" },						//Ia ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "IbDSrcNum" },						//Ib����Դ����
	{ IES_SQL_UTINYINT, 0, "IbDSrcUse" },						//Ib��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "IcDSrcNum" },						//Ic ����Դ����
	{ IES_SQL_UTINYINT, 0, "IcDSrcUse" },						//Ic ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "IoDSrcNum" },						//Io ����Դ����
	{ IES_SQL_UTINYINT, 0, "IoDSrcUse" },						//Io ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "IhDSrcNum" },						//Ih ����Դ����
	{ IES_SQL_UTINYINT, 0, "IhDSrcUse" },						//Ih ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "SDSrcNum" },						//S ����Դ����
	{ IES_SQL_UTINYINT, 0, "SDSrcUse" },						//S ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "CosDSrcNum" },						//Cos ����Դ����
	{ IES_SQL_UTINYINT, 0, "CosDSrcUse" },						//Cos ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "FDSrcNum" },						//F ����Դ����
	{ IES_SQL_UTINYINT, 0, "FDSrcUse" },						//F ��ǰʹ������Դ

	{ IES_SQL_DOUBLE, 0, "ZPDDCoef" },							//����PKWH����ϵ��
	{ IES_SQL_DOUBLE, 0, "ZQDDCoef" },							//����QKWH����ϵ��
	{ IES_SQL_DOUBLE, 0, "FPDDCoef" },							//����PKWH����ϵ��
	{ IES_SQL_DOUBLE, 0, "FQDDCoef" },							//����QKWH����ϵ��
	{ IES_SQL_DOUBLE, 0, "PDCoef" },							//�������PKWHϵ��
	{ IES_SQL_DOUBLE, 0, "QDCoef" },							//�������QKWHϵ��
	{ IES_SQL_DOUBLE, 0, "FPDCoef" },							//�������PKWHϵ��
	{ IES_SQL_DOUBLE, 0, "FQDCoef" },							//�������QKWHϵ��
	{ IES_SQL_UTINYINT, 0, "DDMode" },							//���ģ����
	{ IES_SQL_UTINYINT, 0, "DDClear" },							//������㷽ʽ

	{ IES_SQL_BOOL, 0, "PCFlag" },								//��ʽ���� P
	{ IES_SQL_BOOL, 0, "QCFlag" },								//��ʽ���� Q
	{ IES_SQL_BOOL, 0, "IaCFlag" },								//��ʽ���� I

	{ IES_SQL_BOOL, 0, "PMFlag" },								//P �����־
	{ IES_SQL_FLOAT, 0, "PMVal" },								//P ����ֵ

	{ IES_SQL_BOOL, 0, "QMFlag" },								//Q �����־
	{ IES_SQL_FLOAT, 0, "QMVal" },								//Q ����ֵ

	{ IES_SQL_BOOL, 0, "IaMFlag" },								//Ia �����־
	{ IES_SQL_FLOAT, 0, "IaMVal" },								//Ia �˹�ֵ

	{ IES_SQL_BOOL, 0, "IbMFlag" },								//Ib �����־
	{ IES_SQL_FLOAT, 0, "IbMVal" },								//Ib ����ֵ

	{ IES_SQL_BOOL, 0, "IcMFlag" },								//Ic �����־
	{ IES_SQL_FLOAT, 0, "IcMVal" },								//Ic ����ֵ

	{ IES_SQL_BOOL, 0, "IoMFlag" },								//Io �����־
	{ IES_SQL_FLOAT, 0, "IoMVal" },								//Io ����ֵ

	{ IES_SQL_BOOL, 0, "IhMFlag" },								//Ih �����־
	{ IES_SQL_FLOAT, 0, "IhMVal" },								//Ih ����ֵ

	{ IES_SQL_BOOL, 0, "SMFlag" },								//S �����־
	{ IES_SQL_FLOAT, 0, "SMVal" },								//S ����ֵ

	{ IES_SQL_BOOL, 0, "CosMFlag" },							//Cos �����־
	{ IES_SQL_FLOAT, 0, "CosMVal" },							//Cos ����ֵ

	{ IES_SQL_BOOL, 0, "FMFlag" },								//F �����־
	{ IES_SQL_FLOAT, 0, "FMVal" },								//F ����ֵ

	{ IES_SQL_BOOL, 0, "PRmtW" },								//����PKWH����ֵ
	{ IES_SQL_BOOL, 0, "PFRmtW" },								//����PKWH����ֵ
	{ IES_SQL_BOOL, 0, "QRmtW" },								//����QKWH����ֵ
	{ IES_SQL_BOOL, 0, "QFRmtW" },								//����QKWH����ֵ

	{ IES_SQL_BOOL, 0, "PJFFlag" },								//P ����
	{ IES_SQL_BOOL, 0, "QJFFlag" },								//Q ����
};

//PT
#define dbPtLen 40
static SClmInfo aPT_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16, "BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN, "MingZi" },							//����
	{ IES_SQL_STRING, 32, "ProdType" },							//��Ʒ����
	{ IES_SQL_TIMESTAMP, 0, "UsedTime" },						//Ͷ������
	{ IES_SQL_STRING, 16, "TranRate" },							//���

	{ IES_SQL_UTINYINT, 0, "UaDSrcNum" },						//Ua ����Դ����
	{ IES_SQL_UTINYINT, 0, "UaDSrcUse" },						//Ua ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "UbDSrcNum" },						//Ub ����Դ����
	{ IES_SQL_UTINYINT, 0, "UbDSrcUse" },						//Ub ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "UcDSrcNum" },						//Uc ����Դ����
	{ IES_SQL_UTINYINT, 0, "UcDSrcUse" },						//Uc ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "UabxDSrcNum" },						//Uabx ����Դ����
	{ IES_SQL_UTINYINT, 0, "UabxDSrcUse" },						//Uabx ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "UbcxDSrcNum" },						//Ubcx ����Դ����
	{ IES_SQL_UTINYINT, 0, "UbcxDSrcUse" },						//Ubcx ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "UcaxDSrcNum" },						//Ucax ����Դ����
	{ IES_SQL_UTINYINT, 0, "UcaxDSrcUse" },						//Ucax ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "UoDSrcNum" },						//Uo ����Դ����
	{ IES_SQL_UTINYINT, 0, "UoDSrcUse" },						//Uo ��ǰʹ������Դ

	{ IES_SQL_UTINYINT, 0, "UangDSrcNum" },						//�������Դ����
	{ IES_SQL_UTINYINT, 0, "UangDSrcUse" },						//��ǵ�ǰʹ������Դ

	{ IES_SQL_BOOL, 0, "UaMFlag" },								//Ua �����־
	{ IES_SQL_FLOAT, 0, "UaMVal" },								//Ua ����ֵ

	{ IES_SQL_BOOL, 0, "UbMFlag" },								//Ub �����־
	{ IES_SQL_FLOAT, 0, "UbMVal" },								//Ub ����ֵ

	{ IES_SQL_BOOL, 0, "UcMFlag" },								//Uc �����־
	{ IES_SQL_FLOAT, 0, "UcMVal" },								//Uc ����ֵ

	{ IES_SQL_BOOL, 0, "UabxMFlag" },							//Uabx �����־
	{ IES_SQL_FLOAT, 0, "UabxMVal" },							//Uabx ����ֵ

	{ IES_SQL_BOOL, 0, "UbcxMFlag" },							//Ubcx �����־
	{ IES_SQL_FLOAT, 0, "UbcxMVal" },							//Ubcx ����ֵ

	{ IES_SQL_BOOL, 0, "UcaxMFlag" },							//Ucax �����־
	{ IES_SQL_FLOAT, 0, "UcaxMVal" },							//Ucax ����ֵ

	{ IES_SQL_BOOL, 0, "UoMFlag" },								//Uo �����־	
	{ IES_SQL_FLOAT, 0, "UoMVal" },								//Uo ����ֵ

	{ IES_SQL_BOOL, 0, "UangMFlag" },							//��������־	
	{ IES_SQL_FLOAT, 0, "UangMVal" },							//�������ֵ
};

//����
#define dbFuheLen 30
static SClmInfo aFuHe_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0,"DianYaDengJiID"},					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//����
	{ IES_SQL_UTINYINT, 0, "FHJiBie" },							//���ɼ���

	{ IES_SQL_UTINYINT, 0, "LJBJType" },						//��Ӧ��������
	{ SQL_DATAID_TYPE,  0, "LJDY1ID" },						//��Ӧ����(P)
	{ SQL_DATAID_TYPE,  0, "LJDY2ID" },						//��Ӧ����(Q)
	{ SQL_DATAID_TYPE,  0, "LJDY3ID" },						//��Ӧ����(I)
	{ SQL_DATAID_TYPE,  0, "LJDY4ID" },						//��Ӧ����(PKWH)
	{ SQL_DATAID_TYPE,  0, "LJDY5ID" },						//��Ӧ����(QKWH)
	{ SQL_DATAID_TYPE,  0, "FLJDY4ID" },						//��Ӧ����(����PKWH)
	{ SQL_DATAID_TYPE,  0, "FLJDY5ID" },						//��Ӧ����(����QKWH)

	{ IES_SQL_BOOL, 0, "PJHFlag" },								//P ���ֱ�־
	{ IES_SQL_BOOL, 0, "QJHFlag" },								//Q ���ֱ�־
	{ SQL_DATAID_TYPE,  0, "PJHDDId" },						//�й����ִ�ŵ�
	{ SQL_DATAID_TYPE,  0, "QJHDDId" },						//�޹����ִ�ŵ�
	{ SQL_DATAID_TYPE,  0, "FPJHDDId" },						//�����й����ִ�ŵ�
	{ SQL_DATAID_TYPE,  0, "FQJHDDId" },						//�����޹����ִ�ŵ�

	{ IES_SQL_UTINYINT, 0, "PSEFlag" },							//P ��������
	{ IES_SQL_FLOAT, 0, "PSERCoef" },							//P ���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "QSEFlag" },							//Q ��������
	{ IES_SQL_FLOAT, 0, "QSERCoef" },							//Q ���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "ISEFlag" },							//I ��������
	{ IES_SQL_FLOAT, 0, "ISERCoef" },							//I ���Ƽ�Ȩ����

	{ IES_SQL_FLOAT, 0, "TopoCoef" },							//��������ϵ��
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//Ԫ��������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
};

//ע��
#define dbZhuruLen 22
static SClmInfo aZhuRu_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//����

	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//��Ӧ��������
	{ SQL_DATAID_TYPE, 0, "PId" },							//��Ӧ����P
	{ SQL_DATAID_TYPE, 0, "QId" },							//��Ӧ����Q
	{ SQL_DATAID_TYPE, 0, "IId" },							//��Ӧ����I
		
	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//���Ӳ�������
	{ SQL_DATAID_TYPE,  0, "LJBJ1ID" },						//���Ӳ���
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//���Ӳ�������

	{ IES_SQL_UTINYINT, 0, "PSEFlag" },							//P ��������
	{ IES_SQL_FLOAT, 0, "PSERCoef" },							//P ���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "QSEFlag" },							//Q ��������
	{ IES_SQL_FLOAT, 0, "QSERCoef" },							//Q ���Ƽ�Ȩ����
	{ IES_SQL_UTINYINT, 0, "ISEFlag" },							//I ��������
	{ IES_SQL_FLOAT, 0, "ISERCoef" },							//I ���Ƽ�Ȩ����

	{ IES_SQL_FLOAT, 0, "TopoCoef" },							//ע������ϵ��	
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//Ԫ��������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
};

//�����
#define dbTiaoxiangLen 21
static SClmInfo aTiaoXiang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//����
	{ IES_SQL_STRING, 32 ,"ProdType" },							//��Ʒ����
	{ IES_SQL_TIMESTAMP,  0, "UsedTime" },						//Ͷ������
	{ IES_SQL_USMALLINT,  0, "TouQieKGID" },					//Ͷ�п���
	{ IES_SQL_FLOAT, 0, "R" },									//��Ч����
	{ IES_SQL_FLOAT, 0, "X" },									//��Ч�翹
	{ IES_SQL_FLOAT, 0, "B" },									//��Ч����

	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//���Ӳ���1 ����
	{ SQL_DATAID_TYPE,  0, "LJBJ1ID" },						//���Ӳ���1
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//���Ӳ���1 ����
	{ IES_SQL_UTINYINT, 0, "LJBJType2" },						//���Ӳ���2 ����
	{ SQL_DATAID_TYPE,  0, "LJBJ2ID" },						//���Ӳ���2
	{ IES_SQL_USMALLINT, 0, "LJBJ2CS" },							//���Ӳ���2 ����

	{ IES_SQL_BOOL, 0, "TouQieTimeF" },							//ͳ��Ͷ��ʱ���־
	
	{ IES_SQL_USMALLINT, 0, "FieldType" },						//Ԫ��������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
};

//��ֹ������
#define dbJingzhibuchangLen 21
static SClmInfo aJingZhiBuChang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//����
	{ IES_SQL_STRING, 32 ,"ProdType" },							//��Ʒ����
	{ IES_SQL_TIMESTAMP,  0, "UsedTime" },						//Ͷ������
	{ IES_SQL_USMALLINT,  0, "TouQieKGID" },					//Ͷ�п���
	{ IES_SQL_FLOAT, 0, "R" },									//��Ч����
	{ IES_SQL_FLOAT, 0, "X" },									//��Ч�翹
	{ IES_SQL_FLOAT, 0, "B" },									//��Ч����

	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//���Ӳ���1 ����
	{ SQL_DATAID_TYPE,  0, "LJBJ1ID" },						//���Ӳ���1
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//���Ӳ���1 ����
	{ IES_SQL_UTINYINT, 0, "LJBJType2" },						//���Ӳ���2 ����
	{ SQL_DATAID_TYPE,  0, "LJBJ2ID" },						//���Ӳ���2
	{ IES_SQL_USMALLINT, 0, "LJBJ2CS" },							//���Ӳ���2 ����

	{ IES_SQL_BOOL, 0, "TouQieTimeF" },							//ͳ��Ͷ��ʱ���־

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//Ԫ��������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
};

//��������
#define dbDianrongLen 22
static SClmInfo aBingLianDianRong_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//����
	{ IES_SQL_STRING, 32 ,"ProdType" },							//��Ʒ����
	{ IES_SQL_TIMESTAMP,  0, "UsedTime" },						//Ͷ������
	{ IES_SQL_USMALLINT,  0, "TouQieKGID" },					//Ͷ�п���
	{ IES_SQL_FLOAT, 0, "C" },									//����������(uf)
	{ IES_SQL_FLOAT, 0, "R" },									//��Ч����
	{ IES_SQL_FLOAT, 0, "X" },									//��Ч�翹
	{ IES_SQL_FLOAT, 0, "B" },									//��Ч����

	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//���Ӳ���1 ����
	{ SQL_DATAID_TYPE,  0, "LJBJ1ID" },						//���Ӳ���1
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//���Ӳ���1 ����
	{ IES_SQL_UTINYINT, 0, "LJBJType2" },						//���Ӳ���2 ����
	{ SQL_DATAID_TYPE,  0, "LJBJ2ID" },						//���Ӳ���2
	{ IES_SQL_USMALLINT, 0, "LJBJ2CS" },							//���Ӳ���2 ����

	{ IES_SQL_BOOL, 0, "TouQieTimeF" },							//ͳ��Ͷ��ʱ���־

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//Ԫ��������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
};

//�����翹
#define dbDiankangLen 27
static SClmInfo aChuanLianDianKang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },					//��ѹ�ȼ�	
	// DMS-MEND>
	{ IES_SQL_STRING, 16 ,"BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//����
	{ IES_SQL_STRING, 32 ,"ProdType" },							//��Ʒ����
	{ IES_SQL_TIMESTAMP,  0, "UsedTime" },						//Ͷ������
	{ SQL_DATAID_TYPE,  0, "DYDianRongID" },					//��Ӧ��������

	{ IES_SQL_FLOAT, 0, "X1" },									//�翹ֵ
	{ IES_SQL_FLOAT, 0, "R1" },									//����ֵ
	{ IES_SQL_FLOAT, 0, "M" },									//���˻���ֵ
	{ IES_SQL_FLOAT, 0, "X2" },									//���˵翹ֵ
	{ IES_SQL_FLOAT, 0, "R2" },									//���˵���ֵ

	{ IES_SQL_UTINYINT, 0, "LJBJType1" },						//���Ӳ���1����
	{ SQL_DATAID_TYPE, 0, "LJBJ1ID" },						//���Ӳ���1
	{ IES_SQL_USMALLINT, 0, "LJBJ1CS" },							//���Ӳ���1 ����
	{ IES_SQL_UTINYINT, 0, "LJBJType2" },						//���Ӳ���2����
	{ SQL_DATAID_TYPE, 0, "LJBJ2ID" },						//���Ӳ���2
	{ IES_SQL_USMALLINT, 0, "LJBJ2CS" },							//���Ӳ���2����
	{ IES_SQL_UTINYINT, 0, "LJBJType3" },						//���Ӳ���3����
	{ SQL_DATAID_TYPE, 0, "LJBJ3ID" },						//���Ӳ���3
	{ IES_SQL_USMALLINT, 0, "LJBJ3CS" },							//���Ӳ���3����

	{ IES_SQL_UTINYINT, 0, "LJType" },							//��������
	{ IES_SQL_BOOL, 0, "TouQieTimeF" },							//ͳ��Ͷ��ʱ���־

	{ IES_SQL_USMALLINT, 0, "FieldType" },						//Ԫ��������
	{ IES_SQL_USMALLINT, 0, "StaFieldID" },						//վ�������
	{ IES_SQL_USMALLINT, 0, "ComponentID" },					//����Ԫ�����
};

//���ⵥ��ģ����
#define dbYaoceLen 11
static SClmInfo aXuNiDMNLiang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID	
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	{ IES_SQL_STRING, 16 ,"BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//����
	{ IES_SQL_UTINYINT, 0, "XNType" },							//��������
	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//��Ӧ��������(����)
	{ SQL_DATAID_TYPE, 0, "DYBJID" },							//��Ӧ����(����)

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//����Դ����
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//��ǰʹ������Դ

	{ IES_SQL_BOOL, 0, "MFlag" },								//�����־
	{ IES_SQL_FLOAT, 0, "MVal" },								//����ֵ
};

//����˫��ģ����
#define dbDianduLen 12
static SClmInfo aXuNiSMNLiang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	{ IES_SQL_STRING, 16 ,"BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//����
	{ IES_SQL_UTINYINT, 0, "XNType" },							//��������
	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//��Ӧ��������(����)
	{ SQL_DATAID_TYPE, 0, "DYBJID" },							//��Ӧ����(����)

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//����Դ����
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//��ǰʹ������Դ

	{ IES_SQL_DOUBLE, 0, "Coef" },								//ϵ��

	{ IES_SQL_BOOL, 0, "RemoteF" },								//ң����־
	{ IES_SQL_BOOL, 0, "JFFlag" },								//���ֱ�־
};

//����״̬��
#define dbYaoxinLen 19
static SClmInfo aXuNiZHTLiang_Col[] =
{
	{ SQL_DATAID_TYPE, 0, "ID" },								//ID
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },					//��վ
	{ IES_SQL_STRING, 16 ,"BianHao" },							//���
	{ IES_SQL_STRING, NAMELEN ,"MingZi" },							//����
	{ IES_SQL_UTINYINT, 0, "XNType" },							//��������
	{ IES_SQL_UTINYINT, 0, "DYBJType" },						//��Ӧ��������(����)
	{ SQL_DATAID_TYPE, 0, "DYBJID" },							//��Ӧ����(����)

	{ IES_SQL_UINT , 0, "DZCount" },							//״̬�仯�ۼƴ���

	{ IES_SQL_UTINYINT, 0, "DSrcNum" },							//����Դ����		//0-4
	{ IES_SQL_UTINYINT, 0, "DSrcUse" },							//��ǰʹ������Դ	//0-4

	{ IES_SQL_BOOL, 0, "SheZhiF" },								//�����־
	{ IES_SQL_BOOL, 0, "STValue" },								//״ֵ̬
	{ IES_SQL_BOOL, 0, "TJTouQie" },							//ͳ����Ͷ��ʱ��
	{ IES_SQL_BOOL, 0, "KeKong" },								//�ɿ�
	{ IES_SQL_UTINYINT, 0, "CZJiBie" },							//���Ƽ���
	{ IES_SQL_BOOL, 0, "ChRec" },								//��λ��¼
	{ IES_SQL_BOOL, 0, "ChAlarm" },								//��λ����
	{ IES_SQL_BOOL, 0, "ChPrint" },								//��λ��ӡ
	{ IES_SQL_BOOL, 0, "ChScr" },								//��λ��ͼ
};

// EMS-Mend<yuecaijuan 2010.11.17 ����һ�廯����I��
// �޸�ԭ��������Ϣ
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
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{IES_SQL_UTINYINT,	0,	"DianYaDengJiID"},	
	// DMS-MEND
	{IES_SQL_UTINYINT,	0,	"BJType"},			
	{SQL_DATAID_TYPE,	0,	"BJID"},				
	{SQL_DATAID_TYPE,	0,	"FEEDERID"},			
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�SQL_DATAID_TYPE���͸�ΪIES_SQL_UINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
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
	// �޸�ԭ�򣺽�SQL_DATAID_TYPE���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
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
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
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
//����������
static STblInfo aDWBuJian_Table[] =
{
	{ sizeof(aDianWang_Col)/sizeof(SClmInfo), "dianwang", MingZi_DianWangID, 1, aDianWang_Col },
	{ sizeof(aDianYaDengJi_Col)/sizeof(SClmInfo), "dianyadengji", "��ѹ�ȼ�", 1, aDianYaDengJi_Col },
	{ sizeof(aChangZhan_Col)/sizeof(SClmInfo), "changzhan", MingZi_ChangZhanID, 1, aChangZhan_Col },
	{ sizeof(aMuXian_Col)/sizeof(SClmInfo), "muxian", "ĸ��", 1, aMuXian_Col },
	{ sizeof(aXianLu_Col)/sizeof(SClmInfo), "xianlu", "��·", 1, aXianLu_Col },
	{ sizeof(aKaiGuan_Col)/sizeof(SClmInfo), "kaiguan", "����", 1, aKaiGuan_Col },
	{ sizeof(aDaoZha_Col)/sizeof(SClmInfo), "daozha", "��բ", 1, aDaoZha_Col },
	{ sizeof(aBaoHu_Col)/sizeof(SClmInfo), "baohu", "����", 1, aBaoHu_Col },
	{ sizeof(aBianYaQi_Col)/sizeof(SClmInfo), "bianyaqi", "��ѹ��", 1, aBianYaQi_Col },
	{ sizeof(aFaDianJi_Col)/sizeof(SClmInfo), "fadianji", "�����", 1, aFaDianJi_Col },
	{ sizeof(aCT_Col)/sizeof(SClmInfo), "ct", "CT", 1, aCT_Col },
	{ sizeof(aPT_Col)/sizeof(SClmInfo), "pt", "PT", 1, aPT_Col },
	{ sizeof(aFuHe_Col)/sizeof(SClmInfo), "fuhe", "����", 1, aFuHe_Col },
	{ sizeof(aZhuRu_Col)/sizeof(SClmInfo), "zhuru", "ע��", 1, aZhuRu_Col },
	{ sizeof(aTiaoXiang_Col)/sizeof(SClmInfo), "tiaoxiang", "�����", 1, aTiaoXiang_Col },
	{ sizeof(aJingZhiBuChang_Col)/sizeof(SClmInfo), "jingzhibuchang", "��ֹ������", 1, aJingZhiBuChang_Col },
	{ sizeof(aBingLianDianRong_Col)/sizeof(SClmInfo), "bingliandianrong", "������������", 1, aBingLianDianRong_Col },
	{ sizeof(aChuanLianDianKang_Col)/sizeof(SClmInfo), "chuanliandiankang", "�����翹", 1, aChuanLianDianKang_Col },
	{ sizeof(aXuNiDMNLiang_Col)/sizeof(SClmInfo), "xunidmnliang", "���ⵥ��ģ����", 1, aXuNiDMNLiang_Col },
	{ sizeof(aXuNiSMNLiang_Col)/sizeof(SClmInfo), "xunismnliang", "����˫��ģ����", 1, aXuNiSMNLiang_Col },
	{ sizeof(aXuNiZHTLiang_Col)/sizeof(SClmInfo), "xunizhtliang", "����״̬��", 1, aXuNiZHTLiang_Col },
	{ sizeof(aFeeder_Col)/sizeof(SClmInfo),  "feeder", "����",1,aFeeder_Col},// EMS-Mend<yuecaijuan 2010.11.17 ����һ�廯����I��
	{ sizeof(aPBBianYaQi_Col)/sizeof(SClmInfo),	  "transformer",	"����ѹ��",1,aPBBianYaQi_Col},
	{ sizeof(aKuiXianDuan_Col)/sizeof(SClmInfo),  "feedersection", "���߶�",1,aKuiXianDuan_Col},
};

//EMS-Mend<
//���ѽ� 2006.4.19 ʵ��iesdraw���ɾ����վ����
//��վ�������ṹ
static STblInfo  aChangZhan_Table = { sizeof(aChangZhan_Col_NEW)/sizeof(SClmInfo), "changzhan", MingZi_ChangZhanID, 1, aChangZhan_Col_NEW };
//�����������ṹ
static STblInfo  aFenQu_Table = { sizeof(aFenQu_Col)/sizeof(SClmInfo), "SubNet_EMS", "����", 1, aFenQu_Col };
//���繫˾�������ṹ
static STblInfo  aFaDianGongSi_Table = { sizeof(aFaDianGongSi_Col)/sizeof(SClmInfo), "powercorp", "���繫˾", 1, aFaDianGongSi_Col };
//EMS-Mend>

//================================================================
//΢����������  99.8
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

//΢���˲���������  99.8
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

//΢���˶˿������� 99.8
static SClmInfo aTopoPort_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },
	{ IES_SQL_UTINYINT, 0, "RecID" },

	{ IES_SQL_STRING,  16 , "PortTag" },
	{ IES_SQL_UTINYINT, 0, "PortNodeID" },
	{ IES_SQL_BOOL, 0, "InPortFlag" },
	{ IES_SQL_USMALLINT, 0, "CorBusID" },
};

//΢�������������� 99.8
static SClmInfo aTopoLine_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },
	{ IES_SQL_UTINYINT, 0, "RecID" },

	{ IES_SQL_STRING,  16, "LineName" },
	{ IES_SQL_UTINYINT, 0, "LineID" },
	{ IES_SQL_BOOL, 0, "BusFlag" },
	{ IES_SQL_UTINYINT, 0, "PortNode" },
};

//΢���˴����ѯ������ 99.8
static SClmInfo aTopoElectronicQuery_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },
	{ IES_SQL_UINT, 0, "RecID" },

//	{ IES_SQL_BINARY, 8, "AllInputFlag" },		//dtt locked for debug
	{ IES_SQL_BINARY, 10, "AllInputFlag" },	
	{ IES_SQL_BINARY, 16, "AllLineFlag" },	
};

//΢����Ԥ������������ 99.12.6
static SClmInfo aTopoPreDeal_Col[] = 
{
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },

	{ IES_SQL_BINARY, 193, "NodeData" },
	{ IES_SQL_BINARY, 33, "BranchData" },
};

//����΢����������  99.8
static SClmInfo aDWTopo_Col[] = 
{
	{ SQL_DATAID_TYPE,	0, "ChangZhanID" },
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },	
	// DMS-MEND>
	{ IES_SQL_USMALLINT, 0, "FieldID" },
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },

	{ IES_SQL_STRING, NAMELEN ,"Name" },
	{ IES_SQL_BOOL, 0, "InUseFlag" },
};

//����΢���˲���������  99.8
static SClmInfo aDWTopoBuJian_Col[] = 
{
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
	{ IES_SQL_UTINYINT, 0, "DianYaDengJiID" },	
	// DMS-MEND>
	{ IES_SQL_USMALLINT, 0, "FieldID" },
	{ IES_SQL_USMALLINT, 0, "FieldTypeID" },

	{ IES_SQL_UTINYINT, 0, "RecID" },
	{ IES_SQL_UTINYINT, 0, "ComponentNo" },
	{ IES_SQL_UTINYINT, 0, "ComponentType" },
	{ SQL_DATAID_TYPE, 0, "ComponentID" },
};

//����΢���˶˿�������  99.8
static SClmInfo aDWTopoPort_Col[] = 
{
	{ SQL_DATAID_TYPE, 0, "ChangZhanID" },
	// DMS-MEND< yuecaijuan, 2008.10.27 19:40
	// �޸�ԭ�򣺽�IES_SQL_USMALLINT���͸�ΪIES_SQL_UTINYINT���ͣ�ԭ����
	// ����������Ϣʱ����ʾORA-01438: ֵ���ڴ���ָ���������ȡ�����������
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
	{ sizeof(aTopo_Col)/sizeof(SClmInfo), "Topo", "����", 1, aTopo_Col },
	{ sizeof(aTopoBuJian_Col)/sizeof(SClmInfo), "TopoBuJian", "���˲���", 1, aTopoBuJian_Col },
	{ sizeof(aTopoPort_Col)/sizeof(SClmInfo), "TopoPort", "���˶˿�", 1, aTopoPort_Col },
	{ sizeof(aTopoLine_Col)/sizeof(SClmInfo), "TopoLine", "��������", 1, aTopoLine_Col },
	{ sizeof(aTopoElectronicQuery_Col)/sizeof(SClmInfo), "TopoEquery", "����״̬��ѯ", 1, aTopoElectronicQuery_Col },
	{ sizeof(aTopoPreDeal_Col)/sizeof(SClmInfo), "TopoPredeal", "Ԥ������", 1, aTopoPreDeal_Col },
	{ sizeof(aDWTopo_Col)/sizeof(SClmInfo), "DWTopo", iES_Conn(MingZi_DianWangID,΢����), 1, aDWTopo_Col },
	{ sizeof(aDWTopoBuJian_Col)/sizeof(SClmInfo), "DWTopoBuJian", iES_Conn(MingZi_DianWangID,΢���˲���), 1, aDWTopoBuJian_Col },
	{ sizeof(aDWTopoPort_Col)/sizeof(SClmInfo), "DWTopoPort", iES_Conn(MingZi_DianWangID,΢���˶˿�), 1, aDWTopoPort_Col },
};