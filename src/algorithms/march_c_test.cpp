#include "march_c_test.h"
#include "faulty_memory.h"
#include <set>

const char* MarchC::name() const
{
    return "MarchC";
}

int MarchC::run(FaultyMemory *mem)
{
    int errorCount = 0;
    std::set<size_t> errorsFound;

    size_t n = mem->size();

    emit message(QString("Старт алгоритма тестирования ") + name() + "\n↑w0; ↑r0,w1; ↑r1; ↓r1,w0; ↓r0; ↑r0");

    // M0: ↑(w0) (восходящий)
    emit message("M0: Запись 0 (восходящий)...");
    for (size_t i = 0; i < n; i++)
        mem->write(i, 0);

    // M1: ↑(r0,w1) - Чтение 0, Запись 1 (восходящий)
    emit message("M1: Чтение 0 и запись 1 (восходящий)...");
    for (size_t i = 0; i < n; i++)
    {
        uint8_t val = mem->read(i);
        if (val != 0)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидался 0, прочитано %2").arg(i).arg(val));
        }
        mem->write(i, 1);
    }

    // M2: ↑(r1) - Чтение 1  (восходящий)
    emit message("M2: Чтение записи 1 (восходящий)...");
    for (size_t i = 0; i < n; i++)
    {
        uint8_t val = mem->read(i);
        if (val != 1)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидалась 1, прочитано %2").arg(i).arg(val));
        }
    }

    // M3: ↓(r1,w0) - Чтение 1, Запись 0 (нисходящий)
    emit message("M3: Чтение 1 и запись 0 (нисходящий)...");
    for (size_t i = n; i-- > 0;)
    {
        uint8_t val = mem->read(i);
        if (val != 1)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидалась 1, прочитано %2").arg(i).arg(val));
        }
        mem->write(i, 0);
    }

    // M4: ↓(r0) - Чтение 0 (нисходящий)
    emit message("M4: Чтение 0 (нисходящий)...");
    for (size_t i = n; i-- > 0;)
    {
        uint8_t val = mem->read(i);
        if (val != 0)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидался 0, прочитано %2").arg(i).arg(val));
        }
    }

    // M5: ↑(r0) - Чтение 0 (восходящий)
    emit message("M5: Чтение 0 (восходящий)...");
    for (size_t i = 0; i < n; i++)
    {
        uint8_t val = mem->read(i);
        if (val != 0)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: ожидался 0, прочитано %2").arg(i).arg(val));
        }
    }

    emit message(QString("Итого дефектных ячеек: %1\nКонец алгоритма тестирования").arg(errorsFound.size()));

    return errorsFound.size();
}
