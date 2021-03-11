#pragma once
#include"lexel.h"
#include<stdbool.h>
QTokenList* token_list;
QToken cur_token;


typedef struct
{
	int row;
	int line;
	char* info;
}QCompErr;

void QInitCompile(QTokenList* tl);
QCompErr* QMakeCompile();
