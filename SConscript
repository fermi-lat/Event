# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/Event/SConscript,v 1.19 2009/09/12 16:09:38 usher Exp $
# Authors: T.Burnett <tburnett@u.washington.edu>
# Version: Event-14-01-01
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('EventLib', depsOnly = 1)
EventLib = libEnv.SharedLibrary('Event',
                                listFiles(['src/MonteCarlo/*.cxx',
                                           'src/Recon/TkrRecon/*.cxx',
                                           'src/Recon/CalRecon/*.cxx',
                                           'src/Recon/AcdRecon/*.cxx',
                                           'src/Digi/*.cxx', 'src/TopLevel/*.cpp',
                                           'src/Utilities/*.cxx']))

progEnv.Tool('EventLib')
test_Event = progEnv.Program('test_Event',['src/test/testmain.cxx'])
test_Tables = progEnv.Program('test_Tables',['src/test/test_RelTabs.cxx'])

test_TkrRecon = progEnv.Program('test_TkrRecon_Event',
                                ['src/test/test_TkrRecon.cxx']) 

progEnv.Tool('registerTargets', package = 'Event',libraryCxts=[[EventLib, libEnv]],
             testAppCxts = [[test_Event, progEnv],  [test_Tables, progEnv],
                            [test_TkrRecon, progEnv]],
             includes = listFiles(['Event/*'], recursive = 1))




