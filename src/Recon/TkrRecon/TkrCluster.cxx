#include "Event/Recon/TkrRecon/TkrCluster.h"

//---------------------------------------------------
//       TkrCluster
//---------------------------------------------------

using namespace Event;

void TkrCluster::writeOut(MsgStream& log) const
{
    // Purpose: writes out debug info
	// Inputs:  message stream
	// Outputs: data written to message stream
	
    log << MSG::DEBUG;
    if (log.isActive()) {
        log << " bilayer " << m_plane << " XY " << (int) m_view
            << " xpos  " << m_position.x()  << " ypos   " << m_position.y()
            << " zpos  " << m_position.z()
            << " i0-if " << m_strip0 <<"-"<< m_stripf;
    }
    log << endreq;
}
