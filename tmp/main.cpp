#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

///the string must have a special character appended at the end to cause a forced flush
const int END_ELEM = -1;
///the character to be appended at the end of the string
const int CURRENT_END = -2;
///used in snd_idx in edge_t
///for generality purposes, the tree is implemented for ints

struct edge_t{
	int to;
	int fst_idx;
	int snd_idx;
	bool valid;

	edge_t(){
		to = 0;
		fst_idx = snd_idx = 0;
		valid = 0;
	}

	edge_t(int to,int fst_idx,int snd_idx,bool valid){
		this->to = to;
		this->fst_idx = fst_idx;
		this->snd_idx = snd_idx;
		this->valid = valid;
	}
};

class SuffixTree{
public:

int root;
int active_point;
edge_t active_edge;
int active_len;
int reminder;
vector< map< int, edge_t > > sons;
vector<int> suffix_link;
vector<int> v;

private:

	int new_node(){
		sons.push_back(map< int, edge_t>());
		suffix_link.push_back(0);
		return (int)suffix_link.size() - 1;
	}

	void fix_edges(int node){
		for(auto &it:sons[node]){
			if(it.second.snd_idx == CURRENT_END){
				it.second.snd_idx = (int)v.size() - 1;
			}
			fix_edges(it.second.to);
		}
	}

	void build(vector<int> &v){
		for(int i = 0;i < (int)v.size();i++){
			int it = v[i];
			reminder++;
			int prev_insert = root;
			while(1){
				if(reminder == 0){
					break;
				}

				if(!active_edge.valid){
					if(sons[active_point].count(it)){
						active_edge = sons[active_point][it];
						active_len = 1;
						if(active_edge.snd_idx == active_edge.fst_idx){
							active_len = 0;
							active_edge = edge_t();
							active_point = active_edge.to;
						}
						break;
					}
					else{
						int nod = new_node();
						sons[active_point][it] = edge_t(nod,i,CURRENT_END,1);
						active_point = suffix_link[active_point];
						active_edge = (sons[active_point].count(it) ? sons[active_point][it]:edge_t());
						reminder--;
					}
				}
				else{
					if(v[active_edge.fst_idx + active_len] != it){
						int nod = new_node();
						int alt_nod = new_node();

						edge_t to_nod = edge_t(nod,active_edge.fst_idx,i - 1,1);
						edge_t from_nod_continue = edge_t(active_edge.to,i,active_edge.snd_idx,1);
						edge_t from_nod_to_new = edge_t(alt_nod,i,CURRENT_END,1);

						sons[active_point][v[active_edge.fst_idx]] = to_nod;
						sons[nod][v[active_edge.fst_idx + active_len]] = from_nod_continue;
						sons[nod][it] = from_nod_to_new;

						if(prev_insert != root){
							suffix_link[prev_insert] = nod;
						}

						reminder--;
						edge_t tmp_edge = active_edge;
						active_point = suffix_link[active_point];
						active_edge = sons[active_point][v[active_edge.fst_idx]];

						while(active_len >= (active_edge.snd_idx == CURRENT_END ? i:active_edge.snd_idx) - active_edge.fst_idx + 1){
							active_len -= ((active_edge.snd_idx == CURRENT_END ? i:active_edge.snd_idx) - active_edge.fst_idx + 1);
							active_point = active_edge.to;
							tmp_edge.fst_idx += ((active_edge.snd_idx == CURRENT_END ? i:active_edge.snd_idx) - active_edge.fst_idx + 1);
							active_edge = sons[active_point][v[tmp_edge.fst_idx + active_len]];
						}
					}
					else{
						active_len++;
						if(active_len >= (active_edge.snd_idx == CURRENT_END ? i:active_edge.snd_idx) - active_edge.fst_idx + 1){
							active_len -= (active_edge.snd_idx == CURRENT_END ? i:active_edge.snd_idx) - active_edge.fst_idx + 1;
							active_point = active_edge.to;
							active_edge = edge_t();
						}
						break;
					}
				}
			}
		}
		fix_edges(root);
	}

public:

	SuffixTree(vector<int> v){
		this->root = 0;
		this->active_point = 0;
		this->active_edge = edge_t();
		this->active_len = 0;
		this->reminder = 0;
		this->sons.push_back( map< int, edge_t >() );
		this->suffix_link.push_back(0);

		v.push_back(END_ELEM);

		this->v = v;

		build(v);
	}

	SuffixTree(string v){

		this->root = 0;
		this->active_point = 0;
		this->active_edge = edge_t();
		this->active_len = 0;
		this->reminder = 0;
		this->sons.push_back( map< int, edge_t >() );
		this->suffix_link.push_back(0);

		vector<int> a;
		for(auto it:v){
			a.push_back((int)it);
		}

		a.push_back(END_ELEM);

		this->v = a;

		build(a);
	}

	void afis(int node = 0){
		for(auto it:sons[node]){
			cout << node << " " << it.second.to << " ";
			for(int i = it.second.fst_idx;i <= it.second.snd_idx;i++){
				cout << (char)(v[i] == -1 ? '$':v[i]);
			}
			cout << "\n";
		}

		for(auto it:sons[node]){
			afis(it.second.to);
		}
	}

};

int main(){

	SuffixTree T("abc");
	T.afis();

	return 0;
}
