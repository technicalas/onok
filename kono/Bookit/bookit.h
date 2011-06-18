/**
* @file bookit.h
*
*  Defines Bookit for Koobe SDK
*
* @author Phyllis Wu for Koobe Inc.
*/

#ifndef __BOOKIT_H__
#define __BOOKIT_H__

#include "Koobe_Common.h"
#include "KoobeDRM_Public.h"
#include "KoobeParser_Public.h"
#include "KoobeRender_Public.h"
#include "KoobePdfProfile_Public.h"

#if defined(WIN32)
#include "windows.h" //for HANDLE
//HANDLE sem_get_booklist;
#else
#include "semaphore.h"
#endif


#ifdef WIN32
#define PDF_RENDER
#endif

#ifdef PDF_RENDER

class PdfRender;
#endif // PDF_RENDER

class IRender
{
	virtual BOOKIT_ERR_CODE renderImage(ImageType nType, BYTE* pContent, int* pnBufferSize, int X, int Y, int* pnWidth, int* pnHeight) = 0;
	virtual BOOKIT_ERR_CODE goFirstPage() = 0;
	virtual BOOKIT_ERR_CODE goLatestPage() = 0;
	virtual BOOKIT_ERR_CODE goNextPage() = 0;
	virtual BOOKIT_ERR_CODE goPrevPage() = 0;
	virtual BOOKIT_ERR_CODE getCurrentPage(int* pnCurrentCount) = 0;
	virtual BOOKIT_ERR_CODE getPageCount(int* pnCount) = 0;
	virtual BOOKIT_ERR_CODE gotoPage(int nIndex) = 0;
	virtual BOOKIT_ERR_CODE renderPage(int nX, int nY, int* pnWidth, int* pnHeight, int pageno) = 0;
	virtual BOOKIT_ERR_CODE getImage(BYTE* pContent, int* pnBufferSize,int nX, int nY, int* pnWidth, int* pnHeight) = 0;
	virtual BOOKIT_ERR_CODE setColorspace(ImageColorspace colorspace) = 0;
	virtual BOOKIT_ERR_CODE isGrayPage() = 0;
};

class ISearch
{
	//virtual BOOKIT_ERR_CODE next(int *o_pnPage,const char* szString) = 0;
	//virtual BOOKIT_ERR_CODE prev(int *o_pnPage,const char* szString) = 0;
};

class IBook
{
	virtual BOOKIT_ERR_CODE getIRender(IRender** pIRender) = 0;
	//virtual BOOKIT_ERR_CODE getISearch(ISearch** pISearch,const char* szKey) = 0;
	virtual BOOKIT_ERR_CODE getThumbnail(int i_nIndex,BYTE* o_pJPGBuffer, UINT32* o_pnBufferSize) = 0;
	virtual BOOKIT_ERR_CODE getMeta(META_TYPE type,const char** pszValue,const char* filenameEpub = NULL) = 0;
	virtual BOOKIT_ERR_CODE getTOCENTRY(int i_nIndex,const TOC_ENTRY *o_psTOC_ENTRY) = 0;
	virtual BOOKIT_ERR_CODE getTOCCount(int* pnCount) = 0;
};

class IBizLogic
{
};


class CKoobeDRMApi;
class CBizLogic;
class ICODEC;
class KePubParser;

/**
* @brief Bookit class
*
* Define API for Koobe SDK
*
*/
class BOOKIT_EXPORT Bookit : public IRender, public ISearch, public IRenderCallback
{
public:

	static BOOKIT_ERR_CODE createIBook(IBook** ppIBook,const char *szfilename, const char *szfilenameDRM);
	static BOOKIT_ERR_CODE destoryIBook(IBook* pIBook);
	static BOOKIT_ERR_CODE createIBizLogic(IBizLogic** ppIBizLogic,BIZ_LOGIC_ENVIRONMENT *i_psEnv);
	static BOOKIT_ERR_CODE destoryIBizLogic(IBizLogic* pIBizLogic);
	static BOOKIT_ERR_CODE globalSetting(DEVICE_INFO& i_sDeviceInfo, ENCRYPT_KEY_INFO& i_sEnKey,bool i_bUseBizLogic, BIZ_LOGIC_ENVIRONMENT& i_sEnv);

	Bookit();
	Bookit(DEVICE_INFO i_sDeviceInfo, ENCRYPT_KEY_INFO i_sEnKey, bool i_bUseBizLogic=false, BIZ_LOGIC_ENVIRONMENT *i_psEnv=NULL);
	virtual ~Bookit(void);

