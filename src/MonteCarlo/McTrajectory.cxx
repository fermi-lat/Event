// $Header: /nfs/slac/g/glast/ground/cvs/Event/src/MonteCarlo/McTrajectory.cxx,v 1.8 2002/05/10 01:56:21 richard Exp $

#include <iostream>
#include <math.h>
#include "Event/MonteCarlo/McTrajectory.h"
#include "Event/Utilities/CLHEPStreams.h"


namespace Event{

/// Retrieve pointer to McParticle (const or non-const)
const McParticle* McTrajectory::getMcParticle() const
{
    return m_mcParticle; 
}
McParticle* McTrajectory::getMcParticle()
{
    return m_mcParticle; 
}


/// Update pointer to McParticle (by a C++ pointer or a smart reference)
void McTrajectory::setMcParticle( McParticle* value )
{
    m_mcParticle = value; 
}
void McTrajectory::setMcParticle( SmartRef<McParticle> value )
{ 
    m_mcParticle = value; 
}


void McTrajectory::addPoints(std::vector<Hep3Vector>& points)
{
  m_points = points;
}

}
