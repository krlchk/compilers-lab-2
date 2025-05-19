#pragma once

#include "nodes.hh"
#include "../utils/errors.hh"

namespace ast {

class Evaluator : public ConstASTIntVisitor {
public:
  int32_t visit(const IntegerLiteral& node) override;
  int32_t visit(const BinaryOperator& node) override;
  int32_t visit(const Sequence& node) override;
  int32_t visit(const IfThenElse& node) override;

  int32_t visit(const StringLiteral&) override { utils::error("Cannot evaluate string literal"); return 0; }
  int32_t visit(const Let&) override { utils::error("Cannot evaluate 'let' expression"); return 0; }
  int32_t visit(const Identifier&) override { utils::error("Cannot evaluate identifier"); return 0; }
  int32_t visit(const VarDecl&) override { utils::error("Cannot evaluate variable declaration"); return 0; }
  int32_t visit(const FunDecl&) override { utils::error("Cannot evaluate function declaration"); return 0; }
  int32_t visit(const FunCall&) override { utils::error("Cannot evaluate function call"); return 0; }
  int32_t visit(const WhileLoop&) override { utils::error("Cannot evaluate while loop"); return 0; }
  int32_t visit(const ForLoop&) override { utils::error("Cannot evaluate for loop"); return 0; }
  int32_t visit(const Break&) override { utils::error("Cannot evaluate break statement"); return 0; }
  int32_t visit(const Assign&) override { utils::error("Cannot evaluate assignment"); return 0; }
};

} // namespace ast
