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
    MAIN, LCURL, RCURL, ASSIGNOP, READ, WRITE, 
    IF, ELSE, WHILE, PLUSOP, MINUSOP, MULTIOP, DIVOP,
    LPAREN, RPAREN, LESSTHAN, GREATTHAN, EQUALTO,
    LESSANDEQUAL, GREATANDEQUAL, NOTEQUAL, 
    SEMICOLON, COMMA, SCANEOF

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
FILE *out;                  /*output file*/
token next_token;           /*next token in source file*/
char token_buffer[100];     /*token buffer*/
int token_ptr;              /*buffer pointer*/
int line_num = 1;           /*line number in source file*/
int error = FALSE;          /*flag to indicate error*/
void  expression_list();


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
        
        }
        else if (isspace(c))       /*skip white spaces and count line number*/
        {
            if(c == '\n'){
                line_num = line_num + 1;
            }

        }
        else if (isalpha(c))      /*identifier or reversed word*/
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

        }
        else if (isdigit(c))         /*integer literal*/
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

        }

        else if(c =='>')               /*greater than*/
             {
            c = getc(fin);
            if(c == '='){               /*and equal*/
                return GREATANDEQUAL;               

            }
            else
            {
                ungetc(c, fin);
                return GREATTHAN;
            }
        }

        else if(c =='<')               /*less than*/
             {
            c = getc(fin);
            if(c == '='){               /*and equal*/
                return LESSANDEQUAL;               

            }
            else
            {
                ungetc(c, fin);
                return LESSTHAN;
            }
        }

        else if(c =='!')               /*greater than*/
             {
            c = getc(fin);
            if(c == '='){               /*and equal*/
                return NOTEQUAL;               

            }
            else
            {
                ungetc(c, fin);
                lexical_error();
            }
        }

        else if(c =='{')               /*left Bracket*/
            return LCURL;

        else if(c =='}')               /*Right bracket*/
            return RCURL;

        else if(c =='(')               /*left parentheses*/
            return LPAREN;
        
        else if(c == ')')               /*right parentheses*/
            return RPAREN;

        else if(c == ',')               /*comma*/
            return COMMA;

        else if (c ==';')               /*semicolon*/
            return SEMICOLON;

        else if(c == '*')               /*multiply operator*/
            return MULTIOP;

        else if(c == '-')               /*minus operator*/
            return MINUSOP;

        else if(c == '+')               /*plus operator*/
            return PLUSOP;

        else if (c == '/')               /*comment or divide operator*/
        {
            c = getc(fin);
            if(c == '/'){               /*read in comment*/
                do                      /*read and discard until end of line*/                  
                   c = getc(fin);
                while(c != '\n');
                line_num = line_num + 1;  
            }
            else
            {
                ungetc(c, fin);
                return DIVSOP;
            }
        }
        else if(c == ':')             /*possible assignment operator*/
        {
            c = getc(fin);            
            if(c == '=')              /*assignment operator*/
                return ASSIGNOP;
            else                      /*error due to :*/
            {
                ungetc(c, fin);
                lexical_error();
            }

        }
    
        else                           /*ivalid character*/
            lexical_error();     

    }

}
/***********************************************************************************************/


/*clears the buffer*/
void clear_buffer()
{
    token_ptr = 0;                      /*reset token pointer*/
    token_buffer[token_ptr] = '\0';     /*add null character*/
}

/***********************************************************************************************/

/*appends the char cter to the buffer*/
void buffer_char(char c)
{
    token_buffer[token_ptr] = c;        /*append current character*/
    token_ptr = token_ptr +1;           /*move token pointer*/
    token_buffer[token_ptr] = '\0';     /*move null characters*/
}

/***********************************************************************************************/

/*checks whearther buffer is reserved word or identifier*/
token check_reserved()
{
    if(strcmp(token_buffer, "main") == 0)  /*six reserved words*/
        return MAIN;
     else if(strcmp(token_buffer, "if") == 0)
        return IF;
     else if(strcmp(token_buffer, "else") == 0)
        return ELSE;  
     else if(strcmp(token_buffer, "while") == 0)
        return WHILE;                   
    else if(strcmp(token_buffer, "read") == 0)
        return READ;
    else if(strcmp(token_buffer, "write") == 0)
        return WRITE;
    else                                    /*identifier*/
        return ID;
}

