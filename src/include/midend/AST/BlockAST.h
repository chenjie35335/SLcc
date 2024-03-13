#include "BaseAST.h"
//每个SinBlock生成一个TreeNode
class BlockAST : public BaseAST {
 public:
    std::unique_ptr<BaseAST> MulBlockItem;
    void Dump() const override {
      auto BlockScope = new IdentTableNode();
      if(IdentTable->child == NULL){
      ScopeLevel++;
      BlockScope->father = IdentTable;
      BlockScope->level  = ScopeLevel;
      IdentTable->child  = BlockScope;
      }
      IdentTable = IdentTable->child;
      MulBlockItem->Dump();
      IdentTable = IdentTable->father;
      IdentTable->child = NULL;
      delete BlockScope;
}
void generateGraph(RawSlice &IR) const override;
};

class MulBlockItemAST : public BaseAST {
  public:
    vector <unique_ptr<BaseAST>> SinBlockItem;
    void Dump() const override{
      for(auto &sinBlockItem : SinBlockItem) {
        sinBlockItem->Dump();
        if(sinBlockItem->calc() == STMTAST_RET) {
            ret_cnt++;
            break;//减支
        }
      }
    }
    void generateGraph(RawSlice &IR) const override;
};
//单个block生成一个作用域
class SinBlockItemAST : public BaseAST {
  public:
    unique_ptr<BaseAST> decl;
    unique_ptr<BaseAST> stmt;
    uint32_t type;
    void Dump() const override{
      switch(type) {
        case SINBLOCKITEM_DEC: 
                decl->Dump();break;
        case SINBLOCKITEM_STM: 
                stmt->Dump();break;
        default:assert(0);
      }
    }
    [[nodiscard]] int calc() const override{
      switch(type) {
        case SINBLOCKITEM_DEC: return 0; break;
        case SINBLOCKITEM_STM: return stmt->calc(); break;//这里调用calc实际上返回的是stmt的类型值
        default: assert(0);
        }
    }
    void generateGraph(RawSlice &IR) const override;
};
