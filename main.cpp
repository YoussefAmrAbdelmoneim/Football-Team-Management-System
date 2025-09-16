#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
using namespace std;

class teamNode {
public:
    int ID;
    string Name, President;
    teamNode* tNext;
    
    teamNode(int id, string name, string president) 
        : ID(id), Name(name), President(president), tNext(nullptr) {}
};

class playerNode {
public:
    int ID, Age;
    double Salary;
    string Name, Position;
    int teamID;
    playerNode* pNext;
    
    playerNode(int id, string name, int teamid, string position, int age, double salary)
        : ID(id), Name(name), teamID(teamid), Position(position), Age(age), Salary(salary), pNext(nullptr) {}
};

class teamList {
private:
    teamNode* tHead;
    int teamCount;
    
public:
    teamList() : tHead(nullptr), teamCount(0) {}
    ~teamList() {
        clearTeams();
    }
    
    bool isEmpty() const {
        return tHead == nullptr;
    }
    
    int getTeamCount() const {
        return teamCount;
    }
    
    void addNewTeam(int id, string name, string president) {
        if (searchTeam(id)) {
            cout << "Team with ID " << id << " already exists!" << endl;
            return;
        }
        
        teamNode* newTeamNode = new teamNode(id, name, president);
        newTeamNode->tNext = tHead;
        tHead = newTeamNode;
        teamCount++;
        
        cout << "\nTeam: " << name << " added successfully." << endl;
    }
    
    void displayTeam() const {
        if (isEmpty()) {
            cout << "============================================" << endl;
            cout << "          No Teams Exist Yet" << endl;
            cout << "============================================" << endl;
            return;
        }
        
        cout << "============================================" << endl;
        cout << "               LIST OF TEAMS" << endl;
        cout << "============================================" << endl;
        
        teamNode* temp = tHead;
        while (temp != nullptr) {
            cout << "   Team ID: " << temp->ID << endl;
            cout << "   Team Name: " << temp->Name << endl;
            cout << "   Team President: " << temp->President << endl;
            cout << "============================================" << endl;
            temp = temp->tNext;
        }
    }
    
    bool searchTeam(int id) const {
        teamNode* temp = tHead;
        while (temp != nullptr) {
            if (temp->ID == id)
                return true;
            temp = temp->tNext;
        }
        return false;
    }
    
    teamNode* getTeam(int id) const {
        teamNode* temp = tHead;
        while (temp != nullptr) {
            if (temp->ID == id)
                return temp;
            temp = temp->tNext;
        }
        return nullptr;
    }
    
    void deleteTeam(int id) {
        if (isEmpty()) {
            cout << "There aren't any teams to be deleted." << endl;
            return;
        }
        
        if (!searchTeam(id)) {
            cout << "Team with ID " << id << " not found." << endl;
            return;
        }
        
        teamNode* delptr = nullptr;
        if (tHead->ID == id) {
            delptr = tHead;
            tHead = tHead->tNext;
        } else {
            teamNode* prev = tHead;
            while (prev->tNext != nullptr && prev->tNext->ID != id) {
                prev = prev->tNext;
            }
            if (prev->tNext != nullptr) {
                delptr = prev->tNext;
                prev->tNext = delptr->tNext;
            }
        }
        
        if (delptr != nullptr) {
            cout << "Team: " << delptr->Name << " (ID: " << delptr->ID << ") has been deleted." << endl;
            delete delptr;
            teamCount--;
        }
    }
    
    void updateTeamInfo(int id, string name, string president) {
        teamNode* team = getTeam(id);
        if (team == nullptr) {
            cout << "Team with ID " << id << " not found." << endl;
            return;
        }
        
        team->Name = name;
        team->President = president;
        cout << "Team information updated successfully." << endl;
    }
    
    bool containsInteger(const string& str) const {
        for (char ch : str) {
            if (ch >= '0' && ch <= '9') {
                return true;
            }
        }
        return false;
    }
    
    string getTeamName(int id) const {
        teamNode* team = getTeam(id);
        if (team != nullptr)
            return team->Name;
        return "Unknown Team";
    }
    
