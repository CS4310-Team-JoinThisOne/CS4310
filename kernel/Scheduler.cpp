/*
 * Copyright (C) 2015 Niek Linnenbank
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

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    priorityQueues[0] = m_queue_1;
    priorityQueues[1] = m_queue_2;
    priorityQueues[2] = m_queue_3;
    priorityQueues[3] = m_queue_4;
    priorityQueues[4] = m_queue_5;
    DEBUG("");
}

Size Scheduler::count() const
{
    return priorityQueues[0].count()
         + priorityQueues[1].count()
         + priorityQueues[2].count()
         + priorityQueues[3].count()
         + priorityQueues[4].count();
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }

    int prio = proc->getPriority();
    if(prio < 1 || prio > 5) {
        ERROR("process priority " << proc->getPriority() << "outside of valid range");
        return InvalidArgument;
    }

    priorityQueues[prio-1].push(proc);
    return Success;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    int prio = proc->getPriority() - 1;
    Size count = priorityQueues[prio].count();

    // Traverse the Queue to remove the Process
    for (Size i = 0; i < count; i++)
    {
        Process *p = priorityQueues[prio].pop();

        if (p == proc)
            return Success;
        else
            priorityQueues[prio].push(p);
    }

    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

Process * Scheduler::select()
{
    for(int i = 4; i >= 0; i--) {
        if(priorityQueues[i].count() == 0) {
            // No processes in this priority level - go to a lower priority level
            continue;
        }
        Process *p = priorityQueues[i].pop();
        priorityQueues[i].push(p);
        return p;
    }

    return (Process *) NULL;
}
