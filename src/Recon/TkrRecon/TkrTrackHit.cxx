
#include "Event/Recon/TkrRecon/TkrTrackHit.h"
#include <stdexcept>


void Event::TkrTrackHit::clean()
{
    m_hitPred     = Event::TkrTrackParams();
    m_hitFit      = Event::TkrTrackParams();
    m_hitSmooth   = Event::TkrTrackParams();
    m_Qmaterial   = Event::TkrTrackParams();

    m_statusBits &= StatusBits::HASCLUSTER | StatusBits::HASMEASURED | StatusBits::HASVALIDTKR;

    m_chiSquareFilter = 0.;
    m_chiSquareSmooth = 0.;
}

void Event::TkrTrackHit::clear()
{
    m_hitMeas     = Event::TkrTrackParams();
    m_hitPred     = Event::TkrTrackParams();
    m_hitFit      = Event::TkrTrackParams();
    m_hitSmooth   = Event::TkrTrackParams();
    m_Qmaterial   = Event::TkrTrackParams();

    m_statusBits &= StatusBits::HASCLUSTER | StatusBits::HASVALIDTKR;

    m_chiSquareFilter = 0.;
    m_chiSquareSmooth = 0.;
}

const Point Event::TkrTrackHit::getPoint(TkrTrackHit::ParamType type) const
{
    const TkrTrackParams& hit = getTrackParams(type);

    return Point(hit.getxPosition(), hit.getyPosition(),m_zPlane);
}

Point Event::TkrTrackHit::getPoint(TkrTrackHit::ParamType type) 
{
    const TkrTrackParams& hit = getTrackParams(type);

    return Point(hit.getxPosition(), hit.getyPosition(),m_zPlane);
}

const Vector Event::TkrTrackHit::getDirection(TkrTrackHit::ParamType type) const
{
    const TkrTrackParams& hit = getTrackParams(type);

    // This assumes that track directions are slopes
    return Vector(-hit.getxSlope(), -hit.getySlope(), -1.).unit();
}

Vector Event::TkrTrackHit::getDirection(TkrTrackHit::ParamType type)
{
    const TkrTrackParams& hit = getTrackParams(type);

    // This assumes that track directions are slopes
    return Vector(-hit.getxSlope(), -hit.getySlope(), -1.).unit();
}

const Event::TkrTrackParams& Event::TkrTrackHit::getTrackParams(TkrTrackHit::ParamType type) const
{
    //
    // Access via this method presumes the track parameters are set. So, REQUIRE the
    // status bits to be valid before returning the hit information
    //
    switch(type)
    {
        case MEASURED:  
        {
            if (!validMeasuredHit()) throw std::invalid_argument("Invalid Measured TkrTrackParams requested");
            return m_hitMeas;
        }
        case PREDICTED: 
        {
            if (!validPredictedHit()) throw std::invalid_argument("Invalid Predicted TkrTrackParams requested");
            return m_hitPred;
        }
        case FILTERED:  
        {
            if (!validFilteredHit()) throw std::invalid_argument("Invalid Filtered TkrTrackParams requested");
            return m_hitFit;
        }
        case SMOOTHED:  
        {
            if (!validSmoothedHit()) throw std::invalid_argument("Invalid Smoothed TkrTrackParams requested");
            return m_hitSmooth;
        }
        case QMATERIAL: 
        {
            if (!validMaterial()) throw std::invalid_argument("Invalid Material TkrTrackParams requested");
            return m_Qmaterial;
        }

        throw std::invalid_argument("Invalid type of TkrTrackParams hit requested");
    }

    return m_hitMeas;
}

Event::TkrTrackParams& Event::TkrTrackHit::getTrackParams(TkrTrackHit::ParamType type)
{
    //
    // Access to track parameters via this method does not require valid status bit 
    // (since this might be need to set them)
    // 
    switch(type)
    {
        case MEASURED:  return m_hitMeas;
        case PREDICTED: return m_hitPred;
        case FILTERED:  return m_hitFit;
        case SMOOTHED:  return m_hitSmooth;
        case QMATERIAL: return m_Qmaterial;

        // If here then something is wrong
        throw std::invalid_argument("Invalid type of TkrTrackParams hit requested");
    }

    return m_hitMeas;
}

void Event::TkrTrackHit::setTrackParams(ITkrTrackParamsAccess& access, TkrTrackHit::ParamType type) 
{
    // Don't forget to update the status bits...
    unsigned int statusBits = 0;

    // Switch on the type of hit to set
    switch(type)
    {
        case ParamType::MEASURED:
        {
            access.setParams(&m_hitMeas);
            statusBits = StatusBits::HASMEASURED;
            break;
        }
        case ParamType::PREDICTED: 
        {
            access.setParams(&m_hitPred);
            statusBits = StatusBits::HASPREDICTED;
            break;
        }
        case ParamType::FILTERED:  
        {
            access.setParams(&m_hitFit);
            statusBits = StatusBits::HASFILTERED;
            break;
        }
        case ParamType::SMOOTHED:
        {
            access.setParams(&m_hitSmooth);
            statusBits = StatusBits::HASSMOOTHED;
            break;
        }
        case ParamType::QMATERIAL: 
        {
            access.setParams(&m_Qmaterial);
            statusBits = StatusBits::HASMATERIAL;
        }
    }

    m_statusBits |= statusBits;

    return;
}

const int Event::TkrTrackHit::getParamIndex(bool meas, bool slope) const
{
    int posIdx = Event::TkrTrackParams::xPosIdx;
    int slpIdx = Event::TkrTrackParams::xSlpIdx;

    if (   ( meas && m_hitID.getView() == idents::TkrId::eMeasureY) 
        || (!meas && m_hitID.getView() == idents::TkrId::eMeasureX) )
    {
        posIdx = Event::TkrTrackParams::yPosIdx;
        slpIdx = Event::TkrTrackParams::ySlpIdx;
    }

    return slope ? slpIdx : posIdx;
}

int Event::TkrTrackHit::getParamIndex(bool meas, bool slope)
{
    int posIdx = Event::TkrTrackParams::xPosIdx;
    int slpIdx = Event::TkrTrackParams::xSlpIdx;

    if (   ( meas && m_hitID.getView() == idents::TkrId::eMeasureY) 
        || (!meas && m_hitID.getView() == idents::TkrId::eMeasureX) )
    {
        posIdx = Event::TkrTrackParams::yPosIdx;
        slpIdx = Event::TkrTrackParams::ySlpIdx;
    }

    return slope ? slpIdx : posIdx;
}

const double Event::TkrTrackHit::getMeasuredPosition(Event::TkrTrackHit::ParamType type) const
{
    return getCoordinate(getTrackParams(type), getParamIndex(true, false));
}

const double Event::TkrTrackHit::getMeasuredSlope(Event::TkrTrackHit::ParamType type) const
{
    return getCoordinate(getTrackParams(type), getParamIndex(true, true));
}

const double Event::TkrTrackHit::getNonMeasuredPosition(Event::TkrTrackHit::ParamType type) const
{
    return getCoordinate(getTrackParams(type), getParamIndex(false, true));
}

const double Event::TkrTrackHit::getNonMeasuredSlope(Event::TkrTrackHit::ParamType type) const
{
    return getCoordinate(getTrackParams(type), getParamIndex(false, false));
}