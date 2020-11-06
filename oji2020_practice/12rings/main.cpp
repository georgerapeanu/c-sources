#include <bits/stdc++.h>

using namespace std;

FILE *f = fopen("in","r");

char c[100];
int val;

int main(){

    vector<vector<double> > gauss;
    vector<int> perm;

    while(fscanf(f,"%s %d\n",c,&val) == 2){
        vector<double> fr= vector<double>(30,0);
        for(int i = 0;c[i] != '\0';i++){
            fr[c[i] - 'a']++;
        }
        fr[29] = val;
        perm.push_back(gauss.size());
        gauss.push_back(fr);
    }


    for(auto it:perm)printf("%d ",it);printf("\n");

    for(auto it:gauss){
        for(auto it2:it){
            printf("%.0f ",it2);
        }
        printf("\n");
    }

    int i = 0;
    int j = 0;

    while(i < (int)gauss.size() && j < gauss[i].size()){
        for(int k = i;k < (int)gauss.size();k++){
            if(gauss[k][j] != 0){
                swap(gauss[k],gauss[i]);
                swap(perm[k],perm[i]);
                break;
            }
        }

        if(gauss[i][j] == 0){
            j++;
            continue;
        }

        for(int k = 0;k < gauss[i].size();k++){
            if(k != j){
                gauss[i][k] /= gauss[i][j];
            }
        }
        gauss[i][j] = 1;

        for(int k = 0;k < (int)gauss.size();k++){
            if(k == i){
                continue;
            }
            double r = gauss[k][j];
            printf("vector %d with base bit %d coef for row %d is %.4f\n",i,j,k,r);
            for(int l = 0;l < (int)gauss[i].size();l++){
                gauss[k][l] -= r * gauss[i][l];
            }
        }
        i++;
        j++;
    }

    for(auto it:perm)printf("%d ",it);printf("\n");

    for(auto it:gauss){
        for(auto it2:it){
            printf("%.0f ",it2);
        }
        printf("\n");
    }

    return 0;
}
