   /* ################################### [ PRACTICA 3 ] ####################################### 
      ###                                                                                    ###
      ###   - Analitzador sintàctic bison                                                    ###
      ###   - Ivan Ricart Borges                                                             ###
      ###                                                                                    ###
      
      ########################################################################################## */

   /* ########################################################################################## */


   /* ################################### [ DECLARACIO ] ####################################### */
         
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "sintactic.tab.h"
#include "symtab.h"
#include "cua.h"

typedef struct t_cadenaRegistreActivacio {
   char * nom;    
   int tam_tipus;
   int tipus;
   int es_array;
   long tam_array;
   long tam_total;
   long offset;
   struct t_cadenaRegistreActivacio * seguent;
} t_cadenaRegistreActivacio;

typedef struct t_registreActivacio {
    char * nom_registre;  
    long currentOffset; 
	int num_llista_parametres, num_llista_locals, num_llista_temporals;
	
	t_cadenaRegistreActivacio * primer_llista_parametres, * primer_llista_locals, * primer_llista_temporals;
	t_cadenaRegistreActivacio * ultim_llista_parametres, * ultim_llista_locals, * ultim_llista_temporals;
} t_registreActivacio;

typedef struct t_registreC3A {
	int num_quadruples;
	Cua * quadrupleC3A;
} t_registreC3A;

typedef struct t_quadrupleC3A {
	int num_sentencia;
	char * sentenciaC3A;
} t_quadrupleC3A;

FILE * fRegActivacio, * fCodi3A;
extern FILE * yyout;
extern int numFila;
extern int yyleng;
extern void yyerror(char * explanation);

int init_analisi_sintactic_O(char * fileOutput, char * nomFitxerRA, char * nomFitxerC3A);
int end_analisi_sintactic_O();
void init_analisi_sintactic(char * nomFitxerRA);
int analisi_semantic();
void printErrorSintactic(Boolean err, char * errorDesc, ...);
void printInfoSintactic(char * desc, ...);
int comprovacioTipusDades(Tipus_Dades t1, Tipus_Dades t2, int vsituacio);
Boolean identificadorDeclarat(char * idSimbol);
Boolean identificadorDeclaratMateixAmbit(char * idSimbol);
void printSimbolInfo(char * idSimbol);
char * tipusDadesID(int idTipus, int espais);
int checkOperadorIncDec(struct t_infoBison p1);
int esTipus(char * nom);
int campExisteixStruct(char * nomStruct, char * campStruct);
int campStructEsArray(char * nomStruct, char * campStruct);

int iniRegistreActivacio(t_registreActivacio * pRegistreActivacio, char * nom_registre);
int iniRegistreActivacioFuncions(char * nom_registre);
int iniC3A(t_registreC3A * pC3A);
int iniC3AFuncions();
void afegirParamRA(t_registreActivacio * pRegistreActivacio, char * nom_var, int tipus_var, int es_array, long tam_array);
void afegirVarLocalRA(t_registreActivacio * pRegistreActivacio, char * nom_var, struct t_simbol * simbol);
char * afegirVarTemporalRA(t_registreActivacio * pRegistreActivacio, int tipusVarTemp);
void printRegistreActivacio(t_registreActivacio * pRegistreActivacio);
void printRegistreActivacioGlobal(t_registreActivacio * pRegistreActivacio);
void printC3AFuncions(t_registreC3A * pC3A, char * nom_funcio);
int tamanyStruct(struct t_simbol * p1);
int tamanyStructbyInfoBison(struct t_infoBison * p1);
int offsetCampStruct(struct t_simbol * p1, char * nomCamp);
int tamanyTipusVar(int tipus);
int operacioC3A(Tipus_Dades t1, Tipus_Dades t2, int operacio);
void emet_cridaC3A(char * nom_funcio, struct t_infoBison * parametres, int tipus_retorn, struct t_infoBison * paramResult);
void emet_condicioC3A(struct t_infoBison * param1, struct t_infoBison * paramResult);
void emet_operacioC3A(struct t_infoBison * param1, struct t_infoBison * param2, struct t_infoBison * paramResult, int operacio);
void emet_operacioCanviSigneC3A(struct t_infoBison * param1, struct t_infoBison * paramResult);
void emet_arrayC3A(struct t_infoBison * paramResult, struct t_infoBison * paramArray, struct t_infoBison * paramArrayIndex);
void emet_structC3A(struct t_infoBison * paramStruct);
void emet_saltC3A(int num_linia);
void emet_retornFuncioC3A(struct t_infoBison * param1);
void completar_llista(Cua * llista, int seguent);

char * idSimbol;
char * nom_fitxerRA, * nom_fitxerC3A;
struct t_simbol simbol, simbol_tmp;
int currentScope;
long long tmpValor;
Boolean arrayDeclaracio = FALSE;
struct t_infoBison * pparam;
struct t_infoBison * pcamp;
struct t_infoBison * recordsetParam;
struct t_infoBison * recordsetCamp;
struct t_infoBison * tmpCondicio;
int num_errors;
int tipus_var_funcio_retorn;
char * valor_retorn;
struct Cua * llista_seguents_funcio_retorn;
int count;
int funcioDeclaradaCorrecte = FALSE;
Boolean errFuncDeclaration = FALSE;
t_registreActivacio * registreActivacioGlobal, * registreActivacioFuncions;
t_registreC3A * C3AGlobal, * C3AFuncions;
char strCastingC3A[4], strOperacioC3A[5];
t_quadrupleC3A * quadrupleC3A;
int conditional_if_while_for;
int tipus_var_tmp;
%}

       /* #####################################################################################################
          ##                                                                                                 ##
              parametres per els arrays
                     - array: indica si es o no array.
                     - tam_array: tamany del array, si el tamany es declara major que LONG_MAX el compilador
                                  visualitzarà un error, posteriorment el array serà redimensionat al seu 
                                  tamany màxim -> LONG_MAX.
              
              parametres per les funcions
                     - funcio: indica si es o no funció.
                     - num_funcio_parametres: numero de paràmetres de la funció.                            
                     - seguent_param_funcio: apuntador al seguent paràmetre, si no n'hi ha apunta a a NULL.  
              
              parametres per les estructures
                     - tipus_var: TIPUS_STRUCT
                     - num_struct_camps: numero de camps de l'estructura.                            
                     - seguent_camp_struct: apuntador al seguent camp, si no n'hi ha apunta a a NULL. 
          ##                                                                                                 ##
          ##################################################################################################### */
          
%union { 	   
    struct t_infoBison {   
       char * valor;
       char * valorC3A;
       int constant;      
       int tipus_var;
       int array;
       long tam_array;
       int array_indexat;
       char * array_indexat_offset;
       int camp_struct_indexat;
       int offset_camp_struct_indexat;
       int funcio;
       int num_funcio_parametres;
       int num_struct_camps;
       struct t_infoBison * seguent_param_funcio;
       struct t_infoBison * seguent_camp_struct;
	   struct Cua * llista_certs;       
  	   struct Cua * llista_falsos;
	   struct Cua * llista_seguents;
	   int punter_quadruple;
       void * no_definit;	
    } infoBison;
}

%token <no_definit>  ID_AUTO ID_BREAK ID_CASE ID_CHAR ID_CONST ID_CONTINUE ID_DEFAULT ID_DO ID_DOUBLE ID_ELSE ID_ENUM ID_EXTERN ID_FLOAT ID_FOR ID_GOTO         
                     ID_IF ID_INT ID_LONG ID_REGISTER ID_RETURN ID_SHORT ID_SIGNED ID_SIZEOF ID_STATIC ID_STRUCT ID_SWITCH ID_TYPEDEF ID_UNION ID_UNSIGNED                               
                     ID_VOID ID_VOLATILE ID_WHILE ID_INC_OP ID_DEC_OP ID_LE_OP ID_GE_OP ID_EQ_OP ID_NE_OP ID_AND_OP ID_OR_OP ID_MUL_ASSIG ID_DIV_ASSIG 
                     ID_MOD_ASSIG ID_ADD_ASSIG ID_SUB_ASSIG                             

%token <infoBison>  ID_IDENTIFICADOR         
%token <infoBison>  ID_TYPEDEF_IDENTIFIER    
%token <infoBison>  ID_CHARACTER_CONSTANT    
%token <infoBison>  ID_INTEGER_CONSTANT      
%token <infoBison>  ID_FLOATING_CONSTANT     
%token <infoBison>  ID_STRING                

%type <no_definit> type_name struct_or_union specifier_qualifier_list jump_statement declaration_list
%type <no_definit> expression_statement iteration_statement labeled_statement    
%type <no_definit> unary_operator external_declaration translation_unit

%type <infoBison> type_specifier declaration_specifiers declarator constant primary_expression postfix_expression unary_expression multiplicative_expression struct_declaration
%type <infoBison> additive_expression relational_expression equality_expression logical_AND_expression logical_OR_expression conditional_expression assignment_expression
%type <infoBison> initializer init_declarator cast_expression constant_expression init_declarator_list typedef_name expression declaration parameter_list parameter_declaration
%type <infoBison> statement_list argument_expression_list function_definition identifier_list compound_statement statement initializer_list abstract_declarator struct_declarator
%type <infoBison> struct_declarator_list struct_declaration_list struct_or_union_specifier assignment_operator selection_statement if_cond_header
%type <infoBison> M N

%right <no_definit> '='
%left  <no_definit> '+' '-'
%left  <no_definit> '*' '/'

%expect 1

%start translation_unit

%%

