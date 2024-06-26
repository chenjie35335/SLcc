#include "../../../include/midend/IR/Function.h"
#include "../../../include/midend/IR/BasicBlock.h"
#include "../../../include/midend/SSA/PHI.h"
#include "../../../include/midend/IR/Programme.h"
#include <assert.h>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
using namespace std;
//这里需要考虑的是，如果我使用的是基本块常量的话，该如何处理
void AddPhi(RawBasicBlock *&bb,RawValue *&data) {
    auto &params = bb->params;
    RawValue *blockarg = new RawValue();
    blockarg->value.tag = RVT_BLOCK_ARGS;
    blockarg->value.data.blockArgs.target = data;
    params.buffer[params.len++] = blockarg;
    blockarg->value.data.blockArgs.index = params.len;
}

// 这里该怎么处理这个defsite集合？
// 首先使用hash表那样弄不一定是一件好事
void AddPhi(RawFunction *& func) {
    auto &bbs = func->bbs;
    auto &values = func->values;
    for(int i = 0; i < bbs.len;i++) {
        RawBasicBlock *bb = (RawBasicBlock *)bbs.buffer[i];
        auto &bbDef = bb->defs;
        for(RawValue* value : bbDef) {
            value->defbbs.insert(bb);
            values.insert(value);
        }
    }
    for(RawValue *value : values) {
        vector<RawBasicBlock *> W;
        copy(value->defbbs.begin(),value->defbbs.end(),W.begin());
        while(!W.empty()) {
            RawBasicBlock *n = W[W.size()-1];
            W.pop_back();
            //computeDF(n);
            for(const RawBasicBlock *Y : n->df) {
                RawBasicBlock* y = (RawBasicBlock *) Y;
                if(y->NessPhi.find(value) == y->NessPhi.end()) {
                    AddPhi(y,value);
                    RawValueP phiValue = (RawValueP) value;
                    y->NessPhi.insert(phiValue);
                    if(phiValue->defbbs.find(y) == phiValue->defbbs.end()) {
                        W.push_back(y);
                    }
                }
            }
        }
    }
}

void AddPhi(RawProgramme *& programme) {
    auto &funcs = programme->Funcs;
    for(int i = 0; i < funcs.len;i++) {
        RawFunction* func = (RawFunction *)funcs.buffer[i];
        AddPhi(func);
    }
}