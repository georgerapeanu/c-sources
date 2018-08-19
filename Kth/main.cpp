#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
FILE *f=fopen("kth.in","r");
FILE *g=fopen("kth.out","w");
struct data
{
    int fst,lst,val;
    bool operator <(const data &other)const
    {
        return fst<other.fst;
    }
};
set<data> S;
int N,M;
bool cmp(data a,data b){return a.val<b.val;}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    data tmp={0,0,0};
    for(int i=1;i<=N;i++)
    {
        int a;
        fscanf(f,"%d",&a);
        if(tmp.val!=a){S.insert(tmp);tmp.fst=i;tmp.lst=i-1;tmp.val=a;}
        tmp.lst=i;
    }
    S.insert(tmp);
    S.erase({0,0,0});
    while(M--)
    {
//        for(auto it:S)
//        {
//            for(int i=it.fst;i<=it.lst;i++)printf("%d ",it.val);
//        }
//        printf("\n");
        int t,x,y,z;
        fscanf(f,"%d %d %d %d",&t,&x,&y,&z);
        if(t==0)
        {
            set<data> ::iterator it=S.lower_bound({x,y,z});
            vector<data> tmp;tmp.clear();
            if(S.end()!=it)
            {
                set<data>::iterator nxt=next(it);
                while(1)
                {
                    if(it->fst>y)break;
                    if(it->lst>y)
                    {
                        data Tmp={y+1,it->lst,it->val};
                        tmp.push_back({it->fst,y,it->val});
                        S.erase(it);
                        S.insert(Tmp);break;
                    }
                    else
                        tmp.push_back(*it);
                    S.erase(it);
                    it=nxt;
                    if(it==S.end())break;
                    nxt++;
                }
            }
            it=S.lower_bound({x,y,z});
            if(it!=S.begin())
            {
                it--;
                if(it->lst>=x)
                {
                    if(it->fst<x)
                    {
                        if(it->lst<=y)
                        {
                             data Tmp={it->fst,x-1,it->val};
                            tmp.push_back({x,it->lst,it->val});
                            S.erase(it);
                            S.insert(Tmp);
                        }
                        else
                        {
                            data tmp1={it->fst,x-1,it->val};
                            data tmp2={y+1,it->lst,it->val};
                            tmp.push_back({x,y,it->val});
                            S.erase(it);
                            S.insert(tmp1);
                            S.insert(tmp2);
                        }
                    }
                    else
                    {
                        tmp.push_back(*it);
                        S.erase(it);
                    }
                }
            }
            sort(tmp.begin(),tmp.end(),cmp);
            for(auto it:tmp)if(z<=it.lst-it.fst+1){z=it.val;break;}else z-=it.lst-it.fst+1;
            S.insert({x,y,z});
        }
        else
        {
            set<data> ::iterator it=S.lower_bound({x,y,z});
            if(S.end()!=it)
            {
                set<data>::iterator nxt=next(it);
                while(1)
                {
                    if(it->fst>y)break;
                    if(it->lst>y)
                    {
                        data Tmp={y+1,it->lst,it->val};
                        S.insert(Tmp);
                        S.erase(it);
                        S.insert(Tmp);break;
                    }
                    S.erase(it);
                    it=nxt;
                    if(it==S.end())break;
                    nxt++;
                }
            }
            it=S.lower_bound({x,y,z});
            if(it!=S.begin())
            {
                it--;
                if(it->lst<x);
                else
                {
                    if(it->fst<x)
                    {
                        if(it->lst<=y)
                        {
                             data Tmp={it->fst,x-1,it->val};
                            S.erase(it);
                            S.insert(Tmp);
                        }
                        else
                        {
                            data tmp1={it->fst,x-1,it->val};
                            data tmp2={y+1,it->lst,it->val};
                            S.erase(it);
                            S.insert(tmp1);
                            S.insert(tmp2);
                        }
                    }
                    else
                        S.erase(it);
                }
            }
            S.insert({x,y,z});
        }
    }
    for(auto it:S)
    {
        for(int i=it.fst;i<=it.lst;i++)fprintf(g,"%d ",it.val);
    }
    fclose(f);
    fclose(g);
    return 0;
}
