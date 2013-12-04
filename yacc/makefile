all:
	go tool yacc a.y && golex a.l && gofmt -w *.go && go build -compiler gccgo -o a
	cat test | ./a

clean:
	rm lex.yy.go y.go a y.output
