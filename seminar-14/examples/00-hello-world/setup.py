from distutils.core import setup
from distutils.core import Extension


hellolib = Extension('hellolib',
                     sources = ['hellolib.c'])

setup(name='hellolib',
      version='0.1.0',
      description='Hello world module written in C',
      ext_modules=[hellolib]
)
