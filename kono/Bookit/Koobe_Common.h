#ifndef __KOOBE_COMMON_H__
#define __KOOBE_COMMON_H__


//============================================================
/// Cross platform dynamic library definition
#if defined(WIN32) || defined(_WIN32_WCE)
    #ifdef BOOKIT_LIB
        #define BOOKIT_EXPORT   __declspec(dllexport)
        #define KOOBEDRM_EXPORT 
    #else
        #define BOOKIT_EXPORT   __declspec(dllimport)
        #define KOOBEDRM_EXPORT 
    #endif
#elif defined(__APPLE__)
    #define BOOKIT_EXPORT
    #define KOOBEDRM_EXPORT
#else
    #define BOOKIT_EXPORT
    #define KOOBEDRM_EXPORT
#endif

//paddy 
//#define BOOKIT_ANDROID_DEBUG

//============================================================
/// definition for data type
#ifndef UINT64
    typedef unsigned long long      UINT64;
#endif
#ifndef UINT32
    typedef unsigned int            UINT32;
#endif
#ifndef UINT16
    typedef unsigned short          UINT16;
#endif
#ifndef UINT8
    typedef unsigned char           UINT8;
#endif

#ifndef INT64
    typedef signed long long        INT64;
#endif
#ifndef INT32
    typedef signed int              INT32;
#endif
#ifndef INT16
    typedef signed short            INT16;
#endif
#ifndef INT8
    typedef signed char             INT8;
#endif

#ifndef BYTE
    typedef UINT8                   BYTE;
#endif

#ifndef PBYTE
    typedef UINT8*                  PBYTE;
#endif

#ifndef HANDLE
    typedef void                    *HANDLE;
#endif

/// definition for BOOL value
#ifndef TRUE
    #define TRUE                    (1)
#endif
#ifndef FALSE
    #define FALSE                   (0)
#endif

#ifndef ULONG_PTR
	typedef unsigned long DWORD_PTR, *PDWORD_PTR;
#endif

#ifndef LOWORD
	#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#endif

#ifndef HIWORD
	#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#endif

#ifndef LOBYTE
	#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#endif

#ifndef HIBYTE
	#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))
#endif

#ifndef __KOOBE_HANDLE__
    #define __KOOBE_HANDLE__
    #define KOOBE_HANDLE            unsigned long
#endif

#define DEBUG_FLAG 1
//============================================================
/// debug print
#ifndef dbg_print
#if defined(WIN32)

#if (DEBUG_FLAG)
#define dbg_print(fmt, ...) printf(fmt, __VA_ARGS__)
#else
#define dbg_print(fmt, ...) 
#endif

#else

#if (DEBUG_FLAG)
#define dbg_print(fmt, args...)    printf(fmt, ## args)
#else
#define dbg_print(fmt, ...) 
#endif

#endif
#endif

//============================================================
/// Cross platform function
#if !defined(WIN32) && !defined(_WIN32_WCE)
    #define _stricmp                strcasecmp
    #define stricmp                 strcasecmp
    #define strnicmp                strncasecmp
#endif


//============================================================
/// Special folder assign
typedef enum _BOOKIT_SPECIAL_FOLDER {
		KOOBE_FOLDER_CACHE,
		KOOBE_FOLDER_LOG,
		KOOBE_FOLDER_TEMP,
		KOOBE_FOLDER_END//Don't remove it for identify END
}BOOKIT_SPECIAL_FOLDER;

