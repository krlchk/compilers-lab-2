#include "evaluator.hh"

namespace ast {

int32_t Evaluator::visit(const IntegerLiteral& node) {
  return node.value;
}

int32_t Evaluator::visit(const BinaryOperator& node) {
  int32_t lhs = node.get_left().accept(*this);
  int32_t rhs = node.get_right().accept(*this);

  switch (node.op) {
    case o_plus: return lhs + rhs;
    case o_minus: return lhs - rhs;
    case o_times: return lhs * rhs;
    case o_divide:
      if (rhs == 0)
        utils::error("Division by zero");
      return lhs / rhs;

    case o_eq:  return lhs == rhs ? 1 : 0;
    case o_neq: return lhs != rhs ? 1 : 0;
    case o_lt:  return lhs < rhs ? 1 : 0;
    case o_le:  return lhs <= rhs ? 1 : 0;
    case o_gt:  return lhs > rhs ? 1 : 0;
    case o_ge:  return lhs >= rhs ? 1 : 0;

    default:
      utils::error("Unsupported binary operator");
      return 0;
  }
}

int32_t Evaluator::visit(const Sequence& node) {
  const auto& exprs = node.get_exprs();
  if (exprs.empty()) {
    utils::error("Cannot evaluate empty sequence");
  }

  int32_t result = 0;
  for (const auto& expr : exprs) {
    result = expr->accept(*this);
  }
  return result;
}

int32_t Evaluator::visit(const IfThenElse& node) {
  int32_t condition = node.get_condition().accept(*this);
  if (condition != 0) {
    return node.get_then_part().accept(*this);
  } else {
    return node.get_else_part().accept(*this);
  }
}

} // namespace ast
