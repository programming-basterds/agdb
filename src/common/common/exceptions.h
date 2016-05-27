/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        exceptions.h
 * @author      Emanuel Bringas, Francisco Herrero
 * @date        2016-05-06
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

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "mili/mili.h"

namespace NSCommon
{

/** @brief  Represents the package exception hierarchy for mili::generic_exception usage. */
struct AgdbExceptionHierarchy {};

/** @brief Generic exception for the NSClient module. */
typedef mili::GenericException<AgdbExceptionHierarchy> AgdbExceptionHandling;

DEFINE_SPECIFIC_EXCEPTION_TEXT(ProgramNotFound, AgdbExceptionHandling,
                               "Program not found");

DEFINE_SPECIFIC_EXCEPTION_TEXT(LocalGDBConnectionFailed, AgdbExceptionHandling,
                               "Could not connect with local gdb");

DEFINE_SPECIFIC_EXCEPTION_TEXT(RemoteGDBConnectionFailed, AgdbExceptionHandling,
                               "Could not connect with remote gdb");


DEFINE_SPECIFIC_EXCEPTION_TEXT(ParameterSettingFailed, AgdbExceptionHandling,
                               "Program arguments could not set");

// Command arguments
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidArgumentNumbers, AgdbExceptionHandling,
                               "Invalid arguments numbers");

DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidArguments, AgdbExceptionHandling,
                               "Invalid arguments");

DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidInstanceID, AgdbExceptionHandling,
                               "Invalid instance id.");

// Printing aspect
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidExpressionToValidate, AgdbExceptionHandling,
                               "Invalid expressions to validate");

// Disassemble aspect
DEFINE_SPECIFIC_EXCEPTION_TEXT(DisassembleExecutionFailed, AgdbExceptionHandling,
                               "Can not execute disassemble command.");

// Listing aspect exceptions.
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidFilename, AgdbExceptionHandling,
                               "Invalid filename");

DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidLineNumber, AgdbExceptionHandling,
                               "Invalid line number");
// Base sspect
DEFINE_SPECIFIC_EXCEPTION_TEXT(MiAsyncModeError, AgdbExceptionHandling,
                               "Error while trying to set MI on asynchronous mode");

DEFINE_SPECIFIC_EXCEPTION_TEXT(ProgramRunError, AgdbExceptionHandling,
                               "Error while trying to run program");

// Gdb proxy exceptions
DEFINE_SPECIFIC_EXCEPTION_TEXT(ErrorContinue, AgdbExceptionHandling,
                               "Error while trying to continue program");

DEFINE_SPECIFIC_EXCEPTION_TEXT(ErrorCreatingBreakpoint, AgdbExceptionHandling,
                               "Error while trying to create breakpoint");

DEFINE_SPECIFIC_EXCEPTION_TEXT(GdbBreakpointError , AgdbExceptionHandling,
                               "Error Setting Breakpoint");

DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidMultibreakpoint, AgdbExceptionHandling,
                               "Invalid Breakpoint Id");


// Raise exceptions
DEFINE_SPECIFIC_EXCEPTION_TEXT(RaiseLocalBreakpointError , AgdbExceptionHandling,
                               "Error Setting Breakpoint for Local Raise");

DEFINE_SPECIFIC_EXCEPTION_TEXT(WrongInstanceNumber, AgdbExceptionHandling,
                               "Wrong GDB instance number");

// MI utils exceptions
DEFINE_SPECIFIC_EXCEPTION_TEXT(ErrorRequestingThreadInfo, AgdbExceptionHandling,
                               "Error Requesting thread info");

// Stepping aspect
DEFINE_SPECIFIC_EXCEPTION_TEXT(SteppingExecutionFailed, AgdbExceptionHandling,
                               "Can not execute stepping command.");

} // End of namespace NSCommon

#endif // EXCEPTIONS_H
