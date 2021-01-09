
#ifndef _FRAMEHEAD_H_
#define _FRAMEHEAD_H_

/* ֡ͷͬ���� */
#define SYN_START_CODE					(0xA0A46801)

/* ֡βУ���� */
#define SYN_END_CODE					(0xF0F46802)

/* ���������� */
#define VIDEO_FRAME						(0)
#define AUDIO_FRAME						(1)

/* ��Ƶ֡����(��Ƶ֡����Ĭ�϶���:0) */
#define I_FRAME							(0)
#define P_FRAME							(1)

/* �������� ---- ��Ƶ֡ */
#define MPG4_ENCODE						(0)
#define ST_MPEG4_ENCODE					(1)	/* ʥ���㷨 */
#define H264_ENCODE						(2)
//#define HI_H264_ENCODE					(2) /* ��˼ */
#define TM_H264_ENCODE					(3)
#define HI_H264_ENCODE                  (4) /*��˼����*��

/* �������� ---- ��Ƶ֡ */
#define ADPCM_ENCODE					(0)
#define G729_ENCODE						(1)
#define G721_ENCODE						(2)
#define HI_ADPCM_ENCODE					(3) /* ��˼ */
#define HI_G726_ENCODE					(4) 
#define HI_G711A_ENCODE					(5) 
#define HI_G711U_ENCODE					(6) 


typedef struct Codec_Head
{
	unsigned long	Syncode;		/* ͬ��ͷ��ֵΪ��SYN_START_CODE�� */
	unsigned short	Width;			/* ��Ƶͼ���ȣ�����Ƶ���ݸ�ֵΪ��0���� */
	unsigned short	Height;			/* ��Ƶͼ��߶ȣ�����Ƶ���ݸ�ֵΪ��0���� */
	unsigned char	StreamType;		/* ���������ͣ���ƵΪ��VIDEO_FRAME����ƵΪ��AUDIO_FRAME�� */
	unsigned char	FrameType;		/* ֡���ͣ���Ƶ֡ΪI_FRAME��P_FRAME����Ƶ֡��ֵΪ��0�� */
	unsigned short	CodecInfo;		/* �������ͣ� */
	unsigned long	TimeStamp;		/* ʱ����� */
	unsigned long	SerialNum;		/* ֡��ţ���Ƶ֡����Ƶ֡�ֱ���ö�����֡��ż������� */
	unsigned long	FrameSize;		/* ��֡ͷ֮�����������֡�غɴ�С����λ��BYTE��������֡βУ���룻 */
}Codec_Head_t,*pCodec_Head_t;

#endif /* End: #ifndef _FRAMEHEAD_H_ */
