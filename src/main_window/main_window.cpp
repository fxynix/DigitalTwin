#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QtConcurrent>
#include <memory>

#include "main_window.h"
#include "ui_main_window.h"
#include "widget_details.h"

#include "memory.h"
#include "faulty_memory.h"

#include "checkerboard_test.h"
#include "lrand_test.h"
#include "march_a_test.h"
#include "march_b_test.h"
#include "march_c_test.h"
#include "march_lr_test.h"
#include "mats_plus_plus_test.h"

#include "stuck_at_zero.h"
#include "stuck_at_one.h"
#include "bit_flip_phy.h"
#include "bit_flip_logic.h"
#include "rnd_stuck_at.h"

#define TOTAL_CELLS 262144  // 32КБ = 32768 Б = 262144 б

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widgetDetails = new WidgetDetails(this);
    memory = new Memory(TOTAL_CELLS);

    // Валидатор для ручного выбора адресов
    QRegularExpression regex("^\\d+(-\\d+)?(,\\d+(-\\d+)?)*$");
    QValidator *validator = new QRegularExpressionValidator(regex, ui->lineEditSelect);
    ui->lineEditSelect->setValidator(validator);

    // Валидатор для количества случайных адресов
    QRegularExpression rndRegex("^\\d+$");
    QValidator *rndValidator = new QRegularExpressionValidator(rndRegex, ui->lineEditRndSelect);
    ui->lineEditRndSelect->setValidator(rndValidator);


    setFixedSize(size());
    initConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete memory;
}

void MainWindow::initConnections()
{
    connect(ui->pushButtonDetails, &QPushButton::clicked, widgetDetails, &WidgetDetails::show);
    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
}

std::set<size_t> MainWindow::generateRandomAddresses(int count) const
{
    std::set<size_t> result;

    if (count <= 0) return result;
    if (count > TOTAL_CELLS) count = TOTAL_CELLS;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, TOTAL_CELLS - 1);

    // Генерируем случайные уникальные адреса
    while (result.size() < static_cast<size_t>(count))
        result.insert(dist(gen));

    return result;
}

std::set<size_t> MainWindow::parseMemorySelection(const QString &text) const
{
    std::set<size_t> result;

    QStringList parts = text.split(',', Qt::SkipEmptyParts);

    for (const QString &part : parts)
    {
        if (part.contains('-'))
        {
            QStringList range = part.split('-');

            bool ok1, ok2;
            size_t start = range[0].toULong(&ok1);
            size_t end = range[1].toULong(&ok2);
            if (!ok1 || !ok2) continue;

            if (start >= TOTAL_CELLS) start = TOTAL_CELLS - 1;
            if (end >= TOTAL_CELLS) end = TOTAL_CELLS - 1;

            if (start <= end)
            {
                for (size_t i = start; i <= end; i++) result.insert(i);
            }
            else
            {
                for (size_t i = start; i >= end; i--) result.insert(i);
            }
        }
        else
        {
            bool ok;
            size_t val = part.toULong(&ok);
            if (ok && val < TOTAL_CELLS) result.insert(val);
        }
    }

    return result;
}

FaultModel* MainWindow::getFaultModel(std::set<size_t> &faultyAddresses) const
{
    int index = ui->comboBoxDefect->currentIndex();

    switch (index)
    {
        case 0: return new StuckAtZero(faultyAddresses);
        case 1: return new StuckAtOne(faultyAddresses);
        case 2: return new BitFlipPhy(faultyAddresses);
        case 3: return new BitFlipLogical(faultyAddresses);
        case 4: return new RndStuckAt(faultyAddresses);
        default: return new StuckAtZero(faultyAddresses);
    }
}

TestAlgorithm* MainWindow::getTestAlgorithm() const
{
    int index = ui->comboBoxAlgorithm->currentIndex();

    switch (index)
    {
        case 0: return new MATSPlusPlus();
        case 1: return new MarchA();
        case 2: return new MarchB();
        case 3: return new MarchC();
        case 4: return new MarchLR();
        case 5: return new CheckerboardTest();
        case 6: return new LRANDTest();

        default: return new MATSPlusPlus();
    }
}

void MainWindow::onStartButtonClicked()
{
    std::set<size_t> faultyAddresses = generateRandomAddresses(ui->lineEditRndSelect->text().toInt());
    faultyAddresses.merge(parseMemorySelection(ui->lineEditSelect->text()));

    auto faultModel = std::shared_ptr<FaultModel>(getFaultModel(faultyAddresses));
    auto testAlgorithm = std::shared_ptr<TestAlgorithm>(getTestAlgorithm());
    auto faultyMemory = std::make_shared<FaultyMemory>(memory, faultModel.get());

    ui->lineEditSelect->setEnabled(false);
    ui->pushButtonStart->setEnabled(false);
    ui->progressBar->setEnabled(true);

    connect(
        testAlgorithm.get(),
        &TestAlgorithm::message,
        widgetDetails,
        &WidgetDetails::appendText,
        Qt::QueuedConnection
    );

    QThreadPool::globalInstance()->start([this, faultModel, testAlgorithm, faultyMemory]()
    {
        int errorCount = testAlgorithm->run(faultyMemory.get());

        QMetaObject::invokeMethod(this, [this, errorCount]()
        {
            ui->lineEditSelect->setEnabled(true);
            ui->progressBar->setEnabled(false);

            if (errorCount != 0)
            {
                QMessageBox::critical(
                    this,
                    "Результат тестирования",
                    QString("Ошибок обнаружено: %1\nДетали в подробностях")
                        .arg(errorCount)
                );
            }
            else
            {
                QMessageBox::information(
                    this,
                    "Результат тестирования",
                    "Ошибок не обнаружено\nДетали в подробностях"
                );
            }
            ui->pushButtonStart->setEnabled(1);
        });
    });
}
