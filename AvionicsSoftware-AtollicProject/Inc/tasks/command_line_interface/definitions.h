#ifndef AVIONICS_DEFINITIONS_H
#define AVIONICS_DEFINITIONS_H

#include <stdbool.h>
#include <getopt.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include "protocols/UART.h"

#define STRINGIFY(a)__STRINGIFY(a)
#define __STRINGIFY(a)#a

#define DECL_NEW_USAGE(NAME)                                                               \
    static const char * NAME##_USAGE                                                       \

#define DECL_NEW_ARG_OPTIONS_FOR(NAME)                                                     \
    static const struct option_and_function NAME##_ARG_OPTIONS                             \

#define OPTION_ADD_OPTION(_name, _label)                                                   \
    {.name=STRINGIFY(_name), .has_arg=no_argument, .flag=NULL, .val=_label}                \

#define OPTION_ADD_FUNCTION(section_name, function_name)                                   \
    {.definition=section_name##_##function_name##_function, .name=STRINGIFY(function_name)}\

#define OPTION_LIST_END {.name=NULL, .has_arg=0, .flag=NULL, .val=0}

#define OPTION_NEW_TOOL_DECL(section_name)                                                 \
    bool section_name##_##parse_arguments##_function(char *);                              \

#define OPTION_NEW_TOOL_IMPL(section_name)                                                 \
    bool section_name##_##parse_arguments##_function(char * ARGUMENTS_STRING)              \

#define OPTION_TOOL_MAIN_FUNCTION(section_name)                                            \
    section_name##_##parse_arguments##_function                                            \

#define OPTION_FUNCTION_DECL(section_name, function_name)                                  \
    bool section_name##_##function_name##_function(char *);                                \

#define OPTION_FUNCTION_IMPL(section_name, function_name)                                  \
    bool section_name##_##function_name##_function(char * ARGUMENTS_STRING)                \

#define OPT_FUNCTION_FOR(section_name, function_name)                                      \
    section_name##_##function_name##_function                                              \

#define OPTIONS_COUNT() sizeof(s_arg_options.long_options) - 1

#define EXTRACT_PROGRAM_NAME_AND_ARGUMENTS(command)                                        \
            char __command[MAX_COMMAND_LENGTH];                                            \
            strcpy(__command, command);                                                    \
            char *PROGRAM[2] = {"execute", strtok(__command, "\x20")};                     \
            char *ARGUMENTS = strtok(NULL, "");                                            \

#define COMMAND_CASE_FUNC(literal_I, literal_C, section_name, function_name, args)         \
            case literal_I:                                                                \
            case literal_C:                                                                \
                OPT_FUNCTION_FOR(section_name, function_name)(args);                       \
            break                                                                          \

#define COMMAND_CASE_TOOL(literal_I, literal_C, section_name, args)                        \
            case literal_I:                                                                \
            case literal_C:                                                                \
                OPTION_TOOL_MAIN_FUNCTION(section_name)(args);                             \
            break                                                                          \

#define ERROR_CASE                                                                         \
            case '?':                                                                      \
            break                                                                          \

#define DEFAULT_CASE(command, uart, output)                                                \
            default:                                                                       \
                sprintf(output, "Command [%s] not recognized.", command);                  \
                uart_transmit_line(uart, output);                                          \
                return false;                                                              \
                
#define EXPAND_ARGUMENTS_STRING(ARGUMENT_STRING)                                           \
            char* __tokens[MAX_ARGUMENTS_LENGTH];                                          \
            uint8_t argc = 0;                                                              \
            __tokens[argc++] = "execute";                                                  \
            char* __cmd = strtok(ARGUMENTS_STRING, "\x20");                                \
            __tokens[argc] = __cmd;                                                        \
            do{    argc++;                                                                 \
                __cmd = strtok(NULL, "\x20");                                              \
                __tokens[argc] = __cmd;                                                    \
            }while(__cmd != NULL);                                                         \
            char **argv = __tokens;                                                        \
            

const static int MAX_ARGUMENTS_LENGTH       = 32;
const static int MAX_COMMAND_LENGTH         = 64;


typedef bool(*opt_arg_function_p)(char *);
typedef struct option opt_arg_long_option;
typedef char opt_arg_short_option;
typedef struct option_function option_function;

typedef struct option_function
{
    opt_arg_function_p  definition;
    const char          *name;
} option_function;

struct option_and_function
{
    const opt_arg_long_option       *LONG;
    const opt_arg_short_option      *SHORT;
    const option_function           *const FUNCTIONS;
};


#endif //AVIONICS_DEFINITIONS_H
