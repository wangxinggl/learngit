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
/*�豸����*/
#define DEVINFO_TYPE_ENCODER				0
#define DEVINFO_TYPE_DECODER				1
#define DEVINFO_TYPE_NVR					2
#define DEVINFO_TYPE_IPCAM                  3
#define DEVINFO_TYPE_NVT                  4
#define DEVINFO_TYPE_CRT                 5

/*�豸����*/
#define DEVINFO_MANUFACTURER_SJ			0
#define DEVINFO_MANUFACTURER_HIK		1
#define DEVINFO_MANUFACTURER_TST		2
#define DEVINFO_MANUFACTURER_BC			3
#define DEVINFO_MANUFACTURER_JL			4  
#define DEVINFO_MANUFACTURER_SJCRT		5
#define DEVINFO_MANUFACTURER_HH			6 
#define DEVINFO_MANUFACTURER_JL_NEW		7
/*�豸״̬*/
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
	U32 nSubDevType;		//���ֱȶԻ���ץ�Ļ�---byjfp20190227
	S8		szUUID[A1600_CLIENT_MINSTRING_LEN];	//�豸UUID
}TabDevInfo_t;

//#define CHANNELINFO_TYPE_CHANNEL				0
#define CHANNELINFO_TYPE_ALARM_IN				1
#define CHANNELINFO_TYPE_ALARM_OUT			2
#define CHANNELINFO_TYPE_QIUJI                  3	//���
#define CHANNELINFO_TYPE_QIANGJI                4	//ǹ��
#define CHANNELINFO_TYPE_GAOSUQIU               5	//������
#define CHANNELINFO_TYPE_SHEXIANGTOU            6	//����ͷ
#define CHANNELINFO_TYPE_SNAP					7	//ץ�Ļ�
#define CHANNELINFO_TYPE_COMPARE				8	//�ȶԻ�
/*ͨ��״̬*/
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
	ALARM_DISK_LOW,					//���̿ռ��
	ALARM_EventCount,
};



#define AALARM_TYPE_FIRE				0x00		//��
#define ALARM_TYPE_SMOKING				0x01		//�̸�
#define ALARM_TYPE_INFRARED				0x02        //����
#define ALARM_TYPE_GAS					0x03		//ȼ��
#define ALARM_TYPE_TEMPERATURE			0x04		//�¶�
#define ALARM_TYPE_GATING				0x05		//�Ž�
#define ALARM_TYPE_NONE					0x06	

#define ALARM_LEVEL_WARNING				0X00 //����
#define ALARM_LEVEL_MINOR				0X01  //��Ҫ
#define ALARM_LEVEL_MAJOR				0X02  //��Ҫ
#define ALARM_LEVEL_CRITICAL			0X03  //����


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

/*Ȩ�޶���*/
#define  PERMISSION_REPLAY 1 //
#define  PERMISSION_REPLAY_FINDFILE 2 //
#define  PERMISSION_REPLAY_DOWNLOAD 3 //
#define  PERMISSION_REPLAY_DEVCONF 4 //


#define		SNAP_TIME_LEN		32
#define		PICTURE_NAME_LEN	64
#define		DEVICE_IP_LEN		16
#define		MAX_PATH_LEN		128

#define		LIB_MAX_ROW   			100000		//�ȶԼ�¼�������
#define		FACE_CMPMAX_PAGENUM     10			//�ȶ�ҳ��
#define		FACE_CMPWEB_PAGENUM      	5
#define		ITEM_NUM   					1
#define		MAX_DEVICE_NUMBER		32			//��������豸
#define		DB_CLEAR_INTERVAL		24 * 60 * 60 * 1000		//һ��

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

//�ȶԼ�¼
typedef struct SMART_FACE_CMP_QUERY_INFO_
{
	int					sLibRowid;				//���к�
	float				sLibSimilarity;			//���ƶ�	

	char				sName[64];				//����(��ѡ)
	char				sUserID[36];			//�û�ID(��ѡ)
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
	char				sSnappicname[80];		//ʵʱ�ȶ�ͼƬ����
	char				sBackPicName[80];		//����ͼƬ����
	char				sBodyPicName[80];		//����ͼƬ����
	char				sLibPicName[80];		//��ͼƬ����
	char				cRes[3];
	int					nFaceAlarm;				//����
	unsigned long		dwSnapPicLen;			//ʵʱ�ȶ�ͼƬ����
	unsigned long		dwBackPicLen;			//����ͼƬ����
	unsigned long		dwBodyPicLen;			//����ͼƬ����
	unsigned long		dwLibPicLen;			//��ͼƬ����
	char				cPath[MAX_PATH];		//����·��
	char				cDevName[A1600_CLIENT_MAXSTRING_LEN];	//�豸����
	char				cDeviceIP[A1600_CLIENT_MAXSTRING_LEN];	//�豸IP
	char*				pSnapPicBuf;			//ץ��ͼ����
	char*				pBackPicBuf;			//����ͼ����
	char*				pBodyPicBuf;			//����ͼ����
	char*				pLibPicBuf;				//��ͼ����
}SMART_FACE_CMP_QUERY_INFO;

