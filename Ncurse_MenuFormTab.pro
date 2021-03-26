######### libary part #########
#TEMPLATE = lib
#CONFIG += staticlib
#CONFIG += warn_on
######### application part ###
TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

############################################################################
##       Meine einstellung immer ohne shadow build in QT creator!!!        #
############################################################################
#unix:!macx:QMAKE_DEL_FILE = rm -f
#unix:!macx:QMAKE_DEL_DIR  = rm -rf
#unix:!macx:OUT_PWD = "$$PWD/Build_v$$VERSION/debug/$$PROGRAMMNAME"
############################################################################
PROGRAMMNAME = Ncurse_MenuFormTab
TARGET = bin/$$PROGRAMMNAME
VERSION = 1.0.0
QMAKE_TARGET_PRODUCT = "$${PROGRAMMNAME}"
QMAKE_TARGET_COMPANY = "HOMELAND"
QMAKE_TARGET_COPYRIGHT = "Copyright (c) by Aktony"
DEFINES += APP_VERSION=\"\\\"$${VERSION}\\\"\" \
           APP_PRODUCT=\"\\\"$${QMAKE_TARGET_PRODUCT}\\\"\" \
           APP_COMPANY=\"\\\"$${QMAKE_TARGET_COMPANY}\\\"\" \
           APP_COPYRIGHT=\"\\\"$${QMAKE_TARGET_COPYRIGHT}\\\"\"
#DESTDIR  = "$$PWD/Build_v158331VERSION/debug/$$PROGRAMMNAME"
############################################################################
#                  release and debug                                       #
############################################################################
CONFIG(debug, debug|release) {
    DEFINES += DEBUG_MODE
    DESTDIR = "$$PWD/Build_v$$VERSION/debug/$$PROGRAMMNAME"
    QMAKE_MAKEFILE = Makefile.debug
    MAKEFILE = Makefile.debug
} else:CONFIG(release, debug|release) {
    DEFINES += RELEASE_MODE
    DESTDIR = "$$PWD/Build_v$$VERSION/release/$$PROGRAMMNAME"
    QMAKE_MAKEFILE = Makefile.release
    MAKEFILE = Makefile.release
} else:CONFIG(force_debug_info) {
    DEFINES += PROFILE_MODE
    DESTDIR = "$$PWD/Build_v$$VERSION/profile/$$PROGRAMMNAME"
    QMAKE_MAKEFILE = Makefile.profile
    MAKEFILE = Makefile.profile
} else {
    DEFINES += DEBUG_MODE
    DESTDIR = "$$PWD/Build_v$$VERSION/debug/$$PROGRAMMNAME"
    QMAKE_MAKEFILE = Makefile.debug
    MAKEFILE = Makefile.debug
}

RCC_DIR = "$$PWD/Build_v$$VERSION/RCCFiles"
UI_DIR = "$$PWD/Build_v$$VERSION/UICFiles"
MOC_DIR = "$$PWD/Build_v$$VERSION/MOCFiles"
OBJECTS_DIR = "$$PWD/Build_v$$VERSION/ObjFiles"
DEPENDPATH = "$$OBJECTS_DIR"
INCLUDEPATH = -I.

message($$_PRO_FILE_ " - Profile!")
message($$_PRO_FILE_PWD_ " - Profile dir!")
message($$DESTDIR " - Destdir Name!")
message($$MAKEFILE " - Makefile Name!")
message($$OUT_PWD " - out_pwd dir!")
message($$QMAKE_MAKEFILE " - Qmakefile Name!")
############################################################################
#                  Copy files to build directory                           #
############################################################################
#copydata0.commands = $(DEL_DIR)     $$DESTDIR/config
#copydata1.commands = $(COPY_FILE)   $$PWD/lib/libLogWriter.a     $$DESTDIR/lib/libLogWriter.a
#copydata2.commands = $(COPY_FILE)   $$PWD/lib/libUserGroupList.a $$DESTDIR/lib/libUserGroupList.a
#first.depends = $(first) copydata0 copydata1 copydata2
#export(first.depends)
#export(copydata0.commands)
#export(copydata1.commands)
#export(copydata2.commands)
#QMAKE_EXTRA_TARGETS += first copydata0  copydata1 copydata2
############################################################################
#                           Libs and Linker                                #
############################################################################
unix:!macx: LIBS += -lncurses++w -Wall -lncursesw -lmenuw -lmenu -lformw -lpanelw -pthread -lreadline -Wreturn-type -lstdc++fs -lsystemd
#-lpam -lpam_misc -lxcb
#unix:!macx:LIBS_PRIVATE += $$DESTDIR/lib/libUserGroupList.a
#unix:!macx:LIBS_PRIVATE += $$DESTDIR/lib/libLogWriter.a
#unix:!macx: LIBS += -L$$DESTDIR/lib/ -lLogWriter -lUserGroupList
#$$DESTDIR/lib/libconfigator.a $$DESTDIR/lib/libdragonfail.a $$DESTDIR/lib/libtermbox.a $ß/lib/libtestoasterror.a
#unix:!macx: LIBS += -L$$DESTDIR/lib/ -largoat -lconfigator -ldragonfail -ltermbox -ltestoasterror
############################################################################
#                           Ende !!!                                       #
############################################################################

SOURCES += \
    MenuWinClass.cpp

#HEADERS +=

HEADERS += \
    MenuWinClass.h

