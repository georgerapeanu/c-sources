#include <cstdio>
#include <vector>

using namespace std;

int n;

int a[505];
int d[505];
vector<int> lant;
bool in[505];
int wh[505];

int main(){
	scanf("%d",&n);
	for(int i = 1;i <= n;i++){
		scanf("%d",&a[i]);
		if(a[i] >= 2){
			lant.push_back(i);
			in[i] = 1;
		}
	}
	
	for(int i = 0;i < (int)lant.size();i++){
		d[lant[i]] = (i != 0) + ( i != (int)lant.size() - 1);
	}
	
	if(lant.empty()){
		printf("NO");
		return 0;
	}
	
	int last = 0,num = lant.size();;
	
	for(int i = 1;i <= n;i++){
		if(!in[i]){
			if(d[lant[0]] < 2){
				d[lant[0]]++;num++;
				wh[i] = lant[0];
			}
			else if(d[lant.back()] < 2){
				d[lant.back()]++;num++;
				wh[i] = lant.back();
			}
			else{
				while(last < (int)lant.size() && d[lant[last]] >= a[lant[last]]){
					last++;
				}
				
				if(last == (int)lant.size()){
					printf("NO");
					return 0;
				}
				
				d[lant[last]]++;
				wh[i] = lant[last];
			}
		}
	}
	
	printf("YES %d\n",num - 1);
	printf("%d\n",n - 1);
	
	
	for(int i = 1;i <= n;i++){
		if(!in[i]){
			printf("%d %d\n",wh[i],i);
		}
	}
	
	for(int i = 1;i < (int)lant.size();i++){
		printf("%d %d\n",lant[i],lant[i - 1]);
	}
	
	return 0;
}