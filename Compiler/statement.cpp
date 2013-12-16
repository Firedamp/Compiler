#include"head.h"

void statement(int level){
	int i;
	if(sym == IDEN){
		i = loc(token, level);
		if(i != 0){
			getsym();
			if(tab[i].obj == VARIABLE)//��ͨ��ֵ���
				assignstatement(i, tab[i].lev, tab[i].adr, level);
			else if(tab[i].obj == FUNCTION)//��������ֵ������ֵ
				if(tab[i].ref == display[level])
					assignstatement(i, tab[i].lev+1, 0, level);
				else
					error(45);//������Ҫ��ֵ�ĺ�������Ӧ�ĺ�����
			else if(tab[i].obj == PROCDURE)//���̵������
				callstatement(i, level);
			else
				error();
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
	else if(statfolsys[sym])//����䣬���������覴�
		;
	else
		error();
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
			error(28);//������������
		else{
			if(z.typ != INTS)
				error(26);//�����±�Ϊ����
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
	else
		error();
	expression(&y, level);
	if(x.typ == y.typ)
		if(x.typ == INTS || x.typ == REALS || x.typ == CHARS)////////////////int,char
			emit(38);
		else //if(x.ref != y.ref)
			error(46);//�޷�ʶ�������,���Ͳ�ƥ��
		//else
			//emit(23, btab[x.ref].vsize);
	else if(x.typ == REALS && y.typ == INTS){
		emit(26, 0);
		emit(38);
	}
	else
		error(46);//���Ͳ�ƥ��
}

void compoundstatement(int level){
	getsym();
	statement(level);
	while(sym == SEMICH || statbegsys[sym]){
		if(sym == SEMICH)
			getsym();
		else
			error(14);//��ʧ�ֺ�
		statement(level);
	}
	if(sym == ENDTK)
		getsym();
	else
		error(57);//��ʧend
}

void ifstatement(int level){
	item x;
	int lc1, lc2;
	getsym();
	condition(&x, level);
	if(x.typ != INTS)
		error(17);
	lc1 = lc;
	emit(11);//jump
	if(sym == THENTK)
		getsym();
	else
		error(52);//ȱ��then
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
	types cvt;
	item x;
	int i, f, lc1, lc2;
	getsym();
	if(sym == IDEN){
		i = loc(token, level);
		if(i == 0)
			cvt = INTS;///////Ϊʲô
		else if(tab[i].obj == VARIABLE){
			cvt = tab[i].typ;
			if(!tab[i].normal)
				error(37);////////////////������
			else
				emit(0, tab[i].lev, tab[i].adr);
			if(cvt != INTS && cvt != CHARS)
				error(18);//����ѭ��������
		}
		else{
			error(37);
			cvt = INTS;
		}
	}
	else
		error();
	if(sym == ASSIGN){
		getsym();
		expression(&x, level);
		if(x.typ != cvt)
			error(19);
	}
	else
		error();
	f = 14;
	if(sym == TOTK ||sym == DOWNTOTK){
		if(sym == DOWNTOTK)
			f = 16;
		getsym();
		expression(&x, level);
		if(x.typ != cvt)
			error(19);
	}
	else
		error();
	lc1 = lc;
	emit(f);
	if(sym == DOTK)
		getsym();
	else
		error(54);
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
				error(39);
			else{
				cp++;
				if(tab[i].normal){//ֵ�β�
					expression(&x, level);
					if(x.typ != tab[cp].typ){
						if(x.typ == INTS && tab[cp].typ == REALS)
							emit(26, 0);
						else
							error(36);//���Ͳ�ƥ��
					}
				}
				else{//�����β�
					if(sym != IDEN)
						error(2);
					else{
						k = loc(token, level);
						getsym();
						if(k != 0){
							if(tab[k].obj != VARIABLE)
								error(37);
							x.typ = tab[k].typ;
							x.ref = tab[k].ref;
							if(tab[k].normal)
								emit(0, tab[k].lev, tab[k].adr);
							else
								emit(1, tab[k].lev, tab[k].adr);
							if(sym == LBRACK)
								selector(&x, level);
							if(x.typ != tab[cp].typ || x.ref != tab[cp].ref)
								error(36);
						}
					}
				}
			}
			test();
		}while(sym != COMMA);
		if(sym == RPARENT)
			getsym();
		else
			error(4);
	}
	if(cp < lastp)
		error(39);//��������
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
				error(2);//ȱ�ٱ�ʶ��
			else{
				i = loc(token, level);
				getsym();
				if(i != 0){
					if(tab[i].obj != VARIABLE)
						error(37);//��ʶ������Ϊ����
					else{
						x.typ = tab[i].typ;    //�����ҵ��ķ���û������Ԫ��,������������һ�������
						x.ref = tab[i].ref;
						if(tab[i].normal)
							f = 0;
						else
							f = 1;
						emit(f, tab[i].lev, tab[i].adr);
						
						/*if(sym == LBRACK){//�ķ���û��ֱ�Ӷ�������Ԫ�أ�������Բ�Ҫ��
							getsym();								//selector
							expression(&z, level);
							if(x.typ != ARRAYS)
								error(28);//������������
							else{
								if(z.typ != INTS)
									error(26);//�����±�Ϊ����
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
							error(41);//���ܶ�ȡ������
					}
				}
			}
			test();
		}while(sym == COMMA);
		if(sym == RPARENT)
			getsym();
		else
			error(4);//ȱ��������
	}
	error();//ȱ��������
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
				expression(&x, level);
				if(x.typ != INTS && x.typ != CHARS && x.typ != REALS)
					error(41);//�������������
				emit(29, x.typ);
			}
		}
		else{
			expression(&x, level);
			if(x.typ != INTS && x.typ != CHARS && x.typ != REALS)
				error(41);//�������������
			emit(29, x.typ);
		}
		if(sym == RPARENT)
			getsym();
		else
			error(4);//ȱ��������
	}
	else
		error();//ȱ��������
}

