/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        CommandList.h
 * @author      Daniel Gutson, Emanuel Bringas
 * @date        2016-05-04
 * @brief
 *
 * This file is part of agdb
 *
 * agdb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * agdb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with agdb.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LAST_SEPARATOR
#   define LAST_SEPARATOR SEPARATOR
#endif

COMMANDS_TABLE(BacktraceCommand,                "backtrace",  "Print backtrace of all stack frames"                                 ) SEPARATOR
COMMANDS_TABLE(BreakpointCommand,               "br",         "Add a break point"                                                   ) SEPARATOR
COMMANDS_TABLE(ContinueCommand,                 "continue",   "Continue current instance"                                           ) SEPARATOR
COMMANDS_TABLE(DisableBreakpointCommand,        "disable",    "Disable breakpoint"                                                  ) SEPARATOR
COMMANDS_TABLE(DisableMultibreakpointCommand,   "dismbr",     "disable Multibreakpoint"                                             ) SEPARATOR
COMMANDS_TABLE(EnableBreakpointCommand,         "enable",     "Enable breakpoint"                                                   ) SEPARATOR
COMMANDS_TABLE(EnableMultibreakpointCommand,    "enambr",     "enable Multibreakpoint"                                              ) SEPARATOR
COMMANDS_TABLE(FwdCommand,                      "fwd",        "Forward given string to gdb interpreter"                             ) SEPARATOR
COMMANDS_TABLE(HelpCommand,                     "help",       "Show this help"                                                      ) SEPARATOR
COMMANDS_TABLE(IgnoreBreakpointCommand,         "ignore",     "Ignore breakpoint"                                                   ) SEPARATOR
COMMANDS_TABLE(IgnoreMultibreakpointCommand,    "ignmbr",     "ignore Multibreakpoint"                                              ) SEPARATOR
COMMANDS_TABLE(InstanceCommand,                 "instance",   "Instance manager"                                                    ) SEPARATOR
COMMANDS_TABLE(ListCommand,                     "list",       "List specified source code lines"                                    ) SEPARATOR
COMMANDS_TABLE(MultiBreakpointCommand,          "mbr",        "Multibreakpoint command"                                             ) SEPARATOR
COMMANDS_TABLE(MultiContinueCommand,            "mcontinue",  "Continue multiple instances"                                         ) SEPARATOR
COMMANDS_TABLE(MultiInterruptCommand,           "minterrupt", "Interrupts the given instances, or each one of them."                ) SEPARATOR
COMMANDS_TABLE(NextCommand,                     "next",       "Step program"                                                        ) SEPARATOR
COMMANDS_TABLE(PrintCommand,                    "print",      "Print value of expression"                                           ) SEPARATOR
COMMANDS_TABLE(QuitCommand,                     "quit",       "Terminate agdb"                                                      ) SEPARATOR
COMMANDS_TABLE(RaiseLocalCommand,               "raise",      "raise command"                                                       ) SEPARATOR
COMMANDS_TABLE(RaiseRemoteCommand,              "rraise",     "raise a remote program"                                              ) SEPARATOR
COMMANDS_TABLE(StepCommand,                     "step",       "Next line of code. Get inside functions"                             ) SEPARATOR
COMMANDS_TABLE(NextDiffCommand,                 "mdiffn",     "Find execution difference of given instances using next"             ) SEPARATOR
COMMANDS_TABLE(NextInstructionDiffCommand,      "mdiffni",    "Find execution difference of given instances using next instruction" ) SEPARATOR
COMMANDS_TABLE(StepDiffCommand,                 "mdiffs",     "Find execution difference of given instances using step"             ) SEPARATOR
COMMANDS_TABLE(StepInstructionDiffCommand,      "mdiffsi",    "Find execution difference of given instances using next instruction" ) SEPARATOR
COMMANDS_TABLE(SetCommand,                      "set",        "Set variable"                                                        ) SEPARATOR
COMMANDS_TABLE(ShowVersion,                     "version",    "Show version of agdb"                                                ) LAST_SEPARATOR

#undef SEPARATOR
#undef LAST_SEPARATOR
#undef COMMANDS_TABLE

