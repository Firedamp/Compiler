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
	"main",			"fatal",			"error",			"test",			"initsys",			"unisys",
	"cpysys",		"enterblock",		"enterreal",		"enterarray",	"enter",			"entervariable",
	"emit",			"loc",				"parameterlist",	"getsym",		"block",			"constdec",
	"variabledec",	"proceduredec",		"constant",			"typ",			"condition",		"expression",
	"term",			"factor",			"resulttype",		"selector",		"statement",		"assignstatement",
	"compoundstatement",				"ifstatement",		"casestatement","caselabel",		"onecase",
	"forstatement",	"callstatement",	"writestatement",	"readstatement","interpret"
};

char *errmsg[] = {
	"0.  未定义的标识符",
	"1.  重定义",
	"2.  缺少标识符",
	"3.  字符串过长",
	"4.  缺少右括号)",
	"5.  缺少冒号:",
	"6.  不能识别的字符",
	"7.  小数点后缺少数字",
	"8.  缺少关键字of",
	"9.  缺少左括号(",
	"10.  缺少单引号'",
	"11.  缺少左中括号[",
	"12.  缺少右中括号]",
	"13.",
	"14.  缺少分号;",
	"15.  无法识别的变量类型",
	"16.  缺少等号",
	"17.",
	"18.  不能循环的类型",
	"19.  类型不匹配",
	"20.  标识符过长",
	"21.  数字过大",
	"22.  缺少句号.",
	"23.  case语句类型错误",
	"24.  意外的程序末端",
	"25.  char类型必须为字母或数字",
	"26.  数组下标只能是整数",
	"27.  数组元素个数不能为0",
	"28.  未定义的数组",
	"29.",
	"30.",
	"31.  不能识别的语句",
	"32.",
	"33.  错误的类型",
	"34.",
	"35.",
	"36.  形参类型与实参类型不匹配",
	"37.  不能是变量形参",
	"38.  应该是变量类型"
	"39.  实参个数与形参个数不等",
	"40.",
	"41.  不能读取或写入的类型",
	"42.",
	"43.",
	"44.",
	"45.  函数名赋值语句只能直接存在对应函数中",
	"46.  赋值语句类型不匹配",
	"47.",
	"48.",
	"49.",
	"50.  不能识别的常量",
	"51.  缺少赋值号:=",
	"52.  缺少then",
	"53.  比较运算符两端的类型无法比较",
	"54.  缺少do",
	"55.  缺少to或downto",
	"56.  缺少begin",
	"57.  缺少end",
	"58.",
	"59.  缺少分号或右括号",
	"60.  无法识别的比较运算符",
	"61.  block table满了",
	"62.  real table满了",
	"63.  array table满了",
	"64.  符号表满了",
	"65.  指令表满了"
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
