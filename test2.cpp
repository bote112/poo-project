#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib> // for system("clear")

using namespace std;

#include <cstring>
#include <iostream>


// Clasa inlocuitoare pentru std::string
class MyString {
public:
    MyString() : m_data(nullptr), m_size(0) {}

    MyString(const char* str) : m_data(nullptr), m_size(0) {
        if (str) {
            m_size = strlen(str);
            m_data = new char[m_size + 1];
            strcpy_s(m_data, m_size + 1, str);
        }
    }

    MyString(const MyString& other) : m_data(nullptr), m_size(0) {
        if (other.m_data) {
            m_size = other.m_size;
            m_data = new char[m_size + 1];
            strcpy_s(m_data, m_size + 1, other.m_data);
        }
    }

    MyString(MyString&& other) noexcept : m_data(other.m_data), m_size(other.m_size) {
        other.m_data = nullptr;
        other.m_size = 0;
    }

    ~MyString() {
        delete[] m_data;
    }

    MyString& operator=(const char* str) {
        if (m_data) {
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
        }
        if (str) {
            m_size = strlen(str);
            m_data = new char[m_size + 1];
            strcpy_s(m_data, m_size + 1, str);
        }
        return *this;
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            if (m_data) {
                delete[] m_data;
                m_data = nullptr;
                m_size = 0;
            }
            if (other.m_data) {
                m_size = other.m_size;
                m_data = new char[m_size + 1];
                strcpy_s(m_data, m_size + 1, other.m_data);
            }
        }
        return *this;
    }

    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            if (m_data) {
                delete[] m_data;
                m_data = nullptr;
                m_size = 0;
            }
            m_data = other.m_data;
            m_size = other.m_size;
            other.m_data = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    char& operator[](int index) {
        return m_data[index];
    }

    const char& operator[](int index) const {
        return m_data[index];
    }

    bool operator==(const MyString& other) const {
        return (m_size == other.m_size && strcmp(m_data, other.m_data) == 0);
    }

    bool operator!=(const MyString& other) const {
        return !(*this == other);
    }

    size_t size() const {
        return m_size;
    }

    const char* c_str() const {
        return m_data;
    }

    void clear() {
        if (m_data) {
            delete[] m_data;
            m_data = nullptr;
            m_size = 0;
        }
    }

private:
    char* m_data;
    size_t m_size;
};

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    os << str.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str) {
    char buffer[1024];
    is >> buffer;
    str = buffer;
    return is;
}




// Clasa pentru jucătorul de basket
class Player {
private:
    MyString name;
    int age;
    MyString position;
public:
    Player(MyString name, int age, MyString position) {
        this->name = name;
        this->age = age;
        this->position = position;
    }
    MyString getName() const { return name; }
    int getAge() const { return age; }
    MyString getPosition() const { return position; }
};

// Clasa pentru echipa de basket
class Team {
private:
    MyString name;
    Player* players[10]; // maximum of 10 players per team
    int numPlayers;
    int maxPlayers;
    int wins;
    int losses;
public:
    Team(MyString name) {
        this->name = name;
        this->wins = 0;
        this->losses = 0;
        this->numPlayers = 0;
        this->maxPlayers = 10;
        std::memset(players, 0, sizeof(players));
    }
    MyString getName() const { return name; }
    const Player** getPlayers() const { return (const Player**)players; }
    int getNumPlayers() const { return numPlayers; }
    int getWins() const { return wins; }
    int getLosses() const { return losses; }
    void addWin() { wins++; }
    void addLoss() { losses++; }
    void addPlayer(Player* player) {
        if (numPlayers < maxPlayers) {
            players[numPlayers++] = player;
        }
    }
};

// Clasa pentru meciul de basket
class Game {
private:
    Team* team1;
    Team* team2;
    int score1;
    int score2;
public:
    Game(Team* team1, Team* team2) {
        this->team1 = team1;
        this->team2 = team2;
        score1 = 0;
        score2 = 0;
    }
    Team* getTeam1() const { return team1; }
    Team* getTeam2() const { return team2; }
    int getScore1() const { return score1; }
    int getScore2() const { return score2; }
    void setScore1(int score) { score1 = score; }
    void setScore2(int score) { score2 = score; }
    // Method to determine the winner and update the wins/losses of each team
    void updateStats() {
        if (score1 > score2) {
            team1->addWin();
            team2->addLoss();
        }
        else if (score2 > score1) {
            team2->addWin();
            team1->addLoss();
        }
    }
};


// Clasa pentru turneul de basket
class Tournament {
private:
    MyString name;
    Game** games;
    int numGames;
    int maxGames;
    Team** teams;
    int numTeams;
    int maxTeams;
public:
    Tournament(MyString name, int maxTeams, int maxGames) {
        this->name = name;
        this->numTeams = 0;
        this->maxTeams = maxTeams;
        this->teams = new Team * [maxTeams];
        this->numGames = 0;
        this->maxGames = maxGames;
        this->games = new Game * [maxGames];
    }

