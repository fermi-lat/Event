// $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/MonteCarlo/McPositionHit.h,v 1.25 2007/03/18 14:51:06 usher Exp $
#ifndef Event_McPositionHit_H
#define Event_McPositionHit_H 1

#include <iostream>
#include <math.h>
#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/SmartRef.h"
#include "Event/TopLevel/Definitions.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Geometry/Point3D.h"
#include "Event/Utilities/CLHEPStreams.h"
#include "Event/Utilities/IDStreams.h"
// Include all Gaudi container types here
//   to simplify inlude statements in algorithms
#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/ObjectList.h"

#include "idents/VolumeIdentifier.h"

#include "Event/MonteCarlo/McParticle.h"


/** @class McPositionHit
 * @brief Monte Carlo class for a position hit such as tracker
 *
 * The class McPositionHit uses the Class Library for HEP (CLHEP).
 *              
 * @author OZAKI Masanobu
 * Changes:     M.Frank 04/10/1999 : Proper use of SmartRefs and SmartRefVectors
 *              P.Binko 19/10/1999 : Proper accessors of smart references
 *                                   Formating of ASCII output
 *              M.Ozaki 2000-12-05 : Modified for GLAST
 *              M.Ozaki 2001-01-05 : MCPositionHits -> McPositionHit
 * 
 *           M.Frailis
 *     R.Giannitrapani
 *             C.Cecchi 2002-02-29 : Added namespace mc, changed the VolumeID with
 *                                   new VolumeIdentifier
 * $Header
 */

#include "GaudiKernel/IInterface.h"

static const CLID& CLID_McPositionHit = InterfaceID("McPositionHit", 1, 0);

namespace Event { // NameSpace

class McPositionHit : virtual public ContainedObject {
  public:
   
      enum HitType {simulation = 0x40000000,
                    overlayHit = 0x80000000 
                   };

    virtual const CLID& clID() const   { return McPositionHit::classID(); }
    static const CLID& classID()       { return CLID_McPositionHit; }

    /// Constructors
    McPositionHit()
      : m_volumeID(),
        m_entry(),
        m_exit(),
        m_globalEntry(),
        m_globalExit(),
        m_depositedEnergy(0.),
        m_particleEnergy(0.),
        m_particleFourMomentum(),
        m_timeOfFlight(0.),
        m_packedFlags(0)
    {}

    virtual ~McPositionHit() { }

    /// special set
    void init(double edep, 
              idents::VolumeIdentifier id, 
              const HepPoint3D& entry, 
              const HepPoint3D& exit, 
              HitType hitType=simulation);

    /// init methods with both local and global coordinates
    void init(double edep, idents::VolumeIdentifier id, 
              const HepPoint3D& entry, const HepPoint3D& exit,
              const HepPoint3D& gEntry, const HepPoint3D& gExit,
              HitType hitType=simulation);

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

    /// Retrieve entry member in global coordinates
    const HepPoint3D& globalEntryPoint() const;
          HepPoint3D& globalEntryPoint();
    /// Update Entry member in global coordinates
    void setGlobalEntryPoint( const HepPoint3D& value );

    /// Retrieve exit point  in global coordinates
    const HepPoint3D& globalExitPoint() const;
          HepPoint3D& globalExitPoint();
    /// Update exit point in global coordinates
    void setGlobalExitPoint( const HepPoint3D& value );

    /// Retrieve deposited energy
    double depositedEnergy() const;
    /// Update deposited energy
    void setDepositedEnergy( double value );
    /// Retrieve depositing particle's energy
    double particleEnergy() const;
    CLHEP::Hep3Vector particleMomentum() const;
    CLHEP::HepLorentzVector particleFourMomentum() const;
    /// Update depositing particle's energy
    ///void setParticleEnergy( double value );
    void setParticle4Momentum( const CLHEP::HepLorentzVector& fourMom);

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

    /// Retrieve particle ID
    McParticle::StdHepId getMcParticleId()const{return m_mcParticleId;};
    /// Set the particle ID
    void setMcParticleId(McParticle::StdHepId id){m_mcParticleId = id;};

    /// Retrieve ancestor particle ID
    McParticle::StdHepId getOriginMcParticleId()const{return m_originMcParticleId;};
    /// Set the ancestor particle ID
    void setOriginMcParticleId(McParticle::StdHepId id){m_originMcParticleId = id;};

    /// Retrieve pointer to the ancestor McParticle (const or non-const)
    const McParticle* originMcParticle() const;
          McParticle* originMcParticle();
    /// Update pointer to McParticle (by a C++ pointer or a smart reference)
    void setOriginMcParticle( McParticle* value );
    void setOriginMcParticle( SmartRef<McParticle> value );

