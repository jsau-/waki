#ifndef waki_modules_module
#define waki_modules_module

#include <string>

struct Module {
  Module(const std::string name) : name(name) {}
  virtual ~Module(){};

  const std::string getName() const { return this->name; }

protected:
  const std::string name;
};

#endif
