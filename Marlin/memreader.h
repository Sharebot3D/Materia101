/* -*- c++ -*- */

#ifndef MEMREADER_H
#define MEMREADER_H

class MemReader
{
public:
  MemReader();
  
  void startMemprint(const uint8_t nr);
  void pauseMemPrint();
  void resumeMemPrint();
  void getStatus();
  void printingHasFinished();

  FORCE_INLINE bool eof() { return pos>=ScriptLength[program]; };
  FORCE_INLINE int16_t get() {  if ( pos<=ScriptLength[program] ) 
                                  return (int16_t)pgm_read_byte_near( &Script[program][pos++] );
                                else
                                  return -1;
                             };
  FORCE_INLINE uint8_t percentDone(){if(!isprinting) return 0; return pos/((ScriptLength[program]+99)/100); };

public:
  bool isprinting;  

private:
  uint8_t program;
  uint32_t pos;

  PROGMEM const char *Script[9];
  uint32_t ScriptLength[9];

};
extern MemReader utility;
#endif
