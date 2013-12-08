%{
package main

import (
    "strconv"
    "bufio"
)

type yylexer struct {
    src *bufio.Reader
    buf []byte
    current byte
    value float64
}
func newLexer(src *bufio.Reader) (y *yylexer) {
    y = &yylexer{src: src}
    if b, err := src.ReadByte(); err == nil {
	y.current = b
    }
    return
}


func (y *yylexer) getc() byte {
    if y.current != 0 {
	y.buf = append(y.buf, y.current)
    }
    y.current = 0
    if b, err := y.src.ReadByte(); err == nil {
	y.current = b
    }
    return y.current
}
func (y yylexer) Error(e string) {
    panic(e)
}

func (y *yylexer) Lex(lval *yySymType) int {
    c := y.current

%}

%yyc c
%yyn c = y.getc()

NUM 0x[a-f0-9]+|[0-9]+
FLOAT [0-9]?"."[0-9]+
EXP ([Ee][-+]?[0-9]+)

%%
    y.buf = y.buf[:0]

[ \t]	

"sqrt"	lval.fn = B_SQRT; return FUNC
"exp"	lval.fn = B_EXP ; return FUNC
"log"	lval.fn = B_LOG ; return FUNC
"print"	lval.fn = B_PRINT;return FUNC

"AND"	return AND

"OR"	return OR


{NUM} 	tmp, _ := strconv.ParseInt(string(y.buf), 0, 64); lval.number = float64(tmp); return NUMBER
{FLOAT}	tmp, _ := strconv.ParseFloat(string(y.buf), 64); lval.number = float64(tmp); return NUMBER

[a-zA-Z][a-zA-Z0-9]* lval.symbol = Lookup(string(y.buf)); return NAME

\n	return EOL

"//".*	return COMMENT

.	return int(y.buf[0])


%%
	return int(c)
}
