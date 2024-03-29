#ifndef __KOOBEPARSER_PUBLIC_H__
#define __KOOBEPARSER_PUBLIC_H__

#define LEN_MAX 1024

//============================================================
/// Meta
typedef enum _META_TYPE {
	META_TYPE_KOOBE_ID = 1000,
	META_TYPE_KOOBE_ORDER,
	META_TYPE_KOOBE_EDITOR_INFO,
	META_TYPE_KOOBE_COVER,
	META_TYPE_KOOBE_TRIALBOOK,
	META_TYPE_RIGHTS,
	META_TYPE_COVERAGE,
	META_TYPE_RELATION,
	META_TYPE_LANGUAGE,
	META_TYPE_LANGUAGE_TYPE,
	META_TYPE_SOURCE,
	META_TYPE_FORMAT,
	META_TYPE_TYPE,
	META_TYPE_DESCRIPTION,
	META_TYPE_PUBLISHER,
	META_TYPE_SUBJECT,
	META_TYPE_DATE,
	META_TYPE_DATE_EVENT,
	META_TYPE_CONTRIBUTOR,
	META_TYPE_CONTRIBUTOR_FILEAS,
	META_TYPE_CONTRIBUTOR_ROLE,
	META_TYPE_CREATOR,
	META_TYPE_CREATOR_FILEAS,
	META_TYPE_CREATOR_ROLE,
	META_TYPE_TITLE,
	META_TYPE_IDENTIFIER,
	META_TYPE_IDENTIFIER_ID,
	META_TYPE_IDENTIFIER_SCHEME,
	META_TYPE_END,
} META_TYPE;

typedef struct _SPINE_INFO	//struct declaration
{
    char m_szIdref[LEN_MAX];
    char m_szHref[LEN_MAX];
    char m_szMediaType[LEN_MAX];
    struct _SPINE_INFO *m_pNext;
} SPINE_INFO;

typedef struct _TOC_ENTRY
{
    int m_nDepth;
    int m_nPlayOrder;
    char m_szLabel[LEN_MAX];
    char m_szLink[LEN_MAX];
    char m_szNavId[LEN_MAX];
    struct _TOC_ENTRY *m_pNext;
} TOC_ENTRY;


#endif /// __KOOBEPARSER_PUBLIC_H__

