#include"head.h"

void condition(item *x, int level){
	item y;
	symbol op;
	expression(x, level);
	if(sym == EQL || sym == NEQ || sym == LSS || sym == LEQ || sym == GRE || sym == GEQ){
		op = sym;
		getsym();
		expression(&y, level);
		if((x->typ == INTS || x->typ == CHARS) && x->typ == y.typ){/////////////////////////int,char
			switch (op){
			case LSS:
				emit(47);
				break;
			case LEQ:
				emit(48);
				break;
			case GRE:
				emit(49);
				break;
			case GEQ:
				emit(50);
				break;
			case EQL:
				emit(45);
				break;
			case NEQ:
				emit(46);
				break;
			default:
				error(CONDITION, 60);
				break;
			}
		}
		else{
			if(x->typ == INTS){
				x->typ = REALS;
				emit(26, 1);
			}
			if(y.typ == INTS){
				y.typ = REALS;
				emit(26, 0);
			}
			if(x->typ == REALS && y.typ == REALS){
				switch (op){
				case LSS:
					emit(41);
					break;
				case LEQ:
					emit(42);
					break;
				case GRE:
					emit(43);
					break;
				case GEQ:
					emit(54);
					break;
				case EQL:
					emit(39);
					break;
				case NEQ:
					emit(40);
					break;
				default:
					error(CONDITION, 60);
					break;
				
				}
			}
			else
				error(CONDITION, 53);
		}
		x->typ = INTS;
	}
	else
		error(CONDITION, 60);
}

void expression(item *x, int level){
	item y;
	symbol op;
	if(sym == PLUS || sym == MINU){
		op = sym;
		getsym();
		term(x, level);
		if(x->typ > REALS)/////char不行吗
			error(EXPRESSION, 33);//错误的类型
		else if(sym == MINU)
			emit(36);
	}
	else
		term(x, level);
	while(sym == PLUS || sym == MINU){
		op = sym;
		getsym();
		term(&y, level);
		x->typ = resulttype(x->typ, y.typ);
		if(x->typ == NOTYP)
			;
		else if(x->typ == INTS){
			if(op == PLUS)
				emit(52);
			else
				emit(53);
		}
		else if(x->typ == REALS){
			if(op == PLUS)
				emit(54);
			else
				emit(55);
		}
		else
			error(EXPRESSION, 33);
	}
}

void term(item *x, int level){
	item y;
	symbol op;
	factor(x, level);
	while(sym == MULT || sym == DIV){
		op = sym;
		getsym();
		factor(&y, level);
		if(op == MULT){
			x->typ = resulttype(x->typ, y.typ);
			if(x->typ == NOTYP)
				;
			else if(x->typ == INTS)
				emit(57);
			else if(x->typ == REALS)
				emit(60);
			else
				error(TERM, 33);
		}
		else if(op == DIV){
			x->typ = resulttype(x->typ, y.typ);
			if(x->typ == NOTYP)
				;
			else if(x->typ == INTS)
				emit(58);
			else if(x->typ == REALS)
				emit(61);
			else
				error(TERM, 33);
		}
	}
}

void factor(item *x, int level){
	int i, f;
	x->typ = NOTYP;
	x->ref = 0;
	test();
	while(facbegsys[sym]){
		if(sym == IDEN){
			i = loc(token, level);
			getsym();
			if(tab[i].obj == CONSTANT){
				x->typ = tab[i].typ;
				x->ref = 0;
				if(x->typ == REALS)
					emit(25, tab[i].adr);
				else
					emit(24, tab[i].adr);
			}
			else if(tab[i].obj == VARIABLE){
				x->typ = tab[i].typ;
				x->ref = tab[i].ref;
				if(sym == LBRACK){
					if(tab[i].normal)
						f = 0;
					else
						f = 1;
					emit(f, tab[i].lev, tab[i].adr);
					
					/*getsym();						//selector
					expression(&z, level);
					if(x->typ != ARRAYS)
						error(28);//变量不是数组
					else{
						if(z.typ != INTS)
							error(26);//数组下标为整数
						else
							emit(20, x->ref);
						x->typ = atab[x->ref].eltyp;
						x->ref = 0;
					}
					getsym();
					if(sym == RBRACK)
						getsym();
					else
						error();*/
					selector(x, level);

					emit(34);
				}
				else{
					if(x->typ == NOTYP || x->typ == INTS || x->typ == REALS || x->typ == CHARS){
						if(tab[i].normal)
							f = 1;
						else
							f = 2;
					}
					else
						error(FACTOR, 33);
					emit(f, tab[i].lev, tab[i].adr);
				}
					
			}
			else if(tab[i].obj == FUNCTION){
				x->typ = tab[i].typ;
				callstatement(i, level);
			}
			else
				error(FACTOR, 33);
		}
		else if(sym == REALCON || sym == INTCON){//////我的文法中应该是没有char的这里
			if(sym == REALCON){
				x->typ = REALS;
				enterreal(rnum);
				emit(25, c1);
			}
			else{
				x->typ = INTS;
				emit(24, inum);
			}
			x->ref = 0;
			getsym();
		}
		else if(sym == LPARENT){
			getsym();
			expression(x, level);
			if(sym == RPARENT)
				getsym();
			else
				error(FACTOR, 4);
		}
		else
			error(FACTOR, 33);
	}
}

types resulttype(types a, types b){
	if(a > REALS || b > REALS){
		error(RESULTTYPE, 33);
		return NOTYP;
	}
	else if(a == NOTYP || b == NOTYP)
		return NOTYP;
	else if(a == INTS){
		if(b == INTS)
			return INTS;
		else{
			emit(26, 1);
			return REALS;
		}
	}
	else{
		if(b == INTS)
			emit(26, 0);
		return REALS;
	}
}

void selector(item *v, int level){
	item x;
	int a, j;
	getsym();						//selector
	expression(&x, level);
	if(v->typ != ARRAYS)
	error(SELECTOR, 28);//变量不是数组
	else{
	if(x.typ != INTS)
		error(SELECTOR, 26);//数组下标为整数
	else
		emit(20, v->ref);
	v->typ = atab[v->ref].eltyp;
	v->ref = 0;
	}
	//getsym();
	if(sym == RBRACK)
		getsym();
	else
		error(SELECTOR, 12);
}