#ifndef NETMODULE_H
#define NETMODULE_H

#ifdef WIN32

#ifdef NETMODULE_EXPORTS

#define VIDEO_NET_API  extern "C" __declspec(dllexport)
#else
#define VIDEO_NET_API  extern "C" __declspec(dllimport)   //VC ��
#endif

#ifndef CALL_METHOD
#define CALL_METHOD	__stdcall  //__cdecl
#endif

#ifndef JVT_LONG
#ifdef _WIN64
#define JVT_LONG    __int64
#else 
#define JVT_LONG    LONG
#endif // _WIN64
#endif // !JVT_LONG

#ifndef JVT_DWORD
#ifdef _WIN64
#define JVT_DWORD   unsigned __int64
#else
#define JVT_DWORD   DWORD
#endif // _WIN64

#endif // !JVT_DWORD


#else	//linux
#define HH_NET_API	extern "C"
#define CALL_METHOD
#define CALLBACK
#define WORD	unsigned short
#define DWORD	unsigned long
#define LPDWORD	DWORD*
#define BOOL	int
#define TRUE	1
#define FALSE	0
#define BYTE	unsigned char
#define LONG	long
#define UINT	unsigned int
#define HDC		void*
#define HWND	void*
#define LPVOID	void*
//#define NULL	0
#define LPCSTR  char*
#define LPCTSTR  const char*
#endif


enum SDK_RET_CODE
{	
	VIDEONET_NOERROR				= 0,				//û�д���
	VIDEONET_SUCCESS				= 1,				//���سɹ�
	VIDEONET_SDK_NOTVALID			= -10000,			//�Ƿ�����
	VIDEONET_NO_INIT				= -10001,			//SDKδ����ʼ��
	VIDEONET_ILLEGAL_PARAM			= -10002,			//�û��������Ϸ�
	VIDEONET_INVALID_HANDLE			= -10003,			//�����Ч
	VIDEONET_SDK_UNINIT_ERROR		= -10004,			//SDK�������
	VIDEONET_SDK_TIMEOUT			= -10005,			//�ȴ���ʱ
	VIDEONET_SDK_MEMORY_ERROR		= -10006,			//�ڴ���󣬴����ڴ�ʧ��
	VIDEONET_SDK_NET_ERROR			= -10007,			//�������
	VIDEONET_SDK_OPEN_FILE_ERROR	= -10008,			//���ļ�ʧ��
	VIDEONET_SDK_UNKNOWNERROR		= -10009,			//δ֪����
	VIDEONET_DEV_VER_NOMATCH		= -11000,			//�յ����ݲ���ȷ�����ܰ汾��ƥ��
	VIDEONET_SDK_NOTSUPPORT			= -11001,			//�汾��֧��
	VIDEONET_SDK_FILE_FORAMAT_ERROR			= -11002,	//����ͼƬ�ļ���ʽ����
	VIDEONET_SDK_ADDP2PPORT_FAIL	= -11003,			//����P2P�˿�ʧ��
	VIDEONET_SDK_FILE_DATA_LARGE_ERROR	= -11004,		//�ļ����ݹ���
	VIDEONET_SDK_CONNECT_P2PSERVER_FAIL = -11005,		//���ӻ��Ʒ�����ʧ��

	VIDEONET_OPEN_CHANNEL_ERROR		= -11200,			//��ͨ��ʧ��
	VIDEONET_CLOSE_CHANNEL_ERROR	= -11201,			//�ر�ͨ��ʧ��
	VIDEONET_SUB_CONNECT_ERROR		= -11202,			//����ý��������ʧ��
	VIDEONET_SUB_CONNECT_SEND_ERROR	= -11203,			//ý��������ͨѶʧ��
	VIDEONET_NATCONNET_REACHED_MAX  = -11204,           //Nat��Ƶ���Ӵﵽ��󣬲������µ�Nat��Ƶ���� 

	

	/// �û������ִ�����
	VIDEONET_NOPOWER					= -11300,			//��Ȩ��
	VIDEONET_PASSWORD_NOT_VALID			= -11301,			// �˺����벻��
	VIDEONET_LOGIN_USER_NOEXIST			= -11302,			//�û�������
	VIDEONET_USER_LOCKED				= -11303,			// ���û�������
	VIDEONET_USER_IN_BLACKLIST			= -11304,			// ���û����������(�ں�������)
	VIDEONET_USER_HAS_USED				= -11305,			// ���û��Ե�½
	VIDEONET_USER_NOT_LOGIN				= -11306,			// ���û�û�е�½
	VIDEONET_CONNECT_DEVICE_ERROR		= -11307,			//�����豸������
	VIDEONET_ACCOUNT_INPUT_NOT_VALID	= -11308,			//�û��������벻�Ϸ�
	VIDEONET_ACCOUNT_OVERLAP			= -11309,			//�����ظ�
	VIDEONET_ACCOUNT_OBJECT_NONE		= -11310,			//�����ڶ���, ���ڲ�ѯʱ
	VIDEONET_ACCOUNT_OBJECT_NOT_VALID	= -11311,			//�����ڶ���
	VIDEONET_ACCOUNT_OBJECT_IN_USE		= -11312,			//��������ʹ��
	VIDEONET_ACCOUNT_SUBSET_OVERLAP		= -11313,			//�Ӽ�����Χ (�����Ȩ�޳���Ȩ�ޱ��û�Ȩ�޳������Ȩ�޷�Χ�ȵ�)
	VIDEONET_ACCOUNT_PWD_NOT_VALID		= -11314,			//���벻��ȷ
	VIDEONET_ACCOUNT_PWD_NOT_MATCH		= -11315,			//���벻ƥ��
	VIDEONET_ACCOUNT_RESERVED			= -11316,			//�����ʺ�


	/// ���ù�����ش�����
	
	VIDEONET_OPT_RESTART			= -11400,			// �������ú���Ҫ����Ӧ�ó���
	VIDEONET_OPT_REBOOT				= -11401,			// ��Ҫ����ϵͳ
	VIDEONET_OPT_FILE_ERROR			= -11402,			// д�ļ�����
	VIDEONET_OPT_CAPS_ERROR			= -11403,			// �������Բ�֧��
	VIDEONET_OPT_VALIDATE_ERROR		= -11404,			// ����У��ʧ��
	VIDEONET_OPT_CONFIG_NOT_EXIST	= -11405,			// ����������õ����ò�����
	
	/// 

	VIDEONET_CTRL_PAUSE_ERROR		= -11500,			//��ͣʧ��
	VIDEONET_SDK_NOTFOUND			= -11501,			//����ʧ�ܣ�û���ҵ���Ӧ�ļ�
	VIDEONET_CFG_NOT_ENABLE         = -11502,           //����δ����

	VIDEONET_DECORD_FAIL            = -11503,           //����ʧ��

	//DNSЭ��������ش�����
	VIDEONET_SOCKET_ERROR             = -11600,         //�����׽���ʧ��
	VIDEONET_SOCKET_CONNECT           = -11601,         //�����׽���ʧ��
	VIDEONET_SOCKET_DOMAIN            = -11602,         //��������ʧ��
	VIDEONET_SOCKET_SEND              = -11603,         //��������ʧ��
	VIDEONET_ARSP_NO_DEVICE           = -11604,         //û�л�ȡ���豸��Ϣ���豸Ӧ�ò�����
	VIDEONET_ARSP_BUSING              = -11605,         //ARSP����æ
	VIDEONET_ARSP_BUSING_SELECT       = -11606,         //ARSP����æ,selectʧ��
	VIDEONET_ARSP_BUSING_RECVICE	  = -11607,         //ARSP����æ,recviceʧ��
	VIDEONET_CONNECTSERVER_ERROR      = -11608,        //���ӷ�����ʧ��

	//
	VIDEONET_CONNECT_FULL      = -11612,              //����������������


	//��Ȩ���
	VIDEONET_PIRATESOFTWARE           =-11700,       //�豸����

};


//��̨��������
enum PTZ_ControlType
{
	PTZ_TILT_UP = 0,			//��
	PTZ_TILT_DOWN,				//��
	PTZ_PAN_LEFT,				//��
	PTZ_PAN_RIGHT,				//��
	PTZ_PAN_LEFTTOP,			//����
	PTZ_PAN_LEFTDOWN,			//����
	PTZ_PAN_RIGTHTOP,			//����
	PTZ_PAN_RIGTHDOWN,			//����
	PTZ_ZOOM_OUT,				//�䱶С
	PTZ_ZOOM_IN,				//�䱶��
	PTZ_FOCUS_FAR,				//������
	PTZ_FOCUS_NEAR,				//����ǰ��
	PTZ_IRIS_OPEN,				//��Ȧ����
	PTZ_IRIS_CLOSE,				//��Ȧ��С13

	EXTPTZ_OPERATION_ALARM,			///< �������� 
	EXTPTZ_LAMP_ON,					///< �ƹ⿪
	EXTPTZ_LAMP_OFF,				//�ƹ��
	EXTPTZ_POINT_SET_CONTROL,			//����Ԥ�õ� 
	EXTPTZ_POINT_DEL_CONTROL,			//���Ԥ�õ� 
	EXTPTZ_POINT_MOVE_CONTROL,			//תԤ�õ�
	EXTPTZ_STARTPANCRUISE,			//��ʼˮƽ��ת		20	
	EXTPTZ_STOPPANCRUISE,			//ֹͣˮƽ��ת	
	EXTPTZ_SETLEFTBORDER,			//������߽�		
	EXTPTZ_SETRIGHTBORDER,			//�����ұ߽�	
	EXTPTZ_STARTLINESCAN,			//�Զ�ɨ�迪ʼ 
	EXTPTZ_CLOSELINESCAN,			//�Զ�ɨ�迪ֹͣ 
	EXTPTZ_ADDTOLOOP,				//����Ԥ�õ㵽Ѳ��	p1Ѳ����·	p2Ԥ�õ�ֵ	
	EXTPTZ_DELFROMLOOP,				//ɾ��Ѳ����Ԥ�õ�	p1Ѳ����·	p2Ԥ�õ�ֵ	
	EXTPTZ_POINT_LOOP_CONTROL,			//��ʼѲ�� 28
	EXTPTZ_POINT_STOP_LOOP_CONTROL,	//ֹͣѲ��
	EXTPTZ_CLOSELOOP,				//���Ѳ��	p1Ѳ����·		
	EXTPTZ_FASTGOTO,				//���ٶ�λ	
	EXTPTZ_AUXIOPEN,				//�������أ��ر�����������//param1 �μ�SDK_PtzAuxStatus��param2���������ֵ
	EXTPTZ_OPERATION_MENU,				//����˵����������а��������أ�ȷ���ȵ�
	EXTPTZ_REVERSECOMM,				//��ͷ��ת
	EXTPTZ_OPERATION_RESET,			///< ��̨��λ
	EXTPTZ_PATTERN,					///< ����ģʽ��ʼ

	EXTPTZ_BRUSH_ON,				//��ˢ��	37
	EXTPTZ_BRUSH_OFF,				//��ˢ��

	EXTPTZ_TOTAL,
};
/// ��̨��������
enum SDK_PtzAuxStatus
{
	EXTPTZ_AUX_ON,		///< ��
	EXTPTZ_AUX_OFF,	///< ��
	EXTPTZ_AUX_NR,		
};

#define PTZ_PAN_AUTO		29	/* ��̨��SS���ٶ������Զ�ɨ�� */
//#define EXTPTZ_FASTGOTO	30	//��ά��λ


#define NET_MAX_CHANNUM 			32			//���ͨ������
#define NET_DECORDR_CH              32          //������ͨ������
#define NET_MAX_USER_NUM			60			//����û���
#define NET_MAX_RIGTH_NUM			128			//���Ȩ����
#define NET_MAX_GROUP_NUM			50			//�������
#define NET_MAX_USER_LENGTH			32			//�û���������󳤶�
#define NET_MAX_COMBINE_NUM			2			//�����ϱ���ͨ����
#define NET_MAX_DECORDR_CH          32          //������ͨ������	

#define NET_MAX_DDNS_TYPE			5			//֧�ֵ�DDNS����
#define NET_MAX_ARSP_TYPE			5
#define NET_MAX_ALARMSERVER_TYPE    5           //֧�ֱ�����������
#define NET_MAX_SYSFUNC				20			//���ϵͳ���ܸ���
#define NET_MAX_PTZ_PROTOCOL_LENGTH 32			//��̨Э��������󳤶�
#define NET_N_WEEKS					7			//������
#define	NET_N_TSECT					6			//ʱ�����
#define NET_MD_REGION_ROW			32			//��̬�����������
#define NET_COVERNUM				8			 //����������
#define NET_MAX_FILTERIP_NUM		64			//IP��ַ��������
#define NET_NAME_PASSWORD_LEN		64			//�û���������󳤶�
#define NET_MAX_PATH_LENGTH	        260			//·������
#define NET_N_MIN_TSECT				2
#define NET_MAX_RETURNED_LOGLIST	128			//�����־����
#define NET_MAX_MAC_LEN             32          //MAC��ַ�ַ���󳤶�
#define NET_IW_ENCODING_TOKEN_MAX   128
#define NET_MAX_AP_NUMBER           32          //SID����������ݶ�10
#define NET_MAX_INFO_LEN		    128
#define NET_MAX_USERNAME_LENGTH		128
#define NET_MAX_SERIALNO_LENGTH		128          //������ͨ������
#define NET_CHANNEL_NAME_MAX_LEN   64		///< ͨ��������󳤶�
#define NET_MAX_LINE_PER_OSD_AREA   6      ///<������һ��OSD������������ʾ���ַ�����
#define NET_NAME_URL_LEN            128    //URL   

//DDNS����
#define DDNS_MAX_DDNS_NAMELEN 64  //����������
#define DDNS_MAX_DDNS_PWDLEN 32   //���볤��
#define DDNS_MAX_DDNS_IPSIZE 64   //IP��ַ����
#define DDNS_MAX_DDNS_IDSIZE 32   //�豸��ʶ����
#define DDNS_MAX_SERIALINFO_SIZE 16 //���к��Լ��û�������



//���������
#define CAMERAPARA_MAXNUM  16    //�ع�������Ŀǰ��󳤶�
//�����������
#define SDK_MAX_RECIVE_MSG_PHONE_COUNT 3	///<�������������

//VGA�ֱ���
#define VGA_MAXNUM     32       //�ֱ��� ����
#define VGA_NAME_LENGTH 10		//�ֱ��� ����	

//��ʾ���豸�б�(�豸������)
#define DEV_LIST_SHOW  256

//IP SIZE
#define IP_SIZE  16
//#define  MAX_HVR_CHNCAP       16
//DDNS�������豸����Ϣ

#define  NET_NAME_TOKEN_LEN 128

typedef struct _DDNS_INFO
{
	char ID[64];    //�豸��ʶ
	char Alias[DDNS_MAX_DDNS_NAMELEN];
	char IP[DDNS_MAX_DDNS_IPSIZE];   //����IP
	char LanIP[DDNS_MAX_DDNS_IPSIZE];//����IP
	int WebPort; //Web�˿�,Ĭ��Ϊ80
	int MediaPort; //ý��˿�,Ĭ��Ϊ34567
	int MobilePort;  //�ֻ���ض˿ڣ�Ĭ��Ϊ34599
	int UPNPWebPort;  //UPNP������Web�˿�,UPNP������Ϊ0
	int UPNPMediaPort; //UPNP������ý��˿�,UPNP������Ϊ0
	int UPNPMobilePort; //UPNP�������ֻ���ض˿�,UPNP������Ϊ0
	int ChannelNum; //ͨ����
	int Status; //״̬
	char Username[DDNS_MAX_DDNS_NAMELEN]; //�û���
	char Password[DDNS_MAX_DDNS_PWDLEN]; //����
}DDNS_INFO,*pDDNS_INFO;

//DDNS��Ϣ��ѯģʽ
typedef struct _SearchMode
{
	int  nType;        //��ѯ���ͣ���SearchModeType
	char szSerIP[DDNS_MAX_DDNS_IPSIZE];//��������ַ
	int nSerPort;           //�������˿ں�
	char szSerialInfo[DDNS_MAX_SERIALINFO_SIZE];  //����ǰ����кţ���Ϊ���кţ�������û�������Ϊ�û���
	char szPassWord[DDNS_MAX_DDNS_PWDLEN]; //���û�����½ʱ�������

}SearchMode;

//DDNS��Ϣ��ѯ����
enum SearchModeType
{
	DDNS_SERIAL = 0,//�����к�
	DDNS_USERNAME,  //���û���
};
//ʵʱԤ����չ�ӿ����ӵĲ�����Ԥ������
typedef enum _VideoNet_RealPlayType
{
	NET_RType_Realplay = 0,	//ʵʱԤ��
	NET_RType_Main_Realplay2,	//ʵʱ����-����������ͬ��NET_RType_Realplay
	NET_RType_Main_Realplay3,
	NET_RType_Sub_Realplay_1,	//ʵʱ����-������1
	NET_RType_Sub_Realplay_2,	//ʵʱ����-������2
	NET_RType_Sub_Realplay_3,	//ʵʱ����-������3

	NET_RType_Multiplay_1,	//�໭��Ԥ����1����
	NET_RType_Multiplay_4,	//�໭��Ԥ����4����
	NET_RType_Multiplay_6,	//�໭��Ԥ����6����
	NET_RType_Multiplay_8,	//�໭��Ԥ����8����
	NET_RType_Multiplay_9,	//�໭��Ԥ����9����
	NET_RType_Multiplay_12,	//�໭��Ԥ����12����
	NET_RType_Multiplay_16,	//�໭��Ԥ����16����
} NET_RealPlayType;

/// ��ϱ���ģʽ
enum NetCombinType
{
	NET_COMBIN_NONE,
	NET_COMBIN_1,
	NET_COMBIN_2,
	NET_COMBIN_3,
	NET_COMBIN_4,
	NET_COMBIN_5,
	NET_COMBIN_6,
	NET_COMBIN_7,
	NET_COMBIN_8,
	NET_COMBIN_9,
	NET_COMBIN_10,
	NET_COMBIN_11,
	NET_COMBIN_12,
	NET_COMBIN_13,
	NET_COMBIN_14,
	NET_COMBIN_15,
	NET_COMBIN_16,
	NET_COMBIN_1_4,
	NET_COMBIN_5_8,
	NET_COMBIN_9_12,
	NET_COMBIN_13_16,
	NET_COMBIN_1_8,
	NET_COMBIN_9_16,
	NET_COMBIN_1_9,
	NET_COMBIN_8_16,
	NET_COMBIN_1_16
};

//��Щ�ṹ���ö�����ṩ���ⲿʹ�ã����п��ܻ���豸�Ǳ߶�����2��,���Զ���ǰ�����SDK_
enum SDK_CAPTURE_SIZE_t {
	SDK_CAPTURE_SIZE_D1,		///< 720*576(PAL)	720*480(NTSC)
	SDK_CAPTURE_SIZE_HD1,		///< 352*576(PAL)	352*480(NTSC)
	SDK_CAPTURE_SIZE_BCIF,		///< 720*288(PAL)	720*240(NTSC)
	SDK_CAPTURE_SIZE_CIF,		///< 352*288(PAL)	352*240(NTSC)
	SDK_CAPTURE_SIZE_QCIF,		///< 176*144(PAL)	176*120(NTSC)
	SDK_CAPTURE_SIZE_VGA,		///< 640*480(PAL)	640*480(NTSC)
	SDK_CAPTURE_SIZE_QVGA,		///< 320*240(PAL)	320*240(NTSC)
	SDK_CAPTURE_SIZE_SVCD,		///< 480*480(PAL)	480*480(NTSC)
	SDK_CAPTURE_SIZE_QQVGA,		///< 160*128(PAL)	160*128(NTSC)
	SDK_CAPTURE_SIZE_ND1 = 9,     ///< 240*192
	SDK_CAPTURE_SIZE_650TVL,      ///< 926*576
	SDK_CAPTURE_SIZE_720P,        ///< 1280*720
	SDK_CAPTURE_SIZE_1_3M,        ///< 1280*960
	SDK_CAPTURE_SIZE_UXGA ,       ///< 1600*1200
	SDK_CAPTURE_SIZE_1080P,       ///< 1920*1080
	SDK_CAPTURE_SIZE_WUXGA,       ///< 1920*1200
	SDK_CAPTURE_SIZE_2_5M,        ///< 1872*1408
	SDK_CAPTURE_SIZE_3M,          ///< 2048*1536
	SDK_CAPTURE_SIZE_5M,          ///< 3744*1408
	SDK_CAPTURE_SIZE_EXT_NR =19,    ///< ö�ٵ�ͼ�δ�С�������Ŀ��
	SDK_CAPTURE_SIZE_1080N = 19,     ///< 960*1080
	SDK_CAPTURE_SIZE_4M,        ///< 2592*1520
	SDK_CAPTURE_SIZE_6M,		///< 3072��2048
	SDK_CAPTURE_SIZE_8M,		///< 3264��2448
	SDK_CAPTURE_SIZE_12M,		///< 4000*3000
	SDK_CAPTURE_SIZE_4K,		///< 4096 * 2160ͨ��/3840*2160��˼
	SDK_CAPTURE_SIZE_EXT_V2_NR=25,    ///< ö�ٵ�ͼ�δ�С�������Ŀ��
	SDK_CAPTURE_SIZE_720N = 25,  //  640*720
	SDK_CAPTURE_SIZE_WSVGA,      ///< 1024*576
	SDK_CAPTURE_SIZE_RES2,       // 0*0
	SDK_CAPTURE_SIZE_RES3,       // 0*0
	SDK_CAPTURE_SIZE_RES4,       // 0*0
	SDK_CAPTURE_SIZE_RES5,       // 0*0
	SDK_CAPTURE_SIZE_RES6,       // 0*0
	SDK_CAPTURE_SIZE_NR,
};

/// ������������ģʽ����
enum SDK_capture_brc_t {
	SDK_CAPTURE_BRC_CBR,			///< �̶�������
	SDK_CAPTURE_BRC_VBR,			///< �ɱ�������
	SDK_CAPTURE_BRC_MBR,			///< ���������
	SDK_CAPTURE_BRC_NR				///< ö�ٵ���������ģʽ��Ŀ��
};

/// ����ѹ����ʽ����
enum SDK_CAPTURE_COMP_t {
	SDK_CAPTURE_COMP_DIVX_MPEG4,	///< DIVX MPEG4��
	SDK_CAPTURE_COMP_MS_MPEG4,		///< MS MPEG4��
	SDK_CAPTURE_COMP_MPEG2,			///< MPEG2��
	SDK_CAPTURE_COMP_MPEG1,			///< MPEG1��
	SDK_CAPTURE_COMP_H263,			///< H.263
	SDK_CAPTURE_COMP_MJPG,			///< MJPG
	SDK_CAPTURE_COMP_FCC_MPEG4,		///< FCC MPEG4
	SDK_CAPTURE_COMP_H264,			///< H.264
	SDK_CAPTURE_COMP_H265,
	SDK_CAPTURE_COMPRESS_H265_S,		///< H.265+  //add by barney 2017/08/28
	SDK_CAPTURE_COMP_NR				///< ö�ٵ�ѹ����׼��Ŀ��
};

/// ����ͨ������
enum SDK_CAPTURE_CHANNEL_t {
	SDK_CHL_MAIN_T = 0,		///< ��ͨ��	��	������1 
	SDK_CHL_2END_T = 1,		///< ��ͨ��	��	��������2 
	SDK_CHL_3IRD_T = 2,		///< ��ͨ��	��	��������3 
	SDK_CHL_4RTH_T = 3,		///< ��ͨ��	��	��������4 
	SDK_CHL_JPEG_T = 4,		///< ��ͨ��	��	��JPEGץͼ 
	SDK_CHL_FUNCTION_NUM
};
/// ��Ƶ��������
enum SDK_AudioEncodeTypes
{
	SDK_AUDIO_ENCODE_NONE = 0,
	SDK_AUDIO_ENCODE_G729_8KBIT,
	SDK_AUDIO_ENCODE_G726_16KBIT,
	SDK_AUDIO_ENCODE_G726_24KBIT,
	SDK_AUDIO_ENCODE_G726_32KBIT,
	SDK_AUDIO_ENCODE_G726_40KBIT,
	SDK_AUDIO_ENCODE_PCM_8TO16BIT,
	SDK_AUDIO_ENCODE_PCM_ALAW,
	SDK_AUDIO_ENCODE_PCM_ULAW,
	SDK_AUDIO_ENCODE_ADPCM8K16BIT,
	SDK_AUDIO_ENCODE_ADPCM16K16BIT,
	SDK_AUDIO_ENCODE_G711_ALAW,
	SDK_AUDIO_ENCODE_MPEG2_LAYER1,
	SDK_AUDIO_ENCODE_AMR8K16BIT,
	SDK_AUDIO_ENCODE_G711_ULAW,
	SDK_AUDIO_ENCODE_IMA_ADPCM_8K16BIT,
	SDK_AUDIO_ENCODE_TYPES_NR,
};

