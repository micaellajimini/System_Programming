#include"20151567.h"

int main(){
		int fr;
		char str1[256];
		dump_cnt=-1;//dump_cnt : the last address which is printed
		progad=0;//default: progaddr=0x00
		makeht();//make hash table
		vir_mem=(unsigned char*)calloc(1048576,sizeof(char));//virtual memory is made
		bplist=(int*)calloc(1048576,sizeof(char));

		while(1){
				cmd1[0]='\0';
				printf("sicsim> ");
				fgets(str1,256,stdin);//scanf all
				sscanf(str1,"%s",cmd1);//check command first
				if(cmd1[0]=='\0'&&(str1[0]=='\n'||str1[0]==' '||str1[0]=='\t')) continue;//if enter,tab,space with no command, go prompt
				else if(strcmp(cmd1,cmdlist[0])==0||strcmp(cmd1,cmdlist[1])==0) {//help
						char trash[256]={0};
						sscanf(str1,"%s %s",cmd1,trash);
						if(trash[0]!='\0'){// if command is with extra input, error 
								printf("command is wrong\n");	
								continue;
						}
						push(str1);//if it is right command, store at history list
						Shell_help();
				}
				else if(strcmp(cmd1,cmdlist[2])==0||strcmp(cmd1,cmdlist[3])==0){//directory
						char trash[256]={0};
						sscanf(str1,"%s %s",cmd1,trash);
						if(trash[0]!='\0'){//if command is with extra input, error
								printf("command is wrong\n");	
								continue;
						}
						push(str1);//if it is right command, store at history list
						Shell_dir();
				}
				else if(strcmp(cmd1,cmdlist[4])==0||strcmp(cmd1,cmdlist[5])==0) {//quit
						char trash[256]={0};
						sscanf(str1,"%s %s",cmd1,trash);
						if(trash[0]!='\0'){//if command is with extra input, error
								printf("command is wrong\n");	
								continue;
						}
						push(str1);//if it is right command, store at history list
						break;
				}
				else if(strcmp(cmd1,cmdlist[6])==0||strcmp(cmd1,cmdlist[7])==0){//history
						char trash[256]={0};
						sscanf(str1,"%s %s",cmd1,trash);
						if(trash[0]!='\0'){//if command is with extra input, error
								printf("command is wrong\n");	
								continue;
						}
						push(str1);//if it is right command, store at history list. history is also stored
						if(head==NULL) continue;
						else Shell_history();
				}
				else if(strcmp(cmd1,cmdlist[8])==0||strcmp(cmd1,cmdlist[9])==0) {//dump - tokenize one by one
						int i=0,j=0;
						int start,end;
						int len;
						char stbuf[256],enbuf[256];//startstring,endstring
						int flag;
						int suc;
						int flagw=0;

						while(str1[i]==' '||str1[i]=='\t') {i++;}//deny space or tab

						for(j=0;str1[i]!=' '&&str1[i]!='\t'&&str1[i]!='\n';i++,j++){//command
								cmd1[j]=str1[i];
						}

						while(str1[i]==' '||str1[i]=='\t') {i++;}//deny space or tab

						if(str1[i]=='\n') {//only dump : flag=0
								flag=0;
								push(str1);
								Shell_dump(start,end,flag);
								continue;
						}
						else{
								if(str1[i]==',') {//when ',' is before start address
										printf("command is wrong\n");
										continue;
								}
								for(j=0;str1[i]!=' '&&str1[i]!=','&&str1[i]!='\t'&&str1[i]!='\n';i++,j++){
										stbuf[j]=str1[i];
								}
								len=j;
								suc=changechar(stbuf,len);//get start
								if(suc==-1) {
										printf("command is wrong\n");
										continue;
								}
								else start=suc;

								while(str1[i]==' '||str1[i]=='\t') {i++;}
								if(str1[i]=='\n') {//dump start : flag=1
										if(start<0||start>=1048576){//if start address is not in boundary
												printf("command is wrong(boundary error)\n");
												continue;
										}
										flag=1;
										push(str1);
										Shell_dump(start,end,flag);
										continue;
								}
								else if(str1[i]!=',') {//if there are more ',' after ','
										printf("command is wrong\n");
										continue;
								}
								i++;//','

								while(str1[i]==' '||str1[i]=='\t') {i++;}
								for(j=0;str1[i]!=' '&&str1[i]!=','&&str1[i]!='\t'&&str1[i]!='\n';i++,j++){
										enbuf[j]=str1[i];
								}
								len=j;
								suc=changechar(enbuf,len);//get end
								if(suc==-1){
										printf("command is wrong\n");
										continue;
								}
								else end=suc;

								while(str1[i]!='\n'){
										if(str1[i]!=' '&&str1[i]!='\t'){//if there are extra input, error
												printf("command is wrong\n");
												flagw=1;
												break;
										}
										i++;
								}
								if(flagw==1) continue;

						}
						if(start<0||end<0||start>=1048576||end>=1048576||start>end){//check boundary
								printf("command is wrong(boundary error)\n");
								continue;
						}
						flag=2;
						push(str1);
						Shell_dump(start,end,flag);//dump start,end
				}
				else if(strcmp(cmd1,cmdlist[10])==0||strcmp(cmd1,cmdlist[11])==0) {//edit
						char trash[256]={0};
						int address,value;
						char comma;
						int errch;
						errch=sscanf(str1,"%s %8x %c %8x %s",cmd1,&address,&comma,&value,trash);//check if it is right command
						if(errch>=0&&errch<4) {
								printf("command is wrong\n");
								continue;
						}
						else if(trash[0]!='\0'){
								printf("command is wrong\n");	
								continue;
						}
						else if(address<0 || address>=1048576){//check boundary
								printf("command is wrong\n");
								continue;
						}
						else if(comma!=','){
								printf("command is wrong\n");
								continue;
						}
						else if(value<0 || value>=256){//check boundary
								printf("command is wrong\n");
								continue;
						}
						else{
								push(str1);
								Shell_edit(address,value);
						}
				}
				else if(strcmp(cmd1,cmdlist[12])==0||strcmp(cmd1,cmdlist[13])==0) {//fill
						char trash[256]={0};
						int start,end,value;
						char comma1,comma2;
						int errch;

						errch=sscanf(str1,"%s %8x %c %8x %c %8x %s",cmd1,&start,&comma1,&end,&comma2,&value,trash);//check if it is right command
						if(errch>=0&&errch<6){
								printf("command is wrong\n");
								continue;
						}
						else if(trash[0]!='\0'){
								printf("command is wrong\n");
								continue;
						}
						else if(start<0||end<0||start>=1048576||end>=1048576||start>end){//check boundary
								printf("command is wrong\n");
								continue;
						}
						else if(comma1!=','||comma2!=','){
								printf("command is wrong\n");
								continue;
						}
						else if(value<0 || value>=256){//check boundary
								printf("command is wrong\n");
								continue;
						}
						else{
								push(str1);
								Shell_fill(start,end,value);
						}
				}
				else if(strcmp(cmd1,cmdlist[14])==0) {//reset
						char trash[256]={0};
						sscanf(str1,"%s %s",cmd1,trash);
						if(trash[0]!='\0'){//if there are extra input
								printf("command is wrong\n");
								continue;
						}
						push(str1);
						Shell_reset();
				}
				else if(strcmp(cmd1,cmdlist[15])==0) {//opcode mnemonic
						char trash[256]={0};
						char mnemonic[10];
						int errch,notc=0;
						int no;
						int i;

						errch=sscanf(str1,"%s %s %s",cmd1,mnemonic,trash);//check if it is right command
						if(errch<2){
								printf("command is wrong\n");
								continue;
						}
						else if(trash[0]!='\0'){
								printf("command is wrong\n");
								continue;
						}
						for(i=0;i<strlen(mnemonic);i++){
								if(mnemonic[i]<'A'||mnemonic[i]>'Z'){//if mnemonic is not capital letter, error
										notc=-1;
										break;
								}
						}
						if(notc==-1){
								printf("command is wrong\n");
								continue;
						}
						no=opcode_mnemonic(mnemonic);//if there are no such mnemonic
						if(no==-1){
								printf("command is wrong\n");
								continue;
						}
						else{
								push(str1);//store at history
						}

				}
				else if(strcmp(cmd1,cmdlist[16])==0) {
						char trash[256]={0};

						sscanf(str1,"%s %s",cmd1,trash);//if extra input
						if(trash[0]!='\0'){
								printf("command is wrong!\n");
								continue;
						}
						push(str1);
						opcodelist_print();
				}
				else if(strcmp(cmd1,cmdlist[17])==0){//type filename
						char trash[256]={0};
						char filename[256]={0};
						int check;
						sscanf(str1,"%s %s %s",cmd1,filename,trash);
						if(trash[0]!='\0'||filename[0]=='\0'){
								printf("command is wrong!\n");
								continue;
						}
						check=Shell_type(filename);
						if(check==-1){
								printf("there is no file!\n");
						}
						push(str1);
				}
				else if(strcmp(cmd1,cmdlist[18])==0){//assemble filename
						char trash[256]={0};
						char filename[256]={0};
						char fi[5];
						int filen;
						int check;
						FILE *in;
						int r;
						for(r=0;r<20;r++){
								free(symtb[r]);
								symtb[r]=NULL;
						}//before assemble, initialize symbol_table
						free(obj);
						obj=NULL;
						symtb_size=0;
						sscanf(str1,"%s %s %s",cmd1,filename,trash);
						if(trash[0]!='\0'||filename[0]=='\0'){
								printf("command is wrong!\n");
								continue;
						}
						else if(strlen(filename)<=4){
								printf("filename is wrong!\n");
								continue;
						}
						else{
								filen=strlen(filename);
								strcpy(fi,filename+filen-4);
								if(strcmp(fi,".asm")!=0){//filename check
										printf("filename is wrong!\n");
										continue;
								}
								else{
										in=fopen(filename,"r");//check if there is file
										if(in==NULL){
												printf("There is no such filename\n");
												continue;
										}
								}

								check=assemble(filename);
								if(check==-1){//during assemble, if error exist, go to prompt
										continue;
								}
								push(str1);
						}
				}
				else if(strcmp(cmd1,cmdlist[19])==0){//symbol
						char trash[256]={'\0',};
						sscanf(str1,"%s %s",cmd1,trash);
						if(trash[0]!='\0'){
							printf("command is wrong!\n");
							continue;
						}
						push(str1);
						print_symtb();
				}
				else if(strcmp(cmd1,cmdlist[20])==0){//progaddr
					char add[10]={'\0',};
					char trash[256]={'\0',};
					sscanf(str1,"%s %s %s",cmd1,add,trash);
					if(trash[0]!='\0'){
						printf("command is wrong!\n");
						continue;
					}
					if(add[0]!='\0'){
						progad=changechar2(add,strlen(add));
						if(progad==-1){
							printf("address is wrong!\n");
							continue;
						}
						push(str1);
					}
					else{
						printf("command is wrong!\n");
						continue;
					}
				}
				else if(strcmp(cmd1,cmdlist[21])==0){//loader
					char file1[35]={'\0',};
					char file2[35]={'\0',};
					char file3[35]={'\0',};
					char trash[256]={'\0',};
					int num=0;
					int checker;

					sscanf(str1,"%s %s %s %s %s",cmd1,file1,file2,file3,trash);
					if(trash[0]!='\0'){
						printf("command is wrong!\n");
						continue;
					}
					if(file1[0]=='\0'){
						printf("There is no object file!\n");
						continue;
					}
					else{
						if(strcmp(file1+strlen(file1)-4,".obj")!=0){
							printf("filename is wrong!\n");
							continue;
						}
						num++;
					}
					if(file2[0]!='\0'){
						if(strcmp(file2+strlen(file2)-4,".obj")!=0){
							printf("filename is wrong!\n");
							continue;
						}
						num++;
					}
					if(file3[0]!='\0'){
						if(strcmp(file3+strlen(file3)-4,".obj")!=0){
							printf("filename is wrong!\n");
							continue;
						}
						num++;
					}
					free(tb);
					tb=NULL;
					proglen=-1;
					checker=loader(file1,file2,file3,num);
					if(checker==-1) continue;
					push(str1);

				}
				else if(strcmp(cmd1,cmdlist[22])==0){//run
					char trash[256]={'\0',};
					int checkrun;

					sscanf(str1,"%s %s",cmd1,trash);
					if(trash[0]!='\0'){
						printf("command is wrong!\n");
						continue;
					}
					else if(proglen==-1){
						printf("error : no linking&loading before\n");
						continue;
					}
					if(startrun==-1) {
							int k;
							for(k=0;k<10;k++){
								Rlist[k]=0;
							}
							Rlist[8]=progad;
							//Rlist[2]=progad+proglen;//
							startrun=0;
					}
					checkrun=run(proglen);
					if(checkrun==-1) continue;
					else push(str1);
				}
				else if(strcmp(cmd1,cmdlist[23])==0){//bp
					char add[256]={'\0',};
					char trash[256]={'\0',};
					int bpi;
					int bpbuf;

					sscanf(str1,"%s %s %s",cmd1,add,trash);
					if(trash[0]!='\0'){
						printf("command is wrong!\n");
						continue;
					}
					else if(add[0]=='\0'){//bp
						printf("\t\tbreakpoint\n");
						printf("\t\t-------\n");
						for(bpi=0;bpi<bpnum;bpi++){
							printf("\t\t%-X\n",bplist[bpi]);
						}
					}
					else{
						if(strcmp(add,"clear")==0){//bp clear
							for(bpi=0;bpi<bpnum;bpi++){
								bplist[bpi]=0;
							}
							bpnum=0;
							printf("\t\t[ok] clear all breakpoints\n");
						}
						else {//set bp
								if(strlen(add)>5){
									printf("command is wrong!\n");
									continue;
								}
								bpbuf=changechar2(add,strlen(add));
								if(bpbuf==-1){
									printf("command is wrong!\n");
									continue;
								}
								mkbp(bpbuf);
								printf("\t\t[ok] create breakpoint %X\n",bpbuf);
						}
					}
					push(str1);

				}
				else {
						printf("command is wrong\n");
				}
		}
		free(vir_mem);//free memory
		free(bplist);
		free(head);
		for(fr=0;fr<20;fr++){
				free(ht[fr]);
				free(symtb[fr]);
		}

		return 0;
}
/***********************************************************/
//print register(A,X,L,PC,B,S,T)
//at breakpoints
/***********************************************************/
void printbp(){
	printf("\t\tA : %06X X : %06X\n",Rlist[0],Rlist[1]);
	printf("\t\tL : %06X PC : %06X\n",Rlist[2],Rlist[8]);
	printf("\t\tB : %06X S : %06X\n",Rlist[3],Rlist[4]);
	printf("\t\tT : %06X\n",Rlist[5]);
}
/************************************************************/
//check valid bp
//int exec : executed instruction start address
//int pc : next instruction start address
/************************************************************/
int wherebp(int exec,int pc){
	int k;
	if(bpnum==0) return -1;
	for(k=0;k<bpnum;k++){
		if(pc==bplist[k]){
			//if(-4<pc-exec&&pc-exec<4) return -1;
			return k;
		}
	}
	return -1;
}
/*************************************************************/
//len=program length
//int execindex : now executed instruction start address
//int target : calculate TA
//int bpk : check bp
//char n,i,x,b,p,e : check bits
/*************************************************************/
int run(int len){
	int execindex;
	int target=0;
	//int between=0;
	int bpk;
	//int num=0;
	char n,i,x,b,p,e;
	//table *th;
	//Rlist[8]=execaddr;
	execindex=Rlist[8];
	while(1){
		n=(vir_mem[execindex]&0x02)>>1;
		i=vir_mem[execindex]&0x01;
		x=(vir_mem[execindex+1]&0x80)>>7;
		b=(vir_mem[execindex+1]&0x40)>>6;
		p=(vir_mem[execindex+1]&0x20)>>5;
		e=(vir_mem[execindex+1]&0x10)>>4;
		
		if((vir_mem[execindex]&0xFC)==0xB4){//CLEAR
			Rlist[vir_mem[execindex+1]>>4]=0;
			Rlist[8]+=2;
			bpk=wherebp(execindex,Rlist[8]);
			if(bpk!=-1){
				printbp();
				printf("\tStop at checkpoint[%X]\n",bplist[bpk]);
				break;
			}
			execindex+=2;
			continue;
		}
		else if((vir_mem[execindex]&0xFC)==0xA0){//COMPR
			if(Rlist[vir_mem[execindex+1]>>4]<Rlist[vir_mem[execindex+1]&0x0F]){
				Rlist[9]=-1;
			}
			else if(Rlist[vir_mem[execindex+1]>>4]==Rlist[vir_mem[execindex+1]&0x0F]){
				Rlist[9]=0;
			}
			else Rlist[9]=1;
			
			Rlist[8]+=2;
			bpk=wherebp(execindex,Rlist[8]);
			if(bpk!=-1){
				printbp();
				printf("\tStop at checkpoint[%X]\n",bplist[bpk]);
				break;
			}
			execindex+=2;
			continue;
		}
		else if((vir_mem[execindex]&0xFC)==0xB8){//TIXR
			Rlist[1]++;
			if(Rlist[1]<Rlist[vir_mem[execindex+1]>>4]) Rlist[9]=-1;
			else if(Rlist[1]==Rlist[vir_mem[execindex+1]>>4]) Rlist[9]=0;
			else Rlist[9]=1;

			Rlist[8]+=2;
			bpk=wherebp(execindex,Rlist[8]);
			if(bpk!=-1){
				printbp();
				printf("\tStop at checkpoint[%X]\n",bplist[bpk]);
				break;
			}
			execindex+=2;
			continue;
		}
		else if((vir_mem[execindex]&0xFC)==0x90){//ADDR
			Rlist[vir_mem[execindex+1]%16]=Rlist[vir_mem[execindex+1]>>4]+Rlist[vir_mem[execindex+1]%16];
			
			Rlist[8]+=2;
			bpk=wherebp(execindex,Rlist[8]);
			if(bpk!=-1){
				printbp();
				printf("\tStop at checkpoint[%X]\n",bplist[bpk]);
				break;
			}
			execindex+=2;
			continue;
		}
		else if((vir_mem[execindex]&0xFC)==0x9C){//DIVR
			Rlist[vir_mem[execindex+1]%16]=Rlist[vir_mem[execindex+1]%16]/Rlist[vir_mem[execindex+1]>>4];

			Rlist[8]+=2;
			bpk=wherebp(execindex,Rlist[8]);
			if(bpk!=-1){
				printbp();
				printf("\tStop at checkpoint[%X]\n",bplist[bpk]);
				break;
			}
			execindex+=2;
			continue;
		}
		else if((vir_mem[execindex]&0xFC)==0x98){//MULR
			Rlist[vir_mem[execindex+1]%16]=Rlist[vir_mem[execindex+1]%16]*Rlist[vir_mem[execindex+1]>>4];

			Rlist[8]+=2;
			bpk=wherebp(execindex,Rlist[8]);
			if(bpk!=-1){
				printbp();
				printf("\tStop at checkpoint[%X]\n",bplist[bpk]);
				break;
			}
			execindex+=2;
			continue;
		}
		else if((vir_mem[execindex]&0xFC)==0x94){
			Rlist[vir_mem[execindex+1]%16]=Rlist[vir_mem[execindex+1]%16]-Rlist[vir_mem[execindex+1]>>4];

			Rlist[8]+=2;
			bpk=wherebp(execindex,Rlist[8]);
			if(bpk!=-1){
				printbp();
				printf("\tStop at checkpoint[%X]\n",bplist[bpk]);
				break;
			}
			execindex+=2;
			continue;
		}
		else{
			int a;
			a=vir_mem[execindex]&0xFC;
			if(a==0x90||a==0x9C||a==0x98||a==0xAC||a==0xA4||a==0xA8||a==0x94||a==0xB0){
				Rlist[8]+=2;
				bpk=wherebp(execindex,Rlist[8]);
				if(bpk!=-1){
					printbp();
					printf("\tStop at checkpoint[%X]\n",bplist[bpk]);
					break;
				}
				execindex+=2;
				continue;
			}
		}
		
		target=0;
		if(n==0&&i==0){//SIC
				Rlist[8]+=3;
				target+=vir_mem[execindex+2];
				target+=(vir_mem[execindex+1]&0x7F)*256;
				if((b!=1)&&((target&0x800)==0x800)){
					target=target-0xFFF-1;
				}
		}
		else{
				if(e==1){
					Rlist[8]+=4;
					target+=vir_mem[execindex+3];
					target+=vir_mem[execindex+2]*256;
					target+=(vir_mem[execindex+1]&0x0F)*256*256;
				}
				else{
					Rlist[8]+=3;
					target+=vir_mem[execindex+2];
					target+=(vir_mem[execindex+1]&0x0F)*256;;
				}
				if((b!=1)&&((target&0x800)==0x800)){
					target=target-0xFFF-1;
				}
		}
		if(x==1) target+=Rlist[1];
		if(p==1) target+=Rlist[8];
		else if(b==1) target+=Rlist[3];

		
		if((vir_mem[execindex]&0xFC)==0x14){//STL
			if(n==1&&i==1){//simple addressing
				int buf;
				buf=Rlist[2];
				vir_mem[target+2]=buf%256;
				buf=buf/256;
				vir_mem[target+1]=buf%256;
				buf=buf/256;
				vir_mem[target]=buf;
			//	printf("%X",buf);
			}
			else if(n==1){//indirect
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				vir_mem[buf+2]=Rlist[2]%256;
				vir_mem[buf+1]=(Rlist[2]/256)%256;
				vir_mem[buf]=Rlist[2]/(256*256);
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x7C){//STS
			if(n==1&&i==1){//simple addressing
				int buf;
				buf=Rlist[4];
				vir_mem[target+2]=buf%256;
				buf=buf/256;
				vir_mem[target+1]=buf%256;
				buf=buf/256;
				vir_mem[target]=buf;
			//	printf("%X",buf);
			}
			else if(n==1){//indirect
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				vir_mem[buf+2]=Rlist[4]%256;
				vir_mem[buf+1]=(Rlist[4]/256)%256;
				vir_mem[buf]=Rlist[4]/(256*256);
			}
		}
		else if((vir_mem[execindex]&0xFC)==0xE8){//STSW
			if(n==1&&i==1){//simple addressing
				int buf;
				buf=Rlist[9];
				vir_mem[target+2]=buf%256;
				buf=buf/256;
				vir_mem[target+1]=buf%256;
				buf=buf/256;
				vir_mem[target]=buf;
			//	printf("%X",buf);
			}
			else if(n==1){//indirect
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				vir_mem[buf+2]=Rlist[9]%256;
				vir_mem[buf+1]=(Rlist[9]/256)%256;
				vir_mem[buf]=Rlist[9]/(256*256);
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x84){//STT
			if(n==1&&i==1){//simple addressing
				int buf;
				buf=Rlist[5];
				vir_mem[target+2]=buf%256;
				buf=buf/256;
				vir_mem[target+1]=buf%256;
				buf=buf/256;
				vir_mem[target]=buf;
			//	printf("%X",buf);
			}
			else if(n==1){//indirect
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				vir_mem[buf+2]=Rlist[5]%256;
				vir_mem[buf+1]=(Rlist[5]/256)%256;
				vir_mem[buf]=Rlist[5]/(256*256);
			}
		}
		
		else if((vir_mem[execindex]&0xFC)==0x68){//LDB
			if(n==1&&i==1){
				Rlist[3]=vir_mem[target+2];
				Rlist[3]+=vir_mem[target+1]*256;
				Rlist[3]+=vir_mem[target]*256*256;
			}
			else if(n==1){
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				Rlist[3]=vir_mem[buf+2];
				Rlist[3]+=vir_mem[buf+1]*256;
				Rlist[3]+=vir_mem[buf]*256*256;
			}
			else if(i==1){
				Rlist[3]=target;
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x08){//LDL
			if(n==1&&i==1){
				Rlist[2]=vir_mem[target+2];
				Rlist[2]+=vir_mem[target+1]*256;
				Rlist[2]+=vir_mem[target]*256*256;
			}
			else if(n==1){
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				Rlist[2]=vir_mem[buf+2];
				Rlist[2]+=vir_mem[buf+1]*256;
				Rlist[2]+=vir_mem[buf]*256*256;
			}
			else if(i==1){
				Rlist[2]=target;
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x6C){//LDS
			if(n==1&&i==1){
				Rlist[4]=vir_mem[target+2];
				Rlist[4]+=vir_mem[target+1]*256;
				Rlist[4]+=vir_mem[target]*256*256;
			}
			else if(n==1){
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				Rlist[4]=vir_mem[buf+2];
				Rlist[4]+=vir_mem[buf+1]*256;
				Rlist[4]+=vir_mem[buf]*256*256;
			}
			else if(i==1){
				Rlist[4]=target;
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x04){//LDX
			if(n==1&&i==1){
				Rlist[1]=vir_mem[target+2];
				Rlist[1]+=vir_mem[target+1]*256;
				Rlist[1]+=vir_mem[target]*256*256;
			}
			else if(n==1){
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				Rlist[1]=vir_mem[buf+2];
				Rlist[1]+=vir_mem[buf+1]*256;
				Rlist[1]+=vir_mem[buf]*256*256;
			}
			else if(i==1){
				Rlist[1]=target;
			}
		}

		else if((vir_mem[execindex]&0xFC)==0x48){//JSUB
			if(n==1&&i==1){
				Rlist[2]=Rlist[8];
				Rlist[8]=target;
				//execindex=target;
			}
			//only simple
		}
		else if((vir_mem[execindex]&0xFC)==0x00){//LDA
			if(n==1&&i==1){
				Rlist[0]=vir_mem[target+2];
				Rlist[0]+=vir_mem[target+1]*256;
				Rlist[0]+=vir_mem[target]*256*256;
			}
			else if(n==1){
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				Rlist[0]=vir_mem[buf+2];
				Rlist[0]+=vir_mem[buf+1]*256;
				Rlist[0]+=vir_mem[buf]*256*256;
			}
			else if(i==1){
				Rlist[0]=target;
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x28){//COMP
			if(n==1&&i==1){
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				if(buf<Rlist[0]) Rlist[9]=1;
				else if(buf==Rlist[0]) Rlist[9]=0;
				else Rlist[9]=-1;
			}
			else if(n==1){
				int buf=0,this=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				this+=vir_mem[buf+2];
				this+=vir_mem[buf+1]*256;
				this+=vir_mem[buf]*256*256;
				if(this<Rlist[0]) Rlist[9]=1;
				else if(this==Rlist[0]) Rlist[9]=0;
				else Rlist[9]=-1;
			}
			else{
				if(target<Rlist[0]) Rlist[9]=1;
				else if(target==Rlist[0]) Rlist[9]=0;
				else Rlist[9]=-1;
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x30){//JEQ
			if(Rlist[9]!=0){
			//	if(e==1) execindex+=4;
			//	else execindex+=3;
			}
			else{
				if(n==1&&i==1){
					Rlist[8]=target;
			//		execindex=target;
				}
				//only simple
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x3C){//J
			if(i==1&&n==1){
				Rlist[8]=target;
			//	execindex=target;
			}
			else{
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				Rlist[8]=buf;
			//	execindex=buf;
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x0C){//STA
			if(n==1&&i==1){//simple addressing
				int buf;
				buf=Rlist[0];
				vir_mem[target+2]=buf%256;
				buf=buf/256;
				vir_mem[target+1]=buf%256;
				buf=buf/256;
				vir_mem[target]=buf;
			}
			else if(n==1){//indirect
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				vir_mem[buf+2]=Rlist[0]%256;
				vir_mem[buf+1]=(Rlist[0]/256)%256;
				vir_mem[buf]=Rlist[0]/(256*256);
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x78){//STB
			if(n==1&&i==1){//simple addressing
				int buf;
				buf=Rlist[3];
				vir_mem[target+2]=buf%256;
				buf=buf/256;
				vir_mem[target+1]=buf%256;
				buf=buf/256;
				vir_mem[target]=buf;
			}
			else if(n==1){//indirect
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				vir_mem[buf+2]=Rlist[3]%256;
				vir_mem[buf+1]=(Rlist[3]/256)%256;
				vir_mem[buf]=Rlist[3]/(256*256);
			}
		}

		else if((vir_mem[execindex]&0xFC)==0x74){//LDT
			if(n==1&&i==1){
				Rlist[5]=vir_mem[target+2];
				Rlist[5]+=vir_mem[target+1]*256;
				Rlist[5]+=vir_mem[target]*256*256;
			}
			else if(n==1){
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				Rlist[5]=vir_mem[buf+2];
				Rlist[5]+=vir_mem[buf+1]*256;
				Rlist[5]+=vir_mem[buf]*256*256;
			}
			else if(i==1){
				Rlist[5]=target;
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x54){//STCH
			if(n==1&&i==1){
				vir_mem[target]=Rlist[0]&0x0F;
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x38){//JLT
			if(Rlist[9]>=0){
		//		if(e==1) execindex+=4;
		//		else execindex+=3;
			}
			else{
				if(n==1&&i==1){
					Rlist[8]=target;
			//		execindex=target;
				}
				//only simple
			}
		}
		else if((vir_mem[execindex]&0xFC)==0x10){//STX
			if(n==1&&i==1){
				vir_mem[target+2]=Rlist[1]%256;
				vir_mem[target+1]=(Rlist[1]/256)%256;
				vir_mem[target]=Rlist[1]/(256*256);
			}
			else if(n==1){
				int buf=0;
				buf+=vir_mem[target+2];
				buf+=vir_mem[target+1]*256;
				buf+=vir_mem[target]*256*256;
				vir_mem[buf+2]=Rlist[1]%256;
				vir_mem[buf+1]=(Rlist[1]/256)%256;
				vir_mem[buf]=Rlist[1]/256/256;
			}

		}
		else if((vir_mem[execindex]&0xFC)==0x4C){//RSUB
			Rlist[8]=Rlist[2];
		//	execindex=Rlist[2];
		}
		else if((vir_mem[execindex]&0xFC)==0x50){//LDCH
			if(n==1&&i==1){
				Rlist[0]=vir_mem[target];
			}

		}
		else if((vir_mem[execindex]&0xFC)==0xD8){//RD
		}
		else if((vir_mem[execindex]&0xFC)==0xDC){//WD
		}
		else{
			if((vir_mem[execindex]&0xFC)==0xE0){
				Rlist[9]=1;
			}

		}
		/*if(e==1) bpk=wherebp(execindex,Rlist[8]);
		else bpk=wherebp(execindex,Rlist[8]);*/
		
		//check breakpoint
		bpk=wherebp(execindex,Rlist[8]);

		if(bpk!=-1){
			printbp();
			printf("\tStop at checkpoint[%X]\n",bplist[bpk]);
			break;
		}
		//change execindex
		if((vir_mem[execindex]&0xFC)==0x3C) execindex=Rlist[8];
		else if((vir_mem[execindex]&0xFC)==0x30) execindex=Rlist[8];
		else if((vir_mem[execindex]&0xFC)==0x34) execindex=Rlist[8];
		else if((vir_mem[execindex]&0xFC)==0x38) execindex=Rlist[8];
		else if((vir_mem[execindex]&0xFC)==0x48) execindex=Rlist[8];
		else if((vir_mem[execindex]&0xFC)==0x4C) execindex=Rlist[8];
		else{
			if(e==1) execindex+=4;
			else execindex+=3;
		}
			
		if(execindex==progad+len) {
				startrun=-1;
			//	firstbp=0;
				Rlist[8]=progad;
				printbp();
				printf("\tEnd Program\n");
				break;
		}
	}
	//printf("%X\n\n",vir_mem[102]);
	//print
	return 0;


}
/**************************************************************/
//make estab
//char cs : csect name
//char sym : external symbol
//int add : location counter for external symbol
//int length : csect length
/**************************************************************/
void mkest(char cs[10],char sym[10],int add,int length){
	estab *ptr=tb;
	estab *new=(estab*)malloc(sizeof(estab));
	
	strcpy(new->csect,cs);
	if(sym==NULL) new->symname[0]='\0';
	else strcpy(new->symname,sym);
	new->add=add;
	new->length=length;
	new->link=NULL;

	if(tb==NULL) tb=new;
	else if(tb->link==NULL) tb->link=new;
	else{
		while(ptr->link!=NULL){
			ptr=ptr->link;
		}
		ptr->link=new;
	}
}
/******************************************************************/
//make bplist: breakpoint list
//bp : added breakpoint
/******************************************************************/
void mkbp(int bp){
	int i,j,tmp;
	bplist[bpnum++]=bp;
	for(i=1;i<bpnum;i++){
		tmp=bplist[i];
		for(j=i;--j>=0&&tmp<bplist[j];) bplist[j+1]=bplist[j];
		bplist[j+1]=tmp;
	}	
}
/********************************************************************/
//linking loader
//pass1 : error checking and make load map
//		: csect locctr
//pass2 : calculate real value using modification record
//file1,file2,file3 : files for linking and loading
//num : number of files
/********************************************************************/
int loader(char file1[256],char file2[256],char file3[256],int num){
	int i;
	char temp[80]={'\0',};
	char cs[10];
	char sym[10];
	char htmp[10];
	char*** refer=(char***)malloc(sizeof(char**)*num);
	int add;
	int addnext;
	int csadd;
	int len;
	int flag=0;
	FILE* in;
	estab* ptr;
	//pass1
	
	for(i=0;i<num;i++){
		refer[i]=(char**)malloc(sizeof(char*)*14);
	}
	for(i=0;i<num;i++){
		refer[i][1]=(char*)malloc(sizeof(char)*6);
	}

	for(i=0;i<num;i++){
		if(i==0) in=fopen(file1,"r");
		else if(i==1) in=fopen(file2,"r");
		else if(i==2) in=fopen(file3,"r");

		while(fgets(temp,80,in)!=NULL){
			if(temp[0]=='H'){
				estab* mtmp;
				
				strncpy(cs,temp+1,6);
				strncpy(refer[i][1],cs,6);
				if(i==0) add=progad;
				strncpy(htmp,temp+13,6);
				len=changechar2(htmp,6);
				mtmp=dup_es(cs);
				if(mtmp!=NULL){
					printf("duplicate external symbol\n");
					return -1;
				}
				mkest(cs,NULL,add,len);
				addnext=add+len;
			}
			else if(temp[0]=='R'){
				int index=1;
				temp[strlen(temp)-1]='\0';
				if(flag!=0) {
						refer[i]=realloc(refer,(12*(flag+1)+2)*sizeof(char*));
				}
				while(1){
					int refernum;
					if(temp[index]=='\0'){
						printf("object file error: refer record\n");
						return -1;
					}
					strncpy(htmp,temp+index,2);
					htmp[2]='\0';
					index+=2;
					if(temp[index]=='\0'){
						printf("object file error: refer record\n");
						return -1;
					}
					refernum=changeop(htmp);
					refer[i][refernum]=(char*)malloc(sizeof(char)*6);
					strncpy(refer[i][refernum],temp+index,6);
					if(strlen(temp+index)<6){
						int k;
						for(k=strlen(temp+index);k<6;k++){
							refer[i][refernum][k]=' ';
						}
						refer[i][refernum][6]='\0';
					}
					index+=6;
					if(index>=strlen(temp)-1) break;
				}
				flag=1;
			}
			else if(temp[0]=='D'){
				int index=1;
				estab* mtmp;
				while(1){
					if(temp[index]=='\0'){
						printf("object file error: define record\n");
						return -1;
					}
					strncpy(sym,temp+index,6);
					index+=6;
					mtmp=dup_es(sym);
					if(mtmp!=NULL){
						printf("duplicate external symbol\n");
						return -1;
					}
					if(temp[index]=='\0'){
						printf("object file error: define record\n");
						return -1;
					}
					strncpy(htmp,temp+index,6);
					mkest(cs,sym,add+changechar2(htmp,6),len);
					index+=6;
					if(index==strlen(temp)-1) break;
				}
			}
			else if(temp[0]=='T'){
				int textlen;
				strncpy(htmp,temp+7,2);
				textlen=changechar2(htmp,2);
				if(strlen(temp)!=textlen*2+10){
					printf("object file error: text record\n");
					return -1;
				}
			}
			else if(temp[0]=='E'){
				if(strlen(temp)!=1){
					execaddr=add+changechar2(temp+1,6);
				}
				add=addnext;
				flag=0;
			}
			else if(temp[0]=='.'||temp[0]=='M') continue;
			else{
				printf("object file error: we don't need such record\n");
				return -1;
			}
		}

		fclose(in);
	}

	//pass2

	flag=0;

	for(i=0;i<num;i++){
		if(i==0) in=fopen(file1,"r");
		else if(i==1) in=fopen(file2,"r");
		else if(i==2) in=fopen(file3,"r");

		while(fgets(temp,80,in)!=NULL){
			if(temp[0]=='H'){
				strncpy(cs,temp+1,6);
				if(i==0) add=progad;
				strncpy(htmp,temp+7,6);
				csadd=changechar2(htmp,6);
				strncpy(htmp,temp+13,6);
				len=changechar2(htmp,6);
				addnext=add+len;
			}	
			else if(temp[0]=='T'){
				int textlen;
				int k;
				int putad;
				strncpy(htmp,temp+1,6);
				if(i==0) putad=progad+changechar2(htmp,6)-csadd;
				else putad=add+changechar2(htmp,6)-csadd;
				strncpy(htmp,temp+7,2);
				textlen=changechar2(htmp,2);
				textlen*=2;
				for(k=9;k<textlen+9;k+=2){
					strncpy(htmp,temp+k,2);
					vir_mem[putad++]=(unsigned int)changechar2(htmp,2);
				}
			}
			else if(temp[0]=='M'){
				int modiloc;
		//		int modilen;
				int k;
				estab* mtmp;
				
				strncpy(htmp,temp+1,6);
				if(i==0) modiloc=progad+changechar2(htmp,6)-csadd;
				else modiloc=add+changechar2(htmp,6)-csadd;
				//strncpy(htmp,temp+7,2);
				//modilen=changechar2(htmp,2);
				temp[strlen(temp)-1]='\0';
				mtmp=find_es(temp+10,refer,i);
				if(mtmp==NULL){
						printf("object file error: there is no such external definition\n");
						return -1;
				}
				else{
					unsigned int modihex=0;
					int h=1;
				//	printf("%X\n",modiloc);
					for(k=modiloc+2;k>=modiloc;k--,h*=256){
						modihex+=vir_mem[k]*h;
					}
					if(temp[9]=='+') modihex+=mtmp->add;
					if(temp[9]=='-') modihex-=mtmp->add;
					for(k=modiloc+2;k>=modiloc;k--){
						vir_mem[k]=modihex%256;
						modihex=modihex/256;
					}
				//	printf("modi : %X\n",modihex);
				}
			}
			else if(temp[0]=='E'){
				add=addnext;
			}
			else continue;//'.'
		}
		fclose(in);
	}
	//jump to location given by execaddr

	//load map
	printf("\t\tcontrol\t\tsymbol\t\taddress\t\tlength\n");
	printf("\t\tsection\t\tname\n");
	printf("\t\t----------------------------------------------------------------------------\n");
	flag=0;
	ptr=tb;
	while(ptr!=NULL){
		if(flag==0) {
				strcpy(htmp,ptr->csect);
		}
		if(strcmp(htmp,ptr->csect)==0) {
				if(ptr==tb) printf("\t\t%s\t\t",ptr->csect);
				else printf("\t\t      \t\t");
		}
		else {
				printf("\t\t%s\t\t",ptr->csect);
				flag=0;
		}
		if(ptr->symname[0]=='\0') printf("      \t\t");
		else printf("%s\t\t",ptr->symname);
		printf("%04X\t\t",ptr->add);
		if(flag==0){
			printf("%04X\n",ptr->length);
			flag=1;
			strcpy(htmp,ptr->csect);
		}
		else printf("\n");
		ptr=ptr->link;
	}
	printf("\t\t----------------------------------------------------------------------------\n");
	printf("\t\t      \t\t      \t\ttotal length      %04X\n",add-progad);
	proglen=add-progad;
	return 0;
}
/*****************************************************/
//find external symbol
//refer : reference symbol table
//num : from which file
/*****************************************************/
estab* find_es(char *symbol,char ***refer,int num){
	int index;
	char symbol2[10];
	estab* ptr=tb;

	index=changeop(symbol);

	strcpy(symbol2,refer[num][index]);
	
	while(ptr!=NULL){
		if(strcmp(ptr->symname,symbol2)==0){
			return ptr;
		}
		else if(strcmp(ptr->csect,symbol2)==0) return ptr;
		ptr=ptr->link;
	}
	return NULL;
}
estab* dup_es(char *sym){
	estab* ptr=tb;
	while(ptr!=NULL){
		if(strcmp(ptr->symname,sym)==0) return ptr;
		else if(strcmp(ptr->csect,sym)==0) return ptr;
		ptr=ptr->link;
	}
	return NULL;
}
//***********************************************************************//
//print content of file(filename)
//***********************************************************************//
int Shell_type(char filename[256]){
		FILE *in;
		char buf[256];

		in=fopen(filename,"r");
		if(in==NULL){
				return -1;
		}
		while(fgets(buf,256,in)!=NULL){
				printf("%s",buf);
		}
		return 0;
}
//************************************************************************//
//filename : what i will assemble
//2 pass in here
//if error is found during pass1, print error message with line number
//if error is found during pass1, do not make obj file and lst file
//if error is found during pass2(operand symbol is not exist),
//		remove obj file and lst file
//in : file pointer to read file
//out3 : file pointer to write intermediate file
//out1 : file pointer to write lst file
//out2 : file pointer to write obj file
//just : file pointer to write just file
//		 just file : used when write obj file
//filename_lst : lst filename , filename_obj : obj filename
//label : receive label or '.'
//opcode : receive opcode
//operand : receive operand
//buf : buffer to receive one line
//buf1 : copy of buf
//ptr : receive array after ','
//num : return value if sscanf
//errorflag : information if there are errors
//linenum : line number
//startloc : start location counter
//programlen : program length
//dup_start,checkstart : information if it is start section
//pcctr : pc counter
//base : base counter
//locctr : location counter
//temp : return value of find_op
//tmp : return value of find_sym
//************************************************************************//
int assemble(char filename[256]){
		FILE *in;
		FILE *out3;
		FILE *out1;
		FILE *out2;
		FILE *just;
		char filename_lst[256],filename_obj[256];
		char label[35];
		char opcode[35];
		char operand[35];
		char buf[140];
		char buf1[140];
		char buf2[140];
		char *ptr;
		int num;
		int errorflag=0;
		int linenum=0;
		int startloc=0;
		int programlen=0;
		int dup_start=0;
		int checkstart=0;
		int pcctr,base=0;
		unsigned int locctr=0;
		table *temp;
		sym *tmp;

		strncpy(filename_lst,filename,strlen(filename)-4);
		filename_lst[strlen(filename)-4]='\0';
		strcpy(filename_obj,filename_lst);
		strcat(filename_lst,".lst");
		strcat(filename_obj,".obj");

		in=fopen(filename,"r");
		out3=fopen("intermediate_file","w+");

		//pass1

		while(fgets(buf,35*4,in)!=NULL){

				strcpy(buf1,buf);
				linenum+=5;

				sscanf(buf,"%s",label);
				if(label[0]=='\n') {
						fprintf(out3,"%s",buf);
						continue;
				}

				ptr=strtok(buf1,",");
				if(buf[0]!=' '&&buf[0]!='\t'&&buf[0]!='\r'){
						num=sscanf(ptr,"%s %s %s",label,opcode,operand);
						if(num==2) operand[0]='\0';
				}
				else{
						num=sscanf(ptr,"%s %s",opcode,operand);
						if(num==1) operand[0]='\0';
				}
				if(strchr(buf,',')!=NULL){
						strcpy(ptr,strchr(buf,',')+1);
				}
				else ptr[0]='\0';//tokenize
				if(strcmp(opcode,"START")==0){
						int i,h=1;
						int result=0,temp;
						dup_start++;
						if(dup_start>1){
								printf("line %d : Syntax Error : duplicate start\n",linenum);
								errorflag=1;
						}
						if(linenum!=5){
								printf("line %d : Syntax Error : start must not be here\n",linenum);
								errorflag=1;
						}

						for(i=strlen(operand)-1;i>=0;i--){
								if(operand[i]>='0'&&operand[i]<='9') temp=operand[i]-'0';
								else if(operand[i]>='A'&&operand[i]<='F') temp=operand[i]-'A'+10;
								else if(operand[i]>='a'&&operand[i]<='f') temp=operand[i]-'a'+10;
								else {
										errorflag=1;
										break;

								}
								result+=temp*h;
								h*=16;
						}
						if(errorflag==1){
								errorflag=1;
								printf("line %d : Syntax Error : operand is wrong\n",linenum);
						}
						else{
								locctr=result;
								startloc=result;
								fprintf(out3,"%X\t%s",locctr,buf);
								make_symht(locctr,label);
						}
				}//start
				else{
						if(linenum==5) locctr=0;		

						if(strcmp(opcode,"END")==0) break;

						if(label[0]!='.'){
								if(buf[0]!=' '&&buf[0]!='\t'&&buf[0]!='\r'){//if there is label
										if(find_sym(label)!=NULL){
												errorflag=1;
												printf("line %d : Syntax Error : duplicate symbol\n",linenum);
										}
										else {
												int operror=0;
												if(label[0]<'A'||label[0]>'Z') operror=1;
												else{
														int k;
														for(k=0;k<strlen(label);k++){
																if(!((label[k]>='A'&&label[k]<='Z')||(label[k]>='0'&&label[k]<='9'))) operror=1;
														}
												}
												if(operror==1) {
														errorflag=1;
														printf("line %d : Syntax Error : invalid symbol\n",linenum);
												}
												else make_symht(locctr,label);
										}
								}
								if(strcmp(opcode,"ADDR")==0||strcmp(opcode,"COMPR")==0||strcmp(opcode,"DIVR")==0||strcmp(opcode,"MULR")==0||strcmp(opcode,"RMO")==0||strcmp(opcode,"SHIFTR")==0||strcmp(opcode,"SHIFTL")==0||strcmp(opcode,"SUBR")==0){//if operand is two
										char a[5]={'\0',};
										sscanf(ptr,"%s",a);
										if(operand[0]=='\0'||a[0]=='\0'){
												errorflag=1;
												printf("line %d : Syntax Error : there are few operands\n",linenum);
										}
										else if(find_regi(operand)==-1) {
												errorflag=1;
												printf("line %d : Syntax Error : there is no such register\n",linenum);
										}
										else if(find_regi(a)==-1){
												if(strcmp(opcode,"SHIFTL")==0||strcmp(opcode,"SHIFTR")==0){//SHIFTL r1,n || SHIFTR r1,n
														int k;
														int er=0;
														for(k=0;k<strlen(a);k++){
																if(a[k]<'0'||a[k]>'9') er=1;
														}
														if(er==1) {
																errorflag=1;
																printf("line %d : Syntax Error : operand is wrong\n",linenum);
														}
												}
												else {
														errorflag=1;
														printf("line %d : Syntax Error : there is no such register\n",linenum);
												}
										}
								}
								else if(strcmp(opcode,"CLEAR")==0||strcmp(opcode,"TIXR")==0){//one operand of register
										char a[5]={'\0',};
										sscanf(ptr,"%s",a);
										if(a[0]!='\0'){
											errorflag=1;
											printf("line %d : Syntax Error : there are so many operands\n",linenum);
										}
										if(operand[0]=='\0'){
											errorflag=1;
											printf("line %d : Syntax Error : there are few operands\n",linenum);
										}
										else if(find_regi(operand)==-1){
												errorflag=1;
												printf("line %d : Syntax Error : there is no such register\n",linenum);
										}
								}
								else if(strcmp(opcode,"FIX")==0||strcmp(opcode,"FLOAT")==0||strcmp(opcode,"HIO")==0||strcmp(opcode,"NORM")==0||strcmp(opcode,"SIO")==0||strcmp(opcode,"TIO")==0){//format 1
									if(operand[0]!='\0'){
										errorflag=1;
										printf("line %d : Syntax Error : there is so many operands\n",linenum);
									}
								}
								else if(strcmp(opcode,"SVC")==0){//SVC n
									int k;
									if(operand[0]=='\0'){
										errorflag=1;
										printf("line %d : Syntax Error : there is few operands\n",linenum);
									}
									else{
										for(k=0;k<strlen(operand);k++){
											if(operand[k]<'0'||operand[k]>'9') break;
										}
										if(k!=strlen(operand)){
											errorflag=1;
											printf("line %d : Syntax Error : invalid operand\n",linenum);
										}
									}
								}
								if(opcode[0]=='+'&&find_op(opcode+1)!=NULL){//format 4
										locctr+=4;
								}
								else if(find_op(opcode)!=NULL){//format 1,2,3
										temp=find_op(opcode);
										locctr+=(temp->format[0])-'0';
								}
								else if(strcmp(opcode,"BASE")==0) {
										fprintf(out3,"%X\t%s",locctr,buf);
										continue;
								}
								else if(strcmp(opcode,"WORD")==0) {
										if(!((operand[0]>='0'&&operand[0]<='9')||(operand[0]>='A'&&operand[0]<='F'))){
											errorflag=1;
											printf("line %d : Syntax Error : invalid operand\n",linenum);
										}
										locctr+=3;
								}
								else if(strcmp(opcode,"RESW")==0){
										int opre;
										opre=changeop(operand);
										if(opre!=-1) locctr+=3*opre;
								}
								else if(strcmp(opcode,"RESB")==0){
										int opre;
										opre=changeop(operand);
										if(opre==-1){
												errorflag=1;
												printf("line %d : Syntax Error : invalid operand\n",linenum);
										} 
										else locctr+=opre;
								}
								else if(strcmp(opcode,"BYTE")==0){
										//question!!!!!!!!!!!!!!!!!!!!!!
										if(operand[0]=='C'){
												locctr+=(strlen(operand+2)-1);
										}
										else if(operand[0]=='X'){
												int k;
												for(k=2;k<strlen(operand+2)-1;k++){
													if(!((operand[k]>='0'&&operand[k]<='9')||(operand[k]>='A'&&operand[k]<='F')))
													{
														errorflag=1;
														printf("line %d : Syntax Error : invalid value\n",linenum);
													}
												}
												locctr+=strlen(operand+2)/2;
										}
										else{
											errorflag=1;
											printf("line %d : Syntax Error : invalid operand\n",linenum);
										}
								}
								else{//there are no such opcode
										errorflag=1;
										printf("line %d : Syntax Error : invalid operation code\n",linenum);
								}

						}
						fprintf(out3,"%X\t%s",locctr,buf);			
				}
				programlen=locctr-startloc;

		}
		fprintf(out3,"%X\t%s",locctr,buf);
		fclose(in);
		fclose(out3);	

		if(errorflag==1){
				int k;
				for(k=0;k<20;k++){
						symtb[k]=NULL;
				}
				return -1;
		}//if error is found, finish function

		//pass2

		linenum=0;
		locctr=startloc;
		in=fopen(filename,"r");
		out1=fopen(filename_lst,"w+");
		out2=fopen(filename_obj,"w+");
		out3=fopen("intermediate_file","r");

		while(fgets(buf,150,in)!=NULL){

				strcpy(buf1,buf);
				fgets(buf2,150,out3);
				sscanf(buf2,"%x",&pcctr);

				linenum+=5;

				sscanf(buf,"%s",label);
				if(label[0]=='\n'){
						fprintf(out1,"%-100s",buf);
						continue;
				}

				ptr=strtok(buf1,",");
				if(buf[0]!=' '&&buf[0]!='\t'&&buf[0]!='\r'){
						num=sscanf(ptr,"%s %s %s",label,opcode,operand);
						if(num==2) operand[0]='\0';
				}
				else{
						num=sscanf(ptr,"%s %s",opcode,operand);
						if(num==1) operand[0]='\0';
				}
				if(strchr(buf,',')!=NULL){
						strcpy(ptr,strchr(buf,',')+1);
				}
				else ptr[0]='\0';//tokenize
				if(strcmp(opcode,"BASE")==0){
						sym *t;
						t=find_sym(operand);
						base=t->loc;
				}//store base location counter
				if(strcmp(opcode,"START")==0){
						int a;
						int k=6-strlen(label);
						fprintf(out2,"H");
						for(k=k-1;k>-1;k--){
							fprintf(out2," ");
						}
						fprintf(out2,"%s%06X%06X\n",label,startloc,programlen);
						fprintf(out1,"%6d\t%04X\t",linenum,locctr);
						a=strlen(buf)-1;
						buf[a]='\0';
						fprintf(out1,"%-100s\t\n",buf);
						checkstart=1;
				}
				else{
						int a;
						a=strlen(buf)-1;
						buf[a]='\0';

						if(linenum==5) 
						{
								locctr=0;
								fprintf(out2,"H      %06X%06X\n",startloc,programlen);
								checkstart=1;
						}
						if(checkstart==1){
						//	fprintf(out2,"T%06X",locctr);
							checkstart=0;
							just=fopen("just","w+");
						}

						if(strcmp(opcode,"END")==0) break;
						fprintf(out1,"%6d\t",linenum);
						if(label[0]!='.'){
								unsigned int dis;
								int xbpe=0;

								if(opcode[0]=='+'){//format 4
										temp=find_op(opcode+1);
										if(operand[0]=='#'){//immediate addressing mode
											tmp=find_sym(operand+1);
											fprintf(out1,"%04X\t%-100s\t%02X",locctr,buf,temp->opcode+1);
											fprintf(just,"%06X\t%02X",locctr,temp->opcode+1);
											
										}
										else if(operand[0]=='@'){//indirect addressing mode
											tmp=find_sym(operand+1);
											fprintf(out1,"%04X\t%-100s\t%02X",locctr,buf,temp->opcode+2);
											fprintf(just,"%06X\t%02X",locctr,temp->opcode+2);
										}
										else{//symbol addressing mode
											tmp=find_sym(operand);
											fprintf(out1,"%04X\t%-100s\t%02X",locctr,buf,temp->opcode+3);
											fprintf(just,"%06X\t%02X",locctr,temp->opcode+3);
										}
										if(ptr[0]!='\0') xbpe+=9;
										else xbpe+=1;
										fprintf(out1,"%X",xbpe);
										fprintf(just,"%X",xbpe);
										if(tmp==NULL){
											if(operand[0]=='@'||operand[0]=='#'){
												if(operand[1]<'0'||operand[1]>'9'){//if operand(symbol) is not valid, finish function(remove lst,obj file)
													int fr=0;
													printf("line %d : Syntax Error : invalid symbol\n",linenum);
													fclose(in);
													fclose(out1);
													fclose(out2);
													fclose(out3);
													remove(filename_lst);
													remove(filename_obj);
													for(fr=0;fr<20;fr++){
														free(symtb[fr]);
														symtb[fr]=NULL;
													}
													symtb_size=0;
													return -1;
												}
												else{
													int result=0;
													result=changeop(operand+1);
													fprintf(out1,"%05X",result);
													fprintf(just,"%05X",result);
												}
											}
											else{
												if(operand[0]<'0'||operand[0]>'9'){//if operand(symbol) is not valid, finish function(remove lst,obj file)
													int fr;
													printf("line %d : Syntax Error : invalid symbol\n",linenum);
													fclose(in);
													fclose(out1);
													fclose(out2);
													fclose(out3);
													remove(filename_lst);
													remove(filename_obj);
													for(fr=0;fr<20;fr++){
														free(symtb[fr]);
														symtb[fr]=NULL;
													}
													symtb_size=0;
													return -1;
												}
												else{
													int result=0;
													result=changeop(operand);
													fprintf(out1,"%05X",result);
													fprintf(just,"%05X",result);
												}
											}
										}
										else{
												fprintf(out1,"%05X",tmp->loc);
												fprintf(just,"%05X",tmp->loc);
												modi(locctr);
										}
										
								}
								else{//format 1,2,3
										temp=find_op(opcode);
										if(temp!=NULL){
												if(strcmp(opcode,"ADDR")==0||strcmp(opcode,"CLEAR")==0||strcmp(opcode,"COMPR")==0||strcmp(opcode,"DIVR")==0||strcmp(opcode,"MULR")==0||strcmp(opcode,"RMO")==0||strcmp(opcode,"SHIFTL")==0||strcmp(opcode,"SHIFTR")==0||strcmp(opcode,"SUBR")==0||strcmp(opcode,"TIXR")==0){//format 2
														char a[5]={'\0',},b[5]={'\0'};
														table *temp2;

														sscanf(operand,"%s",a);
														sscanf(ptr,"%s",b);
														temp2=find_op(opcode);
														fprintf(out1,"%04X\t%-100s\t%02X%d",locctr,buf,temp2->opcode,find_regi(a));
														fprintf(just,"%06X\t%02X%d",locctr,temp2->opcode,find_regi(a));
														if(b[0]!='\0'){
																if(find_regi(b)==-1){
																		fprintf(out1,"%X",changeop(b));
																		fprintf(just,"%X",changeop(b));
																}
																else {
																		fprintf(out1,"%d",find_regi(b));
																		fprintf(just,"%d",find_regi(b));
																}
														}
														else{
																fprintf(out1,"0");
																fprintf(just,"0");
														}

												}
												else if(strcmp(opcode,"SVC")==0){
													char a[5]={'\0',};
													table *temp2;
													sscanf(ptr,"%s",a);
													temp2=find_op(opcode);
													fprintf(out1,"%04X\t%-100s\t%02X%X0",locctr,buf,temp2->opcode,changeop(a));
													fprintf(just,"%06X\t%02X%X0",locctr,temp2->opcode,changeop(a));
												}
												else if(strcmp(opcode,"FIX")==0||strcmp(opcode,"FLOAT")==0||strcmp(opcode,"HIO")==0||strcmp(opcode,"NORM")==0||strcmp(opcode,"SIO")==0||strcmp(opcode,"TIO")==0){//format 1
													table *temp2;
													temp2=find_op(opcode);
													fprintf(out1,"%04X\t%-100s\t%02X",locctr,buf,temp2->opcode);
													fprintf(just,"%06X\t%02X",locctr,temp2->opcode);
												}
												else{//format 3
														int a=0;
														if(operand[0]=='#'){
																tmp=find_sym(operand+1);
																if(tmp==NULL){
																		if(changeop(operand+1)==-1){//if operand(symbol) is not valid, finish function(remove lst, obj file)
																				int fr;
																				printf("line %d : Syntax Error : invalid symbol\n",linenum);
																				fclose(in);
																				fclose(out1);
																				fclose(out2);
																				fclose(out3);
																				remove(filename_lst);
																				remove(filename_obj);
																				for(fr=0;fr<20;fr++){
																					free(symtb[fr]);
																					symtb[fr]=NULL;
																				}
																				symtb_size=0;
																				return -1;

																		}
																}
																fprintf(out1,"%04X\t%-100s\t%02X",locctr,buf,temp->opcode+1);
																fprintf(just,"%06X\t%02X",locctr,temp->opcode+1);

														}
														else if(operand[0]=='@'){
																tmp=find_sym(operand+1);
																if(tmp==NULL){
																		if(changeop(operand+1)==-1){//if operand(symbol) is not valid, finish function(move lst, obj file)
																			int fr;
																			printf("line %d : Syntax Error : invalid symbol\n",linenum);
																			fclose(in);
																			fclose(out1);
																			fclose(out2);
																			fclose(out3);
																			remove(filename_lst);
																			remove(filename_obj);
																			for(fr=0;fr<20;fr++){
																				free(symtb[fr]);
																				symtb[fr]=NULL;
																			}
																			symtb_size=0;
																			return -1;

																		}
																}
																fprintf(out1,"%04X\t%-100s\t%02X",locctr,buf,temp->opcode+2);
																fprintf(just,"%06X\t%02X",locctr,temp->opcode+2);
														}
														else{
																tmp=find_sym(operand);
																if(tmp==NULL){
																		if(changeop(operand)==-1){//if operand(symbol) is not valid, finish function(move lst, obj file)
																			int fr;
																			printf("line %d : Syntax Error : invalid symbol\n",linenum);
																			fclose(in);
																			fclose(out1);
																			fclose(out2);
																			fclose(out3);
																			remove(filename_lst);
																			remove(filename_obj);
																			for(fr=0;fr<20;fr++){
																				free(symtb[fr]);
																				symtb[fr]=NULL;
																			}
																			symtb_size=0;
																			return -1;

																		}
																}
																fprintf(out1,"%04X\t%-100s\t%02X",locctr,buf,temp->opcode+3);
																fprintf(just,"%06X\t%02X",locctr,temp->opcode+3);
														}
														if(ptr[0]!='\0') xbpe+=8;
														if(tmp==NULL){//operand is number
															if(operand[0]=='@'||operand[0]=='#'){
																dis=changeop(operand+1);
															}
															else{
																dis=changeop(operand);
															}
														}
														else if(tmp->loc-pcctr>=-2048&&tmp->loc-pcctr<=2047){//pc relative
																xbpe+=2;
																dis=(unsigned int)(tmp->loc-pcctr);
																dis=dis&4095;
																a++;
														}
														else if(tmp->loc-base>=0&&tmp->loc-base<=4095){//base relative
																xbpe+=4;
																dis=(unsigned int)(tmp->loc-base);
																dis=dis&4095;
																a++;
														}
														else{
																dis=tmp->loc;
																if(a==0) errorflag=1;
														}
														fprintf(out1,"%X",xbpe);
														fprintf(just,"%X",xbpe);
														
														fprintf(out1,"%03X",dis);
														fprintf(just,"%03X",dis);
														
												}
										}
										else if(strcmp(opcode,"BYTE")==0){
												char *ch=strchr(buf,39);
												fprintf(out1,"%04X\t%-100s\t",locctr,buf);
												fprintf(just,"%06X\t",locctr);
												if(operand[0]=='X'){
														int k;
														for(k=2;k<strlen(operand)-1;k++){
																fprintf(out1,"%c",operand[k]);
																fprintf(just,"%c",operand[k]);
														}
												}
												else if(operand[0]=='C'){
														int k;

														for(k=0;k<strlen(ch+1)-1;k++){
																fprintf(out1,"%02X",(int)(*(ch+1+k)));
																fprintf(just,"%02X",(int)(*(ch+1+k)));
														}
												}
										}
										else if(strcmp(opcode,"WORD")==0){
											int result=0;
											
											fprintf(out1,"%04X\t%-100s\t",locctr,buf);
											fprintf(just,"%06X\t",locctr);
											result=changeop(operand);
											fprintf(out1,"%06X",result);
											fprintf(just,"%06X",result);
										}
										else if(strcmp(opcode,"RESW")==0||strcmp(opcode,"RESB")==0){
												fprintf(out1,"%04X\t%-100s",locctr,buf);
												fprintf(just,"%06X\tno",locctr);
										}
										else if(strcmp(opcode,"BASE")==0){
												fprintf(out1,"    \t%s\t",buf);
										}
								}
								fprintf(out1,"\n");
								fprintf(just,"\n");
								locctr=pcctr;
								xbpe=0;
						}
						else fprintf(out1,"    \t%-100s\n",buf);
				}

		}
		fprintf(out1,"%6d\t      \t%-100s\n",linenum,buf);

		fclose(just);
		just=fopen("just","r");
		
		num=-1;	
		dup_start=0;

		while(1){
			char objcode[100]={'\0',};//store one line of obj file
			linenum=0;
			if(dup_start==1) dup_start=0;
			else fprintf(out2,"T");
			if(num!=-1) {
					fprintf(out2,"%s",buf1);
					strcpy(objcode,buf);
					linenum+=strlen(buf);
			}
			buf[0]='\0';
			while((num=fscanf(just,"%s %s",buf1,buf))!=-1&&linenum+strlen(buf)<=60){//not EOF, cannot over 30 bytes
				if(strcmp(buf,"no")==0) {
						while((num=fscanf(just,"%s %s",buf1,buf))!=-1&&strcmp(buf,"no")==0);
						break;
				}
				if(linenum==0) {
						fprintf(out2,"%s",buf1);
						strcpy(objcode,buf);
				}
				else strcat(objcode,buf);
				linenum+=strlen(buf);
			}
			if(linenum!=0){
				fprintf(out2,"%02X%s",(int)(linenum/2),objcode);
				fprintf(out2,"\n");
			}
			else dup_start=1;
			if(num==-1) break;
		}
		tmp=obj;
		while(tmp!=NULL){
			fprintf(out2,"M%06X05\n",tmp->loc-startloc);
			tmp=tmp->link;
		}
		fprintf(out2,"E%06X\n",startloc);
		
		

		fclose(out1);
		fclose(out2);
		fclose(out3);
		fclose(in);

		printf("\toutput file : [%s], [%s]\n",filename_lst,filename_obj);

		return 0;
}
//**************************************************************//
//operand : register
//find register number
//if there is no such register, return -1
//return register number
//**************************************************************//
int find_regi(char *operand){
		int i;
		for(i=0;i<10;i++){
				if(strcmp(operand,regi[i])==0) return i;
		}
		return -1;
}
//**************************************************************//
//operand : what i want to change to decimal
//change character array to decimal number
//if operand is not valid, return -1
//return decimal number
//**************************************************************//
int changeop(char*operand){
		int i,temp,result=0,cnt=1;
		for(i=strlen(operand)-1;i>=0;i--,cnt*=10){
				if(operand[i]<'0'||operand[i]>'9') return -1;
				temp=operand[i]-'0';
				result+=temp*cnt;
		}
		return result;
}
//***************************************************************//
//for modification record, store location counter
//locctr : where modification is needed
//***************************************************************//
void modi(int locctr){
	sym *new=(sym*)malloc(sizeof(sym));
	sym *ptr=obj;
	new->loc=locctr+1;
	new->link=NULL;
	if(obj==NULL) obj=new;
	else if(obj->link==NULL) obj->link=new;
	else{
		while(ptr->link!=NULL){
			ptr=ptr->link;
		}
		ptr->link=new;
	}
}
//***************************************************************//
//be used in quick sort of symbol table
//decide order using strcmp function
//***************************************************************//
int compare(const void*p1, const void*p2){
	return -strcmp(((sym*)p1)->s,((sym*)p2)->s);
}
//***************************************************************//
//print symbol table made in recent assemble
//line up symbol in descending order('Z'->'A')
//srt : store every symbol and location counter
//	  : use qsort function using compare function
//    : after sort and print, free array
//***************************************************************//
void print_symtb(){
	int size=0;
	int k;
	sym*ptr;
	sym*srt;

	srt=(sym*)malloc(sizeof(sym)*symtb_size);
	for(k=0;k<20;k++){
		ptr=symtb[k];
		while(ptr!=NULL){
			srt[size].loc=ptr->loc;
			strcpy(srt[size].s,ptr->s);
			ptr=ptr->link;
			size++;
		}
	}
	qsort(srt,symtb_size,sizeof(sym),compare);
	for(k=0;k<size;k++){
		printf("\t%s\t%04X\n",srt[k].s,srt[k].loc);
	}
	free(srt);
}
//****************************************************************//
//data : string which will be changed to hexadecimal number
//len : string length
//return result hexadecimal number
//if there are character which is not hexadecimal number, return -1
//if result is over boundary, return -1
//****************************************************************//
int changechar(char *data,int len){
		int i;
		int result=0;
		int h=1;
		int temp;
		for(i=0;i<len;i++){
				if(data[len-i-1]>='0'&&data[len-i-1]<='9') temp=data[len-i-1]-'0';
				else if(data[len-i-1]>='a'&&data[len-i-1]<='f') temp=data[len-i-1]-'a'+10;
				else if(data[len-i-1]>='A'&&data[len-i-1]<='F') temp=data[len-i-1]-'A'+10;
				else return -1;
				result+=temp*h;
				h*=16;
				if(result>=1048576 || h>1048576) return -1;
		}
		return result;
}
//**************************************************/
//change char data, hexadecimal into decimal
//**************************************************/
int changechar2(char *data,int len){
	int i;
	int result=0;
	int h=1;
	int temp;
	for(i=0;i<len;i++){
				if(data[len-i-1]>='0'&&data[len-i-1]<='9') temp=data[len-i-1]-'0';
				else if(data[len-i-1]>='a'&&data[len-i-1]<='f') temp=data[len-i-1]-'a'+10;
				else if(data[len-i-1]>='A'&&data[len-i-1]<='F') temp=data[len-i-1]-'A'+10;
				else return -1;
				result+=temp*h;
				h*=16;
		}
		return result;

}
//****************************************************************//
//make hash table
//data is from "opcode.txt"
//hash function : change string to number(sum all character)
//              : and mod 20(hash table size)
//****************************************************************//
void makeht(){
		FILE *in;
		unsigned int opcode;
		char monic[10];
		char format[5];
		int sum=0;
		int err=0;

		in=fopen("opcode.txt","r");
		while(1){
				table *new=(table*)malloc(sizeof(table));
				int i;

				new->link=NULL;
				err=fscanf(in,"%x %s %s",&opcode,monic,format);
				if(err==-1) break;
				new->opcode=opcode;
				strcpy(new->monic,monic);
				strcpy(new->format,format);

				for(i=0;i<strlen(monic);i++){
						sum+=(int)monic[i];
				}
				sum=sum%20;

				if(ht[sum]==NULL){
						ht[sum]=new;
				}
				else if(ht[sum]->link==NULL){
						ht[sum]->link=new;
				}
				else{
						table *ptr=ht[sum];
						while(ptr->link!=NULL){
								ptr=ptr->link;
						}
						ptr->link=new;
				}
				sum=0;
		}
		fclose(in);
}
//********************************************************************//
//make symbol table(hash table)
//when store symbol, store location counter together
//locctr : location counter
//lable : symbol to be stored
//********************************************************************//
void make_symht(int locctr,char label[35]){
		int i;
		int temp=0;
		sym *newtb=(sym*)malloc(sizeof(sym));
		newtb->loc=locctr;
		newtb->link=NULL;
		strcpy(newtb->s,label);

		for(i=0;i<strlen(label);i++){
				temp+=(int)label[i];
		}
		if(symtb[temp%20]==NULL){
				symtb[temp%20]=newtb;
		}
		else if(symtb[temp%20]->link==NULL){
				symtb[temp%20]->link=newtb;
		}
		else{
				sym *ptr=symtb[temp%20];
				while(ptr->link!=NULL){
						ptr=ptr->link;
				}
				ptr->link=newtb;
		}

		symtb_size++;
}
//******************************************************************//
//find symbol in symtab
//if found, return that struct
//if not, return NULL
//label : what i want to find
//******************************************************************//
sym* find_sym(char label[35]){
		int temp=0;
		int i;
		sym *ptr;

		for(i=0;i<strlen(label);i++){
				temp+=(int)label[i];
		}
		ptr=symtb[temp%20];
		while(ptr!=NULL){
				if(strcmp(ptr->s,label)==0) return ptr;
				ptr=ptr->link;
		}
		return NULL;
}
//********************************************************************//
//find opcode in hash table of opcode(optable)
//if found, return that struct
//if not, return NULL
//opcode : what i want to find
//********************************************************************//
table* find_op(char opcode[35]){
		int i;
		int temp=0;
		table *ptr;

		for(i=0;i<strlen(opcode);i++){
				temp+=(int)opcode[i];
		}
		ptr=ht[temp%20];
		while(ptr!=NULL){
				if(strcmp(ptr->monic,opcode)==0) {
						return ptr;
				}
				ptr=ptr->link;
		}
		return NULL;
}
//*******************************************************************//
//print all command
//*******************************************************************//
void Shell_help(){
		printf("h[elp]\n");
		printf("d[ir]\n");
		printf("q[uit]\n");
		printf("hi[story]\n");
		printf("du[mp] [start, end]\n");
		printf("e[dit] address, value\n");
		printf("f[ill] start, end, value\n");
		printf("reset\n");
		printf("opcode mnemonic\n");
		printf("opcodelist\n");
		printf("assemble filename\n");
		printf("type filename\n");
		printf("symbol\n");
		printf("progaddr [address]\n");
		printf("loader [object filename1] [object filename2] [...]\n");
		printf("run\n");
		printf("bp [address]\n");
		printf("bp clear\n");
		printf("bp\n");
}
//********************************************************************//
//print all file in this directory
//not print '.' and '..'
//print 3 in one sentence
//********************************************************************//
void Shell_dir(){
		DIR *direx;
		struct dirent *dip;
		struct stat buf;
		int cnt=0;

		direx=opendir(".");

		while((dip=readdir(direx))!=NULL){
				stat(dip->d_name,&buf);
				if(strcmp(dip->d_name,".")==0||strcmp(dip->d_name,"..")==0) continue;
				printf("\t\t");
				printf("%s",dip->d_name);
				if(S_ISDIR(buf.st_mode)) printf("/");
				else if(buf.st_mode&S_IXUSR) printf("*");
				cnt++;
				if(cnt%3==0) printf("\n");
		}
		if(cnt%3!=0) printf("\n");
}
//********************************************************************//
//print history of command
//the recent command should be final
//make history in linked list
//********************************************************************//
void Shell_history(){
		int count=0;
		node *ptr=head;

		if(head==NULL) return;
		while(ptr!=NULL){
				printf("%d\t%s",++count,ptr->cmd);
				ptr=ptr->link;
		}

}
//*********************************************************************//
//flag: classify command(dump/dump start/dump start,end)
//dump	: print 10 lines , 160 bytes
//		: if boundary over, print by FFFFF
//		: it can be 11 lines
//		: store the last printed address
//		: if the stored address is the final address of memory,
//		:  print from first address
//dump start	: print 10 lines from start
//				: it can be 10 lines(160bytes)
//				: it also store the last printed address
//				: if boundary over, print by the last address
//dump start,end	: print from start to end
//					: if boundary over, error
//					: it also store the last printed address
//*********************************************************************//
void Shell_dump(int start,int end,int flag){
		int i=dump_cnt+1,j;
		int cnt=0;
		int temp;
		int k,st;
		if(i==1048576){
				i=0;
				dump_cnt=-1;
		}
		if(flag==0){//dump
				int printfin;
				int bf=0;
				temp=(i/16)*16;
				while(1){
						printf("%05X",i/16*16);//address
						for(j=0;j<16;j++,i++){//contents(hexadecimal)
								if(i/16*16+j<dump_cnt+1){ 
										printf("    ");
										i--;
								}
								else {
										printf("  %02X",vir_mem[i]);
										cnt++;
								}
								if(i==1048575){//if final address
										st=i;
										for(k=st+1,i++;k<=(st)/16*16+15;k++,i++){
												printf("    ");
										}
										break;
								}
								if(cnt==160){
										int k;
										printfin=i;
										for(k=printfin+1,i++;k<=printfin/16*16+15;k++,i++){
												printf("    ");
										}
										break;
								} 
						}
						printf(" ; ");
						if((i-1)/16*16==temp) i=dump_cnt+1;
						else i-=16;
						for(j=0;j<16;j++,i++){//contents by char
								if(i/16*16+j<dump_cnt+1) {
										printf(".");
										i--;
								}
								else {
										if(vir_mem[i]>=32&&vir_mem[i]<=126){
												printf("%c",vir_mem[i]);
										}
										else{
												printf(".");
										}
								}
								if(i==st){//if final address
										for(k=st,i++;k<=(st)/16*16+15;k++,i++){
												printf(".");
										}
										bf=1;
										dump_cnt=st;
										break;
								}
								if(i==printfin) {
										int k;
										for(k=printfin+1,i++;k<=printfin/16*16+15;k++,i++){
												printf(".");
										}
										bf=1;
										dump_cnt=printfin;
										break;
								}
						}
						printf("\n");
						if(bf==1) break;
				}
		}
		else if(flag==1){//dump start
				int bf=0;
				int printfin;
				i=start;
				temp=(i/16)*16;
				while(1){
						printf("%05X",i/16*16);//print address
						for(j=0;j<16;j++,i++){//print contents(hexadecimal)
								if(i/16*16+j<start){
										printf("    ");
										i--;
								}
								else {
										printf("  %02X",vir_mem[i]);
										cnt++;
								}
								if(i==1048575){//if final address
										st=i;
										for(k=st+1,i++;k<=(st)/16*16+15;k++,i++){
												printf("    ");
										}
										break;
								}
								if(cnt==160){
										int k;
										printfin=i;
										for(k=printfin+1,i++;k<=printfin/16*16+15;k++,i++){
												printf("    ");
										}
										break;

								}
						}
						printf(" ; ");
						if((i-1)/16*16==temp) i=start;
						else i-=16;
						for(j=0;j<16;j++,i++){//print contents by char
								if(i/16*16+j<start){
										printf(".");
										i--;
								}
								else{
										if(vir_mem[i]>=32&&vir_mem[i]<=126){
												printf("%c",vir_mem[i]);
										}
										else{
												printf(".");
										}
								}
								if(i==st){//if final address
										for(k=st,i++;k<=(st)/16*16+15;k++,i++){
												printf(".");
										}
										bf=1;
										dump_cnt=st;
										break;
								}
								if(i==printfin){
										int k;
										for(k=printfin+1,i++;k<=printfin/16*16+15;k++,i++){
												printf(".");											
										}
										bf=1;
										dump_cnt=printfin;
										break;

								}
						}
						printf("\n");
						if(bf==1) break;
				}

		}
		else if(flag==2){//dump start,end
				int bf=0;
				int k;
				i=start;
				temp=(i/16)*16;
				while(1){
						printf("%05X",i/16*16);//print address
						for(j=0;j<16;j++,i++){//print contents(hexadecimal)
								if((i/16)*16+j<start){
										printf("    ");
										i--;
								}
								else printf("  %02X",vir_mem[i]);
								if(i==end) {
										for(k=end+1,i++;k<=end/16*16+15;k++,i++){
												printf("    ");
										}
										break;
								}
						}
						printf(" ; ");
						if((i-1)/16*16==temp) i=start;
						else i-=16;
						for(j=0;j<16;j++,i++){//print contents(char)
								if(i/16*16+j<start) {
										printf(".");
										i--;
								}
								else {
										if(vir_mem[i]>=32&&vir_mem[i]<=126){
												printf("%c",vir_mem[i]);
										}
										else{
												printf(".");
										}
								}
								if(i==end) {
										for(k=end+1,i++;k<=end/16*16+15;k++,i++){
												printf(".");
										}
										bf=1;
										break;
								}
						}
						printf("\n");
						if(bf==1) break;
				}
				dump_cnt=end;
		}
}
//*******************************************************************//
//address : given address
//value : what you want to put
//put value at given address
//*******************************************************************//
void Shell_edit(int address,int value){//edit
		*(vir_mem+address)=value;
}
//*******************************************************************//
//start,end : field you want change
//value : what you want to put
//*******************************************************************//
void Shell_fill(int start,int end,int value){
		int i;
		for(i=start;i<=end;i++){
				*(vir_mem+i)=value;
		}
}
//*******************************************************************//
//reset(to 0) values
//*******************************************************************//
void Shell_reset(){
		int i;
		for(i=0;i<1048576;i++){
				vir_mem[i]=0;
		}
}
//*******************************************************************//
//monic[5] = the mnemonic string which you want to find
//find mnemonic from hash table and print opcode
//*******************************************************************//
int opcode_mnemonic(char monic[5]){
		int sum=0;
		int k;
		table *ptr;

		for(k=0;k<strlen(monic);k++){
				sum+=(int)monic[k];
		}
		sum=sum%20;
		ptr=ht[sum];

		while(ptr!=NULL){
				if(strcmp(monic,ptr->monic)==0){
						printf("opcode is %X\n",ptr->opcode);
						return 0;
				}
				ptr=ptr->link;
		}
		if(ptr==NULL) return -1;
		return 1;
}
//******************************************************************//
//print hashtable
//******************************************************************//
void opcodelist_print(){
		int k;
		for(k=0;k<20;k++){
				table *ptr;
				ptr=ht[k];

				printf("%d :",k);
				while(ptr!=NULL){
						printf(" [%s,%X]",ptr->monic,ptr->opcode);
						ptr=ptr->link;
						if(ptr!=NULL) printf(" ->");
				}
				printf("\n");
		}
}
//******************************************************************//
//cmdnode[256] : what you put to list
//make history list
//FIFO
//******************************************************************//
void push(char cmdnode[256]){
		node *new=(node*)malloc(sizeof(node));
		node *ptr=head;
		strcpy(new->cmd,cmdnode);
		new->link=NULL;

		if(head==NULL){
				head=new;
		}
		else if(head->link==NULL){
				head->link=new;
		}
		else{
				while(ptr->link!=NULL){
						ptr=ptr->link;
				}
				ptr->link=new;
		}
}
