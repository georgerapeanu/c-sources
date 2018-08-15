#include <cstdio>
#include <algorithm>
#include <deque>
using namespace std;
FILE *f=fopen("calandrinon.in","r");
FILE *g=fopen("calandrinon.out","w");
int N,i,frecv[30],nr,f2[30];
char c[1000005],rez[30];
bool ap[30],ok;
deque<char> st;
int main()
{
    fscanf(f,"%d\n",&N);
    fgets(c,N+1,f);
    for(i=0;i<N;i++)
        {frecv[c[i]-'a']++;}
    for(i=0;i<N;i++)
    {
        if(ap[c[i]-'a']==1)
        {
            ok=1;
            for(deque<char>::iterator it=st.begin();it!=st.end()&&ok==1;it++)
                if(frecv[*it]<=1)
                    ok=0;
            if(st.front()>c[i]&&ok==1)
            {
                while(!st.empty())
                {
                    ap[st.front()]=0;
                    st.pop_front();
                }
                st.push_back(c[i]);
            }
            else if(st.front()==c[i])
            {
                deque<char>::iterator it=st.begin();
                ok=1;
                nr=i+1
                while(it!=st.end()&&nr<N)
                {
                    do
                    {
                        f2[c[nr]-'a']++;
                        nr++;
                    }
                    while(f2[c[nr-1]-'a']!=frecv[c[nr-1]-'a']&&nr<N);
                    nr--;
                    if(c[nr]<)
                }
            }
        }
        else
        {
            while(!st.empty()&&frecv[st.back()-'a']>1&&c[i]<st.back()&&ap[c[i]-'a']==0)
            {
                frecv[st.back()-'a']--;
                ap[st.back()-'a']=0;
                st.pop_back();
            }
            if(ap[c[i]-'a']==0)
           {
            st.push_back(c[i]);
            ap[c[i]-'a']=1;
            }
            else
                frecv[st.back()-'a']--;
        }
    }
     while(!st.empty())
     {
         rez[nr++]=st.back();
         st.pop_back();
     }
     nr--;
     for(i=0;i<=nr/2;i++)
        swap(rez[i],rez[nr-i]);

    fputs(rez,g);
    fclose(f);
    fclose(g);
    return 0;
}
