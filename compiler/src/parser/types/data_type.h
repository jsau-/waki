#ifndef waki_parser_types_data_type
#define waki_parser_types_data_type

#include "../../tokenizer/lexeme_type.h"

enum class DataType {
  UNKNOWN = (int)LexemeType::UNKNOWN,
  SIGNED_INTEGER_32 = (int)LexemeType::SIGNED_INTEGER_32,
  FLOAT = (int)LexemeType::FLOAT,
  DOUBLE = (int)LexemeType::DOUBLE,
  BOOLEAN = (int)LexemeType::BOOLEAN,
  STRING = (int)LexemeType::STRING,
};

#endif
