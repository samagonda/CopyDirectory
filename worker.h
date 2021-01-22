#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include<copydir.h>
#include<QThread>
class Worker : public QObject
{
    Q_OBJECT

public:
    QString src_path;
    QString des_path;
    bool flag;
    explicit Worker(QObject *parent = nullptr);

signals:
    void sentpath(QString ,QString);
    void filesread();
    void done();
public slots:
    void pathfromW();

    void getpath(QString ,QString);
};

#endif // WORKER_H
