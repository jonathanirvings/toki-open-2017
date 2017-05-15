#include "jump.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

const int INF = 1000000010;
const int MAX_NONZERO = 2000;

class Answers {
public:
  pair<int, int> answer1;
  pair<int, int> answer2;

  Answers() {
    answer1 = answer2 = make_pair(-INF, -INF);
  }

  Answers(pair<int, int> answer) {
    answer1 = answer;
    answer2 = make_pair(-INF, -INF);
  }

  void update(pair<int, int> answer) {
    if (answer > answer1) {
      answer2 = answer1;
      answer1 = answer;
    } else if (answer > answer2) {
      answer2 = answer;
    }
  }
};

class Interval {
public:
  vector<int> num;
  int N;
  int K;
  vector<vector<int> > dp;

  Interval(string S) {
    num.clear();
    N = S.size();
    for (int i = 0; i < N; ++i) {
      num.push_back(S[i] - '0');
    }
  }

  void init(int _K) {
    K = min(_K, N - 1);
    int max_cost = 9 * ((N + K - 1) / K);
    dp.resize(max_cost + 1);
    for (int cost = 0; cost <= max_cost; ++cost) {
      dp[cost].resize(N);
      for (int i = 0; i < N; ++i) {
        dp[cost][i] = i;
        if (i + K >= N - 1) {
          dp[cost][i] = N - 1;
        } else {
          if (i + K < N - 1 && cost >= num[i + K]) {
            dp[cost][i] = max(dp[cost][i], dp[cost - num[i + K]][i + K]);
          }
          if (i > 0) {
            dp[cost][i] = max(dp[cost][i], dp[cost][i - 1]);
          } else {
            for (int j = 1; j <= K; ++j) {
              if (cost >= num[j]) {
                dp[cost][i] = max(dp[cost][i], dp[cost - num[j]][j]);
              }
            }
          }
        }
      }
    }
  }

  int query(int l, int r) {
    int ret = 0;
    if (l + K < r) {
      int lo = 0;
      int hi = dp.size() - 1;
      while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (dp[mid][l] + K >= r) {
          ret = mid;
          hi = mid - 1;
        } else {
          lo = mid + 1;
        }
      }
    }
    return ret + num[l] + (l == r ? 0 : num[r]);
  }
};

int N;
string S;
vector<int> L;
vector<int> R;
vector<int> K;

vector<pair<int, int>> intervalRanges;
vector<Interval> intervalObjects;
vector<int> prefixFullInterval;
int intervals;

bool sortQueries(int x, int y) {
  return K[x] < K[y];
}

int queryInInterval(int intervalIndex, int l, int r) {
  return intervalObjects[intervalIndex].query(
      l - intervalRanges[intervalIndex].first,
      r - intervalRanges[intervalIndex].first);
}

void processNewK(int K) {
  prefixFullInterval.clear();
  for (int i = 0; i < intervals; ++i) {
    intervalObjects[i].init(K);
    prefixFullInterval.push_back(queryInInterval(i, intervalRanges[i].first, intervalRanges[i].second));
    if (i > 0) {
      prefixFullInterval[i] += prefixFullInterval[i - 1];
    }
  }
}

std::vector<int> getMinimumPoints(int N, int Q, std::string _S,
    std::vector<int> _L, std::vector<int> _R, std::vector<int> _K) {
  S = "0" + _S + "10";
  string now = "";
  intervals = 0;

  for (int i = 0; i < S.size(); ++i) {
    now += S[i];
    if (S[i] == '0') {
      if (now.size() > 2) {
        ++intervals;
        intervalRanges.push_back(make_pair(i - now.size() + 1, i));
        intervalObjects.push_back(Interval(now));
      }
      now = "0";
    }
  }
  L = _L;
  R = _R;
  K = _K;
  vector<int> queries, answers;
  for (int i = 0; i < Q; ++i) {
    queries.push_back(i);
    answers.push_back(-1);
  }
  sort(queries.begin(), queries.end(), sortQueries);
  for (int i = 0; i < Q; ++i) {
    if (i == 0 || K[queries[i]] != K[queries[i - 1]]) {
      processNewK(K[queries[i]]);
    }
    int l = L[queries[i]];
    int r = R[queries[i]];
    int result = 0;
    int lo = upper_bound(intervalRanges.begin(), intervalRanges.end(), make_pair(l, -INF)) - intervalRanges.begin() - 1;
    int hi = upper_bound(intervalRanges.begin(), intervalRanges.end(), make_pair(r, INF)) - intervalRanges.begin() - 1;
    if (lo >= 0) {
      if (intervalRanges[lo].second >= l) {
        result += queryInInterval(lo, l, min(intervalRanges[lo].second, r));
      }
    }
    ++lo;
    if (hi >= 0 && hi >= lo) {
      if (intervalRanges[hi].second >= r) {
        result += queryInInterval(hi, intervalRanges[hi].first, r);
        --hi;
      }
    }
    if (0 <= lo && lo <= hi) {
      result += prefixFullInterval[hi] - (lo == 0 ? 0 : prefixFullInterval[lo - 1]);
    }
    answers[queries[i]] = result;
  }
  
  return answers;
}
