#include <cstdio>
#define tp long long
using namespace std;
FILE *f=fopen("tabela.in","r");
FILE *g=fopen("tabela.out","w");
tp L,C;
tp rez(tp L,tp C,int l)
{
    if(l<0)return 0;
    if(L<(1LL<<l)&&C<(1LL<<l)) return rez(L,C,l-1);
    else if(L<(1LL<<l)&&C>=(1LL<<l))return rez(L,C-(1LL<<l),l-1)+(1LL<<l);
    else if(C<(1LL<<l)&&L>=(1LL<<l))return rez(L-(1LL<<l),C,l-1)+(1LL<<l);
    else return(rez(L-(1LL<<l),C-(1LL<<l),l-1));
}
int main()
{
    fscanf(f,"%lld%lld",&L,&C);
    fprintf(g,"%lld",rez(L-1,C-1,31));
    fclose(f);
    fclose(g);
    return 0;
}
