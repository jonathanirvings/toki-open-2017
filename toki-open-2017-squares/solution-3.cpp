#include "squares.h"

#include <algorithm>
#include <stdlib.h>
#include <vector>

const int MAX_DISTANCE = 200000;

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
  std::vector<std::vector<std::pair<int, int>>> distances(MAX_DISTANCE + 1);
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      int dist = distance(i, j, active, length, X, Y);
      distances[dist].push_back(std::make_pair(i, j));
    }
  }
  for (int dist = 1; dist < distances.size(); ++dist) {
    while (distances[dist].size() > 0) {
      int first = distances[dist].back().first;
      int second = distances[dist].back().second;
      distances[dist].pop_back();
      if (distance(first, second, active, length, X, Y) != dist) {
        continue;
      }
      if (active[first]) {
        active[first] = false;
        length[first] = dist;
        for (int i = 0; i < N; ++i) {
          if (i == second || !active[i]) {
            continue;
          }
          int dist = distance(first, i, active, length, X, Y);
          distances[dist].push_back(std::make_pair(first, i));
        }
      }
      if (active[second]) {
        active[second] = false;
        length[second] = dist;
        for (int i = 0; i < N; ++i) {
          if (i == first || !active[i]) {
            continue;
          }
          int dist = distance(second, i, active, length, X, Y);
          distances[dist].push_back(std::make_pair(second, i));
        }
      }
    }
  }
  long long area = 0;
  for (int i = 0; i < N; ++i) {
    area += (long long)length[i] * length[i];
  }
  return area;
}
