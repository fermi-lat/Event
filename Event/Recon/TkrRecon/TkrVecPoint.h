/** @file TkrVecPoint.h

* @class TkrVecPoint
*
* @brief Container class for the XY hit pairs which are produced by TkrVecPoints.
*
* last modified 11/01/2004
*
* @authors b. allgood, w. atwood and l. rochester
*
* $Header: /nfs/slac/g/glast/ground/cvs/TkrRecon/src/PatRec/VectorLinks/TkrVecPoint.h,v 1.2 2006/03/21 01:12:37 usher Exp $
*/

#ifndef __TkrVecPoint_H
#define __TkrVecPoint_H

#include "geometry/Point.h"
#include "geometry/Vector.h"
#include "geometry/Ray.h"
#include "Event/Recon/TkrRecon/TkrCluster.h"
#include <vector>

#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/IInterface.h"

// Declare Gaudi object interface ID
static const CLID& CLID_TkrVecPoint = InterfaceID("TkrVecPoint",  1, 0);

namespace Event {  // NameSpace

class TkrVecPoint: virtual public ContainedObject
{
public:
    // Status bit definitions    
    enum StatusBits {ASSOCIATED = 0x0001,
                     LINKTOPHIT = 0x0010,
                     LINKBOTHIT = 0x0020};

    // constructors
    TkrVecPoint() : m_layer(-1), m_pXCluster(0), m_pYCluster(0), m_position(0.,0.,0.) 
    {}

    TkrVecPoint(int layer, 
        const Event::TkrCluster* xClus, const Event::TkrCluster* yClus):
         m_status(0), m_layer(layer), m_pXCluster(xClus), m_pYCluster(yClus),
         m_position(m_pXCluster->position().x(), m_pYCluster->position().y(),
            0.5*(m_pXCluster->position().z() + m_pYCluster->position().z()))
    {}

    //! Retrieve pointer to class defininition structure
    virtual const CLID& clID()    const   { return TkrVecPoint::classID(); }
    static  const CLID& classID()         { return CLID_TkrVecPoint; }

    // destructor
    virtual ~TkrVecPoint() 
    {
        return;
    }

    // Initializer
    void initialize(int layer, const Event::TkrCluster* xClus, const Event::TkrCluster* yClus)
    {
        m_status    = 0;
        m_layer     = layer;
        m_pXCluster = xClus;
        m_pYCluster = yClus;
    }

    /// Set status bits
    void setAssociated() {m_status |= ASSOCIATED;}
    void setLinkTopHit() {m_status |= LINKTOPHIT;}
    void setLinkBotHit() {m_status |= LINKBOTHIT;}

    /// @name access methods
    //@{
    /// Is this hit associated to a link?
    const bool isAssociated() const {return (m_status & ASSOCIATED) != 0;}
    /// Is this hit used as a top hit in a link?
    const bool isLinkTopHit() const {return (m_status & LINKTOPHIT) != 0;}
    /// Is this hit used as a bottom hit in a link?
    const bool isLinkBotHit() const {return (m_status & LINKBOTHIT) != 0;}
    /// Pointer to the cluster in the x plane of this layer
    const Event::TkrCluster*   getXCluster()   const {return m_pXCluster;}
    /// Pointer to the cluster of the y plane of this layer
    const Event::TkrCluster*   getYCluster()   const {return m_pYCluster;}
    /// returns the ray between 2 TkrVecPoints, with corrections for slopes
    Ray getRayTo(const TkrVecPoint* point) const;
    /// at least one of the clusters in this point is flagged
    bool flagged() const { return m_pXCluster->hitFlagged() || m_pYCluster->hitFlagged(); }
    /// distance in layers between these two TkrVecPoints (always positive-definite)
    int  getLayerSeparationFrom(const TkrVecPoint* point) const;
    /// the layer number of this TkrVecPoint (for Neural Net, could go away)
    int  getLayer() const { return m_layer; }
    /// position of this TkrVecPoint, using info from x and y clusters
    const Point& getPosition() const {return m_position;}
//        return Point(m_pXCluster->position().x(), m_pYCluster->position().y(),
//            0.5*(m_pXCluster->position().z() + m_pYCluster->position().z())); }
    /// Tower of this point... (x and y clusters are guaranteed to be in the same tower)
    int getTower() const { return m_pXCluster->tower(); }
    /// x/y distance to a reference point
    double getDistanceSquaredTo(Point refPoint) const {
        Vector diff = refPoint - getPosition();
        return diff.x()*diff.x() + diff.y()*diff.y();    
    }

    //@}

    /// @name other methods
    //@{
    /// equality operator - requires both clusters to match
    bool operator==(const TkrVecPoint& point) const;
    /// equality operator - requires only one cluster to match
    bool operator|=(const TkrVecPoint& point) const;
    /// inequality operator
    bool operator!=(const TkrVecPoint& point) const;
    //@}

private:

    // data members
    /// Status word
    unsigned int             m_status;
    /// layer number
    int                      m_layer;
    /// pointer to x cluster
    const Event::TkrCluster* m_pXCluster;
    /// pointer to y cluster
    const Event::TkrCluster* m_pYCluster;
    /// Position from the above two clusters
    Point                    m_position;
};

inline int TkrVecPoint::getLayerSeparationFrom(const TkrVecPoint* point) const
{
    return abs(m_layer - point->m_layer);
}

inline bool TkrVecPoint::operator==(const TkrVecPoint& point) const
{
    // same point if both clusters matche (note &&)
    return( (m_pXCluster == point.m_pXCluster) &&
        (m_pYCluster == point.m_pYCluster) );
}

inline bool TkrVecPoint::operator|=(const TkrVecPoint& point) const
{
    // same point if either cluster matches (note ||)
    return( (m_pXCluster == point.m_pXCluster) ||
        (m_pYCluster == point.m_pYCluster) );
}

inline bool TkrVecPoint::operator!=(const TkrVecPoint& point) const
{
    // different point if different clusters
    return( (m_pXCluster != point.m_pXCluster) ||
            (m_pYCluster != point.m_pYCluster) );
}

typedef std::vector<TkrVecPoint*> TkrVecPointList;
typedef TkrVecPointList::const_iterator TkrVecPointListConItr;

// Typedefs for gaudi container for these objects
typedef ObjectVector<TkrVecPoint>      TkrVecPointCol;
typedef TkrVecPointCol::iterator       TkrVecPointColPtr;
typedef TkrVecPointCol::const_iterator TkrVecPointColConPtr;

}; // Namespace

#endif // __TkrVecPoint_H
