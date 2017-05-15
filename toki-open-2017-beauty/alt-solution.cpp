#include "beauty.h"
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;
typedef struct {
	int value;
	vector<int> member, edge;
} komponen;

bool artic[200007];
int dimana[200007], level[200007], val[200007];
int lca[200007][21], mem[200007][21];
vector<int> edge[200007];
vector<komponen> comp;

bool flag[200007];
int depth[200007], low[200007], par[200007];
stack<int> S;

void DFS(int pos, int d) {
	depth[pos] = d;
	low[pos] = d;
	int numChildren = 0;

	flag[pos] = true;
	S.push(pos);

	for (int i = 0; i < edge[pos].size(); i++) {
		int next = edge[pos][i];
		if (!flag[next]) {
			numChildren++;
			par[next] = pos;
			DFS(next, d + 1);

			if (low[next] >= depth[pos] && par[pos] != -1) {
				if (!artic[pos]) {
					artic[pos] = true;
					dimana[pos] = comp.size();

					komponen tmp;
					tmp.value = val[pos];
					tmp.member.push_back(pos);
					comp.push_back(tmp);
				}

				// ADDITIONAL WOW
				komponen tmp;
				tmp.value = val[pos];
				tmp.member.push_back(pos);
				while (S.top() != next) {
					tmp.value = max(tmp.value, val[S.top()]);
					tmp.member.push_back(S.top());
					S.pop();
				}
				tmp.value = max(tmp.value, val[S.top()]);
				tmp.member.push_back(S.top());
				S.pop();
				comp.push_back(tmp);
			}

			low[pos] = min(low[pos], low[next]);
		} else if (next != par[pos]) {
			low[pos] = min(low[pos], depth[next]);
		}
	}
}

void DFS2(int pos, int d) {
	level[pos] = d;
	for (int i = 0; i < comp[pos].edge.size(); i++) {
		int next = comp[pos].edge[i];
		if (level[next] == -1) {
			lca[next][0] = pos;
			mem[next][0] = max(comp[pos].value, comp[next].value);
			DFS2(next, d+1);
		}
	}
}

PII LCA(int x, int y) {
    if (x == y) return PII(x, comp[x].value);
    
    int ans = comp[x].value;
    
    if (level[x] < level[y]) swap(x, y);
    
    for (int i = 20; i >= 0; i--) {
        if (level[x] - (1 << i) >= level[y]) {
            ans = max(ans, mem[x][i]);
            x = lca[x][i];
        }
    }
    
    if (x == y) return PII(x, ans);
    
    for (int i = 20; i >= 0; i--) {
        if (lca[x][i] != -1 && lca[x][i] != lca[y][i]) {
            ans = max(ans, max(mem[x][i], mem[y][i]));
            x = lca[x][i];
            y = lca[y][i];
        }
    }
    
    ans = max(ans, max(mem[x][0], mem[y][0]));
    return PII(lca[x][0], ans);
}

std::vector<int> getMaximumBeauty(int N, int M, int Q, std::vector<int> T,
    	std::vector<int> U, std::vector<int> V,
    	std::vector<int> A, std::vector<int> B) {
  	
  	std::vector<int> ans;

  	for (int i = 1; i <= N; i++) {
  		flag[i] = false;
  		depth[i] = -1;
  		low[i] = -1;
  		par[i] = -1;
  		val[i] = T[i-1];
  	}

  	for (int i = 0; i < M; i++) {
  		edge[U[i]].push_back(V[i]);
  		edge[V[i]].push_back(U[i]);
  	}

  	par[0] = -1;
  	edge[0].push_back(1);
  	edge[1].push_back(0);
  	DFS(0, 0);
  	
  	for (int i = 0; i < comp.size(); i++) if (comp[i].member.size() > 1) {
  		for (int j = 0; j < comp[i].member.size(); j++) {
  			int x = comp[i].member[j];
  			if (artic[x]) {
  				int dimanax = dimana[x];
  				comp[i].edge.push_back(dimanax);
  				comp[dimanax].edge.push_back(i);
  			} else {
  				dimana[x] = i;
  			}
  		}
  	}

  	/*for (int i = 0; i < comp.size(); i++) {
  		printf("Comp %d : %d\n", i, comp[i].value);
  		for (int j = 0; j < comp[i].member.size(); j++) {
  			printf("%d ", comp[i].member[j]);
  		}
  		printf("\n");
  		for (int j = 0; j < comp[i].edge.size(); j++) {
  			printf("%d ", comp[i].edge[j]);
  		}
  		printf("\n");
  	}*/

  	for (int i = 0; i < comp.size(); i++) {
  		level[i] = -1;
  		lca[i][0] = -1;
  		mem[i][0] = comp[i].value;
  	}
  	
  	DFS2(0, 0);

  	for (int j = 1; j <= 20; j++) {
        for (int i = 0; i < comp.size(); i++) {
            int tmp = lca[i][j-1];
  			if (tmp != -1) {
  				lca[i][j] = lca[tmp][j-1];
  				mem[i][j] = mem[i][j-1];
  				if (lca[i][j] != -1) mem[i][j] = max(mem[i][j], mem[tmp][j-1]);
			}
        }
    }

  	for (int i = 0; i < Q; i++) {
        int posA, posB;
        posA = dimana[A[i]];
        posB = dimana[B[i]];

        PII tmp = LCA(posA, posB);
        ans.push_back(tmp.second);
    }

  	return ans;
}
