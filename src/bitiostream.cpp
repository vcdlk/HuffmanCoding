#include "bitiostream.h"
#include <ostream>


BitOutPutStream::BitOutPutStream(std::ostream& out_put):m_out_put(out_put){
  m_current_bytes = 0;
  m_numbits_filled = 0;  
}


void BitOutPutStream::write(int b){
  if(b != 0 && b != 1){
		throw std::domain_error("Argument must be 0 or 1");
  }
  m_current_bytes = (m_current_bytes << 1) | b;
  m_numbits_filled++;
  if(m_numbits_filled == 8){
    m_out_put.put(static_cast<char>(m_current_bytes));
    m_current_bytes = 0;
    m_numbits_filled = 0;
  }
}
void BitOutPutStream::finish(){
  while(m_numbits_filled != 0){
    write(0);
  }
}