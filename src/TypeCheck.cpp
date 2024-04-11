#include "TypeCheck.h"

// global tabels
typeMap func2retType; // function name to return type

// global token ids to type
typeMap g_token2Type;

// local token ids to type, since func param can override global param
typeMap funcparam_token2Type;
vector<typeMap> local_token2Type;

paramMemberMap func2Param;
paramMemberMap struct2Members;
// private util functions
void error_print(std::ostream &out, A_pos p, string info)
{
    out << "Typecheck error in line " << p->line << ", col " << p->col << ": " << info << std::endl;
    exit(0);
}

void print_token_map(typeMap *map)
{
    for (auto it = map->begin(); it != map->end(); it++)
    {
        std::cout << it->first << " : ";
        switch (it->second->type->type)
        {
        case A_dataType::A_nativeTypeKind:
            switch (it->second->type->u.nativeType)
            {
            case A_nativeType::A_intTypeKind:
                std::cout << "int";
                break;
            default:
                break;
            }
            break;
        case A_dataType::A_structTypeKind:
            std::cout << *(it->second->type->u.structType);
            break;
        default:
            break;
        }
        switch (it->second->isVarArrFunc)
        {
        case 0:
            std::cout << " scalar";
            break;
        case 1:
            std::cout << " array";
            break;
        case 2:
            std::cout << " function";
            break;
        }
        std::cout << std::endl;
    }
}

void print_token_maps()
{
    std::cout << "global token2Type:" << std::endl;
    print_token_map(&g_token2Type);
    std::cout << "local token2Type:" << std::endl;
    print_token_map(&funcparam_token2Type);
}

bool comp_aA_type(aA_type target, aA_type t)
{
    if (!target || !t)
        return false;
    if (target->type != t->type)
        return false;
    if (target->type == A_dataType::A_nativeTypeKind)
        if (target->u.nativeType != t->u.nativeType)
            return false;
    if (target->type == A_dataType::A_structTypeKind)
        if (target->u.structType != t->u.structType)
            return false;
    return true;
}

bool comp_tc_type(tc_type target, tc_type t)
{
    if (!target || !t)
        return false;

    // arr kind first
    if (target->isVarArrFunc & t->isVarArrFunc == 0)
        return false;

    // if target type is nullptr, alwayse ok
    return comp_aA_type(target->type, t->type);
}

tc_type tc_Type(aA_type t, uint isVarArrFunc)
{
    tc_type ret = new tc_type_;
    ret->type = t;
    ret->isVarArrFunc = isVarArrFunc;
    return ret;
}

tc_type tc_Type(aA_varDecl vd)
{
    if (vd->kind == A_varDeclType::A_varDeclScalarKind)
        return tc_Type(vd->u.declScalar->type, 0);
    else if (vd->kind == A_varDeclType::A_varDeclArrayKind)
        return tc_Type(vd->u.declArray->type, 1);
    return nullptr;
}

// public functions
void check_Prog(std::ostream &out, aA_program p)
{
    for (auto ele : p->programElements)
    {
        if (ele->kind == A_programVarDeclStmtKind)
        {
            check_VarDecl(out, ele->u.varDeclStmt);
        }
        else if (ele->kind == A_programStructDefKind)
        {
            check_StructDef(out, ele->u.structDef);
        }
    }

    for (auto ele : p->programElements)
    {
        if (ele->kind == A_programFnDeclStmtKind)
        {
            check_FnDeclStmt(out, ele->u.fnDeclStmt);
        }
        else if (ele->kind == A_programFnDefKind)
        {

            check_FnDecl(out, ele->u.fnDef->fnDecl);
        }
    }
    for (auto ele : p->programElements)
    {
        if (ele->kind == A_programFnDefKind)
        {
            check_FnDef(out, ele->u.fnDef);
        }
        else if (ele->kind == A_programNullStmtKind)
        {
            // do nothing
        }
    }
    out << "Typecheck passed!" << std::endl;
    return;
}

void check_MultiDecl(std::ostream &out, string name, A_pos pos)
{
    if (g_token2Type.find(name) != g_token2Type.end())
    {
        error_print(out, pos, name + " dplicates with global variable");
    }
    if (struct2Members.find(name) != struct2Members.end())
    {
        error_print(out, pos, name + " dplicates with struct variable");
    }
    if (funcparam_token2Type.find(name) != funcparam_token2Type.end())
    {
        error_print(out, pos, "This name " + name + " has been declared in func variable list");
    }
}

