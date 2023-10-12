//
// Created by drew_ on 10/12/2023.
//

#include <iostream>
#include <sstream>
#include "options_manager.h"

namespace ccliparser
{
    options_manager::options_manager(char *context)
    {
        this->context = context;
    }

    option *options_manager::add_option(char *short_name, char *long_name, char *description, bool is_required, bool has_argument)
    {
        option *opt = new option{short_name, long_name, description, is_required, has_argument};
        this->options.push_back(opt);
        return opt;
    }

    void options_manager::parse(int argc, char **argv)
    {

    }

    void options_manager::print_help()
    {
        std::cout << this->get_help() << std::endl;
    }

    char *options_manager::get_help()
    {
        std::stringstream buf;
        buf << this->context << " Help:\n";

        for (auto &option: this->options)
        {
            buf << " -" << option->short_name << ", --" << option->long_name << " - " << option->description;
            if (option->has_argument)
            {
                buf << " <arg> ";
            }
            if (option->is_required)
            {
                buf << " (required)";
            }

            buf << "\n";
        }

        return buf.str().data();
    }

} // ccliparser