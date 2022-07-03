#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cstring>

std::vector<std::string> splitString(const std::string toSplit, const char delimiter) {

	std::vector<std::string> splitResult;
	std::string currentPart;

	for(char currentChar: toSplit) {

		if(currentChar == delimiter) { 

			splitResult.emplace_back(currentPart); 
			currentPart = "";
		}

		else { currentPart += currentChar; }
	}

	if(currentPart != "") { splitResult.emplace_back(currentPart); }

	return splitResult;
}

bool isCommentaryLine(const std::vector<std::string> splittedLine) {

	for(std::string currentPart: splittedLine) {

		if(currentPart == "/*" || currentPart == "//" || currentPart == "///") { return true; }
	}

	return false;
}

bool isEnumLine(const std::vector<std::string> splittedLine) {

	for(std::string currentPart: splittedLine) {

		if(currentPart == "enum") { return true; }
	}

	return false;
}

bool isForwardDeclarationLine(const std::vector<std::string> splittedLine) {

	for(std::string currentPart: splittedLine) {

		if(currentPart.find(";") != std::string::npos) { return true; }
	}

	return false;
}

bool containtInheritance(const std::vector<std::string> splittedLine) {

	for(std::string currentPart: splittedLine) {

		if(currentPart.find(":") != std::string::npos) { return true; }
	}

	return false;
}

void printLine(const std::vector<std::string> splittedLine) {

	for(std::string currentPart: splittedLine) {

		std::cout << currentPart << " ";
	}

	std::cout << std::endl;
}

void removeKeyword(std::vector<std::string> &splittedLine, const std::string toDelete) {

	for(size_t i{0}; i < splittedLine.size(); i++) {

		if(splittedLine[i] == toDelete) { 

			splittedLine.erase(splittedLine.begin() + i); 
			i = 0;
		}
	}
}

void splitEndCharacterFromString(std::vector<std::string> &splittedLine, const char toSplit) {

	for(size_t i{0}; i < splittedLine.size(); i++) {

		if(splittedLine[i].back() == toSplit) {

			splittedLine[i].pop_back();
			splittedLine.insert(splittedLine.begin() + i + 1, std::string{toSplit});
			i++;
		}
	}
}

std::map<std::string, std::vector<std::string>> searchInFile(const std::filesystem::path currentFilePath) {

	std::map<std::string, std::vector<std::string>> searchResult;

	std::ifstream currentFile{currentFilePath};
	if(!currentFile) { 

		std::cout << "ERROR: can't open file " << currentFilePath << ": " << std::strerror(errno) << std::endl;
		return searchResult; 
	}

	std::string currentLine;

	std::vector<std::string> linesToTreat;

	while(std::getline(currentFile, currentLine, '\n')) {

		if(currentLine.find("class") != std::string::npos) { linesToTreat.emplace_back(currentLine); }
	}

	currentFile.close();

	for(std::string currentLineToTreat: linesToTreat) {

		std::vector<std::string> splittedCurrentLine = splitString(currentLineToTreat, ' ');

		if(isCommentaryLine(splittedCurrentLine)) { continue; }
		if(isEnumLine(splittedCurrentLine)) { continue; }
		if(isForwardDeclarationLine(splittedCurrentLine)) { continue; }
		if(!containtInheritance(splittedCurrentLine)) { continue; }

		splitEndCharacterFromString(splittedCurrentLine, ',');
		splitEndCharacterFromString(splittedCurrentLine, ':');

		removeKeyword(splittedCurrentLine, "public");
		removeKeyword(splittedCurrentLine, "private");
		removeKeyword(splittedCurrentLine, "protected");
		removeKeyword(splittedCurrentLine, "class");
		removeKeyword(splittedCurrentLine, "{");
		removeKeyword(splittedCurrentLine, ",");
		removeKeyword(splittedCurrentLine, "");
		removeKeyword(splittedCurrentLine, " ");
		removeKeyword(splittedCurrentLine, "	");
		removeKeyword(splittedCurrentLine, "\t");

		size_t inheritanceSeparatorIndex{0};
		bool foundInheritanceSeparator{false};

		for(size_t i{0}; i < splittedCurrentLine.size(); i++) {

			if(splittedCurrentLine[i] == ":") {

				inheritanceSeparatorIndex = i;
				foundInheritanceSeparator = true;
			}
		}

		if(!foundInheritanceSeparator || inheritanceSeparatorIndex == 0 || inheritanceSeparatorIndex == splittedCurrentLine.size() - 1) { continue; }

		if(!searchResult.contains(splittedCurrentLine[inheritanceSeparatorIndex - 1])) {

			searchResult.insert(std::make_pair(splittedCurrentLine[inheritanceSeparatorIndex - 1], std::vector<std::string>()));

			for(size_t i{inheritanceSeparatorIndex + 1}; i < splittedCurrentLine.size(); i++) { 

				searchResult[splittedCurrentLine[inheritanceSeparatorIndex - 1]].emplace_back(splittedCurrentLine[i]);
			}
		}
	}

	return searchResult;
}