    void clearTeams() {
        while (tHead != nullptr) {
            teamNode* temp = tHead;
            tHead = tHead->tNext;
            delete temp;
        }
        teamCount = 0;
    }
    
    vector<teamNode*> getAllTeams() const {
        vector<teamNode*> teams;
        teamNode* temp = tHead;
        while (temp != nullptr) {
            teams.push_back(temp);
            temp = temp->tNext;
        }
        return teams;
    }
};

class playerList {
private:
    playerNode* pHead;
    int playerCount;
    
public:
    playerList() : pHead(nullptr), playerCount(0) {}
    ~playerList() {
        clearPlayers();
    }
    
    bool isEmpty() const {
        return pHead == nullptr;
    }
    
    int getPlayerCount() const {
        return playerCount;
    }
    
    void addNewPlayer(int id, string name, int teamid, string position, int age, double salary, const teamList& teams) {
        if (!teams.searchTeam(teamid)) {
            cout << "Team ID " << teamid << " not found. Player not added." << endl;
            return;
        }
        
        if (searchPlayerByID(id)) {
            cout << "Player with ID " << id << " already exists!" << endl;
            return;
        }
        
        playerNode* newPlayerNode = new playerNode(id, name, teamid, position, age, salary);
        newPlayerNode->pNext = pHead;
        pHead = newPlayerNode;
        playerCount++;
        
        cout << "Player: " << name << " added successfully to team " << teams.getTeamName(teamid) << "." << endl;
    }
    
    void displayPlayersByTeam(int teamid, const teamList& teams) const {
        if (isEmpty()) {
            cout << "============================================" << endl;
            cout << "     No Players Exist in This Team Yet" << endl;
            cout << "============================================" << endl;
            return;
        }
        
        if (!teams.searchTeam(teamid)) {
            cout << "Team ID " << teamid << " not found." << endl;
            return;
        }
        
        string teamName = teams.getTeamName(teamid);
        cout << "============================================" << endl;
        cout << "   Players of Team: " << teamName << " (ID: " << teamid << ")" << endl;
        cout << "============================================" << endl;
        
        playerNode* temp = pHead;
        bool found = false;
        
        while (temp != nullptr) {
            if (temp->teamID == teamid) {
                found = true;
                cout << "   Player Name: " << temp->Name << endl;
                cout << "   Player ID: " << temp->ID << endl;
                cout << "   Position: " << temp->Position << endl;
                cout << "   Age: " << temp->Age << " years" << endl;
                cout << "   Salary: " << fixed << setprecision(2) << temp->Salary << " EGP" << endl;
                cout << "============================================" << endl;
            }
            temp = temp->pNext;
        }
        
        if (!found) {
            cout << "   No players found for this team." << endl;
            cout << "============================================" << endl;
        }
    }
    
    bool searchPlayer(const string& name) const {
        playerNode* temp = pHead;
        while (temp != nullptr) {
            if (temp->Name == name)
                return true;
            temp = temp->pNext;
        }
        return false;
    }
    
    bool searchPlayerByID(int id) const {
        playerNode* temp = pHead;
        while (temp != nullptr) {
            if (temp->ID == id)
                return true;
            temp = temp->pNext;
        }
        return false;
    }
    
    void deletePlayer(int id) {
        if (isEmpty()) {
            cout << "There aren't any players to be deleted." << endl;
            return;
        }
        
        if (!searchPlayerByID(id)) {
            cout << "Player with ID " << id << " not found." << endl;
            return;
        }
        
        playerNode* delptr = nullptr;
        if (pHead->ID == id) {
            delptr = pHead;
            pHead = pHead->pNext;
        } else {
            playerNode* prev = pHead;
            while (prev->pNext != nullptr && prev->pNext->ID != id) {
                prev = prev->pNext;
            }
            if (prev->pNext != nullptr) {
                delptr = prev->pNext;
                prev->pNext = delptr->pNext;
            }
        }
        
        if (delptr != nullptr) {
            cout << "Player: " << delptr->Name << " (ID: " << delptr->ID << ") has been removed." << endl;
            delete delptr;
            playerCount--;
        }
    }
    
