#include "copywidget.h"

CopyWidget::CopyWidget(QWidget *parent)
    : QWidget(parent)
{
    folder1=new QPushButton("Browse");
    folder2=new QPushButton("Browse");
    copy=new QPushButton("Copy");
    line1=new QLineEdit;
    line2=new QLineEdit;
    hbox1=new QHBoxLayout;
    hbox2=new QHBoxLayout;
    vbox=new QVBoxLayout;
    hbox1->addWidget(line1);
    hbox1->addWidget(folder1);
    hbox2->addWidget(line2);
    hbox2->addWidget(folder2);
    vbox->addLayout(hbox1);
    vbox->addLayout(hbox2);
    vbox->addWidget(copy);
    this->setLayout(vbox);
    connect(folder1,SIGNAL(clicked()),this,SLOT(onfolder1()));
    connect(folder2,SIGNAL(clicked()),this,SLOT(onfolder2()));
    connect(copy,SIGNAL(clicked()),this,SLOT(oncopyclicked()));
    worker=new Worker;
    workerthread=new QThread;
    worker->moveToThread(workerthread);
    connect(this,SIGNAL(paths(QString ,QString )),worker,SLOT(getpath(QString ,QString)));
    connect(workerthread,SIGNAL(started()), worker,SLOT(pathfromW()));
    connect(worker,SIGNAL(done()),this,SLOT(complete()));
    connect(worker,SIGNAL(filesread()),this,SLOT(setvalue1()));
    workerthread->start();
    src_path=new QString;
    des_path=new QString;

}
void CopyWidget::onfolder1()
{
    *src_path= QFileDialog::getExistingDirectory(this,"open  source folder","C://");
    line1->setText(*src_path);
}
void CopyWidget::onfolder2()
{
    *des_path= QFileDialog::getExistingDirectory(this,"open  source folder","C://");
    line2->setText(*des_path);
}
void CopyWidget::oncopyclicked()
{
    emit paths(*src_path,*des_path);
    QDirIterator it(*src_path, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    files=new QStringList;
    while (it.hasNext())
    {*files << it.next();}

    //    connect(workerthread, &QThread::finished, worker, &QObject::deleteLater);

    progressDialog=new QProgressDialog(this) ;
    progressDialog->setCancelButtonText(tr("&Cancel"));
    progressDialog->setRange(0, files->size());
    progressDialog->setWindowTitle(tr("Copy Files"));
    progressDialog->show();
}
CopyWidget::~CopyWidget()
{

}

void CopyWidget::setvalue1()
{
    static int i=0;
    ++i;
    progressDialog->setValue(i);
    progressDialog->setLabelText(tr("Coping file number %1 of %n...",0,files->size()).arg(i));
    if(files->size()==i)
    {

        i=0;
    }
}
void CopyWidget::complete()
{
    progressDialog->cancel();
}
