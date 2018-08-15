#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
typedef struct nod
{
    char *data;
    struct nod *next;
}nod;
nod *prim=NULL;  //primul element din lista
int nrelem;
nod *creare(char *info) //creearea unui nod care va contine cuvinte(nodul putand contine si numere)
{
    nod *nou;
     nou=(nod *)malloc(sizeof(nod));//atribuim memorie nodului nou
     nou->data=(char *)malloc((strlen(info)+1)*sizeof(char));
     strcpy(nou->data,info);       //atribuim informatiei stocate in nod ceea ce vrem
     nou->next=NULL;
     return nou;
}
nod *adaugin(nod *nou) //adaugare la inceputul listei
{
    nou->next=prim;             //urmatorul noului nod pointeaza primul element,astfel devenind el primul nod
    prim=nou;                  //dupa care ii atribuim "titlul" primului
    nrelem++;                  //incrementam numarul de elemente
}
nod *adaugsf(nod *nou)         //adaugare la sfarsitul listei
{
       if(prim!=NULL)
       {
            nod *p;
            p=prim;
            while(p->next!=NULL)
            p=p->next;            //parcurgem lista pana cand urmatorul element este NULL
            p->next=nou;          //acolo fiind locul ideal de a plasa elementul
            nrelem++;             //incrementam numarul de elemente
       }
       else
       {
           adaugin(nou);
       }
}
nod *adaug_nr_ord(nod *nou,int nr_ord)   //adaugaare la un anumit numar de ordine
{
    int nr=1;
    nod *p;
    p=prim;
    if(nr_ord<=nrelem)        //daca nu se afla dupa sarsitul listei
    {
        while(nr+1<nr_ord)   //cat timp inca nu am ajuns
        {
            p=p->next;
            nr++;
        }
    nou->next=p->next;  //urmatorul nodului nou este urmatorul nodului p
    p->next=nou;        //urmatorul nodului p este nodul nou
    }
    else            //daca se afla dupa sfarsitul listei, il adaugam la sfarsit
    {
           adaugsf(nou);
           nrelem--; //in adaugsf(nou) incrementeaza nrelem,asa ca aici il scadem
    }
    nrelem++;          //incrementam numarul de elemente
}
nod *stergeprim(nod *p)  //p=prim
{
    prim=p->next;        //prim devine urmatorul
    free(p);             //eliberam adresa fostului prim
    nrelem--;
}
nod *stergesf(nod *p)   //p=prim
{
    if(nrelem!=0)
    {
        while(p->next->next!=NULL)    //cat timp urmatorul nu este sfarsitul listei
        {
            p=p->next;                //parcurgem lista
        }
        free(p->next);                //eliberam sfarsitul listei
        p->next=NULL;                 //declaram elementul de dinainte ca sfarsit
    }
    nrelem--;
}
nod *sterg_nr_ord(nod *p,int nr_ord)
{
     if(nr_ord==1)
     stergeprim(p);
     else if(nr_ord==nrelem)
     stergesf(p);
     else if(nr_ord>nrelem)
     printf("nu exista");
     else
     {
         int nr=1;
        while(nr+1<nr_ord)
        {
            p=p->next;
            nr++;
        }
        nod *aux;
        aux=p->next;
        p->next=aux->next;
        free(aux);nrelem--;
     }
}
nod *sterg_info(char *info,nod *p)
{
     while(p->next->data!=info&&p->next!=NULL)
     p=p->next;
     if(p->next->data==info)
     {
        nod *aux;
        aux=p->next;
        p->next=aux->next;
        free(aux);nrelem--;
     }
     else
     printf("nu exista\n");
}
nod *caut(char *info,nod *p)
{
      int nr=1,nr_ord=0;
          while(p->next!=NULL)
          {
              if(p->data==info)
              {
                  nr_ord=nr;
                  break;
              }
              p=p->next;
              nr++;
          }
      if(nr_ord==0)
      printf("nu exista\n");
      else
      printf("%d\n",nr_ord);
}
nod *afisnr(int nr,nod *p)
{
        if(nr>nrelem)
        printf("nu exista\n");
        else
        {
            int nr_ord=1;
            while(nr_ord!=nr)
            {
                nr_ord++;
                p=p->next;
            }
            printf("%s\n",p->data);
        }
}
nod list(nod *p)
{
    int nr=1;
   while(p!=NULL)
   {
       printf("%d %s\n",nr,p->data);
       nr++;
       p=p->next;
   }
}
int main()
{
    char c,*ch;
    int val, info;
     printf("a value char:adaugare numar pe pozitia value(daca value=0 se v-a adauga la sfarsit,daca value=-1 se v-a adauga la inceput,daca nici una, se va adauga pe pozitia value,char e informatia)\n");
     printf("s value char:functioneaza ca si a, doar ca cu s se sterge,daca value e -2, atunci sterge un sir de caractere\n");
     printf("l: listeaza lista\n");
     printf("c val info: daca val=0, atunci v-a afisa elementul de pe pozitia info, daca val=1, atunci v-a cauta elementul cu data=info\n");
     printf("t:sfarsit program\n");
    do
    {
              scanf("%c",&c);
              if(c=='a')
              {
                  scanf("%d %s",&val,ch);
                  if(val==0)
                  adaugsf(creare(ch));
                  else if(val==-1)
                  adaugin(creare(ch));
                  else
                  adaug_nr_ord(creare(ch),val);
              }
              else if(c=='s')
              {
                  scanf("%d",&val);
                  if(val==0)
                  stergesf(prim);
                  else if(val==-1)
                  stergeprim(prim);
                  else if(val==-2)
                  {
                    scanf("%s",&ch);
                    sterg_info(ch,prim);
                  }
                  else
                  sterg_nr_ord(prim,val);
              }
              else if(c=='l')
              {
                  list(prim);
              }
              else if(c=='c')
              {
                  scanf("%d",&val);
                  if(val==0)
                  {
                    scanf("%d",&info);
                    afisnr(info,prim);
                  }
                  else
                  {
                      scanf("%s",&ch);
                      caut(ch,prim);
                  }
              }
    }
    while(c!='t');
    return 0;
}
//sterg info si caut de lucru
