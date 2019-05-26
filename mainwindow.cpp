#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "todoobject.h"
#include <QStackedWidget>

vector<todoObject> todoObjects;
int currentObjectIndex = 0;
QStringListModel *model;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Create button
void MainWindow::on_pushButton_clicked()
{
    QString newTodoName = ui->lineEdit->text();
    ui->lineEdit->clear();

    if (newTodoName.length() < 1) {
        return;
    }

    todoObject *newTodoObj = new todoObject(newTodoName.toUtf8().constData());
    todoObjects.push_back(*newTodoObj);

    updateTable();
}

void MainWindow::updateTable() {
    ui->tableWidget->setRowCount(0);

    for (int i=0;i < todoObjects.size(); i++) {
        todoObject *newTodoObj = new todoObject(todoObjects[i].name);
        int rowNumber = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowNumber);

        QString listName = QString::fromStdString(newTodoObj->name);
        QString listProgress = QString::fromStdString(newTodoObj->getProgress());
        QString listDate = QString::fromStdString(newTodoObj->getDateString());

        ui->tableWidget->setItem(rowNumber, 0, new QTableWidgetItem(listName));
        ui->tableWidget->setItem(rowNumber, 1, new QTableWidgetItem(listProgress));
        ui->tableWidget->setItem(rowNumber, 2, new QTableWidgetItem(listDate));
    }
}

//Edit button
void MainWindow::on_pushButton_2_clicked()
{
    int selectedRow = ui->tableWidget->currentRow(); //throw error when nothing selected
    QTableWidgetItem *selectedItem = ui->tableWidget->takeItem(selectedRow, 2);
    QString selectedListDate = selectedItem->text();
    int selectedItemIndex = getListIndexByDate(selectedListDate);
    currentObjectIndex = selectedItemIndex;
    ui->stackedWidget->setCurrentIndex(1);

    QLabel *label = new QLabel(ui->stackedWidget);
    label->setText(QString::fromStdString(todoObjects[selectedItemIndex].name));
    label->setGeometry(QRect(40, 110, 300, 50));
    label->setStyleSheet("font: bold 20px;"
                         "color: white;");
    label->show();
    updateTaskLabels();
}

int MainWindow::getListIndexByDate(QString itemDate) {
    for(int i=0; i < int(todoObjects.size()); i++) {
        if (QString::fromStdString(todoObjects[i].getDateString()) == itemDate) {
            return i;
        }
    }
}

void MainWindow::on_createTask_clicked()
{
    if (todoObjects[currentObjectIndex].tasks.size() > 5) {
        return;
    }

    QString taskName = ui->taskName->text();
    ui->taskName->clear();
    todoObjects[currentObjectIndex].addTask(taskName.toStdString());
    updateTaskLabels();
}

void MainWindow::updateTaskLabels() {
    QStringList List;
    for (int i=0;i < todoObjects[currentObjectIndex].tasks.size();i++) {
        List.push_back(QString::fromStdString(todoObjects[currentObjectIndex].tasks[i]));
    }
    model->setStringList(List);
    ui->listView->setModel(model);
}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    updateTable();
}

//Delete a list
void MainWindow::on_pushButton_3_clicked()
{
    int selectedRow = ui->tableWidget->currentRow(); //throw error when nothing selected
    QTableWidgetItem *selectedItem = ui->tableWidget->takeItem(selectedRow, 2);
    QString selectedListDate = selectedItem->text();
    int selectedItemIndex = getListIndexByDate(selectedListDate);
    todoObjects.erase(todoObjects.begin() + selectedItemIndex);
    updateTable();
}
