#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
#include <map>
#include <limits>
#include <algorithm>

std::map<std::string, std::string> getTextToCopy(std::ifstream &stream) {

	std::string currentPart{""};
	std::string currentLine;
	std::map<std::string, std::string> result;

	while(std::getline(stream, currentLine)) {

		if(currentLine.find("#---------------------------------------------#") != std::string::npos) {

			std::getline(stream, currentLine);
			currentLine.erase(0, 1);
			result.emplace(currentLine, currentPart);
			currentPart = "";
		}

		else { currentPart += currentLine + "\n"; }
	}

	return result;
}

std::string addTextForLibrary(const std::string &libraryName, const std::string &allPart, const std::string &libPart) {

	std::string result{""};
	result += "#This file was auto-generated by the MakefileCreator. Please, don't modify it\n\n";
	result += allPart + '\n';
	result += "LIBRARY_NAME = " + libraryName + '\n';
	result += "LIBRARY_FOLDER = " + libraryName + '\n';
	result += libPart + '\n';
	return result;
	
}

std::string addTextForExecutable(const std::string &exeName, const std::string &allPart, const std::string &exePart) {

	std::string result{""};
	result += "#This file was auto-generated by the MakefileCreator. Please, don't modify it\n\n";
	result += allPart + '\n';
	result += "EXE_NAME = " + exeName + '\n';
	result += "EXE_FOLDER = " + exeName + '\n';
	result += exePart + '\n';
	return result;
}


std::string replaceInFile(const std::string &toReplace, const std::string &toSearch, const std::string &replacedBy) {

	std::string result{toReplace};

	size_t foundPosition{0};

	while(foundPosition != std::string::npos) {

		foundPosition = result.find(toSearch, 0);
		if(foundPosition != std::string::npos) { result.replace(foundPosition, toSearch.size(), replacedBy); }
	}

	return result;
}

std::string replaceCommandForLinux(const std::string &toReplace) {

	std::string result{toReplace};
	result = replaceInFile(result, "$(COMMAND_CLEAR)", "clear");
	result = replaceInFile(result, "$(COMMAND_PRINTF)", "printf");
	result = replaceInFile(result, "$(COMMAND_RM)", "rm");
	result = replaceInFile(result, "$(COMMAND_LN)", "ln");
	result = replaceInFile(result, "$(COMMAND_MV)", "mv");
	result = replaceInFile(result, "$(COMMAND_MKDIR)", "mkdir");
	result = replaceInFile(result, "$(COMMAND_AR)", "ar");
	result = replaceInFile(result, "$(COMMAND_CP)", "cp");
	result = replaceInFile(result, "$(COMMAND_FIND)", "find");
	result = replaceInFile(result, "$(COMMAND_TR)", "tr");
	return result;
}

std::string replaceCommandForWindows(const std::string &toReplace) {

	std::string result{toReplace};
	result = replaceInFile(result, "$(COMMAND_CLEAR)", "cls");
	result = replaceInFile(result, "$(COMMAND_PRINTF)", "wsl printf");
	result = replaceInFile(result, "$(COMMAND_RM)", "wsl rm");
	result = replaceInFile(result, "$(COMMAND_LN)", "wsl ln");
	result = replaceInFile(result, "$(COMMAND_MV)", "wsl mv");
	result = replaceInFile(result, "$(COMMAND_MKDIR)", "wsl mkdir");
	result = replaceInFile(result, "$(COMMAND_AR)", "wsl ar");
	result = replaceInFile(result, "$(COMMAND_CP)", "wsl cp");
	result = replaceInFile(result, "$(COMMAND_FIND)", "wsl find");
	result = replaceInFile(result, "$(COMMAND_TR)", "wsl tr");
	return result;
}

