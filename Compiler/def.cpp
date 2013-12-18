#include"head.h"

char *symstr[NSY] = {
	"CONSTTK",	"INTTK",	"CHARTK",	"REALTK",	"VARTK",	"ARRAYTK",	"OFTK",
	"REPTTK",	"UNLTK",	"IFTK",		"WHILETK",	"CASETK",	"THENTK",	"ELSETK",	"DOTK",
	"FORTK",	"TOTK",		"DOWNTOTK",	"PROCETK",	"FUNCTK",	"READTK",	
	"WRITETK",	"BEGINTK",	"ENDTK",	"PLUS",		"MINU",		"MULT",
	"DIV",		"LSS",		"LEQ",		"GRE",		"GEQ",		"EQL",
	"NEQ",		"ASSIGN",	"SEMICH",	"COMMA",	"PERIOD",	"COLON",
	"QMARK",	"DQMARK",	"LPARENT",	"RPARENT",	"LBRACK",	"RBRACK",
	"IDEN",		"INTCON",	"CHARCON",	"STRCON",	"REALCON",	"NUL"
};

char *objstr[] = {"CON", "VAR", "PRO", "FUN"};
char *typstr[] = {"NOTYP", "INTS", "REALS", "CHARS", "ARRAYS"};
char *boolstr[] = {"false", "true"};

char *key[NKW] = {
	"const",		"integer",		"char",			"real",			"var",			"array",		"of",
	"repeat",		"until",		"if",			"while",		"case",			"then",			"else",			"do",
	"for",			"to",			"downto",		"procedure",	"function",		"read",
	"write",		"begin",		"end"
};

char *instr[OMAX] = {
	"LDA",	"LOD",	"LDI",	"DIS",	"",		"",		"",		"",
	"FCT",	"INT",	"JMP",	"JPC",	"SWT",	"CAS",	"F1U",	"F2U",
	"F1D",	"F2D",	"MKS",	"CAL",	"IDX",	"IXX",	"LDB",	"CPB",
	"LDC",	"LDR",	"FLT",	"RED",	"WRS",	"WRW",	"WRU",	"HLT",
	"EXP",	"EXF",	"LDT",	"NOT",	"MUS",	"WRR",	"STO",	"EQR",
	"NER",	"LSR",	"LER",	"GTR",	"GER",	"EQL",	"NEQ",	"LSS",
	"LER",	"GRT",	"GEQ",	"ORR",	"ADD",	"SUB",	"ADR",	"SUR",
	"AND",	"MUL",	"DIV",	"MOD",	"MUR",	"DIR",	"RDL",	"WRL"
};

char *posstr[] = {
	"main",
	"fatal",
	"error",
	"test",
	"initsys",
	"unisys",
	"cpysys",
	"enterblock",
	"enterreal",
	"enterarray",
	"enter",
	"entervariable",
	"emit",
	"loc",
	"parameterlist",
	"getsym",
	"block",
	"constdec",
	"variabledec",
	"proceduredec",
	"constant",
	"typ",
	"condition",
	"expression",
	"term",
	"factor",
	"resulttype",
	"selector",
	"statement",
	"assignstatement",
	"compoundstatement",
	"ifstatement",
	"casestatement",
	"caselabel",
	"onecase",
	"forstatement",
	"callstatement",
	"writestatement",
	"readstatement",
	"interpret"
};

symbol sym;
int ll, cc;				//行数列数
int lc;					//代码指针

int inum;							//读到的整数
double rnum;						//读到的实数
int sleng;
char token[ALNG], ch = ' ';			//读到的单词与一个字符

int t, a, b, sx, c1, c2;			//表格指针

int uk;				//缺失标识符的过程与方法定义数

bool blockbegsys[NSY];
bool statbegsys[NSY];
bool facbegsys[NSY];
bool statfolsys[NSY];//暂时还没有初始化

int display[LMAX];
double rconst[C2MAX];
struct table tab[TMAX];
struct btable btab[BMAX];
struct atable atab[AMAX];
struct order code[CMAX];
char stab[SMAX];


FILE *input, *output;
