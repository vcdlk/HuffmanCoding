#pragma once

#include "bitiostream.h"
#include "code_tree.h"



class HuffmanDecoder final{
  public:
  explicit HuffmanDecoder(BitInputStream& input);

  void SetCodeTree(const CodeTree* code_tree);

  int Read();

  private:
  BitInputStream m_bitinput;
  const CodeTree* m_code_tree;
};