void check_VarDecl(std::ostream &out, aA_varDeclStmt vd)
{
    if (!vd)
        return;
    string name;
    if (vd->kind == A_varDeclStmtType::A_varDeclKind)
    {
        // decl only
        aA_varDecl vdecl = vd->u.varDecl;
        tc_type tokenType;
        if (vdecl->kind == A_varDeclType::A_varDeclScalarKind)
        {
            name = *vdecl->u.declScalar->id;
            /* fill code here*/
            aA_varDeclScalar varDeclScalar = vdecl->u.declScalar;
            check_MultiDecl(out, name, varDeclScalar->pos);
        }
        else if (vdecl->kind == A_varDeclType::A_varDeclArrayKind)
        {
            name = *vdecl->u.declArray->id;
            /* fill code here*/
            aA_varDeclArray varDeclArray = vdecl->u.declArray;
            check_MultiDecl(out, name, varDeclArray->pos);
        }
        tokenType = tc_Type(vdecl);
        /*栈空时为全局变量，不空时为局部变量*/
        if (local_token2Type.empty())
        {
            g_token2Type[name] = tokenType;
        }
        else
        {
            funcparam_token2Type[name] = tokenType;
        }
    }
    else if (vd->kind == A_varDeclStmtType::A_varDefKind)
    {
        // decl and def
        aA_varDef vdef = vd->u.varDef;
        tc_type tokenType;
        if (vdef->kind == A_varDefType::A_varDefScalarKind)
        {
            name = *vdef->u.defScalar->id;
            /* fill code here, allow omited type */
            check_MultiDecl(out, name, vdef->u.defScalar->pos);
            /*当没有声明类型时判断右值类型，是native就赋值类型*/
            tokenType = check_rightValValid(out, vdef->u.defScalar->val);
            if (local_token2Type.empty())
            {
                g_token2Type[name] = tokenType;
            }
            else
            {
                funcparam_token2Type[name] = tokenType;
            }
        }
        else if (vdef->kind == A_varDefType::A_varDefArrayKind)
        {
            name = *vdef->u.defArray->id;
            /* fill code here, allow omited type */
            check_MultiDecl(out, name, vdef->u.defArray->pos);
            tokenType = tc_Type(vdef->u.defArray->type, 0);
            if (local_token2Type.empty())
            {
                g_token2Type[name] = tokenType;
            }
            else
            {
                funcparam_token2Type[name] = tokenType;
            }
        }
    }
    return;
}

tc_type check_rightValValid(std::ostream &out, aA_rightVal rightVal)
{
    if (rightVal == nullptr)
        return nullptr;
    if (rightVal->kind == A_rightValType::A_arithExprValKind)
    {
        return check_arithExprValValid(out, rightVal->u.arithExpr);
    }
    return nullptr;
}

tc_type check_arithExprValValid(std::ostream &out, aA_arithExpr arithExpr)
{
    if (arithExpr == nullptr)
        return nullptr;
    switch (arithExpr->kind)
    {
    case (A_arithExprType::A_exprUnitKind):
    {
        return check_ExprUnit(out, arithExpr->u.exprUnit);
        break;
    }
    case (A_arithExprType::A_arithBiOpExprKind):
    {
        return check_ArithExpr(out, arithExpr);
        break;
    }
    }
    return nullptr;
}

void check_StructDef(std::ostream &out, aA_structDef sd)
{
    if (!sd)
        return;
    string name = *sd->id;
    if (struct2Members.find(name) != struct2Members.end())
        error_print(out, sd->pos, "This id is already defined!");
    struct2Members[name] = &(sd->varDecls);
    return;
}

string getATypeName(aA_type type)
{
    switch (type->type)
    {
    case (A_dataType::A_nativeTypeKind):
    {
        return "int";
    }
    case (A_dataType::A_structTypeKind):
    {
        return *(type->u.structType);
    }
    }
    return "nulltype";
}

string getVarDeclName(aA_varDecl x)
{
    if (x == nullptr)
        return nullptr;
    switch (x->kind)
    {

    case (A_varDeclType::A_varDeclArrayKind):
    {
        return *(x->u.declArray->id);
    }
    break;
    case (A_varDeclType::A_varDeclScalarKind):
    {
        return *(x->u.declScalar->id);
    }
    break;
    }
    return "";
}

