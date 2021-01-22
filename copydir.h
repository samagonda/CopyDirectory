#ifndef COPYDIR_H
#define COPYDIR_H

 #include <QObject>
#include<QFileDialog>
#include<QDir>
#include<QDirIterator>
#include<QThread>
#include<QDebug>
class CopyDir : public QObject
{
    Q_OBJECT
public:
    QString des_path;
    QString src_path;

    explicit CopyDir(QObject *parent = nullptr);
    QString filename(QString path);

    QString getDes_path() const;
    void setDes_path(const QString &value);

    QString getSrc_path() const;
    void setSrc_path(const QString &value);

signals:
    void setsize();
    void copingcomplete();
public slots:
    bool copyPath_1(QString , QString );
    void getpaths(QString src, QString des);
};

#endif // COPYDIR_H
