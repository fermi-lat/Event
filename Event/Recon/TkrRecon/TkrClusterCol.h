#ifndef TkrClusterCol_H
#define TkrClusterCol_H 

#include <vector>
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/IInterface.h"
#include "geometry/Point.h"
#include "Event/Recon/TkrRecon/TkrCluster.h"

static const CLID& CLID_TkrClusterCol=InterfaceID("TkrClusterCol",1,0);

/** 
* @class TkrClusterCol
*
* @brief TDS Object for TkrCluster vector, and array of vectors.
*
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/TkrRecon/Attic/TkrClusterCol.h,v 1.10 2002/10/06 19:06:47 lsrea Exp $
*/

namespace Event { //Namespace

class TkrClusterCol : public DataObject
{
public:

    /// constants for the array of cluster lists
    enum {NVIEWS=2, NPLANES=18};

    TkrClusterCol();
    /// destructor: also deletes the clusters in the list
    virtual ~TkrClusterCol();
    static const CLID& classID() {return CLID_TkrClusterCol;}
    virtual const CLID& clID() const {return classID();}
    
    /// returns total number of clusters
    int nHits()  const {return m_clustersList.size();}

    /// flags TkrCluster with id i
    void flagHit(int i, int iflag=1)   {getHit(i)->flag(iflag);}
    /// unflag ith TkrCluster
    void unflagHit(int i)  {getHit(i)->unflag();}
    /// returns true if the TkrCluster with id i is flagged
    bool hitFlagged(int i) const {return getHit(i)->hitFlagged();}
    /// returns size of the cluster with id i
    double size(int i) const {return getHit(i)->size();}     
    /// returns  space position of the TkrCluster with id i
    Point position(int i)  const {return getHit(i)->position();}
    /// returns pointer to the TkrCluster with id i
    TkrCluster* getHit(int i) const;
          
    /// returns a reference the a cluster list of hits in a given layer
    const std::vector<TkrCluster*>& getHits(TkrCluster::view v, int iplane)
        const
    {return m_clustersByPlaneList[TkrCluster::viewToInt(v)][iplane];}
    
    /// returns the number of clusters in a given view and plane
    int nHits(TkrCluster::view v, int iplane) const; 
    
    void addCluster(TkrCluster* cl);

    /// delete the clusters in the cluster list
    /// called by the destructor. 

    virtual void clear();
    
    /// write out the information of the Clusters
    void writeOut(MsgStream& log) const;

        /// intialize the TkrClusterCol
    virtual void ini();
    
private:
        /// cluster list
    std::vector<TkrCluster*> m_clustersList;
    /// cluster list by plane and view
    std::vector<TkrCluster*> m_clustersByPlaneList[NVIEWS][NPLANES]; 
};

}; //Namespace

#endif // TkrClusterCol
