
#ifndef _FRAMEHEAD_H_
#define _FRAMEHEAD_H_

/* 帧头同步码 */
#define SYN_START_CODE					(0xA0A46801)

/* 帧尾校验码 */
#define SYN_END_CODE					(0xF0F46802)

/* 数据流类型 */
#define VIDEO_FRAME						(0)
#define AUDIO_FRAME						(1)

/* 视频帧类型(音频帧类型默认都是:0) */
#define I_FRAME							(0)
#define P_FRAME							(1)

/* 编码类型 ---- 视频帧 */
#define MPG4_ENCODE						(0)
#define ST_MPEG4_ENCODE					(1)	/* 圣堂算法 */
#define H264_ENCODE						(2)
//#define HI_H264_ENCODE					(2) /* 海思 */
#define TM_H264_ENCODE					(3)
#define HI_H264_ENCODE                  (4) /*海思高清*、

/* 编码类型 ---- 音频帧 */
#define ADPCM_ENCODE					(0)
#define G729_ENCODE						(1)
#define G721_ENCODE						(2)
#define HI_ADPCM_ENCODE					(3) /* 海思 */
#define HI_G726_ENCODE					(4) 
#define HI_G711A_ENCODE					(5) 
#define HI_G711U_ENCODE					(6) 


typedef struct Codec_Head
{
	unsigned long	Syncode;		/* 同步头，值为：SYN_START_CODE； */
	unsigned short	Width;			/* 视频图像宽度（对音频数据该值为：0）； */
	unsigned short	Height;			/* 视频图像高度（对音频数据该值为：0）； */
	unsigned char	StreamType;		/* 数据流类型，视频为：VIDEO_FRAME；音频为：AUDIO_FRAME； */
	unsigned char	FrameType;		/* 帧类型，视频帧为I_FRAME或P_FRAME，音频帧该值为：0； */
	unsigned short	CodecInfo;		/* 编码类型； */
	unsigned long	TimeStamp;		/* 时间戳； */
	unsigned long	SerialNum;		/* 帧序号，视频帧和音频帧分别采用独立的帧序号计数器； */
	unsigned long	FrameSize;		/* 除帧头之外的所有数据帧载荷大小（单位：BYTE），包括帧尾校验码； */
}Codec_Head_t,*pCodec_Head_t;

#endif /* End: #ifndef _FRAMEHEAD_H_ */
