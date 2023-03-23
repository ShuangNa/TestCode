#ifndef PROJECTFRAME_H
#define PROJECTFRAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ProjectFrame; }
QT_END_NAMESPACE

class ProjectFrame : public QMainWindow
{
    Q_OBJECT

public:
    ProjectFrame(QWidget *parent = nullptr);
    ~ProjectFrame();

private:
    Ui::ProjectFrame *ui;
};
#endif // PROJECTFRAME_H
