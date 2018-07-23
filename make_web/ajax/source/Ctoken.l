%{
#include <stdio.h>
#include <string.h>
FILE *ff;

int fun_start=0;
int bra_num=0;
int count=0;
int PRINT_ENTER=4;
int macro_start=0;

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
{	if(fun_start==1 || macro_start==1){
		char *fun_name=s;
		char str[30]="@";

		fun_name=strtok(fun_name,"(");		
		strcat(str,fun_name); 
		count_print(); printf("%s  ",str); 
	}
}

void my_print(char* str)			
{ if(fun_start==1 || macro_start==1) {count_print(); printf("%s  ",str);}  }

void count_print(){
	if(count==PRINT_ENTER) { count=0; printf("\n"); }
	++count;
}

	


%}
comment1		"//".*\n|"//".*\r
comment2		"/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*"*"+"/"
digit 			(([0-9]+)|([0-9]*"."[0-9]+)([eE][-+]?[0-9]+)?)[;]?|"true"|"false"
String			\"(.*)\"
Cstring			\'[.]\'
ID			[\*&]*[a-zA-Z_]+[0-9]*("["([\*&]*[a-zA-Z_0-9]*)"]")*"->"?"."?
		

MACRO_FUN		"#define"[" "\t]*[a-zA-Z_]+[0-9]*\(([" "]*|([" "a-zA-Z0-9]+([," "\t]+[a-zA-Z0-9]+)*)+)\)

stl			("<"[<>a-zA-Z0-9_" ",]+">")*
stl2			("<"[<>a-zA-Z0-9_" ",]+">")
const			const|register
para			({const}|[" "]+)*(([a-zA-Z_0-9\*&" "]+{stl2}[" "\n\t\r\*&]*[\(\)a-zA-Z_0-9\*&\[\]]+)|([a-zA-Z_0-9\*&]+[" "]+[\n\t\r\*&]*[\(\)a-zA-Z_0-9\*&\[\]]+)|([a-zA-Z_0-9\*&]+[\n\t\r\*&]*[\(]+[\(\)a-zA-Z_0-9\*&\[\]]+))|([" "]*"..."[" "]*)|([a-zA-Z_0-9\*&]+[" "]+[\n\t\r\*&]*[" "]*[\*]+[" "]*[\(\)a-zA-Z_0-9&\[\]]+)
parameter		[" "]*|[" "]*"void"[" "]*|{para}([" ",\n\t\r]+{para}+)*[" "\n\t\r]*

call_fun 		[a-zA-Z_]+[a-zA-Z_0-9]*[" "\n\t\r]*\({parameter}\)
call_fun2 		[a-zA-Z_]+[a-zA-Z_0-9]*[" "]*\(
define_fun 		[a-zA-Z_]+{stl}[" "]*[&\*]*[" "\n]+[a-zA-Z0-9_\n]*"::"?{call_fun}
define_fun2 	[a-zA-Z_]+{stl}[" "]*[&\*]+[a-zA-Z0-9_\n]*"::"?{call_fun}

fun_end 		[" "\n\t\r]*"const"?[" "\n\t\r]*\{


bit_op			<<|>>|&|\^|\|~|\|
relational_op		<=|>=|>|<|==|!=|\?|:
arithm_op		\+|-|\*|\/|%
plus			"+"
minu			"-"
mul			"*"
div			"/"
rem			"%"

assignment_op		\+=|-=|\*=|\/=|%=|<<=|>>=|&=|^=|\|=
assign			=
increment_op		\+\+
decrement_op		--
logical_op		&&|\|\||!


ASM			asm
AUTO			auto
CATCH			catch
CLASS			class
CONST			const
CONST_CAST		const_cast
DELETE			delete
DO			do
ENUM			enum
EXPLICIT		explicit
EXPORT			export
EXTERN			extern
GOTO			goto
FRIEND			friend
INLINE			inline
NAMESPACE		namespace
NEW			new
NULL			NULL
OPERATOR		operator
PRIVATE			private
PROTECTED		protected
PUBLIC			public
REGISTER		register
SIZEOF			sizeof
STATIC			static
STRUCT			struct
THIS			this
TYPEDEF			typedef
TRY			try
THROW			throw
TYPEID			typeid
TYPENAME		typename
UNION			union
USING			using
VIRTUAL			virtual
VOLATILE		volatile


type			bool|byte|char|double|int|long|short|string|unsigned|void|float|signed


CONTINUE		continue
BREAK			break
RETURN			return
DEFAULT			default
CASE			case

IF_FOR_WHILE		(if|for|while|switch)+[" "\t]*\(|"else"[" "\t\n\t]*\(

IF			("if"[" "\t]*\()
ELSE			("else")|("else"[" "\t]+"if"[" "\t]*\()
WHILE			"while"[" "\t]*\(
FOR			"for"[" "\t]*\(
SWITCH			"switch"[" "\t]*\(





%%

{comment1}		;
{comment2}		;

{MACRO_FUN}		{ define_fun(yytext); macro_start=1;}


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

{ASM}				{ my_print("#ASM");  }	
{AUTO}				{ my_print("#AUTO"); }
{CATCH}				{ my_print("#CATCH"); }
{CLASS}				{ my_print("#CLASS"); }
{CONST}				{ my_print("#CONST"); }
{CONST_CAST}		{ my_print("#CONST2"); }
{DELETE}			{ my_print("#DELETE"); }
{DO}				{ my_print("#DO"); }
{ENUM}				{ my_print("#ENUM"); }
{EXPLICIT}			{ my_print("#EXPL"); }
{EXPORT}			{ my_print("#EXPORT"); }	
{EXTERN}			{ my_print("#EXTERN"); }
{GOTO}				{ my_print("#GOTO"); }
{FRIEND}			{ my_print("#FRIEND"); }	
{INLINE}			{ my_print("#INLINE"); }	
{NAMESPACE}			{ my_print("#NS");  }
{NEW}				{ my_print("#NEW"); }
{NULL}				{ my_print("#NULL");}
{OPERATOR}			{ my_print("#OPERA"); }
{PRIVATE}			{ my_print("#PRIVATE"); }	
{PROTECTED}			{ my_print("#PROTE"); }
{PUBLIC}			{ my_print("#PUBLIC"); }	
{REGISTER}			{ my_print("#REGISTER"); }
{SIZEOF}			{ my_print("#SIZEOF"); }	
{STATIC}			{ my_print("#STATIC"); }	
{STRUCT}			{ my_print("#STRUCT"); }	
{THIS}				{ my_print("#THIS"); }
{TYPEDEF}			{ my_print("#TYPEDEF"); }	
{TRY}				{ my_print("#TRY"); }
{THROW}				{ my_print("#THROW"); }
{TYPEID}			{ my_print("#TPID");  }	
{TYPENAME}			{ my_print("#TPNAME");}
{UNION}				{ my_print("#UNION"); }
{USING}				{ my_print("#USING"); }
{VIRTUAL}			{ my_print("#VIRTUAL"); }	
{VOLATILE}			{ my_print("#VOLATILE");}


{ID}			;
\n			{ if(macro_start==1) {  my_print("}"); printf("\n"); macro_start=0; count=0; } }
.			;




%%


main(int argc, char *argv[]){
	ff=fopen(argv[1],"r+");
	yyin=ff;
	yylex();
	fclose(ff);
}




