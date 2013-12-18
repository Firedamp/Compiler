#include"head.h"

void block(bool fsys[], bool isfun, int level){    //nextfsys
	int dx;		//数据相对位置
	int prt;	//符号表指针
	int prb;	//btab指针
	int x;

	bool nextfsys[NSY];

	dx = 5;
	prt = t;
	if(level >= LMAX)
		fatal(5);	
	test();
	enterblock();
	prb = b;
	display[level] = b;
	tab[prt].typ = NOTYP;
	tab[prt].ref = prb;
	if(sym == LPARENT && level > 0)
		parameterlist(&dx, level);		//形式参数表
	else if(sym != LPARENT && level >0)///////我的文法中必须有括号吧
		error(BLOCK);					/////////
	btab[prb].lastpar = t;
	btab[prb].psize = dx;
	if(isfun){
		if(sym == COLON){
			getsym();
			if(sym == INTTK){
				tab[prt].typ = INTS;
				getsym();
			}
			else if(sym == CHARTK){
				tab[prt].typ = CHARS;
				getsym();
			}
			else if(sym == REALTK){
				tab[prt].typ = REALS;
				getsym();
			}
			else
				error(BLOCK, 15);//无法识别的类型
		}
		else
			error(BLOCK, 5);//缺少冒号
	}
	if(sym == SEMICH && level > 0)
		getsym();
	else if(level != 0)		////////
		error(BLOCK, 14);//缺少分号
	//do{
	if(sym == CONSTTK)
		constdec(fsys, level);
	if(sym == VARTK)
		variabledec(fsys, level, &dx);
	btab[prb].vsize = dx;
	while(sym == PROCETK || sym == FUNCTK)
		proceduredec(fsys, level);
	//test();
	//}while(sym in statbegsys);
	tab[prt].adr = lc;
	//getsym();
	//while
	if(sym == BEGINTK)
		compoundstatement(level);
	else
		error(BLOCK, 14);//缺少begin
	//test();
	printf("Block Completed\n");
}

void parameterlist(int *dx, int level){ //形式参数表
	types tp;
	bool valpar;
	int rf, sz, x, t0;
	getsym();
	tp = NOTYP;
	rf = 0;
//	sz = 0;
	test();/////
	while(sym == IDEN || sym == VARTK){
		if(sym != VARTK)
			valpar = true;
		else{
			getsym();
			valpar = false;
		}
		t0 = t;
		entervariable(level);
		while(sym == COMMA){
			getsym();
			entervariable(level);
		}
		if(sym == COLON){
			getsym();
			if(sym == INTTK){
				tp = INTS;
				getsym();
			}
			else if(sym == CHARTK){
				tp = CHARS;
				getsym();
			}
			else if(sym == REALTK){
				tp = REALS;
				getsym();
			}
			else
				error(PARAMETERLIST, 15);//无法识别的类型
			rf = 0;
			sz = 1;
//			if(valpar)
//				sz = 1;
//			else
//			sz = 1;
		}//test
		else
			error(PARAMETERLIST, 5);
		while(t0 < t){/////////////////
			t0++;
			tab[t0].typ = tp;
			tab[t0].ref = rf;
			tab[t0].adr = *dx;
			tab[t0].lev = level;
			tab[t0].normal = valpar;
			(*dx)++;
//			dx += sz;
		}
//		if(sym != RPARENT){
			if(sym == SEMICH)
				getsym();
			else if(sym == RPARENT)
				break;
			else{
				error(PARAMETERLIST, 14);
//				if(sym == COMMA)
//					getsym();
			}
			test();
//		}
	}
	if(sym == RPARENT){
		getsym();
		test();
	}
	else
		error(PARAMETERLIST, 4);
}

void constdec(bool fsys[], int level){     //fsys
	struct conrec c;
	bool nextfsys[NSY];

	getsym();
	test();
	if(sym != IDEN)///////
		error(CONSTDEC);
	while(sym == IDEN){
		enter(token, CONSTANT, level);
		getsym();
		if(sym == EQL)
			getsym();
		else
			error(CONSTANTT, 16);//缺少等号
		
		cpysys(nextfsys, fsys);
		nextfsys[SEMICH] = true;
		nextfsys[COMMA] = true;
		nextfsys[IDEN] = true;

		constant(nextfsys, &c);
		tab[t].typ = c.tp;
		tab[t].ref = 0;
		tab[t].normal = true;
		if(c.tp == REALS){
			enterreal(c.r);
			tab[t].adr = c1;
		}
		else
			tab[t].adr = c.i;
		if(sym == COMMA){
			getsym();
			if(sym != IDEN)
				error(CONSTANTT);
		}
		if(sym == SEMICH){
			getsym();
			break;
		}
	}
		
}

