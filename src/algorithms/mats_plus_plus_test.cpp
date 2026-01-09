#include "mats_plus_plus_test.h"

#include "mats_plus_plus_test.h"
#include "faulty_memory.h"
#include <set>

const char* MATSPlusPlus::name() const
{
    return "MATS++";
}

int MATSPlusPlus::run(FaultyMemory *mem)
{
    std::set<size_t> errorsFound;
    size_t n = mem->size();

    emit message("Старт алгоритма MATS++ (Minimum Algorithm for Test Stuck-at)");
    emit message("↑(w0); ↑(r0,w1); ↓(r1,w0)");

    // M0: ↑(w0)
    emit message("M0: Запись 0...");
    for (size_t i = 0; i < n; i++)
        mem->write(i, 0);

    // M1: ↑(r0,w1)
    emit message("M1: Чтение 0 и запись 1 (восходящий)...");
    for (size_t i = 0; i < n; i++)
    {
        uint8_t val = mem->read(i);
        if (val != 0)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу  %1: ожидался 0, прочитано %2").arg(i).arg(val));
        }
        mem->write(i, 1);
    }

    // M2: ↓(r1,w0)
    emit message("M2: Чтение 1 и Запись 0 (нисходящий)...");
    for (size_t i = n; i-- > 0;)
    {
        uint8_t val = mem->read(i);
        if (val != 1)
        {
            errorsFound.insert(i);
            emit message(QString("  Ошибка по адресу  %1: ожидалась 1, прочитано %2").arg(i).arg(val));
        }
        mem->write(i, 0);
    }

    emit message(QString("Итого дефектных ячеек: %1\nКонец алгоритма тестирования").arg(errorsFound.size()));
    return errorsFound.size();
}
