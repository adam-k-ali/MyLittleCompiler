// A short program to test the lexer

package "main";

include "lib.fmt";

enum TokenType {
    EOF,
    IDENT,
    INT
}

struct Token {
    string type;
    string value;
}

class Test: Object {
    private int foo; // 4 bytes

    int main(char[] args) {
        if(args.size() == 1) {
            foo = 1 << 2;
        } else {
            foo = 2 >> 1;
        }

        if (true) {
            foo = 3;
        } else if (false) {
            foo = 4;
        } else {
            foo = 5;
        }

        for (int i = 0; i < 10; i++) {
            foo = 5;
        }
        ...

        while (true) {
            foo = 6;
        }

        int bar;
        foo = 5;
        bar = 9;

        print(foo);

        return 0;
    }

    void print(int x) {
        fmt.println(x);
    }
}