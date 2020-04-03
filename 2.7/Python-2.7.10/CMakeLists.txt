project(python27)

cmake_minimum_required(VERSION 2.4.0)

if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
	cmake_policy(SET CMP0005 NEW)
endif(COMMAND cmake_policy)

enable_language(C ASM)
add_definitions(-DMACOSX)
add_definitions(-DNDEBUG -DHAVE_NDBM_H -DHAVE_SEM_OPEN -DOBJC2RUNTIME)

add_definitions(-DVERSION="2.7" -DPREFIX="/System/Library/Frameworks/Python.framework/Versions/2.7" -DSUFFIX="${BITS}")
add_definitions(-DPLATFORM="darwin" -DPYTHONPATH=":plat-darwin:plat-mac:plat-mac/lib-scriptpackages:lib-tk:lib-old")

add_definitions(
	-w
	-nostdinc
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fwrapv -fPIC")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/Include
	${CMAKE_CURRENT_SOURCE_DIR}/Modules/_ctypes/libffi_osx/include
)

set(python_sources
	Python/asdl.c
	Python/ast.c
	Python/atof.c
	Python/bltinmodule.c
	Python/ceval.c
	Python/codecs.c
	Python/compile.c
	Python/dtoa.c
	Python/dup2.c
	Python/dynload_shlib.c
	Python/errors.c
	Python/formatter_string.c
	Python/formatter_unicode.c
	Python/frozen.c
	Python/frozenmain.c
	Python/future.c
	Python/getargs.c
	Python/getcompiler.c
	Python/getcopyright.c
	Python/getopt.c
	Python/getplatform.c
	Python/getversion.c
	Python/graminit.c
	Python/import.c
	Python/importdl.c
	# Python/mactoolboxglue.c # Needs Carbon and similar stuff
	Python/marshal.c
	Python/modsupport.c
	Python/mysnprintf.c
	Python/mystrtoul.c
	Python/peephole.c
	Python/pyarena.c
	Python/pyctype.c
	Python/pyfpe.c
	Python/pymath.c
	Python/pystate.c
	Python/pystrcmp.c
	Python/pystrtod.c
	Python/Python-ast.c
	Python/pythonrun.c
	Python/random.c
	#Python/sigcheck.c
	Python/strdup.c
	Python/strtod.c
	Python/structmember.c
	Python/symtable.c
	Python/sysmodule.c
	Python/thread.c
	Python/traceback.c
	Python/_warnings.c

	Parser/acceler.c
	Parser/bitset.c
	Parser/firstsets.c
	Parser/grammar1.c
	Parser/grammar.c
	#Parser/intrcheck.c
	Parser/listnode.c
	Parser/metagrammar.c
	Parser/myreadline.c
	Parser/node.c
	Parser/parser.c
	Parser/parsetok.c
	Parser/pgen.c
	#Parser/pgenmain.c
	Parser/printgrammar.c
	Parser/tokenizer.c
	#Parser/tokenizer_pgen.c

	Objects/abstract.c
	Objects/boolobject.c
	Objects/bufferobject.c
	Objects/bytearrayobject.c
	Objects/bytes_methods.c
	Objects/capsule.c
	Objects/cellobject.c
	Objects/classobject.c
	Objects/cobject.c
	Objects/codeobject.c
	Objects/complexobject.c
	Objects/descrobject.c
	Objects/dictobject.c
	Objects/enumobject.c
	Objects/exceptions.c
	Objects/fileobject.c
	Objects/floatobject.c
	Objects/frameobject.c
	Objects/funcobject.c
	Objects/genobject.c
	Objects/intobject.c
	Objects/iterobject.c
	Objects/listobject.c
	Objects/longobject.c
	Objects/memoryobject.c
	Objects/methodobject.c
	Objects/moduleobject.c
	Objects/object.c
	Objects/obmalloc.c
	Objects/rangeobject.c
	Objects/setobject.c
	Objects/sliceobject.c
	Objects/stringobject.c
	Objects/structseq.c
	Objects/tupleobject.c
	Objects/typeobject.c
	Objects/unicodectype.c
	Objects/unicodeobject.c
	Objects/weakrefobject.c

	Modules/gcmodule.c
	Modules/getpath.c
	Modules/config.c
	Modules/threadmodule.c
	Modules/signalmodule.c
	Modules/posixmodule.c
	Modules/errnomodule.c
	Modules/pwdmodule.c
	Modules/_sre.c
	Modules/_codecsmodule.c
	Modules/zipimport.c
	Modules/symtablemodule.c
	Modules/getbuildinfo.c
	Modules/xxsubtype.c
	Modules/_weakref.c
	Modules/_math.c
)

