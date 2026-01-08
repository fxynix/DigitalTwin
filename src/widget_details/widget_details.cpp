#include "widget_details.h"
#include "ui_widget_details.h"

WidgetDetails::WidgetDetails(QWidget *parent) : QWidget(parent), ui(new Ui::WidgetDetails) {
    ui->setupUi(this);
    
    setMinimumSize(size());
    setWindowFlag(Qt::Window);

    connect(ui->pushButtonClear, &QPushButton::clicked, ui->plainTextEditDetails, &QPlainTextEdit::clear);
}

WidgetDetails::~WidgetDetails() {
    delete ui;
}

void WidgetDetails::appendText(const QString &msg) {
    QTextCursor cursor = ui->plainTextEditDetails->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(msg + "\n");
    ui->plainTextEditDetails->setTextCursor(cursor);
    ui->plainTextEditDetails->ensureCursorVisible();
}