#include "include/common.h"
using namespace std;

extern FILE *yyin;
extern int yyparse(unique_ptr<BaseAST> &ast);
extern void backend(RawProgramme *& programme);

int main(int argc, const char *argv[]) {
  // 解析命令行参数. 测试脚本/评测平台要求你的编译器能接收如下参数:
  // compiler 模式 输入文件 -o 输出文件
  assert(argc == 5 || argc == 6);
  auto mode = argv[1];
  auto input = argv[2];
  auto OutMode = argv[3];
  auto output = argv[4];
  auto optMode = (argc == 6) ? argv[5]:nullptr;
  assert(strcmp(OutMode,"-o") == 0);

  // 打开输入文件, 并且指定 lexer 在解析的时候读取这个文件
  yyin = fopen(input, "r");
  assert(yyin);

  // 调用 parser 函数, parser 函数会进一步调用 lexer 解析输入文件的
  unique_ptr<BaseAST> ast;
  auto ret = yyparse(ast);
  assert(!ret);
  freopen(output,"w",stdout);
  // 输出解析得到的 AST, 其实就是个字符串
  //生成后端代码
  // if(strcmp(mode,"-riscv") == 0){
      // RawProgramme* irGraph;
      // ast->generateGraph(irGraph);
      // backend(irGraph);
  // }
  // else if (strcmp(mode,"-koopa") == 0)
  // {
    // RawProgramme* irGraph;
    // ast->generateGraph(irGraph);
    // GeneratorIRTxt(irGraph);
  // }
  // else if (strcmp(mode,"-dt")==0)
  // {
    // RawProgramme* irGraph;
    // ast->generateGraph(irGraph);
    // GeneratorDT(irGraph->Funcs);
  // }
  RawProgramme *irGraph;
  ast->generateGraph(irGraph);
  if(strcmp(mode,"-riscv") == 0) {
    if(optMode != nullptr && strcmp(optMode,"-O1") == 0) {
      GeneratorDT(irGraph->Funcs);
      AddPhi(irGraph);
    }
    else backend(irGraph);
  } 
  else if(strcmp(mode,"-koopa") == 0) {
    GeneratorIRTxt(irGraph);
  }
  return 0;
}