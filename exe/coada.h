#ifndef COADA
#define COADA
typedef struct coada
{
   void *data;
   struct coada *next;
   struct coada *prev;
}coada;
coada *creeare_coada(void *info)
{
    coada *nou;
    nou=(coada *)malloc(sizeof(coada)*50);
    nou->data=malloc(50*type);
    if(type==1)
    strcpy((char *)nou->data,(char *)info);
    else
    nou->data=info;
    nou->next=NULL;
    nou->prev=NULL;
    return nou;
}
coada *adaugare_coada(void *info,coada *primc,coada *ultimc)
{
     coada *temp=NULL;
     temp=creeare_coada(info);
     if(ultimc==NULL&&primc==NULL)
     {
         primc=ultimc=temp;
     }
     else
     {
        primc->prev=temp;
        temp->next=primc;
        temp->prev=NULL;
        primc=temp;
     }
     return primc;
}
coada *stergere_coada(coada *primc,coada *ultimc)
{
    coada *temp;
    temp=ultimc;
    ultimc=temp->prev;
    free(temp);
    ultimc->next=NULL;
    if(ultimc==NULL)
    primc=NULL;
    return ultimc;
}
#endif // COADA
//dupa prima functie adaugare_coada trebuie sa faci ultim=prim(sau dupa oricare functie adaugare_Coada in care precedent ambele erau null)
//dupa fiecare functie stergere_coada trebuie sa faci if(ultim==NULL) prim=NULL
