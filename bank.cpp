#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string ClientsFileName = "data/clients.txt";
const string UsersFileName = "data/users.txt";

void ShowMainMenue();
void ShowTransactionsMenue();
void ShowManageUsersMenu();

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

struct sUser
{
    string Username;
    string Password;
    short Permission = 0;
    bool MarkForDelete = false;
};

enum enTransactionsMenueOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eShowTotalBalance = 3,
    eShowMainMenue = 4
};

enum enMainMenueOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eShowTransactionsMenue = 6,
    eManageUsers = 7,
    eLogOut = 8
};

enum enManageUsersOptions
{
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMenu = 6
};

sUser UserSession;

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord;
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);
    return Client;
}

sUser ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    sUser User;
    vector<string> vUserData = SplitString(Line, Seperator);
    User.Username = vUserData[0];
    User.Password = vUserData[1];
    User.Permission = stoi(vUserData[2]);
    return User;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

string ConvertRecordToLine(sUser User, string Seperator = "#//#")
{
    string stUserRecord = "";
    stUserRecord += User.Username + Seperator;
    stUserRecord += User.Password + Seperator;
    stUserRecord += to_string(User.Permission);
    return stUserRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return false;
}

bool UserExistByUsername(string Username, string FileName, sUser &User)
{
    fstream Myfile;
    Myfile.open(UsersFileName, ios::in);
    if (Myfile.is_open())
    {
        string Line;
        while (getline(Myfile, Line))
        {
            User = ConvertLineToRecord(Line);
            if (User.Username == Username)
            {
                Myfile.close();
                return true;
            }
        }
        Myfile.close();
    }
    return false;
}

sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "]already exists,Enter another Account Number ? ";
        getline(cin >> ws, Client.AccountNumber);
    }
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

enum UserPermissions
{
    VIEW_USERS = 1,  // 2^0 = 1
    ADD_USER = 2,    // 2^1 = 2
    DELETE_USER = 4, // 2^2 = 4
    UPDATE_USER = 8, // 2^3 = 8
    FIND_USER = 16   // 2^4 = 16
};

short ReadPermission()
{
    short permissions = 0;
    char choice;

    std::cout << "\nDo you want to have access to users list? ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
        permissions |= VIEW_USERS;

    std::cout << "\nDo you want to have access to add user? ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
        permissions |= ADD_USER;

    std::cout << "\nDo you want to have access to delete user? ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
        permissions |= DELETE_USER;

    std::cout << "\nDo you want to have access to update user? ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
        permissions |= UPDATE_USER;

    std::cout << "\nDo you want to have access to find user? ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
        permissions |= FIND_USER;

    return permissions;
}

bool IsAccesed(short Permission, enManageUsersOptions Option)
{
    return (Permission & Option) == Option || Permission == -1;
}

sUser ReadNewUser()
{
    sUser User;
    char choice;
    cout << "Enter Username ? ";
    cin >> User.Username;
    while (UserExistByUsername(User.Username, UsersFileName, User))
    {
        cout << "\nClient with [" << User.Username << "]already exists,Enter another Username ? ";
        cin >> User.Username;
    }
    cout << "Enter Password ";
    cin >> User.Password;
    cout << "Do you want to have all access ? ";
    cin >> choice;
    choice == 'Y' || choice == 'y' ? User.Permission = -1 : User.Permission = ReadPermission();

    return User;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

vector<sUser> LoadUsersDataFromFile(string FileName)
{
    vector<sUser> vUsers;
    fstream Myfile;
    Myfile.open(FileName, ios::in);
    if (Myfile.is_open())
    {
        string Line;
        sUser User;
        while (getline(Myfile, Line))
        {
            User = ConvertLineToRecord(Line);
            vUsers.push_back(User);
        }
        Myfile.close();
    }
    return vUsers;
}

void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintClientRecordBalanceLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintUserRecordLine(sUser User)
{
    cout << "| " << setw(40) << left << User.Username;
    cout << "| " << setw(40) << left << User.Password;
    cout << "| " << setw(10) << left << User.Permission;
}

void ShowAccessDenidedScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\nAccess denied!";
    cout << "\n-----------------------------------\n";
}

