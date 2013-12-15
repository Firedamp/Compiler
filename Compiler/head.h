#ifndef head
#define head

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//#define MAXIDENTLENGTH	20
//#define MAXNUMLENGTH	20
//#define MAXLENGTH		100
//#define RESERNUM		21
//#define MAXIDENTNUM		10*


//enum symbol{
//	CONSTTK,	/*const*/			INTTK,		/*integer*/			CHARTK,		/*char*/
//	VARTK,		/*var*/				ARRAYTK,	/*array*/			OFTK,		/*of*/			
//	REPTTK,		/*repeat*/			UNLTK,		/*until*/			IFTK,		/*if*/		WHILETK,			
//	THENTK,		/*then*/			ELSETK,		/*else*/			DOTK,		/*do*/	
//	FORTK,		/*for*/				TOTK,		/*to*/				DOWNTOTK,	/*downto*/		
//	PROCETK,	/*procdure*/		FUNCTK,		/*function*/		READTK,		/*read*/	
//	WRITETK,	/*write*/			BEGINTK,	/*begin*/			ENDTK,		/*end*/		
//	PLUS,		/*+*/				MINU,		/*-*/				MULT,		/***/	
//	DIV,		/*/*/				LSS,		/*<*/				LEQ,		/*<=*/	
//	GRE,		/*>*/				GEQ,		/*>=*/				EQL,		/*=*/	
//	NEQ,		/*<>*/				ASSIGN,		/*:=*/				SEMICH,		/*;*/
//	COMMA,		/*,*/				PERIOD,		/*.*/				COLON,		/*:*/
//	QMARK,		/*'*/				DQMARK,		/*"*/				LPARENT,	/*(*/
//	RPARENT,	/*)*/				LBRACK,		/*[*/				RBRACK		/*]*/,
//	IDEN,		/*��ʶ��*/			INTCON,		/*�޷������γ���*/	CHARCON,	/*�ַ�����*/
//	STRCON,		/*�ַ���*/			NUL			/*ʲô������*/
//};


/*extern char *symstr[];
extern char *reserve[];
extern symbol sym;
extern int line, column;
extern char ch, word[];
extern FILE *input, *output;

void block();
void getch();
void getsym();

void error();

void const_declar();
void var_declar();
void proc_declar();
void funct_declar();
void multi_statement();*/

#define		NKW		24//27		//�ؼ��ָ���
#define		NSY		49		//����������
#define		ALNG	10		//��ʶ����󳤶�
#define		LLNG	121		
#define		KMAX	15		//�������λ��
#define		TMAX	100		//���ű���
#define		BMAX	20		//btab����
#define		AMAX	30		//atab����
#define		C2MAX	20		//ʵ������
#define		CSMAX	30
#define		CMAX	800		//����γ���
#define		LMAX	7		//���Ƕ�ײ���
#define		SMAX	600		//�ַ�������
#define		ASIZE	100		//����Ԫ��������
#define		ERMAX	58
#define		OMAX	63
#define		XMAX	32767
#define		NMAX	32767
#define		LINELENG	132
#define		LINELIMIT	200
#define		STACKSIZE	1450

enum symbol{
	CONSTTK,	/*const*/			INTTK,		/*integer*/			CHARTK,		/*char*/		REALTK,
	VARTK,		/*var*/				ARRAYTK,	/*array*/			OFTK,		/*of*/			
	REPTTK,		/*repeat*/			UNLTK,		/*until*/			IFTK,		/*if*/			WHILETK,	CASETK,
	THENTK,		/*then*/			ELSETK,		/*else*/			DOTK,		/*do*/	
	FORTK,		/*for*/				TOTK,		/*to*/				DOWNTOTK,	/*downto*/		
	PROCETK,	/*procdure*/		FUNCTK,		/*function*/		READTK,		/*read*/	
	WRITETK,	/*write*/			BEGINTK,	/*begin*/			ENDTK,		/*end*/		
	PLUS,		/*+*/				MINU,		/*-*/				MULT,		/***/	
	DIV,		/*/*/				LSS,		/*<*/				LEQ,		/*<=*/	
	GRE,		/*>*/				GEQ,		/*>=*/				EQL,		/*=*/	
	NEQ,		/*<>*/				ASSIGN,		/*:=*/				SEMICH,		/*;*/
	COMMA,		/*,*/				PERIOD,		/*.*/				COLON,		/*:*/
	QMARK,		/*'*/				DQMARK,		/*"*/				LPARENT,	/*(*/
	RPARENT,	/*)*/				LBRACK,		/*[*/				RBRACK		/*]*/,
	IDEN,		/*��ʶ��*/			INTCON,		/*�޷������γ���*/	CHARCON,	/*�ַ�����*/
	STRCON,		/*�ַ���*/			REALCON,	/*ʵ�ͳ���*/			NUL			/*ʲô������*/
};

enum objecttyp{ CONSTANT, VARIABLE, PROCDURE, FUNCTION};

enum types{ NOTYP, INTS, REALS, CHARS, ARRAYS};

struct table{
	char name[ALNG];
	int link;
	objecttyp obj;
	types typ;
	int ref;
	bool normal;
	int lev;
	int adr;
};

struct atable{
	 types eltyp;
	 int size;
};

struct btable{
	int last;
	int lastpar;
	int psize;
	int vsize;
};

struct conrec{
	types tp;
	int i;
	double r;
};

struct order{
	int f;
	int x;
	int y;
};

struct item{
	types typ;
	int ref;
};



extern symbol sym;
extern int ll, cc;				//��������
extern int lc;

extern int inum;							//����������
extern double rnum;						//������ʵ��
extern char token[ALNG], ch;			//�����ĵ�����һ���ַ�
extern int t, a, b, sx, c1, c2;			//���ָ��
extern int uk;			//ȱʧ��ʶ���Ĺ����뷽��������

extern char *key[];
extern char *symstr[];
extern char *objstr[];
extern char *typstr[];
extern char *boolstr[];

extern int display[LMAX];	//��û�г�ʼ��
extern double rconst[C2MAX];
extern struct table tab[TMAX];
extern struct btable btab[BMAX];
extern struct atable atab[AMAX];
extern struct order code[CMAX];

extern bool blockbegsys[NSY];
extern bool statbegsys[NSY];
extern bool statfolsys[NSY];

extern FILE *input, *output;


void fatal(int n);
void error(int n);
void error();

void test();

void initsys();
void unisys(bool *s, bool *s1, bool *s2);
void cpysys(bool *s1, bool *s2);

void enterblock();
void enterreal(double r);
void enterarray(int sz);
void enter(char token[], objecttyp k, int level);
void entervariable(int level);
void emit(int fct);
void emit(int fct, int b);
void emit(int fct, int a, int b);
int loc(char id[], int level);

void parameterlist(int *dx, int level);
void getsym();

void block(bool fsys[], bool isfun, int level);
void constdec(bool fsys[], int level);
void variabledec(bool fsys[], int level, int *dx);
void proceduredec(bool fsys[], int level);
void constant(bool fsys[], struct conrec *c);
void typ(bool fsys[], types *tp, int *rf, int *sz);



#endif