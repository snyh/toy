%{
package main

import (
    "bufio"
    "os"
)

%}

%union {
    node AST
    number float64
    fn int
    symbol *Symbol
    operator string
}


%token EOL COMMENT LET
%token <number> NUMBER
%token <fn> FUNC 
%token <operator> CMP
%token <symbol> NAME

%type <node> exp explist

%start calclist
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


explist: exp
       | exp ',' explist { $$ = NewAST("List", $1, $3) }

exp: exp CMP exp { $$ = NewAST($2, $1, $3)  }
   | exp '+' exp { $$ = NewAST("+", $1, $3) }
   | exp '-' exp { $$ = NewAST("-", $1, $3) }
   | exp '*' exp { $$ = NewAST("*", $1, $3) }
   | exp '/' exp { $$ = NewAST("/", $1, $3) }
   | exp OR exp  { $$ = NewAST("OR", $1, $3) }
   | exp AND exp { $$ = NewAST("AND", $1, $3) }
   | '|' exp 	 { $$ = NewAST("|", $2, nil) }
   | '(' exp ')' { $$ = $2 }
   | NUMBER      { $$ = NumberAST($1) }
   | NAME 	 { $$ = NewRef($1) }
   | '-' exp %prec UMINUS { $$ = NewAST("M", $2, nil) }
   | NAME '=' exp  { $$ = NewASIGN($1, $3) }
   | FUNC '(' explist ')' { $$ = NewFunc($1, $3) }
   | NAME '(' explist ')' { $$ = NewCall($1, $3) }
   ;

%%

func main() {
    yyParse(newLexer(bufio.NewReader(os.Stdin)))
}
