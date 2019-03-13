#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

FILE *f = fopen("siruri3.in","r");
FILE *g = fopen("siruri3.out","w");

const int KMAX = 1e5;
const int NMAX = 100;

int n,len;

int v[NMAX + 5][NMAX + 5];

int nr0,nr1;

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

struct data_t{
    pair<int,int> center;
    vector< pair<int,int> > around0;
    vector< pair<int,int> > around1;
};

data_t Find(int ce_type,int cnt0,int cnt1){
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            if(v[i][j] == ce_type){
                vector<pair<int,int> > tmp0;
                vector<pair<int,int> > tmp1;
                for(int k = 0;k < 4;k++){
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if(x <= 0 || x > n || y <= 0 || y > n){
                        continue;
                    }
                    if(v[x][y] == 0){
                        tmp0.push_back({x,y});
                    }
                    else{
                        tmp1.push_back({x,y});
                    }
                }

                if((int)tmp0.size() >= cnt0 && (int)tmp1.size() >= cnt1){
                    tmp0.resize(cnt0);
                    tmp1.resize(cnt1);
                    return {make_pair(i,j),tmp0,tmp1};
                }
            }
        }
    }

    return {make_pair(-1,-1),vector<pair<int,int>>(),vector<pair<int,int>>()};
}

void alternate(pair<int,int> a,pair<int,int> b,int len){
    for(int i = 1;i <= len;i++){
        if(i & 1){
            fprintf(g,"%d %d\n",a.first,a.second);
        }
        else{
            fprintf(g,"%d %d\n",b.first,b.second);
        }
    }
}

int main(){

    fscanf(f,"%d %d",&n,&len);

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            fscanf(f,"%d",&v[i][j]);
        }
    }

    for(int i = 1;i <= len;i++){
        int val;
        fscanf(f,"%d",&val);
        if(val == 0){
            nr0++;
        }
        else{
            nr1++;
        }
    }

    if(nr0 >= nr1){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= n;j++){
                v[i][j] ^= 1;
            }
        }
        swap(nr0,nr1);
    }

    if(nr0 == 0){
        if(nr1 == 1){
            for(int i = 1;i <= n;i++){
                for(int j = 1;j <= n;j++){
                    if(v[i][j] == 1){
                        fprintf(g,"%d %d\n",i,j);
                        return 0;
                    }
                }
            }
            fprintf(g,"-1\n");
            return 0;
        }
        data_t tmp = Find(1,0,1);
        if(tmp.center.first == -1){
            fprintf(g,"-1");
            return 0;
        }
        alternate(tmp.center,tmp.around1[0],len);
        return 0;
    }
    else if(nr0 < nr1){
        data_t tmp = Find(1,1,1);
        if(tmp.center.first != -1){
            if((nr1 - nr0) % 2 == 0){
                alternate(tmp.around1[0],tmp.center,nr1 - nr0);
                alternate(tmp.around0[0],tmp.center,2 * nr0);
            }
            else{
                alternate(tmp.center,tmp.around1[0],nr1 - nr0);
                alternate(tmp.around0[0],tmp.center,2 * nr0);
            }
            return 0;
        }
        else if(nr1 - nr0 == 1){
            data_t tmp = Find(1,1,0);
            if(tmp.center.first == -1){
                fprintf(g,"-1");
                return 0;
            }
            alternate(tmp.center,tmp.around0[0],len);
            return 0;
        }
        fprintf(g,"-1");
        return 0;
    }

    else if(nr0 == nr1){
        data_t tmp = Find(0,0,1);
        if(tmp.center.first == -1){
            fprintf(g,"-1");
            return 0;
        }
        alternate(tmp.center,tmp.around1[0],len);
        return 0;
    }

    fclose(f);
    fclose(g);

    return 0;
}
