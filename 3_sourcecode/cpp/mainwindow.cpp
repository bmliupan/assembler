#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QFileDialog>
#include <QTextStream>
#include <QList>


#define TIMER_TIMEOUT   (500)

#define printNormal(x)              ui->textBrowser->setTextColor("blue");\
                                    ui->textBrowser->append(x);
#define printWarnning(x)            ui->textBrowser->setTextColor("red");\
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
    uint8_t flag = 0;
    uint8_t num = 0;
    QList<QString> linkPathList;
    QList<QString> dependPathList;

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        printWarnning("读取工程文件失败！");
        return;
    }
    printNormal("工程文件解析中...");
    QTextStream prjStream(&file);
    while (!prjStream.atEnd()) {
        QString str = prjStream.readLine();
        if (str.contains("[LINK]", Qt::CaseSensitive)) {
           flag = 1;
        }
        if (str.contains("[DEPEND]", Qt::CaseSensitive)) {
           flag = 2;
        }
        if ((flag == 1) && str.contains("ITEM", Qt::CaseSensitive)) {
           num = str.indexOf("=") + 1;
           linkPathList.append(str.mid(num));
        }
        if ((flag == 2) && str.contains("ITEM", Qt::CaseSensitive)) {
           num = str.indexOf("=") + 1;
           dependPathList.append(str.mid(num));
        }
        printNormal(str);
    }
    file.close();

    return;
}
