
#ifndef TkrTrackHit_H
#define TkrTrackHit_H

#include "GaudiKernel/SmartRefVector.h"
#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/ContainedObject.h"
#include "GaudiKernel/SmartRef.h"
#include "GaudiKernel/IInterface.h"

#include "Event/Recon/TkrRecon/TkrCluster.h"
#include "Event/Recon/TkrRecon/TkrTrackParams.h"

#include "idents/TkrId.h"

/** 
* @class TkrTrackHit
*
* @brief This contained data object holds summary information for each plane enountered
*        by a track as it traverses the tracker, and also holds the four sets of track
*        parameters:
*        MEASURED:   Contains the measured coordinates and associated covariance matrix
*        PREDICTED   The values predicted from extrapolating from a previous set of hits
*        FILTERED    The "filtered" values from the Kalman Filter fit
*        SMOOTHED    The "smoothed" values from the Kalman Filter fit
*
* @author Bill Atwood, Leon Rochester, Johann Cohen-Tanugi, Tracy Usher
*
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/TkrRecon/TkrTrackHit.h,v 1.9 2005/02/07 20:35:20 lsrea Exp $
*/

static const CLID& CLID_TkrTrackHit = InterfaceID("TkrTrackHit",  1, 1);

namespace Event { // Namespace

// Move this to TkrCluster eventually
typedef SmartRef<Event::TkrCluster> TkrClusterPtr;

class TkrTrackHit : virtual public ContainedObject
{
public:
  /** The ParamType enum defines the possible "types" of track parameters:
   * - MEASURED  = Measured values from the tracker Si planes
   * - PREDICTED = Projected estimated values from previous plane
   * - FILTERED  = Parameters from track fit (KF filter stage)
   * - SMOOTHED  = Parameters from Kalman Filter smoothing stage
   * - QMATERIAL = For access to the contribution from scattering
   * - UNKNOWN}  = Unknown
   */
    enum ParamType  {MEASURED,               // Measured values from the tracker Si planes
                     PREDICTED,              // Projected estimated values from previous plane
                     FILTERED,               // Parameters from track fit (KF filter stage)
                     REVFIT,                 // Parameters from track fit (KF filter stage)
                     SMOOTHED,               // Parameters from Kalman Filter smoothing stage
                     QMATERIAL,              // For access to the contribution from scattering
                     UNKNOWN};               // Unknown

    /// Status word bits organized like:
    /// low:   |  0   0   0   0  |  0   0   0   0  |  0   0   0   0  |  0   0   0   0   |
    ///         < volume info  >  <   hit type    > <    track fitting status          >
    /// high:  |  0   0   0   0  |  0   0   0   0  |  0   0   0   0  |  0   0   0   0   |
    ///                                                                < more hit type >
    enum StatusBits {HITONFIT     = 0x0001,  // Hit is used in the fit
                     HASMEASURED  = 0x0002,  // Hit has valid measured parameters
                     HASPREDICTED = 0x0004,  // Hit has valid predicted parameters
                     HASFILTERED  = 0x0008,  // Hit has valid filtered parameters
                     HASSMOOTHED  = 0x0010,  // Hit has valid smoothed parameters
                     HASMATERIAL  = 0x0020,  // Hit has valid material matrix
                     UPWARDS      = 0x0040,  // Track direction is upwards (tz > 0)

                     HITISSSD     = 0x0100,  // Hit comes from a SSD
                     HITISDEADST  = 0x0200,  // Hit coresponds to a dead SSD Strip
                     HITISGAP     = 0x0400,  // Hit comes from gap between SSDs
                     HITISTWR     = 0x0800,  // Hit comes outside live SSD plane

                     MEASURESX    = 0x1000,  // Plane measures in X direction
                     MEASURESY    = 0x2000,  // Plane measures in Y direction
                     HASVALIDTKR  = 0x8000,  // Valid track volume identifier

                     HITISUNKNOWN = 0x10000, // Missing cluster, but fails all tests
                     HITISDEADPLN = 0x20000  // Entire plane is dead
    };


