#ifndef __KOOBERENDER_PUBLIC_H__
#define __KOOBERENDER_PUBLIC_H__

//============================================================
/// ImageType
typedef enum _ImageType
{
	ImageType_BMP,
	ImageType_PNG,
	ImageType_REF,
} ImageType;

typedef enum _ImageColorspace
{
	ImageColorspace_GRAY=0,
	ImageColorspace_RGB,
	ImageColorspace_BGR,
	ImageColorspace_CMYK
} ImageColorspace;


#  ifdef __cplusplus
extern "C" {
#  endif /* __cplusplus */

class IRenderCallback
{
public:
	virtual BOOKIT_ERR_CODE setRandAccessMode(bool bRandomMode) = 0;
	virtual BOOKIT_ERR_CODE getRandAccessMode(bool* bpRandomMode) = 0;
	virtual BOOKIT_ERR_CODE getPartialData_CRTSafe(const char* href, unsigned char* dataOut, const UINT32 nFrom, const UINT32 nTo, bool bEnableSeek, bool bEnableRead) = 0;
	virtual BOOKIT_ERR_CODE getData_CRTSafe(const char* href, /*out with default buffer*/char* dataOut, UINT32 *outsize) = 0;
	virtual BOOKIT_ERR_CODE getHrefByID(const char* szID,const char** pszHref) = 0;
};


#  ifdef __cplusplus
}
#  endif /* __cplusplus */

#endif /// __KOOBERENDER_PUBLIC_H__

