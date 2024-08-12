#include "options_manager.h"

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
        buf <<
#ifdef ANSIConsoleColors
                    colors::ConsoleColors::GetColorCode(colors::ColorCodes::Blue) <<
#endif

                " -"
                << option->short_name << ", " <<

#ifdef ANSIConsoleColors
                    colors::ConsoleColors::GetColorCode(colors::ColorCodes::Cyan) <<
#endif
                "--"
                << option->long_name;
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
