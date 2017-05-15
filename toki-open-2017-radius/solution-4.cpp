#include "radius.h"

#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <map>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;

vector<int> path[100005];
vector<int> maxlev[100005];
int visit[100005];
int par[100005];
int depth[100005];

int dfs(int pos, int level){
	visit[pos] = 1;
  depth[pos] = level;
	for(int v: path[pos])
		if (!visit[v]){
      par[v] = pos;
			maxlev[pos].push_back(dfs(v, level + 1));
    }
  if (maxlev[pos].size() == 0)
    return 1;
  sort(maxlev[pos].begin(), maxlev[pos].end());
  reverse(maxlev[pos].begin(), maxlev[pos].end());
  return maxlev[pos][0] + 1;
}


std::vector<int> getRadius(int N, int Q,
    std::vector<int> U, std::vector<int> V, std::vector<int> A) {
  std::vector<int> ans;
  for (int i=0;i<N-1;i++){
		path[U[i] - 1].push_back(V[i] - 1);
		path[V[i] - 1].push_back(U[i] - 1);
	}
  dfs(0,0);
  for (int i=0;i<Q;i++){
    
    int res = 0;
    int pos = A[i] - 1;
    int kagi = 1;
    int prev = -1;
    while (true){
      int wow = 0;
      if (maxlev[pos].size() > 0)
        wow = maxlev[pos][0];
      
      if (wow == prev + 1 && maxlev[pos].size() > 1)
        wow = maxlev[pos][1];
      else if (wow == prev + 1)
        wow = 0;
      res = max(res, min(kagi,depth[pos]) + wow);

      if (maxlev[pos].size() > 0)
        prev = maxlev[pos][0];
      else
        prev = 0;
      
      kagi++;
      if (pos == 0)
        break;
      pos = par[pos];
    }

  	ans.push_back(res);
  }

  return ans;
}
