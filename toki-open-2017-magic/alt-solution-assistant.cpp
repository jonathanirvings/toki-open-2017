#include "assistant.h"

#include <vector>
using namespace std;

int hint[1<<20];
bool taken[1<<20];

void initAssistant(int N, int K) {
	for (int i=0;i<(1<<N);i++){
		if (__builtin_popcount(i)!=K) continue;
		for (int j=0;j<N;j++){
			if (i & (1<<j) || taken[(i + (1<<j))]) continue;
			taken[(i + (1<<j))] = 1;
			hint[i] = j + 1;
			break; 
		}
	}
}

int giveClue(std::vector<int> cards) {
	int x = 0;
	for (int c:cards)
		x+=(1<<(c-1));
  	return hint[x];
}

