#ifndef __A1600CLIENT_TABLE_STRUCTS_HEADER__
#define __A1600CLIENT_TABLE_STRUCTS_HEADER__

/*---------------------------Includes----------------------------*/
#include "basetypes.h"
#include <Windows.h>
#include <QString>

/*---------------------------Defines----------------------------*/
#define A1600_CLIENT_MINSTRING_LEN              64
#define A1600_CLIENT_MAXSTRING_LEN				256

/* table name */
#define A1600_CLIENT_TAB_USERINFO					"UserInfo"
#define A1600_CLIENT_TAB_DEVINFO					"DevInfo"
#define A1600_CLIENT_TAB_CHANNELINFO			"ChannelInfo"
#define A1600_CLIENT_TAB_USERDEVGROUP		"UserDevGroup"
#define A1600_CLIENT_TAB_DEVGROUP				"DevGroup"
#define A1600_CLIENT_TAB_PRESETPOS				"PresetPos"
#define A1600_CLIENT_TAB_TRACKSEQUENCE     "TrackSequence"
#define A1600_CLIENT_TAB_TRACKPOS					"TrackPos"
#define A1600_CLIENT_TAB_COMMONCFG			"CommonCfg"
#define A1600_CLIENT_TAB_									" "



/*---------------------------Struts----------------------------*/
/*
 * UserInfo Table
 */
typedef struct
{
	U32	nUId;
	S8		szUserName[A1600_CLIENT_MINSTRING_LEN];
	S8		szPassword[A1600_CLIENT_MINSTRING_LEN];
}TabUserInfo_t;

/*
 * DevInfo Table
 */
/*设备类型*/
#define DEVINFO_TYPE_ENCODER				0
#define DEVINFO_TYPE_DECODER				1
#define DEVINFO_TYPE_NVR					2
#define DEVINFO_TYPE_IPCAM                  3
#define DEVINFO_TYPE_NVT                  4
#define DEVINFO_TYPE_CRT                 5

/*设备厂家*/
#define DEVINFO_MANUFACTURER_SJ			0
#define DEVINFO_MANUFACTURER_HIK		1
#define DEVINFO_MANUFACTURER_TST		2
#define DEVINFO_MANUFACTURER_BC			3
#define DEVINFO_MANUFACTURER_JL			4  
#define DEVINFO_MANUFACTURER_SJCRT		5
#define DEVINFO_MANUFACTURER_HH			6 
#define DEVINFO_MANUFACTURER_JL_NEW		7
/*设备状态*/
#define DEVINFO_DEVSTATUS_ONLINE		0
#define DEVINFO_DEVSTATUS_OFFLINE		1
typedef struct
{
	U32	nDevId;
	S8		szIpAddr[A1600_CLIENT_MINSTRING_LEN];
	U32	nPort;
	S8		szLoginName[A1600_CLIENT_MINSTRING_LEN];
	S8		szPassword[A1600_CLIENT_MINSTRING_LEN];
	S8		szDevName[A1600_CLIENT_MAXSTRING_LEN];
	U32	nType;
	U32	nManufacturer;
	S8		szDevType[A1600_CLIENT_MINSTRING_LEN];
	U32	nDevStatus;
	U32 nSubDevType;		//区分比对机，抓拍机---byjfp20190227
	S8		szUUID[A1600_CLIENT_MINSTRING_LEN];	//设备UUID
}TabDevInfo_t;

//#define CHANNELINFO_TYPE_CHANNEL				0
#define CHANNELINFO_TYPE_ALARM_IN				1
#define CHANNELINFO_TYPE_ALARM_OUT			2
#define CHANNELINFO_TYPE_QIUJI                  3	//球机
#define CHANNELINFO_TYPE_QIANGJI                4	//枪机
#define CHANNELINFO_TYPE_GAOSUQIU               5	//高速球
#define CHANNELINFO_TYPE_SHEXIANGTOU            6	//摄像头
#define CHANNELINFO_TYPE_SNAP					7	//抓拍机
#define CHANNELINFO_TYPE_COMPARE				8	//比对机
/*通道状态*/
#define CHANNELINFO_STATUS_OPEN         1
#define CHANNELINFO_STATUS_CLOSE        0

