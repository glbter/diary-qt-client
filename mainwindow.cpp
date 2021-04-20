#include "mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QTextEdit>
#include <qlabel.h>
#include <QList>
#include <QVector>
#include <QFileDialog>
#include <QMessageBox>
#include <loginwindow.h>
#include <QWidget>


MainWindow::MainWindow(IClient& controller, QWidget *parent)
: QMainWindow(parent)
{
    setWindowTitle("Super-puper schodennyk");
    setGeometry(100, 100, 400, 500);
    setMinimumSize(200, 200);

    int paddingX = 10;
    int paddingY = 10;
    this->notesController = &controller;
    uiNotes = new QListWidget(this);
    uiNotes->addItem(QString("Here will be shown list of writings"));
    uiNotes->setGeometry(paddingX, paddingY, 380, 100);
    uiNotes->setCurrentRow(1);

    connect(uiNotes, SIGNAL(itemSelectionChanged()), this, SLOT(resfreshNoteTextField()));

    outputField = new QTextEdit("Your text here", this);
    outputField->setGeometry(paddingX, paddingY + 110, 190, 100);
    outputField->setReadOnly(true);

    int titleLine = paddingY + 230;
    titleLb = new QLineEdit(this);
    titleLb->setGeometry(paddingX, titleLine, 47, 20);
    titleLb->setReadOnly(true);
    titleLb->setText("Title: ");

    inputFieldNoteTitle = new QLineEdit(this);
    inputFieldNoteTitle->setGeometry(paddingX + 50, titleLine, 100, 20);

    int textLine = paddingY + 260;
    textLb = new QLineEdit(this);
    textLb->setGeometry(paddingX, textLine, 47, 20);
    textLb->setReadOnly(true);
    textLb->setText("Note: ");

    inputFieldNoteText = new QTextEdit(this);
    inputFieldNoteText->setGeometry(paddingX + 50, textLine, 240, 40);

    okButton = new QPushButton("Add", this);
    okButton->setGeometry(paddingX + 300, textLine, 40, 20);
    connect(okButton, SIGNAL(released()), this, SLOT(handleButton()));

    loadFileBtn = new QPushButton("Load file", this);
    loadFileBtn->setGeometry(paddingX, textLine + 50, 100, 35);
    connect(loadFileBtn, SIGNAL(released()), this, SLOT(saveFile()));

//    this->setVisible(true);
    openLogin(controller);
    refreshList();
}

void MainWindow::handleButton() {
    string title = inputFieldNoteTitle->text().toUtf8().constData();
    notesController->AddNote(
                inputFieldNoteTitle->text().toUtf8().constData(),
                inputFieldNoteText->toPlainText().toUtf8().constData());
    inputFieldNoteTitle->clear();
    inputFieldNoteText->clear();
    refreshList();
}

void MainWindow::refreshList() {
    uiNotes->clear();
    listNotes.clear();
    std::vector<Note> notesList = notesController->GetAllNotes();
    QStringList listItems = QStringList ();
    for(Note note: notesList) {
        listNotes.push_back(note);
        listItems << QString::fromStdString(note.getTitle());
    }
    uiNotes->addItems(listItems);
    uiNotes->setCurrentRow(0);
}

void MainWindow::resfreshNoteTextField() {
    int index = uiNotes->currentRow();
    Note& note = listNotes.at(index);
    outputField->setText(QString::fromStdString(note.getText()));
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Save Address Book"), "",
          tr("Text file (*.txt);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)){
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
        }
        QTextStream in(&file);
        QString qtext = in.readAll();
        string text = qtext.toUtf8().constData();
        string header = fileName.toUtf8().constData();
        int start = header.rfind('/') + 1;
        int stop = header.rfind('.');
        header = header.erase(stop);
        header = header.substr(start, stop);

        notesController->AddNote(header, text);
        file.close();

        refreshList();
    }
}


void MainWindow::openLogin(IClient& controller){
    LoginWindow* window = new LoginWindow(this, controller);
    //window->show();
    int res = window->exec();
    if(res == QDialog::Rejected){
        setWindowTitle("pasasi");
    }
    //if(controller.isLogined() == false){
    //    setWindowTitle("pasasi");
    //}
    //close();
   // hide();
}

MainWindow::~MainWindow()
{
    delete inputFieldNoteText;
    delete inputFieldNoteTitle;
    delete titleLb;
    delete textLb;
    delete outputField;
    delete uiNotes;
//    delete notesController;
    delete okButton;
    delete loadFileBtn;
}
