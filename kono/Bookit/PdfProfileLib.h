#ifndef __PDF_PROFILE_H__
#define __PDF_PROFILE_H__

//============================================================
/// ImageType
typedef struct _PdfBookProfile
{
	int page_count;
	int width;
	int height;
} PdfBookProfile;

typedef enum _PdfPageComponentType
{
	TYPE_FILLPATH,
	TYPE_STROKEPATH,
	TYPE_CLIPPATH,
	TYPE_CLIPSTROKEPATH,
	TYPE_FILLTEXT,
	TYPE_STROKETEXT,
	TYPE_CLIPTEXT,
	TYPE_CLIPSTROKETEXT,
	TYPE_IGNORETEXT,
	TYPE_FILLSHADE,
	TYPE_FILLIMAGE,
	TYPE_FILLIMAGEMASK,
	TYPE_CLIPIMAGEMASK,
	TYPE_POPCLIP,
	TYPE_BEGINMASK,
	TYPE_ENDMASK,
	TYPE_BEGINGROUP,
	TYPE_ENDGROUP,
} PdfPageComponentType;

typedef struct _PdfPageComponentImage
{
	int x, y, w, h, color_depth;
	char colorspace[16];
} PdfPageComponentImage;

typedef struct _PdfPageComponent
{
	PdfPageComponentType type;
	struct _PdfPageComponent *next;
	union {
		PdfPageComponentImage *image;
	} item;
} PdfPageComponent;

typedef struct _PdfPageProfile
{
	int componet_count;
	PdfPageComponent *first;
} PdfPageProfile;

#endif /// __PDF_PROFILE_H__

