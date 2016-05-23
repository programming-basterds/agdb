/**
 * Copyright © 2016 Daniel Gutson, Aurelio Remonda, Leonardo Boquillón,
 *                  Francisco Herrero, Emanuel Bringas, Gustavo Ojeda,
 *                  Taller Technologies.
 *
 * @file        GdbProxy.h
 * @author      Leonardo Boquillón
 * @date        2016-05-02
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

#ifndef _GDB_PROXY_INCLUDE_H_
#define _GDB_PROXY_INCLUDE_H_

#include "gdbProxy/GdbBaseAspect.h"
#include "gdbProxy/GdbBreakpointAspect.h"
#include "gdbProxy/GdbDisassembleAspect.h"
#include "gdbProxy/GdbListAspect.h"
#include "gdbProxy/GdbPrintAspect.h"
#include "gdbProxy/GdbRaiseAspect.h"
#include "gdbProxy/GdbStackFrameAspect.h"
#include "gdbProxy/GdbSteppingAspect.h"
#include "gdbProxy/GdbFwdAspect.h"
#include "common/AOPBuilder.h"

namespace NSGdbProxy
{

using GdbProxy = NSCommon::AOPBuilder<GdbDisassembleAspect,
      GdbListAspect,
      GdbRaiseAspect,
      GdbBreakpointAspect,
      GdbPrintAspect,
      GdbStackFrameAspect,
      GdbFwdAspect,
      GdbSteppingAspect,
      GdbBaseAspect>;

} // namespace NSGdbProxy

#endif /* _GDB_PROXY_INCLUDE_H_  */