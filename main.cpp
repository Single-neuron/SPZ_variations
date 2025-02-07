#include <cstddef>
#include <fstream>
#include <ios>
#include <iostream>
#include <optional>
#include <string>
#include <sys/types.h>

std::size_t pow(uint base, uint pow) {
  std::size_t result{1};
  for (int i = 0; i < pow; ++i) {
    result *= base;
  }
  return result;
}

std::size_t factorial(uint x) {
  std::size_t result = 1;
  for (int i{2}; i <= x; ++i) {
    result *= i;
  }
  return result;
}

void SPZvariations(int curr_letter_amount, int curr_number_amount,
                   int max_letters, int max_numbers, std::string &SPZ,
                   std::optional<std::ofstream> &file) {
  if (curr_letter_amount < max_letters) {
    for (char i{0}; i < 26; ++i) {
      SPZ.push_back(static_cast<char>('A' + i));
      SPZvariations(curr_letter_amount + 1, curr_number_amount, max_letters,
                    max_numbers, SPZ, file);
      SPZ.pop_back();
    }
  }
  if (curr_number_amount < max_numbers) {
    for (char i{0}; i < 10; ++i) {
      SPZ.push_back('0' + i);
      SPZvariations(curr_letter_amount, curr_number_amount + 1, max_letters,
                    max_numbers, SPZ, file);
      SPZ.pop_back();
    }
  }

  if (curr_letter_amount >= max_letters && curr_number_amount >= max_numbers) {
    if (file) {
      *file << SPZ << '\n';
    } else {
      std::cout << SPZ << '\n';
    }
    return;
  }
}

int main(int argc, char **argv) {
  std::optional<std::ofstream> file{};

  if (argc < 3 || argc > 4) {
    std::cout
        << "USAGE: spz [#digits] [#letters] [(optional)file to output to]\n";
    return 1;
  } else if (argc == 4) {
    file.emplace();
    file->open(argv[3], std::ios::out);
    if (!file.value().is_open()) {
      std::cout << "failed to open file\n";
      return 1;
    }
  }

  const int max_numbers{std::stoi(argv[1])};
  const int max_letters{std::stoi(argv[2])};

  std::cout << pow(26, max_letters) * pow(10, max_numbers) *
                   factorial(max_letters + max_numbers) /
                   (factorial(max_numbers) * factorial(max_letters))
            << '\n';

  std::string SPZ{};
  long counter{0};

  std::cout << "starting\n";

  SPZvariations(0, 0, max_letters, max_numbers, SPZ, file);

  if (file) {
    file->close();
  }

  std::cout << "success\n";
  return 0;
}
