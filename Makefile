#####################################################################
# *******************************************************************
# *                Simple C++ Makefile Template                     *
# *                                                                 *
# * Author: Arash Partow (2003)                                     *
# * URL: http://www.partow.net/programming/makefile/index.html      *
# *                                                                 *
# * Copyright notice:                                               *
# * Free use of this C++ Makefile template is permitted under       *
# * the guidelines and in accordance with the the MIT License       *
# * http://www.opensource.org/licenses/MIT                          *
# *                                                                 *
# *******************************************************************
#####################################################################
APPVERSION   := 1.0.0
TARGET       := Ncurse_MenuFormTab
CC           := gcc
CXX          := g++
DEFINES      := -DAPP_VERSION="\"v1.0.0\"" -DAPP_PRODUCT="\"ServiceControl\"" -DAPP_COMPANY="\"HOMELAND\"" -DAPP_COPYRIGHT="\"Copyright (c) by Aktony\"" -DDEBUG_MODE -DQT_QML_DEBUG
CXXFLAGS     := -pipe -g -Wall -Wextra -fPIC $(DEFINES)
#####################################################################
BUILD     := ./Build_v$(APPVERSION)
OBJ_DIR   := $(BUILD)/objects
#APP_DIR   := $(BUILD)/$(TARGET)
APP_DIR   := $(BUILD)/$(TARGET)/bin
CONF_DIR  := $(BUILD)/$(TARGET)/config
APPLIBDIR := $(BUILD)/$(TARGET)/lib
LOG_DIR   := $(BUILD)/$(TARGET)/log
#####################################################################
INSTALL_DIR  := /Applications/$(TARGET)
AppBinDir   := $(INSTALL_DIR)/bin
AppConfDir  := $(INSTALL_DIR)/config
AppLibDir   := $(INSTALL_DIR)/lib
AppLogDir   := $(INSTALL_DIR)/log
#####################################################################
INCLUDE      := -I.
LDFLAGS      := -L/usr/lib -lncurses++w -Wall -lncursesw -lmenuw -lmenu -lformw -lpanelw -pthread -lreadline -Wreturn-type -lstdc++fs -lsystemd
SRC          := $(wildcard *.cpp)
HEADERS	     := $(wildcard *.h)
OBJECTS      := $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES := $(OBJECTS:.o=.d)
#####################################################################
DOCS	     := README.md
MAIN	     := MenuWinClass.cpp
TARGET_FBIN  := $(APP_DIR)/$(TARGET)
INSTALL      := /usr/bin/install -c
LN_LINK      := /usr/bin/ln -s
MKDIR        := /usr/bin/mkdir -p
exec_perms   := 0755
install-suid-root: exec_perms := 4755
#####################################################################
all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

-include $(DEPENDENCIES)

.PHONY: all build clean debug release info
#####################################################################
build:
#	@mkdir -p $(OBJ_DIR) $(APP_DIR)
	@mkdir -p $(APP_DIR) $(CONF_DIR) $(APPLIBDIR) $(LOG_DIR);
#####################################################################
debug: CXXFLAGS += -DDEBUG -g
debug: all
#####################################################################
release: CXXFLAGS += -O2
release: all
#####################################################################
clean:
	-@rm -rvf $(OBJ_DIR)/* $(APP_DIR)/*
# $(CONF_DIR)/* $(APPLIBDIR)/* $(LOG_DIR)/*
	-@rm -rfv $(BUILD)/ $(INSTALL_DIR) /bin/$(TARGET);
#####################################################################
install:
#	@mkdir -p $(INSTALL_DIR) $(AppBinDir) $(AppConfDir) $(AppLibDir) $(AppLogDir)
	@yes | cp -Riv $(BUILD)/$(TARGET) $(INSTALL_DIR)
	$(LN_LINK) $(AppBinDir)/$(TARGET) /bin/$(TARGET)
#	$(INSTALL) -m 0755 -Dv $(APP_DIR)/$(TARGET) /usr/bin/$(TARGET);
#	$(INSTALL) -m 0755 -Dv $(BUILD)/$(TARGET) $(AppInstDir);
#####################################################################
info:
	@echo "[*] Application dir: ${APP_DIR}     "
	@echo "[*] Object dir:      ${OBJ_DIR}     "
	@echo "[*] Sources:         ${SRC}         "
	@echo "[*] Objects:         ${OBJECTS}     "
	@echo "[*] Dependencies:    ${DEPENDENCIES}"
	@echo "[*] Includes:        ${INCLUDE}     "
	@echo "[*] Headers:         ${HEADERS}     "

