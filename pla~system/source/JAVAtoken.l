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
{	if(fun_start==1 ){
		char *fun_name=s;
		char str[30]="@";

		fun_name=strtok(fun_name,"(");
		if(strcmp(fun_name,"super")==0){
			strcpy(str,"#CALLSUPER");
		}
		else if (strcmp(fun_name,"this")==0){
			strcpy(str,"#CALLTHIS");
		}
		else {
			strcat(str,fun_name);
		}
		
		count_print(); printf("%s  ",str); 
	}
}

void my_print(char* str)			
{ if(fun_start==1) {count_print(); printf("%s  ",str);}  }

void count_print(){
	if(count==PRINT_ENTER) { count=0; printf("\n"); }
	++count;
}

	

%}

comment1		"//".*\n|"//".*\r
comment2		"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*"*"+"/"
digit 			(([0-9]+)|([0-9]*"."[0-9]+)([eE][-+]?[0-9]+)?)[;]?
String			\"(.*)\"
Cstring			\'[.]\'
ID			[\*&]*[a-zA-Z_]+[0-9]*("["([\*&]*[a-zA-Z_0-9]*)"]")*"->"?"."?
		

stl			("<"[<>a-zA-Z0-9_" ",]+">")*
stl2			("<"[<>a-zA-Z0-9_" ",]+">")
const			const|register
para			({const}|[" "]+)*(([a-zA-Z_0-9\*&" "]+{stl2}[" "\n\t\r\*&]*[\(\)a-zA-Z_0-9\*&\[\]]+)|([a-zA-Z_0-9\*&]+[" "]+[\n\t\r\*&]*[\(\)a-zA-Z_0-9\*&\[\]]+)|([a-zA-Z_0-9\*&]+[\n\t\r\*&]*[\(]+[\(\)a-zA-Z_0-9\*&\[\]]+))|([" "]*"..."[" "]*)|([a-zA-Z_0-9\*&]+[" "]+[\n\t\r\*&]*[" "]*[\*]+[" "]*[\(\)a-zA-Z_0-9&\[\]]+)|([a-zA-Z]+[\[\]a-zA-Z0-9" "]+)
parameter		[" "]*|[" "]*"void"[" "]*|{para}([" ",\n\t\r]+{para}+)*[" "\n\t\r]*

call_fun 		[a-zA-Z_]+[a-zA-Z_0-9]*[" "\n\t\r]*\({parameter}\)
call_fun2 		[a-zA-Z_]+[a-zA-Z_0-9]*[" "]*\(
define_fun 		[a-zA-Z_]+{stl}[" "]*[&\*]*[" "\n]+[a-zA-Z0-9_\n]*"::"?{call_fun}
define_fun2 	[a-zA-Z_]+{stl}[" "]*[&\*]+[a-zA-Z0-9_\n]*"::"?{call_fun}

fun_end 		[" "\n\t\r]*"const"?[" "\n\t\r]*\{

bit_op			<<|>>|&|\^|\|~|\||>>>
relational_op		<=|>=|>|<|==|!=|\?|:
arithm_op		\+|-|\*|\/|%
plus			"+"
minu			"-"
mul			"*"
div			"/"
rem			"%"

assignment_op		\+=|-=|\*=|\/=|%=|<<=|>>=|&=|^=|\|=|<<=|>>=|>>>=|\|=
assign			=
increment_op		\+\+
decrement_op		--
logical_op		&&|\|\||!


ABSTRACT		abstract
ASSERT			assert							
CATCH			catch						
DO				do				
ENUM			enum			
EXTENDS			extends			
FINAL 			final			
FINALLY			finally			
IMPLEMENTS		implements		
INSTANCEOF		instanceof		
INTERFACE		interface		
NATIVE			native			
NEW				new				
PACKAGE			package			
PRIVATE			private			
PROTECTED		protected		
PUBLIC			public					
STATIC			static			
STRICTFP		strictfp		
SUPER			super			
SYNCHRONIZED	synchronized	
THIS			this			
THROW			throw
THROWS			thwows			
TRANSIENT		transient		
TRY				try				
VOLATILE		volatile		

type 			boolean|byte|char|double|int|long|short|String|float


CONTINUE		continue
BREAK			break
RETURN			return
DEFAULT			default
CASE			case

IF_FOR_WHILE		(if|for|while|switch)+[" "\t]*\(|"else"[" "\t\n\t]*\(

IF				("if"[" "\t]*\()
ELSE			("else")|("else"[" "\t]+"if"[" "\t]*\()
WHILE			"while"[" "\t]*\(
FOR				"for"[" "\t]*\(
SWITCH			"switch"[" "\t]*\(

TRUE			true
FALSE			false







%%

{comment1}		;
{comment2}		;




{define_fun}{fun_end}	{ define_fun(yytext);  fun_start=1; my_print("#Y");}

{define_fun2}{fun_end}	{ define_fun2(yytext); fun_start=1;  my_print("#Y"); }
	
\{			{ my_print("#Y"); if(fun_start==1) ++bra_num;	}
\}			{ 
				if(fun_start==1){
					my_print("#Z");
					if(bra_num==0){ my_print("}"); printf("\n"); fun_start=0; count=0;}
					else --bra_num; 			
			  	}
			}


{increment_op}		{ my_print("#1"); }
{decrement_op}		{ my_print("#2"); }
{assignment_op}		{ my_print("#3"); }
{bit_op}			{ my_print("#4"); }
{relational_op}		{ my_print("#5"); }
{logical_op}		{ my_print("#6"); }
{assign}			{ my_print("#7"); }
{plus}				{ my_print("#8"); }
{minu}				{ my_print("#9"); }
{mul}				{ my_print("#10"); }
{div}				{ my_print("#11"); }
{rem}				{ my_print("#12"); }

{IF}				{ my_print("#IF");  }
{ELSE}				{ my_print("#ELSE");  }
{FOR}				{ my_print("#FOR"); }
{WHILE}				{ my_print("#WHILE");  }
{SWITCH}			{ my_print("#SWITCH"); }

{CONTINUE}			{ my_print("#CONTI"); }
{BREAK}				{ my_print("#BREAK"); }
{RETURN}			{ my_print("#RET"); }
{DEFAULT}			{ my_print("#DF");  }
{CASE}				{ my_print("#CASE");  }

{call_fun2}			{ print_fun(yytext);  }			//call function

{digit}				{ my_print("#N");  }
{type}				{ my_print("#TYPE");  }

{ABSTRACT}			{ my_print("#ABSTRACT");  }	
{ASSERT}			{ my_print("#ASSERT");  }
{CATCH}				{ my_print("#CATCH");  }
{DO}				{ my_print("#DO");  }
{ENUM}				{ my_print("#ENUM");  }		
{EXTENDS}			{ my_print("#EXTENDS");  }	
{FINALLY}			{ my_print("#FINALLY");  }	
{FINAL}				{ my_print("#FINAL");  }	
{IMPLEMENTS}		{ my_print("#IMPLEMENTS");  }	
{INSTANCEOF}		{ my_print("#INSTANCEOF");  }	
{INTERFACE}			{ my_print("#INTERFACE");  }	
{NATIVE}			{ my_print("#NATIVE");  }	
{NEW}				{ my_print("#NEW");  }	
{PACKAGE}			{ my_print("#PACKAGE");  }	
{PRIVATE}			{ my_print("#PRIVATE");  }	
{PROTECTED}			{ my_print("#PROTECTED");  }
{PUBLIC}			{ my_print("#PUBLIC");  }	
{STATIC}			{ my_print("#STATIC");  }	
{STRICTFP}			{ my_print("#STRICTFP");  }	
{SUPER}				{ my_print("#SUPER");  }	
{SYNCHRONIZED}		{ my_print("#SYNCHRONIZED");  }	
{THIS}				{ my_print("#THIS");  }	
{THROW}				{ my_print("#THROW");  }	
{THROWS}			{ my_print("#THROWS");  }	
{TRANSIENT}			{ my_print("#TRANSIENT");  }	
{TRY}				{ my_print("#TRY");  }	
{VOLATILE}			{ my_print("#VOLATILE");  }	


{ID}			;
\n			;
.			;




%%

main(){
	ff=fopen("fibo.c","r+");
	yyin=ff;
	yylex();
	fclose(ff);
}




