#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent)
{
    qDebug()<<"worker therad id"<<QThread::currentThreadId();
    flag=false;

}

void Worker::pathfromW()
{
    qDebug()<<"worker therad id"<<QThread::currentThreadId();
    CopyDir *copy= new CopyDir;
    connect(this, SIGNAL(sentpath(QString ,QString )), copy, SLOT( getpaths(QString,QString )));
    connect(this, SIGNAL(sentpath(QString ,QString )), copy, SLOT(copyPath_1(QString,QString)));
    connect(copy,SIGNAL(setsize()),this,SIGNAL(filesread()));
    connect(copy,SIGNAL(copingcomplete()),this,SIGNAL(done()));


}

void Worker::getpath(QString src, QString des)
{

    emit sentpath(src,des);
}
