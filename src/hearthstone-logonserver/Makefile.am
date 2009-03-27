INCLUDES += -I$(srcdir) -I$(srcdir)/../../dep/include -I$(srcdir)/../hearthstone-shared

bin_PROGRAMS = hearthstone-logonserver

hearthstone_logonserver_SOURCES = \
	AccountCache.cpp \
	AccountCache.h \
	AuthSocket.cpp \
	AuthSocket.h \
	AuthStructs.h \
	LogonCommServer.cpp \
	LogonCommServer.h \
	LogonConsole.cpp \
	LogonConsole.h \
	LogonOpcodes.cpp \
	LogonOpcodes.h \
	LogonStdAfx.cpp \
	LogonStdAfx.h \
	AutoPatcher.h \
	AutoPatcher.cpp \
	Main.cpp \
	Main.h \
	PeriodicFunctionCall_Thread.h

hearthstone_logonserver_LDADD = -lshared -lz
hearthstone_logonserver_LDFLAGS = -L$(srcdir)/../hearthstone-shared
