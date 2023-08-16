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

STRING_OK      = $(COLOR_GREEN_LIGHT)[SUCCES]$(COLOR_END)
STRING_WARNING = $(COLOR_YELLOW_LIGHT)[WARNING]$(COLOR_END)
STRING_ERROR   = $(COLOR_RED_LIGHT)[ERROR]$(COLOR_END)



FMODARCHI = x86_64
CXX       = g++
CXXFLAGS  = -g -std=c++2a -Wextra -Wall -pedantic

SOURCE_FOLDER  = Sources
INCLUDE_FOLDER = Includes
OBJECT_FOLDER  = Obj
EXE_FOLDER     = .
EXE_NAME       = ListOfComponents


ifeq ($(DETECTED_OS),Windows)
	DIRECTORIES = $(subst $(SOURCE_FOLDER),$(OBJECT_FOLDER),$(shell wsl find $(SOURCE_FOLDER) -type d))
	OBJECT_FILES = $(shell wsl find $(OBJECT_FOLDER) -name *.o)
else
	DIRECTORIES = $(subst $(SOURCE_FOLDER),$(OBJECT_FOLDER),$(shell find $(SOURCE_FOLDER) -type d))
	OBJECT_FILES = $(shell find $(OBJECT_FOLDER) -name *.o)
endif

SOURCES     = $(wildcard $(SOURCE_FOLDER)/*.cpp) $(wildcard $(SOURCE_FOLDER)/**/*.cpp) $(wildcard $(SOURCE_FOLDER)/**/**/*.cpp)
OBJECTS     = $(SOURCES:$(SOURCE_FOLDER)/%.cpp=$(OBJECT_FOLDER)/%.o)


all: $(OBJECTS)
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Compilation done$(ENDCOLOR)\\n"
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Linking $(COLOR_END)$(LYELLOWCOLOR)$^$(COLOR_END)\\n"
	@$(CXX) $^ -o $(EXE_FOLDER)/$(EXE_NAME) $(LIBRARIES)
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Linking done$(COLOR_END)\\n"
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Executable created at path: $(COLOR_END)$(COLOR_RED_LIGHT)$(EXE_FOLDER)/$(EXE_NAME)$(COLOR_END)\\n"

$(OBJECT_FOLDER)/%.o: $(SOURCE_FOLDER)/%.cpp
	@$(COMMAND_MKDIR) -p $(DIRECTORIES)
	@$(COMMAND_PRINTF) "$(COLOR_GREEN_LIGHT)Compiling:  $(COLOR_END)$(COLOR_CYAN_LIGHT)$<$(COLOR_END)\\n"
	@-$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@ -I $(INCLUDE_FOLDER)


clean:
	@$(COMMAND_RM) -rf $(OBJECT_FOLDER)