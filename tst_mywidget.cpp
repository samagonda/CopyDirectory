#include <QtTest>
#include <QCoreApplication>
#include<QtWidgets>
#include<QLineEdit>
#include<copywidget.h>
#include<copydir.h>
#include<worker.h>
#include<QDir>
#include<QFileDialog>
#include<QSignalSpy>
// add necessary includes here

class mywidget : public QObject
{
    Q_OBJECT

public:
    mywidget();
    ~mywidget();

private slots:
    void test_case1();
    void test_paths();
    void test_directory();
    void test_copyfun();
    void test_filecount();
    void test_copyDirSignals();
    void test_copywidgetSignals();
    void test_dosomething();
};

mywidget::mywidget()
{

}

mywidget::~mywidget()
{

}

void mywidget::test_case1()
{
    QLineEdit lineEdit;
    QTest::keyClicks(&lineEdit, "hello world");
    QCOMPARE(lineEdit.text(), QString("hello world"));
}
void mywidget::test_paths()
{
    QString src="C:/Dell";
    QString src_path= QFileDialog::getExistingDirectory(nullptr,"open  source folder","C:/");

    QString des="D:/Temp";
    QString des_path= QFileDialog::getExistingDirectory(nullptr,"open  destination folder","C:/");
    QCOMPARE(src,src_path);
    QCOMPARE(des,des_path);
}
void mywidget::test_directory()
{
    QString sourcepath="C:/Dell";
    QDir originDirectory(sourcepath);
    QString des_path="D:/shashi";
    QDir Des_Directory(des_path);

    QVERIFY2(originDirectory.exists(),"this directory is not exits");
    QVERIFY2(Des_Directory.exists(),"this directory is not exits");
}

void mywidget::test_copyfun()
{
    CopyDir cd;
    QString src="C:/Dell";
    QString des="D:/Temp";
    bool result=cd.copyPath_1(src,des);
    QCOMPARE(true,result);
}

void mywidget::test_filecount()
{
    QString src="C:/Dell";
    int count=2;
    QDirIterator it(src, QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList *files=new QStringList;
    while (it.hasNext())
    {*files << it.next();}
    QCOMPARE(count,files->size());
}

void mywidget::test_copyDirSignals()
{
    CopyDir cd;
    QString src="C:/Dell";
    QString des="D:/Temp";
    QSignalSpy spy(&cd, SIGNAL(setsize()));
    QSignalSpy spy1(&cd, SIGNAL(copingcomplete()));

    // do something that triggers the signal
    cd.copyPath_1(src,des);

    QCOMPARE(spy.count(), 2); // make sure the signal was emitted exactly two time
    QVERIFY2(spy1.isValid(),"signal failed");
}

void mywidget::test_copywidgetSignals()
{
    CopyWidget wi;
    QSignalSpy spy(&wi, SIGNAL(paths(QString ,QString )));

    // do something that triggers the signal
    QTest::mouseClick(wi.copy, Qt::LeftButton);

    QVERIFY2(spy.isValid(),"signal failed");
    QList<QVariant> arguments = spy.takeFirst();
    QVERIFY(arguments.at(0).type() == QVariant::String);
    QVERIFY(arguments.at(1).type() == QVariant::String);
}

void mywidget::test_dosomething()
{
    QTest::addColumn<QTestEventList>("events");
     QTest::addColumn<QString>("expected");

     QTestEventList list1;
     list1.addKeyClick('a');
     QTest::newRow("char") << list1 << "a";

     QTestEventList list2;
     list2.addKeyClick('a');
     list2.addKeyClick(Qt::Key_Backspace);
        QTest::newRow("there and back again") << list2 << "";
}

QTEST_MAIN(mywidget)

#include "tst_mywidget.moc"
