#include "Logger.hpp"

std::ofstream Logger::m_file;
bool Logger::m_isReady{false};
bool Logger::m_firstEntry{false};
uint32_t Logger::m_nbEntry{0};
uint32_t Logger::m_nbMaxCharacter{100};

bool Logger::openFile(const std::string &path) {

	if(m_file) { closeFile(); }

	m_file.open(path);

	if(m_file) { 

		m_isReady = true; 
		m_firstEntry = true;
	}

	return m_isReady;
}

void Logger::closeFile() {

	writeEnd();
	m_file.close();
	m_isReady = false;
}


void Logger::setMaxCharacters(const uint32_t nb) { m_nbMaxCharacter = nb; }


void Logger::write(const std::string &sentence, const LogType type) { 

	if(m_isReady) {

		if(m_firstEntry) {

			writeBegin();
			m_firstEntry = false;
		}

		std::vector<std::string> splitedSentence{splitSentence(sentence)};

		m_file << "┣━━━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━╋";

		//+2 for spaces at begin and end
		for(uint32_t i{0}; i < m_nbMaxCharacter+ 2; i++) { m_file << "━"; }
		m_file << "┫" << std::endl;

		writeNbEntry();
		writeDate();
		writeHour();
		writeType(type);

		for(size_t i{0}; i < splitedSentence.size(); i++) {

			if(i == 0) { m_file << " " << leftText(m_nbMaxCharacter, splitedSentence[i]) << " ┃" << std::endl; }
			else { m_file << "┃            ┃            ┃          ┃         ┃ " << leftText(m_nbMaxCharacter, splitedSentence[i]) << " ┃" << std::endl; }
		}

		m_file.flush();
		m_nbEntry++;
	} 
}


void Logger::writeBegin() {

	if(m_isReady) { 

		m_file << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

		for(uint32_t i{0}; i < m_nbMaxCharacter+ 2; i++) { m_file << "━"; }
		m_file << "┓" << std::endl;


		m_file << "┃" << centerText(49 + m_nbMaxCharacter, "Begin of logs") << "┃" << std::endl;
		m_file << "┣━━━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━┳";

		for(uint32_t i{0}; i < m_nbMaxCharacter+ 2; i++) { m_file << "━"; }
		m_file << "┫" << std::endl;

		m_file << "┃  Entry nb  ┃    Date    ┃   Hour   ┃  Type   ┃";

		for(uint32_t i{0}; i < m_nbMaxCharacter+ 2; i++) { m_file << " "; }
		m_file << "┃" << std::endl;
	} 
}

void Logger::writeEnd() {

	if(m_isReady) { 

		if(m_firstEntry) {//No entry in file

			m_file << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << std::endl;
			m_file << "┃                   No entry                   ┃" << std::endl;
			m_file << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << std::endl;
		}

		else {

			m_file << "┣━━━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━┻";

			for(uint32_t i{0}; i < m_nbMaxCharacter+ 2; i++) { m_file << "━"; }
			m_file << "┫" << std::endl;

			m_file << "┃" << centerText(49 + m_nbMaxCharacter, "End of logs") << "┃" << std::endl;
			m_file << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━";

			for(uint32_t i{0}; i < m_nbMaxCharacter+ 2; i++) { m_file << "━"; }
			m_file << "┛" << std::endl;
		}
	}
}


void Logger::writeNbEntry() {

	//10 = number of digits in 2^32
	if(m_isReady) { m_file << "┃" << centerText(12, std::to_string(m_nbEntry)) << "┃ "; }
}

void Logger::writeDate() {

	time_t rawtime;
	struct tm *timeinfo;
	char buffer[11];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 11, "%d/%m/%Y", timeinfo);

	m_file << buffer << " ┃ ";
}

void Logger::writeHour() {

	time_t rawtime;
	struct tm *timeinfo;
	char buffer[9];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 9, "%T", timeinfo);
 
	m_file << buffer << " ┃";
}

