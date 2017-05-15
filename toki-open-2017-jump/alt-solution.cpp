#include "jump.h"

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

const int N = 3e5 + 50;
const int NN = 6e3 + 3;

struct Query {
  int l, r, k, idx;
};

int n, sz;
vector<vi> intervalDP[NN];
vector<pii> intervals;
vector<string> strings;
vi prefixSum;
string s;

void preprocess() {
  int i = 0;
  while (i < n) {
    if (s[i] == '0') {
      i++;
      continue;
    }
    int j = i;
    while (j < n && s[j] != '0') {
      j++;
    }
    assert(i > 0 && j < n);
    intervals.emplace_back(i - 1, j);
    strings.push_back(string(begin(s) + i - 1, begin(s) + j + 1));
    i = j;
  }
}

void build(int k) {
  prefixSum.resize(SZ(intervals));
  for (int it = 0; it < SZ(intervals); it++) {
    int l = intervals[it].fi;
    int r = intervals[it].se;
    auto &str = strings[it];
    int len = SZ(str);
    int maxCost = (9 * (r - l + 1) + k - 1) / k;
    intervalDP[it].resize(maxCost + 1);
    for (int i = 0; i <= maxCost; i++) {
      intervalDP[it][i].assign(len, -1);
    }
    auto &dp = intervalDP[it];
    for (int i = 0; i < len; i++) {
      dp[0][i] = i;
    }
    for (int c = 0; c <= maxCost; c++) {
      for (int i = 0; i < len; i++) {
        if (i > 0) {
          dp[c][i] = max(dp[c][i], dp[c][i - 1]);
        }
        if (c > 0) {
          dp[c][i] = max(dp[c][i], dp[c - 1][i]);
        }
        if (i == 0) {
          for (int kk = 1; kk < k; kk++) {
            if (i + kk >= len - 1) {
              dp[c][i] = len - 1;
              break;
            }
            if (c >= str[i + kk] - '0') {
              dp[c][i] = max(dp[c][i], dp[c - str[i + kk] + '0'][i + kk]);
            }
          }
        }
        if (i + k >= len - 1) {
          dp[c][i] = len - 1;
        } else {
          if (c >= str[i + k] - '0') {
            dp[c][i] = max(dp[c][i], dp[c - str[i + k] + '0'][i + k]);
          }
        }
      }
    }
    int lo = -1, hi = maxCost + 1;
    while (lo + 1 < hi) { 
      int mid = (lo + hi) / 2;
      if (dp[mid][0] < len - 1) {
        lo = mid;
      } else {
        hi = mid;
      }
    }
    prefixSum[it] = hi;
    if (it > 0) {
      prefixSum[it] += prefixSum[it - 1];
    }
    debug {
      printf("BUILD INTERVAL [%d, %d]\n", intervals[it].fi, intervals[it].se);
      printf("STRING = %s\n", strings[it].c_str());
      for (int c = 0; c <= maxCost; c++) {
        for (int i = 0; i < len; i++) {
          printf("dp[%d][%d] = %d\n", c, i, dp[c][i]);
        }
      }
    }
  }
}

int query(int pos, int l, int r, int k) {
  l = min(l, SZ(strings[pos]) - 1);
  r = min(r, SZ(strings[pos]) - 1);
  assert(l >= 0 && l <= r && r < SZ(strings[pos]));
  int maxCost = (9 * (r - l + 1) + k - 1) / k;
  int lo = -1, hi = maxCost + 1;
  while (lo + 1 < hi) {
    int mid = (lo + hi) / 2;
    if (intervalDP[pos][mid][l] + k < r) {
      lo = mid;
    } else {
      hi = mid;
    }
  }
  return hi + strings[pos][l] - '0' + (l != r ? strings[pos][r] - '0' : 0);
}

vector<int> getMinimumPoints(int N, int Q, string S,
    vector<int> L, vector<int> R, vector<int> K) {
  S = "010" + S + "010";
  N = SZ(S);
  n = N;
  s = S;
  for (int &k : K) {
     k = min(k, 2002);
  }
  vector<Query> queries;
  for (int i = 0; i < Q; i++) {
    queries.push_back({L[i] + 2, R[i] + 2, K[i], i});
  }
  sort(ALL(queries), [] (const Query &a, const Query &b) {
    return a.k < b.k;
  });
  preprocess();
  vi ans(Q);
  for (int i = 0, j = 0; i < Q; i = j) {
    build(queries[i].k);
    while (j < Q && queries[j].k == queries[i].k) {
      j++;
    }
    for (int k = i; k < j; k++) {
      int l = queries[k].l;
      int r = queries[k].r;
      int kk = queries[k].k;
      int idx = queries[k].idx;
      int start = upper_bound(ALL(intervals), pii(l, -1)) - begin(intervals) - 1;
      int finish = upper_bound(ALL(intervals), pii(r, -1)) - begin(intervals) - 1;
      int res = 0;
      if (start == finish) {
        res += query(start, l - intervals[start].fi, r - intervals[start].fi, kk);
      } else {
        res += query(start, l - intervals[start].fi, SZ(strings[start]) - 1, kk);
        res += query(finish, 0, r - intervals[finish].fi, kk);
        start++;
        finish--;
        if (start <= finish) {
          res += prefixSum[finish] - (start > 0 ? prefixSum[start - 1] : 0);
        }
      }
      ans[idx] = res;
    }
  }
  return ans;
}

