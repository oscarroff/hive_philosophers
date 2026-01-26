# hive_philosophers
philosophers project for Hive, Helsinki

The classic philosophers problem! This is the basis of many coding challenges in different languages. For this project we had to learn to use the `pthread.h` library and functions handling multithreading (pthreads) and multual-exclusion locks (mutexes).

## The Problem ##
A given number of philosophers sit around a circular table. The same number of forks are on the table, one fork between each pair of philosophers. In order to eat they need to pick up two forks (it's obviously something very tricky to eat, I'm going to hazzard a guess at one of those Master Chef sculpture-like desserts), which means that the neighbouring two philosophers cannot eat simultaneously. All philosophers eat, sleep and think for a give amount of time. While eating, they cannot sleep or think. While sleeping, they cannot eat or think. And of course, while thinking, they cannot eat or sleep. If a philosopher has not started eating in a given amount of time since starting their last meal then they die, at which point the simulation ends for all philosophers. An optional extra argument can be provided for the number of times a philosopher needs to eat before it is fed, and it no longer needs to complete tasks. If all philosophers are fed then the simulation also ends.

## The Instructions ##
For this school task we were specifically instructed to represent each philosopher with its own thread (pthread for the pthread.h library), and each fork had to be locked with its own mutex. Other requirements included the rule that philosophers cannot communicate with one another, and another that there should be no  data races (when two or more threads are competing for access to the same memory).

## The Implementation ##
I first read up on the subject and the tools at our displosal from the pthread.h library. With this in mind I then attempted to write as much of the code as possible without reference to solutions. A side-quest for this project was to write code with better error handling. I had just finished the school minishell project and tracing errors had become a big issue in the latter stages. Thus I wanted to try writing code with a consistent and comprehensive approach to error handling as I had sometimes seen in peers' work. The ft_error function was made with this in mind. I switched to a new scheme for exit codes (`0 Success`, `1 Fail/False` and `-1 Error`). Additionally I had error messages for each function get printed by the calling function.

At a glance, my first version ran relatively well, but in tighter time frames (e.g. where philosophers could theoretically only JUST survive in the given time) the philosophers were slow and erratic. Data races were also present and my thread and mutex creation had little saftey checks for when things went wrong. After discussing the problem with my peers I realised I lacked a monitor thread to which a lot of the philosophers' workload could be outsourced. Another major problem was the synchronisation of different numbers of philosophers to ensure maximum survival rates. If an even number was present then the philosophers should ideally fall into an alternating pattern where even and odd numbered philosophers should eat separately. Furthermore, if an odd total number of philosophers was present then they should follow a 3 stage eating cycle to account for the odd one out. These two issues required a bit of a rebuild, during which I created separate routines for philosophers, wait times for initalised threads (arbitrary values of 0.8 x and 1.6 x the eat time for even numbered and the last philosopher seemed to work well), and a master monitor thread that would track the state of each philosopher and the overall simulation state.

With these updates my program passsed most tests. However there was a final hurdle. In some cases syncronisation would fall apart after the first set of meals  eaten. For this I had to conceptualise a table of 3 philosophers in a situation where the sleeping was shorter than or equal to the eating time. Even if I set the philosophers off at staggered times then the first philosopher could potentially still steal the forks after the second philsopher had finished, or worse, the first and third philosophers could both take a single fork and we would enter a deadlock state  where the program would hang.

The key to unlocking this final problem was making use of the thinking time. Until now had just been a marker for when a philosopher finished sleeping. But I realised that by setting a minimum thinking time I could maintatin the initial syncronisation pattern. When sleep <= eat the value would be set to think = eat - sleep + 1. The extra one milisecond was an essential tweak foor situations where sleep and eat time was equal. This extra milisecond was all that was needed to  prevent a philosopher from stealing a mealtime from the intended next one in line.

## Data Structures ##
### Parent Program ###
Struct for shared program variables
- n: number of philosophers
- die: time until a philosopher will die after starting their last meal
- eat: time a philosopher will spend eating
- sleep: time a philosopher will spend sleeping
- think: minimum time a philosopher will spend thinking
- fed: number of times each philosopher must eat before simulation end
- i: counter for philosophers used to assign 'x' in t_philo
- f: forks, an array of bools, either unused (false) or used (true)
- flock: the fork locks, a array of mutexes
- ate: timestamp of last meal in miliseconds
- Philosopher states in bool arrays:
    -- eating: eating (true) or not (false)
    -- dead: dead (true) or alive (false)
    -- done: ate "fed" number of times and exits
- end: flag to end simulation if a philosopher dies
- t: system IDs of all threads
- m: mutex lock
- err_i: counter for if mutex or thread creation fails
### Philosophers ###
- Struct for each philosopher
- x: unique number of each philosopher
- meals: number of times a philosopher has eaten
- fork_l: fork to left of philosopher
- fork_r: fork to right of philosopher
- lock_l: lock for fork to left of philosopher
- lock_r: lock for fork to right of philosopher

## Usage ##
Philosophers usage:
`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`
- number_of_philosophers: number of philosophers and forks
- time_to_die (in milliseconds): if they have not eaten in this time, they die
- time_to_eat (in milliseconds): time it takes for them to eat
- time_to_sleep (in milliseconds): time they will spend sleeping
- number_of_times_each_philosopher_must_eat (optional argument): if all have
  eaten this number of times then simulation stops, otherwise it runs until
  someone dies

*Oscar Roff January 2026*
