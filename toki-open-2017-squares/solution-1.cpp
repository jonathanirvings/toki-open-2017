#include "squares.h"

#include <algorithm>
#include <vector>

const int MAXPOS = 200;

long long getTotalArea(int N, std::vector<int> X, std::vector<int> Y) {
  std::vector<bool> active(N);
  std::vector<int> length(N);
  std::vector<std::vector<int>> belongs;
  belongs.resize(MAXPOS + 1);
  for (int i = 0; i <= MAXPOS; ++i) {
    belongs[i].assign(MAXPOS + 1, -1);
  }
  for (int i = 0; i < N; ++i) {
    X[i] *= 2;
    Y[i] *= 2;
    active[i] = true;
    length[i] = 0;
    belongs[X[i]][Y[i]] = i;
  }
  long long answer = 0;
  while (true) {
    bool stop = true;
    for (int i = 0; i < N; ++i) {
      if (!active[i]) {
        continue;
      }
      stop = false;
      ++length[i];
      for (int j = std::max(0, X[i] - length[i]); j <= std::min(MAXPOS, X[i] + length[i]); ++j) {
        for (int k = std::max(0, Y[i] - length[i]); k <= std::min(MAXPOS, Y[i] + length[i]); ++k) {
          if (belongs[j][k] == -1) {
            belongs[j][k] = i;
          } else if (belongs[j][k] != i) {
            int collide_with = belongs[j][k];
            if (active[i]) {
              active[i] = false;
              answer += length[i] * length[i];
            }
            if (active[collide_with]) {
              active[collide_with] = false;
              answer += length[collide_with] * length[collide_with];
            }
          }
        }
      }
    }
    if (stop) {
      break;
    }
  }

  return answer;
}
