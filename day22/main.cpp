#include <iostream>
#include <list>
#include <regex>

#include "util.h"

std::regex newStackRegex{R"#(deal into new stack)#"};
std::regex incrementRegex{R"#(^deal with increment (\d+)$)#"};
std::regex cutRegex{R"#(^cut (-?\d+)$)#"};

class Deck : public std::list<unsigned> {
 public:
  using std::list<unsigned>::list;

  unsigned& operator[](Deck::size_type index) {
    if (index >= size()) {
      std::cerr << "invalid index " << index;
      exit(EXIT_FAILURE);
    }

    auto it = begin();
    for (Deck::size_type i = 0; i < index; i++) it++;

    return *it;
  }

  Deck::size_type getCardPosition(unsigned card) {
    auto it = begin();
    Deck::size_type position{0};

    while (*it != card) {
      position++;
      it++;
    }

    return position;
  }
};

void dealIntoNewStack(Deck& deck) { deck.reverse(); }

void increment(Deck& deck, int parameter) {
  Deck newDeck(deck.size());

  auto it = deck.begin();
  for (Deck::size_type i = 0; i < deck.size(); i++) {
    auto position = i * parameter % deck.size();
    newDeck[position] = *it;
    it++;
  }

  deck = std::move(newDeck);
}

void cut(Deck& deck, int parameter) {
  if (parameter >= 0) {
    for (int i = 0; i < parameter; i++) {
      auto card = deck.front();
      deck.pop_front();
      deck.push_back(card);
    }
  } else {
    for (int i = 0; i < abs(parameter); i++) {
      auto card = deck.back();
      deck.pop_back();
      deck.push_front(card);
    }
  }
}

void process(Deck& deck, const char* filename) {
  auto instructionsList = util::readInput(filename);

  for (const auto& instruction : instructionsList) {
    std::smatch matchResult;

    if (std::regex_match(instruction, matchResult, newStackRegex)) {
      dealIntoNewStack(deck);
    } else if (std::regex_match(instruction, matchResult, incrementRegex)) {
      auto parameter = std::stoi(matchResult[1].str());
      increment(deck, parameter);
    } else if (std::regex_match(instruction, matchResult, cutRegex)) {
      auto parameter = std::stoi(matchResult[1].str());
      cut(deck, parameter);
    } else {
      std::cerr << "instruction: " << instruction << " could not be matched"
                << std::endl;
    }
  }
}

int main() {
  Deck d1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  process(d1, "/home/rafal/Workspace/advent_of_code_2019/day22/input1.txt");
  std::cout << std::boolalpha << (d1 == Deck{0, 3, 6, 9, 2, 5, 8, 1, 4, 7})
            << std::endl;

  Deck d2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  process(d2, "/home/rafal/Workspace/advent_of_code_2019/day22/input2.txt");
  std::cout << std::boolalpha << (d2 == Deck{3, 0, 7, 4, 1, 8, 5, 2, 9, 6})
            << std::endl;

  Deck d3{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  process(d3, "/home/rafal/Workspace/advent_of_code_2019/day22/input3.txt");
  std::cout << std::boolalpha << (d3 == Deck{6, 3, 0, 7, 4, 1, 8, 5, 2, 9})
            << std::endl;

  Deck d4{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  process(d4, "/home/rafal/Workspace/advent_of_code_2019/day22/input4.txt");
  std::cout << std::boolalpha << (d4 == Deck{9, 2, 5, 8, 1, 4, 7, 0, 3, 6})
            << std::endl;

  Deck mainDeck{};
  for (unsigned i = 0; i < 10007; i++) mainDeck.push_back(i);

  process(mainDeck,
          "/home/rafal/Workspace/advent_of_code_2019/day22/main_input.txt");
  std::cout << std::boolalpha << (mainDeck.getCardPosition(2019) == 4096)
            << std::endl;

  return 0;
}
