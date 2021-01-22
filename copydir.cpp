#include "copydir.h"

QString CopyDir::getDes_path() const
{
    return des_path;
}

void CopyDir::setDes_path(const QString &value)
{
    des_path = value;
}

QString CopyDir::getSrc_path() const
{
    return src_path;
}

void CopyDir::setSrc_path(const QString &value)
{
    src_path = value;
}

CopyDir::CopyDir(QObject *parent) : QObject(parent)
{
    
    
}
void CopyDir:: getpaths(QString src,QString des)
{
    
    src_path=src;
    des_path=des;

}
bool CopyDir::copyPath_1(QString sourceDir, QString destinationDir)
{


    QDir originDirectory(sourceDir);
    if (! originDirectory.exists())
    {
        return false;
    }

    QDir destinationDirectory(destinationDir);
    if (! destinationDirectory.exists())
    {
        return false;
    }

    foreach (QString d, originDirectory.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {

        QString dst_path = destinationDir + "/" + d;
        originDirectory.mkpath(dst_path);
        copyPath_1(sourceDir+ "/" + d, dst_path);

    }
    foreach (QString fileName, originDirectory.entryList(QDir::Files))
    {
        QFile::copy(sourceDir + "/" +  fileName, destinationDir + "/" + fileName);
        emit setsize();
    }
    QDir finalDestination(destinationDir);
    finalDestination.refresh();

    if(finalDestination.exists())
    {
        emit copingcomplete();
        return true;
    }
    return false;
}

QString CopyDir::filename(QString path)
{
    QString folder;
    QString destpath;
    for(int i=src_path.size();i<path.size();i++)
    {
        folder.append(path.at(i));
    }
    destpath=des_path+folder;
    return destpath;

}
