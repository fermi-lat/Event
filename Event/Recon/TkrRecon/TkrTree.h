/**
 * @class TkrTree
 *
 * @brief This defines a class to associate the trees defined by TkrTrees with TkrTracks
 *
 * @author Tracy Usher
 *
 * $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/TkrRecon/TkrTree.h,v 1.3 2010/11/24 16:35:47 usher Exp $
 */

#ifndef TkrTree_h
#define TkrTree_h

#include "Event/Recon/TkrRecon/TkrVecNodes.h"
#include "Event/Recon/TkrRecon/TkrTrack.h"
#include "Event/Recon/TkrRecon/TkrFilterParams.h"

#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/IInterface.h"

#include "Event/RelTable/RelTable.h"

#include <map>
#include <vector>

// Declare Gaudi object interface ID
static const CLID& CLID_TkrTree = InterfaceID("TkrTree",  1, 0);

namespace Event {  // NameSpace

// Typedef for the map of siblings at each layer
typedef std::map<int, std::vector<const TkrVecNode*> > TkrNodeSiblingMap;
typedef std::vector<Event::TkrTrack*>            TkrTrackVec;

class TkrTree: virtual public ContainedObject, public TkrTrackVec
{
public:
    // Constructors
    TkrTree() :
            m_headNode(0), m_siblingMap(0), m_axisParams(0)
            {TkrTrackVec::clear();}

    TkrTree(TkrVecNode* node, TkrNodeSiblingMap* nodeSiblingMap, TkrFilterParams* axisParams, TkrTrack* track) :
            m_headNode(node), m_siblingMap(nodeSiblingMap), m_axisParams(axisParams)
            {TkrTrackVec::clear(); push_back(track);}

    virtual ~TkrTree() 
    {
        if (m_siblingMap) delete m_siblingMap;
        if (m_axisParams) delete m_axisParams;
    }

    //! Retrieve pointer to class defininition structure
    virtual const CLID& clID()    const   { return TkrTree::classID(); }
    static  const CLID& classID()         { return CLID_TkrTree; }

    // Methods to return information
    // Return pointer to the head node for this tree
    const TkrVecNode*        getHeadNode()   const {return m_headNode;}
    // Return pointer to the sibling map
    const TkrNodeSiblingMap* getSiblingMap() const {return m_siblingMap;}
    // Return pointer to the axis parameters
    const TkrFilterParams*   getAxisParams() const {return m_axisParams;}
    // Return pointer to the track for this tree
    const TkrTrack*          getBestTrack()  const {return front();}

private:
    // Pointer to the head node in the Tree
    TkrVecNode*        m_headNode;

    // Pointer to the Node sibling map
    TkrNodeSiblingMap* m_siblingMap;

    // Pointer to the tree axis parameters 
    TkrFilterParams*   m_axisParams;
};

// Typedefs for gaudi container for these objects
typedef ObjectVector<TkrTree>                   TkrTreeCol;
typedef TkrTreeCol::iterator                    TkrTreeColPtr;
typedef TkrTreeCol::const_iterator              TkrTreeColConPtr;

}; // Namespace

#endif

