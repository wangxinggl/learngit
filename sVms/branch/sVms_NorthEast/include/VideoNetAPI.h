#ifndef NETMODULE_H
#define NETMODULE_H

#ifdef WIN32

#ifdef NETMODULE_EXPORTS

#define VIDEO_NET_API  extern "C" __declspec(dllexport)
#else
#define VIDEO_NET_API  extern "C" __declspec(dllimport)   //VC 用
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
	VIDEONET_NOERROR				= 0,				//没有错误
	VIDEONET_SUCCESS				= 1,				//返回成功
	VIDEONET_SDK_NOTVALID			= -10000,			//非法请求
	VIDEONET_NO_INIT				= -10001,			//SDK未经初始化
	VIDEONET_ILLEGAL_PARAM			= -10002,			//用户参数不合法
	VIDEONET_INVALID_HANDLE			= -10003,			//句柄无效
	VIDEONET_SDK_UNINIT_ERROR		= -10004,			//SDK清理出错
	VIDEONET_SDK_TIMEOUT			= -10005,			//等待超时
	VIDEONET_SDK_MEMORY_ERROR		= -10006,			//内存错误，创建内存失败
	VIDEONET_SDK_NET_ERROR			= -10007,			//网络错误
	VIDEONET_SDK_OPEN_FILE_ERROR	= -10008,			//打开文件失败
	VIDEONET_SDK_UNKNOWNERROR		= -10009,			//未知错误
	VIDEONET_DEV_VER_NOMATCH		= -11000,			//收到数据不正确，可能版本不匹配
	VIDEONET_SDK_NOTSUPPORT			= -11001,			//版本不支持
	VIDEONET_SDK_FILE_FORAMAT_ERROR			= -11002,	//人脸图片文件格式不对
	VIDEONET_SDK_ADDP2PPORT_FAIL	= -11003,			//查找P2P端口失败
	VIDEONET_SDK_FILE_DATA_LARGE_ERROR	= -11004,		//文件数据过大
	VIDEONET_SDK_CONNECT_P2PSERVER_FAIL = -11005,		//连接华科服务器失败

	VIDEONET_OPEN_CHANNEL_ERROR		= -11200,			//打开通道失败
	VIDEONET_CLOSE_CHANNEL_ERROR	= -11201,			//关闭通道失败
	VIDEONET_SUB_CONNECT_ERROR		= -11202,			//建立媒体子连接失败
	VIDEONET_SUB_CONNECT_SEND_ERROR	= -11203,			//媒体子连接通讯失败
	VIDEONET_NATCONNET_REACHED_MAX  = -11204,           //Nat视频链接达到最大，不允许新的Nat视频链接 

	

	/// 用户管理部分错误码
	VIDEONET_NOPOWER					= -11300,			//无权限
	VIDEONET_PASSWORD_NOT_VALID			= -11301,			// 账号密码不对
	VIDEONET_LOGIN_USER_NOEXIST			= -11302,			//用户不存在
	VIDEONET_USER_LOCKED				= -11303,			// 该用户被锁定
	VIDEONET_USER_IN_BLACKLIST			= -11304,			// 该用户不允许访问(在黑名单中)
	VIDEONET_USER_HAS_USED				= -11305,			// 该用户以登陆
	VIDEONET_USER_NOT_LOGIN				= -11306,			// 该用户没有登陆
	VIDEONET_CONNECT_DEVICE_ERROR		= -11307,			//可能设备不存在
	VIDEONET_ACCOUNT_INPUT_NOT_VALID	= -11308,			//用户管理输入不合法
	VIDEONET_ACCOUNT_OVERLAP			= -11309,			//索引重复
	VIDEONET_ACCOUNT_OBJECT_NONE		= -11310,			//不存在对象, 用于查询时
	VIDEONET_ACCOUNT_OBJECT_NOT_VALID	= -11311,			//不存在对象
	VIDEONET_ACCOUNT_OBJECT_IN_USE		= -11312,			//对象正在使用
	VIDEONET_ACCOUNT_SUBSET_OVERLAP		= -11313,			//子集超范围 (如组的权限超过权限表，用户权限超出组的权限范围等等)
	VIDEONET_ACCOUNT_PWD_NOT_VALID		= -11314,			//密码不正确
	VIDEONET_ACCOUNT_PWD_NOT_MATCH		= -11315,			//密码不匹配
	VIDEONET_ACCOUNT_RESERVED			= -11316,			//保留帐号


	/// 配置管理相关错误码
	
	VIDEONET_OPT_RESTART			= -11400,			// 保存配置后需要重启应用程序
	VIDEONET_OPT_REBOOT				= -11401,			// 需要重启系统
	VIDEONET_OPT_FILE_ERROR			= -11402,			// 写文件出错
	VIDEONET_OPT_CAPS_ERROR			= -11403,			// 配置特性不支持
	VIDEONET_OPT_VALIDATE_ERROR		= -11404,			// 配置校验失败
	VIDEONET_OPT_CONFIG_NOT_EXIST	= -11405,			// 请求或者设置的配置不存在
	
	/// 

	VIDEONET_CTRL_PAUSE_ERROR		= -11500,			//暂停失败
	VIDEONET_SDK_NOTFOUND			= -11501,			//查找失败，没有找到对应文件
	VIDEONET_CFG_NOT_ENABLE         = -11502,           //配置未启用

	VIDEONET_DECORD_FAIL            = -11503,           //解码失败

	//DNS协议解析返回错误码
	VIDEONET_SOCKET_ERROR             = -11600,         //创建套节字失败
	VIDEONET_SOCKET_CONNECT           = -11601,         //连接套节字失败
	VIDEONET_SOCKET_DOMAIN            = -11602,         //域名解析失败
	VIDEONET_SOCKET_SEND              = -11603,         //发送数据失败
	VIDEONET_ARSP_NO_DEVICE           = -11604,         //没有获取到设备信息，设备应该不在线
	VIDEONET_ARSP_BUSING              = -11605,         //ARSP服务繁忙
	VIDEONET_ARSP_BUSING_SELECT       = -11606,         //ARSP服务繁忙,select失败
	VIDEONET_ARSP_BUSING_RECVICE	  = -11607,         //ARSP服务繁忙,recvice失败
	VIDEONET_CONNECTSERVER_ERROR      = -11608,        //连接服务器失败

	//
	VIDEONET_CONNECT_FULL      = -11612,              //服务器连接数已满


	//版权相关
	VIDEONET_PIRATESOFTWARE           =-11700,       //设备盗版

};


//云台操作类型
enum PTZ_ControlType
{
	PTZ_TILT_UP = 0,			//上
	PTZ_TILT_DOWN,				//下
	PTZ_PAN_LEFT,				//左
	PTZ_PAN_RIGHT,				//右
	PTZ_PAN_LEFTTOP,			//左上
	PTZ_PAN_LEFTDOWN,			//左下
	PTZ_PAN_RIGTHTOP,			//右上
	PTZ_PAN_RIGTHDOWN,			//右下
	PTZ_ZOOM_OUT,				//变倍小
	PTZ_ZOOM_IN,				//变倍大
	PTZ_FOCUS_FAR,				//焦点后调
	PTZ_FOCUS_NEAR,				//焦点前调
	PTZ_IRIS_OPEN,				//光圈扩大
	PTZ_IRIS_CLOSE,				//光圈缩小13

	EXTPTZ_OPERATION_ALARM,			///< 报警功能 
	EXTPTZ_LAMP_ON,					///< 灯光开
	EXTPTZ_LAMP_OFF,				//灯光关
	EXTPTZ_POINT_SET_CONTROL,			//设置预置点 
	EXTPTZ_POINT_DEL_CONTROL,			//清除预置点 
	EXTPTZ_POINT_MOVE_CONTROL,			//转预置点
	EXTPTZ_STARTPANCRUISE,			//开始水平旋转		20	
	EXTPTZ_STOPPANCRUISE,			//停止水平旋转	
	EXTPTZ_SETLEFTBORDER,			//设置左边界		
	EXTPTZ_SETRIGHTBORDER,			//设置右边界	
	EXTPTZ_STARTLINESCAN,			//自动扫描开始 
	EXTPTZ_CLOSELINESCAN,			//自动扫描开停止 
	EXTPTZ_ADDTOLOOP,				//加入预置点到巡航	p1巡航线路	p2预置点值	
	EXTPTZ_DELFROMLOOP,				//删除巡航中预置点	p1巡航线路	p2预置点值	
	EXTPTZ_POINT_LOOP_CONTROL,			//开始巡航 28
	EXTPTZ_POINT_STOP_LOOP_CONTROL,	//停止巡航
	EXTPTZ_CLOSELOOP,				//清除巡航	p1巡航线路		
	EXTPTZ_FASTGOTO,				//快速定位	
	EXTPTZ_AUXIOPEN,				//辅助开关，关闭在子命令中//param1 参见SDK_PtzAuxStatus，param2传入具体数值
	EXTPTZ_OPERATION_MENU,				//球机菜单操作，其中包括开，关，确定等等
	EXTPTZ_REVERSECOMM,				//镜头翻转
	EXTPTZ_OPERATION_RESET,			///< 云台复位
	EXTPTZ_PATTERN,					///< 设置模式开始

	EXTPTZ_BRUSH_ON,				//雨刷开	37
	EXTPTZ_BRUSH_OFF,				//雨刷关

	EXTPTZ_TOTAL,
};
/// 云台辅助功能
enum SDK_PtzAuxStatus
{
	EXTPTZ_AUX_ON,		///< 开
	EXTPTZ_AUX_OFF,	///< 关
	EXTPTZ_AUX_NR,		
};

#define PTZ_PAN_AUTO		29	/* 云台以SS的速度左右自动扫描 */
//#define EXTPTZ_FASTGOTO	30	//三维定位


#define NET_MAX_CHANNUM 			32			//最大通道个数
#define NET_DECORDR_CH              32          //最大解码通道个数
#define NET_MAX_USER_NUM			60			//最多用户数
#define NET_MAX_RIGTH_NUM			128			//最多权限数
#define NET_MAX_GROUP_NUM			50			//最多组数
#define NET_MAX_USER_LENGTH			32			//用户名密码最大长度
#define NET_MAX_COMBINE_NUM			2			//最大组合编码通道数
#define NET_MAX_DECORDR_CH          32          //最大解码通道个数	

#define NET_MAX_DDNS_TYPE			5			//支持的DDNS种类
#define NET_MAX_ARSP_TYPE			5
#define NET_MAX_ALARMSERVER_TYPE    5           //支持报警中心种类
#define NET_MAX_SYSFUNC				20			//最多系统功能个数
#define NET_MAX_PTZ_PROTOCOL_LENGTH 32			//云台协议名称最大长度
#define NET_N_WEEKS					7			//星期数
#define	NET_N_TSECT					6			//时间段数
#define NET_MD_REGION_ROW			32			//动态检测区域行数
#define NET_COVERNUM				8			 //覆盖区域数
#define NET_MAX_FILTERIP_NUM		64			//IP地址最大过滤数
#define NET_NAME_PASSWORD_LEN		64			//用户名密码最大长度
#define NET_MAX_PATH_LENGTH	        260			//路径长度
#define NET_N_MIN_TSECT				2
#define NET_MAX_RETURNED_LOGLIST	128			//最多日志条数
#define NET_MAX_MAC_LEN             32          //MAC地址字符最大长度
#define NET_IW_ENCODING_TOKEN_MAX   128
#define NET_MAX_AP_NUMBER           32          //SID最大数量，暂定10
#define NET_MAX_INFO_LEN		    128
#define NET_MAX_USERNAME_LENGTH		128
#define NET_MAX_SERIALNO_LENGTH		128          //最大解码通道个数
#define NET_CHANNEL_NAME_MAX_LEN   64		///< 通道名称最大长度
#define NET_MAX_LINE_PER_OSD_AREA   6      ///<编码中一个OSD区域最多可以显示的字符行数
#define NET_NAME_URL_LEN            128    //URL   

//DDNS参数
#define DDNS_MAX_DDNS_NAMELEN 64  //主机名长度
#define DDNS_MAX_DDNS_PWDLEN 32   //密码长度
#define DDNS_MAX_DDNS_IPSIZE 64   //IP地址长度
#define DDNS_MAX_DDNS_IDSIZE 32   //设备标识长度
#define DDNS_MAX_SERIALINFO_SIZE 16 //序列号以及用户名长度



//摄象机参数
#define CAMERAPARA_MAXNUM  16    //曝光能力中目前最大长度
//短信最大数量
#define SDK_MAX_RECIVE_MSG_PHONE_COUNT 3	///<最大发生短信数量

//VGA分辨率
#define VGA_MAXNUM     32       //分辨率 种类
#define VGA_NAME_LENGTH 10		//分辨率 长度	

//显示的设备列表(设备端搜索)
#define DEV_LIST_SHOW  256

//IP SIZE
#define IP_SIZE  16
//#define  MAX_HVR_CHNCAP       16
//DDNS服务器设备的信息

#define  NET_NAME_TOKEN_LEN 128

typedef struct _DDNS_INFO
{
	char ID[64];    //设备标识
	char Alias[DDNS_MAX_DDNS_NAMELEN];
	char IP[DDNS_MAX_DDNS_IPSIZE];   //外网IP
	char LanIP[DDNS_MAX_DDNS_IPSIZE];//内网IP
	int WebPort; //Web端口,默认为80
	int MediaPort; //媒体端口,默认为34567
	int MobilePort;  //手机监控端口，默认为34599
	int UPNPWebPort;  //UPNP启动下Web端口,UPNP不开启为0
	int UPNPMediaPort; //UPNP启动下媒体端口,UPNP不开启为0
	int UPNPMobilePort; //UPNP启动下手机监控端口,UPNP不开启为0
	int ChannelNum; //通道数
	int Status; //状态
	char Username[DDNS_MAX_DDNS_NAMELEN]; //用户名
	char Password[DDNS_MAX_DDNS_PWDLEN]; //密码
}DDNS_INFO,*pDDNS_INFO;

//DDNS信息查询模式
typedef struct _SearchMode
{
	int  nType;        //查询类型，见SearchModeType
	char szSerIP[DDNS_MAX_DDNS_IPSIZE];//服务器地址
	int nSerPort;           //服务器端口号
	char szSerialInfo[DDNS_MAX_SERIALINFO_SIZE];  //如果是按序列号，则为序列号，如果是用户名，则为用户名
	char szPassWord[DDNS_MAX_DDNS_PWDLEN]; //按用户名登陆时候的密码

}SearchMode;

//DDNS信息查询类型
enum SearchModeType
{
	DDNS_SERIAL = 0,//按序列号
	DDNS_USERNAME,  //按用户名
};
//实时预览扩展接口增加的参数：预览类型
typedef enum _VideoNet_RealPlayType
{
	NET_RType_Realplay = 0,	//实时预览
	NET_RType_Main_Realplay2,	//实时监视-主码流，等同于NET_RType_Realplay
	NET_RType_Main_Realplay3,
	NET_RType_Sub_Realplay_1,	//实时监视-从码流1
	NET_RType_Sub_Realplay_2,	//实时监视-从码流2
	NET_RType_Sub_Realplay_3,	//实时监视-从码流3

	NET_RType_Multiplay_1,	//多画面预览－1画面
	NET_RType_Multiplay_4,	//多画面预览－4画面
	NET_RType_Multiplay_6,	//多画面预览－6画面
	NET_RType_Multiplay_8,	//多画面预览－8画面
	NET_RType_Multiplay_9,	//多画面预览－9画面
	NET_RType_Multiplay_12,	//多画面预览－12画面
	NET_RType_Multiplay_16,	//多画面预览－16画面
} NET_RealPlayType;

/// 组合编码模式
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

//这些结构体和枚举是提供给外部使用，所有可能会和设备那边定义了2次,所以都在前面加了SDK_
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
	SDK_CAPTURE_SIZE_EXT_NR =19,    ///< 枚举的图形大小种类的数目。
	SDK_CAPTURE_SIZE_1080N = 19,     ///< 960*1080
	SDK_CAPTURE_SIZE_4M,        ///< 2592*1520
	SDK_CAPTURE_SIZE_6M,		///< 3072×2048
	SDK_CAPTURE_SIZE_8M,		///< 3264×2448
	SDK_CAPTURE_SIZE_12M,		///< 4000*3000
	SDK_CAPTURE_SIZE_4K,		///< 4096 * 2160通用/3840*2160海思
	SDK_CAPTURE_SIZE_EXT_V2_NR=25,    ///< 枚举的图形大小种类的数目。
	SDK_CAPTURE_SIZE_720N = 25,  //  640*720
	SDK_CAPTURE_SIZE_WSVGA,      ///< 1024*576
	SDK_CAPTURE_SIZE_RES2,       // 0*0
	SDK_CAPTURE_SIZE_RES3,       // 0*0
	SDK_CAPTURE_SIZE_RES4,       // 0*0
	SDK_CAPTURE_SIZE_RES5,       // 0*0
	SDK_CAPTURE_SIZE_RES6,       // 0*0
	SDK_CAPTURE_SIZE_NR,
};

/// 捕获码流控制模式类型
enum SDK_capture_brc_t {
	SDK_CAPTURE_BRC_CBR,			///< 固定码流。
	SDK_CAPTURE_BRC_VBR,			///< 可变码流。
	SDK_CAPTURE_BRC_MBR,			///< 混合码流。
	SDK_CAPTURE_BRC_NR				///< 枚举的码流控制模式数目。
};

/// 捕获压缩格式类型
enum SDK_CAPTURE_COMP_t {
	SDK_CAPTURE_COMP_DIVX_MPEG4,	///< DIVX MPEG4。
	SDK_CAPTURE_COMP_MS_MPEG4,		///< MS MPEG4。
	SDK_CAPTURE_COMP_MPEG2,			///< MPEG2。
	SDK_CAPTURE_COMP_MPEG1,			///< MPEG1。
	SDK_CAPTURE_COMP_H263,			///< H.263
	SDK_CAPTURE_COMP_MJPG,			///< MJPG
	SDK_CAPTURE_COMP_FCC_MPEG4,		///< FCC MPEG4
	SDK_CAPTURE_COMP_H264,			///< H.264
	SDK_CAPTURE_COMP_H265,
	SDK_CAPTURE_COMPRESS_H265_S,		///< H.265+  //add by barney 2017/08/28
	SDK_CAPTURE_COMP_NR				///< 枚举的压缩标准数目。
};

/// 捕获通道类型
enum SDK_CAPTURE_CHANNEL_t {
	SDK_CHL_MAIN_T = 0,		///< 主通道	－	主码流1 
	SDK_CHL_2END_T = 1,		///< 辅通道	－	出辅码流2 
	SDK_CHL_3IRD_T = 2,		///< 辅通道	－	出辅码流3 
	SDK_CHL_4RTH_T = 3,		///< 辅通道	－	出辅码流4 
	SDK_CHL_JPEG_T = 4,		///< 辅通道	－	出JPEG抓图 
	SDK_CHL_FUNCTION_NUM
};
/// 音频编码类型
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
	E_SDK_CONFIG_USER,					//用户信息，包含了权限列表，用户列表和组列表	对应结构体USER_MANAGE_INFO
	E_SDK_CONFIG_ADD_USER,				//增加用户										对应结构体USER_INFO
	E_SDK_CONFIG_MODIFY_USER,			//修改用户										对应结构体CONF_MODIFYUSER
	E_SDK_CONFIG_DELETE_USER,			//删除用户										对应结构体USER_INFO
	E_SDK_CONFIG_ADD_GROUP,				//增加组										对应结构体USER_GROUP_INFO
	E_SDK_CONFIG_MODIFY_GROUP,			//修改组										对应结构体CONF_MODIFYGROUP
	E_SDK_COFIG_DELETE_GROUP,			//删除组										对应结构体USER_GROUP_INFO
	E_SDK_CONFIG_MODIFY_PSW,			//修改密码										对应结构体_CONF_MODIFY_PSW

	E_SDK_CONFIG_ABILITY_SYSFUNC = 9,	//支持的网络功能								对应结构体SDK_SystemFunction
	E_SDK_CONFIG_ABILTY_ENCODE,			//首先获得编码能力								对应结构体CONFIG_EncodeAbility
	E_SDK_CONFIG_ABILITY_PTZPRO,		//云台协议										对应结构体SDK_PTZPROTOCOLFUNC
	E_SDK_COMFIG_ABILITY_COMMPRO,		//串口协议										对应结构体SDK_COMMFUNC

	E_SDK_CONFIG_ABILITY_MOTION_FUNC,	//动态检测块									对应结构体SDK_MotionDetectFunction
	E_SDK_CONFIG_ABILITY_BLIND_FUNC,	//视频遮挡块									对应结构体SDK_BlindDetectFunction
	E_SDK_CONFIG_ABILITY_DDNS_SERVER,	//DDNS服务支持类型								对应结构体SDK_DDNSServiceFunction
	E_SDK_CONFIG_ABILITY_TALK,			//对讲编码类型									对应结构体SDK_DDNSServiceFunction


	E_SDK_CONFIG_SYSINFO = 17,			//系统信息										对应结构体VideoNet_DEVICEINFO
	E_SDK_CONFIG_SYSNORMAL,				//普通配置										对应结构体SDK_CONFIG_NORMAL
	E_SDK_CONFIG_SYSENCODE,				//编码配置										对应结构体SDK_EncodeConfigAll_SIMPLIIFY
	E_SDK_CONFIG_SYSNET,				//网络设置										对应结构体SDK_CONFIG_NET_COMMON
	E_SDK_CONFIG_PTZ,					//云台页面										对应结构体SDK_STR_PTZCONFIG_ALL
	E_SDK_CONFIG_COMM,					//串口页面										对应结构体SDK_CommConfigAll
	E_SDK_CONFIG_RECORD,				//录像设置界面									对应结构体SDK_RECORDCONFIG
	E_SDK_CONFIG_MOTION,				//动态检测页面									对应结构体SDK_MOTIONCONFIG
	E_SDK_CONFIG_SHELTER,				//视频遮挡										对应结构体SDK_BLINDDETECTCONFIG
	E_SDK_CONFIG_VIDEO_LOSS,			//视频丢失,										对应结构体SDK_VIDEOLOSSCONFIG
	E_SDK_CONFIG_ALARM_IN,				//报警输入										对应结构体SDK_ALARM_INPUTCONFIG
	E_SDK_CONFIG_ALARM_OUT,				//报警输出										对应结构体SDK_AlarmOutConfigAll
	E_SDK_CONFIG_DISK_MANAGER,			//硬盘管理界面									对应结构体SDK_StorageDeviceControl
	E_SDK_CONFIG_OUT_MODE,				//输出模式界面    								对应结构体SDK_VideoWidgetConfi
	E_SDK_CONFIG_CHANNEL_NAME,			//通道名称										对应结构体SDK_ChannelNameConfigAll
	E_SDK_CONFIG_AUTO,					//自动维护界面配置								对应结构体SDK_AutoMaintainConfig
	E_SDK_CONFIG_DEFAULT,				//恢复默认界面配置								对应结构体SDK_SetDefaultConfigTypes
	E_SDK_CONFIG_DISK_INFO,				//硬盘信息										对应结构体SDK_StorageDeviceInformationAll
	E_SDK_CONFIG_LOG_INFO,				//查询日志										对应结构体SDK_LogList
	E_SDK_CONFIG_NET_IPFILTER,			//黑名单配置									对应结构体SDK_NetIPFilterConfig
	E_SDK_CONFIG_NET_DHCP,				//DHC配置										对应结构体SDK_NetDHCPConfigAll
	E_SDK_CONFIG_NET_DDNS,				//DDNS信息										对应结构体SDK_NetDDNSConfigALL
	E_SDK_CONFIG_NET_EMAIL,				//EMAIL											对应结构体SDK_NetEmailConfig
	E_SDK_CONFIG_NET_MULTICAST,			//组播											对应结构体SDK_NetMultiCastConfig
	E_SDK_CONFIG_NET_NTP,				//NTP											对应结构体SDK_NetNTPConfig
	E_SDK_CONFIG_NET_PPPOE,				//PPPOE											对应结构体SDK_NetPPPoEConfig
	E_SDK_CONFIG_NET_DNS,				//DNS											对应结构体SDK_NetDNSConfig
	E_SDK_CONFIG_NET_FTPSERVER,			//FTP											对应结构体SDK_FtpServerConfig

	E_SDK_CONFIG_SYS_TIME,				//系统时间										对应结构体SDK_SYSTEM_TIME
	E_SDK_CONFIG_CLEAR_LOG,				//清除日志													
	E_SDK_REBOOT_DEV,					//重启启动设备													
	E_SDK_CONFIG_ABILITY_LANG,			//支持语言									    对应结构体SDK_MultiLangFunction
	E_SDK_CONFIG_VIDEO_FORMAT,																	
	E_SDK_CONFIG_COMBINEENCODE,			//组合编码										对应结构体SDK_CombineEncodeConfigAll
	E_SDK_CONFIG_EXPORT,				//配置导出														
	E_SDK_CONFIG_IMPORT,				//配置导入
	E_SDK_LOG_EXPORT,					//日志导出														
	E_SDK_CONFIG_COMBINEENCODEMODE,		//组合编码模式									对应结构体SDK_CombEncodeModeAll
	E_SDK_WORK_STATE,					//运行状态																
	E_SDK_ABILITY_LANGLIST,				//实际支持的语言集									
	E_SDK_CONFIG_NET_ARSP,				//ARSP											对应结构体SDK_NetARSPConfigAll
	E_SDK_CONFIG_SNAP_STORAGE,			//												对应结构体SDK_SnapshotConfig
	E_SDK_CONFIG_NET_3G,				//3G拨号										对应结构体SDK_Net3GConfig
	E_SDK_CONFIG_NET_MOBILE,			//手机监控										对应结构体SDK_NetMoblieConfig
	E_SDK_CONFIG_UPGRADEINFO,			//获取升级信息									参数 文件名
	E_SDK_CONFIG_NET_DECODER,
	E_SDK_ABILITY_VSTD,					//实际支持的视频制式
	E_SDK_CONFIG_ABILITY_VSTD,			//支持视频制式									对应结构体SDK_MultiVstd
	E_SDK_CONFIG_NET_UPNP,				//UPUN设置										对应结构体SDK_NetUPNPConfig
	E_SDK_CONFIG_NET_WIFI,				//WIFI											对应结构体SDK_NetWifiConfig
	E_SDK_CONFIG_NET_WIFI_AP_LIST,		//												对应结构体SDK_NetWifiDeviceAll
	E_SDK_CONFIG_SYSENCODE_SIMPLIIFY,	//简化的编码配置								对应结构体SDK_EncodeConfigAll_SIMPLIIFY
	E_SDK_CONFIG_ALARM_CENTER,			//告警中心										对应结构体SDK_NetAlarmServerConfigAll
	E_SDK_CONFIG_NET_ALARM,																			
	E_SDK_CONFIG_NET_MEGA,				//互信互通
	E_SDK_CONFIG_NET_XINGWANG,			//星望
	E_SDK_CONFIG_NET_SHISOU,			//视搜
	E_SDK_CONFIG_NET_VVEYE,				//VVEYE
	E_SDK_CONFIG_NET_PHONEMSG,			//短信											对应结构体SDK_NetShortMsgCfg
	E_SDK_CONFIG_NET_PHONEMEDIAMSG,		//彩信											对应结构体SDK_NetMultimediaMsgCfg
	E_SDK_VIDEO_PREVIEW,
	E_SDK_CONFIG_NET_DECODER_V2,
	E_SDK_CONFIG_NET_DECODER_V3,		//数字通道										对应结构体SDK_NetDigitChnConfig
	E_SDK_CONFIG_ABILITY_SERIALNO,		//序列号
	E_SDK_CONFIG_NET_RTSP,				//RTSP											对应结构体SDK_NetRTSPConfig
	E_SDK_GUISET,						//GUISET										对应结构体SDK_GUISetConfig
	E_SDK_CATCHPIC,						//抓图												
	E_SDK_VIDEOCOLOR,					//视频颜色设置
	E_SDK_CONFIG_COMM485,				//												对应结构体SDK_STR_RS485CONFIG_ALL
	E_SDK_COMFIG_ABILITY_COMMPRO485,	//串口485										对应结构体SDK_COMMFUNC
	E_SDK_CONFIG_SYS_TIME_NORTC,		//系统时间noRtc									对应结构体SDK_COMMFUNC
	E_SDK_CONFIG_REMOTECHANNEL,			//远程通道										对应结构体SDK_CONFIG_NET_COMMON
	E_SDK_CONFIG_OPENTRANSCOMCHANNEL ,	//打开透明串口									对应结构体TransComChannel
	E_SDK_CONFIG_CLOSETRANSCOMCHANNEL,  //关闭透明串口
	E_SDK_CONFIG_SERIALWIRTE,			//写入透明串口信息
	E_SDK_CONFIG_SERIALREAD,			//读取透明串口信息
	E_SDK_CONFIG_CHANNELTILE_DOT,		//点阵信息
	E_SDK_CONFIG_CAMERA,				//摄象机参数									对应结构体SDK_CameraParam
	E_SDK_CONFIG_ABILITY_CAMERA,		//曝光能力级									对应结构体SDK_CameraAbility
	E_SDK_CONFIG_BUGINFO,				//命令调试													
	E_SDK_CONFIG_STORAGENOTEXIST,		//硬盘不存在									对应结构体SDK_VIDEOLOSSCONFIG
	E_SDK_CONFIG_STORAGELOWSPACE,		//硬盘容量不足									对应结构体SDK_StorageLowSpaceConfig
	E_SDK_CONFIG_STORAGEFAILURE,		//硬盘出错										对应结构体SDK_VIDEOLOSSCONFIG
	E_SDK_CFG_NETIPCONFLICT,			//IP冲突										对应结构体SDK_VIDEOLOSSCONFIG
	E_SDK_CFG_NETABORT,					//网络异常										对应结构体SDK_VIDEOLOSSCONFIG

	E_SDK_CONFIG_CHNSTATUS,				//通道状态										对应结构体SDK_NetDecorderChnStatusAll
	E_SDK_CONFIG_CHNMODE,				//通道模式										对应结构体SDK_NetDecorderChnModeConfig

	E_SDK_CONFIG_NET_DAS,				//主动注册										对应结构体SDK_DASSerInfo
	E_SDK_CONFIG_CAR_INPUT_EXCHANGE,	//外部信息输入与车辆状态的对应关系			
	E_SDK_CONFIG_DELAY_TIME,			//车载系统延时配置
	E_SDK_CONFIG_NET_ORDER,				//网络优先级
	E_SDK_CONFIG_ABILITY_NETORDER ,		//网络优先级设置能力
	E_SDK_CONFIG_CARPLATE,				//车牌号配置	
	E_SDK_CONFIG_LOCALSDK_NET_PLATFORM, //网络平台信息设置								对应SDK_LocalSdkNetPlatformConfig
	E_SDK_CONFIG_GPS_TIMING,			//GPS校时相关配置								对应SDK_GPSTimingConfig
	E_SDK_CONFIG_VIDEO_ANALYZE,			//视频分析(智能DVR)                             对应SDK_RULECONFIG
	E_SDK_CONFIG_GODEYE_ALARM,			//神眼接警中心系统								对应SDK_GodEyeConfig
	E_SDK_CONFIG_NAT_STATUS_INFO,		//nat状态信息									对应SDK_NatStatusInfo
	E_SDK_CONFIG_BUGINFOSAVE,			//命令调试(保存)									 
	E_SDK_CONFIG_MEDIA_WATERMARK,		//水印设置										对应SDK_WaterMarkConfigAll
	E_SDK_CONFIG_ENCODE_STATICPARAM,	//编码器静态参数						        对应SDK_EncodeStaticParamAll
	E_SDK_CONFIG_LOSS_SHOW_STR,			//视频丢失显示字符串
	E_SDK_CONFIG_DIGMANAGER_SHOW,		//通道管理显示配置                              对应SDK_DigManagerShowStatus
	E_SDK_CONFIG_ABILITY_ANALYZEABILITY, //智能分析能力									对应SDK_ANALYZEABILITY
	E_SDK_CONFIG_VIDEOOUT_PRIORITY,		//显示HDMI VGA优先级别配置
	E_SDK_CONFIG_NAT,		  			//NAT功能，MTU值配置                            对应SDK_NatConfig
	E_SDK_CONFIG_CPCINFO,				//智能CPC计数数据信息                           对应SDK_CPCDataAll
	E_SDK_CONFIG_STORAGE_POSITION,      //录像存储设备类型，                            对应 SDK_RecordStorageType
	E_SDK_CONFIG_ABILITY_CARSTATUSNUM,  //车辆状态数									对应 SDK_CarStatusNum
	E_SDK_CFG_VPN,						//VPN											对应SDK_VPNConfig
	E_SDK_CFG_VIDEOOUT,					//VGA视频分辨率									对应SDK_VGAresolution
	E_SDK_CFG_ABILITY_VGARESOLUTION,    //支持的VGA分辨率列表							对应SDK_VGAResolutionAbility
	E_SDK_CFG_NET_LOCALSEARCH,          //搜索设备，设备端的局域网设备					对应SDK_NetDevList
	E_SDK_CFG_NETPLAT_KAINENG,			// 												SDK_CONFIG_KAINENG_INFO
	E_SDK_CFG_ENCODE_STATICPARAM_V2,	//DVR编码器静态参数                             SDK_EncodeStaticParamV2
	E_SDK_ABILITY_ENC_STATICPARAM,		//静态编码能力集 DVR							SDK_EncStaticParamAbility (掩码)
	E_SDK_CFG_C7_PLATFORM,				//												SDK_C7PlatformConfig
	E_SDK_CFG_MAIL_TEST,				////邮件测试                                    SDK_NetEmailConfig
	E_SDK_CFG_NET_KEYBOARD,				//网络键盘服务                                  SDK_NetKeyboardConfig
	E_SDK_ABILITY_NET_KEYBOARD,			//网络键盘协议									SDK_NetKeyboardAbility  
	E_SDK_CFG_SPVMN_PLATFORM,			//28181协议配置		                            SDK_ASB_NET_VSP_CONFIG	
	E_SDK_CFG_PMS,						//手机服务                                      SDK_PMSConfig
	E_SDK_CFG_OSD_INFO,					//屏幕提示信息                                  SDK_OSDInfoConfigAll
	E_SDK_CFG_KAICONG,					//                                              SDK_KaiCongAlarmConfig
	E_SDK_CFG_DIGITAL_REAL,				//真正支持的通道模式				            SDK_VideoChannelManage
	E_SDK_ABILITY_PTZCONTROL,			//PTZ控制能力集                                 SDK_PTZControlAbility
	E_SDK_CFG_XMHEARTBEAT,				//												SDK_XMHeartbeatConfig
	E_SDK_CFG_MONITOR_PLATFORM,			//												SDK_MonitorPlatformConfig
	E_SDK_CFG_PARAM_EX,					//摄像头扩展参数                                SDK_CameraParamEx
	E_SDK_CFG_NETPLAT_ANJU_P2P,			//安巨P2P										SDK_NetPlatformCommonCfg  
	E_SDK_GPS_STATUS,					///< GPS连接信息								SDK_GPSStatusInfo 
	E_SDK_WIFI_STATUS,					///< Wifi连接信息								SDK_WifiStatusInfo
	E_SDK_3G_STATUS,					///< 3G连接信息									SDK_WirelessStatusInfo
	E_SDK_DAS_STATUS,					///< 主动注册状态								SDK_DASStatusInfo 
	E_SDK_ABILITY_DECODE_DELEY,			//解码策略能力									SDK_DecodeDeleyTimePrame
	E_SDK_CFG_DECODE_PARAM,				//解码最大延时									SDK_DecodeParam
	E_SDK_CFG_VIDEOCOLOR_CUSTOM,        //												SDK_VIDEOCOLOR_PARAM_CUSTOM
	E_SDK_ABILITY_ONVIF_SUB_PROTOCOL,	//onvif子协议									SDK_AbilityMask   
	E_SDK_CONFIG_EXPORT_V2,				//导出设备默认配置，即出厂的配置
	E_SDK_CFG_CAR_BOOT_TYPE,			//车载开关机模式								SDK_CarBootTypeConfig
	E_SDK_CFG_IPC_ALARM,				//IPC网络报警									SDK_IPCAlarmConfigAll
	E_SDK_CFG_NETPLAT_TUTK_IOTC,		//TUTK IOTC平台配置								SDK_NetPlatformCommonCfg
	E_SDK_CFG_BAIDU_CLOUD,				//baidu云   SDK_BaiduCloudCfg

	
	E_SDK_CFG_SMARTDETECTION_CODEC,			//智能编码		
	E_SDK_CFG_SMARTDETECTION_DETECT,		//智能检测		
	E_SDK_CFG_SMARTDETECTION_CONTROL,		//智能控制		
	E_SDK_CFG_SMARTDETECTION_LUMINANCE,		//亮度侦测		
	E_SDK_CFG_SMARTDETECTION_MOVE,			//移动侦测		
	E_SDK_CFG_SMARTDETECTION_OCCLUSION,		//遮挡侦测		
	E_SDK_CFG_SMARTDETECTION_CROSSLINE,		//虚拟警戒线	
	E_SDK_CFG_SMARTDETECTION_CROSSAREA,		//区域入侵		
	E_SDK_CFG_SMARTDETECTION_COLOR,			//颜色			
	E_SDK_CFG_SMARTDETECTION_SOUND,			//声音			
	E_SDK_CFG_SMARTDETECTION_LOSEOBJ,		//物品预留		
	

	E_SDK_CFG_CALIBRATION_GET_CAMERA_PARAMETER,			//获取摄像机是否已经标定		
	E_SDK_CFG_CALIBRATION_SET_SUBCAMERA_CONNECTINFO,	//设置从机登录信息				
	E_SDK_CFG_CALIBRATION_SET_POINTS,					//设置标定坐标(增、删，3D)		
	E_SDK_CFG_CALIBRATION_ACTION,						//设置标定（开始、完成）		  
	E_SDK_CFG_CALIBRATION_MODE,							//标定模式						
	E_SDK_CFG_CALIBRATION_ZOOMTIMES,					//变倍系数						
	E_SDK_CFG_CALIBRATION_PTZINFO,						//PTZ参数
	E_SDK_CFG_CALIBRATION_PANOTYPE,						//获取全景摄像机类型	
	
	E_SDK_CFG_CALIBRATION_SETINFO_YW,					//参数					SDK_MS_Calibrate_Point    
	E_SDK_CFG_CALIBRATION_RESULT_YW,					//结果	 Result			SDK_MS_ANALY_POINT		
	E_SDK_CFG_CALIBRATION_ENCRYPT,

	E_SDK_CFG_CALIBRATION_NAMING,						//点名球设置（只设置，不读）


	E_SDK_CFG_FACECOMPARE_RESULT_ALARM,					//对比结果报警					

	E_SDK_CFG_SMARTFACE_COMMON_PARAMETER,				//人脸识别参数	抓拍参数SDK_FA_SNAP_FACE_CONFIG				
	E_SDK_CFG_SMARTFACE_AREADETECTION,					//人脸识别侦测区域	
	E_SDK_CFG_SMARTFACE_AREASHIELDED,					//人脸区域屏蔽
	E_SDK_CFG_SMARTFACE_VERSION,						//识别算法版本号				
	E_SDK_CFG_SMARTFACE_ALARM,							//人脸报警参数设置	

	E_SDK_CFG_LINKAGE_BIND,								//全景联动绑定
	E_SDK_CFG_CUSTOMIZED_QT,							//定制-长沙全图
	E_SDK_CFG_OSD,										//对应结构体SDK_OSD_SWITCH_S;
	E_SDK_CFG_SMART,									//对应结构体SDK_SMART_FRAME_DROP_S
	E_SDK_CFG_EXPOSURE,									//对应结构体SDK_EXPOSURE_MS_PARAM_S

	E_SDK_CFG_FORMAT,									//格式化SD卡对应结构体SDK_FORMAT_PARAM_S

	E_SDK_CFG_EXPOSURE_MUIT,							//多播地址设置,对应结构体SDK_EXPOSURE_MUIT
	E_SDK_CFG_AWBAUTO_MODE,								//白平衡设置,对应结构体SDK_AWBAUTO_MODE
	E_SDK_CFG_NET_HTTPSERVER,							//HTTP对应结构体SDK_HTTPSERVERCONFIG
	E_SDK_CFG_FACE_CAPTURE_MODE,						//人脸模式选择，对应结构体SDK_FACE_CAPTURE_MODE
	
	E_SDK_NVR_SEARCH_FILE,								//拼接解码器搜索录像对应结构体为SDK_SYSTEM_TIME
	E_SDK_NVR_REALPLAY,									//拼接解码器播放实时视频	SDK_SYSTEM_TIME
	E_SDK_NVR_REPLAY,									//拼接解码器回放录像	SDK_SYSTEM_TIME
}SDK_CONFIG_TYPE;