std::string replaceOSDifference(const std::string &toReplace, std::string osType) {

	std::string result{toReplace};

	size_t foundPosition{0};

	while(foundPosition != std::string::npos) {

		foundPosition = result.find("#OS-DIFFERENCE#", 0);
		if(foundPosition != std::string::npos) {

			size_t currentDiffEnd = result.find("#OS-DIFFERENCE-END#", 0);

			std::string diffText = result.substr(foundPosition, currentDiffEnd - foundPosition);
			size_t osPartBegin = diffText.find("#" + osType, 0) + 1 + osType.size();
			if(osPartBegin == std::string::npos) { std::cout << "ERROR: can't find difference for" + osType << std::endl; return result; }

			size_t osPartEnd = osPartBegin + 1;
			std::string osPartText{""};
			while(diffText[osPartEnd] != '#') { 

				osPartText += diffText[osPartEnd]; 
				osPartEnd++;
			}

			result.replace(foundPosition, (currentDiffEnd + 20) - foundPosition, osPartText);
		}
	}

	return result;
}


std::string replaceForOS(const std::string &toReplace) {

	std::string result{toReplace};

	#if defined(_linux_)
		result = replaceCommandForLinux(toReplace);
		result = replaceOSDifference(result, "Linux");
	#elif defined(_WIN32)
		result = replaceCommandForWindows(toReplace);
		result = replaceOSDifference(result, "Windows");
	#elif defined(_WIN64)
		result = replaceCommandForWindows(toReplace);
		result = replaceOSDifference(result, "Windows");
	#endif

	return result;
}

std::string addLibraries(const std::vector<std::string> libraries, const std::string &text) {

	std::string result{text};

	for(const std::string &currentLibrary: libraries) {

		if(currentLibrary.find("Gulg") != std::string::npos) {

			//Not already added include
			size_t foundVariable = result.find("GENERATED_LIBRARIES_TO_INCLUDE =");
			if(foundVariable == std::string::npos) { std::cout << "Can't find LIBRARIES_TO_INCLUDE = gulg" << std::endl;}
			result.replace(foundVariable + 32, 0, " -I ../GulgLibraries/Includes");

			//Link

			std::string currentLibraryAsLowerCase = currentLibrary;
			for(size_t i{0}; i < currentLibraryAsLowerCase.size(); i++) { currentLibraryAsLowerCase[i] = std::tolower(currentLibraryAsLowerCase[i]); }
			foundVariable = result.find("GENERATED_LIBRARIES_TO_LINK =");
			if(foundVariable == std::string::npos) { std::cout << "Can't find LIBRARIES_TO_LINK = gulg" << std::endl;}
			result.replace(foundVariable + 29, 0, " -L ../GulgLibraries/Includes/" + currentLibrary + "/Statics -l" + currentLibraryAsLowerCase);
		}

		if(currentLibrary.find("SFML") != std::string::npos) {

			//Not already added include

			size_t foundVariable = result.find("GENERATED_LIBRARIES_TO_INCLUDE =");
			if(foundVariable == std::string::npos) { std::cout << "Can't find LIBRARIES_TO_INCLUDE = sfml" << std::endl;}
			result.replace(foundVariable + 32, 0, " -I $(EXTERNAL_LIBRARIES_FOLDER)/SFML/include");
			

			//Link

			foundVariable = result.find("GENERATED_LIBRARIES_TO_LINK =");
			if(foundVariable == std::string::npos) { std::cout << "Can't find LIBRARIES_TO_LINK = sfml" << std::endl;}
			result.replace(foundVariable + 29, 0, " $(SFML_LINK)");


			const std::string sfmlLink = "\n"
"#SFML\n"
"\n"
"#OS-DIFFERENCE#\n"
"#Windows\n"
"SFML_LINK_FOLDER 		        = SFML/lib/Windows\n"
"SFML_NEEDED_LIBRARIES_TO_LINK  =\n"
"SFML_STATIC_LIBRARIES_TO_LINK  = -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d\n"
"SFML_DYNAMIC_LIBRARIES_TO_LINK = -lsfml-graphics-d-2 -lsfml-window-d-2 -lsfml-system-d-2\n"
"#Linux\n"
"SFML_LINK_FOLDER 		        = SFML/lib/Linux\n"
"SFML_NEEDED_LIBRARIES_TO_LINK  = -lpthread -lGL -lX11 -lXrandr -lfreetype -lGLEW -lopenal -ludev\n"
"SFML_STATIC_LIBRARIES_TO_LINK  = -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d\n"
"SFML_DYNAMIC_LIBRARIES_TO_LINK = -lsfml-graphics-d -lsfml-window-d -lsfml-system-d\n"
"#OS-DIFFERENCE-END#\n"
"\n"
"SFML_LINK = -L $(EXTERNAL_LIBRARIES_FOLDER)/$(SFML_LINK_FOLDER) $(SFML_STATIC_LIBRARIES_TO_LINK) $(SFML_NEEDED_LIBRARIES_TO_LINK)\n"
"\n";

			//std::cout << result << std::endl;
			foundVariable = result.find("GENERATED_LIBRARIES_TO_INCLUDE =");
			if(foundVariable == std::string::npos) { std::cout << "Can't find LIBRARIES_TO_INCLUDE = sdfsdf" << std::endl;}
			result.replace(foundVariable, 0, sfmlLink);
		}
	}

	return result;
}



