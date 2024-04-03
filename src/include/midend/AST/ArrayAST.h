#include "BaseAST.h"
#ifndef ARRAYAST_LXH
#define ARRAYAST_LXH

class ConstArrayInitAST : public BaseAST{
  public:
    unique_ptr<BaseAST> multiArrayElement;
    void generateGraph(string &sign) const override{}
};

class MultiArrayElementAST : public BaseAST{
  public:
    vector<unique_ptr<BaseAST>> sinArrayElement;
    void generateGraph(string &sign) const override{}
};


class SinArrayElementAST : public BaseAST {
    public:
      enum {
        ARELEM_AI,
        ARELEN_EX,
        ARELEM_NULL
      }kind;
      unique_ptr<BaseAST> constExp;
      unique_ptr<BaseAST> constArrayInit;
      int type;
      void generateGraph(string &sign) const override{}
};
class ArrayDimenAST : public BaseAST {
  public:
    vector<unique_ptr<BaseAST>> sinArrayDimen;
    void generateGraph(string &sign) const override{}
};

class SinArrayDimenAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> exp;
    void generateGraph() const override{}
};

class ConstArrayAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> content;
    int type;
    void generateGraph() const override{}
};

//arra para
class ArrParaAST : public BaseAST {
  public:
    vector<unique_ptr<BaseAST>> sinArrPara;
    void generateGraph() const override{}
};

class SinArrParaAST : public BaseAST {
  public:
    std::unique_ptr<BaseAST> exp;
    void generateGraph() const override{}
};

class ParaTypeAST : public BaseAST {
  public:
    int type;
    void generateGraph() const override {}
};

#endif