/* ============================================================================================ */
/* ==================================== [ primary_expression ] ================================ */
/* ============================================================================================ */
primary_expression : 
   ID_IDENTIFICADOR {
      $$ = $<infoBison>1;
      $$.funcio = FALSE; 
      
      fprintf(yyout, ">>> linia %i: ID_IDENTIFICADOR -> [%s] REDUCE TO primary_expression\n", numFila, $<infoBison>1.valor);     
   }
   | constant { 
      $$ = $<infoBison>1;
      $$.array = FALSE;
      $$.tam_array = 0;
      
      fprintf(yyout, ">>> linia %i: constant REDUCE TO primary_expression\n", numFila); 
   }
   | ID_STRING {
      $$ = $<infoBison>1;
      $$.constant = TRUE;       
      $$.tipus_var = TIPUS_STRING;
      $$.array = FALSE;
      $$.tam_array = 0;
            
      fprintf(yyout, ">>> linia %i: ID_STRING -> [%s] REDUCE TO primary_expression\n", numFila, $<infoBison>1.valor);
   }
   | '(' expression ')' { 
      $$ = $<infoBison>2;

      fprintf(yyout, ">>> linia %i: (expression) REDUCE TO primary_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ======================================== [ constant ] ====================================== */
/* ============================================================================================ */
constant :
   ID_INTEGER_CONSTANT {
      $$ = $<infoBison>1;
      $$.constant = TRUE;       
      $$.tipus_var = TIPUS_INTEGER;
          
      fprintf(yyout, ">>> linia %i: ID_INTEGER_CONSTANT -> [%s] REDUCE TO constant\n", numFila, $<infoBison>1.valor);    
   } 
   | ID_CHARACTER_CONSTANT {
      $$ = $<infoBison>1;                     
      $$.constant = TRUE;       
      $$.tipus_var = TIPUS_CHARACTER;
            
      fprintf(yyout, ">>> linia %i: ID_CHARACTER_CONSTANT -> [%s] REDUCE TO constant\n", numFila, $<infoBison>1.valor);
   }
   | ID_FLOATING_CONSTANT {
      $$ = $<infoBison>1;
      $$.constant = TRUE;       
      $$.tipus_var = TIPUS_FLOAT;
      
      fprintf(yyout, ">>> linia %i: ID_FLOATING_CONSTANT -> [%s] REDUCE TO constant\n", numFila, $<infoBison>1.valor);
   }
;

/* ============================================================================================ */
/* ==================================== [ postfix_expression ] ================================ */
/* ============================================================================================ */
postfix_expression : 
   primary_expression {
      $$ = $<infoBison>1;
      
      if ($<infoBison>1.constant != TRUE) {
         if (!identificadorDeclarat($<infoBison>1.valor)) {
            $$.tipus_var = TIPUS_NULL;
            if ($<infoBison>1.funcio == TRUE) { num_errors++; printErrorSintactic(TRUE, ERR_NO_DECLARADA_FUNC_VAR, "funcio", $<infoBison>1.valor); }               
            else { num_errors++; printErrorSintactic(TRUE, ERR_NO_DECLARADA_FUNC_VAR, "variable", $<infoBison>1.valor); }
         }
         else {
            $$.tipus_var = $<infoBison>1.tipus_var;
            
            if (simbol.funcio == TRUE) printInfoSintactic(OK_CONSULTA_TAULA_SIMBOL_FUN_VAR, "funcio", $<infoBison>1.valor);
            else printInfoSintactic(OK_CONSULTA_TAULA_SIMBOL_FUN_VAR, "variable", $<infoBison>1.valor);
         }
      }
      else $$.tipus_var = $<infoBison>1.tipus_var;
         
      fprintf(yyout, ">>> linia %i: primary_expression REDUCE TO postfix_expression\n", numFila);
   }
   | postfix_expression '[' expression ']' {
      $$ = $<infoBison>1;
      $$.array = TRUE;
      $$.tipus_var = TIPUS_NULL;
      
      if ($<infoBison>1.constant != TRUE) {
         if (identificadorDeclarat($<infoBison>1.valor)) {
            if (simbol.array == TRUE) {
               if ($<infoBison>3.tipus_var < 5) {
                  if (atol($<infoBison>3.valor) >= simbol.tam_array) {
                     num_errors++; printErrorSintactic(TRUE, ERR_INDEX_ARRAY_FORA_RANG, $<infoBison>1.valor);
                  }
                  else { 
                     $$.tipus_var = simbol.tipus_var; 
                     
                     if ($<infoBison>1.valorC3A == NULL) {
                        $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
                        strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
                     }
                     if ($<infoBison>3.valorC3A == NULL) {
                        $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
                        strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
                     }
                              
                     emet_arrayC3A(&$<infoBison>$, &$<infoBison>1, &$<infoBison>3);
                     
                     printInfoSintactic(OK_INDEX_ARRAY, $<infoBison>1.valor, $<infoBison>3.valor);
                  }
               }
               else { num_errors++; printErrorSintactic(TRUE, ERR_INDEX_ARRAY_NO_INT, $<infoBison>1.valor); }   
            }   
            else { num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_ARRAY, $<infoBison>1.valor); }
         }
      }
      else { num_errors++; printErrorSintactic(TRUE, ERR_CONSTANT_NO_VARIABLE, $<infoBison>1.valor, "ARRAY"); }
      
      fprintf(yyout, ">>> linia %i: postfix_expression[expression] REDUCE TO postfix_expression\n", numFila);
   }
   | postfix_expression '(' ')' {
      $$ = $<infoBison>1;                  
      $$.funcio = TRUE;
      $$.tipus_var = TIPUS_NULL;
      
      if ($<infoBison>1.constant != TRUE) {
         if (identificadorDeclarat($<infoBison>1.valor)) {
            if (simbol.funcio == TRUE) {
               if (simbol.num_funcio_parametres == 0) {
                  $$.tipus_var = simbol.tipus_var;
                  
                  emet_cridaC3A($<infoBison>1.valor, NULL, simbol.tipus_var, &$<infoBison>$);
                  printInfoSintactic(OK_CRIDA_FUNCIO, $<infoBison>1.valor);
               }
               else {
                  num_errors++;  
                  printErrorSintactic(TRUE, ERR_FUNCIO_PARAMS_INSUFICIENTS, $<infoBison>1.valor);   
               }                   
            }
            else { num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_FUNCIO, $<infoBison>1.valor); }
         }
      }
      else { num_errors++; printErrorSintactic(TRUE, ERR_CONSTANT_NO_VARIABLE, $<infoBison>1.valor, "FUNCIO"); }
      
      fprintf(yyout, ">>> linia %i: postfix_expression() REDUCE TO postfix_expression\n", numFila);
   }
   | postfix_expression '(' argument_expression_list ')' {
      $$ = $<infoBison>1;                  
      $$.funcio = TRUE;
      $$.tipus_var = TIPUS_NULL;
      
      funcioDeclaradaCorrecte = TRUE;
      if ($<infoBison>1.constant != TRUE) {
         if (identificadorDeclarat($<infoBison>1.valor)) {
            if (simbol.funcio == TRUE) {
               if (simbol.num_funcio_parametres == 0) {
                  num_errors++;                              
                  printErrorSintactic(TRUE, ERR_FUNCIO_PARAMS_EXCESIUS, $<infoBison>1.valor);
               }
               else {
                  if (simbol.num_funcio_parametres != $<infoBison>3.num_funcio_parametres) {
                     num_errors++;
                     printErrorSintactic(TRUE, ERR_FUNCIO_NUM_PARAMS_DIFERENTS, $<infoBison>1.valor);  
                  }
                  else {
                     /* Numero de parametres correctes per cridar la funcio */
                     recordsetParam = $<infoBison>3.seguent_param_funcio; 
                     for (count = 0; count < $<infoBison>3.num_funcio_parametres; count++) {
                        if ((recordsetParam -> constant == FALSE) && (sym_lookup(recordsetParam -> valor, &simbol_tmp) != SYMTAB_OK)) {
                           funcioDeclaradaCorrecte = FALSE;
                        }
                        else {
                           if ((simbol.funcio_params[count].tipus_var != TIPUS_NULL) && (recordsetParam -> tipus_var != TIPUS_NULL)) {
                              if (recordsetParam -> constant == FALSE) {
                                 /* Si ens han passat una variable declarada => comprovacio de tipus i d'arrays */
                                 if ((simbol_tmp.array != TRUE) && (simbol.funcio_params[count].array == TRUE)) {
                                    num_errors++; funcioDeclaradaCorrecte = FALSE; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ES_ARRAY, count + 1, $<infoBison>1.valor);
                                 }
                                 /* Variable que ens passen es un array i la declaracio de la funcio no ho és: es poden donar 2 casos, que l'array s'accedeixi de forma indexada o no. */
                                 /* Forma no indexada es incorrecte */
                                 else if ((simbol_tmp.array == TRUE) && (simbol.funcio_params[count].array != TRUE) && (recordsetParam -> array != TRUE)) {
                                    num_errors++; funcioDeclaradaCorrecte = FALSE; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_NO_ES_ARRAY, count + 1, $<infoBison>1.valor);
                                 }
                                 /* Forma en que els 2 casos son arrays, pero s'indexa => error */
                                 else if ((simbol_tmp.array == TRUE) && (simbol.funcio_params[count].array == TRUE) && (recordsetParam -> array == TRUE)) {
                                    num_errors++; funcioDeclaradaCorrecte = FALSE; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ARRAY_METODE_ACCESS, count + 1, $<infoBison>1.valor);
                                 }
                                 else {
                                    comprovacioTipusDades(simbol.funcio_params[count].tipus_var, recordsetParam -> tipus_var, ID_SITUACIO_FUNCIO);
                                 }
                              }
                              else {
                                 /* Si ens han passat una constant => comprovacio de tipus i d'array en la funcio */
                                 if (simbol.funcio_params[count].array == TRUE) {
                                    num_errors++; funcioDeclaradaCorrecte = FALSE; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ES_ARRAY, count + 1, $<infoBison>1.valor);   
                                 }
                                 else {
                                    comprovacioTipusDades(simbol.funcio_params[count].tipus_var, recordsetParam -> tipus_var, ID_SITUACIO_FUNCIO);
                                 }
                              }
                           }
                           else if (recordsetParam -> tipus_var == TIPUS_NULL) {
                              funcioDeclaradaCorrecte = FALSE;
                           }      
                        }
                        recordsetParam = recordsetParam -> seguent_param_funcio;
                     }
                     if (funcioDeclaradaCorrecte) {
                        $$.tipus_var = simbol.tipus_var;
                        
                        emet_cridaC3A($<infoBison>1.valor, &$<infoBison>3, simbol.tipus_var, &$<infoBison>$);
                        printInfoSintactic(OK_CRIDA_FUNCIO, $<infoBison>1.valor);   
                     }
                     else { num_errors++; printErrorSintactic(TRUE, ERR_CRIDA_FUNCIO, $<infoBison>1.valor); }
                  }
               }
            }
            else { num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_FUNCIO, $<infoBison>1.valor); }
         }                           
      }
      
      fprintf(yyout, ">>> linia %i: postfix_expression(argument_expression_list) REDUCE TO postfix_expression\n", numFila);
   }
   | postfix_expression '.' ID_IDENTIFICADOR {
      $$ = $<infoBison>1;
      $$.tipus_var = TIPUS_NULL;
      
      if ($<infoBison>1.constant == TRUE) {
         num_errors++;                        
         printErrorSintactic(TRUE, ERR_STRUCT_CONSTANT);
      }
      else {
         if (identificadorDeclarat($<infoBison>1.valor)) {
            if (simbol.tipus_var != TIPUS_STRUCT) {
               num_errors++;                  
               printErrorSintactic(TRUE, ERR_STRUCT_TIPUS_DIFERENT, $<infoBison>1.valor);
            }
            else {
               $$.tipus_var = campExisteixStruct($<infoBison>1.valor, $<infoBison>3.valor);
               if ($$.tipus_var == TIPUS_NULL) {
                  num_errors++;
                  printErrorSintactic(TRUE, ERR_CAMP_NO_EXISTEIX_STRUCT, $<infoBison>3.valor, $<infoBison>1.valor);
               }
               else {
                  $$.offset_camp_struct_indexat = offsetCampStruct(&simbol, $<infoBison>3.valor);
                  $$.camp_struct_indexat = TRUE;
                  
                  printInfoSintactic(OK_CAMP_EXISTEIX_STRUCT, $<infoBison>3.valor, $<infoBison>1.valor);
               }
            }
         }
      }
      
      fprintf(yyout, ">>> linia %i: postfix_expression.ID_IDENTIFICADOR -> [%s] REDUCE TO postfix_expression\n", numFila, $<infoBison>3.valor);
   }
   | postfix_expression ID_INC_OP {
      $$ = $<infoBison>1;
      $$.tipus_var = TIPUS_NULL;
      
      if ($<infoBison>1.constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DEC_O_INC_CONSTANT, "incrementar");
      }
      else { 
         $$.tipus_var = checkOperadorIncDec($<infoBison>1);
         $<infoBison>2.valorC3A = malloc(2); strcpy($<infoBison>2.valorC3A, "1");
         
         if ($<infoBison>1.valorC3A == NULL) {
            $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
            strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
         }
         $<infoBison>2.constant = TRUE;
         $<infoBison>2.tipus_var = TIPUS_INTEGER;     
         $<infoBison>2.array_indexat = FALSE;
         $<infoBison>2.camp_struct_indexat = FALSE;
             
         emet_operacioC3A(&$<infoBison>1, &$<infoBison>2, &$<infoBison>$, '+');
         emet_operacioC3A(&$<infoBison>$, NULL, &$<infoBison>1, '=');
      }
      fprintf(yyout, ">>> linia %i: postfix_expression++ REDUCE TO postfix_expression\n", numFila);
   }
   | postfix_expression ID_DEC_OP {
      $$ = $<infoBison>1;
      $$.tipus_var = TIPUS_NULL;
      
      if ($<infoBison>1.constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DEC_O_INC_CONSTANT, "decrementar");
      }
      else {
         $$.tipus_var = checkOperadorIncDec($<infoBison>1);
         $<infoBison>2.valorC3A = malloc(2); strcpy($<infoBison>2.valorC3A, "1");
         
         if ($<infoBison>1.valorC3A == NULL) {
            $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
            strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
         }
         $<infoBison>2.constant = TRUE;
         $<infoBison>2.tipus_var = TIPUS_INTEGER;     
         $<infoBison>2.array_indexat = FALSE;
         $<infoBison>2.camp_struct_indexat = FALSE;
             
         emet_operacioC3A(&$<infoBison>1, &$<infoBison>2, &$<infoBison>$, '-');
         emet_operacioC3A(&$<infoBison>$, NULL, &$<infoBison>1, '=');
      }
      fprintf(yyout, ">>> linia %i: postfix_expression-- REDUCE TO postfix_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================= [ argument_expression_list ] ============================= */
/* ============================================================================================ */
argument_expression_list : 
   assignment_expression {
      $$ = $<infoBison>1;
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = $<infoBison>1;
      pparam->tipus_var = $<infoBison>1.tipus_var;
      pparam->seguent_param_funcio = NULL;
      
      $$.seguent_param_funcio = pparam;
      $$.num_funcio_parametres = 1;
      
      fprintf(yyout, ">>> linia %i: assignment_expression REDUCE TO argument_expression_list\n", numFila);      
   }
   | argument_expression_list ',' assignment_expression {
      $$ = $<infoBison>1;
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = $<infoBison>3;
      pparam->seguent_param_funcio = NULL;
      pparam->tipus_var = $<infoBison>3.tipus_var;
      
      recordsetParam = $$.seguent_param_funcio; 
      for (count = 1; count < $$.num_funcio_parametres; count++) {
         recordsetParam = recordsetParam -> seguent_param_funcio;
      }
      recordsetParam -> seguent_param_funcio = pparam;
      $$.num_funcio_parametres++;
      
      fprintf(yyout, ">>> linia %i: argument_expression_list,assignment_expression REDUCE TO argument_expression_list\n", numFila);  
   }
;

/* ============================================================================================ */
/* ==================================== [ unary_expression ] ================================== */
/* ============================================================================================ */
unary_expression : 
   postfix_expression {
      $$ = $<infoBison>1;
       
      fprintf(yyout, ">>> linia %i: postfix_expression REDUCE TO unary_expression\n", numFila);    
   }
   | ID_INC_OP unary_expression {
      $$ = $<infoBison>2;
      $$.tipus_var = TIPUS_NULL;
      
      if ($<infoBison>2.constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DEC_O_INC_CONSTANT, "incrementar");
      }
      else {
         $$.tipus_var = checkOperadorIncDec($<infoBison>2);
         $<infoBison>1.valorC3A = malloc(2); strcpy($<infoBison>1.valorC3A, "1");
         
         if ($<infoBison>2.valorC3A == NULL) {
            $<infoBison>2.valorC3A = malloc(strlen($<infoBison>2.valor) + 1); 
            strcpy($<infoBison>2.valorC3A, $<infoBison>2.valor);
         }
         $<infoBison>1.constant = TRUE;
         $<infoBison>1.tipus_var = TIPUS_INTEGER;     
         $<infoBison>1.array_indexat = FALSE;
         $<infoBison>1.camp_struct_indexat = FALSE;
             
         emet_operacioC3A(&$<infoBison>2, &$<infoBison>1, &$<infoBison>$, '+');
         emet_operacioC3A(&$<infoBison>$, NULL, &$<infoBison>2, '=');
      }
            
      fprintf(yyout, ">>> linia %i: ++unary_expression REDUCE TO unary_expression\n", numFila);      
   }
   | ID_DEC_OP unary_expression {
      $$ = $<infoBison>2;
      $$.tipus_var = TIPUS_NULL;
      
      if ($<infoBison>2.constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DEC_O_INC_CONSTANT, "decrementar");
      }
      else {
         $$.tipus_var = checkOperadorIncDec($<infoBison>2);
         $<infoBison>1.valorC3A = malloc(2); strcpy($<infoBison>1.valorC3A, "1");
         
         if ($<infoBison>2.valorC3A == NULL) {
            $<infoBison>2.valorC3A = malloc(strlen($<infoBison>2.valor) + 1); 
            strcpy($<infoBison>2.valorC3A, $<infoBison>2.valor);
         }
         $<infoBison>1.constant = TRUE;
         $<infoBison>1.tipus_var = TIPUS_INTEGER;     
         $<infoBison>1.array_indexat = FALSE;
         $<infoBison>1.camp_struct_indexat = FALSE;
             
         emet_operacioC3A(&$<infoBison>2, &$<infoBison>1, &$<infoBison>$, '-');
         emet_operacioC3A(&$<infoBison>$, NULL, &$<infoBison>2, '=');
      }      
      fprintf(yyout, ">>> linia %i: --unary_expression REDUCE TO unary_expression\n", numFila);
   }
   | unary_operator cast_expression {
      $$ = $<infoBison>2;
      
      if (strcmp($<infoBison>1.valor, "!") == 0) {
         $<infoBison>$.llista_certs = $<infoBison>2.llista_falsos;
         $<infoBison>$.llista_falsos = $<infoBison>2.llista_certs;
      }
      else if (strcmp($<infoBison>1.valor, "-") == 0) {
         if ($<infoBison>2.valorC3A == NULL) {
            $<infoBison>2.valorC3A = malloc(strlen($<infoBison>2.valor) + 1); 
            strcpy($<infoBison>2.valorC3A, $<infoBison>2.valor);
         }
         
         emet_operacioCanviSigneC3A(&$<infoBison>2, &$<infoBison>$);
      }
          
      fprintf(yyout, ">>> linia %i: unary_operator cast_expression REDUCE TO unary_expression\n", numFila);
   }
   | ID_SIZEOF unary_expression {
      $$ = $<infoBison>2;
      $$.tipus_var = TIPUS_INTEGER;
      
      fprintf(yyout, ">>> linia %i: ID_SIZEOF unary_expression REDUCE TO unary_expression\n", numFila);
   }
   | ID_SIZEOF '(' type_name ')' {
      $$ = $<infoBison>2;
      $$.tipus_var = TIPUS_INTEGER;
      
      fprintf(yyout, ">>> linia %i: ID_SIZEOF (type_name) REDUCE TO unary_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ===================================== [ unary_operator ] =================================== */
/* ============================================================================================ */
unary_operator : 
   '+' { 
      fprintf(yyout, ">>> linia %i: '+' REDUCE TO unary_operator\n", numFila);   
   }
   | '-' {
      fprintf(yyout, ">>> linia %i: '-' REDUCE TO unary_operator\n", numFila);
   }
   | '!' {
      fprintf(yyout, ">>> linia %i: '!' REDUCE TO unary_operator\n", numFila);   
   }
;

/* ============================================================================================ */
/* ===================================== [ cast_expression ] ================================== */
/* ============================================================================================ */
cast_expression : 
   unary_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: unary_expression REDUCE TO cast_expression\n", numFila);
   }
   | '(' type_name ')' cast_expression {
      fprintf(yyout, ">>> linia %i: (type_name) cast_expression REDUCE TO cast_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================ [ multiplicative_expression ] ============================= */
/* ============================================================================================ */
multiplicative_expression : 
   cast_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: cast_expression REDUCE TO multiplicative_expression\n", numFila);
   }
   | multiplicative_expression '*' cast_expression {
      $$ = $<infoBison>1; 
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);  

      if ($<infoBison>1.valorC3A == NULL) {
         $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
         strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
      }
      if ($<infoBison>3.valorC3A == NULL) {
         $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
         strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
      }      
         
      emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, '*');
         
      fprintf(yyout, ">>> linia %i: multiplicative_expression '*' cast_expression REDUCE TO multiplicative_expression\n", numFila);
   }
   | multiplicative_expression '/' cast_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = TIPUS_NULL;
      
      if (strcmp($<infoBison>3.valor, "0") == 0) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_DIVISIO_PER_ZERO);
      }
      else {
         $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);
         
         if ($<infoBison>1.valorC3A == NULL) {
            $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
            strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
         }
         if ($<infoBison>3.valorC3A == NULL) {
            $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
            strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
         }      
         
         emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, '/');
      }
      
      fprintf(yyout, ">>> linia %i: multiplicative_expression '/' cast_expression REDUCE TO multiplicative_expression\n", numFila);
   }
   | multiplicative_expression '%' cast_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);

      if ($<infoBison>1.valorC3A == NULL) {
         $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
         strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
      }
      if ($<infoBison>3.valorC3A == NULL) {
         $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
         strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
      }      
         
      emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, '%');
      
      fprintf(yyout, ">>> linia %i: multiplicative_expression %% cast_expression REDUCE TO multiplicative_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* =================================== [ additive_expression ] ================================ */
/* ============================================================================================ */
additive_expression : 
   multiplicative_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: multiplicative_expression REDUCE TO additive_expression\n", numFila);   
   }
   | additive_expression '+' multiplicative_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);
      
      if ($<infoBison>1.valorC3A == NULL) {
         $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
         strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
      }
      if ($<infoBison>3.valorC3A == NULL) {
         $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
         strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
      }      
         
      emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, '+');
      
      fprintf(yyout, ">>> linia %i: additive_expression '+' multiplicative_expression REDUCE TO additive_expression\n", numFila);
   }
   | additive_expression '-' multiplicative_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);

      if ($<infoBison>1.valorC3A == NULL) {
         $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
         strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
      }
      if ($<infoBison>3.valorC3A == NULL) {
         $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
         strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
      }      
         
      emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, '-');
      
      fprintf(yyout, ">>> linia %i: REDUCE additive_expression '-' multiplicative_expression REDUCE TO additive_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================== [ relational_expression ] =============================== */
/* ============================================================================================ */
relational_expression : 
   additive_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: additive_expression REDUCE TO relational_expression\n", numFila);
   }
   | relational_expression '<' additive_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);
      if ($$.tipus_var != TIPUS_NULL) {
         $$.tipus_var = TIPUS_INTEGER;
         if ($<infoBison>1.valorC3A == NULL) {
            $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
            strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
         }
         if ($<infoBison>3.valorC3A == NULL) {
            $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
            strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
         }

         emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, '<');                                       
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&$<infoBison>$, &$<infoBison>$);
      }
      fprintf(yyout, ">>> linia %i: relational_expression '<' additive_expression REDUCE TO relational_expression\n", numFila);
   }
   | relational_expression '>' additive_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);
      if ($$.tipus_var != TIPUS_NULL) {
         $$.tipus_var = TIPUS_INTEGER;
         if ($<infoBison>1.valorC3A == NULL) {
            $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
            strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
         }
         if ($<infoBison>3.valorC3A == NULL) {
            $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
            strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
         }

         emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, '>');
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&$<infoBison>$, &$<infoBison>$);     
      }
      fprintf(yyout, ">>> linia %i: relational_expression '>' additive_expression REDUCE TO relational_expression\n", numFila);
   }
   | relational_expression ID_LE_OP additive_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);
      if ($$.tipus_var != TIPUS_NULL) {
         $$.tipus_var = TIPUS_INTEGER;
         if ($<infoBison>1.valorC3A == NULL) {
            $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
            strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
         }
         if ($<infoBison>3.valorC3A == NULL) {
            $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
            strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
         }

         emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, ID_LE_OP);
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&$<infoBison>$, &$<infoBison>$);
      }      
      fprintf(yyout, ">>> linia %i: relational_expression <= additive_expression REDUCE TO relational_expression\n", numFila);
   }
   | relational_expression ID_GE_OP additive_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);
      if ($$.tipus_var != TIPUS_NULL) {
         $$.tipus_var = TIPUS_INTEGER;
         if ($<infoBison>1.valorC3A == NULL) {
            $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
            strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
         }
         if ($<infoBison>3.valorC3A == NULL) {
            $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
            strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
         }

         emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, ID_GE_OP);
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&$<infoBison>$, &$<infoBison>$);
      }      
      fprintf(yyout, ">>> linia %i: relational_expression >= additive_expression REDUCE TO relational_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* =================================== [ equality_expression ] ================================ */
/* ============================================================================================ */
equality_expression : 
   relational_expression {
      $$ = $<infoBison>1;
            
      fprintf(yyout, ">>> linia %i: relational_expression REDUCE TO equality_expression\n", numFila);
   }
   | equality_expression ID_EQ_OP relational_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);
      if ($$.tipus_var != TIPUS_NULL) {
         $$.tipus_var = TIPUS_INTEGER;
         if ($<infoBison>1.valorC3A == NULL) {
            $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
            strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
         }
         if ($<infoBison>3.valorC3A == NULL) {
            $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
            strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
         }

         emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, ID_EQ_OP);
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&$<infoBison>$, &$<infoBison>$);
      }      
      fprintf(yyout, ">>> linia %i: equality_expression == relational_expression REDUCE TO equality_expression\n", numFila);
   }
   | equality_expression ID_NE_OP relational_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>3);
      if ($$.tipus_var != TIPUS_NULL) {
         $$.tipus_var = TIPUS_INTEGER;
         if ($<infoBison>1.valorC3A == NULL) {
            $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
            strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
         }
         if ($<infoBison>3.valorC3A == NULL) {
            $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
            strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
         }

         emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, ID_NE_OP);
         if (conditional_if_while_for == TRUE) emet_condicioC3A(&$<infoBison>$, &$<infoBison>$);
      }      
      fprintf(yyout, ">>> linia %i: equality_expression <> relational_expression REDUCE TO equality_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================== [ logical_AND_expression ] ============================== */
/* ============================================================================================ */
logical_AND_expression : 
   equality_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: equality_expression REDUCE TO logical_AND_expression\n", numFila);   
   }
   | logical_AND_expression ID_AND_OP M equality_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>4);
      if ($$.tipus_var != TIPUS_NULL) {
         $$.tipus_var = TIPUS_INTEGER;
         
         completar_llista((Cua *) $<infoBison>1.llista_certs , $<infoBison>3.punter_quadruple);
	     $<infoBison>$.llista_certs = $<infoBison>4.llista_certs;
	     $<infoBison>$.llista_falsos = (struct Cua *) fusionar_cues(((Cua *) $<infoBison>1.llista_falsos), ((Cua *) $<infoBison>4.llista_falsos));   
      }
      fprintf(yyout, ">>> linia %i: logical_AND_expression && equality_expression REDUCE TO logical_AND_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* =================================== [ logical_OR_expression ] ============================== */
/* ============================================================================================ */
logical_OR_expression : 
   logical_AND_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: logical_AND_expression REDUCE TO logical_OR_expression\n", numFila);
   }
   | logical_OR_expression ID_OR_OP M logical_AND_expression {
      $$ = $<infoBison>1;
      $$.tipus_var = checkOperadors($<infoBison>1, $<infoBison>4);
      if ($$.tipus_var != TIPUS_NULL) {
         $$.tipus_var = TIPUS_INTEGER;
         
         completar_llista((Cua *) $<infoBison>1.llista_falsos , $<infoBison>3.punter_quadruple);
	     $<infoBison>$.llista_falsos = $<infoBison>4.llista_falsos;
	     $<infoBison>$.llista_certs = (struct Cua *) fusionar_cues(((Cua *) $<infoBison>1.llista_certs), ((Cua *) $<infoBison>4.llista_certs));
      }
      fprintf(yyout, ">>> linia %i: logical_OR_expression || logical_AND_expression REDUCE TO logical_OR_expression\n", numFila);   
   }
;

/* ============================================================================================ */
/* ================================== [ conditional_expression ] ============================== */
/* ============================================================================================ */
conditional_expression : 
   logical_OR_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: logical_OR_expression REDUCE TO conditional_expression\n", numFila); 
   }
   | logical_OR_expression '?' expression ':' conditional_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: logical_OR_expression '?' expression ':' conditional_expression REDUCE TO conditional_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================== [ constant_expression ] ================================= */
/* ============================================================================================ */
constant_expression : 
   conditional_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: conditional_expression REDUCE TO constant_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================= [ assignment_expression ] ================================ */
