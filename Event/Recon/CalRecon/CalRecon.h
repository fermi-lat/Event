#ifndef Event_CALRECON_H
#define Event_CALRECON_H 1

#include <iostream>
#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/IInterface.h"
#include "Event/TopLevel/Definitions.h"

static const CLID& CLID_CalRecon=InterfaceID("CalRecon,1,0);

/** @class CalRecon
* @brief Defines the top level object for digitization data.
* It can be identified by "/Event/CalRecon" on the TDS
* 
* 
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/CalRecon/CalRecon.h,v 1.1 2004/03/11 16:45:33 berthon Exp $
*/
namespace Event {  // NameSpace

class CalRecon : public DataObject {
    
public:
    
    CalRecon()
        : DataObject() { }
    
    virtual ~CalRecon() { }
    

    /// Retrieve reference to class definition structure
    virtual const CLID& clID() const  { return CalRecon::classID(); }
    static const CLID& classID() { return CLID_CalRecon; }
    
};

}


#endif  // GLASTEVENT_CALRECON_H
