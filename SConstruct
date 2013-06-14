
env = Environment(CCFLAGS='-g') 
env.ParseConfig( 'pkg-config --cflags glib-2.0' )
env.Program('bin/main',Glob('src/*.c'),srcdir='src',        
         LIBS = ['zlog','pthread','lua','m','dl'],
         INCLUDEPATH=['usr/local/include','/usr/local/glib2.0/include'],
         LIBPATH = ['/usr/lib','/usr/local/lib','/usr/local/glib2.0/lib'],
        parse_flags = ['-I/usr/local/include','-I/usr/local/glib2.0/include']        
        )