/* ============================================================================================ */
assignment_expression : 
   conditional_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: conditional_expression REDUCE TO assignment_expression\n", numFila);
   }
   | unary_expression assignment_operator assignment_expression {
      $$ = $<infoBison>1;
      
      if ($<infoBison>1.constant == TRUE) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_ASIGNACIO_CONSTANT, $<infoBison>1.valor);   
      }
      else {
         if (identificadorDeclarat($<infoBison>1.valor)) {
            if ((simbol.array == TRUE) && ($<infoBison>1.array != TRUE)) {
               num_errors++;
               printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, $<infoBison>1.valor);   
            }
            else {  
               if ($<infoBison>3.constant == TRUE) {
                  if ($<infoBison>1.valorC3A == NULL) {
                     $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
                     strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
                  }
                  if ($<infoBison>3.valorC3A == NULL) {
                     $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
                     strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
                  }

                  if (strcmp($<infoBison>2.valor, "=") != 0) {
                     emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, ($<infoBison>2.valor)[0]);
                     emet_operacioC3A(&$<infoBison>$, NULL, &$<infoBison>1, '=');
                  }
                  else emet_operacioC3A(&$<infoBison>3, NULL, &$<infoBison>1, '=');
                  
                  if (strlen($<infoBison>2.valor) == 1) { 
                     comprovacioTipusDades($<infoBison>1.tipus_var, $<infoBison>3.tipus_var, ID_SITUACIO_ASSIGNACIO);
                  }
                  else {
                     comprovacioTipusDades($<infoBison>1.tipus_var, comprovacioTipusDades($<infoBison>1.tipus_var, $<infoBison>3.tipus_var, ID_SITUACIO_OPERACIO), ID_SITUACIO_ASSIGNACIO);
                  }
               }
               else {
                  if (identificadorDeclarat($<infoBison>3.valor)) {
                     if ((simbol.array == TRUE) && ($<infoBison>3.array != TRUE)) {
                        num_errors++;
                        printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, $<infoBison>3.valor);   
                     }
                     else {
                        if ($<infoBison>1.valorC3A == NULL) {
                           $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
                           strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
                        }
                        if ($<infoBison>3.valorC3A == NULL) {
                           $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
                           strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
                        }
                        
                        if (strcmp($<infoBison>2.valor, "=") != 0) {
                           emet_operacioC3A(&$<infoBison>1, &$<infoBison>3, &$<infoBison>$, ($<infoBison>2.valor)[0]);
                           emet_operacioC3A(&$<infoBison>$, NULL, &$<infoBison>1, '=');
                        }
                        else emet_operacioC3A(&$<infoBison>3, NULL, &$<infoBison>1, '=');  
                        
                        if (strlen($<infoBison>2.valor) == 1) { 
                           comprovacioTipusDades($<infoBison>1.tipus_var, $<infoBison>3.tipus_var, ID_SITUACIO_ASSIGNACIO);
                        }
                        else {
                           comprovacioTipusDades($<infoBison>1.tipus_var, comprovacioTipusDades($<infoBison>1.tipus_var, $<infoBison>3.tipus_var, ID_SITUACIO_OPERACIO), ID_SITUACIO_ASSIGNACIO);
                        }                     
                     }
                  }
               }
            }
         }
      }
      
      fprintf(yyout, ">>> linia %i: unary_expression assignment_operator assignment_expression REDUCE TO assignment_expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================== [ assignment_operator ] ================================= */
/* ============================================================================================ */
assignment_operator : 
   '=' { 
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: '=' REDUCE TO assignment_operator\n", numFila);
   }
   | ID_MUL_ASSIG {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: *= REDUCE TO assignment_operator\n", numFila);
   }
   | ID_DIV_ASSIG {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: /= REDUCE TO assignment_operator\n", numFila);
   }
   | ID_MOD_ASSIG {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: %%= REDUCE TO assignment_operator\n", numFila);
   }
   | ID_ADD_ASSIG {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: += REDUCE TO assignment_operator\n", numFila);
   }
   | ID_SUB_ASSIG {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: -= REDUCE TO assignment_operator\n", numFila);
   }
;

/* ============================================================================================ */
/* ==================================== [ expression ] ======================================== */
/* ============================================================================================ */
expression : 
   assignment_expression {
      $$ = $<infoBison>1;  
      fprintf(yyout, ">>> linia %i: assignment_expression REDUCE TO expression\n", numFila);
   }
   | expression ',' assignment_expression {
      fprintf(yyout, ">>> linia %i: expression,assignment_expression REDUCE TO expression\n", numFila);
   }
;

/* ============================================================================================ */
/* ====================================== [ declaration ] ===================================== */
/* ============================================================================================ */
declaration : 
   declaration_specifiers ';' {
      fprintf(yyout, ">>> linia %i: declaration_specifiers; REDUCE TO declaration\n", numFila);
   }
   | declaration_specifiers init_declarator_list ';' {
      fprintf(yyout, ">>> linia %i: declaration_specifiers init_declarator_list; REDUCE TO declaration\n", numFila);
   }
   | ID_TYPEDEF declaration_specifiers declarator ';' {
      $$ = $<infoBison>3;
      $$.tipus_var = $<infoBison>2.tipus_var;
      idSimbol = (char *) malloc(strlen($<infoBison>3.valor) + 1);
      strcpy(idSimbol, $<infoBison>3.valor); 
      simbol.tipus_var = $<infoBison>2.tipus_var;
      simbol.tipus = TIPUS_BASIC;
      simbol.idLexic = ID_TYPEDEF_IDENTIFIER;
      strcpy(simbol.nomLexic, "TYPEDEF_IDENTIFIER");
      currentScope = sym_get_scope();
      simbol.ambit = currentScope;
               
      if ($$.tipus_var == TIPUS_STRUCT) {
         $$.num_struct_camps = $<infoBison>2.num_struct_camps;
         $$.seguent_camp_struct = $<infoBison>2.seguent_camp_struct;
         simbol.num_struct_camps = $<infoBison>2.num_struct_camps;

         if (simbol.num_struct_camps > 0) {
            simbol.struct_camps = malloc(sizeof(struct t_param) * $<infoBison>2.num_struct_camps);
          
            recordsetCamp = $<infoBison>2.seguent_camp_struct;
            for (count = 0; (count < $<infoBison>2.num_struct_camps); count++) {
               simbol.struct_camps[count].valor = malloc(strlen(recordsetCamp -> valor) + 1);
               strcpy(simbol.struct_camps[count].valor, recordsetCamp -> valor); 
            
               simbol.struct_camps[count].tipus_var = recordsetCamp -> tipus_var;
               if (recordsetCamp -> array == TRUE) {
                  simbol.struct_camps[count].array = TRUE;
                  simbol.struct_camps[count].tam_array = recordsetCamp -> tam_array;
               }
               else {
                  simbol.struct_camps[count].array = FALSE;
                  simbol.struct_camps[count].tam_array = 0;
               }
               recordsetCamp = recordsetCamp -> seguent_camp_struct;
            }
         }
      }
             
      if (sym_lookup($<infoBison>3.valor, &simbol_tmp) == SYMTAB_OK) {
         num_errors++;
         printErrorSintactic(TRUE, ERR_REDECLARACIO_TIPUS, idSimbol);
      }
      else {
         if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) { num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_TIPUS, idSimbol); }
         else { printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_TIPUS, idSimbol); printSimbolInfo((char *) idSimbol); }
      }
              
      fprintf(yyout, ">>> linia %i: ID_TYPEDEF declaration_specifiers declarator; REDUCE TO declaration\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================= [ declaration_specifiers ] =============================== */
/* ============================================================================================ */
declaration_specifiers : 
   type_specifier {
      $$ = $<infoBison>1;
      tipus_var_tmp = $<infoBison>1.tipus_var;
          
      fprintf(yyout, ">>> linia %i: type_specifier REDUCE TO declaration_specifiers\n", numFila);
   }
;

/* ============================================================================================ */
/* =================================== [ init_declarator_list ] =============================== */
/* ============================================================================================ */
init_declarator_list : 
   init_declarator {
      $$ = $<infoBison>0;
      
      errFuncDeclaration = FALSE;
      
      if ($<infoBison>1.tipus_var != TIPUS_NULL) comprovacioTipusDades($<infoBison>0.tipus_var, $<infoBison>1.tipus_var, ID_SITUACIO_ASSIGNACIO);
      
      idSimbol = (char *) malloc(strlen($<infoBison>1.valor) + 1);
      strcpy(idSimbol, $<infoBison>1.valor);
      simbol.tipus_var = $<infoBison>0.tipus_var;
      
      if ($<infoBison>1.funcio == TRUE) {
         simbol.tipus = FUNCIO;
         simbol.funcio = TRUE;
         simbol.num_funcio_parametres = $<infoBison>1.num_funcio_parametres;
      }
      else {
         simbol.tipus = VARIABLE;
         simbol.funcio = FALSE; 
         simbol.num_funcio_parametres = 0;
         if ($<infoBison>0.tipus_var == TIPUS_STRUCT) {      
            simbol.tipus_var = TIPUS_STRUCT;
            simbol.num_struct_camps = $<infoBison>0.num_struct_camps;
         }
      }
      
      simbol.idLexic = ID_IDENTIFICADOR;
      strcpy(simbol.nomLexic, "IDENTIFICADOR"); 
      if ($<infoBison>1.array == TRUE) {
         simbol.array = TRUE;
         simbol.tam_array = $<infoBison>1.tam_array;
      }
      else simbol.array = FALSE;
      
      if (simbol.funcio == TRUE) {
          if ($<infoBison>1.num_funcio_parametres == 1) {
             if (($<infoBison>1.seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus($<infoBison>1.seguent_param_funcio -> valor))) {
                num_errors++;
                errFuncDeclaration = TRUE;
                printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
             }
             else if ($<infoBison>1.seguent_param_funcio -> tipus_var == TIPUS_VOID) {
                $<infoBison>1.num_funcio_parametres--;
                simbol.num_funcio_parametres = 0;
             }
          }

          if (!errFuncDeclaration) {
             simbol.funcio_params = malloc(sizeof(struct t_param) * $<infoBison>1.num_funcio_parametres);
          
             recordsetParam = $<infoBison>1.seguent_param_funcio;
             for (count = 0; ((count < $<infoBison>1.num_funcio_parametres) && (!errFuncDeclaration)); count++) {
                if (recordsetParam -> tipus_var == TIPUS_VOID) {
                   num_errors++;
                   errFuncDeclaration = TRUE;
                   printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
                }
                else {
                   simbol.funcio_params[count].tipus_var = recordsetParam -> tipus_var;
                   if (recordsetParam -> array == TRUE) {
                      simbol.funcio_params[count].array = TRUE;
                      simbol.funcio_params[count].tam_array = recordsetParam -> tam_array;
                   }
                   else {
                      simbol.funcio_params[count].array = FALSE;
                      simbol.funcio_params[count].tam_array = 0;
                   }
                }
                recordsetParam = recordsetParam -> seguent_param_funcio;
             }
          } 
      }
      else if (simbol.tipus_var == TIPUS_STRUCT) {
         simbol.struct_camps = malloc(sizeof(struct t_param) * $<infoBison>0.num_struct_camps);
          
         recordsetCamp = $<infoBison>0.seguent_camp_struct;
         for (count = 0; (count < $<infoBison>0.num_struct_camps); count++) {
            simbol.struct_camps[count].valor = malloc(strlen(recordsetCamp -> valor) + 1); 
            strcpy(simbol.struct_camps[count].valor, recordsetCamp -> valor); 
            
            simbol.struct_camps[count].tipus_var = recordsetCamp -> tipus_var;
            if (recordsetCamp -> array == TRUE) {
               simbol.struct_camps[count].array = TRUE;
               simbol.struct_camps[count].tam_array = recordsetCamp -> tam_array;
            }
            else {
               simbol.struct_camps[count].array = FALSE;
               simbol.struct_camps[count].tam_array = 0;
            }
            recordsetCamp = recordsetCamp -> seguent_camp_struct;
         }
      }          
      
      if (!errFuncDeclaration) {
         if (identificadorDeclaratMateixAmbit($<infoBison>1.valor)) {
            if (simbol_tmp.funcio == TRUE) { num_errors++; printErrorSintactic(TRUE, ERR_REDECLARACIO_FUNC_VAR, "funcio", idSimbol); }
            else { num_errors++; printErrorSintactic(TRUE, ERR_REDECLARACIO_FUNC_VAR, "variable", idSimbol); }
         }
         else {
            if (simbol.funcio == TRUE) {
               simbol.ambit = -1;
               if (sym_global_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "funcio", idSimbol);
               }
               else { 
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "funcio", idSimbol);
               }
            }
            else {
               currentScope = sym_get_scope();
               simbol.ambit = currentScope;
               if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "variable", idSimbol);
               }
               else { 
                  if (currentScope == -1) afegirVarLocalRA(registreActivacioGlobal, idSimbol, &simbol);
                  else afegirVarLocalRA(registreActivacioFuncions, idSimbol, &simbol);

                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "variable", idSimbol);
               }
            }
            printSimbolInfo((char *) idSimbol);
         }
      }
      
      fprintf(yyout, ">>> linia %i: init_declarator REDUCE TO init_declarator_list\n", numFila);
   }
   | init_declarator_list ',' init_declarator {
      $$ = $<infoBison>1;
      errFuncDeclaration = FALSE;
      
      if ($<infoBison>3.tipus_var != TIPUS_NULL) comprovacioTipusDades($<infoBison>0.tipus_var, $<infoBison>3.tipus_var, ID_SITUACIO_ASSIGNACIO);
      
      idSimbol = (char *) malloc(strlen($<infoBison>3.valor) + 1);
      strcpy(idSimbol, $<infoBison>3.valor);
      simbol.tipus_var = $<infoBison>1.tipus_var;
      
      if ($<infoBison>3.funcio == TRUE) {
         simbol.tipus = FUNCIO;
         simbol.funcio = TRUE;
         simbol.num_funcio_parametres = $<infoBison>3.num_funcio_parametres;
      }
      else {
         simbol.tipus = VARIABLE;
         simbol.funcio = FALSE; 
         simbol.num_funcio_parametres = 0;
         if ($<infoBison>1.tipus_var == TIPUS_STRUCT) {      
            simbol.tipus_var = TIPUS_STRUCT;
            simbol.num_struct_camps = $<infoBison>0.num_struct_camps;
         }
      }
      
      simbol.idLexic = ID_IDENTIFICADOR;
      strcpy(simbol.nomLexic, "IDENTIFICADOR");
      currentScope = sym_get_scope();
      simbol.ambit = currentScope;
      
      if ($<infoBison>3.array == TRUE) {
         simbol.array = TRUE;
         simbol.tam_array = $<infoBison>3.tam_array;
      }
      else simbol.array = FALSE;
      
      if (simbol.funcio == TRUE) {
          if ($<infoBison>3.num_funcio_parametres == 1) {
             if (($<infoBison>3.seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus($<infoBison>3.seguent_param_funcio -> valor))) {
                errFuncDeclaration = TRUE;
                num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
             }
             else if ($<infoBison>3.seguent_param_funcio -> tipus_var == TIPUS_VOID) {
                $<infoBison>3.num_funcio_parametres--;
                simbol.num_funcio_parametres = 0;
             }
          }

          if (!errFuncDeclaration) {
             simbol.funcio_params = malloc(sizeof(struct t_param) * $<infoBison>3.num_funcio_parametres);
             
             recordsetParam = $<infoBison>3.seguent_param_funcio;
             for (count = 0; ((count < $<infoBison>3.num_funcio_parametres) && (!errFuncDeclaration)); count++) {
                if (recordsetParam -> tipus_var == TIPUS_VOID) {
                   errFuncDeclaration = TRUE;
                   num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
                }
                else {
                   simbol.funcio_params[count].tipus_var = recordsetParam -> tipus_var;
                   if (recordsetParam -> array == TRUE) {
                      simbol.funcio_params[count].array = TRUE;
                      simbol.funcio_params[count].tam_array = recordsetParam -> tam_array;
                   }
                   else {
                      simbol.funcio_params[count].array = FALSE;
                      simbol.funcio_params[count].tam_array = 0;
                   }
                }
                recordsetParam = recordsetParam -> seguent_param_funcio;
             }
          }
      }
      else if (simbol.tipus_var == TIPUS_STRUCT) {
         simbol.struct_camps = malloc(sizeof(struct t_param) * $<infoBison>0.num_struct_camps);
          
         recordsetCamp = $<infoBison>0.seguent_camp_struct;
         for (count = 0; (count < $<infoBison>0.num_struct_camps); count++) {
            simbol.struct_camps[count].valor = malloc(strlen(recordsetCamp -> valor) + 1);
            strcpy(simbol.struct_camps[count].valor, recordsetCamp -> valor); 
            
            simbol.struct_camps[count].tipus_var = recordsetCamp -> tipus_var;
            if (recordsetCamp -> array == TRUE) {
               simbol.struct_camps[count].array = TRUE;
               simbol.struct_camps[count].tam_array = recordsetCamp -> tam_array;
            }
            else {
               simbol.struct_camps[count].array = FALSE;
               simbol.struct_camps[count].tam_array = 0;
            }
            recordsetCamp = recordsetCamp -> seguent_camp_struct;
         }
      }
      
      if (!errFuncDeclaration) {
         if (identificadorDeclaratMateixAmbit($<infoBison>3.valor)) {
            if (simbol_tmp.funcio == TRUE) { num_errors++; printErrorSintactic(TRUE, ERR_REDECLARACIO_FUNC_VAR, "funcio", idSimbol); }
            else { num_errors++; printErrorSintactic(TRUE, ERR_REDECLARACIO_FUNC_VAR, "variable", idSimbol); }
         }
         else {
            if (simbol.funcio == TRUE) {
               simbol.ambit = -1;
               if (sym_global_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "funcio", idSimbol);
               }
               else { 
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "funcio", idSimbol);
               }
            }
            else {
               currentScope = sym_get_scope();
               simbol.ambit = currentScope;
               if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "variable", idSimbol);
               }
               else { 
                  if (currentScope == -1) afegirVarLocalRA(registreActivacioGlobal, idSimbol, &simbol);
                  else afegirVarLocalRA(registreActivacioFuncions, idSimbol, &simbol);
                  
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "variable", idSimbol);
               }
            }
            printSimbolInfo((char *) idSimbol);
         }
      }
      
      fprintf(yyout, ">>> linia %i: init_declarator_list,init_declarator REDUCE TO init_declarator_list\n", numFila);
   }
;

/* ============================================================================================ */
/* ===================================== [ init_declarator ] ================================== */
/* ============================================================================================ */
init_declarator : 
   declarator {
      $$ = $<infoBison>1;
      $$.tipus_var = TIPUS_NULL;
      
      fprintf(yyout, ">>> linia %i: declarator REDUCE TO init_declarator\n", numFila);
   }
   | declarator '=' initializer {
      $$ = $<infoBison>1;
      $$.constant = FALSE;
      $$.tipus_var = tipus_var_tmp;

      $<infoBison>1.tipus_var = tipus_var_tmp;
            
      if ($<infoBison>3.constant != TRUE) { num_errors++; printErrorSintactic(TRUE, ERR_VALOR_INICIAL_NO_CONST); }
      else if (($<infoBison>1.array == TRUE) && ($<infoBison>3.tipus_var == TIPUS_STRING) && ((strlen($<infoBison>3.valor)) > $<infoBison>1.tam_array)) {
         num_errors++; printErrorSintactic(TRUE, ERR_ASSIGNACIO_STRING_ARRAY, strlen($<infoBison>3.valor), $<infoBison>1.tam_array);    
      }
      else {  
         if (($<infoBison>1.array == TRUE) && ($<infoBison>3.tipus_var == TIPUS_STRING)) {
            if ($<infoBison>1.valorC3A == NULL) {
               $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
               strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
            }
            $<infoBison>1.array_indexat = TRUE;
            $<infoBison>1.array_indexat_offset = (char *) malloc(log10Func(strlen($<infoBison>3.valor)) + 1);
            $<infoBison>3.valorC3A = (char *) malloc(4);
            for(count = 0; count < strlen($<infoBison>3.valor); count++) {
               sprintf($<infoBison>1.array_indexat_offset, "%d", count);
               sprintf($<infoBison>3.valorC3A, "'%c'", $<infoBison>3.valor[count]);  
               
               emet_operacioC3A(&$<infoBison>3, NULL, &$<infoBison>1, '=');
               
               $<infoBison>1.array_indexat = TRUE;
               strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
            }
         }
         else {  
            if ($<infoBison>1.valorC3A == NULL) {
               $<infoBison>1.valorC3A = malloc(strlen($<infoBison>1.valor) + 1); 
               strcpy($<infoBison>1.valorC3A, $<infoBison>1.valor);
            }
            if ($<infoBison>3.valorC3A == NULL) {
               $<infoBison>3.valorC3A = malloc(strlen($<infoBison>3.valor) + 1); 
               strcpy($<infoBison>3.valorC3A, $<infoBison>3.valor);
            }
            emet_operacioC3A(&$<infoBison>3, NULL, &$<infoBison>1, '=');
         }
      }
      
      fprintf(yyout, ">>> linia %i: declarator '=' initializer REDUCE TO init_declarator\n", numFila);
   }
;

/* ============================================================================================ */
/* ===================================== [ type_specifier ] =================================== */
/* ============================================================================================ */
type_specifier : 
   ID_VOID {
      $$.constant = FALSE;
      $$.tipus_var = TIPUS_VOID;         
      fprintf(yyout, ">>> linia %i: ID_VOID REDUCE TO type_specifier\n", numFila);
   }
   | ID_CHAR {
      $$.constant = FALSE;
      $$.tipus_var = TIPUS_CHARACTER; 
      fprintf(yyout, ">>> linia %i: ID_CHAR REDUCE TO type_specifier\n", numFila);
   }
   | ID_SHORT { 
      $$.constant = FALSE;
      $$.tipus_var = TIPUS_SHORT;       
      fprintf(yyout, ">>> linia %i: ID_SHORT REDUCE TO type_specifier\n", numFila);
   }
   | ID_INT {    
      $$.constant = FALSE;
      $$.tipus_var = TIPUS_INTEGER;
      fprintf(yyout, ">>> linia %i: ID_INT REDUCE TO type_specifier\n", numFila);
   }
   | ID_LONG {     
      $$.constant = FALSE;
      $$.tipus_var = TIPUS_LONG;
      fprintf(yyout, ">>> linia %i: ID_LONG REDUCE TO type_specifier\n", numFila);
   }
   | ID_FLOAT {      
      $$.constant = FALSE;
      $$.tipus_var = TIPUS_FLOAT;
      fprintf(yyout, ">>> linia %i: ID_FLOAT REDUCE TO type_specifier\n", numFila);           
   }
   | ID_DOUBLE {       
      $$.constant = FALSE;
      $$.tipus_var = TIPUS_DOUBLE;
      fprintf(yyout, ">>> linia %i: ID_DOUBLE REDUCE TO type_specifier\n", numFila);
   }
   | struct_or_union_specifier {
      $$ = $<infoBison>1;
      $$.constant = FALSE;
      $$.tipus_var = TIPUS_STRUCT;
      fprintf(yyout, ">>> linia %i: struct_or_union_specifier REDUCE TO type_specifier\n", numFila);
   }
   | typedef_name {
      $$ = $<infoBison>1;
      $$.constant = FALSE;
      fprintf(yyout, ">>> linia %i: typedef_name REDUCE TO type_specifier\n", numFila);
   }
;

