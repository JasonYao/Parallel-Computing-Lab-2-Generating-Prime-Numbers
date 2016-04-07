# Project Conclusions

## The graphs
### Speedup
The speedup due to thread count is shown in the graph below:
- For `N = 1,000`

![The speedup due to thread count](img/speedupA.png)

- For `N = 10,000`

![The speedup due to thread count](img/speedupB.png)

- For both speedup graphs combined

![The speedup due to thread count](img/speedup.png)

Where we define speedup per Dr.Zahran's notes as:

![Process speedup definition](img/speedupDefinition.png)

This speedup graph was derived from the averages of the time required to execute fully, 
shown in the graph below, and taken from a sample size of 5 runs per each set, 
with the full data available for viewing [here](Aggregate Output.xlsx).

### Runtime
The original wall-clock runtimes are shown in the following graphs:
- For `N = 1,000`

![Program runtime](img/runtimeA.png)

- For `N = 10,000`

![Program runtime](img/runtimeB.png)

- For both runtime graphs combined

![Program runtime](img/runtime.png)

### Performance
We define the performance of an executing program per Dr. Zahran's definition as:

![Performance Definition](img/performanceDefinition.png)

From this definition, the following performance graphs were derived from the full data set linked above:

- For `N = 1,000`

![Thread performance](img/performanceA.png)

- For `N = 10,000`

![Thread performance](img/performanceB.png)

- For both performance graphs combined

![Thread performance](img/performance.png)

## The "Why" for the speedup graphs
As we can see per the trendline in the speedup graphs, there is an exponential decrease in 
speedup as the number of threads increases. This could be attributed to the fact that as the
number of threads increase, the amount of work per thread is decreased. Combine this fact with
the performance cost of `fork()`ing and `join()`ing threads, and we can see that overhead 
increases as the number of threads increase.

Another thing to note from the speedup graphs is that as the value of `N` increases, generally 
speaking there is a noticeable decrease in the speedup. This could be attributed to the fact that
since each thread has more data to work on, it requires more time to process during each parallel
section.