int main(int argc, char** argv) {

	//Check number of arguments

	if(argc < 3) { 

		std::cout << "ERROR: received " << argc - 1 << ", need at least of 2 arguments." << std::endl;  
		return -1;
	}

	//Check the folder (argument 1)

	std::filesystem::path newMakefileFolder{argv[1]};

	if(!std::filesystem::exists(newMakefileFolder)) { 

		std::cout << newMakefileFolder << " - doesn't exist, can't continue." << std::endl;
		return -1;
	}

	//Check the type of makeifle (argument 2)

	if(std::string{argv[2]} != "exe" && std::string{argv[2]} != "lib") {

		std::cout << "ERROR: The second argument must specifie if the makefile will be for a library or an executable. Must be choose with \"exe\" of \"lib\"" << std::endl;  
		return -1;
	}

	bool makefileForLibrary{true};

	if(std::string{argv[2]} == "exe") { makefileForLibrary = false; }

	//Get infos from the main makefile

	std::filesystem::path mainMakefilePath{"MakefileToCopy"};

	if(!std::filesystem::exists(mainMakefilePath)) {

		std::cout << "ERROR: Can't find the original makefile" << std::endl;
		return -1;
	}

	std::ifstream mainMakefile{mainMakefilePath};
	if(!mainMakefile) {

		std::cout << "ERROR: Can't open the original makefile" << std::endl;
		return -1;
	}

	std::map<std::string, std::string> textToCopy = getTextToCopy(mainMakefile);
	mainMakefile.close();

	//Check we found all infos
	if(textToCopy.find("All") == textToCopy.end()) { std::cout << "ERROR: Can't find ALL part." << std::endl; return -1; }
	if(textToCopy.find("lib") == textToCopy.end()) { std::cout << "ERROR: Can't find lib part." << std::endl; return -1; }
	if(textToCopy.find("exe") == textToCopy.end()) { std::cout << "ERROR: Can't find exe part." << std::endl; return -1; }

	std::string makefileText{""};

	//Put stuff for library/executable

	if(makefileForLibrary) { makefileText = addTextForLibrary(std::string{argv[1]}, textToCopy["All"], textToCopy["lib"]); }
	else                   { makefileText = addTextForExecutable(std::string{argv[1]}, textToCopy["All"], textToCopy["exe"]); }

	//Add asked libraries

	std::vector<std::string> askdedLibraries;
	for(int i{3}; i < argc; i++) { askdedLibraries.emplace_back(argv[i]); }

	makefileText = addLibraries(askdedLibraries, makefileText);

	//replace commands, depending of the OS

	makefileText = replaceForOS(makefileText);

	std::filesystem::path pathToNewMakefile{newMakefileFolder};
	pathToNewMakefile += std::filesystem::path{"/Makefile"};

	std::fstream newMakefile{pathToNewMakefile, std::ios::in | std::ios::out | std::ios::trunc};
	if(!newMakefile) {

		std::cout << "ERROR: Can't open the new makefile" << std::endl;
		return -1;
	}

	newMakefile << makefileText;

	newMakefile.close();

	std::cout << "New makefile for the ";
	if(makefileForLibrary) { std::cout << "library ";}
	else { std::cout << "executable "; }
	std::cout << std::string{argv[1]} <<" created at path: " << pathToNewMakefile << std::endl;

	return 0;
}