/// 报警事件码
enum SDK_EventCodeTypes
{
	SDK_EVENT_CODE_INIT = 0,
	SDK_EVENT_CODE_LOCAL_ALARM = 1,	//本地报警
	SDK_EVENT_CODE_NET_ALARM,		//网络报警
	SDK_EVENT_CODE_MANUAL_ALARM,	//手动报警
	SDK_EVENT_CODE_VIDEO_MOTION,	//动态检测
	SDK_EVENT_CODE_VIDEO_LOSS,		//视频丢失
	SDK_EVENT_CODE_VIDEO_BLIND,		//视频遮挡
	SDK_EVENT_CODE_VIDEO_TITLE,		
	SDK_EVENT_CODE_VIDEO_SPLIT,
	SDK_EVENT_CODE_VIDEO_TOUR,
	SDK_EVENT_CODE_STORAGE_NOT_EXIST,//存储设备不存在
	SDK_EVENT_CODE_STORAGE_FAILURE,//存储设备访问失败
	SDK_EVENT_CODE_LOW_SPACE,		//存储设备容量过低
	SDK_EVENT_CODE_NET_ABORT,
	SDK_EVENT_CODE_COMM,
	SDK_EVENT_CODE_STORAGE_READ_ERROR,//存储设备读错误
	SDK_EVENT_CODE_STORAGE_WRITE_ERROR,//存储设备写错误
	SDK_EVENT_CODE_NET_IPCONFLICT,	//ip冲突
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
	SDK_EventConsSensorAlarm, //消费类产品绑定的外部设备报警
	SDK_EventBrightness,
	SDK_EventShelter,
	SDK_EventCrossLine,
	SDK_EventCrossArea,
	SDK_EventColor,
	SDK_EventSound,
	SDK_EventLoseOBJ,

	SDK_EVENT_CODE_LUMA_WARNNING,		//亮度报警
	SDK_EVENT_CODE_OD_WARNNING,		//遮挡报警
	SDK_EVENT_CODE_CROSSLINE_WARNNING,		//虚拟警戒线报警
	SDK_EVENT_CODE_CROSSAREA_WARNNING,		//区域入侵报警
	SDK_EVENT_CODE_COLOR_WARNNING,		//颜色侦测报警
	SDK_EVENT_CODE_SOUND_WARNNING,		//声音侦测报警
	SDK_EVENT_CODE_LOSEOBJ_WARNNING,		//遗留物体侦测报警

	SDK_EVENT_CODE_SMARTFACE_BLACKLIST,
	SDK_EVENT_CODE_SMARTFACE_WHITELIST,
	SDK_EVENT_CODE_SMARTFACE_VIPLIST,
	SDK_EVENT_CODE_SMARTFACE_NONWHITELIST,//49

	SDK_EVENT_CODE_NR,
};
//! 编码配置的类型
enum SDK_ENCODE_TYPE_BY_RECORD
{
	SDK_ENCODE_TYPE_TIM = 0,
	SDK_ENCODE_TYPE_MTD = 1,
	SDK_ENCODE_TYPE_ALM = 2,
	SDK_ENCODE_TYPE_NUM = 3,
	SDK_ENCODE_TYPE_SNAP_TIMER = 0,
	SDK_ENCODE_TYPE_SNAP_TRIGGER = 1,
};
#define SDK_EXTRATYPES 3 //辅码流类型

//网络传输策略
enum SDK_TransferPolicy
{
	SDK_TRANSFER_POLICY_AUTO,		///< 自适应
	SDK_TRANSFER_POLICY_QUALITY,	///< 质量优先
	SDK_TRANSFER_POLICY_FLUENCY,	///< 流量优先
	SDK_TRANSFER_POLICY_TRANSMISSION,//< 网传优先
	SDK_TRANSFER_POLICY_NR,
};



typedef struct {
	int left;
	int top;
	int right;
	int bottom;
}sdkRect;

/// 音频输入格式，语音对讲用
struct SDK_AudioInFormatConfig
{
	int iBitRate;	   ///< 码流大小，kbps为单位，比如192kbps，128kbps
	int iSampleRate;   ///< 采样率，Hz为单位，比如44100Hz
	int iSampleBit;    ///< 采样的位深
	int iEncodeType;   ///< 编码方式，参照AudioEncodeTypes定义
};

//语音对讲格式
typedef enum __TALK_CODING_TYPE
{
	TALK_DEFAULT = 0,
	TALK_PCM = 1,					//PCM
	TALK_G711a,						//G711a
	TALK_AMR,						//AMR
	TALK_G711u,						//G711u
	TALK_G726,						//G726
}TALK_CODING_TYPE;
//语音对讲
typedef struct  
{
	TALK_CODING_TYPE		encodeType;		//编码类型
	int						nAudioBit;		//用实际的值表示，如8位 则填值为8
	unsigned int			dwSampleRate;	//采样率，如16k 则填值为16000
	char					reserved[64];
}VIDEONET_TALKDECODE_INFO;


/// 系统时间结构
typedef struct SDK_SYSTEM_TIME{
	int  year;///< 年。   
	int  month;///< 月，January = 1, February = 2, and so on.   
	int  day;///< 日。   
	int  wday;///< 星期，Sunday = 0, Monday = 1, and so on   
	int  hour;///< 时。   
	int  minute;///< 分。   
	int  second;///< 秒。   
	int  isdst;///< 夏令时标识。   
}SDK_SYSTEM_TIME;

//录像设置相关结构体
typedef struct tagSDK_TIMESECTION
{
	//!使能
	int enable;
	//!开始时间:小时
	int startHour;
	//!开始时间:分钟
	int	startMinute;
	//!开始时间:秒钟
	int	startSecond;
	//!结束时间:小时
	int	endHour;
	//!结束时间:分钟
	int	endMinute;
	//!结束时间:秒钟
	int	endSecond;
}SDK_TIMESECTION;	

typedef struct{
	int dwYear;		//年
	int dwMonth;	//月
	int dwDay;		//日
	int dwHour;		//时
	int dwMinute;	//分
	int dwSecond;	//秒
}VIDEONET_TIME,*LPVIDEONET_TIME;

//时间结构
typedef struct _NEW_NET_TIME								
{
	unsigned int second			:6;					//	秒	1-60		
	unsigned int minute			:6;					//	分	1-60		
	unsigned int hour			:5;					//	时	1-24		
	unsigned int day			:5;					//	日	1-31		
	unsigned int month			:4;					//	月	1-12		
	unsigned int year			:6;					//	年	2000-2063	
}NEW_NET_TIME, *LPNET_TIME;
///< 夏令时结构
struct DSTPoint
{
	int	iYear;
	int	iMonth;
	int	iWeek;		///<周1:first  to2 3 4 -1:last one   0:表示使用按日计算的方法[-1,4]
	int	iWeekDay;	///<weekday from sunday=0	[0, 6]
	int Hour;
	int Minute;
};

struct SDK_VIDEO_FORMAT
{
	int		iCompression;			//  压缩模式 	
	int		iResolution;			//  分辨率 参照枚举SDK_CAPTURE_SIZE_t
	int		iBitRateControl;		//  码流控制 参照枚举SDK_capture_brc_t
	int		iQuality;				//  码流的画质 档次1-6		
	int		nFPS;					//  帧率值，NTSC/PAL不区分,负数表示多秒一帧		
	int		nBitRate;				//  0-4096k,该列表主要由客户端保存，设备只接收实际的码流值而不是下标。
	int		iGOP;					//  描述两个I帧之间的间隔时间，2-12 
} ;
struct  SDK_AUDIO_FORMAT
{
	int		nBitRate;				//  码流kbps	
	int		nFrequency;				//  采样频率	
	int		nMaxVolume;				//  最大音量阈值
} ;
// 媒体格式
struct SDK_MEDIA_FORMAT
{
	SDK_VIDEO_FORMAT vfFormat;			//  视频格式定义 			
	SDK_AUDIO_FORMAT afFormat;			//  音频格式定义 
	bool	bVideoEnable;				//  开启视频编码 
	bool	bAudioEnable;				//  开启音频编码 	
} ;

typedef union {	//IP addr
	unsigned char	c[4];
	unsigned short	s[2];
	unsigned int 	l;
}CONFIG_IPAddress;

///////////////////用户帐号管理相关结构体/////////////////////////////////
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
	bool		reserved;		//是否保留
	bool		shareable;		//本用户是否允许复用 1-复用，0-不复用
}USER_INFO_JL;

typedef struct _USER_GROUP_INFO
{
	int			rigthNum;
	char		memo[NET_MAX_USER_LENGTH]; 
	char		name[NET_MAX_USER_LENGTH];
	char		rights[NET_MAX_RIGTH_NUM][NET_MAX_USER_LENGTH];	//权限列表
}USER_GROUP_INFO;

//用户信息配置结构
typedef struct _USER_MANAGE_INFO
{
	int					rigthNum;
	OPR_RIGHT			rightList[NET_MAX_RIGTH_NUM];
	int					groupNum;
	USER_GROUP_INFO		groupList[NET_MAX_GROUP_NUM];
	int					userNum;
	USER_INFO_JL			userList[NET_MAX_USER_NUM];
}USER_MANAGE_INFO;

//修改用户
typedef struct _CONF_MODIFYUSER
{
	char UserName[NET_MAX_USER_LENGTH];
	USER_INFO_JL User;
}CONF_MODIFYUSER;

//修改组
typedef struct _CONF_MODIFYGROUP
{
	char GroupName[NET_MAX_USER_LENGTH];
	USER_GROUP_INFO Group;
}CONF_MODIFYGROUP;


/// 修改用户密码请求
struct _CONF_MODIFY_PSW
{
	char sUserName[NET_MAX_USER_LENGTH];
	char Password[NET_MAX_USER_LENGTH];
	char NewPassword[NET_MAX_USER_LENGTH];
};

//普通配置页结构体
typedef struct _SDK_CONFIG_NORMAL
{	
	SDK_SYSTEM_TIME sysTime;		//系统时间

	int iLocalNo;			/*!< 本机编号:[0, 998] */
	int iOverWrite;			/*!< 硬盘满时处理 "OverWrite", "StopRecord" */		
	int iSnapInterval;			///< 定时抓图的时间间隔，以秒为单位 
	char sMachineName[64];	///< 机器名
	int iVideoStartOutPut;	/*!< 输出模式 */
	int iAutoLogout;			///< 本地菜单自动注销(分钟)	[0, 120]

	int iVideoFormat;		/*!< 视频制式:“PAL”, “NTSC”, “SECAM” */
	int iLanguage;			/*!< 语言选择:“English”, “SimpChinese”, “TradChinese”, “Italian”, “Spanish”, “Japanese”, “Russian”, “French”, “German” */	
	int iDateFormat;		/*!< 日期格式:“YYMMDD”, “MMDDYY”, “DDMMYY” */
	int iDateSeparator;		/*!< 日期分割符:“.”, “-”, “/” */
	int iTimeFormat;		/*!< 时间格式:“12”, “24” */
	int iDSTRule;			///< 夏令时规则 
	int iWorkDay;			///< 工作日
	DSTPoint dDSTStart;
	DSTPoint dDSTEnd;
}SDK_CONFIG_NORMAL;



//osd开关设置
typedef struct OSD_SWITCH_S
{
	DWORD			title0;	//标题0					
	DWORD			title1;	//标题1						
	DWORD			title2;	//标题2				
	DWORD			title3;	 //标题3	
	DWORD			day;						
	DWORD			week;							
	DWORD			time;							
	DWORD			bitRate;
	DWORD			connectNum;	
}SDK_OSD_SWITCH_S;

//降帧处理
typedef struct SMART_FRAME_DROP_S 
{
	DWORD	lowFrameEnable; //0 关 1开				
}SDK_SMART_FRAME_DROP_S;

//曝光主从设置
typedef struct EXPOSURE_MS_PARAM_S
{
	DWORD			msMode; //0:slave  1: master			
}SDK_EXPOSURE_MS_PARAM_S;

//格式化SD
typedef struct FORMAT_PARAM_S
{
	DWORD IpcStorageNum;	//SD卡号
}SDK_FORMAT_PARAM_S;

//多播地址设置
typedef struct EXPOSURE_MUIT_S
{
	char byMuitAddr[128];	//多播地址
}SDK_EXPOSURE_MUIT;

//白平衡模式
typedef struct SDK_AWBAUTO_MODE_S
{
	DWORD dwAwbMode;	//白平衡模式
	DWORD dwAutoAwb;	//白平衡	0自动, 1 手动 
	DWORD dwAwBblue;	//白平衡	蓝  0~255
	DWORD dwAwBRed;		//白平衡	红  0~255
	DWORD dwAwBGreen;	//白平衡	绿	 0~255
}SDK_AWBAUTO_MODE;

typedef enum _SDK_AUTOWB_GROUP //全图自动白平衡模式
{
	AWB_GROUP_NOMAL			= 0x0, //白平衡1==> 普通镜头
	AWB_GROUP_FTK_CS120 	= 0x1, //白平衡2==> 福特科cs120镜头标定参数
	AWB_GROUP_YT3611 		= 0x2, //白平衡3==>yt3.6-11mm电动变倍镜头	默认
	AWB_GROUP_HM1212MP5 	= 0x3, //白平衡4==>中联创HM121MP5 大光圈镜头

}SDK_AUTOWB_GROUP;


//以下编码配置相关
// 编码设置
struct SDK_CONFIG_ENCODE
{
	SDK_MEDIA_FORMAT dstMainFmt[SDK_ENCODE_TYPE_NUM];		//  主码流格式 	
	SDK_MEDIA_FORMAT dstExtraFmt[SDK_EXTRATYPES];	//  辅码流格式 
	SDK_MEDIA_FORMAT dstSnapFmt[SDK_ENCODE_TYPE_NUM];		//  抓图格式 
};
struct  SDK_EncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_CHANNUM];
};


// 简化版本编码配置
/// 媒体格式
struct SDK_MEDIA_FORMAT_SIMPLIIFY
{
	SDK_VIDEO_FORMAT vfFormat;			//  视频格式定义 			
	bool	bVideoEnable;			//  开启视频编码 
	bool	bAudioEnable;			//  开启音频编码 	
};

/// 编码设置
struct SDK_CONFIG_ENCODE_SIMPLIIFY
{
	SDK_MEDIA_FORMAT dstMainFmt;		//  主码流格式 	
	SDK_MEDIA_FORMAT dstExtraFmt;	//  辅码流格式 
};

/// 全通道编码配置
struct SDK_EncodeConfigAll_SIMPLIIFY
{
	SDK_CONFIG_ENCODE_SIMPLIIFY vEncodeConfigAll[NET_MAX_CHANNUM];
};


struct  SDK_CombineEncodeConfigAll
{
	SDK_CONFIG_ENCODE vEncodeConfigAll[NET_MAX_COMBINE_NUM];
};

/// 组合编码模式
struct SDK_CombEncodeParam
{
	int iEncodeMode;	 //见CombineEncodeMode
};

struct SDK_CombEncodeModeAll
{
	SDK_CombEncodeParam vEncodeParam[NET_MAX_COMBINE_NUM];
};

//!视频物件结构
struct  SDK_VIDEO_WIDGET
{
	unsigned int rgbaFrontground;		///< 物件的前景MakeRGB，和透明度	
	unsigned int rgbaBackground;		///< 物件的后景MakeRGB，和透明度	
	sdkRect	rcRelativePos;			///< 物件边距与整长的比例*8191
	bool	bPreviewBlend;			///< 预览叠加	
	bool	bEncodeBlend;			///< 编码叠加
};

//!视频物件设置
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
	}ChannelName;					/// 通道名称
	int				iCoverNum;		/*!< 当前该通道有几个叠加的区域 */
};

/// 视频物件(输出模式对话框)
struct SDK_VideoWidgetConfigAll
{
	SDK_CONFIG_VIDEOWIDGET vVideoWidegetConfigAll[NET_MAX_CHANNUM];
};

//视频颜色
struct SDK_VIDEOCOLOR_PARAM
{
	int	nBrightness;		///< 亮度	0-100
	int	nContrast;			///< 对比度	0-100
	int	nSaturation;		///< 饱和度	0-100
	int	nHue;				///< 色度	0-100
	int	mGain;				///< 增益	0-100 第７位置1表示自动增益		
	int	mWhitebalance;		///< 自动白电平控制，bit7置位表示开启自动控制.0x0,0x1,0x2分别代表低,中,高等级
	int nAcutance;          ///< 锐度   0-15
};
///< 视频颜色设置
struct SDK_VIDEOCOLOR
{
	SDK_TIMESECTION			tsTimeSection;		/// 时间段
	SDK_VIDEOCOLOR_PARAM	dstColor;			/// 颜色定义
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


/// 所有通道名称标题
struct SDK_ChannelNameConfigAll
{
	char channelTitle[NET_MAX_CHANNUM][NET_NAME_PASSWORD_LEN];
};

//输出模式
struct SDK_GUISetConfig
{
	int iWindowAlpha;			///< 窗口透明度	[128, 255]
	bool bTimeTitleEn;			///< 时间标题显示使能
	bool bChannelTitleEn;		///< 通道标题显示使能	
	bool bAlarmStatus;			///<  报警状态
	bool bRecordStatus;			///<  录像状态显示使能
	bool bChanStateRecEn;		///< 录像标志显示使能
	bool bChanStateVlsEn;		///< 视频丢失标志显示使能
	bool bChanStateLckEn;		///< 通道锁定标志显示使能	
	bool bChanStateMtdEn;		///< 动态检测标志显示使能
	bool bBitRateEn;			///< 码流显示使能
	bool bRemoteEnable;			///< 遥控器使能
	bool bDeflick;				///< 抗抖动
};


////!普通网络设置
struct SDK_CONFIG_NET_COMMON
{
	//!主机名
	char HostName[NET_NAME_PASSWORD_LEN];
	//!主机IP
	CONFIG_IPAddress HostIP;
	//!子网掩码
	CONFIG_IPAddress Submask;
	//!网关IP
	CONFIG_IPAddress Gateway;
	//!HTTP服务端口
	int HttpPort;
	//!TCP侦听端口
	int TCPPort;	
	//!SSL侦听端口
	int SSLPort;
	//!UDP侦听端口
	int UDPPort;
	//!最大连接数
	int MaxConn;
	//!监视协议 {"TCP","UDP","MCAST",…}
	int MonMode;
	//!限定码流值
	int MaxBps;
	//!传输策略
	//char TransferPlan[NET_NAME_PASSWORD_LEN];
	int TransferPlan;

	//!是否启用高速录像下载测率
	bool bUseHSDownLoad;

	//!MAC地址
	char sMac[NET_MAX_MAC_LEN];

