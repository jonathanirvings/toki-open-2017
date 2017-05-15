#include "assistant.h"

#include <vector>

namespace assistant {
  int N, K;

  int next(int x) {
    return x % N + 1;
  }

  int giveClue(std::vector<int> cards) {
    if (K == 1) {
      return next(cards[0]);
    } else {
      if (next(cards[0]) == cards[1]) {
        return next(cards[1]);
      } else if (next(cards[1]) == cards[0]) {
        return next(cards[0]);
      } else {
        if (next(next(cards[0])) != cards[1]) {
          return next(cards[0]);
        } else {
          return next(cards[1]);
        }
      }
    }
  }
}

void initAssistant(int N, int K) {
  assistant::N = N;
  assistant::K = K;
}

int giveClue(std::vector<int> cards) {
  return assistant::giveClue(cards);
}
