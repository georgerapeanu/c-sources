#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("undo2.in","r");
FILE *g = fopen("undo2.out","w");

const int VMAX = 2e5;
const int LEN = 1e4;
int ind = LEN - 1;
char buff[LEN];

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}


int n;
vector<int> pos[VMAX + 5];
int lst = 0;
int sterg_lst = 0;

int v[VMAX + 5];

int main(){

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        int t,x;
        fscanf(f,"%d %d",&t,&x);
        if(t == 1){
            for(int i = sterg_lst;i > lst;i--){
                pos[v[i]].pop_back();                
                v[i] = 0;
            }
            pos[x].push_back(++lst);
            v[lst] = x;
            sterg_lst = lst;
        }
        else if(t == 2){
            lst -= x;
        }
        else if(t == 3){
            lst += x;
            for(int i = sterg_lst;i > lst;i--){
                pos[v[i]].pop_back();                
                v[i] = 0;
            }
            sterg_lst = lst;
        }
        else{
            int ans = lower_bound(pos[x].begin(),pos[x].end(),lst + 1) - pos[x].begin();
            fprintf(g,"%d\n",ans);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
