#include "ui.h"

#include <iostream>
#include <string>

namespace rock_paper_scissors_lizard_spock {

namespace {

namespace ansi {
constexpr const char* reset = "\033[0m";
constexpr const char* bold = "\033[1m";
constexpr const char* red = "\033[91m";
constexpr const char* green = "\033[92m";
constexpr const char* yellow = "\033[93m";
constexpr const char* blue = "\033[94m";
constexpr const char* magenta = "\033[95m";
constexpr const char* cyan = "\033[96m";
constexpr const char* white = "\033[97m";
constexpr const char* gray = "\033[90m";
}  // namespace ansi

const char* move_color(Move m) {
  switch (m) {
    case Move::Rock:
      return ansi::yellow;
    case Move::Paper:
      return ansi::blue;
    case Move::Scissors:
      return ansi::red;
    case Move::Lizard:
      return ansi::green;
    case Move::Spock:
      return ansi::cyan;
    default:
      return ansi::white;
  }
}

std::string pad_r(const std::string& s, size_t w) {
  return s.size() >= w ? s.substr(0, w) : s + std::string(w - s.size(), ' ');
}

std::string pad_l(int n, size_t w) {
  std::string s = std::to_string(n);
  return s.size() >= w ? s : std::string(w - s.size(), ' ') + s;
}

}  // namespace

void print_banner() {
  std::cout << "\n"
            << ansi::bold << ansi::cyan
            << "  ╔═════════════════════════════════════════════╗\n"
            << "  ║   Rock · Paper · Scissors · Lizard · Spock  ║\n"
            << "  ╚═════════════════════════════════════════════╝\n"
            << ansi::reset << "\n";
}

void print_rounds(const std::vector<RoundResult>& rounds) {
  const int n = static_cast<int>(rounds.size());

  std::cout << "  " << ansi::bold << ansi::white
            << "Rounds played: " << ansi::yellow << n << ansi::reset << "\n\n";

  std::cout << ansi::gray
            << "  ┌──────┬────────────┬────────────┬────────────┐\n"
            << "  │  #   │  Player 1  │  Player 2  │  Result    │\n"
            << "  ├──────┼────────────┼────────────┼────────────┤\n"
            << ansi::reset;

  for (int i = 0; i < n; ++i) {
    const auto& r = rounds[i];
    const std::string p1 = pad_r(MoveInfo::to_string(r.p1_move), 8);
    const std::string p2 = pad_r(MoveInfo::to_string(r.p2_move), 8);

    const char* res_color;
    const char* res_text;
    if (r.winner == 1) {
      res_color = ansi::green;
      res_text = "P1 wins!";
    } else if (r.winner == 2) {
      res_color = ansi::magenta;
      res_text = "P2 wins!";
    } else {
      res_color = ansi::yellow;
      res_text = "  Tie!  ";
    }

    std::cout << ansi::gray << "  │" << ansi::reset << "  " << ansi::bold
              << pad_l(i + 1, 2) << ansi::reset << "  " << ansi::gray << "│"
              << ansi::reset << "  " << move_color(r.p1_move) << p1
              << ansi::reset << "  " << ansi::gray << "│" << ansi::reset << "  "
              << move_color(r.p2_move) << p2 << ansi::reset << "  "
              << ansi::gray << "│" << ansi::reset << "  " << res_color
              << ansi::bold << res_text << ansi::reset << "  " << ansi::gray
              << "│\n"
              << ansi::reset;
  }

  std::cout << ansi::gray
            << "  └──────┴────────────┴────────────┴────────────┘\n"
            << ansi::reset << "\n";
}

void print_score(const Score& s) {
  const std::string score_str =
      std::to_string(s.p1) + " : " + std::to_string(s.p2);
  const int score_len = static_cast<int>(score_str.size());
  const int side_inner = 3 + 8 + 3;  // "   Player X   "
  const int pad_total = 45 - side_inner * 2 - score_len;
  const int pad_l_val = pad_total / 2;
  const int pad_r_val = pad_total - pad_l_val;

  std::cout << ansi::gray
            << "  ╔═════════════════════════════════════════════╗\n"
            << "  ║" << ansi::reset << "                 " << ansi::bold
            << ansi::white << "FINAL SCORE" << ansi::reset
            << "                 " << ansi::gray << "║\n"
            << ansi::reset << ansi::gray
            << "  ╠═════════════════════════════════════════════╣\n"
            << "  ║" << ansi::reset << "   " << ansi::bold << ansi::blue
            << "Player 1" << ansi::reset << "   " << std::string(pad_l_val, ' ')
            << ansi::bold << ansi::white << score_str << ansi::reset
            << std::string(pad_r_val, ' ') << "   " << ansi::bold
            << ansi::magenta << "Player 2" << ansi::reset << "   " << ansi::gray
            << "║\n"
            << ansi::reset << ansi::gray
            << "  ╚═════════════════════════════════════════════╝\n"
            << ansi::reset << "\n";
}

void print_winner(const Score& s) {
  if (s.p1 > s.p2) {
    std::cout << ansi::bold << ansi::green << "  \U0001F3C6  PLAYER 1 WINS!\n"
              << ansi::reset;
  } else if (s.p2 > s.p1) {
    std::cout << ansi::bold << ansi::green << "  \U0001F3C6  PLAYER 2 WINS!\n"
              << ansi::reset;
  } else {
    std::cout << ansi::bold << ansi::yellow << "  \U0001F91D  IT'S A TIE!\n"
              << ansi::reset;
  }
  std::cout << "\n";
}

void print_usage_error(const char* program_name) {
  std::cerr << ansi::red << ansi::bold << "  Error: " << ansi::reset
            << "Usage: " << program_name << " <input_file>\n";
}

}  // namespace rock_paper_scissors_lizard_spock
