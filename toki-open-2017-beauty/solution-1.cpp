#include "beauty.h"

#include <bits/stdc++.h>
using namespace std;

#define mt make_tuple
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define ALL(a) begin(a), end(a)
#define SZ(a) ((int)(a).size())

#ifdef __DEBUG
#define debug if (true)
#else
#define debug if (false)
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define MINUS_ONE(v) ({for (int &i : v) i--; })

const int N = 15;

bool dp[1 << N][N];

vector<int> getMaximumBeauty(int N, int M, int Q, vector<int> beauty,
    vector<int> U, vector<int> V,
    vector<int> A, vector<int> B) {
  MINUS_ONE(U); MINUS_ONE(V);
  MINUS_ONE(A); MINUS_ONE(B);
  vector<vi> g(N);
  for (int i = 0; i < M; i++) {
    g[U[i]].push_back(V[i]);
    g[V[i]].push_back(U[i]);
  }
  vi maxB(1 << N);
  for (int i = 0; i < N; i++) {
    maxB[1 << i] = beauty[i];
  }
  for (int i = 1; i < (1 << N); i++) {
    maxB[i] = max(maxB[i ^ (i & -i)], maxB[i & -i]);
  }
  vi ans;
  for (int it = 0; it < Q; it++) {
    memset(dp, 0, sizeof(dp));
    dp[1 << A[it]][A[it]] = true;
    for (int i = 0; i < (1 << N); i++) {
      for (int j = 0; j < N; j++) {
        if (dp[i][j]) {
          for (int k : g[j]) {
            if ((i & (1 << k)) == 0) {
              dp[i | (1 << k)][k] = true;
            }
          }
        }
      }
    }
    int cur = -1;
    for (int i = 0; i < (1 << N); i++) {
      if ((i & (1 << A[it])) && (i & (1 << B[it])) && dp[i][B[it]]) {
        cur = max(cur, maxB[i]);
      }
    }
    ans.push_back(cur);
  }
  return ans;
}