	BOOKIT_ERR_CODE init(DEVICE_INFO i_sDeviceInfo, ENCRYPT_KEY_INFO i_sEnKey, bool i_bUseBizLogic=false, BIZ_LOGIC_ENVIRONMENT *i_psEnv=NULL);

	//biz
	BOOKIT_ERR_CODE bizGetBooksTotalNum(int *o_total, BOOKLIST_FILTER i_eFilter);
	BOOKIT_ERR_CODE bizGetBookListEx(BOOK_LIST_EX *o_pBookList, QUERY_BOOKLIST_INFO *info);
	BOOKIT_ERR_CODE bizCancelIORequest(IO_REQUEST_TYPE io_type);
	BOOKIT_ERR_CODE bizDOADBookHistoryManagement(BOOK_HISTORY_INFO *io_pBuf, void *pData, MANAGEMENT_OP i_Op);
	BOOKIT_ERR_CODE bizGetBookHistoryTotalNum(int *o_total);
	BOOKIT_ERR_CODE bizGetErrCode(BOOKIT_ERR_CODE *o_eDetailErrCode=NULL, KS_STATUS_CODE *o_eKSStatus=NULL);
	BOOKIT_ERR_CODE bizGetChannelList(CHANNEL_LIST **o_psChannelList, int *o_pnListSize);
	BOOKIT_ERR_CODE bizFreeChannelList(CHANNEL_LIST **o_psChannelList);
	BOOKIT_ERR_CODE bizGetAccountList(ACCOUNT_DATA **o_psAccountList, int *o_pnListSize);
	BOOKIT_ERR_CODE bizFreeAccountList(ACCOUNT_DATA **o_psAccountList);
	BOOKIT_ERR_CODE bizManageAccount(ACCOUNT_DATA i_sAccount, KOOBE_DB_OP i_eAct);
	BOOKIT_ERR_CODE bizSyncDB(SYNCDB_FILTER i_eFilter=SYNCDB_NEW);
	BOOKIT_ERR_CODE bizSyncDB(char *i_strMerchantId, char *i_strAccount, SYNCDB_FILTER i_eFilter=SYNCDB_NEW);
	BOOKIT_ERR_CODE bizGetBookList(BOOK_LIST **o_psBookList, int *o_pnListSize, BOOKLIST_FILTER i_eFilter=BOOKLIST_ALL_CLOUD);
	BOOKIT_ERR_CODE bizGetBookList(char *i_strMerchantId, char *i_strAccount, BOOK_LIST **o_psBookList, int *o_pnListSize, BOOKLIST_FILTER i_eFilter);
	BOOKIT_ERR_CODE bizFreeBookList(BOOK_LIST **o_psBookList);
	BOOKIT_ERR_CODE bizSetBookOnDevice(char *i_strBookId, bool i_bIsOnDevice);

