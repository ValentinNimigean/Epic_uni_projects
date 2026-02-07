//
// Created by valen on 3/26/2024.
//
#include "Domain.h"
#include <iostream>
#include <cstring>
#include "Repository.h"
#include "Controller.h"
#include "User_interface.h"
#include "Tests.h"

#include "Principal_window.h"
#include <QtWidgets/QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>

int main(int argc, char* argv[]){
    QApplication a(argc, argv);
    QDialog question;
    question.setWindowTitle("Basket type");
    QVBoxLayout layout(&question);
    QPushButton* button1 = new QPushButton("CSV?");
    QPushButton* button2 = new QPushButton("HTML?");
    layout.addWidget(button1);
    layout.addWidget(button2);
    File_writer* file_writer = nullptr;
    QObject::connect(button1, &QPushButton::clicked, [&]() {
       file_writer = new CSV_file();
        question.accept();
    });
    QObject::connect(button2, &QPushButton::clicked, [&]() {
        file_writer = new HTML_file();
        question.accept();
    });
    if (question.exec() != QDialog::Accepted) {
        return 0;}
    Controller* service= new Controller(file_writer);
    MainWindow w(service);
    w.resize(800, 600);
    w.show();
    return a.exec();
}