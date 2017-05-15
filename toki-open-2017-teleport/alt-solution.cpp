#include "teleport.h"

#include <algorithm>
#include <vector>

const long long INF = 3000000000000000000LL;

long long from_top[1505][1505];
long long to_bottom[1505][1505];
long long from_teleport[1505][1505];

long long getMaximumPoints(int R, int C, int K,
    std::vector<std::vector<int> > T, std::vector<std::vector<int> > P) {

  long long teleport_to_teleport = -INF;
  long long top_to_teleport = -INF;
  long long teleport_to_bottom = -INF;
  long long top_to_bottom = -INF;

  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (i == 0) {
        from_top[i][j] = P[i][j];
      } else {
        from_top[i][j] = from_top[i - 1][j];
        if (j - 1 >= 0) {
          from_top[i][j] = std::max(from_top[i][j], from_top[i - 1][j - 1]);
        }
        if (j + 1 < C) {
          from_top[i][j] = std::max(from_top[i][j], from_top[i - 1][j + 1]); 
        }
        from_top[i][j] += P[i][j];
      }
      if (T[i][j]) {
        top_to_teleport = std::max(top_to_teleport, from_top[i][j]);
      }
    }
  }
  for (int i = R - 1; i >= 0; --i) {
    for (int j = 0; j < C; ++j) {
      if (i == R - 1) {
        to_bottom[i][j] = P[i][j];
      } else {
        to_bottom[i][j] = to_bottom[i + 1][j];
        if (j - 1 >= 0) {
          to_bottom[i][j] = std::max(to_bottom[i][j], to_bottom[i + 1][j - 1]);
        }
        if (j + 1 < C) {
          to_bottom[i][j] = std::max(to_bottom[i][j], to_bottom[i + 1][j + 1]); 
        }
        to_bottom[i][j] += P[i][j];
      }
      if (T[i][j]) {
        teleport_to_bottom = std::max(teleport_to_bottom, to_bottom[i][j]);
      }
    }
  }
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      if (i == 0) {
        from_teleport[i][j] = (T[i][j] ? P[i][j] : -INF);
      } else {
        from_teleport[i][j] = from_teleport[i - 1][j];
        if (j - 1 >= 0) {
          from_teleport[i][j] = std::max(from_teleport[i][j], from_teleport[i - 1][j - 1]);
        }
        if (j + 1 < C) {
          from_teleport[i][j] = std::max(from_teleport[i][j], from_teleport[i - 1][j + 1]); 
        }
        if (T[i][j]) {
          from_teleport[i][j] = std::max(from_teleport[i][j], 0LL);
        }
        from_teleport[i][j] += P[i][j];
      }
      if (T[i][j]) {
        teleport_to_teleport = std::max(teleport_to_teleport, from_teleport[i][j]);
      }
    }
  }
  for( int j = 0; j < C; ++j) {
    top_to_bottom = std::max(top_to_bottom, from_top[R - 1][j]);
  }

  long long res = top_to_bottom;
  if (K > 0) {
    res = std::max(res, top_to_teleport + teleport_to_bottom);
    if (teleport_to_teleport > 0) {
      res = std::max(res, top_to_teleport + teleport_to_bottom + teleport_to_teleport * (K - 1));
    }
  }

  return res;
}
