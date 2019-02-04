all: lex_pro re_pro lcs_pro
RM = lex_pro lex_pro.c re_pro lcs_pro
CC  = gcc
LEX = lex
CPP = g++

lex_pro: lex_pro.c
	$(CC) -g -o $@ $< -ll

lex_pro.c: file19.l
	$(LEX) -o $@ $<

re_pro: pro1.cpp
	$(CPP) -g -o $@ $<

lcs_pro: lcs.cpp
	$(CPP) -g -o $@ $<

clean:
	rm $(RM)