/* ============================================================================================ */
/* ====================================== [ typedef_name ] ==================================== */
/* ============================================================================================ */
typedef_name : 
   ID_TYPEDEF_IDENTIFIER {
      $$ = $<infoBison>1;
      
      if ($<infoBison>1.tipus_var == TIPUS_STRUCT) {
         if (sym_lookup($<infoBison>1.valor, &simbol) == SYMTAB_OK) {
            if (simbol.num_struct_camps > 0) {
               recordsetCamp = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
               $$.seguent_camp_struct = recordsetCamp;
               $$.num_struct_camps = simbol.num_struct_camps;
               recordsetCamp -> seguent_camp_struct = NULL;
            
               for(count = 0; count < simbol.num_struct_camps; count++) {
                  recordsetCamp -> valor = malloc(strlen(simbol.struct_camps[count].valor) + 1);       
                  strcpy(recordsetCamp -> valor, simbol.struct_camps[count].valor);
                  
                  recordsetCamp -> tipus_var = simbol.struct_camps[count].tipus_var;
                  recordsetCamp -> array = simbol.struct_camps[count].array;
                  recordsetCamp -> tam_array = simbol.struct_camps[count].tam_array;
               
                  recordsetCamp -> seguent_camp_struct = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
                  recordsetCamp = recordsetCamp -> seguent_camp_struct;
               }
            }
         }  
      }

      fprintf(yyout, ">>> linia %i: ID_TYPEDEF_IDENTIFIER REDUCE TO typedef_name\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================ [ struct_or_union_specifier ] ============================= */
/* ============================================================================================ */
struct_or_union_specifier : 
   struct_or_union ID_IDENTIFICADOR '{' struct_declaration_list '}' {
      $$ = $<infoBison>2;
      $$.tipus_var = TIPUS_STRUCT;
      $$.num_struct_camps = $<infoBison>4.num_struct_camps;
      $$.seguent_camp_struct = $<infoBison>4.seguent_camp_struct;
      
      fprintf(yyout, ">>> linia %i: struct_or_union ID_IDENTIFICADOR -> [%s] { struct_declaration_list } REDUCE TO struct_or_union_specifier\n", numFila, $<infoBison>2.valor);
   }
   | struct_or_union '{' struct_declaration_list '}' {  
      $$.tipus_var = TIPUS_STRUCT;
      $$.num_struct_camps = $<infoBison>3.num_struct_camps;
      $$.seguent_camp_struct = $<infoBison>3.seguent_camp_struct;      
      
      fprintf(yyout, ">>> linia %i: struct_or_union { struct_declaration_list } REDUCE TO struct_or_union_specifier\n", numFila);
   }
;

/* ============================================================================================ */
/* ===================================== [ struct_or_union ] ================================== */
/* ============================================================================================ */
struct_or_union : 
   ID_STRUCT {
      fprintf(yyout, ">>> linia %i: ID_STRUCT REDUCE TO struct_or_union\n", numFila);
   }
   | ID_UNION {
      fprintf(yyout, ">>> linia %i: ID_UNION REDUCE TO struct_or_union\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================= [ struct_declaration_list ] ============================== */
/* ============================================================================================ */
struct_declaration_list : 
   struct_declaration {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: struct_declaration REDUCE TO struct_declaration_list\n", numFila);
   }
   | struct_declaration_list struct_declaration {
      $$ = $<infoBison>1;
      
      recordsetCamp = $$.seguent_camp_struct; 
      for (count = 1; count < $$.num_struct_camps; count++) {   
         recordsetCamp = recordsetCamp -> seguent_camp_struct;
      }
      recordsetCamp -> seguent_camp_struct = $<infoBison>2.seguent_camp_struct;
      $$.num_struct_camps += $<infoBison>2.num_struct_camps;
      
      fprintf(yyout, ">>> linia %i: struct_declaration_list struct_declaration REDUCE TO struct_declaration_list\n", numFila);
   }
;

/* ============================================================================================ */
/* ==================================== [ struct_declaration ] ================================ */
/* ============================================================================================ */
struct_declaration : 
   specifier_qualifier_list struct_declarator_list ';' {
      $$ = $<infoBison>2;
      
      fprintf(yyout, ">>> linia %i: specifier_qualifier_list struct_declarator_list; REDUCE TO struct_declaration\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================== [ struct_declarator_list ] ============================== */
/* ============================================================================================ */
struct_declarator_list : 
   struct_declarator {
      $$ = $<infoBison>1;
      
      pcamp = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pcamp = $<infoBison>1;
      pcamp->tipus_var = $<infoBison>0.tipus_var;
      pcamp->seguent_camp_struct = NULL;
      
      $$.seguent_camp_struct = pcamp;
      $$.num_struct_camps = 1;
      $$.tipus_var = $<infoBison>0.tipus_var;
      
      fprintf(yyout, ">>> linia %i: struct_declarator REDUCE TO struct_declarator_list\n", numFila);
   }
   | struct_declarator_list ',' struct_declarator {
      $$ = $<infoBison>1;
      pcamp = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pcamp = $<infoBison>3;
      pcamp->seguent_camp_struct = NULL;
      pcamp->tipus_var = $<infoBison>1.tipus_var;
      
      recordsetCamp = $$.seguent_camp_struct; 
      for (count = 1; count < $$.num_struct_camps; count++) {
         recordsetCamp = recordsetCamp -> seguent_camp_struct;
      }
      recordsetCamp -> seguent_camp_struct = pcamp;
      $$.num_struct_camps++;
      
      fprintf(yyout, ">>> linia %i: struct_declarator_list,struct_declarator REDUCE TO struct_declarator_list\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================== [ struct_declarator ] =================================== */
/* ============================================================================================ */
struct_declarator : 
   declarator {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: declarator REDUCE TO struct_declarator\n", numFila);
   }
;

/* ============================================================================================ */
/* ====================================== [ declarator ] ====================================== */
/* ============================================================================================ */
declarator : 
   ID_IDENTIFICADOR {  
      $$ = $<infoBison>1; 
      $$.funcio = FALSE;
             
      fprintf(yyout, ">>> linia %i: ID_IDENTIFICADOR -> [%s] REDUCE TO declarator\n", numFila, $<infoBison>1.valor);
   }
   | '(' declarator ')' {
      $$ = $<infoBison>2;
      
      fprintf(yyout, ">>> linia %i: (declarator) REDUCE TO declarator\n", numFila);
   }
   | declarator '[' ID_INTEGER_CONSTANT ']' {
      $$ = $<infoBison>1;
      $$.array = TRUE;
      
      tmpValor = atoll($<infoBison>3.valor);
      
      if (tmpValor > 0) {
         if (tmpValor > LONG_MAX) { $$.tam_array = LONG_MAX; printErrorSintactic(FALSE, WARNING_ARRAY_TAMANY_MAXIM, $<infoBison>1.valor, LONG_MAX); }
         else $$.tam_array = tmpValor;
      }
      else { $$.tam_array = 0; num_errors++; printErrorSintactic(TRUE, ERR_ARRAY_TAMANY_INCORRECTE, $<infoBison>3.valor, $<infoBison>1.valor); }
      
      arrayDeclaracio = TRUE;
      fprintf(yyout, ">>> linia %i: declarator[ID_INTEGER_CONSTANT -> [%s]] REDUCE TO declarator\n", numFila, $<infoBison>3.valor);
   }
   | declarator '(' parameter_list ')' { 
      $$ = $<infoBison>1;
      $$.seguent_param_funcio = $<infoBison>3.seguent_param_funcio;
      $$.num_funcio_parametres = $<infoBison>3.num_funcio_parametres;
      $$.funcio = TRUE;
     
      fprintf(yyout, ">>> linia %i: declarator(parameter_list) REDUCE TO declarator\n", numFila);
   }
   | declarator '(' identifier_list ')' {
      $$ = $<infoBison>1;
      $$.seguent_param_funcio = $<infoBison>3.seguent_param_funcio;
      $$.num_funcio_parametres = $<infoBison>3.num_funcio_parametres;
      $$.funcio = TRUE;
               
      fprintf(yyout, ">>> linia %i: declarator(identifier_list) REDUCE TO declarator\n", numFila);
   }
   | declarator '(' ')' {
      $$ = $<infoBison>1;
      $$.seguent_param_funcio = NULL;
      $$.num_funcio_parametres = 0;
      $$.funcio = TRUE;
      
      fprintf(yyout, ">>> linia %i: declarator() REDUCE TO declarator\n", numFila);
   }
;

/* ============================================================================================ */
/* ==================================== [ parameter_list ] ==================================== */
/* ============================================================================================ */
parameter_list : 
   parameter_declaration {
      $$ = $<infoBison>1;
      
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = $<infoBison>1;
      pparam->tipus_var = $<infoBison>1.tipus_var;
      pparam->seguent_param_funcio = NULL;
      
      $$.seguent_param_funcio = pparam;
      $$.num_funcio_parametres = 1;
      
      fprintf(yyout, ">>> linia %i: parameter_declaration REDUCE TO parameter_list\n", numFila);
   }
   | parameter_list ',' parameter_declaration {
      $$ = $<infoBison>1;
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = $<infoBison>3;
      pparam->seguent_param_funcio = NULL;
      pparam->tipus_var = $<infoBison>3.tipus_var;
      
      recordsetParam = $$.seguent_param_funcio; 
      for (count = 1; count < $$.num_funcio_parametres; count++) {
         recordsetParam = recordsetParam -> seguent_param_funcio;
      }
      recordsetParam -> seguent_param_funcio = pparam;
      $$.num_funcio_parametres++;

      fprintf(yyout, ">>> linia %i: parameter_list,parameter_declaration REDUCE TO parameter_list\n", numFila);   
   }
;

/* ============================================================================================ */
/* ================================= [ parameter_declaration ] ================================ */
/* ============================================================================================ */
parameter_declaration : 
   declaration_specifiers declarator {
      $$ = $<infoBison>2;
      $$.tipus_var = $<infoBison>1.tipus_var;
      
      fprintf(yyout, ">>> linia %i: declaration_specifiers declarator REDUCE TO parameter_declaration\n", numFila);
   }
   | declaration_specifiers abstract_declarator {
      fprintf(yyout, ">>> linia %i: declaration_specifiers abstract_declarator REDUCE TO parameter_declaration\n", numFila);
   }
   | declaration_specifiers {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: declaration_specifiers REDUCE TO parameter_declaration\n", numFila);
   }
;

/* ============================================================================================ */
/* ==================================== [ identifier_list ] =================================== */
/* ============================================================================================ */
identifier_list : 
   ID_IDENTIFICADOR {
      $$ = $<infoBison>1;
      
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = $<infoBison>1;
      pparam->tipus_var = TIPUS_NULL;
      pparam->seguent_param_funcio = NULL;
      
      $$.seguent_param_funcio = pparam;
      $$.num_funcio_parametres = 1;
      
      fprintf(yyout, ">>> linia %i: ID_IDENTIFICADOR -> [%s] REDUCE TO identifier_list\n", numFila, $<infoBison>1.valor);   
   }
   | identifier_list ',' ID_IDENTIFICADOR {
      $$ = $<infoBison>1;
      pparam = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));
      *pparam = $<infoBison>3;
      pparam->seguent_param_funcio = NULL;
      pparam->tipus_var = TIPUS_NULL;
      
      recordsetParam = $$.seguent_param_funcio; 
      for (count = 1; count < $$.num_funcio_parametres; count++) {
         recordsetParam = recordsetParam -> seguent_param_funcio;
      }
      recordsetParam -> seguent_param_funcio = pparam;
      $$.num_funcio_parametres++;
      
      fprintf(yyout, ">>> linia %i: identifier_list,ID_IDENTIFICADOR -> [%s] REDUCE TO identifier_list\n", numFila, $<infoBison>3.valor);
   }
;

/* ============================================================================================ */
/* ======================================= [ type_name ] ====================================== */
/* ============================================================================================ */
type_name : 
   specifier_qualifier_list {
      fprintf(yyout, ">>> linia %i: specifier_qualifier_list REDUCE TO type_name\n", numFila);
   }
   | specifier_qualifier_list abstract_declarator {
      fprintf(yyout, ">>> linia %i: specifier_qualifier_list abstract_declarator REDUCE TO type_name\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================ [ specifier_qualifier_list ] ============================== */
/* ============================================================================================ */
specifier_qualifier_list : 
   type_specifier specifier_qualifier_list {
      fprintf(yyout, ">>> linia %i: type_specifier specifier_qualifier_list REDUCE TO specifier_qualifier_list\n", numFila);
   }
   | type_specifier {
      fprintf(yyout, ">>> linia %i: type_specifier REDUCE TO specifier_qualifier_list\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================== [ abstract_declarator ] ================================= */
/* ============================================================================================ */
abstract_declarator : 
   '(' abstract_declarator ')' {
      $$ = $<infoBison>2;
      
      fprintf(yyout, ">>> linia %i: (abstract_declarator) REDUCE TO abstract_declarator\n", numFila);
   }
   | '[' ID_INTEGER_CONSTANT ']' {
      $$ = $<infoBison>2;
      
      fprintf(yyout, ">>> linia %i: [ID_INTEGER_CONSTANT -> [%s]] REDUCE TO abstract_declarator\n", numFila, $<infoBison>2.valor);
   }
   | abstract_declarator '[' ID_INTEGER_CONSTANT ']' {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: abstract_declarator [ID_INTEGER_CONSTANT -> [%s]] REDUCE TO abstract_declarator\n", numFila, $<infoBison>3.valor);
   }
   | '(' ')' {
      fprintf(yyout, ">>> linia %i: () REDUCE TO abstract_declarator\n", numFila);
   }
   | '(' parameter_list ')' {
      $$ = $<infoBison>2;
      
      fprintf(yyout, ">>> linia %i: (parameter_list) REDUCE TO abstract_declarator\n", numFila);
   }
   | abstract_declarator '(' ')' {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: abstract_declarator() REDUCE TO abstract_declarator\n", numFila);
   }
   | abstract_declarator '(' parameter_list ')' {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: abstract_declarator(parameter_list) REDUCE TO abstract_declarator\n", numFila);
   }
;

/* ============================================================================================ */
/* ====================================== [ initializer ] ===================================== */
/* ============================================================================================ */
initializer : 
   assignment_expression {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: assignment_expression REDUCE TO initializer\n", numFila);   
   }
   | '{' initializer_list '}' {
      fprintf(yyout, ">>> linia %i: {initializer_list} REDUCE TO initializer\n", numFila);
   }
   | '{' initializer_list ',' '}' {
      fprintf(yyout, ">>> linia %i: {initializer_list,} REDUCE TO initializer\n", numFila);
   }
;

/* ============================================================================================ */
/* =================================== [ initializer_list ] =================================== */
/* ============================================================================================ */
initializer_list : 
   initializer {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: initializer REDUCE TO initializer_list\n", numFila);
   }
   | initializer_list ',' initializer {
      $$ = $<infoBison>1;
      
      fprintf(yyout, ">>> linia %i: initializer_list , initializer  REDUCE TO initializer_list\n", numFila);
   }
;

/* ============================================================================================ */
/* ======================================= [ statement ] ====================================== */
/* ============================================================================================ */
statement : 
   labeled_statement {
      $$ = $<infoBison>1;
      fprintf(yyout, ">>> linia %i: labeled_statement REDUCE TO statement\n", numFila);
   }
   | compound_statement {
      $$ = $<infoBison>1;
      fprintf(yyout, ">>> linia %i: compound_statement REDUCE TO statement\n", numFila);
   }
   | expression_statement {
      $$ = $<infoBison>1;
      fprintf(yyout, ">>> linia %i: expression_statement REDUCE TO statement\n", numFila);
   }
   | selection_statement {
      $$ = $<infoBison>1;
      fprintf(yyout, ">>> linia %i: selection_statement REDUCE TO statement\n", numFila);
   }
   | iteration_statement {
      $$ = $<infoBison>1;
      fprintf(yyout, ">>> linia %i: iteration_statement REDUCE TO statement\n", numFila);
   }
   | jump_statement {
      $$ = $<infoBison>1;
      fprintf(yyout, ">>> linia %i: jump_statement REDUCE TO statement\n", numFila);
   }
;

/* ============================================================================================ */
/* =================================== [ labeled_statement ] ================================== */
/* ============================================================================================ */
labeled_statement : 
   ID_CASE constant_expression ':' statement {
      fprintf(yyout, ">>> linia %i: ID_CASE constant_expression ':' statement REDUCE TO labeled_statement\n", numFila);
   }
   | ID_DEFAULT ':' statement {
      fprintf(yyout, ">>> linia %i: ID_DEFAULT ':' statement REDUCE TO statement\n", numFila);
   }
;

/* ============================================================================================ */
/* =================================== [ compound_statement ] ================================= */
/* ============================================================================================ */
compound_statement : 
   '{' '}' {
      fprintf(yyout, ">>> linia %i: { } REDUCE TO compound_statement\n", numFila);
   }
   | '{' declaration_list '}' {
      $$ = $<infoBison>2;
      fprintf(yyout, ">>> linia %i: { declaration_list } REDUCE TO compound_statement\n", numFila);
   }
   | '{' statement_list '}' {
      $$ = $<infoBison>2;
      fprintf(yyout, ">>> linia %i: { statement_list } REDUCE TO compound_statement\n", numFila);
   }
   | '{' declaration_list statement_list '}' {
      $$ = $<infoBison>3;
      fprintf(yyout, ">>> linia %i: { declaration_list statement_list } REDUCE TO compound_statement\n", numFila);
   }
;

/* ============================================================================================ */
/* ===================================== [ statement_list ] =================================== */
/* ============================================================================================ */
statement_list : 
   statement {
      $$ = $<infoBison>1;
      fprintf(yyout, ">>> linia %i: statement REDUCE TO statement_list\n", numFila);
   }
   | statement_list M statement {
	  $$ = $<infoBison>3;
	  completar_llista((Cua *) $<infoBison>1.llista_seguents, $<infoBison>2.punter_quadruple);
      fprintf(yyout, ">>> linia %i: statement_list statement REDUCE TO statement_list\n", numFila);
   }
;

/* ============================================================================================ */ 
/* ================================== [ expression_statement ] ================================ */
/* ============================================================================================ */ 
expression_statement : 
   ';' {
      fprintf(yyout, ">>> linia %i: ';' REDUCE TO expression_statement\n", numFila);
   }
   | expression ';' {
      fprintf(yyout, ">>> linia %i: expression; REDUCE TO expression_statement\n", numFila);
   }
;

/* ============================================================================================ */       
/* ====================================== [ if_token ] ======================================== */
/* ============================================================================================ */
if_token : 
   ID_IF { conditional_if_while_for = TRUE; }
;

/* ============================================================================================ */       
/* ==================================== [ if_cond_header ] ==================================== */
/* ============================================================================================ */
if_cond_header : 
   if_token '(' expression ')' { 
      conditional_if_while_for = FALSE;
      $<infoBison>$ = $<infoBison>3; 
   }
;

/* ============================================================================================ */       
/* ======================================== [ for_token ] ===================================== */
/* ============================================================================================ */
for_token : 
   ID_FOR { conditional_if_while_for = TRUE; }
;

/* ============================================================================================ */       
/* ================================== [ selection_statement ] ================================= */
/* ============================================================================================ */
selection_statement : 
   if_cond_header M statement {
      completar_llista((Cua *) $<infoBison>1.llista_certs, $<infoBison>2.punter_quadruple);
      $<infoBison>$.llista_seguents = (void *) fusionar_cues((Cua *) $<infoBison>3.llista_seguents, (Cua *) $<infoBison>1.llista_falsos);
  
      fprintf(yyout, ">>> linia %i: ID_IF (expression) statement REDUCE TO selection_statement\n", numFila);
   }
   | if_cond_header M statement ID_ELSE N M statement {
      completar_llista((Cua *) $<infoBison>1.llista_certs, $<infoBison>2.punter_quadruple);
      completar_llista((Cua *) $<infoBison>1.llista_falsos, $<infoBison>6.punter_quadruple);
      $<infoBison>$.llista_seguents = (void *) fusionar_cues((Cua *) $<infoBison>7.llista_seguents, (Cua *) fusionar_cues((Cua *) $<infoBison>3.llista_seguents ,(Cua *) $<infoBison>5.llista_seguents));
		
      fprintf(yyout, ">>> linia %i: ID_IF (expression) statement ID_ELSE statement REDUCE TO selection_statement\n", numFila);
   }
   | ID_SWITCH '(' expression ')' statement {
      fprintf(yyout, ">>> linia %i: ID_SWITCH (expression) statement REDUCE TO selection_statement\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================== [ iteration_statement ] ================================= */
/* ============================================================================================ */
iteration_statement : 
   ID_WHILE { conditional_if_while_for = TRUE } '(' M expression ')' { conditional_if_while_for = FALSE; 
   } M statement {
      completar_llista((Cua *) $<infoBison>5.llista_certs, $<infoBison>8.punter_quadruple);
	  completar_llista((Cua *) $<infoBison>9.llista_seguents, $<infoBison>4.punter_quadruple);
	
      $<infoBison>$ = $<infoBison>5;
      $<infoBison>$.llista_seguents = $<infoBison>5.llista_falsos;
      
      emet_saltC3A($<infoBison>4.punter_quadruple);       
      fprintf(yyout, ">>> linia %i: ID_WHILE (expression) statement REDUCE TO iteration_statement\n", numFila);
   }
   | ID_DO M statement ID_WHILE { conditional_if_while_for = TRUE 
   } '(' M expression ')' ';' {
      conditional_if_while_for = FALSE;

      completar_llista((Cua *) $<infoBison>8.llista_certs, $<infoBison>2.punter_quadruple);
      completar_llista((Cua *) $<infoBison>3.llista_seguents, $<infoBison>7.punter_quadruple);
      
      $<infoBison>$.llista_seguents = $<infoBison>8.llista_falsos;  
      fprintf(yyout, ">>> linia %i: ID_DO statement ID_WHILE (expression); REDUCE TO iteration_statement\n", numFila);
   }
   | for_token '(' expression ';' M expression ';' {
      conditional_if_while_for = FALSE;
   
   } M expression ')' N M statement {
      completar_llista((Cua *) $<infoBison>6.llista_certs, $<infoBison>13.punter_quadruple);
	  completar_llista((Cua *) $<infoBison>12.llista_seguents, $<infoBison>5.punter_quadruple);
      completar_llista((Cua *) $<infoBison>14.llista_seguents, $<infoBison>9.punter_quadruple);
		
	  $<infoBison>$.llista_seguents = $<infoBison>6.llista_falsos;
	  emet_saltC3A($<infoBison>9.punter_quadruple);
		
      fprintf(yyout, ">>> linia %i: ID_FOR (expression; expression; expression) REDUCE TO iteration_statement\n", numFila);
   }
   | for_token '(' ';' M expression ';' {
      conditional_if_while_for = FALSE;
      
   } M expression ')' N M statement {
      completar_llista((Cua *) $<infoBison>5.llista_certs, $<infoBison>12.punter_quadruple);
	  completar_llista((Cua *) $<infoBison>11.llista_seguents, $<infoBison>4.punter_quadruple);
      completar_llista((Cua *) $<infoBison>13.llista_seguents, $<infoBison>8.punter_quadruple);
		
	  $<infoBison>$.llista_seguents = $<infoBison>5.llista_falsos;
	  emet_saltC3A($<infoBison>8.punter_quadruple);
       
      fprintf(yyout, ">>> linia %i: ID_FOR (;expression;expression) statement REDUCE TO iteration_statement\n", numFila);
   }
   
   | for_token '(' ';' M ';' {
      conditional_if_while_for = FALSE;         
      tmpCondicio = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));      
      
      tmpCondicio -> valorC3A = malloc(2); 
      strcpy(tmpCondicio -> valorC3A, "1");
      tmpCondicio -> tipus_var = TIPUS_INTEGER;
      tmpCondicio -> array = FALSE;
      tmpCondicio -> array_indexat = FALSE;
      tmpCondicio -> camp_struct_indexat = FALSE;
      
      emet_condicioC3A(tmpCondicio, tmpCondicio);
      
   } M expression ')' N M statement {
      completar_llista((Cua *) tmpCondicio -> llista_certs, $<infoBison>11.punter_quadruple);
	  completar_llista((Cua *) $<infoBison>10.llista_seguents, $<infoBison>4.punter_quadruple);
      completar_llista((Cua *) $<infoBison>12.llista_seguents, $<infoBison>7.punter_quadruple);
		
	  $<infoBison>$.llista_seguents = tmpCondicio -> llista_falsos;
	  emet_saltC3A($<infoBison>7.punter_quadruple);
       
      fprintf(yyout, ">>> linia %i: ID_FOR (;;expression) statement REDUCE TO iteration_statement\n", numFila);
   }
   | for_token '(' ';' M ';' {
      conditional_if_while_for = FALSE;         
      tmpCondicio = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));      
      
      tmpCondicio -> valorC3A = malloc(2); 
      strcpy(tmpCondicio -> valorC3A, "1");
      tmpCondicio -> tipus_var = TIPUS_INTEGER;
      tmpCondicio -> array = FALSE;
      tmpCondicio -> array_indexat = FALSE;
      tmpCondicio -> camp_struct_indexat = FALSE;
      
      emet_condicioC3A(tmpCondicio, tmpCondicio);
      
   } ')' M statement {
      completar_llista((Cua *) tmpCondicio -> llista_certs, $<infoBison>8.punter_quadruple);
		
	  $<infoBison>$.llista_seguents = tmpCondicio -> llista_falsos;
	  emet_saltC3A($<infoBison>4.punter_quadruple);
	  
      fprintf(yyout, ">>> linia %i: ID_FOR (;;) statement REDUCE TO iteration_statement\n", numFila);
   }
   | for_token '(' expression ';' M ';' {
      conditional_if_while_for = FALSE;         
      tmpCondicio = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));      
      
      tmpCondicio -> valorC3A = malloc(2); 
      strcpy(tmpCondicio -> valorC3A, "1");
      tmpCondicio -> tipus_var = TIPUS_INTEGER;
      tmpCondicio -> array = FALSE;
      tmpCondicio -> array_indexat = FALSE;
      tmpCondicio -> camp_struct_indexat = FALSE;
      
      emet_condicioC3A(tmpCondicio, tmpCondicio);
      
   } M expression ')' N M statement {
      completar_llista((Cua *) tmpCondicio -> llista_certs, $<infoBison>12.punter_quadruple);
	  completar_llista((Cua *) $<infoBison>11.llista_seguents, $<infoBison>5.punter_quadruple);
      completar_llista((Cua *) $<infoBison>13.llista_seguents, $<infoBison>8.punter_quadruple);
		
	  $<infoBison>$.llista_seguents = tmpCondicio -> llista_falsos;
	  emet_saltC3A($<infoBison>8.punter_quadruple);
       
      fprintf(yyout, ">>> linia %i: ID_FOR (expression;;expression) REDUCE TO iteration_statement\n", numFila);
   }
   | for_token '(' expression ';' M ';' {
      conditional_if_while_for = FALSE;         
      tmpCondicio = (struct t_infoBison *) malloc(sizeof(struct t_infoBison));      
      
      tmpCondicio -> valorC3A = malloc(2); 
      strcpy(tmpCondicio -> valorC3A, "1");
      tmpCondicio -> tipus_var = TIPUS_INTEGER;
      tmpCondicio -> array = FALSE;
      tmpCondicio -> array_indexat = FALSE;
      tmpCondicio -> camp_struct_indexat = FALSE;
      
      emet_condicioC3A(tmpCondicio, tmpCondicio);
      
   } ')' M statement {
      completar_llista((Cua *) tmpCondicio -> llista_certs, $<infoBison>9.punter_quadruple);
		
	  $<infoBison>$.llista_seguents = tmpCondicio -> llista_falsos;
	  emet_saltC3A($<infoBison>5.punter_quadruple);
	  
      fprintf(yyout, ">>> linia %i: ID_FOR (expression;;) statement REDUCE TO iteration_statement\n", numFila);
   }
   | for_token '(' ';' M expression ';' {               
      conditional_if_while_for = FALSE;
      
   } ')' M statement {
      completar_llista((Cua *) $<infoBison>5.llista_certs, $<infoBison>9.punter_quadruple);
		
	  $<infoBison>$.llista_seguents = $<infoBison>5.llista_falsos;
	  emet_saltC3A($<infoBison>4.punter_quadruple);
	  
      fprintf(yyout, ">>> linia %i: ID_FOR (;expression;) statement REDUCE TO iteration_statement\n", numFila);
   }
   | for_token '(' expression ';' M expression ';' {
      conditional_if_while_for = FALSE;
      
   } ')' M statement {
      completar_llista((Cua *) $<infoBison>6.llista_certs, $<infoBison>10.punter_quadruple);
		
	  $<infoBison>$.llista_seguents = $<infoBison>6.llista_falsos;
	  emet_saltC3A($<infoBison>5.punter_quadruple);
	  
      fprintf(yyout, ">>> linia %i: ID_FOR (expression;expression;) statement REDUCE TO iteration_statement\n", numFila);
   }
   | for_token '(' type_specifier expression error ';' error ';' error ')' statement {
      num_errors++; printErrorSintactic(TRUE, ERR_FOR_DECLARACIO_VARIABLES);
      yyerrok;
   }
;

/* ============================================================================================ */
/* ==================================== [ jump_statement ] ==================================== */
/* ============================================================================================ */
jump_statement : 
   ID_CONTINUE ';' {
      fprintf(yyout, ">>> linia %i: ID_CONTINUE; REDUCE TO jump_statement\n", numFila);   
   }
   | ID_BREAK ';' {
      fprintf(yyout, ">>> linia %i: ID_BREAK; REDUCE TO jump_statement\n", numFila);
   }
   | ID_RETURN ';' {
      fprintf(yyout, ">>> linia %i: ID_RETURN; REDUCE TO jump_statement\n", numFila);
   }
   | ID_RETURN expression ';' {
      if ($<infoBison>2.valorC3A == NULL) {
         $<infoBison>2.valorC3A = malloc(strlen($<infoBison>2.valor) + 1); 
         strcpy($<infoBison>2.valorC3A, $<infoBison>2.valor);
      }
      emet_retornFuncioC3A(&$<infoBison>2);
      
      fprintf(yyout, ">>> linia %i: ID_RETURN expression; REDUCE TO jump_statement\n", numFila);
   }
;

/* ============================================================================================ */
/* =================================== [ translation_unit ] =================================== */
/* ============================================================================================ */
translation_unit : 
   external_declaration {
      fprintf(yyout, ">>> linia %i: external_declaration REDUCE TO translation_unit\n", numFila);
   }
   | translation_unit external_declaration {
      fprintf(yyout, ">>> linia %i: translation_unit external_declaration REDUCE TO translation_unit\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================= [ external_declaration ] ================================= */
/* ============================================================================================ */
external_declaration : 
   function_definition {
      fprintf(yyout, ">>> linia %i: function_definition REDUCE TO external_declaration\n", numFila);
   }
   | declaration {
      fprintf(yyout, ">>> linia %i: declaration REDUCE external_declaration\n", numFila);
   }
;

/* ============================================================================================ */
/* ================================= [ function_definition ] ================================== */
/* ============================================================================================ */
function_definition : 
   declarator {
      $<infoBison>$ = $<infoBison>1;                  
      $<infoBison>$.tipus_var = TIPUS_VOID;
      
      tipus_var_funcio_retorn = TIPUS_VOID;
      valor_retorn = NULL;
      llista_seguents_funcio_retorn = (void *) crear_cua();
      
      funcioDeclaradaCorrecte = TRUE;
      sym_push_scope();
      currentScope = sym_get_scope();
      printInfoSintactic(OK_INCREMENT_AMBIT, currentScope);
      
      if (identificadorDeclarat($<infoBison>1.valor)) {
         if (simbol.funcio == TRUE) {
            printInfoSintactic(OK_CONSULTA_TAULA_SIMBOL_FUN_VAR, "funcio", $<infoBison>1.valor);
            $<infoBison>$.tipus_var = simbol.tipus_var;
          
            if ($<infoBison>1.num_funcio_parametres == 1) {
               if (($<infoBison>1.seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus($<infoBison>1.seguent_param_funcio -> valor))) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
               }
               else if ($<infoBison>1.seguent_param_funcio -> tipus_var == TIPUS_VOID) {
                  $<infoBison>1.num_funcio_parametres--;
               }
            }
          
            if (funcioDeclaradaCorrecte) {
               if (simbol.num_funcio_parametres != $<infoBison>1.num_funcio_parametres) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_DEF_FUNCIO_NUM_PARAMS_DIFERENTS, $<infoBison>1.valor);  
               }
               else {
                  /* Numero de parametres correctes per definir la funcio */
                  recordsetParam = $<infoBison>1.seguent_param_funcio;
                  for (count = 0; count < $<infoBison>1.num_funcio_parametres; count++) {
                     if ((recordsetParam -> array != TRUE) && (simbol.funcio_params[count].array == TRUE)) {
                        funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ES_ARRAY, count + 1, $<infoBison>1.valor);
                     }
                     else if ((recordsetParam -> array == TRUE) && (simbol.funcio_params[count].array != TRUE)) {
                        funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_NO_ES_ARRAY, count + 1, $<infoBison>1.valor);
                     }
                     else {
                        if (simbol.funcio_params[count].tipus_var != recordsetParam -> tipus_var) {
                           funcioDeclaradaCorrecte = FALSE;
                           num_errors++; printErrorSintactic(TRUE, ERR_PARAM_FUNCIO_DEFINICIO, count + 1, $<infoBison>1.valor, tipusDadesID(simbol.funcio_params[count].tipus_var, 0), tipusDadesID(recordsetParam -> tipus_var, 0));
                        }
                     }
                     recordsetParam = recordsetParam -> seguent_param_funcio;
                  }
                  if (funcioDeclaradaCorrecte) {
                     printInfoSintactic(OK_DEFINICIO_FUNCIO, $<infoBison>1.valor);   
                  }   
               }
            }             
         }
         else { funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_FUNCIO, $<infoBison>1.valor); }
      }
      else {

         idSimbol = (char *) malloc(strlen($<infoBison>1.valor) + 1);
         strcpy(idSimbol, $<infoBison>1.valor);
         simbol.tipus_var = TIPUS_VOID;
         simbol.tipus = FUNCIO;
         simbol.funcio = TRUE;
         simbol.num_funcio_parametres = $<infoBison>1.num_funcio_parametres;
      
         simbol.idLexic = ID_IDENTIFICADOR;
         strcpy(simbol.nomLexic, "IDENTIFICADOR");
         simbol.ambit = -1; 

         if ($<infoBison>1.num_funcio_parametres == 1) {
            if (($<infoBison>1.seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus($<infoBison>1.seguent_param_funcio -> valor))) {
               funcioDeclaradaCorrecte = FALSE;
               num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
            }
            else if ($<infoBison>1.seguent_param_funcio -> tipus_var == TIPUS_VOID) {
               $<infoBison>1.num_funcio_parametres--;
               simbol.num_funcio_parametres = 0;
            }
         }
         
         if (funcioDeclaradaCorrecte) { 
            simbol.funcio_params = malloc(sizeof(struct t_param) * $<infoBison>1.num_funcio_parametres);
          
            recordsetParam = $<infoBison>1.seguent_param_funcio;
            for (count = 0; (count < $<infoBison>1.num_funcio_parametres); count++) {
               if (recordsetParam -> tipus_var == TIPUS_VOID) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
               }
               else {               
                  simbol.funcio_params[count].tipus_var = recordsetParam -> tipus_var;
                  if (recordsetParam -> array == TRUE) {
                     simbol.funcio_params[count].array = TRUE;
                     simbol.funcio_params[count].tam_array = recordsetParam -> tam_array;
                  }
                  else {
                     simbol.funcio_params[count].array = FALSE;
                     simbol.funcio_params[count].tam_array = 0;
                  }
               }
               recordsetParam = recordsetParam -> seguent_param_funcio;
            } 
            
            if (funcioDeclaradaCorrecte) {
               if (sym_global_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "funcio", idSimbol);
               }
               else { 
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "funcio", idSimbol);
               }
         
               printSimbolInfo((char *) idSimbol); 
            }
         }
      }
      
      if (funcioDeclaradaCorrecte) {
         iniRegistreActivacioFuncions($<infoBison>1.valor);    
         iniC3AFuncions();

         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen($<infoBison>1.valor) + 7);
         sprintf(quadrupleC3A -> sentenciaC3A, "START %s", $<infoBison>1.valor);
          
         encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
         C3AFuncions -> num_quadruples++;
                            
         recordsetParam = $<infoBison>1.seguent_param_funcio;
         for (count = 0; count < $<infoBison>1.num_funcio_parametres; count++) {
            if (esTipus(recordsetParam -> valor) == FALSE) {               
               idSimbol = (char *) malloc(strlen(recordsetParam -> valor) + 1);
               strcpy(idSimbol, recordsetParam -> valor);
               simbol.tipus_var = recordsetParam -> tipus_var;
               simbol.tipus = VARIABLE;
               simbol.funcio = FALSE;
               simbol.num_funcio_parametres = 0;
      
               if (recordsetParam -> array == TRUE) {
                 simbol.array = TRUE;
                 simbol.tam_array = recordsetParam -> tam_array;
               }
               else simbol.array = FALSE;
        
               simbol.idLexic = ID_IDENTIFICADOR;
               strcpy(simbol.nomLexic, "IDENTIFICADOR");
               simbol.ambit = sym_get_scope(); 

               simbol.funcio_params = NULL;
         
               if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) { num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRES_LOCALS_FUNCIO, idSimbol); }
               else {
                  afegirParamRA(registreActivacioFuncions, recordsetParam -> valor, recordsetParam -> tipus_var, recordsetParam -> array, recordsetParam -> tam_array);
                  printInfoSintactic(OK_PARAMETRES_LOCALS_FUNCIO, idSimbol);
               }
            }
            else printErrorSintactic(FALSE, WARNING_NOM_PARAMETRE_FUNCIO_NO_DEC, count + 1, idSimbol);
           
            recordsetParam = recordsetParam -> seguent_param_funcio;
         }  
      }
   }
   compound_statement M { 
      currentScope = sym_get_scope();
      sym_pop_scope();
      printInfoSintactic(OK_DECREMENT_AMBIT, currentScope);
      if (funcioDeclaradaCorrecte) { 
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
         encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
         C3AFuncions -> num_quadruples++;

         quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("RETURN") + 1);
         sprintf(quadrupleC3A -> sentenciaC3A, "RETURN"); 
   
         completar_llista((Cua *) llista_seguents_funcio_retorn, $<infoBison>4.punter_quadruple);
         completar_llista((Cua *) $<infoBison>3.llista_seguents, $<infoBison>4.punter_quadruple);                          
         printRegistreActivacio(registreActivacioFuncions);
         printC3AFuncions(C3AFuncions, $<infoBison>1.valor);
      }

      fprintf(yyout, ">>> linia %i: declarator compound_statement REDUCE TO function_definition\n", numFila);
   }
   | declaration_specifiers declarator declaration_list compound_statement {
      fprintf(yyout, ">>> linia %i: declaration_specifiers declarator declaration_list compound_statement REDUCE TO function_definition\n", numFila);
   }
   | declaration_specifiers declarator {
      $<infoBison>$ = $<infoBison>2; 
      
      tipus_var_funcio_retorn = TIPUS_VOID;
      valor_retorn = NULL;
      llista_seguents_funcio_retorn = (void *) crear_cua();
      
      funcioDeclaradaCorrecte = TRUE;
      sym_push_scope();
      currentScope = sym_get_scope();
      printInfoSintactic(OK_INCREMENT_AMBIT, currentScope);
      
      if (identificadorDeclarat($<infoBison>2.valor)) {
         if (simbol.funcio == TRUE) {
            printInfoSintactic(OK_CONSULTA_TAULA_SIMBOL_FUN_VAR, "funcio", $<infoBison>2.valor);
            $<infoBison>$.tipus_var = simbol.tipus_var;
            tipus_var_funcio_retorn = simbol.tipus_var;
            
            if ($<infoBison>2.num_funcio_parametres == 1) {
               if (($<infoBison>2.seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus($<infoBison>2.seguent_param_funcio -> valor))) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
               }
               else if ($<infoBison>2.seguent_param_funcio -> tipus_var == TIPUS_VOID) {
                  $<infoBison>2.num_funcio_parametres--;
               }
            }
            
            if (funcioDeclaradaCorrecte) {
               if (simbol.num_funcio_parametres != $<infoBison>2.num_funcio_parametres) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_DEF_FUNCIO_NUM_PARAMS_DIFERENTS, $<infoBison>2.valor);  
               }
               else {
                  if (simbol.tipus_var == $<infoBison>1.tipus_var) {
                     /* Numero de parametres correctes per definir la funcio */
                     recordsetParam = $<infoBison>2.seguent_param_funcio;
                     for (count = 0; count < $<infoBison>2.num_funcio_parametres; count++) {
                        if ((recordsetParam -> array != TRUE) && (simbol.funcio_params[count].array == TRUE)) {
                           funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_ES_ARRAY, count + 1, $<infoBison>2.valor);
                        }
                        else if ((recordsetParam -> array == TRUE) && (simbol.funcio_params[count].array != TRUE)) {
                           funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_FUNCIO_PARAM_NO_ES_ARRAY, count + 1, $<infoBison>2.valor);
                        }
                        else {
                           if (simbol.funcio_params[count].tipus_var != recordsetParam -> tipus_var) {
                              funcioDeclaradaCorrecte = FALSE;
                              num_errors++; printErrorSintactic(TRUE, ERR_PARAM_FUNCIO_DEFINICIO, count + 1, $<infoBison>2.valor, tipusDadesID(simbol.funcio_params[count].tipus_var, 0), tipusDadesID(recordsetParam -> tipus_var, 0));
                           }
                        }
                        recordsetParam = recordsetParam -> seguent_param_funcio;
                     }
                     if (funcioDeclaradaCorrecte) {
                        printInfoSintactic(OK_DEFINICIO_FUNCIO, $<infoBison>2.valor);   
                     }
                  }
                  else { funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_VALOR_RETORN_FUNCIO, $<infoBison>2.valor); }
               } 
            }            
         }
         else { funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_VARIABLE_NO_FUNCIO, $<infoBison>2.valor); }
      }
      else {

         idSimbol = (char *) malloc(strlen($<infoBison>2.valor) + 1);
         strcpy(idSimbol, $<infoBison>2.valor);
         simbol.tipus_var = $<infoBison>1.tipus_var;
         tipus_var_funcio_retorn = $<infoBison>1.tipus_var;
         $<infoBison>$.tipus_var = $<infoBison>1.tipus_var;
         simbol.tipus = FUNCIO;
         simbol.funcio = TRUE;
         simbol.num_funcio_parametres = $<infoBison>2.num_funcio_parametres;
      
         simbol.idLexic = ID_IDENTIFICADOR;
         strcpy(simbol.nomLexic, "IDENTIFICADOR");
         simbol.ambit = -1; 
         
         if ($<infoBison>2.num_funcio_parametres == 1) {
            if (($<infoBison>2.seguent_param_funcio -> tipus_var == TIPUS_VOID) && (!esTipus($<infoBison>2.seguent_param_funcio -> valor))) {
               funcioDeclaradaCorrecte = FALSE;
               num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
            }
            else if ($<infoBison>2.seguent_param_funcio -> tipus_var == TIPUS_VOID) {
               $<infoBison>2.num_funcio_parametres--;
               simbol.num_funcio_parametres = 0;
            }
         }
         
         if (funcioDeclaradaCorrecte) {
            simbol.funcio_params = malloc(sizeof(struct t_param) * $<infoBison>2.num_funcio_parametres);
          
            recordsetParam = $<infoBison>2.seguent_param_funcio;
            for (count = 0; (count < $<infoBison>2.num_funcio_parametres); count++) {
               if (recordsetParam -> tipus_var == TIPUS_VOID) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRE_FUNCIO_VOID);
               }
               else {
                  simbol.funcio_params[count].tipus_var = recordsetParam -> tipus_var;
                  if (recordsetParam -> array == TRUE) {
                     simbol.funcio_params[count].array = TRUE;
                     simbol.funcio_params[count].tam_array = recordsetParam -> tam_array;
                  }
                  else {
                     simbol.funcio_params[count].array = FALSE;
                     simbol.funcio_params[count].tam_array = 0;
                  }
               }
               recordsetParam = recordsetParam -> seguent_param_funcio;
            } 
            
            if (funcioDeclaradaCorrecte) {
               if (sym_global_add((char *) idSimbol, &simbol) != SYMTAB_OK) {
                  funcioDeclaradaCorrecte = FALSE;
                  num_errors++; printErrorSintactic(TRUE, ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR, "funcio", idSimbol);
               }
               else { 
                  printInfoSintactic(OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR, "funcio", idSimbol);
               }
         
               printSimbolInfo((char *) idSimbol); 
            }
         }
      }
      if (funcioDeclaradaCorrecte) {
         iniRegistreActivacioFuncions($<infoBison>2.valor);
         iniC3AFuncions();
         
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen($<infoBison>2.valor) + 7);
         sprintf(quadrupleC3A -> sentenciaC3A, "START %s", $<infoBison>2.valor);
          
         encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
         C3AFuncions -> num_quadruples++;
         
         afegirParamRA(registreActivacioFuncions, "RETURN", $<infoBison>1.tipus_var, $<infoBison>1.array, $<infoBison>1.tam_array);                   
         
         recordsetParam = $<infoBison>2.seguent_param_funcio;
         for (count = 0; count < $<infoBison>2.num_funcio_parametres; count++) {
            if (esTipus(recordsetParam -> valor) == FALSE) {          
               idSimbol = (char *) malloc(strlen(recordsetParam -> valor) + 1);
               strcpy(idSimbol, recordsetParam -> valor);
               simbol.tipus_var = recordsetParam -> tipus_var;
               simbol.tipus = VARIABLE;
               simbol.funcio = FALSE;
               simbol.num_funcio_parametres = 0;
      
               if (recordsetParam -> array == TRUE) {
                  simbol.array = TRUE;
                  simbol.tam_array = recordsetParam -> tam_array;
               }
               else simbol.array = FALSE;
      
               simbol.idLexic = ID_IDENTIFICADOR;
               strcpy(simbol.nomLexic, "IDENTIFICADOR");
               simbol.ambit = sym_get_scope(); 

               simbol.funcio_params = NULL;
           
               if (sym_add((char *) idSimbol, &simbol) != SYMTAB_OK) { num_errors++; printErrorSintactic(TRUE, ERR_PARAMETRES_LOCALS_FUNCIO, idSimbol); }
               else {
                  afegirParamRA(registreActivacioFuncions, recordsetParam -> valor, recordsetParam -> tipus_var, recordsetParam -> array, recordsetParam -> tam_array);
                  printInfoSintactic(OK_PARAMETRES_LOCALS_FUNCIO, idSimbol);
               }   
            }
            else printErrorSintactic(FALSE, WARNING_NOM_PARAMETRE_FUNCIO_NO_DEC, count + 1, idSimbol);
            
            recordsetParam = recordsetParam -> seguent_param_funcio;
         }      
      }
   }
   compound_statement M {                
      currentScope = sym_get_scope();
      sym_pop_scope();
      printInfoSintactic(OK_DECREMENT_AMBIT, currentScope);
      if (funcioDeclaradaCorrecte) {
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
         encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
         C3AFuncions -> num_quadruples++;

         if (valor_retorn == NULL) {
            quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("RETURN") + 1);
            sprintf(quadrupleC3A -> sentenciaC3A, "RETURN"); 
         }
         else {
            quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("RETURN ") + strlen(valor_retorn) + 1);
            sprintf(quadrupleC3A -> sentenciaC3A, "RETURN %s", valor_retorn);
         }
         completar_llista((Cua *) llista_seguents_funcio_retorn, $<infoBison>5.punter_quadruple);
         completar_llista((Cua *) $<infoBison>4.llista_seguents, $<infoBison>5.punter_quadruple);                     
         printRegistreActivacio(registreActivacioFuncions);
         printC3AFuncions(C3AFuncions, $<infoBison>2.valor);
      }
      
      fprintf(yyout, ">>> linia %i: declaration_specifiers declarator compound_statement REDUCE TO function_definition\n", numFila);
   }
   | declarator declaration_list compound_statement {               
      fprintf(yyout, ">>> linia %i: declarator declaration_list compound_statement REDUCE TO function_definition\n", numFila);
   }
