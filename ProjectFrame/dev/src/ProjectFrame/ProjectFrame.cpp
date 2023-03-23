#include "ProjectFrame.h"
#include "ui_ProjectFrame.h"



ProjectFrame::ProjectFrame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProjectFrame)
{
    ui->setupUi(this);
}

ProjectFrame::~ProjectFrame()
{
    delete ui;
}

