#pragma once

#include <cstdint>
#include <memory>
#include <vector>

class Node {
public:
  virtual ~Node() = 0; 
};

class Leaf final: public Node{
  public:
  explicit Leaf(std::uint32_t symbol);
  std::uint32_t m_symbol;
};

class InternalNode final :public Node{
  public:
  explicit InternalNode(std::unique_ptr<Node>&& left, std::unique_ptr<Node>&& right);
  std::unique_ptr<Node> m_left_node;
  std::unique_ptr<Node> m_right_node;
};


class CodeTree final{
public:
  explicit CodeTree(InternalNode&& node, std::uint64_t symbol_limit);

  void BuildCodeList(const Node* node, std::vector<char>& prefix);

  const std::vector<char>& GetCode(std::uint64_t symbol) const;
  
  InternalNode m_root;
private:

  std::vector<std::vector<char>> code_list;
};
