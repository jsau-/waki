#ifndef waki_parser_types_data_type
#define waki_parser_types_data_type

#include "../../tokenizer/token_type.h"

enum class DataType {
  UNKNOWN = (int)TokenType::UNKNOWN,
  SIGNED_INTEGER_32 = (int)TokenType::SIGNED_INTEGER_32,
  FLOAT = (int)TokenType::FLOAT,
  DOUBLE = (int)TokenType::DOUBLE,
  BOOLEAN = (int)TokenType::BOOLEAN,
  STRING = (int)TokenType::STRING,
};

#endif
