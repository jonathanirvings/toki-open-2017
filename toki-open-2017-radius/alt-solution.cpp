#include "radius.h"

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
const int INF = 1000000000;

class SegmentTree {
  vector<int> tree;
  int sz;

  void set(int ix, int L, int R, int pos, int val) {
    if (L == R) {
      tree[ix] = val;
      return;
    }
    int M = (L + R) >> 1;
    if (pos <= M) {
      set(ix * 2 + 1, L, M, pos, val);
    } else {
      set(ix * 2 + 2, M + 1, R, pos, val);
    }
    tree[ix] = max(tree[ix * 2 + 1], tree[ix * 2 + 2]);
  }

  int query(int ix, int L, int R, int x, int y) {
    if (x <= L && R <= y) {
      return tree[ix];
    }
    if (R < x || y < L) {
      return -INF;
    }
    int M = (L + R) >> 1;
    return max(query(ix * 2 + 1, L, M, x, y), query(ix * 2 + 2, M + 1, R, x, y));
  }

public:
  void init(int _sz) {
    sz = _sz;
    tree.resize(4 * sz);
  }

  void set(int pos, int val) {
    set(0, 0, sz - 1, pos, val);
  }

  int query(int x, int y) {
    return query(0, 0, sz - 1, x, y);
  }
};

int N, Q;
vector<int> adj[MAXN + 5];
int d[MAXN + 5], answer[MAXN + 5];
pair<int, int> maxd[MAXN + 5];
SegmentTree atas, bawah;

void update(pair<int, int> &a, int b) {
  if (b > a.first) {
    a.second = a.first;
    a.first = b;
  } else if (b > a.second) {
    a.second = b;
  }
}

void dfs(int u, int pt) {
  maxd[u] = make_pair(d[u], -INF);
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v == pt) {
      continue;
    }
    d[v] = d[u] + 1;
    dfs(v, u);
    update(maxd[u], maxd[v].first);
  }
}

void dfs2(int u, int pt) {
  bawah.set(d[u], -INF);
  for (int i = 0; i < adj[u].size(); ++i) {
    int v = adj[u][i];
    if (v == pt) {
      continue;
    }
    int max_without_v = maxd[u].first;
    if (maxd[u].first == maxd[v].first) {
      max_without_v = maxd[u].second;
    }
    atas.set(d[u], max_without_v);
    bawah.set(d[u], max_without_v - 2 * d[u]);
    dfs2(v, u);
  }
  if (pt != -1) {
    int mid = d[u] >> 1;
    int from_top = atas.query(0, mid);
    int from_bottom = d[u] + 1 + bawah.query(mid + 1, d[u]);
    int to_bottom = maxd[u].first - d[u] + 1;
    // printf("%d %d %d %d\n", u, from_top, from_bottom, to_bottom);
    answer[u] = max(max(from_top, from_bottom), to_bottom);
  }
}

std::vector<int> getRadius(int N, int Q,
    std::vector<int> U, std::vector<int> V, std::vector<int> A) {
  ::N = N;
  ::Q = Q;
  for (int i = 0; i < N - 1; ++i) {
    adj[U[i] - 1].push_back(V[i] - 1);
    adj[V[i] - 1].push_back(U[i] - 1);
  }
  atas.init(N);
  bawah.init(N);
  dfs(0, -1);
  dfs2(0, -1);
  vector<int> ans;
  for (int i = 0; i < Q; ++i) {
    ans.push_back(answer[A[i] - 1]);
  }
  return ans;
}