bool inheritsFromAbstractComponent(const std::vector<std::string> parentsOfCurrentClass, const std::map<std::string, std::vector<std::string>> classesAndParents) {

	for(std::string currentParent: parentsOfCurrentClass) {

		if(currentParent == "AbstractComponent") { return true; }
		else if(classesAndParents.contains(currentParent) && inheritsFromAbstractComponent(classesAndParents.at(currentParent), classesAndParents)) { return true; }
	}

	return false;
}




void createGeneratedComponentTypesFile(const std::filesystem::path &folderToWriteResult,const std::vector<std::string> &classToAddInEnum) {

	std::filesystem::path pathToFile{folderToWriteResult};
	pathToFile += std::filesystem::path{"ComponentTypes.hpp"};

	std::ofstream currentFile{pathToFile};
	if(!currentFile) { 

		std::cout << "ERROR: can't open file " << pathToFile << ": " << std::strerror(errno) << std::endl;
		return;
	}

	currentFile << "#ifndef COMPONENT_TYPES_HPP" << std::endl;
	currentFile << "#define COMPONENT_TYPES_HPP" << std::endl;
	currentFile << std::endl;
	currentFile << "//This file was auto_generated by the ListOfComponents program. Please, don't modify it." << std::endl;
	currentFile << std::endl;
	currentFile << "namespace Gg {" << std::endl;
	currentFile << std::endl;
	currentFile << "\tnamespace Component {" << std::endl;
	currentFile << std::endl;
	currentFile << "\t\tconst uint32_t MaxComponentType = " << classToAddInEnum.size() << ";" << std::endl;
	currentFile << std::endl;
	currentFile << "\t\tenum class Type {" << std::endl;
	currentFile << std::endl;

	for(size_t i{0}; i < classToAddInEnum.size(); i++) {

		currentFile << "\t\t\t" << classToAddInEnum[i];
		if(i != classToAddInEnum.size() - 1) { currentFile << ","; }
		currentFile << std::endl;
	}

	currentFile << "\t\t};" << std::endl;
	currentFile << "\t}" << std::endl;
	currentFile << "}" << std::endl;
	currentFile << std::endl;
	currentFile << "#endif" << std::endl;

	std::cout << "Types successfully writed in " << pathToFile << std::endl;

	currentFile.close();
}

