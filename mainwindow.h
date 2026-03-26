#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "excelmanager.h"
#include <QMainWindow>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpenExcelClicked();
    void onShowCurrentMonthClicked();
    void onShowSortedClicked();
    void fillTableFromMap(QTableWidget *table, const QMultiMap<QDate, QString> &dataMap);// Наш слот для кнопки
    void fillTableFiltered(QTableWidget *table, const QMultiMap<QDate, QString> &dataMap,
                            int day, int month, int year);  // <-- Функция фильтрации
    void fillTableFilteredWithScrollers(QTableWidget *table, const QMultiMap<QDate, QString> &dataMap,
                           int day, int month, int year);

private:
    Ui::MainWindow *ui;
    ExcelManager excelManager; // Объект менеджера
};
#endif // MAINWINDOW_H
