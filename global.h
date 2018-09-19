#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define TRUE 1
#define FALSE 0
#define Boolean unsigned char

#define NOM_LEXIC_TAM                          100
#define LONG_MAX                               2147483647

#define ID_SITUACIO_ASSIGNACIO                 0
#define ID_SITUACIO_FUNCIO                     1
#define ID_SITUACIO_OPERACIO                   2

#define ERR_VALOR_INICIAL_NO_CONST             "el valor inicial no es constant"
#define ERR_NO_DECLARADA_FUNC_VAR              "la %s -> [%s] no ha sigut declarada anteriorment"
#define ERR_INTRODUCCIO_TAULA_SIMBOL_FUNC_VAR  "la %s -> [%s] no s'ha pogut introduir a la taula de simbols"
#define ERR_INTRODUCCIO_TAULA_SIMBOL_TIPUS     "el tipus -> [%s] no s'ha pogut introduir a la taula de simbols"
#define ERR_REDECLARACIO_FUNC_VAR              "la %s -> [%s] ha sigut declarada anteriorment"
#define ERR_REDECLARACIO_TIPUS                 "el tipus -> [%s] ha sigut declarat anteriorment"
#define ERR_DIVISIO_PER_ZERO                   "divisio per zero"
#define ERR_STRING_STRING_OP                   "la %s entre strings no esta permesa" 
#define ERR_ASIGNACIO_CONSTANT                 "assignacio de valor a una constant -> [%s]"
#define ERR_ARRAY_TAMANY_INCORRECTE            "el tamany -> [%s] introduit a l'array -> [%s] es incorrecte"
#define ERR_ASSIGNACIO_STRING_ARRAY            "el tamany del string -> [%lu] string supera al tamany del array -> [%lu]"
#define ERR_CONSTANT_NO_VARIABLE               "no es pot utilitzar una constant -> [%s] en aquesta expressio (%s)"  
#define ERR_VARIABLE_NO_ARRAY                  "la variable -> [%s] no ha sigut declarat com un array"
#define ERR_INDEX_ARRAY_NO_INT                 "la indexacio del array -> [%s] ha de ser de tipus int, short, char o long"
#define ERR_INDEX_ARRAY_FORA_RANG              "la indexacio del array -> [%s] supera el rang declarat"
#define ERR_UTILITZACIO_ARRAY                  "la variable -> [%s] es un array pero no s'ha accedit com a tal"
#define ERR_VARIABLE_NO_FUNCIO                 "el identificador -> [%s] no ha sigut declarat com una funcio"
#define ERR_FUNCIO_PARAMS_INSUFICIENTS         "falten parametres per realitzar la crida de la funcio -> [%s]"
#define ERR_FUNCIO_PARAMS_EXCESIUS             "masses parametres per realitzar la crida de la funcio -> [%s]"
#define ERR_FUNCIO_NUM_PARAMS_DIFERENTS        "el nombre de parametres per realitzar la crida a la funcio -> [%s] es diferent"
#define ERR_DEC_O_INC_CONSTANT                 "s'ha intentat %s una constant"
#define ERR_FUNCIO_PARAM_ARRAY_METODE_ACCESS   "el parametre %d de la funcio -> [%s] es un array i la funcio acepta un array, pero no s'ha accedit com a tal"
#define ERR_FUNCIO_PARAM_ES_ARRAY              "el parametre %d de la funcio -> [%s] ha de ser un array" 
#define ERR_FUNCIO_PARAM_NO_ES_ARRAY           "el parametre %d de la funcio -> [%s] no ha de ser un array"
#define ERR_FUNCIO_PARAM_NO_DECLARAT           "el parametre %d de la funcio -> [%s] no ha sigut declarat anteriorment"
#define ERR_PARAM_FUNCIO_DEFINICIO             "el parametre %d de la funcio -> [%s] ha de ser de tipus %s, el tipus introduit ha sigut %s"
#define ERR_PARAMETRES_LOCALS_FUNCIO           "no s'ha pogut introduir el parametre -> [%s] com a variable local de la funcio"
#define ERR_VALOR_RETORN_FUNCIO                "el valor de retorn de la funcio -> [%s] no concideix amb la declaracio"
#define ERR_PARAMETRE_FUNCIO_VOID              "no es pot declarar un parametre de la funcio com a tipus void"
#define ERR_CRIDA_FUNCIO                       "no s'ha pogut efectuar la crida a la funcio -> [%s]"
#define ERR_DEF_FUNCIO_NUM_PARAMS_DIFERENTS    "el nombre de parametres per realitzar la definicio de la funcio -> [%s] es diferent"
#define ERR_FUNCIO_PARAMS_NOT_NULL             "el parametre %d de la funcio -> [%s] ha de ser de tipus NULL (SENSE TIPUS)" 
#define ERR_STRUCT_CONSTANT                    "no es pot accedir com una estructura en una constant"
#define ERR_STRUCT_TIPUS_DIFERENT              "no es pot accedir a una estructura quan la variable -> [%s] no es de tipus estructura"
#define ERR_CAMP_NO_EXISTEIX_STRUCT            "s'ha intentat accedir a un camp -> [%s] de l'estructura -> [%s] inexistent" 
#define ERR_OPERACIO_ASSIG_ENTRE_STRUCTS       "No es permet realitzar l'%s si un dels elements es una estructura"
#define ERR_CRIDA_FUNCIO_STRUCTS               "No es pot realitzar cap casting si un dels elements es una estructura"
#define ERR_TYPE_TO_STRING                     "%s %s - string"
#define ERR_STRING                             "%s string - %s"
#define ERR_FOR_DECLARACIO_VARIABLES           "s'ha utilitzat la declaracio inicial del cicle for fora del mode C99" 

