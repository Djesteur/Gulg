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

COLOR_RED	 = \033[0;31m
COLOR_GREEN  = \033[0;32m
COLOR_YELLOW = \033[0;33m
COLOR_BLUE	 = \033[0;34m
COLOR_PURPLE = \033[0;35m
COLOR_CYAN	 = \033[0;36m
COLOR_GREY 	 = \033[0;37m

COLOR_RED_LIGHT	  = \033[1;31m
COLOR_GREEN_LIGHT  = \033[1;32m
COLOR_YELLOW_LIGHT = \033[1;33m
COLOR_BLUE_LIGHT   = \033[1;34m
COLOR_PURPLE_LIGHT = \033[1;35m
COLOR_CYAN_LIGHT	  = \033[1;36m
COLOR_GREY_LIGHT	  = \033[1;37m

COLOR_END = \033[m

STRING_OK   = $(COLOR_GREEN_LIGHT)[SUCCES]$(COLOR_END)
STRING_WARNING  = $(COLOR_YELLOW_LIGHT)[WARNING]$(COLOR_END)
STRING_ERROR  = $(COLOR_RED_LIGHT)[ERROR]$(COLOR_END)

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
	COMMAND_RM = del /s /q
else
	COMMAND_RM = rm -rf
endif

ifeq ($(DETECTED_OS),Windows)
	SLASH = \\
else
	SLASH = /
endif

#Replace text function
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
	$(call string_replace,$(MAKESUFFIX),,$@, REPLACED_TEXT)
	@$(MAKE) -C $(REPLACED_TEXT) --no-print-directory

documentation:
	@doxygen Documentation/Doxyfile
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Documentation created.$(COLOR_END)\\n"

clean: $(FOLDERSTOCLEAN)
	@$(COMMAND_RM) $(GULGLIBRARIESFOLDER)

$(FOLDERSTOCLEAN):
	$(call string_replace,$(CLEANSUFFIX),,$@, REPLACED_TEXT)
	@$(MAKE) clean -C $(REPLACED_TEXT) --no-print-directory
	@$(COMMAND_RM) -rf $(DOCUMENTATIONFOLDER)