#ifndef Event_AcdRecon_H
#define Event_AcdRecon_H 1

#include <iostream>
#include "idents/AcdId.h"
#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/StreamBuffer.h"
#include "GaudiKernel/DataObject.h"

#include "Event/TopLevel/Definitions.h"

#include <vector>
#include <map>

extern const CLID& CLID_AcdRecon;

namespace Event {
    
/** @class AcdRecon        
* @brief Reconstruction data for ACD
*                                 
* @author Heather Kelly
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/AcdRecon/AcdRecon.h,v 1.2 2002/09/05 20:08:05 heather Exp $          
*/
    class AcdRecon : virtual public DataObject  { 
        
    public:
        AcdRecon()
            : m_totEnergy(0.0),
            m_tileCount(0),
            m_gammaDoca(-99999.0),
            m_doca(-99999.0)
        {};
        
        AcdRecon(double e, int count, double gDoca, double doca, double actDist,
            const idents::AcdId &minDocaId, const std::vector<double> &rowDoca,
            const std::vector<double> &rowActDist,
            const std::map<idents::AcdId,double> &energies)       
            : m_totEnergy(e),
            m_tileCount(count),
            m_gammaDoca(gDoca),
            m_doca(doca),
            m_actDist(actDist),
            m_minDocaId(minDocaId),
            m_rowDocaCol(rowDoca),
            m_rowActDistCol(rowActDist),
            m_energyCol(energies)
            
        {};
        
        virtual ~AcdRecon() { };

        void initialize (double e, int count, double gDoca, double doca, double actDist,
            const idents::AcdId minDocaId, const std::vector<double> &rowDoca,
            const std::vector<double> &rowActDist,
            const std::map<idents::AcdId, double> &energyCol) {
            m_totEnergy = e;
            m_tileCount = count;
            m_gammaDoca = gDoca;
            m_doca = doca;
            m_actDist = actDist;
            m_minDocaId = minDocaId;
            m_rowDocaCol = rowDoca;
            m_rowActDistCol = rowActDist;
            m_energyCol = energyCol;
        };
        
        //! Retrieve reference to class definition structure
        virtual const CLID& clID() const   { return AcdRecon::classID(); }
        static const CLID& classID()       { return CLID_AcdRecon; }
        
        inline const double getEnergy() const { return m_totEnergy; };
        inline const int getTileCount() const { return m_tileCount; };
        inline const double getGammaDoca() const { return m_gammaDoca; };
        inline const double getDoca() const { return m_doca; };
        inline const double getActiveDist() const { return m_actDist; };
        inline const idents::AcdId& getMinDocaId() const { return m_minDocaId; };
        inline const std::vector<double>& getRowDocaCol() const { return m_rowDocaCol; };
        inline const std::vector<double>& getRowActDistCol() const { return m_rowActDistCol; };
        inline const std::map<idents::AcdId, double>& getEnergyCol() const { return m_energyCol; };
        
        /// Serialize the object for writing
        virtual StreamBuffer& serialize( StreamBuffer& s ) const;
        /// Serialize the object for reading
        virtual StreamBuffer& serialize( StreamBuffer& s );
        
        
        friend std::ostream& operator << (std::ostream& s, const AcdRecon& obj)
        {
            return obj.fillStream(s);
        };
        
        /// Fill the ASCII output stream
        virtual std::ostream& fillStream( std::ostream& s ) const;
        
    private:
        
        /// Total energy in MeV deposited in the whole ACD system
        double m_totEnergy;
        /// Total number of ACD tiles above threshold
        int m_tileCount;
        /// Distance of Closest Approach for the reconstructed gamme, 
        /// if there is one
        double m_gammaDoca;
        /// Minimum Distance of Closest Approach for all tracks and all ACD tiles
        double m_doca;
        /// New Bill Atwood DOCA calculation using edge of tiles
        double m_actDist;
        // record of the tile with the minimum Distance of Closest Approach
        idents::AcdId m_minDocaId;
        /// Collection of distance of closest approach calculations
        /// for each side row of the ACD
        /// zeroth element corresponds to the top, and index one corresponds to
        /// the first row closest to the top, etc.
        std::vector<double> m_rowDocaCol;
        /// Collection of Active Distance quantities for each row of the ACD
        /// zeroth element corresponds to the top, and index one corresponds to
        /// the first row closest to the top, etc.
        std::vector<double> m_rowActDistCol;
        
        /// Stores reconstructed energy per ACD digi
        std::map<idents::AcdId, double> m_energyCol;
        
    };
    
    
    /// Serialize the object for writing
    inline StreamBuffer& AcdRecon::serialize( StreamBuffer& s ) const
    {
        DataObject::serialize(s);
        return s
            << m_totEnergy
            << m_tileCount
            << m_gammaDoca
            << m_doca;
    }
    
    
    /// Serialize the object for reading
    inline StreamBuffer& AcdRecon::serialize( StreamBuffer& s )
    {
        DataObject::serialize(s);
        
        s >> m_totEnergy
            >> m_tileCount
            >> m_gammaDoca
            >> m_doca;
        
        return s;
    }
    
    
    /// Fill the ASCII output stream
    inline std::ostream& AcdRecon::fillStream( std::ostream& s ) const
    {
        return s
            << "    base class AcdRecon :"
            << "\n        total energy      = "
            << EventFloatFormat( EventFormat::width, EventFormat::precision )
            << m_totEnergy << ", "
            << "\n        tile Count              = "
            << EventFloatFormat( EventFormat::width, EventFormat::precision )
            << m_tileCount   << " )"
            << "\n        gamma DOCA     = "
            << m_gammaDoca << " )"
            << "\n        DOCA     = "
            << EventFloatFormat( EventFormat::width, EventFormat::precision )
            << m_doca << " )";
    }
    
    
} // namespace Event

#endif    // Event_AcdRecon_H