#define WARNING_CASTING                        "casting en %s (%s >> %s)"
#define WARNING_PRECISIO                       "perdua de precisio en %s (%s >> %s)"
#define WARNING_ARRAY_TAMANY_MAXIM             "la declaracio del array -> [%s] esta fora de rang, es restableix el seu tamany al tamany maxim -> [%lu]"
#define WARNING_NOM_PARAMETRE_FUNCIO_NO_DEC    "el nom del parametre %d de la funcio -> [%s] no s'ha declarat"  

#define OK_INTRODUCCIO_TAULA_SIMBOL_FUN_VAR    "la %s -> [%s] s'ha insertat correctament a la taula de simbols"
#define OK_INTRODUCCIO_TAULA_SIMBOL_TIPUS      "el tipus -> [%s] s'ha insertat correctament a la taula de simbols"
#define OK_CONSULTA_TAULA_SIMBOL_FUN_VAR       "la %s -> [%s] s'ha trobat en la taula de simbols"
#define OK_CRIDA_FUNCIO                        "s'ha efectuat la crida a la funcio -> [%s]"
#define OK_DEFINICIO_FUNCIO                    "la funcio -> [%s] s'ha definit correctament"
#define OK_PARAMETRES_LOCALS_FUNCIO            "s'ha introduit el parametre -> [%s] com a variable local de la funcio"
#define OK_INDEX_ARRAY                         "s'ha pogut accedir correctament a l'array -> [%s], l'index [%s] esta dintre del rang declarat"
#define OK_CAMP_EXISTEIX_STRUCT                "s'ha accedit al camp -> [%s] de l'estructura -> [%s]" 
#define OK_INCREMENT_AMBIT                     "s'ha introduit el nou ambit amb identificador -> [%d]"
#define OK_DECREMENT_AMBIT                     "s'ha eliminat l'ambit amb identificador -> [%d]"

typedef enum {
    TIPUS_NULL = -1,
    TIPUS_VOID = 0,
    TIPUS_CHARACTER = 1,
    TIPUS_SHORT = 2,
	TIPUS_INTEGER = 3,
	TIPUS_LONG = 4,
	TIPUS_FLOAT = 5,
	TIPUS_DOUBLE = 6,
	TIPUS_STRING = 7,
	TIPUS_STRUCT = 8,
} Tipus_Dades;

typedef enum {
    TIPUS_BASIC = 0,
	PARAULA_RESERVADA = 1,
	OPERADOR = 2,
	VARIABLE = 3,
    FUNCIO = 4, 
} Tipus_Simbol; 

#endif
