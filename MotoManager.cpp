#include "MotoManager.h"

MotoManager::MotoManager(QWidget *parent) : QWidget(parent)
{
    Q_INIT_RESOURCE(MotoManager);

	gridBoxLayout = new QGridLayout;
	
	checkBackup = new QCheckBox("Backup");
	checkRestore = new QCheckBox("Restore");
	
	list = new QComboBox;
	list->insertItem(0, "config");
	list->insertItem(1, "boot");
	list->insertItem(2, "efuse");
	list->insertItem(3, "expdb");
	list->insertItem(4, "flashinfo");
	list->insertItem(5, "frp");
	list->insertItem(6, "keystore");
	list->insertItem(7, "lk");
	list->insertItem(8, "loader");
	list->insertItem(9, "logo");
	list->insertItem(10, "metadata");
	list->insertItem(11, "nvdata");
	list->insertItem(12, "nvram");
	list->insertItem(13, "oemkeystore");
	list->insertItem(14, "para");
	list->insertItem(15, "proinfo");
	list->insertItem(16, "protect1");
	list->insertItem(17, "protect2");
	list->insertItem(18, "recovery");
	list->insertItem(19, "seccfg");
	list->insertItem(20, "secro");
	list->insertItem(21, "tee1");
	list->insertItem(22, "tee2");
	
	log = new QPlainTextEdit;
	log->setReadOnly(true);
	
	btnGotIt = new QPushButton("Сделай Это!");
	btnAbout = new QPushButton("О Программе");
	
	gridBoxLayout->addWidget(checkBackup, 0, 0);
	gridBoxLayout->addWidget(checkRestore, 0, 1);
	gridBoxLayout->addWidget(list, 1, 0, 1, 2);
	gridBoxLayout->addWidget(log, 2, 0, 2, 2);
	gridBoxLayout->addWidget(btnGotIt, 3, 0);
	gridBoxLayout->addWidget(btnAbout, 3, 1);
	
	setLayout(gridBoxLayout);
	
	QObject::connect(checkBackup, SIGNAL(clicked()), this, SLOT(switchToBackup()));
	QObject::connect(checkRestore, SIGNAL(clicked()), this, SLOT(switchToRestore()));
	
	QObject::connect(btnGotIt, SIGNAL(clicked()), this, SLOT(gotIt()));
	QObject::connect(btnAbout, SIGNAL(clicked()), this, SLOT(about()));
	
    QObject::connect(btnAbout, SIGNAL(clicked()), this, SLOT(secret()));
}

MotoManager::~MotoManager()
{
    Q_CLEANUP_RESOURCE(MotoManager);

    delete checkBackup;
    delete checkRestore;

    delete btnAbout;
    delete btnGotIt;

    delete gridBoxLayout;

    delete player;

    delete procBackup;
    delete procRestore;

    delete boxAbout;
    delete boxError;
    delete boxSecret;
}

void MotoManager::switchToBackup()
{
	if(checkBackup->isChecked())
	{
		checkRestore->setChecked(false);
	}
}

void MotoManager::switchToRestore()
{
	if(checkRestore->isChecked())
	{
		checkBackup->setChecked(false);
	}
}

void MotoManager::gotIt()
{
	if(checkBackup->isChecked())
	{
		QString device = list->currentText();
		
		procBackup = new QProcess;
		procBackup->setProcessChannelMode(QProcess::SeparateChannels);
		procBackup->start("su", QStringList() << "-c" << "backup" << device);
		
		if(!procBackup->waitForFinished())
		{
			log->setPlainText(procBackup->errorString());
		}
		else
		{
			log->setPlainText(procBackup->readAll());
		}
	}
	
	else if(checkRestore->isChecked())
	{
		QString device = list->currentText();
		
		procRestore = new QProcess;
		procRestore->setProcessChannelMode(QProcess::SeparateChannels);
		procRestore->start("su", QStringList() << "-c" << "restore" << device);
		
		if(!procRestore->waitForFinished())
		{
			log->setPlainText(procRestore->errorString());
		}
		else
		{
			log->setPlainText(procRestore->readAll());
		}
	}
	
	else if(!checkBackup->isChecked() and !checkRestore->isChecked())
	{
		boxError = new QMessageBox();
		boxError->setText("Либо ты инвалид, либо автор программы! Проверь галочки, особенный ты наш!");
		boxError->exec();
	}
	else
	{
		boxError = new QMessageBox();
		boxError->setText("Что-то пошло не так!");
		boxError->exec();
	}
}

void MotoManager::about()
{
	boxAbout = new QMessageBox();
	boxAbout->setTextFormat(Qt::RichText);
	boxAbout->setText("GUI приложение для консольных утилит backup и restore."
	
	"\n Разработано с помощью QT Framework."
	""
	"\n Links:"
	"\n https://qt.io"
	"\nРазраб: Danilka Terentyev(4pda: AC97; GitHub: ac973k; vk: id498051587)"
	""
	"\n Специально для Moto C 4G(Namath)");
	boxAbout->exec();
}

void MotoManager::secret()
{
    if(count == 5)
    {
		player = new QMediaPlayer;
        player->setMedia(QUrl("qrc:/audio/jazi.mp3"));
		player->setVolume(100);
		player->play();
		
		boxSecret = new QMessageBox();
		boxSecret->setText("Бранимир — Жази"
"\n Музыка, слова принадлежат Александру Паршикову(Бранимир), кто начнет доебываться, идите нахуй. Саня норм мужик, грех не добавить его песню.\n P.S. Привет из Волгограда!");
        boxSecret->exec();
        
        count = 0;
    }
    else if(count > 5)
    {
        boxError = new QMessageBox();
        boxError->setText("Как, мать твою, ты это сделал?!");
        boxError->exec();
    }
    else if(count == 3)
    {
        boxSecret = new QMessageBox();
        boxSecret->setText("Давай, ещё пару нажатий :=)");
        boxSecret->exec();

        ++count;
    }
    else
    {
        ++count;
    }
}
