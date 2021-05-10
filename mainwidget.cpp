#include "mainwidget.h"
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


MainWidget::MainWidget(Client &controller, QWidget *parent) : QWidget(parent)
{
    int paddingX = 10;
    int paddingY = 10;
    this->notesController = &controller;
    uiNotes = new QListWidget(this);
    //uiNotes->addItem(QString("Here will be shown list of writings"));
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

    connect(&controller, &Client::allNotesReceived, this, &MainWidget::refreshList);
    //connect(&controller, SIGNAL(noteGetted()), this, SLOT());
    connect(&controller, &Client::noteAdded, this, &MainWidget::addedNote);


    lastAddedNote.setId(0);
//    this->setVisible(true);
    controller.GetAllNotes();
}

void MainWidget::handleButton() {
    string title = inputFieldNoteTitle->text().toUtf8().constData();
    string text = inputFieldNoteText->toPlainText().toUtf8().constData();
    inputFieldNoteTitle->clear();
    inputFieldNoteText->clear();
    addNote(title, text);
}

void MainWidget::addNote(const string title, const string text){
    notesController->AddNote(title, text);
    lastAddedNote.setText(text);
    lastAddedNote.setTitle(title);
}

void MainWidget::refreshList(vector<Note> notesList) {
    uiNotes->clear();
    listNotes.clear();
    int id = 0;
    QStringList listItems = QStringList ();
    for(Note note: notesList) {
        id = id + 1;
        note.setId(id);
        listNotes.push_back(note);
        listItems << QString::fromStdString(note.getTitle());
    }
    lastAddedNote.setId(id);
    uiNotes->addItems(listItems);
    uiNotes->setCurrentRow(0);
}

void MainWidget::resfreshNoteTextField() {
    int index = uiNotes->currentRow();
    Note& note = listNotes.at(index);
    outputField->setText(QString::fromStdString(note.getText()));
}

void MainWidget::saveFile()
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
        file.close();
        addNote(header, text);
    }
}


void MainWidget::addedNote(int id){
   lastAddedNote.setId(lastAddedNote.getId() + 1);
   listNotes.push_back(lastAddedNote);
   uiNotes->addItem(QString::fromStdString(lastAddedNote.getTitle()));
}



MainWidget::~MainWidget()
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
