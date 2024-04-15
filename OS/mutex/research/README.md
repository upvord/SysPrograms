# Bank Account Management System

## Overview
This C program simulates a basic banking system using pthreads where multiple threads perform operations on a shared bank account object. The operations include depositing and withdrawing money. Mutexes are used to ensure that balance update operations are thread-safe to prevent data inconsistency.

## Features
- **Thread-Safe Transactions**: Utilizes mutexes to synchronize deposit and withdrawal operations.
- **Concurrent Access**: Simulates multiple users accessing the bank account concurrently through multiple threads.
- **Randomized Transactions**: Each thread performs random deposit or withdrawal operations.

## Requirements
- GCC Compiler
- POSIX Threads Library

## Compilation and Execution
To compile the program, use the following command:

```bash
gcc -o bank_account bank_account.c -lpthread


# Bank Account Management System

## Program Structure

### Bank Account
A `BankAccount` structure is defined to hold the account balance and a mutex for synchronization.

### Transaction Functions
- **`deposit()`**: Deposits a specified amount into the bank account.
- **`withdraw()`**: Withdraws a specified amount from the bank account if sufficient funds are available.

### Thread Function
- **`perform_transactions()`**: A function that each thread executes to perform a series of deposit and withdrawal operations.

### Main Function
The `main()` function initializes a `BankAccount` with a starting balance, creates multiple threads, and starts them to perform transactions. After all threads complete, it destroys the mutex and outputs the final account balance.

## Future Enhancements
- **User Identification**: Add user IDs to track which user performed each transaction.
- **Enhanced Transaction Types**: Introduce more complex transaction types beyond simple deposit and withdrawal.

## Notes
- Ensure that your system supports POSIX threads as this program relies on pthreads for thread management.
- This program is designed for educational purposes to demonstrate the use of mutexes in a multithreaded environment.

## License
This project is open source and available under the [MIT License](LICENSE).

This README file is designed to be comprehensive, guiding a user from a basic understanding of the project to compiling and running it, along with an understanding of its structure and potential future improvements. Feel free to modify and extend it as needed for your project!
