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

const int N = 6000;

int nn = 0;
int compBeauty[N];
int compId[N];
int num[N], low[N];
int ans[N];
bool isAP[N];
vi beauty;
vi g[N];
vi g2[N];
stack<int> st;

int timer = -1;
void tarjan(int u, int par) {
  num[u] = low[u] = ++timer;
  st.push(u);
  for (int v : g[u]) {
    if (num[v] == -1) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] >= num[u]) {
        if (!isAP[u]) {
          isAP[u] = true;
          compId[u] = nn;
          debug printf("%d itu AP, compId = %d\n", u, compId[u]);
          compBeauty[nn] = beauty[u];
          nn++;
        }
        for (;;) {
          assert(!st.empty());
          int w = st.top();
          st.pop();
          if (isAP[w]) {
            g2[compId[w]].push_back(nn);
            g2[nn].push_back(compId[w]);
          } else {
            compId[w] = nn;
          }
          compBeauty[nn] = max(compBeauty[nn], beauty[w]);
          debug printf("%d masuk ke %d\n", w, nn);
          if (w == v) {
            break;
          }
        }
        compBeauty[nn] = max(compBeauty[nn], beauty[u]);
        g2[compId[u]].push_back(nn);
        g2[nn].push_back(compId[u]);
        nn++;
      }
    } else if (v != par) {
      low[u] = min(low[u], num[v]);
    }
  }
  debug {
    if (isAP[u]) printf("AP %d\n", u);
  }
  if (par == -1) { // root
    for (;;) {
      int w = st.top();
      st.pop();
      if (isAP[w]) {
        g2[compId[w]].push_back(nn);
        g2[nn].push_back(compId[w]);
      } else {
        compId[w] = nn;
      }
      compBeauty[nn] = max(compBeauty[nn], beauty[w]);
      debug printf("%d masuk ke %d\n", w, nn);
      if (w == u) {
        break;
      }
    }
    assert(st.empty());
    nn++;
  }
}

void dfs(int u, int par, int maxSoFar) {
  maxSoFar = max(maxSoFar, compBeauty[u]);
  ans[u] = maxSoFar;
  for (int v : g2[u]) {
    if (v != par) {
      dfs(v, u, maxSoFar);
    }
  }
}

vector<int> getMaximumBeauty(int N, int M, int Q, vector<int> beauty,
    vector<int> U, vector<int> V,
    vector<int> A, vector<int> B) {
  MINUS_ONE(U); MINUS_ONE(V);
  MINUS_ONE(A); MINUS_ONE(B);
  ::beauty = beauty;
  for (int i = 0; i < M; i++) {
    g[U[i]].push_back(V[i]);
    g[V[i]].push_back(U[i]);
  }
  fill_n(num, N, -1);
  tarjan(0, -1);
  debug {
    printf("nn = %d\n", nn);
    for (int i = 0; i < N; i++) {
      printf("compId[%d] = %d\n", i, compId[i]);
    }
    for (int i = 0; i < N; i++) {
      printf("%d: num = %d, low = %d\n", i, num[i], low[i]);
    }
  }
  vector<vi> precomp(nn, vi(nn));
  for (int i = 0; i < nn; i++) {
    dfs(i, -1, 0);
    for (int j = 0; j < nn; j++) {
      precomp[i][j] = ::ans[j];
    }
  }
  vi ans;
  for (int i = 0; i < Q; i++) {
    ans.push_back(precomp[compId[A[i]]][compId[B[i]]]);
  }
  return ans;
}
