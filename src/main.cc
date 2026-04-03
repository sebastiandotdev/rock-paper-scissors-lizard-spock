#include <iostream>

#include "game.h"
#include "ui.h"

using namespace rock_paper_scissors_lizard_spock;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    print_usage_error(argv[0]);
    return 1;
  }

  print_banner();

  try {
    const GameResult result = tally_from_file_full(argv[1]);

    if (!result.rounds.empty()) print_rounds(result.rounds);

    print_score(result.score);
    print_winner(result.score);

  } catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
