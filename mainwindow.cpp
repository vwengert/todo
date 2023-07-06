#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui{new Ui::MainWindow}
    , mTasks{}
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    qDebug() << "User clicked on add task button!";
    Task* task = new Task("Untitled Task");
    mTasks.append(task);
    ui->tasksLayout->addWidget(task);
}

#include "moc_mainwindow.cpp"