void ShowAllClientsScreen()
{
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (sClient Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

void ShowAllUsersScreen(sUser Session)
{
    if (!IsAccesed(Session.Permission, enManageUsersOptions::eListUsers))
    {
        ShowAccessDenidedScreen();
    }
    else
    {
        vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
        cout << "\n\t\t\t\t\tClient List (" << vUsers.size() << ")User(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        cout << "| " << left << setw(40) << "Username";
        cout << "| " << left << setw(40) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else
            for (sUser User : vUsers)
            {
                PrintUserRecordLine(User);
                cout << endl;
            }
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << endl;
    }
}

void ShowTotalBalances()
{
    vector<sClient> vClients =
        LoadCleintsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ")Client(s).";
    cout
        << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    double TotalBalances = 0;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (sClient Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

void PrintUserCard(sUser User)
{
    cout << "\nThe following are the user details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername : " << User.Username;
    cout << "\nPassword : " << User.Password;
    cout << "\nPermissions : " << User.Permission;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

bool FindUserByUsername(string Username, vector<sUser> vUsers, sUser &User)
{
    for (sUser U : vUsers)
    {
        if (U.Username == Username)
        {
            User = U;
            return true;
        }
    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

sUser UpdateUserRecord(string Username)
{
    sUser User;
    char choice;
    User.Username = Username;
    cout << "\nEnter Password ? ";
    cin >> User.Password;
    cout << "Do you want to have all access ? ";
    cin >> choice;
    choice == 'Y' || choice == 'y' ? User.Permission = -1 : User.Permission = ReadPermission();
    return User;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    for (sClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

bool MarkUserForDeleteByUsername(string Username, vector<sUser> &vUsers)
{
    for (sUser &U : vUsers)
    {
        if (U.Username == Username)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);
    string DataLine;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

vector<sUser> SaveUsersDataToFile(string FileName, vector<sUser> vUsers)
{
    fstream Myfile;
    Myfile.open(UsersFileName, ios::out);
    if (Myfile.is_open())
    {
        string Line;
        for (sUser U : vUsers)
        {
            if (U.MarkForDelete == false)
            {
                Line = ConvertRecordToLine(U);
                Myfile << Line << endl;
            }
        }
        Myfile.close();
    }
    return vUsers;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewUser()
{
    sUser User = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertRecordToLine(User));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        // system("cls");
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y / N? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void AddNewUsers()
{
    char choice = 'y';
    do
    {
        // system("cls");
        cout << "Adding New Client:\n\n";
        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more users? Y / N? ";
        cin >> choice;
    } while (toupper(choice) == 'Y');
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);
            // Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool DeleteUsersByUsername(string Username, vector<sUser> &vUsers)
{
    if (Username == "Admin")
    {
        cout << "\nYou can NOT delete Admin";
        return false;
    }
    sUser User;
    char Answer = 'n';
    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);
        cout << "\n\nAre you sure you want delete this user? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUsername(Username, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);
            // Refresh Clients
            vUsers = LoadUsersDataFromFile(UsersFileName);
            cout << "\n\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n? ";
        cin >>
            Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateUserByUsername(string Username, vector<sUser> &vUsers)
{
    sUser User;
    char Answer = 'n';
    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this user? y/n? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUser &U : vUsers)
            {
                if (U.Username == Username)
                {
                    U = UpdateUserRecord(Username);
                    break;
                }
            }
            SaveUsersDataToFile(UsersFileName, vUsers);
            cout << "\n\nUser Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
        return false;
    }
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient> &vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction?y /n? ";
    cin >>
        Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        }
        return false;
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

string ReadUserUsername()
{
    string Username = "";
    cout << "\nPlease enter Username? ";
    cin >> Username;
    return Username;
}

string ReadUserPassword()
{
    string Password = "";
    cout << "\nPlease enter Password? ";
    cin >> Password;
    return Password;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowDeleteUserScreen(sUser Session)
{
    if (!IsAccesed(Session.Permission, enManageUsersOptions::eDeleteUser))
    {
        ShowAccessDenidedScreen();
    }
    else
    {

        cout << "\n-----------------------------------\n";
        cout << "\tDelete User Screen";
        cout << "\n-----------------------------------\n";
        vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
        string Username = ReadUserUsername();
        DeleteUsersByUsername(Username, vUsers);
    }
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateUserScreen(sUser Session)
{
    if (!IsAccesed(Session.Permission, enManageUsersOptions::eUpdateUser))
    {
        ShowAccessDenidedScreen();
    }
    else
    {
        cout << "\n-----------------------------------\n";
        cout << "\tUpdate User Info Screen";
        cout << "\n-----------------------------------\n";
        vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
        string Username = ReadUserUsername();
        UpdateUserByUsername(Username, vUsers);
    }
}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClients();
}

void ShowAddNewUserScreen(sUser Session)
{
    if (!IsAccesed(Session.Permission, enManageUsersOptions::eAddNewUser))
    {
        ShowAccessDenidedScreen();
    }
    else
    {
        cout << "\n-----------------------------------\n";
        cout << "\tAdd New Users Screen";
        cout << "\n-----------------------------------\n";
        AddNewUsers();
    }
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients =
        LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber
             << "] is not found!";
}

void ShowFindUserScreen(sUser Session)
{
    if (!IsAccesed(Session.Permission, enManageUsersOptions::eFindUser))
    {
        ShowAccessDenidedScreen();
    }
    else
    {

        cout << "\n-----------------------------------\n";
        cout << "\tFind User Screen";
        cout << "\n-----------------------------------\n";
        vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
        sUser User;
        string Username = ReadUserUsername();
        if (FindUserByUsername(Username, vUsers, User))
            PrintUserCard(User);
        else
            cout << "\nUser with Username[" << Username << "] is not found!";
    }
}

bool UserExist(const string Username, const string Password, const string FileName, sUser &User)
{
    fstream Myfile(FileName, ios::in);

    if (!Myfile.is_open())
    {
        cerr << "Error: Could not open file " << FileName << "!\n";
        return false;
    }

    string Line;

    while (getline(Myfile, Line))
    {
        User = ConvertLineToRecord(Line);

        if (User.Username == Username && User.Password == Password)
        {
            Myfile.close();
            return true;
        }
    }

    Myfile.close();
    return false;
}

sUser ReadExistUser()
{
    sUser User;
    bool isExist;
    do
    {
        User.Username = ReadUserUsername();
        User.Password = ReadUserPassword();

        isExist = UserExist(User.Username, User.Password, UsersFileName, User);

        if (!isExist)
            cout << "\nInvalid username or password";
    } while (!isExist);

    return User;
}

void PerformLogin()
{
    UserSession = ReadExistUser();
    ShowMainMenue();
    system("pause>0");
}

void ShowLoginScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tLogin Screen\n";
    cout << "===========================================\n";
    PerformLogin();
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n ";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double Amount = 0;
    cout << "\nPlease enter deposit amount? ";
    cin >> Amount;
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";
    sClient Client;
    vector<sClient> vClients =
        LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n ";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double Amount = 0;
    cout << "\nPlease enter withdraw amount? ";
    cin >> Amount;
    // Validate that the amount does not exceeds the balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout
            << "Please enter another amount? ";
        cin >> Amount;
    }
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void ShowTotalBalancesScreen()
{
    ShowTotalBalances();
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue... ";
    system("pause>0");
    ShowTransactionsMenue();
}

void GoBackToManageUsersMenue()
{
    cout << "\n\nPress any key to go back to Manage Users Menue... ";
    system("pause>0");
    ShowManageUsersMenu();
}

short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

short ReadManageUsersMenueOption()
{
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }
    case enTransactionsMenueOptions::eShowMainMenue:
    {
        ShowMainMenue();
    }
    }
}

void PerfromManageUsersMenueOption(enManageUsersOptions ManageUsersMenuOption)
{
    switch (ManageUsersMenuOption)
    {
    case enManageUsersOptions::eListUsers:
    {
        system("cls");
        ShowAllUsersScreen(UserSession);
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eAddNewUser:
    {
        system("cls");
        ShowAddNewUserScreen(UserSession);
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eDeleteUser:
    {
        system("cls");
        ShowDeleteUserScreen(UserSession);
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eUpdateUser:
    {
        system("cls");
        ShowUpdateUserScreen(UserSession);
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eFindUser:
    {
        system("cls");
        ShowFindUserScreen(UserSession);
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eMainMenu:
    {
        ShowMainMenue();
    }
    }
}

void ShowTransactionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

void ShowManageUsersMenu()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "===========================================\n";
    PerfromManageUsersMenueOption((enManageUsersOptions)ReadManageUsersMenueOption());
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eShowTransactionsMenue:
        system("cls");
        ShowTransactionsMenue();
        break;
    case enMainMenueOptions::eManageUsers:
        system("cls");
        ShowManageUsersMenu();
        break;
    case enMainMenueOptions::eLogOut:
        system("cls");
        ShowLoginScreen();
        break;
    }
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] LogOut.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

int main()
{
    ShowLoginScreen();
    system("pause");
    return 0;
}