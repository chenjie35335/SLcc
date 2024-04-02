#include "../../../include/midend/IR/IRGraph.h"
#include "../../../include/midend/IR/IRBuilder.h"
#include "../../../include/midend/IR/ValueKind.h"
#include "../../../include/midend/AST/ast.h"
#include "../../../include/midend/ValueTable/SignTable.h"
#include <cstdlib>
#include <unordered_map>
using namespace std;
extern IRBuilder* irBuilder;
extern SignTable signTable;

void ConstArrayDefAST::generateGraph(string &sign) const{
    //add sth.
    //Exp->generateGraph(); 
    //ident
    dimension->generateGraph();
    arrayVar->generateGraph();
    //是否需要传参
}

void ArrayDimenAST::generateGraph(string &sign) const {
    switch(type){
        case 0: 
            constExp->generateGraph(sign);
            break;
        case 1:
            constExp->generateGraph(sign);
    }
    
}

void MulArrayDimenAST::generateGraph() const{
    exp->generateGraph();
    dim->generateGraph();
}

//数组变量初始化-中端最麻烦
void ConstArrayVarAST::generateGraph() const{
    switch (type)
    {
    case 0:
        content->generateGraph();
        break;
    case 1:
        //cout<<{0}<<endl;
        break;
    default:
        break;
    }
}

void ArrayContentAST::generateGraph() const{
    switch (type)
    {
    case 0:
        var->generateGraph();
        break;
    case 1:
        var->generateGraph();
        break;
    case 2:
        var->generateGraph();
        break;
    default:
        break;
    }
    var->generateGraph();
}


void MulArrayContentAST::generateGraph() const{
    switch (type)
    {
    case 0:
        sin->generateGraph();
        mul->generateGraph();
        break;
    case 1:
        sin->generateGraph();
        mul->generateGraph();
        break;
    case 2:
        sin->generateGraph();
        mul->generateGraph();
        break;
    default:
        break;
    }
    
}


void ArrParaAST::generateGraph() const{
    exp->generateGraph();
}

void MulArrParaAST::generateGraph() const{
    exp->generateGraph();
    para->generateGraph();
}
