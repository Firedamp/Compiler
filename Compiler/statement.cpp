#include"head.h"

void statement(int level){
	int i;
	if(sym == IDEN){
		i = loc(token, level);
		if(i != 0){
			getsym();
			if(tab[i].obj == VARIABLE)//普通赋值语句
				assignstatement(i, tab[i].lev, tab[i].adr, level);
			else if(tab[i].obj == FUNCTION)//函数名赋值，返回值
				if(tab[i].ref == display[level])
					assignstatement(i, tab[i].lev+1, 0, level);
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

void assignstatement(int i, int lv, int ad, int level){
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
		getsym();								//selector
		expression(&z, level);
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
	expression(&y, level);
	if(x.typ == y.typ)
		if(x.typ == INTS || x.typ == REALS || x.typ == CHARS)////////////////int,char
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

void ifstatement(int level){
	item x;
	int lc1, lc2;
	getsym();
	expression(&x, level);
	if(x.typ != INTS)
		error(17);
	lc1 = lc;
	emit(11);//jump
	if(sym == THENTK)
		getsym();
	else
		error(52);//缺少then
	statement(level);
	if(sym == ELSETK){
		getsym();
		lc2 = lc;
		emit(10);
		code[lc1].y = lc;
		statement(level);
		code[lc2].y = lc;
	}
	else
		code[lc1].y = lc;
}

void casestatement(int level){
}

void forstatement(int level){
}

void callstatement(int i){
}

void readstatement(int level){
	int i, f;
	item x, y;
	if(sym == LPARENT){
		do{
			getsym();
			if(sym != IDEN)
				error(2);//缺少标识符
			else{
				i = loc(token, level);
				getsym();
				if(i != 0){
					if(tab[i].obj != VARIABLE)
						error(37);//标识符必须为变量
					else{
						x.typ = tab[i].typ;    //这里我的文法中没有数组元素,可以整个数组一起读入吗
						x.ref = tab[i].ref;
						if(tab[i].normal)
							f = 0;
						else
							f = 1;
						emit(f, tab[i].lev, tab[i].adr);
						
						/*if(sym == LBRACK){//文法中没有直接读入数组元素，这里可以不要了
							getsym();								//selector
							expression(&z, level);
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
								error();*/

						if(x.typ == INTS || x.typ == REALS || x.typ == CHARS)
							emit(27, x.typ);
						else
							error(41);//不能读取的类型
					}
				}
			}
			test();
		}while(sym != COMMA);
		if(sym == RPARENT)
			getsym();
		else
			error(4);//缺少右括号
	}
}

void writestatement(int level){
	int a, f;
	item x, y;
	if(sym == LPARENT){
		getsym();
		if(sym == STRCON){
			emit(24, sleng);
			emit(28, inum);
			getsym();
			if(sym == COMMA){
				expression(&x, level);
				if(x.typ != INTS && x.typ != CHARS && x.typ != REALS)
					error(41);//不能输出的类型
				emit(29, x.typ);
			}
		}
		else{
			expression(&x, level);
			if(x.typ != INTS && x.typ != CHARS && x.typ != REALS)
				error(41);//不能输出的类型
			emit(29, x.typ);
		}
		if(sym == RPARENT)
			getsym();
		else
			error(4);//缺少右括号
	}
	else
		error();//缺少左括号
}

