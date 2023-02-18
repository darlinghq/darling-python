# This is a temporary setup script to allow distribution of
# MacPython 2.4 modules for MacPython 2.3.

from distutils.core import Extension, setup

setup(name="OSA", version="0.1",
        ext_modules=[
                Extension('_OSA', ['_OSAmodule.c'],
                extra_compile_args=['-no64'], extra_link_args=['-framework', 'Carbon', '-no64'])
        ],
        py_modules=['OSA.OSA', 'OSA.OSAconst'],
        package_dir={'OSA':'../../../Lib/plat-mac/Carbon'}
        )
