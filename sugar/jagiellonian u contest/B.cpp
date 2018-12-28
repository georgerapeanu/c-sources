#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(){
	
	int z;
	scanf("%d",&z);
	
	while(z--){
		int n;
		scanf("%d",&n);
		vector<int> tmp;
		for(int i = 0;i < (1 << n) - 1;i++){
			int val;
			scanf("%d",&val);
			tmp.push_back(val);
		}
		sort(tmp.begin(),tmp.end());
		vector<int> ans;
		
		while(tmp.size()){
			queue<int> scoate;
			vector<int> nv;
			
			int mn_val = tmp[0];
			
			for(int i = 1;i < (int)tmp.size();i++){
				if(scoate.size() && scoate.front() < tmp[i]){
					goto failed;
				}
				else if(scoate.size() && scoate.front() == tmp[i]){
					scoate.pop();
					continue;
				}
				nv.push_back(tmp[i]);
				scoate.push(tmp[i] + mn_val);
			}
			if(scoate.size()){
				goto failed;
			}
			tmp = nv;
			ans.push_back(mn_val);
		}
		
		for(int i = 0;i < (int)ans.size();i++){
			printf("%d",ans[i]);
			if(i != (int)ans.size() - 1){
				printf(" ");
			}
		}

		printf("\n");

		goto ending;
		
		failed:
		
			printf("NO");
			printf("\n");
	
		goto ending;
		ending:;
	}
	
	return 0;
}