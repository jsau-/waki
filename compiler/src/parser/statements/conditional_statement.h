#ifndef waki_parser_statements_conditional_statement
#define waki_parser_statements_conditional_statement

#include <memory>
#include <optional.h>
#include <tuple>

#include "../expressions/expression.h"
#include "block_statement.h"
#include "statement.h"

/**
 * Statement representing a set of conditional statements. A conditional
 * statement may be a single if block, or a sequential definition of if /
 * else if / else.
 *
 * @example
 * ```waki
 * if (true) {
 *
 * } else if (false) {
 *
 * } else if (true) {
 *
 * } else {
 *
 * };
 * ```
 */
struct ConditionalStatement : Statement {
  typedef std::tuple<std::shared_ptr<Expression>, std::shared_ptr<BlockStatement>> Conditional;

  ConditionalStatement(uint64_t line, uint64_t column, Conditional ifBlock,
                       std::vector<Conditional> elseIfBlocks = {},
                       tl::optional<Conditional> elseBlock = tl::nullopt)
    : Statement(line, column), ifBlock(ifBlock), elseIfBlocks(elseIfBlocks), elseBlock(elseBlock) {}

  virtual void acceptAstVisitor(AstVisitor &visitor) override {
    visitor.visitConditionalStatement(*this);
  };

  Conditional ifBlock;
  std::vector<Conditional> elseIfBlocks;
  tl::optional<Conditional> elseBlock;
};

#endif
