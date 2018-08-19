#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int N,M;
pair<int,int> V[3005];
vector<int> voters[3005];
bool U[3005];

bool cmp(pair<int,int> a,pair<int,int> b){
    return a.second < b.second;
}

int main(){

    fscanf(stdin,"%d %d",&N,&M);

    for(int i = 1;i <= N;i++){
        fscanf(stdin,"%d %d",&V[i].first,&V[i].second);
    }

    sort(V + 1,V + 1 + N,cmp);
    reverse(V + 1,V + 1 + N);

    long long best = 1LL << 62;

    for(int max_votes = 0;max_votes <= N;max_votes++){
        long long cost = 0;

        for(int i = 1;i <= M;i++){
            voters[i].clear();
        }
        for(int i = 1;i <= N;i++){
            voters[V[i].first].push_back(i);
            U[i] = (V[i].first == 1);
        }


        for(int i = 2;i <= M;i++){
            while(voters[i].size() > max_votes){
                cost += V[voters[i].back()].second;
                voters[1].push_back(voters[i].back());
                U[voters[i].back()] = 1;
                voters[i].pop_back();
            }
        }

        for(int i = N;i && max_votes >= (int)voters[1].size();i--){
            if(!U[i]){
                U[i] = 1;
                cost += V[i].second;
                voters[1].push_back(i);
            }
        }

        best = min(best,cost);
    }

    fprintf(stdout,"%I64d",best);

    return 0;
}
