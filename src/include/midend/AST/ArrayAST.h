#include "BaseAST.h"
#ifndef ARRAYAST_LXH
#define ARRAYAST_LXH

class ConstArrayDefAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> dimension;
    std::unique_ptr<BaseAST> arrayVar;
    string ident;
    void generateGraph(string &sign) const override;
    
};


class ArrayDimenAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> constExp;
    int type;
    void generateGraph(string &sign) const override;
};

class MulArrayDimenAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> exp;
    std::unique_ptr<BaseAST> dim;
    void generateGraph() const override;
};

class ConstArrayVarAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> content;
    int type;
    void generateGraph() const override;
};

class ArrayContentAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> var;
    int type;
    //three situation
    void generateGraph() const override;

};

class MulArrayContentAST : public BaseAST {
  public: 
    std::unique_ptr<BaseAST> sin;
    std::unique_ptr<BaseAST> mul;
    int type;
    void generateGraph() const override;
};



//arra para
class ArrParaAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> exp;
    int type;
    void generateGraph() const override;
};

class MulArrParaAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> exp;
    std::unique_ptr<BaseAST> para;
    void generateGraph() const override;
};

#endif



//1. int a[100];
//a[100] = {0};
//define a[exp]  b[var]
//2. 2nd dimension
// a[1][5] define;
//3.  global array define
// int // const int 
//way:
//4. giving value to the array: 
// {1,2,3,}
// auto fill it with 0
//5. 2nd dimension array giving value
//using it in global