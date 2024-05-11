#include "ast2llvm.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>
#include <list>
#include <iostream>

using namespace std;
using namespace LLVMIR;

static unordered_map<string,FuncType> funcReturnMap;
static unordered_map<string,StructInfo> structInfoMap;
static unordered_map<string,Name_name*> globalVarMap;
static unordered_map<string,Temp_temp*> localVarMap;
static list<L_stm*> emit_irs;

LLVMIR::L_prog* ast2llvm(aA_program p)
{
    auto defs = ast2llvmProg_first(p);
    auto funcs = ast2llvmProg_second(p);
    vector<L_func*> funcs_block;
    for(const auto &f : funcs)
    {
        funcs_block.push_back(ast2llvmFuncBlock(f));
    }
    for(auto &f : funcs_block)
    {
        ast2llvm_moveAlloca(f);
    }
    return new L_prog(defs,funcs_block);
}

int ast2llvmRightVal_first(aA_rightVal r)
{
    if(r == nullptr)
    {
        return 0;
    }
    switch (r->kind)
    {
    case A_arithExprValKind:
    {
        return ast2llvmArithExpr_first(r->u.arithExpr);
        break;
    }
    case A_boolExprValKind:
    {
        return ast2llvmBoolExpr_first(r->u.boolExpr);
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmBoolExpr_first(aA_boolExpr b)
{
    switch (b->kind)
    {
    case A_boolBiOpExprKind:
    {
        return ast2llvmBoolBiOpExpr_first(b->u.boolBiOpExpr);
        break;
    }
    case A_boolUnitKind:
    {
        return ast2llvmBoolUnit_first(b->u.boolUnit);
        break;
    }
    default:
         break;
    }
    return 0;
}

int ast2llvmBoolBiOpExpr_first(aA_boolBiOpExpr b)
{
    int l = ast2llvmBoolExpr_first(b->left);
    int r = ast2llvmBoolExpr_first(b->right);
    if(b->op == A_and)
    {
        return l && r;
    }
    else
    {
        return l || r;
    }
}

int ast2llvmBoolUOpExpr_first(aA_boolUOpExpr b)
{
    if(b->op == A_not)
    {
        return !ast2llvmBoolUnit_first(b->cond);
    }
    return 0;
}

int ast2llvmBoolUnit_first(aA_boolUnit b)
{
    switch (b->kind)
    {
    case A_comOpExprKind:
    {
        return ast2llvmComOpExpr_first(b->u.comExpr);
        break;
    }
    case A_boolExprKind:
    {
        return ast2llvmBoolExpr_first(b->u.boolExpr);
        break;
    }
    case A_boolUOpExprKind:
    {
        return ast2llvmBoolUOpExpr_first(b->u.boolUOpExpr);
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmComOpExpr_first(aA_comExpr c)
{
    auto l = ast2llvmExprUnit_first(c->left);
    auto r = ast2llvmExprUnit_first(c->right);
    switch (c->op)
    {
    case A_lt:
    {
        return l < r;
        break;
    }
    case A_le:
    {
        return l <= r;
        break;
    }
    case A_gt:
    {
        return l > r;
        break;
    }
    case A_ge:
    {
        return l >= r;
        break;
    }
    case A_eq:
    {
        return l == r;
        break;
    }
    case A_ne:
    {
        return l != r;
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmArithBiOpExpr_first(aA_arithBiOpExpr a)
{
    auto l= ast2llvmArithExpr_first(a->left);
    auto r = ast2llvmArithExpr_first(a->right);
    switch (a->op)
    {
    case A_add:
    {
        return l + r;
        break;
    }
    case A_sub:
    {
        return l - r;
        break;
    }
    case A_mul:
    {
        return l * r;
        break;
    }
    case A_div:
    {
        return l / r;
        break;
    }
    default:
        break;
    }
    return 0;
}

int ast2llvmArithUExpr_first(aA_arithUExpr a)
{
    if(a->op == A_neg)
    {
        return -ast2llvmExprUnit_first(a->expr);
    }
    return 0;
}

int ast2llvmArithExpr_first(aA_arithExpr a)
{
    switch (a->kind)
    {
    case A_arithBiOpExprKind:
    {
        return ast2llvmArithBiOpExpr_first(a->u.arithBiOpExpr);
        break;
    }
    case A_exprUnitKind:
    {
        return ast2llvmExprUnit_first(a->u.exprUnit);
        break;
    }
    default:
        assert(0);
        break;
    }
    return 0;
}

int ast2llvmExprUnit_first(aA_exprUnit e)
{
    if(e->kind == A_numExprKind)
    {
        return e->u.num;
    }
    else if(e->kind == A_arithExprKind)
    {
        return ast2llvmArithExpr_first(e->u.arithExpr);
    }
    else if(e->kind == A_arithUExprKind)
    {
        return ast2llvmArithUExpr_first(e->u.arithUExpr);
    }
    else
    {
        assert(0);
    }
    return 0;
}

std::vector<LLVMIR::L_def*> ast2llvmProg_first(aA_program p)
{
    vector<L_def*> defs;
    defs.push_back(L_Funcdecl("getch",vector<TempDef>(),FuncType(ReturnType::INT_TYPE)));
    defs.push_back(L_Funcdecl("getint",vector<TempDef>(),FuncType(ReturnType::INT_TYPE)));
    defs.push_back(L_Funcdecl("putch",vector<TempDef>{TempDef(TempType::INT_TEMP)},FuncType(ReturnType::VOID_TYPE)));
    defs.push_back(L_Funcdecl("putint",vector<TempDef>{TempDef(TempType::INT_TEMP)},FuncType(ReturnType::VOID_TYPE)));
    defs.push_back(L_Funcdecl("putarray",vector<TempDef>{TempDef(TempType::INT_TEMP),TempDef(TempType::INT_PTR,-1)},FuncType(ReturnType::VOID_TYPE)));
    defs.push_back(L_Funcdecl("_sysy_starttime",vector<TempDef>{TempDef(TempType::INT_TEMP)},FuncType(ReturnType::VOID_TYPE)));
    defs.push_back(L_Funcdecl("_sysy_stoptime",vector<TempDef>{TempDef(TempType::INT_TEMP)},FuncType(ReturnType::VOID_TYPE)));
    for(const auto &v : p->programElements)
    {
        switch (v->kind)
        {
        case A_programNullStmtKind:
        {
            break;
        }
        case A_programVarDeclStmtKind:
        {
            if(v->u.varDeclStmt->kind == A_varDeclKind)
            {
                if(v->u.varDeclStmt->u.varDecl->kind == A_varDeclScalarKind)
                {
                    if(v->u.varDeclStmt->u.varDecl->u.declScalar->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declScalar->id,
                            Name_newname_struct(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declScalar->id),*v->u.varDeclStmt->u.varDecl->u.declScalar->type->u.structType));
                        TempDef def(TempType::STRUCT_TEMP,0,*v->u.varDeclStmt->u.varDecl->u.declScalar->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declScalar->id,def,vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declScalar->id,
                            Name_newname_int(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declScalar->id)));
                        TempDef def(TempType::INT_TEMP,0);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declScalar->id,def,vector<int>()));
                    }
                }
                else if(v->u.varDeclStmt->u.varDecl->kind == A_varDeclArrayKind)
                {
                    if(v->u.varDeclStmt->u.varDecl->u.declArray->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declArray->id,
                            Name_newname_struct_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declArray->id),v->u.varDeclStmt->u.varDecl->u.declArray->len,*v->u.varDeclStmt->u.varDecl->u.declArray->type->u.structType));
                        TempDef def(TempType::STRUCT_PTR,v->u.varDeclStmt->u.varDecl->u.declArray->len,*v->u.varDeclStmt->u.varDecl->u.declArray->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declArray->id,def,vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDecl->u.declArray->id,
                            Name_newname_int_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDecl->u.declArray->id),v->u.varDeclStmt->u.varDecl->u.declArray->len));
                        TempDef def(TempType::INT_PTR,v->u.varDeclStmt->u.varDecl->u.declArray->len);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declArray->id,def,vector<int>()));
                    }
                }
                else
                {
                    assert(0);
                }
            }
            else if(v->u.varDeclStmt->kind == A_varDefKind)
            {
                if(v->u.varDeclStmt->u.varDef->kind == A_varDefScalarKind)
                {
                    if(v->u.varDeclStmt->u.varDef->u.defScalar->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defScalar->id,
                            Name_newname_struct(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defScalar->id),*v->u.varDeclStmt->u.varDef->u.defScalar->type->u.structType));
                        TempDef def(TempType::STRUCT_TEMP,0,*v->u.varDeclStmt->u.varDef->u.defScalar->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defScalar->id,def,vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defScalar->id,
                            Name_newname_int(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defScalar->id)));
                        TempDef def(TempType::INT_TEMP,0);
                        vector<int> init;
                        init.push_back(ast2llvmRightVal_first(v->u.varDeclStmt->u.varDef->u.defScalar->val));
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defScalar->id,def,init));
                    }
                }
                else if(v->u.varDeclStmt->u.varDef->kind == A_varDefArrayKind)
                {
                    if(v->u.varDeclStmt->u.varDef->u.defArray->type->type == A_structTypeKind)
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defArray->id,
                            Name_newname_struct_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defArray->id),v->u.varDeclStmt->u.varDef->u.defArray->len,*v->u.varDeclStmt->u.varDef->u.defArray->type->u.structType));
                        TempDef def(TempType::STRUCT_PTR,v->u.varDeclStmt->u.varDef->u.defArray->len,*v->u.varDeclStmt->u.varDef->u.defArray->type->u.structType);
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defArray->id,def,vector<int>()));
                    }
                    else
                    {
                        globalVarMap.emplace(*v->u.varDeclStmt->u.varDef->u.defArray->id,
                            Name_newname_int_ptr(Temp_newlabel_named(*v->u.varDeclStmt->u.varDef->u.defArray->id),v->u.varDeclStmt->u.varDef->u.defArray->len));
                        TempDef def(TempType::INT_PTR,v->u.varDeclStmt->u.varDef->u.defArray->len);
                        vector<int> init;
                        for(auto &el : v->u.varDeclStmt->u.varDef->u.defArray->vals)
                        {
                            init.push_back(ast2llvmRightVal_first(el));
                        }
                        defs.push_back(L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defArray->id,def,init));
                    }
                }
                else
                {
                    assert(0);
                }
            }
            else
            {
                assert(0);
            }
            break;
        }
        case A_programStructDefKind:
        {
            StructInfo si;
            int off = 0;
            vector<TempDef> members;
            for(const auto &decl : v->u.structDef->varDecls)
            {
                if(decl->kind == A_varDeclScalarKind)
                {
                    if(decl->u.declScalar->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_TEMP,0,*decl->u.declScalar->type->u.structType);
                        MemberInfo info(off++,def);
                        si.memberinfos.emplace(*decl->u.declScalar->id,info);
                        members.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_TEMP,0);
                        MemberInfo info(off++,def);
                        si.memberinfos.emplace(*decl->u.declScalar->id,info);
                        members.push_back(def);
                    }
                }
                else if(decl->kind == A_varDeclArrayKind)
                {
                    if(decl->u.declArray->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_PTR,decl->u.declArray->len,*decl->u.declArray->type->u.structType);
                        MemberInfo info(off++,def);
                        si.memberinfos.emplace(*decl->u.declArray->id,info);
                        members.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_PTR,decl->u.declArray->len);
                        MemberInfo info(off++,def);
                        si.memberinfos.emplace(*decl->u.declArray->id,info);
                        members.push_back(def);
                    }
                }
                else
                {
                    assert(0);
                }
            }
            structInfoMap.emplace(*v->u.structDef->id,std::move(si));
            defs.push_back(L_Structdef(*v->u.structDef->id,members));
            break;
        }
        case A_programFnDeclStmtKind:
        {
            FuncType type;
            if(v->u.fnDeclStmt->fnDecl->type == nullptr)
            {
                type.type = ReturnType::VOID_TYPE;
            }
            if(v->u.fnDeclStmt->fnDecl->type->type == A_nativeTypeKind)
            {
                type.type = ReturnType::INT_TYPE;
            }
            else if(v->u.fnDeclStmt->fnDecl->type->type == A_structTypeKind)
            {
                type.type = ReturnType::STRUCT_TYPE;
                type.structname = *v->u.fnDeclStmt->fnDecl->type->u.structType;
            }
            else
            {
                assert(0);
            }
            if(funcReturnMap.find(*v->u.fnDeclStmt->fnDecl->id) == funcReturnMap.end())
                funcReturnMap.emplace(*v->u.fnDeclStmt->fnDecl->id,std::move(type));
            vector<TempDef> args;
            for(const auto & decl : v->u.fnDeclStmt->fnDecl->paramDecl->varDecls)
            {
                if(decl->kind == A_varDeclScalarKind)
                {
                    if(decl->u.declScalar->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_PTR,0,*decl->u.declScalar->type->u.structType);
                        args.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_TEMP,0);
                        args.push_back(def);
                    }
                }
                else if(decl->kind == A_varDeclArrayKind)
                {
                    if(decl->u.declArray->type->type == A_structTypeKind)
                    {
                        TempDef def(TempType::STRUCT_PTR,-1,*decl->u.declArray->type->u.structType);
                        args.push_back(def);
                    }
                    else
                    {
                        TempDef def(TempType::INT_PTR,-1);
                        args.push_back(def);
                    }
                }
                else
                {
                    assert(0);
                }
            }
            defs.push_back(L_Funcdecl(*v->u.fnDeclStmt->fnDecl->id,args,type));
            break;
        }
        case A_programFnDefKind:
        {
            if(funcReturnMap.find(*v->u.fnDef->fnDecl->id) == funcReturnMap.end())
            {
                FuncType type;
                if(v->u.fnDef->fnDecl->type == nullptr)
                {
                    type.type = ReturnType::VOID_TYPE;
                }
                else if(v->u.fnDef->fnDecl->type->type == A_nativeTypeKind)
                {
                    type.type = ReturnType::INT_TYPE;
                }
                else if(v->u.fnDef->fnDecl->type->type == A_structTypeKind)
                {
                    type.type = ReturnType::STRUCT_TYPE;
                    type.structname = *v->u.fnDef->fnDecl->type->u.structType;
                }
                else
                {
                    assert(0);
                }
                funcReturnMap.emplace(*v->u.fnDef->fnDecl->id,std::move(type));
            }
            break;
        }
        default:
            assert(0);
            break;
        }
    }
    return defs;
}

