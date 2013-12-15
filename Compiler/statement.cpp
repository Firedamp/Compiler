#include"head.h"

void statement(int level){
	int i;
	if(sym == IDEN){
		i = loc(token, level);
		if(i != 0){
			getsym();
			if(tab[i].obj == VARIABLE)//��ͨ��ֵ���
				assignstatement(i, tab[i].lev, tab[i].adr);
			else if(tab[i].obj == FUNCTION)//��������ֵ������ֵ
				if(tab[i].ref == display[level])
					assignstatement(i, tab[i].lev+1, 0);
				else
					error(45);//������Ҫ��ֵ�ĺ�������Ӧ�ĺ�����
			else if(tab[i].obj == PROCDURE)//���̵������
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
	else if(statfolsys[sym])//����䣬���������覴�
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

