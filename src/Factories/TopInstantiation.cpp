/*! \file TopInstanciation.cpp
\brief based upon topInstanciation.cpp by Markus Frank available within the LHCbEvent package
This file instantiates concretely the implementation of all of these
classes so that they may be included within factories in the DLL.

*/

#define EVENT_FACTORIES_TOPINSTANTIATION_CPP  1

// Include files
#include "GaudiKernel/ObjectFactory.h"
#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/ObjectList.h"

#define _ImplementTopContainedFactories(x)  \
  _ImplementContainedObjectFactory( x )    \
  _ImplementDataObjectFactory( x##Vector ) \
  _ImplementDataObjectFactory( x##List )

#define DLL_DECL_CONTAINEDOBJECTFACTORY(x)  \
  DLL_DECL_OBJECTFACTORY( x ) \
  DLL_DECL_OBJECTFACTORY( x##Vector )\
  DLL_DECL_OBJECTFACTORY( x##List )


// ====================================================================
// Object factory implementation for objects of class Run
// ===================================================================
//#include "LHCbEvent/TopLevel/Run.h"
//_ImplementDataObjectFactory(Run)

// ====================================================================
// Object factory implementation for objects of class Event
// ===================================================================
#include "GlastEvent/TopLevel/Event.h"
_ImplementDataObjectFactory(Event);

// ====================================================================
// Object factory implementation for objects of class MCEvent
// ===================================================================
#include "GlastEvent/TopLevel/MCEvent.h"
_ImplementDataObjectFactory(MCEvent)

// ====================================================================
// Object factory implementation for objects of class IrfEvent
// ===================================================================
#include "GlastEvent/TopLevel/IrfEvent.h"
_ImplementDataObjectFactory(IrfEvent)

// ====================================================================
// Object factory implementation for objects of class DigiEvent
// ==================================================================
#include "GlastEvent/TopLevel/DigiEvent.h"
_ImplementDataObjectFactory(DigiEvent)

// ====================================================================
// Object factory implementation for objects of class RawEvent
// ===================================================================
#include "GlastEvent/TopLevel/RawEvent.h"
_ImplementDataObjectFactory(RawEvent)

/*
// ====================================================================
// Object factory implementation for objects of class RecEvent
// ===================================================================
#include "LHCbEvent/TopLevel/RecEvent.h"
_ImplementDataObjectFactory(RecEvent)

// ====================================================================
// Object factory implementation for objects of class AnalEvent
// ===================================================================
#include "LHCbEvent/TopLevel/AnalEvent.h"
_ImplementDataObjectFactory(AnalEvent)
*/
void TopInstantiation()  {
  //DLL_DECL_OBJECTFACTORY( Run );
  DLL_DECL_OBJECTFACTORY( Event );
  DLL_DECL_OBJECTFACTORY( MCEvent );
  DLL_DECL_OBJECTFACTORY( IrfEvent );
  DLL_DECL_OBJECTFACTORY( DigiEvent );
  DLL_DECL_OBJECTFACTORY( RawEvent );
  //DLL_DECL_OBJECTFACTORY( RecEvent );
  //DLL_DECL_OBJECTFACTORY( AnalEvent );
}
