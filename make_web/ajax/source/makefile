all: lex_CS lex_CH lex_JAVAS lex_JAVAH re_pro Alcs_pro nAlcs_pro
RM = lex_CS lex_CH lex_JAVAS lex_JAVAH lex_CS.c lex_CH.c lex_JAVAS.c lex_JAVAH.c re_pro Alcs_pro nAlcs_pro
CC  = gcc
LEX = lex
CPP = g++

lex_CS: lex_CS.c
	$(CC) -g -o $@ $< -ll

lex_CH: lex_CH.c
    $(CC) -g -o $@ $< -ll

lex_JAVAS: lex_JAVAS.c
	$(CC) -g -o $@ $< -ll

lex_JAVAH: lex_JAVAH.c
	$(CC) -g -o $@ $< -ll

lex_CS.c: CtokenS.l
	$(LEX) -o $@ $<

lex_CH.c: CtokenH.l
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
