#pragma once

#include <cstdint>
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


