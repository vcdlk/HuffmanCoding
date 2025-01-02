#pragma once
#include "code_tree.h"

#include <cstdint>
#include <vector>
class CanonicalCode final{
  public:
  explicit CanonicalCode(const std::vector<uint32_t>& code_lens);
  explicit CanonicalCode(const CodeTree& tree, std::uint32_t symbol_limit);


  std::uint32_t GetSymbolLimit() const;
  std::uint32_t GetCodeLength(std::uint32_t symbol) const;
  
  CodeTree ToCodeTree() const;
  private:
  void BuildCodeLengths(const Node* node, std::uint32_t depth);

  std::vector<uint32_t> m_code_lengths;

};


