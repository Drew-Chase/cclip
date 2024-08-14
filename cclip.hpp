/**
    This file is part of the CClip project, a simple and convenient library for handling command line arguments in C++ applications. 
    The primary purpose of CClip is to make the parsing of command-line options easier, providing a structured and consistent way to manage command-line inputs. 
    It enables developers to define specific command-line options and arguments that their applications can accept. Once these options are defined, CClip allows them to be easily parsed and retrieved when the application is run, reducing the complexity associated with command-line input handling. 
    The parsing functionality provided by CClip is intuitive and efficient, making it an ideal choice for any C++ application that requires command-line input functionality.
    For more information please visit our github page at https://github.com/Drew-Chase/cclip
*/

#pragma once
#define CCLIP_VERSION "0.0.9"


#ifndef OPTION_H
#define OPTION_H

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
         * Whether or not the option executes before it requires any other options.
         * This means that if required options are not present but this is, the missing required options will be ignored.
         * This is great for help and version options.
         */
        bool executes_before_requires;
        /**
         * The argument of the option.
         */
        char *argument;
    };
}
#endif


#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>


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


#include <filesystem>
#include <iostream>

inline cclip::options_manager::options_manager(const char *context, const char *description)
{
    this->context = context;
    this->description = description;
    this->version = nullptr;
}

inline void cclip::options_manager::add_example_usage(const char *example_usage)
{
    this->example_usages.push_back(example_usage);
}

inline void cclip::options_manager::set_version(const char *version)
{
    this->version = version;
}

inline const char *cclip::options_manager::get_version()
{
    return this->version;
}

inline void cclip::options_manager::print_version() const
{
    if (this->version != nullptr)
    {
        std::cout <<
#ifdef ANSIConsoleColors
                    colors::ConsoleColors::GetColorCode(colors::ColorCodes::Green) <<
#endif
                this->context << " " <<
#ifdef ANSIConsoleColors
                    colors::ConsoleColors::GetColorCode(colors::ColorCodes::Yellow) <<
#endif
                this->version <<
#ifdef ANSIConsoleColors
                    colors::ConsoleColors::GetColorCode(colors::ColorCodes::Default) <<
#endif
                std::endl;
    }
}

inline void cclip::options_manager::print_examples() const
{
    std::cout <<
#ifdef ANSIConsoleColors
                colors::ConsoleColors::GetColorCode(colors::ColorCodes::Yellow) <<
#endif
            "Example Usages:" <<
#ifdef ANSIConsoleColors
                colors::ConsoleColors::GetColorCode(colors::ColorCodes::Blue) <<
#endif
            std::endl;
    for (const auto &example_usage: this->example_usages)
    {
        std::cout <<
                example_usage <<
                std::endl;
    }

#ifdef ANSIConsoleColors
        colors::ConsoleColors::ResetConsoleColor();
#endif
}

inline cclip::option *cclip::options_manager::add_option(const char *short_name, const char *long_name, const char *description, const bool is_required, const bool has_argument, const bool executes_before_requires)
{
    auto *opt = new option{short_name, long_name, description, is_required, has_argument, executes_before_requires, nullptr};
    this->options.push_back(opt);
    return opt;
}

inline void cclip::options_manager::parse(const int argc, char **argv)
{
    this->command_name = std::filesystem::path(argv[0]).stem().string(); // Get the executable name
    for (int i = 0; i < argc; ++i)
    {
        if (const char *arg = argv[i]; arg[0] == '-')
        {
            if (arg[1] == '-')
            {
                // long option
                const char *name = arg + 2;
                if (option *opt = this->get_option_from_global_list(name); opt == nullptr)
                {
#ifdef ANSIConsoleColors
                        colors::ConsoleColors::SetForegroundColor(colors::ColorCodes::Red);
#endif
                    std::cerr << "Unknown option: --" << name << std::endl;
#ifdef ANSIConsoleColors
                        colors::ConsoleColors::ResetConsoleColor();
#endif
                    this->print_help();
                    exit(1);
                } else
                {
                    if (opt->has_argument)
                    {
                        if (i + 1 >= argc)
                        {
#ifdef ANSIConsoleColors
                                colors::ConsoleColors::SetForegroundColor(colors::ColorCodes::Red);
#endif
                            std::cerr << "Missing argument for option: " << name << std::endl;

#ifdef ANSIConsoleColors
                                colors::ConsoleColors::ResetConsoleColor();
#endif
                            this->print_help();
                            exit(1);
                        }
                        opt->argument = argv[i + 1];
                    }
                    this->present_options.push_back(opt);
                }
            } else
            {
                // short option
                const char *name = arg + 1;
                if (option *opt = this->get_option_from_global_list(name); opt == nullptr)
                {
                    std::cerr << "Unknown option: -" << name << std::endl;
                    this->print_help();
                    exit(1);
                } else
                {
                    if (opt->has_argument)
                    {
                        if (i + 1 >= argc)
                        {
                            std::cerr << "Missing argument for option: " << name << std::endl;
                            this->print_help();
                            exit(1);
                        }
                        opt->argument = argv[i + 1];
                    }
                    this->present_options.push_back(opt);
                }
            }
        }
    }
    bool ignore_missing = false;
    for (const auto &option: this->options)
    {
        if (option->executes_before_requires && this->is_present(option->short_name))
        {
            ignore_missing = true;
            break;
        }
    }
    if (!ignore_missing)
    {
        bool missing = false;
        for (const auto &option: this->options)
        {
            if (option->is_required && !this->is_present(option->short_name))
            {
#ifdef ANSIConsoleColors
                colors::ConsoleColors::SetForegroundColor(colors::ColorCodes::Red);
#endif
                std::cerr << "Missing required option: -" << option->short_name << " or --" << option->long_name << std::endl;
#ifdef ANSIConsoleColors
                colors::ConsoleColors::ResetConsoleColor();
#endif
                missing = true;
            }
        }
        if (missing)
        {
            this->print_help();
            exit(1);
        }
    }
}

