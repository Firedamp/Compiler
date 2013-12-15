#include"head.h"

void condition(item *x){
	item y;
	symbol op;
	expression(x);
	if(sym == EQL || sym == NEQ || sym == LSS || sym == LEQ || sym == GRE || sym == GEQ){
		op = sym;
		getsym();
		expression(&y);
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
					break;
				
				}
			}
			else
				error(53);//左右两边类型无法比较
		}
		x->typ = INTS;
	}
}

void expression(item *x){
	item y;
	symbol op;
	if(sym == PLUS || sym == MINU){
		op = sym;
		getsym();
		term(x);
		if(x->typ > REALS)/////char不行吗
			error(33);//错误的类型
		else if(sym == MINU)
			emit(36);
	}
	else
		term(x);
	while(sym == PLUS || sym == MINU){
		op = sym;
		getsym();
		term(&y);
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
	}
}

types resulttype(types a, types b){
	if(a > REALS || b > REALS){
		error(33);
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
