#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowTitle("Notepad");
  this->setCentralWidget(
      ui->textEdit); // this means that text_edit will take up all the screen
  this->on_actionNew_triggered();
  QApplication::setAttribute(
      Qt::AA_DisableWindowContextHelpButton); // disable help buttons
}

MainWindow::~MainWindow() // destructor
{
  delete ui;
}

QMessageBox::ButtonRole
createMessageBox(QWidget *parent, const QMessageBox::Icon &icon,
                 const QString &windowTitle, const QString &windowText,
                 const QString &Button_1, const QString &Button_2)
{
  QMessageBox dialogBox(parent);
  dialogBox.setIcon(icon);
  dialogBox.setWindowTitle(windowTitle);
  dialogBox.setText(windowText);
  dialogBox.addButton(Button_1, QMessageBox::AcceptRole);
  dialogBox.addButton(Button_2, QMessageBox::RejectRole);
  return static_cast<QMessageBox::ButtonRole>(dialogBox.exec());
}

bool MainWindow::isTextEmpty() const
{
  return (ui->textEdit->toPlainText().isEmpty()) ? true : false;
}

void MainWindow::on_actionNew_triggered()
{
  if (!isTextEmpty())
  {
    if (createMessageBox(this, QMessageBox::Icon::Warning, "New File...",
                         "Are you sure, this will delete all text", "Yes",
                         "No") == QMessageBox::RejectRole)
    {
      return;
    }
  }

  currentFile.clear();   // clears the string and nulls it
  ui->textEdit->clear(); // deletes all text in the text editor
}

void MainWindow::on_actionOpen_triggered()
{
  QDialog confirm(this);

  currentFile = QFileDialog::getOpenFileName(this, QString("Open a file.."),
                                             QString(), "*.*");

  if (QFileInfo::exists(currentFile))
  {
    ui->textEdit->clear(); // deletes all text in the text editor
    QFile file(currentFile);

    if (!file.open(
            QIODevice::ReadOnly |
            QIODevice::Text)) // QIODevice::Text is the same as QFile::Text
    {
      return;
    }
    QTextStream in(&file);
    ui->textEdit->insertPlainText(in.readAll());
  }
  else
  {
    on_actionOpen_triggered(); // if file doesn't exist run again
  }
}

void MainWindow::on_actionExit_triggered()
{
  if (!isTextEmpty())
  {
    if (createMessageBox(this, QMessageBox::Icon::Warning, "Exit..",
                         "Are you sure you want to exit?", "Yes",
                         "No") == QMessageBox::ButtonRole::AcceptRole)
    {
      QApplication::quit();
    }
  }
  else
  {
    QApplication::quit();
  }
}

void MainWindow::on_actionPrint_triggered()
{
  QPrinter *printer{};
  QPrintDialog printDialog(printer, this);
  printer = printDialog.printer();
  if (printDialog.exec() == QPrintDialog::Accepted)
  {
    QTextDocument *printThis;
    printThis = ui->textEdit->document();
    printThis->print(printer);
  }
}

void MainWindow::on_actionSave_triggered()
{
  if (!currentFile.isNull())
  {
    QFile file(currentFile);
    QTextDocument *writing = ui->textEdit->document();
    QString text = writing->toPlainText();
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      QTextStream stream(&file);
      stream << text;
      return;
    }
  }
  else if (isTextEmpty() || currentFile.isNull())
  {
    QString fileName = QInputDialog::getText(
        this, "Enter Name..", "Please enter the name for this file");
    if (fileName.isNull())
    {
      return;
    }
    else
    {
      QFile newFile(fileName);
      QFileDialog saveFile;
      saveFile.setFileMode(QFileDialog::AnyFile);
      QString dir =
          saveFile.getSaveFileName(this, "Save..", fileName, "", nullptr);
      if (!dir.isNull())
      {
        currentFile = dir;
        if (QFileInfo::exists(dir))
        {
          on_actionSave_triggered();
        }
        else
        {
          std::ofstream out(dir.toStdString()); // create file
          on_actionSave_triggered();
        }
      }
    }
  }
}

void MainWindow::on_actionUndo_triggered() { ui->textEdit->undo(); }

void MainWindow::on_actionRedo_triggered() { ui->textEdit->redo(); }
