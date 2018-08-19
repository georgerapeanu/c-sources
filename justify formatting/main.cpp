#include <bits/stdc++.h>

using namespace std;
vector<string> justifyFormatting(vector<string> words, int K) {
    vector<string> rez;
    vector<string> tmp;
    int sz=0;
    for(auto it:words)
    {
        if(sz+tmp.size()+it.size()>K)
        {
            int gap=(K-sz)/(tmp.size()-1);
            int extragap=(K-sz)%(tmp.size()-1);
            string a;a.clear();
            for(int i=0;i<tmp.size();i++)
            {
                if(i)for(int j=1;j<=gap;j++)a+=' ';
                if(i&&i<=extragap)a+=' ';
                a+=tmp[i];
            }
            rez.push_back(a);
            tmp.clear();
            sz=0;
        }
        tmp.push_back(it);
        sz+=it.size();
    }
    if(!tmp.empty())
    {
        string a;a.clear();
        for(auto it:tmp)
            a=a+' '+it;
        rez.push_back(a.substr(1));
    }
    return rez;
}
int main()
{
    vector<string> a=justifyFormatting({"Hello","world,","welcome","to","CS","Academy!"},14);
    for(auto it:a)
        cout<<it<<"\n";
    return 0;
}
