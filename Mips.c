/* Mips compiler written in c*/
/* 
Name :- Amarnath
cs15btech11040
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct reg
{
	char name[4];
	int val;
};


struct i_reg
{
	int fun,r1,r2,r3;
	char label_name[20],label_jump[20];
};

struct reg Reg[32];
struct i_reg ins_reg[2000];							// Maximum 2000 lines of code 
char buffer[30],p[30];
int stack[1000];									// Maximum of 1000 values in the stack
int p_line=0,pc=1;

void init_Reg()
{
	strcpy(Reg[0].name,"$0");
	strcpy(Reg[1].name,"$at");
	strcpy(Reg[2].name,"$v0");
	strcpy(Reg[3].name,"$v1");
	strcpy(Reg[4].name,"$a0");
	strcpy(Reg[5].name,"$a1");
	strcpy(Reg[6].name,"$a2");
	strcpy(Reg[7].name,"$a3");
	strcpy(Reg[8].name,"$t0");
	strcpy(Reg[9].name,"$t1");
	strcpy(Reg[10].name,"$t2");
	strcpy(Reg[11].name,"$t3");
	strcpy(Reg[12].name,"$t4");
	strcpy(Reg[13].name,"$t5");
	strcpy(Reg[14].name,"$t6");
	strcpy(Reg[15].name,"$t7");
	strcpy(Reg[16].name,"$s0");
	strcpy(Reg[17].name,"$s1");
	strcpy(Reg[18].name,"$s2");
	strcpy(Reg[19].name,"$s3");
	strcpy(Reg[20].name,"$s4");
	strcpy(Reg[21].name,"$s5");
	strcpy(Reg[22].name,"$s6");
	strcpy(Reg[23].name,"$s7");
	strcpy(Reg[24].name,"$t8");
	strcpy(Reg[25].name,"$t9");
	strcpy(Reg[26].name,"$k0");
	strcpy(Reg[27].name,"$k1");
	strcpy(Reg[28].name,"$gp");
	strcpy(Reg[29].name,"$sp");
	strcpy(Reg[30].name,"$fp");
	strcpy(Reg[31].name,"$ra");
	for(int i=0;i<32;i++)
	{
		Reg[i].val=0;
	}
	return;
}


void removelastcharacter(char *p) 
{    
   int s = strlen(p);
   p[s - 1] = '\0'; 
}

char lastchar(char *p)
{
	int s = strlen(p);
	char l=p[s-1];
	return l;
}

void print1()
{
	printf("\nBefore the operation \n");
	printf("%s -- %d\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val);
	printf("%s -- %d\n",Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val);
	printf("%s -- %d\n\n",Reg[ins_reg[pc].r3].name,Reg[ins_reg[pc].r3].val);
	return;
}

void print2()
{
	printf("\nBefore the operation \n");
	printf("%s -- %d\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val);
	printf("%s -- %d\n",Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val);
	printf("3rd register value -- %d\n\n",ins_reg[pc].r3);
	return;
}

void print3()
{
	printf("\nBefore the operation\n");
	printf("\n%s -- %d\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val);
	printf("\nStack value at index %d -- %d\n\n",abs(ins_reg[pc].r2 + Reg[29].val/4),stack[abs(ins_reg[pc].r2 + Reg[29].val/4) ]);
	return;
	
}

void print4()
{
	printf("\nBefore the operation \n");
	printf("%s -- %d\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val);
	printf("%s -- %d\n",Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val);
	printf("\nLabel is %s\n\n",ins_reg[pc].label_jump);
	return;
}

void fassign(FILE *fp)
{
	int i=0;
	if (strcmp(buffer,".text")==0)
	{
		ins_reg[p_line].fun=19;
		return ;
	}
	else if(buffer[0]=='#')
	{
		ins_reg[p_line].fun=20;
		fgets(buffer,30,fp);
		return;
	}
	else if(lastchar(buffer)==':')
	{
		removelastcharacter(buffer);
		ins_reg[p_line].fun=17;
		strcpy(ins_reg[p_line].label_name,buffer);
		return;
	}
	else if( (strcmp(buffer,"addi") && strcmp(buffer,"andi") && strcmp(buffer,"ori") && strcmp(buffer,"slti") )==0)
	{
		if (strcmp(buffer,"addi")==0)
		{
			ins_reg[p_line].fun=2;
		}
		if (strcmp(buffer,"andi")==0)
		{
			ins_reg[p_line].fun=6;
		}
		if (strcmp(buffer,"ori")==0)
		{
			ins_reg[p_line].fun=8;
		}
		if (strcmp(buffer,"slti")==0)
		{
			ins_reg[p_line].fun=11;
		}
		i=0;
		fscanf(fp, "%s", buffer);
  		removelastcharacter(buffer);
  		while(strcmp(buffer, Reg[i].name) != 0)
  					i++;
  		ins_reg[p_line].r1=i;
  		i=0;
  		fscanf(fp, "%s", buffer);
  		removelastcharacter(buffer);
  		while(strcmp(buffer, Reg[i].name) != 0)
  					i++;
  		ins_reg[p_line].r2=i;
  		i=0;
  		fscanf(fp, "%s", buffer);
  		i = atoi (buffer);
  		ins_reg[p_line].r3=i;
  		i=0;
  		return;

	}
	else if( (strcmp(buffer,"add") && strcmp(buffer,"sub") && strcmp(buffer,"mul") && strcmp(buffer,"and") && strcmp(buffer,"or") && strcmp(buffer,"nor") && strcmp(buffer,"slt") )==0)
	{
		if (strcmp(buffer,"add")==0)
		{
			ins_reg[p_line].fun=1;
		}
		if (strcmp(buffer,"sub")==0)
		{
			ins_reg[p_line].fun=3;
		}
		if (strcmp(buffer,"mul")==0)
		{
			ins_reg[p_line].fun=4;
		}
		if (strcmp(buffer,"and")==0)
		{
			ins_reg[p_line].fun=5;
		}
		if (strcmp(buffer,"or")==0)
		{
			ins_reg[p_line].fun=7;
		}
		if (strcmp(buffer,"nor")==0)
		{
			ins_reg[p_line].fun=9;
		}
		if (strcmp(buffer,"slt")==0)
		{
			ins_reg[p_line].fun=10;
		}
		i=0;
		fscanf(fp, "%s", buffer);
  		removelastcharacter(buffer);
  		while(strcmp(buffer, Reg[i].name) != 0)
  					i++;

  		ins_reg[p_line].r1=i;
  		i=0;
  		fscanf(fp, "%s", buffer);
  		removelastcharacter(buffer);
  		while(strcmp(buffer, Reg[i].name) != 0)
  					i++;
  		ins_reg[p_line].r2=i;
  		i=0;
  		fscanf(fp, "%s", buffer);
  		while(strcmp(buffer, Reg[i].name) != 0)
  					i++;
  		ins_reg[p_line].r3=i;
  		i=0;	
  		return;
	}
	else if((strcmp(buffer,"beq") && strcmp(buffer,"bne") )==0)
	{
		if (strcmp(buffer,"beq")==0)
		{
			ins_reg[p_line].fun=14;
		}
		if (strcmp(buffer,"bne")==0)
		{
			ins_reg[p_line].fun=15;
		}
		i=0;
		fscanf(fp, "%s", buffer);
  		removelastcharacter(buffer);
  		while(strcmp(buffer, Reg[i].name) != 0)
  					i++;
  		ins_reg[p_line].r1=i;
  		i=0;
  		fscanf(fp, "%s", buffer);
  		removelastcharacter(buffer);
  		while(strcmp(buffer, Reg[i].name) != 0)
  					i++;
  		ins_reg[p_line].r2=i;
  		i=0;
  		fscanf(fp, "%s", buffer);
  		strcpy(ins_reg[p_line].label_jump,buffer);
  		return;
	}
	else if(strcmp(buffer,"j")==0)
	{
		ins_reg[p_line].fun=16;
		fscanf(fp, "%s", buffer);
  		strcpy(ins_reg[p_line].label_jump,buffer);
  		return;
	}
	else if((strcmp(buffer,"halt") )==0)
	{
		ins_reg[p_line].fun=18;
		return;
	}
	else if ((strcmp(buffer,"lw") && strcmp(buffer,"sw"))==0)
	{
		if (strcmp(buffer,"lw")==0)
		{
			ins_reg[p_line].fun=12;
		}
		if (strcmp(buffer,"sw")==0)
		{
			ins_reg[p_line].fun=13;
		}
		fscanf(fp, "%s", buffer);
  		removelastcharacter(buffer);
  		while(strcmp(buffer, Reg[i].name) != 0)
  					i++;
  		ins_reg[p_line].r1=i;
  		fscanf(fp, "%s", buffer);
		i=0;
	   	while(buffer[i]!='(')
	   		{
	   			p[i]=buffer[i];
	   			i++;
	   		}	
	   	i = atoi (p);
  		i=i/4;
  		ins_reg[p_line].r2=i;
  		return;		
	}
	else 
	{
		printf("Error at line %d \n",p_line );
		abort();
	}
}

void readfile(FILE *fp)
{

	while(!feof(fp))
	{
		p_line++;
		fscanf(fp, "%s", buffer);
		fassign(fp);
	}

}

void execute()
{
	
	while(pc<=p_line)
	{
		printf("Line of instruction is %d\n",pc );

		switch (ins_reg[pc].fun)
		{
			case 1:
			print1();
			Reg[ins_reg[pc].r1].val= (Reg[ins_reg[pc].r2].val) + (Reg[ins_reg[pc].r3].val);
			printf("\n==> %s(%d) = %s(%d) + %s(%d) \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,Reg[ins_reg[pc].r3].name,Reg[ins_reg[pc].r3].val );
			break;
			case 2:
			print2();
			Reg[ins_reg[pc].r1].val= (Reg[ins_reg[pc].r2].val) + (ins_reg[pc].r3);
			printf("\n==> %s(%d) = %s(%d) + %d \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,ins_reg[pc].r3 );
			break;
			case 3:
			print1();
			Reg[ins_reg[pc].r1].val= (Reg[ins_reg[pc].r2].val) - (Reg[ins_reg[pc].r3].val);
			printf("\n==> %s(%d) = %s(%d) - %s(%d) \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,Reg[ins_reg[pc].r3].name,Reg[ins_reg[pc].r3].val );
			break;
			case 4:
			print1();
			Reg[ins_reg[pc].r1].val= (Reg[ins_reg[pc].r2].val) * (Reg[ins_reg[pc].r3].val);
			printf("\n==> %s(%d) = %s(%d) * %s(%d) \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,Reg[ins_reg[pc].r3].name,Reg[ins_reg[pc].r3].val );
			break;
			case 5:
			print1();
			Reg[ins_reg[pc].r1].val= (Reg[ins_reg[pc].r2].val) & (Reg[ins_reg[pc].r3].val);
			printf("\n==> %s(%d) = %s(%d) (AND) %s(%d) \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,Reg[ins_reg[pc].r3].name,Reg[ins_reg[pc].r3].val );
			break;
			case 6:
			print2();
			Reg[ins_reg[pc].r1].val= (Reg[ins_reg[pc].r2].val) & (ins_reg[pc].r3);
			printf("\n==> %s(%d) = %s(%d) (AND) %d \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,ins_reg[pc].r3 );
			break;
			case 7:
			print1();
			Reg[ins_reg[pc].r1].val= (Reg[ins_reg[pc].r2].val) | (Reg[ins_reg[pc].r3].val);
			printf("\n==> %s(%d) = %s(%d) (OR) %s(%d) \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,Reg[ins_reg[pc].r3].name,Reg[ins_reg[pc].r3].val );
			break;
			case 8:
			print2();
			Reg[ins_reg[pc].r1].val= (Reg[ins_reg[pc].r2].val) | (ins_reg[pc].r3);
			printf("\n==> %s(%d) = %s(%d) (OR) %d \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,ins_reg[pc].r3 );
			break;
			case 9:
			print1();
			Reg[ins_reg[pc].r1].val= ~((Reg[ins_reg[pc].r2].val) | (Reg[ins_reg[pc].r3].val));
			printf("\n==> %s(%d) = %s(%d) (NOR) %s(%d) \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,Reg[ins_reg[pc].r3].name,Reg[ins_reg[pc].r3].val );
			break;
			case 10:
			print1();
			Reg[ins_reg[pc].r1].val= ((Reg[ins_reg[pc].r2].val) < (Reg[ins_reg[pc].r3].val))? 1 : 0;
			printf("\n==> %s(%d)= ( (%s(%d) < %s(%d)) ? 1:0 \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,Reg[ins_reg[pc].r3].name,Reg[ins_reg[pc].r3].val );
			break;
			case 11:
			print1();
			Reg[ins_reg[pc].r1].val= ((Reg[ins_reg[pc].r2].val) < (ins_reg[pc].r3))? 1 : 0;
			printf("\n==> %s(%d)= ( (%s(%d) < %d) ? 1:0 \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,ins_reg[pc].r3 );
			break;
			case 12:
			print3();
			Reg[ins_reg[pc].r1].val= stack[abs(ins_reg[pc].r2 + Reg[29].val/4) ] ;
			printf("\n==>  %s(%d) <-- $sp[%d](%d) \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,abs(ins_reg[pc].r2 + Reg[29].val/4),stack[abs(ins_reg[pc].r2 + Reg[29].val/4) ]);
			break;
			case 13:
			print3();
			stack[abs(ins_reg[pc].r2 + Reg[29].val/4)]=Reg[ins_reg[pc].r1].val;
			printf("\n==>  %s(%d) --> $sp[%d](%d) \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,abs(ins_reg[pc].r2 + Reg[29].val/4),stack[abs(ins_reg[pc].r2 + Reg[29].val/4) ]);
			break;
			case 14:
			print4();
			if((Reg[ins_reg[pc].r1].val) == (Reg[ins_reg[pc].r2].val))
			{
				for(int i=1;i<=p_line;i++)
				{
					if((ins_reg[i].label_name) == (ins_reg[pc].label_jump) )
					{
						printf("\n==> %s(%d) (Equal to) %s(%d) (jump to lable) --->> %s /* Continue to next statement */ \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,ins_reg[pc].label_jump);
						pc=i;
						break;
					}
				}
			}
			printf("\n==> %s(%d) (Not equal to) %s(%d) /* Continue to next statement ignoring the label */\n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val);
			break;
			case 15:
			print4();
			if((Reg[ins_reg[pc].r1].val) != (Reg[ins_reg[pc].r2].val))
			{
				for(int i=1;i<=p_line;i++)
				{
					if((ins_reg[i].label_name) == (ins_reg[pc].label_jump) )
					{
						printf("\n==> %s(%d) (Not Equal to) %s(%d) (jump to lable) --->> %s /* Continue to next statement */ \n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val,ins_reg[pc].label_jump);
						pc=i;
						break;
					}
				}
			}
			printf("\n==> %s(%d) (Equal to) %s(%d) /* Continue to next statement ignoring the label */\n\n",Reg[ins_reg[pc].r1].name,Reg[ins_reg[pc].r1].val,Reg[ins_reg[pc].r2].name,Reg[ins_reg[pc].r2].val);
			break;
			case 16:
			for(int i=1;i<=p_line;i++)
				{
					if((ins_reg[i].label_name) == (ins_reg[pc].label_jump) )
					{
						printf("\nJump to the label - %s\n",ins_reg[pc].label_jump);
						pc=i;
						break;
					}
				}
			break;
			case 17:
			printf("\n ==> Label: moving to the next line \n\n");
			break;
			case 18:
			printf("\nExiting the program !!\n");
			return;
			break;
			case 19:
			printf("\n ==> .text moving to the next line \n\n");
			break;
			case 20:
			printf("\n ==> Comment moving to the next line \n\n");
			break;
			default :
			break;
		}
		pc++;
	}
	return;

}

int main(int argc,char*args[])
{
	init_Reg();
	FILE *f;
	f=fopen(args[1],"r");
	readfile(f);
	printf("\nThe instruction code  is of %d lines\n\n",p_line );
	execute();
	fclose(f);
	printf("\nThe values in the register are :- \n");
	for(int i=0;i<=31;i++)
	{
	printf("\n%s -- %d\n",Reg[i].name,Reg[i].val );
	}
	return 0;
}