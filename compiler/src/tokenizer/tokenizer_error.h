#ifndef waki_tokenizer_tokenizer_error
#define waki_tokenizer_tokenizer_error

#include <exception>
#include <string>

struct TokenizerError : public std::exception {
  std::string sourceText;
  size_t index;
  uint64_t line;
  uint64_t column;
  std::string errorMsg;

  TokenizerError(std::string sourceText, size_t index, uint64_t line, uint64_t column) : sourceText(sourceText), index(index), line(line), column(column) {
    auto errorStream = std::ostringstream();

    this->errorMsg = std::string("Tokenizer error at line ")
      + std::to_string(this->line)
      + std::string(", column ")
      + std::to_string(this->column)
      + std::string(". Unrecognized character '")
      + this->sourceText.substr(this->index, 1)
      + std::string("'.")
      + std::string("\n");
  };

  char const* what() const throw() {
    return this->errorMsg.c_str();
  }
};

#endif
