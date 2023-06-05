#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct Circle{
    QPoint center;
    int radius;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;
    const int B = 25, R = 100;
    QPoint circle, ant, fly, min_now, ant_move, moves[4];
    bool contains(Circle c, QPoint p);
    QVector<QPoint> min_p;
    Circle c;
    float len;
};
#endif // MAINWINDOW_H
