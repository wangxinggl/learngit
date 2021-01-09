#pragma  once
#include <QPoint>
#include "../include/VideoNetAPI.h"
#define  OCX_BACK_COLOR		RGB(0, 0,   0)		//RGB(99,125,174)
#define  OCX_SELECT_COLOR	RGB(0, 255 ,255)
#define  OCX_BORDER_CLOLOR	RGB(106, 106, 106)
#define  OCX_STATUS_CLOLOR	RGB(255, 255, 0)

#define   DRAW_LINE_COUNT				1
#define   DRAW_RECTANGLE_COUNT			4
#define   DRAW_TRIANGLE_COUNT			4
#define   DRAW_QUADRILATERA_COUNT		4

typedef struct _DEV_ATTRIBUTE
{
	VIDEONET_DEVICEINFO deviveInfo;
	SDK_CONFIG_NORMAL   NormalConfig;
}DEV_ATTRIBUTE;



typedef struct
{
	QString strText;
	DWORD dwSize;
	DWORD dsMask;
}SResolution;

static int STREAM_CODE_VALUE[SDK_CAPTURE_SIZE_NR][6] = {
	{ 512, 768, 1024, 1536, 2048, 2560 },	///< D1
	{ 384, 512, 768, 1024, 1536, 2048 },	///< HD1
	{ 384, 512, 768, 1024, 1536, 2048 },	///< BCIF
	{ 64, 192, 384, 512, 768, 1024 },		///< CIF
	{ 64, 128, 192, 384, 448, 512 },	///< QCIF
	{ 512, 768, 896, 1280, 1536, 2048 },	///< VGA
	{ 256, 384, 512, 640, 768, 1024 },	///< QVGA
	{ 512, 768, 896, 1280, 1536, 2048 },	///< SVCD
	{ 64, 128, 192, 384, 448, 512 },	///< QQVGA
	{ 64, 128, 256, 448, 512, 768 },	///< ND1
	{ 896, 1024, 1536, 2048, 3072, 4096 },	///< 650TVL
	{ 1024, 1536, 2048, 2560, 3072, 4096 },	///< 720P
	{ 1024, 1536, 2048, 3072, 4096, 5120 },	///< 1_3M
	{ 1024, 2048, 3072, 4096, 6144, 8192 },	///< UXGA
	{ 1024, 2048, 3072, 4096, 6144, 8192 }, ///< 1080P
	{ 1177, 2355, 3532, 4710, 7065, 10240 }, ///< WUXGA
	{ 1280, 2560, 3840, 5120, 7680, 10240 }, ///< 2_5M
	{ 1536, 3072, 4096, 6144, 8192, 10240 }, ///< 3M
	{ 2048, 3072, 4096, 6144, 8192, 10240 }, ///5M
	{ 1024, 2048, 3072, 4096, 6144, 8192 }, ///1080PN
	{ 2048, 3072, 4096, 6144, 8192, 10240 }, ///4M
	{ 2048, 3072, 4096, 6144, 8192, 10240 }, ///6M
	{ 2048, 3072, 4096, 6144, 8192, 10240 }, ///8M
	{ 2048, 3072, 4096, 6144, 8192, 10240 }, ///12M
	{ 2048, 3072, 4096, 6144, 8192, 10240 } ///4K
};

enum
{
	MAIN_STREAM = 0,
	EXPAND_STREAM,
	COMBINE_STREAM,
	STREAM_NUM,
};

enum
{
	CONTROL_RESOLUTION,
	CONTROL_FRAME,
	CONTROL_BITCONTROL,
	CONTROL_QUALITY,
	CONTROL_BIT_RATE,
	CONTROL_GOP,
	CONTROL_VIDEO,
	CONTROL_AUDIO,
	CONTROL_FORMAT,
	CONTROL_NUM,
};

enum
{
	EM_AnalyseEncode,  //ÖÇÄÜ±àÂë
	EM_AnalyseShelter, //»­¾ØÐÎ
	EM_AnalyseOverStep, //Ô½½çÕì²â
	EM_AnalyseAreaInvade,//ÇøÓòÈëÇÖ
	EM_AnalyseCarryOver,//ÒÅÁôÎï
	EM_FaceShelter, //ÈËÁ³ÇøÓò
	EM_AnalyseShiled,//ÈËÁ³ÆÁ±Î
	EM_FaceRWL_Import, //ºÚ°×Ãûµ¥
	EM_FaceRWL_Verify, //ÈËÁ³Ê¶±ð¶Ô±È
	Analyse_type_COUNT,
};
enum
{
	DRAW_PEN_Line,
	DRAW_PEN_Rectangle,
	DRAW_PEN_Triangle,
	DRAW_PEN_Quadrilateral,
	DRAW_PEN_COUNT,
};

