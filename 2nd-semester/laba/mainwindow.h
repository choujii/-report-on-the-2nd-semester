#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
enum{LEFT,RIGHT,UNDIFINED};
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    int classify(QLine n,QPoint m);
    Ui::MainWindow *ui;
    QPoint f1;
    QPoint f2;

    int a = 0;
};
#endif // MAINWINDOW_H
