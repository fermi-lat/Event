
#ifndef __TkrPatCandHit_H
#define __TkrPatCandHit_H 1

#include <vector>
#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/MsgStream.h"
#include "Event/Recon/TkrRecon/TkrCluster.h"
/** 
* @class TkrPatCandHit
*
* @brief Class definition for candidate track hit information
*
* @author The Tracking Software Group
*
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/TkrRecon/TkrPatCandHit.h,v 1.5 2003/08/04 19:41:47 usher Exp $
*/

namespace Event { //Namespace

class TkrPatCandHit : virtual public ContainedObject
{    
public:
    
    TkrPatCandHit(TkrCluster* pCluster);
    TkrPatCandHit(unsigned int hitId, const Point& pos, unsigned int tower, 
        unsigned int layer, TkrCluster::view v);
   ~TkrPatCandHit() {}

    //Output method to write out the contents of the class
    void writeOut(MsgStream& log) const; 

    //Provide access to the information contained in the class
    Point Position()         const {return m_position;}
    int   HitIndex()         const {return m_hitIndex;}
    int   TowerIndex()       const {return m_towerIndex;}
    int   PlaneIndex()       const {return m_planeIndex;}
    TkrCluster::view  View() const {return m_view;}

    //The following provided to allow sorting (by layer)
    friend bool operator>( const TkrPatCandHit& o1, const TkrPatCandHit& o2) {return o1.m_position.z() <  o2.m_position.z();}
    friend bool operator==(const TkrPatCandHit& o1, const TkrPatCandHit& o2) {return o1.m_position.z() == o2.m_position.z();}
    friend bool operator!=(const TkrPatCandHit& o1, const TkrPatCandHit& o2) {return o1.m_position.z() != o2.m_position.z();}

private:

    Point m_position;          //xyz coordinates of this hit
    int   m_hitIndex;          //Index into TkrClusters list of this hit
    int   m_towerIndex;        //Index of the tower containing this hit
    int   m_planeIndex;        //Plane (layer) index
    TkrCluster::view  m_view;  //Primary measurement projection (x or y)
};

//Following typedefs for containing hits
typedef ObjectVector<TkrPatCandHit>           CandHitVector;
typedef ObjectVector<TkrPatCandHit>::iterator CandHitVectorPtr;

};
    
#endif
