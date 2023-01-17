//
// Created by Adam Ali on 17/01/2023.
//

#ifndef COMPILER_GENASM_H
#define COMPILER_GENASM_H

#include <array>
#include <bitset>

enum Registers {
    RAX, RBX, RCX, RDX, RSI, RDI, NUM_REGS
};

/**
 * Generates x64 assembly code for the given AST
 */
class GenAsm {
private:
    FILE *output;
    const std::array<const char*, Registers::NUM_REGS> regNames = {
            "rax", "rbx", "rcx", "rdx", "rsi", "rdi"
    };
    std::bitset<Registers::NUM_REGS> regUsed = {0};

    int alloc_register();
    int free_register(int reg);

    /**
     * Generate the string for an x64 assembly instruction
     * with two operands
     * @param indent The number of tabs to indent the instruction
     * @param opcode The opcode of the instruction
     * @param operand1 The first operand
     * @param operand2 The second operand
     */
     void genAsm(int indent, const std::string &opcode, const std::string &operand1, const std::string &operand2) {
        for (int i = 0; i < indent; i++) {
            fprintf(output, "\t");
        }
        fprintf(output, "%s\t%s, %s\n", opcode.c_str(), operand1.c_str(), operand2.c_str());
    }

    /**
     * Generate the string for an x64 assembly instruction
     * with only one operand
     * @param indent The number of tabs to indent the instruction
     * @param opcode The opcode of the instruction
     * @param operand1 The operand
     */
    void genAsm(int indent, const std::string &opcode, const std::string &operand1) {
        for (int i = 0; i < indent; i++) {
            fprintf(output, "\t");
        }
        fprintf(output, "%s\t%s\n", opcode.c_str(), operand1.c_str());
    }

    /**
     * Generate the string for an x64 assembly instruction
     * with no operands
     * @param indent The number of tabs to indent the instruction
     * @param opcode The opcode of the instruction
     */
     void genAsm(int indent, const std::string &opcode) {
        for (int i = 0; i < indent; i++) {
            fprintf(output, "\t");
        }
        fprintf(output, "%s\n", opcode.c_str());
    }

    /**
     * Print a blank line to the output file
     */
     void blankLine() {
        fprintf(output, "\n");
    }

    /**
     * Print a comment to the output file
     */
     void comment(const std::string &comment) {
        fprintf(output, "# %s\n", comment.c_str());
    }

    /**
     * Generate the preamble for the assembly file
     */
    void cgpreamble();

    /**
     * Generate the postamble for the assembly file
     */
     void cgpostamble();

     /**
      * Print a register
      * @param reg The register to print
      */
      void cgprintint(int reg);

    /**
     * Generate the assembly code to load an integer literal into a register
     * @param value
     * @return The register number
     */
    int cgload(int value);

    /**
     * Generate the assembly code to add two registers
     * @param S
     * @param reg2
     * @return The register number of the result
     */
    int cgadd(int S, int reg2);

    /**
     * Generate the assembly code to subtract two registers
     * @param reg1
     * @param reg2
     * @return The register number of the result
     */
    int cgsub(int reg1, int reg2);

    /**
     * Generate the assembly code to multiply two registers
     * @param reg1
     * @param reg2
     * @return The register number of the result
     */
    int cgmul(int reg1, int reg2);

    /**
     * Generate the assembly code to divide two registers
     * @param reg1
     * @param reg2
     * @return The register number of the result
     */
    int cgdiv(int reg1, int reg2);

    /**
     * Given the AST, generate the assembly code
     * @param node
     * @return
     */
    int genAst(struct ASTNode* node);
public:
    GenAsm(const char *filename);
    ~GenAsm();

    /**
     * Generate the assembly code for the given AST
     * @param node The AST
     */
     void compile(struct ASTNode* node);
};

#endif //COMPILER_GENASM_H
