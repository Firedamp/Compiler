#include"head.h"

void block(bool isfun, int level){    //nextfsys
	int dx;		//�������λ��
	int prt;	//���ű�ָ��
	int prb;	//btabָ��
	int x;

	dx = 5;
	prt = t;
	if(level >= LMAX)
		fatal(5);	
	enterblock();
	prb = b;
	display[level] = b;
	tab[prt].typ = NOTYP;
	tab[prt].ref = prb;
	if(sym == LPARENT && level > 0)
		parameterlist(&dx, level);		//��ʽ������
	else if(sym != LPARENT && level >0)///////�ҵ��ķ��б��������Ű�
		error(BLOCK, 9);					/////////
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
			else{
				error(BLOCK, 15);//�޷�ʶ�������
				getsym();
			}
		}
		else{
			error(BLOCK, 5);//ȱ��ð��
			getsym();
		}
	}
	if(sym == SEMICH && level > 0)
		getsym();
	else if(level != 0){	////////
		error(BLOCK, 14);//ȱ�ٷֺ�
		getsym();
	}
	//do{
	if(sym == CONSTTK)
		constdec(level);
	if(sym == VARTK)
		variabledec(level, &dx);
	btab[prb].vsize = dx;
	while(sym == PROCETK || sym == FUNCTK)
		proceduredec(level);
	//test();
	//}while(sym in statbegsys);
	tab[prt].adr = lc;
	//getsym();
	//while
	if(sym == BEGINTK)
		compoundstatement(level);
	else
		error(BLOCK, 56);//ȱ��begin
	//test();
	printf("Block Completed\n");
}

void parameterlist(int *dx, int level){ //��ʽ������
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
				error(PARAMETERLIST, 15);//�޷�ʶ�������
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
				error(PARAMETERLIST, 59);
//				if(sym == COMMA)
//					getsym();
			}
			//test();
//		}
	
	}
	if(sym == RPARENT){
		getsym();
		//test();
	}
	else{
		error(PARAMETERLIST, 4);
		getsym();
	}
}

void constdec(int level){     //fsys
	struct conrec c;

	getsym();
	test();
	if(sym != IDEN)///////
		error(CONSTDEC, 2);
	while(sym == IDEN){
		enter(token, CONSTANT, level);
		getsym();
		if(sym == EQL)
			getsym();
		else{
			error(CONSTANTT, 16);//ȱ�ٵȺ�
			getsym();
		}
		
		constant(&c);
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
				error(CONSTANTT, 2);
		}
		if(sym == SEMICH){
			getsym();
			break;
		}
	}
		
}

void variabledec(int level, int *dx){
	types tp;
	int t0, t1, rf, sz;

	getsym();
	if(sym != IDEN)
		error(VARIABLEDEC, 2);//ȱ�ٱ�ʶ��
	while(sym == IDEN){
		t0 = t;
		entervariable(level);
		while(sym == COMMA){
			getsym();
			entervariable(level);
		}
		if(sym == COLON)
			getsym();
		else{
			error(VARIABLEDEC, 5);//ȱ��ð��
			getsym();
		}
		t1 = t;


		typ(&tp, &rf, &sz);

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

void proceduredec(int level){
	bool isfun;

	isfun = (sym == FUNCTK);
	getsym();
	if(sym != IDEN){
		error(PROCEDUREDEC, 2);
		strcpy(token, "_unknow ");
		token[7] = uk++ + '0';
	}
	if(isfun)
		enter(token, FUNCTION, level);
	else
		enter(token, PROCDURE, level);
	tab[t].normal = true;
	getsym();

	block(isfun, level+1);

	if(sym == SEMICH)
		getsym();
	else{
		error(PROCEDUREDEC, 14);
		getsym();
	}
	emit(32+isfun);
}

void typ(types *tp, int *rf, int *sz){
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
		else{
			error(TYP, 11);//ȱ��[
			getsym();
		}
		if(sym == INTCON){
			if(inum > ASIZE){
				error(TYP, 21);
				*sz = ASIZE;
			}
			else if(inum == 0){
				error(TYP, 27);
				*sz = ASIZE;
			}
			else
				*sz = inum;
			enterarray(*sz);
			*rf = a;
			getsym();
		}
		else
			error(TYP, 26);
		if(sym == RBRACK)
			getsym();
		else{
			error(TYP, 12);
			getsym();
		}
		if(sym == OFTK)
			getsym();
		else
			error(TYP, 8);
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
			error(TYP, 15);
	}
	else
		error(TYP, 15);

}

void constant(struct conrec *c){
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
			error(CONSTANTT, 50);//����ʶ��ĳ���///////////////skip
		//test();
	}
}

			

