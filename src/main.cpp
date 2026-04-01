#include <iostream>

#include "game.h"

using namespace rock_paper_scissors_lizard_spock;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>\n";
    return 1;
  }

  try {
    Score score = tally_from_file(argv[1]);

    std::cout << "Player 1: " << score.p1 << "\n";
    std::cout << "Player 2: " << score.p2 << "\n";

    if (score.p1 > score.p2) {
      std::cout << "Player 1 wins!\n";
    } else if (score.p2 > score.p1) {
      std::cout << "Player 2 wins!\n";
    } else {
      std::cout << "It's a tie!\n";
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
