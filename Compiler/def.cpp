#include"head.h"

char *symstr[] = {
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

symbol sym;
int ll, cc;				//行数列数
int lc;					//代码指针

int inum;							//读到的整数
double rnum;						//读到的实数
char token[ALNG], ch = ' ';			//读到的单词与一个字符

int t, a, b, sx, c1, c2;			//表格指针

int uk;				//缺失标识符的过程与方法定义数

bool blockbegsys[NSY];
bool statbegsys[NSY];
bool statfolsys[NSY];//暂时还没有初始化

int display[LMAX];
double rconst[C2MAX];
struct table tab[TMAX];
struct btable btab[BMAX];
struct atable atab[AMAX];
struct order code[CMAX];

FILE *input, *output;
