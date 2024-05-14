#pragma once

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
         * The argument of the option.
         */
        char *argument;
    };
}
#endif
