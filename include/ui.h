#pragma once

#include <vector>

#include "game.h"

namespace rock_paper_scissors_lizard_spock {

void print_banner();
void print_rounds(const std::vector<RoundResult>& rounds);
void print_score(const Score& score);
void print_winner(const Score& score);
void print_usage_error(const char* program_name);

}  // namespace rock_paper_scissors_lizard_spock
