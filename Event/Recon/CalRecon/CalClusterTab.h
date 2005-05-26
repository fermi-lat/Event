#ifndef CalCluster_h
#define CalCluster_h

#include "GaudiKernel/MsgStream.h"
#include "Event/RelTable/RelTable.h"
#include "Event/RelTable/Relation.h"
#include "Event/Recon/CalRecon/CalXtalRecData.h"
#include "Event/Recon/CalRecon/CalCluster.h"

/** 
* @class CalClusterTab
*
* @brief CalCluster header file for relational table typedefs
*
*
* @author(s) The CalRecon Software Group
*
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/CalRecon/CalClusterTab.h,v 1.0 2004/09/18 18:16:58 usher Exp $
*/

namespace Event
{
    typedef Event::RelTable<Event::CalXtalRecData, Event::CalCluster>               CalClusterHitTab;
    typedef Event::Relation<Event::CalXtalRecData, Event::CalCluster>               CalClusterHitRel;
    typedef ObjectList< Event::Relation<Event::CalXtalRecData, Event::CalCluster> > CalClusterHitTabList;
};

#endif