void variabledec(bool fsys[], int level, int *dx){
	types tp;
	int t0, t1, rf, sz;
	bool nextfsys[NSY];

	getsym();
	if(sym != IDEN)
		error(VARIABLEDEC, 2);//缺少标识符
	while(sym == IDEN){
		t0 = t;
		entervariable(level);
		while(sym == COMMA){
			getsym();
			entervariable(level);
		}
		if(sym == COLON)
			getsym();
		else
			error(VARIABLEDEC, 5);//缺少冒号
		t1 = t;

		cpysys(nextfsys, fsys);
		nextfsys[SEMICH] = true;
		nextfsys[COMMA] = true;
		nextfsys[IDEN] = true;

		typ(nextfsys, &tp, &rf, &sz);

		while(t0 < t1){
			t0++;
			tab[t0].typ = tp;
			tab[t0].ref = rf;
			tab[t0].lev = level;
			tab[t0].adr = *dx;
			tab[t0].normal = true;
			(*dx) += sz;
		}
		if(sym == SEMICH)
			getsym();
		else
			error(VARIABLEDEC, 14);
	}
}

void proceduredec(bool fsys[], int level){
	bool isfun;
	bool nextfsys[NSY];

	isfun = (sym == FUNCTK);
	getsym();
	if(sym != IDEN){
		error(PROCEDUREDEC);
		strcpy(token, "_unknow ");
		token[7] = uk + '0';
	}
	if(isfun)
		enter(token, FUNCTION, level);
	else
		enter(token, PROCDURE, level);
	tab[t].normal = true;
	getsym();

	cpysys(nextfsys, fsys);
	nextfsys[SEMICH] = true;
	block(nextfsys, isfun, level+1);

	if(sym == SEMICH)
		getsym();
	else
		error(PROCEDUREDEC);
	emit(32+isfun);
}

void typ(bool fsys[], types *tp, int *rf, int *sz){
	*tp = NOTYP;
	*rf = 0;
	*sz = 1;
	test();
	if(sym == INTTK){
		*tp = INTS;
		getsym();
	}
	else if(sym == CHARTK){
		*tp = CHARS;
		getsym();
	}
	else if(sym == REALTK){
		*tp = REALS;
		getsym();
	}
	else if(sym == ARRAYTK){
		getsym();
		*tp = ARRAYS;
		if(sym == LBRACK)
			getsym();
		else
			error(TYP, 11);//缺少[
		if(sym == INTCON){
			if(inum > ASIZE){
				error(TYP);
				*sz = ASIZE;
			}
			else if(inum == 0){
				error(TYP);
				*sz = ASIZE;
			}
			else
				*sz = inum;
			enterarray(*sz);
			*rf = a;
			getsym();
		}
		else
			error(TYP);
		if(sym == RBRACK)
			getsym();
		else
			error(TYP);
		if(sym == OFTK)
			getsym();
		else
			error(TYP);
		if(sym == INTTK){
			atab[*rf].eltyp = INTS;
			getsym();
		}
		else if(sym == CHARTK){
			atab[*rf].eltyp = CHARS;
			getsym();
		}
		else if(sym == REALTK){
			atab[*rf].eltyp = REALS;
			getsym();
		}
		else
			error(TYP);
	}
	else
		error(TYP);

}

void constant(bool fsys[], struct conrec *c){
	int x,sign;
	c->tp = NOTYP;
	c->i = 0;
	test();//////
	if(sym == CHARCON){
		c->tp = CHARS;
		c->i = inum;
		getsym();
	}
	else{
		sign = 1;
		if(sym == MINU){
			sign = -1;
			getsym();
		}
		else if(sym == PLUS)
			getsym();
		if(sym == INTCON){
			c->tp = INTS;
			c->i = sign * inum;
			getsym();
		}
		else if(sym == REALCON){
			c->tp = REALS;
			c->r = sign * rnum;
			getsym();
		}
		else
			error(CONSTANTT, 50);//不能识别的常量///////////////skip
		test();
	}
}

			