void insertAutoGeneratedInitOfComponentSignatureKeeper(const std::filesystem::path &fileToInsert,const std::vector<std::string> &classToAddInEnum) {

	std::ifstream currentFileToCopy{fileToInsert};
	if(!currentFileToCopy) { 

		std::cout << "ERROR: can't open file " << fileToInsert << ": " << std::strerror(errno) << std::endl;
		return;
	}

	std::vector<std::string> beginToCopy, endToCopy;
	bool foundBeginInsert{false}, foundEndInsert{false};

	std::string currentLine;
	while(std::getline(currentFileToCopy, currentLine)) {

		if(!foundBeginInsert) { beginToCopy.emplace_back(currentLine); }
		if(currentLine == "//BEGIN - AUTOGENERATED") { foundBeginInsert = true; }
		if(currentLine == "//END - AUTOGENERATED") { foundEndInsert = true; }
		if(foundEndInsert) { endToCopy.emplace_back(currentLine); }
	}

	currentFileToCopy.close();


	if(!foundBeginInsert || !foundEndInsert) {

		std::cout << "ERROR: problem with insert zone in file " << fileToInsert << std::endl;
		if(!foundBeginInsert) { std::cout << "Cant find the begin of the insert zone." << std::endl; }
		if(!foundEndInsert) { std::cout << "Cant find the end of the insert zone." << std::endl; }
		return;
	}


	std::ofstream currentFileToRewrite{fileToInsert};
	if(!currentFileToRewrite) { 

		std::cout << "ERROR: can't open file " << fileToInsert << ": " << std::strerror(errno) << std::endl;
		return;
	}

	for(std::string currentString: beginToCopy) { currentFileToRewrite << currentString << std::endl; }

	currentFileToRewrite << "void ComponentSignatureKeeper::Init() {" << std::endl;
	currentFileToRewrite << std::endl;

	for(size_t i{0}; i < classToAddInEnum.size(); i++) {

		currentFileToRewrite << "\tm_signatures.insert(std::make_pair(Component::Type::" << classToAddInEnum[i];
		currentFileToRewrite << ", Signature{std::array<bool, " << classToAddInEnum.size() << "> { ";

		for(unsigned int j{0}; j < classToAddInEnum.size(); j++) {

			if(i == j) { currentFileToRewrite << "1"; }
			else { currentFileToRewrite << "0"; }

			if(j != classToAddInEnum.size() - 1) { currentFileToRewrite << ", "; }
		}

		currentFileToRewrite << " }}));" << std::endl;
	}

	currentFileToRewrite << "}" << std::endl;

	for(std::string currentString: endToCopy) { currentFileToRewrite << currentString << std::endl; }

	currentFileToRewrite.close();
}




int main(int argc, char** argv) {

	//The first argument is the name of the program
	if(argc != 4) { 

		std::cout << "ERROR: received " << argc - 1 << " instead of 3 arguments." << std::endl;  
		return -1;
	}

	std::filesystem::path folderWhereStartSearch{argv[1]};
	std::filesystem::path folderToWriteResult{argv[2]};
	std::filesystem::path fileToInsertComponents{argv[3]};

	if(!std::filesystem::exists(folderWhereStartSearch)) { 

		std::cout << folderWhereStartSearch << " - doesn't exist, can't continue." << std::endl;
		return -1;
	}

	if(!std::filesystem::exists(folderToWriteResult)) { 

		std::cout << folderToWriteResult << " - doesn't exist, can't continue." << std::endl;
		return -1;
	}

	if(!std::filesystem::exists(fileToInsertComponents)) { 

		std::cout << fileToInsertComponents << " - doesn't exist, can't continue." << std::endl;
		return -1;
	}


	std::vector<std::string> pathToIgnore{};
	std::vector<std::filesystem::directory_entry> filesToSearch;

	for(const std::filesystem::directory_entry &currentDir: std::filesystem::recursive_directory_iterator(folderWhereStartSearch)) {

		if(currentDir.path().extension() == ".hpp") { filesToSearch.emplace_back(currentDir); }
	}

	std::map<std::string, std::vector<std::string>> classesAndParents;

	for(const std::filesystem::directory_entry &currentDir: filesToSearch) {

		std::map<std::string, std::vector<std::string>> justFind = searchInFile(currentDir.path());

		for(std::map<std::string, std::vector<std::string>>::iterator it = justFind.begin(); it != justFind.end(); it++) {

			if(classesAndParents.find(it->first) == classesAndParents.end()) { classesAndParents.insert(std::make_pair(it->first, it->second)); }
		}

	}

	std::vector<std::string> classToAddInEnum;

	for(std::map<std::string, std::vector<std::string>>::iterator it = classesAndParents.begin(); it != classesAndParents.end(); it++) {

		if(inheritsFromAbstractComponent(it->second, classesAndParents)) { classToAddInEnum.emplace_back(it->first); }
	}

	for(std::string foundComponent: classToAddInEnum) {

		std::cout << "Found component: " << foundComponent << std::endl;
	}

	std::sort(classToAddInEnum.begin(), classToAddInEnum.end(), [](const std::string a, const std::string b) { return a < b; } );

	createGeneratedComponentTypesFile(folderToWriteResult, classToAddInEnum);
	insertAutoGeneratedInitOfComponentSignatureKeeper(fileToInsertComponents, classToAddInEnum);
}