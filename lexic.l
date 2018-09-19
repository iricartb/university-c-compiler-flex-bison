   /* ################################### [ PRACTICA 3 ] ####################################### 
      ###                                                                                    ###
      ###   - Analitzador lèxic flex                                                         ###
      ###   - Ivan Ricart Borges                                                             ###
      ###                                                                                    ###
      
      ########################################################################################## */
      
   /* ########################################################################################## */


   /* ################################### [ DECLARACIO ] ####################################### */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sintactic.tab.h"
#include "lexic.h"
#include "symtab.h"

extern FILE * yyin;
FILE * fileLexLog;

int init_analisi_lexic_I(char * fileInput);
int end_analisi_lexic_I();
void gestioParaulesReservades();
void incFila();
void printErrorLex(char * str, char * lexema, int numFila, int numColumna);
void printErrorLexFull(char * str, char * lexema, char * str2, int numFila, int numColumna);
void writeLexLog(char * token, int id_token);

int numFila = 1, numColumna = 1;
int estat_tipus = 0;
%}

lletra                               [a-zA-Z]
digit        	                        [0-9]
guio                                      [_]
menys                                     [-]
punt                                      [.]
cometes_simples                           [']
neg_cometes_simples              [^'\x0A\x0D]
cometes_dobles                            ["]
neg_cometes_dobles               [^"\x0A\x0D]
carac_especials       [;(){}#:.?\x5B\x5D\x2C]
 
%X COMENTARI_SIMPLE
%X COMENTARI_MULTILINIA

%%

   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ Regles ]: per a tractar enters, floats, caràcters i Strings                     ##
      ##                                                                                      ##
      ########################################################################################## */
            
{digit}+{punt}{digit}+ { 
   writeLexLog("CONSTANT_FLOTANT", ID_FLOATING_CONSTANT);
   yylval.infoBison.valor = (char *) malloc((sizeof(char) * (yyleng + 1)));
   strncpy(yylval.infoBison.valor, yytext, yyleng);
   
   numColumna += yyleng;
   return ID_FLOATING_CONSTANT;
}

{digit}+ { 	
   writeLexLog("CONSTANT_ENTERA", ID_INTEGER_CONSTANT);
   yylval.infoBison.valor = (char *) malloc((sizeof(char) * (yyleng + 1)));
   strncpy(yylval.infoBison.valor, yytext, yyleng);
   
   numColumna += yyleng; 
   return ID_INTEGER_CONSTANT; 
}

{cometes_simples}{neg_cometes_simples}{cometes_simples} { 
   writeLexLog("CONSTANT_CARACTER", ID_CHARACTER_CONSTANT);
   yylval.infoBison.valor = (char *) malloc(2);
   yylval.infoBison.valor[0] = yytext[1]; yylval.infoBison.valor[1] = '\x00'; 
   
   numColumna += yyleng; 
   return ID_CHARACTER_CONSTANT;	
}

{cometes_simples}{neg_cometes_simples}{2,}{cometes_simples}       { printErrorLexFull("Caracters", yytext, "mal format", numFila, numColumna); numColumna += yyleng; }

{cometes_dobles}{neg_cometes_dobles}*{cometes_dobles} { 
   writeLexLog("STRING", ID_STRING);
   yylval.infoBison.valor = (char *) malloc((sizeof(char) * (yyleng - 1)));
   strncpy(yylval.infoBison.valor, (yytext + 1), yyleng - 2);
		
   numColumna += yyleng;
   return ID_STRING;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ Regles ]: tractament dels identificadors                                        ##
      ##                - si apareixen per primer cop => inserir a la taula de simbols        ##
      ##                - tractament de l'etiqueta typedef utilitzant estats                  ##
      ##                                                                                      ##
      ########################################################################################## */
      
({lletra}|{digit}|{guio})* { 
   struct t_simbol simbol;
   
   if ((yytext[0] >= 48) && (yytext[0] <= 57)) {
      printErrorLex("Identificador", yytext, numFila, numColumna);
   }
   else {
      if (sym_lookup(yytext, &simbol) == SYMTAB_OK) {
         writeLexLog(simbol.nomLexic, simbol.idLexic);
      
         yylval.infoBison.valor = (char *) malloc((sizeof(char) * (yyleng + 1)));
         strcpy(yylval.infoBison.valor, yytext);
         yylval.infoBison.tipus_var = simbol.tipus_var;  
         
         numColumna += yyleng;
         return simbol.idLexic;   
      } 
      else {
         writeLexLog("IDENTIFICADOR", ID_IDENTIFICADOR);
      
         yylval.infoBison.valor = (char *) malloc((sizeof(char) * (yyleng + 1)));
         strcpy(yylval.infoBison.valor, yytext);
         yylval.infoBison.tipus_var = TIPUS_NULL;
      
         numColumna += yyleng;
      
         return ID_IDENTIFICADOR;
      }	
   }	   
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ Regles ]: tractaments dels comentaris simples i multilinies amb estats          ##
      ##                                                                                      ##
      ########################################################################################## */
      
\x2f\x2f                                                          { BEGIN COMENTARI_SIMPLE; }
<COMENTARI_SIMPLE>\n                                              { incFila(); BEGIN 0; }
<COMENTARI_SIMPLE>.	                                              { numColumna += yyleng; }

\x2f\x2a                                                          { BEGIN COMENTARI_MULTILINIA; }
<COMENTARI_MULTILINIA>\x2a\x2f                                    { BEGIN 0; }
<COMENTARI_MULTILINIA>\n                                          { incFila(); }
<COMENTARI_MULTILINIA>.	                                          { numColumna += yyleng; }


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ Regles ]: tractaments dels simbols d'operació                                   ##
      ##                                                                                      ##
      ########################################################################################## */
      
("++"|"--"|"<="|">="|"=="|"!="|"&&"|"||"|"*="|"/="|"%="|"+="|"-="|"+"|"-"|"%"|"/"|"*"|"<"|">"|"="|"!"|\x7E|\x7C|\x26|\x5E) {
    
    yylval.infoBison.valor = (char *) malloc((sizeof(char) * (yyleng + 1)));
    strncpy(yylval.infoBison.valor, yytext, yyleng);
   
    if (yyleng == 1) { writeLexLog(yytext, yytext[0]); numColumna += yyleng; return yytext[0]; } 
    else {
       switch (yytext[0]) {
           case '+':   switch (yytext[1]) {
                          case '+' : writeLexLog("INC_OP", ID_INC_OP); numColumna += yyleng; return ID_INC_OP; break;
                          case '=' : writeLexLog("ADD_ASSIG", ID_ADD_ASSIG); numColumna += yyleng; return ID_ADD_ASSIG; break;
                       }
                       break;
                    
           case '-':   switch (yytext[1]) {
                          case '-' : writeLexLog("DEC_OP", ID_DEC_OP); numColumna += yyleng; return ID_DEC_OP; break;
                          case '=' : writeLexLog("SUB_ASSIG", ID_SUB_ASSIG); numColumna += yyleng; return ID_SUB_ASSIG; break;
                       }
                       break;
                    
           case '<': writeLexLog("LE_OP", ID_LE_OP); numColumna += yyleng; return ID_LE_OP; break;
           case '>': writeLexLog("GE_OP", ID_GE_OP); numColumna += yyleng; return ID_GE_OP; break;
           case '=': writeLexLog("EQ_OP", ID_EQ_OP); numColumna += yyleng; return ID_EQ_OP; break;
           case '!': writeLexLog("NE_OP", ID_NE_OP); numColumna += yyleng; return ID_NE_OP; break;
           case '&': writeLexLog("AND_OP", ID_AND_OP); numColumna += yyleng; return ID_AND_OP; break;
           case '|': writeLexLog("OR_OP", ID_OR_OP); numColumna += yyleng; return ID_OR_OP; break;
           case '*': writeLexLog("MUL_ASSIG", ID_MUL_ASSIG); numColumna += yyleng; return ID_MUL_ASSIG; break;
           case '/': writeLexLog("DIV_ASSIG", ID_DIV_ASSIG); numColumna += yyleng; return ID_DIV_ASSIG; break;
           case '%': writeLexLog("MOD_ASSIG", ID_MOD_ASSIG); numColumna += yyleng; return ID_MOD_ASSIG; break;
       }
    }
}

   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ Regles ]: tractaments dels caràcters especials                                  ##
      ##                                                                                      ##
      ########################################################################################## */
      
{carac_especials} {
   if (strcmp(yytext, ";") == 0) {
      writeLexLog("PUNT_I_COMA", ID_PUNT_I_COMA);  
   } 
   else if (strcmp(yytext, "{") == 0) {
      writeLexLog("CLAU_OBERTA", ID_CLAU_OBERTA);
   }
   else if (strcmp(yytext, "}") == 0) {
      writeLexLog("CLAU_TANCADA", ID_CLAU_TANCADA);
   }
   else if (strcmp(yytext, "(") == 0) {
      writeLexLog("PARENTESI_OBERT", ID_PARENTESI_OBERT);
   }
   else if (strcmp(yytext, ")") == 0) {
      writeLexLog("PARENTESI_TANCAT", ID_PARENTESI_TANCAT);
   }
   else if (strcmp(yytext, "#") == 0) {
      writeLexLog("COIXINETA", ID_COIXINETA);
   }
   else if (strcmp(yytext, ":") == 0) {
      writeLexLog("DOS_PUNTS", ID_DOS_PUNTS);
   }
   else if (strcmp(yytext, ".") == 0) {
      writeLexLog("PUNT", ID_PUNT);
   }
   else if (strcmp(yytext, "[") == 0) {
      writeLexLog("C_OBERT", ID_C_OBERT);
   }
   else if (strcmp(yytext, "]") == 0) {
      writeLexLog("C_TANCAT", ID_C_TANCAT);
   }
   else if (strcmp(yytext, "?") == 0) {
      writeLexLog("INTERROGANT", ID_INTERROGANT);
   }
   else if (strcmp(yytext, ",") == 0) {
      writeLexLog("COMA", ID_COMA);
   }
   numColumna += yyleng;
   return yytext[0];
}

\n                                                                { incFila(); }                                         
. { 
   if ((strcmp(yytext, "\x20") != 0) && (strcmp(yytext, "\r") != 0)) printErrorLex("Caracter", yytext, numFila, numColumna); 
   numColumna += yyleng; 
}

%%


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: init_analisi_lexic_I(char * fileInput)                                ##
      ##                   - fileInput: fitxer d'entrada (codi font)                          ##
      ##                                                                                      ##
      ########################################################################################## */
      
int init_analisi_lexic_I(char * fileInput) {
   int error; 
   yyin = fopen(fileInput, "r");

   if(yyin == NULL) error = EXIT_FAILURE;
   else { 
      fileLexLog = fopen(FILE_LEX_LOG, "w");
      
      if (fileLexLog == NULL) error = EXIT_FAILURE;
      else error = EXIT_SUCCESS;
   }

   return error;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: end_analisi_lexic_I(): tancament del fitxer d'entrada                 ##
      ##                                                                                      ##
      ########################################################################################## */
      
int end_analisi_lexic_I() {
   int error; 
   
   error = fclose(yyin);
   if (error == 0) { 
      error = fclose(fileLexLog);
      if (error == 0) error = EXIT_SUCCESS;
      else error = EXIT_FAILURE;
   }
   else error = EXIT_FAILURE;
   
   return error; 
}

void incFila() {
   numFila++;
   numColumna = 1;
}

   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIONS ]: sortida d'informació d'errors per pantalla                          ##
      ##                  sortida d'informació flex per fitxer                                ##
      ##                                                                                      ##      
      ########################################################################################## */
      
void printErrorLex(char * str, char * lexema, int numFila, int numColumna) {
   if (stdout != yyout) {
      fprintf(stdout, "\n[ LEXIC -> Error ] >>> linia %i columna %i: %s %s no reconegut\n", numFila, numColumna, str, lexema);
      fprintf(yyout, "[ LEXIC -> Error ] >>> linia %i columna %i: %s %s no reconegut\n", numFila, numColumna, str, lexema);
   }
   else fprintf(stderr, "\n[ LEXIC -> Error ] >>> linia %i columna %i: %s %s no reconegut\n", numFila, numColumna, str, lexema);    
}

void printErrorLexFull(char * str, char * lexema, char * str2, int numFila, int numColumna) {
   
   if (stdout != yyout) {
      fprintf(stdout, "\n[ LEXIC -> Error ] >>> linia %i columna %i: %s %s %s no reconegut\n", numFila, numColumna, str, lexema, str2);   
      fprintf(yyout, "[ LEXIC -> Error ] >>> linia %i columna %i: %s %s %s no reconegut\n", numFila, numColumna, str, lexema, str2);   
   }
   else fprintf(stderr, "[ LEXIC -> Error ] >>> linia %i columna %i: %s %s %s no reconegut\n", numFila, numColumna, str, lexema, str2);   
}

void writeLexLog(char * token, int id_token) {
   fprintf(fileLexLog, "%s %s %d %d %d\n", token, yytext, id_token, numFila, numColumna);   
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCION ]: gestioParaulesReservades(): inicialització taula de simbols          ##
      ##                                                                                      ##      
      ########################################################################################## */
      
void gestioParaulesReservades() {
   struct t_simbol simbol;   
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_AUTO;
   strcpy(simbol.nomLexic, "AUTO");
   sym_global_add("auto", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_BREAK;
   strcpy(simbol.nomLexic, "BREAK");
   sym_global_add("break", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_CASE;
   strcpy(simbol.nomLexic, "CASE");
   sym_global_add("case", &simbol);

   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_CONST;
   strcpy(simbol.nomLexic, "CONST");
   sym_global_add("const", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_CONTINUE;
   strcpy(simbol.nomLexic, "CONTINUE");
   sym_global_add("continue", &simbol);

   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_DEFAULT;
   strcpy(simbol.nomLexic, "DEFAULT");
   sym_global_add("default", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_DO;
   strcpy(simbol.nomLexic, "DO");
   sym_global_add("do", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_ELSE;
   strcpy(simbol.nomLexic, "ELSE");
   sym_global_add("else", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_ENUM;
   strcpy(simbol.nomLexic, "ENUM");
   sym_global_add("enum", &simbol);

   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_EXTERN;
   strcpy(simbol.nomLexic, "EXTERN");
   sym_global_add("extern", &simbol);

   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_FOR;
   strcpy(simbol.nomLexic, "FOR");
   sym_global_add("for", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_GOTO;
   strcpy(simbol.nomLexic, "GOTO");
   sym_global_add("goto", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_IF;
   strcpy(simbol.nomLexic, "IF");
   sym_global_add("if", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_REGISTER;
   strcpy(simbol.nomLexic, "REGISTER");
   sym_global_add("register", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_RETURN;
   strcpy(simbol.nomLexic, "RETURN"); 
   sym_global_add("return", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_SIGNED;
   strcpy(simbol.nomLexic, "SIGNED");
   sym_global_add("signed", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_SIZEOF;
   strcpy(simbol.nomLexic, "SIZEOF");
   sym_global_add("sizeof", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_STATIC;
   strcpy(simbol.nomLexic, "STATIC");
   sym_global_add("static", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_STRUCT;
   strcpy(simbol.nomLexic, "STRUCT");
   sym_global_add("struct", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_SWITCH;
   strcpy(simbol.nomLexic, "SWITCH");
   sym_global_add("switch", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_TYPEDEF;
   strcpy(simbol.nomLexic, "TYPEDEF");
   sym_global_add("typedef", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_UNION;
   strcpy(simbol.nomLexic, "UNION");
   sym_global_add("union", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_UNSIGNED;
   strcpy(simbol.nomLexic, "UNSIGNED");
   sym_global_add("unsigned", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_VOLATILE;
   strcpy(simbol.nomLexic, "VOLATILE");   
   sym_global_add("volatile", &simbol);
   
   simbol.tipus = PARAULA_RESERVADA;
   simbol.idLexic = ID_WHILE;
   strcpy(simbol.nomLexic, "WHILE");
   sym_global_add("while", &simbol); 
   
   simbol.tipus = TIPUS_BASIC;
   simbol.idLexic = ID_VOID;
   strcpy(simbol.nomLexic, "VOID");
   sym_global_add("void", &simbol);
   
   simbol.tipus = TIPUS_BASIC;
   simbol.idLexic = ID_CHAR;
   strcpy(simbol.nomLexic, "CHAR");
   sym_global_add("char", &simbol);
   
   simbol.tipus = TIPUS_BASIC;
   simbol.idLexic = ID_INT;
   strcpy(simbol.nomLexic, "INT");
   sym_global_add("int", &simbol);
   
   simbol.tipus = TIPUS_BASIC;
   simbol.idLexic = ID_LONG;
   strcpy(simbol.nomLexic, "LONG");
   sym_global_add("long", &simbol);

   simbol.tipus = TIPUS_BASIC;
   simbol.idLexic = ID_SHORT;
   strcpy(simbol.nomLexic, "SHORT");
   sym_global_add("short", &simbol);
   
   simbol.tipus = TIPUS_BASIC;
   simbol.idLexic = ID_FLOAT;
   strcpy(simbol.nomLexic, "FLOAT");
   sym_global_add("float", &simbol);
   
   simbol.tipus = TIPUS_BASIC;
   simbol.idLexic = ID_DOUBLE;
   strcpy(simbol.nomLexic, "DOUBLE");
   sym_global_add("double", &simbol);
}
