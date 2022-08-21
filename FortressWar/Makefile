#Compilation
CXX        = g++
CXXFLAGS   = -g -std=c++2a -Wextra -Wall -pedantic

OBJFOLDERS = $(subst $(SRCFOLDER),$(OBJFOLDER),$(shell find $(SRCFOLDER) -type d))
OBJFILES   = $(shell find $(OBJFOLDER) -name *.o)


#List of all .cpp files to compile
SRC     = $(wildcard $(SRCFOLDER)/*.cpp) $(wildcard $(SRCFOLDER)/**/*.cpp) $(wildcard $(SRCFOLDER)/**/**/*.cpp) $(wildcard $(SRCFOLDER)/**/**/**/*.cpp)

#List of targets for the compilation (a .o for each .cpp file)
OBJ     = $(SRC:$(SRCFOLDER)/%.cpp=$(OBJFOLDER)/%.o)

#Paths

SRCFOLDER = ./Sources
INCFOLDER = ./Includes
OBJFOLDER = ./Obj
BINFOLDER = ./Bin
EXENAME   = GulgGraphics

SRCFOLDER = Sources
INCFOLDER = Includes
OBJFOLDER = Obj
EXEFOLDER = .
EXENAME   = FortressWarExe

#Libraries

LIBRARIESTOINCLUDE  = $(GULGLIBRARIESINCLUDESFOLDER) $(EXTERNALLIBFOLDERSTOINCLUDE)
LIBRARIESTOLINK     = $(GULGLIBRARIESTOLINK) $(EXTERNALLIBFOLDERSTOLINK)

#Gulg libraries

GULGLIBRARIESTOLINK 		= -L $(GULGLIBRARIESLIBFOLDER)/GulgECS/Static -L $(GULGLIBRARIESLIBFOLDER)/GulgGraphics/Static -L $(GULGLIBRARIESLIBFOLDER)/GulgInput/Static -lgulginput -lgulggraphics -lgulgecs

#Folder where we will create a symbolink link to INCFOLDER for other libraries
GULGLIBRARIESINCLUDESFOLDER = ../GulgLibraries/Includes

#Folder where we will create a symbolink link to LIBFOLDER for other libraries
GULGLIBRARIESLIBFOLDER 		= ../GulgLibraries/Libraries

#External libraries

EXTERNALLIBFOLDER 			= ../ExternalLibraries/
EXTERNALLIBFOLDERSTOINCLUDE = -I $(EXTERNALLIBFOLDER)/$(SFMLINCLUDEFOLDER)
EXTERNALLIBTOLINK    		= $(SFMLLINK)

#SFML
SFMLINCLUDEFOLDER 	= SFML/include
SFMLLINKFOLDER 		= SFML/lib
SFMLLIBTOLINK 		= -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d
SFMLNEEDEDLIBTOLINK = -lpthread -lGL -lX11 -lXrandr -lfreetype -lGLEW -lopenal -ludev
SFMLLINK 			= -L $(EXTERNALLIBFOLDER)/$(SFMLLINKFOLDER) $(SFMLLIBTOLINK) $(SFMLNEEDEDLIBTOLINK)


DIRECTORIES = $(subst $(SRCFOLDER),$(OBJFOLDER),$(shell find $(SRCFOLDER) -type d))
OBJFILES = $(shell find $(OBJFOLDER) -name *.o)

SRC     = $(wildcard $(SRCFOLDER)/*.cpp) $(wildcard $(SRCFOLDER)/**/*.cpp) $(wildcard $(SRCFOLDER)/**/**/*.cpp) $(wildcard $(SRCFOLDER)/**/**/**/*.cpp)
OBJ     = $(SRC:$(SRCFOLDER)/%.cpp=$(OBJFOLDER)/%.o)

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

OKSTRING   = $(LGREENCOLOR)[SUCCES]$(ENDCOLOR)
WARSTRING  = $(LYELLOWCOLOR)[WARNING]$(ENDCOLOR)
ERRSTRING  = $(LREDCOLOR)[ERROR]$(ENDCOLOR)

all: $(OBJ) copyExeToParent
	@printf "$(LGREENCOLOR)Compilation done$(ENDCOLOR)\\n"
	@printf "$(LGREENCOLOR)Linking $(ENDCOLOR)$(LYELLOWCOLOR)$(OBJ)$(ENDCOLOR)\\n"
	@$(CXX) $(OBJ) -o $(EXEFOLDER)/$(EXENAME) $(GULGLIBRARIESTOLINK) $(EXTERNALLIBTOLINK)
	@printf "$(LGREENCOLOR)Linking done$(ENDCOLOR)\\n"
	@printf "$(LGREENCOLOR)Executable created at path: $(ENDCOLOR)$(LREDCOLOR)$(EXEFOLDER)/$(EXENAME)$(ENDCOLOR)\\n"

copyExeToParent:
	@cp $(EXEFOLDER)/$(EXENAME) ../

$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.cpp
	@mkdir -p $(DIRECTORIES)
	@printf "$(LGREENCOLOR)Compiling:  $(ENDCOLOR)$(LCYANCOLOR)$<$(ENDCOLOR)\\n"
	@-$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@ -I $(INCFOLDER) -I $(GULGLIBRARIESINCLUDESFOLDER) $(EXTERNALLIBFOLDERSTOINCLUDE)

clean:
	@rm -rf $(OBJFOLDER)
	@rm -rf $(BINFOLDER)