# cclip - C/C++ Command Line Interface Parser

`cclip` is a simple C++ library for parsing command line arguments. It allows you to define and parse command-line options and arguments easily in your C++ applications.

## Installation

> ### **NOTE:**
> This library is header-only, so you don't need to build or install anything. Just include the `cclip.hpp` header file in your project.   
> Also this project requires a C++17 compatible compiler.

### Github Clone

```bash
git clone https://github.com/Drew-Chase/cclip.git ./vendor/cclip
```

### Github Submodule

```bash
git submodule add https://github.com/Drew-Chase/cclip.git ./vendor/cclip
```

### Manual

Download the latest release from the [releases page](https://github.com/Drew-Chase/cclip/releases) and extract the options_manager.hpp to your project's directory.

## Usage

### Create an Options Manager

```c++
cclip::options_manager manager("cclip test");
```

You can also include a description of the program.

```c++
cclip::options_manager manager("cclip test", "optional description");
```

### Adding Options

```c++
const char *short_name = "h";
const char *long_name = "help";
const char *description = "Print this help message";
bool is_required = false;
bool has_argument = false;
    manager.add_option(short_name, long_name, description, is_required, has_argument);
```

### Parsing Command Line Arguments

```c++
manager.parse(argc, argv);
```

### Checking if an Option is Present

```c++
if (manager.is_present("h")) {
    manager.print_help();
}
```

### Getting an Option

The `option` represents an individual command-line option. It contains the following fields:

- `short_name`: The short name of the option (e.g. -h).
- `long_name`: The long name of the option (e.g. --help).
- `description`: The description of the option.
- `is_required`: Whether the option is required.
- `has_argument`: Whether the option has an argument.
- `argument`: The argument of the option.

```c++
if (manager.is_present("f")) {
    auto option = manager.get_option("f");
    if (option->argument != nullptr) {
        // Do something with the argument
        std::cout << "File: " << option->argument << std::endl;
    }
}
```

### Additional Options

```c++
    // Set the version of the application
    manager.set_version("0.0.1");
    // Add example usages
    manager.add_example_usage(R"(-f C:\Users\user\Desktop\file.txt)");
    // ... add more example usages
```

### Example

Here is an example of how to use the `cclip` library to parse command-line arguments in a C++ program:

```c++
#include "cclip/cclip.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    // Create an options manager with the program name
    cclip::options_manager manager("cclip test"); 
    
    // Create an options manager with the program name and description
    cclip::options_manager manager("cclip test", "optional description");
    
    // Add options
    manager.add_option("h", "help", "Print this help message", false, false);
    manager.add_option("v", "version", "Print the version", false, false);
    manager.add_option("V", "verbose", "Print the result verbosely", false, false); // Example of a short option with a capital letter
    manager.add_option("f", "file", "The file to read", true, true);
    
    // Set the version and example usage
    manager.set_version("0.0.1");
    manager.add_example_usage(R"(-f C:\Users\user\Desktop\file.txt)");
    manager.add_example_usage(R"(-f "C:\Users\user with space\Desktop\file.txt")");

    // Parse the command line arguments
    manager.parse(argc, argv);

    if (manager.is_present("h")) {
        manager.print_help();
        return 0;
    }
    
    if (manager.is_present("v")) {
        manager.print_version();
        return 0;
    }

    if (manager.is_present("f") && manager.get_option("f")->argument != nullptr) {
        std::cout << "File: " << manager.get_option("f")->argument << std::endl;
    }

    return 0;
}
```

## Colorful Output

To add a little color to your output, you can use the [ANSIConsoleColors](https://github.com/drew-chase/ANSIConsoleColors) library, and add the header above the `cclip` header.

```c++
#include "ANSIConsoleColors/ANSIConsoleColors.h"
#include "cclip/cclip.hpp"
```

![image](https://github.com/Drew-Chase/cclip/assets/5598099/be68abbf-36d6-4e39-8abe-b2ef94334051)
![image](https://github.com/Drew-Chase/cclip/assets/5598099/057d8848-9515-416c-a5ce-ef1577091852)

## Contributing

If you'd like to contribute to the `cclip` library, please feel free to submit issues, pull requests, or suggestions on [GitHub](https://github.com/Drew-Chase/cclip/).

## License

This project is licensed under the GNU GENERAL PUBLIC LICENSE V3 - see the [LICENSE](https://raw.githubusercontent.com/Drew-Chase/cclip/main/LICENSE) file for details.
