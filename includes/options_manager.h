#pragma once

#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>
#include "option.h"

namespace cclip
{
    class options_manager
    {
    private:
        const char *context;
        std::vector<option *> options;
        std::vector<option *> present_options;
        std::vector<const char *> example_usages;
        const char *version;
        const char *description;
        std::string command_name;

        option *get_option_from_global_list(const std::string &name);

    public:
        /**
         * Constructor for options_manager class.
         *
         * @param context The context of the options manager.
         * @param description The description of the options manager.
         */
        explicit options_manager(const char *context, const char *description = nullptr);

        /**
         * Add an example usage to the options manager.
         * @param example_usage the example usage to add
         */
        void add_example_usage(const char *example_usage);

        /**
         * Set the version of the options manager.
         *
         * @param version the version string to set (e.g. "1.0.0")
         */
        void set_version(const char *version);

        /**
         * Get the version of the options manager.
         *
         * @return the version string
         */
        const char *get_version();

        /**
         * Get the version of the options manager.
         *
         * @return the version string
         */
        [[nodiscard]] char *get_version() const;

        /**
         * Print the version of the options manager to the standard output.
         */
        void print_version() const;

        /**
         * Print examples of how to use the options manager.
         */
        void print_examples() const;

        /**
         * Add an option to the options manager.
         * @param short_name the short name of the option (e.g. -h) minus the dash (-)
         * @param long_name the long name of the option (e.g. --help) minus the dashes (--)
         * @param description the description of the option
         * @param is_required whether or not the option is required
         * @param has_argument whether or not the option has an argument
         * @param executes_before_requires  Whether or not the option executes before it requires any other options. This means that if required options are not present but this is, the missing required options will be ignored. This is great for help and version options.
         * @return the option that was added
         */
        option *add_option(const char *short_name, const char *long_name, const char *description, bool is_required, bool has_argument, bool executes_before_requires = false);

        /**
         * Parse the command line arguments.
         * @param argc the number of arguments
         * @param argv the arguments
         */
        void parse(int argc, char **argv);

        /**
         * Print the help message to stdout.
         */
        void print_help(bool print_examples = true) const;

        /**
         * Get the help message. This is useful if you want to print the help message to a file or something.<br>
         * <b style="color: #f81c1c;"><i>Make sure to delete the returned string when you're done with it.</i></b>
         * @return the help message
         */
        [[nodiscard]] const char *get_help() const;

        /**
         * Check if the option is present in the arguments.
         * @param name the short or long name of the option
         * @return whether or not the option is present
         */
        [[nodiscard]] bool is_present(const std::string &name) const;

        /**
         * Get the option by name.
         * @param name the short or long name of the option
         * @return the option
         */
        option *get_option(const std::string &name);

        /**
         * Builds a PowerShell script snippet for autocomplete feature.
         *
         * This method constructs a PowerShell script snippet that can be used as a
         * completion script for cclip-example command. The script snippet registers
         * an argument completer for the command, which provides autocompletion for
         * command options.
         *
         * The constructed script snippet iterates over the list of options in the
         * options_manager object and adds their short names and long names to the
         * list of options. The short names are enclosed in single quotes followed by a
         * hyphen, and the long names are preceded by two hyphens. The list of options
         * is then joined as a string, with each option separated by a comma and a space.
         * The trailing comma and space are removed.
         *
         * Finally, the script block is created, which takes three parameters: the
         * commandName, the wordToComplete, and the cursorPosition. The script block
         * assigns the constructed list of options to a variable called $options.
         * It then filters the options using the wordToComplete and checks for a partial
         * match with the options in the list. For each matching option, a
         * System.Management.Automation.CompletionResult object is created with the
         * option as the display text, the option as the completion text, 'ParameterName'
         * as the completion type, and the option as the tooltip. The completion results
         * are output as the result of the script block.
         *
         * @return The PowerShell script snippet as a C-string.
         */
        char *build_autocomplete_ps1() const;
    };
}