;

/* ============================================================================================ */
/* =================================== [ declaration_list ] =================================== */
/* ============================================================================================ */
declaration_list : 
   declaration {
      fprintf(yyout, ">>> linia %i: declaration REDUCE TO declaration_list\n", numFila);
   }
   | declaration_list declaration {
      fprintf(yyout, ">>> linia %i: declaration_list declaration REDUCE TO declaration_list\n", numFila);
   }
;

/* ============================================================================================ */
/* ========================================== [ M ] =========================================== */
/* ============================================================================================ */
M: { 
   $$.punter_quadruple = C3AFuncions -> num_quadruples + 1; 
};

/* ============================================================================================ */
/* ========================================== [ N ] =========================================== */
/* ============================================================================================ */
N: {
   $$.llista_seguents = (void *) crear_cua();
    
   quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
   quadrupleC3A -> num_sentencia = C3AFuncions -> num_quadruples + 1;
   encuar(C3AFuncions -> quadrupleC3A, (void *) quadrupleC3A);
   C3AFuncions -> num_quadruples++;

   quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("GOTO ") + 1);
   sprintf(quadrupleC3A -> sentenciaC3A, "GOTO ");     
         
   $$.punter_quadruple = C3AFuncions -> num_quadruples;
   encuar((void *) $$.llista_seguents,(void *) quadrupleC3A);
};

