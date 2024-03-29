#include "../../../include/midend/ValueTable/SignTable.h"

SignTable signTable;
int alloc_now = -1;

void SignTable::insertFunction(const string &name, RawFunction *&function){
    this->FuncTable.insert(pair<string,RawFunction*>(name,function));
}

void SignTable::identForward(){
    if(this->IdentTable->child == nullptr) {
    auto child = new IdentTableNode(this->IdentTable,tempScope);
    this->IdentTable->child = child;
    }
    this->IdentTable = this->IdentTable->child;
}

void SignTable::identBackward(){
    this->IdentTable = this->IdentTable->father;
}

void SignTable::deleteBackward() {
    this->IdentTable = this->IdentTable->father;
    delete this->IdentTable->child;
    this->IdentTable->child = nullptr;
}

RawValue * SignTable::getMidVar(string &name) {
    assert(MidVarTable.find(name) != MidVarTable.end());
    return MidVarTable.at(name);
}

void SignTable::insertMidVar(string &name, RawValue* &value){
    MidVarTable.insert(pair<string,RawValue *>(name,value));
}

RawValue * SignTable::getVarL(string &name){
    return IdentTable->SearchVarL(name);
}

RawValue * IdentTableNode::SearchVarL(string &name){
    if(findValue(name)) {
        cerr << '"' << name << '"' << "is a constant and can't be altered" << endl;
        assert(0);
    } else if(findVariable(name)) {
        return this->VarTable.at(name);
    } else if(this->father == nullptr){
        cerr << "Error: " << '"' << name << '"' << " is not defined" << endl;
        assert(0);
    } else {
        return this->father->SearchVarL(name);
    }
}

RawValue *SignTable::getVarR(const string &name) {
    return IdentTable->SearchVarR(name);
}

RawValue * IdentTableNode::SearchVarR(const string &name){
    if(findValue(name)){
        int value = ConstTable.at(name);
        string svalue = to_string(value);
        generateRawValue(value);
        return signTable.getMidVar(svalue);
    }
    else if(findVariable(name)) {
        return this->VarTable.at(name);
    } else if(this->father == nullptr){
        cerr << "Error: " << '"' << name << '"' << " is not defined" << endl;
        assert(0);
    } else {
        return this->father->SearchVarR(name);
    }
}

void SignTable::insertVar(const string &name, RawValue *&value){
    IdentTable->insertVar(name,value);
}

void SignTable::insertNumber(int number,RawValue *&value){
    if(MidVarTable.find(to_string(number)) != MidVarTable.end()){
        MidVarTable[to_string(number)] = value;
    } else {
        MidVarTable.insert(pair<string,RawValue*>(to_string(number),value));
    }
}
//既要考虑ident被重复定义，也要考虑其被定义为变量
void SignTable::constMulDef(const string &ident) {
    if(IdentTable->findValue(ident) || IdentTable->findVariable(ident)) {
        cerr << '"' << ident << '"' << "redefined." << endl;
        assert(0);
    }
}

void SignTable::varMultDef(const string &ident) {
    if(IdentTable->findValue(ident)) {
        cerr << '"' << ident << '"' << " has been defined as constant" << endl;
        assert(0);
    } else if(IdentTable->findVariable(ident)){
        cerr << '"' << ident << '"' << " redefined." << endl;
        assert(0);
    }
}

void SignTable::insertConst(const string &ident,int value){
    IdentTable->insertValue(ident,value);
}

RawFunction *SignTable::getFunction(const string &ident) {
    assert(FuncTable.find(ident) != FuncTable.end());
    return FuncTable.at(ident);
}
