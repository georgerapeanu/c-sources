#include <cstdio>
#include <vector>

using namespace std;

int a[1005];
int x[1005];
int r[1005];

int main(){
	int n;
	
	scanf("%d",&n);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		r[i] = a[i] - a[i - 1];
	}
	
	vector<int> ans;
	
	for(int per = 1;per <= n;per++){
		bool ok = true;
		for(int i = per + 1;i <= n;i++){
			if(r[i - per] != r[i]){
				ok = false;
				break;
			}
		}
		if(ok){
			ans.push_back(per);
		}
	}
	
	printf("%d\n",ans.size());
	for(auto it:ans){
		printf("%d ",it);
	}
	
	return 0;
}