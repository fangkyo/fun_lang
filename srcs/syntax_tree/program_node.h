#ifndef SYNTAX_TREE_PROGRAM_NODE_H_
#define SYNTAX_TREE_PROGRAM_NODE_H_

#include <boost/ptr_container/ptr_vector.hpp>

#include "syntax_tree/ast_node.h"
#include "syntax_tree/ast_visitor.h"

namespace flang {

// This class represents the program of a file, which is the root
// of a syntax tree.
class ProgramNode : public ASTNode {
 public:
  ProgramNode();
  ~ProgramNode() override {}

  void accept(ASTVisitor* visitor) override;

  //const boost::ptr_vector<ASTNode>& getChildNodes() {
    //return child_nodes_;
  //};
  void addChildNode(ASTNode* child_node);

  bool getChildNodes(ASTNodeList* child_nodes) override;

 private:
  boost::ptr_vector<ASTNode> child_nodes_;
};

} // namespace flang

#endif
