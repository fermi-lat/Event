//  associated with Tracker for all the evt Status
//
//---------------------------------------------------

#ifndef TKRCLUSTER_H
#define TKRCLUSTER_H 1

#include <vector>
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/DataObject.h"
#include "GaudiKernel/ContainedObject.h"

#include "geometry/Point.h"

/** 
* @class TkrCluster
*
* @brief Contains the data members which specify a TKR cluster, 
* and access methods
*
* Adapted from SiCluster of Jose Hernando
*
* @author Tracy Usher, Leon Rochester
*
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/TkrRecon/TkrCluster.h,v 1.5 2004/03/11 05:15:13 heather Exp $
*/

extern const CLID& CLID_TkrCluster;

namespace Event { //Namespace

    class TkrCluster : virtual public ContainedObject
    {
    public:

        /// enumeration of the view of the cluster
        enum view 
        {
            X, /**< cluster measures X */ 
            Y, /**< cluster measures Y */ 
            XY /**< not valid for clusters */
        };

        enum {Version=1};

        enum {
            fieldRawToT  = 0xff,  // for the raw ToT < 256
            fieldFlag    = 1,     // "used" flag
            fieldEnd     = 3,     // end for this hit 2 = mixed
            fieldVersion = 3      // 0 for old style
        };
        enum {
            shiftRawToT  = 8,     
            shiftFlag    = 0,  // to preserve compatibility with old form
            shiftEnd     = 1,
            shiftVersion = 30
        };
        enum {
            maskRawToT  = fieldRawToT<<shiftRawToT, 
            maskFlag    = fieldFlag<<shiftFlag,
            maskEnd     = fieldEnd<<shiftEnd,
            maskVersion = fieldVersion<<shiftVersion
        };

        enum {NPLANES=18};

        TkrCluster(){}
        /// Constructor with arguments
        /**
        * Construct a cluster with all of its private members set
        * @param id Sequential ID of cluster
        * @param v  View of cluster (x=0, y=1)
        * @param istrip0  first strip
        * @param istripf  last strip
        * @param ToT 
        * @param tower tower number
        */
        TkrCluster(int id, int ilayer, int v, int istrip0, int istripf, 
            Point position, double ToT, int tower, int rawToT, int end) 
            : m_id(id), m_view(intToView(v)), m_plane(ilayer),
            m_strip0(istrip0), m_stripf(istripf), m_position(position),
            m_ToT(ToT), m_tower(tower), m_flag(Version<<shiftVersion) 
        {
            m_flag = m_flag | maskRawToT&(rawToT<<shiftRawToT);  
            m_flag = m_flag | maskEnd&(end<<shiftEnd);
        }
         TkrCluster(int id, int ilayer, int v, int istrip0, int istripf, 
            Point position, double ToT, int tower, int status) 
            : m_id(id), m_view(intToView(v)), m_plane(ilayer),
            m_strip0(istrip0), m_stripf(istripf), m_position(position),
            m_ToT(ToT), m_tower(tower), m_flag(status)
         {}

       virtual ~TkrCluster() {}

        //! Retrieve pointer to class defininition structure
        virtual const CLID& clID() const   { return TkrCluster::classID(); }
        static const CLID& classID()       { return CLID_TkrCluster; }

        /// sets the flag of a cluster
        inline void flag(int flag=1) {
            if (flag==0) {
                unflag();
            } else {
                m_flag = ( m_flag&maskVersion ? ((m_flag&~maskFlag) | (1<<shiftFlag)) : 1);
            }
        }
        /// clears the flag of a cluster
        inline void unflag() {
            m_flag = ( m_flag&maskVersion ? m_flag&~maskFlag : 0);
        }

        inline int  tower()      const {return m_tower;}
        inline int  id()         const {return m_id;}
        inline int  plane()      const {return m_plane;}
        inline view v()          const {return m_view;}
        inline int  firstStrip() const {return m_strip0;}
        inline int  lastStrip()  const {return m_stripf;}
        inline double ToT()      const {return getRawToT();}

        int chip()	             const {return m_strip0/64;}
        double strip()           const {return 0.5*(m_strip0+m_stripf);}
        double size ()           const {return std::abs(m_stripf-m_strip0) + 1.;}

        Point position()         const {return m_position;}

        /// tests if hit is used on a track
        bool hitFlagged() const {
            return ( m_flag&maskVersion ? ((m_flag&maskFlag)!=0) : (m_flag!=0) );
        }

        /// writes out the information of the cluster if msglevel is set to debug
        void writeOut(MsgStream& log) const;

        /// converts the view integer to enum view
        static enum view intToView(int iv) {
            TkrCluster::view v = XY;
            if (iv == 0) v = X;
            else if (iv == 1) v =Y;
            return v;
        }

        /// converts enum to int; guarantees that X->0 and Y->1
        static int viewToInt(view v)
        {
            if (v == TkrCluster::XY) return 2;
            return (v == TkrCluster::X? 0:1);
        }
        /// retrieves raw ToT (will be raw or corrected depending on the version)
        inline double getRawToT() const { 
            return ( m_flag&maskVersion ? (m_flag&maskRawToT)>>shiftRawToT : m_ToT );
        }
        /// retrieve corrected ToT (zero for old-style records)
        inline double getMips() const {
            return ( m_flag&maskVersion ? m_ToT : 0.0 );
        }
        // retrieve full status word
        inline int getStatusWord() const { return m_flag; }
        /// retrieve end
        inline int getEnd() const {
            return ( m_flag&maskVersion ? m_flag&(maskEnd>>shiftEnd) : 2 );
        }
        /// retrieve version number (old-style is zero)
        inline int getVersion() const {
            return m_flag&maskVersion>>shiftVersion;
        }

    private:

        /// tower id (should be idents/TowerId)
        int m_tower;
        /// not plane; actually recon layer number
        int m_plane;
        /// view (X or Y [XY is illegal here)
        TkrCluster::view m_view;

        /// initial strip address of the cluster
        int m_strip0;
        /// final strip address of the cluster
        int m_stripf;
        /// ToT value, raw or corrected, depends on version
        double m_ToT;
        /// space position of the cluster
        Point m_position;

        /// id of the cluster, sequential in order of construction
        int m_id;
        /// used flag, or status word, depends on version
        int m_flag;

    };

}; //Namespace

#endif // TKRCLUSTER_H
