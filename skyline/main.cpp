#include <cstdio>
#include <stack>
#define nmax 40500
using namespace std;
FILE *f=fopen("skyline.in","r"),*g=fopen("skyline.out","w");
stack <long long> st,dr;
long long left[nmax],right[nmax],l[nmax],h[nmax],i,n;
unsigned long long rez,arie;
int main()
{
    //l[i]=l[1]+l[2]+l[3]+....+l[i-1]+l[i]
    //idea programului este ca se folosesc 2 stive si 2 vectori
    //se observa ca tot timpul inaltimea dreptunghiului(cum pe exemplu e 8)
    //va fi una dintre elementele vectorului h
    //se fixeasa pe rand fiecare element ca inaltime h
    //left[i]= pentru dreptunghiul care o sa contina cladirea i, cat de in stanga se poate duce
    //right[i]= pentru dreptunghiul care o sa contina cladirea i, cat de in dreapta se poate duce
    //stiva st va avea la fiecare pas prima cladire dinaintea cladirii i care nu va fi in dreptunghiul cu inaltime h[i]
    //determinam asta folosind faptul ca daca in st.top() este un element cu h mai mare
    // il eliminam pentru ca v-a participa in crearea dreptunghiului
    //la final dupa ce terminam de prelucrat stiva la pasul i, left[i]=st.top()
    //analog la stiva dr, doar ca la fiecare pas stiva va reprezenta ultima cladire care va fi in dreptunghiul
    //care contine cladirea i
    //in final, vom lua i de la 1 la n, si rez=max(rez,(l[right[i]]-l[left[i]])*h[i])
    fscanf(f,"%lld",&n);
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%lld%lld",&h[i],&l[i]);
        l[i]+=l[i-1];
    }
    st.push(0);
    dr.push(n+1);
    h[n+1]=h[0]=-1;
    for(i=1;i<=n;i++)
    {
        while(h[st.top()]>=h[i])
            st.pop();
        while(h[dr.top()]>=h[n-i+1])
            dr.pop();
        left[i]=st.top();
        right[n-i+1]=dr.top()-1;
        st.push(i);
        dr.push(n-i+1);
    }
    for(i=1;i<=n;i++)
    {
        arie=(l[right[i]]-l[left[i]])*h[i];
        if(rez<arie)
        rez=arie;
    }
    fprintf(g,"%llu",rez);
    fclose(f);
    fclose(g);
    return 0;
}
