#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer m_tickTimer;
signals:
    void sigPutFsmEvent(QByteArray eventData);
private slots:
    void onNewFsmEvent(QByteArray eventData);
    void onTick();

};

#endif // MAINWINDOW_H
