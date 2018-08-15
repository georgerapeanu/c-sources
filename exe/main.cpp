#include <cstdio>
#include "set_type.h"
#include "coada.h"
#include "stiva.h"
using namespace std;
int main()
{
    settype("int");
    coada *prim=NULL,*ultim=NULL;
    prim=adaugare_coada((void *)1,prim,ultim);
    ultim=prim;
    prim=adaugare_coada((void *)2,prim,ultim);
    prim=adaugare_coada((void *)3,prim,ultim);
    ultim=stergere_coada(prim,ultim);
    if(ultim==NULL)
    prim=NULL;
    stiva *varf=NULL;
    varf=adaugare_stiva((void *)1,varf);
    varf=adaugare_stiva((void *)2,varf);
    varf=adaugare_stiva((void *)3,varf);
    varf=stergere_stiva(varf);
    while(varf!=NULL)
    {
        printf("%d ",varf->data);
        varf=varf->prev;
    }
    return 0;
}