    ~Tournament() {
        for (int i = 0; i < numGames; i++) {
            delete games[i];
        }
        delete[] games;
        for (int i = 0; i < numTeams; i++) {
            delete teams[i];
        }
        delete[] teams;
    }

    const MyString& getName() const {
        return name;
    }

    int getNumTeams() const {
        return numTeams;
    }

    int getNumGames() const {
        return numGames;
    }

    bool addTeam(Team* team) {
        if (numTeams >= maxTeams) {
            return false;
        }
        teams[numTeams++] = team;
        return true;
    }

    bool addGame(Game* game) {
        if (numGames >= maxGames) {
            return false;
        }
        games[numGames++] = game;
        return true;
    }

    const Team** getTeams() const {
        return (const Team**)teams;
    }

    const Game** getGames() const {
        return (const Game**)games;
    }

    void play() {
        for (int i = 0; i < numGames; i++) {
            games[i]->updateStats();
        }
    }
};


void creareEchipe() {
    MyString lakersName("Los Angeles Lakers");
    Team lakers(lakersName);
    lakers.addPlayer(new Player(MyString("LeBron James"), 37, MyString("SF")));
    lakers.addPlayer(new Player(MyString("Anthony Davis"), 28, MyString("PF")));
    lakers.addPlayer(new Player(MyString("Russell Westbrook"), 33, MyString("PG")));
    lakers.addPlayer(new Player(MyString("Carmelo Anthony"), 37, MyString("SF")));
    lakers.addPlayer(new Player(MyString("Dwight Howard"), 36, MyString("C")));

    MyString clippersName("Los Angeles Clippers");
    Team clippers(clippersName);
    clippers.addPlayer(new Player(MyString("Kawhi Leonard"), 30, MyString("SF")));
    clippers.addPlayer(new Player(MyString("Paul George"), 31, MyString("SG")));
    clippers.addPlayer(new Player(MyString("Serge Ibaka"), 32, MyString("PF")));
    clippers.addPlayer(new Player(MyString("Reggie Jackson"), 31, MyString("PG")));
    clippers.addPlayer(new Player(MyString("Marcus Morris"), 32, MyString("PF")));

    MyString bucksName("Milwaukee Bucks");
    Team bucks(bucksName);
    bucks.addPlayer(new Player(MyString("Giannis Antetokounmpo"), 27, MyString("PF")));
    bucks.addPlayer(new Player(MyString("Khris Middleton"), 30, MyString("SF")));
    bucks.addPlayer(new Player(MyString("Jrue Holiday"), 31, MyString("PG")));
    bucks.addPlayer(new Player(MyString("Brook Lopez"), 33, MyString("C")));
    bucks.addPlayer(new Player(MyString("Pat Connaughton"), 28, MyString("SG")));

    MyString netsName("Brooklyn Nets");
    Team nets(netsName);
    nets.addPlayer(new Player(MyString("Kevin Durant"), 33, MyString("SF")));
    nets.addPlayer(new Player(MyString("James Harden"), 32, MyString("SG")));
    nets.addPlayer(new Player(MyString("Kyrie Irving"), 29, MyString("PG")));
    nets.addPlayer(new Player(MyString("Blake Griffin"), 32, MyString("PF")));
    nets.addPlayer(new Player(MyString("LaMarcus Aldridge"), 36, MyString("C")));

    MyString sixersName("Philadelphia 76ers");
    Team sixers(sixersName);
    sixers.addPlayer(new Player(MyString("Joel Embiid"), 27, MyString("C")));
    sixers.addPlayer(new Player(MyString("Ben Simmons"), 24, MyString("PG")));
    sixers.addPlayer(new Player(MyString("Tobias Harris"), 28, MyString("SF")));
    sixers.addPlayer(new Player(MyString("Seth Curry"), 31, MyString("SG")));
    sixers.addPlayer(new Player(MyString("Danny Green"), 34, MyString("SF")));

    MyString warriorsName("Golden State Warriors");
    Team warriors(warriorsName);
    warriors.addPlayer(new Player(MyString("Stephen Curry"), 33, MyString("PG")));
    warriors.addPlayer(new Player(MyString("Klay Thompson"), 31, MyString("SG")));
    warriors.addPlayer(new Player(MyString("Draymond Green"), 31, MyString("PF")));
    warriors.addPlayer(new Player(MyString("Andrew Wiggins"), 26, MyString("SF")));
    warriors.addPlayer(new Player(MyString("James Wiseman"), 20, MyString("C")));

}