typedef struct _tagRECTANGLE_COORDINATE
{
	int  nPointNumber;
	BOOL bDrawFinish;
	QPoint RectanglePoint[2];
	_tagRECTANGLE_COORDINATE()
	{
		memset(this, 0x00, sizeof(_tagRECTANGLE_COORDINATE));
	}
	QPoint Point[2];
}RECTANGLE_COORDINATE;

typedef struct _tagQUADRILATERAL_COORDINATE
{
	int  nPointNumber;
	BOOL bDrawFinish;
	QPoint QuadrilateralPoint[4];
	_tagQUADRILATERAL_COORDINATE()
	{
		memset(this, 0x00, sizeof(_tagQUADRILATERAL_COORDINATE));
	}
}QUADRILATERAL_COORDINATE;

typedef struct _tagTRIANGLE_COORDINATE
{
	int  nPointNumber;
	BOOL bDrawFinish;
	QPoint TrianglePoint[3];
	_tagTRIANGLE_COORDINATE()
	{
		memset(this, 0x00, sizeof(_tagTRIANGLE_COORDINATE));
	}
}TRIANGLE_COORDINATE;

typedef struct _tagLINE_COORDINATE
{
	int nArrowDirection;
	BOOL bDrawFinish;
	QPoint LinePoint[2];

	_tagLINE_COORDINATE()
	{
		memset(this, 0x00, sizeof(_tagLINE_COORDINATE));
	}

}LINE_COORDINATE;

enum LanguageTypes
{
	ENGLISH,		//Ó¢Óï
	CHINESE_S,		//¼òÌåÖÐÎÄ
	CHINESE_T,		//·±ÌåÖÐÎÄ
	ITALIAN,		//Òâ´óÀûÓï
	SPANISH,		//Î÷°àÑÀÓï
	JAPANESE,		//ÈÕÓï
	RUSSIAN,		//¶íÓï
	FRENCH,			//·¨Óï
	GERMAN,			//µÂÓï
	PORTUGAL,		//ÆÏÌÑÑÀÎÄ
	TURKEY,			//ÍÁ¶úÆäÎÄ
	POLAND,			//²¨À¼ÎÄ
	ROMANIAN,       //ÂÞÂíÄáÑÇ
	HUNGARIAN,      //ÐÙÑÀÀûÓï
	FINNISH,		//·ÒÀ¼Óï
	ESTONIAN,	    //°®É³ÄáÑÇÓï
	KOREAN,		    //º«Óï
	FARSI,          //²¨Ë¹Óï 
	DANSK,			//µ¤ÂóÓï
	THAI,			//Ì©¹úÓï
	GREEK,			//Ï£À°Óï
	VIETNAMESE,		//Ô½ÄÏÓï
	UKRAINIAN,      //ÎÚ¿ËÀ¼Óï
	BRAZILIAN,      //°ÍÎ÷Óï
	HEBREW,         //Ï£²®À´Óï
	INDONESIAN,     //Ó¡ÄáÓï
	ARABIC,         //°¢À­²®Óï
	SWEDISH,        //ÈðµäÓï
	CZECH,          //½Ý¿ËÓï
	BULGARIAN,      //±£¼ÓÀûÑÇ
	SLOVAKIA,		//Ë¹Âå·¥¿ËÓï
	DUTCH,			//ºÉÀ¼Óï
	LANG_NR
};

struct ConfigPair
{
	const char* name;
	int value;
};


static ConfigPair s_language[] =
{
	{ "English", ENGLISH },
	{ "SimpChinese", CHINESE_S },
	{ "TradChinese", CHINESE_T },
	{ "Italian", ITALIAN },
	{ "Spanish", SPANISH },
	{ "Japanese", JAPANESE },
	{ "Russian", RUSSIAN },
	{ "French", FRENCH },
	{ "German", GERMAN },
	{ "Portugal",PORTUGAL },
	{ "Turkey",TURKEY },
	{ "Poland",POLAND },
	{ "Romanian",ROMANIAN },
	{ "Hungarian",HUNGARIAN },
	{ "Finnish",FINNISH },
	{ "Estonian",ESTONIAN },
	{ "Korean",KOREAN },
	{ "Farsi",FARSI },
	{ "Dansk",DANSK },
	{ "Thai", THAI },
	{ "Greek", GREEK },
	{ "Vietnamese", VIETNAMESE },
	{ "Ukrainian", UKRAINIAN },
	{ "Brazilian", BRAZILIAN },
	{ "Hebrew", HEBREW },
	{ "Indonesian", INDONESIAN },
	{ "Arabic", ARABIC },
	{ "Swedish", SWEDISH },
	{ "Czech", CZECH },
	{ "Bulgarian", BULGARIAN },
	{ "Slovakia", SLOVAKIA },
	{ "Dutch", DUTCH },
	{ NULL, }
};
