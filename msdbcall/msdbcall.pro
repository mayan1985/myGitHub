include ($$(IESBASE)/src/ies_base.pri)

TEMPLATE	=lib
CONFIG		+= qt warn_off dll thread
LANGUAGE	= C++



SOURCES	+= \
		msdbcall.cpp \
		topocall.cpp \
		commcall.cpp \
		rtucall.cpp \
		sdcall.cpp \
		dtscall.cpp \
		dbvariant.cpp

HEADERS += \
		table_info_ms.h \
		topodefext.h \
		../../include/msdbcall.h
		


INCLUDEPATH += \
		../../include
		
OBJECTS_DIR = ../../../obj/base/msdbcall
DESTDIR 	= ../../../lib

win32 {
	DEFINES += MSDBCALL /GR /GX
	LIBS 	+= ../../../lib/iesstd.lib \
		../../../lib/dbi_odbc.lib \
		../../../lib/sbmixdll.lib \
		../../../lib/iescommon.lib
}

unix {
	LIBS 	+= -L../../../lib \
		-liesstd \
		-ldbi_odbc \
		-lsbunixdll \
		-liescommon
}