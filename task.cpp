#include "task.h"
#include "ui_task.h"

#include <QInputDialog>

Task::Task( const QString& name, QWidget* parent ) :
    QWidget( parent ),
    ui( new Ui::Task )
{
    ui->setupUi( this );
    setName( name );
    connect( ui->editTaskButton, &QPushButton::clicked, this, &Task::rename );
    connect( ui->removeButton, &QPushButton::clicked, this, [this] {
        emit removed( this );
    } );
    connect( ui->taskCheckBox, &QCheckBox::toggled, this, &Task::checked );
}

Task::~Task()
{
    delete ui;
}

void Task::setName( const QString& name )
{
    ui->taskCheckBox->setText( name );
}

QString Task::name() const
{
    return ui->taskCheckBox->text();
}

bool Task::isCompleted() const
{
    return ui->taskCheckBox->isChecked();
}

void Task::rename()
{
    bool ok;
    QString value =
        QInputDialog::getText( this,
                               tr( "Edit task" ),
                               tr( "Task name" ),
                               QLineEdit::Normal,
                               this->name(), &ok );

    if( ok && !value.isEmpty() ) {
        setName( value );
    }
}

void Task::checked( bool checked )
{
    QFont font( ui->taskCheckBox->font() );
    font.setStrikeOut( checked );
    ui->taskCheckBox->setFont( font );
    emit statusChanged( this );
}

#include "moc_task.cpp"