	char szUserName[NET_NAME_PASSWORD_LEN];		//设备用户名
	char szPassword[NET_NAME_PASSWORD_LEN];		//设备密码
};

////!普通网络设置 --
struct SDK_CONFIG_NET_COMMON_V2
{
	//!主机名
	char HostName[NET_NAME_PASSWORD_LEN];
	//!主机IP
	CONFIG_IPAddress HostIP;
	//!子网掩码
	CONFIG_IPAddress Submask;
	//!网关IP
	CONFIG_IPAddress Gateway;
	//!HTTP服务端口
	int HttpPort;
	//!TCP侦听端口
	int TCPPort;	
	//!SSL侦听端口
	int SSLPort;
	//!UDP侦听端口
	int UDPPort;
	//!最大连接数
	int MaxConn;
	//!监视协议 {"TCP","UDP","MCAST",…}
	int MonMode;
	//!限定码流值
	int MaxBps;
	//!传输策略
	//char TransferPlan[NET_NAME_PASSWORD_LEN];
	int TransferPlan;

	//!是否启用高速录像下载测率
	bool bUseHSDownLoad;

	//!MAC地址
	char sMac[NET_MAX_MAC_LEN];

	char sSn[NET_MAX_MAC_LEN]; 	///序列号
	int ChannelNum;			///通道数                //by zjh 20170807
	int	DeviceType;			///设备类型，如枚举DevType  //by zjh 20170807
	char szUserName[NET_NAME_PASSWORD_LEN];		//设备用户名
	char szPassword[NET_NAME_PASSWORD_LEN];		//设备密码
	char Resume[56];	///保留
};
//设备类型定义
typedef enum _SDK_DEVICE_TYPE
{
	SDK_DEV_TYPE_IPC = 0,		//普通摄像机

	SDK_DEV_TYPE_DVR,			//兼容NVR中协议有关设备定义		
	SDK_DEV_TYPE_HVR,
	SDK_DEV_TYPE_POEIPC,
	SDK_DEV_TYPE_NVR,
	SDK_DEV_TYPE_RTSPIPC,

	SDK_DEV_TYPE_BSIPC,			//比对机 6
	SDK_DEV_TYPE_FPIPC,			//抓拍机 7
	SDK_DEV_TYPE_CPIPC,			//车牌抓拍机 
	SDK_DEV_TYPE_END
}SDK_DEVICE_TYPE;

//DHCP
#define SDK_MAX_ETH_NUM 4
struct SDK_NetDHCPConfig
{
	bool bEnable;
	char ifName[32];
};
/// 所有网卡的DHCP配置
struct SDK_NetDHCPConfigAll
{
	SDK_NetDHCPConfig vNetDHCPConfig[SDK_MAX_ETH_NUM];
};

///< DNS设置
struct SDK_NetDNSConfig
{
	CONFIG_IPAddress		PrimaryDNS;
	CONFIG_IPAddress		SecondaryDNS;
};
///< 服务器结构定义
struct SDK_RemoteServerConfig
{
	char ServerName[NET_NAME_PASSWORD_LEN];	///< 服务名
	CONFIG_IPAddress ip;						///< IP地址
	int Port;							///< 端口号
	char UserName[NET_NAME_PASSWORD_LEN];		///< 用户名
	char Password[NET_NAME_PASSWORD_LEN];		///< 密码	
	bool Anonymity;							///< 是否匿名登录
};
///< 服务器结构定义扩展,将域名，用户名，和密码
struct SDK_RemoteServerConfig_EX
{
	char ServerName[NET_NAME_URL_LEN];	///< 服务名
	CONFIG_IPAddress ip;						///< IP地址
	char ServerUrl[NET_NAME_URL_LEN];	//服务器Url
	int Port;							///< 端口号
	char UserName[NET_NAME_URL_LEN];		///< 用户名
	char Password[NET_NAME_URL_LEN];		///< 密码	
	bool Anonymity;							///< 是否匿名登录
};
///< IP权限设置
struct SDK_NetIPFilterConfig
{
	bool Enable;		///< 是否开启
	CONFIG_IPAddress BannedList[NET_MAX_FILTERIP_NUM];		///< 黑名单列表
	CONFIG_IPAddress TrustList[NET_MAX_FILTERIP_NUM];		///< 白名单列表
};

///< 组播设置
struct SDK_NetMultiCastConfig
{
	bool Enable;		///< 是否开启
	SDK_RemoteServerConfig Server;		///< 组播服务器
};

///< pppoe设置
struct SDK_NetPPPoEConfig
{
	bool Enable;	///< 是否开启
	SDK_RemoteServerConfig Server;		///< PPPOE服务器
	CONFIG_IPAddress addr;		///< 拨号后获得的IP地址
};

///< DDNS设置
struct SDK_NetDDNSConfig
{
	bool Enable;	///< 是否开启
	bool Online;		///< 是否在线
	char DDNSKey[NET_NAME_PASSWORD_LEN];	///< DDNS类型名称, 目前有: JUFENG
	char HostName[NET_NAME_PASSWORD_LEN];	///< 主机名
	SDK_RemoteServerConfig Server;			///< DDNS服务器
	
};

///< DDNS设置
struct SDK_NetDDNSConfigALL
{
	SDK_NetDDNSConfig ddnsConfig[NET_MAX_DDNS_TYPE];
};

///< FTP设置
struct SDK_FtpServerConfig{
	bool bEnable;        ///< 服务器使能     
	SDK_RemoteServerConfig Server;	///< FTP服务器
	char cRemoteDir[NET_MAX_PATH_LENGTH];	///< 远程目录
	int iMaxFileLen;	///< 文件最大长度
};

///<HTTP设置
typedef struct _SDK_HTTPSERVERCONFIG_   //1948字节
{
	int      bEnable;		//http推送使能 0关，1开
	char     serverip[128]; 	//接收图片信息服务器地址(IP或域名)
	int      serverport;		//接收图片信息服务器端口
	char     serverpath[128];	//接收图片信息的服务器路径 (格式: /[path])
	int      resendnum;  		//重传次数（0-5）
	int 	 bImgEnable;  		//是否上传图片   ,0否，1是
	int 	 nListenPort;		//监听端口
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
	//消息类型: 
	//0:所有人上传 1: 比对成功上传 2:黑名单上传 3:白名单上传 4: VIP名单上传
	//5:陌生人上传 6: 非白名单上传
	int 	 msgType;
	int	 featureEn;	   	//特征值使能: 0不上传特征值 1 上传特征值
	char     byRes11[64];
	char     byRes12[64];
	int      bKeepAliveEnable;	//是否开启心跳推送功能  ,   0关，1开
	char     keepaliveaddr[64]; 	//接收心跳信息的服务器地址(ip或域名)
	int      keepaliveport;		//接收心跳信息的服务器端口
	char     keepalivepath[128];	//接收心跳信息的服务器路径(格式: /[path])
	int      keepaliveInterval; 	//心跳间隔(1~100000秒)
	char     byRes13[64];
	int      bRemoteUpgrade; 	//远程升级,   0关，1开
	int      bGetVersionInterval;	//检查版本时间间隔(1~100000分钟) 
	char     GetVersionURL[128]; 	//获取版本地址
	char     postUrl[128];		//推送识别信息地址 (格式: http://[ip]:[port]/[path])
	char     byRes14[128];
	char     postKeepAliveUrl[128]; //推送心跳信息地址 (格式: http://[ip]:[port]/[path])
	int      nRes15;
	BYTE	 byRes[92];
}SDK_HTTPSERVERCONFIG;

///< NTP设置
struct SDK_NetNTPConfig
{
	///< 是否开启
	bool Enable;
	///< PPPOE服务器
	SDK_RemoteServerConfig Server;
	///< 更新周期
	int UpdatePeriod;
	///< 时区
	int TimeZone;
};
#define  NET_MAX_EMAIL_TITLE_LEN 64
#define  NET_MAX_EMAIL_RECIEVERS  5
#define  NET_EMAIL_ADDR_LEN  32

///< EMAIL设置
struct SDK_NetEmailConfig
{
	///< 是否开启
	bool Enable;
	///< smtp 服务器地址使用字符串形式填充
	///< 可以填ip,也可以填域名
	SDK_RemoteServerConfig Server;
	bool bUseSSL;
	///< 发送地址
	char SendAddr[NET_EMAIL_ADDR_LEN];
	///< 接收人地址
	char Recievers[NET_MAX_EMAIL_RECIEVERS][NET_EMAIL_ADDR_LEN];
	///< 邮件主题
	char Title[NET_MAX_EMAIL_TITLE_LEN];
	///< email有效时间
	SDK_TIMESECTION Schedule[NET_N_MIN_TSECT];
};

///< ARSP(主动注册服务器)设置
struct SDK_NetARSPConfig
{
	bool bEnable;	///< 是否开启
	char sARSPKey[NET_NAME_PASSWORD_LEN];	///< DNS类型名称
	int iInterval;	///< 保活间隔时间
	char sURL[NET_NAME_PASSWORD_LEN];    ///< 本机域名
	SDK_RemoteServerConfig Server;		///< DDNS服务器
	int nHttpPort;                  ///< 服务器HTTP端口
};

struct SDK_NetARSPConfigAll
{
	SDK_NetARSPConfig vNetARSPConfigAll[NET_MAX_ARSP_TYPE];
};

///< 解码器地址设置
struct SDK_NetDecoderConfig
{
	bool Enable;						///< 是否开启
	char UserName[NET_NAME_PASSWORD_LEN];	///< DDNS类型名称, 目前有: JUFENG
	char PassWord[NET_NAME_PASSWORD_LEN];	///< 主机名
	char Address[NET_NAME_PASSWORD_LEN];
	int Protocol;
	int Port;							///< 解码器连接端口
	int Channel;						///< 解码器连接通道号
	int Interval;                       ///< 轮巡的间隔时间(s)
};

/// 所有通道的解码器地址设置
struct SDK_NetDecoderConfigAll
{
	SDK_NetDecoderConfig vNetDecoderConfig[NET_MAX_DECORDR_CH];
};


/// 解码器地址设置V2版本
struct SDK_NetDecoderConfig_V2
{
	int nTotalNum;            //有效的数组个数，最大为NET_MAX_CHANNUM
	SDK_NetDecoderConfig vNetDecoderConfig[NET_MAX_CHANNUM];
};

/// 所有通道的解码器地址设置V2版本
struct SDK_NetDecoderConfigAll_V2
{
	SDK_NetDecoderConfig_V2 vNetDecoderArray[NET_MAX_DECORDR_CH];
};


///< 解码器地址设置
struct SDK_NetDecorderConfigV3
{
	bool Enable;						///< 是否开启
	char UserName[NET_NAME_PASSWORD_LEN];	///< DDNS类型名称, 目前有: JUFENG
	char PassWord[NET_NAME_PASSWORD_LEN];	///< 主机名
	char Address[NET_NAME_URL_LEN];
	int Protocol;
	int Port;							///< 解码器连接端口
	int Channel;						///< 解码器连接通道号
	int Interval;                       ///< 轮巡的间隔时间(s),0:表示永久
	char ConfName[NET_NAME_PASSWORD_LEN];	///<配置名称
	int DevType;						///<设备类型
	int StreamType;						///<连接的码流类型CaptureChannelTypes
	char MainRtspUrl[NET_NAME_URL_LEN];		///<rtsp协议时表示前端设备的主码流地址
	char SubRtspUrl[NET_NAME_URL_LEN];		///<rtsp协议时表示前端设备的辅码流地址
};

/*解码器连接类型*/
enum SDK_DecorderConnType
{
	SDK_CONN_SINGLE = 0, 	/*单连接*/
	SDK_CONN_MULTI = 1,		/*多连接轮巡*/
	SDK_CONN_TYPE_NR,
};

/*数字通道的配置*/
struct SDK_NetDigitChnConfig
{
	bool Enable;		/*数字通道是否开启*/		
	int ConnType;		/*连接类型，取DecoderConnectType的值*/
	int TourIntv;		/*多连接时轮巡间隔*/
	unsigned int SingleConnId;	/*单连接时的连接配置ID, 从1开始，0表示无效*/
	bool EnCheckTime;	/*开启对时*/
	SDK_NetDecorderConfigV3 NetDecorderConf[32]; /*网络设备通道配置表*/
	int nNetDeorde; // 有多少个
};

/*所有数字通道的配置*/
struct SDK_NetDecorderConfigAll_V3
{
	SDK_NetDigitChnConfig DigitChnConf[NET_MAX_DECORDR_CH];
};

//通道模式
#define MAX_HVR_CHNCAP_CHN		32
typedef struct SDK_HVR_CHNCAP 
{
	int nD1Chn;		// 支持的D1路数
	int n960HChn;	// 支持的960H路数
	int n720PChn;	// 支持的720P路数
	int n1080PChn;	// 支持的1080P路数
	int nCIFChn;	//支持的CIF通道数
	int nHD1Chn;	//支持的HD1通道数
	unsigned char nPlayChn; //支持回放路数
	unsigned char nDigiTalChn; //支持最大数字通道路数
	unsigned char n960PChn; //支持的960P通道数
	unsigned char n3MChn; //支持的3M通道数
	unsigned char n5MChn; //支持的5M通道数
	unsigned char nWUXGAChn; //支持的WUXGA通道数
	unsigned char nResChar[2]; //冗余
}SDK_HVR_CHNCAP, *SDK_PHVR_CHNCAP;

typedef struct SDK_CAPTURE_HVRCAP 
{
	SDK_HVR_CHNCAP DigitalCap;		// 支持的数字通道信息
	SDK_HVR_CHNCAP AnalogCap;		// 支持的模拟通道信息
}SDK_CAPTURE_HVRCAP, *SDK_PCAPTURE_HVRCAP;

typedef struct SDK_CAPTURE_TOTAL_HVRCAP 
{
	int		nHVRCap;			// 实际支持的模式
	SDK_CAPTURE_HVRCAP	HVRCap[MAX_HVR_CHNCAP_CHN];		// 所有模式的汇总
}SDK_CAPTURE_TOTAL_HVRCAP, *SDK_PCAPTURE_TOTAL_HVRCAP;

//通道模式配置
struct SDK_NetDecorderChnModeConfig
{
	SDK_CAPTURE_TOTAL_HVRCAP 	HVRTotalCap;
	int HVRCurCapMode;
};


/*数字通道状态*/
struct SDK_NetDecorderChnStatus
{
	char ChnName[NET_NAME_PASSWORD_LEN];
	char pMaxResName[50];
	char	pCurResName[50];
	char pStatus[50];
};

/*所有数字通道状态*/
struct SDK_NetDecorderChnStatusAll
{
	SDK_NetDecorderChnStatus ChnStatusAll[MAX_HVR_CHNCAP_CHN];
};

///< 3G拨号设置
struct SDK_Net3GConfig
{
	bool bEnable;			  ///< 无线模块使能标志
	int iNetType;			  ///< 无线网络类型
	char sAPN[NET_NAME_PASSWORD_LEN];		///< 接入点名称
	char sDialNum[NET_NAME_PASSWORD_LEN];   ///< 拨号号码
	char sUserName[NET_NAME_PASSWORD_LEN];  ///< 拨号用户名
	char sPassword[NET_NAME_PASSWORD_LEN];  ///< 拨号密码
	CONFIG_IPAddress addr;			  ///< 拨号后获得的IP地址
};

///< 手机监控设置包括
struct SDK_NetMoblieConfig
{
	bool bEnable;	///< 是否开启
	SDK_RemoteServerConfig Server;		///< 服务器
};

//RTSP
struct SDK_NetRTSPConfig
{
	bool bServer;
	bool bClient;
	SDK_RemoteServerConfig Server;		///< 服务器模式
	SDK_RemoteServerConfig Client;		///< 客户端模式
};

///< UPNP设置
struct SDK_NetUPNPConfig
{
	bool bEnable;			  ///< 使能标志
	bool bState;              ///< 状态, 1: OK 0: NOK
	int iHTTPPort;			  ///< HTTP连接映射后的端口
	int iMediaPort;			  ///< 媒体连接映射后的端口
	int iMobliePort;		  ///< 手机监控映射后的端口
};

///< WIFI设置
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

///< 报警中心设置
struct SDK_NetAlarmCenterConfig
{
	bool bEnable;		///< 是否开启
	char sAlarmServerKey[NET_NAME_PASSWORD_LEN];	///< 报警中心协议类型名称, 
	///< 报警中心服务器
	SDK_RemoteServerConfig Server;	
	bool bAlarm;
	bool bLog;
};

struct SDK_NetAlarmServerConfigAll
{
	SDK_NetAlarmCenterConfig vAlarmServerConfigAll[NET_MAX_ALARMSERVER_TYPE];
};


//互信互通
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

// 新望平台
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

// 视搜平台
struct SDK_CONFIG_NET_SHISOU
{
	bool bEnable;
	SDK_RemoteServerConfig Server;
	char szSID[NET_MAX_USERNAME_LENGTH];
};

// VVEYE平台
struct SDK_CONFIG_NET_VVEYE
{
	bool bEnable;                
	bool bCorpEnable;            //只有在使用企业服务器时才需要设置Server
	SDK_RemoteServerConfig Server;
	char szDeviceName[NET_MAX_USERNAME_LENGTH];
};

// 报警中心消息类型
enum SDK_AlarmCenterMsgType
{
	SDK_ALARMCENTER_ALARM,
	SDK_ALARMCENTER_LOG,
};

// 报警中心消息类型
enum SDK_AlarmCenterStatus
{
	SDK_AC_START,
	SDK_AC_STOP,
};

// 告警中心消息内容
struct SDK_NetAlarmCenterMsg
{
	CONFIG_IPAddress HostIP;		///< 设备IP
	int nChannel;                   ///< 通道
	int nType;                      ///< 类型 见AlarmCenterMsgType
	int nStatus;                    ///< 状态 见AlarmCenterStatus
	SDK_SYSTEM_TIME Time;           ///< 发生时间
	char sEvent[NET_MAX_INFO_LEN];  ///< 事件
	char sSerialID[NET_MAX_MAC_LEN]; ///< 设备序列号
	char sDescrip[NET_MAX_INFO_LEN];  ///< 描述
};

/// 编码信息
struct SDK_EncodeInfo
{
	bool bEnable;			///< 使能项
	int iStreamType;		///< 码流类型，capture_channel_t
	bool bHaveAudio;		///< 是否支持音频
	unsigned int uiCompression;		///< capture_comp_t的掩码
	unsigned int uiResolution;		///< SDK_CAPTURE_SIZE_t的掩码
};

/// 编码能力
struct CONFIG_EncodeAbility
{
	unsigned int iMaxEncodePower;		///< 支持的最大编码能力
	int iChannelMaxSetSync;		///< 每个通道分辨率是否需要同步 0-不同步, 1 -同步
	unsigned int nMaxPowerPerChannel[NET_MAX_CHANNUM];		///< 每个通道支持的最高编码能力
	unsigned int ImageSizePerChannel[NET_MAX_CHANNUM];		///< 每个通道支持的图像分辨率
	unsigned int ExImageSizePerChannel[NET_MAX_CHANNUM];		///< 每个通道支持的辅码流图像分辨率
	SDK_EncodeInfo vEncodeInfo[SDK_CHL_FUNCTION_NUM];	///< 编码信息,暂时最大就4中码流
	SDK_EncodeInfo vCombEncInfo[SDK_CHL_FUNCTION_NUM];	///< 组合编码信息,暂时最大就4中码流
	int	iMaxBps;				///< 最高码流Kbps
	unsigned int ExImageSizePerChannelEx[NET_MAX_CHANNUM][SDK_CAPTURE_SIZE_NR];	///< 每个通道支持的辅码流图像分辨率
};

// 串口协议
enum SDK_CommProtocol
{
	SDK_CONSOLE = 0,
	SDK_KEYBOARD,
	SDK_COM_TYPES,
};
/// 串口协议
struct SDK_COMMFUNC
{
	//每个协议最多由64个字符组成
	int nProNum;
	char vCommProtocol[100][32];
};

/// 云台协议
struct SDK_PTZPROTOCOLFUNC
{
	//每个协议最多由64个字符组成
	int nProNum;
	char vPTZProtocol[100][NET_MAX_PTZ_PROTOCOL_LENGTH];
};

/// 区域遮挡能力集
struct SDK_BlindDetectFunction
{
	int iBlindConverNum;	///< 区域遮挡块数
};

/// 动检区域能力集
struct SDK_MotionDetectFunction
{
	int iGridRow;
	int iGridColumn;
};

/// 支持的DDNS类型
struct SDK_DDNSServiceFunction
{
	int  nTypeNum;
	char vDDNSType[NET_MAX_DDNS_TYPE][64];
};

/// 支持语言
struct SDK_MultiLangFunction
{
	//每个协议最多由64个字符组成
	int nLangNum;
	char vLanguageName[128][64];
};

/// 支持的视频制式
struct SDK_MultiVstd
{
	//每个协议最多由3个字符组成
	int nVstdNum;
	char vVstdName[3][64];
};

/// 编码功能
enum SDK_EncodeFunctionTypes
{
	SDK_ENCODE_FUNCTION_TYPE_DOUBLE_STREAM,		///< 双码流功能
	SDK_ENCODE_FUNCTION_TYPE_COMBINE_STREAM,	///< 组合编码功能
	SDK_ENCODE_FUNCTION_TYPE_SNAP_STREAM,		///< 抓图功能
	SDK_ENCODE_FUNCTION_TYPE_WATER_MARK,		///< 水印功能
	SDK_ENCODE_FUNCTION_TYPE_IFRAME_RANGE,		///< I帧间隔
	SDK_ENCODE_FUNCTION_TYPE_LOW_BITRATE,		///< 低码流，家用产品使用
	SDK_ENCODE_FUNCTION_TYPE_NR,
};

/// 报警功能
enum SDK_AlarmFucntionTypes
{
	SDK_ALARM_FUNCTION_TYPE_MOTION_DETECT,	///< 动态检测
	SDK_ALARM_FUNCTION_TYPE_BLIND_DETECT,	///< 视屏遮挡
	SDK_ALARM_FUNCTION_TYPE_LOSS_DETECT,	///< 视屏丢失
	SDK_ALARM_FUNCTION_TYPE_LOCAL_ALARM,	///< 本地报警
	SDK_ALARM_FUNCTION_TYPE_NET_ALARM,		///< 网络报警
	SDK_ALARM_FUNCTION_TYPE_IP_CONFLICT,	///< IP地址冲突
	SDK_ALARM_FUNCTION_TYPE_NET_ABORT,		///< 网络异常
	SDK_ALARM_FUNCTION_TYPE_STORAGE_NOTEXIST,	///< 存储设备不存在
	SDK_ALARM_FUNCTION_TYPE_STORAGE_LOWSPACE,	///< 存储设备容量不足
	SDK_ALARM_FUNCTION_TYPE_STORAGE_FAILURE,	///< 存储设备访问失败
	SDK_ALARM_FUNCTION_TYPE_VIDEOANALYSE,///<视频分析
	SDK_ALARM_FUNCTION_TYPE_NET_ABORT_EXTEND,	//网络异常扩展
	SDK_ALARM_FUNCTION_TYPE_IPC_ALARM,			//IPC报警
	SDK_ALARM_FUNCTION_TYPE_NR
};

/// 网络服务功能
enum SDK_NetServerTypes
{
	SDK_NET_SERVER_TYPES_IPFILTER,		///< 白黑名单
	SDK_NET_SERVER_TYPES_DHCP,			///< DHCP功能
	SDK_NET_SERVER_TYPES_DDNS,			///< DDNS功能
	SDK_NET_SERVER_TYPES_EMAIL,			///< Email功能
	SDK_NET_SERVER_TYPES_MULTICAST,		///< 多播功能
	SDK_NET_SERVER_TYPES_NTP,			///< NTP功能
	SDK_NET_SERVER_TYPES_PPPOE,
	SDK_NET_SERVER_TYPES_DNS,
	SDK_NET_SERVER_TYPES_ARSP,			///< 主动注册服务
	SDK_NET_SERVER_TYPES_3G,            ///< 3G拨号
	SDK_NET_SERVER_TYPES_MOBILE=10,        ///< 手机监控
	SDK_NET_SERVER_TYPES_UPNP,			    ///< UPNP
	SDK_NET_SERVER_TYPES_FTP,			    ///< FTP
	SDK_NET_SERVER_TYPES_WIFI,          ///<WIFI
	SDK_NET_SERVER_TYPES_ALARM_CENTER,  ///< 告警中心
	SDK_NET_SERVER_TYPES_NETPLAT_MEGA,  ///< 互信互通
	SDK_NET_SERVER_TYPES_NETPLAT_XINWANG,  ///< 星望
	SDK_NET_SERVER_TYPES_NETPLAT_SHISOU,  ///< 视搜
	SDK_NET_SERVER_TYPES_NETPLAT_VVEYE,  ///< 威威眼
	SDK_NET_SERVER_TYPES_RTSP,     //RTSP
	SDK_NET_SERVER_TYPES_PHONEMSG=20,     //手机信息发送配置
	SDK_NET_SERVER_TYPES_PHONEMULTIMEDIAMSG,     //手机信息发送配置
	SDK_NET_SERVER_TYPES_DAS,          //主动注册
	SDK_NET_SERVER_TYPES_LOCALSDK_PLATFORM,          //网络平台信息设置
	SDK_NET_SERVER_TYPES_GOD_EYE,///<神眼接警中心系统
	SDK_NET_SERVER_TYPES_NAT,		///NAT穿透，MTU配置
	SDK_NET_SERVER_TYPES_VPN,     ///VPN
	SDK_NET_SERVER_TYPES_NET_KEYBOARD,	///网络键盘配置
	SDK_NET_SERVER_TYPES_SPVMN,		///28181协议配置
	SDK_NET_SERVER_TYPES_PMS,      //手机服务
	SDK_NET_SERVER_TYPE_KAICONG,		///凯聪配置
	SDK_NET_SERVER_TYPE_PROTOCOL_MAC,///支持MAC协议
	SDK_NET_SERVER_TYPE_XMHEARTBEAT, //雄迈心跳
	SDK_NET_SERVER_TYPES_MONITOR_PLATFORM, //神州数码监控平台
	SDK_NET_SERVER_TYPES_ANJUP2P,			//
	SDK_NET_SERVER_TYPES_TUTKIOTC,		//TUTK IOTC平台
	SDK_NET_SERVER_TYPES_BAIDUCLOUD, //百度云
	SDK_NET_SERVER_TYPES_MOBILWATCH,		//手机看店
	SDK_NET_SERVER_TYPES_BJLTHY,				//北京龙腾访问服务器平台
	SDK_NET_SERVER_TYPES_OPENVPN,			//openvpn配置
	SDK_NET_SERVER_TYPES_PROTOCOL_NAT,		//支持NAT协议
	SDK_NET_SERVER_TYPES_PLATFORM_GBEYES,	//支持环保数据叠加
	SDK_NET_SERVER_TYPES_DATALINK,			//DataLink客户网络服务中执行程序使能配置
	SDK_NET_SERVER_TYPES_WIFI_MODE,			//是否支持wifi模式相关配置
	SDK_NET_SERVER_TYPES_IPV6,				//支持ipv6
	SDK_NET_SERVER_TYPES_PMS_V2,			//新版PMS页面
	SDK_NET_SERVER_TYPES_4G,				//无线拨号的协议下拉框是否显示4G
	SDK_NET_SERVER_TYPES_NR,   
};

/// 预览功能
enum SDK_PreviewTypes
{
	SDK_PREVIEW_TYPES_TOUR,		///< 轮巡
	SDK_PREVIEW_TYPES_TALK,		///< GUI界面配置
	SDK_PREVIEW_TYPES_NR
};

///串口类型
enum SDK_CommTypes
{
	SDK_COMM_TYPES_RS485,			///<485串口
	SDK_COMM_TYPES_RS232,			///<232串口
	SDK_COMM_TYPES_NR
};

//输入法限制
enum SDK_InPutMethod
{
	SDK_NO_SUPPORT_CHINESE,		//不支持中文输入
	SDK_NO_SUPPORT_NR
};

//报警中标签显示
enum SDK_TipShow
{
	SDK_NO_BEEP_TIP_SHOW,  //蜂鸣提示
	SDK_NO_FTP_TIP_SHOW,  //FTP提示
	SDK_NO_EMAIL_TIP_SHOW,  //EMAIL提示
	SDK_NO_TIP_SHOW_NR
};
///车载功能
enum SDK_MobileCar
{
	SDK_MOBILEDVR_STATUS_EXCHANGE,
	SDK_MOBILEDVR_DELAY_SET,
	SDK_MOBILEDVR_CARPLATE_SET,
	SDK_MOBILEDVR_GPS_TIMING,
	SDK_MOBILEDVR_DVR_BOOT_TYPE_SET,
	SDK_MOBILEDVR_NR
};

///其他功能
enum SDK_OtherFunction
{
	SDK_OTHER_DOWNLOADPAUSE,		//录像下载暂停功能
	SDK_OTHER_USB_SUPPORT_RECORD,	//USB支持录像功能
	SDK_OTHER_SD_SUPPORT_RECORD,		//SD支持录像功能
	SDK_OTHER_ONVIF_CLIENT_SUPPORT,	//是否支持ONVIF客户端
	SDK_OTHER_NET_LOCALSEARCH_SUPPORT,	//是否支持远程搜索
	SDK_OTHER_MAXPLAYBACK_SUPPORT, //是否支持最大回放通道数显示
	SDK_OTHER_NVR_SUPPORT, //是否是专业NVR
	SDK_OTHER_C7_PLATFORM_SUPPORT,//支持C7平台
	SDK_OTHER_MAIL_TEST_SUPPORT,		//支持邮件测试
	SDK_OTHER_SHOW_OSD_INFO,            //支持显示3行OSD信息
	SDK_OTHER_HIDE_DIGITAL, //通道模式屏蔽功能	
	SDK_OTHER_ACUTANCE_HORIZONTAL,	//锐度
	SDK_OTHER_ACUTANCE_VERTIAL,
	SDK_OTHER_BROAD_TRENDS,		//宽动态功能
	SDK_OTHER_NO_TALK,		//对讲能力
	SDK_OTHER_ALTER_DIGITAL_NAME,	//修改数字通道名称
	SDK_OTHER_SHOW_CONNECT_STATUS,      //支持显示wifi 3G 主动注册等的连接状态
	SDK_OTHER_SUPPORT_ECACT_SEEK,	//支持回放精准定位
	SDK_OTHER_UPLOAD_TITLEANDSTATE,		//通道标题和数字通道状态上传能力集
	SDK_OTHER_NO_HDD_RECORD,		//无硬盘录像
	SDK_OTHER_MUSICFILE_PLAY,		//播放音频文件
	SDK_OTHER_SUPPORT_SET_DIG_IP,//设置前端ip能力
	SDK_OTHER_VERSION_PRODUCT_TYPE,//支持在版本信息里显示设备型号
	SDK_OTHER_SUPPORT_CAMERA_IMG_STYLE,//支持摄像机图像风格
	SDK_OTHER_SUPPORT_TITLE_ABILITY,//支持修改onvif标题(当做模拟通道处理)
	SDK_OTHER_SUPPORT_DIMEN_CODE,//支持二维码
	SDK_OTHER_SHOWFALSE_CHECKTIME,//屏蔽解码器时间同步功能
	SDK_OTHER_SUPPORT_TIME_ZONE, //支持时区设置
	SDK_OTHER_SHOW_ALARM_LEVEL_REGION,//显示数字通道报警功能的灵敏度和区域设置
	SDK_OTHER_SUPPORT_POS,//支持POS功能
	SDK_OTHER_HDD_LOWSPACE_USE_MB,//硬盘空间不足报警下限用MB
	SDK_OTHER_SUPPORT_CUSTOMIZE_OEMINFO,//定制OEM客户版本信息
	SDK_OTHER_DIGITAL_ENCODE,//数字通道编码配置
	SDK_OTHER_RESUME_PTZ_STATE,//开机恢复云台状态
	SDK_OTHER_SUPPORT_SNAP_CFG,//支持抓图配置
	SDK_OTHER_ABNORMITY_SEND_EMAIL,//存储设备存在及存储异常及存储空间不足发邮件
	SDK_OTHER_SUPPORT_DIGITAL_PRE, //支持数字通道预录
	SDK_OTHER_SUPPORT_WRITE_LOG,   //报警页面添加是否写日志勾选框
	SDK_OTHER_SUPPORT_CHANGE_ONVIF_PORT,//支持修改onvif端口
	SDK_OTHER_SUPPORT_COMM_DATA_UPLOAD,  //支持串口数据上传到指定服务器
	SDK_OTHER_SUPPORT_TEXT_PASSWORD,     //记录可反解的密码
	SDK_OTHER_SUPPORT_CLOUD_UPGRADE,	// 支持通过云升级设备程序
	SDK_OTHER_SUPPORT_USER_PROGRAM,//支持启动客户小程序
	SDK_OTHER_SUPPORT_MODIFY_FRONT_CFG,//支持修改前端配置
	SDK_OTHER_SUPPORT_FTP_TEST,    //新程序支持FTP支持FTP测试，老程序不支持。
	SDK_OTHER_SUPPORT_PTZ_IDLE_STATE, //云台空闲时执行何种操作的配置
	SDK_OTHER_SUPPORT_IMP_RCD,	//web端是否提供关键录像搜索的选项	
	SDK_OTHER_SUPPORT_CAMERA_MOTOR_CTRL, //支持机器人马达控制
	SDK_OTHER_SUPPORT_ENCODE_ADD_BEEP,// 视频编码每隔30秒加入beep声	
	SDK_OTHER_SUPPORT_FISH_EYE,	        //鱼眼功能能力集
	SDK_OTHER_SUPPORT_SPVMN_NAS_SERVER,	//安徽超清客户的nas服务器配置
	SDK_OTHER_SUPPORT_SMALL_CHN_TITLE_FONT,  //IE端传12*18的通道标题点阵
	SDK_OTHER_RTSP_CLIENT_SUPPORT,			 //数字通道是否支持通过RTSP连接前端设备
	SDK_OTHER_SUPPORT_CFG_CLOUD_UPGRADE, 	//支持新的云升级功能配置
	SDK_OTHER_SUPPORT_STORAGE_FAIL_REBOOT,	//全部硬盘出错后自动重启
	SDK_OTHER_SUPPORT_SPLIT_CONTROL,		//修改DVR的预览画面分割模式
	SDK_OTHER_NR
};

///支持的系统功能
struct SDK_SystemFunction
{
	bool vEncodeFunction[SDK_ENCODE_FUNCTION_TYPE_NR];	///< 编码功能SDK_EncodeFunctionTypes
	bool vAlarmFunction[SDK_ALARM_FUNCTION_TYPE_NR];		///< 报警功能AlarmFucntionTypes
	bool vNetServerFunction[SDK_NET_SERVER_TYPES_NR];	///< 网络服务功能NetServerTypes
	bool vPreviewFunction[SDK_PREVIEW_TYPES_NR];		///< 预览功能PreviewTypes
	bool vCommFunction[SDK_COMM_TYPES_NR];			///<串口类型SDK_CommTypes
	bool vInputMethodFunction[SDK_NO_SUPPORT_NR];  //<输入法限制SDK_InPutMethod>
	bool vTipShowFunction[SDK_NO_TIP_SHOW_NR];               //报警标签显示SDK_TipShow>
	bool vMobileCarFunction[SDK_MOBILEDVR_NR];//车载功能
	bool	vOtherFunction[SDK_OTHER_NR];				//其他功能OtherFunction
};

struct SDK_COMMATTRI
{
	int	iDataBits;	// 数据位取值为5,6,7,8 
	int	iStopBits;	// 停止位
	int	iParity;	// 校验位
	int	iBaudRate;	// 实际波特率
};

// 串口配置
struct SDK_CONFIG_COMM_X
{
	char iProtocolName[32];	// 串口协议:“Console” 
	int iPortNo;		// 端口号 
	SDK_COMMATTRI aCommAttri;		// 串口属性 
};

struct SDK_CommConfigAll
{
	SDK_CONFIG_COMM_X vCommConfig[SDK_COM_TYPES];
};


// 云台设置
struct SDK_STR_CONFIG_PTZ
{
	char sProtocolName[NET_MAX_PTZ_PROTOCOL_LENGTH];	// 协议名称 	
	int	ideviceNo;				// 云台设备地址编号 	
	int	iNumberInMatrixs;		// 在矩阵中的统一编号	
	int iPortNo;				// 串口端口号	[1, 4] 	
	SDK_COMMATTRI dstComm;			// 串口属性 	
};

//所有通道云台协议
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
	SDK_TIMESECTION	tsSchedule[NET_N_WEEKS][NET_N_TSECT];	/*!< 时间段 */
};

