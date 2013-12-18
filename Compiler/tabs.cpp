#include "head.h"

void enterblock(){
	if(b >= BMAX-1)
		fatal(2);//btab满了
	b++;
	btab[b].last = 0;
	btab[b].lastpar = 0;
}

void enterreal(double r){
	/*if(c2 >= C2MAX-1)
		fatal(3);//实数表满了
	rconst[c2+1] = r;
	c1 = 0;
	while(rconst[c1] != r)
		c1++;
	if(c1 > c2)
		c2 = c1;*/
	bool flag = false;
	for(c1 = 0; c1 <= c2; c1++)
		if(rconst[c1]== r)
			flag = true;
	if(!flag){
		if(c2 >= C2MAX-1)
			fatal(3);//实数表满了
		rconst[++c2]= r;
		c1++;
	}
}

void enterarray(int sz){
	a++;
	atab[a].size = sz;
}



void enter(char token[], objecttyp k, int level){
	int j, l;
	if(t >= TMAX-1)
		fatal(1);
	strcpy(tab[0].name, token);
	j = btab[display[level]].last;
	l = j;
	while(strcmp(tab[j].name, token) != 0)
		j = tab[j].link;
	if(j != 0)
		error(ENTER, 1);//重定义
	else{
		t++;
		strcpy(tab[t].name, token);
		tab[t].link = l;
		tab[t].obj = k;
		tab[t].typ = NOTYP;
		tab[t].ref = 0;
		tab[t].lev = level;
		tab[t].adr = 0;
		tab[t].normal = true;
	}
	btab[display[level]].last = t;
}

void entervariable(int level){
	if(sym == IDEN){
		enter(token, VARIABLE, level);
		getsym();
	}
	else
		error(ENTERVARIABLE, 2);//缺少标识符
}

void emit(int fct){
	if(lc >= CMAX)
		fatal(6);//汇编指令表满了
	code[lc++].f = fct;
}

void emit(int fct, int b){
	if(lc >= CMAX)
		fatal(6);//汇编指令表满了
	else{
		code[lc].f = fct;
		code[lc].y = b;
		lc++;
	}
}

void emit(int fct, int a, int b){
	if(lc >= CMAX)
		fatal(6);//汇编指令表满了
	else{
		code[lc].f = fct;
		code[lc].x = a;
		code[lc].y = b;
		lc++;
	}
}

int loc(char id[], int level){
	int i, j;
	i = level;
	strcpy(tab[0].name, id);
	do{
		j = btab[display[i]].last;
		while(strcmp(tab[j].name, id) != 0)
			j = tab[j].link;
		i--;
	}while(i >= 0 && j == 0);
	if(j == 0)
		error(LOC, 0);//未定义的标识符
	return j;
}


