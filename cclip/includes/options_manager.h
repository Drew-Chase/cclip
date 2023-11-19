#pragma once

#ifndef CCOMMANDLINEPARSER_OPTIONS_MANAGER_H
#define CCOMMANDLINEPARSER_OPTIONS_MANAGER_H

#include <vector>

using namespace std;

namespace cclip
{
    struct option
    {
        /**
         * The short name of the option (e.g. -h) minus the dash (-).
         */
        const char *short_name;
        /**
         * The long name of the option (e.g. --help) minus the dashes (--).
         */
        const char *long_name;
        /**
         * The description of the option.
         */
        const char *description;
        /**
         * Whether or not the option is required.
         */
        bool is_required;
        /**
         * Whether or not the option has an argument.
         */
        bool has_argument;
        /**
         * The argument of the option.
         */
        char *argument;
    };

    class options_manager
    {
    private:
        const char *context;
        vector<option *> options;
        vector<option *> present_options;

        option *get_option_from_global_list(const char *name);

    public:
        /**
         * Create a new options manager.
         * @param context the application context (e.g. "myapp" or "My App")
         */
        explicit options_manager(const char *context);

        ~options_manager() = default;

        /**
         * Add an option to the options manager.
         * @param short_name the short name of the option (e.g. -h) minus the dash (-)
         * @param long_name the long name of the option (e.g. --help) minus the dashes (--)
         * @param description the description of the option
         * @param is_required whether or not the option is required
         * @param has_argument whether or not the option has an argument
         * @return the option that was added
         */
        option *add_option(const char *short_name, const char *long_name, const char *description, bool is_required, bool has_argument);

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
         * Get the help message. This is useful if you want to print the help message to a file or something.<br>
         * <b style="color: #f81c1c;"><i>Make sure to delete the returned string when you're done with it.</i></b>
         * @return the help message
         */
        const char *get_help();

        /**
         * Check if the option is present in the arguments.
         * @param name the short or long name of the option
         * @return whether or not the option is present
         */
        bool is_present(const char *name);

        /**
         * Get the option by name.
         * @param name the short or long name of the option
         * @return the option
         */
        option *get_option(const char *name);
    };

} // cclip

#endif //CCOMMANDLINEPARSER_OPTIONS_MANAGER_H