/***********************************************************************************************/

/*reports lexical error and sets the error flag*/
void lexical_error()
{
    printf("lexical error in line %d\n", line_num);
    error = TRUE;
}

/***********************************************************************************************/

/*parses source file */
void parser()
{
    next_token = scanner();             /*read the first token*/
    program();                          /*parse the program*/
    match(SCANEOF);                     /*check end of file*/
}

/***********************************************************************************************/

/*parses a progaram */
/* <program> --> begin<stmtlist>end */
void program()
{
    match(BEGIN);                       /*begin**/
    statement_list();                   /*list of statements*/
    match(END);                         /*end*/
}

/***********************************************************************************************/

/*parses list of  statement*/
/* <stmtlist> --> <stmt>{<stmt>} */
void statement_list()
{
    statement();                        /*first statement*/
    while (TRUE)
    {
        if(next_token == ID || next_token == READ || next_token == WRITE)
            statement();                /*subsequent statements*/
        else
            break;
    }
}

/***********************************************************************************************/

/*parses one statement*/
/* <stmt> --> id:=<expr>;
   <stmt> --> read(<idlist>);
   <stmt> --> write(<exprlist>); */
void statement()
{
    if(next_token == ID)               /*assignment statement*/
    {
        match(ID);
        match(ASSIGNOP);
        expression();
        match(SEMICOLON);
    }
    else if (next_token == READ)        /*read statement */
    {
        match(READ);
        match(LPAREN);
        id_list();
        match(RPAREN);
        match(SEMICOLON);
    }
    else if (next_token == WRITE)       /*write statement*/
    {
        match(WRITE);
        match(LPAREN);
        expression_list();
        match(RPAREN);
        match(SEMICOLON);
    }
    else                                /*invalid beginning of statement*/
        syntax_error();
}

/***********************************************************************************************/

/*parses list of identifiers*/
/* <idlist> --> id{, id} */
void id_list()
{
    match(ID);                          /*first identifer*/
    while(next_token == COMMA)
    {
        match(ID);
        while(next_token == COMMA)
        {
            match(COMMA);
            match(ID);                  /*subsequent identifiers*/
        }
    }
}

/***********************************************************************************************/

/*parses list of expressions */
/* <explist> --> <term>{<adop><term>} */
void  expression_list()
{
    expression();                       /*first expression*/
    while(next_token == COMMA)
    {
        match(COMMA);
        expression();                   /*susequent expression*/
    }
}

/***********************************************************************************************/

/*parses one expression*/
/* <exp> --> <term>{<adop><term>} */
void expression()
{
    term();                             /*first term*/
    while(next_token == PLUSOP || next_token == MINUSOP)
    {
        add_op();                       /*plus or minus operators*/
        term();                         /*subsequenbt terms*/
    }
}

/***********************************************************************************************/

/*parses one term*/
/* <term> --> id
   <term> --> integer
   <term> --> (<expr>)  */
void term()
{
    if(next_token == ID)                /*identifer*/
        match(ID);
    else if(next_token == INTLITERAL)   /*integer literal*/
        match(INTLITERAL);
    else if (next_token == LPAREN)      /*expression inside parentheses*/
    {
        match(LPAREN);
        expression();
        match(RPAREN);
    }
    else
        syntax_error();                 /*invalid term*/
}

/***********************************************************************************************/

/*parses plus or minus operator*/
/* <adop> --> +|- */
void add_op()
{
    if(next_token == PLUSOP || next_token == MINUSOP)
        match(next_token);
    else
        syntax_error();
}

/***********************************************************************************************/

/*checks wheather the expected token and the actual token match, and also reads the next 
token from source file*/
void match(token tok)
{
    if(tok == next_token)               /*expected token and actual token match*/
    ;
    else
        syntax_error();                  /*expected token and actual token do not match*/
    next_token = scanner();             /*read next token*/
}

/***********************************************************************************************/

/*report syntax errors*/
void syntax_error()
{
    printf("syntax error in line %d\n", line_num);
    error = TRUE;
}

/***********************************************************************************************/

