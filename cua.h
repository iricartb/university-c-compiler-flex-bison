#ifndef __CUA_H__
#define __CUA_H__

   struct Tipus_Node_Cua
   {
      void *node;
      struct Tipus_Node_Cua *anterior;
   };
   typedef struct Tipus_Node_Cua Node_Cua;

   struct Tipus_Cua
   {
      Node_Cua *primer;
      Node_Cua *ultim;
      Node_Cua *pdi;
   };       
   typedef struct Tipus_Cua Cua;
   
   Cua *crear_cua(void);
   unsigned int cua_buida(Cua *c);
   void encuar(Cua *c, void *valors);
   void desencuar(Cua *c);
   void *primer(Cua *c);
   void reiniciar_PDI(Cua *c);
   void *obtenir_element_PDI(Cua *c);
   int seguent_PDI(Cua *c);
   Cua *fusionar_cues(Cua *cua1, Cua *cua2);
   void *obtenir_element_pos(Cua *cua, int posicio);

#endif

