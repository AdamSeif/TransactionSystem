# Bank Transaction System

This is a simple multi-threaded bank transaction system implemented in C. It simulates transactions among multiple accounts and clients.

## Prerequisites
- C compiler
- pthread library

## How to Use
1. Compile the program using a C compiler. For example, using gcc:
    ```
    gcc -o bank_transaction bank_transaction.c -pthread
    ```

2. Prepare an input file named `test_input.txt` containing transaction details. The format of the input file is as follows:
    ```
    balance <account_name> <initial_balance>
    <client_name> <transaction_type> <account_name> <amount>
    <client_name> <transaction_type> <account_name> <amount>
    ...
    ```

    Example:
    ```
    balance A 100
    balance B 200
    Alice deposit A 50
    Bob withdraw B 30
    ```

3. Run the program:
    ```
    ./bank_transaction
    ```

## Structure
- **Account**: Represents a bank account with a name and balance.
- **Transaction**: Represents a transaction with type (deposit/withdraw), account name, and amount.
- **Client**: Represents a client with a name and an array of transactions.
- **processTransactions**: Function to process transactions for a client.
- **main**: Entry point of the program where accounts and clients are read from the input file, threads are created to process transactions, and results are printed.

## Features
- Multi-threaded processing of transactions.
- Mutex locks to ensure thread safety while accessing shared data (accounts).
- Handles deposit and withdraw transactions.

## Note
- The program assumes the input file (`test_input.txt`) follows the specified format.
- Error handling for invalid input is not implemented in this version.
