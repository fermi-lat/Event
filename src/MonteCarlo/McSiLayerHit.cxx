/**
 * @class McSiLayerHit
 *
 * @brief Implements a Gaudi Tool for setting the candidate track energies before 
 *        the track fit
 *
 * @author The Tracking Software Group
 *
 * $Header: /nfs/slac/g/glast/ground/cvs/TkrRecon/src/MonteCarlo/McSiLayerHit.cxx,v 1.2 2003/08/19 00:17:54 usher Exp $
 */
#include "Event/MonteCarlo/McSiLayerHit.h"

namespace Event {
McSiLayerHit::McSiLayerHit(const Event::McParticle* particle): 
m_McParticle(particle), m_cluster(0), m_statusBits(0)
{
    m_PositionHitsVec.clear();
}

McSiLayerHit::~McSiLayerHit()
{
    return;
}

void McSiLayerHit::addMcPositionHit(const Event::McPositionHit* posHit)
{
    if (m_PositionHitsVec.size() == 0)
    {
        m_volIdent = posHit->volumeID();
    }

    m_PositionHitsVec.push_back(posHit);

    return;
}

void McSiLayerHit::setTkrCluster(const Event::TkrCluster* cluster) 
{
    m_cluster = cluster;

    if (cluster) m_statusBits |= McSiLayerHit::CLUSTERHIT;
}

const HepPoint3D McSiLayerHit::getHitPosition() const
{
    double x = 0.;
    double y = 0.;
    double z = 0.;

    // If we have some McPositionHits then calculate average position
    if (m_PositionHitsVec.size() > 0)
    {
        // If only one hit then this is a bit easier
        if (m_PositionHitsVec.size() == 1)
        {
            const SmartRef<Event::McPositionHit>& posHit = m_PositionHitsVec.front();

            x = 0.5* (posHit->globalEntryPoint().x() + posHit->globalExitPoint().x());
            y = 0.5* (posHit->globalEntryPoint().y() + posHit->globalExitPoint().y());
            z = 0.5* (posHit->globalEntryPoint().z() + posHit->globalExitPoint().z());
        }
        else
        {
            // Get an interator to the position hits
            SmartRefVector<Event::McPositionHit>::const_iterator posHitVecIter = m_PositionHitsVec.begin();

            // Get the first McPositionHit
            const SmartRef<Event::McPositionHit>& posHit = *posHitVecIter++;

            // Now global entry and exit points
            HepPoint3D entryPoint = posHit->globalEntryPoint();
            HepPoint3D exitPoint  = posHit->globalExitPoint();

            double xLow  = entryPoint.x() < exitPoint.x() ? entryPoint.x() : exitPoint.x();
            double xHigh = entryPoint.x() > exitPoint.x() ? entryPoint.x() : exitPoint.x();
            double yLow  = entryPoint.y() < exitPoint.y() ? entryPoint.y() : exitPoint.y();
            double yHigh = entryPoint.y() > exitPoint.y() ? entryPoint.y() : exitPoint.y();
            double zLow  = entryPoint.z() < exitPoint.z() ? entryPoint.z() : exitPoint.z();
            double zHigh = entryPoint.z() > exitPoint.z() ? entryPoint.z() : exitPoint.z();

            for( ;posHitVecIter != m_PositionHitsVec.end(); posHitVecIter++)
            {
                entryPoint = (*posHitVecIter)->globalEntryPoint();
                if (entryPoint.x() < xLow)  xLow  = entryPoint.x();
                if (entryPoint.x() > xHigh) xHigh = entryPoint.x();
                if (entryPoint.y() < yLow)  yLow  = entryPoint.y();
                if (entryPoint.y() > yHigh) yHigh = entryPoint.y();
                if (entryPoint.z() < zLow)  zLow  = entryPoint.z();
                if (entryPoint.z() > zHigh) zHigh = entryPoint.z();

                exitPoint  = (*posHitVecIter)->globalExitPoint();
                if (exitPoint.x() < xLow)   xLow  = exitPoint.x();
                if (exitPoint.x() > xHigh)  xHigh = exitPoint.x();
                if (exitPoint.y() < yLow)   yLow  = exitPoint.y();
                if (exitPoint.y() > yHigh)  yHigh = exitPoint.y();
                if (exitPoint.z() < zLow)   zLow  = exitPoint.z();
                if (exitPoint.z() > zHigh)  zHigh = exitPoint.z();
            }

            x = 0.5 * (xLow + xHigh);
            y = 0.5 * (yLow + yHigh);
            z = 0.5 * (zLow + zHigh);
        }
    }

    return HepPoint3D(x,y,z);
}


};