inline void cclip::options_manager::print_help(const bool print_examples) const
{
    const char *help = this->get_help();
    if (print_examples)
    {
        this->print_examples();
    }
    std::cout << help << std::endl;
    delete(help); // Deletes the memory allocated by get_help()
}


inline const char *cclip::options_manager::get_help() const
{
    std::stringstream buf;
    buf <<
#ifdef ANSIConsoleColors
                colors::ConsoleColors::GetColorCode(colors::ColorCodes::Magenta) <<
#endif
            this->context << " Help:\n";
    if (this->description != nullptr)
    {
        buf <<
#ifdef ANSIConsoleColors
                colors::ConsoleColors::GetColorCode(colors::ColorCodes::LightGray) <<
#endif
                this->description << "\n";
    }

    for (auto &option: this->options)
    {
        if (option->short_name[0])
        {
            buf <<
#ifdef ANSIConsoleColors
                    colors::ConsoleColors::GetColorCode(colors::ColorCodes::Blue) <<
#endif
                    "-" << option->short_name;
            if (option->long_name[0])
                buf << ", ";
        }

        if (option->long_name[0])
        {
            buf <<
#ifdef ANSIConsoleColors
                    colors::ConsoleColors::GetColorCode(colors::ColorCodes::Cyan) <<
#endif
                    "--" << option->long_name;
        }

        if (option->has_argument)
        {
            buf << " <arg>";
        }
        if (option->is_required)
        {
            buf <<
#ifdef ANSIConsoleColors
                        colors::ConsoleColors::GetColorCode(colors::ColorCodes::Red)
                        <<
#endif
                    " (required)";
        }

        buf <<
#ifdef ANSIConsoleColors
                    colors::ConsoleColors::GetColorCode(colors::ColorCodes::LightGray)
                    <<
#endif
                "\n\t" << option->description << "\n";
    }

#ifdef ANSIConsoleColors
        buf << colors::ConsoleColors::GetColorCode(colors::ColorCodes::Default);
#endif

    const size_t length = buf.str().length() + 1;
    const auto help_str = new char[length];
    strcpy(help_str, buf.str().c_str());
    return help_str;
}

inline bool cclip::options_manager::is_present(const std::string &name) const
{
    return std::any_of(this->present_options.begin(), this->present_options.end(), [&name](const option *opt)
    {
        return opt->short_name == name || opt->long_name == name;
    });
}

inline cclip::option *cclip::options_manager::get_option(const std::string &name)
{
    for (const auto &option: this->present_options)
    {
        if (option->short_name == name || option->long_name == name)
        {
            return option;
        }
    }
    return nullptr;
}

inline cclip::option *cclip::options_manager::get_option_from_global_list(const std::string &name)
{
    for (const auto &option: this->options)
    {
        if (std::strcmp(option->short_name, name.c_str()) == 0 || std::strcmp(option->long_name, name.c_str()) == 0)
        {
            return option;
        }
    }
    return nullptr;
}

char *cclip::options_manager::build_autocomplete_ps1() const
{
    if (this->command_name.empty())
    {
        throw std::runtime_error("Command name is not set, make sure to run after parsing the command line arguments.");
    }
    std::string options;

    for (const auto &option: this->options)
    {
        if (option->short_name[0])
        {
            options += "'-";
            options += option->short_name;
            options += "', ";
        }

        if (option->long_name[0])
        {
            options += "'--";
            options += option->long_name;
            options += "', ";
        }
    }
    options = options.substr(0, options.length() - 2); // Remove the trailing comma and space

    std::string ps1 =
            "# " + std::string(this->context) + " command-line autocomplete\n"
            "Register-ArgumentCompleter -CommandName " + this->command_name + " -ScriptBlock {\n"
            "param($commandName, $wordToComplete, $cursorPosition)\n"
            "$options = " + options + "\n\n"
            "$options | Where-Object { $_ -like \"$wordToComplete * \" } | ForEach-Object {\n"
            "[System.Management.Automation.CompletionResult]::new($_, $_, 'ParameterName', $_)\n"
            "}\n"
            "}\n";
    return strdup(ps1.c_str());
}
