#include <cstdio>
#include <algorithm>
#include <vector>
 
using namespace std;
 
FILE *f = fopen("intersectie.in","r");
FILE *g = fopen("intersectie.ok","w");
 
int n,m,t;
 
vector<pair<unsigned int,unsigned int> > segments;
 
int main(){
 
    fscanf(f,"%d %d %d",&n,&m,&t);
 
    for(int i = 1;i <= m;i++){
        unsigned int x,y;
        fscanf(f,"%u %u",&x,&y);
        if(x <= y){
            segments.push_back({x,y});
            segments.push_back({x + n,y + n});
            segments.push_back({x + 2 * n,y + 2 * n});
        }
        else{
            y += n;
            segments.push_back({x,y});
            segments.push_back({x + n,y + n});
        }
    }
 
    sort(segments.begin(),segments.end());
 
    while(t--){
        unsigned int x,y;
        fscanf(f,"%u %u",&x,&y);
        if(x > y){
            y += n;
        }
        else{
            x += n;
            y += n;
        }
 
        bool found = false;
        bool ok = true;
 
        for(auto it:segments){
            if(it.second < x || it.first > y){
                continue;
            }
            found = true;
            if(!(it.first <= x && y <= it.second)){
                ok = false;
            }
        }
 
        fprintf(g,"%d\n",(ok == true));
    }
 
    return 0;
}

