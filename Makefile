GULGECSFOLDER = GulgECS
GULGGRAPHICSFOLDER = GulgGraphics
GULGINPUTFOLDER = GulgInput
FORTRESSWAR = FortressWar
GULGLIBRARIESFOLDER = GulgLibraries
SUBFOLDERS = $(GULGECSFOLDER) $(GULGGRAPHICSFOLDER) $(GULGINPUTFOLDER) $(FORTRESSWAR)
MAKESUFFIX = _make
CLEANSUFFIX = _clean
FOLDERSTOMAKE = $(addsuffix $(MAKESUFFIX), $(SUBFOLDERS))
FOLDERSTOCLEAN = $(addsuffix $(CLEANSUFFIX), $(SUBFOLDERS))

DOCUMENTATIONFOLDER = Documentation/html

LISTOFCOMPONENTSEXEPATH = ./ListOfComponents/ListOfComponents
GULGTYPESFOLDER = GulgECS/Includes/GulgECS/
GULGSIGNATUREKEEPERPATH = GulgECS/Sources/GulgECS/ComponentSignatureKeeper.cpp

ENDCOLOR    = \033[m

REDCOLOR	= \033[0;31m
GREENCOLOR  = \033[0;32m
YELLOWCOLOR = \033[0;33m
BLUECOLOR	= \033[0;34m
PURPLECOLOR = \033[0;35m
CYANCOLOR	= \033[0;36m
GREYCOLOR 	= \033[0;37m

LREDCOLOR	 = \033[1;31m
LGREENCOLOR	 = \033[1;32m
LYELLOWCOLOR = \033[1;33m
LBLUECOLOR   = \033[1;34m
LPURPLECOLOR = \033[1;35m
LCYANCOLOR	 = \033[1;36m
LGREYCOLOR	 = \033[1;37m


REPLACED_TEXT =

#Commands

ifeq ($(OS),Windows_NT)
	DETECTED_OS = Windows
else
	DETECTED_OS = Linux
endif
 
ifeq ($(DETECTED_OS),Windows)
	COMMAND_CLEAR = cls
else
	COMMAND_CLEAR = clear
endif

ifeq ($(DETECTED_OS),Windows)
	COMMAND_PRINTF =
else
	COMMAND_PRINTF = printf
endif

ifeq ($(DETECTED_OS),Windows)
	COMMAND_RM = rmdr /s /q
else
	COMMAND_RM = rm -rf
endif


define string_replace
	$(if $(filter $(DETECTED_OS),Windows), $(eval $(4)=$(shell WindowsScript\subst.bat "$1" "$2" "$3")), $(4)=$(subst $1, $2, $3))
endef

.PHONY: all clean listOfComponents documentation $(FOLDERSTOMAKE) $(FOLDERSTOCLEAN) toDoBeforeMake

all: toDoBeforeMake listOfComponents $(FOLDERSTOMAKE)

toDoBeforeMake:
	@$(COMMAND_CLEAR)
	@echo Detected OS: $(DETECTED_OS)
	$(call string_replace,is,bob,This is a test, TESTNAME)
	@echo $(TESTNAME)


listOfComponents:
	@$(LISTOFCOMPONENTSEXEPATH) . $(GULGTYPESFOLDER) $(GULGSIGNATUREKEEPERPATH)

$(FOLDERSTOMAKE):
	@$(MAKE) -C $(subst $(MAKESUFFIX),, $@) --no-print-directory

documentation:
	@doxygen Documentation/Doxyfile
	@$(COMMAND_PRINTF) "$(LGREENCOLOR)Documentation created.$(ENDCOLOR)\\n"

clean: $(FOLDERSTOCLEAN)
	@$(COMMAND_RM) $(GULGLIBRARIESFOLDER)

$(FOLDERSTOCLEAN):
	$(call string_replace,$(CLEANSUFFIX),,$@, REPLACED_TEXT)
	@$(MAKE) clean -C $(REPLACED_TEXT) --no-print-directory
	@$(COMMAND_RM) -rf $(DOCUMENTATIONFOLDER)