typedef enum _SDK_CONFIG_TYPE
{
	E_SDK_CONFIG_NOTHING = 0,			//
	E_SDK_CONFIG_USER,					//�û���Ϣ��������Ȩ���б��û��б�����б�	��Ӧ�ṹ��USER_MANAGE_INFO
	E_SDK_CONFIG_ADD_USER,				//�����û�										��Ӧ�ṹ��USER_INFO
	E_SDK_CONFIG_MODIFY_USER,			//�޸��û�										��Ӧ�ṹ��CONF_MODIFYUSER
	E_SDK_CONFIG_DELETE_USER,			//ɾ���û�										��Ӧ�ṹ��USER_INFO
	E_SDK_CONFIG_ADD_GROUP,				//������										��Ӧ�ṹ��USER_GROUP_INFO
	E_SDK_CONFIG_MODIFY_GROUP,			//�޸���										��Ӧ�ṹ��CONF_MODIFYGROUP
	E_SDK_COFIG_DELETE_GROUP,			//ɾ����										��Ӧ�ṹ��USER_GROUP_INFO
	E_SDK_CONFIG_MODIFY_PSW,			//�޸�����										��Ӧ�ṹ��_CONF_MODIFY_PSW

	E_SDK_CONFIG_ABILITY_SYSFUNC = 9,	//֧�ֵ����繦��								��Ӧ�ṹ��SDK_SystemFunction
	E_SDK_CONFIG_ABILTY_ENCODE,			//���Ȼ�ñ�������								��Ӧ�ṹ��CONFIG_EncodeAbility
	E_SDK_CONFIG_ABILITY_PTZPRO,		//��̨Э��										��Ӧ�ṹ��SDK_PTZPROTOCOLFUNC
	E_SDK_COMFIG_ABILITY_COMMPRO,		//����Э��										��Ӧ�ṹ��SDK_COMMFUNC

	E_SDK_CONFIG_ABILITY_MOTION_FUNC,	//��̬����									��Ӧ�ṹ��SDK_MotionDetectFunction
	E_SDK_CONFIG_ABILITY_BLIND_FUNC,	//��Ƶ�ڵ���									��Ӧ�ṹ��SDK_BlindDetectFunction
	E_SDK_CONFIG_ABILITY_DDNS_SERVER,	//DDNS����֧������								��Ӧ�ṹ��SDK_DDNSServiceFunction
	E_SDK_CONFIG_ABILITY_TALK,			//�Խ���������									��Ӧ�ṹ��SDK_DDNSServiceFunction


	E_SDK_CONFIG_SYSINFO = 17,			//ϵͳ��Ϣ										��Ӧ�ṹ��VideoNet_DEVICEINFO
	E_SDK_CONFIG_SYSNORMAL,				//��ͨ����										��Ӧ�ṹ��SDK_CONFIG_NORMAL
	E_SDK_CONFIG_SYSENCODE,				//��������										��Ӧ�ṹ��SDK_EncodeConfigAll_SIMPLIIFY
	E_SDK_CONFIG_SYSNET,				//��������										��Ӧ�ṹ��SDK_CONFIG_NET_COMMON
	E_SDK_CONFIG_PTZ,					//��̨ҳ��										��Ӧ�ṹ��SDK_STR_PTZCONFIG_ALL
	E_SDK_CONFIG_COMM,					//����ҳ��										��Ӧ�ṹ��SDK_CommConfigAll
	E_SDK_CONFIG_RECORD,				//¼�����ý���									��Ӧ�ṹ��SDK_RECORDCONFIG
	E_SDK_CONFIG_MOTION,				//��̬���ҳ��									��Ӧ�ṹ��SDK_MOTIONCONFIG
	E_SDK_CONFIG_SHELTER,				//��Ƶ�ڵ�										��Ӧ�ṹ��SDK_BLINDDETECTCONFIG
	E_SDK_CONFIG_VIDEO_LOSS,			//��Ƶ��ʧ,										��Ӧ�ṹ��SDK_VIDEOLOSSCONFIG
	E_SDK_CONFIG_ALARM_IN,				//��������										��Ӧ�ṹ��SDK_ALARM_INPUTCONFIG
	E_SDK_CONFIG_ALARM_OUT,				//�������										��Ӧ�ṹ��SDK_AlarmOutConfigAll
	E_SDK_CONFIG_DISK_MANAGER,			//Ӳ�̹������									��Ӧ�ṹ��SDK_StorageDeviceControl
	E_SDK_CONFIG_OUT_MODE,				//���ģʽ����    								��Ӧ�ṹ��SDK_VideoWidgetConfi
	E_SDK_CONFIG_CHANNEL_NAME,			//ͨ������										��Ӧ�ṹ��SDK_ChannelNameConfigAll
	E_SDK_CONFIG_AUTO,					//�Զ�ά����������								��Ӧ�ṹ��SDK_AutoMaintainConfig
	E_SDK_CONFIG_DEFAULT,				//�ָ�Ĭ�Ͻ�������								��Ӧ�ṹ��SDK_SetDefaultConfigTypes
	E_SDK_CONFIG_DISK_INFO,				//Ӳ����Ϣ										��Ӧ�ṹ��SDK_StorageDeviceInformationAll
	E_SDK_CONFIG_LOG_INFO,				//��ѯ��־										��Ӧ�ṹ��SDK_LogList
	E_SDK_CONFIG_NET_IPFILTER,			//����������									��Ӧ�ṹ��SDK_NetIPFilterConfig
	E_SDK_CONFIG_NET_DHCP,				//DHC����										��Ӧ�ṹ��SDK_NetDHCPConfigAll
	E_SDK_CONFIG_NET_DDNS,				//DDNS��Ϣ										��Ӧ�ṹ��SDK_NetDDNSConfigALL
	E_SDK_CONFIG_NET_EMAIL,				//EMAIL											��Ӧ�ṹ��SDK_NetEmailConfig
	E_SDK_CONFIG_NET_MULTICAST,			//�鲥											��Ӧ�ṹ��SDK_NetMultiCastConfig
	E_SDK_CONFIG_NET_NTP,				//NTP											��Ӧ�ṹ��SDK_NetNTPConfig
	E_SDK_CONFIG_NET_PPPOE,				//PPPOE											��Ӧ�ṹ��SDK_NetPPPoEConfig
	E_SDK_CONFIG_NET_DNS,				//DNS											��Ӧ�ṹ��SDK_NetDNSConfig
	E_SDK_CONFIG_NET_FTPSERVER,			//FTP											��Ӧ�ṹ��SDK_FtpServerConfig

	E_SDK_CONFIG_SYS_TIME,				//ϵͳʱ��										��Ӧ�ṹ��SDK_SYSTEM_TIME
	E_SDK_CONFIG_CLEAR_LOG,				//�����־													
	E_SDK_REBOOT_DEV,					//���������豸													
	E_SDK_CONFIG_ABILITY_LANG,			//֧������									    ��Ӧ�ṹ��SDK_MultiLangFunction
	E_SDK_CONFIG_VIDEO_FORMAT,																	
	E_SDK_CONFIG_COMBINEENCODE,			//��ϱ���										��Ӧ�ṹ��SDK_CombineEncodeConfigAll
	E_SDK_CONFIG_EXPORT,				//���õ���														
	E_SDK_CONFIG_IMPORT,				//���õ���
	E_SDK_LOG_EXPORT,					//��־����														
	E_SDK_CONFIG_COMBINEENCODEMODE,		//��ϱ���ģʽ									��Ӧ�ṹ��SDK_CombEncodeModeAll
	E_SDK_WORK_STATE,					//����״̬																
	E_SDK_ABILITY_LANGLIST,				//ʵ��֧�ֵ����Լ�									
	E_SDK_CONFIG_NET_ARSP,				//ARSP											��Ӧ�ṹ��SDK_NetARSPConfigAll
	E_SDK_CONFIG_SNAP_STORAGE,			//												��Ӧ�ṹ��SDK_SnapshotConfig
	E_SDK_CONFIG_NET_3G,				//3G����										��Ӧ�ṹ��SDK_Net3GConfig
	E_SDK_CONFIG_NET_MOBILE,			//�ֻ����										��Ӧ�ṹ��SDK_NetMoblieConfig
	E_SDK_CONFIG_UPGRADEINFO,			//��ȡ������Ϣ									���� �ļ���
	E_SDK_CONFIG_NET_DECODER,
	E_SDK_ABILITY_VSTD,					//ʵ��֧�ֵ���Ƶ��ʽ
	E_SDK_CONFIG_ABILITY_VSTD,			//֧����Ƶ��ʽ									��Ӧ�ṹ��SDK_MultiVstd
	E_SDK_CONFIG_NET_UPNP,				//UPUN����										��Ӧ�ṹ��SDK_NetUPNPConfig
	E_SDK_CONFIG_NET_WIFI,				//WIFI											��Ӧ�ṹ��SDK_NetWifiConfig
	E_SDK_CONFIG_NET_WIFI_AP_LIST,		//												��Ӧ�ṹ��SDK_NetWifiDeviceAll
	E_SDK_CONFIG_SYSENCODE_SIMPLIIFY,	//�򻯵ı�������								��Ӧ�ṹ��SDK_EncodeConfigAll_SIMPLIIFY
	E_SDK_CONFIG_ALARM_CENTER,			//�澯����										��Ӧ�ṹ��SDK_NetAlarmServerConfigAll
	E_SDK_CONFIG_NET_ALARM,																			
	E_SDK_CONFIG_NET_MEGA,				//���Ż�ͨ
	E_SDK_CONFIG_NET_XINGWANG,			//����
	E_SDK_CONFIG_NET_SHISOU,			//����
	E_SDK_CONFIG_NET_VVEYE,				//VVEYE
	E_SDK_CONFIG_NET_PHONEMSG,			//����											��Ӧ�ṹ��SDK_NetShortMsgCfg
	E_SDK_CONFIG_NET_PHONEMEDIAMSG,		//����											��Ӧ�ṹ��SDK_NetMultimediaMsgCfg
	E_SDK_VIDEO_PREVIEW,
	E_SDK_CONFIG_NET_DECODER_V2,
	E_SDK_CONFIG_NET_DECODER_V3,		//����ͨ��										��Ӧ�ṹ��SDK_NetDigitChnConfig
	E_SDK_CONFIG_ABILITY_SERIALNO,		//���к�
	E_SDK_CONFIG_NET_RTSP,				//RTSP											��Ӧ�ṹ��SDK_NetRTSPConfig
	E_SDK_GUISET,						//GUISET										��Ӧ�ṹ��SDK_GUISetConfig
	E_SDK_CATCHPIC,						//ץͼ												
	E_SDK_VIDEOCOLOR,					//��Ƶ��ɫ����
	E_SDK_CONFIG_COMM485,				//												��Ӧ�ṹ��SDK_STR_RS485CONFIG_ALL
	E_SDK_COMFIG_ABILITY_COMMPRO485,	//����485										��Ӧ�ṹ��SDK_COMMFUNC
	E_SDK_CONFIG_SYS_TIME_NORTC,		//ϵͳʱ��noRtc									��Ӧ�ṹ��SDK_COMMFUNC
	E_SDK_CONFIG_REMOTECHANNEL,			//Զ��ͨ��										��Ӧ�ṹ��SDK_CONFIG_NET_COMMON
	E_SDK_CONFIG_OPENTRANSCOMCHANNEL ,	//��͸������									��Ӧ�ṹ��TransComChannel
	E_SDK_CONFIG_CLOSETRANSCOMCHANNEL,  //�ر�͸������
	E_SDK_CONFIG_SERIALWIRTE,			//д��͸��������Ϣ
	E_SDK_CONFIG_SERIALREAD,			//��ȡ͸��������Ϣ
	E_SDK_CONFIG_CHANNELTILE_DOT,		//������Ϣ
	E_SDK_CONFIG_CAMERA,				//���������									��Ӧ�ṹ��SDK_CameraParam
	E_SDK_CONFIG_ABILITY_CAMERA,		//�ع�������									��Ӧ�ṹ��SDK_CameraAbility
	E_SDK_CONFIG_BUGINFO,				//�������													
	E_SDK_CONFIG_STORAGENOTEXIST,		//Ӳ�̲�����									��Ӧ�ṹ��SDK_VIDEOLOSSCONFIG
	E_SDK_CONFIG_STORAGELOWSPACE,		//Ӳ����������									��Ӧ�ṹ��SDK_StorageLowSpaceConfig
	E_SDK_CONFIG_STORAGEFAILURE,		//Ӳ�̳���										��Ӧ�ṹ��SDK_VIDEOLOSSCONFIG
	E_SDK_CFG_NETIPCONFLICT,			//IP��ͻ										��Ӧ�ṹ��SDK_VIDEOLOSSCONFIG
	E_SDK_CFG_NETABORT,					//�����쳣										��Ӧ�ṹ��SDK_VIDEOLOSSCONFIG

	E_SDK_CONFIG_CHNSTATUS,				//ͨ��״̬										��Ӧ�ṹ��SDK_NetDecorderChnStatusAll
	E_SDK_CONFIG_CHNMODE,				//ͨ��ģʽ										��Ӧ�ṹ��SDK_NetDecorderChnModeConfig

	E_SDK_CONFIG_NET_DAS,				//����ע��										��Ӧ�ṹ��SDK_DASSerInfo
	E_SDK_CONFIG_CAR_INPUT_EXCHANGE,	//�ⲿ��Ϣ�����복��״̬�Ķ�Ӧ��ϵ			
	E_SDK_CONFIG_DELAY_TIME,			//����ϵͳ��ʱ����
	E_SDK_CONFIG_NET_ORDER,				//�������ȼ�
	E_SDK_CONFIG_ABILITY_NETORDER ,		//�������ȼ���������
	E_SDK_CONFIG_CARPLATE,				//���ƺ�����	
	E_SDK_CONFIG_LOCALSDK_NET_PLATFORM, //����ƽ̨��Ϣ����								��ӦSDK_LocalSdkNetPlatformConfig
	E_SDK_CONFIG_GPS_TIMING,			//GPSУʱ�������								��ӦSDK_GPSTimingConfig
	E_SDK_CONFIG_VIDEO_ANALYZE,			//��Ƶ����(����DVR)                             ��ӦSDK_RULECONFIG
	E_SDK_CONFIG_GODEYE_ALARM,			//���۽Ӿ�����ϵͳ								��ӦSDK_GodEyeConfig
	E_SDK_CONFIG_NAT_STATUS_INFO,		//nat״̬��Ϣ									��ӦSDK_NatStatusInfo
	E_SDK_CONFIG_BUGINFOSAVE,			//�������(����)									 
	E_SDK_CONFIG_MEDIA_WATERMARK,		//ˮӡ����										��ӦSDK_WaterMarkConfigAll
	E_SDK_CONFIG_ENCODE_STATICPARAM,	//��������̬����						        ��ӦSDK_EncodeStaticParamAll
	E_SDK_CONFIG_LOSS_SHOW_STR,			//��Ƶ��ʧ��ʾ�ַ���
	E_SDK_CONFIG_DIGMANAGER_SHOW,		//ͨ��������ʾ����                              ��ӦSDK_DigManagerShowStatus
	E_SDK_CONFIG_ABILITY_ANALYZEABILITY, //���ܷ�������									��ӦSDK_ANALYZEABILITY
	E_SDK_CONFIG_VIDEOOUT_PRIORITY,		//��ʾHDMI VGA���ȼ�������
	E_SDK_CONFIG_NAT,		  			//NAT���ܣ�MTUֵ����                            ��ӦSDK_NatConfig
	E_SDK_CONFIG_CPCINFO,				//����CPC����������Ϣ                           ��ӦSDK_CPCDataAll
	E_SDK_CONFIG_STORAGE_POSITION,      //¼��洢�豸���ͣ�                            ��Ӧ SDK_RecordStorageType
	E_SDK_CONFIG_ABILITY_CARSTATUSNUM,  //����״̬��									��Ӧ SDK_CarStatusNum
	E_SDK_CFG_VPN,						//VPN											��ӦSDK_VPNConfig
	E_SDK_CFG_VIDEOOUT,					//VGA��Ƶ�ֱ���									��ӦSDK_VGAresolution
	E_SDK_CFG_ABILITY_VGARESOLUTION,    //֧�ֵ�VGA�ֱ����б�							��ӦSDK_VGAResolutionAbility
	E_SDK_CFG_NET_LOCALSEARCH,          //�����豸���豸�˵ľ������豸					��ӦSDK_NetDevList
	E_SDK_CFG_NETPLAT_KAINENG,			// 												SDK_CONFIG_KAINENG_INFO
	E_SDK_CFG_ENCODE_STATICPARAM_V2,	//DVR��������̬����                             SDK_EncodeStaticParamV2
	E_SDK_ABILITY_ENC_STATICPARAM,		//��̬���������� DVR							SDK_EncStaticParamAbility (����)
	E_SDK_CFG_C7_PLATFORM,				//												SDK_C7PlatformConfig
	E_SDK_CFG_MAIL_TEST,				////�ʼ�����                                    SDK_NetEmailConfig
	E_SDK_CFG_NET_KEYBOARD,				//������̷���                                  SDK_NetKeyboardConfig
	E_SDK_ABILITY_NET_KEYBOARD,			//�������Э��									SDK_NetKeyboardAbility  
	E_SDK_CFG_SPVMN_PLATFORM,			//28181Э������		                            SDK_ASB_NET_VSP_CONFIG	
	E_SDK_CFG_PMS,						//�ֻ�����                                      SDK_PMSConfig
	E_SDK_CFG_OSD_INFO,					//��Ļ��ʾ��Ϣ                                  SDK_OSDInfoConfigAll
	E_SDK_CFG_KAICONG,					//                                              SDK_KaiCongAlarmConfig
	E_SDK_CFG_DIGITAL_REAL,				//����֧�ֵ�ͨ��ģʽ				            SDK_VideoChannelManage
	E_SDK_ABILITY_PTZCONTROL,			//PTZ����������                                 SDK_PTZControlAbility
	E_SDK_CFG_XMHEARTBEAT,				//												SDK_XMHeartbeatConfig
	E_SDK_CFG_MONITOR_PLATFORM,			//												SDK_MonitorPlatformConfig
	E_SDK_CFG_PARAM_EX,					//����ͷ��չ����                                SDK_CameraParamEx
	E_SDK_CFG_NETPLAT_ANJU_P2P,			//����P2P										SDK_NetPlatformCommonCfg  
	E_SDK_GPS_STATUS,					///< GPS������Ϣ								SDK_GPSStatusInfo 
	E_SDK_WIFI_STATUS,					///< Wifi������Ϣ								SDK_WifiStatusInfo
	E_SDK_3G_STATUS,					///< 3G������Ϣ									SDK_WirelessStatusInfo
	E_SDK_DAS_STATUS,					///< ����ע��״̬								SDK_DASStatusInfo 
	E_SDK_ABILITY_DECODE_DELEY,			//�����������									SDK_DecodeDeleyTimePrame
	E_SDK_CFG_DECODE_PARAM,				//���������ʱ									SDK_DecodeParam
	E_SDK_CFG_VIDEOCOLOR_CUSTOM,        //												SDK_VIDEOCOLOR_PARAM_CUSTOM
	E_SDK_ABILITY_ONVIF_SUB_PROTOCOL,	//onvif��Э��									SDK_AbilityMask   
	E_SDK_CONFIG_EXPORT_V2,				//�����豸Ĭ�����ã�������������
	E_SDK_CFG_CAR_BOOT_TYPE,			//���ؿ��ػ�ģʽ								SDK_CarBootTypeConfig
	E_SDK_CFG_IPC_ALARM,				//IPC���籨��									SDK_IPCAlarmConfigAll
	E_SDK_CFG_NETPLAT_TUTK_IOTC,		//TUTK IOTCƽ̨����								SDK_NetPlatformCommonCfg
	E_SDK_CFG_BAIDU_CLOUD,				//baidu��   SDK_BaiduCloudCfg

	
	E_SDK_CFG_SMARTDETECTION_CODEC,			//���ܱ���		
	E_SDK_CFG_SMARTDETECTION_DETECT,		//���ܼ��		
	E_SDK_CFG_SMARTDETECTION_CONTROL,		//���ܿ���		
	E_SDK_CFG_SMARTDETECTION_LUMINANCE,		//�������		
	E_SDK_CFG_SMARTDETECTION_MOVE,			//�ƶ����		
	E_SDK_CFG_SMARTDETECTION_OCCLUSION,		//�ڵ����		
	E_SDK_CFG_SMARTDETECTION_CROSSLINE,		//���⾯����	
	E_SDK_CFG_SMARTDETECTION_CROSSAREA,		//��������		
	E_SDK_CFG_SMARTDETECTION_COLOR,			//��ɫ			
	E_SDK_CFG_SMARTDETECTION_SOUND,			//����			
	E_SDK_CFG_SMARTDETECTION_LOSEOBJ,		//��ƷԤ��		
	

	E_SDK_CFG_CALIBRATION_GET_CAMERA_PARAMETER,			//��ȡ������Ƿ��Ѿ��궨		
	E_SDK_CFG_CALIBRATION_SET_SUBCAMERA_CONNECTINFO,	//���ôӻ���¼��Ϣ				
	E_SDK_CFG_CALIBRATION_SET_POINTS,					//���ñ궨����(����ɾ��3D)		
	E_SDK_CFG_CALIBRATION_ACTION,						//���ñ궨����ʼ����ɣ�		  
	E_SDK_CFG_CALIBRATION_MODE,							//�궨ģʽ						
	E_SDK_CFG_CALIBRATION_ZOOMTIMES,					//�䱶ϵ��						
	E_SDK_CFG_CALIBRATION_PTZINFO,						//PTZ����
	E_SDK_CFG_CALIBRATION_PANOTYPE,						//��ȡȫ�����������	
	
	E_SDK_CFG_CALIBRATION_SETINFO_YW,					//����					SDK_MS_Calibrate_Point    
	E_SDK_CFG_CALIBRATION_RESULT_YW,					//���	 Result			SDK_MS_ANALY_POINT		
	E_SDK_CFG_CALIBRATION_ENCRYPT,

	E_SDK_CFG_CALIBRATION_NAMING,						//���������ã�ֻ���ã�������


	E_SDK_CFG_FACECOMPARE_RESULT_ALARM,					//�ԱȽ������					

	E_SDK_CFG_SMARTFACE_COMMON_PARAMETER,				//����ʶ�����	ץ�Ĳ���SDK_FA_SNAP_FACE_CONFIG				
	E_SDK_CFG_SMARTFACE_AREADETECTION,					//����ʶ���������	
	E_SDK_CFG_SMARTFACE_AREASHIELDED,					//������������
	E_SDK_CFG_SMARTFACE_VERSION,						//ʶ���㷨�汾��				
	E_SDK_CFG_SMARTFACE_ALARM,							//����������������	

	E_SDK_CFG_LINKAGE_BIND,								//ȫ��������
	E_SDK_CFG_CUSTOMIZED_QT,							//����-��ɳȫͼ
	E_SDK_CFG_OSD,										//��Ӧ�ṹ��SDK_OSD_SWITCH_S;
	E_SDK_CFG_SMART,									//��Ӧ�ṹ��SDK_SMART_FRAME_DROP_S
	E_SDK_CFG_EXPOSURE,									//��Ӧ�ṹ��SDK_EXPOSURE_MS_PARAM_S

	E_SDK_CFG_FORMAT,									//��ʽ��SD����Ӧ�ṹ��SDK_FORMAT_PARAM_S

	E_SDK_CFG_EXPOSURE_MUIT,							//�ಥ��ַ����,��Ӧ�ṹ��SDK_EXPOSURE_MUIT
	E_SDK_CFG_AWBAUTO_MODE,								//��ƽ������,��Ӧ�ṹ��SDK_AWBAUTO_MODE
	E_SDK_CFG_NET_HTTPSERVER,							//HTTP��Ӧ�ṹ��SDK_HTTPSERVERCONFIG
	E_SDK_CFG_FACE_CAPTURE_MODE,						//����ģʽѡ�񣬶�Ӧ�ṹ��SDK_FACE_CAPTURE_MODE
	
	E_SDK_NVR_SEARCH_FILE,								//ƴ�ӽ���������¼���Ӧ�ṹ��ΪSDK_SYSTEM_TIME
	E_SDK_NVR_REALPLAY,									//ƴ�ӽ���������ʵʱ��Ƶ	SDK_SYSTEM_TIME
	E_SDK_NVR_REPLAY,									//ƴ�ӽ������ط�¼��	SDK_SYSTEM_TIME
}SDK_CONFIG_TYPE;

/// �����¼���
enum SDK_EventCodeTypes
{
	SDK_EVENT_CODE_INIT = 0,
	SDK_EVENT_CODE_LOCAL_ALARM = 1,	//���ر���
	SDK_EVENT_CODE_NET_ALARM,		//���籨��
	SDK_EVENT_CODE_MANUAL_ALARM,	//�ֶ�����
	SDK_EVENT_CODE_VIDEO_MOTION,	//��̬���
	SDK_EVENT_CODE_VIDEO_LOSS,		//��Ƶ��ʧ
	SDK_EVENT_CODE_VIDEO_BLIND,		//��Ƶ�ڵ�
	SDK_EVENT_CODE_VIDEO_TITLE,		
	SDK_EVENT_CODE_VIDEO_SPLIT,
	SDK_EVENT_CODE_VIDEO_TOUR,
	SDK_EVENT_CODE_STORAGE_NOT_EXIST,//�洢�豸������
	SDK_EVENT_CODE_STORAGE_FAILURE,//�洢�豸����ʧ��
	SDK_EVENT_CODE_LOW_SPACE,		//�洢�豸��������
	SDK_EVENT_CODE_NET_ABORT,
	SDK_EVENT_CODE_COMM,
	SDK_EVENT_CODE_STORAGE_READ_ERROR,//�洢�豸������
	SDK_EVENT_CODE_STORAGE_WRITE_ERROR,//�洢�豸д����
	SDK_EVENT_CODE_NET_IPCONFLICT,	//ip��ͻ
	SDK_EVENT_CODE_ALARM_EMERGENCY,
	SDK_EVENT_CODE_DEC_CONNECT,	
	SDK_EventUpgrade,
	SDK_EventBackup,
	SDK_EventShutdown,
	SDK_EventReboot,
	SDK_EventNewFile,
	SDK_EVENT_CODE_VideoAnalyze=25,	
	SDK_EventIPCAlarm,
	SDK_EventSpeedAlarm,
	SDK_EventGSensorAlarm,
	SDK_EventLoginFailed,
	SDK_EventSerialAlarm,
	SDK_EventConsSensorAlarm, //�������Ʒ�󶨵��ⲿ�豸����
	SDK_EventBrightness,
	SDK_EventShelter,
	SDK_EventCrossLine,
	SDK_EventCrossArea,
	SDK_EventColor,
	SDK_EventSound,
	SDK_EventLoseOBJ,

	SDK_EVENT_CODE_LUMA_WARNNING,		//���ȱ���
	SDK_EVENT_CODE_OD_WARNNING,		//�ڵ�����
	SDK_EVENT_CODE_CROSSLINE_WARNNING,		//���⾯���߱���
	SDK_EVENT_CODE_CROSSAREA_WARNNING,		//�������ֱ���
	SDK_EVENT_CODE_COLOR_WARNNING,		//��ɫ��ⱨ��
	SDK_EVENT_CODE_SOUND_WARNNING,		//������ⱨ��
	SDK_EVENT_CODE_LOSEOBJ_WARNNING,		//����������ⱨ��

	SDK_EVENT_CODE_SMARTFACE_BLACKLIST,
	SDK_EVENT_CODE_SMARTFACE_WHITELIST,
	SDK_EVENT_CODE_SMARTFACE_VIPLIST,
	SDK_EVENT_CODE_SMARTFACE_NONWHITELIST,//49

	SDK_EVENT_CODE_NR,
};
//! �������õ�����
enum SDK_ENCODE_TYPE_BY_RECORD
{
	SDK_ENCODE_TYPE_TIM = 0,
	SDK_ENCODE_TYPE_MTD = 1,
	SDK_ENCODE_TYPE_ALM = 2,
	SDK_ENCODE_TYPE_NUM = 3,
	SDK_ENCODE_TYPE_SNAP_TIMER = 0,
	SDK_ENCODE_TYPE_SNAP_TRIGGER = 1,
};
#define SDK_EXTRATYPES 3 //����������

//���紫�����
enum SDK_TransferPolicy
{
	SDK_TRANSFER_POLICY_AUTO,		///< ����Ӧ
	SDK_TRANSFER_POLICY_QUALITY,	///< ��������
	SDK_TRANSFER_POLICY_FLUENCY,	///< ��������
	SDK_TRANSFER_POLICY_TRANSMISSION,//< ��������
	SDK_TRANSFER_POLICY_NR,
};



typedef struct {
	int left;
	int top;
	int right;
	int bottom;
}sdkRect;

/// ��Ƶ�����ʽ�������Խ���
struct SDK_AudioInFormatConfig
{
	int iBitRate;	   ///< ������С��kbpsΪ��λ������192kbps��128kbps
	int iSampleRate;   ///< �����ʣ�HzΪ��λ������44100Hz
	int iSampleBit;    ///< ������λ��
	int iEncodeType;   ///< ���뷽ʽ������AudioEncodeTypes����
};

//�����Խ���ʽ
typedef enum __TALK_CODING_TYPE
{
	TALK_DEFAULT = 0,
	TALK_PCM = 1,					//PCM
	TALK_G711a,						//G711a
	TALK_AMR,						//AMR
	TALK_G711u,						//G711u
	TALK_G726,						//G726
}TALK_CODING_TYPE;
//�����Խ�
typedef struct  
{
	TALK_CODING_TYPE		encodeType;		//��������
	int						nAudioBit;		//��ʵ�ʵ�ֵ��ʾ����8λ ����ֵΪ8
	unsigned int			dwSampleRate;	//�����ʣ���16k ����ֵΪ16000
	char					reserved[64];
}VIDEONET_TALKDECODE_INFO;


/// ϵͳʱ��ṹ
typedef struct SDK_SYSTEM_TIME{
	int  year;///< �ꡣ   
	int  month;///< �£�January = 1, February = 2, and so on.   
	int  day;///< �ա�   
	int  wday;///< ���ڣ�Sunday = 0, Monday = 1, and so on   
	int  hour;///< ʱ��   
	int  minute;///< �֡�   
	int  second;///< �롣   
	int  isdst;///< ����ʱ��ʶ��   
}SDK_SYSTEM_TIME;

//¼��������ؽṹ��
typedef struct tagSDK_TIMESECTION
{
	//!ʹ��
	int enable;
	//!��ʼʱ��:Сʱ
	int startHour;
	//!��ʼʱ��:����
	int	startMinute;
	//!��ʼʱ��:����
	int	startSecond;
	//!����ʱ��:Сʱ
	int	endHour;
	//!����ʱ��:����
	int	endMinute;
	//!����ʱ��:����
	int	endSecond;
}SDK_TIMESECTION;	

typedef struct{
	int dwYear;		//��
	int dwMonth;	//��
	int dwDay;		//��
	int dwHour;		//ʱ
	int dwMinute;	//��
	int dwSecond;	//��
}VIDEONET_TIME,*LPVIDEONET_TIME;

//ʱ��ṹ
typedef struct _NEW_NET_TIME								
{
	unsigned int second			:6;					//	��	1-60		
	unsigned int minute			:6;					//	��	1-60		
	unsigned int hour			:5;					//	ʱ	1-24		
	unsigned int day			:5;					//	��	1-31		
	unsigned int month			:4;					//	��	1-12		
	unsigned int year			:6;					//	��	2000-2063	
}NEW_NET_TIME, *LPNET_TIME;
///< ����ʱ�ṹ
struct DSTPoint
{
	int	iYear;
	int	iMonth;
	int	iWeek;		///<��1:first  to2 3 4 -1:last one   0:��ʾʹ�ð��ռ���ķ���[-1,4]
	int	iWeekDay;	///<weekday from sunday=0	[0, 6]
	int Hour;
	int Minute;
};

struct SDK_VIDEO_FORMAT
{
	int		iCompression;			//  ѹ��ģʽ 	
	int		iResolution;			//  �ֱ��� ����ö��SDK_CAPTURE_SIZE_t
	int		iBitRateControl;		//  �������� ����ö��SDK_capture_brc_t
	int		iQuality;				//  �����Ļ��� ����1-6		
	int		nFPS;					//  ֡��ֵ��NTSC/PAL������,������ʾ����һ֡		
	int		nBitRate;				//  0-4096k,���б���Ҫ�ɿͻ��˱��棬�豸ֻ����ʵ�ʵ�����ֵ�������±ꡣ
	int		iGOP;					//  ��������I֮֡��ļ��ʱ�䣬2-12 
} ;
struct  SDK_AUDIO_FORMAT
{
	int		nBitRate;				//  ����kbps	
	int		nFrequency;				//  ����Ƶ��	
	int		nMaxVolume;				//  ���������ֵ
} ;
// ý���ʽ
struct SDK_MEDIA_FORMAT
{
	SDK_VIDEO_FORMAT vfFormat;			//  ��Ƶ��ʽ���� 			
	SDK_AUDIO_FORMAT afFormat;			//  ��Ƶ��ʽ���� 
	bool	bVideoEnable;				//  ������Ƶ���� 
	bool	bAudioEnable;				//  ������Ƶ���� 	
} ;

typedef union {	//IP addr
	unsigned char	c[4];
	unsigned short	s[2];
	unsigned int 	l;
}CONFIG_IPAddress;

///////////////////�û��ʺŹ�����ؽṹ��/////////////////////////////////
typedef struct _OPR_RIGHT
{
	char name[NET_MAX_USER_LENGTH];
}OPR_RIGHT;

typedef struct _USER_INFO
{
	int			rigthNum;
	char		rights[NET_MAX_RIGTH_NUM][NET_MAX_USER_LENGTH];
	char		Groupname[NET_MAX_USER_LENGTH];
	char		memo[NET_MAX_USER_LENGTH];
	char		name[NET_MAX_USER_LENGTH];
	char		passWord[NET_MAX_USER_LENGTH];
	bool		reserved;		//�Ƿ���
	bool		shareable;		//���û��Ƿ������� 1-���ã�0-������
}USER_INFO_JL;

typedef struct _USER_GROUP_INFO
{
	int			rigthNum;
	char		memo[NET_MAX_USER_LENGTH]; 
	char		name[NET_MAX_USER_LENGTH];
	char		rights[NET_MAX_RIGTH_NUM][NET_MAX_USER_LENGTH];	//Ȩ���б�
}USER_GROUP_INFO;

//�û���Ϣ���ýṹ
typedef struct _USER_MANAGE_INFO
{
	int					rigthNum;
	OPR_RIGHT			rightList[NET_MAX_RIGTH_NUM];
	int					groupNum;
	USER_GROUP_INFO		groupList[NET_MAX_GROUP_NUM];
	int					userNum;
	USER_INFO_JL			userList[NET_MAX_USER_NUM];
}USER_MANAGE_INFO;

//�޸��û�
typedef struct _CONF_MODIFYUSER
{
	char UserName[NET_MAX_USER_LENGTH];
	USER_INFO_JL User;
}CONF_MODIFYUSER;

//�޸���
typedef struct _CONF_MODIFYGROUP
{
	char GroupName[NET_MAX_USER_LENGTH];
	USER_GROUP_INFO Group;
}CONF_MODIFYGROUP;


/// �޸��û���������
struct _CONF_MODIFY_PSW
{
	char sUserName[NET_MAX_USER_LENGTH];
	char Password[NET_MAX_USER_LENGTH];
	char NewPassword[NET_MAX_USER_LENGTH];
};

//��ͨ����ҳ�ṹ��
typedef struct _SDK_CONFIG_NORMAL
{	
	SDK_SYSTEM_TIME sysTime;		//ϵͳʱ��

	int iLocalNo;			/*!< �������:[0, 998] */
	int iOverWrite;			/*!< Ӳ����ʱ���� "OverWrite", "StopRecord" */		
	int iSnapInterval;			///< ��ʱץͼ��ʱ����������Ϊ��λ 
	char sMachineName[64];	///< ������
	int iVideoStartOutPut;	/*!< ���ģʽ */
	int iAutoLogout;			///< ���ز˵��Զ�ע��(����)	[0, 120]

	int iVideoFormat;		/*!< ��Ƶ��ʽ:��PAL��, ��NTSC��, ��SECAM�� */
	int iLanguage;			/*!< ����ѡ��:��English��, ��SimpChinese��, ��TradChinese��, ��Italian��, ��Spanish��, ��Japanese��, ��Russian��, ��French��, ��German�� */	
	int iDateFormat;		/*!< ���ڸ�ʽ:��YYMMDD��, ��MMDDYY��, ��DDMMYY�� */
	int iDateSeparator;		/*!< ���ڷָ��:��.��, ��-��, ��/�� */
	int iTimeFormat;		/*!< ʱ���ʽ:��12��, ��24�� */
	int iDSTRule;			///< ����ʱ���� 
	int iWorkDay;			///< ������
	DSTPoint dDSTStart;
	DSTPoint dDSTEnd;
}SDK_CONFIG_NORMAL;



//osd��������
typedef struct OSD_SWITCH_S
{
	DWORD			title0;	//����0					
	DWORD			title1;	//����1						
	DWORD			title2;	//����2				
	DWORD			title3;	 //����3	
	DWORD			day;						
	DWORD			week;							
	DWORD			time;							
	DWORD			bitRate;
	DWORD			connectNum;	
}SDK_OSD_SWITCH_S;

//��֡����
typedef struct SMART_FRAME_DROP_S 
{
	DWORD	lowFrameEnable; //0 �� 1��				
}SDK_SMART_FRAME_DROP_S;

//�ع���������
typedef struct EXPOSURE_MS_PARAM_S
{
	DWORD			msMode; //0:slave  1: master			
}SDK_EXPOSURE_MS_PARAM_S;

//��ʽ��SD
typedef struct FORMAT_PARAM_S
{
	DWORD IpcStorageNum;	//SD����
}SDK_FORMAT_PARAM_S;

//�ಥ��ַ����
typedef struct EXPOSURE_MUIT_S
{
	char byMuitAddr[128];	//�ಥ��ַ
}SDK_EXPOSURE_MUIT;

//��ƽ��ģʽ
typedef struct SDK_AWBAUTO_MODE_S
{
	DWORD dwAwbMode;	//��ƽ��ģʽ
	DWORD dwAutoAwb;	//��ƽ��	0�Զ�, 1 �ֶ� 
	DWORD dwAwBblue;	//��ƽ��	��  0~255
	DWORD dwAwBRed;		//��ƽ��	��  0~255
	DWORD dwAwBGreen;	//��ƽ��	��	 0~255
}SDK_AWBAUTO_MODE;

typedef enum _SDK_AUTOWB_GROUP //ȫͼ�Զ���ƽ��ģʽ
{
	AWB_GROUP_NOMAL			= 0x0, //��ƽ��1==> ��ͨ��ͷ
	AWB_GROUP_FTK_CS120 	= 0x1, //��ƽ��2==> ���ؿ�cs120��ͷ�궨����
	AWB_GROUP_YT3611 		= 0x2, //��ƽ��3==>yt3.6-11mm�綯�䱶��ͷ	Ĭ��
	AWB_GROUP_HM1212MP5 	= 0x3, //��ƽ��4==>������HM121MP5 ���Ȧ��ͷ

}SDK_AUTOWB_GROUP;


//���±����������
// ��������
struct SDK_CONFIG_ENCODE
{
	SDK_MEDIA_FORMAT dstMainFmt[SDK_ENCODE_TYPE_NUM];		//  ��������ʽ 	
	SDK_MEDIA_FORMAT dstExtraFmt[SDK_EXTRATYPES];	//  ��������ʽ 
	SDK_MEDIA_FORMAT dstSnapFmt[SDK_ENCODE_TYPE_NUM];		//  ץͼ��ʽ 
};
struct  SDK_EncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_CHANNUM];
};


// �򻯰汾��������
/// ý���ʽ
struct SDK_MEDIA_FORMAT_SIMPLIIFY
{
	SDK_VIDEO_FORMAT vfFormat;			//  ��Ƶ��ʽ���� 			
	bool	bVideoEnable;			//  ������Ƶ���� 
	bool	bAudioEnable;			//  ������Ƶ���� 	
};

/// ��������
struct SDK_CONFIG_ENCODE_SIMPLIIFY
{
	SDK_MEDIA_FORMAT dstMainFmt;		//  ��������ʽ 	
	SDK_MEDIA_FORMAT dstExtraFmt;	//  ��������ʽ 
};

/// ȫͨ����������
struct SDK_EncodeConfigAll_SIMPLIIFY
{
	SDK_CONFIG_ENCODE_SIMPLIIFY vEncodeConfigAll[NET_MAX_CHANNUM];
};


struct  SDK_CombineEncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_COMBINE_NUM];
};

/// ��ϱ���ģʽ
struct SDK_CombEncodeParam
{
	int iEncodeMode;	 //��CombineEncodeMode
};

struct SDK_CombEncodeModeAll
{
	SDK_CombEncodeParam vEncodeParam[NET_MAX_COMBINE_NUM];
};

//!��Ƶ����ṹ
struct  SDK_VIDEO_WIDGET
{
	unsigned int rgbaFrontground;		///< �����ǰ��MakeRGB����͸����	
	unsigned int rgbaBackground;		///< ����ĺ�MakeRGB����͸����	
	sdkRect	rcRelativePos;			///< ����߾��������ı���*8191
	bool	bPreviewBlend;			///< Ԥ������	
	bool	bEncodeBlend;			///< �������
};

//!��Ƶ�������
struct SDK_CONFIG_VIDEOWIDGET
{
	SDK_VIDEO_WIDGET	dstCovers[NET_COVERNUM];
	SDK_VIDEO_WIDGET	ChannelTitle;
	SDK_VIDEO_WIDGET	TimeTitle;
	struct 
	{
		char strName[NET_NAME_PASSWORD_LEN];
#ifdef WIN32
 		__int64 iSerialNo;	
#else
		long long iSerialNo;	
#endif
	}ChannelName;					/// ͨ������
	int				iCoverNum;		/*!< ��ǰ��ͨ���м������ӵ����� */
};

/// ��Ƶ���(���ģʽ�Ի���)
struct SDK_VideoWidgetConfigAll
{
	SDK_CONFIG_VIDEOWIDGET vVideoWidegetConfigAll[NET_MAX_CHANNUM];
};

//��Ƶ��ɫ
struct SDK_VIDEOCOLOR_PARAM
{
	int	nBrightness;		///< ����	0-100
	int	nContrast;			///< �Աȶ�	0-100
	int	nSaturation;		///< ���Ͷ�	0-100
	int	nHue;				///< ɫ��	0-100
	int	mGain;				///< ����	0-100 �ڣ�λ��1��ʾ�Զ�����		
	int	mWhitebalance;		///< �Զ��׵�ƽ���ƣ�bit7��λ��ʾ�����Զ�����.0x0,0x1,0x2�ֱ�����,��,�ߵȼ�
	int nAcutance;          ///< ���   0-15
};
///< ��Ƶ��ɫ����
struct SDK_VIDEOCOLOR
{
	SDK_TIMESECTION			tsTimeSection;		/// ʱ���
	SDK_VIDEOCOLOR_PARAM	dstColor;			/// ��ɫ����
	int					iEnable;
};

struct SDK_CONFIG_VIDEOCOLOR
{
	SDK_VIDEOCOLOR dstVideoColor[NET_N_MIN_TSECT];
};

struct SDK_VideoColorConfigAll
{
	SDK_CONFIG_VIDEOCOLOR vVideoColorAll[NET_MAX_CHANNUM];
};


/// ����ͨ�����Ʊ���
struct SDK_ChannelNameConfigAll
{
	char channelTitle[NET_MAX_CHANNUM][NET_NAME_PASSWORD_LEN];
};

