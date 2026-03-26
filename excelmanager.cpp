#include "excelmanager.h"
#include <QFileDialog>
#include <QDebug>
#include <qtablewidget.h>

bool ExcelManager::openAndReadXlsx() {
    // 1. Вызываем диалог выбора файла
    QString filePath = QFileDialog::getOpenFileName(
        nullptr,
        "Выберите таблицу Excel",
        "",
        "Excel Files (*.xlsx)"
        );

    if (filePath.isEmpty()) {
        qDebug() << "Файл не выбран";
        return false;
    }

    try {
        // 2. Открываем документ через OpenXLSX
        // В OpenXLSX используется std::string, поэтому конвертируем QString
        OpenXLSX::XLDocument doc;
        doc.open(filePath.toStdString());
        processWorkbook(doc);

        doc.close();
        return true;
    } catch (const std::exception& e) {
        qDebug() << "Ошибка при открытии файла:" << e.what();
        return false;
    }
}

void ExcelManager::processWorkbook(OpenXLSX::XLDocument& doc) {
    // Получаем список имен всех листов в книге
    auto sheetNames = doc.workbook().worksheetNames();

    if (sheetNames.empty()) {
        qDebug() << "В файле нет ни одного листа!";
        return;
    }

    m_dataMap.clear();

    QMultiMap<QDate, QString> dataMap;

    // Берем самый первый лист из списка (индекс 0)
    std::string firstSheetName = sheetNames[0];
    auto wks = doc.workbook().worksheet(firstSheetName);

    uint32_t rows = wks.rowCount();

    qDebug() << "Всего строк:" << rows;
    // 4. Проходим циклом по строкам (в Excel индекс начинается с 1)
    for (uint32_t i = 1; i <= rows; ++i) {
        OpenXLSX::XLCellValue value = wks.cell(i, 9).value();

        //qDebug() << value.typeAsString();
        if (value.typeAsString() == "integer") {
            double excelDate = value.getDouble();
            // Excel использует 30.12.1899 как базу
            QDate date = QDate(1899, 12, 30).addDays(excelDate);

        //date(tm.tm_year, tm.tm_mon, tm.tm_yday);
            QString inventaryNumber = QString::fromStdString(wks.cell(i, 3).value().getString());

        //qDebug() << "KeyI" << date.day() << date.month() << date.year() << wks.cell(i, 3).value().getString();
            m_dataMap.insert(date, inventaryNumber);

           // dataMap.insert(date, QString::fromStdString(inventaryNumber));
        }
    }


    // Проверка результата в консоли
    qDebug() << "Считано пар данных:" << dataMap.size();

    // Пример вывода:
    // Поиск всех значений для даты
    QDate targetDate = QDate::fromString("2024-04-01", "yyyy-MM-dd");
    auto range = dataMap.equal_range(targetDate);

    for (auto it = range.first; it != range.second; ++it) {
        qDebug() << "Value:" << it.value();
    }
    // Количество записей для даты

    //qDebug() << "Открыт лист:" << QString::fromStdString(firstSheetName);
}


