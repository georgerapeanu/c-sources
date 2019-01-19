#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("amiba.in","r");
FILE *g = fopen("amiba.out","w");

int t,n,a,b;

long long solve_individual(vector< pair<int,int> > &boss, 
                      vector< pair<int,int> > &junior, 
                      vector< pair<int,int> > &slim,
                      vector< pair<int,int> > &ans){

    long long cost = 0;
    vector< pair<int,int> > used(boss.size(),{0,0});

    int x = 0,y = 0;

    for(int i = 0;i < (int)boss.size();i++){
    
        while(x < (int)junior.size() && junior[x].first < boss[i].first){
            x++;
        }
        while(y < (int)slim.size() && slim[y].first < boss[i].first){
            y++;
        }

        if(x == (int)junior.size() || y == (int)slim.size()){
            break;
        }

        used[x].first = true;
        used[y].second = true;

        ans[boss[i].second].first = junior[x++].first;
        ans[boss[i].second].second = slim[y++].first;
    }

    for(int i = 0;i < (int)boss.size();i++){

        if(ans[boss[i].second].first != -1 || ans[boss[i].second].second != -1){
            continue;
        }

        while(x < (int)junior.size() && junior[x].first < boss[i].first){
            x++;
        }
        while(y < (int)slim.size() && slim[y].first < boss[i].first){
            y++;
        }

        if(x == (int)junior.size() && y == (int)slim.size()){
            break;
        }
        else if(x != (int)junior.size() && (y == (int)slim.size() || junior[x].first < slim[y].first)){
            used[x].first = true;
            ans[boss[i].second].first = junior[x++].first;
        }    
        else{
            used[y].second = true;
            ans[boss[i].second].second = slim[y++].first;
        }
    }

    x = 0;y = 0;

    for(int i = 0;i < (int)boss.size();i++){
        if(ans[boss[i].second].first == -1){
            while(used[x].first){
                x++;
            }
            ans[boss[i].second].first = junior[x++].first;
        }
        if(ans[boss[i].second].second == -1){
            while(used[y].second){
                y++;
            }
            ans[boss[i].second].second = slim[y++].first;
        }
    }
    
    for(int i = 0;i < (int)boss.size();i++){
        int ind = boss[i].second;

        if(ans[ind].first >= boss[i].first && ans[ind].second >= boss[i].first){
            ;
        }
        else if(ans[ind].first >= boss[i].first || ans[ind].second >= boss[i].first){
            cost += b;
        }
        else{
            cost += a;
        }
    }

    return cost;
}

long long solve_combined(vector< pair<int,int> > &boss, 
                    vector< pair<int,int> > &junior, 
                    vector< pair<int,int> > &slim,
                    vector< pair<int,int> > &ans){

    long long cost = 0;
    vector< pair<int,int> > used(boss.size(),{0,0});

    int x = 0,y = 0;

    for(int i = 0;i < (int)boss.size();i++){
    
        while(x < (int)junior.size() && junior[x].first < boss[i].first){
            x++;
        }
        while(y < (int)slim.size() && slim[y].first < boss[i].first){
            y++;
        }

        if(x == (int)junior.size() && y == (int)slim.size()){
            break;
        }
        else if(x != (int)junior.size() && (y == (int)slim.size() || junior[x].first < slim[y].first)){
            used[x].first = true;
            ans[boss[i].second].first = junior[x++].first;
        }    
        else{
            used[y].second = true;
            ans[boss[i].second].second = slim[y++].first;
        }
    }

    int st = 0,dr = (int)boss.size() - 1;

    for(int i = (int)boss.size() - 1;i >= 0;i--){
        if(ans[boss[i].second].first == -1){
            while(used[st].first){
                st++;
            }
            while(used[dr].first){
                dr--;
            }
            if(junior[dr].first >= boss[i].first){
                ans[boss[i].second].first = junior[dr--].first;
            }
            else{
                ans[boss[i].second].first = junior[st++].first;
            }
        }
    }
    
    st = 0,dr = (int)boss.size() - 1;
    
    for(int i = (int)boss.size() - 1;i >= 0;i--){
        if(ans[boss[i].second].second == -1){
            while(used[st].second){
                st++;
            }
            while(used[dr].second){
                dr--;
            }
            if(slim[dr].first >= boss[i].first){
                ans[boss[i].second].second = slim[dr--].first;
            }
            else{
                ans[boss[i].second].second = slim[st++].first;
            }
        }
    }

    for(int i = 0;i < (int)boss.size();i++){
        int ind = boss[i].second;

        if(ans[ind].first >= boss[i].first && ans[ind].second >= boss[i].first){
            ;
        }
        else if(ans[ind].first >= boss[i].first || ans[ind].second >= boss[i].first){
            cost += b;
        }
        else{
            cost += a;
        }
    }

    return cost;
}

int main(){

    fscanf(f,"%d",&t);

    while(t--){
        
        fscanf(f,"%d %d %d",&n,&a,&b);
        vector< pair<int,int> > boss(n,{0,0});
        vector< pair<int,int> > junior(n,{0,0});
        vector< pair<int,int> > slim(n,{0,0});
        vector< pair<int,int> > ans1(n,make_pair(-1,-1));
        vector< pair<int,int> > ans2(n,make_pair(-1,-1));

        for(int i = 0;i < n;i++){
            fscanf(f,"%d",&boss[i].first);         
            boss[i].second = i;
        }   
        
        for(int i = 0;i < n;i++){
            fscanf(f,"%d",&junior[i].first);     
            junior[i].second = i;
        }   
        
        for(int i = 0;i < n;i++){
            fscanf(f,"%d",&slim[i].first);   
            slim[i].second = i;
        }   

        sort(boss.begin(),boss.end());
        sort(junior.begin(),junior.end());
        sort(slim.begin(),slim.end());
        
        long long cost1 = solve_combined(boss,junior,slim,ans1);
        long long cost2 = solve_individual(boss,junior,slim,ans2);

        if(cost1 > cost2){
            swap(ans1,ans2);
        }

        for(auto it:ans1){
            fprintf(g,"%d ",it.first);
        }
        fprintf(g,"\n");

        for(auto it:ans1){
            fprintf(g,"%d ",it.second);
        }
        fprintf(g,"\n");
     }

    fclose(f);
    fclose(g);

    return 0;
}
