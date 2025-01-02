#include "frequency_table.h"
#include "code_tree.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <queue>
#include <stdexcept>
#include <vector>
#include <iostream>

uint64_t FrequencyTable::Get(uint32_t symbol) {
  if (symbol < m_freq_table.size()) {
    return m_freq_table.at(symbol);
  } else {
    return 0;
  }
}

int FrequencyTable::Increment(uint32_t symbol) {
  assert(m_freq_table[symbol] < UINT32_MAX);
  m_freq_table[symbol]++;
  return 0;
}

CodeTree FrequencyTable::BuildCodeTree() const {
  std::priority_queue<NodeWithFreq> pqueue;


  for(size_t i = 0; i < m_freq_table.size(); i++){
    const auto& freq = m_freq_table.at(i);
    if(freq > 0){
      pqueue.push(NodeWithFreq(new Leaf(i), i, freq));
    }
  }

  // atleast 3 characters
  if(pqueue.size() <= 2){
    for(size_t i = 0; i < m_freq_table.size(); i++){
      const auto& freq = m_freq_table.at(i);
      if(freq == 0){
        pqueue.push(NodeWithFreq(new Leaf(i), i, freq));
      }
      if(pqueue.size() > 2){
        break;
      }
    }
  }

  assert(pqueue.size() >= 2);

  while (pqueue.size() > 1) {
    NodeWithFreq x = PopQueue(pqueue);
    NodeWithFreq y = PopQueue(pqueue);
    pqueue.push(
        NodeWithFreq(new InternalNode(std::move(x.m_node), std::move(y.m_node)),
                     std::min(x.m_lowest_symbol, y.m_lowest_symbol),
                     x.m_frequency + y.m_frequency));
  }
  NodeWithFreq temp = PopQueue(pqueue);
  InternalNode* root = dynamic_cast<InternalNode*>(temp.m_node.release());
  CodeTree result(std::move(*root), GetSymbolLimit());
  delete root;
  return result;
}


uint32_t FrequencyTable::GetSymbolLimit()const{
  return m_freq_table.size();
}


FrequencyTable::NodeWithFreq::NodeWithFreq(Node *node, uint32_t symbol,
                                           uint64_t freq)
    : m_node(std::unique_ptr<Node>(node)), m_lowest_symbol(symbol),
      m_frequency(freq) {}

bool FrequencyTable::NodeWithFreq::operator<(const NodeWithFreq &other) const {
  if (m_frequency > other.m_frequency) {
    return true;
  } else if (m_frequency < other.m_frequency) {
    return false;
  } else if (m_lowest_symbol > other.m_lowest_symbol) {
    return true;
  } else {
    return false;
  }
}


FrequencyTable::NodeWithFreq
FrequencyTable::PopQueue(std::priority_queue<NodeWithFreq> &pop_queue) {
  FrequencyTable::NodeWithFreq result =
      std::move(const_cast<NodeWithFreq &&>(pop_queue.top()));
  pop_queue.pop();
  return result;
}