void check_typeValid(std::ostream &out, aA_type varType)
{
    if (!varType)
        return;
    string name = getATypeName(varType);
    if (name != "int" && struct2Members.find(name) == struct2Members.end())
        error_print(out, varType->pos, "not int!");
}

void check_VarDeclValid(std::ostream &out, aA_varDecl varDecl)
{
    aA_type varType = tc_Type(varDecl)->type;
    check_typeValid(out, varType);
}

void check_MultiParams(std::ostream &out, vector<aA_varDecl> varDeclList)
{
    vector<string> paramNames;
    for (auto varDecl : varDeclList)
    {
        check_VarDeclValid(out, varDecl);
        string name = getVarDeclName(varDecl);
        for (auto paramName : paramNames)
        {
            if (name == paramName)
            {
                error_print(out, varDecl->pos, "dplicate variable name!");
            }
        }
        paramNames.push_back(name);
    }
}
bool vectorsMatch(const vector<aA_varDecl> &vec1, const vector<aA_varDecl> &vec2)
{
    // Step 1: Check if sizes are equal
    if (vec1.size() != vec2.size())
    {
        return false;
    }

    // Step 2: Compare elements one by one
    for (size_t i = 0; i < vec1.size(); ++i)
    {
        if (!comp_tc_type(tc_Type(vec1[i]), tc_Type(vec2[i])))
        { // Assuming aA_varDecl supports comparison
            return false;
        }
    }

    // If we reach here, vectors match
    return true;
}
void check_FnDecl(std::ostream &out, aA_fnDecl fd)
{
    if (!fd)
        return;
    string name = *fd->id;
    // if already declared, should match
    if (func2Param.find(name) != func2Param.end())
    {
        // is function ret val matches
        /* fill code here */
        if (!comp_tc_type(func2retType[name], tc_Type(fd->type, 0)))
        {
            error_print(out, fd->pos, "function type doesn't match the type.");
            return;
        }
        // is function params matches decl
        /* fill code here */
        vector<aA_varDecl> *params1 = func2Param[name];
        vector<aA_varDecl> params2 = fd->paramDecl->varDecls;
        if (!vectorsMatch(*params1, params2))
        {
            error_print(out, fd->pos, "function definition doesn't match the declaration.");
            return;
        }
    }
    else
    {
        // if not defined
        /* fill code here */
        check_MultiParams(out, fd->paramDecl->varDecls);
        check_typeValid(out, fd->type);
        func2Param[name] = &(fd->paramDecl->varDecls);
        func2retType[name] = tc_Type(fd->type, 0);
    }
    return;
}

void check_FnDeclStmt(std::ostream &out, aA_fnDeclStmt fd)
{
    if (!fd)
        return;
    check_FnDecl(out, fd->fnDecl);
    return;
}

void check_FnDef(std::ostream &out, aA_fnDef fd)
{
    if (!fd)
        return;
    // should match if declared
    check_FnDecl(out, fd->fnDecl);
    // add params to local tokenmap, func params override global ones
    for (aA_varDecl vd : fd->fnDecl->paramDecl->varDecls)
    {
        /* fill code here */
        string name = getVarDeclName(vd);
        funcparam_token2Type[name] = tc_Type(vd);
    }
    local_token2Type.push_back(funcparam_token2Type);
    /* fill code here */
    for (aA_codeBlockStmt stmt : fd->stmts)
    {
        check_CodeblockStmt(out, stmt);
        // return value type should match
        /* fill code here */
    }
    funcparam_token2Type.clear();
    /*     if (*fd->fnDecl->id == "foo")
            error_print(out, fd->pos, "wwwwwwwwwwwww"); */
    if (local_token2Type.size() != 0)
        local_token2Type.pop_back();
    /* if (*fd->fnDecl->id == "foo")
        error_print(out, fd->pos, "wwwwwwwwwwwww"); */
    return;
}

