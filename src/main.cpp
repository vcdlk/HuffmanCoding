

#include "bitiostream.h"
#include "canonicalcode.h"
#include "code_tree.h"
#include "frequency_table.h"
#include "huffman_coder.h"

#include <cassert>
#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cout << "Usage " << argv[0] << " Inputfile Outputfile" << std::endl;
    return 0;
  }

  std::string input_file_name = argv[1];
  std::string output_file_name = argv[2];

  FrequencyTable freqs(std::vector<uint32_t>(257, 0));
  std::ifstream input_file(input_file_name, std::ios::binary);

  while (true) {
    int b = input_file.get();
    if (b == std::char_traits<char>::eof()) {
      break;
    }
    assert(0 <= b || b <= 256);
    freqs.Increment(static_cast<uint32_t>(b));
  }
  // eof ++
  freqs.Increment(256);
  CodeTree code_tree = freqs.BuildCodeTree();

  CanonicalCode canonicalcode(code_tree, freqs.GetSymbolLimit());
  code_tree = canonicalcode.ToCodeTree();

  std::ofstream out(output_file_name, std::ios::binary);
  BitOutPutStream bout(out);

  // write file head
  for (uint32_t i = 0; i < canonicalcode.GetSymbolLimit(); i++) {
    uint32_t val = canonicalcode.GetCodeLength(i);
    for (int j = 7; j >= 0; j--) {
      bout.write((val >> j) & 1);
    }
  }

  HuffmanEncoder encoder(bout);
  encoder.setcodetree(&code_tree);

  input_file.clear();
  input_file.seekg(0);

  while (true) {
    int symbol = input_file.get();
    if (symbol == std::char_traits<char>::eof())
      break;
    encoder.write(static_cast<uint32_t>(symbol));
  }
  encoder.write(256);
  bout.finish();

  return 0;
}