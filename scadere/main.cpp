#include <cstdio>
#include <cstring>
#include <cctype>
#include <stack>
using namespace std;
FILE *f=fopen("scadere.in","r");
FILE *g=fopen("scadere.out","w");
stack <long long> st,sens;
long long tip,N,X[5005],i,ind,val,tp,rez,nrp;
char V[40005];
int main()
{
    fscanf(f,"%lld\n%lld",&tip,&N);
    for(i=1;i<=N;i++)
        fscanf(f,"%lld",&X[i]);
    if(tip==1)
    {
        rez=X[1]-X[2];
        for(i=3;i<=N;i++)
        {
            if(X[i]<0)
                rez-=X[i];
            else
                rez+=X[i];
        }
        fprintf(g,"%lld\n",rez);
        fprintf(g,"x1-");
        for(i=3;i<=N;i++)
        {
            if(X[i]>=0)
               {if(nrp%2==0)
                {fprintf(g,"(");nrp++;}
               }
            else
                if(nrp%2==1)
                    {fprintf(g,"(");nrp++;}
                fprintf(g,"x%lld-",i-1);
        }
        fprintf(g,"x%lld",N);
        for(i=1;i<=nrp;i++)
            fprintf(g,")");
   }
    else
    {
        fscanf(f,"\n");
        fgets(V,40000,f);
        st.push(0);
        st.push(0);
        N=strlen(V);
        i=0;sens.push(1);
        sens.push(1);
        while(i<N-1)
        {
            if(V[i]=='-')
                sens.top()=-1;
            else if(V[i]=='x')
                ;
            else if(V[i]=='(')
                    {st.push(0);sens.push(1);}
            else if(V[i]==')')
            {
                val=st.top();
                st.pop();
                sens.pop();
                val=val*sens.top();
                val+=st.top();
                st.pop();
                st.push(val);
            }
            else
            {
                val=0;
                while(isdigit(V[i]))
                {
                    val=val*10+V[i]-'0';i++;
                }
                i--;
                val=st.top()+X[val]*sens.top();
                st.pop();
                st.push(val);
            }
            tp=st.top();
            i++;
        }
        fprintf(g,"%lld",st.top());
    }
    fclose(f);
    fclose(g);
    return 0;
}

