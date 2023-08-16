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

SOURCE_FOLDER  = ./Sources
INCLUDE_FOLDER = ./Includes
OBJECT_FOLDER  = ./Obj
LIBRARY_FOLDER = ./Bin
LIBRARY_NAME   = GulgGraphics

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

GULG_LIBRARIES_TO_LINK 		   = -L $(GULG_LIBRARIES_TO_LINK_FOLDER)

#Folder where we will create a symbolink link to INCLUDE_FOLDER for other libraries
GULG_LIBRARIES_INCLUDES_FOLDER = ../GulgLibraries/Includes

#Folder where we will create a symbolink link to LIBRARY_FOLDER for other libraries
GULG_LIBRARIES_TO_LINK_FOLDER  = ../GulgLibraries/Libraries

#External libraries

EXTERNAL_LIBRARIES_FOLDER 			  = ../ExternalLibraries/
EXTERNAL_LIBRARIES_FOLDERS_TO_INCLUDE = $(EXTERNAL_LIBRARIES_FOLDER)/$(SFML_INCLUDE_FOLDER)
EXTERNAL_LIBRARIES_TO_LINK    		  = $(SFML_LINK)

#SFML

ifeq ($(DETECTED_OS),Windows)
	SFML_LINK_FOLDER 		       = SFML/lib/Windows
	SFML_NEEDED_LIBRARIES_TO_LINK  = -lpthread -lGL -lX11 -lXrandr -lfreetype -lGLEW -lopenal -ludev
	SFML_DYNAMIC_LIBRARIES_TO_LINK = -lsfml-graphics-d-2 -lsfml-window-d-2 -lsfml-system-d-2
else
	SFML_LINK_FOLDER 		       = SFML/lib/Linux
	SFML_NEEDED_LIBRARIES_TO_LINK  = -lpthread -lGL -lX11 -lXrandr -lfreetype -lGLEW -lopenal -ludev
	SFML_DYNAMIC_LIBRARIES_TO_LINK = -lsfml-graphics-d -lsfml-window-d -lsfml-system-d
endif

SFML_INCLUDE_FOLDER 	      = SFML/include
SFML_STATIC_LIBRARIES_TO_LINK = -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d
SFML_LINK 			          = -L $(EXTERNAL_LIBRARIES_FOLDERS_TO_INCLUDE)/$(SFML_LINK_FOLDER) $(SFML_STATIC_LIBRARIES_TO_LINK) $(SFML_NEEDED_LIBRARIES_TO_LINK)


all: compile staticlib exportLib
	@$(COMMAND_PRINTF) "$(COLOR_PURPLE_LIGHT)$(LIBRARY_NAME) successfully make$(COLOR_END)\\n"

compile: $(OBJECTS)
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Compilation done$(COLOR_END)\\n"

$(OBJECT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.cpp
	@$(COMMAND_MKDIR) -p $(OBJECT_FOLDERS)
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Compiling:  $(COLOR_END)$(COLOR_CYAN_LIGHT)$<$(COLOR_END)\\n"
	@-$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@ -I $(INCLUDE_FOLDER) -I $(GULG_LIBRARIES_INCLUDES_FOLDER) -I $(EXTERNAL_LIBRARIES_FOLDERS_TO_INCLUDE)
	

staticlib: compile
	@$(COMMAND_MKDIR) -p $(LIBRARY_FOLDER)/$(STATIC_LIBRARY_FOLDER)
	@$(COMMAND_AR) rsc $(LIBRARY_FOLDER)/$(STATIC_LIBRARY_FOLDER)/$(STATIC_LIBRARY_NAME) $(OBJECT_FILES)
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Static library created$(COLOR_END)\\n"

dynamiclib: compile
	@$(COMMAND_MKDIR) -p $(LIBRARY_FOLDER)/$(DYNAMIC_LIBRARY_FOLDER)
	@-$(CXX) -shared -o $(LIBRARY_FOLDER)/$(DYNAMIC_LIBRARY_FOLDER)/$(DYNAMIC_LIBARY_NAME) $(OBJECT_FILES)
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Dynamic library created$(COLOR_END)\\n"

exportLib:
	@$(COMMAND_MKDIR) -p $(GULG_LIBRARIES_INCLUDES_FOLDER)
	@$(COMMAND_MKDIR) -p $(GULG_LIBRARIES_TO_LINK_FOLDER)

ifeq ($(DETECTED_OS),Windows)
	@$(COMMAND_RM) -f $(GULG_LIBRARIES_INCLUDES_FOLDER)/$(LIBRARY_NAME)
	@$(COMMAND_RM) -f $(GULG_LIBRARIES_TO_LINK_FOLDER)/$(LIBRARY_NAME)
	@mklink /D "$(realpath $(GULG_LIBRARIES_INCLUDES_FOLDER)/$(LIBRARY_NAME))" "$(realpath $(INCLUDE_FOLDER)/$(LIBRARY_NAME))"
	@mklink /D "$(realpath $(GULG_LIBRARIES_TO_LINK_FOLDER)/$(LIBRARY_NAME))" "$(realpath $(LIBRARY_FOLDER))"
	
else
	@ln -sf "$(realpath $(INCLUDE_FOLDER)/$(LIBNAME))" $(GULG_LIBRARIES_INCLUDES_FOLDER)
	@ln -sf "$(realpath $(LIBRARY_FOLDER))/$(LIBRARY_NAME)" $(GULG_LIBRARIES_TO_LINK_FOLDER)
endif

	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Library successfully exported$(COLOR_END)\\n"

clean:
	@$(COMMAND_RM) -rf $(GULG_LIBRARIES_INCLUDES_FOLDER)/$(LIBRARY_NAME)
	@$(COMMAND_RM) -rf $(GULG_LIBRARIES_TO_LINK_FOLDER)/$(LIBRARY_NAME)
	@$(COMMAND_RM) -rf $(OBJECT_FOLDER)
	@$(COMMAND_RM) -rf $(LIBRARY_FOLDER)