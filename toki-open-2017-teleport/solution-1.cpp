#include "teleport.h"
#include <cstdio>
#include <vector>

using namespace std;

#define MINUS_INFINITY -2000000000000000000LL

int R, C, K;
vector<vector<int> > T, P;
long long mem[257][257][257];

long long DP(int x, int y, int k) {
	if (mem[x][y][k] != MINUS_INFINITY) return mem[x][y][k];
	
	long long ans = MINUS_INFINITY;

	if (x == R - 1) ans = max(ans, 0LL);
	if (x < R - 1) {
		if (y > 0) ans = max(ans, P[x+1][y-1] + DP(x+1,y-1,k));
		ans = max(ans, P[x+1][y] + DP(x+1,y,k));
		if (y < C - 1) ans = max(ans, P[x+1][y+1] + DP(x+1,y+1,k));
	}
	if (T[x][y] == 1 && k > 0) {
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (T[i][j] == 1) ans = max(ans, P[i][j] + DP(i,j,k-1));
			}
		}
	}

	return mem[x][y][k] = ans;
}

long long getMaximumPoints(int RR, int CC, int KK, vector<vector<int> > TT, vector<vector<int> > PP) {
	R = RR;
	C = CC;
	K = KK;
	T = TT;
	P = PP;
	
	long long ans = MINUS_INFINITY;

	for (int i = 0; i < R; i++) {
  		for (int j = 0; j < C; j++) {
	  		for (int k = 0; k <= K; k++) {
	  			mem[i][j][k] = MINUS_INFINITY;
	  		}
	  	}
  	}

  	for (int j = 0; j < C; j++) ans = max(ans,P[0][j] + DP(0,j,K));
  	return ans;
}