std::vector<Func_local*> ast2llvmProg_second(aA_program p)
{
    vector<Func_local*> func_local;
    for(const auto &v : p->programElements){
        switch (v->kind)
        {
            case A_programFnDefKind:
            {
                Func_local* f = ast2llvmFunc(v->u.fnDef);
                func_local.push_back(f);
                break;
            }
            default:
            {
                break;
            }
        }
    }
    return func_local;
}

Func_local* ast2llvmFunc(aA_fnDef f)
{
    string name = f->fnDecl->id[0];
    FuncType ret = funcReturnMap[name];
    std::vector<Temp_temp*> args;

    for(const auto & decl : f->fnDecl->paramDecl->varDecls)
    {
        
        if(decl->kind == A_varDeclScalarKind)
        {
            if(decl->u.declScalar->type->type == A_structTypeKind)
            {
                auto temp = Temp_newtemp_struct_ptr(0, decl->u.declScalar->type->u.structType[0]);
                args.push_back(temp);
                localVarMap.emplace(decl->u.declScalar->id[0], temp);
            }
            else
            {
                auto temp = Temp_newtemp_int();
                args.push_back(temp);
                localVarMap.emplace(decl->u.declScalar->id[0], temp);
            }
        }
        else if(decl->kind == A_varDeclArrayKind)
        {
            if(decl->u.declArray->type->type == A_structTypeKind)
            {
                auto temp = Temp_newtemp_struct_ptr(-1, decl->u.declArray->type->u.structType[0]);
                args.push_back(temp);
                localVarMap.emplace(decl->u.declArray->id[0], temp);
            }
            else
            {
                auto temp = Temp_newtemp_int_ptr(-1);
                args.push_back(temp);
                localVarMap.emplace(decl->u.declArray->id[0], temp);
            }
        }
        else
        {
            assert(0);
        }
    }
    emit_irs.push_back(L_Label(Temp_newlabel()));
    for(auto cs : f->stmts) {
        ast2llvmBlock(cs);
    }

    std::list<LLVMIR::L_stm*> irs(emit_irs);
    emit_irs.clear();
    localVarMap.clear();
    return new Func_local(name, ret, args, irs);
}

