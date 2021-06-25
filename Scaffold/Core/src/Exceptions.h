#pragma once

#include <exception>
#include <string>


namespace scaffold::exceptions
{
	class BaseException : std::exception
	{
	protected:
		std::string file;
		unsigned int line;

	public:
		BaseException(const char* _file, unsigned int _line)
		{
			line = _line;

			int lastSlash = 0;
			int i = 0;
			char testChar = '0';
			while (testChar != '\0')
			{
				testChar = _file[i++];
				if (testChar == '\\')
					lastSlash = i;
			}
			file = _file + lastSlash;
		}

		std::string File() const { return file; }
		unsigned int Line() const { return line; }

		virtual std::string ExceptionType() const { return ""; }
		virtual std::string Message() const { return ""; }
	};

	class GenericException : public BaseException
	{
	protected:
		std::string message;
		std::string type;

	public:
		GenericException(std::string _message, const char* _file, unsigned int _line, std::string _type = "Generic") : BaseException(_file, _line)
		{
			message = _message;
			type = _type;
		}

		std::string ExceptionType() const override
		{
			return type;
		}

		std::string Message() const override
		{
			return message;
		}
	};
}
