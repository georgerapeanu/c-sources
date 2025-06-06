#include <cstdio>
#include <cstring>
#include <map>
#include <stack>
using namespace std;
FILE *f=fopen("excel.in","r");
FILE *g=fopen("excel.out","w");
char C[35];
long long val;
int i,cnt;
long long l,c;
map <long long,long long> M;
stack <int> st;
long long put26[20];
int codificare()
{
    int j=6,k,cnt=0;
    short rez[30];
    memset(rez,0,sizeof(rez));
    while(put26[j]>c)
        j--;
    k=j;
    while(j>=0)
    {
        rez[j]=c/put26[j];
        c%=put26[j];
        if(rez[j]==0)
        {
            int l=j;
            while(rez[l]==0&&rez[l+1]>0)
            {
                rez[l]+=26;
                rez[l+1]-=1;
                l++;
            }
        }
        j--;
    }
    while(rez[k]==0)
        k--;
    while(k>=0)
    {
        C[cnt++]=rez[k]+'A'-1;
        k--;
    }
    C[cnt]='\0';
    return cnt;
}
int main()
{
    put26[0]=1;
    for(i=1;put26[i-1]<=30000000;i++)
        put26[i]=put26[i-1]*26;
    while(fscanf(f,"%s %lld\n",C,&val)!=EOF)
    {
        i=1;
        l=0;
        c=0;
        while('0'<=C[i]&&C[i]<='9')
        {
            l=l*10+C[i]-'0';
            i++;
        }
        i++;
        while('0'<=C[i]&&C[i]<='9')
        {
            c=c*10+C[i]-'0';
            i++;
        }
        M[l]+=val;
        cnt=codificare();
        while(l)
        {
            st.push(l%10);
            l/=10;
        }
        while(!st.empty())
        {
            C[cnt++]=st.top()+'0';
            st.pop();
        }
        C[cnt]='\0';
        fputs(C,g);
        fputc('\n',g);
    }
    map<long long,long long> ::iterator fit;
    M[0]=1;
    for(map<long long,long long> ::iterator it=M.begin();it!=M.end();it++)
    {
        if(it!=M.begin())
            {
                if((*it).first-(*fit).first-1>0)
                    fprintf(g,"%lld 0 %lld ",(*it).first-(*fit).first-1,(*it).second);
                else if((*it).second==0)
                    {M.erase(it);it--;}
                else
                    fprintf(g,"%lld ",(*it).second);
            }
        fit=it;
    }
    fclose(f);
    fclose(g);
    return 0;
}
