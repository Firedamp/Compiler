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
					error(STATEMENT, 45);//不在所要赋值的函数名对应的函数中
			else if(tab[i].obj == PROCDURE)//过程调用语句
				callstatement(i, level);
			else
				error(STATEMENT, 31);
		}
	}
	else if(sym == BEGINTK)
		compoundstatement(level);
	else if(sym == IFTK)
		ifstatement(level);
	else if(sym == CASETK)
		casestatement(level);
	else if(sym == FORTK)
		forstatement(level);
	else if(sym == WRITETK)
		writestatement(level);
	else if(sym == READTK)
		readstatement(level);
	else if(statfolsys[sym])//空语句，这个处理有瑕疵
		;
	else
		error(STATEMENT, 31);
}

void assignstatement(int i, int lv, int ad, int level){
	item x, y;
	int f, a;
	x.typ = tab[i].typ;
	x.ref = tab[i].ref;
	if(tab[i].normal)
		f = 0;
	else
		f = 1;
	emit(f, lv, ad);
	if(sym == LBRACK){
		/*getsym();								//selector
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
		selector(&x, level);
	}
	if(sym == ASSIGN)
		getsym();
	else{
		error(ASSIGNSTATEMENT, 51);
		if(sym == EQL)
			getsym();
	}
	expression(&y, level);
	if(x.typ == y.typ)
		if(x.typ == INTS || x.typ == REALS || x.typ == CHARS)////////////////int,char
			emit(38);
		else //if(x.ref != y.ref)
			error(ASSIGNSTATEMENT, 46);//无法识别的类型,类型不匹配
		//else
			//emit(23, btab[x.ref].vsize);
	else if(x.typ == REALS && y.typ == INTS){
		emit(26, 0);
		emit(38);
	}
	else if(x.typ == CHARS && y.typ == INTS)
		emit(38);
	else if(x.typ == INTS && y.typ == CHARS)
		emit(38);
	else
		error(ASSIGNSTATEMENT, 46);//类型不匹配
}

void compoundstatement(int level){
	getsym();
	if(sym != ENDTK)
		statement(level);
	while(sym == SEMICH || statbegsys[sym]){
		if(sym == SEMICH)
			getsym();
		else
			error(COMPOUNDSTATEMENT, 14);//丢失分号
		statement(level);
	}
	if(sym == ENDTK)
		getsym();
	else
		error(COMPOUNDSTATEMENT, 57);//丢失end
}

void ifstatement(int level){
	item x;
	int lc1, lc2;
	getsym();
	condition(&x, level);
	if(x.typ != INTS)
		error(IFSTATEMENT, 33);
	lc1 = lc;
	emit(11);//jump
	if(sym == THENTK)
		getsym();
	else
		error(IFSTATEMENT, 52);//缺少then
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
	item x;
	int i, j, k, lc1;
	casestab casetab[CSMAX];
	int exittab[CSMAX];
	getsym();
	i = -1;
	j = -1;
	expression(&x, level);
	if(x.typ != INTS && x.typ != CHARS)
		error(CASESTATEMENT, 23);
	lc1 = lc;
	emit(12);
	if(sym == OFTK)
		getsym();
	else
		error(CASESTATEMENT, 8);
	onecase(casetab, exittab, &i, &j, &x, level);
	while(sym == SEMICH){
		getsym();
		onecase(casetab, exittab, &i, &j, &x, level);
	}
	code[lc1].y = lc;
	for(k = 0; k <= i; k++){
		emit(13, casetab[k].val);
		emit(13, casetab[k].lc);
	}
	emit(10, 0);
	for(k = 0; k <= j; k++)
		code[exittab[k]].y = lc;
	if(sym == ENDTK)
		getsym();
	else
		error(CASESTATEMENT, 57);//缺少end
	
}

void caselabel(casestab casetab[], int *i, item *x){
	conrec lab;
	int k;

	constant(&lab);
	if(lab.tp != x->typ)
		error(CASELABEL, 33);//
	else
		if(*i >= CSMAX-1)
			fatal(6);///
		else{
			(*i)++;
			k = -1;
			casetab[*i].val = lab.i;
			casetab[*i].lc = lc;
			do k++;
			while(casetab[k].val != lab.i);
			if(k < *i)
				error(CASELABEL, 1);//重定义
		}
}

void onecase(casestab casetab[], int exittab[], int *i, int *j, item *x, int level){
	//if sym in constbegsys
	caselabel(casetab, i, x);
	while(sym == COMMA){
		getsym();
		caselabel(casetab, i, x);
	}
	if(sym = COLON)
		getsym();
	else
		error(ONECASE, 5);//缺少冒号
	statement(level);
	(*j)++;
	exittab[*j] = lc;
	emit(10);
}

void forstatement(int level){
	types cvt;
	item x;
	int i, f, lc1, lc2;
	getsym();
	if(sym == IDEN){
		i = loc(token, level);
		getsym();
		if(i == 0)
			cvt = INTS;
		else if(tab[i].obj == VARIABLE){
			cvt = tab[i].typ;
			if(!tab[i].normal)
				error(FORSTATEMENT, 37);////////////老师说可以报错   //emit(1, tab[i].lev, tab[i].adr);
			else
				emit(0, tab[i].lev, tab[i].adr);
			if(cvt != INTS && cvt != CHARS)
				error(FORSTATEMENT, 18);//不能循环的类型
		}
		else{
			error(FORSTATEMENT, 18);
			cvt = INTS;
		}
	}
	else
		error(FORSTATEMENT, 2);
	if(sym == ASSIGN){
		getsym();
		expression(&x, level);
		if(x.typ != cvt)
			error(FORSTATEMENT, 19);
	}
	else
		error(FORSTATEMENT, 51);
	f = 14;
	if(sym == TOTK ||sym == DOWNTOTK){
		if(sym == DOWNTOTK)
			f = 16;
		getsym();
		expression(&x, level);
		if(x.typ != cvt)
			error(FORSTATEMENT, 19);
	}
	else{
		error(FORSTATEMENT, 55);
		getsym();
	}
	lc1 = lc;
	emit(f);
	if(sym == DOTK)
		getsym();
	else
		error(FORSTATEMENT, 54);
	lc2 = lc;
	statement(level);
	emit(f+1, lc2);
	code[lc1].y = lc;
}

void callstatement(int i, int level){
	item x;
	int lastp, cp, k;
	emit(18, i);
	lastp = btab[tab[i].ref].lastpar;
	cp = i;
	if(sym == LPARENT){
		do{
			getsym();
			if(cp >= lastp)
				error(CALLSTATEMENT, 39);
			else{
				cp++;
				if(tab[cp].normal){//值形参
					expression(&x, level);
					if(x.typ != tab[cp].typ){
						if(x.typ == INTS && tab[cp].typ == REALS)
							emit(26, 0);
						else
							error(CALLSTATEMENT, 36);//类型不匹配
					}
				}
				else{//变量形参
					if(sym != IDEN)
						error(CALLSTATEMENT, 2);
					else{
						k = loc(token, level);
						getsym();
						if(k != 0){
							if(tab[k].obj != VARIABLE)
								error(CALLSTATEMENT, 38);
							x.typ = tab[k].typ;
							x.ref = tab[k].ref;
							if(tab[k].normal)
								emit(0, tab[k].lev, tab[k].adr);
							else
								emit(1, tab[k].lev, tab[k].adr);
							if(sym == LBRACK)
								selector(&x, level);
							if(x.typ != tab[cp].typ || x.ref != tab[cp].ref)
								error(CALLSTATEMENT, 36);
						}
					}
				}
			}
			test();
		}while(sym == COMMA);
		if(sym == RPARENT)
			getsym();
		else{
			error(CALLSTATEMENT, 4);
			getsym();
		}
	}
	if(cp < lastp)
		error(CALLSTATEMENT, 39);//参数不够
	emit(19, btab[tab[i].ref].psize-1);
	if(tab[i].lev < level)
		emit(3, tab[i].lev, level);
}
					
void readstatement(int level){
	int i, f;
	item x, y;
	getsym();
	if(sym == LPARENT){
		do{
			getsym();
			if(sym != IDEN)
				error(READSTATEMENT, 2);//缺少标识符
			else{
				i = loc(token, level);
				getsym();
				if(i != 0){
					if(tab[i].obj != VARIABLE)
						error(READSTATEMENT, 38);//标识符必须为变量
					else{
						x.typ = tab[i].typ;    //这里我的文法中没有数组元素,可以整个数组一起读入吗
						x.ref = tab[i].ref;
						if(tab[i].normal)
							f = 0;
						else
							f = 1;
						emit(f, tab[i].lev, tab[i].adr);
						
						//selector(&x, level);//我的文法中这里没有数组元素

						if(x.typ == INTS || x.typ == REALS || x.typ == CHARS)
							emit(27, x.typ);
						else
							error(READSTATEMENT, 41);//不能读取的类型
					}
				}
			}
			test();
		}while(sym == COMMA);
		if(sym == RPARENT)
			getsym();
		else{
			error(READSTATEMENT, 4);//缺少右括号
			getsym();
		}
	}
	else
		error(READSTATEMENT, 9);//缺少左括号
}

void writestatement(int level){
	int a, f;
	item x, y;
	getsym();
	if(sym == LPARENT){
		getsym();
		if(sym == STRCON){
			emit(24, sleng);
			emit(28, inum);
			getsym();
			if(sym == COMMA){
				getsym();
				expression(&x, level);
				if(x.typ != INTS && x.typ != CHARS && x.typ != REALS)
					error(WRITESTATEMENT, 41);//不能输出的类型
				emit(29, x.typ);
			}
		}
		else{
			expression(&x, level);
			if(x.typ != INTS && x.typ != CHARS && x.typ != REALS)
				error(WRITESTATEMENT, 41);//不能输出的类型
			emit(29, x.typ);
		}
		if(sym == RPARENT)
			getsym();
		else{
			error(WRITESTATEMENT, 4);//缺少右括号
			getsym();
		}
	}
	else
		error(WRITESTATEMENT, 9);//缺少左括号
}

