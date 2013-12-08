package main

import "fmt"
import "math"

type Symbol struct {
	name  string
	value float64
}

var _symTable = make(map[string]*Symbol)

func Lookup(name string) *Symbol {
	if _, ok := _symTable[name]; !ok {
		_symTable[name] = &Symbol{}
	}
	return _symTable[name]
}

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

type AsignAST struct {
	name  *Symbol
	value AST
}

func (v AsignAST) Type() string { return "=" }
func (v AsignAST) Eval() float64 {
	v.name.value = v.value.Eval()
	return v.name.value
}

func NewASIGN(name *Symbol, value AST) AST {
	return &AsignAST{name, value}
}

type CallAST struct {
	fn   *Symbol
	args AST
}

func NewCall(fn *Symbol, value AST) AST {
	return CallAST{fn, value}
}

func (v CallAST) Eval() float64 {
	return 0
}
func (v CallAST) Type() string {
	return "C"
}

type SymbolAST struct {
	name *Symbol
}

func (v SymbolAST) Eval() float64 {
	return v.name.value
}
func (v SymbolAST) Type() string { return "=" }
func NewRef(sym *Symbol) AST {
	return SymbolAST{sym}
}

func NewAST(op string, left, right AST) AST {
	return &ASTImpl{left, right, op}
}

func (tree ASTImpl) Type() string { return tree.operator }

func (tree ASTImpl) Eval() float64 {
	switch tree.operator {
	case ">":
		if tree.left.Eval() > tree.right.Eval() {
			return 1
		} else {
			return 0
		}
	case "<":
		if tree.left.Eval() < tree.right.Eval() {
			return 1
		} else {
			return 0
		}
	case "!=":
		if tree.left.Eval() != tree.right.Eval() {
			return 1
		} else {
			return 0
		}
	case "==":
		if tree.left.Eval() == tree.right.Eval() {
			return 1
		} else {
			return 0
		}
	case ">=":
		if tree.left.Eval() >= tree.right.Eval() {
			return 1
		} else {
			return 0
		}
	case "<=":
		if tree.left.Eval() <= tree.right.Eval() {
			return 1
		} else {
			return 0
		}
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
	case "List":
		tree.left.Eval()
		return tree.right.Eval()
	case "":
		return tree.Eval()
	}
	panic(fmt.Sprintf("Didn't support operator: %v", tree))
}

func eval(tree AST) {
	fmt.Println(tree.Eval())
}
