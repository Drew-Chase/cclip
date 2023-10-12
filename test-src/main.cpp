#include "../src/options_manager.h"

int main(int argc, char **argv)
{
    cclip::options_manager manager("cclip test");
    manager.add_option("h", "help", "Print this help message", false, false);
    manager.add_option("v", "version", "Print the version", false, false);
    manager.add_option("f", "file", "The file to read", true, true);

    manager.parse(argc, argv);

    if (manager.is_present("h"))
    {
        manager.print_help();
        return 0;
    }


    return 0;
}