void ast2llvmBlock(aA_codeBlockStmt b,Temp_label *con_label,Temp_label *bre_label)
{
    switch (b->kind)
    {
        case A_codeBlockStmtType::A_varDeclStmtKind:
        {
            if(b->u.varDeclStmt->kind == A_varDeclKind)
            {
                if(b->u.varDeclStmt->u.varDecl->kind == A_varDeclScalarKind)
                {
                    if(b->u.varDeclStmt->u.varDecl->u.declScalar->type->type == A_structTypeKind)
                    {
                        auto temp = Temp_newtemp_struct_ptr(0, b->u.varDeclStmt->u.varDecl->u.declScalar->type->u.structType[0]);
                        localVarMap.emplace(b->u.varDeclStmt->u.varDecl->u.declScalar->id[0], temp);
                        AS_operand* tempOperand = AS_Operand_Temp(temp);
                        auto alloca = L_Alloca(tempOperand);
                        emit_irs.push_back(alloca);
                    }
                    else
                    {
                        auto temp = Temp_newtemp_int_ptr(0);
                        localVarMap.emplace(b->u.varDeclStmt->u.varDecl->u.declScalar->id[0], temp);
                        AS_operand* tempOperand = AS_Operand_Temp(temp);
                        auto alloca = L_Alloca(tempOperand);
                        emit_irs.push_back(alloca);
                    }
                }
                else if(b->u.varDeclStmt->u.varDecl->kind == A_varDeclArrayKind)
                {
                    if(b->u.varDeclStmt->u.varDecl->u.declArray->type->type == A_structTypeKind)
                    {
                        auto temp = Temp_newtemp_struct_ptr(b->u.varDeclStmt->u.varDecl->u.declArray->len, b->u.varDeclStmt->u.varDecl->u.declArray->type->u.structType[0]);
                        localVarMap.emplace(b->u.varDeclStmt->u.varDecl->u.declArray->id[0], temp);
                        AS_operand* tempOperand = AS_Operand_Temp(temp);
                        auto alloca = L_Alloca(tempOperand);
                        emit_irs.push_back(alloca);
                    }
                    else
                    {
                        auto temp = Temp_newtemp_int_ptr(b->u.varDeclStmt->u.varDecl->u.declArray->len);
                        localVarMap.emplace(b->u.varDeclStmt->u.varDecl->u.declArray->id[0], temp);
                        AS_operand* tempOperand = AS_Operand_Temp(temp);
                        auto alloca = L_Alloca(tempOperand);
                        emit_irs.push_back(alloca);
                    }
                }
                else
                {
                    assert(0);
                }
            }
            else if(b->u.varDeclStmt->kind == A_varDefKind)
            {
                if(b->u.varDeclStmt->u.varDef->kind == A_varDefScalarKind)
                {
                    if(b->u.varDeclStmt->u.varDef->u.defScalar->type->type == A_structTypeKind)
                    {
                        auto temp = Temp_newtemp_struct_ptr(0, b->u.varDeclStmt->u.varDef->u.defScalar->type->u.structType[0]);
                        localVarMap.emplace(b->u.varDeclStmt->u.varDef->u.defScalar->id[0], temp);
                        AS_operand* tempOperand = AS_Operand_Temp(temp);
                        auto alloca = L_Alloca(tempOperand);
                        emit_irs.push_back(alloca);
                    }
                    else
                    {
                        auto temp = Temp_newtemp_int_ptr(0);
                        localVarMap.emplace(b->u.varDeclStmt->u.varDef->u.defScalar->id[0], temp);
                        AS_operand* tempOperand = AS_Operand_Temp(temp);
                        auto alloca = L_Alloca(tempOperand);
                        emit_irs.push_back(alloca);
                        AS_operand* rightVal = ast2llvmRightVal(b->u.varDeclStmt->u.varDef->u.defScalar->val);
                        emit_irs.push_back(L_Store(rightVal, tempOperand));
                    }
                }
                else if(b->u.varDeclStmt->u.varDef->kind == A_varDefArrayKind)
                {
                    if(b->u.varDeclStmt->u.varDef->u.defArray->type->type == A_structTypeKind)
                    {
                        auto temp = Temp_newtemp_struct_ptr(b->u.varDeclStmt->u.varDef->u.defArray->len, b->u.varDeclStmt->u.varDef->u.defArray->type->u.structType[0]);
                        localVarMap.emplace(b->u.varDeclStmt->u.varDecl->u.declArray->id[0], temp);
                        AS_operand* tempOperand = AS_Operand_Temp(temp);
                        emit_irs.push_back(L_Alloca(tempOperand));
                    }
                    else
                    {
                        auto temp = Temp_newtemp_int_ptr(b->u.varDeclStmt->u.varDef->u.defArray->len);
                        localVarMap.emplace(b->u.varDeclStmt->u.varDecl->u.declArray->id[0], temp);
                        AS_operand* tempOperand = AS_Operand_Temp(temp);
                        emit_irs.push_back(L_Alloca(tempOperand));

                        for(int i = 0; i < b->u.varDeclStmt->u.varDef->u.defArray->vals.size(); i++) {
                            aA_rightVal rightVal = b->u.varDeclStmt->u.varDef->u.defArray->vals[i];
                            AS_operand* newptr = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
                            emit_irs.push_back(L_Gep(newptr, tempOperand, AS_Operand_Const(i)));
                            AS_operand* rightOperand = ast2llvmRightVal(rightVal);
                            emit_irs.push_back(L_Store(rightOperand, newptr));
                        }
                    }
                }
                else
                {
                    assert(0);
                }
            }
            else
            {
                assert(0);
            }
            break;
        }
        case A_codeBlockStmtType::A_assignStmtKind:
        {
            AS_operand* leftVal = ast2llvmLeftVal(b->u.assignStmt->leftVal);
            AS_operand* rightVal = ast2llvmRightVal(b->u.assignStmt->rightVal);
            emit_irs.push_back(L_Store(rightVal, leftVal));
            break;
        }
        case A_codeBlockStmtType::A_callStmtKind:
        {
            string name = b->u.callStmt->fnCall->fn[0];
            vector<AS_operand*> args;
            for(auto val : b->u.callStmt->fnCall->vals) {
                auto rightVal = ast2llvmRightVal(val);
                args.push_back(rightVal);
            }
            emit_irs.push_back(L_Voidcall(name, args));
            break;
        }
        case A_codeBlockStmtType::A_nullStmtKind:
        {
            break;
        }
        case A_codeBlockStmtType::A_ifStmtKind:
        {
            auto ifstmt = b->u.ifStmt->ifStmts;
            auto elsestmt = b->u.ifStmt->elseStmts;
            auto boolstmt = b->u.ifStmt->boolExpr;
            auto if_label = Temp_newlabel();
            auto else_label = Temp_newlabel();
            auto next_label = Temp_newlabel();
            
            ast2llvmBoolExpr(boolstmt, if_label, else_label);
            
            emit_irs.push_back(L_Label(if_label));
            for(auto stmt : ifstmt) {
                ast2llvmBlock(stmt);
            }
            emit_irs.push_back(L_Jump(next_label));

            emit_irs.push_back(L_Label(else_label));
            for(auto stmt : elsestmt) {
                ast2llvmBlock(stmt);
            }
            emit_irs.push_back(L_Jump(next_label));

            emit_irs.push_back(L_Label(next_label));
            break;
        }
        case A_codeBlockStmtType::A_whileStmtKind:
        {
            auto continue_label = Temp_newlabel();
            auto true_label = Temp_newlabel();
            auto break_label = Temp_newlabel();
            emit_irs.push_back(L_Jump(continue_label));

            emit_irs.push_back(L_Label(continue_label));
            ast2llvmBoolExpr(b->u.whileStmt->boolExpr, true_label, break_label);

            emit_irs.push_back(L_Label(true_label));
            for(auto stmt : b->u.whileStmt->whileStmts) {
                ast2llvmBlock(stmt, continue_label, break_label);
            }
            emit_irs.push_back(L_Jump(continue_label));
            emit_irs.push_back(L_Label(break_label));
            break;
        }
        case A_codeBlockStmtType::A_returnStmtKind:
        {
            if(b->u.returnStmt->retVal == nullptr) {
                emit_irs.push_back(L_Ret(nullptr));
            } else {
                auto rightVal = ast2llvmRightVal(b->u.returnStmt->retVal);
                emit_irs.push_back(L_Ret(rightVal));
            }
            break;
        }
        case A_codeBlockStmtType::A_breakStmtKind:
        {
            emit_irs.push_back(L_Jump(bre_label));
            break;
        }
        case A_codeBlockStmtType::A_continueStmtKind:
        {
            emit_irs.push_back(L_Jump(con_label));
            break;
        }
        default:
        {
            break;
        }
    }
}

