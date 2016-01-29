#ifndef LASER_VIEW_H
#define LASER_VIEW_H

#include <QWidget>
#include <QWebPage>
#include <QWebFrame>
#include <QGraphicsView>
#include <QGraphicsWebView>
#include <QGLWidget>
namespace Ui {
class Laser_View;
}

class Laser_View : public QWidget
{
    Q_OBJECT

public:
    explicit Laser_View(QWidget *parent = 0);
    ~Laser_View();
    void reload(const QString& str);
private:
    Ui::Laser_View *ui;
    QGraphicsScene *scene;
    QGraphicsWebView *web_view;
Q_SIGNALS:
    void reload_view(QString);
public slots:
    void addJS_object();
};

#endif // LASER_VIEW_H
