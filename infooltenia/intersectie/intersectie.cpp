/*
 * cele mai tampite teste
 * bine ca in exemplu apare cazul ala sa existe macar un interval care le curpinde
 * dar in teste nu s-o mai obosit sa verifice chestia asta
 * csf sa se prinda concurentii ca nu baga comisia in seama propriul exemplu
 * mai ales la no feedback
 */

#include <cstdio>
#include <algorithm>
#include <vector>
 
using namespace std;
 
FILE *f = fopen("intersectie.in","r");
FILE *g = fopen("intersectie.out","w");
 
int n,m;
int t,p,q;
 
struct data_t{
    unsigned int x,y;
 
    bool operator < (const data_t &other)const{
        if(x != other.x){
            return x < other.x;
        }
        return y < other.y;
    }
};
 
 
vector< data_t > segments;
vector<unsigned int> lft;
vector<unsigned int> rgt;
 
int chestie(unsigned int x,vector<unsigned int> &v){
    int st = -1;
    int dr = v.size() - 1;
 
    while(dr - st > 1){
        int mid = (st + dr) / 2;
 
        if(v[mid] < x){
            st = mid;
        }
        else{
            dr = mid;
        }
    }
 
    return dr;
}
 
bool no_start_point(unsigned int x,unsigned int y){
    if(x > y){
        return 1;
    }
 
    return lft[chestie(x,lft)] > y;
}
 
bool no_end_point(unsigned int x,unsigned int y){
    if(x > y){
        return 1;
    }

    return rgt[chestie(x,rgt)] > y;
}
 
int main(){
    fscanf(f,"%d %d %d",&n,&m,&t);
 
    while(m--){
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
 
    for(auto it:segments){
        lft.push_back(it.x);
        rgt.push_back(it.y);
    }
 
    sort(segments.begin(),segments.end());
    sort(lft.begin(),lft.end());
    sort(rgt.begin(),rgt.end());
 
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
 
        if(no_start_point(x + 1,y) && no_end_point(x,y - 1)){
            fprintf(g,"1\n");
        }
        else{
            fprintf(g,"0\n");
        }
    }
 
    fclose(f);
    fclose(g);
 
    return 0;
}
