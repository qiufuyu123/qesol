#pragma once
#include"lexel.h"
#include<stdbool.h>
#include<malloc.h>
char* tlist_symbol = "~!@#$%^&*()-=+/[]";
bool WIsNumber(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}
bool WIsWord(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return true;
	return false;
}
bool WIsSymbol(char c)
{
	char* tmp = tlist_symbol;
	while (*tmp)
	{
		if (*tmp == c)
			return true;
		tmp++;
	}
	return false;
}
bool WIsSplit(char c)
{

}

bool IsKeyWords(char* c)
{

}
bool IsWords(char* c)
{
	char* tmp = c;
	while (*tmp)
	{
		if (!WIsWord(*tmp))
			return false;
		tmp++;
	}
	return true;
}
bool IsNumber(char* c)
{
	char* tmp = c;
	while (*tmp)
	{
		if (!WIsNumber(*tmp))
			return false;
		tmp++;
	}
	return true;
}
QToken* MakeToken(int type, char* value, int row, int line)
{
	QToken* re = malloc(sizeof(QToken));
	if (re == NULL)
		return NULL;
	re->value = malloc(sizeof(value));
	strcpy(re->value, value);
	re->type = type;
	re->line = line;
	re->row = row;
	return re;
}
void AddToken(QToken* t, QTokenList* tl)
{
	if (tl == NULL || t == NULL)
		return;
	tl->tlist[tl->cur] = *t;
	tl->cur++;

}
QLexerErr* MakeErr(int row, int line, char* info)
{
	QLexerErr* le = malloc(sizeof(QLexerErr));
	if (le == NULL)
		return NULL;
	le->info = info;
	le->row = row;
	le->line = line;
	return le;
}
QLexerErr* QLexerMake(char* txt, QTokenList* tk)
{
	char* codes = txt;
	int crow = 0, cline = 0;
	char now_str[100] = "";
	int cout = 0;
	int strl = strlen(codes);
	while (*codes)
	{

		crow++;

		if (WIsSymbol(*codes) || cout == strl - 1)
		{
			if (IsNumber(now_str) && strcmp(now_str, "") != 0)
				AddToken(MakeToken(TT_NUM, now_str, crow, cline), tk);
			if (WIsSymbol(*codes))
			{
				char ls[2] = "??";
				ls[0] = *codes;
				ls[1] = '\0';
				AddToken(MakeToken(TT_SYMBOL, ls, crow, cline), tk);
			}
			memset(now_str, '\0', sizeof(now_str));
		}
		else if (WIsNumber(*codes))
		{
			now_str[strlen(now_str)] = *codes;
			now_str[strlen(now_str)] = '\0';
		}
		else if (*codes == ' ')
			memset(now_str, '\0', sizeof(now_str));//遇到空格跳过
		else if (*codes == '\n')
		{
			crow = 0;
			cline++;
		}
		else return MakeErr(crow, cline, "lex:unknow symbol or word!\n");
		codes++;
		cout++;
	}
	return NULL;
}
