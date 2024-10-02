# Restaurant Simulation System

This project was developed as a task for the **Data Structures and Algorithms** course during the first semester of 2021 at the Pontifical Catholic University of Chile. The main objective of this task is to introduce the fundamentals of the C programming language, particularly focusing on **structs**, **pointers**, **arrays**, and **linked lists**.

## Project Overview

The task revolves around helping the fictional chef "DCChef Remy" manage his chain of restaurants. Due to the growing number of customers, Remy needs an efficient system to handle seating arrangements, customer orders, and table management across multiple restaurants.

This system simulates a variety of events, such as opening tables, seating customers, handling orders, and managing bills. The goal is to correctly implement these operations using the appropriate data structures.

### Key Objectives

- Understand the difference between arrays and linked lists and implement these structures.
- Become familiar with pointers and memory management.
- Model real-world problems using data structures.
- Analyze and apply concepts related to time complexity.

## Features

- **Opening Tables**: Manage table capacities and customer seating.
- **Customer Management**: Add and remove customers dynamically.
- **Order Processing**: Handle individual customer orders.
- **Bill Creation**: Generate bills per table with detailed breakdowns.
- **Table and Customer Interaction**: Handle special events like seat swapping or customer exits.

## Execution Instructions

To compile and run the program, follow these steps:

1. **Compilation**:
   Use the provided `Makefile` to compile the program. In the project directory, run:

   ```bash
   make
    ```

    This will generate an executable named ratatouille.

2. **Running the Program**: To execute the program, use the following command:

    ```bash
    ./ratatouille tests/<difficulty>/<test_file> output.txt
    ```

    - `tests/<difficulty>/<test_file>`: A file containing the events to simulate. The difficulty can be `easy`, `medium`, or `hard`, and the test file can be any of the provided test cases.
    - `output.txt`: A file where the results of the simulation will be saved.

## Input Format

- The input file will first indicate the number of restaurants N, followed by the number of tables in each restaurant.
- Events such as opening tables, adding customers, and handling orders will be listed sequentially.
- The file ends with the END command, which triggers the final status report of all tables.

### Example Input:

```sql
3
5 3 4
2
OPEN-TABLE 1 1 4
OPEN-TABLE 2 1 6
3
MENU-ITEM 1 1500
MENU-ITEM 2 2500
CUSTOMER 1 1 101
ORDER-CREATE 1 1 101 1
TABLE-STATUS 1 1
END
```

## Output Format

The output file will display the status of each table after the simulation, detailing which tables are occupied, the orders placed by each customer, and the final bill generation.

### Example Output:

```sql
ESTADO MESA 1:1
CAPACIDAD TOTAL 4
CAPACIDAD RESTANTE 3
CLIENTES
101
FIN ESTADO
BOLETA MESA 1:1
PEDIDOS
PERSONA 101
1 1500
gastoTotalPersona 1500
FIN PERSONA
TOTAL 1500
FIN BOLETA
```