void printTok(token current){
    char str[20];
    switch(current){                    /*This funtion will be used to return strings to output tokens*/
        case MAIN:
            printf("MAIN\n");
            fprintf(out,"%s\n","MAIN");
            break;
        case INTLITERAL:
            printf("INTLITERAL\n");
            fprintf(out,"%s\n","INTLITERAL");
            break;
        case BEGIN:
            printf("BEGIN\n");
            fprintf(out,"%s\n","BEGIN");
            break;
        case END:
            printf("END\n");
            fprintf(out,"%s\n","END");
            break;
        case READ:
            printf("READ\n");
            fprintf(out,"%s\n","READ");
            break;
        case WRITE: 
            printf("WRITE\n");
            fprintf(out,"%s\n","WRITE");
            break;
        case PLUSOP:
            printf("PLUSOP\n");
            fprintf(out,"%s\n","PLUSOP");
            break;
        case MINUSOP:
            printf("MINUSOP\n");
            fprintf(out,"%s\n","MINUSOP");
            break;
        case ASSIGNOP:
            printf("ASSIGNOP\n");
            fprintf(out,"%s\n","ASSIGNOP");
            break;
        case LPAREN:
            printf("LPAREN\n");
            fprintf(out,"%s\n","LPAREN");
            break;
        case RPAREN:
            printf("RPAREN\n");
            fprintf(out,"%s\n","RPAREN");
            break;
        case COMMA:
            printf("COMMA\n");
            fprintf(out,"%s\n","COMMA");
            break;
        case SEMICOLON:
            printf("SEMICOLON\n");
            fprintf(out,"%s\n","SEMICOLON");
            break;
        case SCANEOF:
            printf("SCANEOF\n");
            fprintf(out,"%s\n","SCANEOF");
            break;
        case LCURL:
            printf("LCURL\n");
            fprintf(out,"%s\n","LCURL");
            break;
        case RCURL:
            printf("RCURL\n");
            fprintf(out,"%s\n","RCURL");
            break;
        case IF:
            printf("IF\n");
            fprintf(out,"%s\n","IF");
            break;
        case ELSE:
            printf("ELSE\n");
            fprintf(out,"%s\n","ELSE");
            break;
        case WHILE:
            printf("WHILE\n");
            fprintf(out,"%s\n","WHILE");
            break;
        case MULTIOP:
            printf("MULTIOP\n");
            fprintf(out,"%s\n","MULTIOP");
            break;
        case DIVOP:
            printf("DIVOP\n");
            fprintf(out,"%s\n","DIVOP");
            break;
        case LESSTHAN:
            printf("LESSTHAN\n");
            fprintf(out,"%s\n","LESSTHAN");
            break;
        case GREATTHAN:
            printf("GREATTHAN\n");
            fprintf(out,"%s\n","GREATTHAN");
            break;
        case EQUALTO:
            printf("EQUALTO\n");
            fprintf(out,"%s\n","EQUALTO");
            break;
        case LESSANDEQUAL:
            printf("LESSANDEQUAL\n");
            fprintf(out,"%s\n","LESSANDEQUAL");
            break;
        case GREATANDEQUAL:
            printf("GREATANDEQUAL\n");
            fprintf(out,"%s\n","GREATANDEQUAL");
            break;
        case NOTEQUAL:
            printf("NOTEQUAL\n");
            fprintf(out,"%s\n","NOTEQUAL");
            break;
        
    }
}

int main()
{   
    printf("Welcome to Nathaniel Fishel's Scanner and Parrser for the ExMicro language\nPlease select an option below\n");
    printf("1: Scanner\n2: Parser\n");
    int x = 0;
    scanf("%d",&x);
    switch(x){
        case 1:
        printf("\nEnter the name of the file you would like to scan\n");        /*get file name and open it*/
        char infile[25];
        scanf("%s",infile);
        fin = fopen(infile,"r");

        printf("Enter the name of the output file for the tokens\n");            /*get name and open output file*/
        char outfile[25];
        scanf("%s",outfile);
        out = fopen(outfile,"w");
        
        token current;                                                          /*Output the tokens to the output file*/
        while(current != SCANEOF){
            current = scanner(); 
            printTok(current);
            printf("\n");
        }
        break;

        case 2:
        printf("comming soon");
        break;
    }
}
