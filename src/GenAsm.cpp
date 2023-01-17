//
// Created by Adam Ali on 17/01/2023.
//
#include "GenAsm.h"
#include "Token.h"

int GenAsm::alloc_register() {
    for (int i = 0; i < Registers::NUM_REGS; i++) {
        if (!regUsed[i]) {
            regUsed[i] = true;
            return i;
        }
    }
    throw std::runtime_error("No registers available");
}

int GenAsm::free_register(int reg) {
    if (regUsed[reg]) {
        regUsed[reg] = false;
        return 0;
    }
    return -1;
}


GenAsm::GenAsm(const char* filename) {
    output = fopen(filename, "w");
    if (output == nullptr) {
        throw std::runtime_error("Could not open file");
    }
}

GenAsm::~GenAsm() {
    fclose(output);
}

void GenAsm::compile(struct ASTNode *node) {
    cgpreamble();
    int reg = genAst(node);
    cgprintint(reg);
    cgpostamble();
}

int GenAsm::genAst(struct ASTNode *node) {
    int leftreg, rightreg;

    if (node->left) {
        leftreg = genAst(node->left);
    }
    if (node->right) {
        rightreg = genAst(node->right);
    }

    switch(node->type) {
        case TokenType::Number:
            return cgload(*(int *) node->value);
        case TokenType::Plus:
            return cgadd(leftreg, rightreg);
        case TokenType::Minus:
            return cgsub(leftreg, rightreg);
        case TokenType::Star:
            return cgmul(leftreg, rightreg);
        case TokenType::Slash:
            return cgdiv(leftreg, rightreg);
        default:
            fprintf(stderr, "Unknown AST operator %d", node->type);
            exit(1);
    }
}

void GenAsm::cgpreamble() {
    comment("Preamble");
    genAsm(1, ".text");
    genAsm(0, ".LC0");
    genAsm(1, ".string", "\"%d\\n\"");
    genAsm(0, "printint:");
    genAsm(1, "pushq", "%rbp");
    genAsm(1, "movq", "%rsp", "%rbp");
    genAsm(1, "subq", "$16", "%rsp");
    genAsm(1, "movl", "%edi", "-4(%rbp)");
    genAsm(1, "movl", "-4(%rbp)", "%eax");
    genAsm(1, "movl", "%eax", "%esi");
    genAsm(1, "leaq", ".LC0(%rip)", "%rdi");
    genAsm(1, "movl", "$0", "%eax");
    genAsm(1, "call", "printf@PLT");
    genAsm(1, "nop");
    genAsm(1, "leave");
    genAsm(1, "ret");
    blankLine();
    genAsm(1, ".globl", "main");
    genAsm(1, ".type", "main", "@function");
    blankLine();
    genAsm(0, "main:");
    genAsm(1, "pushq", "%rbp");
    genAsm(1, "movq", "%rsp", "%rbp");
    blankLine();
    genAsm(1, "movq", "$2", "%r8");
    genAsm(1, "movq", "$3", "%r9");
    genAsm(1, "movq", "$5", "%r10");
    genAsm(1, "imulq", "%r9", "%r10");
    genAsm(1, "addq", "%r8", "%r10");
    blankLine();
    genAsm(1, "movq", "$8", "%r8");
    genAsm(1, "movq", "$3", "%r9");
    genAsm(1, "movq", "%r8", "%rax");
    genAsm(1, "cqo");
    genAsm(1, "idivq", "%r9");
    genAsm(1, "movq", "%rax", "%r8");
    genAsm(1, "subq", "%r10", "%rdi");
    genAsm(1, "call", "printint");
    comment("End of preamble");
    blankLine();
}

void GenAsm::cgpostamble() {
    blankLine();
    comment("Postamble");
    genAsm(1, "movl", "$0", "%eax");
    genAsm(1, "popq", "%rbp");
    genAsm(1, "ret");
    comment("End of postamble");
}

void GenAsm::cgprintint(int reg) {
    genAsm(1, "movq", "%rdi");
    genAsm(1, "call", "printint");
    free_register(reg);
}

int GenAsm::cgload(int D) {
    int reg = alloc_register();

    genAsm(1, "mov", regNames[reg], std::to_string(D));

    return D;
}

int GenAsm::cgadd(int S, int D) {
    fprintf(output, "\tadd\t%s,\t%d\n", regNames[D], S);

    free_register(S);

    return D;
}

int GenAsm::cgsub(int S, int D) {
    fprintf(output, "\tsub\t%s,\t%d\n", regNames[D], S);

    free_register(S);

    return D;
}

int GenAsm::cgmul(int reg1, int reg2) {
    fprintf(output, "\timul\t%s,\t%s\n", regNames[reg1], regNames[reg2]);

    free_register(reg2);

    return reg1;
}

int GenAsm::cgdiv(int reg1, int reg2) {
    fprintf(output, "\tmovq\t%s,%%rax\n", regNames[reg1]);
    fprintf(output, "\tcqo\n");
    fprintf(output, "\tidivq\t%s\n", regNames[reg2]);
    fprintf(output, "\tmovq\t%%rax,%s\n", regNames[reg1]);

    free_register(reg2);
    return reg1;
}