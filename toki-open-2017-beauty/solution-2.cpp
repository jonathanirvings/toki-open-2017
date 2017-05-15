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

//Add Edge : DinicMaxFlow.addEdge(int from, int to, F capacity)
//Solve : DinicMaxFlow.calcMaxFlow(int source, int sink)
// {{{ Dinic Max Flow<F=int>
template<typename F = int>
struct DinicMaxFlow {
  struct Edge {
    int to, rev;
    F flow, cap;
  };

  const F INF_FLOW = numeric_limits<F>::max() / 2;
  const int INF_DIST = 1e9;

  int source, sink;
  vector<vector<Edge>> graph;
  vector<int> dist, ptr;

  DinicMaxFlow(int N) : graph(N), dist(N), ptr(N) {}

  void addEdge(int from, int to, F cap) {
    if (from == to) {
      return;
    }
    Edge e1 { to, SZ(graph[to]), 0, cap };
    Edge e2 { from, SZ(graph[from]), 0, 0 };
    graph[from].push_back(e1);
    graph[to].push_back(e2);
  }

  bool buildLevelGraph() {
    fill(begin(dist), end(dist), INF_DIST);
    queue<int> q;
    dist[source] = 0;
    q.push(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (const auto &e : graph[u]) {
        if (e.flow < e.cap && dist[e.to] > dist[u] + 1) {
          dist[e.to] = dist[u] + 1;
          q.push(e.to);
        }
      }
    }
    return dist[sink] != INF_DIST;
  }

  F dfs(int u, F bottleneck) {
    if (u == sink || bottleneck == 0) {
      return bottleneck;
    }
    for (int &i = ptr[u]; i < SZ(graph[u]); i++) {
      auto &e = graph[u][i];
      auto &b = graph[e.to][e.rev];
      if (dist[e.to] != dist[u] + 1 || e.flow >= e.cap) {
        continue;
      }
      F pushed = dfs(e.to, min(e.cap - e.flow, bottleneck));
      if (pushed > 0) {
        e.flow += pushed;
        b.flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  F calcMaxFlow(const int source, const int sink) {
    this->source = source;
    this->sink = sink;
    F mf = 0;
    while (buildLevelGraph()) {
      fill(begin(ptr), end(ptr), 0);
      F pushed;
      while ((pushed = dfs(source, INF_FLOW))) {
        mf += pushed;
      }
    }
    return mf;
  }
};
// }}}

vector<int> getMaximumBeauty(int N, int M, int Q, vector<int> beauty,
    vector<int> U, vector<int> V,
    vector<int> A, vector<int> B) {
  MINUS_ONE(U); MINUS_ONE(V);
  MINUS_ONE(A); MINUS_ONE(B);
  vi ans;
  for (int it = 0; it < Q; it++) {
    int cur = -1;
    for (int mx = 0; mx < N; mx++) {
      DinicMaxFlow<> mf(2 * N + 2);
      for (int i = 0; i < M; i++) {
        mf.addEdge(2 * U[i] + 1, 2 * V[i], 1);
        mf.addEdge(2 * V[i] + 1, 2 * U[i], 1);
      }
      for (int i = 0; i < N; i++) {
        mf.addEdge(2 * i, 2 * i + 1, 1);
      }
      mf.addEdge(2 * mx, 2 * mx + 1, 1);
      mf.addEdge(2 * N, 2 * mx, 2);
      mf.addEdge(2 * A[it] + 1, 2 * N + 1, 1);
      mf.addEdge(2 * B[it] + 1, 2 * N + 1, 1);
      int maxFlow = mf.calcMaxFlow(2 * N, 2 * N + 1);
      if (maxFlow == 2) {
        cur = max(cur, beauty[mx]);
      }
    }
    ans.push_back(cur);
  }
  return ans;
}

