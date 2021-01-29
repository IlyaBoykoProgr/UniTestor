#include "thewindow.h"
#include "ui_thewindow.h"
#include <QScreen>

TheWindow::TheWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TheWindow)
{
    ui->setupUi(this);
    connect(ui->butt_open,SIGNAL(clicked()),this,SLOT(on_test_open_triggered()));
}

void TheWindow::on_test_open_triggered()
{
    QUrl path=QFileDialog::getOpenFileUrl(this,"Открытие теста",QUrl(),"*.ut");
    if(path.isEmpty())return;
    openTest(path.toString().replace("file:///",""));
}

void TheWindow::openTest(QString path){
    hide();
    QFile file(path.toUtf8().data());
    file.open(QFile::ReadOnly);
    uint64_t p_count=0,right_count=0;
    QDataStream qds(&file);
    qds>>p_count;
    for(uint64_t i=0;i<p_count;i++){
        pagedata temp;
        temp<<qds;
        testingDialog test(this,&temp);
        test.getResultTo(right_count);
    }
    QMessageBox::information(this,path,"Набрано "+QString::number(right_count)+" из "+QString::number(p_count));
    show();
}

void TheWindow::on_test_create_triggered()
{
    if(
       QMessageBox::question(this,"Подтверждение","Действительно хотите создать тест?")
       == QMessageBox::No
    )return;
    QString path=QFileDialog::getOpenFileUrl(this,"Выберите место сохранения",QUrl(),"*.ut").toString().replace("file:///","");
    uint64_t p_count=0;
    QList<pagedata> page;
    do{
        p_count++;
        pagedata cur_page;
        pageCreationDialog pcd;
        pcd.getTo(&cur_page);
        page.append(cur_page);
    }while(QMessageBox::question(this,"","Создать еще вопрос в тесте?")==QMessageBox::Yes);
    QFile file(path.toUtf8().data());
    file.open(QFile::WriteOnly|QFile::Truncate);
    QDataStream qds(&file);
    qds<<p_count;
    for(uint64_t i=0;i<p_count;i++) page[i]>>qds;
    file.close();
    QMessageBox::information(this,"Успех","Сохранено!");
}

TheWindow::~TheWindow(){delete ui;}
