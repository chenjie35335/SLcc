#include "BaseAST.h"
#ifndef LVALAST_STORMY
#define LVALAST_STORMY
class LValLAST : public BaseAST {
  public:
    string ident;
    void Dump(string &sign) const override {
      sign = ident;
    }
};

class LValRAST : public BaseAST {
  public:
    string ident;
    void Dump() const override {}
    void Dump(string &sign) const override {
      auto p = IdentTable;
      while(p != nullptr) {
      auto &ValueTable = p->ConstTable;
      auto &VarTable   = p->VarTable;
      int dep = p->level;
      //cout << "value = " << VarTable.at(ident) << endl;
      if( ValueTable.find(ident) != ValueTable.end()){
          int CalValue = ValueTable.at(ident);
          sign = to_string(CalValue);
          break;
       }
       else if(VarTable.find(ident) != VarTable.end()) {
          alloc_now++;
          sign = "%"+to_string(alloc_now);
          cout << "  "<<sign << " = " << "load " << "@"+ident+"_"+to_string(dep)<<endl;
          //is_lva = 1;
          break;
       }
       p = p->father;
      }
      //cout << 1 << endl;
       if(p == nullptr) {
         cerr << "Error: " << '"' << ident << '"' << " is not defined" << endl;
         exit(-1);
       }
    }
    int calc() const override {
      auto p           = IdentTable;
      while(p != nullptr) {
      auto &ValueTable = p->ConstTable;
      auto &VarTable   = p->VarTable;
      if (ValueTable.find(ident) != ValueTable.end())
        {
          int CalValue = ValueTable.at(ident);
          return CalValue;
        }
        else if(VarTable.find(ident) != VarTable.end()) {
          return VarTable.at(ident);
        }
        p = p->father;
      }
        if(p == nullptr)
        {
          cerr << "Error: " << '"' << ident << '"' << "is not defined" << endl;
          exit(-1);
        } 
      }
};

#endif