AS_operand* ast2llvmRightVal(aA_rightVal r)
{
    switch (r->kind)
    {
        case A_rightValType::A_arithExprValKind:
        {
            return ast2llvmArithExpr(r->u.arithExpr);
            break;
        }
        case A_rightValType::A_boolExprValKind:
        {
            auto true_label = Temp_newlabel();
            auto false_label = Temp_newlabel();
            auto next_label = Temp_newlabel();
            auto temp = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
            emit_irs.push_back(L_Alloca(temp));
            ast2llvmBoolExpr(r->u.boolExpr, true_label, false_label);
            emit_irs.push_back(L_Label(true_label));
            emit_irs.push_back(L_Store(AS_Operand_Const(1), temp));
            emit_irs.push_back(L_Jump(next_label));

            emit_irs.push_back(L_Label(false_label));
            emit_irs.push_back(L_Store(AS_Operand_Const(0), temp));
            emit_irs.push_back(L_Jump(next_label));

            emit_irs.push_back(L_Label(next_label));
            auto dst = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.push_back(L_Load(dst, temp));
            return dst;
            break;
        }
        default:
        {
            assert(0);
            break;
        }
    }
}

AS_operand* ast2llvmLeftVal(aA_leftVal l)
{
    switch (l->kind)
    {
        case A_leftValType::A_varValKind:
        {
            string id = l->u.id[0];
            if(localVarMap.find(id) != localVarMap.end()){
                return AS_Operand_Temp(localVarMap[id]);
            } else if(globalVarMap.find(id) != globalVarMap.end()) {
                return AS_Operand_Name(globalVarMap[id]);
            } else {
                assert(0);
            }
            break;
        }
        case A_leftValType::A_arrValKind:
        {
            AS_operand* indexOperand = ast2llvmIndexExpr(l->u.arrExpr->idx);
            AS_operand* arrOperand = ast2llvmLeftVal(l->u.arrExpr->arr);
            AS_operand* newptr;
            switch (arrOperand->kind)
            {
                case OperandKind::NAME:
                {
                    switch (arrOperand->u.NAME->type)
                    {
                        case TempType::INT_PTR:
                        {
                            newptr = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
                            break;
                        }
                        case TempType::STRUCT_PTR:
                        {
                            newptr = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, arrOperand->u.NAME->structname));
                            break;
                        }                    
                        default:
                        {
                            assert(0);
                            break;
                        }
                    }
                    break;
                }
                case OperandKind::TEMP:
                {
                    switch (arrOperand->u.TEMP->type)
                    {
                        case TempType::INT_PTR:
                        {
                            newptr = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
                            break;
                        }
                        case TempType::STRUCT_PTR:
                        {
                            newptr = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, arrOperand->u.TEMP->structname));
                            break;
                        }                    
                        default:
                        {
                            assert(0);
                            break;
                        }
                    }
                    break;
                }                
                default:
                {
                    assert(0);
                    break;
                }
            }
            emit_irs.push_back(L_Gep(newptr, arrOperand, indexOperand));
            return newptr;
            break;
        }
        case A_leftValType::A_memberValKind:
        {
            AS_operand* structOperand = ast2llvmLeftVal(l->u.memberExpr->structId);
            string memberId = l->u.memberExpr->memberId[0];
            string structId;
            switch (structOperand->kind)
            {
                case OperandKind::TEMP:
                {
                    structId = structOperand->u.TEMP->structname;
                    break;
                } 
                case OperandKind::NAME:
                {
                    structId = structOperand->u.NAME->structname;
                    break;
                }              
                default:
                {
                    assert(0);
                    break;
                }
            }

            AS_operand* newptr;
            MemberInfo memberInfo = structInfoMap[structId].memberinfos[memberId];
            AS_operand* index = AS_Operand_Const(memberInfo.offset);
            switch(memberInfo.def.kind) 
            {
                case TempType::INT_TEMP:
                {
                    newptr = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
                    break;
                }
                case TempType::INT_PTR:
                {
                    newptr = AS_Operand_Temp(Temp_newtemp_int_ptr(memberInfo.def.len));
                    break;
                }
                case TempType::STRUCT_TEMP:
                {
                    newptr = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, memberInfo.def.structname));
                    break;
                }
                case TempType::STRUCT_PTR:
                {
                    newptr = AS_Operand_Temp(Temp_newtemp_struct_ptr(memberInfo.def.len, memberInfo.def.structname));
                    break;
                }
                default:
                {
                    assert(0);
                    break;
                }
            }
            emit_irs.push_back(L_Gep(newptr, structOperand, index));
            return newptr;
            break;
        }
        default:
        {
            assert(0);
            break;
        }
    }
}

