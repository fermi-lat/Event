// $Id: EventModel.cpp,v 1.5 2000/10/25 17:58:38 igable Exp $
// 
//  Original author: Sawyer Gillespie
//                   hgillesp@u.washington.edu
//
#define _GlastEvent_EventModel_CPP_


// Include files
#include "GlastEvent/TopLevel/EventModel.h"
#include "Gaudi/Kernel/Kernel.h"

    
    //------------------------------------------------------------------------------
    //
    // Implementation of class :  EvModel
    //
    // Author :                   Markus Frank
    //
    // Changes:                   Pavel Binko :  New data types added
    //
    //------------------------------------------------------------------------------
    
    class EvModel {
        
    public:
        EvModel() {
            

            // The whole LHCb event
            EventModel::Event            = "/Event";
            
            // set up the MC structure
            EventModel::MC::Event = EventModel::Event + "/MC";
            EventModel::MC::MCACDHits = EventModel::MC::Event + "/MCACDHits";
            EventModel::MC::MCCalorimeterHits = EventModel::MC::Event + "/MCCalorimeterHits";
            EventModel::MC::MCTKRHits = EventModel::MC::Event + "/MCTKRHits";

            // Hits event
            EventModel::Hits::Event
                = EventModel::Event        + "/Hits";

            EventModel::Hits::Glast
                = EventModel::Hits::Event  + "/Glast";

            
            // These are names used to identify the various components
            //EventModel::Hits::CalorimeterName = "/Calorimeter";

//            EventModel::Hits::ACDTilesName = "/ACDTile";
            // temporarily simplifying the data model...
            EventModel::ACDTilesName = EventModel::Event + "/ACDTile";

            //EventModel::Hits::SiLayersName = "/SiLayer";

            //EventModel::Hits::TowerName = "/Tower";


            // Run through and come up with names for all of the layers
        }
    };
    
    
    static EvModel mod;
    
    // Class ID definitions for the LHCb Event Model (1st and 2nd byte)
    //   Reserved numbers are from the GAUDI Framework are 0-99
    //   Maximum CLID is 65536 = 2^16 - 1
    
    //  
  //  const CLID& CLID_Event                = 1000;  // Event root

    // Hits event class ID's
    const CLID& CLID_EventHits            = 2000;   // Hits event root
    const CLID& CLID_GlastHits            = 2001;   // Glast hits
    const CLID& CLID_ACDTileHits          = 2002;   // ACD tile hits
    const CLID& CLID_TowerHits            = 2003;   // Tower hits
    const CLID& CLID_SiLayerHits          = 2004;   // SiLayer hits
    const CLID& CLID_SiStripHits          = 2005;   // SiStrip hits
    const CLID& CLID_CalorimeterHits      = 2006;   // Calorimeter hits
    const CLID& CLID_CalorimeterLogHits   = 2007;   // Calorimeter log hits
    const CLID& CLID_MCTKRHit          = 2008;   // Tracker hits
    const CLID& CLID_MCACDHit             = 2009;
    const CLID& CLID_MCTrack              = 2010; //Ian Mod
const CLID& CLID_MCCalorimeterHit     = 2011;
    const CLID& CLID_MCEvent              = 2012;
    const CLID& CLID_MCSiLayer          = 2013;
        