//============================================================
/// Koobe Sysetm Return Code
typedef enum _KS_STATUS_CODE {
    KS_000=0,       // not try to connect to Koobe System
    KS_001,         // unknow
    KS_002,         // CURLE is not OK
    KS_003,         // CURLINFO_HTTP_CODE status is not 200
    KS_004,         // CURLINFO_HTTP_CODE status is 200, but out is empty
    KS_005,         // Koobe System Data's Checksum is error
    KS_100=100,     // 處理成功。
    KS_101,
    KS_102,
    KS_200=200,     // 無此數位內容的授權資料。 ==> 您尚未付費購買本書，或所購買的閱讀權限已過，請先確認本書的版權訊息！
    KS_201,
    KS_202,
    KS_203,
    KS_210=210,     // 已超過可散佈的裝置數量。 ==> 您已經超過電子書所允許散播安裝的電腦數量，請聯絡您的服務廠商！
    KS_211,         // 已超過可同時閱讀裝置的數量。 ==> 您已在其他電腦登入閱讀，請在關閉他台電腦閱讀器後，再重新登入，如果依然有異常狀態，敬請聯絡您的服務廠商！
    KS_300=300,
    KS_301,
    KS_302,
    KS_303,
    KS_304,
    KS_305,
    KS_306,
    KS_307,
    KS_310=310,
    KS_400=400,
    KS_401,
    KS_402,
    KS_900=900,
    KS_990=990
} KS_STATUS_CODE;


