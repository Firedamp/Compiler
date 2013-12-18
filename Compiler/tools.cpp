#include"head.h"

void initsys(){
	for(int i = 0; i < NSY; i++){
		statbegsys[i] = false;
		blockbegsys[i] = false;
		facbegsys[i] = false;
		statfolsys[i] = false;
	}

	statbegsys[BEGINTK] = true;
	statbegsys[IFTK] = true;
	statbegsys[REPTTK] = true;
	statbegsys[FORTK] = true;

	blockbegsys[CONSTTK] = true;
	blockbegsys[VARTK] = true;
	blockbegsys[PROCETK] = true;
	blockbegsys[FUNCTK] = true;
	blockbegsys[BEGINTK] = true;

	facbegsys[INTCON] = true;
	facbegsys[REALCON] = true;
	//facbegsys[CHARCON] = true;//我的文法应该是没有这一条的
	facbegsys[IDEN] = true;
	facbegsys[LPARENT] = true;

	statfolsys[ENDTK] = true;
	statfolsys[SEMICH] = true;
}

void unisys(bool *s, bool *s1, bool *s2){
	for(int i = 0; i < NSY; i++)
		s[i] = s1[i] || s2[i];
}

void cpysys(bool *s1, bool *s2){
	for(int i = 0 ; i < NSY; i++)
		s1[i] = s2[1];
}

