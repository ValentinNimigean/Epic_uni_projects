
#include "Controller.h"
#include <QMainWindow>

class MainWindow : public QMainWindow {
Q_OBJECT

public:

    MainWindow(Controller *service, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAdminMode();
    void onUserMode();

private:
    void setupUi();

    Controller *service;

    void onGraphMode();
};
