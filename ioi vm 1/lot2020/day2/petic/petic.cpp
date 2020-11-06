#include "petic.h"
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct query_t{
    int pos;
    int l,r;
    int id;
    int sgn;


    bool operator < (const query_t &other)const{
        if(pos != other.pos)return pos < other.pos;
        if(l != other.l)return l < other.l;
        if(r != other.r)return l < other.l;
        if(id != other.id)return l < other.l;
        return sgn < other.sgn;
    }
};

class idk_yet{
private:
    int n;
    vector<pair<int,int> > segments;
public:
    idk_yet(int n){
    }

    void add(int l,int r){
        if(l == -1)return ;
//        printf("add %d %d\n",l,r);
        segments.push_back({l,r});
    }

    int query(int l,int r){
        int ans = 0;
        for(auto it:segments){
            ans += (l <= it.first && it.second <= r);
        }
//        printf("query %d %d with %d\n",l,r,ans);
        return ans;
    }

    void reset(){
        segments.clear();
//        printf("cleared");
    }
};

struct aib2d{
    int n,m;
    vector<vector<int> > aib;

    aib2d(int n,int m){
        aib = vector<vector<int>>(n + 1,vector<int>(m + 1,0));
        this->n = n;
        this->m = m;
    }

    void add(int x,int y){
        if(x == -1)return ;
        x++;
        y++;
        for(int i = x;i;i -= (-i) & i){
            for(int j = y;j <= m;j += (-j) & (j)){
                aib[i][j] += 1;
            }
        }
//        printf("add %d %d\n",x,y);
    }

    int query(int x,int y){
        if(y == -1)return 0;
        x++;y++;
        int ans = 0;
        for(int i = x;i <= n;i += (-i) & i){
            for(int j = y;j;j -= (-j) & j){
                ans += aib[i][j];
            }
        }

//        printf("query %d %d with %d\n",x,y,ans);
        return ans;
    }
};

vector<int> solve(int nrLin, int nrCol, int Q, vector<string> matrix, 
                  vector<int> X1, vector<int> Y1, vector<int> X2, vector<int> Y2) {

    int n = nrLin,m = nrCol;

    if(n > m){
        vector<string> new_matrix;

        string tmp;
        for(int i = 0;i < n;i++)tmp += '0';
        for(int j = 0;j < m;j++)new_matrix.push_back(tmp);

        for(int i = 0;i < n;i++){
            for(int j = 0;j < m;j++){
                new_matrix[j][i] = matrix[i][j];
            }
        }

        for(int i = 0;i < Q;i++){
            swap(X1[i],Y1[i]);
            swap(X2[i],Y2[i]);
        }
        matrix = new_matrix;
        swap(n,m);
    }

    vector<pair<int,int> > lin_segm;
    vector<pair<int,int> > col_segm;

    int good_lines = 0,good_cols = 0;

    for(int i = 0;i < n;i++){
        int fst = -1,lst = -1;
        for(int j = 0;j < m;j++){
            if(matrix[i][j] == '1'){
                if(fst == -1){
                    fst = j;
                }
                lst = j;
            }
        }
        lin_segm.push_back({fst,lst});
        if(fst != -1){
            good_lines++;
        }
    }
    
    for(int j = 0;j < m;j++){
        int fst = -1,lst = -1;
        for(int i = 0;i < n;i++){
            if(matrix[i][j] == '1'){
                if(fst == -1){
                    fst = i;
                }
                lst = i;
            }
        }
        col_segm.push_back({fst,lst});
        if(fst != -1){
            good_cols++;
        }
    }
    
    vector<int> ans(Q,good_lines + good_cols);

    vector<query_t> lin_queries,col_queries;

    for(int t = 0;t < Q;t++){///TODO if using aint, reindex somewhere
        lin_queries.push_back({X1[t] - 1,Y1[t],Y2[t],t,+1});
        lin_queries.push_back({X2[t],Y1[t],Y2[t],t,-1});
        col_queries.push_back({Y1[t] - 1,X1[t],X2[t],t,+1});
        col_queries.push_back({Y2[t],X1[t],X2[t],t,-1});
    }

    sort(lin_queries.begin(),lin_queries.end());
    sort(col_queries.begin(),col_queries.end());

    aib2d aib(n,n);

    map<int,int> to_norm;

    for(auto it:lin_segm){
        to_norm[it.first] = 1;
        to_norm[it.second] = 1;
    }

    int lst = -1;

    for(auto &it:to_norm){
        it.second = ++lst;
    }

    int lst_lin = -1;

    aib2d stuff(lst + 1,lst + 1);

    for(auto it:lin_queries){
        while(lst_lin + 1 <= it.pos){
            lst_lin++;
            stuff.add(to_norm[lin_segm[lst_lin].first],to_norm[lin_segm[lst_lin].second]);
        }
        map<int,int> :: iterator tmp = to_norm.lower_bound(it.l);
        if(tmp == to_norm.end()){
            it.l = m + 1;
        }
        else{
            it.l = tmp->second;
        }
        tmp = to_norm.lower_bound(it.r + 1);
        if(tmp != to_norm.begin()){
            tmp--;
            it.r = tmp->second;
        }
        else{
            it.r = -1;
        }
        ans[it.id] += it.sgn * stuff.query(it.l,it.r);
//        printf("line %d %d %d %d %d %d\n",it.pos,it.l,it.r,it.id,it.sgn,stuff.query(it.l,it.r));
    }

    int lst_col = -1;

    for(auto it:col_queries){
        while(lst_col + 1 <= it.pos){
            lst_col++;
            aib.add(col_segm[lst_col].first,col_segm[lst_col].second);
        }
        ans[it.id] += it.sgn * aib.query(it.l,it.r);
//        printf("col %d %d %d %d %d\n",it.pos,it.l,it.r,it.id,it.sgn,stuff.query(it.l,it.r));
    }

    return ans;
}
