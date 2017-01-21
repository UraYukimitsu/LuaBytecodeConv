#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OPs 6
#define As  8
#define Bs  9
#define Cs  9
#define Bxs (Bs + Cs)
#define Axs (As + Bs + Cs)

typedef struct _Bytecode {
	char name[10];
	int opcode;
	int A;
	int B;
	int C;
	int Bsp;
} Bytecode;

Bytecode *new_B(char *name, int opcode, int A, int B, int C, int Bsp)
{
	Bytecode *ret = NULL;
	ret = malloc(sizeof(Bytecode));
	if(!ret)
		exit(1);
		
	strcpy(ret->name, name);
	ret->opcode = opcode;
	ret->A      = A;
	ret->B      = B;
	ret->C      = C;
	ret->Bsp     = Bsp;
	
	return ret;
}

void strupp(char* s)
{
    while (*s = toupper(*s)) s++;
}

int main(int argc, char **argv)
{
	Bytecode *tbl[40];
	Bytecode *b = NULL;
	int ret = 0, arg = 0;
	int i = 0, used = 0, tmp = 0, Bx = 0;
	tbl[0]  = new_B("MOVE",      0, As , Bs , Cs, 0);
	tbl[1]  = new_B("LOADK",     1, As , Bxs, 0 , 0);
	tbl[2]  = new_B("LOADKX",    2, As , Bs , Cs, 0);
	tbl[3]  = new_B("LOADBOOL",  3, As , Bs , Cs, 0);
	tbl[4]  = new_B("LOADNIL",   4, As , Bs , Cs, 0); 
	tbl[5]  = new_B("GETUPVAL",  5, As , Bs , Cs, 0);
	tbl[6]  = new_B("GETTABUP",  6, As , Bs , Cs, 0);
	tbl[7]  = new_B("GETTABLE",  7, As , Bs , Cs, 0);
	tbl[8]  = new_B("SETTABUP",  8, As , Bs , Cs, 0);
	tbl[9]  = new_B("SETUPVAL",  9, As , Bs , Cs, 0);
	tbl[10] = new_B("SETTABLE", 10, As , Bs , Cs, 0);
	tbl[11] = new_B("NEWTABLE", 11, As , Bs , Cs, 0);
	tbl[12] = new_B("SELF",     12, As , Bs , Cs, 0);
	tbl[13] = new_B("ADD",      13, As , Bs , Cs, 0);
	tbl[14] = new_B("SUB",      14, As , Bs , Cs, 0);
	tbl[15] = new_B("MUL",      15, As , Bs , Cs, 0);
	tbl[16] = new_B("DIV",      16, As , Bs , Cs, 0);
	tbl[17] = new_B("MOD",      17, As , Bs , Cs, 0);
	tbl[18] = new_B("POW",      18, As , Bs , Cs, 0);
	tbl[19] = new_B("UNM",      19, As , Bs , Cs, 0);
	tbl[20] = new_B("NOT",      20, As , Bs , Cs, 0);
	tbl[21] = new_B("LEN",      21, As , Bs , Cs, 0);
	tbl[22] = new_B("CONCAT",   22, As , Bs , Cs, 0);
	tbl[23] = new_B("JMP",      23, As , Bxs, 0 , 1);
	tbl[24] = new_B("EQ",       24, As , Bs , Cs, 0);
	tbl[25] = new_B("LT",       25, As , Bs , Cs, 0);
	tbl[26] = new_B("LE",       26, As , Bs , Cs, 0);
	tbl[27] = new_B("TEST",     27, As , 0  , Cs, 0);
	tbl[28] = new_B("TESTSET",  28, As , Bs , Cs, 0);
	tbl[29] = new_B("CALL",     29, As , Bs , Cs, 0);
	tbl[30] = new_B("TAILCALL", 30, As , Bs , Cs, 0);
	tbl[31] = new_B("RETURN",   31, As , Bs , Cs, 0);
	tbl[32] = new_B("FORLOOP",  32, As , Bxs, 0 , 1);
	tbl[33] = new_B("FORPREP",  33, As , Bxs, 0 , 1);
	tbl[34] = new_B("TFORCALL", 34, As , 0  , Cs, 0);
	tbl[35] = new_B("TFORLOOP", 35, As , Bxs, 0 , 1);
	tbl[36] = new_B("SETLIST",  36, As , Bs , Cs, 0);
	tbl[37] = new_B("CLOSURE",  37, As , Bxs, 0 , 0);
	tbl[38] = new_B("VARARG",   38, As , Bs , Cs, 0);
	tbl[39] = new_B("EXTRAARG", 39, Axs, 0  , 0 , 0);
	
	if(argc > 2)
	{
		strupp(argv[1]);
		while(strcmp(argv[1], tbl[i]->name)) if(++i == 40) return 1;
		b = tbl[i];
		ret = b->opcode << used;
		ret = b->opcode;
		used += OPs;
		arg = atoi(argv[2]);
		if(arg < 0) arg = -arg - 1;;
		ret = ret | arg << used;
		used += b->A;

		if(argc > 4)
		{
			arg = atoi(argv[4]);
			tmp = b->C;
			if(!tmp) {used += Cs; tmp = b->B;}
			if(arg < 0)
			{
				arg = -arg - 1;
				arg |= 1 << (tmp - 1);
			}
			ret = ret | arg << used;
		}
		
		used += b->C;

		if(argc > 3)
		{
			arg = atoi(argv[3]);
			tmp = b->B;
			if(b->Bsp)
				arg = -arg;
			if(arg < 0)
			{
				arg = -arg - 1;
				if(b->Bsp || b->B == Bs) arg |= 1 << (tmp - 1);
			}
			ret = ret | arg << used;
			used += tmp;
		}

		printf("%02X %02X %02X %02X\n", 
			(ret >> 0 )&0xFF,
			(ret >> 8 )&0xFF,
			(ret >> 16)&0xFF,
			(ret >> 24)&0xFF
		);
	}

	for(i = 0; i < 40; i++)
		free(tbl[i]);
	return 0;
}