/// 录像模式种类
enum SDK_RecordModeTypes
{
	SDK_RECORD_MODE_CLOSED,		///< 关闭录像
	SDK_RECORD_MODE_MANUAL,		///< 手动录像
	SDK_RECORD_MODE_CONFIG,		///< 按配置录像
	SDK_RECORD_MODE_NR,		
};

///< 录像设置
struct SDK_RECORDCONFIG
{
	int iPreRecord;			///< 预录时间，为零时表示关闭	
	bool bRedundancy;		///< 冗余开关
	bool bSnapShot;			///< 快照开关	
	int iPacketLength;		///< 录像打包长度（分钟）[1, 255]
	int iRecordMode;		///< 录像模式，0 关闭，1 禁止 2 配置
	SDK_CONFIG_WORKSHEET wcWorkSheet;			///< 录像时间段	
	unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];		///< 录像类型掩码
};

//录像设置结构体
struct SDK_RECORDCONFIG_ALL
{
	SDK_RECORDCONFIG vRecordConfigAll[NET_MAX_CHANNUM];
};

///< 图片设置
struct SDK_SnapshotConfig
{
	int iPreSnap;			///< 预抓图片数
	bool bRedundancy;		///< 冗余开关
	int iSnapMode;		///< 录像模式，见RecordModeTypes
	SDK_CONFIG_WORKSHEET wcWorkSheet;				///< 录像时间段	
	unsigned int typeMask[NET_N_WEEKS][NET_N_TSECT];	///< 录像类型掩码，见enum RecordTypes
};

struct SDK_SnapshotConfigAll
{
	SDK_SnapshotConfig vSnapshotConfigAll[NET_MAX_CHANNUM];
};


//报警相关结构体
//  云台联动结构
struct SDK_PtzLinkConfig
{
	int iType;		// 联动的类型 
	int iValue;		// 联动的类型对应的值 
};

#define CHANNELNAME_MAX_LEN 64  //通道名称最大长度

struct SDK_EventHandler
{
	unsigned int	dwRecord;				// 录象掩码 
	int		iRecordLatch;			// 录像延时：10～300 sec  	
	unsigned int	dwTour;					// 轮巡掩码 	
	unsigned int	dwSnapShot;				// 抓图掩码 
	unsigned int	dwAlarmOut;				// 报警输出通道掩码 
	unsigned int	dwMatrix;				// 矩阵掩码 
	int		iEventLatch;			// 联动开始延时时间，s为单位 
	int		iAOLatch;				// 报警输出延时：10～300 sec  
	SDK_PtzLinkConfig PtzLink[NET_MAX_CHANNUM];		// 云台联动项 
	SDK_CONFIG_WORKSHEET schedule;		// 录像时间段

	bool	bRecordEn;				// 录像使能 
	bool	bTourEn;				// 轮巡使能 
	bool	bSnapEn;				// 抓图使能 	
	bool	bAlarmOutEn;			// 报警使能 
	bool	bPtzEn;

	// 云台联动使能 
	bool	bTip;					// 屏幕提示使能 	
	bool	bMail;					// 发送邮件 	
	bool	bMessage;				// 发送消息到报警中心 	
	bool	bBeep;					// 蜂鸣 	
	bool	bVoice;					// 语音提示 		
	bool	bFTP;					// 启动FTP传输 
	bool	bMatrixEn;				// 矩阵使能 
	bool	bLog;					// 日志使能
	bool	bMessagetoNet;			// 消息上传给网络使能 

	bool    bShowInfo;              // 是否在GUI上和编码里显示报警信息
	unsigned int    dwShowInfoMask;         // 要联动显示报警信息的通道掩码
	char    pAlarmInfo[CHANNELNAME_MAX_LEN];//要显示的报警信息

	bool    bShortMsg;              //发送短信
	bool    bMultimediaMsg;         //发送彩信
};

//人脸模式设置NVR
typedef struct _SDK_FACE_CAPTURE_MODE
{
	int	CaptureMode[4];		//Para Value:0 两者都不选，1前抓，2后抓
}SDK_FACE_CAPTURE_MODE;

enum SDK_ANALYSE_MODE
{
	SDK_ANALYSE_TRIPWIRE = 0, //单绊线
	SDK_ANALYSE_PERIMETER     //周界检测
};
/** 周界检测模式 */
enum SDK_URP_PERIMETER_MODE_E
{
	SDK_URP_PMODE_INTRUSION = 0,			/**< 入侵 */
	SDK_URP_PMODE_ENTER,				/**< 进入 */
	SDK_URP_PMODE_EXIT				/**< 离开 */
};

/** 最大边界点数 */
#define SDK_MAX_BOUNDARY_POINT_NUM 8
#define SDK_MAX_POINT_NUM 4
#define SDK_NAME_BUF_SIZE 16

/** 坐标点 */
struct URP_SDK_POINT_S
{
	short X;					/**< x */
	short Y;					/**< y */
};

/** 线结构 */
struct SDK_URP_LINE_S
{
	URP_SDK_POINT_S stStartPt;			/**< 线段起点 */
	URP_SDK_POINT_S stEndPt;			/**< 线段终点 */
};

struct SDK_URP_POLYGON_REGION_S
{
	int iValid;
	int iPointNum;
	URP_SDK_POINT_S astPoint[SDK_MAX_BOUNDARY_POINT_NUM];
};

/** URP周界检测边界点 */
struct SDK_URP_PERIMETER_LIMIT_BOUNDARY_S
{
	int      iBoundaryPtNum;					/**< 边界点数目 */
	URP_SDK_POINT_S   astBoundaryPts[SDK_MAX_BOUNDARY_POINT_NUM];	/**< 边界点集合 */
};

/** URP周界检测限制参数 */
struct SDK_URP_PERIMETER_LIMIT_PARA_S
{
	int iMinDist;						/**< 最小像素距离 */
	int iMinTime;						/**< 最短时间 */
	int	iDirectionLimit;					/**< 是否做方向限制 */
	int iForbiddenDirection;					/**< 禁止方向角度(单位: 角度) */
	SDK_URP_PERIMETER_LIMIT_BOUNDARY_S stBoundary;			/**< 周界边界区域 */
};

/** URP周界检测规则参数 */
struct SDK_URP_PERIMETER_RULE_PARA_S
{
	int iTypeLimit;						/**< 目标类型限制 */
	int iTypeHuman;						/**< 目标类别：人(限定类型时使用) */
	int iTypeVehicle;						/**< 目标类别：车 */
	int iMode;						/**< 周界模式 */
	SDK_URP_PERIMETER_LIMIT_PARA_S stLimitPara;				/**< 周界限制参数 */
} ;

// ----------------------------------------------------------------------
//  绊线数据结构
/** URP单绊线最多条数 */
#define SDK_URP_MAX_TRIPWIRE_CNT 8

/** URP单绊线结构 */
struct SDK_URP_TRIPWIRE_S
{
	int     iValid;						/**< 是否有效 */
	int    iIsDoubleDirection;				/**< 表示该绊线是否为双向绊线(0: 否, 1: 是) */
	int     iForbiddenDirection;				/**< 单绊线禁止方向*/
	SDK_URP_LINE_S	stLine;						/**< 单绊线位置 */
};

/** URP单绊线限制参数 */
struct SDK_URP_TRIPWIRE_LIMIT_PARA_S
{
	int iMinDist;						/**< 最小像素距离 */
	int iMinTime;						/**< 最短时间 */
};

/** URP单绊线规则参数 */
struct SDK_URP_TRIPWIRE_RULE_PARA_S
{
	int iTypeLimit;						/**< 目标类型限制 */
	int iTypeHuman;						/**< 目标类别：人(限定类型时使用) */
	int iTypeVehicle;						/**< 目标类别：车 */
	SDK_URP_TRIPWIRE_S astLines[SDK_URP_MAX_TRIPWIRE_CNT];		/**< 单绊线 */
	SDK_URP_TRIPWIRE_LIMIT_PARA_S stLimitPara;				/**< 单绊线限制参数 */
};


/** URP目标输出灵敏度级别 */
enum SDK_SENSITIVITY_LEVEL_E
{
	SDK_HIGH_LEVEL_SENSITIVITY,         /**< 高灵敏度 */
	SDK_MIDDLE_LEVEL_SENSITIVITY,		/**< 中灵敏度 */
	SDK_LOW_LEVEL_SENSITIVITY			/**< 低灵敏度 */
};

/** 算法模块 */

enum SDK_MODULE_TYPE
{
	SDK_MODULE_TYPE_PEA = 0,
	SDK_MODULE_TYPE_OSC,
	SDK_MODULE_TYPE_AVD,
	SDK_MODULE_TYPE_ALL
};

// ----------------------------------------------------------------------
// 下面开始是自定义结构

struct SDK_PEA_RULE_S
{
	int iShowTrack;						/// 是否显示轨迹
	int iShowRule;						/// 是否显示规则
	int iLevel;						/// 警戒级别（灵敏度）0：高级（默认值）；1：中级；2：低级；
	int iPerimeterEnable;					/// 周界规则使能
	SDK_URP_PERIMETER_RULE_PARA_S	stPerimeterRulePara;	/**< 周界检测 */
	int iTripWireEnable;					/// 单绊线规则使能
	SDK_URP_TRIPWIRE_RULE_PARA_S	stTripwireRulePara;	/**< 单绊线检测 */
};

/// 算法能力结构
struct SDK_CAPS					/// 置1表示该通道支持对应的智能算法，置0表示不支持。
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
	int dwPerimeter;					/// 入侵检测状态，包括了伴线和周界,，uint值是各个报警输入通道报警状态的掩码。
	/// 低通道在低位，高通道在高位。报警置1，无报警置0，不存在的通道置0。
	int iResv[4];
	int avdStatue;
};


//物品遗留-begin
#define NET_MAX_OSC_NUM 4
#define NET_MAX_POINT_NUM 4
#define NET_NAME_BUF_SIZE 16

struct SDK_URP_OSC_SPECL_REGIONS_S
{
	int nValid; //是否有效
	char chName[NET_NAME_BUF_SIZE]; //区域名称
	SDK_URP_POLYGON_REGION_S stOscRg; //要检测区域定义
	SDK_URP_POLYGON_REGION_S astSubRgA; //检测区域中的无效子区域
	SDK_URP_POLYGON_REGION_S astSubRgB; //检测区域中的无效子区域
	SDK_URP_POLYGON_REGION_S astSubRgC; //检测区域中的无效子区域
};

struct SDK_URP_OSC_LMT_PARA_S
{
	int nTimeMin; //时间约束
	int nSizeMin; //最小尺寸
	int nSizeMax; //最大尺寸
} ;

struct SDK_URP_OSC_RULE_PARA_S
{
	int nSceneType; //场景类型
	int nCameraType; //相机类型
	SDK_URP_OSC_SPECL_REGIONS_S astSpclRgs[NET_MAX_OSC_NUM]; //要处理的区域个数
	SDK_URP_OSC_LMT_PARA_S stOscPara; //一些约束
} ;

struct SDK_OSC_RULE_S
{
	int iShowTrack;				/// 是否显示轨迹
	int iShowRule;						     /// 是否显示规则
	int iLevel;						     /// 警戒级别0：非警报（默认值）；1：低级；2：中级；3: 高级
	int iAbandumEnable;		   	/// 物品遗留使能
	SDK_URP_OSC_RULE_PARA_S stObjAbandumRulePara; /// 物品遗留参数
	int iStolenEnable;			  	 /// 物品被盗使能
	SDK_URP_OSC_RULE_PARA_S stObjStolenRulePara;   /// 物品被盗参数
	int iNoParkingEnable;		 	  	 /// 非法停车使能
	SDK_URP_OSC_RULE_PARA_S stNoParkingRulePara;   /// 非法停车参数
};


struct SDK_AVD_RULE_S
{
	int iLevel;						     /// 灵敏度档位，1-5档，数值越大越灵敏越易报警
	int itBrightAbnmlEnable;				///< 亮度异常使能
	int iClarityEnable;					///< 清晰度检测使能
	int iNoiseEnable;					///< 噪声检测使能
	int iColorEnable;					///< 偏色检测使能
	int iFreezeEnable;					///< 画面冻结检测使能
	int iNosignalEnable;					///< 信号缺失检测使能
	int iChangeEnable;					///< 场景变换检测使能
	int iInterfereEnable;					///< 人为干扰检测使能 
	int iPtzLoseCtlEnable;					///< PTZ失控检测使能
};

/** 坐标点 */
struct SDK_URP_IMP_POINT_S
{
	short s16X;					/**< x */
	short s16Y;					/**< y */
};

struct SDK_CPC_RULE_S
{
	SDK_URP_IMP_POINT_S stRulePoint[4];	///检测规则，需要画满4个点	
	int s32Sizemin;			///最小像距(0,height/2)
	int s32Sizemax;			///最大像距(sizemin, height/2)
	int s32Countmax;			///最大目标数[1~15],
	int s32Sensitivity;		/// 灵敏度档位，1-5档，数值越大越灵敏越易报警	
	unsigned int u32Flag;				///标志位，用来判断进出，默认设0
	int s32EnterDirection;	///进入的方向
};

//各种算法的规则配置集合
struct SDK_RULECONFIG
{
	SDK_PEA_RULE_S stRulePea;   //周界检测与绊线配置
	SDK_OSC_RULE_S stRuleOSC; //物品盗移、滞留，非法停车配置
	SDK_AVD_RULE_S stRuleAVD;//异常视频信号诊断配置
	SDK_CPC_RULE_S stRuleCPC; //人头计数算法配置
};


//一个通道的智能分析配置
struct SDK_ANALYSECONFIG
{
	bool         bEnable;      //是否启用视频分析功能
	int          moduleType;   //使用的那种算法模块
	SDK_EventHandler hEvent;  //联动事件
	SDK_RULECONFIG   stRuleConfig; //各种算法的规则配置
};

//所有通道的智能分析配置
struct SDK_ANALYSECONFIG_ALL
{
	SDK_ANALYSECONFIG vAnalyzeAll[NET_MAX_CHANNUM];
};

//智能分析能力
struct SDK_ANALYZEABILITY
{
	UINT uIntelPEA; //智能PEA支持，位对应通道
	UINT uAlgorithmPEA;//PEA支持的算法类型，例如拌线
	UINT uIntelOSC; //智能OSC支持，位对应通道
	UINT uAlgorithmOSC;//OSC支持的算法类型
	UINT uIntelAVD; //智能AVD支持，位对应通道
	UINT uAlgorithmAVD;//AVD支持的算法类型
	UINT uIntelCPC; //人流量记数支持，位对应通道
	UINT uAlgorithmCPC;//CPC支持的算法类型
};



///< 动态检测设置
struct SDK_MOTIONCONFIG
{
	bool bEnable;							// 动态检测开启 
	int iLevel;								// 灵敏度 
	unsigned int mRegion[NET_MD_REGION_ROW];			// 区域，每一行使用一个二进制串 	
	SDK_EventHandler hEvent;					// 动态检测联动 
};

/// 全通道动态检测配置
struct SDK_MOTIONCONFIG_ALL
{
	SDK_MOTIONCONFIG vMotionDetectAll[NET_MAX_CHANNUM];
};

///< 遮挡检测配置
struct SDK_BLINDDETECTCONFIG
{
	bool	bEnable;		///< 遮挡检测开启
	int		iLevel;			///< 灵敏度：1～6
	SDK_EventHandler hEvent;	///< 遮挡检测联动
};

/// 全通道遮挡检测配置
struct SDK_BLINDDETECTCONFIG_ALL
{
	SDK_BLINDDETECTCONFIG vBlindDetectAll[NET_MAX_CHANNUM];
};

///< 基本事件结构
struct SDK_VIDEOLOSSCONFIG
{
	bool bEnable;			///< 使能
	SDK_EventHandler hEvent;	///< 处理参数
};

/// 所有通道的基本时间结构
struct SDK_VIDEOLOSSCONFIG_ALL
{
	SDK_VIDEOLOSSCONFIG vGenericEventConfig[NET_MAX_CHANNUM];
};

///< 报警输入配置
struct SDK_ALARM_INPUTCONFIG
{
	bool	bEnable;		///< 报警输入开关
	int		iSensorType;	///< 传感器类型常开 or 常闭
	SDK_EventHandler hEvent;	///< 报警联动
};

///< 所有通道的报警输入配置
struct SDK_ALARM_INPUTCONFIG_ALL
{
	SDK_ALARM_INPUTCONFIG vAlarmConfigAll[NET_MAX_CHANNUM];
};

///< 网路报警
struct SDK_NETALARMCONFIG
{
	bool bEnable;			///< 使能
	SDK_EventHandler hEvent;	///< 处理参数
};

/// 所有通道的网路报警结构
struct SDK_NETALARMCONFIG_ALL
{
	SDK_NETALARMCONFIG vNetAlarmConfig[NET_MAX_CHANNUM];
};

///< 本地报警输出配置
struct SDK_AlarmOutConfig
{
	int nAlarmOutType;		///< 报警输出类型: 配置,手动,关闭
	int nAlarmOutStatus;    ///< 报警状态: 0:打开 1;闭合
};

///< 硬盘容量不足事件结构
struct SDK_StorageLowSpaceConfig
{
	bool bEnable;
	int iLowerLimit;		///< 硬盘剩余容量下限, 百分数
	SDK_EventHandler hEvent;	///< 处理参数
	bool bRecordTimeEnable;
	int iRecordTime;		///<录像天数
};

///< 所有通道的报警输出配置
struct SDK_AlarmOutConfigAll
{
	SDK_AlarmOutConfig vAlarmOutConfigAll[NET_MAX_CHANNUM];
};

/// 所有通道的解码器地址设置V2版本
struct SDK_AbilitySerialNo
{
	char serialNo[NET_MAX_SERIALNO_LENGTH];
	char productType[NET_MAX_SERIALNO_LENGTH];
};

///< 驱动器信息结构
struct SDK_DriverInformation 
{
	int		iDriverType;		///< 驱动器类型
	bool	bIsCurrent;			///< 是否为当前工作盘
	unsigned int	uiTotalSpace;		///< 总容量，MB为单位
	unsigned int	uiRemainSpace;		///< 剩余容量，MB为单位
	int		iStatus;			///< 错误标志，文件系统初始化时被设置
	int		iLogicSerialNo;				///< 逻辑序号
	SDK_SYSTEM_TIME  tmStartTimeNew;		///< 新录像时间段的开始时间
	SDK_SYSTEM_TIME	 tmEndTimeNew;			///< 新录像时间段的结束时间
	SDK_SYSTEM_TIME	 tmStartTimeOld;		///< 老录像时间段的开始时间
	SDK_SYSTEM_TIME	 tmEndTimeOld;			///< 老录像时间段的结束时间
};
enum
{
	SDK_MAX_DRIVER_PER_DISK = 2,	///< 每个磁盘最多的分区数
	SDK_MAX_DISK_PER_MACHINE = 8,	///< 最多支持8块硬盘
};
//硬盘管理
struct SDK_STORAGEDISK
{
	int		iPhysicalNo;
	int		iPartNumber;		// 分区数
	SDK_DriverInformation diPartitions[SDK_MAX_DRIVER_PER_DISK];
};

struct SDK_StorageDeviceInformationAll
{
	int iDiskNumber;
	SDK_STORAGEDISK vStorageDeviceInfoAll[SDK_MAX_DISK_PER_MACHINE];
};

/// 存储设备控制类型
enum SDK_StorageDeviceControlTypes
{
	SDK_STORAGE_DEVICE_CONTROL_SETTYPE,		///< 设置类型
	SDK_STORAGE_DEVICE_CONTROL_RECOVER,		///< 恢复错误
	SDK_STORAGE_DEVICE_CONTROL_PARTITIONS,	///< 分区操作
	SDK_STORAGE_DEVICE_CONTROL_CLEAR,		///< 清除操作
	SDK_STORAGE_DEVICE_CONTROL_NR,
};

/// 清除磁盘数据类型
enum SDK_StorageDeviceClearTypes
{
	SDK_STORAGE_DEVICE_CLEAR_DATA,			///< 清除录像数据
	SDK_STORAGE_DEVICE_CLEAR_PARTITIONS,	///< 清除分区
	SDK_STORAGE_DEVICE_CLEAR_NR,
};

/// 驱动器类型
enum SDK_FileSystemDriverTypes
{
	SDK_DRIVER_READ_WRITE	= 0,	///< 读写驱动器
	SDK_DRIVER_READ_ONLY	= 1,	///< 只读驱动器
	SDK_DRIVER_EVENTS		= 2,	///< 事件驱动器
	SDK_DRIVER_REDUNDANT	= 3,	///< 冗余驱动器
	SDK_DRIVER_SNAPSHOT		= 4,	///< 快照驱动器
	SDK_DRIVER_TYPE_NR		= 5,	///< 驱动器类型个数
	SDK_DRIVER_UNUSED		= 0xff,	///< 没有使用的驱动器结构
};

/// 存储设备控制
struct SDK_StorageDeviceControl
{
	int iAction;	///< 见enum SDK_StorageDeviceControlTypes
	int iSerialNo;	///< 磁盘序列号
	int iPartNo;    ///< 分区号
	int iType;		///< enum SDK_StorageDeviceClearTypes或者SDK_FileSystemDriverTypes
	int iPartSize[2/*MAX_DRIVER_PER_DISK*/];	///< 各个分区的大小
};

/// 设备类型
enum SDK_DeviceType
{
	SDK_DEVICE_TYPE_DVR,	///< 普通DVR设备
	SDK_DEVICE_TYPE_NVS,	///< NVS设备
	SDK_DEVICE_TYPE_IPC,	///< IPC设备
	SDK_DEVICE_TYPE_HVR,	///<混合dvr
	SDK_DEVICE_TYPE_IVR,	///<智能dvr
	SDK_DEVICE_TYPE_MVR,	///<车载dvr
	SDK_DEVICE_TYPE_NR
};

/// 设备信息
typedef struct _VIDEONET_DEVICEINFO
{
	char sSoftWareVersion[64];	///< 软件版本信息
	char sHardWareVersion[64];	///< 硬件版本信息
	char sWebVersion[64];	 ///< 页面版本信息
	SDK_SYSTEM_TIME tmBuildTime;///< 软件创建时间
	char sSerialNumber[64];	 ///< 设备序列号
	int byChanNum;	 ///< 视频输入通道数
	int iVideoOutChannel;	 ///< 视频输出通道数
	int byAlarmInPortNum;	 ///< 报警输入通道数
	int byAlarmOutPortNum;	 ///< 报警输出通道数
	int iTalkInChannel;	 ///< 对讲输入通道数
	int iTalkOutChannel;	 ///< 对讲输出通道数
	int iExtraChannel;	 ///< 扩展通道数
	int iAudioInChannel;	 ///< 音频输入通道数
	int iCombineSwitch;	 ///< 组合编码通道分割模式是否支持切换
	int iDigChannel;	 ///<数字通道数
	unsigned int uiDeviceRunTime;	///<系统运行时间
	SDK_DeviceType deviceTye;	///设备类型
	char sHardWare[64];	 ///<设备型号
	char uUpdataTime[20];	 ///<更新日期 例如 2018-09-03 16:26:56
	unsigned int uUpdataType;	///<更新内容
	char sDeviceModel[16];       //设备型号(底层库从加密里获得，sHardWare针对多个设备用同一个程序这种情况区分不了) 
	int nLanguage;//国家的语言ID,0英语 1中文 2中文繁体 3韩语 4德语 5葡萄牙语 6俄语
	char szOnvifModel[32];
	char sProtocol[16];
	char res[112];
}VIDEONET_DEVICEINFO,*LPVIDEONET_DEVICEINFO;

