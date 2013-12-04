%{
package main

import (
    "bufio"
    "fmt"
    "os"
)

%}

%union {
    value AST
    number float64
}


%token NUMBER EOL OP CP COMMENT AND OR

%type <value> exp 
%type <number> NUMBER

%left OR
%left AND
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%%


calclist:
	| calclist COMMENT
	| calclist EOL
	| calclist exp { eval($2) }
	;

exp: exp '+' exp { $$ = NewAST("+", $1, $3) }
   | exp '-' exp { $$ = NewAST("-", $1, $3) }
   | exp '*' exp { $$ = NewAST("*", $1, $3) }
   | exp '/' exp { $$ = NewAST("/", $1, $3) }
   | exp OR exp  { $$ = NewAST("OR", $1, $3) }
   | exp AND exp { $$ = NewAST("AND", $1, $3) }
   | '|' exp 	 { $$ = NewAST("|", $2, nil) }
   | '(' exp ')' { $$ = $2 }
   | NUMBER      { $$ = NumberAST($1) }
   | '-' exp %prec UMINUS { $$ = NewAST("M", $2, nil) }
   ;

%%

func main() {
    yyParse(newLexer(bufio.NewReader(os.Stdin)))
}
