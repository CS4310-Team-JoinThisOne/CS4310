/*
 * Copyright (C) 2009 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <FreeNOS/User.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Timer.h>
#include <FreeNOS/Kernel.h>
#include "unistd.h"
#include "errno.h"
#include <ProcessClient.h>
#include <ProcessManager.h>
#include <Kernel.h>
#include <Process.h>

unsigned int renice(unsigned int pid, unsigned int prio)
{
    if (ProcessCtl(pid, SetPriority, 0, prio))
    {
        errno = EIO;
        return pid;
    }
    printf("Changed the priority to %d\n", prio);
    return 0;
}