AS_operand* ast2llvmIndexExpr(aA_indexExpr index)
{
    switch (index->kind)
    {
        case A_indexExprKind::A_numIndexKind:
        {
            return AS_Operand_Const(index->u.num);
            break;
        }
        case A_indexExprKind::A_idIndexKind:
        {
            string varId = index->u.id[0];
            auto dst = AS_Operand_Temp(Temp_newtemp_int());
            if(localVarMap.find(varId) != localVarMap.end()) {
                auto ptr = AS_Operand_Temp(localVarMap[varId]);
                if(ptr->u.TEMP->type == TempType::INT_PTR && ptr->u.TEMP->len == 0) {
                    emit_irs.push_back(L_Load(dst,ptr));
                    return dst;
                } else {
                    return ptr;
                }
            } else if(globalVarMap.find(varId) != globalVarMap.end()) {
                auto ptr = AS_Operand_Name(globalVarMap[varId]);
                if(ptr->u.NAME->type == TempType::STRUCT_TEMP || ptr->u.NAME->type == TempType::STRUCT_PTR) {
                    return ptr;
                } else if(ptr->u.NAME->len > 0) {
                    return ptr;
                } else {
                    emit_irs.push_back(L_Load(dst, ptr));
                    return dst;
                }
            } else {
                assert(0);
            }
            break;
        }
        default:
        {
            assert(0);
            break;
        }
    }
}

