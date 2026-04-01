#include "game.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>

namespace rock_paper_scissors_lizard_spock {
/**
 * Normalizes a token by trimming whitespace and punctuation, and converting
 * to lowercase. This allows for more flexible parsing of move names.
 */
std::string MoveInfo::normalize_token(std::string_view s) {
  std::string str(s);

  // Trim leading and trailing whitespace and common punctuation characters.
  const char* trim_chars = " \t\n\r\"'(),";
  const auto start = str.find_first_not_of(trim_chars);

  if (start == std::string::npos) return {};

  const auto end = str.find_last_not_of(trim_chars);

  std::string tok = str.substr(start, end - start + 1);
  std::transform(tok.begin(), tok.end(), tok.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });

  return tok;
}

/*
 * Converts a string representation of a move to the corresponding Move enum.
 * Returns Move::Unknown if the string does not match any known move.
 */
Move MoveInfo::from_string(std::string_view s) noexcept {
  const auto tok = normalize_token(s);
  if (tok.empty()) return Move::Unknown;

  for (size_t i = 0; i < MoveInfo::english.size(); ++i) {
    if (tok == MoveInfo::english[i] || tok == MoveInfo::spanish[i]) {
      return static_cast<Move>(i);
    }
  }

  for (const auto& p : MoveInfo::synonyms) {
    if (tok == p.first) return p.second;
  }

  return Move::Unknown;
}

/**
 * Converts a Move enum to its string representation in English.
 * The first letter is capitalized.
 */
std::string MoveInfo::to_string(Move m) {
  const auto idx = static_cast<size_t>(m);

  if (idx < MoveInfo::english.size()) {
    std::string out(MoveInfo::english[idx]);

    if (!out.empty())
      out[0] =
          static_cast<char>(std::toupper(static_cast<unsigned char>(out[0])));

    return out;
  }

  return std::string("Unknown");
}

Move parse_move(std::string_view s) noexcept {
  return MoveInfo::from_string(s);
}

bool beats(Move a, Move b) noexcept {
  switch (a) {
    case Move::Rock:
      return b == Move::Scissors || b == Move::Lizard;
    case Move::Paper:
      return b == Move::Rock || b == Move::Spock;
    case Move::Scissors:
      return b == Move::Paper || b == Move::Lizard;
    case Move::Lizard:
      return b == Move::Spock || b == Move::Paper;
    case Move::Spock:
      return b == Move::Scissors || b == Move::Rock;
    default:
      return false;
  }
}

Score tally_from_file(const std::string& filename) {
  Score score;
  std::ifstream infile(filename);

  if (!infile.is_open()) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  std::string line;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string p1_move_str, p2_move_str;

    if (!(iss >> p1_move_str >> p2_move_str)) continue;

    Move p1_move = parse_move(p1_move_str);
    Move p2_move = parse_move(p2_move_str);

    if (p1_move == Move::Unknown || p2_move == Move::Unknown) continue;

    if (beats(p1_move, p2_move)) {
      ++score.p1;
    } else if (beats(p2_move, p1_move)) {
      ++score.p2;
    }
  }
}
}  // namespace rock_paper_scissors_lizard_spock
