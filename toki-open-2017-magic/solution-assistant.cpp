#include "assistant.h"
#include <bits/stdc++.h>

using namespace std;

namespace assistant {
	int par[10007],pake[10007];
	vector<int> edge[10007];
	vector<int> asli, tambahan;
	bool flag[10007],flag2[10007];
	int mem[10007];

	int alter(int pos) {
		if (flag[pos]) return 0;
		flag[pos] = true;
		
		int i;
		for (i=0 ; i<edge[pos].size() ; i++) {
			flag[edge[pos][i]] = true;
			if (par[edge[pos][i]] == -1 || alter(par[edge[pos][i]])) {
				par[edge[pos][i]] = pos;
				return 1;
			}
		}

		return 0;
	}

	void initAssistant(int N, int K) {
		int i,j;

		for (i=0 ; i<=10000 ; i++) edge[i].clear();
		for (i=0 ; i<=10000 ; i++) par[i] = -1;
		for (j=0 ; j<=10000 ; j++) flag2[j] = false;
		
		for (i=0 ; i<(1 << N) ; i++) {
			if (__builtin_popcount(i) == K) asli.push_back(i);
			if (__builtin_popcount(i) == K+1) tambahan.push_back(i);
		}

		int ans = 0;

		for (i=0 ; i<asli.size() ; i++) {
			for (j=0 ; j<tambahan.size() ; j++) {
				if ((asli[i] & tambahan[j]) == asli[i]) edge[i].push_back(asli.size()+j);
			}
		}

		for (i=0 ; i<asli.size() ; i++) {
			for (j=0 ; j<=10000 ; j++) flag[j] = false;
			pake[i] = alter(i);
			ans += pake[i];
		}
		
		assert(ans == asli.size());
		/*printf("MAXFLOW IS %d\n",ans);
		
		for (i=0 ; i<tambahan.size() ; i++) {
			if (par[asli.size()+i] != -1) {
				printf("%d-%d\n",asli[par[asli.size()+i]],tambahan[i]);
			}
		}*/

		for (i=0 ; i<tambahan.size() ; i++) if (par[asli.size()+i] != -1) {
			int query = asli[par[asli.size()+i]];
			if (__builtin_popcount(query) == K) {
				int xorr = (tambahan[i] ^ query);
				for (int j = 0; j < 12; j++) {
	  				if ((1 << j) & xorr) {
	  					mem[query] = j + 1;
	  					j = 13;
	  				}
	  			}
	  		}
		}
	}

	int giveClue(std::vector<int> cards) {
	  	int i;
	  	int query = 0;
	  	for (i=0 ; i<cards.size() ; i++) {
	  		query ^= (1 << (cards[i]-1));
	  	}
	  	return mem[query];
	}
}

void initAssistant(int N, int K) {
	assistant::initAssistant(N,K);
}

int giveClue(std::vector<int> cards) {
	return assistant::giveClue(cards);
}