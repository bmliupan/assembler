#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFileDialog>

#define TIMER_TIMEOUT   (500)

#define printNormal(x)              ui->textBrowser->setTextColor("blue");\
                                    ui->textBrowser->append(x);
#define printWarnning(x)             ui->textBrowser->setTextColor("red");\
                                    ui->textBrowser->append(x);



QString filePath = "C:";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(timeoutHandle()));
    pTimer->start(TIMER_TIMEOUT);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timeoutHandle()
{
    int nCurrentValue = ui->progressBar->value();
    nCurrentValue ++;
    if (nCurrentValue >= 100) {
        nCurrentValue = 0;
    }

    ui->progressBar->setValue(nCurrentValue);
}

void MainWindow::on_loadButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this,tr("导入工程文件"),filePath,tr("prj文件(*.prj);;"));

    if (filePath == "") {
        printWarnning("工程文件选择取消！");
        return; //取消对话框则直接退出
    } else {
        printNormal("工程文件已选择！");
        printNormal("文件路径：");
        printNormal(filePath);
    }

}

void MainWindow::on_buildButton_clicked()
{
    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly)) {
        printWarnning("读取工程文件失败！");
        return;
    }
    printNormal("工程文件解析中...");

}
