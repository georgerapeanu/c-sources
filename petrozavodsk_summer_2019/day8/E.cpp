#include <bits/stdc++.h>

using namespace std;

vector<long long> toBaseK(long long value, long long k){
  if(value == 0){
    return {0};
  }
  vector<long long> answer;
  while(value){
    answer.push_back(value % k);
    value /= k;
  }
  reverse(answer.begin(), answer.end());
  return answer;
}

long long fromBaseK(const vector<long long>& value, long long k){
  long long answer = 0;
  for(auto it:value){
    answer *= k;
    answer += it;
  }
  return answer;
}

vector<long long> getBiggestBest(const long long k, const vector<long long> &low, const vector<long long> &high, bool strict){
  int bestCommonPrefix = 0;
  long long bestCommonPrefixSum = -1;
  long long prefixSum = 0;
  bool isBiggerThanLow = false;
  for(int i = 0;i < (int)high.size();i++){
    if(high[i] > 0){
      bool ok = true;
      if(isBiggerThanLow || high[i] - 1 >= low[i]){
        long long currentPrefixSum = (prefixSum) + (high[i] - 1 + (high[i] > 1 || i > 0)) + (k) * ((int)high.size() - i - 1);
 //       cerr << "debug " << i << " " << currentPrefixSum << " " << prefixSum << " " << high[i] - 1 + (high[i] > 1 || i > 0) << " " << (k) * ((int)high.size() - i - 1) << " " << strict << "\n";
        if(currentPrefixSum >= bestCommonPrefixSum + strict){
          bestCommonPrefixSum = currentPrefixSum;
          bestCommonPrefix = i;
        }
      }
    }
    prefixSum += high[i] + 1;
    isBiggerThanLow |= (high[i] > low[i]);

  }

  if(prefixSum >= bestCommonPrefixSum + strict){
    bestCommonPrefixSum = prefixSum;
    bestCommonPrefix = (int)high.size();
  }
  
  vector<long long> answer;

  for(int i = 0;i < bestCommonPrefix;i++){
    answer.push_back(high[i]);
  }
  if(bestCommonPrefix < (int)high.size()){
    answer.push_back(high[bestCommonPrefix] - 1);
  }
  for(int i = bestCommonPrefix + 1;i < (int)high.size();i++){
    answer.push_back(k - 1);
  }

  return answer;
}

/*
vector<long long> getSmallestBest(const long long k, const vector<long long> &low, const vector<long long> &high){
  int bestCommonPrefix = 0;
  long long bestCommonPrefixSum = -1;
  long long prefixSum = 0;
  bool isSmallerThanHigh = false;
  for(int i = 0;i < (int)high.size();i++){
    if(isSmallerThanHigh) {
        long long currentPrefixSum = (prefixSum - 1) + (k) * ((int)high.size() - i - 1);
        if(currentPrefixSum > bestCommonPrefixSum){
          currentPrefixSum = bestCommonPrefixSum;
          bestCommonPrefix = i;
        }
    } else if(low[i] < high[i]){
      long long currentPrefixSum = prefixSum + (high[i] - 1 + (high[i] > 1)) + (k) * ((int)low.size() - 1 - i);
      if(currentPrefixSum > bestCommonPrefixSum){
        currentPrefixSum = bestCommonPrefixSum;
        bestCommonPrefix = i;
      }
    }
    prefixSum += high[i] + 1;
    isSmallerThanHigh |= (high[i] > low[i]);

  }

  if(prefixSum > bestCommonPrefixSum){
    bestCommonPrefixSum = prefixSum;
    bestCommonPrefix = (int)high.size();
  }
  
  vector<long long> answer;

  for(int i = 0;i < bestCommonPrefix;i++){
    answer.push_back(high[i]);
  }
  if(bestCommonPrefix < (int)low.size()){
    answer.push_back(high[bestCommonPrefix] - 1);
  }
  for(int i = bestCommonPrefix + 1;i < (int)low.size();i++){
    answer.push_back(k - 1);
  }

  return answer;
}*/

int main(){
  
  int t;
  scanf("%d", &t);

  for(int test = 1;test <= t;test++){
    long long k, l, r;
    scanf("%lld %lld %lld", &k, &l, &r);
    vector<long long> low = toBaseK(l, k);
    vector<long long> high = toBaseK(r, k);
    reverse(low.begin(), low.end());
    while(low.size() < high.size()){
      low.push_back(0);
    }
    reverse(low.begin(), low.end());
    long long biggest = fromBaseK(getBiggestBest(k, low, high, false), k);
    long long smallest = fromBaseK(getBiggestBest(k, low, high, true), k);
    long long m = -2;
    for(auto it:toBaseK(biggest, k)){
      m += it + 1;
    }
    printf("Case #%d: %lld %lld %lld\n", test, m, smallest, biggest, k);
  }

  return 0;
}