//���ģʽ
struct SDK_GUISetConfig
{
	int iWindowAlpha;			///< ����͸����	[128, 255]
	bool bTimeTitleEn;			///< ʱ�������ʾʹ��
	bool bChannelTitleEn;		///< ͨ��������ʾʹ��	
	bool bAlarmStatus;			///<  ����״̬
	bool bRecordStatus;			///<  ¼��״̬��ʾʹ��
	bool bChanStateRecEn;		///< ¼���־��ʾʹ��
	bool bChanStateVlsEn;		///< ��Ƶ��ʧ��־��ʾʹ��
	bool bChanStateLckEn;		///< ͨ��������־��ʾʹ��	
	bool bChanStateMtdEn;		///< ��̬����־��ʾʹ��
	bool bBitRateEn;			///< ������ʾʹ��
	bool bRemoteEnable;			///< ң����ʹ��
	bool bDeflick;				///< ������
};


////!��ͨ��������
struct SDK_CONFIG_NET_COMMON
{
	//!������
	char HostName[NET_NAME_PASSWORD_LEN];
	//!����IP
	CONFIG_IPAddress HostIP;
	//!��������
	CONFIG_IPAddress Submask;
	//!����IP
	CONFIG_IPAddress Gateway;
	//!HTTP����˿�
	int HttpPort;
	//!TCP�����˿�
	int TCPPort;	
	//!SSL�����˿�
	int SSLPort;
	//!UDP�����˿�
	int UDPPort;
	//!���������
	int MaxConn;
	//!����Э�� {"TCP","UDP","MCAST",��}
	int MonMode;
	//!�޶�����ֵ
	int MaxBps;
	//!�������
	//char TransferPlan[NET_NAME_PASSWORD_LEN];
	int TransferPlan;

	//!�Ƿ����ø���¼�����ز���
	bool bUseHSDownLoad;

	//!MAC��ַ
	char sMac[NET_MAX_MAC_LEN];

	char szUserName[NET_NAME_PASSWORD_LEN];		//�豸�û���
	char szPassword[NET_NAME_PASSWORD_LEN];		//�豸����
};

////!��ͨ�������� --
struct SDK_CONFIG_NET_COMMON_V2
{
	//!������
	char HostName[NET_NAME_PASSWORD_LEN];
	//!����IP
	CONFIG_IPAddress HostIP;
	//!��������
	CONFIG_IPAddress Submask;
	//!����IP
	CONFIG_IPAddress Gateway;
	//!HTTP����˿�
	int HttpPort;
	//!TCP�����˿�
	int TCPPort;	
	//!SSL�����˿�
	int SSLPort;
	//!UDP�����˿�
	int UDPPort;
	//!���������
	int MaxConn;
	//!����Э�� {"TCP","UDP","MCAST",��}
	int MonMode;
	//!�޶�����ֵ
	int MaxBps;
	//!�������
	//char TransferPlan[NET_NAME_PASSWORD_LEN];
	int TransferPlan;

	//!�Ƿ����ø���¼�����ز���
	bool bUseHSDownLoad;

	//!MAC��ַ
	char sMac[NET_MAX_MAC_LEN];

	char sSn[NET_MAX_MAC_LEN]; 	///���к�
	int ChannelNum;			///ͨ����                //by zjh 20170807
	int	DeviceType;			///�豸���ͣ���ö��DevType  //by zjh 20170807
	char szUserName[NET_NAME_PASSWORD_LEN];		//�豸�û���
	char szPassword[NET_NAME_PASSWORD_LEN];		//�豸����
	char Resume[56];	///����
};
//�豸���Ͷ���
typedef enum _SDK_DEVICE_TYPE
{
	SDK_DEV_TYPE_IPC = 0,		//��ͨ�����

	SDK_DEV_TYPE_DVR,			//����NVR��Э���й��豸����		
	SDK_DEV_TYPE_HVR,
	SDK_DEV_TYPE_POEIPC,
	SDK_DEV_TYPE_NVR,
	SDK_DEV_TYPE_RTSPIPC,

	SDK_DEV_TYPE_BSIPC,			//�ȶԻ� 6
	SDK_DEV_TYPE_FPIPC,			//ץ�Ļ� 7
	SDK_DEV_TYPE_CPIPC,			//����ץ�Ļ� 
	SDK_DEV_TYPE_END
}SDK_DEVICE_TYPE;

//DHCP
#define SDK_MAX_ETH_NUM 4
struct SDK_NetDHCPConfig
{
	bool bEnable;
	char ifName[32];
};
/// ����������DHCP����
struct SDK_NetDHCPConfigAll
{
	SDK_NetDHCPConfig vNetDHCPConfig[SDK_MAX_ETH_NUM];
};

///< DNS����
struct SDK_NetDNSConfig
{
	CONFIG_IPAddress		PrimaryDNS;
	CONFIG_IPAddress		SecondaryDNS;
};
///< �������ṹ����
struct SDK_RemoteServerConfig
{
	char ServerName[NET_NAME_PASSWORD_LEN];	///< ������
	CONFIG_IPAddress ip;						///< IP��ַ
	int Port;							///< �˿ں�
	char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
	char Password[NET_NAME_PASSWORD_LEN];		///< ����	
	bool Anonymity;							///< �Ƿ�������¼
};
///< �������ṹ������չ,���������û�����������
struct SDK_RemoteServerConfig_EX
{
	char ServerName[NET_NAME_URL_LEN];	///< ������
	CONFIG_IPAddress ip;						///< IP��ַ
	char ServerUrl[NET_NAME_URL_LEN];	//������Url
	int Port;							///< �˿ں�
	char UserName[NET_NAME_URL_LEN];		///< �û���
	char Password[NET_NAME_URL_LEN];		///< ����	
	bool Anonymity;							///< �Ƿ�������¼
};
///< IPȨ������
struct SDK_NetIPFilterConfig
{
	bool Enable;		///< �Ƿ���
	CONFIG_IPAddress BannedList[NET_MAX_FILTERIP_NUM];		///< �������б�
	CONFIG_IPAddress TrustList[NET_MAX_FILTERIP_NUM];		///< �������б�
};

///< �鲥����
struct SDK_NetMultiCastConfig
{
	bool Enable;		///< �Ƿ���
	SDK_RemoteServerConfig Server;		///< �鲥������
};

///< pppoe����
struct SDK_NetPPPoEConfig
{
	bool Enable;	///< �Ƿ���
	SDK_RemoteServerConfig Server;		///< PPPOE������
	CONFIG_IPAddress addr;		///< ���ź��õ�IP��ַ
};

///< DDNS����
struct SDK_NetDDNSConfig
{
	bool Enable;	///< �Ƿ���
	bool Online;		///< �Ƿ�����
	char DDNSKey[NET_NAME_PASSWORD_LEN];	///< DDNS��������, Ŀǰ��: JUFENG
	char HostName[NET_NAME_PASSWORD_LEN];	///< ������
	SDK_RemoteServerConfig Server;			///< DDNS������
	
};

///< DDNS����
struct SDK_NetDDNSConfigALL
{
	SDK_NetDDNSConfig ddnsConfig[NET_MAX_DDNS_TYPE];
};

///< FTP����
struct SDK_FtpServerConfig{
	bool bEnable;        ///< ������ʹ��     
	SDK_RemoteServerConfig Server;	///< FTP������
	char cRemoteDir[NET_MAX_PATH_LENGTH];	///< Զ��Ŀ¼
	int iMaxFileLen;	///< �ļ���󳤶�
};

///<HTTP����
typedef struct _SDK_HTTPSERVERCONFIG_   //1948�ֽ�
{
	int      bEnable;		//http����ʹ�� 0�أ�1��
	char     serverip[128]; 	//����ͼƬ��Ϣ��������ַ(IP������)
	int      serverport;		//����ͼƬ��Ϣ�������˿�
	char     serverpath[128];	//����ͼƬ��Ϣ�ķ�����·�� (��ʽ: /[path])
	int      resendnum;  		//�ش�������0-5��
	int 	 bImgEnable;  		//�Ƿ��ϴ�ͼƬ   ,0��1��
	int 	 nListenPort;		//�����˿�
	char     byRes0[32]; 		
	char     byRes1[64]; 		
	char     byRes2[64]; 		
	char	 byRes3[64];
	char 	 byRes4[64];
	char	 byRes5[64];
	char	 byRes6[64];
	char	 byRes7[128];
	int		nRes8;
	int		nRes9;
	char     byRes10[100];   
	//��Ϣ����: 
	//0:�������ϴ� 1: �ȶԳɹ��ϴ� 2:�������ϴ� 3:�������ϴ� 4: VIP�����ϴ�
	//5:İ�����ϴ� 6: �ǰ������ϴ�
	int 	 msgType;
	int	 featureEn;	   	//����ֵʹ��: 0���ϴ�����ֵ 1 �ϴ�����ֵ
	char     byRes11[64];
	char     byRes12[64];
	int      bKeepAliveEnable;	//�Ƿ����������͹���  ,   0�أ�1��
	char     keepaliveaddr[64]; 	//����������Ϣ�ķ�������ַ(ip������)
	int      keepaliveport;		//����������Ϣ�ķ������˿�
	char     keepalivepath[128];	//����������Ϣ�ķ�����·��(��ʽ: /[path])
	int      keepaliveInterval; 	//�������(1~100000��)
	char     byRes13[64];
	int      bRemoteUpgrade; 	//Զ������,   0�أ�1��
	int      bGetVersionInterval;	//���汾ʱ����(1~100000����) 
	char     GetVersionURL[128]; 	//��ȡ�汾��ַ
	char     postUrl[128];		//����ʶ����Ϣ��ַ (��ʽ: http://[ip]:[port]/[path])
	char     byRes14[128];
	char     postKeepAliveUrl[128]; //����������Ϣ��ַ (��ʽ: http://[ip]:[port]/[path])
	int      nRes15;
	BYTE	 byRes[92];
}SDK_HTTPSERVERCONFIG;

///< NTP����
struct SDK_NetNTPConfig
{
	///< �Ƿ���
	bool Enable;
	///< PPPOE������
	SDK_RemoteServerConfig Server;
	///< ��������
	int UpdatePeriod;
	///< ʱ��
	int TimeZone;
};
#define  NET_MAX_EMAIL_TITLE_LEN 64
#define  NET_MAX_EMAIL_RECIEVERS  5
#define  NET_EMAIL_ADDR_LEN  32

///< EMAIL����
struct SDK_NetEmailConfig
{
	///< �Ƿ���
	bool Enable;
	///< smtp ��������ַʹ���ַ�����ʽ���
	///< ������ip,Ҳ����������
	SDK_RemoteServerConfig Server;
	bool bUseSSL;
	///< ���͵�ַ
	char SendAddr[NET_EMAIL_ADDR_LEN];
	///< �����˵�ַ
	char Recievers[NET_MAX_EMAIL_RECIEVERS][NET_EMAIL_ADDR_LEN];
	///< �ʼ�����
	char Title[NET_MAX_EMAIL_TITLE_LEN];
	///< email��Чʱ��
	SDK_TIMESECTION Schedule[NET_N_MIN_TSECT];
};

///< ARSP(����ע�������)����
struct SDK_NetARSPConfig
{
	bool bEnable;	///< �Ƿ���
	char sARSPKey[NET_NAME_PASSWORD_LEN];	///< DNS��������
	int iInterval;	///< ������ʱ��
	char sURL[NET_NAME_PASSWORD_LEN];    ///< ��������
	SDK_RemoteServerConfig Server;		///< DDNS������
	int nHttpPort;                  ///< ������HTTP�˿�
};

struct SDK_NetARSPConfigAll
{
	SDK_NetARSPConfig vNetARSPConfigAll[NET_MAX_ARSP_TYPE];
};

///< ��������ַ����
struct SDK_NetDecoderConfig
{
	bool Enable;						///< �Ƿ���
	char UserName[NET_NAME_PASSWORD_LEN];	///< DDNS��������, Ŀǰ��: JUFENG
	char PassWord[NET_NAME_PASSWORD_LEN];	///< ������
	char Address[NET_NAME_PASSWORD_LEN];
	int Protocol;
	int Port;							///< ���������Ӷ˿�
	int Channel;						///< ����������ͨ����
	int Interval;                       ///< ��Ѳ�ļ��ʱ��(s)
};

/// ����ͨ���Ľ�������ַ����
struct SDK_NetDecoderConfigAll
{
	SDK_NetDecoderConfig vNetDecoderConfig[NET_MAX_DECORDR_CH];
};


/// ��������ַ����V2�汾
struct SDK_NetDecoderConfig_V2
{
	int nTotalNum;            //��Ч��������������ΪNET_MAX_CHANNUM
	SDK_NetDecoderConfig vNetDecoderConfig[NET_MAX_CHANNUM];
};

/// ����ͨ���Ľ�������ַ����V2�汾
struct SDK_NetDecoderConfigAll_V2
{
	SDK_NetDecoderConfig_V2 vNetDecoderArray[NET_MAX_DECORDR_CH];
};


///< ��������ַ����
struct SDK_NetDecorderConfigV3
{
	bool Enable;						///< �Ƿ���
	char UserName[NET_NAME_PASSWORD_LEN];	///< DDNS��������, Ŀǰ��: JUFENG
	char PassWord[NET_NAME_PASSWORD_LEN];	///< ������
	char Address[NET_NAME_URL_LEN];
	int Protocol;
	int Port;							///< ���������Ӷ˿�
	int Channel;						///< ����������ͨ����
	int Interval;                       ///< ��Ѳ�ļ��ʱ��(s),0:��ʾ����
	char ConfName[NET_NAME_PASSWORD_LEN];	///<��������
	int DevType;						///<�豸����
	int StreamType;						///<���ӵ���������CaptureChannelTypes
	char MainRtspUrl[NET_NAME_URL_LEN];		///<rtspЭ��ʱ��ʾǰ���豸����������ַ
	char SubRtspUrl[NET_NAME_URL_LEN];		///<rtspЭ��ʱ��ʾǰ���豸�ĸ�������ַ
};

/*��������������*/
enum SDK_DecorderConnType
{
	SDK_CONN_SINGLE = 0, 	/*������*/
	SDK_CONN_MULTI = 1,		/*��������Ѳ*/
	SDK_CONN_TYPE_NR,
};

/*����ͨ��������*/
struct SDK_NetDigitChnConfig
{
	bool Enable;		/*����ͨ���Ƿ���*/		
	int ConnType;		/*�������ͣ�ȡDecoderConnectType��ֵ*/
	int TourIntv;		/*������ʱ��Ѳ���*/
	unsigned int SingleConnId;	/*������ʱ����������ID, ��1��ʼ��0��ʾ��Ч*/
	bool EnCheckTime;	/*������ʱ*/
	SDK_NetDecorderConfigV3 NetDecorderConf[32]; /*�����豸ͨ�����ñ�*/
	int nNetDeorde; // �ж��ٸ�
};

/*��������ͨ��������*/
struct SDK_NetDecorderConfigAll_V3
{
	SDK_NetDigitChnConfig DigitChnConf[NET_MAX_DECORDR_CH];
};

//ͨ��ģʽ
#define MAX_HVR_CHNCAP_CHN		32
typedef struct SDK_HVR_CHNCAP 
{
	int nD1Chn;		// ֧�ֵ�D1·��
	int n960HChn;	// ֧�ֵ�960H·��
	int n720PChn;	// ֧�ֵ�720P·��
	int n1080PChn;	// ֧�ֵ�1080P·��
	int nCIFChn;	//֧�ֵ�CIFͨ����
	int nHD1Chn;	//֧�ֵ�HD1ͨ����
	unsigned char nPlayChn; //֧�ֻط�·��
	unsigned char nDigiTalChn; //֧���������ͨ��·��
	unsigned char n960PChn; //֧�ֵ�960Pͨ����
	unsigned char n3MChn; //֧�ֵ�3Mͨ����
	unsigned char n5MChn; //֧�ֵ�5Mͨ����
	unsigned char nWUXGAChn; //֧�ֵ�WUXGAͨ����
	unsigned char nResChar[2]; //����
}SDK_HVR_CHNCAP, *SDK_PHVR_CHNCAP;

typedef struct SDK_CAPTURE_HVRCAP 
{
	SDK_HVR_CHNCAP DigitalCap;		// ֧�ֵ�����ͨ����Ϣ
	SDK_HVR_CHNCAP AnalogCap;		// ֧�ֵ�ģ��ͨ����Ϣ
}SDK_CAPTURE_HVRCAP, *SDK_PCAPTURE_HVRCAP;

typedef struct SDK_CAPTURE_TOTAL_HVRCAP 
{
	int		nHVRCap;			// ʵ��֧�ֵ�ģʽ
	SDK_CAPTURE_HVRCAP	HVRCap[MAX_HVR_CHNCAP_CHN];		// ����ģʽ�Ļ���
}SDK_CAPTURE_TOTAL_HVRCAP, *SDK_PCAPTURE_TOTAL_HVRCAP;

//ͨ��ģʽ����
struct SDK_NetDecorderChnModeConfig
{
	SDK_CAPTURE_TOTAL_HVRCAP 	HVRTotalCap;
	int HVRCurCapMode;
};


/*����ͨ��״̬*/
struct SDK_NetDecorderChnStatus
{
	char ChnName[NET_NAME_PASSWORD_LEN];
	char pMaxResName[50];
	char	pCurResName[50];
	char pStatus[50];
};

/*��������ͨ��״̬*/
struct SDK_NetDecorderChnStatusAll
{
	SDK_NetDecorderChnStatus ChnStatusAll[MAX_HVR_CHNCAP_CHN];
};

///< 3G��������
struct SDK_Net3GConfig
{
	bool bEnable;			  ///< ����ģ��ʹ�ܱ�־
	int iNetType;			  ///< ������������
	char sAPN[NET_NAME_PASSWORD_LEN];		///< ���������
	char sDialNum[NET_NAME_PASSWORD_LEN];   ///< ���ź���
	char sUserName[NET_NAME_PASSWORD_LEN];  ///< �����û���
	char sPassword[NET_NAME_PASSWORD_LEN];  ///< ��������
	CONFIG_IPAddress addr;			  ///< ���ź��õ�IP��ַ
};

///< �ֻ�������ð���
struct SDK_NetMoblieConfig
{
	bool bEnable;	///< �Ƿ���
	SDK_RemoteServerConfig Server;		///< ������
};

//RTSP
struct SDK_NetRTSPConfig
{
	bool bServer;
	bool bClient;
	SDK_RemoteServerConfig Server;		///< ������ģʽ
	SDK_RemoteServerConfig Client;		///< �ͻ���ģʽ
};

///< UPNP����
struct SDK_NetUPNPConfig
{
	bool bEnable;			  ///< ʹ�ܱ�־
	bool bState;              ///< ״̬, 1: OK 0: NOK
	int iHTTPPort;			  ///< HTTP����ӳ���Ķ˿�
	int iMediaPort;			  ///< ý������ӳ���Ķ˿�
	int iMobliePort;		  ///< �ֻ����ӳ���Ķ˿�
};

///< WIFI����
struct SDK_NetWifiConfig
{
	bool bEnable;
	char sSSID[36];            //SSID Number
	int nChannel;                   //channel
	char sNetType[32];         //Infra, Adhoc
	char sEncrypType[32];      //NONE, WEP, TKIP, AES
	char sAuth[32];            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
	int  nKeyType;                  //0:Hex 1:ASCII
	char sKeys[NET_IW_ENCODING_TOKEN_MAX];
	CONFIG_IPAddress HostIP;		///< host ip
	CONFIG_IPAddress Submask;		///< netmask
	CONFIG_IPAddress Gateway;		///< gateway
};

enum SDK_RSSI_SINGNAL
{
	SDK_RSSI_NO_SIGNAL,   //<= -90db
	SDK_RSSI_VERY_LOW,     //<= -81db
	SDK_RSSI_LOW,          //<= -71db
	SDK_RSSI_GOOD,         //<= -67db
	SDK_RSSI_VERY_GOOD,    //<= -57db
	SDK_RSSI_EXCELLENT     //>-57db
};

struct SDK_NetWifiDevice
{
	char sSSID[36];            //SSID Number
	int nRSSI;                 //SEE SDK_RSSI_SINGNAL
	int nChannel;
	char sNetType[32];         //Infra, Adhoc
	char sEncrypType[32];      //NONE, WEP, TKIP, AES
	char sAuth[32];            //OPEN, SHARED, WEPAUTO, WPAPSK, WPA2PSK, WPANONE, WPA, WPA2
};

struct SDK_NetWifiDeviceAll
{
	int nDevNumber;
	SDK_NetWifiDevice vNetWifiDeviceAll[NET_MAX_AP_NUMBER];
};

///< ������������
struct SDK_NetAlarmCenterConfig
{
	bool bEnable;		///< �Ƿ���
	char sAlarmServerKey[NET_NAME_PASSWORD_LEN];	///< ��������Э����������, 
	///< �������ķ�����
	SDK_RemoteServerConfig Server;	
	bool bAlarm;
	bool bLog;
};

struct SDK_NetAlarmServerConfigAll
{
	SDK_NetAlarmCenterConfig vAlarmServerConfigAll[NET_MAX_ALARMSERVER_TYPE];
};


//���Ż�ͨ
struct SDK_CONFIG_NET_MEGA
{
	bool bEnable;
	bool bNetManEnable;
	CONFIG_IPAddress ServerIP;
	int iServerPort;
	char sDeviceId[32];
	char sUserName[24];
	char sPasswd[32];
	int iMaxCon;
	int iVideoPort;
	int iAudioPort;
	int iMsgPort;
	int iUpdatePort;
};

// ����ƽ̨
struct SDK_CONFIG_NET_XINGWANG
{
	bool bEnable;
	bool bSyncTime;
	bool bSubStream;
	CONFIG_IPAddress ServerIP;
	int iServerPort;
	int iDownLoadPort;
	char sPasswd[32];
	char szSID[32];
};

// ����ƽ̨
struct SDK_CONFIG_NET_SHISOU
{
	bool bEnable;
	SDK_RemoteServerConfig Server;
	char szSID[NET_MAX_USERNAME_LENGTH];
};

// VVEYEƽ̨
struct SDK_CONFIG_NET_VVEYE
{
	bool bEnable;                
	bool bCorpEnable;            //ֻ����ʹ����ҵ������ʱ����Ҫ����Server
	SDK_RemoteServerConfig Server;
	char szDeviceName[NET_MAX_USERNAME_LENGTH];
};

// ����������Ϣ����
enum SDK_AlarmCenterMsgType
{
	SDK_ALARMCENTER_ALARM,
	SDK_ALARMCENTER_LOG,
};

// ����������Ϣ����
enum SDK_AlarmCenterStatus
{
	SDK_AC_START,
	SDK_AC_STOP,
};

// �澯������Ϣ����
struct SDK_NetAlarmCenterMsg
{
	CONFIG_IPAddress HostIP;		///< �豸IP
	int nChannel;                   ///< ͨ��
	int nType;                      ///< ���� ��AlarmCenterMsgType
	int nStatus;                    ///< ״̬ ��AlarmCenterStatus
	SDK_SYSTEM_TIME Time;           ///< ����ʱ��
	char sEvent[NET_MAX_INFO_LEN];  ///< �¼�
	char sSerialID[NET_MAX_MAC_LEN]; ///< �豸���к�
	char sDescrip[NET_MAX_INFO_LEN];  ///< ����
};

/// ������Ϣ
struct SDK_EncodeInfo
{
	bool bEnable;			///< ʹ����
	int iStreamType;		///< �������ͣ�capture_channel_t
	bool bHaveAudio;		///< �Ƿ�֧����Ƶ
	unsigned int uiCompression;		///< capture_comp_t������
	unsigned int uiResolution;		///< SDK_CAPTURE_SIZE_t������
};

/// ��������
struct CONFIG_EncodeAbility
{
	unsigned int iMaxEncodePower;		///< ֧�ֵ�����������
	int iChannelMaxSetSync;		///< ÿ��ͨ���ֱ����Ƿ���Ҫͬ�� 0-��ͬ��, 1 -ͬ��
	unsigned int nMaxPowerPerChannel[NET_MAX_CHANNUM];		///< ÿ��ͨ��֧�ֵ���߱�������
	unsigned int ImageSizePerChannel[NET_MAX_CHANNUM];		///< ÿ��ͨ��֧�ֵ�ͼ��ֱ���
	unsigned int ExImageSizePerChannel[NET_MAX_CHANNUM];		///< ÿ��ͨ��֧�ֵĸ�����ͼ��ֱ���
	SDK_EncodeInfo vEncodeInfo[SDK_CHL_FUNCTION_NUM];	///< ������Ϣ,��ʱ����4������
	SDK_EncodeInfo vCombEncInfo[SDK_CHL_FUNCTION_NUM];	///< ��ϱ�����Ϣ,��ʱ����4������
	int	iMaxBps;				///< �������Kbps
	unsigned int ExImageSizePerChannelEx[NET_MAX_CHANNUM][SDK_CAPTURE_SIZE_NR];	///< ÿ��ͨ��֧�ֵĸ�����ͼ��ֱ���
};

// ����Э��
enum SDK_CommProtocol
{
	SDK_CONSOLE = 0,
	SDK_KEYBOARD,
	SDK_COM_TYPES,
};
/// ����Э��
struct SDK_COMMFUNC
{
	//ÿ��Э�������64���ַ����
	int nProNum;
	char vCommProtocol[100][32];
};

/// ��̨Э��
struct SDK_PTZPROTOCOLFUNC
{
	//ÿ��Э�������64���ַ����
	int nProNum;
	char vPTZProtocol[100][NET_MAX_PTZ_PROTOCOL_LENGTH];
};

/// �����ڵ�������
struct SDK_BlindDetectFunction
{
	int iBlindConverNum;	///< �����ڵ�����
};

/// ��������������
struct SDK_MotionDetectFunction
{
	int iGridRow;
	int iGridColumn;
};

/// ֧�ֵ�DDNS����
struct SDK_DDNSServiceFunction
{
	int  nTypeNum;
	char vDDNSType[NET_MAX_DDNS_TYPE][64];
};

/// ֧������
struct SDK_MultiLangFunction
{
	//ÿ��Э�������64���ַ����
	int nLangNum;
	char vLanguageName[128][64];
};

/// ֧�ֵ���Ƶ��ʽ
struct SDK_MultiVstd
{
	//ÿ��Э�������3���ַ����
	int nVstdNum;
	char vVstdName[3][64];
};

/// ���빦��
enum SDK_EncodeFunctionTypes
{
	SDK_ENCODE_FUNCTION_TYPE_DOUBLE_STREAM,		///< ˫��������
	SDK_ENCODE_FUNCTION_TYPE_COMBINE_STREAM,	///< ��ϱ��빦��
	SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM,		///< ץͼ����
	SDK_ENCODE_FUNCTION_TYPE_WATER_MARK,		///< ˮӡ����
	SDK_ENCODE_FUNCTION_TYPE_IFRAME_RANGE,		///< I֡���
	SDK_ENCODE_FUNCTION_TYPE_LOW_BITRATE,		///< �����������ò�Ʒʹ��
	SDK_ENCODE_FUNCTION_TYPE_NR,
};

/// ��������
enum SDK_AlarmFucntionTypes
{
	SDK_ALARM_FUNCTION_TYPE_MOTION_DETECT,	///< ��̬���
	SDK_ALARM_FUNCTION_TYPE_BLIND_DETECT,	///< �����ڵ�
	SDK_ALARM_FUNCTION_TYPE_LOSS_DETECT,	///< ������ʧ
	SDK_ALARM_FUNCTION_TYPE_LOCAL_ALARM,	///< ���ر���
	SDK_ALARM_FUNCTION_TYPE_NET_ALARM,		///< ���籨��
	SDK_ALARM_FUNCTION_TYPE_IP_CONFLICT,	///< IP��ַ��ͻ
	SDK_ALARM_FUNCTION_TYPE_NET_ABORT,		///< �����쳣
	SDK_ALARM_FUNCTION_TYPE_STORAGE_NOTEXIST,	///< �洢�豸������
	SDK_ALARM_FUNCTION_TYPE_STORAGE_LOWSPACE,	///< �洢�豸��������
	SDK_ALARM_FUNCTION_TYPE_STORAGE_FAILURE,	///< �洢�豸����ʧ��
	SDK_ALARM_FUNCTION_TYPE_VIDEOANALYSE,///<��Ƶ����
	SDK_ALARM_FUNCTION_TYPE_NET_ABORT_EXTEND,	//�����쳣��չ
	SDK_ALARM_FUNCTION_TYPE_IPC_ALARM,			//IPC����
	SDK_ALARM_FUNCTION_TYPE_NR
};

/// ���������
enum SDK_NetServerTypes
{
	SDK_NET_SERVER_TYPES_IPFILTER,		///< �׺�����
	SDK_NET_SERVER_TYPES_DHCP,			///< DHCP����
	SDK_NET_SERVER_TYPES_DDNS,			///< DDNS����
	SDK_NET_SERVER_TYPES_EMAIL,			///< Email����
	SDK_NET_SERVER_TYPES_MULTICAST,		///< �ಥ����
	SDK_NET_SERVER_TYPES_NTP,			///< NTP����
	SDK_NET_SERVER_TYPES_PPPOE,
	SDK_NET_SERVER_TYPES_DNS,
	SDK_NET_SERVER_TYPES_ARSP,			///< ����ע�����
	SDK_NET_SERVER_TYPES_3G,            ///< 3G����
	SDK_NET_SERVER_TYPES_MOBILE=10,        ///< �ֻ����
	SDK_NET_SERVER_TYPES_UPNP,			    ///< UPNP
	SDK_NET_SERVER_TYPES_FTP,			    ///< FTP
	SDK_NET_SERVER_TYPES_WIFI,          ///<WIFI
	SDK_NET_SERVER_TYPES_ALARM_CENTER,  ///< �澯����
	SDK_NET_SERVER_TYPES_NETPLAT_MEGA,  ///< ���Ż�ͨ
	SDK_NET_SERVER_TYPES_NETPLAT_XINWANG,  ///< ����
	SDK_NET_SERVER_TYPES_NETPLAT_SHISOU,  ///< ����
	SDK_NET_SERVER_TYPES_NETPLAT_VVEYE,  ///< ������
	SDK_NET_SERVER_TYPES_RTSP,     //RTSP
	SDK_NET_SERVER_TYPES_PHONEMSG=20,     //�ֻ���Ϣ��������
	SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG,     //�ֻ���Ϣ��������
	SDK_NET_SERVER_TYPES_DAS,          //����ע��
	SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM,          //����ƽ̨��Ϣ����
	SDK_NET_SERVER_TYPES_GOD_EYE,///<���۽Ӿ�����ϵͳ
	SDK_NET_SERVER_TYPES_NAT,		///NAT��͸��MTU����
	SDK_NET_SERVER_TYPES_VPN,     ///VPN
	SDK_NET_SERVER_TYPES_NET_KEYBOARD,	///�����������
	SDK_NET_SERVER_TYPES_SPVMN,		///28181Э������
	SDK_NET_SERVER_TYPES_PMS,      //�ֻ�����
	SDK_NET_SERVER_TYPE_KAICONG,		///��������
	SDK_NET_SERVER_TYPE_PROTOCOL_MAC,///֧��MACЭ��
	SDK_NET_SERVER_TYPE_XMHEARTBEAT, //��������
	SDK_NET_SERVER_TYPES_MONITOR_PLATFORM, //����������ƽ̨
	SDK_NET_SERVER_TYPES_ANJUP2P,			//
	SDK_NET_SERVER_TYPES_TUTKIOTC,		//TUTK IOTCƽ̨
	SDK_NET_SERVER_TYPES_BAIDUCLOUD, //�ٶ���
	SDK_NET_SERVER_TYPES_MOBILWATCH,		//�ֻ�����
	SDK_NET_SERVER_TYPES_BJLTHY,				//�������ڷ��ʷ�����ƽ̨
	SDK_NET_SERVER_TYPES_OPENVPN,			//openvpn����
	SDK_NET_SERVER_TYPES_PROTOCOL_NAT,		//֧��NATЭ��
	SDK_NET_SERVER_TYPES_PLATFORM_GBEYES,	//֧�ֻ������ݵ���
	SDK_NET_SERVER_TYPES_DATALINK,			//DataLink�ͻ����������ִ�г���ʹ������
	SDK_NET_SERVER_TYPES_WIFI_MODE,			//�Ƿ�֧��wifiģʽ�������
	SDK_NET_SERVER_TYPES_IPV6,				//֧��ipv6
	SDK_NET_SERVER_TYPES_PMS_V2,			//�°�PMSҳ��
	SDK_NET_SERVER_TYPES_4G,				//���߲��ŵ�Э���������Ƿ���ʾ4G
	SDK_NET_SERVER_TYPES_NR,   
};

/// Ԥ������
enum SDK_PreviewTypes
{
	SDK_PREVIEW_TYPES_TOUR,		///< ��Ѳ
	SDK_PREVIEW_TYPES_TALK,		///< GUI��������
	SDK_PREVIEW_TYPES_NR
};

///��������
enum SDK_CommTypes
{
	SDK_COMM_TYPES_RS485,			///<485����
	SDK_COMM_TYPES_RS232,			///<232����
	SDK_COMM_TYPES_NR
};

//���뷨����
enum SDK_InPutMethod
{
	SDK_NO_SUPPORT_CHINESE,		//��֧����������
	SDK_NO_SUPPORT_NR
};

//�����б�ǩ��ʾ
enum SDK_TipShow
{
	SDK_NO_BEEP_TIP_SHOW,  //������ʾ
	SDK_NO_FTP_TIP_SHOW,  //FTP��ʾ
	SDK_NO_EMAIL_TIP_SHOW,  //EMAIL��ʾ
	SDK_NO_TIP_SHOW_NR
};
///���ع���
enum SDK_MobileCar
{
	SDK_MOBILEDVR_STATUS_EXCHANGE,
	SDK_MOBILEDVR_DELAY_SET,
	SDK_MOBILEDVR_CARPLATE_SET,
	SDK_MOBILEDVR_GPS_TIMING,
	SDK_MOBILEDVR_DVR_BOOT_TYPE_SET,
	SDK_MOBILEDVR_NR
};

