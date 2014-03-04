#ifndef LOG_HPP
#define LOG_HPP

#include <string>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/filesystem.hpp>
namespace logging {

class logger : boost::noncopyable
{
	public:
		logger(const std::string& path_and_filename)
		{
			of.open(path_and_filename, std::ios::out|std::ios::app);	
		}

		template<typename T>
		logger& operator << (const T& message)
		{
			if (of.is_open())
			{
				of << message;
			}
			return *this;
		}

		~logger()
		{
			of.clear();
			of.close();
		}

	private:
		std::ofstream of;
};


template <typename LOG, typename LOG_PTR>
LOG_PTR& single_logger(const std::string& filename = "file.log")
{
	static boost::shared_ptr<LOG> log_ptr = boost::make_shared<LOG>(filename);
	return log_ptr;
}

} // namespace log

inline char const* time_now_string()
{
	time_t t = std::time(0);
	tm* timeinfo = std::localtime(&t);
	static char str[200];
	std::strftime(str, 200, " %b %d %X ", timeinfo);
	return str;
}

#define INIT_LOGGER(filename) do { \
	logging::single_logger<logging::logger, boost::shared_ptr<logging::logger> >(filename); \
} while (0)

#define UNINIT_LOGGER() do { \
	logging::single_logger<logging::logger, boost::shared_ptr<logging::logger> >().reset(); \
} while (0)

#define _LOG_ (*(logging::single_logger<logging::logger, boost::shared_ptr<logging::logger> >()))

#define LOG_INFO(message) do { \
	_LOG_ << time_now_string() << "[INFO]:" << message << "\n"; \
}while (0)

#define LOG_ERROR(message) do { \
	_LOG_ << time_now_string() << "[ERROR]:" << message << "\n"; \
}while (0)

#define LOG_DEBUG(message) do { \
	_LOG_ << time_now_string() << "[DEBUG]:" << message << "\n"; \
}while (0)

#endif // LOG_HPP
