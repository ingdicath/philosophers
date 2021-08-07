# Philoshopers

Actions:
eating
thinking
sleeping

Mandatory
philosopher with **threads** and **mutex**

Bonus
philosopher with **processes** and **semaphore**

- https://www.notion.so/philosophers-VM-c60be9c836084edfbcd9c07e29b429c4
- https://github.com/llefranc/42_philosophers/tree/main/philo_one
- https://hpc-tutorials.llnl.gov/posix/
- https://hpc.llnl.gov/training/tutorials/introduction-parallel-computing-tutorial


Videos
- [Programming with Threads](https://www.youtube.com/watch?v=uA8X5zNOGw8&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM&index=1)
- [Unix Threads in C - playlist](https://www.youtube.com/watch?v=d9s_d28yJq0)
## Requirements

### Allowed functions

```memset, printf, malloc, free, write, usleep, gettimeofday```
```pthread_create, pthread_detach, pthread_join, pthread_mutex_init,```
```pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock```


- Fix race condition -> try to make the operation atomic, it means that we want it all happen without interruption.
- Atomic operations -> In concurrent programming, it means that there will be no context switch during it - nothing can affect the execution of atomic command. An example: a web poll, open-ended questions, but we want to sum up how many people give the same answer.
- Concurrency & parallelism

// for usleep() inaccuracy
static void    stupid_sleep(unsigned long ms)
{
    unsigned long    entry;

    entry = get_time_us();
    ms *= 1000;
    while ((get_time_us() - entry) < ms)
        usleep(100);
}

//parsing
// chequear num args // ok
// verificar que los philos sean > 0
// chequear que sean num enteros positivos // ok
// 		tenemos que hacer un split de los argv // aun no es necesario
//      luego evaluar cada uno de esos strings, y convertirlos a num
// 		verificar que los numeros sean positivos
// chequear el nombre del programa ./philo
// aqui se trabah
//

//question
//in philosophers project should program close after "died" message or it should print another actions?
// R/ Exit right after the death of the first philosopher and not print anything else