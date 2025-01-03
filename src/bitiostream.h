#pragma once

#include <cstdint>
#include <istream>
#include <ostream>
class BitOutPutStream final{
  public:
   explicit BitOutPutStream(std::ostream& out_put);

  void write(int b);

  void finish();

  private:
  std::ostream& m_out_put;
  uint8_t m_current_bytes;
  uint32_t m_numbits_filled;
};


class BitInputStream final{
  public:
  explicit BitInputStream(std::istream& input);

  int read();

  private:
  std::istream& m_input;

  uint32_t m_current_bytes;
  uint32_t m_numbits_remaining;
};