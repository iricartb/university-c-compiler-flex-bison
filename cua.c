#define MODUL_CUA
#include <stdlib.h>
#include <stdio.h>
#include "cua.h"
         
Cua *crear_cua(void)
{
   Cua *nova;

   nova =(Cua *)malloc(sizeof(Cua));
   nova -> primer = NULL;
   nova -> ultim = NULL;
   nova -> pdi = NULL;   
   return nova;
}

unsigned int cua_buida(Cua *c)
{
   if(c -> primer == NULL) 
      return 1;
   else 
      return 0;
}

void encuar(Cua *c, void *valors)
{
   Node_Cua *nou_node;
   
   nou_node = (Node_Cua *)malloc(sizeof(Node_Cua));
   nou_node -> node = valors;
   nou_node -> anterior = NULL;
   if (cua_buida(c))
   {
      c -> primer = nou_node;
      c -> ultim = nou_node;
      c -> pdi = nou_node;
   }
   else
   {
      c -> ultim -> anterior = nou_node;
      c -> ultim = nou_node;
   } 
}

void desencuar(Cua *c)
{
   Node_Cua *aux;
   
   if (!cua_buida(c))
   {  
      if (c -> primer -> anterior == NULL)
      {
         c -> primer = NULL; 
         c -> ultim = NULL;
         c -> pdi = NULL;
      }  
      else
      {
         aux = c -> primer;
         c -> primer = c -> primer -> anterior;
         free(aux);
      }
   }
}

void *primer(Cua *c)
{
   if (c -> primer != NULL)
      return c -> primer -> node;
   else
      return NULL;
}

void reiniciar_PDI(Cua *c)
{
   c -> pdi = c -> primer;
}

void *obtenir_element_PDI(Cua *c)
{
   if(c != NULL)
   {
      if (c -> pdi != NULL)
         return c -> pdi -> node;
      else
         return NULL;
   }
   else
      return NULL;
}

int seguent_PDI(Cua *c)
{
   if(c != NULL)
   {
   	  if (c -> pdi!= NULL)
      {
         c -> pdi = (c -> pdi) -> anterior;
         return 1;
      }
	else
	{
		return 0;
	}
   }
   else
   {
      return 0;   
   }
}

void *obtenir_element_pos(Cua *cua, int posicio)
{
	int posicio_actual = 1; 
	
	reiniciar_PDI(cua);
	void *element = obtenir_element_PDI(cua);
	while (element != NULL) {
		if (posicio_actual == posicio) {
			return element;
		}
		posicio_actual++;
		seguent_PDI(cua);
		element = obtenir_element_PDI(cua);
	}
	
	return NULL;
}

Cua *extreure_element_pos(Cua *cua, int posicio)
{
	Cua *nova_cua = (Cua*)crear_cua();
	int posicio_actual = 1; 
	
	reiniciar_PDI(cua);
	void *element = obtenir_element_PDI(cua);
	while (element != NULL) {
		if (posicio_actual != posicio) {
			encuar(nova_cua, element);
		}
		posicio_actual++;
		seguent_PDI(cua);
		element = obtenir_element_PDI(cua);
	}
	
	return nova_cua;
}

Cua *fusionar_cues(Cua *cua1, Cua *cua2)
{
	Cua *cua_nova = (Cua*)crear_cua();
	
	if (cua1 != NULL) {
		reiniciar_PDI(cua1);
		void *element = obtenir_element_PDI(cua1);
		while (element != NULL) {
			encuar(cua_nova, element);
			seguent_PDI(cua1);
			element = obtenir_element_PDI(cua1);
		}
	}
	
	if (cua2 != NULL) {
		reiniciar_PDI(cua2);
		void *element = obtenir_element_PDI(cua2);
		while (element != NULL) {
			encuar(cua_nova, element);
			seguent_PDI(cua2);
			element = obtenir_element_PDI(cua2);
		}
	}
	
	return cua_nova;
}