///��������
enum SDK_OtherFunction
{
	SDK_OTHER_DOWNLOADPAUSE,		//¼��������ͣ����
	SDK_OTHER_USB_SUPPORT_RECORD,	//USB֧��¼����
	SDK_OTHER_SD_SUPPORT_RECORD,		//SD֧��¼����
	SDK_OTHER_ONVIF_CLIENT_SUPPORT,	//�Ƿ�֧��ONVIF�ͻ���
	SDK_OTHER_NET_LOCALSEARCH_SUPPORT,	//�Ƿ�֧��Զ������
	SDK_OTHER_MAXPLAYBACK_SUPPORT, //�Ƿ�֧�����ط�ͨ������ʾ
	SDK_OTHER_NVR_SUPPORT, //�Ƿ���רҵNVR
	SDK_OTHER_C7_PLATFORM_SUPPORT,//֧��C7ƽ̨
	SDK_OTHER_MAIL_TEST_SUPPORT,		//֧���ʼ�����
	SDK_OTHER_SHOW_OSD_INFO,            //֧����ʾ3��OSD��Ϣ
	SDK_OTHER_HIDE_DIGITAL, //ͨ��ģʽ���ι���	
	SDK_OTHER_ACUTANCE_HORIZONTAL,	//���
	SDK_OTHER_ACUTANCE_VERTIAL,
	SDK_OTHER_BROAD_TRENDS,		//��̬����
	SDK_OTHER_NO_TALK,		//�Խ�����
	SDK_OTHER_ALTER_DIGITAL_NAME,	//�޸�����ͨ������
	SDK_OTHER_SHOW_CONNECT_STATUS,      //֧����ʾwifi 3G ����ע��ȵ�����״̬
	SDK_OTHER_SUPPORT_ECACT_SEEK,	//֧�ֻطž�׼��λ
	SDK_OTHER_UPLOAD_TITLEANDSTATE,		//ͨ�����������ͨ��״̬�ϴ�������
	SDK_OTHER_NO_HDD_RECORD,		//��Ӳ��¼��
	SDK_OTHER_MUSICFILE_PLAY,		//������Ƶ�ļ�
	SDK_OTHER_SUPPORT_SET_DIG_IP,//����ǰ��ip����
	SDK_OTHER_VERSION_PRODUCT_TYPE,//֧���ڰ汾��Ϣ����ʾ�豸�ͺ�
	SDK_OTHER_SUPPORT_CAMERA_IMG_STYLE,//֧�������ͼ����
	SDK_OTHER_SUPPORT_TITLE_ABILITY,//֧���޸�onvif����(����ģ��ͨ������)
	SDK_OTHER_SUPPORT_DIMEN_CODE,//֧�ֶ�ά��
	SDK_OTHER_SHOWFALSE_CHECKTIME,//���ν�����ʱ��ͬ������
	SDK_OTHER_SUPPORT_TIME_ZONE, //֧��ʱ������
	SDK_OTHER_SHOW_ALARM_LEVEL_REGION,//��ʾ����ͨ���������ܵ������Ⱥ���������
	SDK_OTHER_SUPPORT_POS,//֧��POS����
	SDK_OTHER_HDD_LOWSPACE_USE_MB,//Ӳ�̿ռ䲻�㱨��������MB
	SDK_OTHER_SUPPORT_CUSTOMIZE_OEMINFO,//����OEM�ͻ��汾��Ϣ
	SDK_OTHER_DIGITAL_ENCODE,//����ͨ����������
	SDK_OTHER_RESUME_PTZ_STATE,//�����ָ���̨״̬
	SDK_OTHER_SUPPORT_SNAP_CFG,//֧��ץͼ����
	SDK_OTHER_ABNORMITY_SEND_EMAIL,//�洢�豸���ڼ��洢�쳣���洢�ռ䲻�㷢�ʼ�
	SDK_OTHER_SUPPORT_DIGITAL_PRE, //֧������ͨ��Ԥ¼
	SDK_OTHER_SUPPORT_WRITE_LOG,   //����ҳ������Ƿ�д��־��ѡ��
	SDK_OTHER_SUPPORT_CHANGE_ONVIF_PORT,//֧���޸�onvif�˿�
	SDK_OTHER_SUPPORT_COMM_DATA_UPLOAD,  //֧�ִ��������ϴ���ָ��������
	SDK_OTHER_SUPPORT_TEXT_PASSWORD,     //��¼�ɷ��������
	SDK_OTHER_SUPPORT_CLOUD_UPGRADE,	// ֧��ͨ���������豸����
	SDK_OTHER_SUPPORT_USER_PROGRAM,//֧�������ͻ�С����
	SDK_OTHER_SUPPORT_MODIFY_FRONT_CFG,//֧���޸�ǰ������
	SDK_OTHER_SUPPORT_FTP_TEST,    //�³���֧��FTP֧��FTP���ԣ��ϳ���֧�֡�
	SDK_OTHER_SUPPORT_PTZ_IDLE_STATE, //��̨����ʱִ�к��ֲ���������
	SDK_OTHER_SUPPORT_IMP_RCD,	//web���Ƿ��ṩ�ؼ�¼��������ѡ��	
	SDK_OTHER_SUPPORT_CAMERA_MOTOR_CTRL, //֧�ֻ�����������
	SDK_OTHER_SUPPORT_ENCODE_ADD_BEEP,// ��Ƶ����ÿ��30�����beep��	
	SDK_OTHER_SUPPORT_FISH_EYE,	        //���۹���������
	SDK_OTHER_SUPPORT_SPVMN_NAS_SERVER,	//���ճ���ͻ���nas����������
	SDK_OTHER_SUPPORT_SMALL_CHN_TITLE_FONT,  //IE�˴�12*18��ͨ���������
	SDK_OTHER_RTSP_CLIENT_SUPPORT,			 //����ͨ���Ƿ�֧��ͨ��RTSP����ǰ���豸
	SDK_OTHER_SUPPORT_CFG_CLOUD_UPGRADE, 	//֧���µ���������������
	SDK_OTHER_SUPPORT_STORAGE_FAIL_REBOOT,	//ȫ��Ӳ�̳�����Զ�����
	SDK_OTHER_SUPPORT_SPLIT_CONTROL,		//�޸�DVR��Ԥ������ָ�ģʽ
	SDK_OTHER_NR
};

///֧�ֵ�ϵͳ����
struct SDK_SystemFunction
{
	bool vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_NR];	///< ���빦��SDK_EncodeFunctionTypes
	bool vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_NR];		///< ��������AlarmFucntionTypes
	bool vNetServerFunction[SDK_NET_SERVER_TYPES_NR];	///< ���������NetServerTypes
	bool vPreviewFunction[SDK_PREVIEW_TYPES_NR];		///< Ԥ������PreviewTypes
	bool vCommFunction[SDK_COMM_TYPES_NR];			///<��������SDK_CommTypes
	bool vInputMethodFunction[SDK_NO_SUPPORT_NR];  //<���뷨����SDK_InPutMethod>
	bool vTipShowFunction[SDK_NO_TIP_SHOW_NR];               //������ǩ��ʾSDK_TipShow>
	bool vMobileCarFunction[SDK_MOBILEDVR_NR];//���ع���
	bool	vOtherFunction[SDK_OTHER_NR];				//��������OtherFunction
};

struct SDK_COMMATTRI
{
	int	iDataBits;	// ����λȡֵΪ5,6,7,8 
	int	iStopBits;	// ֹͣλ
	int	iParity;	// У��λ
	int	iBaudRate;	// ʵ�ʲ�����
};

// ��������
struct SDK_CONFIG_COMM_X
{
	char iProtocolName[32];	// ����Э��:��Console�� 
	int iPortNo;		// �˿ں� 
	SDK_COMMATTRI aCommAttri;		// �������� 
};

struct SDK_CommConfigAll
{
	SDK_CONFIG_COMM_X vCommConfig[SDK_COM_TYPES];
};


// ��̨����
struct SDK_STR_CONFIG_PTZ
{
	char sProtocolName[NET_MAX_PTZ_PROTOCOL_LENGTH];	// Э������ 	
	int	ideviceNo;				// ��̨�豸��ַ��� 	
	int	iNumberInMatrixs;		// �ھ����е�ͳһ���	
	int iPortNo;				// ���ڶ˿ں�	[1, 4] 	
	SDK_COMMATTRI dstComm;			// �������� 	
};

//����ͨ����̨Э��
struct SDK_STR_PTZCONFIG_ALL
{
	SDK_STR_CONFIG_PTZ ptzAll[NET_MAX_CHANNUM];
};

//RS485
struct SDK_STR_RS485CONFIG_ALL
{
	SDK_STR_CONFIG_PTZ ptzAll[NET_MAX_CHANNUM];
};


struct SDK_CONFIG_WORKSHEET
{	
	SDK_TIMESECTION	tsSchedule[NET_N_WEEKS][NET_N_TSECT];	/*!< ʱ��� */
};

/// ¼��ģʽ����
enum SDK_RecordModeTypes
{
	SDK_RECORD_MODE_CLOSED,		///< �ر�¼��
	SDK_RECORD_MODE_MANUAL,		///< �ֶ�¼��
	SDK_RECORD_MODE_CONFIG,		///< ������¼��
	SDK_RECORD_MODE_NR,		
};

///< ¼������
struct SDK_RECORDCONFIG
{
	int iPreRecord;			///< Ԥ¼ʱ�䣬Ϊ��ʱ��ʾ�ر�	
	bool bRedundancy;		///< ���࿪��
	bool bSnapShot;			///< ���տ���	
	int iPacketLength;		///< ¼�������ȣ����ӣ�[1, 255]
	int iRecordMode;		///< ¼��ģʽ��0 �رգ�1 ��ֹ 2 ����
	SDK_CONFIG_WORKSHEET wcWorkSheet;			///< ¼��ʱ���	
	unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];		///< ¼����������
};

//¼�����ýṹ��
struct SDK_RECORDCONFIG_ALL
{
	SDK_RECORDCONFIG vRecordConfigAll[NET_MAX_CHANNUM];
};

///< ͼƬ����
struct SDK_SnapshotConfig
{
	int iPreSnap;			///< ԤץͼƬ��
	bool bRedundancy;		///< ���࿪��
	int iSnapMode;		///< ¼��ģʽ����RecordModeTypes
	SDK_CONFIG_WORKSHEET wcWorkSheet;				///< ¼��ʱ���	
	unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];	///< ¼���������룬��enum RecordTypes
};

struct SDK_SnapshotConfigAll
{
	SDK_SnapshotConfig vSnapshotConfigAll[NET_MAX_CHANNUM];
};


//������ؽṹ��
//  ��̨�����ṹ
struct SDK_PtzLinkConfig
{
	int iType;		// ���������� 
	int iValue;		// ���������Ͷ�Ӧ��ֵ 
};

#define CHANNELNAME_MAX_LEN 64  //ͨ��������󳤶�

struct SDK_EventHandler
{
	unsigned int	dwRecord;				// ¼������ 
	int		iRecordLatch;			// ¼����ʱ��10��300 sec  	
	unsigned int	dwTour;					// ��Ѳ���� 	
	unsigned int	dwSnapShot;				// ץͼ���� 
	unsigned int	dwAlarmOut;				// �������ͨ������ 
	unsigned int	dwMatrix;				// �������� 
	int		iEventLatch;			// ������ʼ��ʱʱ�䣬sΪ��λ 
	int		iAOLatch;				// ���������ʱ��10��300 sec  
	SDK_PtzLinkConfig PtzLink[NET_MAX_CHANNUM];		// ��̨������ 
	SDK_CONFIG_WORKSHEET schedule;		// ¼��ʱ���

	bool	bRecordEn;				// ¼��ʹ�� 
	bool	bTourEn;				// ��Ѳʹ�� 
	bool	bSnapEn;				// ץͼʹ�� 	
	bool	bAlarmOutEn;			// ����ʹ�� 
	bool	bPtzEn;

	// ��̨����ʹ�� 
	bool	bTip;					// ��Ļ��ʾʹ�� 	
	bool	bMail;					// �����ʼ� 	
	bool	bMessage;				// ������Ϣ���������� 	
	bool	bBeep;					// ���� 	
	bool	bVoice;					// ������ʾ 		
	bool	bFTP;					// ����FTP���� 
	bool	bMatrixEn;				// ����ʹ�� 
	bool	bLog;					// ��־ʹ��
	bool	bMessagetoNet;			// ��Ϣ�ϴ�������ʹ�� 

	bool    bShowInfo;              // �Ƿ���GUI�Ϻͱ�������ʾ������Ϣ
	unsigned int    dwShowInfoMask;         // Ҫ������ʾ������Ϣ��ͨ������
	char    pAlarmInfo[CHANNELNAME_MAX_LEN];//Ҫ��ʾ�ı�����Ϣ

	bool    bShortMsg;              //���Ͷ���
	bool    bMultimediaMsg;         //���Ͳ���
};

//����ģʽ����NVR
typedef struct _SDK_FACE_CAPTURE_MODE
{
	int	CaptureMode[4];		//Para Value:0 ���߶���ѡ��1ǰץ��2��ץ
}SDK_FACE_CAPTURE_MODE;

enum SDK_ANALYSE_MODE
{
	SDK_ANALYSE_TRIPWIRE = 0, //������
	SDK_ANALYSE_PERIMETER     //�ܽ���
};
/** �ܽ���ģʽ */
enum SDK_URP_PERIMETER_MODE_E
{
	SDK_URP_PMODE_INTRUSION = 0,			/**< ���� */
	SDK_URP_PMODE_ENTER,				/**< ���� */
	SDK_URP_PMODE_EXIT				/**< �뿪 */
};

/** ���߽���� */
#define SDK_MAX_BOUNDARY_POINT_NUM 8
#define SDK_MAX_POINT_NUM 4
#define SDK_NAME_BUF_SIZE 16

/** ����� */
struct URP_SDK_POINT_S
{
	short X;					/**< x */
	short Y;					/**< y */
};

/** �߽ṹ */
struct SDK_URP_LINE_S
{
	URP_SDK_POINT_S stStartPt;			/**< �߶���� */
	URP_SDK_POINT_S stEndPt;			/**< �߶��յ� */
};

struct SDK_URP_POLYGON_REGION_S
{
	int iValid;
	int iPointNum;
	URP_SDK_POINT_S astPoint[SDK_MAX_BOUNDARY_POINT_NUM];
};

/** URP�ܽ���߽�� */
struct SDK_URP_PERIMETER_LIMIT_BOUNDARY_S
{
	int      iBoundaryPtNum;					/**< �߽����Ŀ */
	URP_SDK_POINT_S   astBoundaryPts[SDK_MAX_BOUNDARY_POINT_NUM];	/**< �߽�㼯�� */
};

/** URP�ܽ������Ʋ��� */
struct SDK_URP_PERIMETER_LIMIT_PARA_S
{
	int iMinDist;						/**< ��С���ؾ��� */
	int iMinTime;						/**< ���ʱ�� */
	int	iDirectionLimit;					/**< �Ƿ����������� */
	int iForbiddenDirection;					/**< ��ֹ����Ƕ�(��λ: �Ƕ�) */
	SDK_URP_PERIMETER_LIMIT_BOUNDARY_S stBoundary;			/**< �ܽ�߽����� */
};

/** URP�ܽ��������� */
struct SDK_URP_PERIMETER_RULE_PARA_S
{
	int iTypeLimit;						/**< Ŀ���������� */
	int iTypeHuman;						/**< Ŀ�������(�޶�����ʱʹ��) */
	int iTypeVehicle;						/**< Ŀ����𣺳� */
	int iMode;						/**< �ܽ�ģʽ */
	SDK_URP_PERIMETER_LIMIT_PARA_S stLimitPara;				/**< �ܽ����Ʋ��� */
} ;

// ----------------------------------------------------------------------
//  �������ݽṹ
/** URP������������� */
#define SDK_URP_MAX_TRIPWIRE_CNT 8

/** URP�����߽ṹ */
struct SDK_URP_TRIPWIRE_S
{
	int     iValid;						/**< �Ƿ���Ч */
	int    iIsDoubleDirection;				/**< ��ʾ�ð����Ƿ�Ϊ˫�����(0: ��, 1: ��) */
	int     iForbiddenDirection;				/**< �����߽�ֹ����*/
	SDK_URP_LINE_S	stLine;						/**< ������λ�� */
};

/** URP���������Ʋ��� */
struct SDK_URP_TRIPWIRE_LIMIT_PARA_S
{
	int iMinDist;						/**< ��С���ؾ��� */
	int iMinTime;						/**< ���ʱ�� */
};

/** URP�����߹������ */
struct SDK_URP_TRIPWIRE_RULE_PARA_S
{
	int iTypeLimit;						/**< Ŀ���������� */
	int iTypeHuman;						/**< Ŀ�������(�޶�����ʱʹ��) */
	int iTypeVehicle;						/**< Ŀ����𣺳� */
	SDK_URP_TRIPWIRE_S astLines[SDK_URP_MAX_TRIPWIRE_CNT];		/**< ������ */
	SDK_URP_TRIPWIRE_LIMIT_PARA_S stLimitPara;				/**< ���������Ʋ��� */
};


/** URPĿ����������ȼ��� */
enum SDK_SENSITIVITY_LEVEL_E
{
	SDK_HIGH_LEVEL_SENSITIVITY,         /**< �������� */
	SDK_MIDDLE_LEVEL_SENSITIVITY,		/**< �������� */
	SDK_LOW_LEVEL_SENSITIVITY			/**< �������� */
};

/** �㷨ģ�� */

enum SDK_MODULE_TYPE
{
	SDK_MODULE_TYPE_PEA = 0,
	SDK_MODULE_TYPE_OSC,
	SDK_MODULE_TYPE_AVD,
	SDK_MODULE_TYPE_ALL
};

// ----------------------------------------------------------------------
// ���濪ʼ���Զ���ṹ

struct SDK_PEA_RULE_S
{
	int iShowTrack;						/// �Ƿ���ʾ�켣
	int iShowRule;						/// �Ƿ���ʾ����
	int iLevel;						/// ���伶�������ȣ�0���߼���Ĭ��ֵ����1���м���2���ͼ���
	int iPerimeterEnable;					/// �ܽ����ʹ��
	SDK_URP_PERIMETER_RULE_PARA_S	stPerimeterRulePara;	/**< �ܽ��� */
	int iTripWireEnable;					/// �����߹���ʹ��
	SDK_URP_TRIPWIRE_RULE_PARA_S	stTripwireRulePara;	/**< �����߼�� */
};

/// �㷨�����ṹ
struct SDK_CAPS					/// ��1��ʾ��ͨ��֧�ֶ�Ӧ�������㷨����0��ʾ��֧�֡�
{
	int dwPEA;
	int dwAVD;
	int dwVFD;
	int dwAAI;
	int dwOSC;
	int iResv[3];
} ;

struct SDK_PEA_STATUS_S
{
	int dwPerimeter;					/// ���ּ��״̬�������˰��ߺ��ܽ�,��uintֵ�Ǹ�����������ͨ������״̬�����롣
	/// ��ͨ���ڵ�λ����ͨ���ڸ�λ��������1���ޱ�����0�������ڵ�ͨ����0��
	int iResv[4];
	int avdStatue;
};


//��Ʒ����-begin
#define NET_MAX_OSC_NUM 4
#define NET_MAX_POINT_NUM 4
#define NET_NAME_BUF_SIZE 16

struct SDK_URP_OSC_SPECL_REGIONS_S
{
	int nValid; //�Ƿ���Ч
	char chName[NET_NAME_BUF_SIZE]; //��������
	SDK_URP_POLYGON_REGION_S stOscRg; //Ҫ���������
	SDK_URP_POLYGON_REGION_S astSubRgA; //��������е���Ч������
	SDK_URP_POLYGON_REGION_S astSubRgB; //��������е���Ч������
	SDK_URP_POLYGON_REGION_S astSubRgC; //��������е���Ч������
};

struct SDK_URP_OSC_LMT_PARA_S
{
	int nTimeMin; //ʱ��Լ��
	int nSizeMin; //��С�ߴ�
	int nSizeMax; //���ߴ�
} ;

struct SDK_URP_OSC_RULE_PARA_S
{
	int nSceneType; //��������
	int nCameraType; //�������
	SDK_URP_OSC_SPECL_REGIONS_S astSpclRgs[NET_MAX_OSC_NUM]; //Ҫ������������
	SDK_URP_OSC_LMT_PARA_S stOscPara; //һЩԼ��
} ;

struct SDK_OSC_RULE_S
{
	int iShowTrack;				/// �Ƿ���ʾ�켣
	int iShowRule;						     /// �Ƿ���ʾ����
	int iLevel;						     /// ���伶��0���Ǿ�����Ĭ��ֵ����1���ͼ���2���м���3: �߼�
	int iAbandumEnable;		   	/// ��Ʒ����ʹ��
	SDK_URP_OSC_RULE_PARA_S stObjAbandumRulePara; /// ��Ʒ��������
	int iStolenEnable;			  	 /// ��Ʒ����ʹ��
	SDK_URP_OSC_RULE_PARA_S stObjStolenRulePara;   /// ��Ʒ��������
	int iNoParkingEnable;		 	  	 /// �Ƿ�ͣ��ʹ��
	SDK_URP_OSC_RULE_PARA_S stNoParkingRulePara;   /// �Ƿ�ͣ������
};


struct SDK_AVD_RULE_S
{
	int iLevel;						     /// �����ȵ�λ��1-5������ֵԽ��Խ����Խ�ױ���
	int itBrightAbnmlEnable;				///< �����쳣ʹ��
	int iClarityEnable;					///< �����ȼ��ʹ��
	int iNoiseEnable;					///< �������ʹ��
	int iColorEnable;					///< ƫɫ���ʹ��
	int iFreezeEnable;					///< ���涳����ʹ��
	int iNosignalEnable;					///< �ź�ȱʧ���ʹ��
	int iChangeEnable;					///< �����任���ʹ��
	int iInterfereEnable;					///< ��Ϊ���ż��ʹ�� 
	int iPtzLoseCtlEnable;					///< PTZʧ�ؼ��ʹ��
};

/** ����� */
struct SDK_URP_IMP_POINT_S
{
	short s16X;					/**< x */
	short s16Y;					/**< y */
};

struct SDK_CPC_RULE_S
{
	SDK_URP_IMP_POINT_S stRulePoint[4];	///��������Ҫ����4����	
	int s32Sizemin;			///��С���(0,height/2)
	int s32Sizemax;			///������(sizemin, height/2)
	int s32Countmax;			///���Ŀ����[1~15],
	int s32Sensitivity;		/// �����ȵ�λ��1-5������ֵԽ��Խ����Խ�ױ���	
	unsigned int u32Flag;				///��־λ�������жϽ�����Ĭ����0
	int s32EnterDirection;	///����ķ���
};

//�����㷨�Ĺ������ü���
struct SDK_RULECONFIG
{
	SDK_PEA_RULE_S stRulePea;   //�ܽ������������
	SDK_OSC_RULE_S stRuleOSC; //��Ʒ���ơ��������Ƿ�ͣ������
	SDK_AVD_RULE_S stRuleAVD;//�쳣��Ƶ�ź��������
	SDK_CPC_RULE_S stRuleCPC; //��ͷ�����㷨����
};


//һ��ͨ�������ܷ�������
struct SDK_ANALYSECONFIG
{
	bool         bEnable;      //�Ƿ�������Ƶ��������
	int          moduleType;   //ʹ�õ������㷨ģ��
	SDK_EventHandler hEvent;  //�����¼�
	SDK_RULECONFIG   stRuleConfig; //�����㷨�Ĺ�������
};

//����ͨ�������ܷ�������
struct SDK_ANALYSECONFIG_ALL
{
	SDK_ANALYSECONFIG vAnalyzeAll[NET_MAX_CHANNUM];
};

//���ܷ�������
struct SDK_ANALYZEABILITY
{
	UINT uIntelPEA; //����PEA֧�֣�λ��Ӧͨ��
	UINT uAlgorithmPEA;//PEA֧�ֵ��㷨���ͣ��������
	UINT uIntelOSC; //����OSC֧�֣�λ��Ӧͨ��
	UINT uAlgorithmOSC;//OSC֧�ֵ��㷨����
	UINT uIntelAVD; //����AVD֧�֣�λ��Ӧͨ��
	UINT uAlgorithmAVD;//AVD֧�ֵ��㷨����
	UINT uIntelCPC; //����������֧�֣�λ��Ӧͨ��
	UINT uAlgorithmCPC;//CPC֧�ֵ��㷨����
};



///< ��̬�������
struct SDK_MOTIONCONFIG
{
	bool bEnable;							// ��̬��⿪�� 
	int iLevel;								// ������ 
	unsigned int mRegion[NET_MD_REGION_ROW];			// ����ÿһ��ʹ��һ�������ƴ� 	
	SDK_EventHandler hEvent;					// ��̬������� 
};

/// ȫͨ����̬�������
struct SDK_MOTIONCONFIG_ALL
{
	SDK_MOTIONCONFIG vMotionDetectAll[NET_MAX_CHANNUM];
};

///< �ڵ��������
struct SDK_BLINDDETECTCONFIG
{
	bool	bEnable;		///< �ڵ���⿪��
	int		iLevel;			///< �����ȣ�1��6
	SDK_EventHandler hEvent;	///< �ڵ��������
};

/// ȫͨ���ڵ��������
struct SDK_BLINDDETECTCONFIG_ALL
{
	SDK_BLINDDETECTCONFIG vBlindDetectAll[NET_MAX_CHANNUM];
};

///< �����¼��ṹ
struct SDK_VIDEOLOSSCONFIG
{
	bool bEnable;			///< ʹ��
	SDK_EventHandler hEvent;	///< �������
};

/// ����ͨ���Ļ���ʱ��ṹ
struct SDK_VIDEOLOSSCONFIG_ALL
{
	SDK_VIDEOLOSSCONFIG vGenericEventConfig[NET_MAX_CHANNUM];
};

///< ������������
struct SDK_ALARM_INPUTCONFIG
{
	bool	bEnable;		///< �������뿪��
	int		iSensorType;	///< ���������ͳ��� or ����
	SDK_EventHandler hEvent;	///< ��������
};

///< ����ͨ���ı�����������
struct SDK_ALARM_INPUTCONFIG_ALL
{
	SDK_ALARM_INPUTCONFIG vAlarmConfigAll[NET_MAX_CHANNUM];
};

///< ��·����
struct SDK_NETALARMCONFIG
{
	bool bEnable;			///< ʹ��
	SDK_EventHandler hEvent;	///< �������
};

/// ����ͨ������·�����ṹ
struct SDK_NETALARMCONFIG_ALL
{
	SDK_NETALARMCONFIG vNetAlarmConfig[NET_MAX_CHANNUM];
};

///< ���ر����������
struct SDK_AlarmOutConfig
{
	int nAlarmOutType;		///< �����������: ����,�ֶ�,�ر�
	int nAlarmOutStatus;    ///< ����״̬: 0:�� 1;�պ�
};

///< Ӳ�����������¼��ṹ
struct SDK_StorageLowSpaceConfig
{
	bool bEnable;
	int iLowerLimit;		///< Ӳ��ʣ����������, �ٷ���
	SDK_EventHandler hEvent;	///< �������
	bool bRecordTimeEnable;
	int iRecordTime;		///<¼������
};

///< ����ͨ���ı����������
struct SDK_AlarmOutConfigAll
{
	SDK_AlarmOutConfig vAlarmOutConfigAll[NET_MAX_CHANNUM];
};

/// ����ͨ���Ľ�������ַ����V2�汾
struct SDK_AbilitySerialNo
{
	char serialNo[NET_MAX_SERIALNO_LENGTH];
	char productType[NET_MAX_SERIALNO_LENGTH];
};

///< ��������Ϣ�ṹ
struct SDK_DriverInformation 
{
	int		iDriverType;		///< ����������
	bool	bIsCurrent;			///< �Ƿ�Ϊ��ǰ������
	unsigned int	uiTotalSpace;		///< ��������MBΪ��λ
	unsigned int	uiRemainSpace;		///< ʣ��������MBΪ��λ
	int		iStatus;			///< �����־���ļ�ϵͳ��ʼ��ʱ������
	int		iLogicSerialNo;				///< �߼����
	SDK_SYSTEM_TIME  tmStartTimeNew;		///< ��¼��ʱ��εĿ�ʼʱ��
	SDK_SYSTEM_TIME	 tmEndTimeNew;			///< ��¼��ʱ��εĽ���ʱ��
	SDK_SYSTEM_TIME	 tmStartTimeOld;		///< ��¼��ʱ��εĿ�ʼʱ��
	SDK_SYSTEM_TIME	 tmEndTimeOld;			///< ��¼��ʱ��εĽ���ʱ��
};
enum
{
	SDK_MAX_DRIVER_PER_DISK = 2,	///< ÿ���������ķ�����
	SDK_MAX_DISK_PER_MACHINE = 8,	///< ���֧��8��Ӳ��
};
//Ӳ�̹���
struct SDK_STORAGEDISK
{
	int		iPhysicalNo;
	int		iPartNumber;		// ������
	SDK_DriverInformation diPartitions[SDK_MAX_DRIVER_PER_DISK];
};

struct SDK_StorageDeviceInformationAll
{
	int iDiskNumber;
	SDK_STORAGEDISK vStorageDeviceInfoAll[SDK_MAX_DISK_PER_MACHINE];
};

/// �洢�豸��������
enum SDK_StorageDeviceControlTypes
{
	SDK_STORAGE_DEVICE_CONTROL_SETTYPE,		///< ��������
	SDK_STORAGE_DEVICE_CONTROL_RECOVER,		///< �ָ�����
	SDK_STORAGE_DEVICE_CONTROL_PARTITIONS,	///< ��������
	SDK_STORAGE_DEVICE_CONTROL_CLEAR,		///< �������
	SDK_STORAGE_DEVICE_CONTROL_NR,
};

/// ���������������
enum SDK_StorageDeviceClearTypes
{
	SDK_STORAGE_DEVICE_CLEAR_DATA,			///< ���¼������
	SDK_STORAGE_DEVICE_CLEAR_PARTITIONS,	///< �������
	SDK_STORAGE_DEVICE_CLEAR_NR,
};

/// ����������
enum SDK_FileSystemDriverTypes
{
	SDK_DRIVER_READ_WRITE	= 0,	///< ��д������
	SDK_DRIVER_READ_ONLY	= 1,	///< ֻ��������
	SDK_DRIVER_EVENTS		= 2,	///< �¼�������
	SDK_DRIVER_REDUNDANT	= 3,	///< ����������
	SDK_DRIVER_SNAPSHOT		= 4,	///< ����������
	SDK_DRIVER_TYPE_NR		= 5,	///< ���������͸���
	SDK_DRIVER_UNUSED		= 0xff,	///< û��ʹ�õ��������ṹ
};

/// �洢�豸����
struct SDK_StorageDeviceControl
{
	int iAction;	///< ��enum SDK_StorageDeviceControlTypes
	int iSerialNo;	///< �������к�
	int iPartNo;    ///< ������
	int iType;		///< enum SDK_StorageDeviceClearTypes����SDK_FileSystemDriverTypes
	int iPartSize[2/*MAX_DRIVER_PER_DISK*/];	///< ���������Ĵ�С
};

/// �豸����
enum SDK_DeviceType
{
	SDK_DEVICE_TYPE_DVR,	///< ��ͨDVR�豸
	SDK_DEVICE_TYPE_NVS,	///< NVS�豸
	SDK_DEVICE_TYPE_IPC,	///< IPC�豸
	SDK_DEVICE_TYPE_HVR,	///<���dvr
	SDK_DEVICE_TYPE_IVR,	///<����dvr
	SDK_DEVICE_TYPE_MVR,	///<����dvr
	SDK_DEVICE_TYPE_NR
};

/// �豸��Ϣ
typedef struct _VIDEONET_DEVICEINFO
{
	char sSoftWareVersion[64];	///< ����汾��Ϣ
	char sHardWareVersion[64];	///< Ӳ���汾��Ϣ
	char sWebVersion[64];	 ///< ҳ��汾��Ϣ
	SDK_SYSTEM_TIME tmBuildTime;///< �������ʱ��
	char sSerialNumber[64];	 ///< �豸���к�
	int byChanNum;	 ///< ��Ƶ����ͨ����
	int iVideoOutChannel;	 ///< ��Ƶ���ͨ����
	int byAlarmInPortNum;	 ///< ��������ͨ����
	int byAlarmOutPortNum;	 ///< �������ͨ����
	int iTalkInChannel;	 ///< �Խ�����ͨ����
	int iTalkOutChannel;	 ///< �Խ����ͨ����
	int iExtraChannel;	 ///< ��չͨ����
	int iAudioInChannel;	 ///< ��Ƶ����ͨ����
	int iCombineSwitch;	 ///< ��ϱ���ͨ���ָ�ģʽ�Ƿ�֧���л�
	int iDigChannel;	 ///<����ͨ����
	unsigned int uiDeviceRunTime;	///<ϵͳ����ʱ��
	SDK_DeviceType deviceTye;	///�豸����
	char sHardWare[64];	 ///<�豸�ͺ�
	char uUpdataTime[20];	 ///<�������� ���� 2018-09-03 16:26:56
	unsigned int uUpdataType;	///<��������
	char sDeviceModel[16];       //�豸�ͺ�(�ײ��Ӽ������ã�sHardWare��Զ���豸��ͬһ����������������ֲ���) 
	int nLanguage;//���ҵ�����ID,0Ӣ�� 1���� 2���ķ��� 3���� 4���� 5�������� 6����
	char szOnvifModel[32];
	char sProtocol[16];
	char res[112];
}VIDEONET_DEVICEINFO,*LPVIDEONET_DEVICEINFO;

//��������ص�����
struct VIDEONET_ACTIVEREG_INFO
{
	char deviceSarialID[64];//�豸���кţ��������64λ��ֵ0
	VIDEONET_DEVICEINFO deviceInfo;//�豸��Ϣ
	char IP[IP_SIZE];   //����IP
};
///< �Զ�ά������
struct SDK_AutoMaintainConfig
{
	int iAutoRebootDay;				///< �Զ�������������
	int iAutoRebootHour;			///< ��������ʱ��	[0, 23]	
	int iAutoDeleteFilesDays;		///< �Զ�ɾ���ļ�ʱ��[0, 30]
};