int main() {

    MyString lakersName("Los Angeles Lakers");
    Team lakers(lakersName);
    lakers.addPlayer(new Player(MyString("LeBron James"), 37, MyString("SF")));
    lakers.addPlayer(new Player(MyString("Anthony Davis"), 28, MyString("PF")));
    lakers.addPlayer(new Player(MyString("Russell Westbrook"), 33, MyString("PG")));
    lakers.addPlayer(new Player(MyString("Carmelo Anthony"), 37, MyString("SF")));
    lakers.addPlayer(new Player(MyString("Dwight Howard"), 36, MyString("C")));

    MyString clippersName("Los Angeles Clippers");
    Team clippers(clippersName);
    clippers.addPlayer(new Player(MyString("Kawhi Leonard"), 30, MyString("SF")));
    clippers.addPlayer(new Player(MyString("Paul George"), 31, MyString("SG")));
    clippers.addPlayer(new Player(MyString("Serge Ibaka"), 32, MyString("PF")));
    clippers.addPlayer(new Player(MyString("Reggie Jackson"), 31, MyString("PG")));
    clippers.addPlayer(new Player(MyString("Marcus Morris"), 32, MyString("PF")));

    MyString bucksName("Milwaukee Bucks");
    Team bucks(bucksName);
    bucks.addPlayer(new Player(MyString("Giannis Antetokounmpo"), 27, MyString("PF")));
    bucks.addPlayer(new Player(MyString("Khris Middleton"), 30, MyString("SF")));
    bucks.addPlayer(new Player(MyString("Jrue Holiday"), 31, MyString("PG")));
    bucks.addPlayer(new Player(MyString("Brook Lopez"), 33, MyString("C")));
    bucks.addPlayer(new Player(MyString("Pat Connaughton"), 28, MyString("SG")));

    MyString netsName("Brooklyn Nets");
    Team nets(netsName);
    nets.addPlayer(new Player(MyString("Kevin Durant"), 33, MyString("SF")));
    nets.addPlayer(new Player(MyString("James Harden"), 32, MyString("SG")));
    nets.addPlayer(new Player(MyString("Kyrie Irving"), 29, MyString("PG")));
    nets.addPlayer(new Player(MyString("Blake Griffin"), 32, MyString("PF")));
    nets.addPlayer(new Player(MyString("LaMarcus Aldridge"), 36, MyString("C")));

    MyString sixersName("Philadelphia 76ers");
    Team sixers(sixersName);
    sixers.addPlayer(new Player(MyString("Joel Embiid"), 27, MyString("C")));
    sixers.addPlayer(new Player(MyString("Ben Simmons"), 24, MyString("PG")));
    sixers.addPlayer(new Player(MyString("Tobias Harris"), 28, MyString("SF")));
    sixers.addPlayer(new Player(MyString("Seth Curry"), 31, MyString("SG")));
    sixers.addPlayer(new Player(MyString("Danny Green"), 34, MyString("SF")));

    MyString warriorsName("Golden State Warriors");
    Team warriors(warriorsName);
    warriors.addPlayer(new Player(MyString("Stephen Curry"), 33, MyString("PG")));
    warriors.addPlayer(new Player(MyString("Klay Thompson"), 31, MyString("SG")));
    warriors.addPlayer(new Player(MyString("Draymond Green"), 31, MyString("PF")));
    warriors.addPlayer(new Player(MyString("Andrew Wiggins"), 26, MyString("SF")));
    warriors.addPlayer(new Player(MyString("James Wiseman"), 20, MyString("C")));

    // Create the tournament
    const char* tournamentName = "NBA Tournament";
    MyString name(tournamentName);
    Tournament tournament("name", 10, 15);
    tournament.addTeam(&lakers);
    tournament.addTeam(&clippers);
    tournament.addTeam(&bucks);
    tournament.addTeam(&nets);
    tournament.addTeam(&sixers);
    tournament.addTeam(&warriors);

    // Simulate the games
    Game game1(&lakers, &clippers);
    game1.setScore1(105);
    game1.setScore2(100);
    game1.updateStats();

    Game game2(&bucks, &nets);
    game2.setScore1(120);
    game2.setScore2(115);
    game2.updateStats();

    Game game3(&sixers, &warriors);
    game3.setScore1(110);
    game3.setScore2(95);
    game3.updateStats();

    Game game4(&lakers, &nets);
    game4.setScore1(112);
    game4.setScore2(108);
    game4.updateStats();

    Game game5(&bucks, &warriors);
    game5.setScore1(118);
    game5.setScore2(105);
    game5.updateStats();

    Game game6(&clippers, &sixers);
    game6.setScore1(100);
    game6.setScore2(95);
    game6.updateStats();

    Game game7(&lakers, &warriors);
    game7.setScore1(105);
    game7.setScore2(98);
    game7.updateStats();

    Game game8(&clippers, &bucks);
    game8.setScore1(110);
    game8.setScore2(108);
    game8.updateStats();

    Game game9(&nets, &sixers);
    game9.setScore1(120);
    game9.setScore2(115);
    game9.updateStats();

    // Print the final standings
    std::cout << "Final Standings:" << std::endl;
    const Team** teams = tournament.getTeams();
    int numTeams = tournament.getNumTeams();
    for (int i = 0; i < numTeams; i++) {
        std::cout << teams[i]->getName() << ": " << teams[i]->getWins() << " wins, " << teams[i]->getLosses() << " losses" << std::endl;
    }

    return 0;
}
