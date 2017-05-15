#include "magician.h"

#include <vector>

void initMagician(int N, int K) {
  
}

std::vector<int> findOriginalCards(std::vector<int> cards) {
  if (cards[1] - cards[0] == 1) {
    return {cards[0]};
  } else {
    return {cards[1]};
  }
}
