#include <iostream>
#include <cstdio>
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
	int in_need_of_sl;
	vector< map< int, edge_t > > sons;
	vector<int> suffix_link;
	vector<int> v;

	int new_node(){
		sons.push_back(map< int, edge_t>());
		suffix_link.push_back(root);
		return (int)suffix_link.size() - 1;
	}
	
	void fix_edges(){
		for(auto &it:sons){
			for(auto &it2:it){
				it2.second.snd_idx = (it2.second.snd_idx == CURRENT_END ? (int)v.size() - 1:it2.second.snd_idx);
			}
		}
	}
	
	void go_edge(){			
		while(active_edge.valid && active_len >= (active_edge.snd_idx == CURRENT_END ? (int)v.size() - 1:active_edge.snd_idx) - active_edge.fst_idx + 1){
			active_len -= ((active_edge.snd_idx == CURRENT_END ? (int)v.size() - 1:active_edge.snd_idx) - active_edge.fst_idx + 1);
			active_point = active_edge.to;
			active_edge = (active_len && sons[active_point].count(v[(int)v.size() - 1 - active_len]) ? sons[active_point][v[(int)v.size() - 1 - active_len]]:edge_t());
		}
	}
	
	void update_in_need(int repl){
		
		if(in_need_of_sl == repl){
				return;
		}
		
		if(in_need_of_sl != root){
			suffix_link[in_need_of_sl] = repl;
		}
		
		if(suffix_link[repl] != root){
			in_need_of_sl = root;
		}
		else{
			in_need_of_sl = repl;
		}
	}
	
	int split_active_edge(){
		int nod = new_node();
		int suff_nod = new_node();
		edge_t active_to_nod(nod,(int)v.size() - 1 - active_len,(int)v.size() - 2,1);
		edge_t nod_to_suff(suff_nod,(int)v.size() - 1,CURRENT_END,1);
		edge_t nod_to_continue = edge_t(active_edge.to,active_edge.fst_idx + active_len,active_edge.snd_idx,1);
		
		sons[active_point][v[active_to_nod.fst_idx]] = active_to_nod;
		sons[nod][v[nod_to_suff.fst_idx]] = nod_to_suff;
		sons[nod][v[nod_to_continue.fst_idx]] = nod_to_continue;
		
		return nod;
	}
	
	void add_elem(int a){
		v.push_back(a);
		reminder++;
		while(1){
			if(reminder == 0){
				return;
			}
			
			if(active_edge.valid){
				go_edge();
			}
			
			if(!active_edge.valid && sons[active_point].count(v.back())){
				active_edge = sons[active_point][v.back()];
			}
			
			
			if(!active_edge.valid){
				update_in_need(active_point);
				int nod = new_node();
				sons[active_point][v.back()] = edge_t(nod,(int)v.size() - 1,CURRENT_END,1);
				reminder--;
				active_point = suffix_link[active_point];
				continue;
			}
					
			if(v[active_edge.fst_idx + active_len] == v.back()){
				update_in_need(active_point);
				active_len++;
				go_edge();
				return ;
			}
			
			reminder--;
			

			int nod = split_active_edge();
		
			update_in_need(nod);
			
			
			if(active_point == root){
				active_len--;
				active_edge = (active_len != 0 && sons[root].count(v[active_edge.fst_idx + 1]) ? sons[root][v[active_edge.fst_idx + 1]]:edge_t());
			}
			else{
				active_point = suffix_link[active_point];
				active_edge = (active_len != 0 && sons[active_point].count(v[active_edge.fst_idx]) ? sons[active_point][v[active_edge.fst_idx]]:edge_t());
			}
		}
	}
	
	void build(vector<int> &v){
		for(int i = 0;i < (int)v.size();i++){
			add_elem(v[i]);
			update_in_need(root);
		}
		fix_edges();
	}
	
	SuffixTree(vector<int> v){
		this->root = 0;
		this->active_point = this->root;
		this->active_edge = edge_t();
		this->active_len = 0;
		this->reminder = 0;
		this->sons.push_back( map< int, edge_t >() );
		this->suffix_link.push_back(this->root);
		this->in_need_of_sl = this->root;
		
		v.push_back(END_ELEM);
		
		build(v);
	}
	
	SuffixTree(string v){
		
		this->root = 0;
		this->active_point = this->root;
		this->active_edge = edge_t();
		this->active_len = 0;
		this->reminder = 0;
		this->sons.push_back( map< int, edge_t >() );
		this->suffix_link.push_back(this->root);
		this->in_need_of_sl = this->root;
		
		vector<int> a;
		for(auto it:v){
			a.push_back((int)it);
		}
		
		 a.push_back(END_ELEM);
		
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
	
	int total_length(){
		int rez = 0;
		for(auto it:sons){
			for(auto it2:it){
				rez += it2.second.snd_idx - it2.second.fst_idx + 1 - (it2.second.snd_idx == (int)v.size() - 1);
			}
		}
		return rez;
	}
	
};
///tested on timus 1590
///TODO test timus 1393
int T;

int debug_things(){
	// // rthfdffdfdfffffdddffdgdfdfdg
	// // abcdefabxybcdmnabcdex
	 // SuffixTree T("abcdefabxybcdmnabcdex");
	// // cout << "\n";
	// // for(auto it:T.suffix_link){
		// // cout << it << " ";
	// // }
	// // cout << "\n";
	// // cout << T.active_point << " " << T.active_len << " " << T.active_edge.to << "\n";
	// T.afis();
}

void timus1590(){
	
	string  a;
	cin >> a;	
	SuffixTree T(a);
	cout << T.total_length();
}

int main(){
	
	
	return 0;
}