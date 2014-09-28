#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    // Button behaviours
    void on_aboutPushButton_clicked();

    void on_exitPushButton_clicked();

    void on_normalRadioButton_clicked();

    void on_slowRadioButton_clicked();

    void on_fastRadioButton_clicked();

    void on_connect4PushButton_clicked();

    void on_pongPushButton_clicked();

    void on_guessPushButton_clicked();

    void on_hiddenPushButton_clicked();

    void on_invadersPushButton_clicked();

    void on_tankPushButton_clicked();

    void on_mazePushButton_clicked();

    void on_merlinPushButton_clicked();

    void on_missilePushButton_clicked();

    void on_brixPushButton_clicked();

    void on_pong2PushButton_clicked();

    void on_puzzlePushButton_clicked();

    void on_syzygyPushButton_clicked();

    void on_tictactoePushButton_clicked();

    void on_ufoPushButton_clicked();

    void on_vbrixPushButton_clicked();

    void on_wipeoffPushButton_clicked();

    void on_puzzlePushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int mFrequency = 600; // This is the default frequency.
};

#endif // MAINWINDOW_H
