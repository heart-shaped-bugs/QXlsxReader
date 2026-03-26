#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Коннектим кнопку из UI к нашему слоту
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::onOpenExcelClicked);
    connect(ui->pushButtonCurrentMonth, &QPushButton::clicked,
            this, &MainWindow::onShowCurrentMonthClicked);
    connect(ui->pushButtonDate, &QPushButton::clicked, this, &MainWindow::onShowSortedClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenExcelClicked() {
    // Вызываем вашу функцию выбора и открытия файла
    bool success = excelManager.openAndReadXlsx();

    if (success) {
        fillTableFromMap(ui->tableWidget, excelManager.getDataMap());
        // connect(ui->pushButtonCurrentMonth, &QPushButton::clicked,
        //         this, &MainWindow::onShowCurrentMonthClicked);

        qDebug() << "Файл успешно прочитан!";
    } else {
        qDebug() << "Не удалось открыть файл.";
    }
}

// ВНИМАНИЕ: Добавьте префикс MainWindow::
void MainWindow::fillTableFromMap(QTableWidget *table, const QMultiMap<QDate, QString> &dataMap)
{
    for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
        int row = table->rowCount();
        table->insertRow(row);

        QTableWidgetItem *dateItem = new QTableWidgetItem(it.key().toString("dd.MM.yyyy"));
        dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);

        QTableWidgetItem *valueItem = new QTableWidgetItem(it.value());
        valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);

        table->setItem(row, 0, dateItem);
        table->setItem(row, 1, valueItem);
    }

    //table->resizeColumnsToContents();
}


// Фильтрация по месяцу и году
void MainWindow::fillTableFiltered(QTableWidget *table,
                                   const QMultiMap<QDate, QString> &dataMap,
                                   int day,
                                   int month, int year)
{

    table->setRowCount(0);

    for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
        QDate date = it.key();

        qDebug() << date.day() << date.month() << date.year();

        if (date.month() == month && date.year() < year) {
            qDebug() << "МЕСЯЦЫ РАВНЫ" << date.day() << date.month() << date.year();
            int row = table->rowCount();
            table->insertRow(row);


            QTableWidgetItem *dateItem = new QTableWidgetItem(date.toString("dd.MM.yyyy"));
            dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);

            QTableWidgetItem *valueItem = new QTableWidgetItem(it.value());
            valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);

            table->setItem(row, 0, dateItem);
            table->setItem(row, 1, valueItem);
        }
    }

    //table->resizeColumnsToContents();

    // Показываем количество найденных записей в заголовке окна или статусе
    qDebug() << "Найдено записей за" << month << "/" << year << ":" << table->rowCount();
}

void MainWindow::fillTableFilteredWithScrollers(QTableWidget *table,
                                   const QMultiMap<QDate, QString> &dataMap,
                                   int day,
                                   int month, int year)
{
    table->setRowCount(0);

    for (auto it = dataMap.begin(); it != dataMap.end(); ++it) {
        QDate date = it.key();

        if ((day == 0   || date.day() == day) &&
            (month == 0 || date.month() == month) &&
            (year == 0  || date.year() == year)) {

            int row = table->rowCount();
            table->insertRow(row);


            QTableWidgetItem *dateItem = new QTableWidgetItem(date.toString("dd.MM.yyyy"));
            dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsEditable);

            QTableWidgetItem *valueItem = new QTableWidgetItem(it.value());
            valueItem->setFlags(valueItem->flags() & ~Qt::ItemIsEditable);

            table->setItem(row, 0, dateItem);
            table->setItem(row, 1, valueItem);
        }
    }

    qDebug() << "Найдено записей за" << month << "/" << year << ":" << table->rowCount();
}

// Слот для кнопки "Показать текущий месяц"
void MainWindow::onShowCurrentMonthClicked()
{
    QDate currentDate = QDate::currentDate();
    int currentDay = currentDate.day();
    int currentMonth = currentDate.month();
    int currentYear = currentDate.year();

    fillTableFiltered(ui->tableWidget, excelManager.getDataMap(), currentDay, currentMonth + 1, currentYear);

    qDebug() << "Показаны данные за:" << currentMonth << "/" << currentYear;
}

void MainWindow::onShowSortedClicked()
{
    //QDate currentDate = QDate::currentDate();
    int Day = ui->days->value();
    QString stringMonth = ui->months->currentText();
    int Month = 0;
    int Year = ui->year->value();


    if (stringMonth == "Январь") {
        Month = 1;
    }

    if (stringMonth == "Февраль") {
        Month = 2;
    }

    if (stringMonth == "Март") {
        Month = 3;
    }

    if (stringMonth == "Апрель") {
        Month = 4;
    }

    if (stringMonth == "Май") {
        Month = 5;
    }

    if (stringMonth == "Июнь") {
        Month = 6;
    }

    if (stringMonth == "Июль") {
        Month = 7;
    }

    if (stringMonth == "Август") {
        Month = 8;
    }

    if (stringMonth == "Сентябрь") {
        Month = 9;
    }

    if (stringMonth == "Октябрь") {
        Month = 10;
    }

    if (stringMonth == "Ноябрь") {
        Month = 11;
    }

    if (stringMonth == "Декабрь") {
        Month = 12;
    }

    qDebug() << "Pushed" << Day << Month << Year;

    fillTableFilteredWithScrollers(ui->tableWidget, excelManager.getDataMap(), Day, Month, Year);

    qDebug() << "Pushed IF" << Day << "/" << Month << "/" << Year;

}
