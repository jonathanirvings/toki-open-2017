#include "assistant.h"

#include <vector>

int N;

void initAssistant(int _N, int K) {
  N = _N;
}

int giveClue(std::vector<int> cards) {
  return cards[0] % N + 1;
}