set(DYLIB_COMPAT_VERSION "2.7.0")
set(DYLIB_CURRENT_VERSION "2.7.10")
add_framework(Python
	FAT
	CURRENT_VERSION
	SOURCES
		${python_sources}
	VERSION "2.7"
	DEPENDENCIES
		system
)
unset(DYLIB_COMPAT_VERSION)
unset(DYLIB_CURRENT_VERSION)

include(darling_exe)
include(InstallSymlink)
include(versioner)

add_darling_executable(python27exe Modules/main.c Modules/python.c)
target_link_libraries(python27exe system Python_2.7)
set_target_properties(python27exe PROPERTIES OUTPUT_NAME python2.7)
make_fat(python27exe)

install(TARGETS python27exe DESTINATION libexec/darling/System/Library/Frameworks/Python.framework/Versions/2.7/bin)
install(FILES python2.7 DESTINATION libexec/darling/usr/bin)

versioner(python "2.6;2.7" "2.7")

function(pymodule modname)
	foreach(f IN LISTS ARGN)
		set(files ${files} ${f})
	endforeach(f)

	add_darling_bundle("py27_${modname}" "${CMAKE_CURRENT_BINARY_DIR}/python2.7" ${files})
	target_link_libraries("py27_${modname}" system)

	set_property(TARGET "py27_${modname}" APPEND_STRING PROPERTY LINK_FLAGS " -Wl,-flat_namespace ")
	set_target_properties("py27_${modname}" PROPERTIES OUTPUT_NAME ${modname}
														PREFIX ""
														SUFFIX ".so")
	make_fat("py27_${modname}")
	add_dependencies("py27_${modname}" python27exe)

	install(TARGETS "py27_${modname}" DESTINATION libexec/darling/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/lib-dynload)
endfunction(pymodule)

set(sqlite_sources
	Modules/_sqlite/cache.c
	Modules/_sqlite/connection.c
	Modules/_sqlite/cursor.c
	Modules/_sqlite/microprotocols.c
	Modules/_sqlite/module.c
	Modules/_sqlite/prepare_protocol.c
	Modules/_sqlite/row.c
	Modules/_sqlite/statement.c
	Modules/_sqlite/util.c
)

pymodule(zlib Modules/zlibmodule.c)
target_link_libraries(py27_zlib z)
pymodule(unicodedata Modules/unicodedata.c)
pymodule(time Modules/timemodule.c)
pymodule(termios Modules/termios.c)
pymodule(syslog Modules/syslogmodule.c)
pymodule(strop Modules/stropmodule.c)
pymodule(select Modules/selectmodule.c)
pymodule(resource Modules/resource.c)
pymodule(readline Modules/readline.c)
target_link_libraries(py27_readline ncurses edit)
pymodule(pyexpat Modules/pyexpat.c)
target_link_libraries(py27_pyexpat expat)
pymodule(parser Modules/parsermodule.c)
pymodule(operator Modules/operator.c)
#pymodule(nis Modules/nismodule.c)
pymodule(mmap Modules/mmapmodule.c)
pymodule(math Modules/mathmodule.c)
pymodule(itertools Modules/itertoolsmodule.c)
pymodule(imageop Modules/imageop.c)
pymodule(grp Modules/grpmodule.c)
pymodule(future_builtins Modules/future_builtins.c)
pymodule(fcntl Modules/fcntlmodule.c)
pymodule(dl Modules/dlmodule.c)
pymodule(dbm Modules/dbmmodule.c)
pymodule(datetime Modules/datetimemodule.c Modules/timemodule.c)
pymodule(crypt Modules/cryptmodule.c)
pymodule(cmath Modules/cmathmodule.c)
pymodule(cStringIO Modules/cStringIO.c)
pymodule(cPickle Modules/cPickle.c)
pymodule(bz2 Modules/bz2module.c)
target_link_libraries(py27_bz2 bz2)
pymodule(bsddb185 Modules/bsddbmodule.c)
pymodule(binascii Modules/binascii.c)
pymodule(audioop Modules/audioop.c)
pymodule(array Modules/arraymodule.c)
pymodule(_bisect Modules/_bisectmodule.c)
pymodule(_io Modules/_io/bufferedio.c Modules/_io/bytesio.c Modules/_io/fileio.c Modules/_io/iobase.c Modules/_io/_iomodule.c Modules/_io/stringio.c Modules/_io/textio.c)
pymodule(_collections Modules/_collectionsmodule.c)
pymodule(_csv Modules/_csv.c)
pymodule(_ctypes Modules/_ctypes/callbacks.c Modules/_ctypes/callproc.c Modules/_ctypes/cfield.c Modules/_ctypes/_ctypes.c Modules/_ctypes/malloc_closure.c Modules/_ctypes/stgdict.c Modules/_ctypes/darwin/dlfcn_simple.c
	Modules/_ctypes/libffi_osx/ffi.c  Modules/_ctypes/libffi_osx/x86/darwin64.S  Modules/_ctypes/libffi_osx/x86/x86-darwin.S  Modules/_ctypes/libffi_osx/x86/x86-ffi64.c  Modules/_ctypes/libffi_osx/x86/x86-ffi_darwin.c)
