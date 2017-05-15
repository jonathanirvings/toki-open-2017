#include "squares.h"

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

const int N = 2e4 + 4;
const int MAXX = 4e5 + 5;

struct Point {
  int x, y;
} pnts[N * 8 * 4];

int dist(const Point &a, const Point &b) {
  return max(abs(a.x - b.x), abs(a.y - b.y));
}

struct Inner {
  map<int, set<int>> m;
  void insert(int i) { m[pnts[i].y].insert(i); }
  void erase(int i) {
    assert(m.count(pnts[i].y));
    assert(m[pnts[i].y].count(i));
    m[pnts[i].y].erase(i);
    if (SZ(m[pnts[i].y]) == 0) m.erase(pnts[i].y);
  }
  int getAny(int y1, int y2) const {
    auto it = m.lower_bound(y1);
    if (it == end(m) || it->first > y2) return -1;
    else return *it->se.begin();
  }
};

struct RangeTree {
  int n;
  vector<Inner> trees;
  RangeTree(int n) {
    this->n = 1;
    while (this->n < n) this->n *= 2;
    trees.resize(this->n * 2);
  }
  void insert(int i) {
    insert(1, 0, n - 1, pnts[i].x, i);
  }
  void insert(int x, int l, int r, int p, int i) {
    trees[x].insert(i);
    if (l != r) {
      int mid = (l + r) / 2;
      if (p <= mid) insert(2 * x, l, mid, p, i);
      else insert(2 * x + 1, mid + 1, r, p, i);
    }
  }
  void erase(int i) {
    erase(1, 0, n - 1, pnts[i].x, i);
  }
  void erase(int x, int l, int r, int p, int i) {
    trees[x].erase(i);
    if (l != r) {
      int mid = (l + r) / 2;
      if (p <= mid) erase(2 * x, l, mid, p, i);
      else erase(2 * x + 1, mid + 1, r, p, i);
    }
  }
  int getAny(int x1, int x2, int y1, int y2) const {
    return getAny(1, 0, n - 1, x1, x2, y1, y2);
  }
  int getAny(int x, int l, int r, int x1, int x2, int y1, int y2) const {
    if (l > x2 || r < x1) return -1;
    else if (l >= x1 && r <= x2) return trees[x].getAny(y1, y2);
    else {
      int mid = (l + r) / 2;
      int ret = getAny(2 * x, l, mid, x1, x2, y1, y2);
      if (ret == -1) ret = getAny(2 * x + 1, mid + 1, r, x1, x2, y1, y2);
      return ret;
    }
  }
};

int getNearest(const RangeTree &rt, int i) {
  int lo = 0, hi = MAXX;
  int ret = -1;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    int cur = rt.getAny(pnts[i].x - mid, pnts[i].x + mid, pnts[i].y - mid, pnts[i].y + mid);
    if (cur != -1) {
      ret = cur;
      hi = mid - 1;
    } else {
      lo = mid + 1;
    }
  }
  return ret;
}

int n;
int gap[N];
set<pii> pq;
set<int> adj[N];
RangeTree stuck(MAXX), notStuck(MAXX);

void updateGap(int idx, int newGap) {
  if (newGap > gap[idx]) {
    gap[idx] = newGap;
    pq.emplace(gap[idx], idx);
  }
}

long long getTotalArea(int N, std::vector<int> X, std::vector<int> Y) {
  n = N;
  for (int i = 0; i < n; i++) {
    pnts[i].x = X[i];
    pnts[i].y = Y[i];
    pnts[i].x = pnts[i].x * 2 + 100000;
    pnts[i].y = pnts[i].y * 2 + 100000;
    notStuck.insert(i);
  }
  for (int i = 0; i < n; i++) {
    notStuck.erase(i);
    int j = getNearest(notStuck, i);
    notStuck.insert(i);
    assert(j != -1);
    adj[i].insert(j);
    adj[j].insert(i);
    gap[i] = dist(pnts[i], pnts[j]);
    pq.emplace(gap[i], i);
  }
  ll ans = 0;
  while (!pq.empty()) {
    int g = pq.begin()->fi;
    int idx = pq.begin()->se;
    pq.erase(pq.begin());
    if (g != gap[idx]) {
      continue;
    }
    assert(g % 2 == 0);
    g /= 2;
    debug {
      printf("dari %d, addg = %lld\n", idx, 1LL * g * g);
    }
    ans += 1LL * g * g;
    pnts[n++] = Point{pnts[idx].x - g, pnts[idx].y - g};
    pnts[n++] = Point{pnts[idx].x - g, pnts[idx].y + g};
    pnts[n++] = Point{pnts[idx].x + g, pnts[idx].y - g};
    pnts[n++] = Point{pnts[idx].x + g, pnts[idx].y + g};
    notStuck.erase(idx);
    stuck.insert(n - 4);
    stuck.insert(n - 3);
    stuck.insert(n - 2);
    stuck.insert(n - 1);
    auto adjCopy = adj[idx];
    assert(SZ(adjCopy) <= 8);
    for (int nxtIdx : adjCopy) {
      notStuck.erase(nxtIdx);
      int nearestNotStuck = getNearest(notStuck, nxtIdx);
      int nearestStuck = getNearest(stuck, nxtIdx);
      notStuck.insert(nxtIdx);
      if (nearestStuck != -1 && nearestNotStuck != -1) {
        if (dist(pnts[nxtIdx], pnts[nearestStuck]) * 2 < dist(pnts[nxtIdx], pnts[nearestNotStuck])) {
          updateGap(nxtIdx, dist(pnts[nxtIdx], pnts[nearestStuck]) * 2);
        } else {
          adj[nearestNotStuck].insert(nxtIdx);
          adj[nxtIdx].insert(nearestNotStuck);
          updateGap(nxtIdx, dist(pnts[nxtIdx], pnts[nearestNotStuck]));
        }
      } else if (nearestStuck != -1) {
        updateGap(nxtIdx, dist(pnts[nxtIdx], pnts[nearestStuck]) * 2);
      } else if (nearestNotStuck != -1) {
          adj[nearestNotStuck].insert(nxtIdx);
          adj[nxtIdx].insert(nearestNotStuck);
        updateGap(nxtIdx, dist(pnts[nxtIdx], pnts[nearestNotStuck]));
      } else {
        assert(false);
      }
      adj[nxtIdx].erase(idx);
    }
    // adj[idx].clear();
  }
  return ans;
}

