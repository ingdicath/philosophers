# philosophers

CODAM project Curriculum 2019.

- **Project type**: Unix logic.
- **Objective**: Learn the basics of _threading_ a process and how to manage shared memory between threads, including the use of _mutex_.
---
## Requirements

Write the program in C.

### Description

- One or more philosophers are sitting at a round table doing one of three things:
`eating`, `thinking`, or `sleeping`.
- The philosophers sit at a circular table with a bowl of spaghetti in the center with some forks on the table.
- A philosopher must eat with two forks, one for each hand.
- The philosophers must never be starving and each one needs to eat.
- Don't speak each other and don't know when other will die.
- After finished eating, the philosopher will drop his forks and start sleeping, and when finished, will start thinking.
- Simulation stops when a philosopher dies.

### Allowed functions

`memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`
`pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`,
`pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock`
---

## Strategy :bulb:


---
## How to build :hammer:

1. Clone the repository and go to folder ```cd philosophers/philo```
2. Type in the terminal ```make```

### Usage of _philo_ and _philo_bonus_



Mandatory
philosopher with **threads** and **mutex**

Bonus
philosopher with **processes** and **semaphore**

- https://www.notion.so/philosophers-VM-c60be9c836084edfbcd9c07e29b429c4
- https://github.com/llefranc/42_philosophers/tree/main/philo_one
- https://hpc-tutorials.llnl.gov/posix/
- https://hpc.llnl.gov/training/tutorials/introduction-parallel-computing-tutorial
- https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html


Videos
- [Programming with Threads](https://www.youtube.com/watch?v=uA8X5zNOGw8&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM&index=1)
- [Unix Threads in C - playlist](https://www.youtube.com/watch?v=d9s_d28yJq0)
## Requirements

