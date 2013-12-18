#include"head.h"

int main(int argc, char *argv[]){
	bool nextfsys[NSY];

	ll = 1;
	cc = 1;
	lc = 0;		//lc指向下一个即将写入指令的位置（先写后+1），所以初始化为0
	c1 = -1;		//以下其他表格指针指向当前最后一个已经写入指令的位置（先+1后写），所以初始化为-1
	c2 = -1;
	t = 1;
	b = -1;
	a = -1;
	uk = 1;
	sx = 0;

	tab[1].obj = PROCDURE;
	tab[1].typ = NOTYP;
	tab[1].adr = 0;
	tab[1].lev = -1;
	tab[1].link = 0;
	tab[1].ref = 0;
	tab[1].normal = true;
	strcpy(tab[1].name, "     ");

	initsys();

	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	getsym();

	unisys(nextfsys, blockbegsys, statbegsys);
	block(nextfsys, false, 0);

	if(sym == PERIOD){
		emit(31);
		printf("Program Completed\n");
	}
	else
		error(6);//缺少句号

	printf("\n\n== real const table ==\n");
	printf("No.\tvalue\n");
	for(int i = 0; i <= c2; i++)
		printf("%d\t%lf\n", i, rconst[i]);

	printf("\n\n==== array table ====\n");
	printf("No.\ttype\tsize\n");
	for(int i = 0; i <= a; i++)
		printf("%d\t%s\t%d\n", i, typstr[atab[i].eltyp], atab[i].size);

	printf("\n\n============ block table ============\n");
	printf("No.\tlast\tlastpar\tpsize\tvsize\n");
	for(int i = 0; i <= b; i++)
		printf("%d\t%d\t%d\t%d\t%d\n", i, btab[i].last, btab[i].lastpar, btab[i].psize, btab[i].vsize);

	printf("\n\n============================ name table ===========================\n");
	printf("No.\tname\tlink\tobj\ttyp\tref\tlev\tnormal\tadr\n");
	for(int i = 1; i <= t; i++)
		printf("%d\t%s\t%d\t%s\t%s\t%d\t%d\t%s\t%d\n", i, tab[i].name, tab[i].link, objstr[tab[i].obj], typstr[tab[i].typ], tab[i].ref, tab[i].lev, boolstr[tab[i].normal], tab[i].adr);
	
	printf("\n\n============== code ==============\n");
	printf("No.\tname\tf\tx\ty\n");
	for(int i = 0; i < lc; i++){
		if(code[i].f < 4 || code[i].f == 13)
			printf("%d\t%s\t%d\t%d\t%d\n", i, instr[code[i].f], code[i].f, code[i].x, code[i].y);
		else if(code[i].f > 30)
			printf("%d\t%s\t%d\t\t\t\n", i, instr[code[i].f], code[i].f);
		else
			printf("%d\t%s\t%d\t\t%d\n", i, instr[code[i].f], code[i].f, code[i].y);
	}

	fclose(input);
	fclose(output);

	interpret();
}