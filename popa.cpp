#include <iostream>
#include <vector>

using namespace std;

bool ask(int a,int b,int c,int d){
	cout << "0 " << a << " " << b << " " << c << " " << d << endl;
	int ans;
	cin >> ans;
	return ans;
}

void answer(int root,vector<int> &left,vector<int> &right){
	
	cout << "1\n";
	cout << root << '\n';
	
	for(auto it:left){
		cout << it << " ";
	}
	
	cout << '\n';
	
	for(auto it:right){
		cout << it << " ";
	}
	
	cout << endl;
}

int main(){
	int t;
	
	cin >> t;
	
	while(t--){
		int n;
		cin >> n;
		vector<int> left(n,-1);
		vector<int> right(n,-1);
		vector<int> t(n,-1);
		
		int root = 0;
		
		for(int i = 1;i < n;i++){
			int father = i - 1;
			
			while(father != -1 && !ask(father,i,father,father)){
				father = t[father];
			}
			
			if(father == -1){
				left[i] = root;
				t[root] = i;
				root = i;
			}
			else{
				t[i] = father;
				left[i] = right[father];
				if(left[i] != -1)t[left[i]] = i;
				right[father] = i;
			}
		}
		
		answer(root,left,right);
	}
	
	return 0;
}