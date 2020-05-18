#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QString>

bool du_hack_mein(const char* file_name, const char* password);

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void file_choosen();
    void open_file();
    void du_hack();

private:
    Ui::MainWindow *ui;
    QString file_name;
    QLabel* background;
    QPushButton* button;
    QString* password;
};
#endif // MAINWINDOW_H
