#include"head.h"

void error(position p, int n){
	printf("%s : %d,%d\tERROR_%d:  %s\n", posstr[p], ll, cc, n, errmsg[n]);
}

void fatal(int n){
	printf("%d,%d\tÖÂÃüµÄERROR_%d:  %s\n",ll, cc, n, errmsg[n]);
	fclose(input);
	fclose(output);
	exit(0);
}

void test(){
}

