#ifndef waki_tokenizer_tokenizer_error
#define waki_tokenizer_tokenizer_error

#include <exception>
#include <string>
#include <sstream>

struct TokenizerError : public std::exception {
  std::string sourceText;
  size_t index;
  uint64_t line;
  uint64_t column;
  std::string errorMsg;

  TokenizerError(std::string sourceText, size_t index, uint64_t line, uint64_t column) : sourceText(sourceText), index(index), line(line), column(column) {
    auto errorStream = std::ostringstream();

    errorStream
      << "Tokenizer error at line "
      << std::to_string(this->line)
      << ", column "
      << std::to_string(this->column)
      << ". Unrecognized character '"
      << this->sourceText.substr(this->index, 1)
      << "'."
      << std::endl;

    this->errorMsg = errorStream.str();
  };

  char const* what() const throw() {
    return this->errorMsg.c_str();
  }
};

#endif