typedef struct
{
	U32	SlaveDevId;
	U32	DevId;
	U32	Channel;
	S8		szChannelName[A1600_CLIENT_MAXSTRING_LEN];
	U32	Type;
	U32	Status;
}TabChannelInfo_t;

typedef struct
{
	U32	Id;
	S8		szGroupName[A1600_CLIENT_MAXSTRING_LEN];
    U32	ParentId;
}TabUserDevGroup_t;

typedef struct
{
	U32	Id;
	U32	GroupId;
	U32	SlaveDevId;
}TabDevGroup_t;
typedef struct
{
	U32	Id;
	U32	X;
	U32	Y;
	U32	DevId;
	U32	X2;
	U32	Y2;
}TabTvWallBind_t;

typedef struct
{
	U32	nId;
	S8		szPicPath[A1600_CLIENT_MAXSTRING_LEN];
	S8		szVideoPath[A1600_CLIENT_MAXSTRING_LEN];
	S8		szDownPath[A1600_CLIENT_MAXSTRING_LEN];
	U32	nTVWallV;
	U32	nTVWallH;
	U32 nBeginDriver;
	U32 nEndDriver;
	U32 nFileTimeLen;
	U32 nCycleRecord;
	S8		szSnapPath[A1600_CLIENT_MAXSTRING_LEN];
	U32 nPlayType;
}TabCommonCfg_t;

typedef struct
{
	U32	Id;
	U32	SlaveDevId;
	U32	PresetNo;
	S8		szPresetDesc[A1600_CLIENT_MAXSTRING_LEN];
}TabPresetPos_t;

typedef struct
{
	U32	Id;
	U32	SlaveDevId;
	U32	TrackNo;
	S8		szTrackDesc[A1600_CLIENT_MAXSTRING_LEN];
}TabTrackSequence_t;

typedef struct
{
	U32  Id;
	U32	TrackSeq;
	U32	PresetPos;
	U32	StayTime;
	U32	PatrolIndex;
}TabTrackPos_t;

typedef struct
{
	U32  Id;
	U32	WinIndex;
	U32	SlaveDevId;
	U32	StayTime;
	U32	PatrolIndex;
}TabVideoPatrol_t;

enum ALARM_EVENT
{
	ALARM_SOURCE_ALARMIN = 0,
	ALARM_SOURCE_MOVING_DETECT,
	ALARM_SOURCE_LOSE_SIGNAL,
	ALARM_DISK_BAD,
	ALARM_CRT_SERVER,
	ALARM_SOURCE_VIDEO_BLIND,
	ALARM_EventBrightness,
	ALARM_EventShelter,
	ALARM_EventCrossLine,
	ALARM_EventCrossArea,
	ALARM_EventColor,
	ALARM_EventSound,
	ALARM_EventLoseOBJ,
	ALARM_DISK_LOW,					//磁盘空间低
	ALARM_EventCount,
};



#define AALARM_TYPE_FIRE				0x00		//火警
#define ALARM_TYPE_SMOKING				0x01		//烟感
#define ALARM_TYPE_INFRARED				0x02        //红外
#define ALARM_TYPE_GAS					0x03		//燃气
#define ALARM_TYPE_TEMPERATURE			0x04		//温度
#define ALARM_TYPE_GATING				0x05		//门禁
#define ALARM_TYPE_NONE					0x06	

#define ALARM_LEVEL_WARNING				0X00 //警告
#define ALARM_LEVEL_MINOR				0X01  //次要
#define ALARM_LEVEL_MAJOR				0X02  //主要
#define ALARM_LEVEL_CRITICAL			0X03  //严重


typedef struct
{
	U32 Id;                                   
	U32 DevId;                             
	U32 AlarmSource;                  
	U32 Channel;                         
	S8   szAlarmName[A1600_CLIENT_MAXSTRING_LEN];                   
	U32 AlarmType;                     
	U32 AlarmLevel;                     
	U32 Video;                             
	U32 Audio;                             
	U32 Email;                             
	U32 Emap;                             
	U32 TVWall;                           
	U32 AlarmOut; 
}TabAlarmConf_t;

