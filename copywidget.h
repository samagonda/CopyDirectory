#ifndef COPYWIDGET_H
#define COPYWIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QFileDialog>
#include<QDir>
#include<QDirIterator>
#include<QDebug>
#include<QString>
#include<copydir.h>
#include<worker.h>
#include<QThread>
#include<QtConcurrent/QtConcurrent>
#include<QProgressDialog>
class CopyWidget : public QWidget
{
    Q_OBJECT
    QPushButton *folder1,*folder2,*copy;
    QLineEdit *line1,*line2;
    QHBoxLayout *hbox1,*hbox2;
    QVBoxLayout *vbox;
    QString *src_path;
    QString *des_path;
    QThread *workerthread;
    QProgressDialog *progressDialog;
    Worker *worker;
    QStringList *files;
public:
    CopyWidget(QWidget *parent = 0);
    ~CopyWidget();

signals:
    void paths(QString ,QString );
private slots:
    void setvalue1();
    void complete();
    void onfolder1();
    void onfolder2();
    void oncopyclicked();
};

#endif // COPYWIDGET_H
