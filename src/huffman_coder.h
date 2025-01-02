#pragma once


#include <cstdint>
#include <ostream>


#include "bitiostream.h"
#include "code_tree.h"

class HuffmanEncoder final{
  public:
  HuffmanEncoder(BitOutPutStream& out_put);

  void write(uint32_t symbol);

  void setcodetree(const CodeTree* code_tree);

  private:
  BitOutPutStream& m_out_put;
  const CodeTree* m_code_tree;
};