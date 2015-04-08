#ifndef AST_NODE_H_
#define AST_NODE_H_

#include <cstdint>

namespace flang {

class ASTVisitor;

// Abstract syntax tree node class.
class ASTNode {
 public:
  enum ASTNodeType {
    PROGRAM_NODE, // Program node
    STMT_NODE, // Statement node
    FUNC_NODE, // Function definition node
    CLASS_NODE, // Class definition node
    BLOCK_NODE, // Code block node
    EXP_STMT_NODE, // Expression statement node
    IF_STMT_NODE, // If statement node
    WHILE_STMT_NODE, // While statement node
    EMPTY_STMT_NODE, // Empty statement node
    RETURN_STMT_NODE, // Return statement node
    EXP_NODE, // Expression node
    ASSIGNMENT_NODE, // Assignment node
    INFIX_EXP_NODE, // Infix Expression node
    PREFIX_EXP_NODE, // Prefix expression node
    PARENTHESIZED_EXP_NODE, // Parenthesized expression node
    PRIMITIVE_NODE, // Primitive node
    INTEGER_NODE, // Integer node
    STRING_NODE, // String node
    FLOAT_NODE, // Float node
    CHAR_NODE, // Char node
    BOOL_NODE, // Bool node
    NAME_NODE, // Name node
    NULL_NODE, // Null node
    SIMPLE_NAME_NODE, // Simple name node
    FUNC_INVOCATION_NODE, // Function invocation node
    QUALIFIED_NAME_NODE, // Qualified name node
  };

  ASTNode(ASTNodeType node_type, ASTNode* parent = nullptr) :
      node_type_(node_type), parent_(parent) {}

  virtual ~ASTNode() {}
  virtual void accept(ASTVisitor*) = 0;

  // NodeType's getter
  ASTNodeType nodeType() { return node_type_; }

  // Parent's accessor
  void setParent(ASTNode* parent) { parent_ = parent; }
  ASTNode* parent() { return parent_; }

  // Lineno's accessor
  void setLineno(int32_t lineno) { lineno_ = lineno; }
  int32_t lineno() { return lineno_; }

 protected:
  ASTNodeType node_type_;
  ASTNode* parent_;
  int32_t lineno_;
};

}  // namespace flang

#endif
