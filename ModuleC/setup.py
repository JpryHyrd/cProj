from distutils.core import setup, Extension

module1 = Extension(
	'pmath', 
	 sources = ['main.c', 'matem.c'] 
)

setup(
	name = 'pmath',            
	version = '1.0',               
	description = 'Simple module', 
	ext_modules= [module1]         
)