    void displayPlayersBySalary(int teamid, const teamList& teams) const {
        if (isEmpty()) {
            cout << "============================================" << endl;
            cout << "     No Players Exist in This Team Yet" << endl;
            cout << "============================================" << endl;
            return;
        }
        
        if (!teams.searchTeam(teamid)) {
            cout << "Team ID " << teamid << " not found." << endl;
            return;
        }
        
        // Create a vector of players for the specified team
        vector<playerNode*> players;
        playerNode* temp = pHead;
        while (temp != nullptr) {
            if (temp->teamID == teamid) {
                players.push_back(temp);
            }
            temp = temp->pNext;
        }
        
        if (players.empty()) {
            cout << "============================================" << endl;
            cout << "     No Players Exist in This Team Yet" << endl;
            cout << "============================================" << endl;
            return;
        }
        
        // Sort players by salary (descending order)
        sort(players.begin(), players.end(), [](playerNode* a, playerNode* b) {
            return a->Salary > b->Salary;
        });
        
        string teamName = teams.getTeamName(teamid);
        cout << "============================================" << endl;
        cout << " Players of " << teamName << " by Salary (Highest to Lowest)" << endl;
        cout << "============================================" << endl;
        
        for (playerNode* player : players) {
            cout << "   Player Name: " << player->Name << endl;
            cout << "   Player ID: " << player->ID << endl;
            cout << "   Position: " << player->Position << endl;
            cout << "   Age: " << player->Age << " years" << endl;
            cout << "   Salary: " << fixed << setprecision(2) << player->Salary << " EGP" << endl;
            cout << "============================================" << endl;
        }
    }
    
    double calculateAverageAge(int teamid) const {
        int totalAge = 0, playerCount = 0;
        playerNode* temp = pHead;
        
        while (temp != nullptr) {
            if (temp->teamID == teamid) {
                totalAge += temp->Age;
                playerCount++;
            }
            temp = temp->pNext;
        }
        
        return playerCount > 0 ? static_cast<double>(totalAge) / playerCount : 0.0;
    }
    
    void displayTeamsByAverageAge(const teamList& teams) const {
        if (isEmpty()) {
            cout << "============================================" << endl;
            cout << "        No Players Exist Yet" << endl;
            cout << "============================================" << endl;
            return;
        }
        
        // Get all teams
        vector<teamNode*> allTeams = teams.getAllTeams();
        if (allTeams.empty()) {
            cout << "No teams exist." << endl;
            return;
        }
        
        // Create a vector of pairs (team, average age)
        vector<pair<teamNode*, double>> teamAges;
        for (teamNode* team : allTeams) {
            double avgAge = calculateAverageAge(team->ID);
            teamAges.emplace_back(team, avgAge);
        }
        
        // Sort by average age (descending order) using merge sort algorithm
        mergeSort(teamAges, 0, teamAges.size() - 1);
        
        cout << "============================================" << endl;
        cout << "       Teams by Average Player Age" << endl;
        cout << "============================================" << endl;
        
        for (const auto& pair : teamAges) {
            teamNode* team = pair.first;
            double avgAge = pair.second;
            
            cout << "   Team: " << team->Name << endl;
            cout << "   President: " << team->President << endl;
            cout << "   Average Age: " << fixed << setprecision(1) << avgAge << " years" << endl;
            cout << "============================================" << endl;
        }
    }
    
    void displayAllPlayers(const teamList& teams) const {
        if (isEmpty()) {
            cout << "============================================" << endl;
            cout << "          No Players Exist Yet" << endl;
            cout << "============================================" << endl;
            return;
        }
        
        cout << "============================================" << endl;
        cout << "            ALL PLAYERS" << endl;
        cout << "============================================" << endl;
        
        playerNode* temp = pHead;
        while (temp != nullptr) {
            cout << "   Player Name: " << temp->Name << endl;
            cout << "   Player ID: " << temp->ID << endl;
            cout << "   Team: " << teams.getTeamName(temp->teamID) << endl;
            cout << "   Position: " << temp->Position << endl;
            cout << "   Age: " << temp->Age << " years" << endl;
            cout << "   Salary: " << fixed << setprecision(2) << temp->Salary << " EGP" << endl;
            cout << "============================================" << endl;
            temp = temp->pNext;
        }
    }
    