//主动服务回调数据
struct VIDEONET_ACTIVEREG_INFO
{
	char deviceSarialID[64];//设备序列号，如果大于64位则赋值0
	VIDEONET_DEVICEINFO deviceInfo;//设备信息
	char IP[IP_SIZE];   //外网IP
};
///< 自动维护设置
struct SDK_AutoMaintainConfig
{
	int iAutoRebootDay;				///< 自动重启设置日期
	int iAutoRebootHour;			///< 重启整点时间	[0, 23]	
	int iAutoDeleteFilesDays;		///< 自动删除文件时间[0, 30]
};

/// 默认配置种类
enum SDK_DefaultConfigKinds
{
	SDK_DEFAULT_CFG_GENERAL,			// 普通配置
	SDK_DEFAULT_CFG_ENCODE,				// 编码配置
	SDK_DEFAULT_CFG_RECORD,				// 录像配置
	SDK_DEFAULT_CFG_NET_SERVICE,		// 网络服务
	SDK_DEFAULT_CFG_NET_COMMON,			// 通用网络
	SDK_DEFAULT_CFG_ALARM,				// 报警
	SDK_DEFAULT_CFG_PTZCOMM,			// 云台，串口
	SDK_DEFAULT_CFG_USERMANAGER,		// 用户管理
	SDK_DEFAULT_CFG_PREVIEW,			// 预览配置
	SDK_DEFAULT_CFG_CAMERA_PARAM,            // 网络摄像头配置
	SDK_DEFAULT_CFG_END,
};

/// 恢复的默认配置种类
struct SDK_SetDefaultConfigTypes
{
	bool vSetDefaultKinds[SDK_DEFAULT_CFG_END];
}; 


typedef struct VIDEONET_CLIENTINFO{
	int nChannel;	//通道号
	int nStream;	//0表示主码流，为1表示子码流
	int nMode;		//0：TCP方式,1：UDP方式,2：多播方式,3 - RTP方式，4-音视频分开(TCP)
	int nComType;	//只对组合编码通道有效, 组合编码通道的拼图模式
}*LPVIDEONET_CLIENTINFO;


#define		RECORDE_FILE_LENGTH		108
enum SDK_File_Type
{
	SDK_RECORD_ALL = 0,
	SDK_RECORD_ALARM = 1, //外部报警录像
	SDK_RECORD_DETECT,	  //视频侦测录像
	SDK_RECORD_REGULAR,	  //普通录像
	SDK_RECORD_MANUAL,	  //手动录像
	SDK_PIC_ALL = 10,
	SDK_PIC_ALARM,		  //外部报警录像
	SDK_PIC_DETECT,		  //视频侦测录像
	SDK_PIC_REGULAR,      //普通录像
	SDK_PIC_MANUAL,       //手动录像
	SDK_TYPE_NUM,
	SDK_PIC_FACE = 20,		//人脸
	SDK_PIC_CARNO,			//车牌
	SDK_PIC_WIFI,			//wifi探针
	SDK_FACE_QUERY_RECORD,  //人脸搜索录像
};

//查询录像条件
struct VIDEONET_FINDINFO
{
	int nChannelN0;			//通道号
	int nFileType;			//文件类型, 见SDK_File_Type
	VIDEONET_TIME startTime;	//开始时间
	VIDEONET_TIME endTime;	//结束时间
	char szFileName[32];		//文件名，为空的话，系统处理，有值，系统采用
};

//录像文件返回结构体
struct VIDEONET_FILE_DATA 
{
	int ch;						//通道号
	int size;					//文件大小
	char sFileName[RECORDE_FILE_LENGTH];		///< 文件名
	SDK_SYSTEM_TIME stBeginTime;	///< 文件开始时间
	SDK_SYSTEM_TIME stEndTime;		///< 文件结束时间
};

/**************************************图片查找*************************************************************/

#define		CARDNUM_LEN			40
#define		MAX_LICENSE_LEN		16
#define		MAX_FACE_PIC_NUM	30

//图片检索生成项
enum JVT_VCA_OPERATE_TYPE
{  
	JVT_VCA_LICENSE_TYPE       = 0x1,	//车牌号码
	JVT_VCA_PLATECOLOR_TYPE    = 0x2,	//车牌颜色
	JVT_VCA_CARDNO_TYPE        = 0x4,	//卡号
	JVT_VCA_PLATETYPE_TYPE     = 0x8,	//车牌类型
	JVT_VCA_LISTTYPE_TYPE      = 0x10,	//车牌名单类型
	JVT_VCA_INDEX_TYPE         = 0x20,	//数据流水号
	JVT_VCA_OPERATE_INDEX_TYPE = 0x40	//操作数
};

//车辆类型
enum JVT_VCA_VEHICLE_TYPE
{
	JVT_VCA_OTHER_TYPE          = 0x1,	//其它车型
	JVT_VCA_SMALLCAR_TYPE       = 0x2,  //小型车
	JVT_VCA_BIGCAR_TYPE         = 0x4,	//大型车 
	JVT_VCA_BUS_TYPE            = 0x8,  //客车
	JVT_VCA_TRUCK_TYPE          = 0x10,	//货车
	JVT_VCA_CAR_TYPE            = 0x20,	//轿车
	JVT_VCA_MINIBUS_TYPE        = 0x40,	//面包车
	JVT_VCA_SMALL_TRUCK_TYPE    = 0x80	//小货车
};

//图片查询条件
typedef struct SDK_PICTURE_FINDINFO
{
	DWORD            dwSize;		//结构体大小
	LONG             lChannel;		//通道号
	BYTE             byFileType;	//查找图片类型：见SDK_File_Type 20-人脸，21-车牌，22-探针信息，0xff-全部类型
	BYTE             byNeedCard;	//是否需要卡号
	BYTE             byProvince;	//省份索引号：0-保留，1-澳，2-京
	BYTE             sCardNum[CARDNUM_LEN];  //卡号
	SDK_SYSTEM_TIME     startTime;				//查找图片的开始时间
	SDK_SYSTEM_TIME     endTime;				//查找图片的结束时间
	DWORD            dwTrafficType;				//图片检索生成项
	DWORD            dwVehicleType;				//车辆类型			
	DWORD            dwIllegalType;				//违规检测类型
	BYTE             byLaneNo;					//车道号
	BYTE             bySubHvtType;				//混行检测查找子类型：0- 全部， 1- 机动车(机动车子类型中支持车牌检索、省份检索)，2-非机动车，3- 行人 

	char             sLicense[MAX_LICENSE_LEN];	//车牌号码（byFileType为车牌侦测时有效）
	BYTE             byRegion;					//区域索引值：0- 保留，1- 欧洲(Europe Region)，2- 俄罗斯(Russian Region)，3- 欧洲&俄罗斯(EU&CIS)，0xff- 所有 
	BYTE             byCountry;					//国家索引值
	float			 similarity;			//相似度
	int				 sorttype;				//排序方式 0按相似度排序  1按时间排序(从小到大)   2按时间排序(从大到小)
	char			 filepath[128];			//图片完整路径(包含文件名)
	BYTE             byRes3[20];					//保留，置为0
}*LPSDK_PICTURE_FINDINFO;

////区域框参数结构体
//typedef struct NET_VCA_RECT
//{
//	float   fX;  
//	float   fY;  
//	float   fWidth;  
//	float   fHeight;
//}*LPNET_VCA_RECT;
////人脸侦测抓图附加信息结构体
//typedef struct NET_FACE_EXTRA_INFO
//{
//	NET_VCA_RECT    struVcaRect[MAX_FACE_PIC_NUM];
//	BYTE            byRes[64];
//}*LPNET_DVR_FACE_EXTRA_INFO;
//
////人脸侦测抓图附加信息结构体
//typedef union PIC_EXTRA_INFO_UNION
//{
//	BYTE                       byUnionLen[544];
//	NET_FACE_EXTRA_INFO    struFaceExtraInfo;
//}*LPPIC_EXTRA_INFO_UNION;


//图片返回数据
typedef struct SDK_VIDEONET_PICTURE_DATA
{  
	int					nChannel;					//通道号
	char				sFileName[RECORDE_FILE_LENGTH];				//图片名称
	SDK_SYSTEM_TIME		netTime;					//图片的时间
	DWORD				dwFileSize;					//图片的大小
	char				sCardNum[CARDNUM_LEN];		//卡号
	BYTE				byPlateColor;				//车牌颜色
	BYTE				byVehicleLogo;				//汽车品牌
	BYTE				byFileType;					//文件类型
	BYTE				byRecogResult;				//车辆识别结果:0- 未知，1- 客车，2- 货车，3- 轿车，4- 面包车，5- 小货车，6- 行人，7- 二轮车，8- 三轮车，9- SUV/MPV，10- 中型客车，11- 机动车，12- 非机动车
	char				sLicense[MAX_LICENSE_LEN];	//
	BYTE				byEventSearchStatus;		//
	char				sIpV4[16];					//IP地址
	BYTE				sIpV6[128];					//
	WORD				wPort;						//端口号
	BYTE				byRes[256];					//保留
	BYTE*				pPicExtraInfo;				//图片附件信息
	DWORD				dwExtraLen;					//附加信息长度
}*LPSDK_VIDEONET_PICTURE_DATA;
/***************************************************************************************************************************/
//兼容linuxSDK结构信息
//图片查询条件
typedef struct PICTURE_FINDINFO
{
	int              lChannel;				//通道号:掩码的方式
	int				 sorttype;				//排序方式 0按相似度排序  1按时间排序(从小到大)   2按时间排序(从大到小)
	int              byFileType;			//查找图片类型：见SDK_File_Type 20-人脸，21-车牌，22-探针信息，0xff-全部类型
	float			 similarity;			//相似度
	SDK_SYSTEM_TIME  startTime;				//查找图片的开始时间
	SDK_SYSTEM_TIME  endTime;				//查找图片的结束时间
	char			 filepath[128];			//图片完整路径(包含文件名)
}*LPPICTURE_FINDINFO;

typedef struct PICTURE_DATA
{
	short			 index;
	short			 channel;				//图片或者录像所属通道号
	int              size;					//图片大小或者录像时间,图片大小以字节为单位
	float			 similarity;			//相似度
	SDK_SYSTEM_TIME  capturetime;			//图片抓拍时间或者录像开始时间
	char			 filepath[128];			//图片或录像完整路径(包含文件名)
}*LPPICTURE_DATA;

//图片查询返回
typedef struct VIDEONET_PICTURE_DATA
{
	int              photonum;				//图片数目
	PICTURE_DATA	 photodata[5000];			
}*LPVIDEONET_PICTURE_DATA;

//回放动作
enum SEDK_PlayBackAction
{
	SDK_PLAY_BACK_PAUSE,		/*<! 暂停回放 */
	SDK_PLAY_BACK_CONTINUE,		/*<! 继续回放 */
	SDK_PLAY_BACK_SEEK,			/*<! 回放定位，时间s为单位 */
	SDK_PLAY_BACK_FAST,	        /*<! 加速回放 */
	SDK_PLAY_BACK_SLOW,	        /*<! 减速回放 */
	SDK_PLAY_BACK_SEEK_PERCENT, /*<! 回放定位百分比 */
};

//按时间段查询
struct SDK_SearchByTime
{
	int nHighChannel;			///< 33~64录像通道号掩码
	int nLowChannel;			///< 1~32录像通道号掩码
	int nFileType;              ///< 文件类型, 见SDK_File_Type
	SDK_SYSTEM_TIME stBeginTime;	    ///< 查询开始时间
	SDK_SYSTEM_TIME stEndTime;		///< 查询结束时间
	int    iSync;               ///< 是否需要同步
};

//每个通道的录像信息
struct SDK_SearchByTimeInfo
{
	int iChannel;			    ///< 录像通道号
	///< 录像记录用720个字节的5760位来表示一天中的1440分钟
	///< 0000:无录像 0001:F_COMMON 0002:F_ALERT 0003:F_DYNAMIC 0004:F_CARD 0005:F_HAND
	unsigned char cRecordBitMap[720];
};

struct SDK_SearchByTimeResult
{
	int nInfoNum;										 ///< 通道的录像记录信息个数
	SDK_SearchByTimeInfo ByTimeInfo[NET_MAX_CHANNUM];    ///< 通道的录像记录信息
};

//报警信息
typedef struct SDK_ALARM_INFO
{
	int nChannel;
	int iEvent;
	int iStatus;
	SDK_SYSTEM_TIME SysTime;
	char pExtInfo[128]; //附加信息，发送者和接收者对各种报警类型进行格式约定 //by zjh add 20170830
}SDK_AlarmInfo;

/// 日志查询条件
struct SDK_LogSearchCondition
{
	int nType;	///< 日志类型
	int iLogPosition;			///< 从上次查询的结束时的日志指针
	SDK_SYSTEM_TIME stBeginTime;	///< 查询日志开始时间
	SDK_SYSTEM_TIME stEndTime;		///< 查询日志结束时间
};


struct SDK_LogItem
{
	char sType[24];	///< 日志类型
	char sUser[32];	///< 日志用户
	char sData[68];	///< 日志数据
	SDK_SYSTEM_TIME stLogTime;	///< 日志时间
	int iLogPosition;			///< 从上次查询的结束时的日志指针
};

//日志返回信息
struct SDK_LogList
{
	int iNumLog;
	SDK_LogItem Logs[NET_MAX_RETURNED_LOGLIST];
};

/// 语音对讲格式
struct SDK_AudioInFormatConfigAll
{
	SDK_AudioInFormatConfig vAudioInFormatConfig[SDK_AUDIO_ENCODE_TYPES_NR];
};

/// 告警状态
struct SDK_DVR_ALARMSTATE
{
	int iVideoMotion; ///< 移动侦测状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
	int iVideoBlind; ///< 视频遮挡状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
	int iVideoLoss;	///< 视频丢失状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
	int iAlarmIn;	///< 告警输入状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
	int iAlarmOut;	///< 告警输出状态,用掩码表示通道号,bit0代表通道一,以此类推 1: 有告警 0: 无告警
};

// 通道状态
struct SDK_DVR_CHANNELSTATE
{
	bool bRecord; ///< 是否正在录像
	int iBitrate;	///< 当前码率
};

// DVR工作状态
struct SDK_DVR_WORKSTATE
{
	SDK_DVR_CHANNELSTATE vChnState[NET_MAX_CHANNUM];
	SDK_DVR_ALARMSTATE vAlarmState;
};


/// 按键值, 不能随便更改
enum SDK_NetKeyBoardValue
{
	SDK_NET_KEY_0, SDK_NET_KEY_1, SDK_NET_KEY_2, SDK_NET_KEY_3, SDK_NET_KEY_4, SDK_NET_KEY_5, SDK_NET_KEY_6, SDK_NET_KEY_7, SDK_NET_KEY_8, SDK_NET_KEY_9,
	SDK_NET_KEY_10, SDK_NET_KEY_11, SDK_NET_KEY_12, SDK_NET_KEY_13, SDK_NET_KEY_14, SDK_NET_KEY_15, SDK_NET_KEY_16, SDK_NET_KEY_10PLUS,SDK_NET_KEY_DIGIT,
	SDK_NET_KEY_UP = 20,     // 上或者云台向上
	SDK_NET_KEY_DOWN,        // 下或者云台向下
	SDK_NET_KEY_LEFT,        // 左或者云台向左
	SDK_NET_KEY_RIGHT,       // 右或者云台向右
	SDK_NET_KEY_SHIFT, 
	SDK_NET_KEY_PGUP,        // 上一页
	SDK_NET_KEY_PGDN,        // 下一页
	SDK_NET_KEY_RET,         // 确认
	SDK_NET_KEY_ESC,         // 取消或退出
	SDK_NET_KEY_FUNC,        // 切换输入法
	SDK_NET_KEY_PLAY,        // 播放/暂停
	SDK_NET_KEY_BACK,        // 倒放
	SDK_NET_KEY_STOP,        // 停止
	SDK_NET_KEY_FAST,        // 快放
	SDK_NET_KEY_SLOW,        // 慢放
	SDK_NET_KEY_NEXT,        // 下一个文件
	SDK_NET_KEY_PREV,        // 上一个文件
	SDK_NET_KEY_REC = 40,    // 录像设置
	SDK_NET_KEY_SEARCH,      // 录像查询
	SDK_NET_KEY_INFO,        // 系统信息
	SDK_NET_KEY_ALARM,       // 告警输出
	SDK_NET_KEY_ADDR,        // 遥控器地址设置
	SDK_NET_KEY_BACKUP,      // 备份
	SDK_NET_KEY_SPLIT,       // 画面分割模式切换，每按一次切换到下一个风格模式
	SDK_NET_KEY_SPLIT1,      // 单画面
	SDK_NET_KEY_SPLIT4,      // 四画面
	SDK_NET_KEY_SPLIT8,      // 八画面
	SDK_NET_KEY_SPLIT9,      // 九画面
	SDK_NET_KEY_SPLIT16,     // 16画面
	SDK_NET_KEY_SHUT,        // 关机
	SDK_NET_KEY_MENU,        // 菜单
	SDK_NET_KEY_SPLIT25,	// 25画面	
	SDK_NET_KEY_SPLIT36,     // 36画面
	SDK_NET_KEY_PTZ = 60,    // 进入云台控制模式
	SDK_NET_KEY_TELE,        // 变倍减
	SDK_NET_KEY_WIDE,        // 变倍加
	SDK_NET_KEY_IRIS_SMALL,  // 光圈增
	SDK_NET_KEY_IRIS_LARGE,  // 光圈减
	SDK_NET_KEY_FOCUS_NEAR,  // 聚焦远
	SDK_NET_KEY_FOCUS_FAR,   // 聚焦近
	SDK_NET_KEY_BRUSH,       // 雨刷
	SDK_NET_KEY_LIGHT,       // 灯光
	SDK_NET_KEY_SPRESET,     // 设置预置点
	SDK_NET_KEY_GPRESET,     // 转至预置点
	SDK_NET_KEY_DPRESET,     // 清除预置点 
	SDK_NET_KEY_PATTERN,     // 模式
	SDK_NET_KEY_AUTOSCAN,    // 自动扫描开始结束
	SDK_NET_KEY_AUTOTOUR,    // 自动巡航
	SDK_NET_KEY_AUTOPAN,     // 线扫开始/结束
};

/// 按键状态
enum SDK_NetKeyBoardState
{
	SDK_NET_KEYBOARD_KEYDOWN,	// 按键按下
	SDK_NET_KEYBOARD_KEYUP,		// 按键松开
};

struct SDK_NetKeyBoardData
{
	int iValue;
	int iState;
};

// 升级信息获取
struct SDK_UpgradeInfo
{
	char szSerial[64];
	char szHardware[64];
	char szVendor[64];
	unsigned int uiLogoArea[2];
};

/// 网络报警
struct SDK_NetAlarmInfo
{
	int iEvent;  //目前未使用
	int iState;   //每bit表示一个通道,bit0:第一通道,0-无报警 1-有报警, 依次类推
};

enum SERIAL_TYPE
{
	RS232 = 0,
	RS485 = 1,
};


enum MEDIA_PACK_TYPE
{
	FILE_HEAD =	0,	    		// 文件头
	VIDEO_I_FRAME = 1,			// 视频I帧
	VIDEO_B_FRAME =	2,			// 视频B帧
	VIDEO_P_FRAME = 3,			// 视频P帧
	VIDEO_BP_FRAME = 4,			// 视频BP帧
	VIDEO_BBP_FRAME	= 5,		// 视频B帧B帧P帧
	VIDEO_J_FRAME = 6,			// 图片帧
	AUDIO_PACKET = 10,			// 音频包
};

typedef struct
{
	int		nPacketType;				// 包类型,见MEDIA_PACK_TYPE
	char*	pPacketBuffer;				// 缓存区地址
	unsigned int	dwPacketSize;				// 包的大小

	// 绝对时标
	int		nYear;						// 时标:年		
	int		nMonth;						// 时标:月
	int		nDay;						// 时标:日
	int		nHour;						// 时标:时
	int		nMinute;					// 时标:分
	int		nSecond;					// 时标:秒
	unsigned int 	dwTimeStamp;					// 相对时标低位，单位为毫秒
	unsigned int	dwTimeStampHigh;        //相对时标高位，单位为毫秒
	unsigned int   dwFrameNum;             //帧序号
	unsigned int   dwFrameRate;            //帧率
	unsigned short uWidth;              //图像宽度
	unsigned short uHeight;             //图像高度
	unsigned int uEncoderType;			//编码类型
	unsigned int       Reserved[5];     //保留
} PACKET_INFO_EX;


struct SDK_OEMInfo
{
	int nOEMID;                     //OEM ID
	char sCompanyName[NET_MAX_USERNAME_LENGTH]; //公司名
	char sTel[NET_MAX_USERNAME_LENGTH];         //电话
	char sAddr[NET_MAX_USERNAME_LENGTH];        //地址
};
typedef struct __TransComChannel//透明窗口
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

//摄象机参数.....

//曝光配置
struct SDK_ExposureCfg
{
	int  level;    //曝光等级
	unsigned int leastTime;//自动曝光时间下限或手动曝光时间，单位微秒
	unsigned int mostTime; //自动曝光时间上限，单位微秒
	int levelTime;//曝光时间 单位微妙
};

//增益配置
struct SDK_GainCfg
{
	int gain;    //自动增益上限(自动增益启用)或固定增益值
	int autoGain;//自动增益是否启用，0:不开启  1:开启
};

//网络摄像机配置
struct SDK_CameraParam
{
	unsigned int whiteBalance;         //白平衡
	unsigned int dayNightColor;        //日夜模式，取值有彩色、自动切换和黑白
	int elecLevel;             //参考电平值
	unsigned int apertureMode;          //自动光圈模式
	unsigned int BLCMode;               //背光补偿模式
	SDK_ExposureCfg exposureConfig;//曝光配置
	SDK_GainCfg     gainConfig;    //增益配置

	unsigned int PictureFlip;		//图片上下翻转
	unsigned int PictureMirror;	//图片左右翻转(镜像)
	unsigned int RejectFlicker;	//日光灯防闪功能
	unsigned int EsShutter;		//电子慢快门功能

	int ircut_mode;		//IR-CUT切换 0 = 红外灯同步切换 1 = 自动切换

	int dnc_thr;			//日夜转换阈值
	int ae_sensitivity;	//ae灵敏度配置

	int Day_nfLevel;		//noise filter 等级，0-5,0不滤波，1-5 值越大滤波效果越明显
	int Night_nfLevel;
	int Ircut_swap;		//ircut 正常序= 0        反序= 1
	int BLCValue;       //背光补偿值
	int PicWDRLevel;	//宽动态
};

//所有摄象机配置
struct SDK_AllCameraParam
{
	SDK_CameraParam vCameraParamAll[NET_MAX_CHANNUM];   //所有的通道
};

//曝光能力级
struct SDK_CameraAbility
{
	int  count;      //支持曝光速度数量
	unsigned int speeds[CAMERAPARA_MAXNUM]; //曝光速度
	int  status;     //工作状态  >= 0 正常    < 0 异常
	int  elecLevel;  //参考电平值
	int  luminance;  //平均亮度
	char pVersion[64];//xm 2a版本
	char reserve[32];//保留
};

//本地播放控制
enum SDK_LoalPlayAction
{
	SDK_Local_PLAY_PAUSE,		/*<! 暂停播放 */
	SDK_Local_PLAY_CONTINUE,		/*<! 继续正常播放 */
	SDK_Local_PLAY_FAST,	        /*<! 加速播放 */
	SDK_Local_PLAY_SLOW,	        /*<! 减速播放 */	
	
};

//短信配置
struct SDK_NetShortMsgCfg
{
	bool bEnable;       //发送手机短信的功能是否启用
	char pDesPhoneNum[SDK_MAX_RECIVE_MSG_PHONE_COUNT][16];
	int  sendTimes;     //需要向每个手机发送多少次短信
};
//手机彩信配置
struct SDK_NetMultimediaMsgCfg
{
	bool bEnable;				// 发送手机彩信的功能是否启用
	char pDesPhoneNum[SDK_MAX_RECIVE_MSG_PHONE_COUNT][16]; //接收彩信的手机号，现支持3个手机号
	char pGateWayDomain[40];	// 网关地址，域名或IP
	int  gateWayPort;			// 网关端口
	char pMmscDomain[40];		// 彩信服务器地址，IP或域名
	int  mmscPort;				// 彩信服务器端口号
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
enum UploadDataType  //上传数据类型
{
	VEHICLE=0,//车载信息
	SDK_RECORD_STATE,//录像状态
	SDK_DIGITCHN_STATE,	//数字通道连接状态
	SDK_TITLE_INFO,		//通道标题
};
//车载相关************************************************************************
//车辆状态
enum SDK_CAR_STATUS_TYPE
{
	SDK_CAR_WORKING,             //是否在运行
	SDK_CAR_LIGHT_LEFT_TURN,     //左转灯是否点亮
	SDK_CAR_LIGHT_RIGHT_TURN,    //右转灯是否点亮
	SDK_CAR_DOOR_LEFT_FRONT,     //左前门是否打开
	SDK_CAR_DOOR_RIGHT_FRONT,    //右前门是否打开
	SDK_CAR_DOOR_LEFT_BACK,      //左后门是否打开
	SDK_CAR_DOOR_RIGHT_BACK,     //右后门是否打开
	SDK_CAR_DOOR_BACK,           //后门是否打开
	SDK_CAR_BRAKE,               //是否踩刹车
	SDK_CAR_URGENCY_ALARM,       //紧急报警
	SDK_CAR_STATUS_NR, //状态种类数目
};

//外部输入类型
enum SDK_IO_INPUT_TYPE
{
	SDK_LOCAL_ALARM_INPUT,//本地报警输入
	SDK_RS232_INPUT,      //通过232串口输入
	SDK_RS485_INPUT,      //通过485串口输入
};

//外部信息输入与车辆状态的对应关系
struct SDK_CarStatusExchange
{
	int  statusType; //哪一种车辆状态，比如左转灯
	bool bExist;     //是否有该种状态的信息输入，根据车辆的实际情况进行设置
	bool bEnable;    //是否检测该种状态
	int  inputType;  //该种状态对应的信息输入类型，从IO_INPUT_TYPE枚举的值中取
	int  addr;       //地址，比如是本地报警输入口一对应0，输入口二对应1
	int  sensorType; //常开(NO)或常闭(NC)，当inputType是本地报警输入时有效
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

	int timeStartDelay;		//单位:分钟
	int timeCloseDelay;		//单位:分钟
};
enum SDK_network_media {
	SDK_NM_WIRED = 0,  //有线网卡
	SDK_NM_WLAN,       //Wifi
	SDK_NM_3G,         //3G网卡
	SDK_NM_NR,    //种类数
};
//网络连接优先级
typedef struct SDK_tagNetLinkOrder
{
	int netType;  //取值是network_media类型的
	int netOrder; //数字越小，优先级越高,0是最高优先级
}SDK_NetLinkOrder;
//网络优先级
struct SDK_NetOrderConfig
{
	bool         bEnable;        //是否设置网络优先级
	int          netCount;       //网络类型数目
	SDK_NetLinkOrder pNetOrder[SDK_NM_NR];//网络优先级
	SDK_NetLinkOrder pReserve[7-SDK_NM_NR];//给新的网络类型预留
};
///网络优先级能力
struct SDK_NetOrderFunction
{
	bool bNetOrder;
};
#define  MAX_CAR_INFOR 24
/// 车载牌号
struct  SDK_CarPlates
{
	char sPlateName[MAX_CAR_INFOR];
};
enum NET_ISP
{
	ISP_AUTO, //自动选择
	ISP_TELCOM, //电信
	ISP_UNIONCOM, //联通
	ISP_CNC,//网通
	ISP_MOBILE,//移动，铁通
	ISP_USER,//自定义
};
//网络平台信息设置
typedef struct SDK_LocalSdkNetPlatformConfig
{
	int Enable;
	int nISP;                          ///参见NET_ISP
	char sServerName[32];
	char ID[32];
	char sUserName[32];
	char sPassword[32];
	CONFIG_IPAddress HostIP;		///< host ip
	int port;
}SDK_LOCALSDK_NET_PLATFORM_CONFIG;

//GPS校时配置
struct SDK_GPSTimingConfig
{
	bool bEnable;      // 是否启用
	int  timeChange;   // 相对于UTC时间需要改变多少，单位:秒
	int  updatePeriod; // 更新周期  单位:分钟
};
//神眼接警中心系统
struct	SDK_GodEyeConfig
{
	bool	bEnable; 
	char MainSeverName[NET_NAME_PASSWORD_LEN]; //主域名
	int MainPort;	//主端口
	char ExSeverName[NET_NAME_PASSWORD_LEN]; //备用域名
	int ExPort;	//备用端口
};
enum  SDK_DigManagerShowStatus
{
	SDK_DM_SHOW_NONE,
	SDK_DM_SHOW_ALL,
};


//数字通道显示状态
struct SDK_DigitalManagerShow
{
	int  nDigitalManagerShowSta;
};

//NAT传输，MTU值
struct SDK_NatConfig
{
    bool bEnable;
    int nMTU;             // 范围 (100,1400)
	char serverAddr[64];  //云服务的域名或者IP地址。
	int  serverPort;      //云服务的端口;
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
//*** */向设备注册
enum SocketStyle
{
	TCPSOCKET=0,
	UDPSOCKET,	
	SOCKETNR
};


enum SDK_NatStatusType
{
	SDK_NAT_STATUS_DISENABLE,//未开启
	SDK_NAT_STATUS_PROBING,  //正在探测DNS	
	SDK_NAT_STATUS_CONNECTING,//正在连接服务器
	SDK_NAT_STATUS_CONNECTED,//连接成功
};
//nat状态信息
struct SDK_NatStatusInfo
{
	int	iNatStatus;
	char NatInfoCode[64];
};

/// 数字水印配置
struct SDK_WaterMarkConfig
{
	bool	bEnable;		//  开启水印
	char  sKey[8];
	char sUserData[16];
};

struct SDK_WaterMarkConfigAll
{
	SDK_WaterMarkConfig vWaterMarkConfigAll[NET_MAX_CHANNUM];
};

///编码器静态参数
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
	sdk_itemtotalLength = 96,	//2位通道号，20位开始时间，20位结束时间，和两个13位的数据,加冗余
	sdk_maxpack=4,// sdk_maxCPCDataItem/sdk_maxCPCDataReturn
};

struct SDK_CPCDataItem		//人数统计项结构体
{
	int channel;			//对应的通道号
	SDK_SYSTEM_TIME startTime;	//开始时间
	SDK_SYSTEM_TIME endTime;	//结束时间
	int inNum;			//进入人数
	int outNum;			//离开人数
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

/// 录像存储设备类型，以下类型的一种或者多种
struct SDK_RecordStorageType
{
	bool SATA_as;
	bool USB_as;
	bool SD_as;
	bool DVD_as;
};

//VPN结构体
struct SDK_VPNConfig
{
	bool Enable;		///< 是否开启
	CONFIG_IPAddress ServiceIp;						///< 服务器IP地址
	char UserName[NET_NAME_PASSWORD_LEN];		///< 用户名
	char Password[NET_NAME_PASSWORD_LEN];		///< 密码	
	CONFIG_IPAddress addr;		///< 拨号后获得的IP地址
};
//当前VGA分辨率
struct SDK_VGAresolution
{
	int nHeight;
	int nWidth;
};
//支持VGA分辨率列表
struct SDK_VGAResolutionAbility
{
	int vVGANum;
	char vVGAList[VGA_MAXNUM][VGA_NAME_LENGTH];
};

//设备列表(设备搜索的)
struct SDK_NetDevList
{
	int vNetDevNum;
	SDK_CONFIG_NET_COMMON_V2 vNetDevList[DEV_LIST_SHOW];
};

//温州凯能平台
/***用户信息***/ 

struct SDK_CONFIG_KAINENG_USERINFO
{
	char szUserName[16];           //用户姓名：5个汉字或十个字母;
	char szUserAddr[128];           //用户地址：30个汉字或60个字母;
	char szUserAttr[16];           //用户性质：5个汉字或十个字母；

