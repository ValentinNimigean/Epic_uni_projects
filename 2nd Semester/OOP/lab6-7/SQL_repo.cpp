
#include "SQL_repo.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

SQLiteRepository::SQLiteRepository() {
    if (sqlite3_open(":memory:", &db)) {
        throw std::runtime_error("Failed to open the database.");
    }
    std::string create_table_query = "CREATE TABLE IF NOT EXISTS TrenchCoats ("
                                     "Size TEXT, Color TEXT, Price REAL, Quantity INTEGER, PhotoURL TEXT PRIMARY KEY);";
    executeQuery(create_table_query);
}

SQLiteRepository::SQLiteRepository(const std::string& db_file) : db_file(db_file) {
    if (sqlite3_open(db_file.c_str(), &db)) {
        throw std::runtime_error("Failed to open the database.");
    }
    std::string create_table_query = "CREATE TABLE IF NOT EXISTS TrenchCoats ("
                                     "Size TEXT, Color TEXT, Price REAL, Quantity INTEGER, PhotoURL TEXT PRIMARY KEY);";
    executeQuery(create_table_query);
}

SQLiteRepository::~SQLiteRepository() {
    sqlite3_close(db);
}

void SQLiteRepository::executeQuery(const std::string& query) const {
    char* errorMessage = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::string error_str = errorMessage ? errorMessage : "Unknown error";
        sqlite3_free(errorMessage);
        throw std::runtime_error("SQL error: " + error_str);
    }
}

void SQLiteRepository::addCoat_repo(const TrencchCoat& e) {
    std::stringstream ss;
    ss << "INSERT INTO TrenchCoats (Size, Color, Price, Quantity, PhotoURL) VALUES ('"
       << e.getSize() << "', '" << e.getColor() << "', " << e.getPrice() << ", "
       << e.getQuantity() << ", '" << e.getPhotograph() << "');";
    executeQuery(ss.str());
}

void SQLiteRepository::removeCoat_repo(const std::string& photo) {
    std::stringstream ss;
    ss << "DELETE FROM TrenchCoats WHERE PhotoURL = '" << photo << "';";
    executeQuery(ss.str());
}

void SQLiteRepository::updateCoat_repo(const std::string& photo, const TrencchCoat& new_coat) {
    std::stringstream ss;
    ss << "UPDATE TrenchCoats SET Size = '" << new_coat.getSize() << "', Color = '"
       << new_coat.getColor() << "', Price = " << new_coat.getPrice() << ", Quantity = "
       << new_coat.getQuantity() << ", PhotoURL = '" << new_coat.getPhotograph()
       << "' WHERE PhotoURL = '" << photo << "';";
    executeQuery(ss.str());
}

int SQLiteRepository::findCoat_repo(const std::string& photo) {
    std::string query = "SELECT COUNT(*) FROM TrenchCoats WHERE PhotoURL = '" + photo + "';";
    int count = 0;
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        int* count = static_cast<int*>(data);
        if (argc > 0 && argv[0]) {
            *count = std::stoi(argv[0]);
        }
        return 0;
    };
    sqlite3_exec(db, query.c_str(), callback, &count, nullptr);
    return count;
}

std::vector<TrencchCoat> SQLiteRepository::getCoats() const {
    std::vector<TrencchCoat> coats;
    std::string query = "SELECT * FROM TrenchCoats;";
    sqlite3_exec(db, query.c_str(), callback, &coats, nullptr);
    return coats;
}

int SQLiteRepository::callback(void* data, int argc, char** argv, char** azColName) {
    auto* coats = static_cast<std::vector<TrencchCoat>*>(data);
    std::string size = argv[0] ? argv[0] : "";
    std::string color = argv[1] ? argv[1] : "";
    double price = argv[2] ? std::stod(argv[2]) : 0.0;
    int quantity = argv[3] ? std::stoi(argv[3]) : 0;
    std::string photo_url = argv[4] ? argv[4] : "";
    coats->emplace_back(size, color, price, quantity, photo_url);
    return 0;
}

void SQLiteRepository::readFromFile(const std::string& filename) {
    // SQLite database handles data persistence automatically
    // This function might not be necessary
}

void SQLiteRepository::saveToFile(const std::string& filename) {
    // SQLite database handles data persistence automatically
    // This function might not be necessary
}