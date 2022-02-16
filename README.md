![](https://github.com/ingdicath/images_md/blob/main/philosophers.png)

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
- Simulation stops when a philosopher dies or if all philosophers have eaten at least a certain number of times.

---
## How to build :hammer:

1. Clone the repository ```git clone git@github.com:ingdicath/philosophers.git```
2. Go to folder ```cd philosophers/philo```
3. Type in the terminal ```make```

### Usage of _philo_

There are two ways to execute:

1.&ensp;_./philo_&ensp;&ensp;_number_of_philosophers_&ensp;&ensp;_time_to_die_&ensp;&ensp;_time_to_eat_&ensp;&ensp;_time_to_sleep_
 
`./philo 5 800 200 200`

<br>2.&ensp;_./philo_&ensp;&ensp;_number_of_philosophers_&ensp;&ensp;_time_to_die_&ensp;&ensp;_time_to_eat_&ensp;&ensp;_time_to_sleep_&ensp;&ensp;_number_of_times_each_philosopher_must_eat_&ensp;&ensp;

`./philo 5 800 200 200 7`

----
## Outputs 😎
- **Case 1:** Philoshopers don't die.
<p align="center"><img src="https://github.com/ingdicath/images_md/blob/main/philo_no_die.png" width=35%" height="35%"></p>
  
- **Case 2:**  A philoshoper dies.
<p align="center"><img src="https://github.com/ingdicath/images_md/blob/main/philo_die.png" width="35%" height="35%"></p>

- **Case 3:** Philoshoper have eaten a certain number of times.
<p align="center"><img src="https://github.com/ingdicath/images_md/blob/main/philos_eat_enough.png" width="35%" height="35%"></p>
