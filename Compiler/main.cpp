#include"head.h"

int main(int argc, char *argv[]){
	bool nextfsys[NSY];

	ll = 1;
	cc = 1;
	c1 = -1;
	c2 = -1;
	t = 0;
	b = -1;
	a = -1;
	uk = 0;

	initsys();

	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	getsym();

	unisys(nextfsys, blockbegsys, statbegsys);
	block(nextfsys, false, 0);


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
	
	


	
	if(sym == PERIOD)
		printf("Program Completed");
	else
		error(6);//È±ÉÙ¾äºÅ
	fclose(input);
	fclose(output);
}