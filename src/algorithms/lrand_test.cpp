// lrand_test.cpp
#include "lrand_test.h"
#include "faulty_memory.h"
#include <set>
#include <cmath>

const char* LRANDTest::name() const
{
    return "LRAND Test";
}

uint32_t LRANDTest::lcgNext(uint32_t current, uint32_t a, uint32_t c, uint32_t m) const
{
    // Линейный конгруэнтный генератор: Xₙ₊₁ = (a × Xₙ + c) mod m
    return static_cast<uint32_t>((static_cast<uint64_t>(a) * current + c) % m);
}

uint8_t LRANDTest::generateData(uint32_t address, uint32_t iteration) const
{
    // Генерация псевдослучайного бита на основе адреса и итерации с использованием хэш-функции
    uint32_t hash = address ^ (iteration << 16);
    hash = (hash * 1103515245 + 12345) & 0x7FFFFFFF;

    // Возвращаем 0 или 1 на основе хэша
    return (hash & 0x100) ? 1 : 0;
}

int LRANDTest::run(FaultyMemory *mem)
{
    std::set<size_t> errorsFound;
    size_t n = mem->size();

    emit message(QString("Старт алгоритма тестирования ") + name() + "\nПсевдослучайное тестирование с линейным генератором");

    emit message("Формула: Xₙ₊₁ = (a × Xₙ + c) mod N");

    // Параметры LCG (Linear Congruential Generator)
    uint32_t a = 1664525;      // Множитель
    uint32_t c = 1013904223;   // Инкремент
    uint32_t seed = 123456789; // Начальное значение

    emit message(QString("Параметры LCG: a=%1, c=%2, seed=%3").arg(a).arg(c).arg(seed));

    // Фаза 1: Запись псевдослучайных данных
    emit message("\nФаза 1: Запись псевдослучайных данных...");

    uint32_t currentAddr = seed % n;
    std::set<size_t> visitedAddresses;

    for (uint32_t iteration = 0; iteration < n; iteration++)
    {
        // Генерируем данные для записи (0 или 1)
        uint8_t data = generateData(currentAddr, iteration);

        // Записываем данные
        mem->write(currentAddr, data);
        visitedAddresses.insert(currentAddr);

        // Генерируем следующий адрес
        currentAddr = lcgNext(currentAddr, a, c, static_cast<uint32_t>(n));
    }


    emit message(QString("Посещено %1 из %2 адресов").arg(visitedAddresses.size()).arg(n));

    // Фаза 2: Проверка записанных данных (та же последовательность)
    emit message("\nФаза 2: Проверка записанных данных...");

    currentAddr = seed % n; // Сбрасываем к начальному seed

    for (uint32_t iteration = 0; iteration < n; iteration++)
    {
        uint8_t expectedData = generateData(currentAddr, iteration);

        uint8_t actualData = mem->read(currentAddr);

        if (expectedData != actualData)
        {
            errorsFound.insert(currentAddr);

            emit message(QString("  Ошибка по адресу %1: ожидалось %2, прочитано %3")
                                 .arg(currentAddr)
                                 .arg(static_cast<int>(expectedData))
                                 .arg(static_cast<int>(actualData)));
        }

        // Следующий адрес (та же последовательность)
        currentAddr = lcgNext(currentAddr, a, c, static_cast<uint32_t>(n));
    }

    // Фаза 3: Инвертирование данных
    emit message("\nФаза 3: Запись инвертированных данных...");

    currentAddr = seed % n; // Снова начинаем с seed

    for (uint32_t iteration = 0; iteration < n; iteration++)
    {
        // Инвертируем предыдущее значение
        uint8_t invertedData = generateData(currentAddr, iteration) ? 0 : 1;

        mem->write(currentAddr, invertedData);

        currentAddr = lcgNext(currentAddr, a, c, static_cast<uint32_t>(n));
    }

    emit message("\nФаза 4: Проверка инвертированных данных...");

    currentAddr = seed % n;

    for (uint32_t iteration = 0; iteration < n; iteration++)
    {
        uint8_t expectedInverted = generateData(currentAddr, iteration) ? 0 : 1;

        uint8_t actualData = mem->read(currentAddr);

        if (expectedInverted != actualData)
        {
            errorsFound.insert(currentAddr);

            emit message(QString("  Инверсия: адрес %1 - ожидалось %2, прочитано %3")
                        .arg(currentAddr)
                            .arg(static_cast<int>(expectedInverted))
                            .arg(static_cast<int>(actualData)));
        }

        currentAddr = lcgNext(currentAddr, a, c, static_cast<uint32_t>(n));
    }

    emit message(QString("Посещено %1 из %2 адресов").arg(visitedAddresses.size()).arg(n));
    emit message(QString("Итого дефектных ячеек: %1\nКонец алгоритма тестирования").arg(errorsFound.size()));

    return errorsFound.size();
}