//============================================================
/// Bookit Error Code
typedef enum _BOOKIT_ERR_CODE {
    //=====================================
    // Common
    BOOKIT_NO_ERROR = 0,
    BOOKIT_ERR_UNKNOWN,
    BOOKIT_ERR_FAILED_ALLOC_MEM,                    // Alloc memory fail
    BOOKIT_ERR_FAILED_OPEN_EPUB,                    // Failed to open epub file
    BOOKIT_ERR_FAILED_OPEN_DRM,                     // Failed to open drm file
    BOOKIT_ERR_FAILED_GET_BOOKID,                   // Failed to get Book ID
    BOOKIT_ERR_FAILED_FOLDERID,                     // Failed to get/set Folder ID

    //=====================================
    // KoobeDRM
    BOOKIT_ERR_DRM_NOT_INIT = 100,                  // Koobe DRM SDK not init successfully
    BOOKIT_ERR_DRM_ENKEY_NOT_EXIST,                 // Failed to open Encryption-KEY
    BOOKIT_ERR_DRM_FAILED_CHECK_ENKEY,              // Check EnKey Failed
    BOOKIT_ERR_DRM_FAILED_GET_RK_NO,                // Failed to get RKx No
    BOOKIT_ERR_DRM_FAILED_GET_ENKEY,                // Failed to get Encryption-KEY
    BOOKIT_ERR_DRM_FAILED_DATA_EMPTY,               // Data from Koobe System is empty
    BOOKIT_ERR_DRM_FAILED_COMMUNICATE_KS,           // Failed to communicate with Koobe System
    BOOKIT_ERR_DRM_FAILED_REGISTER_STEP1,           // Failed at decide RKx step1
    BOOKIT_ERR_DRM_FAILED_REGISTER_STEP2,           // Failed at decide RKx step2
    BOOKIT_ERR_DRM_FAILED_REGISTER_STEP3,           // Failed at decide RKx step3
    BOOKIT_ERR_DRM_FAILED_REGISTER_STEP4,           // Failed at decide RKx step4
    BOOKIT_ERR_DRM_FAILED_NO_TRUST,                 // Failed to establish Trust before doing Koobe System communicaion
    BOOKIT_ERR_DRM_FAILED_TRUST1,                   // Failed to establish trust1 with DRM system
    BOOKIT_ERR_DRM_FAILED_TRUST2,                   // Failed to establish trust2 with DRM system
    BOOKIT_ERR_DRM_FAILED_TRUST3,                   // Failed to establish trust3 with DRM system
    BOOKIT_ERR_DRM_FAILED_TRUST4,                   // Failed to establish trust4 with DRM system
    BOOKIT_ERR_DRM_FAILED_SIGNIN,                   // Failed to sign in DRM system
    BOOKIT_ERR_DRM_FAILED_GET_SIGNINURI,            // Failed to get sign in url
    BOOKIT_ERR_DRM_FAILED_NO_DRMDATA,               // No DRM Data exist
    BOOKIT_ERR_DRM_FAILED_GET_DRMDATA,              // Failed to get DRM Data
    BOOKIT_ERR_DRM_FAILED_CHECK_DRMDATA,            // Failed to check DRM Data
    BOOKIT_ERR_DRM_FAILED_AUTO_SIGNIN,              // Failed to auto signin
    BOOKIT_ERR_DRM_FAILED_AUTO_OTP_DATA,            // Auto OTP data is fail
    BOOKIT_ERR_DRM_FAILED_GET_BOOKLIST,             // Failed to get book list
    BOOKIT_ERR_DRM_FAILED_GET_BOOKFILEURL,          // Failed to get book file url
    BOOKIT_ERR_DRM_FAILED_SEND_PURCHASEDATA,        // Failed to send purchase data
    BOOKIT_ERR_DRM_FAILED_DRM_KOOBE_ID,             // no KoobeId in OPF file, not valid for DRM system
    BOOKIT_ERR_DRM_FAILED_MAKE_DRMPLUS,             // Failed to generate DRM Plus
    BOOKIT_ERR_DRM_FAILED_DECODE_DRM,               // Failed to Decode DRM Plus flag
    BOOKIT_ERR_DRM_FAILED_DRM_VER,                  // Koobe DRM SDK version not match
    BOOKIT_ERR_DRM_FAILED_DRM_SIZE,                 // Failed to get Koobe DRM size
    BOOKIT_ERR_DRM_FAILED_GET_DRM_COMPLETE,         // Failed to get DRM data complete
    BOOKIT_ERR_DRM_FAILED_DRM_PLUS_KEYINFO_SIZE,    // Failed to get DRM Plus Key Info size
    BOOKIT_ERR_DRM_FAILED_DRM_PLUS_KEYINFO_DEC,     // Failed to decode DRM Plus Key Info
    BOOKIT_ERR_DRM_FAILED_DRM_PLUS_KEYINFO_FLAG1,   // Failed to get DRM Plus Key Info Flag1
    BOOKIT_ERR_DRM_FAILED_DRM_PLUS_KEYINFO_FLAG2,   // Failed to get DRM Plus Key Info Flag2
    BOOKIT_ERR_DRM_FAILED_DRM_PLUS_KEYINFO_FLAG3,   // Failed to get DRM Plus Key Info Flag3
    BOOKIT_ERR_DRM_FAILED_ENCODE_KEY,               // Failed to encode key
    BOOKIT_ERR_DRM_FAILED_DECODE_KEY,               // Failed to decode key
    BOOKIT_ERR_DRM_FAILED_GET_DRM_CODEC,            // Failed to get DRM CODEC
    BOOKIT_ERR_DRM_FAILED_SENDLOG,                  // Failed to send log to Koobe System
    BOOKIT_ERR_DRM_FAILED_LOG_FILE1,                // Failed to open log file
    BOOKIT_ERR_DRM_FAILED_LOG_FILE2,                // Failed to open log file
    BOOKIT_ERR_DRM_FAILED_LOG_READ,                 // Failed to Read file
    BOOKIT_ERR_DRM_FAILED_GET_SERVER_TIME,          // Failed to get server time
    BOOKIT_ERR_DRM_FAILED_SEND_KEEP_ALIVE,          // Failed to send keep alive message to koobe system
    BOOKIT_ERR_DRM_FAILED_RENEW_DRMDATA,            // Failed to renew DRM data from koobe system
    BOOKIT_ERR_DRM_FAILED_CONNECT_KS,               // Failed to connect to koobe system

    // KoobeDRM CODEC
    BOOKIT_ERR_CODEC_DRM_CODEC_NOT_INIT = 300,      // Koobe DRM CODEC not init successfully
    BOOKIT_ERR_CODEC_FAILED_DRM_KEYS,               // DRM Keys is not correct

    // Biz Logic
    BOOKIT_ERR_BIZ_FAILED_SETTING = 500,            // Failed to open database
    BOOKIT_ERR_BIZ_FAILED_DB_OPEN,                  // Failed to open database
    BOOKIT_ERR_BIZ_FAILED_DB_CLOSE,                 // Failed to close database
    BOOKIT_ERR_BIZ_FAILED_DB_CREATE_TABLE,          // Failed to create database
    BOOKIT_ERR_BIZ_FAILED_DB_INSERT_DATA,           // Failed to insert data
    BOOKIT_ERR_BIZ_FAILED_DB_DELETE_DATA,           // Failed to delete data
    BOOKIT_ERR_BIZ_FAILED_DB_UPDATE_DATA,           // Failed to update data
    BOOKIT_ERR_BIZ_FAILED_DB_QUERY,                 // Failed to query
    BOOKIT_ERR_BIZ_FAILED_DB_OPERATION,             // Failed to do unsupport DB operation
    BOOKIT_ERR_BIZ_FAILED_GET_METADATA,             // Failed to get metadata from Koobe System
    BOOKIT_ERR_BIZ_FAILED_GET_METADATA2STORE,       // Failed to get metadata from Koobe System for store use
    BOOKIT_ERR_BIZ_FAILED_GET_ADDATA,               // Failed to get advertisement data from Koobe System
    BOOKIT_ERR_BIZ_FAILED_BL_FILTER,                // Failed to set Book List Filter
    BOOKIT_ERR_BIZ_FAILED_GET_CHANNEL_LIST,         // Failed to get Channel list
    BOOKIT_ERR_BIZ_FAILED_ACCOUNT_ACT,              // Failed to do Account operation
    BOOKIT_ERR_BIZ_FAILED_ENKEY_NOT_EXIST,          // Failed to get EnKey
    BOOKIT_ERR_BIZ_FAILED_SYNC_FILTER,              // Failed to set Sync filter
    BOOKIT_ERR_BIZ_FAILED_PARAMETER_ERROR,          // Failed by received a wrong parmeter      //paddy 2011.02.23
    BOOKIT_ERR_BIZ_FAILED_BOOK_HISTORY_NOT_EXIST,   // Failed to query Book History             //paddy 2011.02.23
    //=====================================
    // EPUB & KEP
    BOOKIT_ERR_EPUB_NOT_INIT = 1000,                // Koobe EPUB SDK not init successfully
    BOOKIT_ERR_NEED_DRM,
    BOOKIT_ERR_OPEN,
    BOOKIT_ERR_FAILED_GET_EPUBDATA,                 // Failed to get Epub Plus Data

    // ePub Parser
    BOOKIT_ERR_EPUB_PARSER_ERROR = 2000,
    BOOKIT_ERR_EPUB_PARSER_OPEN_EPUB_ERROR,
    BOOKIT_ERR_EPUB_PARSER_CONTAINER_NOT_FOUND_ERROR,
    BOOKIT_ERR_EPUB_PARSER_CONTAINER_UNABLE_OPEN_ERROR,
    BOOKIT_ERR_EPUB_PARSER_CONTAINER_CAN_NOT_PARSER_ERROR,
    BOOKIT_ERR_EPUB_PARSER_OPF_NO_OCF_ROOT,
    BOOKIT_ERR_EPUB_PARSER_OPF_NOT_FOUND_ERROR,
    BOOKIT_ERR_EPUB_PARSER_OPF_NO_TOC_ERROR,
    BOOKIT_ERR_EPUB_PARSER_FILE_ID_NOT_FOUND_ERROR,
    BOOKIT_ERR_EPUB_PARSER_NO_ENCRYPT_FILE,
    BOOKIT_ERR_EPUB_PARSER_ENCRYPT_NO_DATA,
    BOOKIT_ERR_EPUB_PARSER_ENCRYPT_CHIPHER_DATA_NO_FOUND,
    BOOKIT_ERR_EPUB_PARSER_ENCRYPT_DATA_KEY_INOF_NO_FOUND,
    BOOKIT_ERR_EPUB_PARSER_ENCRYPT_DATA_NO_FOUND,
    BOOKIT_ERR_EPUB_PARSER_ENCRYPT_FILE_ERROR_1,
    BOOKIT_ERR_EPUB_PARSER_ENCRYPT_FILE_ERROR_2,
    BOOKIT_ERR_EPUB_PARSER_ENCRYPT_UNKNOW_ALGORITHM,
    BOOKIT_ERR_EPUB_PARSER_CODEC_ERROR,
    BOOKIT_ERR_EPUB_PARSER_NEED_DRM,
    BOOKIT_ERR_EPUB_PARSER_MEMORY_INSUFFICIENT,
    BOOKIT_ERR_EPUB_PARSER_FILE_NOT_FOUND,
    BOOKIT_ERR_EPUB_PARSER_FILE_DELETE_ERROR,
    BOOKIT_ERR_EPUB_PARSER_ARCHIEF_ERROR,
    BOOKIT_ERR_EPUB_PARSER_PARAMETER_ERROR,
    BOOKIT_ERR_EPUB_PARSER_FILE_ADD_ERROR,
    BOOKIT_ERR_EPUB_PARSER_FILE_HAD_EXISTED_ERROR,
    BOOKIT_ERR_EPUB_PARSER_IS_OPEN,
    BOOKIT_ERR_EPUB_PARSER_IS_NOT_OPEN,
    BOOKIT_ERR_EPUB_PARSER_WITHOUT_BOOKID,
	BOOKIT_ERR_EPUB_PARSER_ENCRYPT_1_0,
	BOOKIT_ERR_EPUB_PARSER_ENCRYPT_1_1,
	BOOKIT_ERR_EPUB_PARSER_OPEN_OUTPUT_FILE_ERROR,
	BOOKIT_ERR_EPUB_PARSER_FILE_SIZE_IS_INVALID,
	BOOKIT_ERR_BUFFER_BIGGER_THAN_FILE,
	BOOKIT_ERR_EPUB_PARSER_READ_ENCRYPT,

	// Render
    BOOKIT_ERR_RENDER_ERROR = 3000,
    BOOKIT_ERR_RENDER_OPEN_FILE_ERROR,			// open file error
    BOOKIT_ERR_RENDER_INVALID_FILENAME_ERROR,	// null filename
    BOOKIT_ERR_RENDER_LOAD_PDF_TREE_ERROR,		// parse pdf tree error. it may be caused by wrong pdf format.
    BOOKIT_ERR_RENDER_PAGE_NO_ERROR,			// page no less then 0 or over then page count
    BOOKIT_ERR_RENDER_GET_PDF_PAGE_OBJECT_ERROR,// get pdf page object error. it may be caused by wrong pdf format.
    BOOKIT_ERR_RENDER_PDF_PAGE_DRAW_ERROR,		// draw pdf page error.
    BOOKIT_ERR_RENDER_INVALID_BUFFER_ERROR,		// invalid content buffer which should be allocated by ap.
    BOOKIT_ERR_RENDER_INSUFFICIENT_BUFFER_ERROR,// insufficient content buffer which should be allocated by ap.
    BOOKIT_ERR_RENDER_SAVE_PNG_ERROR,			// save png error.
    BOOKIT_ERR_RENDER_SUPPORT_KEP_ONLY_ERROR,	// only support KEP file
    BOOKIT_ERR_RENDER_SEARCH_NOT_FOUND,			// text search not found for pdf
    BOOKIT_ERR_RENDER_SEARCH_NULL_HANDLE,		// null handle for text search for pdf
    BOOKIT_ERR_RENDER_SEARCH_GET_PAGE_ERROR,	// get search page error
    BOOKIT_ERR_RENDER_SEARCH_GET_BRIEF_ERROR,	// get search brief error
    BOOKIT_ERR_RENDER_GRAY_PAGE,			    // is gray page
    BOOKIT_ERR_RENDER_NORMAL_PAGE,			    // is not gray page

} BOOKIT_ERR_CODE;

#endif /// __KOOBE_COMMON_H__