typedef struct _FS_DEV_INFO
{
	unsigned int	nDeviceid;		//�豸ID
	unsigned int	nChannelid;		//ͨ��ID
	char  cDeviceIP[20];	//�豸IP
	unsigned char sMac[32];		//!MAC��ַ
	unsigned char 	Res[56];		//Ԥ�� 	
}FS_DEV_INFO;

typedef struct _FS_Find_INFO_S		
{
	char  StartTime[32];
	char  EndTime[32];
	char  name[32];		//����
	char  number[32];
	int   Wbmode;
	int   cmd;	
	int   curpage;		//��ǰҳ��
	int   flag;
	int   pagecount;	//��ҳ��
	int	  nDevNumber;	//�����豸��
	FS_DEV_INFO fsDevInfo[MAX_DEVICE_NUMBER];
	char IpAddr[256];
	unsigned char 	Res[56];		//Ԥ�� 	
} FS_FIND_INFO;

typedef enum _FIND_SELECT_CONDITION_
{
	CONDITION_ZORE		= 0x00,		//ʱ��
	CONDITION_ONE		= 0x01,		//ʱ�䣬���
	CONDITION_TWO		= 0x02,	    //ʱ�䣬����
	CONDITION_THR		= 0x03,		//ʱ�䣬���������
	CONDITION_FOUR		= 0x04,		//ʱ�䣬��������
	CONDITION_FIVE		= 0x05,		//ʱ�䣬��ţ���������
	CONDITION_SIX		= 0x06,		//ʱ�䣬��������������
	CONDITION_SEV		= 0x07,		//ʱ�䣬��������ţ���������
	CONDITION_EIG		= 0x08,		//ʱ�䣬IP��ַ
	CONDITION_NINE		= 0x09,		//ʱ�䣬IP��ַ�����
	CONDITION_TEN		= 0x0A,		//ʱ�䣬IP��ַ������
	CONDITION_ELEVEN	= 0x0B,		//ʱ�䣬IP��ַ�����������
	CONDITION_TWELVE	= 0x0C,		//ʱ�䣬IP��ַ����������
	CONDITION_THIRTEEN	= 0x0D,		//ʱ�䣬IP��ַ����ţ���������
	CONDITION_FOURTEEN	= 0x0E,		//ʱ�䣬IP��ַ����������������
	CONDITION_FIFTEEN	= 0x0F,		//ʱ�䣬IP��ַ����������ţ���������
}FIND_SELECT_CONDITION;

typedef enum _FIND_FLAG
{
	FLAG_SEARCH_COMMON		= 0x00,		//��ҳ��ѯ
	FLAG_SEARCH_FIRST		= 0x01,		//��һ�β�ѯ
	FLAG_SEARCH_EXPORT		= 0x02,		//������һ�β�ѯ
	FLAG_SEARCH_EXPORT_COMMON = 0x03,	//������ҳ��ѯ
};


//�ȶԽ��
typedef struct _FACET_MONITOR_INFO_S		
{
	unsigned int	deviceid;
	unsigned int	channelid;
	unsigned int	streamid;
	unsigned int	wbmode; 				//�ڰ�����
	unsigned int	libindex;				//�ڰ�����������
	unsigned int	libnumber;				//�ڰ�����������
	char	picnameComp[PICTURE_NAME_LEN];		//��ͼͼƬ����
	char	*pCompImgData;					//��ͼͼƬ����ָ��
	int		iCompImgSize;					//��ͼͼƬ���ݳ���
	char	picnameSnap[PICTURE_NAME_LEN];		//ʵʱ�ȶ�ͼƬ����
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
}FACET_MONITOR_INFO; 

#endif /* __A1600CLIENT_TABLE_STRUCTS_HEADER__ */

