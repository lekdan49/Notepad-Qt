#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  // contructors
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  // methods
  bool isTextEmpty() const;

private slots:
  void on_actionNew_triggered();

  void on_actionOpen_triggered();

  void on_actionExit_triggered();

  void on_actionPrint_triggered();

  void on_actionSave_triggered();

  void on_actionUndo_triggered();

  void on_actionRedo_triggered();

private:
  Ui::MainWindow *ui;
  QString currentFile; // default initializes currentFile to a null QString
};
#endif // MAINWINDOW_H
