#pragma once

#include "code_tree.h"

#include <cstdint>
#include <memory>
#include <queue>
#include <vector>


class FrequencyTable final{
  public:
  FrequencyTable(std::vector<uint32_t> base_frequency): m_freq_table(base_frequency){}

  uint64_t Get(uint32_t symbol);

  int Increment(uint32_t symbol);

  CodeTree BuildCodeTree()const;

  uint32_t GetSymbolLimit()const;

  class NodeWithFreq{
    public:
    explicit NodeWithFreq(Node* node, uint32_t symbol, uint64_t freq);
    std::unique_ptr<Node> m_node;
    uint32_t m_lowest_symbol;
    uint64_t m_frequency;

    bool operator<(const NodeWithFreq& other) const;
  };

  private:
  std::vector<uint32_t> m_freq_table;

  static NodeWithFreq PopQueue(std::priority_queue<NodeWithFreq>& pop_queue);
};

