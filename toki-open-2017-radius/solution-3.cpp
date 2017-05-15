#include "radius.h"

#include <vector>
#include <cstdio>
#include <iostream>
#include <assert.h>
#include <map>
#include <stack>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

vector<int> path[100005];
int ans[100005];
int is_magic[100005];
bool is_magic_magic[100005];

std::vector<int> getRadius(int N, int Q,
    std::vector<int> U, std::vector<int> V, std::vector<int> A) {
  std::vector<int> ans;
  	int magsize = 1;
  	int magtime = 0;
	for (int i=4;i<=N;i*=2){
		for (int j=0;j<magsize;j++)
			is_magic[i+j]=i;
		if (magtime++) magsize*=2, magtime=0;
	}
	is_magic[0] = 1;
	for (int i=N;i>2;i/=2){
		is_magic_magic[is_magic[i]] = 1;
	}
	for (int q:A){
		ans.push_back((is_magic[q] && is_magic_magic[is_magic[q]])?log2(N)-1:log2(N));
	}
	return ans;
}

