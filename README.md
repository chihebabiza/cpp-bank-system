# Client Management System

This is a simple C++ program that implements a basic client management system. The system allows users to perform operations on client records, including viewing, adding, updating, and deleting client information. The client data is stored in a text file.

## Features

- **View Client List**: Display a list of all clients.
- **Add New Client**: Add a new client to the system by providing details such as account number, pin code, name, phone, and account balance.
- **Delete Client**: Delete an existing client by providing the client's account number.
- **Update Client**: Modify the information of an existing client.
- **Find Client**: Search for a client by account number.

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

1. **Main Menu**: The program starts with a main menu allowing the user to choose from several options:
   - View Client List
   - Add New Client
   - Delete Client
   - Update Client
   - Find Client
   - Exit the program

2. **Client Operations**: Depending on the user's choice, the program will either display the list of clients, prompt for input to add/update/delete a client, or search for a client by account number.

## Functions

### `ShowMainMenue()`
Displays the main menu where the user selects an operation.

### `SplitString()`
Splits a string by a delimiter into a vector of substrings.

### `ConvertLinetoRecord()`
Converts a string record from the file into a `sClient` structure.

### `ConvertRecordToLine()`
Converts a `sClient` structure back into a string format for saving to the file.

### `ClientExistsByAccountNumber()`
Checks if a client with a specific account number already exists in the file.

### `ReadNewClient()`
Prompts the user to input information for a new client and returns the `sClient` structure.

### `LoadCleintsDataFromFile()`
Loads all client records from the file into a vector of `sClient` structures.

### `PrintClientRecordLine()`
Prints the details of a client in a formatted line.

### `ShowAllClientsScreen()`
Displays all client records.

### `PrintClientCard()`
Prints the details of a specific client.

### `FindClientByAccountNumber()`
Finds a client by account number from the vector of clients.

### `ChangeClientRecord()`
Allows the user to change the details of an existing client.

### `MarkClientForDeleteByAccountNumber()`
Marks a client for deletion by account number.

### `SaveCleintsDataToFile()`
Saves the updated client data back to the file.

### `AddDataLineToFile()`
Adds a new client record to the file.

### `AddNewClient()`
Prompts the user to add a new client and saves it to the file.

### `AddNewClients()`
Allows the user to add multiple clients.

### `DeleteClientByAccountNumber()`
Deletes a client by account number after user confirmation.

### `UpdateClientByAccountNumber()`
Updates a client by account number after user confirmation.

### `ReadClientAccountNumber()`
Prompts the user for a client’s account number.

### `ShowDeleteClientScreen()`
Displays the screen for deleting a client.

### `ShowUpdateClientScreen()`
Displays the screen for updating a client.

### `ShowAddNewClientsScreen()`
Displays the screen for adding new clients.

### `ShowFindClientScreen()`
Displays the screen for searching a client.

### `ShowEndScreen()`
Displays the end screen when the program exits.

## Example

### Main Menu:
```
===========================================
		Main Menue Screen
===========================================
		[1] Show Client List.
		[2] Add New Client.
		[3] Delete Client.
		[4] Update Client Info.
		[5] Find Client.
		[6] Exit.
===========================================
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact

For inquiries or further information, you can contact the project maintainer:

- Email: [chihababiza9@gmail.com](mailto:chihababiza9@gmail.com)
