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
	COMMAND_RM = wsl rm
else
	COMMAND_RM = rm
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

ifeq ($(DETECTED_OS),Windows)
	COMMAND_CP = wsl cp
else
	COMMAND_CP = cp
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

ifeq ($(DETECTED_OS),Windows)
	OBJECT_FOLDERS = $(subst $(SOURCE_FOLDER),$(OBJECT_FOLDER),$(shell wsl find $(SOURCE_FOLDER) -type d))
	OBJECT_FILES   = $(shell wsl find $(OBJECT_FOLDER) -name *.o)
else
	OBJECT_FOLDERS = $(subst $(SOURCE_FOLDER),$(OBJFOLDER),$(shell find $(SOURCE_FOLDER) -type d))
	OBJECT_FILES   = $(shell find $(OBJFOLDER) -name *.o)
endif


#List of all .cpp files to compile
SOURCES     = $(wildcard $(SOURCE_FOLDER)/*.cpp) $(wildcard $(SOURCE_FOLDER)/**/*.cpp) $(wildcard $(SOURCE_FOLDER)/**/**/*.cpp) $(wildcard $(SOURCE_FOLDER)/**/**/**/*.cpp)

#List of targets for the compilation (a .o for each .cpp file)
OBJECTS     = $(SOURCES:$(SOURCE_FOLDER)/%.cpp=$(OBJECT_FOLDER)/%.o)

#Paths

SOURCE_FOLDER  = Sources
INCLUDE_FOLDER = Includes
OBJECT_FOLDER  = Obj
BIN_FOLDER     = Bin
EXE_NAME       = FortressWar

ifeq ($(DETECTED_OS),Windows)
	LOWER_LIBRARY_NAME = $(shell echo $(LIBRARY_NAME)| wsl tr A-Z a-z)
else
	LOWER_LIBRARY_NAME = $(shell echo $(LIBRARY_NAME)| tr A-Z a-z)
endif

#Link
STATIC_LIBRARY_FOLDER  = Static
DYNAMIC_LIBRARY_FOLDER = Dynamic
STATIC_LIBRARY_NAME    = lib$(LOWER_LIBRARY_NAME).a
DYNAMIC_LIBARY_NAME    = lib$(LOWER_LIBRARY_NAME).so

#Libraries

LIBRARIES_TO_INCLUDE  = $(GULG_LIBRARIES_INCLUDES_FOLDER) $(EXTERNAL_LIBRARIES_FOLDERS_TO_INCLUDE)
LIBRARIES_TO_LINK     = $(GULG_LIBRARIES_TO_LINK) $(GULG_LIBRARIES_TO_LINK_FOLDER)

#Gulg libraries

GULG_LIBRARIES_TO_LINK 		   = -L $(GULG_LIBRARIES_TO_LINK_FOLDER)/GulgECS/Static -L $(GULG_LIBRARIES_TO_LINK_FOLDER)/GulgGraphics/Static -L $(GULG_LIBRARIES_TO_LINK_FOLDER)/GulgInput/Static -lgulginput -lgulggraphics -lgulgecs

#Folder where we will create a symbolink link to INCLUDE_FOLDER for other libraries
GULG_LIBRARIES_INCLUDES_FOLDER = ../GulgLibraries/Includes

#Folder where we will create a symbolink link to LIBRARY_FOLDER for other libraries
GULG_LIBRARIES_TO_LINK_FOLDER  = ../GulgLibraries/Libraries

#External libraries

EXTERNAL_LIBRARIES_FOLDER 			  = ../ExternalLibraries
EXTERNAL_LIBRARIES_FOLDERS_TO_INCLUDE = $(EXTERNAL_LIBRARIES_FOLDER)/$(SFML_INCLUDE_FOLDER)
EXTERNAL_LIBRARIES_TO_LINK    		  = $(SFML_LINK)

#SFML

ifeq ($(DETECTED_OS),Windows)
	SFML_LINK_FOLDER 		       = SFML/lib/Windows
	SFML_NEEDED_LIBRARIES_TO_LINK  =
	SFML_STATIC_LIBRARIES_TO_LINK  = -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d
	SFML_DYNAMIC_LIBRARIES_TO_LINK = -lsfml-graphics-d-2 -lsfml-window-d-2 -lsfml-system-d-2
