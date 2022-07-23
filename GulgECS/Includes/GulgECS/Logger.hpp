#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>

/**
 * @brief      Type of log entry
 */
enum class LogType{Error, Warning, Debug, Info};

/**
 * @brief      Logger for GulgEngine
 */
class Logger {

	public:

		/**
		 * @brief      Opens a file.
		 *
		 * @param[in]  path  The path
		 *
		 * @return     True if the file is succesfully opened, else false
		 */
		static bool openFile(const std::string &path);
		
		/**
		 * @brief      Closes the opened file.
		 */
		static void closeFile();


		/**
		 * @brief      Sets the maximum number of characters per line.
		 *
		 * @param[in]  nb    The new value
		 */
		static void setMaxCharacters(const uint32_t nb);


		/**
		 * @brief      Write an entry into the logs
		 *
		 * @param[in]  sentence  The sentence
		 * @param[in]  log       The log type
		 */
		static void write(const std::string &sentence, const LogType log);

		/**
		 * @brief      Enable logs
		 */
		static void activateLogs();


		/**
		 * @brief      Disable logs
		 */
		static void desactivateLogs();

	private:

		Logger();
		~Logger();

		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger operator=(const Logger&) = delete;

		static void writeBegin();
		static void writeEnd();
		static void writeDate();
		static void writeHour();
		static void writeNbEntry();
		static void writeType(const LogType type);
		static std::string centerText(const uint32_t nbSpaces, const std::string &textToCenter);
		static std::string leftText(const uint32_t nbSpaces, const std::string &textToLeft);
		static std::string rightText(const uint32_t nbSpaces, const std::string &textToRight);
		static std::vector<std::string> splitString(const std::string &str, const char delim);
		static std::vector<std::string> splitSentence(const std::string &sentence);

		static std::ofstream m_file;
		static bool m_isReady;
		static bool m_firstEntry;
		static uint32_t m_nbEntry;
		static uint32_t m_nbMaxCharacter;
		static bool m_logsAreActivated;
};


#endif