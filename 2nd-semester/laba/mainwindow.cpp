#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPoint t = f2-f1;
    QPoint n1(-t.y(),t.x());
    QPoint n2(t.y(),-t.x());
    QPoint t1 = f2 + n1 - f2;
    QPoint t2 = f2 + n2 - f2;
    QPoint n3(t1.y(),-t1.x());
    QPoint n4(-t2.y(),t2.x());
    QLine p(50,50,100,100);
    QPainter painter(this);
    QBrush brush1(Qt::yellow);
    QBrush brush2(Qt::black);
    if(!(f1.isNull()) && !(f2.isNull())){
        painter.drawLine(f1,f2);
        painter.drawLine(f2,f2+n1+n3);
        painter.drawLine(f2,f2+n2+n4);
        painter.setBrush(brush1);
        QPoint u[3] = {f2,f2+n2+n4,f2+n1+n3};
        painter.drawPolygon(u, 3);
    }


}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint t = f2-f1;
    QPoint n1(-t.y(),t.x());
    QPoint n2(t.y(),-t.x());
    QPoint t1 = f2 + n1 - f2;
    QPoint t2 = f2 + n2 - f2;
    QPoint n3(t1.y(),-t1.x());
    QPoint n4(-t2.y(),t2.x());
    a+=1;
    if(a == 1)
        f1 = event->pos();
    if(a == 2)
        f2 = event->pos();
    if(a >= 3){
        int b = classify(QLine(f1,f2),event->pos());
        qDebug("%s",b == LEFT ? "LEFT":b == RIGHT ? "RIGHT":"UNDIFINED");
        int d = classify(QLine(f2 + n2,f2 + n1),event->pos());
        int d1 = classify(QLine(f1 + n1,f1 + n2),event->pos());
        int d2 = classify(QLine(f2,f2+n1+n3),event->pos());
        int d3 = classify(QLine(f2,f2+n2+n4),event->pos());
        if(d == LEFT)
            qDebug("IN");
        if(d1 == LEFT)
            qDebug("BACK");
        if(d == RIGHT && d1 == RIGHT)
            qDebug("SIDE");
        if(d2 == LEFT && d3 == LEFT)
            qDebug("FRONT");
        if(d2 == RIGHT && d3 == RIGHT)
            qDebug("FRONT");


    }

    repaint();

}

int MainWindow::classify(QLine n, QPoint m)
{
    QPoint a = n.p2() - n.p1();
    QPoint b = m - n.p1();
    int c = a.x() * b.y() - b.x() * a.y();
    if(c > 0)
        return RIGHT;
    if(c < 0)
        return LEFT;
    if(c == 0)
        return UNDIFINED;

}



