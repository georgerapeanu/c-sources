#include <bits/stdc++.h>
#include "islands.h"

std::mt19937 rng(20);
static int N;
static std::vector < int > p;
static int queryCount = 0;
void printVector (std::vector < int > v, std::string s = "") {
  bool needComma = 0;
  std::cout << "[";
  for (auto it : v) {
    if (needComma) std::cout << ", ";
    needComma = 1;
    std::cout << it;
  }
  std::cout << "]" << s;
}
std::vector < std::vector < int > > ask (const std::vector < std::vector < int > > &myPartition) {
  	queryCount++;
  	std::cout << "Query ";
  	for (auto v : myPartition)
    	printVector(v);
  	std::cout << "\n";

  	std::vector < std::vector < int > > ans;
  	std::vector < bool > used (N, 0);
  	for (auto v : myPartition) {
    	std::vector < int > curr;
    	for (auto e : v) {
		  	if (e < 0 || e >= N) {
		    	std::cout << "Element out of bounds\n";
		    	exit (0);
		  	}
		  	curr.push_back (p[e]);
		  	if (used[e]) {
		    	std::cout << "Not a partition\n";
		    	exit (0);
		  	}
		  	used[e] = 1;
    	}
    	ans.push_back (curr);
  	}
  	for (int i=0; i<N; i++)
    	if (!used[i]) {
      		std::cout << "Not all elements used\n";
      		exit (0);
    	}
  	for (auto &v : ans)
    	shuffle (v.begin (), v.end (), rng);
  	shuffle (ans.begin (), ans.end (), rng);
  	return ans;
}

int main () {
    std::cin >> N;
    p = std::vector< int > (N, 0);
    for(int i=0; i<N; i++)
        std::cin >> p[i];
    std::cout << "For\n";
    printVector (p, "\n");
    std::vector < int > returnedP = solve (N);
    printf ("returned:\n");
    printVector (returnedP, "\n");
    if(returnedP != p)
        std::cout << "Wrong answer!\n";
    else
        std::cout<< "OK\n";
    std::cout<<"Number of queries: "<<queryCount<<'\n';
    return 0;
}
