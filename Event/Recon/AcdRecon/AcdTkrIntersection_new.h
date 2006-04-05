#ifndef Event_ACDTKRINTERSECTION_H
#define Event_ACDTKRINTERSECTION_H

#include <vector>
#include "geometry/Point.h"
#include "geometry/Vector.h"

#include "Event/TopLevel/Definitions.h"
#include "idents/AcdId.h"

#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/IInterface.h"

class MsgStream;
class HepMatrix;

static const CLID& CLID_AcdTkrIntersectionCol = InterfaceID("AcdTkrIntersectionCol", 1, 0);

/**
*  @class AcdTkrIntersection
*
*
*  @brief This class stores the results of the reconstruction performed
*  in AcdTkrIntersectAlg. It contains the reconstructed data for one
*  expected intersection of a track with the calorimeter. 
*  
*  \author Eric Charles
*
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/AcdRecon/AcdTkrIntersection.h,v 1.2 2005/11/09 01:11:09 heather Exp $
*/

namespace Event
{
  
  class AcdTkrIntersection 
  {

  public:
    
    AcdTkrIntersection(int trackIndex, 
		       const Point& globalPosition, 		       
		       double arcLength,
		       const Event::AcdTkrLocalCoords& local,
		       unsigned char tileHit);

    virtual ~AcdTkrIntersection() {};
    
    /// Direct access to parameters

    /// Which track did the hitting
    inline int          getTrackIndex()          const {return m_trackIndex; };

    /// Location of hit in global coordinates
    inline const Point& getGlobalPosition()      const {return m_location;    };
    inline Point&       getGlobalPosition()            {return m_location;    };
    
    /// Location (and errors) of hit in tile coordinates
    inline double  getActiveX()             const {return m_activeX; };
    inline double  getActiveY()             const {return m_activeY; };
    inline double  getLocalXXCov()          const {return m_localXXCov; };
    inline double  getLocalYYCov()          const {return m_localYYCov; };
    inline double  getLocalXYCov()          const {return m_localXYCov; };

    /// Distance along track from first hit to tile intersection
    inline double  getArcLengthToIntersection() const { return m_arcLengthToIntersection; } ;
    /// Path length of track through tile
    inline double  getPathLengthInTile()    const { return m_pathlengthInTile; } ;

    /// mask to say if the tile was hit
    inline unsigned char tileHit() const { return m_tileHit; };

    /// set everything at once
    void set(const idents::AcdId& acdId, int trackIndex, 
	     const Point& globalPosition, 
	     const double localPosition[2], const HepMatrix& localCovMatrix,
	     double arcLengthToIntersection, double pathLengthInTile,
	     unsigned char tileHit);
        
    // set the individual values (uncomment as needed)
    //inline void setAcdId(const idents::AcdId& val) { m_tileId = val; };
    //inline void setTrackIndex(int val) { m_trackIndex = val; };
    //inline void setGlobalPosition(const Point& val) { m_location = val; };
    //inline void setLocalPosition(const double localPosition[2]) {
    //  m_localX = localPosition[0];
    //  m_localY = localPosition[1];
    //};
    inline void setCovTerms(double XX, double YY, double XY) {
      m_localXXCov = XX;
      m_localYYCov = YY;
      m_localXYCov = XY;      
    }
    //inline void setArcLength(double val) { m_arcLengthToIntersection = val; };
    inline void setPathLength(double val) { m_pathlengthInTile = val; };
    inline void setTileHit(unsigned char val) { m_tileHit = val; };

    virtual void writeOut(MsgStream& stream) const;
    
  protected:

    virtual void ini();
    
  private:
    
    /// ID of hit tile
    idents::AcdId m_tileId;

    /// index of the related track
    int       m_trackIndex;

    /// Global position of expected hit 
    Point     m_location;
    ///  X Position of the expected hit in Tile Coords
    double    m_localX;
    ///  Y Position of the expected hit in Tile Coords
    double    m_localY;
    
    ///  Covariance terms in expected intersection
    double    m_localXXCov;        // local X Error squared  (x for Top, x for +-y planes, y for +- x plane) 
    double    m_localYYCov;        // local Y Error squared  (y for Top, z for +-x and +-y planes)
    double    m_localXYCov;        // correlation term of local X-Y error   

    ///  Distance from first hit to intersection
    double    m_arcLengthToIntersection;
  
    ///  Pathlength through the ACD tile
    double    m_pathlengthInTile;
    
    ///  Mask to store tile hit
    unsigned char m_tileHit;

  };

   
  /*! 
   * @class AcdTkrIntersectionCol
   *
   *  @brief TDS class  to store the results of the reconstruction performed
   *  in AcdTkrIntersectAlg
   *  
   * It inherits from DataObject
   * (to be a part of Gaudi TDS) and from std::vector of pointers
   * to AcdTkrIntersection objects. Some methods just rename the std::vector
   * methods with the same functionality for backward compartibility.
   *
   *
   * @author Eric Charles
   *
   * @todo replace this class by typedef to ObjectVector, make corresponding
   *       changes in AcdTrkIntersectionAlg
   */
    

  class AcdTkrIntersectionCol : public DataObject, public std::vector<AcdTkrIntersection*> 
  {
  public:
    
    AcdTkrIntersectionCol(const std::vector<AcdTkrIntersection*>& acdTkrIntersections);

    AcdTkrIntersectionCol() { clear();}
    
    /// destructor - deleting the clusters pointed
    /// by the vector elements
    ~AcdTkrIntersectionCol() { delIntersections();}
        
    
    // GAUDI members to be use by the converters
    static const CLID& classID() {return CLID_AcdTkrIntersectionCol;}
    virtual const CLID& clID() const {return classID();}
    
    /// add new cluster
    void add(AcdTkrIntersection* cl) {push_back(cl);}
    
    /// get the number of clusters in collection
    int num()                  const {return size();}
    
    /// get pointer to the cluster with given number 
    AcdTkrIntersection* getIntersection(int i) const {return operator[](i);}
    
    /// delete all intersections pointed by the vector elements
    void delIntersections();
    
    /// write information for all clusters to the ascii file 
    /// for debugging purposes
    virtual void writeOut(MsgStream& stream) const;
    
  protected:
    
    /// does the same function as clear() 
    virtual void ini();
        
  };

}

#endif
