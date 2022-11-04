#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

/*
 * format_compression_ratio
 *
 * This function will properly format _compression_ratio_ according
 * to the specifications set forth in the lab document.
 *
 * input: a double, _compression_ratio_, that is the compression ratio
 *        to format.
 * output: a std::string that contains _compression_ratio_ properly
 *         formatted according to the specifications set forth in
 *         the lab document.
 */
std::string format_compression_ratio(double compression_ratio) {
  std::stringstream formatted_ss{};
  formatted_ss << std::fixed << std::setprecision(2) << compression_ratio;
  return formatted_ss.str();
}

/*
 * data_available
 *
 * This function will determine whether there is more data to be read
 * from _file_.
 *
 * input: a std::ifstream, _file_, about which we will determine whether
 *        additional data can be read.
 * output: a bool: true if there is more data that can be read from _file_;
 *         false, otherwise.
 */
bool data_available(std::ifstream &file) {
  // std::iscntrl: Returns non-zero if the character is a control character.
  //               Flip this around logically: if the return value is 0
  //               then we know that the next character to be read is *not*
  //               a control character. 
  // EOF != file.peek(): If the next character to be read is not the end-of-file.
  return (EOF != file.peek() && 0 == std::iscntrl(file.peek()));
}

/*
 * compression_ratio_calculation
 *
 * This function will calculate and format the compression ratio when decompressing a file
 *
 * input: two double variables (deCodeLength and preCodeLength)
 * output: no return variable but it does print the formated compression ratio to the console
 */
void compression_ratio_calculation(double deCodeLength, double preCodeLength) {
  double compressionRatio = deCodeLength/preCodeLength;
  std::cout << format_compression_ratio(compressionRatio) << "\n";
}

/*
 * print_decompression
 *
 * This function will print each character from the decompression vector to the
 * console and increase the deCodeLength counter variable
 *
 * input: a vector of characters and a double counter for the decompression length
 * output: no return variable but it does print each character to the console
 */
void print_decompression(std::vector<char> decode, double& deCodeLength) {
  for(auto c : decode) {
    std::cout << c;
    ++deCodeLength;
  }
  std::cout << "\n";
}

int main() {
  std::vector<char> decode;
  int numberOfCharacters{0};
  char character{'a'};
  char character2{'a'};
  double preCodeLength{0};
  double deCodeLength{0};
  char charNumbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

  std::ifstream inputFile;
  inputFile.open("input.rle");

  if (inputFile.fail())
  {
    std::cout << "Could not open the file containing the compressed data!" << "\n";
    return 0;
  }

  while (data_available(inputFile))
  {
    inputFile >> numberOfCharacters;
    if (numberOfCharacters == 0) {
      std::cout << "Compressed data format error!" << "\n";
      return 0;
    }
    ++preCodeLength;
    if (numberOfCharacters > 9) {
      ++preCodeLength;
    }

    if(!data_available(inputFile)) {
      std::cout << "Compressed data format error!" << "\n";
      return 0;
    }

    inputFile >> character;
    if (numberOfCharacters > 10) {
      std::cout << "Compressed data format error!" << "\n";
      return 0;
    }
    ++preCodeLength;

    if (character == '-') {
      if(!data_available(inputFile)) {
        std::cout << "Compressed data format error!" << "\n";
        return 0;
      }
       
      inputFile >> character2;
      if (character2 == 0) {
        std::cout << "Compressed data format error!" << "\n";
        return 0;
      }
      ++preCodeLength;

      for (int i = 0; i < numberOfCharacters; i++)
      {
        decode.push_back(character2);
      }
    }
    else {
      for (int i = 0; i < numberOfCharacters; i++)
    {
      decode.push_back(character);
    }
    }
  }

  print_decompression(decode, deCodeLength);

  compression_ratio_calculation(deCodeLength, preCodeLength);
}