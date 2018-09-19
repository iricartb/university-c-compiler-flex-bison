
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID_AUTO = 258,
     ID_BREAK = 259,
     ID_CASE = 260,
     ID_CHAR = 261,
     ID_CONST = 262,
     ID_CONTINUE = 263,
     ID_DEFAULT = 264,
     ID_DO = 265,
     ID_DOUBLE = 266,
     ID_ELSE = 267,
     ID_ENUM = 268,
     ID_EXTERN = 269,
     ID_FLOAT = 270,
     ID_FOR = 271,
     ID_GOTO = 272,
     ID_IF = 273,
     ID_INT = 274,
     ID_LONG = 275,
     ID_REGISTER = 276,
     ID_RETURN = 277,
     ID_SHORT = 278,
     ID_SIGNED = 279,
     ID_SIZEOF = 280,
     ID_STATIC = 281,
     ID_STRUCT = 282,
     ID_SWITCH = 283,
     ID_TYPEDEF = 284,
     ID_UNION = 285,
     ID_UNSIGNED = 286,
     ID_VOID = 287,
     ID_VOLATILE = 288,
     ID_WHILE = 289,
     ID_INC_OP = 290,
     ID_DEC_OP = 291,
     ID_LE_OP = 292,
     ID_GE_OP = 293,
     ID_EQ_OP = 294,
     ID_NE_OP = 295,
     ID_AND_OP = 296,
     ID_OR_OP = 297,
     ID_MUL_ASSIG = 298,
     ID_DIV_ASSIG = 299,
     ID_MOD_ASSIG = 300,
     ID_ADD_ASSIG = 301,
     ID_SUB_ASSIG = 302,
     ID_IDENTIFICADOR = 303,
     ID_TYPEDEF_IDENTIFIER = 304,
     ID_CHARACTER_CONSTANT = 305,
     ID_INTEGER_CONSTANT = 306,
     ID_FLOATING_CONSTANT = 307,
     ID_STRING = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 146 "sintactic.y"
 	   
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



/* Line 1676 of yacc.c  */
#line 132 "sintactic.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


