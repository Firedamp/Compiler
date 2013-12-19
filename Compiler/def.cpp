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
	"0.  δ����ı�ʶ��",
	"1.  �ض���",
	"2.  ȱ�ٱ�ʶ��",
	"3.  �ַ�������",
	"4.  ȱ��������)",
	"5.  ȱ��ð��:",
	"6.  ����ʶ����ַ�",
	"7.  С�����ȱ������",
	"8.  ȱ�ٹؼ���of",
	"9.  ȱ��������(",
	"10.  ȱ�ٵ�����'",
	"11.  ȱ����������[",
	"12.  ȱ����������]",
	"13.",
	"14.  ȱ�ٷֺ�;",
	"15.  �޷�ʶ��ı�������",
	"16.  ȱ�ٵȺ�",
	"17.",
	"18.  ����ѭ��������",
	"19.  ���Ͳ�ƥ��",
	"20.  ��ʶ������",
	"21.  ���ֹ���",
	"22.  ȱ�پ��.",
	"23.  case������ʹ���",
	"24.  ����ĳ���ĩ��",
	"25.  char���ͱ���Ϊ��ĸ������",
	"26.  �����±�ֻ��������",
	"27.  ����Ԫ�ظ�������Ϊ0",
	"28.  δ���������",
	"29.",
	"30.",
	"31.  ����ʶ������",
	"32.",
	"33.  ���������",
	"34.",
	"35.",
	"36.  �β�������ʵ�����Ͳ�ƥ��",
	"37.  �����Ǳ����β�",
	"38.  Ӧ���Ǳ�������"
	"39.  ʵ�θ������βθ�������",
	"40.",
	"41.  ���ܶ�ȡ��д�������",
	"42.",
	"43.",
	"44.",
	"45.  ��������ֵ���ֻ��ֱ�Ӵ��ڶ�Ӧ������",
	"46.  ��ֵ������Ͳ�ƥ��",
	"47.",
	"48.",
	"49.",
	"50.  ����ʶ��ĳ���",
	"51.  ȱ�ٸ�ֵ��:=",
	"52.  ȱ��then",
	"53.  �Ƚ���������˵������޷��Ƚ�",
	"54.  ȱ��do",
	"55.  ȱ��to��downto",
	"56.  ȱ��begin",
	"57.  ȱ��end",
	"58.",
	"59.  ȱ�ٷֺŻ�������",
	"60.  �޷�ʶ��ıȽ������",
	"61.  block table����",
	"62.  real table����",
	"63.  array table����",
	"64.  ���ű�����",
	"65.  ָ�������"
};


symbol sym;
int ll, cc;				//��������
int lc;					//����ָ��

int inum;							//����������
double rnum;						//������ʵ��
int sleng;
char token[ALNG], ch = ' ';			//�����ĵ�����һ���ַ�

int t, a, b, sx, c1, c2;			//���ָ��

int uk;				//ȱʧ��ʶ���Ĺ����뷽��������

bool blockbegsys[NSY];
bool statbegsys[NSY];
bool facbegsys[NSY];
bool statfolsys[NSY];//��ʱ��û�г�ʼ��

int display[LMAX];
double rconst[C2MAX];
struct table tab[TMAX];
struct btable btab[BMAX];
struct atable atab[AMAX];
struct order code[CMAX];
char stab[SMAX];


FILE *input, *output;
