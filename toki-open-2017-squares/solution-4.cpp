#include "squares.h"

#include <algorithm>
#include <stack>
#include <stdlib.h>
#include <vector>

int distance(int i, int j,
             const std::vector<bool> &active,
             const std::vector<int> &length,
             const std::vector<int> &X,
             const std::vector<int> &Y) {
  int dist = std::max(abs(X[i] - X[j]), abs(Y[i] - Y[j])) - length[i] - length[j];
  if (active[i] && active[j]) {
    dist /= 2;
  }
  return dist;
}

long long getTotalArea(int N, std::vector<int> X, std::vector<int> Y) {
  std::vector<bool> active(N);
  std::vector<int> length(N);
  for (int i = 0; i < N; ++i) {
    X[i] *= 2;
    Y[i] *= 2;
    length[i] = 0;
    active[i] = true;
  }
  while (true) {
    std::stack<int> S;
    for (int i = 0; i < N; ++i) {
      if (active[i]) {
        S.push(i);
        break;
      }
    }
    if (S.empty()) {
      break;
    }
    while (!S.empty()) {
      int now = S.top(); S.pop();
      if (!active[now]) {
        continue;
      }
      int cmp = S.empty() ? -1 : S.top();
      for (int i = 0; i < N; ++i) {
        if (i == now) {
          continue;
        }
        if (cmp == -1 || distance(now, i, active, length, X, Y) < distance(now, cmp, active, length, X, Y)) {
          cmp = i;
        }
      }
      if (!active[cmp]) {
        active[now] = false;
        length[now] = distance(now, cmp, active, length, X, Y);
      } else if (!S.empty() && cmp == S.top()) {
        length[now] = length[cmp] = distance(now, cmp, active, length, X, Y);
        active[now] = active[cmp] = false;
        S.pop();
      } else {
        S.push(now);
        S.push(cmp);
      }
    }
  }
  long long area = 0;
  for (int i = 0; i < N; ++i) {
    area += (long long)length[i] * length[i];
  }
  return area;
}
