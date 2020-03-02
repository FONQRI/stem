#ifndef COMMAND_LINE_OPTION_HANDLER_H
#define COMMAND_LINE_OPTION_HANDLER_H

/**
 * @brief The command_line_option_handler class: parse input args and init diffrente modules
 */
class command_line_option_handler
{
public:
	command_line_option_handler(int argc, char **argv);

	/**
	 * @brief handle_command_line : parse command line and init modules
	 * @param argc : args number
	 * @param argv : arg strings
	 */
	void handle_command_line(int argc, char **argv);
};

#endif // COMMAND_LINE_OPTION_HANDLER_H
