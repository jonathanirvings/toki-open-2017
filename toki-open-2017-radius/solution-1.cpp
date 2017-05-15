#include "radius.h"

#include <vector>
#include <cstdio>
#include <iostream>
#include <assert.h>
#include <map>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;

vector<int> path[100005];
int lev[100005];
int visit[100005];

void dfs(int pos, int level){
	visit[pos] = 1;
	lev[pos] = min(lev[pos], level);
	for(int v: path[pos])
		if (!visit[v])
			dfs(v, level + 1);
}


std::vector<int> getRadius(int N, int Q,
    std::vector<int> U, std::vector<int> V, std::vector<int> A) {
  std::vector<int> ans;
  for (int i=0;i<N-1;i++){
		path[U[i] - 1].push_back(V[i] - 1);
		path[V[i] - 1].push_back(U[i] - 1);
	}

  for (int i=0;i<Q;i++){
  	for (int j=0;j<N;j++)
  		lev[j] = 999999;
  	memset(visit, 0, sizeof visit);
  	dfs(0,0);
  	memset(visit, 0, sizeof visit);
  	dfs(A[i] - 1, 1);
  	int maks = 0;
  	for (int j=0;j<N;j++)
  		maks = max(maks, lev[j]);

  	ans.push_back(maks);
  }

  return ans;
}
