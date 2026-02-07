#include <Windows.h>
#include <fstream>
#include <ShellAPI.h>
#include "File_writer.h"
void File_writer::save_to_file(std::vector <TrencchCoat> coats) {
    std::ofstream file("basket.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }
    for (const auto& coat : coats) {
        file << coat;
    }

    file.close();
}

void File_writer::open_file() {
    ShellExecute(NULL, reinterpret_cast<LPCWSTR>("open"), reinterpret_cast<LPCWSTR>("basket.txt"), NULL, NULL, SW_SHOWNORMAL);
    system("PAUSE");
}

void CSV_file::open_file() {
    LPCTSTR helpFile = LPCTSTR("basket.csv");
    ShellExecute(NULL, LPCWSTR("open"), helpFile, NULL, NULL, SW_SHOWNORMAL);
    system("PAUSE");
}



void CSV_file::save_to_file(std::vector <TrencchCoat> coats) {


        ofstream f("basket.csv");
        if (!f.is_open())
        {std::cerr << "Error: Unable to open file for writing." << std::endl;
            return;}

        for (auto &coat : coats)
        {
            f << coat;
        }
        f.close();

}

void HTML_file::open_file() {
    LPCTSTR helpFile = LPCTSTR("basket.html");
    ShellExecute(NULL, LPCWSTR("open"), helpFile, NULL, NULL, SW_SHOWNORMAL);

}
void HTML_file::save_to_file(std::vector<TrencchCoat> coats) {

    ofstream f("basket.html");	// will append data
    if (!f.is_open())
    {std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;}

    f << "<!DOCTYPE html>\n";
    f << "<html>\n";
    f << "<head>\n";
    f << "<title>Coats</title>\n";
    f << "</head>\n";
    f << "<body>\n";
    f << "<table border=\"1\">\n";
    f << "<tr>\n";
    f << "<td>Size</td>\n";
    f << "<td>Color</td>\n";
    f << "<td>Price</td>\n";
    f << "<td>Quantity</td>\n";
    f << "<td>Photograph</td>\n";
    f << "</tr>\n";
    for (auto &coat : coats)
    {
        f << "<tr>\n";
        f << "<td>" << coat.getSize() << "</td>\n";
        f << "<td>" << coat.getColor() << "</td>\n";
        f << "<td>" << coat.getPrice() << "</td>\n";
        f << "<td>" << coat.getQuantity() << "</td>\n";
        f << "<td>" << coat.getPhotograph() << "</td>\n";
        f << "</tr>\n";
    }
    f << "</table>\n";
    f << "</body>\n";
    f << "</html>\n";
    f.close();


}

void sql_file::save_to_file(std::vector<TrencchCoat> coats) {

    ofstream f("basket.sql");
    if (!f.is_open())
    {std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;}

    for (auto &coat : coats)
    {
        f << "INSERT INTO coats (size, color, price, quantity, photograph) VALUES (";
        f << "\"" << coat.getSize() << "\", ";
        f << "\"" << coat.getColor() << "\", ";
        f << coat.getPrice() << ", ";
        f << coat.getQuantity() << ", ";
        f << "\"" << coat.getPhotograph() << "\");\n";
    }
    f.close();

}

void sql_file::open_file() {

}
