//$Header: /nfs/slac/g/glast/ground/cvs/GlastEvent/GlastEvent/mainpage.h,v 1.2 2000/11/01 00:40:28 igable Exp $
// (Special "header" just for doxygen)

/*! @mainpage  package GlastEvent

This package contains definitions for all GLAST event data:
	- Event
	- MCEvent
	- RawEvent
	- RecEvent
	- Run

Note that all inherit from DataObject, and correspond to transient 
store objects at the top level, under "Event".

\section MonteCarlo MonteCarlo

All the Monte Carlo classes have been changed to inherit from ContainedObject 
rather than from DataObject. The three classes completed to date are below.


- ContainedObject classes
  - MCCalorimeterHit
  - MCACDHit
  - MCTKRHit

\section RawData RawData

CsIData from GlastSim has been adapted to be a DataObject capable of travelling through 
the TDS unharmed. In addition a new branch has been added to the TDS namely /Event/Raw/.

- DataObject classes
  - CsIData

\section reference Reference Document
  See the formal  
  <a href="http://www.slac.stanford.edu/~hansl/glast/note/rd.pdf">documentation</a>.

  <hr>
  \section notes release notes
  \include release.notes
  \section requirements requirements
  \include requirements


*/
