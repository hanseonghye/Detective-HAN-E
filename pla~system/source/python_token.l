%{
#include <stdio.h>
#include <string.h>
FILE *ff;

int fun_start=0;
int bra_num=0;
int count=0;
int PRINT_ENTER=4;


char *substr(char *input, int i_begin, int i_end)
{
     int cnt = 0;
     int size = (i_end - i_begin)+2;
     char *str = (char*)malloc(size);

     memset(str, 0, size);

     for(int i = i_begin; i <= i_end; i++)
     {
          str[cnt] = input[i];
          cnt++;
     }

     return str;
}


void define_fun(char* s)						//define function
{ 
	if(s[0]=='\n') {}
	else 	{ printf("\n"); count=0; } 

	char *fun_name;
	char _name[15];
	char *name=s;
	char str[30]="$";
	int len, point=0;
	int i;
	
	name=strtok(name,"("); 
	len=strlen(name);
	
	for(i=len-1;i>0;--i){
		if(name[i]!=' ') {point=i; break; }
	}
	name=substr(name,0,point);
	
	len=strlen(name);
	for(i=len-1;i>0;--i){
		if(name[i]==' ') { point=i+1; break; }
		if(name[i]==':') { point=i+1; break; }
		if(name[i]=='	') { point=i+1; break; }
	}
	if(i==0) fun_name=name;
	else fun_name=substr(name,point,strlen(name));

	strcat(fun_name,"{");
	strcat(str,fun_name);
	
	printf("%s  ",str); printf("\n"); count=0; 
}


void define_fun2(char* s)						//define function
{ 
	if(s[0]=='\n') {}
	else 	{ printf("\n"); count=0; } 

	char *fun_name;
	char _name[15];
	char *name=s;
	char str[30]="$";
	int len, point=0;
	int i;
	
	name=strtok(name,"("); 
	len=strlen(name);
	
	for(i=len-1;i>0;--i){
		if(name[i]!=' ') {point=i; break; }
	}
	name=substr(name,0,point);
	
	len=strlen(name);
	for(i=len-1;i>0;--i){
		if(name[i]=='&') { point=i+1; break; }
		if(name[i]=='*') { point=i+1; break; }
		if(name[i]==':') { point=i+1; break; }
	}

	if(i==0) fun_name=name;
	else fun_name=substr(name,point,strlen(name));

	strcat(fun_name,"{");
	strcat(str,fun_name);
	
	printf("%s  ",str); printf("\n"); count=0; 
}

void print_fun(char* s)						//call function
{	if(fun_start==1){
		char *fun_name=s;
		char str[30]="@";

		fun_name=strtok(fun_name,"(");		
		strcat(str,fun_name); 
		count_print(); printf("%s  ",str); 
	}
}

void my_print(char* str)			
{ if(fun_start==1 ) {count_print(); printf("%s  ",str);}  }

void count_print(){
	if(count==PRINT_ENTER) { count=0; printf("\n"); }
	++count;
}

	


%}
comment1		"#".*\n|"//".*\r
comment2		"'''"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*"'''"|\"\"\"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\"\"\"
digit 			(([0-9]+)|([0-9]*"."[0-9]+)([eE][-+]?[0-9]+)?)[;]?|"true"|"false"
String			\"(.*)\"|"'"(.*)"'"
ID				[\*&]*[a-zA-Z_]+[0-9]*("["([\*&]*[a-zA-Z_0-9]*)"]")*"->"?"."?


AND				and 
ASSERT 			assert 
BREAK 			break 
CLASS 			class 
CONTINUE 		continue 
DEF 			def 
DEL 			del 
ELIF 			elif 
ELSE 			else 
EXCEPT 			except 
EXEC 			exec 
FINALLY 		finally 
FOR 			for 
FROM 			from 
GLOBAL 			global 
IF 				if 
IMPORT 			import 
IN 				in 
IS  			is 
LAMBDA 			lambda 
NOT 			not 
OR 				or 
PASS 			pass 
PRINT 			print 
RAISE 			raise 
RETURN 			return 
TRY 			try 
WHILE 			while 
WITH 			with 
YIELD 			yield

MULTILINE 		"\"

DICT			("dict"[" "]*"()")|"{}"

ARITHM_OP		"+"|"-"|"*"|"/"|"%"|"**"|"//"
COMPA_OP		"=="|"!="|">"|"<"|">="|"<="
ASSIGN_OP		"="|"+="|"-="|"*="|"/="|"%/"|"**="|"//="
BIT_OP			"&"|"|"|"^"|"~"|"<<"|">>"



%%

{comment1}		;
{comment2}		;

int("#VOLATILE");}


{ID}			;
\n			;
.			;




%%


main(int argc, char *argv[]){
	ff=fopen(argv[1],"r+");
	yyin=ff;
	yylex();
	fclose(ff);
}




