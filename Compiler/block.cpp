#include"head.h"

void block(bool fsys[], bool isfun, int level){    //nextfsys
	int dx;		//�������λ��
	int prt;	//���ű�ָ��
	int prb;	//btabָ��
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
		parameterlist(&dx, level);		//��ʽ������
	else if(sym != LPARENT && level >0)///////�ҵ��ķ��б��������Ű�
		error();					/////////
	btab[prb].lastpar = t;
	btab[prb].psize = dx;
	if(isfun){
		if(sym == COLON){
			getsym();
			if(sym == INTTK)
				tab[prt].typ = INTS;
			else if(sym == CHARTK)
				tab[prt].typ = CHARS;
			else if(sym == REALTK)
				tab[prt].typ = REALS;
			else
				error(15);//�޷�ʶ�������
		}
		else
			error(5);//ȱ��ð��
	}
	if(sym == SEMICH && level > 0)
		getsym();
	else if(level != 1)		////////
		error(14);//ȱ�ٷֺ�
	//do{
	if(sym == CONSTTK)
		constdec(fsys, level);
	if(sym == VARTK)
		variabledec(fsys, level, &dx);
	btab[prb].vsize = dx;
	while(sym == PROCETK || sym == FUNCTION)
		proceduredec();
	//test();
	//}while(sym in statbegsys);
	tab[prt].adr = lc;
	//getsym();
	//while
	if(sym == BEGINTK)
		;//compoundstatement()
	else
		error(14);//ȱ��begin
	//test();
	printf("Block Completed");
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
				error(15);//�޷�ʶ�������
			rf = 0;
			sz = 1;
//			if(valpar)
//				sz = 1;
//			else
//			sz = 1;
		}//test
		else
			error(5);
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
			else{
				error(14);
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
		error(4);
}



void constdec(bool fsys[], int level){     //fsys
	struct conrec c;
	bool nextfsys[NSY];

	getsym();
	test();
	if(sym != IDEN)///////
		error();
	while(sym == IDEN){
		enter(token, CONSTANT, level);
		getsym();
		if(sym == EQL)
			getsym();
		else
			error(16);//ȱ�ٵȺ�
		
		cpysys(nextfsys, fsys);
		nextfsys[SEMICH] = true;
		nextfsys[COMMA] = true;
		nextfsys[IDEN] = true;

		constant(nextfsys, &c);
		tab[t].typ = c.tp;
		tab[t].ref = 0;
		if(c.tp == REALS){
			enterreal(c.r);
			tab[t].adr = c1;
		}
		else
			tab[t].adr = c.i;
		if(sym == COMMA){
			getsym();
			if(sym != IDEN)
				error();
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
		error(2);//ȱ�ٱ�ʶ��
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
			error(5);//ȱ��ð��
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
	}
}

void proceduredec(){
}

void typ(bool fsys[], types *tp, int *rf, int *sz){
	*tp = NOTYP;
	*rf = 0;
	*sz = 1;
	test();
	if(sym == INTTK){
		*tp = INTS;
	}
	else if(sym == CHARTK)
		*tp = CHARS;
	else if(sym == ARRAYTK){
		getsym();
		*tp = ARRAYS;
		if(sym == LBRACK)
			getsym();
		else
			error(11);//ȱ��[
		if(sym == INTCON){
			if(inum > ASIZE){
				error();
				*sz = ASIZE;
			}
			else if(inum == 0){
				error();
				*sz = ASIZE;
			}
			else
				*sz = inum;
			enterarray(*sz);
			*rf = a;
			getsym();
		}
		else
			error();
		if(sym == RBRACK)
			getsym();
		else
			error();
		if(sym == OFTK)
			getsym();
		else
			error();
		if(sym == INTTK)
			atab[*rf].eltyp = INTS;
		else if(sym == CHARTK)
			atab[*rf].eltyp = CHARS;
		else if(sym == REALTK)
			atab[*rf].eltyp = REALS;
		else
			error();
		getsym();
	}
	else
		error();

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
			error(50);//����ʶ��ĳ���///////////////skip
		test();
	}
}

			

