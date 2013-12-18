#include"head.h"

void interpret(){
	order ir;
	int pc;
	int t;
	int b;
	int h1, h2, h3, h4;
	char c;
	int lncnt, ocnt, blkcnt, chrcnt;
	int fld[4];
	int display[LMAX];
	stack s[STACKSIZE];
	pss ps;

	s[0].i = 0;
	s[1].i = 0;
	s[2].i = -1;
	s[3].i = 1;
	display[0] = 0;
	display[1] = 0;
	t = btab[0].vsize - 1;
	b = 0;
	pc = tab[1].adr;
	lncnt = 0;
	ocnt = 0;
	chrcnt = 0;
	ps = RUN;
	fld[0] = 10;
	fld[1] = 22;
	fld[2] = 10;
	fld[3] = 1;

	while(pc < lc && ps == RUN){
		ir = code[pc];
		pc++;
		ocnt++;
		switch (ir.f)
		{
		case 0:
			t++;
			if(t >= STACKSIZE)
				ps = STKCHK;
			else
				s[t].i = display[ir.x] + ir.y;
			break;
		case 1:
			t++;
			if(t >= STACKSIZE)
				ps = STKCHK;
			else
				s[t] = s[display[ir.x] + ir.y];
			break;
		case 2:
			t++;
			if(t >= STACKSIZE)
				ps = STKCHK;
			else
				s[t] = s[s[display[ir.x] + ir.y].i];
			break;
		case 3:
			h1 = ir.y;
			h2 = ir.x;
			h3 = b;
			do{
				display[h1] = h3;
				h1--;
				h3 = s[h3+2].i;
			}while(h1 != h2);
			break;
		case 8:
			break;
		case 9:
			s[t].i = s[t].i + ir.y;
			break;
		case 10:
			pc = ir.y;
			break;
		case 11:
			if(!s[t].i)
				pc = ir.y;
			t--;
			break;
		case 12:
			h1 = s[t].i;
			t--;
			h2 = ir.y;
			h3 = 0;
			do{
				if(code[h2].f != 13){
					h3 = 1;
					ps = CASCHK;
				}
				else if(code[h2].x == h1){
					h3 = 1;
					pc = code[h2].y;
				}
				else
<<<<<<< HEAD
<<<<<<< HEAD
					h2 += 2;
=======
					h2++;
>>>>>>> 9d8a88ef10a1bd22ac4a88d9c2ead270c339447e
=======
					h2++;
>>>>>>> 9d8a88ef10a1bd22ac4a88d9c2ead270c339447e
			}while(h3 == 0);
			break;
		case 14:
			h1 = s[t-1].i;
			if(h1 <= s[t].i)
				s[s[t-2].i].i = h1;
			else{
				t = t-3;
				pc = ir.y;
			}
			break;
		case 15:
			h2 = s[t-2].i;
			h1 = s[h2].i + 1;
			if(h1 <= s[t].i){
				s[h2].i = h1;
				pc = ir.y;
			}
			else
				t = t - 3;
			break;
		case 16:
			h1 = s[t-1].i;
			if(h1 >= s[t].i)
				s[s[t-2].i].i = h1;
			else{
				pc = ir.y;
				t = t - 3;
			}
			break;
		case 17:
			h2 = s[t-2].i;
			h1 = s[h2].i  - 1;
			if(h1 >= s[t].i){
				s[h2].i = h1;
				pc = ir.y;
			}
			else
				t = t - 3;
			break;
		case 18:
			h1 = btab[tab[ir.y].ref].vsize;
			if(t + h1 >= STACKSIZE)
				ps = STKCHK;
			else{
				t = t + 5;
				s[t-1].i = h1 - 1;
				s[t].i = ir.y;
			}
			break;
		case 19:
			h1 = t - ir.y;
			h2 = s[h1+4].i;
			h3 = tab[h2].lev;
			display[h3+1] = h1;
			h4 = s[h1+3].i + h1;
			s[h1+1].i = pc;
			s[h1+2].i = display[h3];
			s[h1+3].i = b;
			for(h3 = t+1; h3 <= h4; h3++)
				s[h3].i = 0;
			b = h1;
			t = h4;
			pc = tab[h2].adr;
			//if(stackdump)
			//	dump
			break;
		case 20:
			h1 = ir.y;
			h2 = 0;
			h3 = s[t].i;
			if(h3 < h2)
				ps = INXCHK;
			else if(h1 >= atab[h1].size)
				ps = INXCHK;
			else{
				t--;
				s[t].i = s[t].i + h3 - h2;
			}
			break;
		case 21:
			h1 = ir.y;
			h2 = 0;
			h3 = s[t].i;
			if(h3 < h2)
				ps = INXCHK;
			else if(h3 >= atab[h1].size)
				ps = INXCHK;
			else{
				t--;
				s[t].i = s[t].i + (h3 - h2);
			}
			break;
		case 22:
			h1 = s[t].i;
			t--;
			h2 = ir.y + t;
			if(h2 >= STACKSIZE)
				ps = STKCHK;
			else{
				while(t < h2){
					t++;
					s[t] = s[h1];
					h1++;
				}
			}
			break;
		case 23:
			h1 = s[t-1].i;
			h2 = s[t].i;
			h3 = h1 + ir.y;
			while(h1 < h3){
				s[h1] = s[h2];
				h1++;
				h2++;
			}
			t = t - 2;
			break;
		case 24:
			t++;
			if(t >= STACKSIZE)
				ps = STKCHK;
			else
				s[t].i = ir.y;
			break;
		case 25:
			t++;
			if(t >= STACKSIZE)
				ps = STKCHK;
			else
				s[t].r = rconst[ir.y];
			break;
		case 26:
			h1 = t - ir.y;
			s[h1].r = s[h1].i;
			break;
		case 27:
			if(ir.y == 1)
				scanf("%d", &s[s[t].i].i);
			else if(ir.y == 2)
				scanf("%lf", &s[s[t].i].r);
			else if(ir.y == 3){
				scanf("%c", &c);
				s[s[t].i].i = c;
			}
			t--;
			break;
		case 28:
			h1 = s[t].i;
			h2 = ir.y;
			t--;
//			chrcnt = chrcnt + h1;
			if(/*chrcnt*/h1 > LINELENG)
				ps = LNGCHK;
			do{
				printf("%c", stab[h2]);
				h1--;
				h2++;
			}while(h1 != 0);
			break;
		case 29:
			if(ir.y == 1)
				printf("%d", s[t].i);
			else if(ir.y == 2)
				printf("%lf", s[t].r);
			else if(ir.y == 3)
				printf("%c", s[t].i);
			t--;
			break;
		case 30:
			break;
		case 31:
			ps = FIN;
			break;
		case 32:
			t = b;
			pc = s[b+1].i;
			b = s[b+3].i;
			break;
		case 33:
			t = b;
			pc = s[b+1].i;
			b = s[b+3].i;
			break;
		case 34:
			s[t] = s[s[t].i];
			break;
		case 35:
			s[t].i = !s[t].i;
			break;
		case 36:
			s[t].i = -s[t].i;
			s[t].r = -s[t].r;
			break;
		case 37:
			break;
		case 38:
			s[s[t-1].i] = s[t];
			t = t-2;
			break;
		case 39:
			t--;
			s[t].i = (s[t].r == s[t+1].r);
			break;
		case 40:
			t--;
			s[t].i = (s[t].r != s[t+1].r);
			break;
		case 41:
			t--;
			s[t].i = (s[t].r < s[t+1].r);
			break;
		case 42:
			t--;
			s[t].i = (s[t].r <= s[t+1].r);
			break;
		case 43:
			t--;
			s[t].i = (s[t].r > s[t+1].r);
			break;
		case 44:
			t--;
			s[t].i = (s[t].r >= s[t+1].r);
			break;
		case 45:
			t--;
			s[t].i = (s[t].i == s[t+1].i);
			break;
		case 46:
			t--;
			s[t].i = (s[t].i != s[t+1].i);
			break;
		case 47:
			t--;
			s[t].i = (s[t].i < s[t+1].i);
			break;
		case 48:
			t--;
			s[t].i = (s[t].i <= s[t+1].i);
			break;
		case 49:
			t--;
			s[t].i = (s[t].i > s[t+1].i);
			break;
		case 50:
			t--;
			s[t].i = (s[t].i >= s[t+1].i);
			break;
		case 51:
			t--;
			s[t].i = (s[t].i || s[t+1].i);
			break;
		case 52:
			t--;
			s[t].i = s[t].i + s[t+1].i;
			break;
		case 53:
			t--;
			s[t].i = s[t].i - s[t+1].i;
			break;
		case 54:
			t--;
			s[t].r = s[t].r + s[t+1].r;
			break;
		case 55:
			t--;
			s[t].r = s[t].r - s[t+1].r;
			break;
		case 56:
			t--;
			s[t].i = (s[t].i && s[t+1].i);
			break;
		case 57:
			t--;
			s[t].i = s[t].i * s[t+1].i;
			break;
		case 58:
			t--;
			if(s[t+1].i == 0)
				ps = DIVCHK;
			else
				s[t].i = s[t].i / s[t+1].i;
			break;
		case 59:
			t--;
			if(s[t+1].i == 0)
				ps = DIVCHK;
			else
				s[t].i = s[t].i % s[t+1].i;
			break;
		case 60:
			t--;
			s[t].r = (s[t].r * s[t+1].r);
			break;
		case 61:
			t--;
			s[t].r = (s[t].r / s[t+1].r);
			break;
		case 62:
			break;
		case 63:
			break;

		default:
			break;
		}
	}
}