void check_CodeblockStmt(std::ostream &out, aA_codeBlockStmt cs)
{
    if (!cs)
        return;
    // variables declared in a code block should not duplicate with outer ones.
    switch (cs->kind)
    {
    case A_codeBlockStmtType::A_varDeclStmtKind:
        check_VarDecl(out, cs->u.varDeclStmt);
        break;
    case A_codeBlockStmtType::A_assignStmtKind:
        check_AssignStmt(out, cs->u.assignStmt);
        break;
    case A_codeBlockStmtType::A_ifStmtKind:
        check_IfStmt(out, cs->u.ifStmt);
        break;
    case A_codeBlockStmtType::A_whileStmtKind:
        check_WhileStmt(out, cs->u.whileStmt);
        break;
    case A_codeBlockStmtType::A_callStmtKind:
        check_CallStmt(out, cs->u.callStmt);
        break;
    case A_codeBlockStmtType::A_returnStmtKind:
        check_ReturnStmt(out, cs->u.returnStmt);
        break;
    default:
        break;
    }
    return;
}

tc_type idToType(std::ostream &out, A_pos pos, string id)
{
    if (funcparam_token2Type.find(id) != funcparam_token2Type.end())
        return funcparam_token2Type[id];
    // 查找更上级的变量
    for (auto funcp_t : local_token2Type)
    {
        if (funcp_t.find(id) != funcp_t.end())
            return funcp_t[id];
    }
    if (g_token2Type.find(id) != g_token2Type.end())
        return g_token2Type[id];
    if (func2Param.find(id) != func2Param.end())
        error_print(out, pos, "cannot assign a value to function");
    return nullptr;
}
void set_idToType(string id, tc_type deduced_type)
{
    if (funcparam_token2Type.find(id) != funcparam_token2Type.end())
        funcparam_token2Type[id]->type = deduced_type->type;
    else if (g_token2Type.find(id) != g_token2Type.end())
        g_token2Type[id]->type = deduced_type->type;
}
void check_AssignStmt(std::ostream &out, aA_assignStmt as)
{
    if (!as)
        return;
    string name;
    tc_type deduced_type; // deduced type if type is omitted at decl
    tc_type leftValType;
    deduced_type = check_rightValValid(out, as->rightVal);
    switch (as->leftVal->kind)
    {
    case A_leftValType::A_varValKind:
    {
        name = *as->leftVal->u.id;
        /* fill code here */
        leftValType = idToType(out, as->leftVal->pos, name);
    }
    break;
    case A_leftValType::A_arrValKind:
    {
        name = *as->leftVal->u.arrExpr->arr->u.id;
        /* fill code here */
        check_ArrayExpr(out, as->leftVal->u.arrExpr);
        leftValType = idToType(out, as->leftVal->pos, name);
        /*数组成员为左值应该修改其为标量类型*/
        leftValType->isVarArrFunc = 0;
    }
    break;
    case A_leftValType::A_memberValKind:
    {
        /* fill code here */
        leftValType = check_MemberExpr(out, as->leftVal->u.memberExpr);
    }
    break;
    }
    if (leftValType == nullptr)
    {
        error_print(out, as->leftVal->pos, "Left Val here is not declared!");
        return;
    }
    if (leftValType->type == nullptr && as->leftVal->kind != A_leftValType::A_memberValKind)
    {
        set_idToType(name, deduced_type);
        leftValType->type = deduced_type->type;
    }
    if (!comp_tc_type(leftValType, deduced_type))
    {
        error_print(out, as->pos, "The type of left val and right val doesn't match");
    }
    return;
}

void check_ArrayExpr(std::ostream &out, aA_arrayExpr ae)
{
    if (!ae)
        return;
    string name = *ae->arr->u.id;
    // check array name
    /* fill code here */
    tc_type arrType = idToType(out, ae->pos, name);
    if (arrType == nullptr)
        error_print(out, ae->pos, "Array name is not declared!");
    if (arrType->isVarArrFunc != 1)
        error_print(out, ae->pos, "This variable " + name + " is a scalar type!");
    // check index
    /* fill code here */
    if (ae->idx->kind == A_indexExprKind::A_idIndexKind)
    {
        string bTypeName = *(ae->idx->u.id);
        tc_type bType = idToType(out, ae->idx->pos, bTypeName);
        if (bType == nullptr)
            error_print(out, ae->idx->pos, "The name of the val in array here is not declared!");
        if (bType->isVarArrFunc == 1)
            error_print(out, ae->idx->pos, "The name of the val in array here is an array!");
        if (bType->type->type == A_dataType::A_structTypeKind)
            error_print(out, ae->idx->pos, "The name of the val in array here is a struct!");
    }
    return;
}

