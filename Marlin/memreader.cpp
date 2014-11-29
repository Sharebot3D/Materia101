/* -*- c++ -*- */

#include "Marlin.h"
#include "memreader.h"
#include "stepper.h"
#include "temperature.h"
#include "language.h"
#include "ultralcd.h"

#include "language.h"

#if LANGUAGE_CHOICE == 7
// Italian
#if MACHINE_3D == 1
#include "sc_3d_level_plate_a.h"
#include "sc_3d_level_plate_m.h"
#else
#include "sc_level_plate_a.h"
#include "sc_level_plate_m.h"
#endif

#elif LANGUAGE_CHOICE == 1
// English
#if MACHINE_3D == 1
#include "sc_3d_level_plate_a_en.h"
#include "sc_3d_level_plate_m_en.h"
#endif

#ifdef CFG_MATERIA101
#include "sc_101_level_plate_a_en.h"
#include "sc_empty_level_plate_m.h"
#endif

// English: Default
#ifndef SC_LEVEL_PLATE_A
#include "sc_level_plate_a_en.h"
#endif

#ifndef SC_LEVEL_PLATE_M
#include "sc_level_plate_m_en.h"
#endif

#else
// Any other language
#include "sc_level_plate_a.h"
#include "sc_level_plate_m.h"
#endif

#if MACHINE_3D == 1
#include "sc_3d_change_left.h"
#include "sc_3d_change_right.h"
#endif

#ifdef CFG_MATERIA101
#include "sc_empty_change_left.h"
#include "sc_101_change_right.h"
#include "sc_empty_movedown.h"
#endif

#ifndef SC_CHANGE_LEFT
#include "sc_change_left.h"
#endif

#ifndef SC_CHANGE_RIGHT
#include "sc_change_right.h"
#endif

#include "sc_nozzles.h"

#ifndef SC_MOVEDOWN
#include "sc_movedown.h"
#endif

#if EXTRUDERS > 1
#include "sc_dual.h"
#endif

MemReader::MemReader()
{
   program = 0;
   pos = 0;
   isprinting = false;

   Script[0] = NULL;
   Script[1] = LEVEL_PLATE_A;
   Script[2] = LEVEL_PLATE_M;
   Script[3] = CHANGE_RIGHT;
   Script[4] = MOVEDOWN;
#if EXTRUDERS > 1
   Script[5] = CHANGE_LEFT;
   Script[6] = DUAL;
   Script[7] = NULL;
#else
   Script[5] = NULL;
#endif

  // Utilities program length
  ScriptLength[0] = -1;
  ScriptLength[1] = LEVEL_PLATE_A_LENGTH;
  ScriptLength[2] = LEVEL_PLATE_M_LENGTH;
  ScriptLength[3] = CHANGE_RIGHT_LENGTH;
  ScriptLength[4] = MOVEDOWN_LENGTH;
#if EXTRUDERS > 1
  ScriptLength[5] = CHANGE_LEFT_LENGTH;
  ScriptLength[6] = DUAL_LENGTH;
  ScriptLength[7] = -1;
#else
  ScriptLength[5] = -1;
#endif

}

void MemReader::startMemprint(const uint8_t nr)
{
  if ( ScriptLength[nr] > 0 ) {
    program = nr;
    pos = 0;
    isprinting = true;
    lcd_ForceStatusScreen(true);
    lcd_ForceStatusScreen(false);
  }
}

void MemReader::pauseMemPrint( void )
{
   isprinting=false;
}

void MemReader::resumeMemPrint( void )
{
   isprinting=true;
}


/* ??? Check se serve */
void MemReader::getStatus()
{
  if(isprinting){
    SERIAL_PROTOCOLPGM(MSG_SD_PRINTING_BYTE);
    SERIAL_PROTOCOL(pos);
    SERIAL_PROTOCOLPGM("/");
    SERIAL_PROTOCOLLN(ScriptLength[program]);
  }
  else{
    SERIAL_PROTOCOLLNPGM(MSG_SD_NOT_PRINTING);
  }
}

void MemReader::printingHasFinished()
{
    st_synchronize();
    quickStop();
    isprinting = false;
    autotempShutdown();
}
