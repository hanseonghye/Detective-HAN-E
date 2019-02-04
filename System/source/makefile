all: lex_CS lex_CR lex_JAVAS lex_JAVAR re_pro Alcs_pro nAlcs_pro
RM = lex_CS lex_CR lex_JAVAS lex_JAVAR lex_CS.c lex_CR.c lex_JAVAS.c lex_JAVAR.c re_pro Alcs_pro nAlcs_pro
CC  = gcc
LEX = lex
CPP = g++

lex_CS: lex_CS.c
	$(CC) -g -o $@ $< -ll

lex_CR: lex_CR.c
	$(CC) -g -o $@ $< -ll

lex_JAVAS: lex_JAVAS.c
	$(CC) -g -o $@ $< -ll

lex_JAVAR: lex_JAVAR.c
	$(CC) -g -o $@ $< -ll

lex_CS.c: CtokenS.l
	$(LEX) -o $@ $<

lex_CR.c: CtokenR.l
	$(LEX) -o $@ $<

lex_JAVAS.c: JAVAtokenS.l
	$(LEX) -o $@ $<

lex_JAVAR.c: JAVAtokenR.l
	$(LEX) -o $@ $<



re_pro: pro1.cpp
	$(CPP) -g -o $@ $<

Alcs_pro: lcs.cpp
	$(CPP) -g -o $@ $<

nAlcs_pro: lcs_notA.cpp
	$(CPP) -g -o $@ $<


clean:
	rm $(RM)