tc_type check_MemberExpr(std::ostream &out, aA_memberExpr me)
{
    // check if the member exists and return the tyep of the member
    if (!me)
        return nullptr;
    /*变量名*/
    string name = *me->structId->u.id;
    tc_type structVarType;
    vector<aA_varDecl> *varDecls;
    // check struct name
    /* fill code here */
    structVarType = idToType(out, me->pos, name);
    if (structVarType == nullptr)
        error_print(out, me->pos, "The variable " + name + " defined here is not declared!");
    if (structVarType->type->type == A_dataType::A_nativeTypeKind)
        error_print(out, me->pos, "The variable " + name + " used here is a int!");
    // check member name
    /* fill code here */
    /*结构体名*/
    if (struct2Members.find(*(structVarType->type->u.structType)) != struct2Members.end())
    {
        varDecls = struct2Members[*(structVarType->type->u.structType)];
    }
    name = *me->memberId;
    for (auto varDecl : *varDecls)
    {
        if (name == getVarDeclName(varDecl))
        {
            // 获取成员变量类型信息
            return tc_Type(varDecl);
        }
    }
    return nullptr;
}

void check_IfStmt(std::ostream &out, aA_ifStmt is)
{
    if (!is)
        return;
    check_BoolExpr(out, is->boolExpr);
    /* fill code here, take care of variable scope */
    local_token2Type.push_back(funcparam_token2Type);
    funcparam_token2Type.clear();
    for (aA_codeBlockStmt s : is->ifStmts)
    {
        check_CodeblockStmt(out, s);
    }
    /* fill code here */
    funcparam_token2Type.clear();
    for (aA_codeBlockStmt s : is->elseStmts)
    {
        check_CodeblockStmt(out, s);
    }
    /* fill code here */
    funcparam_token2Type.clear();
    local_token2Type.pop_back();
    return;
}

void check_BoolExpr(std::ostream &out, aA_boolExpr be)
{
    if (!be)
        return;
    switch (be->kind)
    {
    case A_boolExprType::A_boolBiOpExprKind:
        check_BoolExpr(out, be->u.boolBiOpExpr->left);
        check_BoolExpr(out, be->u.boolBiOpExpr->right);
        break;
    case A_boolExprType::A_boolUnitKind:
        check_BoolUnit(out, be->u.boolUnit);
        break;
    default:
        break;
    }
    return;
}

void check_BoolUnit(std::ostream &out, aA_boolUnit bu)
{
    if (!bu)
        return;
    switch (bu->kind)
    {
    case A_boolUnitType::A_comOpExprKind:
    {
        /* fill code here */
        tc_type exprUnit1 = check_ExprUnit(out, bu->u.comExpr->left);
        tc_type exprUnit2 = check_ExprUnit(out, bu->u.comExpr->right);
        if (!(exprUnit1->type->type == A_dataType::A_nativeTypeKind && exprUnit1->isVarArrFunc == 0))
        {
            error_print(out, bu->u.comExpr->left->pos, "Left expr type not int!");
        }
        if (!(exprUnit2->type->type == A_dataType::A_nativeTypeKind && exprUnit2->isVarArrFunc == 0))
        {
            error_print(out, bu->u.comExpr->left->pos, "Left expr type not int!");
        }
    }
    break;
    case A_boolUnitType::A_boolExprKind:
        check_BoolExpr(out, bu->u.boolExpr);
        break;
    case A_boolUnitType::A_boolUOpExprKind:
        check_BoolUnit(out, bu->u.boolUOpExpr->cond);
        break;
    default:
        break;
    }
    return;
}

