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

.PHONY: all clean listOfComponents documentation $(FOLDERSTOMAKE) $(FOLDERSTOCLEAN) toDoBeforeMake

all: toDoBeforeMake listOfComponents $(FOLDERSTOMAKE) documentation

toDoBeforeMake:
	@clear

listOfComponents:
	@$(LISTOFCOMPONENTSEXEPATH) . $(GULGTYPESFOLDER) $(GULGSIGNATUREKEEPERPATH)

$(FOLDERSTOMAKE):
	@$(MAKE) -C $(subst $(MAKESUFFIX),, $@) --no-print-directory

documentation:
	@doxygen Documentation/Doxyfile
	@printf "$(LGREENCOLOR)Documentation created.$(ENDCOLOR)\\n"

clean: $(FOLDERSTOCLEAN)
	@rm -rf $(GULGLIBRARIESFOLDER)

$(FOLDERSTOCLEAN):
	@$(MAKE) clean -C $(subst $(CLEANSUFFIX),, $@) --no-print-directory
	@rm -rf $(DOCUMENTATIONFOLDER)