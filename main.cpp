#include <ios>
#include <iostream>
#include <string>
#include <fstream>

void SPZvariations(int curr_letter_amount, int curr_number_amount, int max_letters,
                  int max_numbers, long& counter, std::string& SPZ, std::ofstream& file) {
  if (curr_letter_amount < max_letters) {
    for(char i{0}; i<26; ++i){
        SPZ.push_back(static_cast<char>(65+i));
        SPZvariations(curr_letter_amount+1, curr_number_amount, max_letters,
                          max_numbers, counter, SPZ, file);
        SPZ.pop_back();
    }
  }
  if (curr_number_amount < max_numbers) {
      for(char i{0}; i<10; ++i) {
          SPZ.push_back(48+i);
          SPZvariations(curr_letter_amount, curr_number_amount+1, max_letters,
                            max_numbers, counter, SPZ, file);
          SPZ.pop_back();
      }
  }

  if (curr_letter_amount >= max_letters && curr_number_amount >= max_numbers) {
      file << SPZ << '\n';
      ++counter;
      return;
  }
}

int main(int argc, char** argv){
    std::ofstream file;
    file.open("result", std::ios::out);
    if(!file.is_open()){
        std::cout << "failed to open file\n";
        return 1;
    }

    constexpr int max_letters{3};
    constexpr int max_numbers{4};
    std::string SPZ{};
    long counter{0};
    SPZvariations(0, 0, max_letters, max_numbers, counter, SPZ, file);

    file.close();

    std::cout << counter << '\n';
    return 0;
}
