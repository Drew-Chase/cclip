#pragma once

#ifndef CCOMMANDLINEPARSER_OPTIONS_MANAGER_H
#define CCOMMANDLINEPARSER_OPTIONS_MANAGER_H

#include <vector>

using namespace std;

namespace ccliparser
{
    struct option
    {
        char *short_name;
        char *long_name;
        char *description;
        bool is_required;
        bool has_argument;
    };

    class options_manager
    {
    private:
        char *context;
        vector<option *> options;
    public:
        /**
         * Create a new options manager.
         * @param context the application context (e.g. "myapp" or "My App")
         */
        explicit options_manager(char *context);

        ~options_manager() = default;

        /**
         * Add an option to the options manager.
         * @param short_name the short name of the option (e.g. -h)
         * @param long_name the long name of the option (e.g. --help)
         * @param description the description of the option
         * @param is_required whether or not the option is required
         * @param has_argument whether or not the option has an argument
         * @return the option that was added
         */
        option *add_option(char *short_name, char *long_name, char *description, bool is_required, bool has_argument);

        /**
         * Parse the command line arguments.
         * @param argc the number of arguments
         * @param argv the arguments
         */
        void parse(int argc, char **argv);
        /**
         * Print the help message to stdout.
         */
        void print_help();

        /**
         * Get the help message.
         * @return the help message
         */
        char* get_help();
    };

} // ccliparser

#endif //CCOMMANDLINEPARSER_OPTIONS_MANAGER_H
