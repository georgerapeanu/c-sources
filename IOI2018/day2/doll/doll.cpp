#include "doll.h"

#include <queue>

using namespace std;

int sw[(int)4e5][2];
int trig[(int)2e5];

void create_circuit(int M, vector<int> A) {
	
	for(int i = 0;i <= M;i++){
		trig[i] = -1;
	}
	
	int N = A.size();
	int lgN = 0;
	while((1 << lgN) <= N){
		lgN++;
	}
	lgN--;
	
	int last_switch = -(lgN + 1);
	
	queue< pair<int,int> > switches;
	
	for(int i = 0;i < lgN;i++){
		
		sw[i + 1][1] = -(i + 2);
		
		if((N >> (lgN - i)) & 1){
			sw[i + 1][0] = --last_switch;
			switches.push({last_switch,lgN - i - 1});
		}
		else{
			sw[i + 1][0] = -1;
		}
	}
	
	sw[lgN + 1][1] = 0;
	if(N & 1){
		sw[lgN + 1][0] = 0;
	}
	else{
		sw[lgN + 1][0] = -1;
	}
	
	while(!switches.empty()){
		int s = switches.front().first;
		int lvl = switches.front().second;
		switches.pop();
		if(lvl != 0){
			sw[-s][0] = --last_switch;
			switches.push({last_switch,lvl - 1});
			sw[-s][1] = --last_switch;
			switches.push({last_switch,lvl - 1});
		}
		else{
			sw[-s][0] = sw[-s][1] = 0;
		}
	}
	
	
	int ind = 0;
	int node = -1;
	
	while(node != 0){
		if(sw[-node][0] == 0){
			if(ind == A.size()){
				swap(sw[-node][0],sw[-node][1]);
				node = 0;
				continue;
			}
			sw[-node][0] = A[ind++];
			swap(sw[-node][0],sw[-node][1]);
			node = -1;
		}
		else{
			swap(sw[-node][0],sw[-node][1]);
			node = sw[-node][1];
		}
	}
	
	
	vector<int> X(-last_switch),Y(-last_switch),C(M + 1);
	
	for(int i = 0;i <= M;i++){
		C[i] = trig[i];
	}
	
	
	for(int i = 0;i < -last_switch;i++){
		X[i] = sw[i + 1][0];
		Y[i] = sw[i + 1][1];
	}
	
	answer(C,X,Y);
}