%%

   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_operacioC3A(struct t_infoBison * param1,                         ##
      ##                              struct t_infoBison * param2,                            ##
      ##                              struct t_infoBison * paramResult,                       ##   
      ##                              int operacio)                                           ##
      ##                   - param1: parametre 1                                              ##
      ##                   - param2: parametre 2                                              ##
      ##                   - paramResult: parametre resultat                                  ##
      ##                   - operacio: operacio                                               ##
      ##                                                                                      ##
      ##                     Funcio que emet una operacio en C3A                              ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_operacioC3A(struct t_infoBison * param1, struct t_infoBison * param2, struct t_infoBison * paramResult, int operacio) { 
   int val, err = FALSE;
   int tipus_var_retorn;
   char * varTMPCasting, * varTMPOperacio, * varTMPComplex1, * varTMPComplex2, * varTMP;
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   int solveAssignC3A;
   char * cp1, * cp2;
   
   solveAssignC3A = FALSE;
   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; } 
   
   if (((operacio != '=') && (param1 -> tipus_var != TIPUS_NULL) && (param2 -> tipus_var != TIPUS_NULL) &&
       (param1 -> tipus_var != TIPUS_STRUCT) && (param2 -> tipus_var != TIPUS_STRUCT)) ||
       ((operacio == '=') && (paramResult -> tipus_var != TIPUS_NULL) && (param1 -> tipus_var != TIPUS_NULL) && 
       (paramResult -> tipus_var != TIPUS_STRUCT) && (param1 -> tipus_var != TIPUS_STRUCT))) {
                    
      if (operacio != '=') {
         cp1 = param1 -> valorC3A;
         cp2 = param2 -> valorC3A;
      
         val = operacioC3A(param1 -> tipus_var, param2 -> tipus_var, operacio);
         if (val == 1) tipus_var_retorn = param2 -> tipus_var;
         else tipus_var_retorn = param1 -> tipus_var;
  
         if (((param1 -> camp_struct_indexat == TRUE) && (param2 -> camp_struct_indexat == TRUE)) ||
            ((param1 -> array_indexat == TRUE) && (param2 -> array_indexat == TRUE)) ||
            ((param1 -> camp_struct_indexat == TRUE) && (param2 -> array_indexat == TRUE)) ||
            ((param1 -> array_indexat == TRUE) && (param2 -> camp_struct_indexat == TRUE))) {
            
            /* Cas complex: param1 i param2 son tipus complexes */
            if ((param1 -> camp_struct_indexat == TRUE) && (param2 -> camp_struct_indexat == TRUE)) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex1, param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            
               varTMPComplex2 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex2) + strlen(param2 -> valorC3A) + log10Func(param2 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex2, param2 -> valorC3A, param2 -> offset_camp_struct_indexat);
 
               param2 -> valorC3A = varTMPComplex2;
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            }
            else if ((param1 -> camp_struct_indexat == TRUE) && (param2 -> array_indexat == TRUE)) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex1, param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
               
               varTMPComplex2 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex2) + strlen(param2 -> valorC3A) + strlen(param2 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex2, param2 -> valorC3A, param2 -> array_indexat_offset);
 
               param2 -> valorC3A = varTMPComplex2;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            }
            else if ((param1 -> array_indexat == TRUE) && (param2 -> camp_struct_indexat == TRUE)) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex1, param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
                              
               varTMPComplex2 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex2) + strlen(param2 -> valorC3A) + log10Func(param2 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex2, param2 -> valorC3A, param2 -> offset_camp_struct_indexat);
 
               param2 -> valorC3A = varTMPComplex2;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            }
            else {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex1, param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;

               varTMPComplex2 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex2) + strlen(param2 -> valorC3A) + strlen(param2 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex2, param2 -> valorC3A, param2 -> array_indexat_offset);
 
               param2 -> valorC3A = varTMPComplex2;
            
               encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
               pC3A -> num_quadruples++;
            }       
         }
         else if ((param1 -> camp_struct_indexat == TRUE) || (param1 -> array_indexat == TRUE) ||
                  (param2 -> camp_struct_indexat == TRUE) || (param2 -> array_indexat == TRUE))  {
            
            /* Cas semi-complex: param1 o param2 es de tipus complex */
            if (param1 -> camp_struct_indexat == TRUE) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex1, param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
            }
            else if (param2 -> camp_struct_indexat == TRUE) {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param2 -> valorC3A) + log10Func(param2 -> offset_camp_struct_indexat) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%d]", varTMPComplex1, param2 -> valorC3A, param2 -> offset_camp_struct_indexat);
 
               param2 -> valorC3A = varTMPComplex1;
            }
            else if (param1 -> array_indexat == TRUE) { 
               varTMPComplex1 = afegirVarTemporalRA(pRA, param1 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex1, param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
            }
            else {
               varTMPComplex1 = afegirVarTemporalRA(pRA, param2 -> tipus_var);
               quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
               quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPComplex1) + strlen(param2 -> valorC3A) + strlen(param2 -> array_indexat_offset) + 7);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s[%s]", varTMPComplex1, param2 -> valorC3A, param2 -> array_indexat_offset);
 
               param2 -> valorC3A = varTMPComplex1;
            }
            encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
            pC3A -> num_quadruples++;
         }
         else {
            if ((param1 -> tipus_var == TIPUS_CHARACTER) || (param2 -> tipus_var == TIPUS_CHARACTER)) {
               if ((param1 -> tipus_var == TIPUS_CHARACTER) && (strlen(param1 -> valorC3A) == 1)) {
                  varTMP = (char *) malloc(4);
                  sprintf(varTMP, "'%s'", param1 -> valorC3A);
                  param1 -> valorC3A = varTMP;    
               }
               if ((param2 -> tipus_var == TIPUS_CHARACTER) && (strlen(param2 -> valorC3A) == 1)) {
                  varTMP = (char *) malloc(4);
                  sprintf(varTMP, "'%s'", param2 -> valorC3A);
                  param2 -> valorC3A = varTMP;    
               }
            }  
         }        
      }
      else {
	     val = operacioC3A(paramResult -> tipus_var, param1 -> tipus_var, operacio);
	     tipus_var_retorn = paramResult -> tipus_var;               
         
         if (((param1 -> camp_struct_indexat == TRUE) && (paramResult -> camp_struct_indexat == TRUE)) ||
            ((param1 -> array_indexat == TRUE) && (paramResult -> array_indexat == TRUE)) ||
            ((param1 -> camp_struct_indexat == TRUE) && (paramResult -> array_indexat == TRUE)) ||
            ((param1 -> array_indexat == TRUE) && (paramResult -> camp_struct_indexat == TRUE))) {
                     
            /* Cas complex: param1 i param2 son tipus complexes */
            if ((param1 -> camp_struct_indexat == TRUE) && (paramResult -> camp_struct_indexat == TRUE)) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
               
               varTMPComplex2 = (char *) malloc(strlen(paramResult -> valorC3A) + log10Func(paramResult -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex2, "%s[%d]", paramResult -> valorC3A, paramResult -> offset_camp_struct_indexat);
 
               paramResult -> valorC3A = varTMPComplex2;
               solveAssignC3A = TRUE;                    
            }
            else if ((param1 -> camp_struct_indexat == TRUE) && (paramResult -> array_indexat == TRUE)) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;
               
               varTMPComplex2 = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(paramResult -> array_indexat_offset) + 3);
               sprintf(varTMPComplex2, "%s[%s]", paramResult -> valorC3A, paramResult -> array_indexat_offset);
 
               paramResult -> valorC3A = varTMPComplex2;
               solveAssignC3A = TRUE;
            }
            else if ((param1 -> array_indexat == TRUE) && (paramResult -> camp_struct_indexat == TRUE)) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
               sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
               
               varTMPComplex2 = (char *) malloc(strlen(paramResult -> valorC3A) + log10Func(paramResult -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex2, "%s[%d]", paramResult -> valorC3A, paramResult -> offset_camp_struct_indexat);
 
               paramResult -> valorC3A = varTMPComplex2;
               solveAssignC3A = TRUE;
            }
            else {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
               sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
               
               varTMPComplex2 = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(paramResult -> array_indexat_offset) + 3);
               sprintf(varTMPComplex2, "%s[%s]", paramResult -> valorC3A, paramResult -> array_indexat_offset);
 
               paramResult -> valorC3A = varTMPComplex2;
               solveAssignC3A = TRUE;
            }
         }
         else if ((param1 -> camp_struct_indexat == TRUE) || (param1 -> array_indexat == TRUE) ||
                  (paramResult -> camp_struct_indexat == TRUE) || (paramResult -> array_indexat == TRUE))  {
            
            /* Cas semi-complex: param1 o param2 es de tipus complex */
            if (param1 -> camp_struct_indexat == TRUE) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
               param1 -> valorC3A = varTMPComplex1;            
            }
            else if (paramResult -> camp_struct_indexat == TRUE) {
               varTMPComplex1 = (char *) malloc(strlen(paramResult -> valorC3A) + log10Func(paramResult -> offset_camp_struct_indexat) + 3);
               sprintf(varTMPComplex1, "%s[%d]", paramResult -> valorC3A, paramResult -> offset_camp_struct_indexat);
 
               paramResult -> valorC3A = varTMPComplex1;
            }
            else if (param1 -> array_indexat == TRUE) {
               varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
               sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
               param1 -> valorC3A = varTMPComplex1;
            }
            else {
               varTMPComplex1 = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(paramResult -> array_indexat_offset) + 3);
               sprintf(varTMPComplex1, "%s[%s]", paramResult -> valorC3A, paramResult -> array_indexat_offset);
 
               paramResult -> valorC3A = varTMPComplex1;
            }
         }
         else {
            if ((param1 -> tipus_var == TIPUS_CHARACTER) || (paramResult -> tipus_var == TIPUS_CHARACTER)) {
               if ((param1 -> tipus_var == TIPUS_CHARACTER) && (strlen(param1 -> valorC3A) == 1)) {
                  varTMP = (char *) malloc(4);
                  sprintf(varTMP, "'%s'", param1 -> valorC3A);
                  param1 -> valorC3A = varTMP;    
               }
               if ((paramResult -> tipus_var == TIPUS_CHARACTER) && (strlen(paramResult -> valorC3A) == 1)) {
                  varTMP = (char *) malloc(4);
                  sprintf(varTMP, "'%s'", paramResult -> valorC3A);
                  paramResult -> valorC3A = varTMP;    
               }
            }  
         } 
      }

      if (val != 0) {
         varTMPCasting = afegirVarTemporalRA(pRA, tipus_var_retorn);
      
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      
         if (val == 1) {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(param1 -> valorC3A) + 6);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, param1 -> valorC3A);
         }
         else {
            if (operacio != '=') {
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(param2 -> valorC3A) + 6);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, param2 -> valorC3A);
            }
            else {
               quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(param1 -> valorC3A) + 6);
               sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, param1 -> valorC3A);         
            }
         }
      
         encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
         pC3A -> num_quadruples++;
      }
      else {
         if (solveAssignC3A == TRUE) {
            varTMPCasting = afegirVarTemporalRA(pRA, tipus_var_retorn);
      
            quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
            quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(param1 -> valorC3A) + 5);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s", varTMPCasting, param1 -> valorC3A);
               
            encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
            pC3A -> num_quadruples++;
            val = 2;
         }
      }

      /* ################# C3A -> OPERACIO ################# */
      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;
   
      if (operacio != '=') {
         varTMPOperacio = afegirVarTemporalRA(pRA, tipus_var_retorn);
         paramResult -> valorC3A = varTMPOperacio;
   
         if (val == 1) {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(varTMPCasting) + strlen(strOperacioC3A) + strlen(param2 -> valorC3A) + 7);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s %s", paramResult -> valorC3A, varTMPCasting, strOperacioC3A, param2 -> valorC3A);
         }
         else if (val == 2) {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(param1 -> valorC3A) + strlen(strOperacioC3A) + strlen(varTMPCasting) + 7);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s %s", paramResult -> valorC3A, param1 -> valorC3A, strOperacioC3A, varTMPCasting);
         }
         else {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(param1 -> valorC3A) + strlen(strOperacioC3A) + strlen(param2 -> valorC3A) + 7);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s %s", paramResult -> valorC3A, param1 -> valorC3A, strOperacioC3A, param2 -> valorC3A);
         }
         param1 -> valorC3A = cp1;
         param2 -> valorC3A = cp2;
      }
      else {
         if (val == 2) {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(varTMPCasting) + 5);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s", paramResult -> valorC3A, varTMPCasting);   
         }
         else {
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(param1 -> valorC3A) + 5);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s", paramResult -> valorC3A, param1 -> valorC3A);
         }   
      }
      paramResult -> array_indexat = FALSE;
      paramResult -> camp_struct_indexat = FALSE;
      paramResult -> tipus_var = tipus_var_retorn;
   }
   else paramResult -> tipus_var = TIPUS_NULL;   
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_operacioCanviSigneC3A(struct t_infoBison * param1,               ##
      ##                                           struct t_infoBison * paramResult)          ##
      ##                   - param1: parametre1                                               ##
      ##                   - paramResult: parametre resultat                                  ##
      ##                                                                                      ##
      ##                     Funcio que emet una operacio de canvi de signe en C3A            ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_operacioCanviSigneC3A(struct t_infoBison * param1, struct t_infoBison * paramResult) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;   
   char * varTMPComplex1, * varTMPOperacio;
   char * cp1, * varTMP;
   
   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; } 
   
   if ((param1 -> tipus_var != TIPUS_NULL) && (param1 -> tipus_var != TIPUS_STRUCT)) {
      cp1 = param1 -> valorC3A;
      
      if ((param1 -> camp_struct_indexat == TRUE) || (param1 -> array_indexat == TRUE)) {
         if (param1 -> camp_struct_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
            sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
            param1 -> valorC3A = varTMPComplex1; 
         }
         else {
            varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
            sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
            param1 -> valorC3A = varTMPComplex1;
         }
      }
      else {
         if (param1 -> tipus_var == TIPUS_CHARACTER) {
            if ((param1 -> tipus_var == TIPUS_CHARACTER) && (strlen(param1 -> valorC3A) == 1)) {
               varTMP = (char *) malloc(4);
               sprintf(varTMP, "'%s'", param1 -> valorC3A);
               param1 -> valorC3A = varTMP;    
            }
         }  
      }
      
      /* ################# C3A -> OPERACIO ################# */
      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;
   
      varTMPOperacio = afegirVarTemporalRA(pRA, param1 -> tipus_var);
      paramResult -> valorC3A = varTMPOperacio;
      paramResult -> tipus_var = param1 -> tipus_var;

      switch (param1 -> tipus_var) {
         case TIPUS_CHARACTER: strcpy(strOperacioC3A, "CHSC"); break; 
         case TIPUS_SHORT: strcpy(strOperacioC3A, "CHSS"); break;
         case TIPUS_INTEGER: strcpy(strOperacioC3A, "CHSI"); break;            
         case TIPUS_LONG: strcpy(strOperacioC3A, "CHSL"); break;             
         case TIPUS_FLOAT: strcpy(strOperacioC3A, "CHSF"); break;
         case TIPUS_DOUBLE: strcpy(strOperacioC3A, "CHSD"); break;            
      }
            
      quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(paramResult -> valorC3A) + strlen(strOperacioC3A) + strlen(param1 -> valorC3A) + 6);
      sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", paramResult -> valorC3A, strOperacioC3A, param1 -> valorC3A);
             
      param1 -> valorC3A = cp1;
      paramResult -> array_indexat = FALSE;
      paramResult -> camp_struct_indexat = FALSE;
   }
   else paramResult -> tipus_var = TIPUS_NULL;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_condicioC3A(struct t_infoBison * param1,                         ##
      ##                                 struct t_infoBison * paramResult)                    ##
      ##                   - param1: parametre1                                               ##
      ##                   - paramResult: parametre resultat                                  ##
      ##                                                                                      ##
      ##                     Funcio que emet una condicio en C3A                              ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_condicioC3A(struct t_infoBison * param1, struct t_infoBison * paramResult) {
   int val;
   char * varTMPCasting, * varTMPComplex1, * varTMP;
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   
   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }
   
   if ((param1 -> tipus_var != TIPUS_NULL) && (paramResult -> tipus_var != TIPUS_STRUCT)) {
      
      val = operacioC3A(TIPUS_INTEGER, param1 -> tipus_var, '=');
      
      if ((param1 -> camp_struct_indexat == TRUE) || (param1 -> array_indexat == TRUE)) {     
         /* Cas semi-complex: param1 o param2 es de tipus complex */
         if (param1 -> camp_struct_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + log10Func(param1 -> offset_camp_struct_indexat) + 3);
            sprintf(varTMPComplex1, "%s[%d]", param1 -> valorC3A, param1 -> offset_camp_struct_indexat);
 
            param1 -> valorC3A = varTMPComplex1;            
         }
         else if (param1 -> array_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(param1 -> valorC3A) + strlen(param1 -> array_indexat_offset) + 3);
            sprintf(varTMPComplex1, "%s[%s]", param1 -> valorC3A, param1 -> array_indexat_offset);
 
            param1 -> valorC3A = varTMPComplex1;
         }
      }
      else {
         if ((param1 -> tipus_var == TIPUS_CHARACTER) && (strlen(param1 -> valorC3A) == 1)) {
            varTMP = (char *) malloc(4);
            sprintf(varTMP, "'%s'", param1 -> valorC3A);
            param1 -> valorC3A = varTMP;    
         }  
      }
         
      if (val == 2) {
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
         
         varTMPCasting = afegirVarTemporalRA(pRA, TIPUS_INTEGER);  
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(param1 -> valorC3A) + 6);
         sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, param1 -> valorC3A);

         encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
         pC3A -> num_quadruples++;
      }
      
      /* ################# C3A -> CONDICIO ################# */
      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;
 
      if (val == 2) {
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + 10);
         sprintf(quadrupleC3A -> sentenciaC3A, "IF %s GOTO ", varTMPCasting);
      }
      else {
         quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(param1 -> valorC3A) + 10);
         sprintf(quadrupleC3A -> sentenciaC3A, "IF %s GOTO ", param1 -> valorC3A);
      }

  	  paramResult -> llista_certs = (void *) crear_cua();
	  encuar((void *) paramResult -> llista_certs, (void *) quadrupleC3A); 
	 
      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;

      quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("GOTO ") + 1);
  	  sprintf(quadrupleC3A -> sentenciaC3A, "GOTO ");

  	  paramResult -> llista_falsos = (void *) crear_cua();
	  encuar((void *) paramResult -> llista_falsos, (void *) quadrupleC3A);    
   }    
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_saltC3A(int num_linia)                                           ##  
      ##                   - num_linia: numero de linia                                       ##
      ##                                                                                      ##
      ##                     Funcio que emet un salt al numero de linia indicat               ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_saltC3A(int num_linia) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;

   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }

   quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
   quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
   encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
   pC3A -> num_quadruples++;

   quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("GOTO ") + log10Func(num_linia) + 1);
   sprintf(quadrupleC3A -> sentenciaC3A, "GOTO %d", num_linia);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_cridaC3A(char * nom_funcio,                                      ##
      ##                              struct t_infoBison * parametres,                        ##
      ##                              int tipus_retorn,                                       ##   
      ##                              struct t_infoBison * paramResult)                       ##
      ##                   - nom_funcio: nom de la funcio                                     ##
      ##                   - parametres: parametres de la funcio                              ##
      ##                   - tipus_retorn: tipus de retorn de la funcio                       ##
      ##                   - paramResult: parametre resultat                                  ##
      ##                                                                                      ##
      ##                     Funcio que emet una crida a funcio en C3A                        ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_cridaC3A(char * nom_funcio, struct t_infoBison * parametres, int tipus_retorn, struct t_infoBison * paramResult) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   int numParametres, val;
   char * varTMPComplex1, * varTMPCasting, * varTMP;
   
   currentScope = sym_get_scope();
   if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
   else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }
   
   if (parametres != NULL) {
      recordsetParam = parametres -> seguent_param_funcio; 
      for (count = 0; count < parametres -> num_funcio_parametres; count++) {
         quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
         quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
         encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
         pC3A -> num_quadruples++;

         if (recordsetParam -> valorC3A == NULL) {
            recordsetParam -> valorC3A = malloc(strlen(recordsetParam -> valor) + 1); 
            strcpy(recordsetParam -> valorC3A, recordsetParam -> valor);
         }
         
         if (recordsetParam -> camp_struct_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(recordsetParam -> valorC3A) + log10Func(recordsetParam -> offset_camp_struct_indexat) + 3);
            sprintf(varTMPComplex1, "%s[%d]", recordsetParam -> valorC3A, recordsetParam -> offset_camp_struct_indexat);
 
            recordsetParam -> valorC3A = varTMPComplex1;            
         }
         else if (recordsetParam -> array_indexat == TRUE) {
            varTMPComplex1 = (char *) malloc(strlen(recordsetParam -> valorC3A) + strlen(recordsetParam -> array_indexat_offset) + 3);
            sprintf(varTMPComplex1, "%s[%s]", recordsetParam -> valorC3A, recordsetParam -> array_indexat_offset);
 
            recordsetParam -> valorC3A = varTMPComplex1;
         }
         else if (recordsetParam -> tipus_var == TIPUS_CHARACTER) {
            varTMP = (char *) malloc(4);
            sprintf(varTMP, "'%s'", recordsetParam -> valorC3A);
            recordsetParam -> valorC3A = varTMP;
         }
         
         val = operacioC3A(simbol.funcio_params[count].tipus_var, recordsetParam -> tipus_var, '=');
         
         if (val == 2) { 
            varTMPCasting = afegirVarTemporalRA(pRA, simbol.funcio_params[count].tipus_var);
              
            quadrupleC3A -> sentenciaC3A = (char *) malloc(strlen(varTMPCasting) + strlen(strCastingC3A) + strlen(strOperacioC3A) + strlen(recordsetParam -> valorC3A) + 6);
            sprintf(quadrupleC3A -> sentenciaC3A, "%s := %s %s", varTMPCasting, strCastingC3A, recordsetParam -> valorC3A);

            quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
            quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
            encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
            pC3A -> num_quadruples++;
            
            quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("PARAM ") + strlen(varTMPCasting) + 1);
            sprintf(quadrupleC3A -> sentenciaC3A, "PARAM %s", varTMPCasting);
         }
         else {
            quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("PARAM ") + strlen(recordsetParam -> valorC3A) + 1);
            sprintf(quadrupleC3A -> sentenciaC3A, "PARAM %s", recordsetParam -> valorC3A);
         }
         recordsetParam = recordsetParam -> seguent_param_funcio;
      }
      numParametres = parametres -> num_funcio_parametres;
   }
   else numParametres = 0;
   
   quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
   quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
   encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
   pC3A -> num_quadruples++;
   
   paramResult -> tipus_var = tipus_retorn;
   if ((tipus_retorn != TIPUS_VOID) && (tipus_retorn != TIPUS_NULL)) {
	  paramResult -> valorC3A = afegirVarTemporalRA(pRA, tipus_retorn);
      quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen(paramResult -> valorC3A) + strlen(nom_funcio) + log10Func(numParametres) + 12);
      sprintf(quadrupleC3A -> sentenciaC3A, "%s := CALL %s, %d", paramResult -> valorC3A, nom_funcio, numParametres);
   }
   else {
      quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen(nom_funcio) + log10Func(numParametres) + 8);
      sprintf(quadrupleC3A -> sentenciaC3A, "CALL %s, %d", nom_funcio, numParametres);
   }
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_structC3A(struct t_infoBison * paramStruct)                      ##  
      ##                   - paramStruct: parametre de l'estructura                           ##
      ##                                                                                      ##
      ##                     Funcio que emet una estructura en C3A                            ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_structC3A(struct t_infoBison * paramStruct) {
   struct t_infoBison p1Temp;
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   char * varTMP;

   if (paramStruct -> tipus_var != TIPUS_NULL) { 
      currentScope = sym_get_scope();
      if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
      else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }
   
      varTMP = afegirVarTemporalRA(pRA, paramStruct -> tipus_var);
      
      p1Temp.valorC3A = (char *) malloc(strlen(paramStruct -> valorC3A) + log10Func(paramStruct -> offset_camp_struct_indexat) + 3);
      sprintf(p1Temp.valorC3A, "%s[%d]", paramStruct -> valorC3A, paramStruct -> offset_camp_struct_indexat);
      
      paramStruct -> valorC3A = varTMP;
      
      p1Temp.tipus_var = paramStruct -> tipus_var;
      p1Temp.array_indexat = FALSE;
      paramStruct -> array_indexat = FALSE; 
      p1Temp.camp_struct_indexat = FALSE;
      paramStruct -> camp_struct_indexat = FALSE;
      
      emet_operacioC3A(&p1Temp, NULL, paramStruct, '=');                        
   }
   else paramStruct -> tipus_var = TIPUS_NULL; 
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: emet_arrayC3A(struct t_infoBison * paramResult,                       ##
      ##                              struct t_infoBison * paramArray,                        ##
      ##                              struct t_infoBison * paramArrayIndex)                   ##   
      ##                   - paramResult: parametre resultat                                  ##
      ##                   - paramArray: parametre array                                      ##
      ##                   - paramArrayIndex: parametre index del array                       ##
      ##                                                                                      ##
      ##                     Funcio que emet un array en C3A                                  ##
      ##                                                                                      ##
      ########################################################################################## */
      
void emet_arrayC3A(struct t_infoBison * paramResult, struct t_infoBison * paramArray, struct t_infoBison * paramArrayIndex) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   int tamTipus;
   struct t_infoBison p1Temp, pResTemp;
   char * varTMP;
   
   if ((paramResult -> tipus_var != TIPUS_NULL) && (paramArray -> tipus_var != TIPUS_NULL) && (paramArrayIndex -> tipus_var != TIPUS_NULL)) {
      currentScope = sym_get_scope();
      if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
      else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; } 
   
      if (paramArrayIndex -> camp_struct_indexat == TRUE) {
         emet_structC3A(paramArrayIndex);
      }
      paramResult -> camp_struct_indexat = FALSE;
      
      p1Temp.tipus_var = TIPUS_INTEGER;
      if (paramArray -> tipus_var != TIPUS_STRUCT) tamTipus = tamanyTipusVar(paramArray -> tipus_var);
      else tamTipus = tamanyStructbyInfoBison(paramArray);
   
      p1Temp.valorC3A = (char *) malloc(log10Func(tamTipus) + 1);
      sprintf(p1Temp.valorC3A, "%d", tamTipus);
   
      p1Temp.array_indexat = FALSE;
      paramArrayIndex -> array_indexat = FALSE;
      pResTemp.array_indexat = FALSE;
      p1Temp.camp_struct_indexat = FALSE;
      
      emet_operacioC3A(&p1Temp, paramArrayIndex, &pResTemp, '*');
   
      paramResult -> array_indexat_offset = (char *) malloc(log10Func(pRA -> num_llista_temporals) + 3);
      sprintf(paramResult -> array_indexat_offset, "$t%d", pRA -> num_llista_temporals);
      
      paramResult -> array_indexat = TRUE;
      paramResult -> tipus_var = paramArray -> tipus_var;
   }
   else paramResult -> tipus_var = TIPUS_NULL;   
}

