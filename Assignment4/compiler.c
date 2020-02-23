/*
This program is a compiler for the programming language XMicro
This compiler was created for the COSC-341 class
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* constants for true and false */
#define FALSE 0
#define TRUE 1

/*enumerated types for token types*/
typedef enum
{
    ID, INTLITERAL, BEGIN, END, READ, WRITE,
    PLUSOP, MINUSOP, ASSIGNOP, LPAREN, RPAREN,
    COMMA, SEMICOLON, SCANEOF

} token;

/*functions declarations related to scanner*/
token scanner();
void clear_buffer();
void buffer_char(char c);
token check_reserved();
void lexical_error();

/*functions declartions related to parser*/
void parser();
void program();
void statement_list();
void statement();
void id_list();
void expresssion_list();
void expression();
void term();
void add_op();
void match(token tok);
void syntax_error();

/*global varibles*/
FILE *fin;                  /*source file*/
token next_token;           /*next token in source file*/
char token_buffer[100];     /*token buffer*/
int token_ptr;              /*buffer pointer*/
int line_num = 1;           /*line number in source file*/
int error = FALSE;          /*flag to indicate error*/

/***********************************************************************************************/

/*returns next token from source file*/
token scanner()
{
    char c;                         /*current character in source file*/
    clear_buffer();                 /*empty token buffer*/
    while(TRUE)                     /*loop reads and returns next token*/
    {
        c = getc(fin);              /*read a character from source file*/
        if(c == EOF)                /*read a character from source file*/
        {
            return SCANEOF;         /*end of file*/
        
        }else if (isspace(c))       /*skip white spaces and count line number*/
        {
            if(c == '\n'){
                line_num = line_num++;
            }

        }else if (isaplpha(c))      /*identifier or reversed word*/
        {
            buffer_char(c);         /*buffer the first character*/
            c = getc(fin);
            while (isalnum(c) || c == '_') /*read and buffer subsequent characters*/
            {
                buffer_char(c);
                c = getc(fin);
            }
            ungetc(c, fin);           /*put back the last character read*/
            return check_reserved();  /*return identifier or reserved word*/  

        }else if (isdigit(c))         /*integer literal*/
        {
            buffer_char(c);           /*buffer the first character*/
            c = getc(fin);
            while(isdigit(c))         /*read and buffer subsequent characters*/
            {
                buffer_char(c);
                c = getc(fin);
            }
            ungetc(c, fin);             /*put back the last character read*/
            return INTLITERAL;          /*return integer literal*/

        }else if(c =='(')               /*left parentheses*/
            return LPAREN;
        
        else if(c == ')')               /*right parentheses*/
            return RPAREN;

        else if(c == ',')               /*comma*/
            return COMMA;

        else if (c ==';')               /*semicolon*/
            return SEMICOLON;

        else if(c == '+')               /*plus operator*/
            return PLUSOP;

    }
}