typedef struct
{
	U32 Id;                                   
	U32 AlarmConfId;                             
	S8   szBeginTime[A1600_CLIENT_MAXSTRING_LEN];
	S8   szEndTime[A1600_CLIENT_MAXSTRING_LEN];
}TabAlarmLog_t;                     

typedef struct
{
	U32 Id;                                   
	U32 PresetPosId;                                             
	U32 SlaveDevId;                                             
}TabAlarmVideo_t;  

typedef struct
{
	U32 Id;                                                               
	S8   szFileName[A1600_CLIENT_MAXSTRING_LEN];                                    
}TabAlarmAudio_t;  

typedef struct
{
	U32 Id;
	S8   szName[A1600_CLIENT_MAXSTRING_LEN];                                    
	S8   szPath[A1600_CLIENT_MAXSTRING_LEN];                                    
	S8   szDesc[A1600_CLIENT_MAXSTRING_LEN];                                    
}TabEmap_t;

typedef struct
{
	U32 Id;
	U32 EmapId;
	S8   szName[A1600_CLIENT_MAXSTRING_LEN];                                    
	U32 Type;
	U32 X;
	U32 Y;
	S8   szDesc[A1600_CLIENT_MAXSTRING_LEN];                                    
}TabEmapItem_t;

/*权限定义*/
#define  PERMISSION_REPLAY 1 //
#define  PERMISSION_REPLAY_FINDFILE 2 //
#define  PERMISSION_REPLAY_DOWNLOAD 3 //
#define  PERMISSION_REPLAY_DEVCONF 4 //


#define		SNAP_TIME_LEN		32
#define		PICTURE_NAME_LEN	64
#define		DEVICE_IP_LEN		16
#define		MAX_PATH_LEN		128

#define		LIB_MAX_ROW   			100000		//比对记录最大条数
#define		FACE_CMPMAX_PAGENUM     10			//比对页数
#define		FACE_CMPWEB_PAGENUM      	5
#define		ITEM_NUM   					1
#define		MAX_DEVICE_NUMBER		32			//接入最大设备
#define		DB_CLEAR_INTERVAL		24 * 60 * 60 * 1000		//一天

typedef enum _FACE_ATTRIBUTE_CATEGORY_E
{
	SF_NONE 		= 0x0,
	SF_MAN  		= 0x1,
	SF_WOMAN  		= 0x2,
	SF_GLASSES  	= 0x3,
	SF_SUNGLASSES	= 0x4,
	SF_SMILE 		= 0x5,
	SF_MASK		= 0x6,
	SF_YELLOW		= 0x7,
	SF_BLACK		= 0x8,
	SF_WHITE		= 0x9,
	SF_EYE_CLOSE	= 0xa,
	SF_EYE_OPEN	= 0xb,
	SF_MOUTH_CLOSE=0xc,
	SF_MOUTH_OPEN= 0xd,
	SF_BEARD		= 0xe,
	SF_ANGRY		= 0xf,
	SF_CLAM		= 0x10,
	SF_DISGUST		= 0x11,
	SF_HAPPY		= 0x12,
	SF_SAD 			= 0x13,
	SF_SCARED		= 0x14,
	SF_SQUINT 		= 0x15,
	SF_SCREAM 		= 0x16,
	SF_SURPRISED	= 0x17,	
}FACE_ATTRIBUTE_CATEGORY_E;

