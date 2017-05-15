#include "teleport.h"

#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define ALL(a) begin(a), end(a)
#define SZ(a) ((int)(a).size())

typedef pair<int, int> pii;
typedef long long ll;

const int dc[] = {-1, 0, 1};

long long getMaximumPoints(int R, int C, int K,
    std::vector<std::vector<int> > T, std::vector<std::vector<int> > P) {
  vector<vector<ll>> toBottom(R, vector<ll>(C, LLONG_MIN / 2));
  for (int i = 0; i < C; i++) {
    toBottom[R - 1][i] = P[R - 1][i];
  }
  for (int i = R - 2; i >= 0; i--) {
    for (int j = 0; j < C; j++) {
      for (int k = -1; k <= 1; k++) {
        int ni = i + 1;
        int nj = j + k;
        if (ni < 0 || ni >= R || nj < 0 || nj >= C) {
          continue;
        }
        toBottom[i][j] = max(toBottom[i][j], toBottom[ni][nj] + P[i][j]);
      }
    }
  }
  vector<vector<ll>> toTeleport(R, vector<ll>(C, LLONG_MIN / 2));
  for (int i = R - 1; i >= 0; i--) {
    for (int j = 0; j < C; j++) {
      if (T[i][j]) {
        toTeleport[i][j] = P[i][j];
      }
      for (int k = -1; k <= 1; k++) {
        int ni = i + 1;
        int nj = j + k;
        if (ni < 0 || ni >= R || nj < 0 || nj >= C) {
          continue;
        }
        toTeleport[i][j] = max(toTeleport[i][j], toTeleport[ni][nj] + P[i][j]);
      }
    }
  }
  vector<pii> teleports;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (T[i][j]) {
        teleports.emplace_back(i, j);
      }
    }
  }
  ll topToBottom = *max_element(ALL(toBottom[0]));
  ll topToTeleport = *max_element(ALL(toTeleport[0]));
  ll teleportToBottom = LLONG_MIN;
  ll teleportToTeleport = LLONG_MIN;
  for (auto &t : teleports) {
    teleportToBottom = max(teleportToBottom, toBottom[t.fi][t.se]);
    teleportToTeleport = max(teleportToTeleport, toTeleport[t.fi][t.se]);
  }
  ll ans = topToBottom;
  if (K >= 1 && teleportToBottom > LLONG_MIN) {
    ans = max(ans, topToTeleport + teleportToBottom);
  }
  if (K >= 2 && teleportToBottom > LLONG_MIN && teleportToTeleport > LLONG_MIN) {
    ans = max(ans, topToTeleport + (K - 1) * teleportToTeleport + teleportToBottom);
  }
  return ans;
}

