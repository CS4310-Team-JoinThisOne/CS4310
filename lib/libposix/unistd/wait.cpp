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
#include "unistd.h"
#include "errno.h"
#include <ProcessClient.h>

unsigned int wait(unsigned int pid)
{
    printf("Waiting for process to terminate\n");

    // Wait for the process to terminate
    if (ProcessCtl(pid, WaitPID))
    {
        errno = EIO;
        return pid;
    }

    // Done
    printf("Wait successful\n");
    return 0;
}