void emet_retornFuncioC3A(struct t_infoBison * param1) {
   t_registreC3A * pC3A;
   t_registreActivacio * pRA;
   struct t_infoBison p1Temp;
      
   if ((tipus_var_funcio_retorn != TIPUS_NULL) && (tipus_var_funcio_retorn != TIPUS_VOID) && (param1 -> tipus_var != TIPUS_STRUCT) && (llista_seguents_funcio_retorn != NULL)) {
      currentScope = sym_get_scope();
      if (currentScope == -1) { pRA = registreActivacioGlobal; pC3A = C3AGlobal; }
      else { pRA = registreActivacioFuncions; pC3A = C3AFuncions; }
      
      if (valor_retorn == NULL) {
         valor_retorn = afegirVarTemporalRA(pRA, tipus_var_funcio_retorn);
      }
      
      p1Temp.valorC3A = valor_retorn;
      p1Temp.tipus_var = tipus_var_funcio_retorn;
      p1Temp.array_indexat = FALSE;
      p1Temp.camp_struct_indexat = FALSE;
      
      emet_operacioC3A(param1, NULL, &p1Temp, '=');

      quadrupleC3A = (struct t_quadrupleC3A *) malloc(sizeof(struct t_quadrupleC3A));
      quadrupleC3A -> num_sentencia = pC3A -> num_quadruples + 1;
      encuar(pC3A -> quadrupleC3A, (void *) quadrupleC3A);
      pC3A -> num_quadruples++;

      quadrupleC3A -> sentenciaC3A = (char * ) malloc(strlen("GOTO ") + 1);
      sprintf(quadrupleC3A -> sentenciaC3A, "GOTO ");     
         
      encuar((void *) llista_seguents_funcio_retorn, (void *) quadrupleC3A);
   }  
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: completar_llista(Cua * llista, int seguent)                           ##                           
      ##                   - llista: llista per completar                                     ##
      ##                   - seguent: num linia                                               ##
      ##                                                                                      ##
      ##                     Funcio que completa la llista de seguents                        ##
      ##                                                                                      ##
      ########################################################################################## */
      
void completar_llista(Cua * llista, int seguent) {
   struct t_quadrupleC3A * tmpQuadruple;
   char * tmpSentencia;
	
   if (llista != NULL) {
	   	
      tmpQuadruple = (struct t_quadrupleC3A *) primer(llista);
      while (tmpQuadruple != NULL) {
         tmpSentencia = (char *) malloc(strlen(tmpQuadruple -> sentenciaC3A) + log10Func(seguent) + 1);
         sprintf(tmpSentencia, "%s%d", tmpQuadruple -> sentenciaC3A, seguent);  
         tmpQuadruple -> sentenciaC3A = tmpSentencia;
             
	     desencuar(llista);
         tmpQuadruple = (struct t_quadrupleC3A *) primer(llista);
      }
   }
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: iniC3AFuncions()                                                      ## 
      ##                                                                                      ##                          
      ##                   Funcio que inicialitza el registre C3A de les funcions             ##
      ##                                                                                      ##
      ########################################################################################## */

int iniC3AFuncions() {
   C3AFuncions = (t_registreC3A *) malloc(sizeof(t_registreC3A));
   return iniC3A(C3AFuncions);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: iniC3A(t_registreC3A * pC3A)                                          ##                           ##
      ##                   - pC3A: registre C3A                                               ##
      ##                                                                                      ##
      ##                     Funcio que inicialitza el registre C3A                           ##
      ##                                                                                      ##
      ########################################################################################## */
      
int iniC3A(t_registreC3A * pC3A) {
     
   if (pC3A != NULL) {

      pC3A -> num_quadruples = 0;
	  pC3A -> quadrupleC3A = crear_cua();

      return 0;         
   }
   return -1;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: iniRegistreActivacioFuncions(char * nom_registre)                     ##                           
      ##                   - nom_registre: nom del registre d'activacio                       ##
      ##                                                                                      ##
      ##                     Funcio que inicialitza el registre d'activacio de les funcions   ##
      ##                                                                                      ##
      ########################################################################################## */
        
int iniRegistreActivacioFuncions(char * nom_registre) {
   registreActivacioFuncions = (t_registreActivacio *) malloc(sizeof(t_registreActivacio));
   return iniRegistreActivacio(registreActivacioFuncions, nom_registre);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: iniRegistreActivacio(t_registreActivacio * pRA, char * nom_registre)  ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                   - nom_registre: nom del registre d'activacio                       ##
      ##                                                                                      ##
      ##                     Funcio que inicialitza el registre d'activacio                   ##
      ##                                                                                      ##
      ########################################################################################## */
         
int iniRegistreActivacio(t_registreActivacio * pRegistreActivacio, char * nom_registre) {
     
   if (pRegistreActivacio != NULL) {
      pRegistreActivacio -> nom_registre = malloc(strlen(nom_registre) + 1); strcpy(pRegistreActivacio -> nom_registre, nom_registre);                    
      pRegistreActivacio -> num_llista_parametres = 0;
      pRegistreActivacio -> num_llista_locals = 0;
      pRegistreActivacio -> num_llista_temporals = 0;
      pRegistreActivacio -> currentOffset = 0; 
      
      pRegistreActivacio -> primer_llista_parametres = NULL;
      pRegistreActivacio -> primer_llista_locals = NULL;
      pRegistreActivacio -> primer_llista_temporals = NULL;
      pRegistreActivacio -> ultim_llista_parametres = NULL;
      pRegistreActivacio -> ultim_llista_locals = NULL;
      pRegistreActivacio -> ultim_llista_temporals = NULL;
      
      return 0;         
   }
   return -1;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printRegistreActivacio(t_registreActivacio * pRA)                     ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                                                                                      ##
      ##                     Funcio que imprimeix el registre d'activacio                     ##
      ##                                                                                      ##
      ########################################################################################## */
       
void printRegistreActivacio(t_registreActivacio * pRegistreActivacio) {
   t_cadenaRegistreActivacio * pvalors;
   
   fprintf(fRegActivacio, "FUNCIO %s\n", pRegistreActivacio->nom_registre);
   pvalors = pRegistreActivacio -> primer_llista_parametres;
   
   fprintf(fRegActivacio, "\n[ + ] Parametres (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      if (pvalors -> es_array == FALSE) { 
         fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      }
      else {
         fprintf(fRegActivacio, "\t\t[ - ] %s %s[%lu] %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_array, pvalors -> tam_tipus, pvalors -> offset);
      }
      
      pvalors = pvalors -> seguent;
   } 
   
   pvalors = pRegistreActivacio -> primer_llista_locals;
   fprintf(fRegActivacio, "\n[ + ] Variables Locals (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      if (pvalors -> es_array == FALSE) { 
         fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      }
      else {
         fprintf(fRegActivacio, "\t\t[ - ] %s %s[%lu] %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_array, pvalors -> tam_tipus, pvalors -> offset);
      }
      
      pvalors = pvalors -> seguent;
   }     

   pvalors = pRegistreActivacio -> primer_llista_temporals;
   fprintf(fRegActivacio, "\n[ + ] Variables Temporals (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      
      pvalors = pvalors -> seguent;
   }     
   fprintf(fRegActivacio, "\n\n");
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printRegistreActivacioGlobal(t_registreActivacio * pRA)               ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                                                                                      ##
      ##                     Funcio que imprimeix el registre d'activacio Global              ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printRegistreActivacioGlobal(t_registreActivacio * pRegistreActivacio) {
   t_cadenaRegistreActivacio * pvalors;
   
   fprintf(fRegActivacio, "GLOBAL\n");
      
   pvalors = pRegistreActivacio -> primer_llista_locals;
   fprintf(fRegActivacio, "\n[ + ] Variables Globals (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      if (pvalors -> es_array == FALSE) { 
         fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      }
      else {
         fprintf(fRegActivacio, "\t\t[ - ] %s %s[%lu] %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_array, pvalors -> tam_tipus, pvalors -> offset);
      }
      
      pvalors = pvalors -> seguent;
   }
   
   pvalors = pRegistreActivacio -> primer_llista_temporals;
   fprintf(fRegActivacio, "\n[ + ] Variables Temporals (nom_param tipus_param tipus_param_tamany offset)\n\n");
   
   for (;pvalors;) {
      fprintf(fRegActivacio, "\t\t[ - ] %s %s %d %d\n", pvalors -> nom, tipusDadesID(pvalors -> tipus, 0), pvalors -> tam_tipus, pvalors -> offset);
      
      pvalors = pvalors -> seguent;
   }     
   fprintf(fRegActivacio, "\n\n"); 
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printC3AFuncions(t_registreActivacio * pC3A, char * nom_funcio)       ##                           
      ##                   - pC3A: registre C3A                                               ##
      ##                   - nom_funcio: nom de la funcio                                     ##
      ##                                                                                      ##
      ##                     Funcio que imprimeix el registre C3A                             ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printC3AFuncions(t_registreC3A * pC3A, char * nom_funcio) {
   t_quadrupleC3A * pQuadruple;
   Cua * llista_quadruples;

   fprintf(fCodi3A, "SUBRUTINA %s:\n\n", nom_funcio);
   
   llista_quadruples = pC3A -> quadrupleC3A;
    
   for (;primer(llista_quadruples);) {
      pQuadruple = (struct t_quadrupleC3A *) primer(llista_quadruples);
      fprintf(fCodi3A, "\tLINIA %d: %s\n", pQuadruple -> num_sentencia, pQuadruple -> sentenciaC3A);
      
      desencuar(llista_quadruples);
   }
   fprintf(fCodi3A, "\n");
   
   fprintf(fCodi3A, "HALT\n\n");
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printC3AGlobal(t_registreActivacio * pC3A)                            ##                           
      ##                   - pC3A: registre C3A                                               ##
      ##                                                                                      ##
      ##                     Funcio que imprimeix el registre C3A Global                      ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printC3AGlobal(t_registreC3A * pC3A) {
   t_quadrupleC3A * pQuadruple;
   Cua * llista_quadruples;

   fprintf(fCodi3A, "GLOBAL:\n\n");
   
   llista_quadruples = pC3A -> quadrupleC3A;
    
   for (;primer(llista_quadruples);) {
      pQuadruple = (struct t_quadrupleC3A *) primer(llista_quadruples);
      fprintf(fCodi3A, "\tLINIA %d: %s\n", pQuadruple -> num_sentencia, pQuadruple -> sentenciaC3A);
      
      desencuar(llista_quadruples);
   }
}
 
 
   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: afegirParamRA(t_registreActivacio * pRA, char * nom_var, int t_var)   ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                   - nom_var: nom de la variable                                      ##
      ##                   - t_var: tipus de la variable                                      ##
      ##                   - es_array: el paràmetre es un array o no                          ##
      ##                   - tam_array: en cas de que sigui un array indica el seu tamany     ##
      ##                                                                                      ##
      ########################################################################################## */

void afegirParamRA(t_registreActivacio * pRegistreActivacio, char * nom_var, int tipus_var, int es_array, long tam_array) {
   t_cadenaRegistreActivacio * pcadenaRA;
   
   pcadenaRA = (t_cadenaRegistreActivacio *) malloc(sizeof(t_cadenaRegistreActivacio));
   pcadenaRA -> nom = (char *) malloc(strlen(nom_var) + 1); strcpy(pcadenaRA -> nom, nom_var);
   
   if (tipus_var == TIPUS_STRUCT) pcadenaRA -> tam_tipus = tamanyStruct(&simbol);
   else pcadenaRA -> tam_tipus = tamanyTipusVar(tipus_var);
    
   pcadenaRA -> tipus = tipus_var;
   pcadenaRA -> offset = pRegistreActivacio -> currentOffset;
   pcadenaRA -> es_array = es_array;
   if (es_array) {
      pcadenaRA -> tam_array = tam_array;
      pcadenaRA -> tam_total = (tam_array * (pcadenaRA -> tam_tipus));
   }
   else { 
      pcadenaRA -> tam_array = 0; 
      pcadenaRA -> tam_total = (pcadenaRA -> tam_tipus); 
   }
   
   pRegistreActivacio -> currentOffset += pcadenaRA -> tam_total; 
   
   if (pRegistreActivacio -> num_llista_parametres == 0) {                
      pRegistreActivacio -> primer_llista_parametres = pcadenaRA;
      pRegistreActivacio -> ultim_llista_parametres = pcadenaRA;
   }
   else { 
      (pRegistreActivacio -> ultim_llista_parametres) -> seguent = pcadenaRA;
      pRegistreActivacio -> ultim_llista_parametres = pcadenaRA;
   }
   pRegistreActivacio -> num_llista_parametres++;	
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: afegirVarLocalRA(t_registreActivacio * pRA, char * nom_var,           ##
      ##                                 struct t_simbol * simbol)                            ##                           
      ##                   - pRA: registre d'activacio                                        ##
      ##                   - nom_var: nom de la variable                                      ##
      ##                   - simbol: referencia a la taula de simbols                         ##
      ##                                                                                      ##
      ########################################################################################## */

void afegirVarLocalRA(t_registreActivacio * pRegistreActivacio, char * nom_var, struct t_simbol * simbol) {
   t_cadenaRegistreActivacio * pcadenaRA;
   
   pcadenaRA = (t_cadenaRegistreActivacio *) malloc(sizeof(t_cadenaRegistreActivacio));
   pcadenaRA -> nom = (char *) malloc(strlen(nom_var) + 1); strcpy(pcadenaRA -> nom, nom_var);
   
   if (simbol -> tipus_var == TIPUS_STRUCT) pcadenaRA -> tam_tipus = tamanyStruct(simbol);
   else pcadenaRA -> tam_tipus = tamanyTipusVar(simbol -> tipus_var);
   
   pcadenaRA -> tipus = simbol -> tipus_var;
   pcadenaRA -> offset = pRegistreActivacio -> currentOffset;
   pcadenaRA -> es_array = simbol -> array;
   if (simbol -> array) {
      pcadenaRA -> tam_array = simbol -> tam_array;
      pcadenaRA -> tam_total = (simbol -> tam_array * (pcadenaRA -> tam_tipus));
   }
   else { 
      pcadenaRA -> tam_array = 0; 
      pcadenaRA -> tam_total = (pcadenaRA -> tam_tipus);
   }
   
   pRegistreActivacio -> currentOffset += pcadenaRA -> tam_total; 
   
   if (pRegistreActivacio -> num_llista_locals == 0) {                
      pRegistreActivacio -> primer_llista_locals = pcadenaRA;
      pRegistreActivacio -> ultim_llista_locals = pcadenaRA;
   }
   else { 
      (pRegistreActivacio -> ultim_llista_locals) -> seguent = pcadenaRA;
      pRegistreActivacio -> ultim_llista_locals = pcadenaRA;
   }
   pRegistreActivacio -> num_llista_locals++;	
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: afegirVarTemporalRA(t_registreActivacio * pRA, int tipusVarTemp)      ##                          
      ##                   - pRA: registre d'activacio                                        ##
      ##                   - tipusVarTemp: tipus de la variable temporal                      ##
      ##                                                                                      ##
      ########################################################################################## */
      
char * afegirVarTemporalRA(t_registreActivacio * pRegistreActivacio, int tipusVarTemp) {
   t_cadenaRegistreActivacio * pcadenaRA;
   
   pcadenaRA = (t_cadenaRegistreActivacio *) malloc(sizeof(t_cadenaRegistreActivacio));
   pcadenaRA -> nom = (char *) malloc(2 + (log10Func((pRegistreActivacio -> num_llista_temporals) + 1) + 1)); 
   sprintf(pcadenaRA -> nom, "$t%d", (pRegistreActivacio -> num_llista_temporals) + 1);
   
   pcadenaRA -> tam_tipus = tamanyTipusVar(tipusVarTemp);
   pcadenaRA -> tipus = tipusVarTemp;
   pcadenaRA -> offset = pRegistreActivacio -> currentOffset;
   pcadenaRA -> es_array = 0;
   pcadenaRA -> tam_array = 0;
   pcadenaRA -> tam_total = (pcadenaRA -> tam_tipus);
   pRegistreActivacio -> currentOffset += pcadenaRA -> tam_total;
   
   if (pRegistreActivacio -> num_llista_temporals == 0) {                
      pRegistreActivacio -> primer_llista_temporals = pcadenaRA;
      pRegistreActivacio -> ultim_llista_temporals = pcadenaRA;
   }
   else { 
      (pRegistreActivacio -> ultim_llista_temporals) -> seguent = pcadenaRA;
      pRegistreActivacio -> ultim_llista_temporals = pcadenaRA;
   }
   pRegistreActivacio -> num_llista_temporals++;
   
   return pcadenaRA -> nom;      
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: tamanyTipusVar(int tipus)                                             ##
      ##                   - tipus: tipus de la variable                                      ##
      ##                                                                                      ##
      ##                     Retorna int: numero de bytes del tipus                           ##
      ##                                                                                      ##
      ########################################################################################## */
      
int tamanyTipusVar(int tipus) {
   switch (tipus) {
      case (TIPUS_CHARACTER): return 1;
      case (TIPUS_SHORT): return 2;
      case (TIPUS_INTEGER): return 4;
      case (TIPUS_LONG): return 8;
      case (TIPUS_FLOAT): return 4;
      case (TIPUS_DOUBLE): return 8;
   }
   return 0;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: log10Func(int num)                                                    ##
      ##                   - num: numero                                                      ##
      ##                                                                                      ##
      ##                     Retorna int: numero de bytes que ocupa el numero en string       ##
      ##                                                                                      ##
      ########################################################################################## */
      
int log10Func(int num) {
   if (num <= 0) return 1;
   else return (log10(num) + 1);
}    
     
      
   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: init_analisi_sintactic_O(char * fileOutput, char * nomFitxerRA)       ##
      ##                   - fileOutput: fitxer de sortida                                    ##
      ##                                                                                      ##
      ########################################################################################## */

int init_analisi_sintactic_O(char * fileOutput, char * nomFitxerRA, char * nomFitxerC3A) {
   int error; 
   
   nom_fitxerRA = nomFitxerRA;
   nom_fitxerC3A = nomFitxerC3A;
   yyout = fopen(fileOutput, "w");

   fRegActivacio = fopen(nomFitxerRA, "w");
   fCodi3A = fopen(nomFitxerC3A, "w");
   
   num_errors = 0; valor_retorn = NULL;
   if ((yyout == NULL) || (fRegActivacio == NULL) || (fCodi3A == NULL)) { error = EXIT_FAILURE; }
   else { error = EXIT_SUCCESS; }

   return error;

}

   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: end_analisi_sintactic_O(): tancament del fitxer de sortida            ##
      ##                                                                                      ##
      ########################################################################################## */

int end_analisi_sintactic_O() {
   int error;
   
   printRegistreActivacioGlobal(registreActivacioGlobal);
   printC3AGlobal(C3AGlobal);
   error = fclose(yyout);
   error |= fclose(fRegActivacio);
   error |= fclose(fCodi3A);
   
   if (num_errors > 0) {
      remove(nom_fitxerRA);
      remove(nom_fitxerC3A);         
      fprintf(stdout, "\n\n\t-----------------------------------------------------");
      fprintf(stdout, "\n\t\t[ ERR ] Compilacio amb %d error/s\n", num_errors);
      fprintf(stdout, "\t-----------------------------------------------------\n\n");
   }
   else {
      fprintf(stdout, "\n\n\t-----------------------------------------------------");
      fprintf(stdout, "\n\t\t[ OK ] Compilacio generada correctament\n"); 
      fprintf(stdout, "\t-----------------------------------------------------\n\n");
   }
   
   if (error == 0) { error = EXIT_SUCCESS; }
   else { error = EXIT_FAILURE; }
   
   return error; 
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: analisi_semantic()                                                    ##
      ##                                                                                      ##
      ########################################################################################## */
      
int analisi_semantic() {
   int error;
   
   registreActivacioGlobal = (t_registreActivacio *) malloc(sizeof(t_registreActivacio));
   iniRegistreActivacio(registreActivacioGlobal, "GLOBAL");
   
   C3AGlobal = (t_registreC3A *) malloc(sizeof(t_registreC3A));
   iniC3A(C3AGlobal);
   
   if (yyparse() == 0) { error =  EXIT_SUCCESS; }
   else { error =  EXIT_FAILURE; }
   
   return error;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: identificadorDeclaratMateixAmbit(char * idSimbol)                     ##
      ##                   - idSimbol: identificador del simbol                               ##
      ##                                                                                      ##
      ##                     Funcio per evitar redeclaracions de variables                    ##
      ##                                                                                      ##
      ########################################################################################## */
      
Boolean identificadorDeclaratMateixAmbit(char * idSimbol) {
   currentScope = sym_get_scope();
      
   if (sym_lookup(idSimbol, &simbol_tmp) == SYMTAB_OK) {
      if (simbol_tmp.ambit == currentScope) return TRUE;
   }
   return FALSE;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: identificadorDeclarat(char * idSimbol)                                ##
      ##                   - idSimbol: identificador del simbol                               ##
      ##                                                                                      ##
      ##                     Funcio que retorna TRUE: si esta a la taula de simbols           ##
      ##                                        FALSE: si no esta a la taula de simbols       ##
      ##                                                                                      ##
      ########################################################################################## */
      
Boolean identificadorDeclarat(char * idSimbol) {
   currentScope = sym_get_scope();
      
   if (sym_lookup(idSimbol, &simbol) == SYMTAB_OK) {
      return TRUE;
   }
   return FALSE;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: comprovacioTipusDades(Tipus_Dades t1, Tipus_Dades t2, int vsituacio)  ##
      ##                   - t1: tipus del paràmetre 1                                        ##
      ##                   - t2: tipus del paràmetre 2                                        ##
      ##                   - vsituacio: operacio, assignació, crida a funcio                  ##
      ##                                                                                      ##
      ##                     Funcio que retorna el tipus respecte les entrades                ##
      ##                                                                                      ##
      ########################################################################################## */
      
int comprovacioTipusDades(Tipus_Dades t1, Tipus_Dades t2, int vsituacio) {
   char situacio[20];
   int t3;
   
   if (vsituacio == 0) strcpy(situacio, "assignacio");
   else if (vsituacio == 1) strcpy(situacio, "funcio");
   else strcpy(situacio, "operacio");
   
   
   if ((vsituacio == 1) && (((t1 == TIPUS_STRUCT) && (t1 != t2)) || ((t2 == TIPUS_STRUCT) && (t1 != t2)))) {
      num_errors++; printErrorSintactic(TRUE, ERR_CRIDA_FUNCIO_STRUCTS);
   } 
   else if (((vsituacio == 0) || (vsituacio == 2)) && ((t1 == TIPUS_STRUCT) || (t2 == TIPUS_STRUCT))) {
      num_errors++; printErrorSintactic(TRUE, ERR_OPERACIO_ASSIG_ENTRE_STRUCTS, situacio);
   }
   else { 
       if ((vsituacio == ID_SITUACIO_OPERACIO) && (t1 < t2)) {
          t3 = t1; t1 = t2; t2 = t3;
       }
       
       switch (t1) {
          case TIPUS_INTEGER: 
               switch (t2) {
                  case TIPUS_INTEGER: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "int"); break;
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "INT"); break;
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "INT"); break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "INT");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "INT"); 
                                   break;
                  
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "INT");   
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "FLOAT", "INT");  
                                    break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "INT");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "INT");  
                                     break;
                                    
               }
               break;
               
          case TIPUS_SHORT: 
               switch (t2) {
                  case TIPUS_SHORT: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "short"); break; 
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "SHORT"); break;
                   
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "SHORT");  
                                      printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "INT", "SHORT"); 
                                      break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "SHORT");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "SHORT"); 
                                   break;
                  
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "SHORT");   
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "FLOAT", "SHORT");  
                                    break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "SHORT");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "SHORT");  
                                     break;
                                    
               }
               break;
               
          case TIPUS_CHARACTER: 
               switch (t2) {
                  case TIPUS_CHARACTER: break;
                  case TIPUS_STRING: if (!arrayDeclaracio) {
                                        arrayDeclaracio = FALSE;
                                        funcioDeclaradaCorrecte = FALSE;
                                        num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "char"); 
                                     }   
                                     break;  
                  
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "CHAR");  
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "SHORT", "CHAR"); 
                                    break;
                                      
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "CHAR");  
                                      printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "INT", "CHAR"); 
                                      break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "CHAR");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "CHAR"); 
                                   break;
                  
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "CHAR");   
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "FLOAT", "CHAR");  
                                    break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "CHAR");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "CHAR");  
                                     break;          
               }
               break;
               
          case TIPUS_FLOAT: 
               switch (t2) {
                  case TIPUS_FLOAT: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "float"); break;  
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "FLOAT"); break;
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "FLOAT"); break;
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "FLOAT"); break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "FLOAT");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "FLOAT"); 
                                   break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "FLOAT");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "FLOAT");  
                                     break;          
               }
               break;
               
          case TIPUS_DOUBLE: 
               switch (t2) {
                  case TIPUS_DOUBLE: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "double"); break;  
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "DOUBLE"); break;
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "DOUBLE"); break;
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "DOUBLE"); break;
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "DOUBLE"); break;
                    
                  case TIPUS_LONG: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "LONG", "DOUBLE");  
                                   printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "LONG", "DOUBLE"); 
                                   break;         
               }
               break;
               
          case TIPUS_LONG: 
               switch (t2) {
                  case TIPUS_LONG: break;
                  case TIPUS_STRING: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_STRING, situacio, "long"); break;  
                  case TIPUS_SHORT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "SHORT", "LONG"); break;
                  case TIPUS_INTEGER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "INT", "LONG"); break;
                  case TIPUS_CHARACTER: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "CHAR", "LONG"); break;
                    
                  case TIPUS_FLOAT: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "FLOAT", "LONG");  
                                    printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "FLOAT", "LONG"); 
                                    break;
                  
                  case TIPUS_DOUBLE: printErrorSintactic(FALSE, WARNING_CASTING, situacio, "DOUBLE", "LONG");  
                                     printErrorSintactic(FALSE, WARNING_PRECISIO, situacio, "DOUBLE", "LONG");  
                                     break;          
               }
               break;
               
          case TIPUS_STRING: 
               switch (t2) {
                  case TIPUS_STRING: if (vsituacio == ID_SITUACIO_OPERACIO) {
                                        num_errors++; printErrorSintactic(TRUE, ERR_STRING_STRING_OP, situacio);   
                                     }
                                     break;
                                     
                  case TIPUS_LONG: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "long"); break;
                  
                  case TIPUS_SHORT: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "long"); break;
                  case TIPUS_INTEGER: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "int"); break;
                  case TIPUS_CHARACTER: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "char"); break;
                  case TIPUS_FLOAT: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "float"); break;
                  case TIPUS_DOUBLE: funcioDeclaradaCorrecte = FALSE; num_errors++; printErrorSintactic(TRUE, ERR_TYPE_TO_STRING, situacio, "double"); break;       
               }
               break;
       }
   }
   
   if ((vsituacio == ID_SITUACIO_OPERACIO) && (t1 != TIPUS_STRING) && (t2 != TIPUS_STRING) && (t1 != TIPUS_STRUCT) && (t2 != TIPUS_STRUCT)) {
       return t1;   
   }
   return -1;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: operacioC3A(Tipus_Dades t1, Tipus_Dades t2, int operacio)             ##
      ##                   - t1: tipus del paràmetre 1                                        ##
      ##                   - t2: tipus del paràmetre 2                                        ##
      ##                   - operacio: operacio                                               ##
      ##                                                                                      ##
      ##                     Funcio que retorna el codi 3 adreçes                             ##
      ##                                                                                      ##
      ########################################################################################## */
            