	char szBelongUnit[64];         //归管单位：15个汉字或30个字母;
	char szBelongUnitPhone[16];    //归管单位电话：14位数字；分机用"-" 隔离符;

	char szPoliceUnit[64];         //出警单位：15个汉字或30个字母;
	char szPoliceUnitAddr[128];     //出警单位地址：30个汉字或60个字母;
	char szPoliceUnitPhone[16];    //出警单位电话：14位数字；分机用"-"隔离符;

	char szPolicePhone[4][16];
	char szPolOrCenPhone[2][16];   //警联/中心电话1、2：14位数字；分机用"-" 隔离符;

	char szFTP[64];                //FTP：50个字符；
	char szEMail[64];              //E-Mail: 50个字符；
	CONFIG_IPAddress PoliceIP;            //接警中心IP地址
	int nHttpPort;                 //接警中心IP端口
};

/***设备信息***/
//闲置布防类型枚举
typedef enum SDK_GuardType
{
	 SDK_FORBID = 0,      //禁止
	 SDK_TEN_MIN,         //十分钟
	 SDK_THIRTY_MIN,      //三十分钟
	 SDK_SIXTY_MIN,       //六十分钟
	 SDK_MAX,
}SDK_GUARDTYEP;


struct SDK_CONFIG_KAINENG_DEVINFO
{
	char ProbeNum1;                //条件布防：两个下拉框，每个下拉框从 1号到10号探测器选择 ；默认两个为 <1号探测器>
	char ProbeNum2;                //条件布防：两个下拉框，每个下拉框从 1号到10号探测器选择 ；默认两个为 <1号探测器>	
	char nProbeType;			   //条件：下拉框 可选择3种为 <禁止>  <AND>  <OR>  默认为 <禁止>
	char nGuardType;               //闲置布防, 参照GUARDTYEP

	int AlarmTime;                //警笛开启时间：三位数字从000-999  默认为：180
	int nGuardArea;               //有线防区类型：八位数字，每位最小0最大3，即00000000 到33333333;  默认：00000000；

	char szRemConAddr[4][4];       //遥控器1-4号地址 ：八位16进制字符允许空（即0-9  A-F），默认为空；
	char szLinDevAddr[6][4];       //联运设备地1-6地址：八位16进制字符允许空（即0-9  A-F），默认为空；
	char szProbeAddr[10][4];       //探测器1-10号地址：八位16进制字符允许空（即0-9  A-F），默认为空；

	//定时布撤防
	char szGuardTime[3][9];        //定时布撤防,每组都为char [8] 类型 即00 00 00 00，表达由开始时分到结束时分，不需要年月日期
};

/***联动设置***/
//联动动作枚举
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
	char eLink[10][7];        //联动设置,取值为联动动作枚举
};

//凯能定制，3个界面信息全在这里。
struct SDK_CONFIG_KAINENG_INFO
{
	SDK_CONFIG_KAINENG_USERINFO UserInfo;
	SDK_CONFIG_KAINENG_DEVINFO DevInfo;
	SDK_CONFIG_KAINENG_LINKINFO LinkInfo;
};

//搜索设备协议
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
	int profile; //当前静态编码
	int reserved1[4]; //保留字段
};

/*
==	DVR静态编码能力集，现在3种
==	0 不支持 1 支持baseline 2 支持main profile 4 支持high profile
==  掩码操作
*/
struct SDK_EncStaticParamAbility
{
	unsigned int encStaticParam;
};

//安徽创世C7平台配置
struct SDK_C7PlatformConfig
{
	char pServerAddr[64];//平台地址，IP地址或域名
	int  servPort;       //平台端口
	char pPUID[32];      //PUID
	char pPassword[32];  //密码
	char pStatus[64];    //接入状态，在LocalSDK中是可读可写的，其它地方是只读
	char pResv[60];      //保留
};

///网络键盘
struct SDK_NetKeyboardConfig
{
	bool Enable;		///< 是否开启
	char sTransProtocol[4];	//传输协议
	int ListenPort;		//监听端口
	char sParserProtocol[32];
	int deviceaddr;	//设备地址
};
////// 网络键盘协议
struct SDK_NetKeyboardAbility
{
	//每个协议最多由64个字符组成
	int nTransPNum;
	char vTransProtocol[32][NET_MAX_PTZ_PROTOCOL_LENGTH];
	int nParserNum;
	char vParserProtocol[32][NET_MAX_PTZ_PROTOCOL_LENGTH];
};

//28181协议配置
struct SDK_ASB_NET_VSP_CONFIG
{
	bool		bCsEnable;				//使能标记
	char		szCsIP[64];				//服务器地址	
	short	sCsPort;					//服务器端口
	short	sUdpPort;				//本地绑定udp端口
	char		szServerNo[64];			//服务器序列号
	char 	szServerDn[64];			//服务器所在的域名称
	char		szDeviceNO[64];			//设备序列号
	char 	szConnPass[64];			//设备接入密码
	int		iHsIntervalTime;			//心跳间隔时间,单位是秒
	int		iRsAgedTime;			//重新发送注册时间间隔，单位为秒
	char		Camreaid[NET_MAX_CHANNUM][64];	//设备中摄像头ID
	int		CamreaLevel[NET_MAX_CHANNUM];	//报警等级
	char		Alarmid[NET_MAX_CHANNUM][64];	//设备中摄像头ID
	int		AlarmLevel[NET_MAX_CHANNUM];	//报警等级
	unsigned int		uiAlarmStateGpinEnable;	//外部报警使能
	unsigned int		uiAlarmStateLoseEnable;	//视频丢失告警使能
	unsigned int		uiAlarmStateMotionEnable;//视频动态侦测告警使能
	unsigned int		uiAlarmStateBlindEnable;	//屏幕遮挡告警使能
	unsigned int		uiAlarmStatePerformanceEnable;	//系统异常告警使能
	unsigned int		uiAlarmStateConnectEnable;	//用户连接告警使能
};

//手机服务配置
struct SDK_PMSConfig
{
	bool Enable;		///< 是否开启
	char servname[64];		
	int port;
	char boxid[128];
	char resume[24]; //保留
};

//屏幕提示信息
struct  SDK_OSDInfoConfig
{
	SDK_VIDEO_WIDGET OSDInfoWidget;
	char ppInfo[NET_MAX_LINE_PER_OSD_AREA][NET_CHANNEL_NAME_MAX_LEN];
};

//所有通道的屏幕提示信息
struct  SDK_OSDInfoConfigAll
{
	SDK_OSDInfoConfig   vOSDInfoAll[NET_MAX_CHANNUM];
};
//
struct SDK_KaiCongAlarmConfig
{
	bool Enable;		///< 是否开启
	char ServerName[NET_NAME_PASSWORD_LEN];	///< 服务名
	int Port;							///< 端口号
	char UserName[NET_NAME_PASSWORD_LEN];		///< 用户名
	char Password[NET_NAME_PASSWORD_LEN];		///< 密码	
};
//
struct SDK_VideoChannelManage
{
	int		nHVRCap; 
	int		curMode;
	bool bhide[MAX_HVR_CHNCAP_CHN];
	SDK_CAPTURE_HVRCAP	HVRCap[MAX_HVR_CHNCAP_CHN];	
};

//PTZ控制能力集
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
	bool bEnable;							///< 是否开启
	int iInterval;							///< 保活间隔时间
	char ServerName[NET_NAME_PASSWORD_LEN];	///< 服务名
	int Port;								///< 端口号
	char UserName[NET_NAME_PASSWORD_LEN];		///< 用户名
	char Password[NET_NAME_PASSWORD_LEN];		///< 密码
	char resume[24];
};

struct SDK_MonitorPlatformConfig
{
	int Enable;		///< 是否开启
	char servname[NET_NAME_PASSWORD_LEN];		
	int port;
	char resume[24];
};
//网络摄像头扩展参数
struct SDK_CameraParamEx
{
	SDK_GainCfg broadTrends;	//宽动态
	int res[64];	//冗余
};

// 摄像头所有扩展参数
struct SDK_CameraParamExAll
{
	SDK_CameraParamEx vCameraParamExAll[NET_MAX_CHANNUM];
};