pymodule(_ctypes_test Modules/_ctypes/_ctypes_test.c)
pymodule(_curses_panel Modules/_curses_panel.c)
target_link_libraries(py27__curses_panel ncurses panel)
pymodule(_elementtree Modules/_elementtree.c)
set_target_properties(py27__elementtree PROPERTIES COMPILE_FLAGS "-DUSE_PYEXPAT_CAPI")
pymodule(_functools Modules/_functoolsmodule.c)
pymodule(_hashlib Modules/_hashopenssl.c)
target_link_libraries(py27__hashlib ssl098)
pymodule(_heapq Modules/_heapqmodule.c)
pymodule(_hotshot Modules/_hotshot.c)
pymodule(_json Modules/_json.c)
pymodule(_locale Modules/_localemodule.c)
target_link_libraries(py27__locale ${CoreFoundation})
pymodule(_lsprof Modules/_lsprof.c Modules/rotatingtree.c)
pymodule(_multiprocessing Modules/_multiprocessing/multiprocessing.c Modules/_multiprocessing/semaphore.c  Modules/_multiprocessing/socket_connection.c)
pymodule(_random Modules/_randommodule.c)
pymodule(_socket Modules/socketmodule.c Modules/timemodule.c)
pymodule(_ssl Modules/_ssl.c)
target_link_libraries(py27__ssl ssl098)
pymodule(_struct Modules/_struct.c)
pymodule(_testcapi Modules/_testcapimodule.c)
pymodule(_sqlite ${sqlite_sources})

target_link_libraries(py27__sqlite sqlite3)
target_compile_definitions(py27__sqlite PRIVATE -DMODULE_NAME="sqlite3")

pymodule(_scproxy Mac/Modules/_scproxy.c)
target_link_libraries(py27__scproxy SystemConfiguration)

function(install_lib subdir)
	file(GLOB py_files Lib/${subdir}/*.py)
	install(FILES ${py_files} DESTINATION libexec/darling/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/${subdir})

	string(REGEX REPLACE "/" "_" target_name "py27_${subdir}")
	pyc("${target_name}" SOURCES ${py_files} DESTINATION libexec/darling/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/${subdir})
endfunction(install_lib)

install_lib(.)
install_lib(bsddb)
install_lib(compiler)
install_lib(ctypes)
install_lib(ctypes/macholib)
install_lib(curses)
install_lib(distutils)
install_lib(distutils/command)
install_lib(email)
install_lib(email/mime)
install_lib(encodings)
install_lib(hotshot)
install_lib(importlib)
install_lib(json)
install_lib(logging)
install_lib(multiprocessing)
install_lib(multiprocessing/dummy)
install_lib(plat-darwin)
install_lib(plat-mac)
install_lib(sqlite3)
install_lib(wsgiref)
install_lib(xml)
install_lib(xml/dom)
install_lib(xml/etree)
install_lib(xml/parsers)
install_lib(xml/sax)

pyc(py27_sysconfigdata SOURCES _sysconfigdata.py DESTINATION libexec/darling/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7)
install(FILES _sysconfigdata.py DESTINATION libexec/darling/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/)
install(FILES Lib/site-packages/README DESTINATION libexec/darling/Library/Python/2.7/site-packages)
install(PROGRAMS ../../fix/dummy.py DESTINATION libexec/darling/usr/bin RENAME xattr)
install(PROGRAMS ../../fix/dummy.py DESTINATION libexec/darling/usr/bin RENAME python-config)

set(EXENAME "/System/Library/Frameworks/Python.framework/Versions/2.7/bin/python2.7")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Misc/python-config.in python-config)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/python-config DESTINATION libexec/darling/usr/bin RENAME python2.7-config)

