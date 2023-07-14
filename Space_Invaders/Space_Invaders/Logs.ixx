export module Logs;
import <string>;
import <fstream>;
import <chrono>;
import <filesystem>;

export class Logs
{
	const std::string log_file_name = "logs.txt";

	Logs() {
		if (std::filesystem::exists(log_file_name)) {
			std::ofstream clear_log_file;
			clear_log_file.open(log_file_name, std::ios::trunc);
			clear_log_file.close();
		}
	};

public:
	Logs(const Logs& log) = delete;
	Logs& operator=(const Logs& log) = delete;

	auto operator()(const std::string& message, const std::string& function) const {
		log(message, function);
	}

	static Logs& get_log() {
		static Logs log;
		return log;
	}

	void log(const std::string& message, const std::string& function) const {
		std::ofstream log_file;
		log_file.open(log_file_name, std::ofstream::app);
		const std::string separator = "===================================";
		const auto date_and_time = std::chrono::zoned_time{ std::chrono::current_zone(), std::chrono::system_clock::now() };
		log_file << separator << std::endl << date_and_time << std::endl << "Message:	" << message << std::endl
			<< "Function:	" << function << std::endl;
		log_file.close();
	}
};