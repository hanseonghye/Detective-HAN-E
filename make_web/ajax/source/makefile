all: lex_C lex_JAVA re_pro lcs_pro
RM = lex_C lex_JAVA lex_C.c lex_JAVA.c re_pro lcs_pro
CC  = gcc
LEX = lex
CPP = g++

lex_C: lex_C.c
	$(CC) -g -o $@ $< -ll

lex_JAVA: lex_JAVA.c
	$(CC) -g -o $@ $< -ll

lex_C.c: Ctoken.l
	$(LEX) -o $@ $<

lex_JAVA.c: JAVAtoken.l
	$(LEX) -o $@ $<

re_pro: pro1.cpp
	$(CPP) -g -o $@ $<

lcs_pro: lcs.cpp
	$(CPP) -g -o $@ $<

clean:
	rm $(RM)
