#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const int BUCK = 400;
const int DEB = 0;

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

struct node_t{
    int color;
    vector<int> cells;
    unordered_map<int,unordered_set<int> > neighbors;

    void merge(const node_t &other){
        for(auto it:other.cells){
            this->cells.push_back(it);
        }
        for(auto it:other.neighbors){
            for(auto it2:it.second){
                this->neighbors[it.first].insert(it2);
            }
        }
    }

    int size(){
        return (int)cells.size();
    }

    void swap(node_t &other){
        int aux = this->color;
        this->color = other.color;
        other.color = aux;
        this->cells.swap(other.cells);
        this->neighbors.swap(other.neighbors);
    }
};

class DSU{
    int n,m;
    vector<int> father;
    vector<node_t> stuff;
    vector<int> big_roots;

    int coord_to_pos(int x,int y){
        return (x - 1) * m + y;
    }

    pair<int,int> pos_to_coord(int pos){
        return {(pos - 1) / m + 1,(pos - 1) % m + 1};
    }
    
    int find_root(int nod){
        if(father[nod] == 0){
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

        if(stuff[x].size() > stuff[y].size()){
            swap(x,y);
        }

        father[x] = y;

        stuff[y].merge(stuff[x]);

        return true;
    }

public:

    DSU(int n,int m){
        this->n = n;
        this->m = m;
        father = vector<int>(n * m + 1,0);
        stuff = vector<node_t>(n * m + 1);
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                stuff[coord_to_pos(i,j)].cells = {coord_to_pos(i,j)};
                stuff[coord_to_pos(i,j)].color = -1;
            }
        }

    }

    void update_color(int x,int y,int c){
        int root = find_root(coord_to_pos(x,y));

        vector<int> to_unite = {root};

        if(DEB){
            printf("curr %d\n",root);
        }
        
        if(stuff[root].size() < BUCK){
            for(auto it:stuff[root].cells){
                int x = pos_to_coord(it).first;
                int y = pos_to_coord(it).second;
                for(int k = 0;k < 4;k++){
                    int xx = x + dx[k];
                    int yy = y + dy[k];
                    if(1 <= xx && xx <= n && 1 <= yy && yy <= m){
                        int neighbor_root = find_root(coord_to_pos(xx,yy));
                        if(root != neighbor_root && c == stuff[neighbor_root].color){
                            to_unite.push_back(neighbor_root);
                        }
                    }
                }
            }
        }
        else{
            for(auto it:stuff[root].neighbors[c]){
                int neighbor_root = find_root(it);
                if(root != neighbor_root && c == stuff[neighbor_root].color){
                    to_unite.push_back(neighbor_root);
                }
            }
            stuff[root].neighbors[c].clear();
        }

        sort(to_unite.begin(),to_unite.end());
        to_unite.resize(unique(to_unite.begin(),to_unite.end()) - to_unite.begin());

        int new_size = 0;

        for(auto it:to_unite){
            new_size += stuff[it].size();
        }

        stuff[root].color = c;

        if(new_size >= BUCK){
            node_t tmp;
            tmp.color = c;
            for(auto it:to_unite){
                if(stuff[it].size() < BUCK){
                    for(auto it2:stuff[it].cells){
                        int x = pos_to_coord(it2).first;
                        int y = pos_to_coord(it2).second;
                        for(int k = 0;k < 4;k++){
                            int xx = x + dx[k];
                            int yy = y + dy[k];
                            if(1 <= xx && xx <= n && 1 <= yy && yy <= m){
                                int neighbor_root = find_root(coord_to_pos(xx,yy));
                                if(root != neighbor_root){
                                    tmp.neighbors[stuff[neighbor_root].color].insert(neighbor_root);
                                }
                            }
                        }
                    }
                    
                }
            }
            
            for(auto it:to_unite){
                if(DEB){
                    printf("unite %d %d\n",root,it);
                }
                unite(root,it);
            }
        
            root = find_root(root);

            if(stuff[root].size() < tmp.size()){
                stuff[root].swap(tmp);
            }

            stuff[root].merge(tmp);
            
            big_roots.push_back(root);
            for(auto &it:big_roots){
                it = find_root(it);
            }
            sort(big_roots.begin(),big_roots.end());
            big_roots.resize(unique(big_roots.begin(),big_roots.end()) - big_roots.begin());

            for(auto it:big_roots){
                if(it != root && stuff[root].neighbors[stuff[it].color].count(it)){
                    stuff[it].neighbors[c].insert(root);
                }
            }
        }
        else{
            for(auto it:to_unite){
                if(DEB){
                    printf("unite %d %d\n",root,it);
                }
                unite(root,it);
            }
        
            root = find_root(root);

            for(auto it:stuff[root].cells){
                int x = pos_to_coord(it).first;
                int y = pos_to_coord(it).second;
                for(int k = 0;k < 4;k++){
                    int xx = x + dx[k];
                    int yy = y + dy[k];
                    if(1 <= xx && xx <= n && 1 <= yy && yy <= m){
                        int neighbor_root = find_root(coord_to_pos(xx,yy));
                        if(root != neighbor_root){
                            if(stuff[neighbor_root].size() >= BUCK){
                                stuff[neighbor_root].neighbors[c].insert(root);
                            }
                        }
                    }
                }
            }
        }

        if(DEB){
            printf("end root %d\n\n",root);
        }

    }

    int get_color(int x,int y){
        return stuff[find_root(coord_to_pos(x,y))].color;
    }

    void print(){
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
//                printf("%d ",find_root(coord_to_pos(i,j)));
                printf("%d ",get_color(i,j));
            }
            printf("\n");
        }
    }
};

const int LEN = (1 << 14);
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    while(buff[ind] >= '0' && buff[ind] <= '9'){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }
    return ans;
}

int main(){

    int n,m;
    n = i32();
    m = i32();

    DSU solver(n,m);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            int c;
            c = i32();
            solver.update_color(i,j,c);
        }
    }
    if(DEB){
        solver.print();
    }

    /*for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            solver.update_color(i,j,solver.get_color(i,j));
        }
    }*/

    int q;

    q = i32();

    while(q--){
        int x,y,c;
        x = i32();
        y = i32();
        c = i32();
        solver.update_color(x,y,c);
        if(DEB){
            solver.print();
        }
    }

    solver.print();

    return 0;
}
