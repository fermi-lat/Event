
#ifndef CalRecon_CalXtalRecData_H
#define CalRecon_CalXtalRecData_H 1

#include <iostream>
#include <vector>
#include "idents/CalXtalId.h"

#include "GaudiKernel/Kernel.h"
#include "GaudiKernel/StreamBuffer.h"

#include "GaudiKernel/ObjectVector.h"
#include "GaudiKernel/ContainedObject.h"
#include "Event/TopLevel/Definitions.h"
#include "geometry/Point.h"

#include "GaudiKernel/IInterface.h"

static const CLID& CLID_CalXtalRecData = InterfaceID("CalXtalRecData", 1, 0);

/**
* @class   CalXtalRecData        
*
* @brief TDS class containing reconstructed data for
* one calorimeter crystal
*
* This class stores the reconstructed data  in the vector
* of CalRangeRecData objects (data member m_recData).
* This vector contains 1 or 4 elements,
* depending on  readout mode defined by private data member 
* m_mode (BESTRANGE or ALLRANGE).
* The first element of the vector always contains information
* for the best range, as it was defined during readout process.
*
* Data member m_xtalId contains crystal identification.
* 
* ObjectVector of CalXtalRecData is typedefed as CalXtalRecCol
* and used to store crystal reconstructed data for whole calorimeter. 
* 
* @author  A.Chekhtman
*
* $Header: /nfs/slac/g/glast/ground/cvs/Event/Event/Recon/CalRecon/CalXtalRecData.h,v 1.15 2008/10/21 19:31:38 usher Exp $
*/
namespace Event 
{
    class CalXtalRecData : virtual public ContainedObject { 
        
    public:
	    /// Retrieve reference to class definition structure
 	    virtual const CLID& clID() const   {return CalXtalRecData::classID(); }
	    static const CLID& classID()       {return  CLID_CalXtalRecData; }

        /* enum to define status bits in status word
        ** XTAL_BAD_POSITION   - bad position information for this crystal
        */
        enum statusBits {
            XTAL_BAD_POSITION    = 0x00000001,    // When set indicates position information is "bad" for this xtal
                                                  // INSERT NEW BITS IN THIS AREA (with trailing comma)
            XTAL_BAD             = 0x80000000     // When set indicates all crystal information is not good
        };

        
        /** @class   CalRangeRecData        
        * 
        * @brief   This is teh nested class in CalXtalRecData,
        *          holding reconstructed data for one readout range.
        *
        *          The class contains reconstructed position
        *          and for both POSitive and NEGative faces of a crystal
        *          the reconstructed energy and the range number used
        *          to obtain this energy.           
        *
        *
        * @author  A.Chekhtman
        */
        class CalRangeRecData {  
            
        public:

            /// constructor initializing energies and ranges
            /// and setting position to zero.
            CalRangeRecData(const char rangeP,
                            const double eneP,
                            const char rangeM,
                            const double eneM) :
                  m_eneP(eneP), 
                  m_eneM(eneM),
                  m_pos(Point(0.,0.,0.)),
                  m_rangeP(rangeP), 
                  m_rangeM(rangeM) 
              {};
              
	    ~CalRangeRecData() {};
              
	    /// The separate setting function for reconstructed position
	    /// is needed, because position reconstruction is performed              
	    /// later, than energy reconstruction and is based
	    /// on reconstructed energies
	    void setPosition (const Point pos) { m_pos = pos;}
              
	    /// retrieve position value
	    Point getPosition() const { return m_pos;}
              
            /// Retrieve average energy of two faces for the best range
            inline double getEnergy() const
            {
              return (getEnergy(idents::CalXtalId::POS)
                      +getEnergy(idents::CalXtalId::NEG))/2;
            }

	    /// retrieve energy from specified face
	    inline double getEnergy(const idents::CalXtalId::XtalFace face) const
              {return face == idents::CalXtalId::POS ? m_eneP : m_eneM;}
              
	    /// retrieve energy range from specified face
	    inline char getRange(const idents::CalXtalId::XtalFace face) const 
              {return face == idents::CalXtalId::POS ? m_rangeP : m_rangeM;}
              
              
        private:
            

            /// reconstructed energy for POSitive face
            double m_eneP;

            /// reconstructed energy for NEGative face
            double m_eneM;

            /// reconstructed position
            Point m_pos;

            /// energy range for POSitive face
            char m_rangeP;
            
            /// energy range for NEGative face
            char m_rangeM;
            
        };
        
