%{
  /*_____Definition section_____literal c++ code between single "%"_____*/


  /*Necesary files to work.*/
  #include "y.tab.h" //yacc output file. Necesary to work.

  /*Necesary imports*/
  #include <string>
  #include <string.h>
  #include <stdlib.h>

  /*Function declaration*/
 void yyerror(std::string S); // Define error message
%}

%option yylineno 

comment ;.+ 
imme   \#-?(0x)?[a-fA-F0-9_]+
numero [a-fA-F0-9_]+

%%
  /*_____Rules section_____*/
 
  /*Operation keywords*/
(v|V)(a|A)(d|D)(d|D)          {yylval.id=strdup(yytext); return vaddition;} //VAdd = vector addition
(v|V)(s|S)(u|U)(b|B)          {yylval.id=strdup(yytext); return vsubtra;} //Vsub = vector substraction
(v|V)(x|X)(o|O)(r|R)          {yylval.id=strdup(yytext); return vxor;} //Vxor = vector xor
(v|V)(m|M)(u|U)(l|L)          {yylval.id=strdup(yytext); return vmultiple;} //vmul = vector multiplication  
(v|V)(a|A)(d|D)(d|D)(s|S)     {yylval.id=strdup(yytext); return vadditions;} //VAdds = vector addition scalar
(v|V)(s|S)(u|U)(b|B)(s|S)     {yylval.id=strdup(yytext); return vsubtras;} //Vsub = vector substraction scalar
(v|V)(x|X)(o|O)(r|R)(s|S)     {yylval.id=strdup(yytext); return vxors;} //Vxor = vector xor scalar
(v|V)(m|M)(u|U)(l|L)(s|S)     {yylval.id=strdup(yytext); return vmultiples;} //vmul = vector multiplication scalar  
(v|V)(a|A)(d|D)(d|D)(i|I)     {yylval.id=strdup(yytext); return vadditioni;} //VAdd = vector addition inmediate
(v|V)(s|S)(u|U)(b|B)(i|I)     {yylval.id=strdup(yytext); return vsubtrai;} //Vsub = vector substraction inmediate
(v|V)(x|X)(o|O)(r|R)(i|I)     {yylval.id=strdup(yytext); return vxori;} //Vxor = vector xor inmediate
(v|V)(m|M)(u|U)(l|L)(i|I)     {yylval.id=strdup(yytext); return vmultiplei;} //vmul = vector multiplication inmediate
(v|V)(r|R)(o|O)(t|T)          {yylval.id=strdup(yytext); return vrot;} //vrot = vector rotation 
(v|V)(r|R)(o|O)(t|T)(r|R)     {yylval.id=strdup(yytext); return vrotr;} //vrotr = vector rotation saving the result in other register
(v|V)(s|S)(t|T)               {yylval.id=strdup(yytext); return vstore;} //vst = vector store
(v|V)(l|L)(d|D)               {yylval.id=strdup(yytext); return vload;} //vld = vector load
(s|S)(m|M)(o|O)(v|V)          {yylval.id=strdup(yytext); return smove;} //smov = scalar move
(r|R)(e|E)(p|P)(e|E)(a|A)(t|T) {yylval.id=strdup(yytext); return vrepeat;} //REPEAT
(e|E)(n|N)(d|D)(r|R)(e|E)(p|P)(e|E)(a|A)(t|T) {yylval.id=strdup(yytext); return vendrepeat;} //REPEAT
(v|V)(l|L)(r|R)(o|O)(t|T)          {yylval.id=strdup(yytext); return vlrot;} //vrot = vector rotation 
(v|V)(l|L)(r|R)(o|O)(t|T)(r|R)     {yylval.id=strdup(yytext); return vlrotr;} //vrotr = vector rotation saving the result in other register

  /* Vector Registers*/
(v|V)[0-9]?         {yylval.id=strdup(yytext); return vreg;} //vector registers

 /* Scalar Registers*/
(s|S)[0-9]?         {yylval.id=strdup(yytext); return sreg;} //scalar registers
    
  /*Immediate*/
{imme}                  {yylval.id=strdup(yytext); return immediate;}
  
  /*Comments*/
{comment}                {yylval.id=strdup(yytext); return commentary;}
  
  /*Numbers*/
{numero}                {yylval.num=atoi(yytext); return number;}

  /*White Spaces*/
[,\[\]\n\=\!]                 {return yytext[0];}
[\t \s]                   {;}


%%
int yywrap(void){
  return 1;
}
