#include "supertrees.h"
#include <vector>
#include <cstdio>

using namespace std;

struct dsu_t{
    int n;
    int father[1005];

    dsu_t(int n){
        this->n = n;
        for(int i = 0;i < n;i++){
            father[i] = -1;
        }
    }

    int find_root(int nod){
        if(father[nod] == -1){
            return nod;
        }
        return father[nod] = find_root(father[nod]);
    }

    bool unite(int x,int y){
        x = find_root(x);
        y = find_root(y);

        if(x == y){
            return false;
        }

        father[x] = y;
        return true;
    }
};

int construct(vector<vector<int>> p) {
	int n = p.size();
	vector<vector<int>> answer(n,vector<int>(n,0));

    dsu_t dsu(n);

	for (int i = 0; i < n; i++) {
	    for(int j = 0;j < n;j++){
            if(p[i][j] == 3){
                return 0;
            }
            else if(p[i][j] == 1){
                if(dsu.unite(i,j)){
                    answer[i][j] = answer[j][i] = 1;
                }
            }
        }
    }
	for (int i = 0; i < n; i++) {
	    for(int j = 0;j < n;j++){
            if(p[i][j] == 2 || p[i][j] == 0){
                if(dsu.find_root(i) == dsu.find_root(j)){
                    return 0;
                }
            }
        }
    }


    dsu_t dsu2(n);

    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(p[i][j] == 2){
                dsu2.unite(dsu.find_root(i),dsu.find_root(j));
            }
        }
    }

    vector<vector<int> > nodes(n,vector<int>());
    vector<vector<int> > nodes2(n,vector<int>());

    for(int i = 0;i < n;i++){
        nodes[dsu.find_root(i)].push_back(i);
        nodes2[dsu2.find_root(i)].push_back(i);
    }

    for(int i = 0;i < n;i++){
        if(nodes2[i].size() == 2){
            return 0;
        }
        if(nodes2[i].size() > 2){
            int len = nodes2[i].size();
            for(int j = 0;j < len;j++){
                answer[nodes2[i][j]][nodes2[i][(j + 1) % len]] = 1;
                answer[nodes2[i][(j + 1) % len]][nodes2[i][j]] = 1;
            }
            for(int j = 0;j < (int)nodes2[i].size();j++){
                for(int k = j + 1;k < (int)nodes2[i].size();k++){
                    for(auto it:nodes[nodes2[i][j]]){
                        for(auto it2:nodes[nodes2[i][k]]){
                            if(p[it][it2] != 2){
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

	build(answer);
	return 1;
}
