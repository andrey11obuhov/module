from distutils.core import setup, Extension

module1 = Extension( 
	'ciphers', # module name in interpreter
	sources = ['main.c'] 
)

setup( 
	name = 'cipher',
	version = '1.1',
	description = 'Simple module',
	ext_modules= [module1]
)