tc_type check_ExprUnit(std::ostream &out, aA_exprUnit eu)
{
    // return the aA_type of expr eu
    if (!eu)
        return nullptr;
    tc_type ret;
    switch (eu->kind)
    {
    case A_exprUnitType::A_idExprKind:
    {
        /* fill code here */
        string name = *eu->u.id;
        auto type = idToType(out, eu->pos, name);
        if (type == nullptr)
        {
            error_print(out, eu->pos, "Var name " + name + " not found");
        }
        return type;
    }
    break;
    case A_exprUnitType::A_numExprKind:
    {
        aA_type numt = new aA_type_;
        numt->pos = eu->pos;
        numt->type = A_dataType::A_nativeTypeKind;
        numt->u.nativeType = A_nativeType::A_intTypeKind;
        ret = tc_Type(numt, 0);
    }
    break;
    case A_exprUnitType::A_fnCallKind:
    {
        check_FuncCall(out, eu->u.callExpr);
        // check_FuncCall will check if the function is defined
        /* fill code here */
        string name = *eu->u.callExpr->fn;
        auto funRetType = func2retType[name];
        if (!(funRetType->type->type == A_dataType::A_nativeTypeKind && funRetType->isVarArrFunc == 0))
        {
            error_print(out, eu->pos, "The func return type is not compatible with fnCall expr Unit");
        }
        return funRetType;
    }
    break;
    case A_exprUnitType::A_arrayExprKind:
    {
        check_ArrayExpr(out, eu->u.arrayExpr);
        /* fill code here */
        string name = *eu->u.arrayExpr->arr->u.id;
        tc_type arrType = idToType(out, eu->pos, name);
        if (!(arrType->type->type == A_dataType::A_nativeTypeKind && arrType->isVarArrFunc == 0))
        {
            error_print(out, eu->pos, "The func return type is not compatible with array expr Unit");
        }
        return arrType;
    }
    break;
    case A_exprUnitType::A_memberExprKind:
    {
        ret = check_MemberExpr(out, eu->u.memberExpr);
    }
    break;
    case A_exprUnitType::A_arithExprKind:
    {
        ret = check_ArithExpr(out, eu->u.arithExpr);
    }
    break;
    case A_exprUnitType::A_arithUExprKind:
    {
        ret = check_ExprUnit(out, eu->u.arithUExpr->expr);
    }
    break;
    }
    return ret;
}

tc_type check_ArithExpr(std::ostream &out, aA_arithExpr ae)
{
    if (!ae)
        return nullptr;
    tc_type ret;
    switch (ae->kind)
    {
    case A_arithExprType::A_arithBiOpExprKind:
    {
        ret = check_ArithExpr(out, ae->u.arithBiOpExpr->left);
        tc_type rightTyep = check_ArithExpr(out, ae->u.arithBiOpExpr->right);
        if (ret->type->type > 0 || ret->type->type != A_dataType::A_nativeTypeKind || ret->type->u.nativeType != A_nativeType::A_intTypeKind ||
            rightTyep->type->type > 0 || rightTyep->type->type != A_dataType::A_nativeTypeKind || rightTyep->type->u.nativeType != A_nativeType::A_intTypeKind)
            error_print(out, ae->pos, "Only int can be arithmetic expression operation values!");
    }
    break;
    case A_arithExprType::A_exprUnitKind:
        ret = check_ExprUnit(out, ae->u.exprUnit);
        break;
    }
    return ret;
}

void check_FuncCall(std::ostream &out, aA_fnCall fc)
{
    if (!fc)
        return;
    // check if function defined
    string func_name = *fc->fn;
    /* fill code here */
    if (func2retType.find(func_name) == func2retType.end())
        error_print(out, fc->pos, "Cannot find the corresponding function name " + func_name);
    // check if parameter list matches
    auto varDeclVec = func2Param[func_name];
    if ((*varDeclVec).size() != fc->vals.size())
        error_print(out, fc->pos, "The fn Call stmt's parameters size not equal to the func declaration's in fn name " + func_name);

    for (int i = 0; i < fc->vals.size(); i++)
    {
        /* fill code here */
        if (!comp_tc_type(tc_Type((*varDeclVec)[i]), check_rightValValid(out, fc->vals[i])))
        {
            error_print(out, fc->pos, "The " + std::to_string(i) + " th parameter in fnCall doesn't match the one in fn declaration in fn name " + func_name);
        }
    }
    return;
}

void check_WhileStmt(std::ostream &out, aA_whileStmt ws)
{
    if (!ws)
        return;
    check_BoolExpr(out, ws->boolExpr);
    /* fill code here, take care of variable scope */
    local_token2Type.push_back(funcparam_token2Type);
    funcparam_token2Type.clear();
    for (aA_codeBlockStmt s : ws->whileStmts)
    {
        check_CodeblockStmt(out, s);
    }
    /* fill code here */
    funcparam_token2Type.clear();
    local_token2Type.pop_back();
    return;
}

void check_CallStmt(std::ostream &out, aA_callStmt cs)
{
    if (!cs)
        return;
    check_FuncCall(out, cs->fnCall);
    return;
}

void check_ReturnStmt(std::ostream &out, aA_returnStmt rs)
{
    if (!rs)
        return;
    return;
}
