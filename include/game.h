#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <utility>

namespace rock_paper_scissors_lizard_spock {

enum class Move : uint8_t { Rock, Paper, Scissors, Lizard, Spock, Unknown };

// const char* is used over std::string_view so these arrays are truly
// constexpr on C++17 toolchains (string_view ctor isn't constexpr until
// C++20).
class MoveInfo {
 public:
  static inline constexpr std::array<const char*, 5> english = {
      "rock", "paper", "scissors", "lizard", "spock"};

  static inline constexpr std::array<const char*, 5> spanish = {
      "piedra", "papel", "tijera", "lagarto", "spock"};

  static inline constexpr std::array<std::pair<const char*, Move>, 1> synonyms =
      {std::pair<const char*, Move>{"tijeras", Move::Scissors}};

  static Move from_string(std::string_view s) noexcept;
  static std::string to_string(Move m);

 private:
  static std::string normalize_token(std::string_view s);
};

struct Score {
  int p1 = 0;
  int p2 = 0;
};

Move parse_move(std::string_view s) noexcept;

bool beats(Move a, Move b) noexcept;

Score tally_from_file(const std::string& filename);

std::string to_string(Move m);

}  // namespace rock_paper_scissors_lizard_spock
