#ifndef waki_modules_epoch
#define waki_modules_epoch

#include "function.h"

struct Epoch : public Function {
  Epoch() : Function("epoch"){};

  virtual std::string getDescription() const {
    return "The number of seconds elapsed since midnight on January 1st 1970 (UTC/GMT), not "
           "including leap seconds.";
  }

  virtual LexemeType getReturnType() const override { return LexemeType::SIGNED_INTEGER_32; }

  virtual std::vector<Identifier> getArguments() const { return {}; }
};

#endif