    /// Provide access to setting/retrieving the "packed flags"
    unsigned long getPackedFlags() const {return m_packedFlags;}
    void setPackedFlags(unsigned long flags) {m_packedFlags  = flags;}
    void addPackedMask(unsigned long mask)   {m_packedFlags |= mask;}

    /// Serialize the object for writing
    virtual StreamBuffer& serialize( StreamBuffer& s ) const;
    /// Serialize the object for reading
    virtual StreamBuffer& serialize( StreamBuffer& s );
    /// Fill the ASCII output stream
    virtual std::ostream& fillStream( std::ostream& s ) const;

  private:
    /// Volume ID
    idents::VolumeIdentifier m_volumeID;
    /// Local coordinates entry point
    HepPoint3D               m_entry;
    /// Local coordinates exit point
    HepPoint3D               m_exit;
    /// Global coordinates entry point
    HepPoint3D               m_globalEntry;
    /// Global coordinates exit point
    HepPoint3D               m_globalExit;
    /// Deposited energy
    double                   m_depositedEnergy;
    /// Depositing particle's energy
    double                   m_particleEnergy;
    CLHEP::HepLorentzVector  m_particleFourMomentum;
    /// Time of flight
    double                   m_timeOfFlight;
    /// ID of the McParticle causing the hit
    McParticle::StdHepId     m_mcParticleId;
    /// ID of the ancestor McParticle
    McParticle::StdHepId     m_originMcParticleId;
    /// Pointer to McParticle causing the hit
    SmartRef<McParticle>     m_mcParticle;
    /// Pointer to the ancestor McParticle
    SmartRef<McParticle>     m_originMcParticle;
    /// Packed flags for the internal use.
    unsigned long            m_packedFlags;
};

inline void McPositionHit::init(double edep, 
                                idents::VolumeIdentifier id, 
                                const HepPoint3D& entry, 
                                const HepPoint3D& exit,
                                HitType type)
{
    m_depositedEnergy = edep;
    m_volumeID        = id;
    m_entry           = entry;
    m_exit            = exit;
    m_packedFlags     = type;
}

inline void McPositionHit::init(double edep, idents::VolumeIdentifier id, 
                                const HepPoint3D& entry, const HepPoint3D& exit,
                                const HepPoint3D& gEntry, const HepPoint3D& gExit,
                                HitType type)
{
    m_depositedEnergy = edep;
    m_volumeID        = id;
    m_entry           = entry;
    m_exit            = exit;
    m_globalEntry     = gEntry;
    m_globalExit      = gExit;
    m_packedFlags     = type;
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




/// Fill the ASCII output stream
inline std::ostream& McPositionHit::fillStream( std::ostream& s ) const
{
  return s
    << "    base class McPositionHit :"
    << "\n        Volume ID             = " << m_volumeID.name()
    << "\n        Entry point (x, y, z) = ( "
    << EventFloatFormat( EventFormat::width, EventFormat::precision )
    << m_entry.x() << ", "
    << EventFloatFormat( EventFormat::width, EventFormat::precision )
    << m_entry.y() << ", "
    << EventFloatFormat( EventFormat::width, EventFormat::precision )
    << m_entry.z() << " )"
    << "\n        Deposited Energy      = "
    << EventFloatFormat( EventFormat::width, EventFormat::precision )
    << m_depositedEnergy
    << "\n        Particle Energy       = "
    << EventFloatFormat( EventFormat::width, EventFormat::precision )
    << m_particleEnergy
    << "\n        Time of flight        = "
    << EventFloatFormat( EventFormat::width, EventFormat::precision )
    << m_timeOfFlight
    << "\n        Exit point (x, y, z)  = ( "
    << EventFloatFormat( EventFormat::width, EventFormat::precision )
    << m_exit.x() << ", "
    << EventFloatFormat( EventFormat::width, EventFormat::precision )
    << m_exit.y() << ", "
    << EventFloatFormat( EventFormat::width, EventFormat::precision )
    << m_exit.z() << " )"
    << "\n        McParticle            = " << m_mcParticle(this)
    << "\n        ancestor McParticle   = " << m_originMcParticle(this);

}

typedef ObjectVector<McPositionHit> McPositionHitVector;
typedef ObjectVector<McPositionHit> McPositionHitCol;
typedef ObjectList<McPositionHit>   McPositionHitList;
}

/*! A small class to use the sort algorithm */
class ComparePosHits {
  public:
    bool operator()(Event::McPositionHit *left, Event::McPositionHit *right)
    {return left->volumeID() < right->volumeID();}

    };

#endif    // Event_McPositionHit_H

