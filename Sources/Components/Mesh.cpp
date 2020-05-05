#include "Components/Mesh.hpp"

void Mesh::fillFinalArray() {

	m_finalArray.resize(m_vertices.size()*2);

	for(size_t i{0}; i < m_vertices.size(); i++) {

		m_finalArray[i*2] = m_vertices[i];
		m_finalArray[i*2 + 1] = m_colors[i];
	}
}


std::vector<std::string> splitString(const std::string &s, char separator) {

    std::vector<std::string> result;
    std::stringstream ss{s};
    std::string currentWord;

    while(std::getline(ss, currentWord, separator)) { result.emplace_back(currentWord); }

    return result;
}


Mesh loadFromFile(const std::string &path) {

	Mesh newMesh;
	std::ifstream file{path};
	if(!file) { throw std::runtime_error("Can't open file and load mesh: \"" + path + "\"."); }

	std::string currentLine;
	std::vector<std::string> splitedLine;
	uint32_t currentLineNumber{0};

	while(std::getline(file, currentLine)) {

		splitedLine = splitString(currentLine, ' ');

		if(splitedLine.size() == 0) { /*Nothing to do, commentary*/}
		else if(splitedLine[0] == "v") {

			if(splitedLine.size() != 4) { Logger::write("Wrong number of datas at line " + std::to_string(currentLineNumber) + " in file: \"" + path + "\"." , LogType::Warning);}
			else { newMesh.m_vertices.emplace_back(glm::vec3{std::stof(splitedLine[1]), std::stof(splitedLine[2]), std::stof(splitedLine[3])}); }
		}

		else if(splitedLine[0] == "vt") {}
		else if(splitedLine[0] == "vn") {}
		else if(splitedLine[0] == "vc") { //Doesnt exist, just color for tests

			if(splitedLine.size() != 4) { Logger::write("Wrong number of datas at line " + std::to_string(currentLineNumber) + " in file: \"" + path + "\"." , LogType::Warning);}
			else { newMesh.m_colors.emplace_back(glm::vec3{std::stof(splitedLine[1]), std::stof(splitedLine[2]), std::stof(splitedLine[3])}); }
		}

		else if(splitedLine[0] == "f") {

			if(splitedLine.size() != 4) { Logger::write("Wrong number of datas at line " + std::to_string(currentLineNumber) + " in file: \"" + path + "\"." , LogType::Warning);}
			else { 

				newMesh.m_indices.emplace_back(std::stoi(splitedLine[1]));
				newMesh.m_indices.emplace_back(std::stoi(splitedLine[2]));
				newMesh.m_indices.emplace_back(std::stoi(splitedLine[3]));
			}
		}

		else if(splitedLine[0] == "o") {} // Not supported in a this Mesh class
		else if(splitedLine[0] == "g") {} // Not implemented
		else if(splitedLine[0] == "usemtl") {} // Not implemented
		else if(splitedLine[0] == "mtllib") {} // Not implemented
		else if(splitedLine[0] == "#") { /*Nothing to do, commentary*/}
		
		else { Logger::write("Unknown data at line " + std::to_string(currentLineNumber) + " in file: \"" + path + "\"." , LogType::Warning); }

		currentLineNumber++;
	}

	file.close();

	newMesh.fillFinalArray();

	return newMesh;
}