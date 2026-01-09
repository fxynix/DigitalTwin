#include "checkerboard_test.h"
#include "faulty_memory.h"
#include <set>

const char* CheckerboardTest::name() const
{
    return "CheckerboardTest (Шахматный)";
}

int CheckerboardTest::run(FaultyMemory *mem)
{
    int errorCount = 0;
    std::set<size_t> errorsFound;

    size_t n = mem->size();

    emit message(QString("Старт алгоритма тестирования ") + name() + "\nЗапись 01010101, Чтение, Запись 101010101, Чтение");

    emit message("Запись 1 чётные, 0 нечётные, чтение...");

    // Записываем паттерн 10101010
    for (size_t i = 0; i < n; i++)
    {
        mem->write(i, (i % 2 == 0) ? 1 : 0);
    }

    // Проверяем
    for (size_t i = 0; i < n; i++)
    {
        uint8_t expected = (i % 2 == 0) ? 1 : 0;
        if (mem->read(i) != expected)
        {
            emit message(QString("  Ошибка по адресу %1: ожидалось %2, прочитано %3").arg(i).arg(expected).arg(!expected));
            errorsFound.insert(i);
        }
    }

    emit message("Запись 0 чётные, 1 нечётные, чтение...");

    // Инвертируем паттерн
    for (size_t i = 0; i < n; i++)
    {
        mem->write(i, (i % 2 == 0) ? 0 : 1);
    }

    // Проверяем
    for (size_t i = 0; i < n; i++)
    {
        uint8_t expected = (i % 2 == 0) ? 0 : 1;
        if (mem->read(i) != expected)
        {
            emit message(QString("  Ошибка по адресу %1: ожидалось %2, прочитано %3").arg(i).arg(expected).arg(!expected));
            errorsFound.insert(i);
        }
    }

    emit message(QString("Итого дефектных ячеек: %1\nКонец алгоритма тестирования").arg(errorsFound.size()));

    return errorsFound.size();
}

