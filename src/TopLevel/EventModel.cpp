// File and Version Information:
// $Header: /home/cvs/SLAC/Event/src/TopLevel/EventModel.cpp,v 1.68 2004/12/15 23:29:25 usher Exp $ 


#define _Event_EventModel_CPP_

// Define this in order to export symbols
#define EVT_DLL_EXPORTS

#include "Event/TopLevel/EventModel.h"
#include "GaudiKernel/ClassID.h"

std::string EventModel::EventHeader = "/Event";

/** 
 *  @class MC
 *
*/
std::string EventModel::MC::Event                   = EventModel::EventHeader + "/MC";
std::string EventModel::MC::McParticleCol           = EventModel::MC::Event  + "/McParticleCol";

std::string EventModel::MC::McPositionHitCol        = EventModel::MC::Event  + "/PositionHitsCol";
std::string EventModel::MC::McIntegratingHitCol     = EventModel::MC::Event  + "/IntegratingHitsCol";
std::string EventModel::MC::McTkrStripCol           = EventModel::MC::Event  + "/StripCol";
std::string EventModel::MC::D2EntryCol              = EventModel::MC::Event  + "/D2EntryCol";
std::string EventModel::MC::ExposureCol             = EventModel::MC::Event  + "/ExposureCol";

std::string EventModel::MC::McEventStructure        = EventModel::MC::Event  + "/McEventStructure";
std::string EventModel::MC::McPartToPosHitTab       = EventModel::MC::Event  + "/McPartToPosHitTab";
std::string EventModel::MC::McPartToClusTab         = EventModel::MC::Event  + "/McPartToClusTab";
std::string EventModel::MC::McPartToClusHitTab      = EventModel::MC::Event  + "/McPartToClusHitTab";

std::string EventModel::MC::McPartToTkrCandHitTab   = EventModel::MC::Event  + "/McPartToTkrCandHitTab";
std::string EventModel::MC::McPartToTkrPatCandTab   = EventModel::MC::Event  + "/McPartToTkrPatCandTab";
std::string EventModel::MC::McPartToTkrTrackHitTab  = EventModel::MC::Event  + "/McPartToTkrTrackHitTab";
std::string EventModel::MC::McPartToTkrTrackTab     = EventModel::MC::Event  + "/McPartToTkrTrackTab";

// Digi event
std::string EventModel::Digi::Event                 = EventModel::EventHeader + "/Digi";
std::string EventModel::Digi::AcdDigiCol            = EventModel::Digi::Event + "/AcdDigiCol";
std::string EventModel::Digi::TkrDigiCol            = EventModel::Digi::Event + "/TkrDigiCol";
std::string EventModel::Digi::CalDigiCol            = EventModel::Digi::Event + "/CalDigiCol";
std::string EventModel::Digi::CalDigiHitTab         = EventModel::Digi::Event + "/CalDigiHitTab";
std::string EventModel::Digi::TkrDigiHitTab         = EventModel::Digi::Event + "/TkrDigiHitTab";
std::string EventModel::Digi::TkrClusterHitTab      = EventModel::Digi::Event + "/TkrClusterHitTab";
      
// reconstructed data (Tracker)
std::string EventModel::TkrRecon::Event             = EventModel::EventHeader + "/TkrRecon";
std::string EventModel::TkrRecon::SiLayers        = EventModel::TkrRecon::Event + "/SiLayers";
std::string EventModel::TkrRecon::TkrClusterCol     = EventModel::TkrRecon::Event + "/TkrClusterCol";
std::string EventModel::TkrRecon::TkrPatCandCol   = EventModel::TkrRecon::Event + "/TkrPatCandCol";
std::string EventModel::TkrRecon::SiRecObjs       = EventModel::TkrRecon::Event + "/SiRecObjs";
std::string EventModel::TkrRecon::TkrFitTrackCol  = EventModel::TkrRecon::Event + "/TkrFitTrackCol";
std::string EventModel::TkrRecon::TkrTrackTab     = EventModel::TkrRecon::Event + "/TkrTrackTab";
std::string EventModel::TkrRecon::TkrVertexCol    = EventModel::TkrRecon::Event + "/TkrVertexCol";
std::string EventModel::TkrRecon::TkrVertexTab    = EventModel::TkrRecon::Event + "/TkrVertexTab";



//reconstructed Cal data
std::string EventModel::CalRecon::Event             = EventModel::EventHeader + "/CalRecon";
std::string EventModel::CalRecon::CalXtalRecCol     = EventModel::CalRecon::Event + "/CalXtalRecCol";
std::string EventModel::CalRecon::CalClusterCol     = EventModel::CalRecon::Event + "/CalClusterCol";

// reconstructed ACD data
std::string EventModel::AcdRecon::Event             = EventModel::EventHeader + "/AcdRecon";







		