    int getPlayerCountByTeam(int teamid) const {
        int count = 0;
        playerNode* temp = pHead;
        while (temp != nullptr) {
            if (temp->teamID == teamid) {
                count++;
            }
            temp = temp->pNext;
        }
        return count;
    }
    
    double getTotalSalaryByTeam(int teamid) const {
        double total = 0;
        playerNode* temp = pHead;
        while (temp != nullptr) {
            if (temp->teamID == teamid) {
                total += temp->Salary;
            }
            temp = temp->pNext;
        }
        return total;
    }
    
private:
    void mergeSort(vector<pair<teamNode*, double>>& arr, int left, int right) const {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
    
    void merge(vector<pair<teamNode*, double>>& arr, int left, int mid, int right) const {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        vector<pair<teamNode*, double>> L(n1), R(n2);
        
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        
        while (i < n1 && j < n2) {
            if (L[i].second >= R[j].second) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    
    void clearPlayers() {
        while (pHead != nullptr) {
            playerNode* temp = pHead;
            pHead = pHead->pNext;
            delete temp;
        }
        playerCount = 0;
    }
};

// Utility functions for input validation
int getValidatedInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

double getValidatedDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0) {
            cout << "Invalid input. Please enter a valid positive number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string getValidatedString(const string& prompt, bool allowNumbers = true) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        
        if (value.empty()) {
            cout << "Input cannot be empty. Please try again." << endl;
            continue;
        }
        
        if (!allowNumbers) {
            bool hasDigit = false;
            for (char c : value) {
                if (isdigit(c)) {
                    hasDigit = true;
                    break;
                }
            }
            if (hasDigit) {
                cout << "Input should not contain numbers. Please try again." << endl;
                continue;
            }
        }
        
        return value;
    }
}

string getValidatedPosition() {
    string position;
    vector<string> validPositions = {"GK", "CB", "RB", "LB", "DMF", "CM", "CAM", "RW", "LW", "CF", "SS"};
    
    while (true) {
        cout << "Enter Player Position [GK-CB-RB-LB-DMF-CM-CAM-RW-LW-CF-SS]: ";
        getline(cin, position);
        
        for (const auto& validPos : validPositions) {
            if (position == validPos) {
                return position;
            }
        }
        
        cout << "Invalid position. Please choose from the allowed positions." << endl;
    }
}

void displayMainMenu() {
    cout << "\n============================================" << endl;
    cout << "     FOOTBALL TEAM MANAGEMENT SYSTEM" << endl;
    cout << "============================================" << endl;
    cout << "1. Add Team" << endl;
    cout << "2. Display All Teams" << endl;
    cout << "3. Search Team by ID" << endl;
    cout << "4. Add Player" << endl;
    cout << "5. Remove Player" << endl;
    cout << "6. Display Players of a Team" << endl;
    cout << "7. Display All Players" << endl;
    cout << "8. Display Players of a Team Ordered by Salary" << endl;
    cout << "9. Search Player by Name" << endl;
    cout << "10. Update Team Info" << endl;
    cout << "11. Remove Team" << endl;
    cout << "12. Display Teams Ordered by Average Age" << endl;
    cout << "13. Display Team Statistics" << endl;
    cout << "14. Exit" << endl;
    cout << "============================================" << endl;
    cout << "Enter your choice: ";
}

void displayTeamStats(const teamList& teams, const playerList& players) {
    if (teams.isEmpty()) {
        cout << "No teams exist yet." << endl;
        return;
    }
    
    int teamId = getValidatedInt("Enter Team ID to show statistics: ");
    
    if (!teams.searchTeam(teamId)) {
        cout << "Team with ID " << teamId << " not found." << endl;
        return;
    }
    
    string teamName = teams.getTeamName(teamId);
    int playerCount = players.getPlayerCountByTeam(teamId);
    double totalSalary = players.getTotalSalaryByTeam(teamId);
    double avgAge = players.calculateAverageAge(teamId);
    
    cout << "============================================" << endl;
    cout << "        STATISTICS FOR " << teamName << endl;
    cout << "============================================" << endl;
    cout << "   Total Players: " << playerCount << endl;
    cout << "   Total Salary: " << fixed << setprecision(2) << totalSalary << " EGP" << endl;
    cout << "   Average Salary: " << fixed << setprecision(2) << (playerCount > 0 ? totalSalary / playerCount : 0) << " EGP" << endl;
    cout << "   Average Age: " << fixed << setprecision(1) << avgAge << " years" << endl;
    cout << "============================================" << endl;
}

int main() {
    teamList teams;
    playerList players;
    int choice;
    
    cout << "Welcome to the Football Team Management System!" << endl;
    
    do {
        displayMainMenu();
        cin >> choice;
        
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number between 1 and 14." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (choice) {
            case 1: {
                int id = getValidatedInt("Enter Team ID: ");
                string name = getValidatedString("Enter Team Name: ");
                string president = getValidatedString("Enter Team President: ", false);
                teams.addNewTeam(id, name, president);
                break;
            }
            case 2:
                teams.displayTeam();
                break;
            case 3: {
                int id = getValidatedInt("Enter Team ID to search: ");
                if (teams.searchTeam(id)) {
                    cout << "Team found: " << teams.getTeamName(id) << endl;
                } else {
                    cout << "Team with ID " << id << " not found." << endl;
                }
                break;
            }
            case 4: {
                if (teams.isEmpty()) {
                    cout << "No teams exist yet. Please add a team first." << endl;
                    break;
                }
                
                int playerId = getValidatedInt("Enter Player ID: ");
                string playerName = getValidatedString("Enter Player Name: ", false);
                int teamId = getValidatedInt("Enter Team ID: ");
                string position = getValidatedPosition();
                int age = getValidatedInt("Enter Player Age: ");
                double salary = getValidatedDouble("Enter Player Salary: ");
                
                players.addNewPlayer(playerId, playerName, teamId, position, age, salary, teams);
                break;
            }
            case 5: {
                if (players.isEmpty()) {
                    cout << "No players exist yet." << endl;
                    break;
                }
                
                int playerId = getValidatedInt("Enter Player ID to remove: ");
                players.deletePlayer(playerId);
                break;
            }
            case 6: {
                if (teams.isEmpty()) {
                    cout << "No teams exist yet." << endl;
                    break;
                }
                
                int teamId = getValidatedInt("Enter Team ID to display players: ");
                players.displayPlayersByTeam(teamId, teams);
                break;
            }
            case 7:
                players.displayAllPlayers(teams);
                break;
            case 8: {
                if (teams.isEmpty()) {
                    cout << "No teams exist yet." << endl;
                    break;
                }
                
                int teamId = getValidatedInt("Enter Team ID to display players by salary: ");
                players.displayPlayersBySalary(teamId, teams);
                break;
            }
            case 9: {
                if (players.isEmpty()) {
                    cout << "No players exist yet." << endl;
                    break;
                }
                
                string name = getValidatedString("Enter Player Name to search: ");
                if (players.searchPlayer(name)) {
                    cout << "Player '" << name << "' found." << endl;
                } else {
                    cout << "Player '" << name << "' not found." << endl;
                }
                break;
            }
            case 10: {
                if (teams.isEmpty()) {
                    cout << "No teams exist yet." << endl;
                    break;
                }
                
                int teamId = getValidatedInt("Enter Team ID to update: ");
                if (teams.searchTeam(teamId)) {
                    string name = getValidatedString("Enter new Team Name: ");
                    string president = getValidatedString("Enter new Team President: ", false);
                    teams.updateTeamInfo(teamId, name, president);
                } else {
                    cout << "Team with ID " << teamId << " not found." << endl;
                }
                break;
            }
            case 11: {
                if (teams.isEmpty()) {
                    cout << "No teams exist yet." << endl;
                    break;
                }
                
                int teamId = getValidatedInt("Enter Team ID to remove: ");
                teams.deleteTeam(teamId);
                break;
            }
            case 12:
                players.displayTeamsByAverageAge(teams);
                break;
            case 13:
                displayTeamStats(teams, players);
                break;
            case 14:
                cout << "Thank you for using the Football Team Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 14." << endl;
                break;
        }
        
        if (choice != 14) {
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
    } while (choice != 14);
    
    return 0;
}