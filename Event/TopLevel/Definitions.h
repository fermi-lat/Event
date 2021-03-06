// $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/TopLevel/Definitions.h,v 1.3 2002/05/10 01:17:35 burnett Exp $
#ifndef LHCBEVENT_DEFINITIONS_H
#define LHCBEVENT_DEFINITIONS_H 1

#include <iostream>
#include <iomanip>


//------------------------------------------------------------------------------
//
// Description: Definitions of Event specific constants
//              e.g. output precision of member data
//                   (used in the function fillstream())
//
// Author:      Pavel Binko
//
//------------------------------------------------------------------------------

namespace EventFormat {

  // Width of the output field of a floating point number
  const int width      = 12;
  // Number of positions after the decimal point
  const int precision  = 2;

  // Width of an integer output field         -999 <= i < 9999
  const int field4     = 4;
  // Width of an integer output field        -9999 <= i < 99999
  const int field5     = 5;
  // Width of an integer output field -99999999999 <= i < 999999999999
  const int field12    = 12;

}


// Macro, which defines the output format of floating point numbers
//   Standard usage :
//     << EventFloatFormat( Event::width, Event::precision ) << 
#define EventFloatFormat(X,Y)       std::setw(X) << std::setprecision(Y)
// The keyword scientific does not work properly om all platforms
// #define EventFloatFormat(X,Y)       std::setw(X)
//                                           << std::setprecision(Y)
//                                           << scientific


// Macro, which defines the output format of integer numbers
//   Standard usage : << EventField( Event::field4 ) << 
#define EventField(X)               std::setw(X)


#endif // LHCBEVENT_DEFINITIONS_H
