#include "mainwindow.h"
#include "./ui_mainwindow.h"
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
    QPainter painter(this);
    painter.setBrush(grass);
    painter.drawRect(contentsRect());
    painter.setBrush(QColor(0, 128, 128));
    painter.drawRect(pool);
    painter.setBrush(QColor(128, 128, 128));

    for (int i = 0; i < clumbs.size(); i++)
        painter.drawImage(clumbs[i], flower);

    for (int i = 0; i < c_clumbs.size(); i++)
        painter.drawEllipse(c_clumbs[i].center, c_clumbs[i].radius, c_clumbs[i].radius);
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button()&Qt::LeftButton) {
        QRect a(QPoint(0, 0), pool.size() * 0.1);
        a.moveCenter(event->pos());
        bool f_rect = true;
        for (int i = 0; i < clumbs.size(); i++)
            if (clumbs[i].intersects(a)){
                QRect a1 = clumbs[i].intersected(a);
                float s_peresecheniya = a1.width() * a1.height();
                float s_clumb = a.width() * a.height();
                if (s_clumb * 0.6 >= s_peresecheniya){
                    f_rect = false;
                    break;
                }
            }
        for(Circle c:c_clumbs)
            if(intersects_circle(c, a))
                return;
        if(!(pool.contains(a.center())) && f_rect)
            clumbs.append(a);
    }
    else {
        bool f_circle = true;
        Circle c = {event->pos(), 20};
        for (int i = 0; i < c_clumbs.size(); i++)
            if (intersects(c_clumbs[i], c)) {
                f_circle = false;
                break;
            }
        for (QRect i:clumbs)
            if (intersects_circle(c, i))
                return;
        if (!(pool.contains(c.center)) && f_circle)
            c_clumbs.append(c);
    }
    repaint();
}



bool MainWindow::intersects(Circle c1, Circle c2)
{
    QPoint c_len(c1.center - c2.center);
    int c = c_len.x() * c_len.x() + c_len.y() * c_len.y();
    return (c < (c1.radius + c2.radius) * (c1.radius + c2.radius));
}



bool MainWindow::contains(Circle c, QPoint p)
{
    QPoint c1(c.center - p);
    return (c.radius * c.radius > QPoint::dotProduct(c1, c1));
}



bool MainWindow::intersects_circle(Circle c, QRect r)
{
    for (int i = 0; i < r.width(); i++) {
        for (int j = 0; j < r.height(); j++) {
            if (contains(c, r.topLeft() + QPoint(i, j)))
                return true;
        }
    }
    return false;
}
