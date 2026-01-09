#ifndef WIDGET_DETAILS_H
#define WIDGET_DETAILS_H

#include <QWidget>

namespace Ui { class WidgetDetails; }

class WidgetDetails : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetDetails(QWidget *parent = nullptr);
    ~WidgetDetails() override;

public slots:
    void appendText(const QString &msg);

private:
    Ui::WidgetDetails *ui;
};

#endif // WIDGET_DETAILS_H
