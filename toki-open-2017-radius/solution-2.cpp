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


std::vector<int> getRadius(int N, int Q,
    std::vector<int> U, std::vector<int> V, std::vector<int> A) {
  std::vector<int> ans;
  int dep = N;
  for (int i=0;i<N;i++){
    lev[i] = max(dep, (N - dep + 1) / 2);
    dep--;
  }
  for (int i=0;i<Q;i++){
  	ans.push_back(lev[A[i] - 1]);
  }

  return ans;
}
