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
	COMMAND_PRINTF = wsl printf
else
	COMMAND_PRINTF = printf
endif

ifeq ($(DETECTED_OS),Windows)
	COMMAND_RM = wsl rm -rf
else
	COMMAND_RM = rm -rf
endif

ifeq ($(DETECTED_OS),Windows)
	COMMAND_LN = wsl ln
else
	COMMAND_LN = ln
endif

ifeq ($(DETECTED_OS),Windows)
	COMMAND_MV = wsl mv
else
	COMMAND_MV = mv
endif

ifeq ($(DETECTED_OS),Windows)
	COMMAND_MKDIR = wsl mkdir
else
	COMMAND_MKDIR = mkdir
endif

ifeq ($(DETECTED_OS),Windows)
	COMMAND_AR = wsl ar
else
	COMMAND_AR = ar
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

GULG_ECS_FOLDER = GulgECS
GULG_GRAPHICS_FOLDER = GulgGraphics
GULG_INPUT_FOLDER = GulgInput
FORTRESSWAR = FortressWar
GULG_LIBRARIES_FOLDER = GulgLibraries
SUB_FOLDERS = $(GULG_ECS_FOLDER) $(GULG_GRAPHICS_FOLDER) $(GULG_INPUT_FOLDER) $(FORTRESSWAR)
MAKE_SUFFIX = _make
CLEAN_SUFFIX = _clean
FOLDERS_TO_MAKE = $(addsuffix $(MAKE_SUFFIX), $(SUB_FOLDERS))
FOLDERS_TO_CLEAN = $(addsuffix $(CLEAN_SUFFIX), $(SUB_FOLDERS))

DOCUMENTATION_FOLDER = Documentation/html

LIST_OF_COMPONENTS_EXE_PATH = ./ListOfComponents/ListOfComponents
GULG_TYPES_FOLDER = GulgECS/Includes/GulgECS/
GULG_SIGNATURE_KEEPER_PATH = GulgECS/Sources/GulgECS/ComponentSignatureKeeper.cpp



.PHONY: all clean listOfComponents documentation $(FOLDERS_TO_MAKE) $(FOLDERS_TO_CLEAN) toDoBeforeMake

all: toDoBeforeMake listOfComponents $(FOLDERS_TO_MAKE)

toDoBeforeMake:
	@$(COMMAND_CLEAR)
	@$(COMMAND_PRINTF) "Detected OS: " $(DETECTED_OS)


listOfComponents:
	@$(LIST_OF_COMPONENTS_EXE_PATH) . $(GULG_TYPES_FOLDER) $(GULG_SIGNATURE_KEEPER_PATH)

$(FOLDERS_TO_MAKE):
	@$(MAKE) -C $(subst $(MAKE_SUFFIX),,$@) --no-print-directory

documentation:
	@doxygen Documentation/Doxyfile
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Documentation created.$(COLOR_END)\\n"

clean: $(FOLDERS_TO_CLEAN)
	@$(COMMAND_RM) $(GULG_LIBRARIES_FOLDER)

$(FOLDERS_TO_CLEAN):
	@$(MAKE) clean -C $(subst $(CLEAN_SUFFIX),,$@) --no-print-directory
	@$(COMMAND_RM) -rf $(DOCUMENTATION_FOLDER)