    /// Default (null) constructor (just in case...)
    TkrTrackHit() : m_statusBits(0), m_cluster(), m_hitID(0,0,0,false), 
                    m_zPlane(0), m_energy(0), m_radLen(0), m_activeDist(0),
                    m_chiSquareFilter(0.), m_chiSquareSmooth(0.) {}

    /// Construct all but the track parameters, they must be set during recon stage
    TkrTrackHit(Event::TkrCluster* cluster,
                idents::TkrId      tkrID,
                const double       hitZ,
                const double       hitEnergy,
                const double       hitRadLen,
                const double       hitActDist,
                const double       hitChiFilter,
                const double       hitChiSmooth) :
                    m_statusBits(0), m_cluster(cluster), m_hitID(tkrID), m_zPlane(hitZ), 
                    m_energy(hitEnergy), m_radLen(hitRadLen), m_activeDist(hitActDist),
                    m_chiSquareFilter(hitChiFilter), m_chiSquareSmooth(hitChiSmooth)
    {
        if (m_cluster != 0)  m_statusBits  = HITISSSD | HITONFIT;
        if (tkrID.hasTray()) m_statusBits |= HASVALIDTKR;
    }

    //! Destructor
   virtual ~TkrTrackHit() {return;}

    //! Gaudi stuff: Retrieve pointer to class defininition structure
    virtual const CLID& clID()                 const   { return TkrTrackHit::classID(); }
    static  const CLID& classID()                      { return CLID_TkrTrackHit;       }

    /// Access the status bits to determine details of the hit
    inline const unsigned int  getStatusBits() const {return m_statusBits;}

    /// Answer quick questions based on status bits
    inline const bool validCluster()      const {return  m_cluster != 0;}
    inline const bool hitUsedOnFit()      const {return (m_statusBits & HITONFIT    ) == HITONFIT;}
    inline const bool validMeasuredHit()  const {return (m_statusBits & HASMEASURED ) == HASMEASURED;}
    inline const bool validPredictedHit() const {return (m_statusBits & HASPREDICTED) == HASPREDICTED;}
    inline const bool validFilteredHit()  const {return (m_statusBits & HASFILTERED ) == HASFILTERED;}
    inline const bool validSmoothedHit()  const {return (m_statusBits & HASSMOOTHED ) == HASSMOOTHED;}
    inline const bool validMaterial()     const {return (m_statusBits & HASMATERIAL ) == HASMATERIAL;}
    inline const bool upwards()         const {return (m_statusBits & UPWARDS ) == UPWARDS;}

    /// Access the hit's associated information
    inline const TkrClusterPtr getClusterPtr()      const {return m_cluster;   }
    inline const double        getZPlane()          const {return m_zPlane;    }
    inline const double        getEnergy()          const {return m_energy;    }
    inline const double        getRadLen()          const {return m_radLen;    }
    inline const double        getActiveDist()      const {return m_activeDist;}
    inline const double        getChiSquareFilter() const {return m_chiSquareFilter;}
    inline const double        getChiSquareRevFit() const {return m_chiSquareRevFit;}
    inline const double        getChiSquareSmooth() const {return m_chiSquareSmooth;}
    inline const idents::TkrId getTkrId()           const {return m_hitID;          }

    /// Allow rudimentary access to the hit information here 
    /// Method to return index to give TkrTrackParams for returning specifc parameter
    enum SSDDirection  {SSDMEASURED, SSDNONMEASURED};

    const int getParamIndex(TkrTrackHit::SSDDirection meas, TkrTrackParams::ParamType type) const; 
    int       getParamIndex(TkrTrackHit::SSDDirection meas, TkrTrackParams::ParamType type); 

    const Point                getPoint(TkrTrackHit::ParamType type)      const;
    Point                      getPoint(TkrTrackHit::ParamType type);
    const Vector               getDirection(TkrTrackHit::ParamType type)  const;
    Vector                     getDirection(TkrTrackHit::ParamType type);
    const double               getMeasuredPosition(TkrTrackHit::ParamType type) const;
    const double               getMeasuredSlope(TkrTrackHit::ParamType type) const;
    const double               getNonMeasuredPosition(TkrTrackHit::ParamType type) const;
    const double               getNonMeasuredSlope(TkrTrackHit::ParamType type) const;

