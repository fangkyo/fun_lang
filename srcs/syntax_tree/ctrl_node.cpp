#include "syntax_tree/ctrl_node.h"

namespace flang {

IfNode::IfNode(ExpNode* test_node, ASTNode* if_node, ASTNode* else_node) {
  setTestPart(test_node);
  setIfPart(if_node);
  setElsePart(else_node);
}

IfNode::IfNode(ExpNode* test_node, ASTNode* if_node) {
  setTestPart(test_node);
  setIfPart(if_node);
}

bool IfNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(test_part_.get());
  child_nodes->push_back(if_part_.get());
  if (else_part_) {
    child_nodes->push_back(else_part_.get());
  }
  return true;
}

WhileNode::WhileNode(ExpNode* test_node, StmtNode* body_node) {
  setTestNode(test_node);
  setBodyNode(body_node);
}

bool WhileNode::getChildNodes(ASTNodeList* child_nodes) {
  child_nodes->push_back(test_node_.get());
  child_nodes->push_back(body_node_.get());
  return true;
}

}  // namespace flang
