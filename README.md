# BankingSystemProject

## Technical Information:

UML diagrams are located in the `docs` folder.

To build the project, clone the repository and run the following commands in the terminal from the directory containing the cloned content:
```
mkdir build && cd build && cmake .. && make && cd ..
```
The minimum required version of CMake is 3.14. GoogleTest must be installed for successful compilation.

To run the application, use the command: `./bin/banking-system`, and to execute all tests, use: `./bin/run-all-tests`.


## Project Description:

**Structure**

The project represents a banking system comprising multiple banks offering financial services for cash operations. Each bank manages accounts and clients. A client has a first name, last name, address, and passport number (first and last name are mandatory, the other details are optional).

There are three types of accounts: debit, deposit, and credit. Each account belongs to a specific client.

* **Debit Account:** A standard account allowing withdrawals at any time without going into negative balance. No fees are applied.
 
* **Deposit Account:** An account that prohibits withdrawals and transfers until the term expires but allows deposits. No fees are charged.

* **Credit Account:** An account with a set credit limit, allowing clients to go negative. A fixed fee is charged for using the credit limit.

**Implementation Details**

Each account provides functionality for withdrawal, deposit, and transfer operations (each account has a unique identifier).

The client creation process occurs in stages. Initially, the client provides their first and last name (mandatory), and may optionally add their address and passport details. If a client does not provide their address or passport number when creating an account, that account is classified as suspicious, which limits withdrawal and transfer operations above a certain threshold (different banks may set varying limits). Once the client provides all the necessary information, the account ceases to be suspicious and is available for unrestricted use.

Additionally, the system includes a transaction cancellation mechanism.

## Additional Features:

The project includes several enhancements that enrich its functionality:

* `MessageHandler` **Class:** Efficiently manages messaging within the system, facilitating easy interface adjustments.

* **Capitalization Viewing:** Clients can view capitalization for any bank, providing insights into their investments.

* **Balance Overview:** Users can check their total balance across multiple banks, streamlining financial management.

* **Transfer Messages:** The ability to add text messages to transfers enhances communication between clients during transactions.

These features significantly improve the user experience and operational flexibility of the banking system.
