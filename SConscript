# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/Event/SConscript,v 1.12 2008/12/18 04:30:08 glastrm Exp $
# Authors: T.Burnett <tburnett@u.washington.edu>
# Version: Event-13-04-02
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('EventLib', depsOnly = 1)
EventLib = libEnv.SharedLibrary('Event', listFiles(['src/MonteCarlo/*.cxx', 'src/Recon/TkrRecon/*.cxx',
                                                    'src/Recon/CalRecon/*.cxx', 'src/Recon/AcdRecon/*.cxx',
                                                    'src/Digi/*.cxx', 'src/TopLevel/*.cpp', 'src/Utilities/*.cxx']))

progEnv.Tool('EventLib')
test_Event = progEnv.Program('test_Event',['src/test/testmain.cxx'])
test_Tables = progEnv.Program('test_Tables',['src/test/test_RelTabs.cxx'])

test_TkrRecon = progEnv.Program('test_TkrRecon_Event', ['src/test/test_TkrRecon.cxx']) 

progEnv.Tool('registerObjects', package = 'Event', libraries = [EventLib],
             testApps = [test_Event, test_Tables, test_TkrRecon], includes = listFiles(['Event/*'], recursive = 1))



