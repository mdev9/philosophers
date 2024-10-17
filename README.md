# 🍽️ Philosophers – Dining Philosophers Simulation

Welcome to **Philosophers**, a multithreaded simulation of the classic dining philosophers problem! 🥳✨ This project explores concurrency and synchronization in programming, utilizing mutexes to ensure that our philosophers dine without starving. 🥢🍽️💻 

## 📝 Project Overview

In this project, we simulate the dining philosophers problem, where philosophers alternately think 🤔 and eat 🍜, sharing limited resources (forks 🍴) while avoiding deadlock 🔒 and ensuring synchronization ⚖️. This project is a great way to deepen your understanding of multithreading and synchronization techniques. 🌐🔍

### Key Features:
- 🔹 **Multithreading**: Utilizes threads to simulate philosophers' behavior. 🧵🧑‍🤝‍🧑
- 🔹 **Mutex Synchronization**: Implements mutex locks 🔐 to manage access to shared resources. 
- 🔹 **Optimized Resource Management**: Avoids deadlocks and ensures that each philosopher gets a chance to eat. 🍽️⚙️

## 📦 Installation & Setup

To get started with **Philosophers**, follow these simple steps:

1. **Clone the repository && Compile the project**:
   ```bash
   git clone https://github.com/mdev9/philosophers.git
   cd philosophers
   make
   ```
2. **Run the simulation**:
   ```bash
   ./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: max_eat_count]
   ```
- `number_of_philosophers`: Total number of philosophers. 👨‍🍳👩‍🍳
- `time_to_die`: Time (in milliseconds) before a philosopher dies from starvation. ⏳
- `time_to_eat`: Time (in milliseconds) it takes for a philosopher to eat. 🍲
- `time_to_sleep`: Time (in milliseconds) a philosopher will sleep. 😴
- `max_eat_count` (optional): Maximum number of times each philosopher should eat. 🍽️🔁

## 🛠️ How to Use the Simulation

Here’s an example demonstrating how to run the philosophers' simulation:
   ```bash
./philosophers 5 800 200 200
   ```
This command will run a simulation with 5 philosophers, where each has 800 milliseconds before they die of starvation, takes 200 milliseconds to eat, and sleeps for 200 milliseconds. 🥱💤

## 🔍 Project Goals
The main objectives of the Philosophers project include:

- 🌐 Simulating the classic dining philosophers problem.
- 🔍 Understanding and implementing multithreading and synchronization concepts.
- 📈 Enhancing skills in parallel programming and optimization. 💪🎯

Thank you for checking out Philosophers! 🌟 May your philosophers dine in harmony! 🍴✨
