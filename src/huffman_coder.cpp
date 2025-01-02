



#include "huffman_coder.h"
#include "code_tree.h"
#include <cstdint>




HuffmanEncoder::HuffmanEncoder(BitOutPutStream& out_put): m_out_put(out_put){}


void HuffmanEncoder::write(uint32_t symbol){
  for(char b : m_code_tree->GetCode(symbol)){
    m_out_put.write(b);
  }
}


void HuffmanEncoder::setcodetree(const CodeTree* code_tree){
  m_code_tree = code_tree;
}


