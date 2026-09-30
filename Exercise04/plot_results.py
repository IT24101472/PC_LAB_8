import matplotlib.pyplot as plt

processors = [1, 2, 4, 8]

# Exercise 2 - Sum
sum_times = [0.00503424, 0.00262514, 0.00133953, 0.00155162]
sum_speedup = [1.00, 1.92, 3.76, 3.24]

# Exercise 3 - Monte Carlo Pi
pi_times = [0.10641206, 0.05330732, 0.02677036, 0.01953430]
pi_speedup = [1.00, 2.00, 3.97, 5.45]

# Time graph
plt.figure()
plt.plot(processors, sum_times, marker='o', label='Sum')
plt.plot(processors, pi_times, marker='o', label='Monte Carlo Pi')
plt.xlabel('Number of Processes')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time vs Number of Processes')
plt.xticks(processors)
plt.grid(True)
plt.legend()
plt.savefig('time_vs_processors.png')
plt.close()

# Speedup graph
plt.figure()
plt.plot(processors, sum_speedup, marker='o', label='Sum')
plt.plot(processors, pi_speedup, marker='o', label='Monte Carlo Pi')
plt.xlabel('Number of Processes')
plt.ylabel('Speedup')
plt.title('Speedup vs Number of Processes')
plt.xticks(processors)
plt.grid(True)
plt.legend()
plt.savefig('speedup.png')
plt.close()

print("Graphs generated successfully.")
