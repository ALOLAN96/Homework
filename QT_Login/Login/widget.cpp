#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //设置界面为固定大小(428*330),更改标题为QQforLan
    this->setFixedSize(428, 330);
    this->setWindowTitle("QQforLan");

    //设置密码输入框为隐式输入
    ui->PasswordEdit->setEchoMode(QLineEdit::Password);

    //添加登录取消图标
    ui->Loginbtn->setIcon(QIcon(":/icon/login.png"));
    ui->CancleBtn->setIcon(QIcon(":/icon/cancel.png"));

    //添加用户名密码图标
    ui->UsernameLab->setPixmap(QPixmap(":/icon/userName.jpg"));
    ui->UsernameLab->setFixedSize(28,28);     //设置控件的固定大小
    ui->UsernameLab->setScaledContents(true);  //设置控件中的内容自适应控件的大小

    ui->PasswordLab->setPixmap(QPixmap(":/icon/passwd.jpg"));
    ui->PasswordLab->setFixedSize(28,28);     //设置控件的固定大小
    ui->PasswordLab->setScaledContents(true);  //设置控件中的内容自适应控件的大小

    QMovie *movie = new QMovie(":/icon/d6ea-irtymmv4160044.gif");
    ui->Loginlab->setMovie(movie);
    movie->start();

    QMovie *movie2 = new QMovie(":/icon/5a79837079e8cc1cf4ab0a89554c50a8969ac522f87b93d48.gif");
    ui->Loginlab2->setMovie(movie2);
    ui->Loginlab2->setScaledContents(true);
    movie2->start();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_Loginbtn_clicked()
{
    if (ui->PasswordEdit->text() == "123456" && ui->UsernameEdit->text() == "admin")
    {
        QMessageBox::StandardButton btn = QMessageBox::information(
                    this,
                    "提示信息",
                    "登录成功",
                    QMessageBox::Ok);
        if (QMessageBox::Ok == btn)
        {
            this->close();
        }
    }
    else
    {
        QMessageBox::StandardButton btn = QMessageBox::critical(
                    this,
                    "警告信息",
                    "账号密码错误，是否重新登录",
                    QMessageBox::Yes | QMessageBox::No);
        if (QMessageBox::Yes == btn)
        {
            ui->PasswordEdit->clear();
            ui->UsernameEdit->clear();
        }
        else if(QMessageBox::No == btn)
        {
            this->close();
        }
    }
}

void Widget::on_CancleBtn_clicked()
{
    QMessageBox::StandardButton btn = QMessageBox::warning(
                this,
                "错误信息",
                "是否要退出登录",
                QMessageBox::Yes | QMessageBox::No);
    if (QMessageBox::Yes == btn)
    {
        this->close();
    }
    else if(QMessageBox::No == btn)
    {

    }

}
