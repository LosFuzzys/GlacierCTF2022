import pyximport
from pyximport import install

old_get_distutils_extension = pyximport.pyximport.get_distutils_extension

def new_get_distutils_extension(modname, pyxfilename, language_level=3):
    extension_mod, setup_args = old_get_distutils_extension(modname, pyxfilename, language_level)
    extension_mod.language='c++'
    extension_mod.include_dirs=['ChaCha20']
    #extension_mod.extra_compile_args = ['-fopenmp']
    #extension_mod.extra_link_args = ['-fopenmp']
    return extension_mod,setup_args

pyximport.pyximport.get_distutils_extension = new_get_distutils_extension
