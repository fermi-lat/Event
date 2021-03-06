#ifndef Event_AcdEventTopology_H
#define Event_AcdEventTopology_H

#include <vector>

#include "Event/TopLevel/Definitions.h"

#include "idents/AcdId.h"


#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/IInterface.h"



class MsgStream;

static const CLID& CLID_AcdEventTopologyCol = InterfaceID("AcdEventTopologyCol", 1, 0);

/**
 *  @class Event::AcdEventTopology
 *
 *  @brief
 *  \author Eric Charles
 *
 * $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/AcdRecon/AcdEventTopology.h,v 1.3.48.1 2012/04/20 03:59:47 kadrlica Exp $
 **/

namespace Event
{

  class AcdEventTopology : virtual public ContainedObject {
    
  public:

    /// Default constructor
    AcdEventTopology();

    /// Copy constructor
    AcdEventTopology(const AcdEventTopology& other);

    /// Constructor for use in reconstruction, 
    AcdEventTopology(unsigned tileCount, unsigned ribbonCount, unsigned vetoCount, unsigned tileVeto,                     
                     float totalTileEnergy, float totalRibbonEnergy, float tileEnergy, float ribbonEnergy,                
                     float ghostTileEnergy, float ghostRibbonEnergy, float triggerTileEnergy, float triggerRibbonEnergy,  
                     unsigned nTilesTop, unsigned nTilesSideRow[4], unsigned nTilesSideFace[4],                           
                     unsigned nVetoTop, unsigned nVetoSideRow[4], unsigned nVetoSideFace[4],                              
                     float tilesEnergyTop, float tileEnergySideRow[4], float tileEnergySideFace[4],                       
                     unsigned nSidesHit, unsigned nSidesVeto);                                                            

    /// Destructor is trivial
    virtual ~AcdEventTopology() {};
    
    /// Assignment operator
    const AcdEventTopology& operator=(const AcdEventTopology& other);
    
    /// Direct access to parameters
    inline unsigned getTileCount() const { return m_tileCount; }
    
    inline unsigned getRibbonCount() const { return m_ribbonCount; }

    inline unsigned getVetoCount() const { return m_vetoCount; }

    inline unsigned getTileVeto() const { return m_tileVeto; }

    inline float getTotalTileEnergy() const { return m_totalTileEnergy; }

    inline float getTotalRibbonEnergy() const { return m_totalRibbonEnergy; }

    inline float getTileEnergy() const { return m_tileEnergy; }

    inline float getRibbonEnergy() const { return m_ribbonEnergy; }

    inline float getGhostTileEnergy() const { return m_ghostTileEnergy; }

    inline float getGhostRibbonEnergy() const { return m_ghostRibbonEnergy; }

    inline float getTriggerTileEnergy() const { return m_triggerTileEnergy; }

    inline float getTriggerRibbonEnergy() const { return m_triggerRibbonEnergy; }

    inline unsigned getVetoCountTop() const { return m_nVetoTop; }

    inline unsigned getVetoCountSideRow(unsigned iRow) const { return m_nVetoSideRow[iRow]; }

    inline unsigned getVetoCountSideFace(unsigned iFace) const { return m_nVetoSideFace[iFace-1]; }

    inline unsigned getTileCountTop() const { return m_nTilesTop; }

    inline unsigned getTileCountSideRow(unsigned iRow) const { return m_nTilesSideRow[iRow]; }

    inline unsigned getTileCountSideFace(unsigned iFace) const { return m_nTilesSideFace[iFace-1]; }

    inline float getTileEnergyTop() const { return m_tileEnergyTop; }

    inline float getTileEnergySideRow(unsigned iRow) const { return m_tileEnergySideRow[iRow]; }

    inline float getTileEnergySideFace(unsigned iFace) const { return m_tileEnergySideFace[iFace-1]; }

    inline unsigned getNSidesHit() const { return m_nSidesHit; }

    inline unsigned getNSidesVeto() const { return m_nSidesVeto; }

    /// set everything at once
    void set(unsigned tileCount, unsigned ribbonCount, unsigned vetoCount, unsigned tileVeto,
             float totalTileEnergy, float totalRibbonEnergy, float tileEnergy, float ribbonEnergy,
             float ghostTileEnergy, float ghostRibbonEnergy, float triggerTileEnergy, float triggerRibbonEnergy,
             unsigned nTilesTop, unsigned nTilesSideRow[4], unsigned nTilesSideFace[4],
             unsigned nVetoTop, unsigned nVetoSideRow[4], unsigned nVetoSideFace[4],
             float tileEnergyTop, float tileEnergySideRow[4], float tileEnergySideFace[4],
             unsigned nSidesHit, unsigned nSidesVeto);
 
    /// Print out this structure on a stream
    virtual void writeOut(MsgStream& stream) const;

    /// Reset all the values to their defaults
    virtual void ini();
    
  protected:

    
  private:    

    unsigned m_tileCount;
    
    unsigned m_ribbonCount;

    unsigned m_vetoCount;

    unsigned m_tileVeto;
    
    float m_totalTileEnergy;

    float m_totalRibbonEnergy;

    float m_tileEnergy;

    float m_ribbonEnergy;

    float m_ghostTileEnergy;

    float m_ghostRibbonEnergy;

    float m_triggerTileEnergy;

    float m_triggerRibbonEnergy;

    unsigned m_nTilesTop;

    unsigned m_nTilesSideRow[4];

    unsigned m_nTilesSideFace[4];

    unsigned m_nVetoTop;

    unsigned m_nVetoSideRow[4];

    unsigned m_nVetoSideFace[4];

    float m_tileEnergyTop;

    float m_tileEnergySideRow[4];

    float m_tileEnergySideFace[4];

    unsigned m_nSidesHit;

    unsigned m_nSidesVeto;

  };



}

#endif
