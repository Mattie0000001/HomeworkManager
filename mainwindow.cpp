#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDebug>

#include "createDB.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 连接数据库
    p_database = new CreateDb;
    p_database->connectDB();

    // 默认radio选中admin
    ui->Radio_admin->setChecked(true);
    thisuser = "admin";

    // 信号与槽 --- student界面与teacher界面关闭时重新弹出登录界面
    connect(p_stu, &Stu::mainwindow_show, this, &MainWindow::open_mainwindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open_mainwindow()
{
    this->show();
}

void MainWindow::on_Btn_login_clicked()
{
    qDebug() << "登录！";
    // 获得id和密码
    ID = ui->Input_ID->text();
    password = ui->Input_password->text();

    if (ID.isEmpty()) {
        // id 为空
        QMessageBox::information(this, "提示", "请输入ID", QMessageBox::Ok);
    } else if (password.isEmpty()) {
        // 密码为空
        QMessageBox::information(this, "提示", "请输入密码", QMessageBox::Ok);
    } else {
        QString limit_info = QString("id = %1").arg(ID);
        // 调用函数查询
        QString rec_value = p_database->select_data(thisuser, limit_info);
        if (rec_value == NULL) {
            QMessageBox::information(this, "提示", "查询失败", QMessageBox::Ok);
        } else if (rec_value == password) {
        // 匹配，登录成功
            qDebug() << "----------登陆成功-------------";
            openUI();
        } else {
            QMessageBox::information(this, "提示", "密码错误！", QMessageBox::Ok);
        }
    }
}

void MainWindow::openUI () {
    if (thisuser == "admin") {
        this->close();
        p_admin = new Administrator;
        p_admin->show();
    } else if (thisuser == "student") {
        this->close();
        p_stu = new Stu;
        p_stu->init(ID); // 初始化
        p_stu->show(); //弹出
    } else {
        this->close();
        // teacher 弹出
    }
}

// radio选中相应给thisuser赋值
void MainWindow::on_Radio_student_clicked()
{
    thisuser = "student";
}

void MainWindow::on_Radio_teacher_clicked()
{
    thisuser = "teacher";
}

void MainWindow::on_Radio_admin_clicked()
{
    thisuser = "admin";
}
