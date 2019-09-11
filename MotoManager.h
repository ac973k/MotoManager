#ifndef MOTOMANAGER_H
#define MOTOMANAGER_H

#include <QWidget>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QMessageBox>

#include <QProcess>

#include <QMediaPlayer>

class QGridLayout;
class QCheckBox;
class QComboBox;
class QPlainTextEdit;
class QPushButton;
class QMessageBox;

class QProcess;

class QMediaPlayer;

class MotoManager : public QWidget
{
	Q_OBJECT
	
	public:
	int count = 0;
	
	MotoManager(QWidget *parent = nullptr);
	~MotoManager();
	
	private:
	QGridLayout *gridBoxLayout; //main Layout
	
	QCheckBox *checkBackup; //checkbox for backup
	QCheckBox *checkRestore; //checkbox for restore
	
	QComboBox *list; //list devices
	
	QPlainTextEdit *log; //logs
	
	QPushButton *btnGotIt; //button backup/restore
	QPushButton *btnAbout; //about button
	
	QMessageBox *boxError; //error messages
	QMessageBox *boxAbout; //about message
    QMessageBox *boxSecret; //secret box menu
	
	QProcess *procBackup; //process backup bin
	QProcess *procRestore; //process restore bin
	
	QMediaPlayer *player;
	
	private slots:
	void switchToBackup(); //switch function to backup
	void switchToRestore(); //switch function to restore
	
	void gotIt(); //functions backup/restore
	void about(); //about
	
	void secret(); //secret music :)
};

#endif // MOTOMANAGER_H
