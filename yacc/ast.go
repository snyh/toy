package main

import "fmt"

type AST interface {
	Eval() float64
	IsNumber() bool
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
func (v NumberAST) IsNumber() bool {
	return true
}

func NewAST(op string, left, right AST) AST {
	return &ASTImpl{left, right, op}
}

func (tree ASTImpl) IsNumber() bool { return false }

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
