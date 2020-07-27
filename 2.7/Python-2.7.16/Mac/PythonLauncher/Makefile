CC=gcc
LD=gcc
BASECFLAGS= -fno-strict-aliasing -fno-common -dynamic
OPT=-DNDEBUG -g -fwrapv -Os -Wall -Wstrict-prototypes
CFLAGS=-g -O2 $(BASECFLAGS) $(OPT)
LDFLAGS=
srcdir=         .
VERSION=	2.7
UNIVERSALSDK=
builddir=	../..

RUNSHARED=      DYLD_FRAMEWORK_PATH=/Users/ariel/git/darling/src/external/python/2.7/Python-2.7.16
BUILDEXE=       .exe
BUILDPYTHON=    $(builddir)/python$(BUILDEXE)
PYTHONFRAMEWORK=Python

# Deployment target selected during configure, to be checked
# by distutils  
MACOSX_DEPLOYMENT_TARGET=10.15
export MACOSX_DEPLOYMENT_TARGET

BUNDLEBULDER=$(srcdir)/../../Lib/plat-mac/bundlebuilder.py

PYTHONAPPSDIR=/Applications/$(PYTHONFRAMEWORK) $(VERSION)
OBJECTS=FileSettings.o MyAppDelegate.o MyDocument.o PreferencesWindowController.o doscript.o main.o

all: Python\ Launcher.app

install: Python\ Launcher.app
	test -d "$(DESTDIR)$(PYTHONAPPSDIR)" || mkdir -p "$(DESTDIR)$(PYTHONAPPSDIR)"
	-test -d "$(DESTDIR)$(PYTHONAPPSDIR)/Python Launcher.app" && rm -r "$(DESTDIR)$(PYTHONAPPSDIR)/Python Launcher.app"
	/bin/cp -r "Python Launcher.app" "$(DESTDIR)$(PYTHONAPPSDIR)"
	touch "$(DESTDIR)$(PYTHONAPPSDIR)/Python Launcher.app"

clean:
	rm -f *.o "Python Launcher"
	rm -rf "Python Launcher.app"

Python\ Launcher.app:  Info.plist \
		Python\ Launcher $(srcdir)/../Icons/PythonLauncher.icns \
		$(srcdir)/../Icons/PythonSource.icns \
		$(srcdir)/../Icons/PythonCompiled.icns \
		$(srcdir)/factorySettings.plist
	rm -fr "Python Launcher.app"
	$(RUNSHARED) $(BUILDPYTHON) $(BUNDLEBULDER) \
		--builddir=. \
		--name="Python Launcher" \
		--executable="Python Launcher" \
		--iconfile=$(srcdir)/../Icons/PythonLauncher.icns \
		--bundle-id=org.python.PythonLauncher \
		--resource=$(srcdir)/../Icons/PythonSource.icns \
		--resource=$(srcdir)/../Icons/PythonCompiled.icns \
		--resource=$(srcdir)/English.lproj \
		--resource=$(srcdir)/factorySettings.plist \
		--plist Info.plist \
		build

FileSettings.o: $(srcdir)/FileSettings.m
	$(CC) $(CFLAGS) -o $@ -c $(srcdir)/FileSettings.m

MyAppDelegate.o: $(srcdir)/MyAppDelegate.m
	$(CC) $(CFLAGS) -o $@ -c $(srcdir)/MyAppDelegate.m

MyDocument.o: $(srcdir)/MyDocument.m
	$(CC) $(CFLAGS) -o $@ -c $(srcdir)/MyDocument.m

PreferencesWindowController.o: $(srcdir)/PreferencesWindowController.m
	$(CC) $(CFLAGS) -o $@ -c $(srcdir)/PreferencesWindowController.m

doscript.o: $(srcdir)/doscript.m
	$(CC) $(CFLAGS) -o $@ -c $(srcdir)/doscript.m

main.o: $(srcdir)/main.m
	$(CC) $(CFLAGS) -o $@ -c $(srcdir)/main.m

Python\ Launcher: $(OBJECTS)
	$(CC) $(LDFLAGS) -o "Python Launcher" $(OBJECTS) -framework AppKit -framework Carbon

Info.plist: $(srcdir)/Info.plist.in
	sed 's/%VERSION%/'"`$(RUNSHARED) $(BUILDPYTHON) -c 'import platform; print platform.python_version()'`"'/g' < $(srcdir)/Info.plist.in > Info.plist
