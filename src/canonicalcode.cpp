#include "canonicalcode.h"
#include "code_tree.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

CanonicalCode::CanonicalCode(const std::vector<uint32_t> &code_lens) {
  m_code_lengths = code_lens;
}

CanonicalCode::CanonicalCode(const CodeTree &tree, std::uint32_t symbol_limit) {
  if (symbol_limit < 2) {
    throw std::invalid_argument("At least 2 symbols needed");
  }

  m_code_lengths = std::vector<uint32_t>(symbol_limit, 0);
  BuildCodeLengths(&tree.m_root, 0);
}

void CanonicalCode::BuildCodeLengths(const Node *node, uint32_t depth) {
  if (dynamic_cast<const InternalNode *>(node) != nullptr) {
    const InternalNode *internalnode = dynamic_cast<const InternalNode *>(node);
    BuildCodeLengths(internalnode->m_left_node.get(), depth + 1);
    BuildCodeLengths(internalnode->m_right_node.get(), depth + 1);
  } else if (dynamic_cast<const Leaf *>(node) != nullptr) {
    uint32_t symbol = dynamic_cast<const Leaf *>(node)->m_symbol;
    m_code_lengths.at(symbol) = depth;
  }
}

CodeTree CanonicalCode::ToCodeTree() const {

  std::vector<std::unique_ptr<Node>> nodes;
  uint32_t max_deep =
      *std::max_element(m_code_lengths.cbegin(), m_code_lengths.cend());
  std::cout << "ToCodeTree 1:" << max_deep << std::endl;
  for (uint32_t i = max_deep; ; i--) {
    std::vector<std::unique_ptr<Node>> temp_nodes;
    if(i > 0){
    size_t j = 0;
    for (const auto &item : m_code_lengths) {
      if (i == item) {
        temp_nodes.push_back(std::unique_ptr<Node>(new Leaf(j)));
      }
      j++;
    }
    }

    std::cout << "ToCodeTree nodes.size:" << nodes.size() << std::endl;
    for (size_t j = 0; j < nodes.size(); j = j + 2) {
      temp_nodes.push_back(std::unique_ptr<InternalNode>(new InternalNode(
          std::move(nodes.at(j)), std::move(nodes.at(j + 1)))));
    }

    nodes = std::move(temp_nodes);
    if(i == 0){
      break;
    }
  }
  std::cout << "ToCodeTree 2:" << max_deep << std::endl;

  std::cout << "ToCodeTree nodes size:" << nodes.size() << std::endl;


  Node *temp = nodes.front().release();
  InternalNode *root = dynamic_cast<InternalNode *>(temp);

  CodeTree result(std::move(*root),
                  static_cast<uint32_t>(m_code_lengths.size()));
  delete root;

  return result;
}

std::uint32_t CanonicalCode::GetCodeLength(std::uint32_t symbol) const {
  return m_code_lengths.at(symbol);
}

std::uint32_t CanonicalCode::GetSymbolLimit() const {
  return static_cast<uint32_t>(m_code_lengths.size());
}