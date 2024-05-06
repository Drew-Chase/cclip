// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "../cclip.hpp"
#include <iostream>

int main(const int argc, char **argv)
{
    cclip::options_manager manager("cclip test");
    manager.add_option("h", "help", "Print this help message", false, false);
    manager.add_option("v", "version", "Print the version", false, false);
    manager.add_option("V", "verbose", "Prints to the console verbosly", false, false);
    manager.add_option("f", "file", "The file to read", true, true);

    manager.parse(argc, argv);

    if (manager.is_present("h"))
    {
        manager.print_help();
        return 0;
    }

    if (manager.is_present("v"))
    {
        std::cout << "cclip test 0.0.1" << std::endl;
        return 0;
    }

    if (manager.is_present("V"))
    {
        std::cout << "This is verbose mode" << std::endl;
    }


    if (manager.is_present("f") && manager.get_option("f")->argument != nullptr)
    {
        std::cout << "File: " << manager.get_option("f")->argument << std::endl;
    }
    system("pause");
}
