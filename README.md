# Bank Client Management System

This is a simple C++ program that implements a basic client management system. The system allows users to perform operations on client records, including viewing, adding, updating, and deleting client information. The client data is stored in a text file.

## Features

- **User Authentication**: Login system with different permission levels for users
- **View Client List**: Display a list of all clients
- **Add New Client**: Add a new client to the system by providing details such as account number, pin code, name, phone, and account balance
- **Delete Client**: Delete an existing client by providing the client's account number
- **Update Client**: Modify the information of an existing client
- **Find Client**: Search for a client by account number
- **Transactions**: Perform banking transactions including deposits and withdrawals
- **User Management**: Manage system users and their permissions

## File Format

The client data is stored in a text file (`data/data.txt`) where each client record is stored on a separate line. The fields in each client record are separated by the string `#//#`. The fields are:

- **Account Number**
- **Pin Code**
- **Client Name**
- **Phone Number**
- **Account Balance**

### Example Record Format:
```
12345#//#1234#//#John Doe#//#123-456-7890#//#5000.00
```

## Program Flow

1. **Login Screen**: The program starts with a login screen where users must authenticate:
   ```
   ===========================================
                   Login Screen
   ===========================================
   
   Please enter Username? Admin
   
   Please enter Password? 
   ```

2. **Main Menu**: After successful login, the main menu is displayed with options based on user permissions:
   ```
   ===========================================
                   Main Menue Screen
   ===========================================
           [1] Show Client List.
           [2] Add New Client.
           [3] Delete Client.
           [4] Update Client Info.
           [5] Find Client.
           [6] Transactions.
           [7] Manage Users.
           [8] LogOut.
   ===========================================
   Choose what do you want to do? [1 to 8]?
   ```

3. **Transactions Menu**: When selecting Transactions, a sub-menu is displayed:
   ```
   ===========================================
                   Transactions Menue Screen  
   ===========================================
           [1] Deposit.
           [2] Withdraw.
           [3] Total Balances.
           [4] Main Menue.
   ===========================================
   Choose what do you want to do? [1 to 4]?
   ```

## User Permissions

The system implements role-based access control:
- Different users have different permission levels
- For example, some users may only have access to find clients but not add or modify them
- Administrative users have full access to all system functions

## Functions

### Authentication Functions
- Login system verification
- User permission management

### Client Management Functions
- `ShowMainMenue()`: Displays the main menu where the user selects an operation
- `SplitString()`: Splits a string by a delimiter into a vector of substrings
- `ConvertLinetoRecord()`: Converts a string record from the file into a `sClient` structure
- `ConvertRecordToLine()`: Converts a `sClient` structure back into a string format for saving to the file
- `ClientExistsByAccountNumber()`: Checks if a client with a specific account number already exists in the file
- `ReadNewClient()`: Prompts the user to input information for a new client and returns the `sClient` structure
- `LoadCleintsDataFromFile()`: Loads all client records from the file into a vector of `sClient` structures
- `PrintClientRecordLine()`: Prints the details of a client in a formatted line
- `ShowAllClientsScreen()`: Displays all client records
- `PrintClientCard()`: Prints the details of a specific client
- `FindClientByAccountNumber()`: Finds a client by account number from the vector of clients
- `ChangeClientRecord()`: Allows the user to change the details of an existing client
- `MarkClientForDeleteByAccountNumber()`: Marks a client for deletion by account number
- `SaveCleintsDataToFile()`: Saves the updated client data back to the file
- `AddDataLineToFile()`: Adds a new client record to the file
- `AddNewClient()`: Prompts the user to add a new client and saves it to the file
- `AddNewClients()`: Allows the user to add multiple clients
- `DeleteClientByAccountNumber()`: Deletes a client by account number after user confirmation
- `UpdateClientByAccountNumber()`: Updates a client by account number after user confirmation
- `ReadClientAccountNumber()`: Prompts the user for a client's account number

### Transaction Functions
- Deposit money into client accounts
- Withdraw money from client accounts
- View total account balances

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

For inquiries or further information, you can contact the project maintainer:

Email: [chihababiza9@gmail.com](mailto:chihababiza9@gmail.com)
