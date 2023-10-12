//
// Created by drew_ on 10/12/2023.
//

#include <iostream>
#include <sstream>
#include "options_manager.h"

namespace cclip
{

    options_manager::options_manager(const char *context)
    {
        this->context = context;
    }

    option *options_manager::add_option(const char *short_name, const char *long_name, const char *description, bool is_required, bool has_argument)
    {
        option *opt = new option{short_name, long_name, description, is_required, has_argument};
        this->options.push_back(opt);
        return opt;
    }

    void options_manager::parse(int argc, char **argv)
    {
        for (int i = 0; i < argc; ++i)
        {
            char *arg = argv[i];
            if (arg[0] == '-')
            {
                if (arg[1] == '-')
                {
                    // long option
                    char *name = arg + 2;
                    option *opt = this->get_option_from_global_list(name);
                    if (opt == nullptr)
                    {
                        std::cerr << "Unknown option: " << name << std::endl;
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
                } else
                {
                    // short option
                    char *name = arg + 1;
                    option *opt = this->get_option_from_global_list(name);
                    if (opt == nullptr)
                    {
                        std::cerr << "Unknown option: " << name << std::endl;
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
        bool missing = false;
        for (auto &option: this->options)
        {
            if (option->is_required && !this->is_present(option->short_name))
            {
                std::cerr << "Missing required option: -" << option->short_name << " or --" << option->long_name << std::endl;
                missing = true;
            }
        }
        if (missing)
        {
//            std::cerr << std::endl;
            this->print_help();
            exit(1);
        }

    }

    void options_manager::print_help()
    {
        const char *help = this->get_help();
        std::cout << help << std::endl;
        delete[] help; // Deletes the memory allocated by get_help()
    }

    const char *options_manager::get_help()
    {
        std::stringstream buf;
        buf << this->context << " Help:\n";

        for (auto &option: this->options)
        {
            buf << " -" << option->short_name << ", --" << option->long_name;
            if (option->has_argument)
            {
                buf << " <arg>";
            }
            if (option->is_required)
            {
                buf << " (required)";
            }


            buf << "\n\t" << option->description << "\n";
        }


        size_t length = buf.str().length() + 1;
        char *help_str = new char[length];
        strcpy_s(help_str, length, buf.str().c_str());

        return help_str;
    }

    bool options_manager::is_present(const char *name)
    {
        for (auto &option: this->present_options)
        {
            if (option->short_name == name || option->long_name == name)
            {
                return true;
            }
        }

        return false;
    }

    option *options_manager::get_option(const char *name)
    {
        for (auto &option: this->present_options)
        {
            if (option->short_name == name || option->long_name == name)
            {
                return option;
            }
        }
        return nullptr;
    }

    option *options_manager::get_option_from_global_list(const char *name)
    {
        for (auto &option: this->options)
        {
            if (option->short_name == name || option->long_name == name)
            {
                return option;
            }
        }
        return nullptr;
    }

} // cclip