#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <set>

namespace Ui { class MainWindow; }

class WidgetDetails;
class Memory;
class FaultModel;
class TestAlgorithm;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void onStartButtonClicked();

    FaultModel* getFaultModel(std::set<size_t> &faultyAddresses) const;
    TestAlgorithm* getTestAlgorithm() const;

    void initConnections();
    std::set<size_t> generateRandomAddresses(int count) const;
    std::set<size_t> parseMemorySelection(const QString &text) const;

    Ui::MainWindow *ui;
    WidgetDetails *widgetDetails;
    
    Memory *memory;
};

#endif // MAIN_WINDOW_H
