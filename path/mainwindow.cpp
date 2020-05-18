#include <QMovie>
#include <QLabel>
#include <QProgressBar>
#include <QLineEdit>
#include <QDebug>
#include <QPushButton>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"


const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH = 650;
const int DEFAULT_WIDTH = 200;
const int DEFAULT_HEIGHT= 30;
const int FREE_SPACE = 10;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("soooper pooper ultra hyper hack");

    this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));

    QLabel* copyright = new QLabel("© kyazimov.ru, 2020. All rights reserved.", this);
            copyright->setGeometry(WINDOW_WIDTH - DEFAULT_WIDTH * 5 / 4, WINDOW_HEIGHT - DEFAULT_HEIGHT,
                                   DEFAULT_WIDTH * 5 / 4, DEFAULT_HEIGHT);
            copyright->show();


    background = new QLabel(this);
        background->setScaledContents(true);
        setCentralWidget(background);

    QMovie* ricardo = new QMovie("data\\ricardo.gif");
            background->setMovie(ricardo);
            ricardo->start();

    QMediaPlaylist* play_list = new QMediaPlaylist();
                    play_list->addMedia(QUrl("shrek.mp3"));
                    play_list->setPlaybackMode(QMediaPlaylist::Loop);


    QMediaPlayer* music = new QMediaPlayer();
                  music->setPlaylist(play_list);
                  music->setVolume(1);
                  music->play();

    QPushButton* file_button = new QPushButton("Select file", background);
        file_button->setGeometry(WINDOW_WIDTH / 2 - file_button->width(),
                                 WINDOW_HEIGHT / 2 - file_button->height(), file_button->width() * 2, file_button->height() * 2);

    connect(file_button, &QPushButton::clicked, [this]()
    {
        open_file();

        if(file_name.length() == 0)
            return;

        file_choosen();
    });
}


void MainWindow::file_choosen()
{
    qDeleteAll(background->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));

    QLabel* pass_msg = new QLabel("Enter new password:", background);
            pass_msg->setStyleSheet("QLabel { color: white; font-size: 10pt; }");
            pass_msg->setGeometry(WINDOW_WIDTH / 2 - DEFAULT_WIDTH / 2,
                                  WINDOW_HEIGHT / 2 - 5 * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
            pass_msg->show();

    QLineEdit* pass_input = new QLineEdit(background);
               pass_input->setGeometry(WINDOW_WIDTH / 2 - DEFAULT_WIDTH / 2,
                                       WINDOW_HEIGHT / 2 - 4 * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
               pass_input->show();

    QLabel* confirm_msg = new QLabel("Confirm password:", background);
            confirm_msg->setStyleSheet("QLabel { color: white; font-size: 10pt; }");
            confirm_msg->setGeometry(WINDOW_WIDTH / 2 - DEFAULT_WIDTH / 2,
                                    WINDOW_HEIGHT / 2 - 3 * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
            confirm_msg->show();

    QLineEdit* confirm_input = new QLineEdit(background);
               confirm_input->setGeometry(WINDOW_WIDTH / 2 - DEFAULT_WIDTH / 2,
                                          WINDOW_HEIGHT / 2 - 2 * DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_HEIGHT);
               confirm_input->show();

    QPushButton* hack = new QPushButton("HACK", background);
                 hack->setGeometry(WINDOW_WIDTH / 2 - DEFAULT_WIDTH / 2,
                                   WINDOW_HEIGHT / 2 - DEFAULT_HEIGHT + FREE_SPACE, DEFAULT_WIDTH, 3 * DEFAULT_HEIGHT);
                 hack->show();

    connect(hack, &QPushButton::clicked, [this, confirm_input, pass_input]()
    {
        if(confirm_input->text() != pass_input->text())
        {
            QLabel* error_msg = new QLabel("bruh, passwords are not same", background);
                    error_msg->setStyleSheet("QLabel { color: red; font-size: 9pt; }");
                    error_msg->setGeometry(WINDOW_WIDTH / 2 - DEFAULT_WIDTH / 2,
                                           WINDOW_HEIGHT / 2 + 2 * DEFAULT_HEIGHT + 2 * FREE_SPACE, DEFAULT_WIDTH, DEFAULT_HEIGHT);
                    error_msg->show();

                    return;
        }
        password = new QString(pass_input->text());
        du_hack();
    });
}


void MainWindow::du_hack()
{
    qDeleteAll(background->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));

    QMovie* winlocker = new QMovie("data\\winlocker.gif");
            background->setMovie(winlocker);
            winlocker->start();

    QPushButton* paid = new QPushButton("I PAID", background);
                 paid->setGeometry(WINDOW_WIDTH / 2 - DEFAULT_WIDTH / 2,
                                   WINDOW_HEIGHT / 2 - DEFAULT_HEIGHT, DEFAULT_WIDTH, 2 * DEFAULT_HEIGHT);
                 paid->show();


    connect(paid, &QPushButton::clicked, [this]()
    {
        qDeleteAll(background->findChildren<QWidget*>("", Qt::FindDirectChildrenOnly));

        QMovie* hacked = new QMovie("data\\hacked.gif");
        background->setMovie(hacked);

        hacked->start();

        if(!du_hack_mein(file_name.toStdString().c_str(), password->toStdString().c_str()))
        {
            QLabel* error_msg = new QLabel("NOT", background);
                    error_msg->setStyleSheet("QLabel { color: red; font-size: 30pt; }");
                    error_msg->setGeometry(DEFAULT_WIDTH,
                                           WINDOW_HEIGHT, 3 * DEFAULT_WIDTH, 2 * DEFAULT_HEIGHT);
                    error_msg->show();
        }

        QPushButton* close_button = new QPushButton("CLOSE", background);
                     close_button->setGeometry(WINDOW_WIDTH - DEFAULT_WIDTH, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
                     close_button->show();

        connect(close_button, &QPushButton::clicked, [this]{close();});
    });
}


void MainWindow::open_file()
{
    file_name = QFileDialog::getOpenFileName(this, "Open file", "C:", "*.com");
}


MainWindow::~MainWindow()
{
    delete ui;
}


const unsigned int ENTER = 0xD;
const unsigned int ORG = 0x100;
const unsigned int HASH_POS = 0x152;
const unsigned int BYTE_VALUES = 256;


bool du_hack_mein(const char* file_name, const char* password)
{
    if(file_name == nullptr  || password == nullptr)
        return false;

    FILE* hackable = fopen(file_name, "r+");

    if(hackable == nullptr)
        return false;

    unsigned sum = ENTER;
    for(unsigned int i = 0; password[i] != 0; ++i)
        sum += password[i];

    fseek(hackable, HASH_POS - ORG, SEEK_SET);
    fprintf(hackable, "%c%c", sum % BYTE_VALUES, sum / BYTE_VALUES);

    fclose(hackable);
    return true;
}