/// Ĭ����������
enum SDK_DefaultConfigKinds
{
	SDK_DEFAULT_CFG_GENERAL,			// ��ͨ����
	SDK_DEFAULT_CFG_ENCODE,				// ��������
	SDK_DEFAULT_CFG_RECORD,				// ¼������
	SDK_DEFAULT_CFG_NET_SERVICE,		// �������
	SDK_DEFAULT_CFG_NET_COMMON,			// ͨ������
	SDK_DEFAULT_CFG_ALARM,				// ����
	SDK_DEFAULT_CFG_PTZCOMM,			// ��̨������
	SDK_DEFAULT_CFG_USERMANAGER,		// �û�����
	SDK_DEFAULT_CFG_PREVIEW,			// Ԥ������
	SDK_DEFAULT_CFG_CAMERA_PARAM,            // ��������ͷ����
	SDK_DEFAULT_CFG_END,
};

/// �ָ���Ĭ����������
struct SDK_SetDefaultConfigTypes
{
	bool vSetDefaultKinds[SDK_DEFAULT_CFG_END];
}; 


typedef struct VIDEONET_CLIENTINFO{
	int nChannel;	//ͨ����
	int nStream;	//0��ʾ��������Ϊ1��ʾ������
	int nMode;		//0��TCP��ʽ,1��UDP��ʽ,2���ಥ��ʽ,3 - RTP��ʽ��4-����Ƶ�ֿ�(TCP)
	int nComType;	//ֻ����ϱ���ͨ����Ч, ��ϱ���ͨ����ƴͼģʽ
}*LPVIDEONET_CLIENTINFO;


#define		RECORDE_FILE_LENGTH		108
enum SDK_File_Type
{
	SDK_RECORD_ALL = 0,
	SDK_RECORD_ALARM = 1, //�ⲿ����¼��
	SDK_RECORD_DETECT,	  //��Ƶ���¼��
	SDK_RECORD_REGULAR,	  //��ͨ¼��
	SDK_RECORD_MANUAL,	  //�ֶ�¼��
	SDK_PIC_ALL = 10,
	SDK_PIC_ALARM,		  //�ⲿ����¼��
	SDK_PIC_DETECT,		  //��Ƶ���¼��
	SDK_PIC_REGULAR,      //��ͨ¼��
	SDK_PIC_MANUAL,       //�ֶ�¼��
	SDK_TYPE_NUM,
	SDK_PIC_FACE = 20,		//����
	SDK_PIC_CARNO,			//����
	SDK_PIC_WIFI,			//wifi̽��
	SDK_FACE_QUERY_RECORD,  //��������¼��
};

//��ѯ¼������
struct VIDEONET_FINDINFO
{
	int nChannelN0;			//ͨ����
	int nFileType;			//�ļ�����, ��SDK_File_Type
	VIDEONET_TIME startTime;	//��ʼʱ��
	VIDEONET_TIME endTime;	//����ʱ��
	char szFileName[32];		//�ļ�����Ϊ�յĻ���ϵͳ������ֵ��ϵͳ����
};

//¼���ļ����ؽṹ��
struct VIDEONET_FILE_DATA 
{
	int ch;						//ͨ����
	int size;					//�ļ���С
	char sFileName[RECORDE_FILE_LENGTH];		///< �ļ���
	SDK_SYSTEM_TIME stBeginTime;	///< �ļ���ʼʱ��
	SDK_SYSTEM_TIME stEndTime;		///< �ļ�����ʱ��
};

/**************************************ͼƬ����*************************************************************/

#define		CARDNUM_LEN			40
#define		MAX_LICENSE_LEN		16
#define		MAX_FACE_PIC_NUM	30

//ͼƬ����������
enum JVT_VCA_OPERATE_TYPE
{  
	JVT_VCA_LICENSE_TYPE       = 0x1,	//���ƺ���
	JVT_VCA_PLATECOLOR_TYPE    = 0x2,	//������ɫ
	JVT_VCA_CARDNO_TYPE        = 0x4,	//����
	JVT_VCA_PLATETYPE_TYPE     = 0x8,	//��������
	JVT_VCA_LISTTYPE_TYPE      = 0x10,	//������������
	JVT_VCA_INDEX_TYPE         = 0x20,	//������ˮ��
	JVT_VCA_OPERATE_INDEX_TYPE = 0x40	//������
};

//��������
enum JVT_VCA_VEHICLE_TYPE
{
	JVT_VCA_OTHER_TYPE          = 0x1,	//��������
	JVT_VCA_SMALLCAR_TYPE       = 0x2,  //С�ͳ�
	JVT_VCA_BIGCAR_TYPE         = 0x4,	//���ͳ� 
	JVT_VCA_BUS_TYPE            = 0x8,  //�ͳ�
	JVT_VCA_TRUCK_TYPE          = 0x10,	//����
	JVT_VCA_CAR_TYPE            = 0x20,	//�γ�
	JVT_VCA_MINIBUS_TYPE        = 0x40,	//�����
	JVT_VCA_SMALL_TRUCK_TYPE    = 0x80	//С����
};

//ͼƬ��ѯ����
typedef struct SDK_PICTURE_FINDINFO
{
	DWORD            dwSize;		//�ṹ���С
	LONG             lChannel;		//ͨ����
	BYTE             byFileType;	//����ͼƬ���ͣ���SDK_File_Type 20-������21-���ƣ�22-̽����Ϣ��0xff-ȫ������
	BYTE             byNeedCard;	//�Ƿ���Ҫ����
	BYTE             byProvince;	//ʡ�������ţ�0-������1-�ģ�2-��
	BYTE             sCardNum[CARDNUM_LEN];  //����
	SDK_SYSTEM_TIME     startTime;				//����ͼƬ�Ŀ�ʼʱ��
	SDK_SYSTEM_TIME     endTime;				//����ͼƬ�Ľ���ʱ��
	DWORD            dwTrafficType;				//ͼƬ����������
	DWORD            dwVehicleType;				//��������			
	DWORD            dwIllegalType;				//Υ��������
	BYTE             byLaneNo;					//������
	BYTE             bySubHvtType;				//���м����������ͣ�0- ȫ���� 1- ������(��������������֧�ֳ��Ƽ�����ʡ�ݼ���)��2-�ǻ�������3- ���� 

	char             sLicense[MAX_LICENSE_LEN];	//���ƺ��루byFileTypeΪ�������ʱ��Ч��
	BYTE             byRegion;					//��������ֵ��0- ������1- ŷ��(Europe Region)��2- ����˹(Russian Region)��3- ŷ��&����˹(EU&CIS)��0xff- ���� 
	BYTE             byCountry;					//��������ֵ
	float			 similarity;			//���ƶ�
	int				 sorttype;				//����ʽ 0�����ƶ�����  1��ʱ������(��С����)   2��ʱ������(�Ӵ�С)
	char			 filepath[128];			//ͼƬ����·��(�����ļ���)
	BYTE             byRes3[20];					//��������Ϊ0
}*LPSDK_PICTURE_FINDINFO;

////���������ṹ��
//typedef struct NET_VCA_RECT
//{
//	float   fX;  
//	float   fY;  
//	float   fWidth;  
//	float   fHeight;
//}*LPNET_VCA_RECT;
////�������ץͼ������Ϣ�ṹ��
//typedef struct NET_FACE_EXTRA_INFO
//{
//	NET_VCA_RECT    struVcaRect[MAX_FACE_PIC_NUM];
//	BYTE            byRes[64];
//}*LPNET_DVR_FACE_EXTRA_INFO;
//
////�������ץͼ������Ϣ�ṹ��
//typedef union PIC_EXTRA_INFO_UNION
//{
//	BYTE                       byUnionLen[544];
//	NET_FACE_EXTRA_INFO    struFaceExtraInfo;
//}*LPPIC_EXTRA_INFO_UNION;


//ͼƬ��������
typedef struct SDK_VIDEONET_PICTURE_DATA
{  
	int					nChannel;					//ͨ����
	char				sFileName[RECORDE_FILE_LENGTH];				//ͼƬ����
	SDK_SYSTEM_TIME		netTime;					//ͼƬ��ʱ��
	DWORD				dwFileSize;					//ͼƬ�Ĵ�С
	char				sCardNum[CARDNUM_LEN];		//����
	BYTE				byPlateColor;				//������ɫ
	BYTE				byVehicleLogo;				//����Ʒ��
	BYTE				byFileType;					//�ļ�����
	BYTE				byRecogResult;				//����ʶ����:0- δ֪��1- �ͳ���2- ������3- �γ���4- �������5- С������6- ���ˣ�7- ���ֳ���8- ���ֳ���9- SUV/MPV��10- ���Ϳͳ���11- ��������12- �ǻ�����
	char				sLicense[MAX_LICENSE_LEN];	//
	BYTE				byEventSearchStatus;		//
	char				sIpV4[16];					//IP��ַ
	BYTE				sIpV6[128];					//
	WORD				wPort;						//�˿ں�
	BYTE				byRes[256];					//����
	BYTE*				pPicExtraInfo;				//ͼƬ������Ϣ
	DWORD				dwExtraLen;					//������Ϣ����
}*LPSDK_VIDEONET_PICTURE_DATA;
/***************************************************************************************************************************/
//����linuxSDK�ṹ��Ϣ
//ͼƬ��ѯ����
typedef struct PICTURE_FINDINFO
{
	int              lChannel;				//ͨ����:����ķ�ʽ
	int				 sorttype;				//����ʽ 0�����ƶ�����  1��ʱ������(��С����)   2��ʱ������(�Ӵ�С)
	int              byFileType;			//����ͼƬ���ͣ���SDK_File_Type 20-������21-���ƣ�22-̽����Ϣ��0xff-ȫ������
	float			 similarity;			//���ƶ�
	SDK_SYSTEM_TIME  startTime;				//����ͼƬ�Ŀ�ʼʱ��
	SDK_SYSTEM_TIME  endTime;				//����ͼƬ�Ľ���ʱ��
	char			 filepath[128];			//ͼƬ����·��(�����ļ���)
}*LPPICTURE_FINDINFO;

typedef struct PICTURE_DATA
{
	short			 index;
	short			 channel;				//ͼƬ����¼������ͨ����
	int              size;					//ͼƬ��С����¼��ʱ��,ͼƬ��С���ֽ�Ϊ��λ
	float			 similarity;			//���ƶ�
	SDK_SYSTEM_TIME  capturetime;			//ͼƬץ��ʱ�����¼��ʼʱ��
	char			 filepath[128];			//ͼƬ��¼������·��(�����ļ���)
}*LPPICTURE_DATA;

//ͼƬ��ѯ����
typedef struct VIDEONET_PICTURE_DATA
{
	int              photonum;				//ͼƬ��Ŀ
	PICTURE_DATA	 photodata[5000];			
}*LPVIDEONET_PICTURE_DATA;

//�طŶ���
enum SEDK_PlayBackAction
{
	SDK_PLAY_BACK_PAUSE,		/*<! ��ͣ�ط� */
	SDK_PLAY_BACK_CONTINUE,		/*<! �����ط� */
	SDK_PLAY_BACK_SEEK,			/*<! �طŶ�λ��ʱ��sΪ��λ */
	SDK_PLAY_BACK_FAST,	        /*<! ���ٻط� */
	SDK_PLAY_BACK_SLOW,	        /*<! ���ٻط� */
	SDK_PLAY_BACK_SEEK_PERCENT, /*<! �طŶ�λ�ٷֱ� */
};

//��ʱ��β�ѯ
struct SDK_SearchByTime
{
	int nHighChannel;			///< 33~64¼��ͨ��������
	int nLowChannel;			///< 1~32¼��ͨ��������
	int nFileType;              ///< �ļ�����, ��SDK_File_Type
	SDK_SYSTEM_TIME stBeginTime;	    ///< ��ѯ��ʼʱ��
	SDK_SYSTEM_TIME stEndTime;		///< ��ѯ����ʱ��
	int    iSync;               ///< �Ƿ���Ҫͬ��
};

//ÿ��ͨ����¼����Ϣ
struct SDK_SearchByTimeInfo
{
	int iChannel;			    ///< ¼��ͨ����
	///< ¼���¼��720���ֽڵ�5760λ����ʾһ���е�1440����
	///< 0000:��¼�� 0001:F_COMMON 0002:F_ALERT 0003:F_DYNAMIC 0004:F_CARD 0005:F_HAND
	unsigned char cRecordBitMap[720];
};

struct SDK_SearchByTimeResult
{
	int nInfoNum;										 ///< ͨ����¼���¼��Ϣ����
	SDK_SearchByTimeInfo ByTimeInfo[NET_MAX_CHANNUM];    ///< ͨ����¼���¼��Ϣ
};

//������Ϣ
typedef struct SDK_ALARM_INFO
{
	int nChannel;
	int iEvent;
	int iStatus;
	SDK_SYSTEM_TIME SysTime;
	char pExtInfo[128]; //������Ϣ�������ߺͽ����߶Ը��ֱ������ͽ��и�ʽԼ�� //by zjh add 20170830
}SDK_AlarmInfo;

/// ��־��ѯ����
struct SDK_LogSearchCondition
{
	int nType;	///< ��־����
	int iLogPosition;			///< ���ϴβ�ѯ�Ľ���ʱ����־ָ��
	SDK_SYSTEM_TIME stBeginTime;	///< ��ѯ��־��ʼʱ��
	SDK_SYSTEM_TIME stEndTime;		///< ��ѯ��־����ʱ��
};


struct SDK_LogItem
{
	char sType[24];	///< ��־����
	char sUser[32];	///< ��־�û�
	char sData[68];	///< ��־����
	SDK_SYSTEM_TIME stLogTime;	///< ��־ʱ��
	int iLogPosition;			///< ���ϴβ�ѯ�Ľ���ʱ����־ָ��
};

//��־������Ϣ
struct SDK_LogList
{
	int iNumLog;
	SDK_LogItem Logs[NET_MAX_RETURNED_LOGLIST];
};

/// �����Խ���ʽ
struct SDK_AudioInFormatConfigAll
{
	SDK_AudioInFormatConfig vAudioInFormatConfig[SDK_AUDIO_ENCODE_TYPES_NR];
};

/// �澯״̬
struct SDK_DVR_ALARMSTATE
{
	int iVideoMotion; ///< �ƶ����״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	int iVideoBlind; ///< ��Ƶ�ڵ�״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	int iVideoLoss;	///< ��Ƶ��ʧ״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	int iAlarmIn;	///< �澯����״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
	int iAlarmOut;	///< �澯���״̬,�������ʾͨ����,bit0����ͨ��һ,�Դ����� 1: �и澯 0: �޸澯
};

// ͨ��״̬
struct SDK_DVR_CHANNELSTATE
{
	bool bRecord; ///< �Ƿ�����¼��
	int iBitrate;	///< ��ǰ����
};

// DVR����״̬
struct SDK_DVR_WORKSTATE
{
	SDK_DVR_CHANNELSTATE vChnState[NET_MAX_CHANNUM];
	SDK_DVR_ALARMSTATE vAlarmState;
};


/// ����ֵ, ����������
enum SDK_NetKeyBoardValue
{
	SDK_NET_KEY_0, SDK_NET_KEY_1, SDK_NET_KEY_2, SDK_NET_KEY_3, SDK_NET_KEY_4, SDK_NET_KEY_5, SDK_NET_KEY_6, SDK_NET_KEY_7, SDK_NET_KEY_8, SDK_NET_KEY_9,
	SDK_NET_KEY_10, SDK_NET_KEY_11, SDK_NET_KEY_12, SDK_NET_KEY_13, SDK_NET_KEY_14, SDK_NET_KEY_15, SDK_NET_KEY_16, SDK_NET_KEY_10PLUS,SDK_NET_KEY_DIGIT,
	SDK_NET_KEY_UP = 20,     // �ϻ�����̨����
	SDK_NET_KEY_DOWN,        // �»�����̨����
	SDK_NET_KEY_LEFT,        // �������̨����
	SDK_NET_KEY_RIGHT,       // �һ�����̨����
	SDK_NET_KEY_SHIFT, 
	SDK_NET_KEY_PGUP,        // ��һҳ
	SDK_NET_KEY_PGDN,        // ��һҳ
	SDK_NET_KEY_RET,         // ȷ��
	SDK_NET_KEY_ESC,         // ȡ�����˳�
	SDK_NET_KEY_FUNC,        // �л����뷨
	SDK_NET_KEY_PLAY,        // ����/��ͣ
	SDK_NET_KEY_BACK,        // ����
	SDK_NET_KEY_STOP,        // ֹͣ
	SDK_NET_KEY_FAST,        // ���
	SDK_NET_KEY_SLOW,        // ����
	SDK_NET_KEY_NEXT,        // ��һ���ļ�
	SDK_NET_KEY_PREV,        // ��һ���ļ�
	SDK_NET_KEY_REC = 40,    // ¼������
	SDK_NET_KEY_SEARCH,      // ¼���ѯ
	SDK_NET_KEY_INFO,        // ϵͳ��Ϣ
	SDK_NET_KEY_ALARM,       // �澯���
	SDK_NET_KEY_ADDR,        // ң������ַ����
	SDK_NET_KEY_BACKUP,      // ����
	SDK_NET_KEY_SPLIT,       // ����ָ�ģʽ�л���ÿ��һ���л�����һ�����ģʽ
	SDK_NET_KEY_SPLIT1,      // ������
	SDK_NET_KEY_SPLIT4,      // �Ļ���
	SDK_NET_KEY_SPLIT8,      // �˻���
	SDK_NET_KEY_SPLIT9,      // �Ż���
	SDK_NET_KEY_SPLIT16,     // 16����
	SDK_NET_KEY_SHUT,        // �ػ�
	SDK_NET_KEY_MENU,        // �˵�
	SDK_NET_KEY_SPLIT25,	// 25����	
	SDK_NET_KEY_SPLIT36,     // 36����
	SDK_NET_KEY_PTZ = 60,    // ������̨����ģʽ
	SDK_NET_KEY_TELE,        // �䱶��
	SDK_NET_KEY_WIDE,        // �䱶��
	SDK_NET_KEY_IRIS_SMALL,  // ��Ȧ��
	SDK_NET_KEY_IRIS_LARGE,  // ��Ȧ��
	SDK_NET_KEY_FOCUS_NEAR,  // �۽�Զ
	SDK_NET_KEY_FOCUS_FAR,   // �۽���
	SDK_NET_KEY_BRUSH,       // ��ˢ
	SDK_NET_KEY_LIGHT,       // �ƹ�
	SDK_NET_KEY_SPRESET,     // ����Ԥ�õ�
	SDK_NET_KEY_GPRESET,     // ת��Ԥ�õ�
	SDK_NET_KEY_DPRESET,     // ���Ԥ�õ� 
	SDK_NET_KEY_PATTERN,     // ģʽ
	SDK_NET_KEY_AUTOSCAN,    // �Զ�ɨ�迪ʼ����
	SDK_NET_KEY_AUTOTOUR,    // �Զ�Ѳ��
	SDK_NET_KEY_AUTOPAN,     // ��ɨ��ʼ/����
};

/// ����״̬
enum SDK_NetKeyBoardState
{
	SDK_NET_KEYBOARD_KEYDOWN,	// ��������
	SDK_NET_KEYBOARD_KEYUP,		// �����ɿ�
};

struct SDK_NetKeyBoardData
{
	int iValue;
	int iState;
};

// ������Ϣ��ȡ
struct SDK_UpgradeInfo
{
	char szSerial[64];
	char szHardware[64];
	char szVendor[64];
	unsigned int uiLogoArea[2];
};

/// ���籨��
struct SDK_NetAlarmInfo
{
	int iEvent;  //Ŀǰδʹ��
	int iState;   //ÿbit��ʾһ��ͨ��,bit0:��һͨ��,0-�ޱ��� 1-�б���, ��������
};

enum SERIAL_TYPE
{
	RS232 = 0,
	RS485 = 1,
};


enum MEDIA_PACK_TYPE
{
	FILE_HEAD =	0,	    		// �ļ�ͷ
	VIDEO_I_FRAME = 1,			// ��ƵI֡
	VIDEO_B_FRAME =	2,			// ��ƵB֡
	VIDEO_P_FRAME = 3,			// ��ƵP֡
	VIDEO_BP_FRAME = 4,			// ��ƵBP֡
	VIDEO_BBP_FRAME	= 5,		// ��ƵB֡B֡P֡
	VIDEO_J_FRAME = 6,			// ͼƬ֡
	AUDIO_PACKET = 10,			// ��Ƶ��
};

typedef struct
{
	int		nPacketType;				// ������,��MEDIA_PACK_TYPE
	char*	pPacketBuffer;				// ��������ַ
	unsigned int	dwPacketSize;				// ���Ĵ�С

	// ����ʱ��
	int		nYear;						// ʱ��:��		
	int		nMonth;						// ʱ��:��
	int		nDay;						// ʱ��:��
	int		nHour;						// ʱ��:ʱ
	int		nMinute;					// ʱ��:��
	int		nSecond;					// ʱ��:��
	unsigned int 	dwTimeStamp;					// ���ʱ���λ����λΪ����
	unsigned int	dwTimeStampHigh;        //���ʱ���λ����λΪ����
	unsigned int   dwFrameNum;             //֡���
	unsigned int   dwFrameRate;            //֡��
	unsigned short uWidth;              //ͼ����
	unsigned short uHeight;             //ͼ��߶�
	unsigned int uEncoderType;			//��������
	unsigned int       Reserved[5];     //����
} PACKET_INFO_EX;


struct SDK_OEMInfo
{
	int nOEMID;                     //OEM ID
	char sCompanyName[NET_MAX_USERNAME_LENGTH]; //��˾��
	char sTel[NET_MAX_USERNAME_LENGTH];         //�绰
	char sAddr[NET_MAX_USERNAME_LENGTH];        //��ַ
};
typedef struct __TransComChannel//͸������
{
	SERIAL_TYPE TransComType;//SERIAL_TYPE
	unsigned int baudrate;
	unsigned int databits;
	unsigned int stopbits;
	unsigned int parity;
} TransComChannel;
enum SDK_State_Type
{
	DEV_STATE_DDNS=0,	
};

//���������.....

//�ع�����
struct SDK_ExposureCfg
{
	int  level;    //�ع�ȼ�
	unsigned int leastTime;//�Զ��ع�ʱ�����޻��ֶ��ع�ʱ�䣬��λ΢��
	unsigned int mostTime; //�Զ��ع�ʱ�����ޣ���λ΢��
	int levelTime;//�ع�ʱ�� ��λ΢��
};

//��������
struct SDK_GainCfg
{
	int gain;    //�Զ���������(�Զ���������)��̶�����ֵ
	int autoGain;//�Զ������Ƿ����ã�0:������  1:����
};

//�������������
struct SDK_CameraParam
{
	unsigned int whiteBalance;         //��ƽ��
	unsigned int dayNightColor;        //��ҹģʽ��ȡֵ�в�ɫ���Զ��л��ͺڰ�
	int elecLevel;             //�ο���ƽֵ
	unsigned int apertureMode;          //�Զ���Ȧģʽ
	unsigned int BLCMode;               //���ⲹ��ģʽ
	SDK_ExposureCfg exposureConfig;//�ع�����
	SDK_GainCfg     gainConfig;    //��������

	unsigned int PictureFlip;		//ͼƬ���·�ת
	unsigned int PictureMirror;	//ͼƬ���ҷ�ת(����)
	unsigned int RejectFlicker;	//�չ�Ʒ�������
	unsigned int EsShutter;		//���������Ź���

	int ircut_mode;		//IR-CUT�л� 0 = �����ͬ���л� 1 = �Զ��л�

	int dnc_thr;			//��ҹת����ֵ
	int ae_sensitivity;	//ae����������

	int Day_nfLevel;		//noise filter �ȼ���0-5,0���˲���1-5 ֵԽ���˲�Ч��Խ����
	int Night_nfLevel;
	int Ircut_swap;		//ircut ������= 0        ����= 1
	int BLCValue;       //���ⲹ��ֵ
	int PicWDRLevel;	//��̬
};

//�������������
struct SDK_AllCameraParam
{
	SDK_CameraParam vCameraParamAll[NET_MAX_CHANNUM];   //���е�ͨ��
};

//�ع�������
struct SDK_CameraAbility
{
	int  count;      //֧���ع��ٶ�����
	unsigned int speeds[CAMERAPARA_MAXNUM]; //�ع��ٶ�
	int  status;     //����״̬  >= 0 ����    < 0 �쳣
	int  elecLevel;  //�ο���ƽֵ
	int  luminance;  //ƽ������
	char pVersion[64];//xm 2a�汾
	char reserve[32];//����
};

//���ز��ſ���
enum SDK_LoalPlayAction
{
	SDK_Local_PLAY_PAUSE,		/*<! ��ͣ���� */
	SDK_Local_PLAY_CONTINUE,		/*<! ������������ */
	SDK_Local_PLAY_FAST,	        /*<! ���ٲ��� */
	SDK_Local_PLAY_SLOW,	        /*<! ���ٲ��� */	
	
};

//��������
struct SDK_NetShortMsgCfg
{
	bool bEnable;       //�����ֻ����ŵĹ����Ƿ�����
	char pDesPhoneNum[SDK_MAX_RECIVE_MSG_PHONE_COUNT][16];
	int  sendTimes;     //��Ҫ��ÿ���ֻ����Ͷ��ٴζ���
};
//�ֻ���������
struct SDK_NetMultimediaMsgCfg
{
	bool bEnable;				// �����ֻ����ŵĹ����Ƿ�����
	char pDesPhoneNum[SDK_MAX_RECIVE_MSG_PHONE_COUNT][16]; //���ղ��ŵ��ֻ��ţ���֧��3���ֻ���
	char pGateWayDomain[40];	// ���ص�ַ��������IP
	int  gateWayPort;			// ���ض˿�
	char pMmscDomain[40];		// ���ŷ�������ַ��IP������
	int  mmscPort;				// ���ŷ������˿ں�
};

struct SDK_DASSerInfo
{
	bool enable;
	char serAddr[NET_NAME_PASSWORD_LEN];
	int  port;
	char userName[NET_NAME_PASSWORD_LEN];
	char passwd[NET_NAME_PASSWORD_LEN];
	char devID[NET_NAME_PASSWORD_LEN];
};
enum UploadDataType  //�ϴ���������
{
	VEHICLE=0,//������Ϣ
	SDK_RECORD_STATE,//¼��״̬
	SDK_DIGITCHN_STATE,	//����ͨ������״̬
	SDK_TITLE_INFO,		//ͨ������
};
//�������************************************************************************
//����״̬
enum SDK_CAR_STATUS_TYPE
{
	SDK_CAR_WORKING,             //�Ƿ�������
	SDK_CAR_LIGHT_LEFT_TURN,     //��ת���Ƿ����
	SDK_CAR_LIGHT_RIGHT_TURN,    //��ת���Ƿ����
	SDK_CAR_DOOR_LEFT_FRONT,     //��ǰ���Ƿ��
	SDK_CAR_DOOR_RIGHT_FRONT,    //��ǰ���Ƿ��
	SDK_CAR_DOOR_LEFT_BACK,      //������Ƿ��
	SDK_CAR_DOOR_RIGHT_BACK,     //�Һ����Ƿ��
	SDK_CAR_DOOR_BACK,           //�����Ƿ��
	SDK_CAR_BRAKE,               //�Ƿ��ɲ��
	SDK_CAR_URGENCY_ALARM,       //��������
	SDK_CAR_STATUS_NR, //״̬������Ŀ
};

//�ⲿ��������
enum SDK_IO_INPUT_TYPE
{
	SDK_LOCAL_ALARM_INPUT,//���ر�������
	SDK_RS232_INPUT,      //ͨ��232��������
	SDK_RS485_INPUT,      //ͨ��485��������
};

//�ⲿ��Ϣ�����복��״̬�Ķ�Ӧ��ϵ
struct SDK_CarStatusExchange
{
	int  statusType; //��һ�ֳ���״̬��������ת��
	bool bExist;     //�Ƿ��и���״̬����Ϣ���룬���ݳ�����ʵ�������������
	bool bEnable;    //�Ƿ������״̬
	int  inputType;  //����״̬��Ӧ����Ϣ�������ͣ���IO_INPUT_TYPEö�ٵ�ֵ��ȡ
	int  addr;       //��ַ�������Ǳ��ر��������һ��Ӧ0������ڶ���Ӧ1
	int  sensorType; //����(NO)�򳣱�(NC)����inputType�Ǳ��ر�������ʱ��Ч
};

struct SDK_CarStatusExchangeAll
{
	SDK_CarStatusExchange exchangeAll[16];
};

struct SDK_CarStatusNum  
{
	int iCarStatusNum;
};

struct SDK_CarDelayTimeConfig
{
	bool bStartDelay;
	bool bCloseDelay;

	int timeStartDelay;		//��λ:����
	int timeCloseDelay;		//��λ:����
};
enum SDK_network_media {
	SDK_NM_WIRED = 0,  //��������
	SDK_NM_WLAN,       //Wifi
	SDK_NM_3G,         //3G����
	SDK_NM_NR,    //������
};
//�����������ȼ�
typedef struct SDK_tagNetLinkOrder
{
	int netType;  //ȡֵ��network_media���͵�
	int netOrder; //����ԽС�����ȼ�Խ��,0��������ȼ�
}SDK_NetLinkOrder;
//�������ȼ�
struct SDK_NetOrderConfig
{
	bool         bEnable;        //�Ƿ������������ȼ�
	int          netCount;       //����������Ŀ
	SDK_NetLinkOrder pNetOrder[SDK_NM_NR];//�������ȼ�
	SDK_NetLinkOrder pReserve[7-SDK_NM_NR];//���µ���������Ԥ��
};
///�������ȼ�����
struct SDK_NetOrderFunction
{
	bool bNetOrder;
};
#define  MAX_CAR_INFOR 24
/// �����ƺ�
struct  SDK_CarPlates
{
	char sPlateName[MAX_CAR_INFOR];
};
enum NET_ISP
{
	ISP_AUTO, //�Զ�ѡ��
	ISP_TELCOM, //����
	ISP_UNIONCOM, //��ͨ
	ISP_CNC,//��ͨ
	ISP_MOBILE,//�ƶ�����ͨ
	ISP_USER,//�Զ���
};
//����ƽ̨��Ϣ����
typedef struct SDK_LocalSdkNetPlatformConfig
{
	int Enable;
	int nISP;                          ///�μ�NET_ISP
	char sServerName[32];
	char ID[32];
	char sUserName[32];
	char sPassword[32];
	CONFIG_IPAddress HostIP;		///< host ip
	int port;
}SDK_LOCALSDK_NET_PLATFORM_CONFIG;

//GPSУʱ����
struct SDK_GPSTimingConfig
{
	bool bEnable;      // �Ƿ�����
	int  timeChange;   // �����UTCʱ����Ҫ�ı���٣���λ:��
	int  updatePeriod; // ��������  ��λ:����
};
//���۽Ӿ�����ϵͳ
struct	SDK_GodEyeConfig
{
	bool	bEnable; 
	char MainSeverName[NET_NAME_PASSWORD_LEN]; //������
	int MainPort;	//���˿�
	char ExSeverName[NET_NAME_PASSWORD_LEN]; //��������
	int ExPort;	//���ö˿�
};
enum  SDK_DigManagerShowStatus
{
	SDK_DM_SHOW_NONE,
	SDK_DM_SHOW_ALL,
};


//����ͨ����ʾ״̬
struct SDK_DigitalManagerShow
{
	int  nDigitalManagerShowSta;
};

//NAT���䣬MTUֵ
struct SDK_NatConfig
{
    bool bEnable;
    int nMTU;             // ��Χ (100,1400)
	char serverAddr[64];  //�Ʒ������������IP��ַ��
	int  serverPort;      //�Ʒ���Ķ˿�;
};

enum SubConnType
{
	conn_realTimePlay=1,
	conn_talk,
	conn_playback,
	conn_facepicture,
	conn_faceCompareResult,
	conn_faceBlackAndWhitelList,
	conn_CarLicensePlate,
	conn_faceMonitor,
};
//*** */���豸ע��
enum SocketStyle
{
	TCPSOCKET=0,
	UDPSOCKET,	
	SOCKETNR
};


enum SDK_NatStatusType
{
	SDK_NAT_STATUS_DISENABLE,//δ����
	SDK_NAT_STATUS_PROBING,  //����̽��DNS	
	SDK_NAT_STATUS_CONNECTING,//�������ӷ�����
	SDK_NAT_STATUS_CONNECTED,//���ӳɹ�
};
//nat״̬��Ϣ
struct SDK_NatStatusInfo
{
	int	iNatStatus;
	char NatInfoCode[64];
};

/// ����ˮӡ����
struct SDK_WaterMarkConfig
{
	bool	bEnable;		//  ����ˮӡ
	char  sKey[8];
	char sUserData[16];
};

struct SDK_WaterMarkConfigAll
{
	SDK_WaterMarkConfig vWaterMarkConfigAll[NET_MAX_CHANNUM];
};

///��������̬����
struct SDK_EncodeStaticParam
{
	int profile;
	int level;
	int reserved1[4];
};


struct SDK_EncodeStaticParamAll
{
	SDK_EncodeStaticParam	EncodeStaticParamAll[NET_MAX_CHANNUM];	
};

enum
{
	sdk_maxCPCDataItem = 2048,
	sdk_maxCPCDataReturn = 512,
	sdk_itemtotalLength = 96,	//2λͨ���ţ�20λ��ʼʱ�䣬20λ����ʱ�䣬������13λ������,������
	sdk_maxpack=4,// sdk_maxCPCDataItem/sdk_maxCPCDataReturn
};

struct SDK_CPCDataItem		//����ͳ����ṹ��
{
	int channel;			//��Ӧ��ͨ����
	SDK_SYSTEM_TIME startTime;	//��ʼʱ��
	SDK_SYSTEM_TIME endTime;	//����ʱ��
	int inNum;			//��������
	int outNum;			//�뿪����
};

struct SDK_CPCData
{
	int nItemNum;
	SDK_CPCDataItem CPCData[sdk_maxCPCDataReturn];
};

struct SDK_CPCDataAll
{
	int nCount;
	SDK_CPCData nCpcData[sdk_maxpack] ;
};

/// ¼��洢�豸���ͣ��������͵�һ�ֻ��߶���
struct SDK_RecordStorageType
{
	bool SATA_as;
	bool USB_as;
	bool SD_as;
	bool DVD_as;
};

//VPN�ṹ��
struct SDK_VPNConfig
{
	bool Enable;		///< �Ƿ���
	CONFIG_IPAddress ServiceIp;						///< ������IP��ַ
	char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
	char Password[NET_NAME_PASSWORD_LEN];		///< ����	
	CONFIG_IPAddress addr;		///< ���ź��õ�IP��ַ
};
//��ǰVGA�ֱ���
struct SDK_VGAresolution
{
	int nHeight;
	int nWidth;
};
//֧��VGA�ֱ����б�
struct SDK_VGAResolutionAbility
{
	int vVGANum;
	char vVGAList[VGA_MAXNUM][VGA_NAME_LENGTH];
};

