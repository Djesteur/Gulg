FMODARCHI = x86_64
CXX       = g++
CXXFLAGS  = -g -std=c++2a -Wextra -Wall -pedantic
LIBRARIES = -L ../Gulg/Bin/Static -l$(LIBNAME) $(SFMLLIBRARIES) $(OTHERLIBRARIES)
SFMLLIBRARIES = -L ExternalLibraries/SFML/lib -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d
OTHERLIBRARIES = -lpthread -lGL -lX11 -lXrandr -lfreetype -lGLEW -lopenal -ludev

SRCFOLDER = Sources
INCFOLDER = Includes
OBJFOLDER = Obj
EXEFOLDER = .
BINFOLDER = Bin
EXENAME = test
LIBNAME  = gulgengine

DIRECTORIES = $(subst $(SRCFOLDER),$(OBJFOLDER),$(shell find $(SRCFOLDER) -type d))
OBJFILES = $(shell find $(OBJFOLDER) -name *.o)

SRC     = $(wildcard $(SRCFOLDER)/*.cpp) $(wildcard $(SRCFOLDER)/**/*.cpp) $(wildcard $(SRCFOLDER)/**/**/*.cpp)
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

all: $(OBJ)
	@printf "$(LGREENCOLOR)Compilation done$(ENDCOLOR)\\n"
	@printf "$(LGREENCOLOR)Linking $(ENDCOLOR)$(LYELLOWCOLOR)$^$(ENDCOLOR)\\n"
	@$(CXX) $^ -o $(EXEFOLDER)/$(EXENAME) $(LIBRARIES)
	@printf "$(LGREENCOLOR)Linking done$(ENDCOLOR)\\n"
	@printf "$(LGREENCOLOR)Executable created at path: $(ENDCOLOR)$(LREDCOLOR)$(EXEFOLDER)/$(EXENAME)$(ENDCOLOR)\\n"

$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.cpp
	@mkdir -p $(DIRECTORIES)
	@printf "$(LGREENCOLOR)Compiling:  $(ENDCOLOR)$(LCYANCOLOR)$<$(ENDCOLOR)\\n"
	@-$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@ -I $(INCFOLDER) -I ../Gulg/Includes/ -I ./ExternalLibraries/SFML/include/


clean:
	@rm -rf $(OBJFOLDER)
	@rm -rf $(BINFOLDER)