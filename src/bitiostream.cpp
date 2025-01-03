#include "bitiostream.h"
#include <istream>
#include <ostream>
#include <string>

BitOutPutStream::BitOutPutStream(std::ostream &out_put) : m_out_put(out_put) {
  m_current_bytes = 0;
  m_numbits_filled = 0;
}

void BitOutPutStream::write(int b) {
  if (b != 0 && b != 1) {
    throw std::domain_error("Argument must be 0 or 1");
  }
  m_current_bytes = (m_current_bytes << 1) | b;
  m_numbits_filled++;
  if (m_numbits_filled == 8) {
    m_out_put.put(static_cast<char>(m_current_bytes));
    m_current_bytes = 0;
    m_numbits_filled = 0;
  }
}
void BitOutPutStream::finish() {
  while (m_numbits_filled != 0) {
    write(0);
  }
}

BitInputStream::BitInputStream(std::istream &input)
    : m_input(input), m_current_bytes(0), m_numbits_remaining(0) {}


int BitInputStream::read(){
  if(m_current_bytes == std::char_traits<char>::eof()){
    return -1;
  }

  if(m_numbits_remaining == 0){
    m_current_bytes = m_input.get();
    if(m_current_bytes == std::char_traits<char>::eof()){
      return -1;
    }
    m_numbits_remaining = 8;
  }
  m_numbits_remaining--;
  return (m_current_bytes >>  m_numbits_remaining) & 1;
}
