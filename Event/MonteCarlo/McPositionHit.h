// $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/MonteCarlo/McPositionHit.h,v 1.11 2002/04/08 20:02:47 burnett Exp $
#ifndef Event_McPositionHit_H
#define Event_McPositionHit_H 1


// Include files
#include <iostream>
#include <math.h>
#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/SmartRef.h"
#include "Event/TopLevel/Definitions.h"
#include "CLHEP/Geometry/Point3D.h"
#include "Event/Utilities/CLHEPStreams.h"
#include "Event/Utilities/IDStreams.h"
// Include all Gaudi container types here
//   to simplify inlude statements in algorithms
#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/ObjectList.h"

#include "idents/VolumeIdentifier.h"


#include "Event/MonteCarlo/McParticle.h"

// Forward declarations
class McParticle;


/*!
//------------------------------------------------------------------------------
//
// ClassName:   McPositionHit
//  
// Description: Monte Carlo class for a position hit such as tracker
//
// The class McPositionHit uses the Class Library for HEP (CLHEP).
//              
// Author:      OZAKI Masanobu
// Changes:     M.Frank 04/10/1999 : Proper use of SmartRefs and SmartRefVectors
//              P.Binko 19/10/1999 : Proper accessors of smart references
//                                   Formating of ASCII output
//              M.Ozaki 2000-12-05 : Modified for GLAST
//              M.Ozaki 2001-01-05 : MCPositionHits -> McPositionHit
//
//            M.Frailis
//      R.Giannitrapani
//             C.Cecchi 2002-02-29 : Added namespace mc, changed the VolumeID with
//                                   new VolumeIdentifier
//
//------------------------------------------------------------------------------
 */

extern const CLID& CLID_McPositionHit;

namespace mc { // NameSpace

class McPositionHit : virtual public ContainedObject {
  public:

    virtual const CLID& clID() const   { return McPositionHit::classID(); }
    static const CLID& classID()       { return CLID_McPositionHit; }
    /// Constructors
    McPositionHit()
      : m_depositedEnergy(0.),
        m_timeOfFlight(0.)
    {}
    /// Destructor
    virtual ~McPositionHit() { }

    /// special set
    void init(double edep, idents::VolumeIdentifier id, const HepPoint3D& entry, const HepPoint3D& exit);

    /// Retrieve cell identifier
    idents::VolumeIdentifier volumeID() const;
    /// Update cell identifier
    void setVolumeID( idents::VolumeIdentifier value );

    /// Retrieve entry member
    const HepPoint3D& entryPoint() const;
          HepPoint3D& entryPoint();
    /// Update Entry member
    void setEntryPoint( const HepPoint3D& value );

    /// Retrieve exit point
    const HepPoint3D& exitPoint() const;
          HepPoint3D& exitPoint();
    /// Update exit point
    void setExitPoint( const HepPoint3D& value );

    /// Retrieve deposited energy
    double depositedEnergy() const;
    /// Update deposited energy
    void setDepositedEnergy( double value );
    /// Retrieve depositing particle's energy
    double particleEnergy() const;
    /// Update depositing particle's energy
    void setParticleEnergy( double value );

    /// Retrieve primary-origin flag
    bool primaryOrigin() const;
    /// Update primary-origin flag
    void setPrimaryOrigin( bool value );
    /// Retrieve calorimeter-shower-origin flag
    bool caloShowerOrigin() const;
    /// Update calorimeter-shower-origin flag
    void setCaloShowerOrigin( bool value );

    /// Retrieve whether this hit should be digitized
    bool needDigi() const;
    /// Update whether this hit should be digitized
    void setNeedDigi( bool value );

    /// Retrieve hit's direction cosine
    double directionCosine() const;

    /// Retrieve member TOF
    double timeOfFlight() const;
    /// Update TOF member
    void setTimeOfFlight( double value );

    /// Retrieve pointer to McParticle (const or non-const)
    const McParticle* mcParticle() const;
          McParticle* mcParticle();
    /// Update pointer to McParticle (by a C++ pointer or a smart reference)
    void setMcParticle( McParticle* value );
    void setMcParticle( SmartRef<McParticle> value );

