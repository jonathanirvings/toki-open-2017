#include "magician.h"

#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;

int pasangan[1<<20];

void initMagician(int N, int K) {
  	for (int i=0;i<(1<<N);i++){
		if (__builtin_popcount(i)!=K) continue;
		for (int j=0;j<N;j++){
			if (i & (1<<j) || pasangan[(i + (1<<j))]) continue;
			pasangan[(i + (1<<j))] = i;
			break; 
		}
	}
}

std::vector<int> findOriginalCards(std::vector<int> cards) {
	int x = 0;
	for (int c:cards)
		x+=(1<<(c-1));
	int ans = pasangan[x];


	for (int i=0;i<cards.size();i++){
		if (ans & (1<<(cards[i]-1))) continue;
		cards.erase(cards.begin() + i);
		return cards;
 	}
  return cards;
}

