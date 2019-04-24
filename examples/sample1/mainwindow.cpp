#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "samplemachine.h"

static SampleMachine s_machine;
static FsmStateMachine *p_machine;

static MainWindow *s_windowInstance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    p_machine = SampleMachineInit(&s_machine);

    connect(this, &MainWindow::sigPutFsmEvent, this, &MainWindow::onNewFsmEvent, Qt::QueuedConnection);
    s_windowInstance = this;
    m_tickTimer.setSingleShot(false);
    m_tickTimer.start(1000);
    connect(&m_tickTimer, &QTimer::timeout, this, &MainWindow::onTick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewFsmEvent(QByteArray eventData)
{
    FsmStateMachine *machine;
    QByteArray data;
    memcpy(&machine, eventData.constData(), sizeof(SampleMachine *));
    data = eventData.mid(sizeof(SampleMachine *));
    fsm_dispatch_event(machine, (void *)data.constData(), data.length());
}

void MainWindow::onTick()
{
    FsmEventData trigger;
    trigger.trigger = TrTick;
    p_machine->put(p_machine, &trigger, sizeof(trigger));
}

//will be called from c code
extern "C"{
void sample_fsm_put(SampleMachine *me, void *p_event_data, uint16_t event_size)
{
    QByteArray eventData;
    eventData.append((char *)&me, sizeof(SampleMachine *));
    eventData.append((char *)p_event_data, event_size);
    emit s_windowInstance->sigPutFsmEvent(eventData);
}
}
