#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

//struct for history linked list
typedef struct _NODE{
	char cmd[256];
	struct _NODE *link;
}node;
//struct for hash table
typedef struct _TABLE{
	char monic[10];
	unsigned int opcode;
	char format[5];
	struct _TABLE *link;
}table;
//struct for symtab
typedef struct _SYMBOL{
	char s[35];
	int loc;
	struct _SYMBOL *link;
}sym;
typedef struct _ESTAB{
	char csect[10];
	char symname[10];
	int add;
	int length;
	struct _ESTAB *link;
}estab;

node *head=NULL;//history
table *ht[20];//hash table(optable)
sym *symtb[20];//symtab
sym *obj=NULL;//linked list for modification record
estab *tb=NULL;//estab
int* bplist;//bp list
int bpnum=0;//bp number
//Shell command
void Shell_help();
void Shell_dir();
void Shell_history();
int Shell_type(char filename[256]);
//memory command
void Shell_dump(int start,int end,int flag);
void Shell_edit(int address,int value);
void Shell_fill(int start, int end, int value);
void Shell_reset();
//opcode table command
int opcode_mnemonic(char monic[5]);
void opcodelist_print();
//linked_list(history)
void push(char cmdnode[256]);
//SIC/XE assmebler
int assemble(char filename[256]);
int wherebp(int exec,int pc);
int run(int len);
void printbp();

int loader(char file1[256],char file2[256],char file3[256],int num);
void mkest(char cs[10],char sym[10],int add,int length);//make estab
void mkbp(int bp);
//change number
int changechar(char*data,int len);
int changechar2(char*data,int len);
int changeop(char*operand);
//make linked list
void modi(int locctr);
//make hash table
void makeht();
void make_symht(int locctr,char label[35]);
//print symtab
void print_symtb();
//used for quick sort
int compare(const void *p1,const void *p2);
//find opcode or symbol or register
sym* find_sym(char label[35]);
table* find_op(char opcode[35]);
int find_regi(char *operand);
estab* find_es(char *symbol,char ***refer,int num);//for modification
estab* dup_es(char *symbol);//for check duplicate external symbol
//the last printed address
int dump_cnt;
int progad=0;
int execaddr;//do not used in this program(End record)
int symtb_size=0;
int proglen=-1;
int startrun=-1;//check start running
//int firstbp=0;

//command buffer
char cmd1[256];

const char *cmdlist[24] = {"h","help","d","dir","q","quit","hi","history","du","dump","e","edit","f","fill","reset","opcode","opcodelist","type","assemble","symbol","progaddr","loader","run","bp"};
const char *regi[10] = {"A","X","L","B","S","T","F",NULL,"PC","SW"};
//virtual memory
unsigned char *vir_mem;

int Rlist[10]={0,};//Register 0~9

