// march_lr_test.cpp
#include "march_lr_test.h"
#include "faulty_memory.h"
#include <set>

const char* MarchLR::name() const
{
    return "March LR";
}

int MarchLR::run(FaultyMemory *mem)
{
    int errorCount = 0;
    std::set<size_t> errorsFound;

    size_t n = mem->size();

    emit message(QString("Старт алгоритма тестирования ") + name() + "\n↑w0; ↑(r0,w1,r1,w0); ↓(r0,w1,r1,w0); ↑r0");

    // M0: ↑(w0) - Инициализация всех в 0 (восходящий)
    emit message("M0: Запись 0 (восходящий)...");
    for (size_t i = 0; i < n; i++)
        mem->write(i, 0);

    // M1: ↑(r0,w1,r1,w0) - Проверка переходов 0→1 и 1→0 (восходящий)
    emit message("M1: Проверка переходов 0→1 и 1→0 (восходящий)...");
    for (size_t i = 0; i < n; i++)
    {
        // r0: Чтение 0
        uint8_t val = mem->read(i);
        if (val != 0)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1 - ожидался 0, прочитано %2").arg(i).arg(val));
        }

        // w1: Запись 1
        mem->write(i, 1);

        // r1: Чтение 1
        val = mem->read(i);
        if (val != 1)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу %1: - ожидалась 1, прочитано %2").arg(i).arg(val));
        }

        // w0: Запись 0
        mem->write(i, 0);
    }

    // M2: ↓(r0,w1,r1,w0) - Проверка переходов 0→1 и 1→0 (нисходящий)
    emit message("M2: Проверка переходов 0→1 и 1→0 (нисходящий)...");
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
    }

    // M3: ↑(r0) - Чтение 0 (восходящий)
    emit message("M3: Чтение 0 (восходящий)...");
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
