%{
#include <stdio.h>
#include <string.h>
#include "TeaplAst.h"
#include "y.tab.hpp"
extern int line, col;
int c;
int calc(char *s, int len);
%}


%start COMMENT_SHORT COMMENT_LONG
%%
<INITIAL>"\t" { col+=4; }
<INITIAL>[1-9][0-9]* {
    yylval.tokenNum = A_TokenNum(A_Pos(line, col), calc(yytext, yyleng));
    col+=yyleng;
    return NUM;
}
<INITIAL>0 {
    yylval.tokenNum = A_TokenNum(A_Pos(line, col), 0);
    ++col;
    return NUM;
}
<COMMENT_SHORT>{
[\n\r] {  BEGIN INITIAL; line=line+1; col=0; }
. {  /* 单行注释 */ }
}
<COMMENT_LONG>{
"*/" {  BEGIN INITIAL;  }
[\n\r] { line=line+1; col=0;  }
. { /* 多行注释 */ }
}
<INITIAL>{
"//"  { BEGIN COMMENT_SHORT; }
"/*" { BEGIN COMMENT_LONG; }
[\n\r] { line=line+1; col=0; }
"->"    { yylval.pos = A_Pos(line, col); col+=yyleng; return ARROW; }
"*"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return MUL; }
"/"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return DIV; }
"+"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return ADD; }
"-"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return SUB; }

";"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return SEMICOLON; }
","	{ yylval.pos = A_Pos(line, col); col+=yyleng; return COMMA; }
"struct"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return STRUCT; }
"if"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return IF; }
"else"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return ELSE; }
"let"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return LET; }
">="	{ yylval.pos = A_Pos(line, col); col+=yyleng; return LESS_EQ; }
">"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return GREATER; }
"<="	{ yylval.pos = A_Pos(line, col); col+=yyleng; return GREATER_EQ; }
"<"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return LESS; }
"=="	{ yylval.pos = A_Pos(line, col); col+=yyleng; return EQUAL; }
"!="	{ yylval.pos = A_Pos(line, col); col+=yyleng; return NOT_EQUAL; }
"="	{ yylval.pos = A_Pos(line, col); col+=yyleng; return ASSIGN; }
"("	{ yylval.pos = A_Pos(line, col); col+=yyleng; return LPAREN; }
")"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return RPAREN; }
"["	{ yylval.pos = A_Pos(line, col); col+=yyleng; return LBRACKET; }
"]"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return RBRACKET; }
"{"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return LBRACE; }
"}"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return RBRACE; }
"."	{ yylval.pos = A_Pos(line, col); col+=yyleng; return DOT; }
":"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return COLON; }
"int"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return INT; }
"&&"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return AND; }
"||"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return OR; }
"!"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return NOT; }


"fn"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return FN; }

"ret"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return RET; }
"continue"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return CONTINUE; }
"break"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return BREAK; }
"while"	{ yylval.pos = A_Pos(line, col); col+=yyleng; return WHILE; }
[a-zA-Z_]+([a-zA-Z0-9_]*) 	{ 
    int len = yyleng;
    char* new_text = (char*)malloc((len+1)*sizeof(char));
    strcpy(new_text, yytext);
    new_text[len]='\0';
    yylval.tokenId = A_TokenId(A_Pos(line, col), new_text); col+=yyleng; return ID; 
}

" "   { col+=1; }

.	{ printf("词法错误: 未知字符: %s 在 %d 行 %d 列\n", yytext, line, col); }

}
%%

// This function takes a string of digits and its length as input, and returns the integer value of the string.
int calc(char *s, int len) {
    int ret = 0;
    for(int i = 0; i < len; i++)
        ret = ret * 10 + (s[i] - '0');
    return ret;
}