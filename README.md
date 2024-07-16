<a id="top"></a>

# Philosophers Project


## Table of Contents
- [Introduction](#introduction)
- [Objectives](#objectives)
- [Rules](#rules)
- [Installation](#installation)
- [Usage](#usage)
- [Example](#example)

## Introduction

The ```philosophers``` project is a classic concurrency problem often used to illustrate synchronization issues and techniques in concurrent algorithms. The problem involves a group of philosophers sitting at a table, each alternating between thinking and eating. There is a fork between each pair of philosophers, and a philosopher needs both forks to eat. The challenge is to design a protocol that allows the philosophers to eat without causing a **deadlock** or starvation.

## Objectives

In this project, students are asked to learn and apply:

1. **Concurrency and Parallelism**: Understanding the principles of concurrent execution and managing multiple threads.
	
2. **Synchronization Techniques**: Using mutexes, semaphores, and other synchronization mechanisms to coordinate access to shared resources.
3. **Deadlock and Starvation Avoidance**: Implementing strategies to prevent deadlock and ensure all threads get fair access to resources.

4. **Thread Management**: Creating, managing, and terminating threads safely.


## Rules

1. **Number of Philosophers**: The number of philosophers is specified as the first argument when running the program.

2. **Time to Die**: The maximum time (in milliseconds) a philosopher can go without eating before they die.

3. **Time to Eat**: The time (in milliseconds) it takes for a philosopher to eat.

4. **Time to Sleep**: The time (in milliseconds) a philosopher spends sleeping after eating.

5. **Number of Times Each Philosopher Must Eat**: The number of times each philosopher must eat before the simulation ends. <u>If not specified, the simulation continues indefinitely.</u>

6. **Thinking and Eating**: Philosophers can either be thinking or eating. They need two forks to eat.

7. **Forks**: There is one fork between each pair of philosophers.

8. **Synchronization**: Ensure that no two philosophers can access the same fork simultaneously.

9. **Deadlock and Starvation**: Avoid scenarios where philosophers are waiting indefinitely for a fork (deadlock) and ensure that all philosophers get a chance to eat (avoid starvation).

## Installation

To install and set up the project, follow these steps:

1. Clone the repository:
```bash
git clone https://github.com/KarlQuerel/42-philosophers.git
```

2. Navigate to the project directory:
```
cd 42-philosophers
```

3. Compile the project using ```make```:
```bash
make
```

## Usage

To run the Philosophers program, use the following command:

```bash
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>
```

## Example
Replace placeholders with the desired values. For example:

```bash
./philosophers 7 800 200 200 10
```
The program will output the state of each 7 philosopher (thinking, eating or sleeping) and ensure that synchronization rules are followed to prevent deadlock or starvation.

For more information, refer to the [subject PDF](https://github.com/KarlQuerel/42-philosophers/blob/master/docs/en.subject.pdf).

[Back to Top](#top)
