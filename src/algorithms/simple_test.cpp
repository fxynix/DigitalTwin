#include "simple_test.h"
#include "faulty_memory.h"

const char* SimpleTest::name() const {
    return "Write 0 / Read / Write 1 / Read";
}

int SimpleTest::run(FaultyMemory *mem) {
    int errorCount = 0;
    size_t n = mem->size();

    emit message(QString("Старт алгоритма тестирования \"") + name() + "\"...");

    for (size_t i = 0; i < n; i++) mem->write(i, 0);

    for (size_t i = 0; i < n; i++) {
        uint8_t val = mem->read(i);
        if (val != 0) {
            errorCount++;
            emit message(QString("Ошибка по адресу %1: ожидалось 0, прочитано %2").arg(i).arg(val));
        }
    }

    for (size_t i = 0; i < n; i++) mem->write(i, 1);

    for (size_t i = 0; i < n; i++) {
        uint8_t val = mem->read(i);
        if (val != 1) {
            errorCount++;
            emit message(QString("Ошибка по адресу %1: ожидалось 1, прочитано %2").arg(i).arg(val));
        }
    }

    emit message("Конец алгоритма тестирования");

    return errorCount;
}
