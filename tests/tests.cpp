//
// Created by Adam Ali on 17/01/2023.
//
#include "gtest/gtest.h"

#include "Token.h"
#include "Parser.h"
#include "Scanner.h"
#include "FileMap.h"
#include "Interpret.h"
#include "GenAsm.h"

class MathExpressionTest : public ::testing::Test {
private:
    static std::string treeToString(ASTNode* root) {
        if (root == nullptr) {
            return "";
        }
        std::string result;

        result += "(";
        // If the node is an operator, print the operator
        if (root->dtype == Types::Operator) {

            result += tokenToName.at(root->type);
        } else {
            // Otherwise, print the value
            result += root->toString();
        }
        result += treeToString(root->left);
        result += treeToString(root->right);

        result += ")";
        return result;
    }
public:
    static void testParsing(const std::string input, std::string expected) {
        FileMap file(input.c_str());

        Scanner scanner(file.begin(), file.end());
        Parser parser(scanner.getTokens());
        struct ASTNode* expr = parser.parse();
        std::string actual = treeToString(expr);
        ASSERT_EQ(expected, actual);
    }

    static ASTNode* parse(const std::string input) {
        FileMap file(input.c_str());

        Scanner scanner(file.begin(), file.end());
        Parser parser(scanner.getTokens());
        return parser.parse();
    }
};

TEST(MathExpressionTest, SampleA) {
    MathExpressionTest::testParsing("/Users/adamali/Developer/CLionProjects/Compiler/tests/test_res/Sample.b", "(Minus(Plus(Star(5.000000)(5.000000))(Slash(3.000000)(2.000000)))(7.000000))");
}

TEST(MathExpressionTest, SampleAInterpret) {
    ASTNode* expr = MathExpressionTest::parse("/Users/adamali/Developer/CLionProjects/Compiler/tests/test_res/Sample.b");
    ASSERT_EQ(interpretAST(expr), 19.5);
}

TEST(MathExpressionTest, SampleACompile) {
    ASTNode* expr = MathExpressionTest::parse("/Users/adamali/Developer/CLionProjects/Compiler/tests/test_res/Sample.b");
    GenAsm genAsm("/Users/adamali/Developer/CLionProjects/Compiler/tests/test_res/Sample.s");
    genAsm.compile(expr);
}