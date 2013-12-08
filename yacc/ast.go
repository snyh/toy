package main

import "fmt"
import "math"

type AST interface {
	Eval() float64
	Type() string
}

type ASTImpl struct {
	left     AST
	right    AST
	operator string
}

type NumberAST float64

func (v NumberAST) Eval() float64 {
	return float64(v)
}
func (v NumberAST) Type() string {
	return "K"
}

const (
	B_SQRT = iota
	B_EXP
	B_LOG
	B_PRINT
)

type BuiltInAST struct {
	fnName int
	arg    AST
}

func NewFunc(name int, value AST) AST {
	return BuiltInAST{name, value}
}

func (v BuiltInAST) Eval() float64 {
	switch v.fnName {
	case B_SQRT:
		return math.Sqrt(v.arg.Eval())
	case B_EXP:
		return math.Exp(v.arg.Eval())
	case B_LOG:
		return math.Log(v.arg.Eval())
	case B_PRINT:
		println(v.arg.Eval())
		return v.arg.Eval()
	}
	panic("Didn't support build-in type")
}

func (v BuiltInAST) Type() string { return "F" }

func NewAST(op string, left, right AST) AST {
	return &ASTImpl{left, right, op}
}

func (tree ASTImpl) Type() string { return tree.operator }

func (tree ASTImpl) Eval() float64 {
	switch tree.operator {
	case "-":
		return tree.left.Eval() - tree.right.Eval()
	case "+":
		return tree.left.Eval() + tree.right.Eval()
	case "/":
		return tree.left.Eval() / tree.right.Eval()
	case "*":
		return tree.left.Eval() * tree.right.Eval()
	case "M":
		return -tree.left.Eval()
	case "AND":
		return float64(int(tree.left.Eval()) & int(tree.right.Eval()))
	case "OR":
		return float64(int(tree.left.Eval()) | int(tree.right.Eval()))
	case "|":
		v := tree.left.Eval()
		if v > 0 {
			return v
		} else {
			return -v
		}
	case "":
		return tree.Eval()
	}
	panic(fmt.Sprintf("Didn't support operator: %v", tree))
}

func eval(tree AST) {
	fmt.Println(tree.Eval())
}
