#ifndef __KOOBEDRM_PUBLIC_H__
#define __KOOBEDRM_PUBLIC_H__

#include "Koobe_Common.h"

//============================================================
/// Definitions for KoobeDRM
#define LEN_SN                      100
#define LEN_APP_NAME                20
#define LEN_APP_VERSION             10
#define LEN_DEVICE_MODEL            20
#define LEN_PROJECT_CODE            20
#define LEN_PLATFORM                20
#define LEN_LANG                    10
#define LEN_COLOR_RESOLUTION        20

#define DB_PATH_SIZE                255
#define IMG_PATH_SIZE               255

#define LEN_USER_ID                 64
#define LEN_MERCHANT_ID             64
#define LEN_ACCOUNT                 64
#define LEN_PASSWORD                64
#define LEN_LAST_UPDATE_TIME        64
#define LEN_BOOK_ID                 100
#define LEN_REVISION                10
#define LEN_FORMAT                  10
#define LEN_TITLE                   100
#define LEN_DOWNLOADURL             255
#define LEN_AUTHOR                  64      //paddy 2011.02.23
#define LEN_PAGE                    10      //paddy 2011.02.23
#define LEN_CHANNEL                 128     //paddy 2011.03.22
#define LEN_MTITLE                  128     //paddy 2011.03.22
#define LEN_FILESIZE				64

#define KOOBE_DRM_KEY_LEN           32
#define KOOBE_DRM_IV_LEN            16
#define ENCRYPT_DRM_KEY_LEN         (KOOBE_DRM_KEY_LEN<<1)
#define ENCRYPT_DRM_IV_LEN          (KOOBE_DRM_IV_LEN<<1)
#define KOOBE_DRM_RK_NUM            5


//paddy add
typedef enum _KOOBE_DB_OP {
	DB_OP_ADD,
	DB_OP_UPDATE,
	DB_OP_DELETE,
	DB_OP_QUERY,
	DB_OP_UNKNOW
} KOOBE_DB_OP;
//..

typedef enum _BOOKLIST_FILTER {
    BOOKLIST_ALL_DB,
    BOOKLIST_NEW,
    BOOKLIST_HAS_DOWNLOAD,
    BOOKLIST_NOT_DOWNLOAD,
    BOOKLIST_HAS_DOWNLOAD_BUT_DEL,
    BOOKLIST_ALL_CLOUD, // test only
} BOOKLIST_FILTER;

typedef enum _SYNCDB_FILTER {
    SYNCDB_NEW,
    SYNCDB_ALL
} SYNCDB_FILTER;

typedef enum _SELL_CHANNEL {
    APPLE_STORE,
    ANDROID_MARKET
} SELL_CHANNEL;

typedef enum _USER_LOG_ACTION {
    USER_LOG_OPEN,
    USER_LOG_CLOSE,
    USER_LOG_READ,
    USER_LOG_SEARCH,
    USER_LOG_NOTE,
    USER_LOG_MARK,
    USER_LOG_BOOKMARK
} USER_LOG_ACTION;

typedef enum _DRM_PERIOD {
    DRM_PERIOD_DAY,
    DRM_PERIOD_MONTH
} DRM_PERIOD;

typedef enum _AD_TYPE {
    AD_VIDEO_MPEG4,
    AD_IMAGE,
    AD_HTML,
    AD_TOTAL
} AD_TYPE;


//============================================================
/// Data Structure for KoobeDRM & Biz Logic
typedef struct _PLATFORM_INFO {
    char strAppName[LEN_APP_NAME];
    char strAppVersion[LEN_APP_VERSION];
    char strDeviceModel[LEN_DEVICE_MODEL];
    char strProjectCode[LEN_PROJECT_CODE];
    char strPlatform[LEN_PLATFORM];
    char strLang[LEN_LANG];
    char strColorResolution[LEN_COLOR_RESOLUTION];
} PLATFORM_INFO;

typedef struct _DEVICE_INFO {
    char strSN[LEN_SN];
    PLATFORM_INFO sPlatformInfo;
} DEVICE_INFO;

typedef struct _ENCRYPT_KEY_INFO {
    BYTE strKey[ENCRYPT_DRM_KEY_LEN];
    BYTE strIv[ENCRYPT_DRM_IV_LEN];
} ENCRYPT_KEY_INFO;

typedef struct _RAW_KEY_INFO {
    BYTE strKey[KOOBE_DRM_KEY_LEN];
    BYTE strIv[KOOBE_DRM_IV_LEN];
} RAW_KEY_INFO;

typedef struct _KOOBE_RK_DATA {
    RAW_KEY_INFO sKey[KOOBE_DRM_RK_NUM];
} KOOBE_RK_DATA;

typedef struct _BIZ_LOGIC_ENVIRONMENT {
    char strUserId[LEN_USER_ID];
    char strDBPath[DB_PATH_SIZE];
    char strImgPath[IMG_PATH_SIZE];
    bool bIsAutoEnKeyManage;
    KOOBE_RK_DATA *psRKData;
} BIZ_LOGIC_ENVIRONMENT;

typedef struct _ACCOUNT_DATA {
    char strUserId[LEN_USER_ID];
    char strMerchantId[LEN_MERCHANT_ID];
    char strAccount[LEN_ACCOUNT];
    char strPassword[LEN_PASSWORD];
    char strLastUpdateTime[LEN_LAST_UPDATE_TIME];
    char strMerchantTitle[LEN_MTITLE];
    struct _ACCOUNT_DATA *pNext;
} ACCOUNT_DATA;

