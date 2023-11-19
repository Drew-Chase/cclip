# cclip - C/C++ Command Line Interface Parser

`cclip` is a simple C/C++ library for parsing command line arguments. It allows you to define and parse command-line options and arguments easily in your C or C++ applications.

## Installation
### Github Clone
```bash
git clone https://github.com/Drew-Chase/cclip.git ./vendor/cclip
```
### Github Submodule
```bash
git submodule add https://github.com/Drew-Chase/cclip.git ./vendor/cclip
```



## Usage

### Example

Here is an example of how to use the `cclip` library to parse command-line arguments in a C++ program:

```cpp
#include "cclip/options_manager.h"
#include <iostream>

int main(int argc, char **argv) {
    cclip::options_manager manager("cclip test");
    manager.add_option("h", "help", "Print this help message", false, false);
    manager.add_option("v", "version", "Print the version", false, false);
    manager.add_option("f", "file", "The file to read", true, true);

    manager.parse(argc, argv);

    if (manager.is_present("h")) {
        manager.print_help();
        return 0;
    }

    if (manager.is_present("v")) {
        std::cout << "cclip test 0.0.1" << std::endl;
        return 0;
    }

    if (manager.is_present("f") && manager.get_option("f")->argument != nullptr) {
        std::cout << "File: " << manager.get_option("f")->argument << std::endl;
    }

    return 0;
}
```

### `options_manager` Class

The `options_manager` class is the core of the `cclip` library. It allows you to define and parse command-line options. Here are some of its key functions:

- `options_manager::add_option`: Add a new option with a short name, long name, description, and properties.
- `options_manager::parse`: Parse the command line arguments.
- `options_manager::print_help`: Print the help message.
- `options_manager::get_help`: Get the help message as a C-style string. Remember to delete the returned string when you're done with it.
- `options_manager::is_present`: Check if an option is present in the arguments.
- `options_manager::get_option`: Get an option by name.

### `option` Struct

The `option` struct represents an individual command-line option. It contains the following fields:

- `short_name`: The short name of the option (e.g. -h).
- `long_name`: The long name of the option (e.g. --help).
- `description`: The description of the option.
- `is_required`: Whether or not the option is required.
- `has_argument`: Whether or not the option has an argument.
- `argument`: The argument of the option.

## Contributing

If you'd like to contribute to the `cclip` library, please feel free to submit issues, pull requests, or suggestions on [GitHub](https://github.com/Drew-Chase/cclip/).

## License
This project is licensed under the GNU GENERAL PUBLIC LICENSE V3 - see the [LICENSE](https://raw.githubusercontent.com/Drew-Chase/cclip/main/LICENSE) file for details.