    /// Retrieve pointer to the ancestor McParticle (const or non-const)
    const McParticle* originMcParticle() const;
          McParticle* originMcParticle();
    /// Update pointer to McParticle (by a C++ pointer or a smart reference)
    void setOriginMcParticle( McParticle* value );
    void setOriginMcParticle( SmartRef<McParticle> value );

    /// Serialize the object for writing
    virtual StreamBuffer& serialize( StreamBuffer& s ) const;
    /// Serialize the object for reading
    virtual StreamBuffer& serialize( StreamBuffer& s );
    /// Fill the ASCII output stream
    virtual std::ostream& fillStream( std::ostream& s ) const;

  private:
    /// Volume ID
    idents::VolumeIdentifier m_volumeID;
    /// Entry point
    HepPoint3D              m_entry;
    /// Exit point
    HepPoint3D              m_exit;
    /// Deposited energy
    double                  m_depositedEnergy;
    /// Depositing particle's energy
    double                  m_particleEnergy;
    /// Time of flight
    double                  m_timeOfFlight;
    /// Pointer to McParticle causing the hit
    SmartRef<McParticle>    m_mcParticle;
    /// Pointer to the ancestor McParticle
    SmartRef<McParticle>    m_originMcParticle;
    /// Packed flags for the internal use.
    unsigned long           m_packedFlags;
};

inline void McPositionHit::init(double edep, idents::VolumeIdentifier id, const HepPoint3D& entry, const HepPoint3D& exit)
{
    m_depositedEnergy = edep;
    m_volumeID=id;
    m_entry = entry;
    m_exit = exit;
}

/// Serialize the object for writing
inline StreamBuffer& McPositionHit::serialize( StreamBuffer& s ) const
{
  ContainedObject::serialize(s);
  return s
    << m_volumeID
    << m_entry
    << m_exit
    << m_depositedEnergy
    << m_particleEnergy
    << m_timeOfFlight
    << m_mcParticle(this)
    << m_originMcParticle(this)
    << m_packedFlags;
}


/// Serialize the object for reading
inline StreamBuffer& McPositionHit::serialize( StreamBuffer& s )
{
  ContainedObject::serialize(s);
  return s
    >> m_volumeID
    >> m_entry
    >> m_exit
    >> m_depositedEnergy
    >> m_particleEnergy
    >> m_timeOfFlight
    >> m_mcParticle(this)
    >> m_originMcParticle(this)
    >> m_packedFlags;
}


}

/// Fill the ASCII output stream
inline std::ostream& mc::McPositionHit::fillStream( std::ostream& s ) const
{
  return s
    << "    base class McPositionHit :"
    << "\n        Volume ID             = " << m_volumeID.name()
    << "\n        Entry point (x, y, z) = ( "
    << EventFloatFormat( Event::width, Event::precision )
    << m_entry.x() << ", "
    << EventFloatFormat( Event::width, Event::precision )
    << m_entry.y() << ", "
    << EventFloatFormat( Event::width, Event::precision )
    << m_entry.z() << " )"
    << "\n        Deposited Energy      = "
    << EventFloatFormat( Event::width, Event::precision )
    << m_depositedEnergy
    << "\n        Particle Energy       = "
    << EventFloatFormat( Event::width, Event::precision )
    << m_particleEnergy
    << "\n        Time of flight        = "
    << EventFloatFormat( Event::width, Event::precision )
    << m_timeOfFlight
    << "\n        Exit point (x, y, z)  = ( "
    << EventFloatFormat( Event::width, Event::precision )
    << m_exit.x() << ", "
    << EventFloatFormat( Event::width, Event::precision )
    << m_exit.y() << ", "
    << EventFloatFormat( Event::width, Event::precision )
    << m_exit.z() << " )"
    << "\n        McParticle            = " << m_mcParticle(this)
    << "\n        ancestor McParticle   = " << m_originMcParticle(this);
}


typedef ObjectVector<mc::McPositionHit> McPositionHitVector;
typedef ObjectList<mc::McPositionHit>   McPositionHitList;

/*! A small class to use the sort algorithm */
class ComparePosHits {
  public:
    bool operator()(mc::McPositionHit *left, mc::McPositionHit *right)
    {return left->volumeID() < right->volumeID();}

    };


#endif    // Event_McPositionHit_H