typedef struct _AD_DATA {
    AD_TYPE eType;
    char *strLinkAddr;
    UINT8 u8Order;
    struct _AD_DATA *pNext;
} AD_DATA;

typedef struct _KOOBE_DRM_PERMISSION {
    char strNumOfConcurrentUsers[10];
    char strNumOfDevices[10];
    char strInterval[10];
    char strDatetimeStart[50];
    char strDatetimeEnd[50];
    char strAccumulated[10];
    bool bIsAdvertisement;
} KOOBE_DRM_PERMISSION;

typedef struct _CHANNEL_LIST {
    char *strMerchantId;
    char *strTitle;
    char *strCISImageName;
    char *strDescription;
    char *strUrlBookStore;
    char *strUrlJoinMembership;
    char *strUrlAccountValidator;
    char *strUrlBookDetails;
    struct _CHANNEL_LIST *pNext;
} CHANNEL_LIST;

typedef struct _METADATA_STORE {
    char *strAuthor;
    char *strPublisher;
    char *strPublishDate;    
} METADATA_STORE;

//paddy 2011.03.18
typedef struct _METADATA_STORE_EX {
    char strAuthor[64]; //size==database's size
    char strPublisher[64];
    char strPublishDate[20];    
} METADATA_STORE_EX;

typedef struct _QUERY_BOOKLIST_INFO {
    int istart_pos;
    int irequest_num;
    int oret_num;
    BOOKLIST_FILTER i_eFilter;    
} QUERY_BOOKLIST_INFO;

typedef struct _BOOK_LIST_EX {
    char strBookId[LEN_BOOK_ID];
    char strRevision[LEN_REVISION];
    char strFormat[LEN_FORMAT];
    char strTitle[LEN_TITLE];
    char strDownloadUrl[LEN_DOWNLOADURL];
    char strMerchantId[LEN_MERCHANT_ID];
    char strAccount[LEN_ACCOUNT];
    char strChannelTitle[LEN_CHANNEL];          //paddy 2011.03.22
	char strFileSize[LEN_FILESIZE] ;
    METADATA_STORE_EX Metadata;
} BOOK_LIST_EX;
//..
//paddy 2011.05.10
typedef struct _BOOK_ID_LIST {
    char strBookId[LEN_BOOK_ID];
} BOOK_ID_LIST;

typedef struct _BOOK_LIST {
    char strBookId[LEN_BOOK_ID];
    char strRevision[LEN_REVISION];
    char strFormat[LEN_FORMAT];
    char strTitle[LEN_TITLE];
    char strDownloadUrl[LEN_DOWNLOADURL];
    char strMerchantId[LEN_MERCHANT_ID];        //paddy add for Win32 2011.03.08
    char strAccount[LEN_ACCOUNT];               //paddy add for Win32 2011.03.08
    char strChannelTitle[LEN_CHANNEL];          //paddy 2011.03.22
	char strFileSize[LEN_FILESIZE] ;
    METADATA_STORE *pMetadata;
    struct _BOOK_LIST *pNext;
} BOOK_LIST;

typedef struct _METADATA {
    char *strUid;
    char *strTitle;
    char *strAuthor;
    char *strPublisher;
    char *strPublishDate;
    char *strPages;
    char *strUrl;
    char *strType;
    char *strStandardNo;
    char *strDescription;
} METADATA;

//paddy 2011.03.17
typedef enum _IO_REQUEST_TYPE{
    IO_TYPE_GETBOOKLIST=0x01,
} IO_REQUEST_TYPE;

//paddy 2011.02.23
typedef struct _ENKEY_DATA {
    char strUserId[LEN_USER_ID];
    char strKey[ENCRYPT_DRM_KEY_LEN];
    char strIv[ENCRYPT_DRM_IV_LEN];
    
} ENKEY_DATA;

typedef struct _BOOK_HISTORY_INFO {
    char strBookId[LEN_BOOK_ID];
    char strTitle[LEN_TITLE];
    char strAuthor[LEN_AUTHOR];
    int  iPage;
    char strDateTime[50];   
} BOOK_HISTORY_INFO;

typedef struct _QUERY_BOOK_HISTORY_INPUT_DATA {
    int istart_pos;
    int irequest_num;
    int iop;
    int oret_num;
    char *op_parameter;
} QUERY_BOOK_HISTORY_INPUT_DATA;

typedef enum _QUERY_BOOK_HISTORY_FLAG {
    /* MNG_OP_GET */
    GET_SORT_BY_BOOKID=0,
    GET_SORT_BY_AUTHOR,
    GET_SORT_BY_DATETIME,
    GET_SORT_TOTAL,
    GET_COMP_BY_BOOKID,
    
    /*MNG_OP_SET: compare Bookid*/
    SET_OP_DELETE=100,
    SET_OP_UPDATE, /*if item is not exist, DB will add it into DB. */

} QUERY_BOOK_HISTORY_FLAG;

typedef enum _MANAGEMENT_OP {
    MNG_OP_GET=0,
    MNG_OP_SET,
    
} MANAGEMENT_OP;
//..

class IUrlCommuncate 
{
public:
	virtual bool communicateKS(char *strUrlContext, char *content4096, bool bChkChecksum=FALSE) = 0;
	virtual bool communicateKSPostMethod(char *strUrlContext, char *strLog, char *strHash, char *contentcontent4096, bool bChkChecksum=FALSE) = 0;
	virtual bool communicateKSSimple(char *strUrlContext, char *content4096) = 0;
};

//..
#endif /// __KOOBEDRM_PUBLIC_H__