void Logger::writeType(const LogType type) {

	switch(type) {

		case LogType::Error:
			m_file << centerText(9, "ERROR");
			break;

		case LogType::Warning:
			m_file << centerText(9, "WARNING");
			break;

		case LogType::Debug:
			m_file << centerText(9, "DEBUG");
			break;

		case LogType::Info:
			m_file << centerText(9, "INFO");
			break;
	}

	m_file << "┃";
}


std::string Logger::centerText(const uint32_t nbSpaces, const std::string &textToCenter) {

	if(textToCenter.size() >= nbSpaces) { return textToCenter; }

	const uint32_t nbSpacesToSplit{nbSpaces - static_cast<uint32_t>(textToCenter.size())};
	const uint32_t beforeTextSpaceNb{nbSpacesToSplit/2};
	const uint32_t afterTextSpaceNb{nbSpacesToSplit - beforeTextSpaceNb};

	std::string result;
	result.resize(nbSpaces);

	for(uint32_t i{0}; i < beforeTextSpaceNb; i++) { result[i] = ' '; }
	for(size_t i{0}; i < textToCenter.size(); i++) { result[beforeTextSpaceNb + i] = textToCenter[i]; }
	for(uint32_t i{0}; i < afterTextSpaceNb; i++) { result[beforeTextSpaceNb + textToCenter.size() + i] = ' '; }
	return result;
}

std::string Logger::leftText(const uint32_t nbSpaces, const std::string &textToLeft) {

	if(textToLeft.size() >= nbSpaces) { return textToLeft; }

	const uint32_t afterTextSpaceNb{nbSpaces - static_cast<uint32_t>(textToLeft.size())};

	std::string result;
	result.resize(nbSpaces);

	for(size_t i{0}; i < textToLeft.size(); i++) { result[i] = textToLeft[i]; }
	for(uint32_t i{0}; i < afterTextSpaceNb; i++) { result[textToLeft.size() + i] = ' '; }
	return result;
}

std::string Logger::rightText(const uint32_t nbSpaces, const std::string &textToRight) {

	if(textToRight.size() >= nbSpaces) { return textToRight; }

	const uint32_t beforeTextSpaceNb{nbSpaces - static_cast<uint32_t>(textToRight.size())};

	std::string result;
	result.resize(nbSpaces);

	for(uint32_t i{0}; i < beforeTextSpaceNb; i++) { result[i] = ' '; }
	for(size_t i{0}; i < textToRight.size(); i++) { result[beforeTextSpaceNb + i] = textToRight[i]; }
	return result;
}

std::vector<std::string> Logger::splitString(const std::string &str, const char delim) {

    std::stringstream ss{str};
    std::string currentString;
    std::vector<std::string> result;

    while(std::getline(ss, currentString, delim)) { result.emplace_back(currentString); }

    return result;
}

std::vector<std::string> Logger::splitSentence(const std::string &sentence) {

	//Split by \n

	std::vector<std::string> firstSplit{splitString(sentence, '\n')};

	//Split by space

	std::vector<std::string> secondSplit, splitBySpace;
	std::string currentLine;

	for(const std::string &currentSentence: firstSplit) {

		splitBySpace = splitString(currentSentence, ' ');
		currentLine = "";

		for(size_t i{0}; i < splitBySpace.size(); i++) {

			if(currentLine.size() + splitBySpace[i].size() + 1 <= m_nbMaxCharacter) { currentLine += splitBySpace[i] + ' '; } //+1 for space between words
			else {

				secondSplit.emplace_back(currentLine);
				currentLine = splitBySpace[i];
			}

			if(currentLine.size() == m_nbMaxCharacter) {

				secondSplit.emplace_back(currentLine);
				currentLine = "";
			}
		}

		if(!currentLine.empty()) { secondSplit.emplace_back(currentLine); }
	}

	return secondSplit;
}