else
	SFML_LINK_FOLDER 		       = SFML/lib/Linux
	SFML_NEEDED_LIBRARIES_TO_LINK  = -lpthread -lGL -lX11 -lXrandr -lfreetype -lGLEW -lopenal -ludev
	SFML_STATIC_LIBRARIES_TO_LINK  = -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d
	SFML_DYNAMIC_LIBRARIES_TO_LINK = -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
endif

SFML_INCLUDE_FOLDER 	      = SFML/include
SFML_LINK 			          = -L $(EXTERNAL_LIBRARIES_FOLDER)/$(SFML_LINK_FOLDER) $(SFML_STATIC_LIBRARIES_TO_LINK) $(SFML_NEEDED_LIBRARIES_TO_LINK)





GULG_ECS_FOLDER      = GulgECS
GULG_GRAPHICS_FOLDER = GulgGraphics
GULG_INPUT_FOLDER    = GulgInput
FORTRESSWAR          = FortressWar

GULG_LIBRARIES_FOLDER = GulgLibraries

SUB_FOLDERS = $(GULG_ECS_FOLDER) $(GULG_GRAPHICS_FOLDER) $(GULG_INPUT_FOLDER) $(FORTRESSWAR)

MAKE_SUFFIX = _make
CLEAN_SUFFIX = _clean

FOLDERS_TO_MAKE = $(addsuffix $(MAKE_SUFFIX), $(SUB_FOLDERS))
FOLDERS_TO_CLEAN = $(addsuffix $(CLEAN_SUFFIX), $(SUB_FOLDERS))

DOCUMENTATION_FOLDER = Documentation/html

LIST_OF_COMPONENTS_EXE_PATH  = ./ListOfComponents/ListOfComponents
GULG_TYPES_FOLDER            = GulgECS/Includes/GulgECS/
GULG_SIGNATURE_KEEPER_PATH   = GulgECS/Sources/GulgECS/ComponentSignatureKeeper.cpp


.PHONY: all clean listOfComponents documentation $(FOLDERS_TO_MAKE) $(FOLDERS_TO_CLEAN) toDoBeforeMake

all: compileMakefileCreator generateMakefiles compileListOfComponents runListOfComponents $(FOLDERS_TO_MAKE) documentation


compileMakefileCreator:
	@-$(CXX) $(CXXFLAGS) -fPIC MakefileCreator/Sources/main.cpp -o MakefileCreator/MakefileCreator

generateMakefiles: compileMakefileCreator
	@MakefileCreator/MakefileCreator GulgECS lib
	@MakefileCreator/MakefileCreator GulgGraphics lib
	@MakefileCreator/MakefileCreator GulgInput lib
	@MakefileCreator/MakefileCreator ListOfComponents exe
	@MakefileCreator/MakefileCreator FortressWar exe

compileListOfComponents: generateMakefiles
	@-$(CXX) $(CXXFLAGS) -fPIC ListOfComponents/Sources/main.cpp -o ListOfComponents/ListOfComponents

runListOfComponents: compileListOfComponents
	@$(LIST_OF_COMPONENTS_EXE_PATH) . $(GULG_TYPES_FOLDER) $(GULG_SIGNATURE_KEEPER_PATH)

gulgECS: generateMakefiles runListOfComponents
	@$(MAKE) -C $(subst $(MAKE_SUFFIX),,$@) --no-print-directory


$(FOLDERS_TO_MAKE):
	@$(MAKE) -C $(subst $(MAKE_SUFFIX),,$@) --no-print-directory

documentation:
	@doxygen Documentation/Doxyfile
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Documentation created.$(COLOR_END)\\n"

clean: $(FOLDERS_TO_CLEAN)
	@$(COMMAND_RM) -rf $(GULG_LIBRARIES_FOLDER)

$(FOLDERS_TO_CLEAN):
	@$(MAKE) clean -C $(subst $(CLEAN_SUFFIX),,$@) --no-print-directory
	@$(COMMAND_RM) -rf $(DOCUMENTATION_FOLDER)

totalClean: clean
	@$(COMMAND_RM) GulgECS/Makefile
	@$(COMMAND_RM) GulgGraphics/Makefile
	@$(COMMAND_RM) GulgInput/Makefile
	@$(COMMAND_RM) FortressWar/Makefile
	@$(COMMAND_RM) ListOfComponents/Makefile