//网络服务定制平台通用配置，以后定制都用这个
struct SDK_NetPlatformCommonCfg
{
	int	Enable;
	int Port;									///< 端口号
	char ServerName[NET_NAME_PASSWORD_LEN];		///< 服务名
	char ID[NET_NAME_PASSWORD_LEN];	
	char UserName[NET_NAME_PASSWORD_LEN];		///< 用户名
	char Password[NET_NAME_PASSWORD_LEN];		///< 密码
	char resume[128];		///预留
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
struct SDK_POSITIONING_POS//经纬度
{
	int  degree;     //以(度/1000)为单位
	char direction;  //方位 取值如枚举值POSITIONING_DIRECTION所示
	char res[3];
};
//GPS状态
struct SDK_GPSStatusInfo
{
	int             positioningStatus; //定位状态，取值如枚举SDK_INFO_NET_LINK_STATUS所述
	SDK_POSITIONING_POS longitudePos;      //经度
	SDK_POSITIONING_POS latitudePos;       //纬度
	char            rev[12];
};

//wifi状态
struct SDK_WifiStatusInfo
{
	int  connectStatus;  //wifi连接状态  如枚举SDK_INFO_NET_LINK_STATUS所述
	int  strength;       //信号强度
	char rev[24];
};

//3G状态
struct SDK_WirelessStatusInfo
{
	int  connectStatus;  //3G连接状态  如枚举SDK_INFO_NET_LINK_STATUS所述
	int  strength;       //信号强度
	char rev[24];
};

//主动注册状态
struct SDK_DASStatusInfo
{
	int  connectStatus;  //DAS连接状态  如枚举SDK_INFO_NET_LINK_STATUS所述
	char rev[28];
};

struct SDK_RecordStorageInfo
{
	unsigned int bStart;//是否录像标志位
	SDK_SYSTEM_TIME beginTime;//录像开始时间
	SDK_SYSTEM_TIME endTime;//录像结束时间
	unsigned int  storageCapacity;//硬盘总容量
	unsigned int  useCapacity;//使用容量
	int res[16];//冗余
};
/// 解码延时等级
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

// 数字通道
struct SDK_DecodeParam
{
	int iMaxDeleyTime[NET_MAX_CHANNUM];	// 最大的解码延时
};

struct SDK_RecordStateInfo
{
	int nchannel;
	BOOL RecordState;
};

//定制视频颜色结构
struct SDK_VIDEOCOLOR_PARAM_EX
{
	int		BrightnessRef;		///< 亮度ref1，取值0-100。
	int		ContrastRef;		///< 对比度ref1，取值0-100。
	int  		ContrastThRef;		///< 对比度阀值ref1，取值0-100。
	int		ContrastSlopeRef;		///< 对比度斜率ref1，取值0-100。
	int 		DarkBlfRef;
	int		DarkNfRef;
	int		DarkEcPthRef;
	int		DarkEcMthRef;
	int		DarkDcRef;
	int		CbGain;	//high low middle
	int		CrGain;	//higg low middle
	int		reserved;	//保留
};

struct SDK_VIDEOCOLOR_PARAM_CUSTOM
{
	SDK_VIDEOCOLOR_PARAM_EX	VideoColor[3];
	int		Saturation;		///< 饱和度，取值0-100。
	int		Gain;			///< 增益，取值0-100。bit7置位表示自动增益，其他位被忽略。
	int		Acutance;		///< 锐度，取值0-100
	int		AeWight;		//背光补偿
};

enum SDK_FileControlType
{
	SDK_FILE_DEL,			//删除文件
	SDK_FILE_DIR_DEL,		//删除文件夹
	SDK_FILE_DIR_CLEAR,		//清空文件夹
	SDK_FILE_NR,
};

struct SDK_NetFileControl
{
	int iAction;			//enum FileControlType
	char strfile[256];
};

enum SDK_DecChnStateType
{
	SDK_DEC_STA_NONE, 			//无用
	SDK_DEC_STA_NOCONFIG,		//未配置
	SDK_DEC_STA_NOLOGIN,		//未登陆
	SDK_DEC_STA_NOCONNECT,	//未连接
	SDK_DEC_STA_CONNECTED,	//已连接
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
	==第一位代表SDK_TRANSFER_PROTOCOL_ONVIF_DEFAULT = 128，以此内推
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
	int iAction;            //参考SDK_Music_Play_Action
	char sFileName[20];
};

/// 音频文件列表信息
struct SDK_MusicFileList
{
	int iNumFiles;		///< 文件数量
	char sFileName[8][20];
};

enum SDK_CAR_BOOT_TYPE
{
	SDK_CAR_BOOT_TYPE_SPARK,  //点火熄火开关机
	SDK_CAR_BOOT_TYPE_TIMING, //定时开关机
	SDK_CAR_BOOT_TYPE_NR,
};

//点火开关机延时配置
struct SDK_CarSparkWork
{
	int bootDelayMinute;  //开机延时分钟数
	int shutDelayMinute;  //关机延时分钟数
	char resv[24];        //保留
};

//车载定时开关机配置
struct SDK_CarTimingWork
{
	SDK_TIMESECTION workSection1; //工作时间段1
	SDK_TIMESECTION workSection2; //工作时间段2
	char resv[32]; //保留
};

struct SDK_CarBootTypeConfig
{
	int           bootType;         //如枚举 SDK_CAR_BOOT_TYPE 所述
	SDK_CarSparkWork  sparkWorkConfig;  //点火开关机配置
	SDK_CarTimingWork timingWorkConfig; //定时开关机时间段1
	char          resv[48];
};

//单个IPC
struct SDK_ALARM_IPCCONFIG
{
	bool	bEnable;		///< 报警输入开关
	int		iSensorType;	///< 传感器类型常开 or 常闭
	SDK_EventHandler hEvent;	///< 报警联动
};
///< 所有数字通道的报警配置
struct SDK_IPCAlarmConfigAll
{
	SDK_ALARM_IPCCONFIG vAlarmConfigAll[NET_DECORDR_CH];
};

//百度云
struct SDK_BaiduCloudCfg
{
	bool	enable;
	char APIKey[NET_NAME_TOKEN_LEN];				//应用API密钥
	char SecretKey[NET_NAME_TOKEN_LEN];			//应用密钥
	char AuthorizationCode[NET_NAME_TOKEN_LEN];	//授权码
	char accessToken[NET_NAME_TOKEN_LEN];		//访问权限码
	char refreshToken[NET_NAME_TOKEN_LEN];		//刷新权限码
	SDK_SYSTEM_TIME	refreshTime;					//上次刷新Token时间
	int channelMain[NET_MAX_CHANNUM];				//是否开启标记
	int channelExtra[NET_MAX_CHANNUM];				//是否开启标记
	int	recordFileMode;						//配置录像模式
	int	recordFileSize;						//录像文件大小
	int	recordFileTime;						//录像最长时间
	char resume[128];							///预留
};

//=================================================================================

#define DETECT_AREA_NUM	4							//侦测路数
#define MAX_ROI_AREA    8
#define MAX_OVERSTRP_AREA 4

//时间: 天
typedef struct SDK_DAY_TIME_S
{
	DWORD			week : 5;							//星期
	DWORD			millisec : 10;						//毫秒: 0 ~ 999
	DWORD			second : 6;							//秒:	0 ~ 59
	DWORD			minute : 6;							//分:   0 ~ 59
	DWORD			hour : 5;							//时:	0 ~ 23
}SDK_DAY_TIME; 


//时间: 时间段 
typedef struct SDK_SEG_TIME_S
{
	BYTE			bEnable;							//是否检测
	BYTE			byTask;								//任务
	BYTE			byRes[2];							//备用
	SDK_DAY_TIME		stBgnTime;							//开始时间
	SDK_DAY_TIME		stEndTime;							//结束时间
}SDK_SEG_TIME; 

//计划时间: 周计划时间
typedef struct SDK_SCHWEEK_TIME_S
{
	SDK_SEG_TIME		stSegTime[7][4];					//0: 星期天，1: 周一，2: 周二
}SDK_SCHWEEK_TIME;


//线
typedef struct SDK_LINE_POIN_S
{
	int			x0;									//x0坐标
	int			y0;									//y0坐标
	int			x1;									//x1宽度
	int			y1;									//y1高度
} SDK_LINE_POIN;


//矩形区域   rectangle   
typedef struct SDK_RECTANGLE_POINT_S
{
	int			x;									//X坐标
	int			y;									//Y坐标
	int			w;									//宽度
	int			h;									//高度
}SDK_RECTANGLE_POINT;

//区域
typedef struct SDK_AREA_RECT_S
{
	short			x;									//X坐标
	short			y;									//Y坐标
	short			w;									//宽度
	short			h;									//高度
}SDK_AREA_RECT;

//四边形区域 _CROSS_RECT_S   

//四边形区域 Quadrilateral   
typedef struct SDK_QUADRILATERAL_POINT_S
{
	int			x0;									//X0坐标
	int			y0;									//Y0坐标
	int			x1;									//X1坐标
	int			y1;									//Y1坐标
	int			x2;									//X2坐标
	int			y2;									//Y2坐标
	int			x3;									//X3坐标
	int			y3;									//Y3坐标
}SDK_QUADRILATERAL_POINT;


//屏蔽
typedef struct SDK_SM_CHN_MASK_S
{
	DWORD			dwChns1;							//bit.0 ~ bit.31  表示通道 1  ~ 32
	DWORD			dwChns2;							//bit.0 ~ bit.31  表示通道 33 ~ 64
}SDK_SM_CHN_MASK;

//报警联动处理
typedef struct SDK_SM_ALARM_HANDLE_S
{
	SDK_SM_CHN_MASK		stMaskAlarmOut;						//报警触发设备的输出通道,报警触发的输出,为1表示触发该输出
	DWORD			dwAlarmOutTime;						//报警输出的时间(秒)

	SDK_SM_CHN_MASK		stMaskAlarmRec;						//联动录像通道 
	DWORD			dwRecSaveMode;						//bit0: 本地存储(当本地有存储设备时, 此位固定为1)  
	//bit2: ftp上传   
	DWORD			dwRecTime;							//录像的时间(秒)

	SDK_SM_CHN_MASK		stMaskAlarmSnap;					//联动抓拍
	DWORD			dwSnapSaveMode;						//bit0: 本地存储(当本地有存储设备时, 此位固定为1)  
	//bit1: email 
	//bit2: ftp上传   

	DWORD			dwSnapNum;							//连续抓拍张数
	DWORD			dwSnapInterval;						//连续抓拍时间间隔(毫秒)  0: 连续抓拍

	DWORD			dwUserData1;						//用户数据1(联动PC录像通道)
	DWORD			dwUserData2;						//用户数据2

	DWORD			dwSnapDealy;						//延迟抓拍

	BYTE			bSendEmail;							//联动发送email
	BYTE			byRes[251];							//备用
}SDK_SM_ALARM_HANDLE;

//智能编码：
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


//智能检测：
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

//智能控制：
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

//亮度侦测数据结构
typedef struct SDK_SM_DETECT_BRIGHTNESS_S						//size 512
{
	int	bEnable;									//使能
	int sensitivity;								//阀值
	SDK_SCHWEEK_TIME	stSchTime;					//布防时间
	SDK_SM_ALARM_HANDLE	stAlarmHandle;				//报警处理
	char res[368];
}SDK_SM_DETECT_BRIGHTNESS;

//移动侦测数据结构
typedef struct SDK_SM_DETECT_MOTION_S
{
	int	bEnable;									//使能
	int sensitivity;								//阀值
	SDK_RECTANGLE_POINT	stMDArea[DETECT_AREA_NUM];		//遮挡区域
	char res[440];
}SDK_SM_DETECT_MOTION;

//遮挡侦测数据结构
typedef struct SDK_SM_DETECT_HIDE_S
{
	int	bEnable;									//使能
	float nRateX;									//X坐标比例
	float nRateY;									//Y坐标比例
	int sensitivity;								//阀值
	SDK_RECTANGLE_POINT	stMDArea[DETECT_AREA_NUM];			//遮挡区域
	SDK_SCHWEEK_TIME	stSchTime;						//布防时间
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//报警处理
	char res[296];
}SDK_SM_DETECT_HIDE;

//虚拟警戒线数据结构
typedef struct SDK_SM_DETECT_VIRTUALCORDON_S						//512
{
	int	bEnable;									//使能
	float nRateX;									//X坐标比例
	float nRateY;									//Y坐标比例
	int direction[DETECT_AREA_NUM];					//侦测方向
	SDK_LINE_POIN	stCrossLine[DETECT_AREA_NUM];  	//侦测虚拟线
	SDK_SCHWEEK_TIME_S	stSchTime;						//布防时间
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//报警处理
	char res[284];
}SDK_SM_DETECT_VIRTUALCORDON, SDK_SM_CROSSLINE;

//区域入侵侦测数据结构
typedef struct SDK_SM_DETECT_CROSSAREA_S
{
	int	bEnable;									//使能
	float nRateX;									//X坐标比例
	float nRateY;									//Y坐标比例
	int direction[DETECT_AREA_NUM];					//侦测方向
	SDK_QUADRILATERAL_POINT stCrossArea[DETECT_AREA_NUM];  		//区域
	SDK_SCHWEEK_TIME_S	stSchTime;						//布防时间
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//报警处理
	char  byAreaDisplay;								//视频流显示 DM_LINKAGE_PTZ
	char  byTrackerEnable;								//跟踪使能
	char  res[118];
}SDK_SM_DETECT_CROSSAREA, SDK_SM_CROSSAREA;

//颜色侦测
typedef struct SDK_SM_DETECT_COLOUR_S
{
	int	bEnable;									//使能
	int sensitivity;								//阀值
	SDK_SCHWEEK_TIME_S	stSchTime;						//布防时间
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//报警处理
	char res[368];
}SDK_SM_DETECT_COLOUR, SDK_SM_DETECTCOLOR;

//声音侦测
typedef struct SDK_SM_DETECT_SOUND_S
{
	int	bEnable;									//使能
	int aType;
	int sensitivity;								//阀值
	SDK_SCHWEEK_TIME_S	stSchTime;						//布防时间
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//报警处理
	char res[364];
}SDK_SM_DETECT_SOUND, SDK_SM_DETECTSOUND;



//遗留物体侦测数据结构
typedef struct SDK_SM_DETECT_GOODS_LEGACY_S
{
	int	bEnable;									//使能
	int time;
	float nRateX;									//X坐标比例
	float nRateY;									//Y坐标比例
	int direction[DETECT_AREA_NUM];					//侦测方向
	SDK_RECTANGLE_POINT stLoseobjArea[DETECT_AREA_NUM];  	//遗留物体侦测区域
	SDK_SCHWEEK_TIME_S	stSchTime;						//布防时间
	SDK_SM_ALARM_HANDLE	stAlarmHandle;					//报警处理
	char res[280];
}SDK_SM_DETECT_GOODS_LEGACY, SDK_SM_LOSEOBJ;

//联动主从绑定
#define LINKAGE_MAX_USER   10
typedef struct SDK_SM_LINKAGE_BIND_S
{
	INT					nEnable;
	DWORD				dwMainIP[LINKAGE_MAX_USER];						//IP地址
	DWORD				dwIPAddr[LINKAGE_MAX_USER];						//IP地址
	DWORD				dwDataPort[LINKAGE_MAX_USER];					//数据端口	
	BYTE				Position[LINKAGE_MAX_USER];						//预置位   1~255
	BYTE				CrossArea_Num[LINKAGE_MAX_USER];				//区域入侵  1~4
	BYTE				byRes[50];
}SDK_SM_LINKAGE_BIND;

//====================================================================================

typedef struct SDK_MS_ACTION_S
{
	int nAction;              //0--开始标定  1--完成标定
}SDK_MS_ACTION;

// by chentf  2018.01.23 
typedef struct SDK_MS_CALIBRATION_PARAMETER_S
{
	int nCalibation;  //该摄像机是否已经标定 0：否 1：是
}SDK_MS_CALIBRATION_PARAMETER;

//摄像机登录成功时给主摄像机传入从机的登录参数
typedef struct SDK_MS_SUBCAMCONNECT_S
{
	BYTE  	byConnectCmd;	//0：解除绑定 1：绑定
	DWORD	dwSlaveIP;		//从机IP
	DWORD	dwPort;			//从机端口号
	char    sUserName[32];	//从机登录用户名
	char    sPaasword[32];  //从机登录密码
}SDK_MS_SUBCAMCONNECT;

//对应CMD_CALIBRATE_命令 调用“确定”\“删除”\“3D放大模式”按钮时传此参数
typedef struct SDK_MS_AREA_RECT_S
{	
	int x; 
	int y;
	int nWeight ;
	int nHight;
	int nWndWeight ;	//窗口的实际宽
	int nWndHight;		//窗口的实际高
	int nNumber;
	int nCommand;       //1--确定 2--删除 3--3D放大模式时的坐标值
	char sRet[4];
}SDK_MS_AREA_RECT;

typedef struct SDK_MS_CALIBRATION_MODE_S
{
	int nMode;  //0:3D放大模式 1:自动跟踪模式
}SDK_MS_CALIBRATION_MODE;

typedef struct _SDK_MS_CALIBRATION_ZOOMTIMES_S
{
	int nZoomTimes;  //变倍系数
}SDK_MS_CALIBRATION_ZOOMTIMES;

typedef struct SDK_MS_CALIBRATION_PTZ_INFO_S
{
	char sCmd;// 0： 获取PTZ信息  1：设置PTZ位置
	int nPan; //水平
	int nTilt;//垂直
	int nZoomStep;//变倍步数  

}SDK_MS_CALIBRATION_PTZ_INFO;

typedef struct SDK_MS_PIC_AREA_POS_S
{
	unsigned int nId;
	int x;
	int y;
}SDK_MS_PIC_AREA_POS;

typedef struct SDK_MS_Calibrate_Point_S
{
	int nCmd;// 0 :增加标定点  1:删除标定点  2:获取当前信息 3:删除所有信息
	SDK_MS_PIC_AREA_POS stPointInfo;
	int nPicWeight;//工具 参考宽
	int nPicHight;	//工具 参考高度
	char byRes[32];

}SDK_MS_Calibrate_Point;


#define  SDK_INV_CALIBRATE_MAX			512
typedef struct SDK_MS_ANALY_POINT_S
{
	int nCmd;
	int nNum;//当前画面内点数量
	SDK_MS_PIC_AREA_POS stPoint[ SDK_INV_CALIBRATE_MAX]; //点 坐标 //返回主码流坐标

	int nOutNum;//画面外数量
	SDK_MS_PIC_AREA_POS stOutPoint[SDK_INV_CALIBRATE_MAX]; //返回在分辨率内外的坐标。

}SDK_MS_ANALY_POINT;

typedef struct SDK_MS_PANOTYPE_S
{
	int nPanoType; //1:IMX385_3611 2:IMX385_FISH120 3:IMX385_FISH180 

}SDK_MS_PANOTYPE;


#define   SDK_MS_QUANTU_PRIVATE_ENCRYPT_LEN			512
typedef struct SDK_MS_QUANTU_ENCRYPT_S
{
	BYTE	byRes[SDK_MS_QUANTU_PRIVATE_ENCRYPT_LEN];
}SDK_MS_QUANTU_ENCRYPT; /*全图开发定制SDK 加入512作为存储*/


typedef struct SDK_MS_NAMING_S 
{
#define CMD_NAMING_SET_PARAM   		0x1  //标定区域  			param: nData[1-4]
#define CMD_NAMING_SET_ZOOM    		0x2  //设置倍率 			param: nData
#define CMD_NAMING_SET_SCANMODE		0x3  //设置扫描模式     		param: nData    
#define CMD_NAMING_SET_SCANTIMES	0X4  //扫描开始后扫描n次后停止 	param: nData[1-4]  

#define CMD_NAMING_SCAN_START   	0x20   //扫描开始 
#define CMD_NAMING_SCAN_STOP    	0x21   //扫描手动停止

	int nCmd;
	int nData;		//[1,4]
	char byRes[128];
}SDK_MS_NAMING;

//新增获取   WINSDK获取参数
typedef struct SDK_GET_NAMING_PARAM_S 
{
	char byEnable; //0:  1：功能可用
	char byCalibrate;//0:未标定  1:已标定存在轨迹或标定区域点名可用。
	char byDomeState; //球机空闲状态0：空闲 1：球机点名中 2：轨迹学习中/标定
	char byRes[128];//
}SDK_GET_NAMING_PARAM;


//=========================================================================
typedef struct SDK_FA_PICTURE_HEAD_S		
{
	WORD 	headflag;		//包头标志 0x4A50
	BYTE	tag;			//固定值0x01
	BYTE	frametype;		//帧类型 0x4A 表示图片
	BYTE	frameinfo;		//暂时保留
	BYTE	version;		//暂时保留
	WORD	messageid;		//消息ID
	WORD	width;			//暂时保留
	WORD	height;			//暂时保留
	DWORD   ndatasize;		//暂时保留
	DWORD   deviceid;		//用户用来区分设备ID
	DWORD   channelid;		//用户用来区分通道ID
	DWORD   streamid;		//用户用来区分图片流ID
	BYTE	picnumber[64];	//暂时保留
	BYTE	filename[64];	//图片name
	unsigned int  featureEn;
	unsigned int  nFeatureLen;
	unsigned int  nDevKeyId;	//设备ID
	BYTE	res[84]; 		//扩展使用
	DWORD   headend;		//结束标志
}SDK_FA_PICTURE_HEAD, *P_SDK_FA_PICTURE_HEAD;

//人脸、车牌图片尺寸
typedef struct _FACEPIC_SIZE_S
{
	int X;
	int Y;
	int nWidth;
	int nHeight;
}FACEPIC_SIZE_S,  CARPIC_SIZE_S;


//人脸、车牌坐标
typedef struct _FACE_POSITION_S
{
	int left;
	int top;
	int right;
	int bottom;
}FACE_POSITION_S, CAR_POSITION_S;

//车牌信息 160bytes
typedef struct _SMART_CAR_INFO_XM_S
{
	char szCarPlateNum[16];	//车牌号
	char byRes[144];
}SMART_CAR_INFO_XM_S;

//Wifi探针信息160bytes
typedef struct _SMART_WIFIPROBE_INFO_XM_S
{
	int   nSignalIntensity;		//wifi信号强度
	int	  nChannel;				//信道
	char szPhoneWifiMac[20];	//手机MAC
	char szRouteMac[20];		//路由MAC
	char byRes[112];
}SMART_WIFIPROBE_INFO_XM_S;	

/*人脸属性检测*/
typedef struct _SDK_FACE_ATTRIBUTE_S
{
	signed char byAge;      //年龄 
	signed char byGender;	//性别 -1 未知, 1 男, 2 女
	signed char byGlasses; 	//眼镜  -1 未知, 0 不戴眼镜, 1 戴眼镜, 2 戴墨镜 
	signed char byMask; 	//口罩 -1 未知, 0 不戴口罩, 1 戴口罩
	signed char byRace;		//种族   -1 未知, 1 黄种人, 2 黑种人, 3 白种人  
	signed char byEye;			//眼睛 -1 未知, 0 闭合, 1 睁开 
	signed char byMouth;		//嘴巴 -1 未知, 0 闭合, 1 张开
	signed char byBeard;		//胡子   -1 未知, 0 无胡子, 1 有胡子  
	signed char byEmotion;		//表情   -1 未知, 1 生气, 2 平静, 3 高兴, 4 悲伤, 5 惊讶, 6 害怕, 7 厌恶, 8 斜视, 9 尖叫
	signed char byAttractive; 	//魅力 [0， ）
	signed char bySmile;      	//笑脸  -1 未知, 0 微笑, 1 平静
	signed char bySunglass;	//墨镜 -1 未知, 0 不戴墨镜, 1 戴墨镜
	signed char byHat;			//带帽 -1 未知, 0 不戴帽子, 1 戴帽子
	signed char byIsCalling;	//打电话 -1 未知, 0 没打电话, 1 在打电话
	signed char byUpperbodyColor;	//上衣颜色 -1 未知, 0 黑色, 1 白色, 2 灰色, 3 红色, 4 蓝色, 5 黄色, 6 橘色, 7 棕色, 8 绿色, 9 紫色, 10 青色, 11 粉红色, 12 条纹, 13 格子, 14 图案
	signed char byUpperbodyStyle;	//上衣款式 -1 未知, 0 背心, 1 T 恤, 2 衬衫, 3 罩衫, 4 连衣裙, 5 卫衣, 6 夹克, 7 针织毛衣, 8 西装, 9 马甲, 10 大衣, 11 羽绒服, 12 牛仔服
	signed char byHairStyle;		//发型 -1 未知, 0 光头, 1 秃头, 2 平头, 3 短发, 4 及肩短发, 5 披肩发, 6 束发
	signed char byRes[15];	
}SDK_FACE_ATTRIBUTE_S;
//图片属性 3072字节
typedef struct SDK_FACE_ATTR_S
{
	int	nvisits;							//来访次数 用于比对机
	int	nPicType;							//图片类型 (人脸、车牌、WiFi探针用到)
	int nFaceQuality;						//质量分数
	int	nPicLen;							//图片大小(人脸、车牌、WiFi探针用到)
	int nPicID;								//图片计数
	int	nFaceID;							//人脸ID (人脸、车牌用到)
	int nFaceOrHead;						//人脸和人头区分(1人头，2人脸)
	int  byIsScenePic;						//场景图标识（0：小图；1场景图） (人脸、车牌用到)
	SDK_FACE_ATTRIBUTE_S stFaceAttribute;		//人脸属性
	FACEPIC_SIZE_S  stFacePicSize;			//用于人脸抠图，原图不用 (人脸、车牌用到)
	FACE_POSITION_S stFacePosition;			//人脸坐标位置(人脸、车牌用到)
	char stFaceTime[32];					//抓拍时间(人脸、车牌用到)
	char stDevUUID[32];						//设备UUID,用HK ID(人脸、车牌、WiFi探针用到)
	char stOsd[64];							//OSD信息(人脸、车牌、WiFi探针用到)
	union
	{
		SMART_CAR_INFO_XM_S stCarInfo;		//车牌信息
		SMART_WIFIPROBE_INFO_XM_S stWifiProbeInfo;//wifi探针信息
	};
	int  nFeatureType;						//特征值类型:0 float, 1 char ,2 int
	int  nFeatureLen;						//结合nFeatureType类型，特征值数组长度
	//用于预留存放人脸特征值
	union
	{
		float	fFeature[512];
		char	cFeature[2048];
		int		nFeature[512];
	}facefeature;
	char stFaceUtcTime[32];					//抓拍UTC时间   // YUVDZ_12_11 
	int byHasFaceAttr;						//是否带人脸属性信息

	char stFacePicname[80];					//抓拍图片名
	char stFramePicname[80];				//背景图片名
	int  nFacePicLen;						//抓拍人脸图大小
	int  nFramePicLen;						//原图图片大小
	int  nLiveNess;							//活体检测 0 表示未检测或者检测未成功  1 表示活体
	float fLiveScore;						//活体分数
	char szBodyPicName[80];					//人形图片名 
	int	 nBodyPicLen;						//人形图大小 
	int  nStructureInfoLen;					//结构化信息长度 
	char sRes[332];					//预留	
}SDK_FACE_ATTR,*PSDK_FACE_ATTR;

typedef struct SDK_FA_ImprotFaceImageInfoCallback_s
{
	unsigned int uiSessionId;		///< 会话ID
	int iRet;				///< 返回值
	char sName[64];		///< 配置名称
	char sFileName[64];		//导入图片的文件名
}SDK_FA_ImprotFaceImageInfoCallback;
//=================================================================================//
//比对结果
typedef struct SDK_FA_FACECOMPARE_RESULT_ALARM_S		
{
	unsigned int   	deviceid;
	unsigned int   	channelid;
	unsigned int   	streamid;
	unsigned int   	wbmode;			//黑白名单
	unsigned int   	libindex;		//黑白名单库索引
	unsigned int   	libnumber;		//黑白名单库里编号
	unsigned char   npicname[64];	//实时比对图片名字
	unsigned char   cpicname[64];	//实时比对图片名字
	float			result;		    //比对结果
	unsigned char   SnapTime[32];	////抓拍时间
	unsigned int   	alarmcmd;
	unsigned char	byRes1[64];

	unsigned int   	guest;			//客流统计
	unsigned char 	Age;      		//年龄 
	unsigned char 	Gender;			//性别
	unsigned char 	Glasses; 		//眼镜  
	unsigned char 	Mask; 			//面具
	unsigned char 	Race;			//种族  
	unsigned char 	Eye;			//眼睛 	
	unsigned char 	Attractive;		//魅力值 
	unsigned char	ByRes[117];		//预留

}SDK_FA_FACECOMPARE_RESULT_ALARM;  

//黑白名单
typedef struct SDK_FA_BLACKANDWHITELIST_CONFIG_S
{
	int					 byOutMode;			// 1 库文件索引; 2 图片
	int					 byWbMode;			// 1 黑名单; 2白名单
	int				 	 byAllNums;			// 实际库数目
	int				 	 byLibIndex;		//库索引
	int					 byFileIndex;		//文件索引
	int					 byDataSize;		//文件大小
	char				 byFileName[64];	//名称
	int					 byErrorCode;		//错误码，参照XM_WB_ERROR_CODE
	int					 bySex;				//1--男 2--女
	int					 byDataType;		// 特征值类型  0 float,1 char ,2 int 
	int					 byExDataLenth;		//扩展数据结构体长度
	unsigned char		 byRes[24];
}SDK_FA_BLACKANDWHITELIST_CONFIG;


typedef struct SDK_XM_WB_CONFIG_EXDATA_S
{
	int					 byValidValue;			// 名单有效值
	char					 byValidStartTime[32];		// 名单开始时间
	char					 byValidEndTime[32];		// 名单结束时间
	char					 byPosition[32];			//职位
	char					 byPhoneNumber[32];		//号码
	char					 byIdCard[32];			//身份证号码
	char					 byHomeAddress[128];	//家庭地址
	char					 byRemark[256];			//备注
	char		 			 byRes[476];
}SDK_XM_WB_CONFIG_EXDATA,*LP_SDK_XM_WB_CONFIG_EXDATA;

//人脸私有协议上传
typedef struct SDK_FA_FS_PROTOCOL_S
{
	char szUDPaddr[64];	//服务器IP
	DWORD dwUDPport;	//服务器端口号
	BYTE nUDPSDKEnable; //私有协议上传使能开关
	BYTE szRes[3];		//保留
	BYTE byRes[64];		//保留
}SDK_FA_FS_PROTOCOL_S;

typedef struct SDK_FA_SMART_FACE_S
{
	INT			nEnable;			//开关
	INT			nquality;			//灵敏度
	BYTE 		nExposureMode; 		//人脸曝光模式
	BYTE		nSnapMode;			//抓拍模式 0离开后抓拍距离选优   1快速抓拍  2间隔抓拍秒为单位  3间隔抓拍帧为单位 4单人模式  5离开后质量选优  6快速+离开后
	BYTE 		nTrackmode;			//人脸跟踪  		 0:关闭 1:开启
	BYTE		nFtpEnable;			//FTP上传开关	0:关闭 1:开启
	INT			nFaceSize;			//人脸识别最小尺寸(60~300)
	INT			nMaxFaceSize;		//最大像素(300~500)
	BYTE		nFaceBLC;			//人脸场景
	BYTE		nPicMode;			//图片上传格式(0人脸；1原图；2人脸及原图)
	BYTE 		nParamCheckFlag;
	BYTE		byFaceAreaExpand;		//人脸图片周边背景扩展系数
	BYTE		byPicPrefixEnable;		//自定义前缀开关
	CHAR		szPicPrefix[16];			//图片前缀
	INT			nTrackFrameNum;		//快速抓拍帧数-----快速抓拍
	BYTE		bySnapNum;				//最大抓拍次数-----离开后抓拍模式
	BYTE		byIntervalTime;			//间隔时间---间隔抓拍，秒为单位
	BYTE		byFacePicQual;			//人脸图片编码质量
	BYTE		byFramePicQual;			//原图编码质量
	INT			nIntervalFrame;			//间隔帧数---间隔抓拍，帧为单位
	BYTE		byAttributeEnable;		//人脸属性开关
	BYTE		byIntervalSnapNum;		//抓拍次数------间隔抓拍模式
	BYTE		byAlignmentRes[2];		//字节对齐，没有用到
	INT			nGateIntervalFrame;		//间隔帧数----闸机模式
	BYTE		byRes[16];
}SDK_FA_SMART_FACE;

//人脸识别参数
typedef struct  SDK_FA_SNAP_FACE_CONFIG_S   
{
	SDK_SCHWEEK_TIME	aTime;
	SDK_FA_SMART_FACE   sSmartFace;  
	SDK_FA_FS_PROTOCOL_S stFsProtocols;
}SDK_FA_SNAP_FACE_CONFIG;

//全通道人脸识别参数
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


//人脸报警设置   384字节
typedef struct SDK_SMART_ALARM_S
{
	BYTE			aEnable;		//报警开关
	BYTE			aBEnable;		//黑名单报警开关
	BYTE			aWEnable;		//白名单报警开关
	BYTE			aIoEnable;		//IO输出使能
	short			aIoTime;		//IO输出时间
	BYTE			aIoType;		//IO输出类型
	BYTE			aSimilarity;	//相似度 (0-100)
	SDK_SCHWEEK_TIME	aTime;			//布防时间

	short			aCmpMode;		//识别模式 (0单次识别  ,1 一直识别)
	short			aCmpNum;		//识别次数 (1-10)
	//手机APP消息推送
	BYTE			aPushEnable;			//推送开关
	BYTE			aBPushEnable;			//黑名单消息推送
	BYTE			aWPushEnable;			//白名单消息推送
	BYTE			aNWPushEnable;			//非白名单消息推送


	//20180528
	BYTE			aAudioInpute;	//音频输入
	BYTE			aVEnable;		//VIP报警
	BYTE			aVPushEnable;	//VIP消息推送
	BYTE			aNonWhite;		//非白名单报警

	INT				aAlarmInfoType;		//推送消息内容类型:  0 中文信息  1英文信息	2 手机默认报警信息

	BYTE		 	byRes[24];
}SDK_SMART_ALARM;
//人脸报警设置全通道
typedef struct SDK_SMART_ALARM_ALL_S
{
	SDK_SMART_ALARM vSmartAlarm[NET_MAX_CHANNUM];
}SDK_SMART_ALARM_ALL;

//人脸算法版本信息
typedef struct SDK_FA_SMART_VERSION_INFO_S
{
	char szLib_version[16] ;    //算法库版本
	char szModel_version[16];	//模型版本
	BYTE  nbyLic;				//保留				
	BYTE  byRes[7];				//保留
}SDK_FA_SMART_VERSION_INFO;

//=========================================================================


//协议对黑白名单操作
typedef enum _WBLIST_ACTION_TYPE
{
	OUT_INDEX = 1,					//导出文件索引
	OUT_PICTURE,					//导出黑白名单库中单张图片
	OUT_PICTURE_COMP,				//比对后导出响应库图片
	OUT_PICTURE_DEL,				//删除库中单张图片
	OUT_PICTURE_DELALL,				//删除黑白名单所有库
	IN_PICTURE_ADD,					//通过导入图片添加一张黑白名单
	IN_PICTURE_ADD_SNAP,			//通过抓拍添加黑白名单
	IN_PICTURE_GET_FEATURE,			//通过导入一张图片获取特征值
	IN_INDEX_GET_FEATURE,			//通过库索引获取特征值
	OUT_PICTURE_USER_INFO,   		//导出用户详细信息
	IN_PICTURE_USER_INFO_UPDATA,	//用户信息更新

	//比对服务器增加的4个,IPC上未用到，但是需要和SDK统一
	IN_PICTURE_GET_SIMILARITY_PIC_MSG = 12, //通过导入一张图片获取特征值最相似的底库图片信息  
	IN_PICTURE_GET_FEA_AND_ALARM = 13,		//通过导入一张图片获取特征值并接受可能的报警
	IN_COPY_DATEBASE = 14, 					//拷贝一个数据库到另一个数据库
	IN_MODIFY_PICTURE_MESSAGE = 15,			//修改图片信息
	IN_FEATURE_ADD,							//通过特征值添加一张黑白名单
	IN_FEATURE_UPDATE,						//通过特征值添加一张黑白名单
	OUT_ATTENDANCE ,						//考勤导出
	OUT_CMP_INFO ,							//比对信息导出
	OUT_WBLIST_EN
}WBLIST_ACTION_TYPE;


//黑白名单文件索引表信息结构体
typedef struct _SDK_INDEX_INFO_S {
	int libindex;		//库编号
	int fileindex;		//图片索引编号	
}SDK_INDEX_INFO;


typedef struct _SDK_FILEINDEX_INFO_S {
	SDK_INDEX_INFO findex;
	int enable;					//是否使用
	union{
		char name[NET_NAME_PASSWORD_LEN];	//图片名字，旧版本
		char userid[NET_NAME_PASSWORD_LEN];	//用户ID,这部分数据联合体，兼容之前的数据内容，适用于新版本
	};
	union{
		int checksum;				//检验码，旧版本
		int syslistID;				//系统ID，这部分数据联合体，兼容之前的数据内容，适用于新版本
	};
}SDK_FILEINDEX_INFO;


typedef struct _SDK_INFO_EX_S
{
	int						byValidValue;			// 名单有效值
	char					 byValidStartTime[32];		// 名单开始时间
	char					 byValidEndTime[32];		// 名单结束时间
	char					 byPosition[32];			//职位
	char					 byPhoneNumber[32];		//号码
	char					 byIdCard[32];			//身份证号码
	char					 byHomeAddress[128];	//家庭地址
	char					 byRemark[256];			//备注
	char		 			 byRes[476];
}SDK_INFO_EX;

typedef struct _SDK_FILEINDEX_DATA_S
{
	SDK_FILEINDEX_INFO  fileindex;
	SDK_INFO_EX 		   info_ex;
}SDK_FILEINDEX_DATA;


typedef struct _SDK_FILEINDEX_INFO_EX_S
{
	int 	syslistid;					//系统ID 在添加时不用赋值，由系统生成
	int 	libindex;					//库编号 在添加时不用赋值，由系统生成
	int 	fileindex;					//图片索引编号 在添加时不用赋值，由系统生成	
	int 	enable;						//使能开关
	int 	timelimit;					//名单有效期 0 永久有效，1 周期有效，有效时间参照sTime和 eTime
	int  	listmode;					//名单模式: 1 黑名单，2白名单，3 VIP名单
	int  	count;						//统计次数
	int  	sex;						//性别
	char    usrid[36];					//用户ID或者编号
	char    idcard[32];					//身份ID
	char 	name[64];					//姓名
	char  	picname[64];				//图片名   系统生成，不支持修改
	char    nation[12];					//民族
	char 	birth[24];					//生日
	char    phone[16];					//号码
	char    areacode[32];				//区域编码
	char	usrcode1[32];				//社区编码
	char	usrcode2[32];				//小区编码
	char 	type[12];					//类型
	char    dTime[20];					//入库时间
	char    sTime[20];					//开始时间
	char    eTime[20];					//结束时间
	int		usrparam1;					//备用参数1
	int		usrparam2;					//备用参数2
	int		usrparam3;					//备用参数3
	int		usrparam4;					//备用参数4 	
	int		usrparam5;					//备用参数5

	char	resID[32];					//房屋ID	   //备用ID
	char	areaAddress[100];			//区域地址
	char	resname[32];				//房屋名称 //备用名称
	char  	usrdata1[32];				//用户备用数据1,
	char  	usrdata2[24];				//用户备用数据2
	char  	usrdata3[32];				//用户备用数据3
	char  	usrdata4[36];				//用户备用数据4
	char  	usrdata5[88];				//用户备用数据5
	char 	remark[180];				//标签		
}SDK_FILEINDEX_INFO_EX;

//考勤：考勤记录查询，查询返回_SMART_CUSTOM_ATTEND_STATISTICS数组512
typedef struct _SDK_SMART_CUSTOM_ATTEND_STATISTICS
{
	//如果是查询当天的时间只显示考勤时间,其他是显示统计上班情况次数
	int					iChannel;					//通道	
	char				byStartTime[32];			//开始时间：日期有效   
	char				byEndTime[32];				//结束时间：日期有效
	char				byName[64];					//名称(可选)
	char				byUserID[36];				//用户ID(可选)
	int					iPage;						//第几页，从第1页开始，0的话表示只返回数量，不返回信息
	int					iPageCount;					//每页多少数量
	int					iQueryOrPaged;				//查询还是翻页  1:查询2:翻页
	int					iQueryStatus;    			//通过状态查询信息
	int					iQuerySomedayOrStatistic;	//查询某天信息还是统计信息
	char				byRes[828];
	int					iTotalCount;				//总数数量
	int					iCount;						//输出数量
}SDK_SMART_CUSTOM_ATTEND_STATISTICS;

typedef struct  _SDK_SMART_PERSON_ATTEND_INFO 
{
	char				byName[64];					//名称(可选)
	char				byUserID[36];				//用户ID(可选)
	int					iSyslistID;					//系统ID
	char				byOnDutyStat;				//上班状态 :0 未考勤,1 正常,2 迟到 
	char				byOffDutyStat;				//下班状态 :0 未考勤,1 正常,3 早退
	char				bysres0[2];
	int					iNormalNum;					//正常次数
	int					iLateNum;					//迟到次数
	int					iEarlyNum;					//早退次数
	int					iAbsentNum;					//未考勤
	int					iShouldTimes;				//应到次数
	int					iActualTimes;				//实到次数
	char				byOnDutyTime[32];			//上班时间
	char				byOffDutyTime[32];			//下班时间
	char				byCheckOnDate[32];			//当天考勤日期
	char				byRes1[796];
}SDK_SMART_PERSON_ATTEND_INFO ;

typedef struct SDK_SMART_FACE_CMP_QUERY_INFO_
{
	int					sLibRowid;				//库行号
	float				sLibSimilarity;			//相似度	

	char				sName[64];				//名称(可选)
	char				sUserID[36];				//用户ID(可选)
	char				sLibSnapTime[32];		//抓拍时间
	int 				sLibChannelid;			//通道号
	int					sLibMode;				//名单	类型		
	int					sSysListID;				//系统ID
	int 	  			nLibGuest;				//客流统计
	char				cLibAge;      			//年龄 
	char  				cLibGender;				//性别
	char				cLibGlasses; 			//眼镜  
	char				cLibMask; 				//面具
	char				cLibRace;				//种族  
	char				cLibEye;				//眼睛 	
	char				cLibAttractive;			//魅力值
	char				cLibBeard;				//胡子
	char				cLibEmotion;			//表情
	char				sLibCpicname[80];		//实时比对图片名字
	char				sBackPicName[80];		//背景图片名称
	char				sBodyPicName[80];		//人形图片名称
	char				sRes0[3];		
	char				sRes1[616];
}SDK_SMART_FACE_CMP_QUERY_INFO;


//比对：比对记录查询，查询数据返回FACE_CMP_QUERY_CONDITION数组信息512
typedef struct SDK_FACE_CMP_QUERY_CONDITION_ 
{
	int				iChannel;				//通道	
	char			sStartTime[32];			//开始时间：日期有效
	char			sEndTime[32];			//结束时间：日期有效
	char			sName[64];				//名称(可选)
	char			sUserID[36];			//用户ID
	int				sLibMode;				//0:所有,1:黑,2:白,3:Vip 名单(可选)			
	int				iPage;					//第几页，从第1页开始，0的话表示只返回数量，不返回信息
	int				iPageCount;				//每页多少数量
	int				iQueryOrPaged;			//查询还是翻页  1:查询2:翻页
	char			sRes[832];
	int				iTotalCount;			//总数数量
	int				iCount;					//输出数量

}SDK_FACE_CMP_QUERY_CONDITION;

typedef struct _SMART_WB_CONFIG_EX		//2048
{
	int						iOpMode;			//名单库操作模式，内容见WBLIST_ACTION_TYPE值
	int						iWbmode;			//名单模式，内容见WBLIST_MODE值
	int						iOpFlag;			//操作唯一标识:0 通过i_sUserID来操作，1 通过i_iSyslistID来操作，默认0
	int						iSyslistID;			//名单系统ID;
	char					sUserID[36];		//用户ID，唯一标识
	char					sFaceID[36];		//人脸ID，用于表示同一用户多张人脸ID,如果不需要的话就不用赋值
	int						iBodyLen;			//配置结构体长度，主要是指sdk_fileindex_info_Ex1长度，如果为0，则没有该参数

	int						iErrorCode;			//错误码
	int						iLibIndex;			//库索引
	int						iFileIndex;			//文件索引
	int						iAllNums;			//实际库数目
	int						iSyslistid;		
	int 					iFeatureType;		//特征值类型  0 float,1 char ,2 int 
	int						iDataSize;
	char					sRes0[104];			//预留
	union
	{
		SDK_FILEINDEX_INFO_EX   stUserInfo;					//用户名单详细信息，在添加、更新时候需要添加该信息
		SDK_SMART_CUSTOM_ATTEND_STATISTICS stAttendInfo;	//考勤查询信息
		SDK_FACE_CMP_QUERY_CONDITION stCmpInfo;				//比对记录查询信息
	};
	char					sRes[800];						//后期可用于SDK_FILEINDEX_INFO_EX扩展
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

//图片头信息
typedef struct _SDK_PICTURE_HEAD_S		//256字节
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
	unsigned int   nDevKeyID;		//设备编号
	unsigned int   nAttrInfoLen;	//人脸属性信息大小
	unsigned int   nCmpInfoLen;		//比对详细信息大小
	unsigned int   nUserInfo1Len;	//用户自定义信息大小
	unsigned int   nFacePicLen;		//抓拍图片大小，等于0时没有数据
	unsigned int   nFramePicLen;	//背景图片大小，等于0时没有数据
	unsigned int   nLibPicLen;		//底库图片大小，等于0时没有数据
	unsigned int   nBodyPicLen;		//人形照大小 
	unsigned int   nPicTotalLen;		//图片总大小 
	unsigned char  res[52];
	unsigned int   headend;			//
}SDK_PICTURE_HEAD, *PXM_PICTURE_HEAD;

//人脸比对信息 2048字节
typedef struct _SDK_FACE_COMPARE_INFO_S
{
	float fCompareResult;				//比对相似度
	int  nFaceAlarm;					//人脸报警
	char stCompareTime[32];				//比对时间
	SDK_FILEINDEX_INFO_EX stIndexInfo;	//人脸底库信息
	char stRes[984];
}SDK_FACE_COMPARE_INFO;

//人脸监视返回信息
typedef struct _SDK_FACE_MONITOR_INFO_S
{
	SDK_PICTURE_HEAD stPictureHead;				//图片头信息
	SDK_FACE_ATTR stFaceAttr;					//人脸信息
	SDK_FACE_COMPARE_INFO stFaceCompareInfo;	//比对信息
}SDK_FACE_MONITOR_INFO, *LPSDK_FACE_MONITOR_INFO;

#define MAX_USER_DATA_LEN		1024			//用户定义数据长度

//错误码
typedef enum _XM_WB_ERROR_CODE
{
	WB_OK = 1,					//成功
	WB_FAILE = -1,				//失败
	WB_COLLECT_ERROR = -2,		//提取特征值失败
	WB_FILEINDEX_ERROR = -3,	//文件名字编号重复
	WB_LIB_FULL = -4,			//库满
	WB_ADD_TIME_OUT = -5,		//添加超时
	WB_PARA_ERROR	= -6,		//参数错误
	WB_FILE_BIG		= -7,		//文件太大
	WB_SPACE_ERROR	= -8,		//存储空间不足
	WB_FILE_OPEN_ERROR	= -9,	//文件打开失败
	WB_NO_DBFILE	= -10,		//没有数据库
	WB_FILE_ERROR	= -11,		//图片读取失败
	WB_DBFILE_BAD	= -12,		//数据库文件损坏
	WB_PIC_QUALITY_ERROR = -13, //图片质量差
	WB_FILE_WHSIZE_ERROR = -14, //图片尺寸错误，宽高不能为奇数
	WB_FILE_FACE_ERROR	 = -15, //检测人脸失败（没检测到人脸或者检测到多人脸）
	WB_PIC_FORMAT_ERROR = -16,  //图片格式错误format

	WB_FACE_AREA_ERROR	 = -17,  //人脸区域错误
	WB_FACE_HAND_ERROR	 = -18,  //算法创建句柄错误
	WB_FACE_BUSY		 = -19,	 //设备忙

}XM_WB_ERROR_CODE;



typedef enum _XM_WB_WBLIST_RESULT_S
{
	WBLIST_OK = 100,
	WBLIST_FAILE = 160, 			//失败
	WBLIST_COLLECT_ERROR = 161, 	//提取特征值失败
	WBLIST_FILEINDEX_ERROR = 162,	//文件名字编号重复
	WBLIST_LIB_FULL = 163,			//库满
	WBLIST_ADD_TIME_OUT = 164,		//添加超时
	WBLIST_PARA_ERROR	= 165,		//参数错误
	WBLIST_FILE_BIG 	= 166,		//文件太大
	WBLIST_SPACE_ERROR	= 167,		//存储空间不足
	WBLIST_FILE_OPEN_ERROR	= 168,		//文件打开失败
	WBLIST_NO_DATABASE = 169,		//没有数据库
	WBLIST_FILE_READ_ERROR = 170,	//图片读取失败
	WBLIST_DATABASE_ERROR = 171,	//数据库损坏
	WBLIST_PIC_QUALITY_ERROR = 172, //图片质量差
	WBLIST_FILE_WHSIZE_ERROR = 173,  // 图片尺寸错误，宽高不能为奇数
	WBLIST_FILE_FACE_ERROR	 = 174,  //检测人脸失败（没检测到人脸或者检测到多人脸）
	WBLIST_PIC_FORMAT_ERROR = 175,  //图片格式错误format
	WBLIST_FACE_AREA_ERROR	 = 176,  //人脸区域错误
	WBLIST_FACE_HAND_ERROR	 = 177,  //算法创建句柄错误
	WBLIST_FACE_BUSY		 = 178,	 //设备忙

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
	int	nDeviceId;		//用户输入参数
	int	nChnnelId;		//用户输入参数
	int	nStreamId;		//用户输入参数
	int nFaceAttrEn;		// 设置相机发送图片属性，用于请求FACE_ATTR数据，所有机型默认打开
	int nFaceCmpInfoEn;		//图片比对信息使能，用于请求FACE_COMPARE_INFO数据，不用该数据不用请求
	int nCaptureEn;			// 抓拍人脸图使能，用于请求抓拍图片数据，不需要可以不用请求
	int nFramePicEn;		// /背景图使能，用于请求抓拍图片时对应的背景图数据，不需要可以不用请求
	int	nLibPicEn;			//人脸库图片，用于请求比对成功时的人脸库图片数据	，不需要可以不用请求
	int nBodyPicEn;			//人形图
	int	nUserExDataEn;		//留给客户扩展，NVR不用请求
}SDK_FACEMONITOR_INFO_FLAG;

#define		SNAP_TIME_LEN		32
#define		PICTURE_NAME_LEN	64
#define		DEVICE_IP_LEN		16
//比对结果
typedef struct SDK_FACECOMPARE_RESULT_S		
{
	unsigned int	deviceid;
	unsigned int	channelid;
	unsigned int	streamid;
	unsigned int	wbmode; 				//名单库类型
	unsigned int	libindex;				//名单库索引
	unsigned int	libnumber;				//名单库里编号
	char	picnameComp[PICTURE_NAME_LEN];	//库图图片名字
	char	*pCompImgData;					//库图图片数据指针
	int		iCompImgSize;					//库图图片数据长度
	char	picnameSnap[PICTURE_NAME_LEN];	//实时比对图片名字
	char	*pSnapImgData;					//实时比对图片数据指针
	int		iSnapImgSize;					//实时比对图片数据长度

	float			result; 		//比对结果
	unsigned char	SnapTime[SNAP_TIME_LEN];	////抓拍时间
	unsigned char   cDeviceIP[DEVICE_IP_LEN];	//设备IP
	unsigned char	byRes[48];

	unsigned int	guest;			//客流统计
	unsigned int	Age;			//年龄 
	unsigned int	Gender; 		//性别
	unsigned int	Glasses;		//眼镜	
	unsigned int	Mask;			//面具
	unsigned int	Race;			//种族	
	unsigned int	Eye;			//眼睛	
	unsigned int	Attractive; 	//魅力值 
	unsigned int	Beard;			//胡须
	unsigned int	Emotion;		//表情
	unsigned char	ByRes[117]; 	//预留

	int 			facealarm;		//人脸报警 , 预留
	float			facecharacter[128];
}SDK_FACECOMPARE_RESULT;  
//=============================================//
//车牌图片数据
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

//定制-长沙全图，用户数据
//7镜头 9镜头
#define SDK_QT_MEMORY_MAX_BYTE   512*1024				//最大字节 512KB
#define SDK_QT_MEMORY_MAX_AREA   64					//最大分区 64 * 8 *1024 
typedef struct SDK_QT_MEMORY_SAVE_S
{
	int type; 			//类型[0-63]
	int len;			//已写入字符串长度 strlen
  	char data[32*1024];		//数据
}SDK_QT_MEMORY_SAVE;




//*************************************************************************************************************自定义结构体

typedef struct _SDK_SM_LUMADETECT
{
	int bEnable;
	int sensitivity;
}SDK_SM_LUMADETECT;


typedef struct _SDK_SM_ODDETECT
{
	int	bEnable;									//使能
	int sensitivity;								//阀值
	SDK_RECTANGLE_POINT	stMDArea[DETECT_AREA_NUM];		//遮挡区域
}SDK_SM_ODDETECT;
//==========================================================================

// 数据上传通道回调函数原型
typedef void (CALL_METHOD *fUploadDataCallBack) (JVT_LONG lLoginID, long UploadType, char *pBuffer, unsigned long dwBufSize, JVT_DWORD nUser);

// 透明串口回调函数原形
typedef void (CALL_METHOD *fTransComCallBack) (JVT_LONG lLoginID, long lTransComType, char *pBuffer, unsigned long dwBufSize, JVT_DWORD nUser);
//服务器断开回调原形
typedef void (CALL_METHOD *fDisConnect)(JVT_LONG lLoginID, char *pchDVRIP, long nDVRPort, unsigned long dwUser);

//原始数据回调原形
typedef int(CALL_METHOD *fRealDataCallBack_JL) (JVT_LONG lLoginID, long dwDataType, unsigned char *pBuffer, long lbufsize, JVT_DWORD nUser);
typedef int(CALL_METHOD *fRealDataCallBack_V2) (JVT_LONG lLoginID, const PACKET_INFO_EX *pFrame, JVT_DWORD nUser);

// 回放录像进度回调原形
typedef void(CALL_METHOD *fDownLoadPosCallBack) (JVT_LONG lLoginID, long lTotalSize, long lDownLoadSize, JVT_DWORD nUser);

//消息（报警,主动注册）回调原形
typedef bool (CALL_METHOD *fMessCallBack)(JVT_LONG lLoginID, char *pBuf, unsigned long dwBufLen, JVT_DWORD nUser);

//升级设备程序回调原形
typedef void(CALL_METHOD *fUpgradeCallBack) (JVT_LONG lLoginID, long lUpgradechannel, int nTotalSize, int nSendSize, JVT_DWORD nUser);

// 语音对讲的音频数据回调函数原形
typedef void (CALL_METHOD *pfAudioDataCallBack)(JVT_LONG lVoiceHandle, char *pDataBuf, long dwBufSize, char byAudioFlag, JVT_DWORD nUser);

//本地播放结束回调原形
typedef void (CALL_METHOD * fLocalPlayFileCallBack)(JVT_LONG lPlayHand, JVT_DWORD nUser);

//信息帧回调设置
typedef void (CALL_METHOD  *InfoFramCallBack)(JVT_LONG lPlayHand, long nType, LPCSTR pBuf,long nSize, JVT_DWORD nUser);

//子连接断线回调
typedef void (CALL_METHOD *fSubDisConnectCallBack)(JVT_LONG lLoginID, SubConnType type, long nChannel, JVT_DWORD nUser);

#ifdef WIN32
//RigisterDraw回调原形
typedef void (CALL_METHOD * fPlayDrawCallBack)(JVT_LONG lPlayHand,HDC hDc,JVT_DWORD nUser);
#else//linux没用到这个回调
typedef void (CALL_METHOD * fPlayDrawCallBack)(JVT_LONG lPlayHand,void* hDc,JVT_DWORD nUser);
#endif // WIN32  


typedef int(CALL_METHOD *fFaceImageDataCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_PICTURE_HEAD *pPictureHead,SDK_FACE_ATTR* pPictureAttr, JVT_DWORD nUser);

typedef int(CALL_METHOD *fFaceCompaeResultCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize, JVT_DWORD dwUser);

typedef int(CALL_METHOD *fFaceBlackAndWhiteListCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,SDK_FA_BLACKANDWHITELIST_CONFIG *pConfig,JVT_DWORD nUser);

typedef int(CALL_METHOD *fCarLicensePlateImageDateCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize,SDK_CAR_MDEIA_HEAD *pConfig,JVT_DWORD nUser);

typedef int(CALL_METHOD *fListManagementCallBack) (JVT_LONG lSubFaceHandle, char* pBuffer,long lbufsize, char* pConfig, JVT_DWORD nUser);

typedef int(CALL_METHOD *fFaceMonitorCallBack) (JVT_LONG lSubFaceHandle, char *pBuffer,long lbufsize, JVT_DWORD dwUser);


//*** */SDK初始化
VIDEO_NET_API long CALL_METHOD VideoNet_Init(fDisConnect cbDisConnect, JVT_DWORD nUser);

//*** */SDK退出清理
VIDEO_NET_API bool CALL_METHOD VideoNet_Cleanup();

//获取错误信息
VIDEO_NET_API long CALL_METHOD VideoNet_GetLastError();

// 设置连接设备超时时间和尝试次数
//nWaitTime:单位ms不设置时默认5000ms,
//nTryTimes:次数,不设置时默认3次
VIDEO_NET_API bool CALL_METHOD VideoNet_SetConnectTime(long nWaitTime, long nTryTimes);

//socketType 参考类型 SocketStyle，默认是0 
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_Login(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPVIDEONET_DEVICEINFO lpDeviceInfo, int *error,int socketType = 0);

//向设备注册扩展接口
//增加登陆类型 0==web 1 ==升级工具 2 == 搜索工具  102 == 外部加密，内部就不用加密了
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_LoginEx(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPVIDEONET_DEVICEINFO lpDeviceInfo, int nType, int *error);

//*** */向设备注销
VIDEO_NET_API long CALL_METHOD VideoNet_Logout(JVT_LONG lLoginID);

//设置接收DVR信息回调, 例如报警信息,以ID号区分
VIDEO_NET_API bool CALL_METHOD VideoNet_SetDVRMessCallBack(fMessCallBack cbAlarmcallback, JVT_LONG lUser);

//建立报警上传通道
VIDEO_NET_API long CALL_METHOD VideoNet_SetupAlarmChan(JVT_LONG lLoginID);
VIDEO_NET_API bool CALL_METHOD VideoNet_CloseAlarmChan(JVT_LONG lLoginID);

//远程配置设备接口 配置类型见SDK_CONFIG_TYPE
VIDEO_NET_API long  CALL_METHOD VideoNet_GetDevConfig(JVT_LONG lLoginID, unsigned long dwCommand, int nChannelNO, char * lpOutBuffer, unsigned long dwOutBufferSize, unsigned long* lpBytesReturned,int waittime = 1000);
VIDEO_NET_API long  CALL_METHOD VideoNet_SetDevConfig(JVT_LONG lLoginID, unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);
//跨网段设置设备配置，目前只支持对网络配置进行设置
VIDEO_NET_API long CALL_METHOD VideoNet_SetConfigOverNet(unsigned long dwCommand, int nChannelNO, char * lpInBuffer, unsigned long dwInBufferSize, int waittime = 1000);

//日志查询
VIDEO_NET_API bool CALL_METHOD VideoNet_FindDVRLog(JVT_LONG lLoginID, SDK_LogSearchCondition *pFindParam, SDK_LogList *pRetBuffer, long lBufSize, int waittime = 2000);

//打开实时预览
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_RealPlay(JVT_LONG lLoginID, LPVIDEONET_CLIENTINFO lpClientInfo);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopRealPlay(JVT_LONG lRealHandle);
VIDEO_NET_API long CALL_METHOD VideoNet_PauseRealPlay(JVT_LONG lLoginID, bool bPause);

//设置回调函数，用户自己处理客户端收到的数据
VIDEO_NET_API bool CALL_METHOD VideoNet_SetRealDataCallBack(JVT_LONG lLoginID,fRealDataCallBack_JL cbRealData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetRealDataCallBack_V2(JVT_LONG lLoginID,fRealDataCallBack_V2 cbRealData, JVT_DWORD nUser);

//清除回调函数,该函数需要在VideoNet_StopRealPlay前调用
VIDEO_NET_API bool CALL_METHOD VideoNet_DelRealDataCallBack(JVT_LONG lLoginID,fRealDataCallBack_JL cbRealData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DelRealDataCallBack_V2(JVT_LONG lLoginID,fRealDataCallBack_V2 cbRealData, JVT_DWORD nUser);

//录像查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的录像数据，外部开内存
//lMaxCount		最大录像数目
//findcount		查找到的录像数目
//waittime		查询超时时间
VIDEO_NET_API long CALL_METHOD VideoNet_FindFile(JVT_LONG lLoginID, VIDEONET_FINDINFO* lpFindInfo, VIDEONET_FILE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime = 5000);

//录像查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的录像数据，外部开内存
//waittime		查询超时时间
VIDEO_NET_API long CALL_METHOD VideoNet_FindFileByTime(JVT_LONG lLoginID, SDK_SearchByTime* lpFindInfo, SDK_SearchByTimeResult *lpFileData, int waittime = 10000);

//录像回放
//lLoginID		登陆句柄
//sPlayBackFileName	回放的录像名称
//cbDownLoadPos 进度回调		用户通知用户设备是否已经将数据发送完毕
								//客户如果想实时显示进度，应该从码流里面获取时间来计算
								//网络部分不分析码流，如果以当前接收数据大小/总大小来计算进度的话不是很准，应该以当前时间，根据开始时间和结束时间来计算进度
//fDownLoadDataCallBack 数据回调
//dwDataUser	回调参数
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_PlayBackByName(JVT_LONG lLoginID, VIDEONET_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_JL fDownLoadDataCallBack, long dwDataUser);
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_PlayBackByName_V2(JVT_LONG lLoginID, VIDEONET_FILE_DATA *sPlayBackFile, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_V2 fDownLoadDataCallBack, long dwDataUser);

//按时间进行录像回放
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_PlayBackByTime(JVT_LONG lLoginID, VIDEONET_FINDINFO* lpFindInfo, fDownLoadPosCallBack cbDownLoadPos, fRealDataCallBack_JL fDownLoadDataCallBack, long dwDataUser);
//VIDEO_NET_API long CALL_METHOD VideoNet_PlayBackByTimeEx(JVT_LONG lLoginID, int nChannelID, LPVIDEONET_TIME lpStartTime,
//											LPVIDEONET_TIME lpStopTime, fRealDataCallBack fDownLoadDataCallBack, long dwDataUser,
//											fDownLoadPosCallBack cbDownLoadPos, long dwPosUser);

VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_PlayBackByTimeEx(JVT_LONG lLoginID, VIDEONET_FINDINFO* lpFindInfo,fRealDataCallBack_JL fDownLoadDataCallBack, JVT_DWORD dwDataUser,
											fDownLoadPosCallBack cbDownLoadPos, JVT_DWORD dwPosUser);

VIDEO_NET_API bool CALL_METHOD VideoNet_StopPlayBack(JVT_LONG lPlayHandle);

//回放控制分,暂停,定位等等
VIDEO_NET_API bool CALL_METHOD VideoNet_PlayBackControl(JVT_LONG lLoginID, long lControlCode,long lCtrlValue);

//录像下载,用户可以不使用回调，自己通过VideoNet_GetDownloadPos获取进度
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_GetFileByName(JVT_LONG lLoginID,VIDEONET_FILE_DATA *sPlayBackFile,char *sSavedFileName, 
											fDownLoadPosCallBack cbDownLoadPos = NULL, JVT_DWORD dwDataUser = NULL,fRealDataCallBack_JL fDownLoadDataCallBack = NULL);
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_GetFileByTime(JVT_LONG lLoginID, VIDEONET_FINDINFO* lpFindInfo, char *sSavedFileDIR, bool bMerge = false,
											fDownLoadPosCallBack cbDownLoadPos = NULL, JVT_DWORD dwDataUser = NULL ,fRealDataCallBack_JL fDownLoadDataCallBack =NULL );

VIDEO_NET_API bool CALL_METHOD VideoNet_StopGetFile(JVT_LONG lFileHandle);
//获取下载进度
VIDEO_NET_API int CALL_METHOD VideoNet_GetDownloadPos(JVT_LONG lFileHandle);

//升级
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_Upgrade(JVT_LONG lLoginID, char *sFileName, int nType = 0, fUpgradeCallBack cbUpgrade = NULL, JVT_DWORD nUser = 0);
//升级状态 1 成功， 2 正在升级 3 失败
VIDEO_NET_API int CALL_METHOD VideoNet_GetUpgradeState(JVT_LONG lUpgradeHandle);
VIDEO_NET_API long CALL_METHOD VideoNet_CloseUpgradeHandle(JVT_LONG lUpgradeHandle);


//云台控制，默认是开启云台，速度4，用户也可以自行设置速度
VIDEO_NET_API bool CALL_METHOD VideoNet_PTZControl(JVT_LONG lLoginID,int nChannelNo, long lPTZCommand, bool bStop = false, long lSpeed = 4);

//扩展云台控制，包括预置点设置，巡航路线，快速定位等等
VIDEO_NET_API bool CALL_METHOD VideoNet_PTZControlEx(JVT_LONG lLoginID,int nChannelNo, long lPTZCommand, 
									long lParam1, long lParam2, long lParam3, bool bStop = false);

//设备控制：返回值 true 成功， false 失败
/*
	==
*/
VIDEO_NET_API bool CALL_METHOD VideoNet_ControlDVR(JVT_LONG lLoginID, int type, int waittime = 2000);
	

//搜索局域网内的设备
VIDEO_NET_API bool CALL_METHOD VideoNet_SearchDevice(char* szBuf, int nBufLen, int* pRetLen, int nSearchTime);


//语音对讲，负责数据传发接口
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartVoiceCom_MR(JVT_LONG lLoginID, pfAudioDataCallBack pVcb, JVT_DWORD dwDataUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_VoiceComSendData(JVT_LONG lVoiceHandle, char *pSendBuf, long lBufSize);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopVoiceCom(JVT_LONG lVoiceHandle);

//设置对讲音频编码方式，用户可以不设置，默认为G711A编码
VIDEO_NET_API bool CALL_METHOD VideoNet_SetTalkMode(JVT_LONG lLoginID, SDK_AudioInFormatConfig* pTalkMode);

// lRecordType录像模式, 见SDK_RecordModeTypes
VIDEO_NET_API bool CALL_METHOD VideoNet_StartDVRRecord(JVT_LONG lLoginID, int nChannelNo ,long lRecordType);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopDVRRecord(JVT_LONG lLoginID, int nChannelNo);

VIDEO_NET_API bool CALL_METHOD VideoNet_SetSystemDateTime(JVT_LONG lLoginID, SDK_SYSTEM_TIME *pSysTime);
VIDEO_NET_API bool CALL_METHOD VideoNet_GetDVRWorkState(JVT_LONG lLoginID, SDK_DVR_WORKSTATE *pWorkState);

VIDEO_NET_API bool CALL_METHOD VideoNet_ClickKey(JVT_LONG lLoginID, SDK_NetKeyBoardData *pKeyBoardData);

// 磁盘管理
VIDEO_NET_API int CALL_METHOD VideoNet_StorageManage(JVT_LONG lLoginID, SDK_StorageDeviceControl *pStorageCtl);

VIDEO_NET_API bool CALL_METHOD VideoNet_SendNetAlarmMsg(JVT_LONG lLoginID, SDK_NetAlarmInfo *pAlarmInfo);

// 抓图
VIDEO_NET_API bool CALL_METHOD VideoNet_CatchPic(JVT_LONG lLoginID, int nChannel, char *sFileName);
VIDEO_NET_API bool CALL_METHOD VideoNet_CatchPicInBuffer(JVT_LONG lLoginID, int nChannel, char *pBuffer, int nBufLen, int *pPicLen);

VIDEO_NET_API bool CALL_METHOD VideoNet_StartAlarmCenterListen(int nPort, fMessCallBack cbAlarmCenter, JVT_DWORD dwDataUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopAlarmCenterListen();

//透明232,485
VIDEO_NET_API bool CALL_METHOD VideoNet_SerialWrite(JVT_LONG lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen);
VIDEO_NET_API bool CALL_METHOD VideoNet_SerialRead(JVT_LONG lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen, int *pReadLen);

VIDEO_NET_API int CALL_METHOD VideoNet_GetDDNSInfo(SearchMode &searchmode, DDNS_INFO *pDevicInfo, int maxDeviceNum, int &nretNum);

//nStream: 0表示主码流，为1表示子码流
VIDEO_NET_API bool CALL_METHOD VideoNet_MakeKeyFrame(JVT_LONG lLoginID, int nChannel, int nStream);

//nStream: 0表示主码流，为1表示子码流
VIDEO_NET_API bool CALL_METHOD VideoNet_GetOEMInfo(JVT_LONG lLoginID, SDK_OEMInfo *pOEMInfo);
// 创建透明串口通道
VIDEO_NET_API bool CALL_METHOD VideoNet_OpenTransComChannel(JVT_LONG lLoginID, TransComChannel *TransInfo, fTransComCallBack cbTransCom, JVT_DWORD lUser);
//关闭透明串口通道
VIDEO_NET_API bool CALL_METHOD VideoNet_CloseTransComChannel(JVT_LONG lLoginID, SERIAL_TYPE nType);
//获取状态信息
VIDEO_NET_API bool CALL_METHOD VideoNet_GetDeviceState(JVT_LONG lLoginID, SDK_State_Type type, char *pState);
//获取ui图片:type 1:为全图片 2:活动区域图片
VIDEO_NET_API bool CALL_METHOD VideoNet_CatchPicUI(JVT_LONG lLoginID,char *saveFileName,int type = 1);
//设置本地ip
VIDEO_NET_API bool CALL_METHOD VideoNet_SetLocalBindAddress(char*szIP);

//上报数据
VIDEO_NET_API bool CALL_METHOD VideoNet_StartUploadData(JVT_LONG lLoginID,UploadDataType upLoadType,fUploadDataCallBack callBack, JVT_DWORD nUser);

VIDEO_NET_API bool CALL_METHOD VideoNet_StopUploadData(JVT_LONG lLoginID,UploadDataType upLoadType);
//主动注册
VIDEO_NET_API bool CALL_METHOD VideoNet_StartActiveRigister(int nPort, fMessCallBack cbFunc, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopActiveRigister();

//子连接异常断开
VIDEO_NET_API long CALL_METHOD VideoNet_SetSubDisconnectCallBack(fSubDisConnectCallBack callBack, JVT_DWORD nUser);

//设置保活时间
VIDEO_NET_API long CALL_METHOD VideoNet_SetKeepLifeTime(JVT_LONG lLoginID,unsigned int perKeeplifeTime,unsigned int detectDisconTime);

//MAC 得到加密
VIDEO_NET_API bool CALL_METHOD VideoNet_CheckEncrypt(char *pMac);

//设备搜索到的设备，与设备在同一个局域网的设备
VIDEO_NET_API bool CALL_METHOD VideoNet_SearchDeviceEX(JVT_LONG lLoginID,SDK_NetDevList *pDevlist,SDK_TransferProtocol_V2 transferProtocol = SDK_TRANSFER_PROTOCOL_NETIP,int waittime = 15000);

//云台快速定位
//使用前 判断是否支持
VIDEO_NET_API bool CALL_METHOD VideoNet_PTZPostion(JVT_LONG lLoginID,int nChannel,SDK_PositionPoint *pPositionPoint);

///< NVR和其连接的前端对讲
VIDEO_NET_API bool CALL_METHOD VideoNet_StartDevTalk(JVT_LONG lLoginID,int nChannel,int waittime = 2000);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopDevTalk(JVT_LONG lLoginID,int nChannel,int waittime = 2000);
///<硬盘录像信息
//录像查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的录像数据，外部开内存
//waittime		查询超时时间
VIDEO_NET_API long CALL_METHOD VideoNet_RecordInfo(JVT_LONG lLoginID, SDK_SearchByTime* lpFindInfo, SDK_RecordStorageInfo *lpRecordData, int waittime = 15000);

VIDEO_NET_API bool CALL_METHOD VideoNet_ControlFile(JVT_LONG lLoginID,SDK_NetFileControl *lpFileControl,int waittime = 15000);

//录像设备里面有多少音频文件，最大8个
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的音频数据，外部开内存
//waittime		查询超时时间
VIDEO_NET_API bool CALL_METHOD VideoNet_FindAudioFile(JVT_LONG lLoginID, SDK_MusicFileList* lpFileList, int waittime = 5000);

/*
	==播放音频文件需要文件名，其他的不需要，ACTION一定要赋值
	== Action  参考 SDK_Music_Play_Action
*/
VIDEO_NET_API bool CALL_METHOD VideoNet_ControlAudio(JVT_LONG lLoginID, SDK_LocalMusicControl *lpMusicControl, int waittime = 2000);



//人脸图片
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceImageFile(JVT_LONG lLoginID,int nChannel);
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceImageFileEx(JVT_LONG lLoginID,int nChannel, int nEnable);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopReceiveFaceImageFile(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetFaceImageDataCallBack(JVT_LONG lSubHandle,fFaceImageDataCallBack cbFacePictureData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteFaceImageDataCallBack(JVT_LONG lSubHandle,fFaceImageDataCallBack cbFacePictureData, JVT_DWORD nUser);

//比对结果
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceCompareResult(JVT_LONG lLoginID,int nChannel); 
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceCompareResultEx(JVT_LONG lLoginID,int nChannel, SDK_COMPINFO_FLAG *pstCompinfoFlag); 
VIDEO_NET_API bool CALL_METHOD VideoNet_StopReceiveFaceCompareResult(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetFaceCompareResultCallBack(JVT_LONG lSubHandle,fFaceCompaeResultCallBack cbFaceCompareResult, JVT_DWORD dwUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteFaceCompareResultCallBack(JVT_LONG lSubHandle,fFaceCompaeResultCallBack cbFaceCompareResult, JVT_DWORD nUser);

//黑白名单
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartSendBlackAndWhiteList(JVT_LONG lLoginID,int nChannel);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopSendBlackAndWhiteList(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetBlackAndWhiteListCallBack(JVT_LONG lSubHandle,fFaceBlackAndWhiteListCallBack cbFaceBlackAndWhiteListData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteBlackAndWhiteListCallBack(JVT_LONG lSubHandle,fFaceBlackAndWhiteListCallBack cbFaceBlackAndWhiteListData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_OperationBlackAndWhiteListData(JVT_LONG lSubHandle,WBLIST_ACTION_TYPE ActionType,int nWBType,int nlibraryIndex,int nFileIndex,char *pFile,/* 填充参数 */int nSex = 0);
VIDEO_NET_API bool CALL_METHOD VideoNet_OperationBlackAndWhiteListDataEx(JVT_LONG lSubHandle,WBLIST_ACTION_TYPE ActionType,SDK_FA_BLACKANDWHITELIST_CONFIG WBListConfig,SDK_XM_WB_CONFIG_EXDATA ConfigData, char *pFile);

//车牌识别图片
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveCarLicensePlateImageFile(JVT_LONG lLoginID,int nChannel);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopReceiveCarLicensePlateImageFile(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetCarLicensePlateImageDataCallBack(JVT_LONG lSubHandle,fCarLicensePlateImageDateCallBack cbFacePictureData, void* nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteCarLicensePlateImageDataCallBack(JVT_LONG lSubHandle,fCarLicensePlateImageDateCallBack cbFacePictureData, void* nUser);

//P2P登录
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_Login_P2P(char* pchDVRIP, unsigned short wDVRPort, 
				   char *pchUserName, char *pchPassword, VIDEONET_DEVICEINFO* lpDeviceInfo, int *error,int socketType = 0);
VIDEO_NET_API long CALL_METHOD VideoNet_SendForHttp_P2P(char *puuid, char *pDataBuf, int iDataLen);
VIDEO_NET_API long CALL_METHOD VideoNet_RecvForHttp_P2P(char *puuid, char **pDataBuf, int *iBufSize,int timeout);

//图片查询
//lLoginID		登陆句柄
//lpFindInfo	查询条件
//lpFileData	查找到的图片数据，外部开内存
//lMaxCount		最大图片数目
//findcount		查找到的图片数目
//waittime		查询超时时间
VIDEO_NET_API long CALL_METHOD VideoNet_FindPicture(JVT_LONG lLoginID, SDK_PICTURE_FINDINFO* lpFindInfo, SDK_VIDEONET_PICTURE_DATA *lpFileData, int lMaxCount, int *findcount, int waittime = 5000);

//图片下载, 自己通过VideoNet_GetDownloadPos获取进度
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_GetPicture(JVT_LONG lLoginID, SDK_VIDEONET_PICTURE_DATA *sPictureFile,char *sSavedFileName, JVT_DWORD dwDataUser = NULL);
/*
	描述:GPIO控制
	参数:
	lLoginID[in]:		 登陆句柄
	返回值:
	=0:成功
	<0:失败
*/
VIDEO_NET_API long CALL_METHOD VideoNet_GPIOControl(JVT_LONG lLoginID, int iSecond);

//通过图片查询图片或者录像   返回值:  1成功   0失败
VIDEO_NET_API long CALL_METHOD VideoNet_Query_Photo_Record(JVT_LONG lLoginID, PICTURE_FINDINFO* lpFindInfo, VIDEONET_PICTURE_DATA *lpFileData, int lMaxCount,int waittime = 5000);

//名单库管理
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartListManagement(JVT_LONG lLoginID,int nChannel);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetListManagementCallBack(JVT_LONG lSubHandle, fListManagementCallBack cbListManagementData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteListManagementCallBack(JVT_LONG lSubHandle, fListManagementCallBack cbListManagementData, JVT_DWORD nUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_StopListManagement(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_ListManagementData(JVT_LONG lSubHandle, char* lpBuffer, unsigned long dwBufferSize, char *pFile);
//图片监视
VIDEO_NET_API JVT_LONG CALL_METHOD VideoNet_StartReceiveFaceMonitor(JVT_LONG lLoginID,int nChannel, SDK_FACEMONITOR_INFO_FLAG *pstCompinfoFlag); 
VIDEO_NET_API bool CALL_METHOD VideoNet_StopReceiveFaceMonitor(JVT_LONG lSubHandle);
VIDEO_NET_API bool CALL_METHOD VideoNet_SetFaceMonitorCallBack(JVT_LONG lSubHandle,fFaceMonitorCallBack cbFaceMonitor, JVT_DWORD dwUser);
VIDEO_NET_API bool CALL_METHOD VideoNet_DeleteFaceMonitorCallBack(JVT_LONG lSubHandle,fFaceMonitorCallBack cbFaceMonitor, JVT_DWORD nUser);

#endif
