


#include "huffman_decoder.h"
#include "bitiostream.h"
#include "code_tree.h"



HuffmanDecoder::HuffmanDecoder(BitInputStream& input): m_bitinput(input){}

void HuffmanDecoder::SetCodeTree(const CodeTree* code_tree){
  m_code_tree = code_tree;
}

int HuffmanDecoder::Read(){
  const InternalNode* current_node = &(m_code_tree->m_root);
  while(true){
    int temp = m_bitinput.read();
    if(temp == -1){
      return -1;
    }
    const Node* temp_node;
    if(temp == 0) {
      temp_node = current_node->m_left_node.get();
    }else if(temp == 1){
      temp_node = current_node->m_right_node.get();
    }

    if(dynamic_cast<const Leaf*>(temp_node) != nullptr){
      return dynamic_cast<const Leaf*>(temp_node)->m_symbol;
    }else if(dynamic_cast<const InternalNode*>(temp_node) != nullptr){
      current_node = dynamic_cast<const InternalNode*>(temp_node);
    }
  }
}




