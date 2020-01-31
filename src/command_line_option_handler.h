#ifndef COMMAND_LINE_OPTION_HANDLER_H
#define COMMAND_LINE_OPTION_HANDLER_H


class command_line_option_handler
{
public:
	command_line_option_handler(int argc, char **argv);
	void handle_command_line(int argc, char **argv);

};

#endif // COMMAND_LINE_OPTION_HANDLER_H
