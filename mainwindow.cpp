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
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStatus()
{
    int completedCount = 0;

    for( const auto t : mTasks ) {
        if( t->isCompleted() ) {
            ++completedCount;
        }
    }

    int todoCount = mTasks.size() - completedCount;
    ui->statusLabel->setText( QString( "Status: %1 / %2 completed" )
                              .arg( todoCount )
                              .arg( completedCount ) );
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
        connect( task, &Task::removed, this, &MainWindow::removeTask );
        connect( task, &Task::statusChanged, this, &MainWindow::taskStatusChanged );
        mTasks.append( task );
        ui->tasksLayout->addWidget( task );
        updateStatus();
    }
}

void MainWindow::removeTask( Task* task )
{
    mTasks.removeOne( task );
    ui->tasksLayout->removeWidget( task );
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged( Task* task )
{
    updateStatus();
}

#include "moc_mainwindow.cpp"