        /// default constructor
        CalXtalRecData() : m_statusBits(0) {};
        
        /// constructor with parameters initializing crystal
        /// identification and readout mode
        CalXtalRecData(const idents::CalXtalId::CalTrigMode mode,
                       const idents::CalXtalId CalXtalId) : 
                       m_statusBits(0), m_mode(mode), m_xtalId(CalXtalId){};
        
        virtual ~CalXtalRecData() { };
        
        /// function initializing crystal identification, readout mode, and clearing rec data
        void initialize (const unsigned int bits,
                         const idents::CalXtalId::CalTrigMode m,
                         const idents::CalXtalId id)
        {m_statusBits = bits; m_mode = m; m_xtalId = id; m_recData.clear() ; }

        /// Retrieve entire status word
        inline const unsigned int getStatusWord() const    {return m_statusBits;}

        /// Is position information good?
        inline const bool isPositionGood() const {return !(m_statusBits & XTAL_BAD_POSITION);}

        /// Set status bit
        inline void setStatusBit(const statusBits& bit)    {m_statusBits |= bit;}

        /// Set entire status word
        inline void setStatusBits(const unsigned int bits) {m_statusBits = bits;}
        
        /// Retrieve readout mode
        inline const idents::CalXtalId::CalTrigMode getMode() const
        { return m_mode; };

        inline int getNReadouts() const { return m_recData.size(); }
        
        /// Retrieve crystal identifier
        inline const idents::CalXtalId getPackedId() const
        { return m_xtalId; };
        
        /// Add one more readout range to the reconstructed data vector
        inline void addRangeRecData(const CalRangeRecData r) { m_recData.push_back(r); } 
        
        /// Retrieve energy range for selected face and readout
        /// returns -1 if readout with requested index doesn't exist
        inline char getRange(const unsigned short readoutIndex,
                             const idents::CalXtalId::XtalFace face) const
        {
            return (readoutIndex < int(m_recData.size())) ? 
                   ((m_recData[readoutIndex])).getRange(face) : (char)-1;
        }
        
        /// Retrieve energy for selected face and readout
        /// returns -1 if readout with requested index doesn't exist
        inline double getEnergy(const unsigned short readoutIndex,
                                const idents::CalXtalId::XtalFace face) const
        {
            return (readoutIndex < int(m_recData.size())) ? 
                   ((m_recData[readoutIndex])).getEnergy(face) : (short)-1;
        }
        
        
        /// Retrieve average energy of two faces for the best range
        inline double getEnergy() const
        {
            return (sqrt(getEnergy(0,idents::CalXtalId::POS)*
                         getEnergy(0,idents::CalXtalId::NEG)));
        }
        
        /// Retrieve the position for the best range (for const objects)
        inline Point getPosition() const
        {
            return getRangeRecData(0)->getPosition();
        }
        
        /// Retrieve reconstructed data from both ends of selected readout
        /// (for const objects)
        inline const CalRangeRecData* getRangeRecData(const unsigned short readoutIndex) const
        {
            if ( readoutIndex < int(m_recData.size()) )
                return &(m_recData[readoutIndex]);
            else
                return 0;
            
        }
        
        /// Retrieve energy from selected range and face
        inline double getEnergySelectedRange(const char range,
                                             const idents::CalXtalId::XtalFace face) const
        {
            
            // get number of ranges as the size of m_recData vector
            char nRanges = (char)m_recData.size();

            // if there is only one range
            if (nRanges == 1)
                
                // and the range number corresponds to what is requested
                // return energy,
                // otherwise return -1
                return (range == ((m_recData[0])).getRange(face)) ?
                       ((m_recData[0])).getEnergy(face) : -1.0;
            
            // if there are 4 ranges - they are stored in increasing order,
            // starting with best range and returning to 0 after 3
            else
                // calculate the index for requested range and return the energy
                return ((m_recData[(nRanges + range -
                ((m_recData[0])).getRange(face)) % nRanges])).getEnergy(face);
        }
                
        
private:

    /// Bit mask to contain status information
    unsigned int                   m_statusBits;
    
    /// Cal readout mode is based on trigger type
    idents::CalXtalId::CalTrigMode m_mode;

    /// crystal ID
    idents::CalXtalId              m_xtalId;

    /// ranges and pulse heights
    std::vector<CalRangeRecData>   m_recData;
    
};

typedef ObjectVector<CalXtalRecData> CalXtalRecCol;    

}


#endif
