from distutils.core import setup, Extension
import os

library_dirs = None
if 'LD_LIBRARY_PATH' in os.environ:
    library_dirs = os.environ['LD_LIBRARY_PATH'].split(":")

module = Extension('rdg',
                    libraries = ['rdg'],
                    library_dirs=library_dirs,
                    sources = ['src/pyrdg.c'])

setup (name = 'rdg',
       version = '1.0.0',
       description = 'A regex-based data generator',
       author = 'Jeff Caffrey-Hill',
       author_email = 'jeff@reverentengineer.com',
       url = 'https://reverentengineer.com/rdg',
       ext_modules = [module]
)
