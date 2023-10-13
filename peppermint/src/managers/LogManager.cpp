#include <peppermint/managers/LogManager.h>

using namespace peppermint::managers;
using namespace std;

void LogManager::debug(string message) {
	if (LogManager::enabledLevels::debug) {
		time_t time = std::time(0);
		tm localbuf = { 0 };
		localtime_s(&localbuf, &time);
		cout << colourToEscape(COLOURS::BRIGHT_BLACK) << "[DEBUG]    " << put_time(&localbuf, "%Y/%m/%d %T") << " \t> " << message.c_str() << colourToEscape(COLOURS::RESET) << endl;
	}
}

void LogManager::info(string message) {
	if (LogManager::enabledLevels::info) {
		time_t time = std::time(0);
		tm localbuf = { 0 };
		localtime_s(&localbuf, &time);
		cout << colourToEscape(COLOURS::BRIGHT_BLUE) << "[INFO]     " << put_time(&localbuf, "%Y/%m/%d %T") << " \t> " << message.c_str() << colourToEscape(COLOURS::RESET) << endl;
	}
}

void LogManager::warn(string message) {
	if (LogManager::enabledLevels::warn) {
		time_t time = std::time(0);
		tm localbuf = { 0 };
		localtime_s(&localbuf, &time);
		cout << colourToEscape(COLOURS::YELLOW) << "[WARN]     " << put_time(&localbuf, "%Y/%m/%d %T") << " \t> " << message.c_str() << colourToEscape(COLOURS::RESET) << endl;
	}
}

void LogManager::error(string message) {
	if (LogManager::enabledLevels::error) {
		time_t time = std::time(0);
		tm localbuf = { 0 };
		localtime_s(&localbuf, &time);
		cout << colourToEscape(COLOURS::RED) << "[ERROR]    " << put_time(&localbuf, "%Y/%m/%d %T") << " \t> " << message.c_str() << colourToEscape(COLOURS::RESET) << endl;
	}
}

void LogManager::critical(string message) {
	if (LogManager::enabledLevels::error) {
		time_t time = std::time(0);
		tm localbuf = { 0 };
		localtime_s(&localbuf, &time);
		cout << colourToEscape(COLOURS::BRIGHT_RED) << "[CRITICAL] " << put_time(&localbuf, "%Y/%m/%d %T") << " \t> " << message.c_str() << colourToEscape(COLOURS::RESET) << endl;
	}
}

const char* LogManager::colourToEscape(COLOURS colour) {
	switch (colour) {
	case RESET:
		return "\033[0m";
	case BLACK:
		return "\x1B[30m";
	case RED:
		return "\x1B[31m";
	case GREEN:
		return "\x1B[32m";
	case YELLOW:
		return "\x1B[33m";
	case BLUE:
		return "\x1B[34m";
	case MAGENTA:
		return "\x1B[35m";
	case CYAN:
		return "\x1B[36m";
	case WHITE:
		return "\x1B[37m";
	case BRIGHT_BLACK:
		return "\x1B[90m";
	case BRIGHT_RED:
		return "\x1B[91m";
	case BRIGHT_GREEN:
		return "\x1B[92m";
	case BRIGHT_YELLOW:
		return "\x1B[93m";
	case BRIGHT_BLUE:
		return "\x1B[94m";
	case BRIGHT_MAGENTA:
		return "\x1B[95m";
	case BRIGHT_CYAN:
		return "\x1B[96m";
	case BRIGHT_WHITE:
		return "\x1B[97m";
	default:
		return "\033[0m";
	}
}