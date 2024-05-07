// LFInteractive LLC. (c) 2020-2024 All Rights Reserved
#include "../cclip.hpp"
#include <iostream>

int main(const int argc, char **argv)
{
    cclip::options_manager manager("CCLIP Example", "This is an example of the cclip library. cclip library is a lightweight command-line argument parsing tool for C++ applications.");
    manager.add_option("h", "help", "Print this help message", false, false);
    manager.add_option("v", "version", "Print the version", false, false);
    manager.add_option("V", "verbose", "Prints to the console verbosly", false, false);
    manager.add_option("f", "file", "The file to read", true, true);

    manager.set_version("0.0.1");
    manager.add_example_usage(R"(-f C:\Users\user\Desktop\file.txt)");
    manager.add_example_usage(R"(-f "C:\Users\user with space\Desktop\file.txt")");

    manager.parse(argc, argv);

    if (manager.is_present("h"))
    {
        manager.print_help();
        return 0;
    }

    if (manager.is_present("v"))
    {
        manager.print_version();
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
