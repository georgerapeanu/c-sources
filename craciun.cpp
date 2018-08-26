#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <deque>
#include <vector>
     
using namespace std;
     
FILE *f = fopen("craciun.in","r");
FILE *g = fopen("craciun.out","w");
     
	
const int BUCK_WILD = 2e3;
const int NMAX = 1e5;
const double EPS = 1e-5;
     
int n;
int clopotei[NMAX + 5];
int weight[NMAX + 5];
long long ans[NMAX + 5];
vector<int> graph[NMAX + 5];
deque<long long> csf_boss[NMAX + 5];
    
void bfs(int nod){
    vector<int> nodes;
    nodes.push_back(nod);
    for(int i = 0;i < (int)nodes.size();i++){
        int it = nodes[i];
        for(int j = 0;j < (int)graph[it].size();j++){
            int it2 = graph[it][j];
            nodes.push_back(it2);
        }
    }
        
    reverse(nodes.begin(),nodes.end());
        
    for(auto it:nodes){
        weight[it] = 1;
        int bigChild = -1;
        for(auto it2:graph[it]){
            weight[it] += weight[it2];
            if(bigChild == -1 || weight[it2] > weight[bigChild]){
                bigChild = it2;
            }
        }
            
        if(bigChild != -1){
            csf_boss[it].swap(csf_boss[bigChild]);
        }
         
        csf_boss[it].push_front(clopotei[it]);
         
        long long sum = 0;
        for(int i = 0;i < BUCK_WILD && i <(int)csf_boss[it].size();i++){
            sum += csf_boss[it][i];
            ans[1 + i] = max(ans[1 + i],sum);
        }
 
         
        for(auto it2:graph[it]){
            if(it2 != bigChild){
                for(int i = 0;i < (int)csf_boss[it2].size();i++){
                    if((int)csf_boss[it].size() > i + 1){
                        csf_boss[it][i + 1] += csf_boss[it2][i];
                    }
                    else{
                         csf_boss[it].push_back(csf_boss[it2][i]);
                    }
                }
				long long sum = 0;
				for(int i = 0;i < (int)csf_boss[it2].size() + BUCK_WILD && i < (int)csf_boss[it].size();i++){
					sum += csf_boss[it][i];
					ans[1 + i] = max(ans[1 + i],sum);
				}
			}
        }   
    }
        
}
     
const int LEN = 1e4;
int ind = LEN - 1;
char buff[LEN];

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9'){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
            ind = 0;
        }
    }

    return ans;
}
	 

int main(){
     
	n = i32();
     
    for(int i = 1; i <= n; i++){
        clopotei[i] = i32();
    }
     
    for(int i = 2;i <= n;i++){
        int tata = i32();
        graph[tata].push_back(i);
    }
        
    bfs(1);
        
    double rez = 0;
        
    for(int i = 1;i <= n;i++){
        rez = max(rez,ans[i] / (double)i);
    }
     
    fprintf(g,"%.5f",rez);
     
    return 0;
}