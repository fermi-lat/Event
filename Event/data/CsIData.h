// $Header:$

#ifndef CSI_DATA_H
#define CSI_DATA_H 1
#pragma warning(disable: 4786)

#include "instrument/XtalId.h"

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include "geometry/Point.h"
#include "instrument/ModuleId.h"

#include "Gaudi/Kernel/Kernel.h"
#include "Gaudi/Kernel/DataObject.h"
#include "GlastEvent/Utilities/CellID.h"

class CsIDetector;

extern const CLID& CLID_CsIData;


/*! \class CsIData
\The First attempt at addapting CsIData from the data package to be a
TDS object. Very preliminary and untested.

*/

class CsIData : virtual public DataObject
{
public:
/*! Inner class used to store data on the individual crystals
    */
    class Xtal 
    {
        
        
    private:
        friend class CsIData;
    public:
        
        Xtal (Point p, float e, ModuleId m, int i, float Left, float Right, std::vector<double> diodes_energy)
            : pos(p), energy(e), id(i), Lresp(Left), Rresp(Right), module(m), Diodes_Energy(diodes_energy)
        {}
        Xtal (Point p, float e, ModuleId m, int i, float Left, float Right)
            : pos(p), energy(e), id(i), Lresp(Left), Rresp(Right), module(m), Diodes_Energy(4,0.)
        {}
        
        
        
    private:
        
        //! Data Members for Class Attributes
        Point pos;
        float energy;
        int id;
        float Lresp;
        float Rresp;
        ModuleId module;
        std::vector<double> Diodes_Energy;
    };
    
    
    
    public:
        CsIData (int numLayers);
        
        
        //	---(deprecated)-- access functions for data
        //	analysis------------------------
        ~CsIData ();
        
        //!	number of hit towers in the layer layer=0..
        int nHits (unsigned int layer) const;
        
        //!	energy recorded in the ith tower
        float energy (unsigned int layer, unsigned int n) const;
        
        //!	position of the center of the crystal
        Point xtalPos (unsigned int layer, unsigned int n) const;
        
        //!	access to module id if desired
        ModuleId moduleId (unsigned int layer, unsigned int n) const;
        
        
        //!	access to xtal  id if desired
        unsigned int xtalId (unsigned int layer, unsigned int n) const;
        
        float Lresp (unsigned int layer, unsigned int n) const;
        
        //!	Left and Right response of this xtal
        float Rresp (unsigned int layer, unsigned int n) const;
        
        //!   energy deposited in each of 4 diodes (left-big, right-big, left-small,right-small)
        const std::vector<double>& Diodes_Energy(unsigned int layer, unsigned int n) const; 
        
        //!load local array using the Calorimeter controllers
        void load (const CsIDetector& xtal);
        
        //!read data from an open stream
        void readData (std::istream& in);
        
        //!write data to an open stream
        void writeData (std::ostream& out) const;
        
        void clear ();
        
        /* Will need for the PDS
        
          //! Serialize the object for reading
          virtual StreamBuffer& serialize( StreamBuffer& s );
          //! Serialize the object for writing
          virtual StreamBuffer& serialize( StreamBuffer& s ) const;
          //! Fill the ASCII output stream
          virtual std::ostream& fillStream( std::ostream& s ) const;
        */
        
        
    protected:
    private:
        
        
        //!	data: id followed by left, right response (keV units)
        std::map< XtalId, std::pair< int, int > > m_xtals;
        
        //!	storage is a list of lists (deprecated)
        std::vector< std::vector< class Xtal >* > calorList;
        
        
        
        
};

        
#endif
