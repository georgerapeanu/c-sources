#include <iostream>
#include <map>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int,pair<int,char*> > data; ///.first=puncte, .second.first=goluri,.second.second=nume
data rez[10];
char t1[150],t2[150];
int i,t1g,t2g,in1,in2,ctr,j;
bool sortare(data a,data b)
{
    if(a.first!=b.first)
        return a.first>b.first;
    if(a.second.first!=b.second.first)
        return a.second.first>b.second.first;
    return a.second.second<b.second.second;
}
void cautare()
{
    bool gasit1=0,gasit2=0;
    for(j=1;j<=ctr;j++)
    {
        if(strcmp(rez[j].second.second,t1)==0)
            {gasit1=1;in1=j;}
        if(strcmp(rez[j].second.second,t2)==0)
            {gasit2=1;in2=j;}
    }
    if(!gasit1)
        in1=++ctr;
    if(!gasit2)
        in2=++ctr;
}
int main()
{
    for(i=1;i<=6;i++)
        {
            cin>>t1>>t2>>t1g>>t2g;
            cautare();
            if(t1g>t2g)
                rez[in1].first+=3;
            else if(t1g==t2g)
            {
                rez[in1].first++;
                rez[in2].first++;
            }
            else
                rez[in2].first+=3;
            rez[in1].second.first+=t1g;
            rez[in2].second.first+=t2g;
            rez[in1].second.second=(char*) malloc(105*sizeof(char));
            rez[in2].second.second=(char*) malloc(105*sizeof(char));
            strcpy(rez[in1].second.second,t1);
            strcpy(rez[in2].second.second,t2);
        }
    sort(rez+1,rez+5,sortare);
    for(i=1;i<=4;i++)
        cout<<rez[i].second.second<<"\n";
    return 0;
}
