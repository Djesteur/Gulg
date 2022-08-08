FMODARCHI = x86_64
CXX       = g++
CXXFLAGS  = -g -std=c++2a -Wextra -Wall -pedantic
LIBRARIES = -L ./GulgLibraries/ -lgulgecs.so $(SFMLLIBRARIES) $(OTHERLIBRARIES)
SFMLLIBRARIES = -L ExternalLibraries/SFML/lib -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d
OTHERLIBRARIES = -lpthread -lGL -lX11 -lXrandr -lfreetype -lGLEW -lopenal -ludev

SRCFOLDER = Sources
INCFOLDER = Includes
OBJFOLDER = Obj
GULGLIBFOLDER = GulgLibraries
EXEFOLDER = .
BINFOLDER = Bin
LIBINCLUDEFOLDERS = -I ../GulgECS/Includes -I ../ExternalLibraries/SFML/include

STATICLIBFOLDER  = Static
DYNAMICLIBFOLDER = Dynamic
STATICLIBNAME  = libgulggraphics.a
DYNAMICLIBNAME = libgulggraphics.so

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

all: copylibs compile staticlib dynamiclib

copylibs:
	@mkdir -p $(GULGLIBFOLDER)
	@cp ../GulgECS/Bin/Static/* $(GULGLIBFOLDER)

compile: $(OBJ)
	@printf "$(LGREENCOLOR)Compilation done$(ENDCOLOR)\\n"

$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.cpp
	@mkdir -p $(DIRECTORIES)
	@printf "$(LGREENCOLOR)Compiling:  $(ENDCOLOR)$(LCYANCOLOR)$<$(ENDCOLOR)\\n"
	@-$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@ -I $(INCFOLDER) $(LIBINCLUDEFOLDERS)

staticlib: copylibs compile
	@mkdir -p $(BINFOLDER)/$(STATICLIBFOLDER)
	@printf "$(LGREENCOLOR)Creating static lib:  $(ENDCOLOR)$(LCYANCOLOR)$(BINFOLDER)/$(STATICLIBNAME)$(ENDCOLOR)\\n"
	@ar rsc $(BINFOLDER)/$(STATICLIBFOLDER)/$(STATICLIBNAME) $(OBJFILES)
	@printf "$(LGREENCOLOR)Static library created$(ENDCOLOR)\\n"

dynamiclib: copylibs compile
	@mkdir -p $(BINFOLDER)/$(DYNAMICLIBFOLDER)
	@printf "$(LGREENCOLOR)Creating dynamic lib:  $(ENDCOLOR)$(LCYANCOLOR)$(BINFOLDER)/$(DYNAMICLIBNAME)$(ENDCOLOR)\\n"
	@-$(CXX) -shared -o $(BINFOLDER)/$(DYNAMICLIBFOLDER)/$(DYNAMICLIBNAME) $(OBJFILES)
	@printf "$(LGREENCOLOR)Dynamic library created$(ENDCOLOR)\\n"


clean:
	@rm -rf $(OBJFOLDER)
	@rm -rf $(BINFOLDER)
	@rm -rf $(GULGLIBFOLDER)