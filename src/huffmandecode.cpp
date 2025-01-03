

#include "bitiostream.h"
#include "canonicalcode.h"
#include "code_tree.h"
#include "huffman_decoder.h"

#include <cassert>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>


int main(int argc, char** argv){
  if(argc != 3){
    std::cout << "Usage" << argv[0] << "InputFile OutputFile" << std::endl;
  }

  std::string input_file_name = argv[1];
  std::string output_file_name = argv[2];

  std::ifstream in(input_file_name, std::ios::binary);
  std::ofstream out(output_file_name, std::ios::binary);
  BitInputStream bin(in);

  std::vector<uint32_t> code_lens;
  for(int i = 0; i < 257; i++){
    int b = in.get();
    if(b == std::char_traits<char>::eof()){
      break;
    }
    assert(0 <= b && b <= 256);
    code_lens.push_back(b);
  }
  CanonicalCode canonicalcode(code_lens);
  CodeTree code_tree = canonicalcode.ToCodeTree();

  HuffmanDecoder huffman_decoder(bin);
  huffman_decoder.SetCodeTree(&code_tree);

  while(true){
    int b = huffman_decoder.Read();
    // std::cout << b << std::endl;
    if(b == 256){
      break;
    }
    if(b == -1){
      break;
    }
    out.put(b);
  }
  return 0;
}