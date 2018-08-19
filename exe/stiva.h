#ifndef STIVA
#define STIVA
typedef struct stiva
{
  void *data;
  struct stiva *prev;
}stiva;
stiva *creare_stiva(void *info)
{
    stiva *nou;
    nou=(stiva *)malloc(sizeof(stiva));
    nou->data=(char *)malloc(type*50);
    if(type==1)
    strcpy((char *)nou->data,(char *)info);
    else
    nou->data=info;
    nou->prev=NULL;
}
stiva *adaugare_stiva(void *info,stiva *varf)
{
    stiva *nou;
    nou=creare_stiva(info);
    if(varf==NULL)
    return nou;
    else
    {
        nou->prev=varf;
        varf=nou;
        return varf;
    }
}
stiva *stergere_stiva(stiva *varf)
{
    if(varf==NULL)
    return varf;
    else
    {
        stiva *temp;
        temp=varf->prev;
        free(varf);
        varf=temp;
        return varf;
    }
}
#endif // STIVA