    /// Direct access to track params
    const TkrTrackParams& getTrackParams(ParamType type) const;

    /// Set methods used during pattern recognition/track fit stages
    inline void setClusterPtr(Event::TkrClusterPtr cluster) {m_cluster         = cluster;}
    inline void setTkrID(idents::TkrId& tkrID)              {m_hitID           = tkrID;  }
    inline void setEnergy(const double energy)              {m_energy          = energy; }
    inline void setZPlane(const double z)                   {m_zPlane          = z;}
    inline void setRadLen(const double rl)                  {m_radLen          = rl;}
    inline void setActiveDist(const double d)               {m_activeDist      = d;}
    inline void setChiSquareFilter(const double c)          {m_chiSquareFilter = c;}
    inline void setChiSquareRevFit(const double c)          {m_chiSquareRevFit = c;}
    inline void setChiSquareSmooth(const double c)          {m_chiSquareSmooth = c;}

    inline void setStatusBit(unsigned int bitToSet)         {m_statusBits      |=  bitToSet;}
    inline void clearStatusBit(StatusBits bitToClear)       {m_statusBits      &= ~bitToClear;}

    /// These methods provide direct "helper" class access to track parameters
    void            setTrackParams(ITkrTrackParamsAccess& access, ParamType type);
    TkrTrackParams& getTrackParams(ParamType type);

    /// Methods used in reconstruction?? Are they necessary?
    void clean();   // clean the PRED - FIT - SMOOTH values but not the MEAS
    void clear();   // clean everything
    std::ostream& fillStream( std::ostream& s ) const;
    
private:
    inline const double getCoordinate(const TkrTrackParams& params, int coord) const;
    inline double       getCoordinate(const TkrTrackParams& params, int coord);

    unsigned int    m_statusBits;      // See StatusBits enumeration above for definitions
    TkrClusterPtr   m_cluster;         // Pointer to the cluster associated with this hit
    idents::TkrId   m_hitID;           // Complete TkrId identifying the details of this hit/plane
    double          m_zPlane;          // Z location of plane
    double          m_energy;          // Energy of track at this plane
    double          m_radLen;          // Radiation Lengths encountered from the previous hit
    double          m_activeDist;      // The distance inside (positive) hit SSD (neg. if outside)
    double          m_chiSquareFilter; // hit chi-square at filter stage of fit
    double          m_chiSquareRevFit; // hit chi-square at filter stage of fit
    double          m_chiSquareSmooth; // hit chi-square at smooth stage of fit
        
    TkrTrackParams m_hitMeas;
    TkrTrackParams m_hitPred;
    TkrTrackParams m_hitFit;
    TkrTrackParams m_hitRevFit;
    TkrTrackParams m_hitSmooth;
    TkrTrackParams m_Qmaterial;  // holds the covariance matrix of the material effects 
};

//typedef for the Container (to be stored in the TDS)
typedef ObjectVector<TkrTrackHit>          TkrTrackHitCol;
typedef TkrTrackHitCol::const_iterator     TkrTrackHitColConItr;
typedef TkrTrackHitCol::iterator           TkrTrackHitColItr;

// typedef for creating a vector in the main track object
typedef SmartRefVector<TkrTrackHit>        TkrTrackHitVec;
typedef TkrTrackHitVec::const_iterator     TkrTrackHitVecConItr;
typedef TkrTrackHitVec::iterator           TkrTrackHitVecItr;

// Define for sorting of hits (is this used?)
bool operator<(const TkrTrackHit&, const TkrTrackHit&); 
bool operator==(const TkrTrackHit&, const TkrTrackHit&); 

// Inline functions here
inline double TkrTrackHit::getCoordinate(const TkrTrackParams& params, int coord) 
              {return params(coord);}
inline const double TkrTrackHit::getCoordinate(const TkrTrackParams& params, int coord) const 
              {return params(coord);}

}; //Namespace

#endif
