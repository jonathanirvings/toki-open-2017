#include "radius.h"
#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000
#define LOG 20

int cost1[100007], cost2[100007];
int LCA[100007][20];
int mem[100007][20];
int depth[100007];
int level[100007];
vector<int> edge[100007];
vector<int> ans;

void DFS(int pos, int par, int lev) {
	vector<int> listDepth;
	listDepth.clear();

	for (int i = 0; i < edge[pos].size(); i++) if (edge[pos][i] != par) {
		DFS(edge[pos][i], pos, lev + 1);
		listDepth.push_back(depth[edge[pos][i]]);
	}

	if (listDepth.size() > 0) sort(listDepth.begin(), listDepth.end(), greater<int>());

	for (int i = 0; i < edge[pos].size(); i++) if (edge[pos][i] != par) {
		int next = edge[pos][i];
		int tmp;

		if (listDepth[0] == depth[next]) {
			tmp = (listDepth.size() > 1 ? listDepth[1] + 1 : 0);
		} else {
			tmp = listDepth[0] + 1;
		}

		cost1[next] = tmp + INF - lev;
		cost2[next] = tmp + lev;
	}

	LCA[pos][0] = par;
	level[pos] = lev;
	depth[pos] = (listDepth.size() > 0 ? 1 + listDepth[0] : 0);
}

void DFS2(int pos, int par, int cost2par) {
	cost2[pos] = max(cost2[pos], cost2par);

	for (int i = 0; i < edge[pos].size(); i++) if (edge[pos][i] != par) {
		DFS2(edge[pos][i], pos, cost2[pos]);
	}
}

std::vector<int> getRadius(int N, int Q, std::vector<int> U, std::vector<int> V, std::vector<int> A) {
  	for (int i = 0; i < N-1; i++) {
  		edge[U[i]].push_back(V[i]);
  		edge[V[i]].push_back(U[i]);
  	}

  	for (int i = 1; i <= N; i++) {
  		cost1[i] = -1;
  		for (int j = 0; j <= LOG; j++) {
  			LCA[i][j] = -1;
  		}
  	}

  	DFS(1, -1, 0);
  	DFS2(1, -1, -1);

  	for (int i = 1; i <= N; i++) {
  		//printf("%d : (%d) %d %d\n", i, depth[i], cost1[i], cost2[i]);
  		mem[i][0] = cost1[i];
  	}

  	for (int j = 1; j <= LOG; j++) {
  		for (int i = 1; i <= N; i++) {
  			int tmp = LCA[i][j-1];
  			if (tmp != -1) {
  				LCA[i][j] = LCA[tmp][j-1];
  				mem[i][j] = mem[i][j-1];
  				if (LCA[i][j] != -1) mem[i][j] = max(mem[i][j], mem[tmp][j-1]);
  			}
  		}
  	}

  	for (int i = 0; i < Q; i++) {
  		int answer = -1;

  		int atas = (level[A[i]] - 1) / 2;
  		int tmp = A[i];

  		for (int i = LOG; i >= 0; i--) {
  			if (atas >= (1 << i)) {
  				answer = max(answer, mem[tmp][i]);
  				atas -= (1 << i);
  				tmp = LCA[tmp][i];
  			}
  		}

  		if (answer > -1) {
  			answer -= INF - level[A[i]];
  			answer += 1;
  		}

  		answer = max(answer, 1 + depth[A[i]]);
  		answer = max(answer, cost2[tmp]);
  		ans.push_back(answer);
  	}

  	return ans;
}
