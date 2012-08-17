# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/Event/EventLib.py,v 1.2 2008/09/30 17:11:57 ecephas Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['Event'])
        if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
	    env.Tool('findPkgPath', package = 'Event') 
    env.Tool('geometryLib')
    env.Tool('identsLib')
    env.Tool('addLibrary', library = env['clhepLibs'])
    env.Tool('addLibrary', library = env['gaudiLibs'])
    if env['PLATFORM']=='win32' and env.get('CONTAINERNAME','')=='GlastRelease':
        env.Tool('findPkgPath', package = 'enums')
def exists(env):
    return 1;
