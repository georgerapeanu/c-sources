#include "petic.h"

using namespace std;

vector<int> solve(int nrLin, int nrCol, int Q, vector<string> matrix, 
                  vector<int> X1, vector<int> Y1, vector<int> X2, vector<int> Y2) {

    int n = nrLin,m = nrCol;
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
    
    vector<int> ans;

    for(int t = 0;t < Q;t++){
        ans.push_back(good_lines + good_cols);
        for(int i = X1[t];i <= X2[t];i++){
            if(lin_segm[i].first != -1 && Y1[t] <= lin_segm[i].first && lin_segm[i].second <= Y2[t]){
                ans.back()--; 
            }
        }
        for(int j = Y1[t];j <= Y2[t];j++){
            if(col_segm[j].first != -1 && X1[t] <= col_segm[j].first && col_segm[j].second <= X2[t]){
                ans.back()--; 
            }
        }
    }

    return ans;
}
