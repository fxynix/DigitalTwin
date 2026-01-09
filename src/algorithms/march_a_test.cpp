#include "march_a_test.h"
#include "faulty_memory.h"
#include <set>

const char* MarchA::name() const
{
    return "March A";
}

int MarchA::run(FaultyMemory *mem)
{
    std::set<size_t> errorsFound;
    size_t n = mem->size();

    emit message(QString("Старт алгоритма тестирования ") + name() + "\n↑w0; ↑r0,w1,r1,w0,r0; ↓r0,w1,r1,w0,r0");

    // M0: ↑(w0) - Запись всех в 0 (восходящий)
    emit message("M0: Инициализация всех ячеек в 0 (восходящий)...");
    for (size_t i = 0; i < n; i++)
        mem->write(i, 0);

    // M1: ↑(r0,w1,r1,w0,r0) - Полный цикл тестирования (восходящий)
    emit message("M1: Чтение 0, запись 1, чтение 1, запись 0, чтение 0 (восходящий)...");
    for (size_t i = 0; i < n; i++)
    {
        // r0: Чтение 0
        uint8_t val = mem->read(i);
        if (val != 0)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидался 0, прочитано %2").arg(i).arg(val));
        }

        // w1: Запись 1
        mem->write(i, 1);

        // r1: Чтение 1
        val = mem->read(i);
        if (val != 1)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидалась 1, прочитано %2").arg(i).arg(val));
        }

        // w0: Запись 0
        mem->write(i, 0);

        // r0: Чтение 0
        val = mem->read(i);
        if (val != 0)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидался 0, прочитано %2").arg(i).arg(val));
        }
    }

    // M2: ↓(r0,w1,r1,w0,r0) - Полный цикл тестирования (нисходящий)
    emit message("M2: Чтение 0, запись 1, чтение 1, запись 0, чтение 0 (нисходящий)...");
    for (size_t i = n; i-- > 0;)
    {
        // r0: Чтение 0
        uint8_t val = mem->read(i);
        if (val != 0)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидался 0, прочитано %2").arg(i).arg(val));
        }

        // w1: Запись 1
        mem->write(i, 1);

        // r1: Чтение 1
        val = mem->read(i);
        if (val != 1)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидалась 1, прочитано %2").arg(i).arg(val));
        }

        // w0: Запись 0
        mem->write(i, 0);

        // r0: Чтение 0
        val = mem->read(i);
        if (val != 0)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидался 0, прочитано %2").arg(i).arg(val));
        }
    }

    emit message(QString("Итого дефектных ячеек: %1\nКонец алгоритма тестирования").arg(errorsFound.size()));
    return errorsFound.size();
}
