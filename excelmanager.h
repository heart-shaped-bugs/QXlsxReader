#ifndef EXCELMANAGER_H
#define EXCELMANAGER_H

#include <QString>
#include <OpenXLSX.hpp>
#include <qdatetime.h>

class ExcelManager {
public:
    // Функция открывает диалог выбора файла и загружает его
    bool openAndReadXlsx();
    const QMultiMap<QDate, QString>& getDataMap() const { return m_dataMap; }
private:
    // Внутренняя логика обработки данных
    void processWorkbook(OpenXLSX::XLDocument& doc);
    QMultiMap<QDate, QString> m_dataMap;

};

#endif // EXCELMANAGER_H
