

#include <string>
#include <vector>
#include <sqlite3.h>
#include "Domain.h"

class SQLiteRepository {
private:


    sqlite3* db;
    std::string db_file;

    void executeQuery(const std::string& query) const;
    static int callback(void* data, int argc, char** argv, char** azColName);

public:
    // Constructor
    SQLiteRepository();
    SQLiteRepository(const std::string& db_file);

    // Destructor
    ~SQLiteRepository();

    // Adds a coat to the repository
    void addCoat_repo(const TrencchCoat& e);

    // Removes a coat from the repository
    void removeCoat_repo(const std::string& photo);

    // Updates a coat in the repository
    void updateCoat_repo(const std::string& photo, const TrencchCoat& new_coat);

    // Finds a coat in the repository
    int findCoat_repo(const std::string& photo);

    // Returns all coats
    std::vector<TrencchCoat> getCoats() const;

    // Reads from file (SQLite database)
    void readFromFile(const std::string& filename);

    // Saves to file (SQLite database)
    void saveToFile(const std::string& filename);
};

