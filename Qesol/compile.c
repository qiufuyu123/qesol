#include"compile.h"
#include<stdlib.h>
#include<string.h>
int nowTokid = 0;
typedef struct
{
	int lval;
	char op[2];
	int rval;
}QNodes;
static QNodes makeNodes(int lval, char* op, int rval)
{
	QNodes nod = { 0 };
	nod.lval = lval;
	nod.rval = rval;
	strcpy(nod.op, op);
	return nod;
}
static bool nextToken()
{
	if (nowTokid == token_list->cur)
		return false;
	cur_token = token_list->tlist[nowTokid];
	nowTokid++;
	return true;
}

void QInitCompile(QTokenList* tl)
{
	token_list = tl;
}
static void throw_err(QCompErr err)
{

}
static QCompErr makeErr(int row, int line, char* info)
{
	QCompErr er;
	er.line = line;
	er.row = row;
	er.info = info;
}
static QCompErr makeCurErr(char* info)
{
	return makeErr(cur_token.row, cur_token.line, info);
}
static int calc_factor();
static QNodes calc_term();
static QNodes calc_expr();
static QNodes calc_calc(QNodes ca);
//expr-> term(+/-)term *
//term-> factor(*//)factor *
//factor-> NUM
//		-> LP/RP
//		-> +/-
static QNodes calc_expr()
{
	QNodes curn = makeNodes(0, "", 0);
	int lv = calc_term().lval;
	curn.lval = lv;

	while (strcmp(cur_token.value, "+") == 0 || strcmp(cur_token.value, "-") == 0)
	{
		strcpy(curn.op, cur_token.value);
		if (nextToken())
		{
			int rv = calc_term().lval;
			curn.rval = rv;
			curn = calc_calc(curn);
		}
		else
		{
			throw_err(makeCurErr("COM:there is nothing behind '+' or '-'!"));
		}
	}
	return curn;
}
static QNodes calc_calc(QNodes ca)
{
	if (strcmp(ca.op, "+") == 0)
		return makeNodes(ca.lval + ca.rval, "", 0);
	else if (strcmp(ca.op, "-") == 0)
		return makeNodes(ca.lval - ca.rval, "", 0);
	else if (strcmp(ca.op, "*") == 0)
		return makeNodes(ca.lval * ca.rval, "", 0);
	else if (strcmp(ca.op, "/") == 0)
		return makeNodes(ca.lval / ca.rval, "", 0);
	else
	{
		throw_err(makeCurErr("COM:no such a operation to calc!"));
	}
}
static QNodes calc_term()
{
	QNodes curn = makeNodes(0, "", 0);
	int lv = calc_factor();
	curn.lval = lv;
	while (strcmp(cur_token.value, "*") == 0 || strcmp(cur_token.value, "/") == 0)
	{
		strcpy(curn.op, cur_token.value);
		if (nextToken())
		{
			int rv = calc_factor();
			curn.rval = rv;
			curn = calc_calc(curn);
		}
		else
		{
			throw_err(makeCurErr("COM:there is nothing behind '*' or '/'!"));
		}
	}
	return curn;
}
static int calc_factor()
{
	int re = 0;
	if (cur_token.type == TT_NUM)
	{
		//如果是数字，直接返回
		re = atoi(cur_token.value);
		nextToken();//这里不用管下一个是否获取失败，因为错误抛出不在最后的节点处理
		return re;
	}
	else if (strcmp(cur_token.value, "+") == 0)
	{
		if (nextToken())
		{
			re = atoi(cur_token.value);
			nextToken();//这里不用管下一个是否获取失败，因为错误抛出不在最后的节点处理
			return re;
		}
		else
		{
			throw_err(makeCurErr("COM:there is not a NUM behind the operation:+!"));
			//抛出错误，因为后面无法解析了，必须停止
		}
	}
	else if (strcmp(cur_token.value, "-") == 0)
	{
		if (nextToken())
		{
			re = -atoi(cur_token.value);
			nextToken();//这里不用管下一个是否获取失败，因为错误抛出不在最后的节点处理
			return re;
		}
		else
		{
			throw_err(makeCurErr("COM:there is not a NUM behind the operation:+!"));
			//抛出错误，因为后面无法解析了，必须停止
		}
	}
	else if (strcmp(cur_token.value, "(") == 0 || strcmp(cur_token.value, ")") == 0)
	{
		if (nextToken())
		{
			re = calc_expr().lval;
			nextToken();
			return re;
		}
		else
		{
			throw_err(makeCurErr("COM:there is nothing behind '(' or ')'!"));
		}
	}
	else
	{
		throw_err(makeCurErr("COM:cannot compile this word!"));
	}
}
QCompErr* QMakeCompile()
{
	nextToken();
	int t = calc_expr().lval;
	int b = 0;
	return NULL;
}
