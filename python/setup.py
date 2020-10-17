from setuptools import setup, Extension
import os

module = Extension('rdg',
                    libraries = ['rdg'],
                    include_dirs = ['../src'],
                    sources = ['src/pyrdg.c'])

setup (name = 'rdg',
       version = '1.1.0',
       description = 'A regex-based data generator',
       author = 'Jeff Caffrey-Hill',
       author_email = 'jeff@reverentengineer.com',
       url = 'https://reverentengineer.com/rdg',
       ext_modules = [module]
)
