#ifndef Event_TKRRECON_H
#define Event_TKRRECON_H 1

#include <iostream>
#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/IInterface.h"
#include "Event/TopLevel/Definitions.h"

static const CLID& CLID_TkrRecon=InterfaceID("TkrRecon",1,0);

/** @class TkrRecon
* @brief Defines the top level object for digitization data.
* It can be identified by "/Event/TkrRecon" on the TDS
* 
* 
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/TkrRecon/TkrRecon.h,v 1.1 2004/03/11 16:45:33 berthon Exp $
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
