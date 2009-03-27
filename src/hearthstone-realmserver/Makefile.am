INCLUDES += -I$(srcdir) -I$(srcdir)/../hearthstone-shared

bin_PROGRAMS = hearthstone-realmserver

hearthstone_realmserver_SOURCES = \
ClientManager.h \
ClusterManager.h \
LogonCommClient.h \
LogonCommHandler.h \
Master.h \
ObjectStorage.h \
RStdAfx.h \
Session.h \
Structures.h \
WorkerOpcodes.h \
WorkerServer.h \
WorkerServerSocket.h \
WorldSocket.h \
CharacterHandler.cpp \
ClientManager.cpp \
ClusterManager.cpp \
LogonCommClient.cpp \
LogonCommHandler.cpp \
Master.cpp \
ObjectStorage.cpp \
QueryHandler.cpp \
RStdAfx.cpp \
Session.cpp \
WorkerServer.cpp \
WorkerServerSocket.cpp \
WorldSocket.cpp 
	
hearthstone_realmserver_LDADD = -lshared -lz

hearthstone_realmserver_LDFLAGS = -L$(srcdir)/../hearthstone-shared \
               -L/usr/lib
               
