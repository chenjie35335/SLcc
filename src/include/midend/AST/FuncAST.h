#include "BaseAST.h"
#ifndef FUNCAST_STORMY
#define FUNCAST_STORMY
class FuncDefAST : public BaseAST {
 public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  std::unique_ptr<BaseAST> block;
  void Dump() const override {
    cout << "fun ";
    cout << "@" << ident << "(): ";
    func_type->Dump();
    cout << "{" << endl;
    cout << "%" << "entry:" << endl;
    block->Dump();
    cout << "}" << endl;
  }
  void Dump(int value) const override{}
  void Dump(string &sign) const override {}
  void Dump(string &sign1,string &sign2,string &sign) const override{}
  [[nodiscard]] int calc() const override{return 0;}
  void generateGraph(RawProgramme &IR) const override{}
  void generateGraph(RawSlice &IR) const override;
  void generateGraph(RawSlice &IR, string &sign) const override{}
};

class FuncTypeAST : public BaseAST {
 public:
    std::string type = std::string("int");
    void Dump() const override {
      cout << "i32" << " ";
    }
    void Dump(int value) const override{}
    void Dump(string &sign) const override {}
    void Dump(string &sign1,string &sign2,string &sign) const override{}
    [[nodiscard]] int calc() const override{return 0;}
    void generateGraph(RawProgramme &IR) const override{}
    void generateGraph(RawSlice &IR) const override{}
    void generateGraph(RawSlice &IR, string &sign) const override{}
};
#endif