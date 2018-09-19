#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "main.h"

int main(int argc, char ** argv) {
   if (argc == 3) {
      char * fRA, * fC3A;
      if (init_analisi_lexic_I(argv[1]) == EXIT_SUCCESS) {
         fRA = (char *) malloc(strlen(argv[2]) + 4);
         fC3A = (char *) malloc(strlen(argv[2]) + 5); 
         sprintf(fRA, "%s.ra", argv[2]);
         sprintf(fC3A, "%s.c3a", argv[2]);                               
         if (init_analisi_sintactic_O(argv[2], fRA, fC3A) == EXIT_SUCCESS) {
            gestioParaulesReservades();       
            analisi_semantic();
         
            end_analisi_lexic_I(); 
            end_analisi_sintactic_O();
         }
         else {
            printf("\n\n###########################################################\n");
            printf("###\t\t\t\t\t\t\t###\n");
            printf("###\t[ ERR ] El fitxers de sortida %s %s %s no s'han creat\t###\n", argv[2], fRA, fC3A);
            printf("###\t\t\t\t\t\t\t###\n");      
            printf("###########################################################\n\n");       
         }
      }
      else {
         printf("\n\n###########################################################\n");
         printf("###\t\t\t\t\t\t\t###\n");
         printf("###\t[ ERR ] El fitxer d'entrada %s no existeix\t###\n", argv[1]);
         printf("###\t\t\t\t\t\t\t###\n");      
         printf("###########################################################\n\n");       
      }
   }         
   else {
      printf("\n\n###########################################################################\n");
      printf("###\t\t\t\t\t\t\t\t\t###\n");
      printf("###\t[ USE ] %s [ F_IN ] [ F_OUT ]      \t\t\t###\n", argv[0]);
      printf("###\t[ EX  ] %s input.txt output.txt\t\t\t###\n", argv[0]);
      printf("###\t\t\t\t\t\t\t\t\t###\n");      
      printf("###########################################################################\n\n");
   }
}     
