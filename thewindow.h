#ifndef THEWINDOW_H
#define THEWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include "testData.h"
#include "pagecreationdialog.h"
#include "testingdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TheWindow; }
QT_END_NAMESPACE
using namespace std;

class TheWindow : public QMainWindow
{
    Q_OBJECT
public:
    TheWindow(QWidget *parent = nullptr);
    ~TheWindow();
public slots:
    void on_test_open_triggered();
private slots:
    void on_test_create_triggered();

private:
    void openTest(QString path);
    Ui::TheWindow *ui;
};
#endif // THEWINDOW_H
