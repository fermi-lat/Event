#ifndef Event_TKRRECON_H
#define Event_TKRRECON_H 1

#include <iostream>
#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/DataObject.h"
#include "Event/TopLevel/Definitions.h"

extern const CLID& CLID_TkrRecon;

/** @class TkrRecon
* @brief Defines the top level object for digitization data.
* It can be identified by "/Event/TkrRecon" on the TDS
* 
* 
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/TopLevel/TkrRecon.h,v 1.10 2002/09/06 21:51:56 heather Exp $
*/
namespace Event {  // NameSpace

class TkrRecon : public DataObject {
    
public:
    
    TkrRecon()
        : DataObject() { }
    
    virtual ~TkrRecon() { }
    

    /// Retrieve reference to class definition structure
    virtual const CLID& clID() const  { return TkrRecon::classID(); }
    static const CLID& classID() { return CLID_TkrRecon; }
    
};

}


#endif  // GLASTEVENT_TKRRECON_H
