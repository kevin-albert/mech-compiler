%{

#include <string>
using namespace std;
#include "parser.h"
#include "grammar.h"

#define YY_USER_ACTION scanner_useraction();

%}

%option 8bit
%option debug
%option nodefault
%option nounput
%option noyywrap
%option verbose
%option warn

LETTER         [A-Za-z_]
DIGIT          [0-9]
INT			   {DIGIT}+
FLOAT          ({DIGIT}+(\.{DIGIT}+)?)|(\.?{DIGIT}+)
IDENT          ({LETTER}({LETTER}|{DIGIT}|_)*)

%%


[ \t]+         { /* whitespace */ }
\n             { scanner_newline(); }
"i32"          { return scan_token(T_I32); }
"f32"          { return scan_token(T_F32); }
{INT}		   { return scan_token(T_INTCON); }
{FLOAT}        { return scan_token(T_FLOATCON); }
{IDENT}        { return scan_token(T_IDENT); }
"=="           { return scan_token(T_EQ); }
"!="           { return scan_token(T_NEQ); }
">="           { return scan_token(T_GTEQ); }
"<="           { return scan_token(T_LTEQ); }
">"            { return scan_token('>'); }
"<"            { return scan_token('<'); }
"="            { return scan_token('='); }
"+"            { return scan_token('+'); }
"-"            { return scan_token('-'); }
"*"            { return scan_token('*'); }
"/"            { return scan_token('/'); }
"%"            { return scan_token('%'); }
"!"            { return scan_token('!'); }
"("            { return scan_token('('); }
")"            { return scan_token(')'); }
"{"            { return scan_token('{'); }
"}"            { return scan_token('}'); }
"."            { return scan_token('.'); }
"["            { return scan_token('['); }
"]"            { return scan_token(']'); }
"."            { return scan_token('.'); }
";"            { return scan_token(';'); }
"|"            { return scan_token('|'); }
":"            { return scan_token(':'); }
.              { return bad_token("illegal token", ';'); }

%%
