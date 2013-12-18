#include"head.h"
#include<math.h>


void getch(){
	ch = fgetc(input);
	cc++;
	if(ch == '\n'){
		ll++;
		cc = 1;
		//ch = fgetc(input);
	}
	
}

void getsym(){
	int i = 0, j = 0, flag = 0;
	while(ch == ' ' || ch == '\t' || ch == '\n')
		getch();
	if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
		do{
			if(i < ALNG)
				token[i++] = ch;
			else if(i == ALNG && !flag){
				printf("line:%d, column:%d : Identifier Too Long\n", ll, cc-i);
				flag++;
			}
			getch();
		}while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'));
		token[i] = '\0';
		sym = IDEN;
		for(j = 0; j < NKW; j++)
			if(strcmp(token, key[j]) == 0)
				sym = (symbol)j;
		printf("%s\t  %s\n", symstr[sym], token);
	}
	else if(ch >= '0' && ch <= '9'){
		inum = 0;
		rnum = 0;
		do{
			if(i < KMAX){
				token[i] = ch;
				inum = inum * 10 + (ch - '0');
				i++;
			}
			else if(i == KMAX && !flag){
				printf("line:%d, column:%d : Number Too Long\n", ll, cc);
				flag++;
			}
			getch();
		}while(ch >= '0' && ch <= '9');
		token[i] = '\0';
		sym = INTCON;
		if(ch == '.'){
			sym = REALCON;
			rnum = inum;
			inum = 0;
			j = 0;
			token[i++] = '.';
			getch();
			if(!(ch >= '0' && ch <= '9'))
				error(GETSYM);
			else{
				do{
					if(j < KMAX){
						token[i+j] = ch;
						inum = inum * 10 + (ch - '0');
						j++;
					}
					else if(j == KMAX && !flag){
						printf("line:%d, column:%d : Number Too Long\n", ll, cc);
						flag++;
					}
					getch();
				}while(ch >= '0' && ch <= '9');
				rnum += inum / pow(10.0, j);
				printf("%s\t  %lf\n", symstr[sym], rnum);
			}
		}
		else printf("%s\t  %d\n", symstr[sym], inum);
	}
	else if(ch == '\''){
		token[0] = '\'';
		getch();
		if(!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) && !(ch >= '0' && ch <= '9')){
			printf("line:%d, column:%d : Char should be a letter or a digit\n", ll, cc);
			sym = NUL;
			getch();
			getch();
		}
		else{
			token[1] = ch;
			inum = ch;
			getch();
			if(ch != '\'')
				printf("line:%d, column:%d : There should be a quotation mark\n", ll, cc);
			token[2] = '\'';
			token[3] = '\0';
			sym = CHARCON;
			printf("%s\t  %c\n", symstr[sym], ch);
			getch();
		}
	}
	else if(ch == '"'){
		//token[0] = '"';
		do{
			if(i < ALNG){
				if(i++) stab[sx++] = ch;
				//token[i++] = ch;
			}
			else if(i == ALNG && !flag){
				printf("line:%d, column:%d : String Too Long\n", ll, cc-i);
				flag++;
			}
			getch();
		}while(ch != '"' && ch != EOF);
		if(ch != EOF)
			getch();
		inum = sx-i+1;
		sleng = i-1;
		//token[i++] = '"';
		//token[i] = '\0';
		sym = STRCON;
	}
	else if(ch == ':'){
		getch();
		if(ch == '='){
			strcpy(token, ":=");
			sym = ASSIGN;
			getch();
		}
		else{
			strcpy(token, ":");
			sym = COLON;
		}
	}
	else if(ch == '<'){
		getch();
		if(ch == '>'){
			strcpy(token, "<>");
			sym = NEQ;
			getch();
		}
		else if(ch == '='){
			strcpy(token, "<=");
			sym = LEQ;
			getch();
		}
		else{
			strcpy(token, "<");
			sym = LSS;
		}
	}
	else if(ch == '>'){
		getch();
		if(ch == '='){
			strcpy(token, ">=");
			sym = GEQ;
			getch();
		}
		else{
			strcpy(token, ">");
			sym = GRE;
		}
	}
	else{
		switch(ch){
		case '+' :
			strcpy(token, "+");
			sym = PLUS;
			getch();
			break;
		case '-' :
			strcpy(token, "-");
			sym = MINU;
			getch();
			break;
		case '*' :
			strcpy(token, "*");
			sym = MULT;
			getch();
			break;
		case '/' :
			strcpy(token, "/");
			sym = DIV;
			getch();
			break;
		case ';' :
			strcpy(token, ";");
			sym = SEMICH;
			getch();
			break;
		case '=' :
			strcpy(token, "=");
			sym = EQL;
			getch();
			break;
		case ',' :
			strcpy(token, ",");
			sym = COMMA;
			getch();
			break;
		case '.' :
			strcpy(token, ".");
			sym = PERIOD;
			getch();
			break;
		case '(' :
			strcpy(token, "(");
			sym = LPARENT;
			getch();
			break;
		case ')' :
			strcpy(token, ")");
			sym = RPARENT;
			getch();
			break;
		case '[' :
			strcpy(token, "[");
			sym = LBRACK;
			getch();
			break;
		case ']' :
			strcpy(token, "]");
			sym = RBRACK;
			getch();
			break;
		case EOF :
			printf("Lexical Analysis Completed.\n");
			fclose(input);
			fclose(output);
			exit(0);
		default :
			printf("line:%d, column:%d : Unknown Character\n", ll, cc);
			strcpy(token, "");
			sym = NUL;
			getch();
		}
	}
}