//�豸�б�(�豸������)
struct SDK_NetDevList
{
	int vNetDevNum;
	SDK_CONFIG_NET_COMMON_V2 vNetDevList[DEV_LIST_SHOW];
};

//���ݿ���ƽ̨
/***�û���Ϣ***/ 

struct SDK_CONFIG_KAINENG_USERINFO
{
	char szUserName[16];           //�û�������5�����ֻ�ʮ����ĸ;
	char szUserAddr[128];           //�û���ַ��30�����ֻ�60����ĸ;
	char szUserAttr[16];           //�û����ʣ�5�����ֻ�ʮ����ĸ��

	char szBelongUnit[64];         //��ܵ�λ��15�����ֻ�30����ĸ;
	char szBelongUnitPhone[16];    //��ܵ�λ�绰��14λ���֣��ֻ���"-" �����;

	char szPoliceUnit[64];         //������λ��15�����ֻ�30����ĸ;
	char szPoliceUnitAddr[128];     //������λ��ַ��30�����ֻ�60����ĸ;
	char szPoliceUnitPhone[16];    //������λ�绰��14λ���֣��ֻ���"-"�����;

	char szPolicePhone[4][16];
	char szPolOrCenPhone[2][16];   //����/���ĵ绰1��2��14λ���֣��ֻ���"-" �����;

	char szFTP[64];                //FTP��50���ַ���
	char szEMail[64];              //E-Mail: 50���ַ���
	CONFIG_IPAddress PoliceIP;            //�Ӿ�����IP��ַ
	int nHttpPort;                 //�Ӿ�����IP�˿�
};

/***�豸��Ϣ***/
//���ò�������ö��
typedef enum SDK_GuardType
{
	 SDK_FORBID = 0,      //��ֹ
	 SDK_TEN_MIN,         //ʮ����
	 SDK_THIRTY_MIN,      //��ʮ����
	 SDK_SIXTY_MIN,       //��ʮ����
	 SDK_MAX,
}SDK_GUARDTYEP;


struct SDK_CONFIG_KAINENG_DEVINFO
{
	char ProbeNum1;                //��������������������ÿ��������� 1�ŵ�10��̽����ѡ�� ��Ĭ������Ϊ <1��̽����>
	char ProbeNum2;                //��������������������ÿ��������� 1�ŵ�10��̽����ѡ�� ��Ĭ������Ϊ <1��̽����>	
	char nProbeType;			   //������������ ��ѡ��3��Ϊ <��ֹ>  <AND>  <OR>  Ĭ��Ϊ <��ֹ>
	char nGuardType;               //���ò���, ����GUARDTYEP

	int AlarmTime;                //���ѿ���ʱ�䣺��λ���ִ�000-999  Ĭ��Ϊ��180
	int nGuardArea;               //���߷������ͣ���λ���֣�ÿλ��С0���3����00000000 ��33333333;  Ĭ�ϣ�00000000��

	char szRemConAddr[4][4];       //ң����1-4�ŵ�ַ ����λ16�����ַ�����գ���0-9  A-F����Ĭ��Ϊ�գ�
	char szLinDevAddr[6][4];       //�����豸��1-6��ַ����λ16�����ַ�����գ���0-9  A-F����Ĭ��Ϊ�գ�
	char szProbeAddr[10][4];       //̽����1-10�ŵ�ַ����λ16�����ַ�����գ���0-9  A-F����Ĭ��Ϊ�գ�

	//��ʱ������
	char szGuardTime[3][9];        //��ʱ������,ÿ�鶼Ϊchar [8] ���� ��00 00 00 00������ɿ�ʼʱ�ֵ�����ʱ�֣�����Ҫ��������
};

/***��������***/
//��������ö��
typedef enum SDK_KNAlarmLink
{
	SDK_LINK_EMPTY = 0,
	SDK_LINK_SWITH,
	SDK_LINK_10S,
	SDK_LINK_30S,
	SDK_LINK_60S,
	SDK_LINK_200S,
	SDK_LINK_600S,
	SDK_LINK_METHOD_1,
	SDK_LINK_METHOD_2,
	SDK_LINK_MAX,
}SDK_KNALARMLINK;

struct SDK_CONFIG_KAINENG_LINKINFO
{
	char eLink[10][7];        //��������,ȡֵΪ��������ö��
};

//���ܶ��ƣ�3��������Ϣȫ�����
struct SDK_CONFIG_KAINENG_INFO
{
	SDK_CONFIG_KAINENG_USERINFO UserInfo;
	SDK_CONFIG_KAINENG_DEVINFO DevInfo;
	SDK_CONFIG_KAINENG_LINKINFO LinkInfo;
};

//�����豸Э��
enum SDK_TransferProtocol_V2
{
	SDK_TRANSFER_PROTOCOL_NETIP,
	SDK_TRANSFER_PROTOCOL_ONVIF,
	SDK_TRANSFER_TRANSFER_PROTOCOL_MAC,
	SDK_TRANSFER_PROTOCOL_NR_V2=5,
	SDK_TRANSFER_PROTOCOL_ONVIF_DEFAULT = 128,
	SDK_TRANSFER_PROTOCOL_ONVIF_NR_V2
};
 
struct SDK_EncodeStaticParamV2
{
	int profile; //��ǰ��̬����
	int reserved1[4]; //�����ֶ�
};

/*
==	DVR��̬����������������3��
==	0 ��֧�� 1 ֧��baseline 2 ֧��main profile 4 ֧��high profile
==  �������
*/
struct SDK_EncStaticParamAbility
{
	unsigned int encStaticParam;
};

//���մ���C7ƽ̨����
struct SDK_C7PlatformConfig
{
	char pServerAddr[64];//ƽ̨��ַ��IP��ַ������
	int  servPort;       //ƽ̨�˿�
	char pPUID[32];      //PUID
	char pPassword[32];  //����
	char pStatus[64];    //����״̬����LocalSDK���ǿɶ���д�ģ������ط���ֻ��
	char pResv[60];      //����
};

///�������
struct SDK_NetKeyboardConfig
{
	bool Enable;		///< �Ƿ���
	char sTransProtocol[4];	//����Э��
	int ListenPort;		//�����˿�
	char sParserProtocol[32];
	int deviceaddr;	//�豸��ַ
};
////// �������Э��
struct SDK_NetKeyboardAbility
{
	//ÿ��Э�������64���ַ����
	int nTransPNum;
	char vTransProtocol[32][NET_MAX_PTZ_PROTOCOL_LENGTH];
	int nParserNum;
	char vParserProtocol[32][NET_MAX_PTZ_PROTOCOL_LENGTH];
};

//28181Э������
struct SDK_ASB_NET_VSP_CONFIG
{
	bool		bCsEnable;				//ʹ�ܱ��
	char		szCsIP[64];				//��������ַ	
	short	sCsPort;					//�������˿�
	short	sUdpPort;				//���ذ�udp�˿�
	char		szServerNo[64];			//���������к�
	char 	szServerDn[64];			//���������ڵ�������
	char		szDeviceNO[64];			//�豸���к�
	char 	szConnPass[64];			//�豸��������
	int		iHsIntervalTime;			//�������ʱ��,��λ����
	int		iRsAgedTime;			//���·���ע��ʱ��������λΪ��
	char		Camreaid[NET_MAX_CHANNUM][64];	//�豸������ͷID
	int		CamreaLevel[NET_MAX_CHANNUM];	//�����ȼ�
	char		Alarmid[NET_MAX_CHANNUM][64];	//�豸������ͷID
	int		AlarmLevel[NET_MAX_CHANNUM];	//�����ȼ�
	unsigned int		uiAlarmStateGpinEnable;	//�ⲿ����ʹ��
	unsigned int		uiAlarmStateLoseEnable;	//��Ƶ��ʧ�澯ʹ��
	unsigned int		uiAlarmStateMotionEnable;//��Ƶ��̬���澯ʹ��
	unsigned int		uiAlarmStateBlindEnable;	//��Ļ�ڵ��澯ʹ��
	unsigned int		uiAlarmStatePerformanceEnable;	//ϵͳ�쳣�澯ʹ��
	unsigned int		uiAlarmStateConnectEnable;	//�û����Ӹ澯ʹ��
};

//�ֻ���������
struct SDK_PMSConfig
{
	bool Enable;		///< �Ƿ���
	char servname[64];		
	int port;
	char boxid[128];
	char resume[24]; //����
};

//��Ļ��ʾ��Ϣ
struct  SDK_OSDInfoConfig
{
	SDK_VIDEO_WIDGET OSDInfoWidget;
	char ppInfo[NET_MAX_LINE_PER_OSD_AREA][NET_CHANNEL_NAME_MAX_LEN];
};

//����ͨ������Ļ��ʾ��Ϣ
struct  SDK_OSDInfoConfigAll
{
	SDK_OSDInfoConfig   vOSDInfoAll[NET_MAX_CHANNUM];
};
//
struct SDK_KaiCongAlarmConfig
{
	bool Enable;		///< �Ƿ���
	char ServerName[NET_NAME_PASSWORD_LEN];	///< ������
	int Port;							///< �˿ں�
	char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
	char Password[NET_NAME_PASSWORD_LEN];		///< ����	
};
//
struct SDK_VideoChannelManage
{
	int		nHVRCap; 
	int		curMode;
	bool bhide[MAX_HVR_CHNCAP_CHN];
	SDK_CAPTURE_HVRCAP	HVRCap[MAX_HVR_CHNCAP_CHN];	
};

//PTZ����������
struct SDK_PTZControlAbility
{
	unsigned int nPTZPosition;
};

struct SDK_PositionPoint
{
	int iPointStart_x;
	int iPointStart_y;
	int iPointEnd_x;
	int iPointEnd_y;
};

struct SDK_XMHeartbeatConfig
{
	bool bEnable;							///< �Ƿ���
	int iInterval;							///< ������ʱ��
	char ServerName[NET_NAME_PASSWORD_LEN];	///< ������
	int Port;								///< �˿ں�
	char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
	char Password[NET_NAME_PASSWORD_LEN];		///< ����
	char resume[24];
};

struct SDK_MonitorPlatformConfig
{
	int Enable;		///< �Ƿ���
	char servname[NET_NAME_PASSWORD_LEN];		
	int port;
	char resume[24];
};
//��������ͷ��չ����
struct SDK_CameraParamEx
{
	SDK_GainCfg broadTrends;	//��̬
	int res[64];	//����
};

// ����ͷ������չ����
struct SDK_CameraParamExAll
{
	SDK_CameraParamEx vCameraParamExAll[NET_MAX_CHANNUM];
};

//���������ƽ̨ͨ�����ã��Ժ��ƶ������
struct SDK_NetPlatformCommonCfg
{
	int	Enable;
	int Port;									///< �˿ں�
	char ServerName[NET_NAME_PASSWORD_LEN];		///< ������
	char ID[NET_NAME_PASSWORD_LEN];	
	char UserName[NET_NAME_PASSWORD_LEN];		///< �û���
	char Password[NET_NAME_PASSWORD_LEN];		///< ����
	char resume[128];		///Ԥ��
};

enum SDK_INFO_NET_LINK_STATUS
{
	SDK_INFO_NET_LINK_OK         = 0,
	SDK_INFO_NET_LINK_FAILED     = 1,
	SDK_INFO_NET_LINK_NO_DEVICE  = 2,
	SDK_INFO_NET_LINK_INVALID    = 9,
};
enum SDK_POSITIONING_DIRECTION
{
	SDK_POS_DIRECTION_EAST  = 'E',
	SDK_POS_DIRECTION_WEST  = 'W',
	SDK_POS_DIRECTION_SOUTH = 'S',
	SDK_POS_DIRECTION_NORTH = 'N'
};
struct SDK_POSITIONING_POS//��γ��
{
	int  degree;     //��(��/1000)Ϊ��λ
	char direction;  //��λ ȡֵ��ö��ֵPOSITIONING_DIRECTION��ʾ
	char res[3];
};
//GPS״̬
struct SDK_GPSStatusInfo
{
	int             positioningStatus; //��λ״̬��ȡֵ��ö��SDK_INFO_NET_LINK_STATUS����
	SDK_POSITIONING_POS longitudePos;      //����
	SDK_POSITIONING_POS latitudePos;       //γ��
	char            rev[12];
};

//wifi״̬
struct SDK_WifiStatusInfo
{
	int  connectStatus;  //wifi����״̬  ��ö��SDK_INFO_NET_LINK_STATUS����
	int  strength;       //�ź�ǿ��
	char rev[24];
};

//3G״̬
struct SDK_WirelessStatusInfo
{
	int  connectStatus;  //3G����״̬  ��ö��SDK_INFO_NET_LINK_STATUS����
	int  strength;       //�ź�ǿ��
	char rev[24];
};

//����ע��״̬
struct SDK_DASStatusInfo
{
	int  connectStatus;  //DAS����״̬  ��ö��SDK_INFO_NET_LINK_STATUS����
	char rev[28];
};

struct SDK_RecordStorageInfo
{
	unsigned int bStart;//�Ƿ�¼���־λ
	SDK_SYSTEM_TIME beginTime;//¼��ʼʱ��
	SDK_SYSTEM_TIME endTime;//¼�����ʱ��
	unsigned int  storageCapacity;//Ӳ��������
	unsigned int  useCapacity;//ʹ������
	int res[16];//����
};
/// ������ʱ�ȼ�
enum SDK_DecodeDeleyTypes
{
	SDK_DecodeDeley_0 = 0,
	SDK_DecodeDeley_1,
	SDK_DecodeDeley_2,
	SDK_DecodeDeley_3,
	SDK_DecodeDeley_4,
	SDK_DecodeDeley_5,
	SDK_DecodeDeley_6,
	SDK_DecodeDeley_TYPE_NR,		
};

struct SDK_DecodeDeleyTimePrame
{
	unsigned int  DecodeDeleyTime[SDK_DecodeDeley_TYPE_NR];
};

// ����ͨ��
struct SDK_DecodeParam
{
	int iMaxDeleyTime[NET_MAX_CHANNUM];	// ���Ľ�����ʱ
};

struct SDK_RecordStateInfo
{
	int nchannel;
	BOOL RecordState;
};

//������Ƶ��ɫ�ṹ
struct SDK_VIDEOCOLOR_PARAM_EX
{
	int		BrightnessRef;		///< ����ref1��ȡֵ0-100��
	int		ContrastRef;		///< �Աȶ�ref1��ȡֵ0-100��
	int  		ContrastThRef;		///< �Աȶȷ�ֵref1��ȡֵ0-100��
	int		ContrastSlopeRef;		///< �Աȶ�б��ref1��ȡֵ0-100��
	int 		DarkBlfRef;
	int		DarkNfRef;
	int		DarkEcPthRef;
	int		DarkEcMthRef;
	int		DarkDcRef;
	int		CbGain;	//high low middle
	int		CrGain;	//higg low middle
	int		reserved;	//����
};

struct SDK_VIDEOCOLOR_PARAM_CUSTOM
{
	SDK_VIDEOCOLOR_PARAM_EX	VideoColor[3];
	int		Saturation;		///< ���Ͷȣ�ȡֵ0-100��
	int		Gain;			///< ���棬ȡֵ0-100��bit7��λ��ʾ�Զ����棬����λ�����ԡ�
	int		Acutance;		///< ��ȣ�ȡֵ0-100
	int		AeWight;		//���ⲹ��
};

enum SDK_FileControlType
{
	SDK_FILE_DEL,			//ɾ���ļ�
	SDK_FILE_DIR_DEL,		//ɾ���ļ���
	SDK_FILE_DIR_CLEAR,		//����ļ���
	SDK_FILE_NR,
};

struct SDK_NetFileControl
{
	int iAction;			//enum FileControlType
	char strfile[256];
};

enum SDK_DecChnStateType
{
	SDK_DEC_STA_NONE, 			//����
	SDK_DEC_STA_NOCONFIG,		//δ����
	SDK_DEC_STA_NOLOGIN,		//δ��½
	SDK_DEC_STA_NOCONNECT,	//δ����
	SDK_DEC_STA_CONNECTED,	//������
};

struct SDK_DigitStateInfo
{
	int nchannel;
	int DigitState; //SDK_DecChnStateType
};

struct SDK_TitleNameInfo
{
	int nchannel;
	char titleName[256];
};
/*
	==SDK_TransferProtocol_V2
	==��һλ����SDK_TRANSFER_PROTOCOL_ONVIF_DEFAULT = 128���Դ�����
*/
struct SDK_AbilityMask
{
	unsigned int AbilityPram;
};

enum SDK_Music_Play_Action
{
	SDK_MUSIC_ACTION_PLAY,
	SDK_MUSIC_ACTION_STOP,
	SDK_MUSIC_ACTION_PAUSE,
	SDK_MUSIC_ACTION_CONTINUE
};

struct SDK_LocalMusicControl
{
	int iAction;            //�ο�SDK_Music_Play_Action
	char sFileName[20];
};

/// ��Ƶ�ļ��б���Ϣ
struct SDK_MusicFileList
{
	int iNumFiles;		///< �ļ�����
	char sFileName[8][20];
};

enum SDK_CAR_BOOT_TYPE
{
	SDK_CAR_BOOT_TYPE_SPARK,  //���Ϩ�𿪹ػ�
	SDK_CAR_BOOT_TYPE_TIMING, //��ʱ���ػ�
	SDK_CAR_BOOT_TYPE_NR,
};

//��𿪹ػ���ʱ����
struct SDK_CarSparkWork
{
	int bootDelayMinute;  //������ʱ������
	int shutDelayMinute;  //�ػ���ʱ������
	char resv[24];        //����
};

//���ض�ʱ���ػ�����
struct SDK_CarTimingWork
{
	SDK_TIMESECTION workSection1; //����ʱ���1
	SDK_TIMESECTION workSection2; //����ʱ���2
	char resv[32]; //����
};

struct SDK_CarBootTypeConfig
{
	int           bootType;         //��ö�� SDK_CAR_BOOT_TYPE ����
	SDK_CarSparkWork  sparkWorkConfig;  //��𿪹ػ�����
	SDK_CarTimingWork timingWorkConfig; //��ʱ���ػ�ʱ���1
	char          resv[48];
};

//����IPC
struct SDK_ALARM_IPCCONFIG
{
	bool	bEnable;		///< �������뿪��
	int		iSensorType;	///< ���������ͳ��� or ����
	SDK_EventHandler hEvent;	///< ��������
};
///< ��������ͨ���ı�������
struct SDK_IPCAlarmConfigAll
{
	SDK_ALARM_IPCCONFIG vAlarmConfigAll[NET_DECORDR_CH];
};

//�ٶ���
struct SDK_BaiduCloudCfg
{
	bool	enable;
	char APIKey[NET_NAME_TOKEN_LEN];				//Ӧ��API��Կ
	char SecretKey[NET_NAME_TOKEN_LEN];			//Ӧ����Կ
	char AuthorizationCode[NET_NAME_TOKEN_LEN];	//��Ȩ��
	char accessToken[NET_NAME_TOKEN_LEN];		//����Ȩ����
	char refreshToken[NET_NAME_TOKEN_LEN];		//ˢ��Ȩ����
	SDK_SYSTEM_TIME	refreshTime;					//�ϴ�ˢ��Tokenʱ��
	int channelMain[NET_MAX_CHANNUM];				//�Ƿ������
	int channelExtra[NET_MAX_CHANNUM];				//�Ƿ������
	int	recordFileMode;						//����¼��ģʽ
	int	recordFileSize;						//¼���ļ���С
	int	recordFileTime;						//¼���ʱ��
	char resume[128];							///Ԥ��
};

//=================================================================================

#define DETECT_AREA_NUM	4							//���·��
#define MAX_ROI_AREA    8
#define MAX_OVERSTRP_AREA 4

//ʱ��: ��
typedef struct SDK_DAY_TIME_S
{
	DWORD			week : 5;							//����
	DWORD			millisec : 10;						//����: 0 ~ 999
	DWORD			second : 6;							//��:	0 ~ 59
	DWORD			minute : 6;							//��:   0 ~ 59
	DWORD			hour : 5;							//ʱ:	0 ~ 23
}SDK_DAY_TIME; 


//ʱ��: ʱ��� 
typedef struct SDK_SEG_TIME_S
{
	BYTE			bEnable;							//�Ƿ���
	BYTE			byTask;								//����
	BYTE			byRes[2];							//����
	SDK_DAY_TIME		stBgnTime;							//��ʼʱ��
	SDK_DAY_TIME		stEndTime;							//����ʱ��
}SDK_SEG_TIME; 

//�ƻ�ʱ��: �ܼƻ�ʱ��
typedef struct SDK_SCHWEEK_TIME_S
{
	SDK_SEG_TIME		stSegTime[7][4];					//0: �����죬1: ��һ��2: �ܶ�
}SDK_SCHWEEK_TIME;


//��
typedef struct SDK_LINE_POIN_S
{
	int			x0;									//x0����
	int			y0;									//y0����
	int			x1;									//x1���
	int			y1;									//y1�߶�
} SDK_LINE_POIN;


//��������   rectangle   
typedef struct SDK_RECTANGLE_POINT_S
{
	int			x;									//X����
	int			y;									//Y����
	int			w;									//���
	int			h;									//�߶�
}SDK_RECTANGLE_POINT;

//����
typedef struct SDK_AREA_RECT_S
{
	short			x;									//X����
	short			y;									//Y����
	short			w;									//���
	short			h;									//�߶�
}SDK_AREA_RECT;

//�ı������� _CROSS_RECT_S   

//�ı������� Quadrilateral   
typedef struct SDK_QUADRILATERAL_POINT_S
{
	int			x0;									//X0����
	int			y0;									//Y0����
	int			x1;									//X1����
	int			y1;									//Y1����
	int			x2;									//X2����
	int			y2;									//Y2����
	int			x3;									//X3����
	int			y3;									//Y3����
}SDK_QUADRILATERAL_POINT;


//����
typedef struct SDK_SM_CHN_MASK_S
{
	DWORD			dwChns1;							//bit.0 ~ bit.31  ��ʾͨ�� 1  ~ 32
	DWORD			dwChns2;							//bit.0 ~ bit.31  ��ʾͨ�� 33 ~ 64
}SDK_SM_CHN_MASK;

//������������
typedef struct SDK_SM_ALARM_HANDLE_S
{
	SDK_SM_CHN_MASK		stMaskAlarmOut;						//���������豸�����ͨ��,�������������,Ϊ1��ʾ���������
	DWORD			dwAlarmOutTime;						//���������ʱ��(��)

	SDK_SM_CHN_MASK		stMaskAlarmRec;						//����¼��ͨ�� 
	DWORD			dwRecSaveMode;						//bit0: ���ش洢(�������д洢�豸ʱ, ��λ�̶�Ϊ1)  
	//bit2: ftp�ϴ�   
	DWORD			dwRecTime;							//¼���ʱ��(��)

	SDK_SM_CHN_MASK		stMaskAlarmSnap;					//����ץ��
	DWORD			dwSnapSaveMode;						//bit0: ���ش洢(�������д洢�豸ʱ, ��λ�̶�Ϊ1)  
	//bit1: email 
	//bit2: ftp�ϴ�   

	DWORD			dwSnapNum;							//����ץ������
	DWORD			dwSnapInterval;						//����ץ��ʱ����(����)  0: ����ץ��

	DWORD			dwUserData1;						//�û�����1(����PC¼��ͨ��)
	DWORD			dwUserData2;						//�û�����2

	DWORD			dwSnapDealy;						//�ӳ�ץ��

	BYTE			bSendEmail;							//��������email
	BYTE			byRes[251];							//����
}SDK_SM_ALARM_HANDLE;

//���ܱ��룺
typedef struct SDK_SM_AUTOCODEC_CONFIG_S
{
	BYTE bySensitive; // 0  low  1 mid  2 high
	BYTE bySaveCurBitrate;
	BYTE byLowBitrate;
	BYTE byStopTime;
	BYTE byRes[256];
}SDK_SM_AUTOCODEC_CONFIG;


typedef struct SDK_SM_ROI_CONFIG_S
{
	SDK_RECTANGLE_POINT stROIRect; //Roi   area  rect
	INT s32Qp;
	INT dwIndex;
	BYTE byEnable;
	BYTE byAbsQp;
	BYTE byRes[14];
}SDK_SM_ROT_CONFIG;

typedef struct SDK_SM_SMART_CODEC_CONFIG_S
{
	SDK_SM_ROT_CONFIG  stROI[MAX_ROI_AREA];   // 
	SDK_SM_AUTOCODEC_CONFIG stAutoCodec;
	BYTE     	 byCodecEnable;  // 0  close,  1  Enable auto update all stream (auto check) ,  2  ROI  (set Rect)
	BYTE 		 byRes1[3];
	BYTE		 byRes[256];	
}SDK_SM_SMART_CODEC_CONFIG, SDK_SMART_CODEC_CONFIG;


//���ܼ�⣺
typedef struct SDK_SM_SMART_SHUNTTER_S
{
	BYTE         byshutterEnable;  // 0 close  1 Enable
	BYTE 		 bySensitive;
	BYTE 		 byShowOsd;
	BYTE 		 bySynMotion; //Synchronous motion detecting alarm
	char 		 szOsd[32];
	BYTE		 byRes[256];	
} SDK_SM_SMART_SHUNTTER;

typedef struct SDK_SM_SMART_OVERSTEP_S
{
	BYTE         byOverStepEnable;  // 0 close  1 Enable
	BYTE 		 bySensitive;
	BYTE 		 byShowOsd;
	BYTE 		 bySynMotion; //Synchronous motion detecting alarm
	SDK_RECTANGLE_POINT  stOverStepRect[MAX_OVERSTRP_AREA];
	char 		 szOsd[32];
	BYTE		 byRes[256];	
} SDK_SM_SMART_OVERSTEP;

typedef struct SDK_SM_SMART_FOCUS_S
{
	BYTE         byAfFocusEnable;  // 0 close  1 Enable
	BYTE 		 bySensitive;
	BYTE 		 byShowOsd;
	BYTE 		 bySynMotion; //Synchronous motion detecting alarm
	DWORD		 dwCurAfVaule;
	DWORD		 dwCurLumaVaule;
	char 		 szOsd[32];
	BYTE		 byAfFocusStudy; // Af Focus Study Again
	BYTE 		 byStudyPresetNum; //Af  Focus Study Preset Num
	BYTE		 byRes1[2];
	BYTE		 byRes[252];	
}SDK_SM_SMART_FOCUS;

typedef struct SDK_SM_SMART_DETECT_CONFIG_S
{
	SDK_SM_SMART_SHUNTTER stSmartShuntter;
	SDK_SM_SMART_OVERSTEP stSmartOverStep;	
	SDK_SM_SMART_FOCUS	   stSmartFocus;
	BYTE		   byRes[256];
} SDK_SM_SMART_DETECT_CONFIG, SDK_SMART_DETECT_CONFIG;

//���ܿ��ƣ�
typedef struct SDK_SM_SMART_CONTROL_CONFIG_S
{
	BYTE		 bySmartCtlEnable;
	BYTE		 bySmartOpenAlarm;
	BYTE		 bySmartCloseAlarm;
	BYTE		 bySmartCleanHappern;
	BYTE 		 bySmartCleanFlag;
	BYTE		 byRes1[3];
	BYTE		 byRes[512];
} SDK_SM_SMART_CONTROL_CONFIG, SDK_SMART_CONTROL_CONFIG;


//detect

//����������ݽṹ
typedef struct SDK_SM_DETECT_BRIGHTNESS_S						//size 512
{
	int	bEnable;									//ʹ��
	int sensitivity;								//��ֵ
	SDK_SCHWEEK_TIME	stSchTime;					//����ʱ��
	SDK_SM_ALARM_HANDLE	stAlarmHandle;				//��������
	char res[368];
}SDK_SM_DETECT_BRIGHTNESS;

//�ƶ�������ݽṹ
typedef struct SDK_SM_DETECT_MOTION_S
{
	int	bEnable;									//ʹ��
	int sensitivity;								//��ֵ
	SDK_RECTANGLE_POINT	stMDArea[DETECT_AREA_NUM];		//�ڵ�����
	char res[440];
}SDK_SM_DETECT_MOTION;

//�ڵ�������ݽṹ
typedef struct SDK_SM_DETECT_HIDE_S
{
	int	bEnable;									//ʹ��
	float nRateX;									//X�������
	float nRateY;									//Y�������
	int sensitivity;								//��ֵ
	SDK_RECTANGLE_POINT	stMDArea[DETECT_AREA_NUM];			//�ڵ�����
	SDK_SCHWEEK_TIME	stSchTime;						//����ʱ��
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//��������
	char res[296];
}SDK_SM_DETECT_HIDE;

//���⾯�������ݽṹ
typedef struct SDK_SM_DETECT_VIRTUALCORDON_S						//512
{
	int	bEnable;									//ʹ��
	float nRateX;									//X�������
	float nRateY;									//Y�������
	int direction[DETECT_AREA_NUM];					//��ⷽ��
	SDK_LINE_POIN	stCrossLine[DETECT_AREA_NUM];  	//���������
	SDK_SCHWEEK_TIME_S	stSchTime;						//����ʱ��
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//��������
	char res[284];
}SDK_SM_DETECT_VIRTUALCORDON, SDK_SM_CROSSLINE;

//��������������ݽṹ
typedef struct SDK_SM_DETECT_CROSSAREA_S
{
	int	bEnable;									//ʹ��
	float nRateX;									//X�������
	float nRateY;									//Y�������
	int direction[DETECT_AREA_NUM];					//��ⷽ��
	SDK_QUADRILATERAL_POINT stCrossArea[DETECT_AREA_NUM];  		//����
	SDK_SCHWEEK_TIME_S	stSchTime;						//����ʱ��
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//��������
	char  byAreaDisplay;								//��Ƶ����ʾ DM_LINKAGE_PTZ
	char  byTrackerEnable;								//����ʹ��
	char  res[118];
}SDK_SM_DETECT_CROSSAREA, SDK_SM_CROSSAREA;

//��ɫ���
typedef struct SDK_SM_DETECT_COLOUR_S
{
	int	bEnable;									//ʹ��
	int sensitivity;								//��ֵ
	SDK_SCHWEEK_TIME_S	stSchTime;						//����ʱ��
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//��������
	char res[368];
}SDK_SM_DETECT_COLOUR, SDK_SM_DETECTCOLOR;

//�������
typedef struct SDK_SM_DETECT_SOUND_S
{
	int	bEnable;									//ʹ��
	int aType;
	int sensitivity;								//��ֵ
	SDK_SCHWEEK_TIME_S	stSchTime;						//����ʱ��
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//��������
	char res[364];
}SDK_SM_DETECT_SOUND, SDK_SM_DETECTSOUND;



//��������������ݽṹ
typedef struct SDK_SM_DETECT_GOODS_LEGACY_S
{
	int	bEnable;									//ʹ��
	int time;
	float nRateX;									//X�������
	float nRateY;									//Y�������
	int direction[DETECT_AREA_NUM];					//��ⷽ��
	SDK_RECTANGLE_POINT stLoseobjArea[DETECT_AREA_NUM];  	//���������������
	SDK_SCHWEEK_TIME_S	stSchTime;						//����ʱ��
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//��������
	char res[280];
}SDK_SM_DETECT_GOODS_LEGACY, SDK_SM_LOSEOBJ;

//�������Ӱ�
#define LINKAGE_MAX_USER   10
typedef struct SDK_SM_LINKAGE_BIND_S
{
	INT					nEnable;
	DWORD				dwMainIP[LINKAGE_MAX_USER];						//IP��ַ
	DWORD				dwIPAddr[LINKAGE_MAX_USER];						//IP��ַ
	DWORD				dwDataPort[LINKAGE_MAX_USER];					//���ݶ˿�	
	BYTE				Position[LINKAGE_MAX_USER];						//Ԥ��λ   1~255
	BYTE				CrossArea_Num[LINKAGE_MAX_USER];				//��������  1~4
	BYTE				byRes[50];
}SDK_SM_LINKAGE_BIND;

//====================================================================================

typedef struct SDK_MS_ACTION_S
{
	int nAction;              //0--��ʼ�궨  1--��ɱ궨
}SDK_MS_ACTION;

// by chentf  2018.01.23 
typedef struct SDK_MS_CALIBRATION_PARAMETER_S
{
	int nCalibation;  //��������Ƿ��Ѿ��궨 0���� 1����
}SDK_MS_CALIBRATION_PARAMETER;

//�������¼�ɹ�ʱ�������������ӻ��ĵ�¼����
typedef struct SDK_MS_SUBCAMCONNECT_S
{
	BYTE  	byConnectCmd;	//0������� 1����
	DWORD	dwSlaveIP;		//�ӻ�IP
	DWORD	dwPort;			//�ӻ��˿ں�
	char    sUserName[32];	//�ӻ���¼�û���
	char    sPaasword[32];  //�ӻ���¼����
}SDK_MS_SUBCAMCONNECT;

//��ӦCMD_CALIBRATE_���� ���á�ȷ����\��ɾ����\��3D�Ŵ�ģʽ����ťʱ���˲���
typedef struct SDK_MS_AREA_RECT_S
{	
	int x; 
	int y;
	int nWeight ;
	int nHight;
	int nWndWeight ;	//���ڵ�ʵ�ʿ�
	int nWndHight;		//���ڵ�ʵ�ʸ�
	int nNumber;
	int nCommand;       //1--ȷ�� 2--ɾ�� 3--3D�Ŵ�ģʽʱ������ֵ
	char sRet[4];
}SDK_MS_AREA_RECT;

typedef struct SDK_MS_CALIBRATION_MODE_S
{
	int nMode;  //0:3D�Ŵ�ģʽ 1:�Զ�����ģʽ
}SDK_MS_CALIBRATION_MODE;

typedef struct _SDK_MS_CALIBRATION_ZOOMTIMES_S
{
	int nZoomTimes;  //�䱶ϵ��
}SDK_MS_CALIBRATION_ZOOMTIMES;

typedef struct SDK_MS_CALIBRATION_PTZ_INFO_S
{
	char sCmd;// 0�� ��ȡPTZ��Ϣ  1������PTZλ��
	int nPan; //ˮƽ
	int nTilt;//��ֱ
	int nZoomStep;//�䱶����  

}SDK_MS_CALIBRATION_PTZ_INFO;