	//DRM	
	int getCurlStatusCode(void);//getDRM status
	BOOKIT_ERR_CODE setEnKey(ENCRYPT_KEY_INFO i_sEnKey);
	BOOKIT_ERR_CODE registerEnKey(KOOBE_RK_DATA i_sRKData, ENCRYPT_KEY_INFO *o_psEnKey, KS_STATUS_CODE *o_peStstusCode);
	BOOKIT_ERR_CODE getDRM_SignInUri(char *i_strEpubFile, char *i_strKoobeId, char *o_strSignInUri, KS_STATUS_CODE *o_peStstusCode);
	BOOKIT_ERR_CODE getDRM_Data(char *i_strEpubFile, PBYTE i_pcHtmlData, KS_STATUS_CODE *o_peStatusCode, PBYTE o_strAutoOtp=NULL);
	BOOKIT_ERR_CODE renewDRM(char *i_strEpubFile, char *i_strDrmFile, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE autoSignIn(PBYTE i_strBookId, PBYTE i_strAutoOtp, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE assignDRM(char *i_strEpubFile, char *i_strDrmFile);
	BOOKIT_ERR_CODE fnAES(PBYTE KeyIn,PBYTE cvIn,PBYTE in,PBYTE out,int direction,unsigned int nInputeLen);

	const char *getKoobeId(const char* filenameEpub = NULL);
	BOOKIT_ERR_CODE bookOpen(const char *filenameEpub, const char *filenameDRM);
	BOOKIT_ERR_CODE bookClose();
	BOOKIT_ERR_CODE newBookOpen(const char* filenameEpub,const char* filenameDRM);
	BOOKIT_ERR_CODE preProcess(const char* filename,bool bOverwrite = true);
	BOOKIT_ERR_CODE deleteKEPCache(const char* filename);

	BOOKIT_ERR_CODE getMediatypeByID(const char* szID,const char** pszMediaType);
	BOOKIT_ERR_CODE getSpineInfoList(const SPINE_INFO **o_psSPINE_INFO);
	const int getSpineItemNumber() const;
	BOOKIT_ERR_CODE getDataSize(const char* href, UINT32 *outsize);    
	BOOKIT_ERR_CODE getData(const char* href, char** dataOut, UINT32 *outsize);
	BOOKIT_ERR_CODE getData_Free(char* dataOut);
	BOOKIT_ERR_CODE setUserLogFile(char *i_strLogFile1,char *i_strLogFile2);
	BOOKIT_ERR_CODE addUserLog(char *i_strCurTime, char *i_strUserID, char *i_strBookID, USER_LOG_ACTION nAction, char *i_strParam=NULL);
	BOOKIT_ERR_CODE sendUserLog(UINT32 *o_u32LogCount, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE getBookList(PBYTE i_strMerchantId, PBYTE i_strUserId, BOOK_LIST **o_psBookList, int *o_nListSize, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE getBookListByPeriod(PBYTE i_strMerchantId, PBYTE i_strUserId, DRM_PERIOD i_ePeriod, UINT8 i_u8Num, BOOK_LIST **o_psBookList, int *o_pnListSize, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE getBookListByRange(PBYTE i_strMerchantId, PBYTE i_strUserId, char *i_strStart, char *i_strEnd, BOOK_LIST **o_psBookList, int *o_pnListSize, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE freeBookList(BOOK_LIST **io_psBookList);
	BOOKIT_ERR_CODE getBookFileUrl(PBYTE i_strMerchantId, PBYTE i_strUserId, PBYTE i_strBookId, PBYTE o_strBookFileUri, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE sendPurchaseData(PBYTE i_strMerchantId, PBYTE i_strUserId, PBYTE i_strSku, SELL_CHANNEL i_eChannel, PBYTE i_strToken, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE getServerTime(char *io_strServerTime, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE sendKeepAlive(KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE getAdData(char *i_strBookId, AD_DATA **o_pAdData, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE freeAdData(AD_DATA **o_pAdData);
	BOOKIT_ERR_CODE getMetadata(char *i_strBookId, METADATA **o_pMetadata, KS_STATUS_CODE *o_peStatusCode);
	BOOKIT_ERR_CODE freeMetadata(METADATA **io_pMetadata);
	BOOKIT_ERR_CODE getDRMPermission(KOOBE_DRM_PERMISSION **o_poDRMPermission);
	BOOKIT_ERR_CODE checkDRMPlus(char *i_strDrmFile, KOOBE_DRM_PERMISSION **o_poDRMPermission);
	BOOKIT_ERR_CODE freeDRMPermission(KOOBE_DRM_PERMISSION **io_poDRMPermission);

	//IRenderCallback
	virtual BOOKIT_ERR_CODE setRandAccessMode(bool bRandomMode);
	virtual BOOKIT_ERR_CODE getRandAccessMode(bool* bpRandomMode);
	virtual BOOKIT_ERR_CODE getPartialData_CRTSafe(const char* href, unsigned char* dataOut, const UINT32 nFrom, const UINT32 nTo, bool bEnableSeek, bool bEnableRead);
	virtual BOOKIT_ERR_CODE getData_CRTSafe(const char* href, /*out with default buffer*/char* dataOut, UINT32 *outsize);
	virtual BOOKIT_ERR_CODE getHrefByID(const char* szID,const char** pszHref);
	
	//IRender
	virtual BOOKIT_ERR_CODE renderImage(ImageType nType, BYTE* pContent, int* pnBufferSize, int X, int Y, int* pnWidth, int* pnHeight);
	virtual BOOKIT_ERR_CODE goFirstPage();
	virtual BOOKIT_ERR_CODE goLatestPage();
	virtual BOOKIT_ERR_CODE goNextPage();
	virtual BOOKIT_ERR_CODE goPrevPage();
	virtual BOOKIT_ERR_CODE getCurrentPage(int* pnCurrentCount);
	virtual BOOKIT_ERR_CODE getPageCount(int* pnCount);
	virtual BOOKIT_ERR_CODE gotoPage(int nIndex);
	virtual BOOKIT_ERR_CODE renderPage(int nX, int nY, int* pnWidth, int* pnHeight, int pageno);
	virtual BOOKIT_ERR_CODE getImage(BYTE* pContent, int* pnBufferSize,int nX, int nY, int* pnWidth, int* pnHeight);
	virtual BOOKIT_ERR_CODE setColorspace(ImageColorspace colorspace);
	virtual BOOKIT_ERR_CODE isGrayPage();

	virtual BOOKIT_ERR_CODE setEnableProfile(bool enable);
	virtual BOOKIT_ERR_CODE getPdfBookProfile(PdfBookProfile** profile);
	virtual BOOKIT_ERR_CODE getPdfPageProfile(PdfPageProfile** profile);
	virtual BOOKIT_ERR_CODE searchNext(HANDLE prevHandle, HANDLE *foundHandle, const char* i_szUTF8Target, int pageno);
	virtual BOOKIT_ERR_CODE getSearchPAGE(HANDLE handle, int* pnPageno);
	virtual BOOKIT_ERR_CODE getBrief(HANDLE handle, char* o_szGetBrief, int i_nBriefBufferSize);
	virtual BOOKIT_ERR_CODE clearSearchMark(HANDLE handle);
	virtual BOOKIT_ERR_CODE setSearchMark(HANDLE handle);
	virtual BOOKIT_ERR_CODE setSearchMarkColor(int rgb);

	//IBook	
	virtual BOOKIT_ERR_CODE getMeta(META_TYPE type,const char** pszValue,const char* filenameEpub = NULL);
	virtual BOOKIT_ERR_CODE getTOC_ENTRYList(const TOC_ENTRY **o_psTOC_ENTRY);
	virtual const int getTocEntryNumber() const;

	BOOKIT_ERR_CODE setMaxMallocSize(long nMax);
	BOOKIT_ERR_CODE getMallocSize(long *pSize);
	/////////////////////////////////////////////////////////////////////////////////

	BOOKIT_ERR_CODE isRendering(bool *pRender);
	BOOKIT_ERR_CODE setWorkingPath(char *pPath);

protected:

	//unused
	BOOKIT_ERR_CODE setURLInterface(IUrlCommuncate* i_pIUrlCommuncate);
	BOOKIT_ERR_CODE setSpecialFolder(BOOKIT_SPECIAL_FOLDER i_nFolderID,const char* i_szFolder);
	BOOKIT_ERR_CODE getSpecialFolder(BOOKIT_SPECIAL_FOLDER i_nFolderID,char* o_szFolder,int i_nBufferSize);

	//interface of ISearch
	virtual BOOKIT_ERR_CODE next(int *o_pnPage,const char* szString);
	virtual BOOKIT_ERR_CODE prev(int *o_pnPage,const char* szString);

#ifdef PDF_RENDER
	BOOKIT_ERR_CODE openPdf(char* filename);

	BOOKIT_ERR_CODE openPdfStream(const char* href);
	BOOKIT_ERR_CODE closePdf();

#endif //#ifdef PDF_RENDER
	const SPINE_INFO *getSpineInfo();
	const TOC_ENTRY *getTocEntry();
private:

	void setSyncFlag(const char* name, bool b);
	bool getSyncFlag(const char* name);
	BOOKIT_ERR_CODE  dealWithPartial(const char* href, KePubParser* m_pKePubParser, ICODEC *m_pCODEC, unsigned char* dataOut, const UINT32 nFrom, const UINT32 nTo, bool bEnableSeek, bool bEnableRead);

	char m_path[512];

	CKoobeDRMApi *m_pDRMAPI;		///< class member for DRM API
	CBizLogic *m_pBizLogic;		///< class member for Data Module API
	ICODEC *m_pCODEC;
	//paddy 2011.03.17
#if defined(WIN32)
	HANDLE sem_get_booklist;
	HANDLE sem_get_history;
	HANDLE sem_sync_db;
#else    
	sem_t sem_get_booklist;
	sem_t sem_get_history;
	sem_t sem_sync_db;
#endif
	//..
#ifdef PDF_RENDER
	PdfRender *m_pPdfRender;	///< class member for PdfRender
	bool m_bGrayPage;
#endif // PDF_RENDER
	bool m_bRandAccessMode;

	KePubParser* m_pKePubParser;
	char* m_ptoUtf8_CRTSafe;

	BOOKIT_ERR_CODE m_lastErr;
};

#endif // __BOO
