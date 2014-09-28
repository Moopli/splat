#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "/home/jobair/Downloads/splat/loadRom.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("SplatImage.png");
    ui->imageLabel->setPixmap(pix);

    // Set default frequency
    ui->normalRadioButton->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// The behaviours for the various buttons

// This is the about button.
// It should take us to https://github.com/e23walls/splat
// Firefox is used because it is always available on Linux
void MainWindow::on_aboutPushButton_clicked()
{
    system("firefox https://github.com/e23walls/splat");
}

// This is the 'exit' button, which will close the app when clicked
void MainWindow::on_exitPushButton_clicked()
{
    qApp->quit();
}

// These buttons load the various ROMs
// Please note the GUI will close after one
// of these are clicked.
void MainWindow::on_connect4PushButton_clicked()
{
    this->close();
    loadRom("c8games/CONNECT4", mFrequency);

}

void MainWindow::on_guessPushButton_clicked()
{
    this->close();
    loadRom("c8games/GUESS", mFrequency);
}

void MainWindow::on_hiddenPushButton_clicked()
{
    this->close();
    loadRom("c8games/HIDDEN", mFrequency);
}

void MainWindow::on_invadersPushButton_clicked()
{
    this->close();
    loadRom("c8games/INVADERS", mFrequency);
}

void MainWindow::on_tankPushButton_clicked()
{
    this->close();
    loadRom("c8games/TANK", mFrequency);
}

void MainWindow::on_mazePushButton_clicked()
{
    this->close();
    loadRom("c8games/MAZE", mFrequency);
}

void MainWindow::on_merlinPushButton_clicked()
{
    this->close();
    loadRom("c8games/MERLIN", mFrequency);
}

void MainWindow::on_missilePushButton_clicked()
{
    this->close();
    loadRom("c8games/MISSILE", mFrequency);
}

void MainWindow::on_brixPushButton_clicked()
{
    this->close();
    loadRom("c8games/BRIX", mFrequency);
}

void MainWindow::on_pongPushButton_clicked()
{
    this->close();
    loadRom("c8games/PONG", mFrequency);
}

void MainWindow::on_pong2PushButton_clicked()
{
    this->close();
    loadRom("c8games/PONG2", mFrequency);
}

void MainWindow::on_puzzlePushButton_clicked()
{
    this->close();
    loadRom("c8games/PUZZLE", mFrequency);
}

void MainWindow::on_syzygyPushButton_clicked()
{
    this->close();
    loadRom("c8games/SYZYGY", mFrequency);
}

void MainWindow::on_tictactoePushButton_clicked()
{
    this->close();
    loadRom("c8games/TICTAC", mFrequency);
}

void MainWindow::on_ufoPushButton_clicked()
{
    this->close();
    loadRom("c8games/UFO", mFrequency);
}

void MainWindow::on_vbrixPushButton_clicked()
{
    this->close();
    loadRom("c8games/VBRIX", mFrequency);
}

void MainWindow::on_wipeoffPushButton_clicked()
{
    this->close();
    loadRom("c8games/WIPEOFF", mFrequency);
}

void MainWindow::on_puzzlePushButton_2_clicked()
{
    this->close();
    loadRom("c8games/PUZZLE", mFrequency);
}

// Radio button section

void MainWindow::on_slowRadioButton_clicked()
{
     mFrequency = 300;
}

void MainWindow::on_normalRadioButton_clicked()
{
    mFrequency = 600;
}

void MainWindow::on_fastRadioButton_clicked()
{
    mFrequency = 900;
}

