#ifndef TEST_ALGORITHM
#define TEST_ALGORITHM

#include <QObject>

class FaultyMemory;

class TestAlgorithm : public QObject {
    Q_OBJECT

public:
    TestAlgorithm(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~TestAlgorithm() = default;

    virtual int run(FaultyMemory *mem) = 0;
    virtual const char* name() const = 0;

signals:
    void message(const QString &msg);
};


#endif // TEST_ALGORITHM