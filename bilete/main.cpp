#include <map>
#include <fstream>
using namespace std;
ifstream f("bilete.in");
ofstream g("bilete.out");
map<string,string> m;
map<string,bool> seen;
map<string,bool>::iterator it;
string oras1,oras2,start;
int i,n;
int main(){
    f>>n;
    for(i=1;i<=n;i++){
        f>>oras1>>oras2;
        m[oras1]=oras2;
        seen[oras2]=1;
        if(seen.find(oras1)==seen.end())
        seen[oras1]=0;
    }
    for(it=seen.begin();it!=seen.end();it++){
        if(it->second==0)
        {
            start=it->first;
        }
    }
    while(m.find(start)!=m.end()){
        g<<start<<" "<<m[start]<<"\n";
        start=m[start];
    }
    f.close();
    g.close();
    return 0;
}
