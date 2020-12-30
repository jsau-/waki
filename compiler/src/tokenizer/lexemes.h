#ifndef waki_tokenizer_lexemes
#define waki_tokenizer_lexemes

#include <map>

#include "lexeme_flags.h"
#include "lexeme_metadata.h"
#include "lexeme_type.h"

struct Lexemes {
  static std::map<LexemeType, LexemeMetadata> metadata;
};

#endif
