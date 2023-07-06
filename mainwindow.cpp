#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , mTasks()
{
    ui->setupUi( this );
    connect( ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    bool ok;
    QString name =
        QInputDialog::getText( this,
                               tr( "Add task" ),
                               tr( "Task name" ),
                               QLineEdit::Normal,
                               tr( "Untitled task" ), &ok );

    if( ok && !name.isEmpty() ) {
        Task* task = new Task( name );
        mTasks.append( task );
        ui->tasksLayout->addWidget( task );
    }
}

#include "moc_mainwindow.cpp"
