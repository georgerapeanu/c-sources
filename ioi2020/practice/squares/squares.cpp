#include "squares.h"
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

vector<int> paint(int n) {
	
    vector<int> labels(n + 1,0);

    vector<vector<bool> > viz(1 << 11,vector<bool>(2,false));

    int k = 1;

    while(n - k + 1 > (1 << k)){
        k++;
    }

    if(n == 2){
        labels = {0,1,1};
        return labels;
    }

    int nod = 0;

    vector<int> st = {nod};
    vector<int> cycle;

    while(st.empty() == false){
        int nod = st.back();
        if(viz[nod][0] == 0){
            st.push_back(nod * 2 - ((((nod * 2) >> (k - 1)) & 1) << (k - 1)));
            viz[nod][0] = 1;
        }
        else if(viz[nod][1] == 0){
            st.push_back(nod * 2 + 1 - ((((nod * 2) >> (k - 1)) & 1) << (k - 1)));
            viz[nod][1] = 1;
        }
        else{
            cycle.push_back(nod);
            st.pop_back();
        }
    }

    reverse(cycle.begin(),cycle.end());

    labels[n] = k;

    for(int i = 0;i < k - 1;i++){
         labels[i] = 0;
    }

    for(int i = k - 1;i < n;i++){
        labels[i] = (cycle[i - k + 2] & 1);
    }

	return labels;
}

int where[2005][2005];
bool viz[2005];

void prepare(int n){
    if(viz[n]){
        return ;
    }
    viz[n] = true;
    vector<int> labels = paint(n);

    int curr = 0;
    int k = labels.back();

    for(int i = 0;i < k;i++){
        curr = curr * 2 + labels[i];
    }

    for(int i = 0;i < n - k + 1;i++){
        where[n][curr] = i;
        curr = (curr * 2 + labels[i + k]) - (labels[i] << k);
    }
}

int find_location(int n, vector<int> c) {
    if(c.back() == -1){
        for(int i = 0;i < (int)c.size();i++){
            if(c[i] == -1){
                return n - i;
            }
        }
    }

    prepare(n);
    
    int target = 0;

    for(auto it:c){
        target = target * 2 + it;
    }

    return where[n][target];
}