AS_operand* ast2llvmBoolExpr(aA_boolExpr b,Temp_label *true_label,Temp_label *false_label)
{
    switch(b->kind) 
    {
        case A_boolExprType::A_boolBiOpExprKind:
        {
            ast2llvmBoolBiOpExpr(b->u.boolBiOpExpr, true_label, false_label);
            break;
        }
        case A_boolExprType::A_boolUnitKind:
        {
            ast2llvmBoolUnit(b->u.boolUnit, true_label, false_label);
            break;
        }
        default:
        {
            assert(0);
            break;
        }
    }
    return nullptr;
}

void ast2llvmBoolBiOpExpr(aA_boolBiOpExpr b,Temp_label *true_label,Temp_label *false_label)
{
    auto left = b->left;
    auto right = b->right;
    auto another_label = Temp_newlabel();
    switch (b->op)
    {
        case A_boolBiOp::A_and:
        {
            ast2llvmBoolExpr(left, another_label, false_label);
            break;
        }
        case A_boolBiOp::A_or:
        {
            ast2llvmBoolExpr(left, true_label, another_label);
            break;
        }
        default:
        {
            assert(0);
            break;
        }
    }
    emit_irs.push_back(L_Label(another_label));
    ast2llvmBoolExpr(right, true_label, false_label);
    
}

