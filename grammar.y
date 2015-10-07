%{

#include <string>
#include <iostream>
using namespace std;

#include "parser.h"

%}

%debug
%defines
%error-verbose
%token-table
%verbose

%token T_BLOCK
%token T_IDENT T_I32 T_F32 
%token T_INTCON T_FLOATCON
 
%token T_ROOT T_MECH T_TRAIT T_TRAITS
%token T_ERR

%right '='
%left '<' '>' T_GTEQ T_LTEQ T_EQ T_NEQ
%left T_SL T_SR
%left '+' '-'
%left '*' '/' '%'
%right T_POS T_NEG '!'
%left '[' '.'
%left '('

%start program

%%

program     : mech                      { set_parse_root($1); }
            ;

mech        : '{' traits '}'            { $$ = buildv($1, T_MECH, $2); }
            | '{' traits ';' '}'        { $$ = buildv($1, T_MECH, $2); }
            | '{' '}'                   { $$ = buildv($1, T_MECH); }
            ;

traits      : traits ';' trait          { adopt($1, $3); }
            | traits error ';'          { parse_error($2); $$ = $1; }
            | trait                     { $$ = buildv($1, T_TRAITS, $1); }
            ;

trait       : '.' tname ':' expr        { $$ = buildv($1, T_TRAIT, $2, $4); }
            ;

tname       : T_IDENT
            | T_I32
            | T_F32
            ;

expr        : con                       {  }
            ;

con         : T_INTCON                  {  }
            | T_FLOATCON                {  }
            ;
%%

string yy_name(int code) {
    return yytname[YYTRANSLATE(code)];
}

