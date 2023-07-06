#include "task.h"
#include "ui_task.h"

Task::Task(const QString &name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);
}

Task::~Task()
{
    delete ui;
}

void Task::setName(const QString &name)
{
    ui->taskCheckBox->setText(name);
}

QString Task::name() const
{
    return ui->taskCheckBox->text();
}

bool Task::isCompleted() const
{
    return ui->taskCheckBox->isChecked();
}

#include "moc_task.cpp"