void ast2llvmBoolUnit(aA_boolUnit b,Temp_label *true_label,Temp_label *false_label)
{
    switch(b->kind) 
    {
        case A_boolUnitType::A_boolExprKind:
        {
            ast2llvmBoolExpr(b->u.boolExpr, true_label, false_label);
            break;
        }
        case A_boolUnitType::A_boolUOpExprKind:
        {
            switch (b->u.boolUOpExpr->op)
            {
                case A_boolUOp::A_not:
                {
                    ast2llvmBoolUnit(b->u.boolUOpExpr->cond, false_label, true_label);
                    break;
                }
                default:
                {
                    assert(0);
                    break;
                }
            }
        }
        case A_boolUnitType::A_comOpExprKind:
        {
            ast2llvmComOpExpr(b->u.comExpr, true_label, false_label);
            break;
        }
        default:
        {
            assert(0);
            break;
        }
    }
}

void ast2llvmComOpExpr(aA_comExpr c,Temp_label *true_label,Temp_label *false_label)
{
    auto left = ast2llvmExprUnit(c->left);
    auto right = ast2llvmExprUnit(c->right);
    switch (c->op)
    {
        case A_comOp::A_eq:
        {
            auto dst = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.push_back(L_Cmp(L_relopKind::T_eq, left, right, dst));
            emit_irs.push_back(L_Cjump(dst, true_label, false_label));
            break;
        }
        case A_comOp::A_ge:
        {
            auto dst = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.push_back(L_Cmp(L_relopKind::T_ge, left, right, dst));
            emit_irs.push_back(L_Cjump(dst, true_label, false_label));
            break;
        }
        case A_comOp::A_gt:
        {
            auto dst = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.push_back(L_Cmp(L_relopKind::T_gt, left, right, dst));
            emit_irs.push_back(L_Cjump(dst, true_label, false_label));
            break;
        }
        case A_comOp::A_le:
        {
            auto dst = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.push_back(L_Cmp(L_relopKind::T_le, left, right, dst));
            emit_irs.push_back(L_Cjump(dst, true_label, false_label));
            break;
        }
        case A_comOp::A_lt:
        {
            auto dst = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.push_back(L_Cmp(L_relopKind::T_lt, left, right, dst));
            emit_irs.push_back(L_Cjump(dst, true_label, false_label));
            break;
        }
        case A_comOp::A_ne:
        {
            auto dst = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.push_back(L_Cmp(L_relopKind::T_ne, left, right, dst));
            emit_irs.push_back(L_Cjump(dst, true_label, false_label));
            break;
        }       
        default:
        {
            assert(0);
            break;
        }
    }
}

AS_operand* ast2llvmArithBiOpExpr(aA_arithBiOpExpr a)
{
    AS_operand* left = ast2llvmArithExpr(a->left);
    AS_operand* right = ast2llvmArithExpr(a->right);
    AS_operand* dst = AS_Operand_Temp(Temp_newtemp_int());
    switch (a->op)
    {
        case A_arithBiOp::A_add:
        {
            emit_irs.push_back(L_Binop(L_binopKind::T_plus, left, right, dst));
            break;
        }
        case A_arithBiOp::A_sub:
        {
            emit_irs.push_back(L_Binop(L_binopKind::T_minus, left, right, dst));
            break;
        }
        case A_arithBiOp::A_mul:
        {
            emit_irs.push_back(L_Binop(L_binopKind::T_mul, left, right, dst));
            break;
        }
        case A_arithBiOp::A_div:
        {
            emit_irs.push_back(L_Binop(L_binopKind::T_div, left, right, dst));
            break;
        }    
        default:
        {
            assert(0);
            break;
        }
    }
    return dst;
}

AS_operand* ast2llvmArithUExpr(aA_arithUExpr a)
{
    auto right = ast2llvmExprUnit(a->expr);
    auto dst = AS_Operand_Temp(Temp_newtemp_int());
    switch (a->op)
    {
        case A_neg:
        {
            AS_operand* zero = AS_Operand_Const(0);
            emit_irs.push_back(L_Binop(L_binopKind::T_minus, zero, right, dst));
            break;
        }       
        default:
        {
            assert(0);
            break;
        }
    }
    return dst;
}

