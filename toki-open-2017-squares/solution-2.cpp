#include "squares.h"

#include <algorithm>
#include <stdlib.h>
#include <vector>

const int INF = 1000000000;

long long getTotalArea(int N, std::vector<int> X, std::vector<int> Y) {
  std::vector<bool> active(N);
  std::vector<int> length(N);
  for (int i = 0; i < N; ++i) {
    X[i] *= 2;
    Y[i] *= 2;
    active[i] = true;
    length[i] = 0;
  }
  while (true) {
    std::pair<int, std::pair<int, int> > collide;
    collide = std::make_pair(INF, std::make_pair(-1, -1));
    for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
        if (!active[i] && !active[j]) {
          continue;
        }
        int dist = std::max(abs(X[i] - X[j]), abs(Y[i] - Y[j])) - length[i] - length[j];
        if (active[i] && active[j]) {
          dist /= 2;
        }
        collide = std::min(collide, std::make_pair(dist, std::make_pair(i, j)));
      }
    }
    if (collide.first == INF) {
      break;
    }
    int dist = collide.first;
    int first = collide.second.first;
    int second = collide.second.second;
    if (active[first]) {
      length[first] = dist;
      active[first] = false;
    }
    if (active[second]) {
      length[second] = dist;
      active[second] = false;
    }
  }
  long long answer = 0;
  for (int i = 0; i < N; ++i) {
    answer += (long long)length[i] * length[i];
  }
  return answer;
}
