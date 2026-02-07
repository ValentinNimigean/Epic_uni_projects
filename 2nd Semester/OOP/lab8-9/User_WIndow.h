

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "Controller.h"
#include "Graph_window.h"

class UserWindow : public QWidget {
Q_OBJECT

public:
    UserWindow(Controller* service, QWidget *parent = nullptr);
    ~UserWindow();

private slots:
    void onViewTrenchCoatsBySize();
    void onAddToBasket();
    void onViewBasket();
    void onNextCoat();
    void onPreviousCoat();

private:
    void setupUi();
    void displayCurrentCoat();

    Controller* service;
    std::vector<TrencchCoat> displayedCoats;
    std::vector<TrencchCoat> basket;
    double totalPrice;
    int currentIndex;

    QLabel* sizeLabel;
    QLabel* colorLabel;
    QLabel* priceLabel;
    QLabel* quantityLabel;
    QLabel* photoLabel;
    QPushButton* nextButton;
    QPushButton* previousButton;
    QPushButton* addToBasketButton;
    Size_Chart* chart;

    void show_chart();
};
