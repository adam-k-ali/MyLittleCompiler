//
// Created by Adam Ali on 17/01/2023.
//
#include "gtest/gtest.h"

#include "Token.h"
#include "Parser.h"
#include "Lexer.h"
#include "FileMap.h"
#include "GenAsm.h"
#include "defs.h"

class MathExpressionTest : public ::testing::Test {
private:
    static std::string treeToString(ASTNode* root) {
        if (root == nullptr) {
            return "";
        }
        std::string result;

        result += "(";
        // If the node is an operator, print the operator
        if (root->dtype == Types::Void) {
            if (TokenToName.find(root->type) != TokenToName.end()) {
                result += TokenToName.at(root->type);
            } else {
                result += "Invalid";
            }
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
        Lexer scanner(file.begin(), file.end());
        // T_PRINT the tokens
        std::vector<Token> tokens = scanner.getTokens();
        printf("Tokens: ");
        for (Token token : tokens) {
            printf("%s,", TokenToName.at(token.getType()).c_str());
        }
        printf("\n");
        Parser parser(tokens);
        std::list<ASTNode*> expr = parser.parse();

        printf("Parsed statements: %d\n", expr.size());

        std::string actual = "";
        for (ASTNode* node : expr) {
            actual += treeToString(node);
        }
        ASSERT_EQ(expected, actual);
    }

    static std::list<ASTNode*> parse(const std::string input) {
        FileMap file(input.c_str());

        Lexer scanner(file.begin(), file.end());
        Parser parser(scanner.getTokens());
        return parser.parse();
    }
};

TEST(MathExpressionTest, SampleA) {
    MathExpressionTest::testParsing("/Users/adamali/Developer/CLionProjects/Compiler/tests/test_res/Sample.b",
                                    "(V_INT(fred))(V_INT(jim))(T_EQUAL(fred)(5))(T_EQUAL(jim)(12))(T_PRINT(T_PLUS(fred)(jim)))");
}