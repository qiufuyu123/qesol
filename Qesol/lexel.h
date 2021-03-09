#pragma once
#include<string.h>
typedef struct
{
	int type;
	char* value;
}QToken;

typedef struct
{
	int row;
	int line;
	char* info;
}QLexerErr;

typedef struct
{
	QToken tlist[4096];
	int cur;
}QTokenList;
enum
{
	TT_NUM = 1,
	TT_KEYWORD,
	TT_WORD,
	TT_SYMBOL,
	TT_SPLIT
};

//char* tlist_keyword[4] = { "","","","" };

QLexerErr* QLexerMake(char* codes, QTokenList* re);
