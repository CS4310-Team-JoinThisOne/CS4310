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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Renice.h"

#include <ProcessClient.h>

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Change the priority of a process");
    parser().registerFlag('n', "new", "Changes process priority");
    parser().registerPositional("PRIO", "The new priority for the process");
    parser().registerPositional("PID", "The ID of the process to change the priority of");
}

Renice::~Renice()
{
}

Renice::Result Renice::exec()
{
    // Get input as integer
    if (arguments().get("new")){

        int prio = atoi(arguments().get("PRIO"));
        int pid = atoi(arguments().get("PID"));

        const ProcessClient process;
        ProcessClient::Info info;

        // Make sure the process is valid
        const ProcessClient::Result result = process.processInfo(pid, info);
        if (result == ProcessClient::Success)
        {
            // Valid process
            if(renice(pid, prio)) 
            {
                ERROR("failed to change priority: " << strerror(errno));
                return IOError;
            }
        }

        else
        {
            // Invalid process - return an error
            ERROR("invalid process id: " << arguments().get("PID") << "'");
            return IOError;
        }

    }
    return Success;
}
