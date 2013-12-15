#include"head.h"

void statement(int level){
	int i;
	if(sym == IDEN){
		i = loc(token, level);
		if(i != 0){
			getsym();
			if(tab[i].obj == VARIABLE)//普通赋值语句
				assignstatement(i, tab[i].lev, tab[i].adr);
			else if(tab[i].obj == FUNCTION)//函数名赋值，返回值
				if(tab[i].ref == display[level])
					assignstatement(i, tab[i].lev+1, 0);
				else
					error(45);//不在所要赋值的函数名对应的函数中
			else if(tab[i].obj == PROCDURE)//过程调用语句
				callstatement(i);
			else
				error();
		}
	}
	else if(sym == BEGINTK)
		compoundstatement(level);
	else if(sym == IFTK)
		ifstatement();
	else if(sym == CASETK)
		casestatement();
	else if(sym == FORTK)
		forstatement();
	else if(sym == WRITETK)
		writestatement();
	else if(sym == READTK)
		readstatement();
	else if(statfolsys[sym])//空语句，这个处理有瑕疵
		;
	else
		error();
}

void assignstatement(int i, int lv, int ad){
	item x, y, z;
	int f, a;
	x.typ = tab[i].typ;
	x.ref = tab[i].ref;
	if(tab[i].normal)
		f = 0;
	else
		f = 1;
	emit(f, lv, ad);
	if(sym == LBRACK){
		getsym();
		expresssion(&z);
		if(x.typ != ARRAYS)
			error(28);//变量不是数组
		else{
			if(z.typ != INTS)
				error(26);//数组下标为整数
			else
				emit(20, x.ref);
			x.typ = atab[x.ref].eltyp;
			x.ref = 0;
		}
		getsym();
		if(sym == RBRACK)
			getsym();
		else
			error();
	}
	if(sym == ASSIGN)
		getsym();
	else
		error();
	expression(&y);
	if(x.typ == y.typ)
		if(x.typ == INTS || x.typ == REALS || x.typ == CHARS)
			emit(38);
		else //if(x.ref != y.ref)
			error(46);//无法识别的类型,类型不匹配
		//else
			//emit(23, btab[x.ref].vsize);
	else if(x.typ == REALS && y.typ == INTS){
		emit(26, 0);
		emit(38);
	}
	else
		error(46);//类型不匹配
}

void compoundstatement(int level){
	getsym();
	statement(level);
	while(sym == SEMICH || statbegsys[sym]){
		if(sym == SEMICH)
			getsym();
		else
			error(14);//丢失分号
		statement(level);
	}
	if(sym == ENDTK)
		getsym();
	else
		error(57);//丢失end
}

void ifstatement(){
	item x;
	int lc1, lc2;

}

void casestatement(){
}

void forstatement(){
}

void callstatement(int i){
}

void writestatement(){
}

void readstatement(){
}