//比对记录
typedef struct SMART_FACE_CMP_QUERY_INFO_
{
	int					sLibRowid;				//库行号
	float				sLibSimilarity;			//相似度	

	char				sName[64];				//名称(可选)
	char				sUserID[36];			//用户ID(可选)
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
	char				sSnappicname[80];		//实时比对图片名字
	char				sBackPicName[80];		//背景图片名称
	char				sBodyPicName[80];		//人形图片名称
	char				sLibPicName[80];		//库图片名称
	char				cRes[3];
	int					nFaceAlarm;				//报警
	unsigned long		dwSnapPicLen;			//实时比对图片长度
	unsigned long		dwBackPicLen;			//背景图片长度
	unsigned long		dwBodyPicLen;			//人形图片长度
	unsigned long		dwLibPicLen;			//库图片长度
	char				cPath[MAX_PATH];		//保存路径
	char				cDevName[A1600_CLIENT_MAXSTRING_LEN];	//设备名称
	char				cDeviceIP[A1600_CLIENT_MAXSTRING_LEN];	//设备IP
	char*				pSnapPicBuf;			//抓拍图数据
	char*				pBackPicBuf;			//背景图数据
	char*				pBodyPicBuf;			//人性图数据
	char*				pLibPicBuf;				//库图数据
}SMART_FACE_CMP_QUERY_INFO;

typedef struct _FS_DEV_INFO
{
	unsigned int	nDeviceid;		//设备ID
	unsigned int	nChannelid;		//通道ID
	char  cDeviceIP[20];	//设备IP
	unsigned char sMac[32];		//!MAC地址
	unsigned char 	Res[56];		//预留 	
}FS_DEV_INFO;

typedef struct _FS_Find_INFO_S		
{
	char  StartTime[32];
	char  EndTime[32];
	char  name[32];		//姓名
	char  number[32];
	int   Wbmode;
	int   cmd;	
	int   curpage;		//当前页数
	int   flag;
	int   pagecount;	//总页数
	int	  nDevNumber;	//搜索设备数
	FS_DEV_INFO fsDevInfo[MAX_DEVICE_NUMBER];
	char IpAddr[256];
	unsigned char 	Res[56];		//预留 	
} FS_FIND_INFO;

typedef enum _FIND_SELECT_CONDITION_
{
	CONDITION_ZORE		= 0x00,		//时间
	CONDITION_ONE		= 0x01,		//时间，编号
	CONDITION_TWO		= 0x02,	    //时间，姓名
	CONDITION_THR		= 0x03,		//时间，姓名，编号
	CONDITION_FOUR		= 0x04,		//时间，名单类型
	CONDITION_FIVE		= 0x05,		//时间，编号，名单类型
	CONDITION_SIX		= 0x06,		//时间，姓名，名单类型
	CONDITION_SEV		= 0x07,		//时间，姓名，编号，名单类型
	CONDITION_EIG		= 0x08,		//时间，IP地址
	CONDITION_NINE		= 0x09,		//时间，IP地址，编号
	CONDITION_TEN		= 0x0A,		//时间，IP地址，姓名
	CONDITION_ELEVEN	= 0x0B,		//时间，IP地址，姓名，编号
	CONDITION_TWELVE	= 0x0C,		//时间，IP地址，名单类型
	CONDITION_THIRTEEN	= 0x0D,		//时间，IP地址，编号，名单类型
	CONDITION_FOURTEEN	= 0x0E,		//时间，IP地址，姓名，名单类型
	CONDITION_FIFTEEN	= 0x0F,		//时间，IP地址，姓名，编号，名单类型
}FIND_SELECT_CONDITION;

typedef enum _FIND_FLAG
{
	FLAG_SEARCH_COMMON		= 0x00,		//分页查询
	FLAG_SEARCH_FIRST		= 0x01,		//第一次查询
	FLAG_SEARCH_EXPORT		= 0x02,		//导出第一次查询
	FLAG_SEARCH_EXPORT_COMMON = 0x03,	//导出分页查询
};


//比对结果
typedef struct _FACET_MONITOR_INFO_S		
{
	unsigned int	deviceid;
	unsigned int	channelid;
	unsigned int	streamid;
	unsigned int	wbmode; 				//黑白名单
	unsigned int	libindex;				//黑白名单库索引
	unsigned int	libnumber;				//黑白名单库里编号
	char	picnameComp[PICTURE_NAME_LEN];		//库图图片名字
	char	*pCompImgData;					//库图图片数据指针
	int		iCompImgSize;					//库图图片数据长度
	char	picnameSnap[PICTURE_NAME_LEN];		//实时比对图片名字
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
}FACET_MONITOR_INFO; 

#endif /* __A1600CLIENT_TABLE_STRUCTS_HEADER__ */

