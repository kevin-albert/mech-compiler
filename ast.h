#ifndef AST_H
#define AST_H

#include <string>
#include <iostream>
#include <vector>

class ast {
    friend ostream &operator<<(ostream&, const ast*);
    public:
        ast(int code, string text, string file, int line, int col): 
            text(text), 
            code(code),
            file(file),
            line(line),
            col(col) {}

        ~ast() {
            for (ast *child: children)
                delete child;
        }

        ast *adopt(ast *child) {
            children.push_back(child);
            return this;
        }

        string get_text() const { return text; }
        int get_code() const { return code; }
        string get_file() const { return file; }
        int get_line() const { return line; }
        int get_col() const { return col; }

        void print(ostream &out, int depth=0) const;

        vector<ast*>::iterator begin() {
            return children.begin();
        }

        vector<ast*>::iterator end() {
            return children.end();
        }

        ast *operator[](int i) {
            return children.at(i);
        }

    private:
        string text; 
        int code;
        string file;
        int line;
        int col;

        vector<ast*> children;

};


#endif
