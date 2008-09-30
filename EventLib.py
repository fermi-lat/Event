# $Header: /nfs/slac/g/glast/ground/cvs/GlastRelease-scons/Event/EventLib.py,v 1.1 2008/07/09 21:13:41 glastrm Exp $
def generate(env, **kw):
    if not kw.get('depsOnly', 0):
        env.Tool('addLibrary', library = ['Event'])
    env.Tool('geometryLib')
    env.Tool('identsLib')
    env.Tool('addLibrary', library = env['clhepLibs'])
    env.Tool('addLibrary', library = env['gaudiLibs'])
def exists(env):
    return 1;
