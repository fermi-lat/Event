#include "Event/Recon/TkrRecon/TkrCluster.h"

//---------------------------------------------------
//       TkrCluster
//---------------------------------------------------

using namespace Event;

TkrCluster::TkrCluster(int id, int ilayer, int v,
                       int istrip0, int istripf, Point position, double ToT, int tower)
					   
{
	// Purpose and method: makes a cluster with attributes
	// Input:  id is the sequential cluster number
	//         v  is the measured view (0->X, 1->Y)
	//         ilayer is the bilayer number (0 at the front)
	//         istrip0 is the first strip in the cluster
	//         istripf is the last strip in the cluster
	//         ToT is the time-over-threshold for this cluster
	//         tower is the tower number
	// Output: a cluster
	// Dependencies: none
	// Caveats: none
	
    m_id     = id;
	m_view   = intToView(v);
	
	m_plane  = ilayer;
	
	m_strip0 = istrip0;
	m_stripf = istripf;
	
	m_position = position;
	
	m_ToT    = ToT;
    m_tower  = tower;
	
    m_flag   = false;
}

void TkrCluster::writeOut(MsgStream& log) const

{
    // Purpose: writes out debug info
	// Inputs:  message stream
	// Outputs: data written to message stream
	
	log << MSG::DEBUG << " plane " << m_plane << " XY " << (int) m_view;
    log << MSG::DEBUG << " xpos  " << m_position.x()  << " ypos   " << m_position.y();
    log << MSG::DEBUG << " zpos  " << m_position.z();
    log << MSG::DEBUG << " i0-if " << m_strip0 <<"-"<< m_stripf;
    log << MSG::DEBUG <<endreq;
}
//---------  Private --------------------------------


int TkrCluster::chip()     
{ 
	// Purpose: returns chip number of this cluster
	// Method: calculated from the strip number
	return m_strip0/64;
}

double TkrCluster::strip() 
{ 
	// Purpose: return the center strip number
	// Method: average of first and last strip
	// Caveat: may be half-integer
	return 0.5*(m_strip0+m_stripf);
}

double TkrCluster::size()  
{ 
	// Purpose: returns number of strips in the cluster
	return fabs(m_stripf-m_strip0) + 1.;
}

TkrCluster::view TkrCluster::intToView(int iv)

{
	// Purpose: converts a view number to an enum
	
	TkrCluster::view v = XY;
	if (iv == 0) v = X;
	else if (iv == 1) v =Y;
	return v;
}


int TkrCluster::viewToInt(TkrCluster::view v)

{
	// Purpose: converts an enum to an integer
	
	if (v == TkrCluster::XY) return 2;
	return (v == TkrCluster::X? 0:1);
}
