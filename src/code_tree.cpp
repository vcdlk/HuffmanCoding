#include "code_tree.h"

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>


Node::~Node() {}

Leaf::Leaf(std::uint32_t symbol) : m_symbol(symbol) {}

InternalNode::InternalNode(std::unique_ptr<Node> &&left, std::unique_ptr<Node> &&right)
    : m_left_node(std::move(left)), m_right_node(std::move(right)) {}

CodeTree::CodeTree(InternalNode&& node, uint64_t symbol_limit):m_root(std::move(node)){
  if(symbol_limit < 2 || symbol_limit > SIZE_MAX){
    throw std::domain_error("At least 2 symbols needed");
  }
  code_list = std::vector<std::vector<char>> (symbol_limit, std::vector<char>());

  std::vector<char> prefix;
  BuildCodeList(&m_root, prefix);
}

void CodeTree::BuildCodeList(const Node* node, std::vector<char>& prefix){
  if(dynamic_cast<const InternalNode*>(node) != nullptr){
    const InternalNode* internal_node = dynamic_cast<const InternalNode*>(node);

    prefix.push_back(0);
    BuildCodeList(internal_node->m_left_node.get(), prefix);
    prefix.pop_back();

    prefix.push_back(1);
    BuildCodeList(internal_node->m_right_node.get(), prefix);
    prefix.pop_back();
  }else if(dynamic_cast<const Leaf*>(node) != nullptr){
    const Leaf* leaf_node = dynamic_cast<const Leaf*>(node);
    code_list[leaf_node->m_symbol] = prefix;
  }
  return;
}

const std::vector<char>& CodeTree::GetCode(std::uint64_t symbol)const {
  if(!code_list.at(symbol).empty()){
    return code_list.at(symbol);
  }else{
    throw std::logic_error("Assertion error: Illegal node type");
  }
}
