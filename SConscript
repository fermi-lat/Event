# -*- python -*-
# $Header: /nfs/slac/g/glast/ground/cvs/Event/SConscript,v 1.63 2012/08/28 19:08:05 heather Exp $
# Authors: T.Burnett <tburnett@u.washington.edu>
# Version: Event-14-15-00
Import('baseEnv')
Import('listFiles')
Import('packages')
progEnv = baseEnv.Clone()
libEnv = baseEnv.Clone()

libEnv.Tool('addLinkDeps', package='Event', toBuild='shared')
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




