#Commands

ifeq ($(OS),Windows_NT)
	DETECTED_OS = Windows
else
	DETECTED_OS = Linux
endif

ifeq ($(DETECTED_OS),Windows)
	COMMAND_RM = wsl rm
else
	COMMAND_RM = rm
endif

COLOR_RED	 = \033[0;31m
COLOR_GREEN  = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_BLUE	 = \033[0;34m
COLOR_PURPLE = \033[0;35m
COLOR_CYAN	 = \033[0;36m
COLOR_GREY 	 = \033[0;37m

COLOR_RED_LIGHT	   = \033[1;31m
COLOR_GREEN_LIGHT  = \033[1;32m
COLOR_YELLOW_LIGHT = \033[1;33m
COLOR_BLUE_LIGHT   = \033[1;34m
COLOR_PURPLE_LIGHT = \033[1;35m
COLOR_CYAN_LIGHT   = \033[1;36m
COLOR_GREY_LIGHT   = \033[1;37m

COLOR_END = \033[m

STRING_OK      = $(COLOR_GREEN_LIGHT)[SUCCES]$(COLOR_END)
STRING_WARNING = $(COLOR_YELLOW_LIGHT)[WARNING]$(COLOR_END)
STRING_ERROR   = $(COLOR_RED_LIGHT)[ERROR]$(COLOR_END)

#Compilation
CXX        = g++
CXXFLAGS   = -g -std=c++2a -Wextra -Wall -pedantic

.PHONY: all generate clean totalClean compileMakefileCreator generateMakefiles compileListOfComponents runListOfComponents gulgECS gulgMath gulgGraphics gulgInputs fortressWar documentation

all: gulgECS gulgMath gulgGraphics gulgInputs fortressWar

generate: compileMakefileCreator generateMakefiles compileListOfComponents


compileMakefileCreator:
	@-$(CXX) $(CXXFLAGS) -fPIC MakefileCreator/Sources/main.cpp -o MakefileCreator/MakefileCreator

generateMakefiles:
	@MakefileCreator/MakefileCreator GulgECS lib glm
	@MakefileCreator/MakefileCreator GulgGraphics lib SFML glm GulgECS
	@MakefileCreator/MakefileCreator GulgInput lib SFML
	@MakefileCreator/MakefileCreator ListOfComponents exe
	@MakefileCreator/MakefileCreator FortressWar exe SFML glm GulgECS GulgGraphics GulgInput

compileListOfComponents:
	@-$(CXX) $(CXXFLAGS) -fPIC ListOfComponents/Sources/main.cpp -o ListOfComponents/ListOfComponents

runListOfComponents:
	@./ListOfComponents/ListOfComponents . GulgECS/Includes/GulgECS/ GulgECS/Sources/GulgECS/ComponentSignatureKeeper.cpp

gulgECS: runListOfComponents
	@$(MAKE) -C GulgECS --no-print-directory

gulgGraphics: gulgECS
	@$(MAKE) -C GulgGraphics --no-print-directory

gulgInputs: gulgECS
	@$(MAKE) -C GulgInput --no-print-directory

fortressWar: gulgECS gulgGraphics gulgInputs
	@$(MAKE) -C FortressWar --no-print-directory


documentation:
	@doxygen Documentation/Doxyfile
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Documentation created.$(COLOR_END)\\n"

clean: $(FOLDERS_TO_CLEAN)
	@$(MAKE) clean -C GulgECS --no-print-directory
	@$(MAKE) clean -C GulgGraphics --no-print-directory
	@$(MAKE) clean -C GulgInput --no-print-directory
	@$(MAKE) clean -C FortressWar --no-print-directory
	@$(COMMAND_RM) -rf MakefileCreator/MakefileCreator
	@$(COMMAND_RM) -rf GulgLibraries
	@$(COMMAND_RM) -rf Documentation/html


totalclean: clean
	@$(COMMAND_RM) GulgECS/Makefile
	@$(COMMAND_RM) GulgGraphics/Makefile
	@$(COMMAND_RM) GulgInput/Makefile
	@$(COMMAND_RM) FortressWar/Makefile
	@$(COMMAND_RM) ListOfComponents/Makefile