typedef struct SDK_MS_PIC_AREA_POS_S
{
	unsigned int nId;
	int x;
	int y;
}SDK_MS_PIC_AREA_POS;

typedef struct SDK_MS_Calibrate_Point_S
{
	int nCmd;// 0 :���ӱ궨��  1:ɾ���궨��  2:��ȡ��ǰ��Ϣ 3:ɾ��������Ϣ
	SDK_MS_PIC_AREA_POS stPointInfo;
	int nPicWeight;//���� �ο���
	int nPicHight;	//���� �ο��߶�
	char byRes[32];

}SDK_MS_Calibrate_Point;


#define  SDK_INV_CALIBRATE_MAX			512
typedef struct SDK_MS_ANALY_POINT_S
{
	int nCmd;
	int nNum;//��ǰ�����ڵ�����
	SDK_MS_PIC_AREA_POS stPoint[ SDK_INV_CALIBRATE_MAX]; //�� ���� //��������������

	int nOutNum;//����������
	SDK_MS_PIC_AREA_POS stOutPoint[SDK_INV_CALIBRATE_MAX]; //�����ڷֱ�����������ꡣ

}SDK_MS_ANALY_POINT;

typedef struct SDK_MS_PANOTYPE_S
{
	int nPanoType; //1:IMX385_3611 2:IMX385_FISH120 3:IMX385_FISH180 

}SDK_MS_PANOTYPE;


#define   SDK_MS_QUANTU_PRIVATE_ENCRYPT_LEN			512
typedef struct SDK_MS_QUANTU_ENCRYPT_S
{
	BYTE	byRes[SDK_MS_QUANTU_PRIVATE_ENCRYPT_LEN];
}SDK_MS_QUANTU_ENCRYPT; /*ȫͼ��������SDK ����512��Ϊ�洢*/


typedef struct SDK_MS_NAMING_S 
{
#define CMD_NAMING_SET_PARAM   		0x1  //�궨����  			param: nData[1-4]
#define CMD_NAMING_SET_ZOOM    		0x2  //���ñ��� 			param: nData
#define CMD_NAMING_SET_SCANMODE		0x3  //����ɨ��ģʽ     		param: nData    
#define CMD_NAMING_SET_SCANTIMES	0X4  //ɨ�迪ʼ��ɨ��n�κ�ֹͣ 	param: nData[1-4]  

#define CMD_NAMING_SCAN_START   	0x20   //ɨ�迪ʼ 
#define CMD_NAMING_SCAN_STOP    	0x21   //ɨ���ֶ�ֹͣ

	int nCmd;
	int nData;		//[1,4]
	char byRes[128];
}SDK_MS_NAMING;

//������ȡ   WINSDK��ȡ����
typedef struct SDK_GET_NAMING_PARAM_S 
{
	char byEnable; //0:  1�����ܿ���
	char byCalibrate;//0:δ�궨  1:�ѱ궨���ڹ켣��궨����������á�
	char byDomeState; //�������״̬0������ 1����������� 2���켣ѧϰ��/�궨
	char byRes[128];//
}SDK_GET_NAMING_PARAM;


//=========================================================================
typedef struct SDK_FA_PICTURE_HEAD_S		
{
	WORD 	headflag;		//��ͷ��־ 0x4A50
	BYTE	tag;			//�̶�ֵ0x01
	BYTE	frametype;		//֡���� 0x4A ��ʾͼƬ
	BYTE	frameinfo;		//��ʱ����
	BYTE	version;		//��ʱ����
	WORD	messageid;		//��ϢID
	WORD	width;			//��ʱ����
	WORD	height;			//��ʱ����
	DWORD   ndatasize;		//��ʱ����
	DWORD   deviceid;		//�û����������豸ID
	DWORD   channelid;		//�û���������ͨ��ID
	DWORD   streamid;		//�û���������ͼƬ��ID
	BYTE	picnumber[64];	//��ʱ����
	BYTE	filename[64];	//ͼƬname
	unsigned int  featureEn;
	unsigned int  nFeatureLen;
	unsigned int  nDevKeyId;	//�豸ID
	BYTE	res[84]; 		//��չʹ��
	DWORD   headend;		//������־
}SDK_FA_PICTURE_HEAD, *P_SDK_FA_PICTURE_HEAD;

//����������ͼƬ�ߴ�
typedef struct _FACEPIC_SIZE_S
{
	int X;
	int Y;
	int nWidth;
	int nHeight;
}FACEPIC_SIZE_S,  CARPIC_SIZE_S;


//��������������
typedef struct _FACE_POSITION_S
{
	int left;
	int top;
	int right;
	int bottom;
}FACE_POSITION_S, CAR_POSITION_S;

//������Ϣ 160bytes
typedef struct _SMART_CAR_INFO_XM_S
{
	char szCarPlateNum[16];	//���ƺ�
	char byRes[144];
}SMART_CAR_INFO_XM_S;

//Wifi̽����Ϣ160bytes
typedef struct _SMART_WIFIPROBE_INFO_XM_S
{
	int   nSignalIntensity;		//wifi�ź�ǿ��
	int	  nChannel;				//�ŵ�
	char szPhoneWifiMac[20];	//�ֻ�MAC
	char szRouteMac[20];		//·��MAC
	char byRes[112];
}SMART_WIFIPROBE_INFO_XM_S;	

/*�������Լ��*/
typedef struct _SDK_FACE_ATTRIBUTE_S
{
	signed char byAge;      //���� 
	signed char byGender;	//�Ա� -1 δ֪, 1 ��, 2 Ů
	signed char byGlasses; 	//�۾�  -1 δ֪, 0 �����۾�, 1 ���۾�, 2 ��ī�� 
	signed char byMask; 	//���� -1 δ֪, 0 ��������, 1 ������
	signed char byRace;		//����   -1 δ֪, 1 ������, 2 ������, 3 ������  
	signed char byEye;			//�۾� -1 δ֪, 0 �պ�, 1 ���� 
	signed char byMouth;		//��� -1 δ֪, 0 �պ�, 1 �ſ�
	signed char byBeard;		//����   -1 δ֪, 0 �޺���, 1 �к���  
	signed char byEmotion;		//����   -1 δ֪, 1 ����, 2 ƽ��, 3 ����, 4 ����, 5 ����, 6 ����, 7 ���, 8 б��, 9 ���
	signed char byAttractive; 	//���� [0�� ��
	signed char bySmile;      	//Ц��  -1 δ֪, 0 ΢Ц, 1 ƽ��
	signed char bySunglass;	//ī�� -1 δ֪, 0 ����ī��, 1 ��ī��
	signed char byHat;			//��ñ -1 δ֪, 0 ����ñ��, 1 ��ñ��
	signed char byIsCalling;	//��绰 -1 δ֪, 0 û��绰, 1 �ڴ�绰
	signed char byUpperbodyColor;	//������ɫ -1 δ֪, 0 ��ɫ, 1 ��ɫ, 2 ��ɫ, 3 ��ɫ, 4 ��ɫ, 5 ��ɫ, 6 ��ɫ, 7 ��ɫ, 8 ��ɫ, 9 ��ɫ, 10 ��ɫ, 11 �ۺ�ɫ, 12 ����, 13 ����, 14 ͼ��
	signed char byUpperbodyStyle;	//���¿�ʽ -1 δ֪, 0 ����, 1 T ��, 2 ����, 3 ����, 4 ����ȹ, 5 ����, 6 �п�, 7 ��֯ë��, 8 ��װ, 9 ���, 10 ����, 11 ���޷�, 12 ţ�з�
	signed char byHairStyle;		//���� -1 δ֪, 0 ��ͷ, 1 ͺͷ, 2 ƽͷ, 3 �̷�, 4 ����̷�, 5 ���緢, 6 ����
	signed char byRes[15];	
}SDK_FACE_ATTRIBUTE_S;
//ͼƬ���� 3072�ֽ�
typedef struct SDK_FACE_ATTR_S
{
	int	nvisits;							//���ô��� ���ڱȶԻ�
	int	nPicType;							//ͼƬ���� (���������ơ�WiFi̽���õ�)
	int nFaceQuality;						//��������
	int	nPicLen;							//ͼƬ��С(���������ơ�WiFi̽���õ�)
	int nPicID;								//ͼƬ����
	int	nFaceID;							//����ID (�����������õ�)
	int nFaceOrHead;						//��������ͷ����(1��ͷ��2����)
	int  byIsScenePic;						//����ͼ��ʶ��0��Сͼ��1����ͼ�� (�����������õ�)
	SDK_FACE_ATTRIBUTE_S stFaceAttribute;		//��������
	FACEPIC_SIZE_S  stFacePicSize;			//����������ͼ��ԭͼ���� (�����������õ�)
	FACE_POSITION_S stFacePosition;			//��������λ��(�����������õ�)
	char stFaceTime[32];					//ץ��ʱ��(�����������õ�)
	char stDevUUID[32];						//�豸UUID,��HK ID(���������ơ�WiFi̽���õ�)
	char stOsd[64];							//OSD��Ϣ(���������ơ�WiFi̽���õ�)
	union
	{
		SMART_CAR_INFO_XM_S stCarInfo;		//������Ϣ
		SMART_WIFIPROBE_INFO_XM_S stWifiProbeInfo;//wifi̽����Ϣ
	};
	int  nFeatureType;						//����ֵ����:0 float, 1 char ,2 int
	int  nFeatureLen;						//���nFeatureType���ͣ�����ֵ���鳤��
	//����Ԥ�������������ֵ
	union
	{
		float	fFeature[512];
		char	cFeature[2048];
		int		nFeature[512];
	}facefeature;
	char stFaceUtcTime[32];					//ץ��UTCʱ��   // YUVDZ_12_11 
	int byHasFaceAttr;						//�Ƿ������������Ϣ

	char stFacePicname[80];					//ץ��ͼƬ��
	char stFramePicname[80];				//����ͼƬ��
	int  nFacePicLen;						//ץ������ͼ��С
	int  nFramePicLen;						//ԭͼͼƬ��С
	int  nLiveNess;							//������ 0 ��ʾδ�����߼��δ�ɹ�  1 ��ʾ����
	float fLiveScore;						//�������
	char szBodyPicName[80];					//����ͼƬ�� 
	int	 nBodyPicLen;						//����ͼ��С 
	int  nStructureInfoLen;					//�ṹ����Ϣ���� 
	char sRes[332];					//Ԥ��	
}SDK_FACE_ATTR,*PSDK_FACE_ATTR;

typedef struct SDK_FA_ImprotFaceImageInfoCallback_s
{
	unsigned int uiSessionId;		///< �ỰID
	int iRet;				///< ����ֵ
	char sName[64];		///< ��������
	char sFileName[64];		//����ͼƬ���ļ���
}SDK_FA_ImprotFaceImageInfoCallback;
//=================================================================================//
//�ȶԽ��
typedef struct SDK_FA_FACECOMPARE_RESULT_ALARM_S		
{
	unsigned int   	deviceid;
	unsigned int   	channelid;
	unsigned int   	streamid;
	unsigned int   	wbmode;			//�ڰ�����
	unsigned int   	libindex;		//�ڰ�����������
	unsigned int   	libnumber;		//�ڰ�����������
	unsigned char   npicname[64];	//ʵʱ�ȶ�ͼƬ����
	unsigned char   cpicname[64];	//ʵʱ�ȶ�ͼƬ����
	float			result;		    //�ȶԽ��
	unsigned char   SnapTime[32];	////ץ��ʱ��
	unsigned int   	alarmcmd;
	unsigned char	byRes1[64];

	unsigned int   	guest;			//����ͳ��
	unsigned char 	Age;      		//���� 
	unsigned char 	Gender;			//�Ա�
	unsigned char 	Glasses; 		//�۾�  
	unsigned char 	Mask; 			//���
	unsigned char 	Race;			//����  
	unsigned char 	Eye;			//�۾� 	
	unsigned char 	Attractive;		//����ֵ 
	unsigned char	ByRes[117];		//Ԥ��

}SDK_FA_FACECOMPARE_RESULT_ALARM;  

//�ڰ�����
typedef struct SDK_FA_BLACKANDWHITELIST_CONFIG_S
{
	int					 byOutMode;			// 1 ���ļ�����; 2 ͼƬ
	int					 byWbMode;			// 1 ������; 2������
	int				 	 byAllNums;			// ʵ�ʿ���Ŀ
	int				 	 byLibIndex;		//������
	int					 byFileIndex;		//�ļ�����
	int					 byDataSize;		//�ļ���С
	char				 byFileName[64];	//����
	int					 byErrorCode;		//�����룬����XM_WB_ERROR_CODE
	int					 bySex;				//1--�� 2--Ů
	int					 byDataType;		// ����ֵ����  0 float,1 char ,2 int 
	int					 byExDataLenth;		//��չ���ݽṹ�峤��
	unsigned char		 byRes[24];
}SDK_FA_BLACKANDWHITELIST_CONFIG;


typedef struct SDK_XM_WB_CONFIG_EXDATA_S
{
	int					 byValidValue;			// ������Чֵ
	char					 byValidStartTime[32];		// ������ʼʱ��
	char					 byValidEndTime[32];		// ��������ʱ��
	char					 byPosition[32];			//ְλ
	char					 byPhoneNumber[32];		//����
	char					 byIdCard[32];			//���֤����
	char					 byHomeAddress[128];	//��ͥ��ַ
	char					 byRemark[256];			//��ע
	char		 			 byRes[476];
}SDK_XM_WB_CONFIG_EXDATA,*LP_SDK_XM_WB_CONFIG_EXDATA;

//����˽��Э���ϴ�
typedef struct SDK_FA_FS_PROTOCOL_S
{
	char szUDPaddr[64];	//������IP
	DWORD dwUDPport;	//�������˿ں�
	BYTE nUDPSDKEnable; //˽��Э���ϴ�ʹ�ܿ���
	BYTE szRes[3];		//����
	BYTE byRes[64];		//����
}SDK_FA_FS_PROTOCOL_S;

typedef struct SDK_FA_SMART_FACE_S
{
	INT			nEnable;			//����
	INT			nquality;			//������
	BYTE 		nExposureMode; 		//�����ع�ģʽ
	BYTE		nSnapMode;			//ץ��ģʽ 0�뿪��ץ�ľ���ѡ��   1����ץ��  2���ץ����Ϊ��λ  3���ץ��֡Ϊ��λ 4����ģʽ  5�뿪������ѡ��  6����+�뿪��
	BYTE 		nTrackmode;			//��������  		 0:�ر� 1:����
	BYTE		nFtpEnable;			//FTP�ϴ�����	0:�ر� 1:����
	INT			nFaceSize;			//����ʶ����С�ߴ�(60~300)
	INT			nMaxFaceSize;		//�������(300~500)
	BYTE		nFaceBLC;			//��������
	BYTE		nPicMode;			//ͼƬ�ϴ���ʽ(0������1ԭͼ��2������ԭͼ)
	BYTE 		nParamCheckFlag;
	BYTE		byFaceAreaExpand;		//����ͼƬ�ܱ߱�����չϵ��
	BYTE		byPicPrefixEnable;		//�Զ���ǰ׺����
	CHAR		szPicPrefix[16];			//ͼƬǰ׺
	INT			nTrackFrameNum;		//����ץ��֡��-----����ץ��
	BYTE		bySnapNum;				//���ץ�Ĵ���-----�뿪��ץ��ģʽ
	BYTE		byIntervalTime;			//���ʱ��---���ץ�ģ���Ϊ��λ
	BYTE		byFacePicQual;			//����ͼƬ��������
	BYTE		byFramePicQual;			//ԭͼ��������
	INT			nIntervalFrame;			//���֡��---���ץ�ģ�֡Ϊ��λ
	BYTE		byAttributeEnable;		//�������Կ���
	BYTE		byIntervalSnapNum;		//ץ�Ĵ���------���ץ��ģʽ
	BYTE		byAlignmentRes[2];		//�ֽڶ��룬û���õ�
	INT			nGateIntervalFrame;		//���֡��----բ��ģʽ
	BYTE		byRes[16];
}SDK_FA_SMART_FACE;

//����ʶ�����
typedef struct  SDK_FA_SNAP_FACE_CONFIG_S   
{
	SDK_SCHWEEK_TIME	aTime;
	SDK_FA_SMART_FACE   sSmartFace;  
	SDK_FA_FS_PROTOCOL_S stFsProtocols;
}SDK_FA_SNAP_FACE_CONFIG;

//ȫͨ������ʶ�����
typedef struct SDK_FA_SNAP_FACE_CONFIG_ALL_S
{
	SDK_FA_SNAP_FACE_CONFIG vSnapFaceConfigAll[NET_MAX_CHANNUM];
}SDK_FA_SNAP_FACE_CONFIG_ALL;

typedef struct SDK_FA_VI_DECTECT_S
{
	DWORD				dwSize;			
	INT					bEnable;
	SDK_AREA_RECT		stFaceMaskArea;
	BYTE				byRes[32];
}SDK_FA_VI_DECTECT;

typedef struct SDK_FA_VI_SHIELDED_S
{
	DWORD				dwSize;			
	INT					bEnable;
	SDK_AREA_RECT			stFaceArea[4];
	BYTE				byRes[32];
}SDK_FA_VI_SHIELDED;


//������������   384�ֽ�
typedef struct SDK_SMART_ALARM_S
{
	BYTE			aEnable;		//��������
	BYTE			aBEnable;		//��������������
	BYTE			aWEnable;		//��������������
	BYTE			aIoEnable;		//IO���ʹ��
	short			aIoTime;		//IO���ʱ��
	BYTE			aIoType;		//IO�������
	BYTE			aSimilarity;	//���ƶ� (0-100)
	SDK_SCHWEEK_TIME	aTime;			//����ʱ��

	short			aCmpMode;		//ʶ��ģʽ (0����ʶ��  ,1 һֱʶ��)
	short			aCmpNum;		//ʶ����� (1-10)
	//�ֻ�APP��Ϣ����
	BYTE			aPushEnable;			//���Ϳ���
	BYTE			aBPushEnable;			//��������Ϣ����
	BYTE			aWPushEnable;			//��������Ϣ����
	BYTE			aNWPushEnable;			//�ǰ�������Ϣ����


	//20180528
	BYTE			aAudioInpute;	//��Ƶ����
	BYTE			aVEnable;		//VIP����
	BYTE			aVPushEnable;	//VIP��Ϣ����
	BYTE			aNonWhite;		//�ǰ���������

	INT				aAlarmInfoType;		//������Ϣ��������:  0 ������Ϣ  1Ӣ����Ϣ	2 �ֻ�Ĭ�ϱ�����Ϣ

	BYTE		 	byRes[24];
}SDK_SMART_ALARM;
//������������ȫͨ��
typedef struct SDK_SMART_ALARM_ALL_S
{
	SDK_SMART_ALARM vSmartAlarm[NET_MAX_CHANNUM];
}SDK_SMART_ALARM_ALL;

//�����㷨�汾��Ϣ
typedef struct SDK_FA_SMART_VERSION_INFO_S
{
	char szLib_version[16] ;    //�㷨��汾
	char szModel_version[16];	//ģ�Ͱ汾
	BYTE  nbyLic;				//����				
	BYTE  byRes[7];				//����
}SDK_FA_SMART_VERSION_INFO;

//=========================================================================


//Э��Ժڰ���������
typedef enum _WBLIST_ACTION_TYPE
{
	OUT_INDEX = 1,					//�����ļ�����
	OUT_PICTURE,					//�����ڰ��������е���ͼƬ
	OUT_PICTURE_COMP,				//�ȶԺ󵼳���Ӧ��ͼƬ
	OUT_PICTURE_DEL,				//ɾ�����е���ͼƬ
	OUT_PICTURE_DELALL,				//ɾ���ڰ��������п�
	IN_PICTURE_ADD,					//ͨ������ͼƬ���һ�źڰ�����
	IN_PICTURE_ADD_SNAP,			//ͨ��ץ����Ӻڰ�����
	IN_PICTURE_GET_FEATURE,			//ͨ������һ��ͼƬ��ȡ����ֵ
	IN_INDEX_GET_FEATURE,			//ͨ����������ȡ����ֵ
	OUT_PICTURE_USER_INFO,   		//�����û���ϸ��Ϣ
	IN_PICTURE_USER_INFO_UPDATA,	//�û���Ϣ����

	//�ȶԷ��������ӵ�4��,IPC��δ�õ���������Ҫ��SDKͳһ
	IN_PICTURE_GET_SIMILARITY_PIC_MSG = 12, //ͨ������һ��ͼƬ��ȡ����ֵ�����Ƶĵ׿�ͼƬ��Ϣ  
	IN_PICTURE_GET_FEA_AND_ALARM = 13,		//ͨ������һ��ͼƬ��ȡ����ֵ�����ܿ��ܵı���
	IN_COPY_DATEBASE = 14, 					//����һ�����ݿ⵽��һ�����ݿ�
	IN_MODIFY_PICTURE_MESSAGE = 15,			//�޸�ͼƬ��Ϣ
	IN_FEATURE_ADD,							//ͨ������ֵ���һ�źڰ�����
	IN_FEATURE_UPDATE,						//ͨ������ֵ���һ�źڰ�����
	OUT_ATTENDANCE ,						//���ڵ���
	OUT_CMP_INFO ,							//�ȶ���Ϣ����
	OUT_WBLIST_EN
}WBLIST_ACTION_TYPE;


//�ڰ������ļ���������Ϣ�ṹ��
typedef struct _SDK_INDEX_INFO_S {
	int libindex;		//����
	int fileindex;		//ͼƬ�������	
}SDK_INDEX_INFO;


typedef struct _SDK_FILEINDEX_INFO_S {
	SDK_INDEX_INFO findex;
	int enable;					//�Ƿ�ʹ��
	union{
		char name[NET_NAME_PASSWORD_LEN];	//ͼƬ���֣��ɰ汾
		char userid[NET_NAME_PASSWORD_LEN];	//�û�ID,�ⲿ�����������壬����֮ǰ���������ݣ��������°汾
	};
	union{
		int checksum;				//�����룬�ɰ汾
		int syslistID;				//ϵͳID���ⲿ�����������壬����֮ǰ���������ݣ��������°汾
	};
}SDK_FILEINDEX_INFO;


typedef struct _SDK_INFO_EX_S
{
	int						byValidValue;			// ������Чֵ
	char					 byValidStartTime[32];		// ������ʼʱ��
	char					 byValidEndTime[32];		// ��������ʱ��
	char					 byPosition[32];			//ְλ
	char					 byPhoneNumber[32];		//����
	char					 byIdCard[32];			//���֤����
	char					 byHomeAddress[128];	//��ͥ��ַ
	char					 byRemark[256];			//��ע
	char		 			 byRes[476];
}SDK_INFO_EX;

typedef struct _SDK_FILEINDEX_DATA_S
{
	SDK_FILEINDEX_INFO  fileindex;
	SDK_INFO_EX 		   info_ex;
}SDK_FILEINDEX_DATA;


typedef struct _SDK_FILEINDEX_INFO_EX_S
{
	int 	syslistid;					//ϵͳID �����ʱ���ø�ֵ����ϵͳ����
	int 	libindex;					//���� �����ʱ���ø�ֵ����ϵͳ����
	int 	fileindex;					//ͼƬ������� �����ʱ���ø�ֵ����ϵͳ����	
	int 	enable;						//ʹ�ܿ���
	int 	timelimit;					//������Ч�� 0 ������Ч��1 ������Ч����Чʱ�����sTime�� eTime
	int  	listmode;					//����ģʽ: 1 ��������2��������3 VIP����
	int  	count;						//ͳ�ƴ���
	int  	sex;						//�Ա�
	char    usrid[36];					//�û�ID���߱��
	char    idcard[32];					//���ID
	char 	name[64];					//����
	char  	picname[64];				//ͼƬ��   ϵͳ���ɣ���֧���޸�
	char    nation[12];					//����
	char 	birth[24];					//����
	char    phone[16];					//����
	char    areacode[32];				//�������
	char	usrcode1[32];				//��������
	char	usrcode2[32];				//С������
	char 	type[12];					//����
	char    dTime[20];					//���ʱ��
	char    sTime[20];					//��ʼʱ��
	char    eTime[20];					//����ʱ��
	int		usrparam1;					//���ò���1
	int		usrparam2;					//���ò���2
	int		usrparam3;					//���ò���3
	int		usrparam4;					//���ò���4 	
	int		usrparam5;					//���ò���5

	char	resID[32];					//����ID	   //����ID
	char	areaAddress[100];			//�����ַ
	char	resname[32];				//�������� //��������
	char  	usrdata1[32];				//�û���������1,
	char  	usrdata2[24];				//�û���������2
	char  	usrdata3[32];				//�û���������3
	char  	usrdata4[36];				//�û���������4
	char  	usrdata5[88];				//�û���������5
	char 	remark[180];				//��ǩ		
}SDK_FILEINDEX_INFO_EX;

//���ڣ����ڼ�¼��ѯ����ѯ����_SMART_CUSTOM_ATTEND_STATISTICS����512
typedef struct _SDK_SMART_CUSTOM_ATTEND_STATISTICS
{
	//����ǲ�ѯ�����ʱ��ֻ��ʾ����ʱ��,��������ʾͳ���ϰ��������
	int					iChannel;					//ͨ��	
	char				byStartTime[32];			//��ʼʱ�䣺������Ч   
	char				byEndTime[32];				//����ʱ�䣺������Ч
	char				byName[64];					//����(��ѡ)
	char				byUserID[36];				//�û�ID(��ѡ)
	int					iPage;						//�ڼ�ҳ���ӵ�1ҳ��ʼ��0�Ļ���ʾֻ������������������Ϣ
	int					iPageCount;					//ÿҳ��������
	int					iQueryOrPaged;				//��ѯ���Ƿ�ҳ  1:��ѯ2:��ҳ
	int					iQueryStatus;    			//ͨ��״̬��ѯ��Ϣ
	int					iQuerySomedayOrStatistic;	//��ѯĳ����Ϣ����ͳ����Ϣ
	char				byRes[828];
	int					iTotalCount;				//��������
	int					iCount;						//�������
}SDK_SMART_CUSTOM_ATTEND_STATISTICS;

typedef struct  _SDK_SMART_PERSON_ATTEND_INFO 
{
	char				byName[64];					//����(��ѡ)
	char				byUserID[36];				//�û�ID(��ѡ)
	int					iSyslistID;					//ϵͳID
	char				byOnDutyStat;				//�ϰ�״̬ :0 δ����,1 ����,2 �ٵ� 
	char				byOffDutyStat;				//�°�״̬ :0 δ����,1 ����,3 ����
	char				bysres0[2];
	int					iNormalNum;					//��������
	int					iLateNum;					//�ٵ�����
	int					iEarlyNum;					//���˴���
	int					iAbsentNum;					//δ����
	int					iShouldTimes;				//Ӧ������
	int					iActualTimes;				//ʵ������
	char				byOnDutyTime[32];			//�ϰ�ʱ��
	char				byOffDutyTime[32];			//�°�ʱ��
	char				byCheckOnDate[32];			//���쿼������
	char				byRes1[796];
}SDK_SMART_PERSON_ATTEND_INFO ;

typedef struct SDK_SMART_FACE_CMP_QUERY_INFO_
{
	int					sLibRowid;				//���к�
	float				sLibSimilarity;			//���ƶ�	

	char				sName[64];				//����(��ѡ)
	char				sUserID[36];				//�û�ID(��ѡ)
	char				sLibSnapTime[32];		//ץ��ʱ��
	int 				sLibChannelid;			//ͨ����
	int					sLibMode;				//����	����		
	int					sSysListID;				//ϵͳID
	int 	  			nLibGuest;				//����ͳ��
	char				cLibAge;      			//���� 
	char  				cLibGender;				//�Ա�
	char				cLibGlasses; 			//�۾�  
	char				cLibMask; 				//���
	char				cLibRace;				//����  
	char				cLibEye;				//�۾� 	
	char				cLibAttractive;			//����ֵ
	char				cLibBeard;				//����
	char				cLibEmotion;			//����
	char				sLibCpicname[80];		//ʵʱ�ȶ�ͼƬ����
	char				sBackPicName[80];		//����ͼƬ����
	char				sBodyPicName[80];		//����ͼƬ����
	char				sRes0[3];		
	char				sRes1[616];
}SDK_SMART_FACE_CMP_QUERY_INFO;


//�ȶԣ��ȶԼ�¼��ѯ����ѯ���ݷ���FACE_CMP_QUERY_CONDITION������Ϣ512
typedef struct SDK_FACE_CMP_QUERY_CONDITION_ 
{
	int				iChannel;				//ͨ��	
	char			sStartTime[32];			//��ʼʱ�䣺������Ч
	char			sEndTime[32];			//����ʱ�䣺������Ч
	char			sName[64];				//����(��ѡ)
	char			sUserID[36];			//�û�ID
	int				sLibMode;				//0:����,1:��,2:��,3:Vip ����(��ѡ)			
	int				iPage;					//�ڼ�ҳ���ӵ�1ҳ��ʼ��0�Ļ���ʾֻ������������������Ϣ
	int				iPageCount;				//ÿҳ��������
	int				iQueryOrPaged;			//��ѯ���Ƿ�ҳ  1:��ѯ2:��ҳ
	char			sRes[832];
	int				iTotalCount;			//��������
	int				iCount;					//�������

}SDK_FACE_CMP_QUERY_CONDITION;

typedef struct _SMART_WB_CONFIG_EX		//2048
{
	int						iOpMode;			//���������ģʽ�����ݼ�WBLIST_ACTION_TYPEֵ
	int						iWbmode;			//����ģʽ�����ݼ�WBLIST_MODEֵ
	int						iOpFlag;			//����Ψһ��ʶ:0 ͨ��i_sUserID��������1 ͨ��i_iSyslistID��������Ĭ��0
	int						iSyslistID;			//����ϵͳID;
	char					sUserID[36];		//�û�ID��Ψһ��ʶ
	char					sFaceID[36];		//����ID�����ڱ�ʾͬһ�û���������ID,�������Ҫ�Ļ��Ͳ��ø�ֵ
	int						iBodyLen;			//���ýṹ�峤�ȣ���Ҫ��ָsdk_fileindex_info_Ex1���ȣ����Ϊ0����û�иò���

	int						iErrorCode;			//������
	int						iLibIndex;			//������
	int						iFileIndex;			//�ļ�����
	int						iAllNums;			//ʵ�ʿ���Ŀ
	int						iSyslistid;		
	int 					iFeatureType;		//����ֵ����  0 float,1 char ,2 int 
	int						iDataSize;
	char					sRes0[104];			//Ԥ��
	union
	{
		SDK_FILEINDEX_INFO_EX   stUserInfo;					//�û�������ϸ��Ϣ������ӡ�����ʱ����Ҫ��Ӹ���Ϣ
		SDK_SMART_CUSTOM_ATTEND_STATISTICS stAttendInfo;	//���ڲ�ѯ��Ϣ
		SDK_FACE_CMP_QUERY_CONDITION stCmpInfo;				//�ȶԼ�¼��ѯ��Ϣ
	};
	char					sRes[800];						//���ڿ�����SDK_FILEINDEX_INFO_EX��չ
}SDK_SMART_WB_CONFIG_EX;

typedef struct _SDK_COMM_HEAD_S		//size = 20
{
	unsigned char headflag;
	unsigned char version;
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned int  sessionId;
	unsigned int  sequenceNum;
	unsigned char totalPacket;
	unsigned char curPacket;
	unsigned short messageid;
	unsigned int  datalength;
}SDK_COMM_HEAD, *PSDK_COMM_HEAD;

//ͼƬͷ��Ϣ
typedef struct _SDK_PICTURE_HEAD_S		//256�ֽ�
{
	unsigned short headflag;
	unsigned char  tag;
	unsigned char  frametype;
	unsigned char  frameinfo;
	unsigned char  version;
	unsigned short messageid;
	unsigned short  width;
	unsigned short  height;
	unsigned int   ndatasize;
	unsigned int   deviceid;
	unsigned int   channelid;
	unsigned int   streamid;
	unsigned char  picnumber[64];
	unsigned char  filename[64];	//
	unsigned int   featureEn;
	unsigned int   nFeatureLen;
	unsigned int   nDevKeyID;		//�豸���
	unsigned int   nAttrInfoLen;	//����������Ϣ��С
	unsigned int   nCmpInfoLen;		//�ȶ���ϸ��Ϣ��С
	unsigned int   nUserInfo1Len;	//�û��Զ�����Ϣ��С
	unsigned int   nFacePicLen;		//ץ��ͼƬ��С������0ʱû������
	unsigned int   nFramePicLen;	//����ͼƬ��С������0ʱû������
	unsigned int   nLibPicLen;		//�׿�ͼƬ��С������0ʱû������
	unsigned int   nBodyPicLen;		//�����մ�С 
	unsigned int   nPicTotalLen;		//ͼƬ�ܴ�С 
	unsigned char  res[52];
	unsigned int   headend;			//
}SDK_PICTURE_HEAD, *PXM_PICTURE_HEAD;

//�����ȶ���Ϣ 2048�ֽ�
typedef struct _SDK_FACE_COMPARE_INFO_S
{
	float fCompareResult;				//�ȶ����ƶ�
	int  nFaceAlarm;					//��������
	char stCompareTime[32];				//�ȶ�ʱ��
	SDK_FILEINDEX_INFO_EX stIndexInfo;	//�����׿���Ϣ
	char stRes[984];
}SDK_FACE_COMPARE_INFO;

//�������ӷ�����Ϣ
typedef struct _SDK_FACE_MONITOR_INFO_S
{
	SDK_PICTURE_HEAD stPictureHead;				//ͼƬͷ��Ϣ
	SDK_FACE_ATTR stFaceAttr;					//������Ϣ
	SDK_FACE_COMPARE_INFO stFaceCompareInfo;	//�ȶ���Ϣ
}SDK_FACE_MONITOR_INFO, *LPSDK_FACE_MONITOR_INFO;

#define MAX_USER_DATA_LEN		1024			//�û��������ݳ���

