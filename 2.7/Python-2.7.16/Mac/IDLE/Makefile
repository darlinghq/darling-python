prefix=/System/Library/Frameworks/Python.framework/Versions/2.7
CC=gcc
LD=gcc
BASECFLAGS= -fno-strict-aliasing -fno-common -dynamic
OPT=-DNDEBUG -g -fwrapv -Os -Wall -Wstrict-prototypes
CFLAGS=$(BASECFLAGS) $(OPT)
LDFLAGS=
srcdir=         .
VERSION=	2.7
LIBDEST=$(prefix)/lib/python$(VERSION)
UNIVERSALSDK=
builddir=	../..
PYTHONFRAMEWORK=Python


RUNSHARED=      DYLD_FRAMEWORK_PATH=/Users/ariel/git/darling/src/external/python/2.7/Python-2.7.16
BUILDEXE=       .exe
BUILDPYTHON=    $(builddir)/python$(BUILDEXE)

# Deployment target selected during configure, to be checked
# by distutils  
MACOSX_DEPLOYMENT_TARGET=10.15
export MACOSX_DEPLOYMENT_TARGET

BUNDLEBULDER=$(srcdir)/../../Lib/plat-mac/bundlebuilder.py

PYTHONAPPSDIR=/Applications/$(PYTHONFRAMEWORK) $(VERSION)

all: IDLE.app

install: IDLE.app
	test -d "$(DESTDIR)$(PYTHONAPPSDIR)" || mkdir -p "$(DESTDIR)$(PYTHONAPPSDIR)"
	-test -d "$(DESTDIR)$(PYTHONAPPSDIR)/IDLE.app" && rm -r "$(DESTDIR)$(PYTHONAPPSDIR)/IDLE.app"
	/bin/cp -PR IDLE.app "$(DESTDIR)$(PYTHONAPPSDIR)"
	touch "$(DESTDIR)$(PYTHONAPPSDIR)/IDLE.app"
	if [ -f "$(DESTDIR)$(LIBDEST)/idlelib/config-main.def" ]; then \
		/bin/cp -p "$(DESTDIR)$(LIBDEST)/idlelib/config-main.def" \
			"$(DESTDIR)$(LIBDEST)/idlelib/config-main.def~" ; \
		sed -e 's!name= IDLE Classic Windows!name= IDLE Classic OSX!g' \
			< "$(DESTDIR)$(LIBDEST)/idlelib/config-main.def~" \
			> "$(DESTDIR)$(LIBDEST)/idlelib/config-main.def" ; \
		rm "$(DESTDIR)$(LIBDEST)/idlelib/config-main.def~" ; \
	fi
	if [ -f "$(DESTDIR)$(LIBDEST)/idlelib/config-extensions.def" ]; then \
		/bin/cp -p "$(DESTDIR)$(LIBDEST)/idlelib/config-extensions.def" \
			"$(DESTDIR)$(LIBDEST)/idlelib/config-extensions.def~" ; \
		sed -e 's!zoom-height=<Alt-Key-2>!zoom-height=<Option-Key-0>!g' \
			-e 's!<Alt-Key-!<Option-Key-!g' \
			< "$(DESTDIR)$(LIBDEST)/idlelib/config-extensions.def~" \
			> "$(DESTDIR)$(LIBDEST)/idlelib/config-extensions.def" ; \
		rm "$(DESTDIR)$(LIBDEST)/idlelib/config-extensions.def~" ; \
	fi

clean:
	rm -rf IDLE.app

IDLE.app:  \
		$(srcdir)/../Icons/IDLE.icns $(srcdir)/idlemain.py \
		$(srcdir)/../Icons/PythonSource.icns \
		$(srcdir)/../Icons/PythonCompiled.icns Info.plist
	rm -fr IDLE.app
	$(RUNSHARED)  $(BUILDPYTHON) $(BUNDLEBULDER) \
		--builddir=. \
		--name=IDLE \
		--link-exec \
		--plist=Info.plist \
		--mainprogram=$(srcdir)/idlemain.py \
		--iconfile=$(srcdir)/../Icons/IDLE.icns \
		--resource=$(srcdir)/../Icons/PythonSource.icns \
		--resource=$(srcdir)/../Icons/PythonCompiled.icns \
		--python=$(prefix)/Resources/Python.app/Contents/MacOS/Python \
		build

Info.plist: $(srcdir)/Info.plist.in
	sed 's/%VERSION%/'"`$(RUNSHARED) $(BUILDPYTHON) -c 'import platform; print platform.python_version()'`"'/g' < $(srcdir)/Info.plist.in > Info.plist

