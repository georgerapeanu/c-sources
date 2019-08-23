#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

const int STR_END = -2;
const int STR_CHAR = -1;

struct edge_t{
    int to;
    int st,dr;

    edge_t(){
        st = dr = to = 0;
    }

    edge_t(int to,int st,int dr){
        this->to = to;
        this->st = st;
        this->dr = dr;
    }

    bool is_null(){
        return to == 0;
    }
};

///tested on TIMUS1590
///fail function is a bit problematic,but if you think about it,a node shall always point to the last inner node inserted(or if we dont split the node the last active point),and if the suffix is starting to use a new char(like when we advance to a node with all we got,or we insert a new char), beeing an intermediary point and not a leaf, his fail function has to be now
class SuffixTree{
private:
    
    vector<int> v;
    vector<int> _fail;
    vector<unordered_map<int,edge_t>> graph;
    int last_node;
    int lst;
    int active_node;
    edge_t active_edge;
    int active_len;
    int root;
    int last_inner_node;
    int last_leaf;
    int search_idx;

    inline int get_len(const edge_t &a){
        if(a.dr == STR_END){
            return (int)v.size() - a.st;
        }
        return a.dr - a.st + 1;
    }

    inline int get_pos(const edge_t &a,int pos){
        return v[a.st + pos - 1];
    }

    inline int get_node(){
        ++last_node;
        _fail.push_back(0);
        graph.push_back(unordered_map<int,edge_t>());
        return last_node;
    }

    void insert_from_node(){
        int leaf = get_node();
        graph[active_node][v.back()] = {leaf,(int)v.size() - 1,STR_END};

        if(last_leaf != root){
            _fail[last_leaf] = leaf;
        }
        last_leaf = leaf;

        if(last_inner_node != root){
            _fail[last_inner_node] = active_node;
        }
        last_inner_node = active_node;
       
        if(active_node == root){
            search_idx++;
        }

        active_node = _fail[active_node];
        active_edge = edge_t();
        lst++;
    }

    void split_and_insert(){
        int inner = get_node();
        int leaf = get_node();

        graph[active_node][get_pos(active_edge,1)] = {inner,active_edge.st,active_edge.st + active_len - 1};
        graph[inner][get_pos(active_edge,active_len + 1)] = {active_edge.to,active_edge.st + active_len,active_edge.dr};
        graph[inner][v.back()] = {leaf,(int)v.size() - 1,STR_END};

        if(last_leaf != root){
            _fail[last_leaf] = leaf;
        }
        last_leaf = leaf;

        if(last_inner_node != root){
            _fail[last_inner_node] = inner;
        }
        last_inner_node = inner;

        if(active_node == root){
            active_len--;
            search_idx++;
        }

        active_node = _fail[active_node];
        active_edge = edge_t();
        lst++;
    }

public:

    SuffixTree(){
        v = vector<int>(1,0);///to 1-index it
        graph.push_back(unordered_map<int,edge_t>());
        _fail = vector<int>(1,0);
        lst = 1;///last uninserted;
        last_node = active_node = root = 0;
        active_edge = edge_t();
        active_len = 0;
        last_inner_node = last_leaf = 0;
        search_idx = 1;
    }

    void add_elem(int x){
        v.push_back(x);
        if(active_len == 0){
            if(last_inner_node){
                _fail[last_inner_node] = active_node;
                last_inner_node = root;
            }
        }
        last_inner_node = 0;
        while(true){
            if(lst == (int)v.size()){
                return;
            }
            if(active_edge.is_null() == true){
                if(search_idx < (int)v.size() && graph[active_node].count(v[search_idx])){
                    active_edge = graph[active_node][v[search_idx]];
                }
                else{
                    insert_from_node();
                    continue;
                }
            }
            if(active_len >= get_len(active_edge)){
                search_idx += get_len(active_edge);
                active_len -= get_len(active_edge);
                active_node = active_edge.to;
                active_edge = edge_t();
                continue;
            }
            if(get_pos(active_edge,active_len + 1) == v.back()){
                active_len++;
                if(last_inner_node){
                    _fail[last_inner_node] = active_node;
                    last_inner_node = root;
                }
                if(active_len >= get_len(active_edge)){
                    active_len -= get_len(active_edge);
                    search_idx += get_len(active_edge);
                    active_node = active_edge.to;
                    active_edge = edge_t();
                }
                break;
            }
            else{
                split_and_insert();
                continue;
            }
        }
    }

    void fix_edges(){
        for(int i = 0;i <= last_node;i++){
            for(auto &it:graph[i]){
                if(it.second.dr == STR_END){
                    it.second.dr = (int)v.size() - 1;
                }
            }
        }
    }

    void afis(){
        for(int i = 0;i <= last_node;i++){
            for(auto it:graph[i]){
                string tmp;
                for(int x = it.second.st;x <= it.second.dr;x++){
                    tmp += v[x];
                }
                cout << i << " " << it.second.to << " " << tmp << "\n";
            }
            cout << i << " " << _fail[i] << " FAIL\n\n\n"; 
        }
    }

    int timus_specific_task(){
        int rez = 0;
        for(int i = root;i <= last_node;i++){
            for(auto it:graph[i]){
                rez += (it.second.dr == STR_END ? (int)v.size() - 1:it.second.dr) - it.second.st + 1 - (it.second.dr == STR_END);
            }
        }
        return rez;
    }

};

SuffixTree t;

void debug(){
    //string target = "rthfdffdfdfffffdddffdgdfdfdg";
    //string target = "rthfdffdfdf";
    //string target = "abcdefabxybcdmnabcdex";
    //string target = "abcdefabxybc";
    //string target = "abcdefab";
    //string target = "abca";
    //for(auto it:target){
    //    t.add_elem(it);
    //}
    //t.add_elem(STR_CHAR);
    //t.fix_edges();
    //t.afis();
}

int main() {
    
    string a;
    cin >> a;
    for(auto it:a){
        t.add_elem(it);
    }
    t.add_elem(STR_CHAR);
    cout << t.timus_specific_task();

    return 0;
}