//������
typedef enum _XM_WB_ERROR_CODE
{
	WB_OK = 1,					//�ɹ�
	WB_FAILE = -1,				//ʧ��
	WB_COLLECT_ERROR = -2,		//��ȡ����ֵʧ��
	WB_FILEINDEX_ERROR = -3,	//�ļ����ֱ���ظ�
	WB_LIB_FULL = -4,			//����
	WB_ADD_TIME_OUT = -5,		//��ӳ�ʱ
	WB_PARA_ERROR	= -6,		//��������
	WB_FILE_BIG		= -7,		//�ļ�̫��
	WB_SPACE_ERROR	= -8,		//�洢�ռ䲻��
	WB_FILE_OPEN_ERROR	= -9,	//�ļ���ʧ��
	WB_NO_DBFILE	= -10,		//û�����ݿ�
	WB_FILE_ERROR	= -11,		//ͼƬ��ȡʧ��
	WB_DBFILE_BAD	= -12,		//���ݿ��ļ���
	WB_PIC_QUALITY_ERROR = -13, //ͼƬ������
	WB_FILE_WHSIZE_ERROR = -14, //ͼƬ�ߴ���󣬿�߲���Ϊ����
	WB_FILE_FACE_ERROR	 = -15, //�������ʧ�ܣ�û��⵽�������߼�⵽��������
	WB_PIC_FORMAT_ERROR = -16,  //ͼƬ��ʽ����format

	WB_FACE_AREA_ERROR	 = -17,  //�����������
	WB_FACE_HAND_ERROR	 = -18,  //�㷨�����������
	WB_FACE_BUSY		 = -19,	 //�豸æ

}XM_WB_ERROR_CODE;



typedef enum _XM_WB_WBLIST_RESULT_S
{
	WBLIST_OK = 100,
	WBLIST_FAILE = 160, 			//ʧ��
	WBLIST_COLLECT_ERROR = 161, 	//��ȡ����ֵʧ��
	WBLIST_FILEINDEX_ERROR = 162,	//�ļ����ֱ���ظ�
	WBLIST_LIB_FULL = 163,			//����
	WBLIST_ADD_TIME_OUT = 164,		//��ӳ�ʱ
	WBLIST_PARA_ERROR	= 165,		//��������
	WBLIST_FILE_BIG 	= 166,		//�ļ�̫��
	WBLIST_SPACE_ERROR	= 167,		//�洢�ռ䲻��
	WBLIST_FILE_OPEN_ERROR	= 168,		//�ļ���ʧ��
	WBLIST_NO_DATABASE = 169,		//û�����ݿ�
	WBLIST_FILE_READ_ERROR = 170,	//ͼƬ��ȡʧ��
	WBLIST_DATABASE_ERROR = 171,	//���ݿ���
	WBLIST_PIC_QUALITY_ERROR = 172, //ͼƬ������
	WBLIST_FILE_WHSIZE_ERROR = 173,  // ͼƬ�ߴ���󣬿�߲���Ϊ����
	WBLIST_FILE_FACE_ERROR	 = 174,  //�������ʧ�ܣ�û��⵽�������߼�⵽��������
	WBLIST_PIC_FORMAT_ERROR = 175,  //ͼƬ��ʽ����format
	WBLIST_FACE_AREA_ERROR	 = 176,  //�����������
	WBLIST_FACE_HAND_ERROR	 = 177,  //�㷨�����������
	WBLIST_FACE_BUSY		 = 178,	 //�豸æ

}XM_WB_WBLIST_RESULT;

// add by barney 20180919
typedef struct _SDK_COMPINFO_FLAG
{
	int iAlarmEn;
	int iCaptureEn;
	int iFeatureEn;
	int iLibPicEn;
}SDK_COMPINFO_FLAG;

typedef struct _SDK_FACEMONITOR_INFO_FLAG
{
	int	nDeviceId;		//�û��������
	int	nChnnelId;		//�û��������
	int	nStreamId;		//�û��������
	int nFaceAttrEn;		// �����������ͼƬ���ԣ���������FACE_ATTR���ݣ����л���Ĭ�ϴ�
	int nFaceCmpInfoEn;		//ͼƬ�ȶ���Ϣʹ�ܣ���������FACE_COMPARE_INFO���ݣ����ø����ݲ�������
	int nCaptureEn;			// ץ������ͼʹ�ܣ���������ץ��ͼƬ���ݣ�����Ҫ���Բ�������
	int nFramePicEn;		// /����ͼʹ�ܣ���������ץ��ͼƬʱ��Ӧ�ı���ͼ���ݣ�����Ҫ���Բ�������
	int	nLibPicEn;			//������ͼƬ����������ȶԳɹ�ʱ��������ͼƬ����	������Ҫ���Բ�������
	int nBodyPicEn;			//����ͼ
	int	nUserExDataEn;		//�����ͻ���չ��NVR��������
}SDK_FACEMONITOR_INFO_FLAG;

#define		SNAP_TIME_LEN		32
#define		PICTURE_NAME_LEN	64
#define		DEVICE_IP_LEN		16
//�ȶԽ��
typedef struct SDK_FACECOMPARE_RESULT_S		
{
	unsigned int	deviceid;
	unsigned int	channelid;
	unsigned int	streamid;
	unsigned int	wbmode; 				//����������
	unsigned int	libindex;				//����������
	unsigned int	libnumber;				//����������
	char	picnameComp[PICTURE_NAME_LEN];	//��ͼͼƬ����
	char	*pCompImgData;					//��ͼͼƬ����ָ��
	int		iCompImgSize;					//��ͼͼƬ���ݳ���
	char	picnameSnap[PICTURE_NAME_LEN];	//ʵʱ�ȶ�ͼƬ����
	char	*pSnapImgData;					//ʵʱ�ȶ�ͼƬ����ָ��
	int		iSnapImgSize;					//ʵʱ�ȶ�ͼƬ���ݳ���

	float			result; 		//�ȶԽ��
	unsigned char	SnapTime[SNAP_TIME_LEN];	////ץ��ʱ��
	unsigned char   cDeviceIP[DEVICE_IP_LEN];	//�豸IP
	unsigned char	byRes[48];

	unsigned int	guest;			//����ͳ��
	unsigned int	Age;			//���� 
	unsigned int	Gender; 		//�Ա�
	unsigned int	Glasses;		//�۾�	
	unsigned int	Mask;			//���
	unsigned int	Race;			//����	
	unsigned int	Eye;			//�۾�	
	unsigned int	Attractive; 	//����ֵ 
	unsigned int	Beard;			//����
	unsigned int	Emotion;		//����
	unsigned char	ByRes[117]; 	//Ԥ��

	int 			facealarm;		//�������� , Ԥ��
	float			facecharacter[128];
}SDK_FACECOMPARE_RESULT;  
//=============================================//
//����ͼƬ����
typedef struct SDK_CAR_MDEIA_HEAD_S	//size = 20
{
	unsigned char headflag;
	unsigned char version;
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned int  sessionId;
	unsigned int  sequenceNum;
	unsigned char channel;
	unsigned char endflag;
	unsigned short messageid;   
	unsigned int  datalength;
}SDK_CAR_MDEIA_HEAD, *PSDK_CAR_MDEIA_HEAD;
/************************************************/

//����-��ɳȫͼ���û�����
//7��ͷ 9��ͷ
#define SDK_QT_MEMORY_MAX_BYTE   512*1024				//����ֽ� 512KB
#define SDK_QT_MEMORY_MAX_AREA   64					//������ 64 * 8 *1024 
typedef struct SDK_QT_MEMORY_SAVE_S
{
	int type; 			//����[0-63]
	int len;			//��д���ַ������� strlen
  	char data[32*1024];		//����
}SDK_QT_MEMORY_SAVE;




//*************************************************************************************************************�Զ���ṹ��

typedef struct _SDK_SM_LUMADETECT
{
	int bEnable;
	int sensitivity;
}SDK_SM_LUMADETECT;


typedef struct _SDK_SM_ODDETECT
{
	int	bEnable;									//ʹ��
	int sensitivity;								//��ֵ
	SDK_RECTANGLE_POINT	stMDArea[DETECT_AREA_NUM];		//�ڵ�����
}SDK_SM_ODDETECT;
//==========================================================================

// �����ϴ�ͨ���ص�����ԭ��
typedef void (CALL_METHOD *fUploadDataCallBack) (JVT_LONG lLoginID, long UploadType, char *pBuffer, unsigned long dwBufSize, JVT_DWORD nUser);

// ͸�����ڻص�����ԭ��
typedef void (CALL_METHOD *fTransComCallBack) (JVT_LONG lLoginID, long lTransComType, char *pBuffer, unsigned long dwBufSize, JVT_DWORD nUser);
//�������Ͽ��ص�ԭ��
typedef void (CALL_METHOD *fDisConnect)(JVT_LONG lLoginID, char *pchDVRIP, long nDVRPort, unsigned long dwUser);

//ԭʼ���ݻص�ԭ��
typedef int(CALL_METHOD *fRealDataCallBack_JL) (JVT_LONG lLoginID, long dwDataType, unsigned char *pBuffer, long lbufsize, JVT_DWORD nUser);
typedef int(CALL_METHOD *fRealDataCallBack_V2) (JVT_LONG lLoginID, const PACKET_INFO_EX *pFrame, JVT_DWORD nUser);

// �ط�¼����Ȼص�ԭ��
typedef void(CALL_METHOD *fDownLoadPosCallBack) (JVT_LONG lLoginID, long lTotalSize, long lDownLoadSize, JVT_DWORD nUser);

//��Ϣ������,����ע�ᣩ�ص�ԭ��
typedef bool (CALL_METHOD *fMessCallBack)(JVT_LONG lLoginID, char *pBuf, unsigned long dwBufLen, JVT_DWORD nUser);

//�����豸����ص�ԭ��
typedef void(CALL_METHOD *fUpgradeCallBack) (JVT_LONG lLoginID, long lUpgradechannel, int nTotalSize, int nSendSize, JVT_DWORD nUser);

// �����Խ�����Ƶ���ݻص�����ԭ��
typedef void (CALL_METHOD *pfAudioDataCallBack)(JVT_LONG lVoiceHandle, char *pDataBuf, long dwBufSize, char byAudioFlag, JVT_DWORD nUser);

//���ز��Ž����ص�ԭ��
typedef void (CALL_METHOD * fLocalPlayFileCallBack)(JVT_LONG lPlayHand, JVT_DWORD nUser);

//��Ϣ֡�ص�����
typedef void (CALL_METHOD  *InfoFramCallBack)(JVT_LONG lPlayHand, long nType, LPCSTR pBuf,long nSize, JVT_DWORD nUser);

//�����Ӷ��߻ص�
typedef void (CALL_METHOD *fSubDisConnectCallBack)(JVT_LONG lLoginID, SubConnType type, long nChannel, JVT_DWORD nUser);

#ifdef WIN32
//RigisterDraw�ص�ԭ��
typedef void (CALL_METHOD * fPlayDrawCallBack)(JVT_LONG lPlayHand,HDC hDc,JVT_DWORD nUser);
#else//linuxû�õ�����ص�
typedef void (CALL_METHOD * fPlayDrawCallBack)(JVT_LONG lPlayHand,void* hDc,JVT_DWORD nUser);
#endif // WIN32  


typedef int(CALL_METHOD *fFaceImageDataCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_PICTURE_HEAD *pPictureHead,SDK_FACE_ATTR* pPictureAttr, JVT_DWORD nUser);

typedef int(CALL_METHOD *fFaceCompaeResultCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize, JVT_DWORD dwUser);

typedef int(CALL_METHOD *fFaceBlackAndWhiteListCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pConfig,JVT_DWORD nUser);

typedef int(CALL_METHOD *fCarLicensePlateImageDateCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,SDK_CAR_MDEIA_HEAD *pConfig,JVT_DWORD nUser);

typedef int(CALL_METHOD *fListManagementCallBack) (JVT_LONG lSubFaceHandle, char* pBuffer,long lbufsize, char* pConfig, JVT_DWORD nUser);

typedef int(CALL_METHOD *fFaceMonitorCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize, JVT_DWORD dwUser);


//*** */SDK��ʼ��
VIDEO_NET_API long CALL_METHOD VideoNet_Init(fDisConnect cbDisConnect, JVT_DWORD nUser);

//*** */SDK�˳�����
VIDEO_NET_API bool CALL_METHOD VideoNet_Cleanup();

//��ȡ������Ϣ
VIDEO_NET_API long CALL_METHOD VideoNet_GetLastError();

// ���������豸��ʱʱ��ͳ��Դ���
//nWaitTime:��λms������ʱĬ��5000ms,
//nTryTimes:����,������ʱĬ��3��
VIDEO_NET_API bool CALL_METHOD VideoNet_SetConnectTime(long nWaitTime, long nTryTimes);

//socketType �ο����� SocketStyle��Ĭ����0 
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_Login(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPVIDEONET_DEVICEINFO lpDeviceInfo, int *error,int socketType = 0);

//���豸ע����չ�ӿ�
//���ӵ�½���� 0==web 1 ==�������� 2 == ��������  102 == �ⲿ���ܣ��ڲ��Ͳ��ü�����
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_LoginEx(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPVIDEONET_DEVICEINFO lpDeviceInfo, int nType, int *error);

//*** */���豸ע��
VIDEO_NET_API long CALL_METHOD VideoNet_Logout(JVT_LONG lLoginID);

//���ý���DVR��Ϣ�ص�, ���籨����Ϣ,��ID������
VIDEO_NET_API bool CALL_METHOD VideoNet_SetDVRMessCallBack(fMessCallBack cbAlarmcallback, JVT_LONG lUser);

//���������ϴ�ͨ��
VIDEO_NET_API long CALL_METHOD VideoNet_SetupAlarmChan(JVT_LONG lLoginID);
VIDEO_NET_API bool CALL_METHOD VideoNet_CloseAlarmChan(JVT_LONG lLoginID);

//Զ�������豸�ӿ� �������ͼ�SDK_CONFIG_TYPE
VIDEO_NET_API long  CALL_METHOD VideoNet_GetDevConfig(JVT_LONG lLoginID, unsigned long dwCommand, int nChannelNO, char * lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned,int waittime = 1000);
VIDEO_NET_API long  CALL_METHOD VideoNet_SetDevConfig(JVT_LONG lLoginID, unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);
//�����������豸���ã�Ŀǰֻ֧�ֶ��������ý�������
VIDEO_NET_API long CALL_METHOD VideoNet_SetConfigOverNet(unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);

//��־��ѯ
VIDEO_NET_API bool CALL_METHOD VideoNet_FindDVRLog(JVT_LONG lLoginID, SDK_LogSearchCondition *pFindParam, SDK_LogList *pRetBuffer, long lBufSize, int waittime = 2000);

//��ʵʱԤ��
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_RealPlay(JVT_LONG lLoginID, LPVIDEONET_CLIENTINFO lpClientInfo);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopRealPlay(JVT_LONG lRealHandle);
VIDEO_NET_API long CALL_METHOD VideoNet_PauseRealPlay(JVT_LONG lLoginID, bool bPause);

//���ûص��������û��Լ�����ͻ����յ�������
VIDEO_NET_API bool CALL_METHOD VideoNet_SetRealDataCallBack(JVT_LONG lLoginID,fRealDataCallBack_JL cbRealData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetRealDataCallBack_V2(JVT_LONG lLoginID,fRealDataCallBack_V2 cbRealData, JVT_DWORD nUser);

//����ص�����,�ú�����Ҫ��VideoNet_StopRealPlayǰ����
VIDEO_NET_API bool CALL_METHOD VideoNet_DelRealDataCallBack(JVT_LONG lLoginID,fRealDataCallBack_JL cbRealData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DelRealDataCallBack_V2(JVT_LONG lLoginID,fRealDataCallBack_V2 cbRealData, JVT_DWORD nUser);

//¼���ѯ
//lLoginID		��½���
//lpFindInfo	��ѯ����
//lpFileData	���ҵ���¼�����ݣ��ⲿ���ڴ�
//lMaxCount		���¼����Ŀ
//findcount		���ҵ���¼����Ŀ
//waittime		��ѯ��ʱʱ��
VIDEO_NET_API long CALL_METHOD VideoNet_FindFile(JVT_LONG lLoginID, VIDEONET_FINDINFO* lpFindInfo, VIDEONET_FILE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime = 5000);

//¼���ѯ
//lLoginID		��½���
//lpFindInfo	��ѯ����
//lpFileData	���ҵ���¼�����ݣ��ⲿ���ڴ�
//waittime		��ѯ��ʱʱ��
VIDEO_NET_API long CALL_METHOD VideoNet_FindFileByTime(JVT_LONG lLoginID, SDK_SearchByTime* lpFindInfo, SDK_SearchByTimeResult *lpFileData, int waittime = 10000);

//¼��ط�
//lLoginID		��½���
//sPlayBackFileName	�طŵ�¼������
//cbDownLoadPos ���Ȼص�		�û�֪ͨ�û��豸�Ƿ��Ѿ������ݷ������
								//�ͻ������ʵʱ��ʾ���ȣ�Ӧ�ô����������ȡʱ��������
								//���粿�ֲ���������������Ե�ǰ�������ݴ�С/�ܴ�С��������ȵĻ����Ǻ�׼��Ӧ���Ե�ǰʱ�䣬���ݿ�ʼʱ��ͽ���ʱ�����������
//fDownLoadDataCallBack ���ݻص�
//dwDataUser	�ص�����
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_PlayBackByName(JVT_LONG lLoginID, VIDEONET_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_JL fDownLoadDataCallBack, long dwDataUser);
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_PlayBackByName_V2(JVT_LONG lLoginID, VIDEONET_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_V2 fDownLoadDataCallBack, long dwDataUser);

//��ʱ�����¼��ط�
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_PlayBackByTime(JVT_LONG lLoginID, VIDEONET_FINDINFO* lpFindInfo, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_JL fDownLoadDataCallBack, long dwDataUser);
//VIDEO_NET_API long CALL_METHOD VideoNet_PlayBackByTimeEx(JVT_LONG lLoginID, int nChannelID, LPVIDEONET_TIME lpStartTime,
//											LPVIDEONET_TIME lpStopTime, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser,
//											fDownLoadPosCallBack cbDownLoadPos, long dwPosUser);

VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_PlayBackByTimeEx(JVT_LONG lLoginID, VIDEONET_FINDINFO* lpFindInfo,fRealDataCallBack_JL fDownLoadDataCallBack, JVT_DWORD dwDataUser,
											fDownLoadPosCallBack cbDownLoadPos, JVT_DWORD dwPosUser);

VIDEO_NET_API bool CALL_METHOD VideoNet_StopPlayBack(JVT_LONG lPlayHandle);

//�طſ��Ʒ�,��ͣ,��λ�ȵ�
VIDEO_NET_API bool CALL_METHOD VideoNet_PlayBackControl(JVT_LONG lLoginID, long lControlCode,long lCtrlValue);

//¼������,�û����Բ�ʹ�ûص����Լ�ͨ��VideoNet_GetDownloadPos��ȡ����
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_GetFileByName(JVT_LONG lLoginID,VIDEONET_FILE_DATA *sPlayBackFile,char *sSavedFileName, 
											fDownLoadPosCallBack cbDownLoadPos = NULL, JVT_DWORD dwDataUser = NULL,fRealDataCallBack_JL fDownLoadDataCallBack = NULL);
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_GetFileByTime(JVT_LONG lLoginID, VIDEONET_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge = false,
											fDownLoadPosCallBack cbDownLoadPos = NULL, JVT_DWORD dwDataUser = NULL ,fRealDataCallBack_JL fDownLoadDataCallBack =NULL );

VIDEO_NET_API bool CALL_METHOD VideoNet_StopGetFile(JVT_LONG lFileHandle);
//��ȡ���ؽ���
VIDEO_NET_API int CALL_METHOD VideoNet_GetDownloadPos(JVT_LONG lFileHandle);

//����
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_Upgrade(JVT_LONG lLoginID, char *sFileName, int nType = 0, fUpgradeCallBack cbUpgrade = NULL, JVT_DWORD nUser = 0);
//����״̬ 1 �ɹ��� 2 �������� 3 ʧ��
VIDEO_NET_API int CALL_METHOD VideoNet_GetUpgradeState(JVT_LONG lUpgradeHandle);
VIDEO_NET_API long CALL_METHOD VideoNet_CloseUpgradeHandle(JVT_LONG lUpgradeHandle);


//��̨���ƣ�Ĭ���ǿ�����̨���ٶ�4���û�Ҳ�������������ٶ�
VIDEO_NET_API bool CALL_METHOD VideoNet_PTZControl(JVT_LONG lLoginID,int nChannelNo, long lPTZCommand, bool bStop = false, long lSpeed = 4);

//��չ��̨���ƣ�����Ԥ�õ����ã�Ѳ��·�ߣ����ٶ�λ�ȵ�
VIDEO_NET_API bool CALL_METHOD VideoNet_PTZControlEx(JVT_LONG lLoginID,int nChannelNo, long lPTZCommand, 
									long lParam1, long lParam2, long lParam3, bool bStop = false);

//�豸���ƣ�����ֵ true �ɹ��� false ʧ��
/*
	==
*/
VIDEO_NET_API bool CALL_METHOD VideoNet_ControlDVR(JVT_LONG lLoginID, int type, int waittime = 2000);
	

//�����������ڵ��豸
VIDEO_NET_API bool CALL_METHOD VideoNet_SearchDevice(char* szBuf, int nBufLen, int* pRetLen, int nSearchTime);


//�����Խ����������ݴ����ӿ�
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartVoiceCom_MR(JVT_LONG lLoginID, pfAudioDataCallBack pVcb, JVT_DWORD dwDataUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_VoiceComSendData(JVT_LONG lVoiceHandle, char *pSendBuf, long lBufSize);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopVoiceCom(JVT_LONG lVoiceHandle);

//���öԽ���Ƶ���뷽ʽ���û����Բ����ã�Ĭ��ΪG711A����
VIDEO_NET_API bool CALL_METHOD VideoNet_SetTalkMode(JVT_LONG lLoginID, SDK_AudioInFormatConfig* pTalkMode);

// lRecordType¼��ģʽ, ��SDK_RecordModeTypes
VIDEO_NET_API bool CALL_METHOD VideoNet_StartDVRRecord(JVT_LONG lLoginID, int nChannelNo ,long lRecordType);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopDVRRecord(JVT_LONG lLoginID, int nChannelNo);

VIDEO_NET_API bool CALL_METHOD VideoNet_SetSystemDateTime(JVT_LONG lLoginID, SDK_SYSTEM_TIME *pSysTime);
VIDEO_NET_API bool CALL_METHOD VideoNet_GetDVRWorkState(JVT_LONG lLoginID, SDK_DVR_WORKSTATE *pWorkState);

VIDEO_NET_API bool CALL_METHOD VideoNet_ClickKey(JVT_LONG lLoginID, SDK_NetKeyBoardData *pKeyBoardData);

// ���̹���
VIDEO_NET_API int CALL_METHOD VideoNet_StorageManage(JVT_LONG lLoginID, SDK_StorageDeviceControl *pStorageCtl);

VIDEO_NET_API bool CALL_METHOD VideoNet_SendNetAlarmMsg(JVT_LONG lLoginID, SDK_NetAlarmInfo *pAlarmInfo);

// ץͼ
VIDEO_NET_API bool CALL_METHOD VideoNet_CatchPic(JVT_LONG lLoginID, int nChannel, char *sFileName);
VIDEO_NET_API bool CALL_METHOD VideoNet_CatchPicInBuffer(JVT_LONG lLoginID, int nChannel, char *pBuffer, int nBufLen, int *pPicLen);

VIDEO_NET_API bool CALL_METHOD VideoNet_StartAlarmCenterListen(int nPort, fMessCallBack cbAlarmCenter, JVT_DWORD dwDataUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopAlarmCenterListen();

//͸��232,485
VIDEO_NET_API bool CALL_METHOD VideoNet_SerialWrite(JVT_LONG lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen);
VIDEO_NET_API bool CALL_METHOD VideoNet_SerialRead(JVT_LONG lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen, int *pReadLen);

VIDEO_NET_API int CALL_METHOD VideoNet_GetDDNSInfo(SearchMode &searchmode, DDNS_INFO *pDevicInfo, int maxDeviceNum, int &nretNum);

//nStream: 0��ʾ��������Ϊ1��ʾ������
VIDEO_NET_API bool CALL_METHOD VideoNet_MakeKeyFrame(JVT_LONG lLoginID, int nChannel, int nStream);

//nStream: 0��ʾ��������Ϊ1��ʾ������
VIDEO_NET_API bool CALL_METHOD VideoNet_GetOEMInfo(JVT_LONG lLoginID, SDK_OEMInfo *pOEMInfo);
// ����͸������ͨ��
VIDEO_NET_API bool CALL_METHOD VideoNet_OpenTransComChannel(JVT_LONG lLoginID, TransComChannel *TransInfo, fTransComCallBack cbTransCom, JVT_DWORD lUser);
//�ر�͸������ͨ��
VIDEO_NET_API bool CALL_METHOD VideoNet_CloseTransComChannel(JVT_LONG lLoginID, SERIAL_TYPE nType);
//��ȡ״̬��Ϣ
VIDEO_NET_API bool CALL_METHOD VideoNet_GetDeviceState(JVT_LONG lLoginID, SDK_State_Type type, char *pState);
//��ȡuiͼƬ:type 1:ΪȫͼƬ 2:�����ͼƬ
VIDEO_NET_API bool CALL_METHOD VideoNet_CatchPicUI(JVT_LONG lLoginID,char *saveFileName,int type = 1);
//���ñ���ip
VIDEO_NET_API bool CALL_METHOD VideoNet_SetLocalBindAddress(char*szIP);

//�ϱ�����
VIDEO_NET_API bool CALL_METHOD VideoNet_StartUploadData(JVT_LONG lLoginID,UploadDataType upLoadType,fUploadDataCallBack callBack, JVT_DWORD nUser);

VIDEO_NET_API bool CALL_METHOD VideoNet_StopUploadData(JVT_LONG lLoginID,UploadDataType upLoadType);
//����ע��
VIDEO_NET_API bool CALL_METHOD VideoNet_StartActiveRigister(int nPort, fMessCallBack cbFunc, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopActiveRigister();

//�������쳣�Ͽ�
VIDEO_NET_API long CALL_METHOD VideoNet_SetSubDisconnectCallBack(fSubDisConnectCallBack callBack, JVT_DWORD nUser);

//���ñ���ʱ��
VIDEO_NET_API long CALL_METHOD VideoNet_SetKeepLifeTime(JVT_LONG lLoginID,unsigned int perKeeplifeTime,unsigned int detectDisconTime);

//MAC �õ�����
VIDEO_NET_API bool CALL_METHOD VideoNet_CheckEncrypt(char *pMac);

//�豸���������豸�����豸��ͬһ�����������豸
VIDEO_NET_API bool CALL_METHOD VideoNet_SearchDeviceEX(JVT_LONG lLoginID,SDK_NetDevList *pDevlist,SDK_TransferProtocol_V2 transferProtocol = SDK_TRANSFER_PROTOCOL_NETIP,int waittime = 15000);

//��̨���ٶ�λ
//ʹ��ǰ �ж��Ƿ�֧��
VIDEO_NET_API bool CALL_METHOD VideoNet_PTZPostion(JVT_LONG lLoginID,int nChannel,SDK_PositionPoint *pPositionPoint);

///< NVR�������ӵ�ǰ�˶Խ�
VIDEO_NET_API bool CALL_METHOD VideoNet_StartDevTalk(JVT_LONG lLoginID,int nChannel,int waittime = 2000);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopDevTalk(JVT_LONG lLoginID,int nChannel,int waittime = 2000);
///<Ӳ��¼����Ϣ
//¼���ѯ
//lLoginID		��½���
//lpFindInfo	��ѯ����
//lpFileData	���ҵ���¼�����ݣ��ⲿ���ڴ�
//waittime		��ѯ��ʱʱ��
VIDEO_NET_API long CALL_METHOD VideoNet_RecordInfo(JVT_LONG lLoginID, SDK_SearchByTime* lpFindInfo, SDK_RecordStorageInfo *lpRecordData, int waittime = 15000);

VIDEO_NET_API bool CALL_METHOD VideoNet_ControlFile(JVT_LONG lLoginID,SDK_NetFileControl *lpFileControl,int waittime = 15000);

//¼���豸�����ж�����Ƶ�ļ������8��
//lLoginID		��½���
//lpFindInfo	��ѯ����
//lpFileData	���ҵ�����Ƶ���ݣ��ⲿ���ڴ�
//waittime		��ѯ��ʱʱ��
VIDEO_NET_API bool CALL_METHOD VideoNet_FindAudioFile(JVT_LONG lLoginID, SDK_MusicFileList* lpFileList, int waittime = 5000);

/*
	==������Ƶ�ļ���Ҫ�ļ����������Ĳ���Ҫ��ACTIONһ��Ҫ��ֵ
	== Action  �ο� SDK_Music_Play_Action
*/
VIDEO_NET_API bool CALL_METHOD VideoNet_ControlAudio(JVT_LONG lLoginID, SDK_LocalMusicControl *lpMusicControl, int waittime = 2000);



//����ͼƬ
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceImageFile(JVT_LONG lLoginID,int nChannel);
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceImageFileEx(JVT_LONG lLoginID,int nChannel, int nEnable);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopReceiveFaceImageFile(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetFaceImageDataCallBack(JVT_LONG lSubHandle,fFaceImageDataCallBack cbFacePictureData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteFaceImageDataCallBack(JVT_LONG lSubHandle,fFaceImageDataCallBack cbFacePictureData, JVT_DWORD nUser);

//�ȶԽ��
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceCompareResult(JVT_LONG lLoginID,int nChannel); 
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceCompareResultEx(JVT_LONG lLoginID,int nChannel, SDK_COMPINFO_FLAG *pstCompinfoFlag); 
VIDEO_NET_API bool CALL_METHOD VideoNet_StopReceiveFaceCompareResult(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetFaceCompareResultCallBack(JVT_LONG lSubHandle,fFaceCompaeResultCallBack cbFaceCompareResult, JVT_DWORD dwUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteFaceCompareResultCallBack(JVT_LONG lSubHandle,fFaceCompaeResultCallBack cbFaceCompareResult, JVT_DWORD nUser);

//�ڰ�����
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartSendBlackAndWhiteList(JVT_LONG lLoginID,int nChannel);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopSendBlackAndWhiteList(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetBlackAndWhiteListCallBack(JVT_LONG lSubHandle,fFaceBlackAndWhiteListCallBack cbFaceBlackAndWhiteListData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteBlackAndWhiteListCallBack(JVT_LONG lSubHandle,fFaceBlackAndWhiteListCallBack cbFaceBlackAndWhiteListData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_OperationBlackAndWhiteListData(JVT_LONG lSubHandle,WBLIST_ACTION_TYPE ActionType,int nWBType,int nlibraryIndex,int nFileIndex,char *pFile,/* ������ */int nSex = 0);
VIDEO_NET_API bool CALL_METHOD VideoNet_OperationBlackAndWhiteListDataEx(JVT_LONG lSubHandle,WBLIST_ACTION_TYPE ActionType,SDK_FA_BLACKANDWHITELIST_CONFIG WBListConfig,SDK_XM_WB_CONFIG_EXDATA ConfigData, char *pFile);

//����ʶ��ͼƬ
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveCarLicensePlateImageFile(JVT_LONG lLoginID,int nChannel);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopReceiveCarLicensePlateImageFile(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetCarLicensePlateImageDataCallBack(JVT_LONG lSubHandle,fCarLicensePlateImageDateCallBack cbFacePictureData, void* nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteCarLicensePlateImageDataCallBack(JVT_LONG lSubHandle,fCarLicensePlateImageDateCallBack cbFacePictureData, void* nUser);

//P2P��¼
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_Login_P2P(char* pchDVRIP, unsigned short wDVRPort, 
				   char *pchUserName, char *pchPassword, VIDEONET_DEVICEINFO* lpDeviceInfo, int *error,int socketType = 0);
VIDEO_NET_API long CALL_METHOD VideoNet_SendForHttp_P2P(char *puuid, char *pDataBuf, int iDataLen);
VIDEO_NET_API long CALL_METHOD VideoNet_RecvForHttp_P2P(char *puuid, char **pDataBuf, int *iBufSize,int timeout);

//ͼƬ��ѯ
//lLoginID		��½���
//lpFindInfo	��ѯ����
//lpFileData	���ҵ���ͼƬ���ݣ��ⲿ���ڴ�
//lMaxCount		���ͼƬ��Ŀ
//findcount		���ҵ���ͼƬ��Ŀ
//waittime		��ѯ��ʱʱ��
VIDEO_NET_API long CALL_METHOD VideoNet_FindPicture(JVT_LONG lLoginID, SDK_PICTURE_FINDINFO* lpFindInfo, SDK_VIDEONET_PICTURE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime = 5000);

//ͼƬ����, �Լ�ͨ��VideoNet_GetDownloadPos��ȡ����
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_GetPicture(JVT_LONG lLoginID, SDK_VIDEONET_PICTURE_DATA *sPictureFile,char *sSavedFileName, JVT_DWORD dwDataUser = NULL);
/*
	����:GPIO����
	����:
	lLoginID[in]:		 ��½���
	����ֵ:
	=0:�ɹ�
	<0:ʧ��
*/
VIDEO_NET_API long CALL_METHOD VideoNet_GPIOControl(JVT_LONG lLoginID, int iSecond);

//ͨ��ͼƬ��ѯͼƬ����¼��   ����ֵ:  1�ɹ�   0ʧ��
VIDEO_NET_API long CALL_METHOD VideoNet_Query_Photo_Record(JVT_LONG lLoginID, PICTURE_FINDINFO* lpFindInfo, VIDEONET_PICTURE_DATA *lpFileData, int lMaxCount,int waittime = 5000);

//���������
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartListManagement(JVT_LONG lLoginID,int nChannel);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetListManagementCallBack(JVT_LONG lSubHandle, fListManagementCallBack cbListManagementData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteListManagementCallBack(JVT_LONG lSubHandle, fListManagementCallBack cbListManagementData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopListManagement(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_ListManagementData(JVT_LONG lSubHandle, char* lpBuffer, unsigned long dwBufferSize, char *pFile);
//ͼƬ����
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceMonitor(JVT_LONG lLoginID,int nChannel, SDK_FACEMONITOR_INFO_FLAG *pstCompinfoFlag); 
VIDEO_NET_API bool CALL_METHOD VideoNet_StopReceiveFaceMonitor(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetFaceMonitorCallBack(JVT_LONG lSubHandle,fFaceMonitorCallBack cbFaceMonitor, JVT_DWORD dwUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteFaceMonitorCallBack(JVT_LONG lSubHandle,fFaceMonitorCallBack cbFaceMonitor, JVT_DWORD nUser);

#endif