AS_operand* ast2llvmArithExpr(aA_arithExpr a)
{
    switch (a->kind)
    {
    case A_arithExprType::A_exprUnitKind:
        return ast2llvmExprUnit(a->u.exprUnit);
        break;
    case A_arithExprType::A_arithBiOpExprKind:
        return ast2llvmArithBiOpExpr(a->u.arithBiOpExpr);
        break;
    default:
        assert(0);
        break;
    }
}

AS_operand* ast2llvmExprUnit(aA_exprUnit e)
{
    switch(e->kind)
    {
        case A_exprUnitType::A_numExprKind:
        {
            return AS_Operand_Const(e->u.num);
            break;
        }
        case A_exprUnitType::A_idExprKind:
        {
            string varId = e->u.id[0];
            auto dst = AS_Operand_Temp(Temp_newtemp_int());
            if(localVarMap.find(varId) != localVarMap.end()) {
                auto ptr = AS_Operand_Temp(localVarMap[varId]);
                if(ptr->u.TEMP->type == TempType::INT_PTR && ptr->u.TEMP->len == 0) {
                    emit_irs.push_back(L_Load(dst,ptr));
                    return dst;
                }else {
                    return ptr;
                }
            } else if(globalVarMap.find(varId) != globalVarMap.end()) {
                auto ptr = AS_Operand_Name(globalVarMap[varId]);
                if(ptr->u.NAME->type == TempType::STRUCT_TEMP || ptr->u.NAME->type == TempType::STRUCT_PTR) {
                    return ptr;
                } else if(ptr->u.NAME->len > 0){
                    return ptr;
                } else {
                    emit_irs.push_back(L_Load(dst, ptr));
                    return dst;
                }
            } else {
                assert(0);
            }
            break;
        }
        case A_exprUnitType::A_arithExprKind:
        {
            return ast2llvmArithExpr(e->u.arithExpr);
            break;
        }
        case A_exprUnitType::A_fnCallKind:
        {
            string funcId = e->u.callExpr->fn[0];
            std::vector<AS_operand*> args;
            for(auto rightVal : e->u.callExpr->vals) {
                auto arg = ast2llvmRightVal(rightVal);
                args.push_back(arg);
            }
            AS_operand* res = AS_Operand_Temp(Temp_newtemp_int());
            emit_irs.push_back(L_Call(funcId, res, args));
            return res;
            break;
        }
        case A_exprUnitType::A_arrayExprKind:
        {
            aA_leftVal leftVal = (aA_leftVal)malloc(sizeof(aA_leftVal));
            leftVal->kind = A_leftValType::A_arrValKind;
            leftVal->pos = e->u.arrayExpr->pos;
            leftVal->u.arrExpr = e->u.arrayExpr;
            auto ptr = ast2llvmLeftVal(leftVal);
            AS_operand* dst = AS_Operand_Temp(Temp_newtemp_int());
            if(ptr->u.TEMP->type == TempType::INT_PTR && ptr->u.TEMP->len == 0) {
                emit_irs.push_back(L_Load(dst,ptr));
                return dst;
            }else {
                return ptr;
            }
            break;
        }
        case A_exprUnitType::A_memberExprKind:
        {
            aA_leftVal leftVal = (aA_leftVal)malloc(sizeof(aA_leftVal));
            leftVal->kind = A_leftValType::A_memberValKind;
            leftVal->pos = e->u.arrayExpr->pos;
            leftVal->u.memberExpr = e->u.memberExpr;
            auto ptr = ast2llvmLeftVal(leftVal);
            AS_operand* dst = AS_Operand_Temp(Temp_newtemp_int());
            if(ptr->u.TEMP->type == TempType::INT_PTR && ptr->u.TEMP->len == 0) {
                emit_irs.push_back(L_Load(dst,ptr));
                return dst;
            }else {
                return ptr;
            }
            break;
        }
        case A_exprUnitType::A_arithUExprKind:
        {
            return ast2llvmArithUExpr(e->u.arithUExpr);
            break;
        }
        default:
            assert(0);
    }
}

LLVMIR::L_func* ast2llvmFuncBlock(Func_local *f)
{
    string name = f->name;
    FuncType ret = f->ret;
    std::vector<Temp_temp*> args(f->args);
    std::list<L_block*> blocks;
    std::list<L_stm*> instrs;
    int i = 0;
    for(L_stm* ir: f->irs) {
        if(i == 0) {
            instrs.push_back(ir);
        }
        else {
            if(ir->type == L_StmKind::T_LABEL) {
                blocks.push_back(L_Block(instrs));
                instrs.clear();
            }
            instrs.push_back(ir);
        }
        i++;
    }
    if(!instrs.empty()) {
        blocks.push_back(L_Block(instrs));
        instrs.clear();
    }
    return new L_func(name, ret, args, blocks);
}

void ast2llvm_moveAlloca(LLVMIR::L_func *f)
{
    L_block* first;
    int i = 0;
    for(auto block : f->blocks) {
        if(i == 0) {
            first = block;
        }
        else {
            for(auto it = block->instrs.begin(); it != block->instrs.end();) {
                if((*it)->type == L_StmKind::T_ALLOCA) {
                    auto pos = ++first->instrs.begin();
                    first->instrs.insert(pos, *it);
                    it = block->instrs.erase(it);
                } else {
                    it++;
                }
            }
        }
        i++;
    }
    return;
}