#include "laser_view.h"
#include "ui_laser_view.h"
#include <QDir>
Laser_View::Laser_View(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Laser_View)
{
    ui->setupUi(this);
    QString path;
    QDir dir;
    path=dir.currentPath();
    std::string temp;
    temp="file:///";
    temp+=path.toStdString().c_str();
    temp+="/examples/Laser_viewer.html";




       QWebSettings::globalSettings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled, true);
       ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
       ui->graphicsView->setViewport(new QGLWidget());

       scene = new QGraphicsScene(ui->graphicsView);
       web_view = new QGraphicsWebView();

       scene->addItem(web_view);
       ui->graphicsView->setScene(scene);
    web_view->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    web_view->settings()->setAttribute(QWebSettings::WebGLEnabled, true);
    web_view->settings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled, true);
    web_view->load(QUrl(temp.c_str()));
    ui->graphicsView->resize(640,480 );
    web_view->resize(640,480 );

    connect(web_view->page()->mainFrame(),SIGNAL(javaScriptWindowObjectCleared()),this,SLOT(addJS_object()));


}

Laser_View::~Laser_View()
{
    delete ui;
}

void Laser_View::addJS_object(){
web_view->page()->mainFrame()->addToJavaScriptWindowObject("laser_view",this);
}

void Laser_View::reload(const QString & str){
    Q_EMIT reload_view(str);
}