int operacioC3A(Tipus_Dades t1, Tipus_Dades t2, int operacio) {
   char tipus;
   int result = 0;
   
   strcpy(strCastingC3A, "");
   strcpy(strOperacioC3A, "");
   
   switch (t1) {
      case TIPUS_CHARACTER:
         tipus = 'C';
         switch (t2) {        
            case TIPUS_CHARACTER: break; 
            case TIPUS_SHORT: if (operacio == '=') { strcpy(strCastingC3A, "STC"); result = 2; }
                              else { tipus = 'S'; strcpy(strCastingC3A, "CTS"); result = 1; } 
                              break;
                              
            case TIPUS_INTEGER: if (operacio == '=') { strcpy(strCastingC3A, "ITC"); result = 2; }
                                else { tipus = 'I'; strcpy(strCastingC3A, "CTI"); result = 1; } 
                                break;
                            
            case TIPUS_LONG: if (operacio == '=') { strcpy(strCastingC3A, "LTC"); result = 2; }
                             else { tipus = 'L'; strcpy(strCastingC3A, "CTL"); result = 1; } 
                             break;
                              
            case TIPUS_FLOAT: if (operacio == '=') { strcpy(strCastingC3A, "FTC"); result = 2; }
                              else { tipus = 'F'; strcpy(strCastingC3A, "CTF"); result = 1; }
                              break;
                              
            case TIPUS_DOUBLE: if (operacio == '=') { strcpy(strCastingC3A, "DTC"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "CTD"); result = 1; } 
                               break;
         }
         break;
         
      case TIPUS_SHORT : 
         tipus = 'S';   
         switch (t2) {
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTS"); result = 2; break;
            case TIPUS_SHORT: break;   
                        
            case TIPUS_INTEGER: if (operacio == '=') { strcpy(strCastingC3A, "ITS"); result = 2; }
                                else { tipus = 'I'; strcpy(strCastingC3A, "STI"); result = 1; }
                                break;
                                
            case TIPUS_LONG: if (operacio == '=') { strcpy(strCastingC3A, "LTS"); result = 2; }
                             else { tipus = 'L'; strcpy(strCastingC3A, "STL"); result = 1; } 
                             break;
                             
            case TIPUS_FLOAT: if (operacio == '=') { strcpy(strCastingC3A, "FTS"); result = 2; }
                              else { tipus = 'F'; strcpy(strCastingC3A, "STF"); result = 1; }
                              break;
                              
            case TIPUS_DOUBLE: if (operacio == '=') { strcpy(strCastingC3A, "DTS"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "STD"); result = 1; }
                               break;
         }
         break;
         
      case TIPUS_INTEGER: 
         tipus = 'I'; 
         switch (t2) {
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTI"); result = 2; break;
            case TIPUS_SHORT: strcpy(strCastingC3A, "STI"); result = 2; break;               
            case TIPUS_INTEGER: break;
                           
            case TIPUS_LONG: if (operacio == '=') { strcpy(strCastingC3A, "LTI"); result = 2; }
                             else { tipus = 'L'; strcpy(strCastingC3A, "ITL"); result = 1; } 
                             break;
                              
            case TIPUS_FLOAT: if (operacio == '=') { strcpy(strCastingC3A, "FTI"); result = 2; }
                              else { tipus = 'F'; strcpy(strCastingC3A, "ITF"); result = 1; } 
                              break;
                              
            case TIPUS_DOUBLE: if (operacio=='=') { strcpy(strCastingC3A, "DTI"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "ITD"); result = 1; } 
                               break;
         }
         break;
      
      case TIPUS_LONG :
         tipus = 'L'; 
         switch (t2){
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTL"); result = 2; break;
            case TIPUS_SHORT: strcpy(strCastingC3A, "STL"); result = 2; break;
            case TIPUS_INTEGER: strcpy(strCastingC3A, "ITL"); result = 2; break;
            case TIPUS_LONG: break;
            
            case TIPUS_FLOAT: if (operacio == '=') { strcpy(strCastingC3A, "FTL"); result = 2; }
                              else { tipus = 'F'; strcpy(strCastingC3A, "LTF"); result = 1; } 
                              break;
            
            case TIPUS_DOUBLE: if (operacio == '=') { strcpy(strCastingC3A, "DTL"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "LTD"); result = 1; } 
                               break;
         }
         break;
         
      case TIPUS_FLOAT:
         tipus = 'F';
         switch (t2){
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTF"); result = 2; break;
            case TIPUS_SHORT: strcpy(strCastingC3A, "STF"); result = 2; break;
            case TIPUS_INTEGER: strcpy(strCastingC3A, "ITF"); result = 2; break;
            case TIPUS_LONG: strcpy(strCastingC3A, "LTF"); result = 2; break;
            case TIPUS_FLOAT: break;
            
            case TIPUS_DOUBLE: if (operacio == '=') { strcpy(strCastingC3A, "DTF"); result = 2; }
                               else { tipus = 'D'; strcpy(strCastingC3A, "FTD"); result = 1; } 
                               break;
         }
         break;
         
      case TIPUS_DOUBLE :
         tipus = 'D';
         switch (t2){
            case TIPUS_CHARACTER: strcpy(strCastingC3A, "CTD"); result = 2; break;
            case TIPUS_SHORT: strcpy(strCastingC3A, "STD"); result = 2; break;
            case TIPUS_INTEGER: strcpy(strCastingC3A, "ITD"); result = 2; break;
            case TIPUS_LONG: strcpy(strCastingC3A, "LTD"); result = 2; break;
            case TIPUS_FLOAT: strcpy(strCastingC3A, "FTD"); result = 2; break;
            case TIPUS_DOUBLE: break;
         }
         break;
   }
   
   switch(operacio) {
      case '+': strcpy(strOperacioC3A, "ADD_");
                strOperacioC3A[3] = tipus; break;
      
      case '-': strcpy(strOperacioC3A, "SUB_");
                strOperacioC3A[3] = tipus; break;
      
      case '*': strcpy(strOperacioC3A, "MUL_");
                strOperacioC3A[3] = tipus; break;
      
      case '/': strcpy(strOperacioC3A, "DIV_");
                strOperacioC3A[3] = tipus; break;
                 
      case '%': strcpy(strOperacioC3A, "MOD_");
                strOperacioC3A[3] = tipus; break;

      case ID_NE_OP: strcpy(strOperacioC3A, "NE"); break;
      case ID_EQ_OP: strcpy(strOperacioC3A, "EQ"); break;

      case '<': strcpy(strOperacioC3A, "LT_");
                strOperacioC3A[2] = tipus; break;
                
      case ID_LE_OP: strcpy(strOperacioC3A, "LE_");
                     strOperacioC3A[2] = tipus; break;
                  
      case '>': strcpy(strOperacioC3A, "GT_");
                strOperacioC3A[2] = tipus; break;
               
      case ID_GE_OP: strcpy(strOperacioC3A, "GE_");
                     strOperacioC3A[2] = tipus; break;
   }
   return result;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: yyerror(char * explanation)                                           ##
      ##                   - explanation: texte d'error                                       ##
      ##                                                                                      ##
      ########################################################################################## */
      
void yyerror(char * explanation) {
   num_errors++;  
   fprintf(stderr, "\n[ SINTACTIC/SEMANTIC -> Error ] >>> linia %i: %s\n", numFila, explanation);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printErrorSintactic(Boolean err, char * errorDesc, ...)               ##
      ##                   - err: indica si es error o warning                                ##
      ##                   - errorDesc: descripcio del error                                  ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printErrorSintactic(Boolean err, char * errorDesc, ...) {
   va_list args;
   va_start(args, errorDesc);
   char linea[2048];
   
   if (err) sprintf(linea, "\n[ SINTACTIC/SEMANTIC -> Error ] >>> linia %i: ", numFila);
   else sprintf(linea, "\n[ SINTACTIC/SEMANTIC -> Warning ] >>> linia %i: ", numFila);
   
   vsprintf(&linea[strlen(linea)], errorDesc, args);
   if (stdout != yyout) {
      fprintf(stderr, "%s\n", linea);
      fprintf(yyout, "%s\n", linea + 1);
   }
   else fprintf(stderr, "%s\n", linea);    
   va_end(args);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printSimbolInfo(char * idSimbol)                                      ##
      ##                   - idSimbol: identificador del simbol                               ##
      ##                                                                                      ##
      ##                     Mostra tota la informació per pantalla d'un simbol               ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printSimbolInfo(char * idSimbol) {
   if (sym_lookup(idSimbol, &simbol) == SYMTAB_OK) {
      if (simbol.funcio == TRUE) {
         if (stdout != yyout) {
            fprintf(stderr, "\t[ - ] Funcio: %s\n", idSimbol);
            fprintf(yyout, "\t[ - ] Funcio: %s\n", idSimbol);
            fprintf(stderr, "\t[ - ] %i Parametres:\n", simbol.num_funcio_parametres);
            fprintf(yyout, "\t[ - ] %i Parametres:\n", simbol.num_funcio_parametres);
            
            for (count = 0; count < simbol.num_funcio_parametres; count++) {
               if (simbol.funcio_params[count].array == TRUE) {
                  fprintf(stderr, "\t\tTipus: %s  Array: SI  Tamany_Array: %lu\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1), simbol.funcio_params[count].tam_array, 1);
                  fprintf(yyout, "\t\t\tTipus: %s  Array: SI  Tamany_Array: %lu\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1), simbol.funcio_params[count].tam_array, 1);
               }
               else {
                  fprintf(stderr, "\t\tTipus: %s  Array: NO\n\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1));
                  fprintf(yyout, "\t\t\tTipus: %s  Array: NO\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1));
               }    
            }
            
            fprintf(stderr, "\t[ - ] Tipus Retorn: %s\n\n", tipusDadesID(simbol.tipus_var, 1));
            fprintf(yyout, "\t[ - ] Tipus Retorn: %s\n", tipusDadesID(simbol.tipus_var, 1));
         }
         else {
            fprintf(stderr, "\t[ - ] Funcio: %s\n", idSimbol);
            fprintf(stderr, "\t[ - ] %i Parametres:\n", simbol.num_funcio_parametres);
            
            for (count = 0; count < simbol.num_funcio_parametres; count++) {
               if (simbol.funcio_params[count].array == TRUE) {
                  fprintf(stderr, "\t\tTipus: %s  Array: SI  Tamany_Array: %lu\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1), simbol.funcio_params[count].tam_array);
               }
               else {
                  fprintf(stderr, "\t\tTipus: %s  Array: NO\n", tipusDadesID(simbol.funcio_params[count].tipus_var, 1));
               }    
            }
            
            fprintf(stderr, "\t[ - ] Tipus Retorn: %s\n\n", tipusDadesID(simbol.tipus_var, 1));
         }   
      }
      else {
         if (stdout != yyout) {
            fprintf(stderr, "\t[ - ] Variable: %s\n", idSimbol);
            fprintf(yyout, "\t[ - ] Variable: %s\n", idSimbol);
            if (simbol.array == TRUE) {
               fprintf(stderr, "\t\tTipus: %s  Ambit: %d  Array: SI  Tamany_Array: %lu\n\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit, simbol.tam_array);
               fprintf(yyout, "\t\t\tTipus: %s  Ambit %d  Array: SI  Tamany_Array: %lu\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit, simbol.tam_array);
            }
            else {
               fprintf(stderr, "\t\tTipus: %s  Ambit %d  Array: NO\n\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit);
               fprintf(yyout, "\t\t\tTipus: %s  Ambit %d  Array: NO\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit);            
               if (simbol.tipus_var == TIPUS_STRUCT) {
                  fprintf(stderr, "\t\t[ - ] Struct: %s\n", idSimbol);
                  fprintf(stderr, "\t\t[ - ] %i Camps:\n", simbol.num_struct_camps);
                  fprintf(yyout, "\t\t\t[ - ] Struct: %s\n", idSimbol);
                  fprintf(yyout, "\t\t\t[ - ] %i Camps:\n", simbol.num_struct_camps);
                               
                  for (count = 0; count < simbol.num_struct_camps; count++) {
                     if (simbol.struct_camps[count].array == TRUE) {
                        fprintf(stderr, "\t\t\tNom: %s  Tipus: %s  Array: SI  Tamany_Array: %lu\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1), simbol.struct_camps[count].tam_array, 1);
                        fprintf(yyout, "\t\t\t\t    Nom: %s  Tipus: %s  Array: SI  Tamany_Array: %lu\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1), simbol.struct_camps[count].tam_array, 1);
                     }
                     else {
                        fprintf(stderr, "\t\t\tNom: %s  Tipus: %s  Array: NO\n\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1));
                        fprintf(yyout, "\t\t\t\t    Nom: %s  Tipus: %s  Array: NO\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1));
                     }    
                  }
                  fprintf(stderr, "\n");    
               }
            }
         }
         else {
            fprintf(stderr, "\t[ - ] Variable: %s\n", idSimbol);
            if (simbol.array == TRUE) {
               fprintf(stderr, "\t\tTipus: %s  Array: SI  Ambit %d  Tamany_Array: %lu\n\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit, simbol.tam_array);
            }
            else {
               fprintf(stderr, "\t\tTipus: %s  Ambit %d Array: NO\n\n", tipusDadesID(simbol.tipus_var, 1), simbol.ambit);
               if (simbol.tipus_var == TIPUS_STRUCT) {
                  fprintf(stderr, "\t\t[ - ] Struct: %s\n", idSimbol);
                  fprintf(stderr, "\t\t[ - ] %i Camps:\n", simbol.num_struct_camps);
                               
                  for (count = 0; count < simbol.num_struct_camps; count++) {
                     if (simbol.struct_camps[count].array == TRUE) {
                        fprintf(stderr, "\t\t\tNom: %s  Tipus: %s  Array: SI  Tamany_Array: %lu\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1), simbol.struct_camps[count].tam_array, 1);
                     }
                     else {
                        fprintf(stderr, "\t\t\tNom: %s  Tipus: %s  Array: NO\n\n", simbol.struct_camps[count].valor, tipusDadesID(simbol.struct_camps[count].tipus_var, 1));
                     }   
                  }
                  fprintf(stderr, "\n");      
               }         
            }
         }
      }   
   }
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: printInfoSintactic(char * errorDesc, ...)                             ##
      ##                   - errorDesc: descripcio de la informació a mostrar                 ##
      ##                                                                                      ##
      ########################################################################################## */
      
void printInfoSintactic(char * desc, ...) {
   va_list args;
   va_start(args, desc);
   char linea[2048];
   
   sprintf(linea, "\n[ SINTACTIC/SEMANTIC -> OK ] >>> linia %i: ", numFila);
   
   vsprintf(&linea[strlen(linea)], desc, args);
   if (stdout != yyout) {
      fprintf(stdout, "%s\n", linea);
      fprintf(yyout, "%s\n", linea + 1);
   }
   else fprintf(stderr, "%s\n", linea);     
   va_end(args);
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: tamanyStruct(struct t_infoBison * p1)                                 ##
      ##                   - p1: estructura                                                   ##
      ##                                                                                      ##
      ##                     Retorna int: tamany de l'estructura                              ##
      ##                                                                                      ##
      ########################################################################################## */

int tamanyStruct(struct t_simbol * p1) {
   int tamany = 0;
   int count;
 
   if (p1 -> tipus_var == TIPUS_STRUCT) { 
      for (count = 0; count < p1 -> num_struct_camps; count++) {
         if (p1 -> struct_camps[count].array == TRUE) {
            tamany += ((tamanyTipusVar(p1 -> struct_camps[count].tipus_var)) * (p1 -> struct_camps[count].tam_array));
         }
         else {
            tamany += tamanyTipusVar(p1 -> struct_camps[count].tipus_var);
         }   
      }
   }                                
   return tamany;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: tamanyStructbyInfoBison(struct t_infoBison * p1)                      ##
      ##                   - p1: estructura                                                   ##
      ##                                                                                      ##
      ##                     Retorna int: tamany de l'estructura                              ##
      ##                                                                                      ##
      ########################################################################################## */
      
int tamanyStructbyInfoBison(struct t_infoBison * p1) {
   int tamany = 0;
   int count;
   
   if (sym_lookup(p1 -> valor, &simbol) == SYMTAB_OK) {
      tamany = tamanyStruct(&simbol);
   }                                        
   return tamany; 
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: offsetCampStruct(struct t_simbol * p1, char * nomCamp)                ##
      ##                   - p1: estructura                                                   ##
      ##                   - nomCamp: nom del camp de l'estructura                            ##
      ##                     Retorna int: calcul de l'offset del camp respecte a l'estructura ##
      ##                                                                                      ##
      ########################################################################################## */
      
int offsetCampStruct(struct t_simbol * p1, char * nomCamp) {
   int tamany = 0;
   int count;
   int final = 0;
   
   if (p1 -> tipus_var == TIPUS_STRUCT) { 
      for (count = 0; ((count < p1 -> num_struct_camps) && (!final)); count++) {
         if (strcmp(nomCamp, p1 -> struct_camps[count].valor) != 0) {
            if (p1 -> struct_camps[count].array == TRUE) {
               tamany += ((tamanyTipusVar(p1 -> struct_camps[count].tipus_var)) * (p1 -> struct_camps[count].tam_array));
            }
            else {
               tamany += tamanyTipusVar(p1 -> struct_camps[count].tipus_var);
            }   
         }
         else final = 1;
      }
   }                                
   return tamany;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: campExisteixStruct(char * nomStruct, char * campStruct)               ##
      ##                   - nomStruct: idSimbol de l'estructura                              ##
      ##                   - campStruct: nom del camp de l'estructura                         ##
      ##                                                                                      ##
      ##                     Retorna TRUE: si existeix el camp a l'estructura                 ##
      ##                             FALSE: si no existeix el camp                            ##
      ##                                                                                      ##
      ########################################################################################## */
      
int campExisteixStruct(char * nomStruct, char * campStruct) {
   int resultat = TIPUS_NULL;
   
   if (sym_lookup(nomStruct, &simbol) == SYMTAB_OK) {
      if (simbol.tipus_var == TIPUS_STRUCT) {
         for (count = 0; ((count < simbol.num_struct_camps) && (resultat == TIPUS_NULL)); count++) {
            if (strcmp(simbol.struct_camps[count].valor, campStruct) == 0) {
               resultat = simbol.struct_camps[count].tipus_var;
            } 
         }  
      }
   }
   return resultat;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: campStructEsArray(char * nomStruct, char * campStruct)                ##
      ##                   - nomStruct: idSimbol de l'estructura                              ##
      ##                   - campStruct: nom del camp de l'estructura                         ##
      ##                                                                                      ##
      ##                     Retorna TRUE: si el camp de l'estructura es un array             ##
      ##                             FALSE: si no es un array                                 ##
      ##                                                                                      ##
      ########################################################################################## */
      
int campStructEsArray(char * nomStruct, char * campStruct) {
   int resultat = FALSE;
   
   if (sym_lookup(nomStruct, &simbol) == SYMTAB_OK) {
      if (simbol.tipus_var == TIPUS_STRUCT) {
         for (count = 0; ((count < simbol.num_struct_camps) && (resultat == FALSE)); count++) {
            if (strcmp(simbol.struct_camps[count].valor, campStruct) == 0) {
               resultat = simbol.struct_camps[count].array;
            } 
         }  
      }
   }
   return resultat;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: checkOperadorIncDec(struct t_infoBison p1)                            ##
      ##                   - p1: struct infoBison                                             ##
      ##                                                                                      ##
      ##                     Retorna el tipus de l'increment d'un identificador ex -> i++;    ##
      ##                                                                                      ##
      ########################################################################################## */
      
int checkOperadorIncDec(struct t_infoBison p1) {
   if ((p1.constant != TRUE) && (identificadorDeclarat(p1.valor))) {
      if ((simbol.array == TRUE) && (p1.array != TRUE)) {
         num_errors++; printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, p1.valor);   
      }
      else {
         return comprovacioTipusDades(p1.tipus_var, comprovacioTipusDades(p1.tipus_var, TIPUS_INTEGER, ID_SITUACIO_OPERACIO), ID_SITUACIO_ASSIGNACIO);    
      }      
   }
   return TIPUS_NULL;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: checkOperadors(struct t_infoBison p1, struct t_infoBison p2)          ##
      ##                   - p1: struct infoBison                                             ##
      ##                   - p2: struct infoBison                                             ##
      ##                                                                                      ##
      ##                     Retorna el tipus resultant d'una operació                        ##
      ##                                                                                      ##
      ########################################################################################## */
      
int checkOperadors(struct t_infoBison p1, struct t_infoBison p2) {
      
   if ((p1.constant != TRUE) && (identificadorDeclarat(p1.valor))) {
      if ((simbol.array == TRUE) && (p1.array != TRUE)) {
         num_errors++; printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, p1.valor);   
      }
      else {
         if (p2.constant == TRUE) {
            return comprovacioTipusDades(p1.tipus_var, p2.tipus_var, ID_SITUACIO_OPERACIO);
         }
         else {
            if (identificadorDeclarat(p2.valor)) {
               if ((simbol.array == TRUE) && (p2.array != TRUE)) {
                  num_errors++; printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, p2.valor);   
               }
               else return comprovacioTipusDades(p1.tipus_var, p2.tipus_var, ID_SITUACIO_OPERACIO);
            }
         }
      }
   }
   else {
      if (p1.constant == TRUE) {
         if (p2.constant == TRUE) {
            return comprovacioTipusDades(p1.tipus_var, p2.tipus_var, ID_SITUACIO_OPERACIO);
         }
         else {
            if (identificadorDeclarat(p2.valor)) {
               if ((simbol.array == TRUE) && (p2.array != TRUE)) {
                  num_errors++; printErrorSintactic(TRUE, ERR_UTILITZACIO_ARRAY, p2.valor);   
               }
               else return comprovacioTipusDades(p1.tipus_var, p2.tipus_var, ID_SITUACIO_OPERACIO);
            }
         }   
      } 
   }
      
   return TIPUS_NULL;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: esTipus(char * nom)                                                   ##
      ##                   - nom: identificador del tipus                                     ##
      ##                                                                                      ##
      ##                     Retorna TRUE: si el tipus del simbol es un TIPUS_BASIC           ##
      ##                             FALSE: en cas contrari                                   ##
      ##                                                                                      ##
      ########################################################################################## */
      
int esTipus(char * nom) {
   if (sym_lookup(nom, &simbol_tmp) == SYMTAB_OK) {
      if (simbol_tmp.tipus == TIPUS_BASIC) {
         return TRUE;
      }
   }
   return FALSE;
}


   /* ########################################################################################## 
      ##                                                                                      ##
      ##    [ FUNCIO ]: tipusDadesID(int idTipus, int espais)                                 ##
      ##                   - idTipus: identificador del tipus de dades                        ##
      ##                   - espais: es mostra la informació amb un format o no               ##
      ##                                                                                      ##
      ##                     Retorna el string del tipus                                      ##
      ##                                                                                      ##
      ########################################################################################## */
      
char * tipusDadesID(int idTipus, int espais) {
   char * tdades = (char *) malloc(10);
   
   strcpy(tdades, "");
   
   if (espais) {
      switch (idTipus) {
         case -1: strcpy(tdades, "NULL     "); break;
         case 0: strcpy(tdades, "VOID     "); break;
         case 1: strcpy(tdades, "CHAR     "); break;
         case 2: strcpy(tdades, "SHORT    "); break;
         case 3: strcpy(tdades, "INT      "); break;
         case 4: strcpy(tdades, "LONG     "); break;
         case 5: strcpy(tdades, "FLOAT    "); break;
         case 6: strcpy(tdades, "DOUBLE   "); break;
         case 7: strcpy(tdades, "STRING   "); break;
         case 8: strcpy(tdades, "STRUCT   "); break;
      }
   }
   else {
      switch (idTipus) {
         case -1: strcpy(tdades, "NULL"); break;
         case 0: strcpy(tdades, "VOID"); break;
         case 1: strcpy(tdades, "CHAR"); break;
         case 2: strcpy(tdades, "SHORT"); break;
         case 3: strcpy(tdades, "INT"); break;
         case 4: strcpy(tdades, "LONG"); break;
         case 5: strcpy(tdades, "FLOAT"); break;
         case 6: strcpy(tdades, "DOUBLE"); break;
         case 7: strcpy(tdades, "STRING"); break;
         case 8: strcpy(tdades, "STRUCT"); break;
      }   
   }
   return tdades;
}
