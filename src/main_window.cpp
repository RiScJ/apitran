#include "main_window.hpp"

#include <QFileDialog>


Canvas* MainWindow::_view = nullptr;

QDockWidget* MainWindow::_dock = nullptr;
QListWidget* MainWindow::_list = nullptr;
QMenuBar* MainWindow::_menu = nullptr;
QToolBar* MainWindow::_bar = nullptr;
QStatusBar* MainWindow::_status = nullptr;
QAction* MainWindow::_decode_WAV = nullptr;
QAction* MainWindow::_decode_IQ = nullptr;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	_view = new Canvas();

	MainWindow::create_menubar();
	MainWindow::create_statusbar();
	MainWindow::create_actions();
	MainWindow::create_toolbar();
//	MainWindow::create_dockwidget();

	setCentralWidget(_view);

	connect(this, &MainWindow::load_WAV, _view, &Canvas::load_WAV);
};


void MainWindow::create_statusbar(void) {
	_status = new QStatusBar(this);
	_status->addWidget(new QLabel(tr("File: ")));
	setStatusBar(_status);
};


void MainWindow::create_dockwidget(void) {
	QDockWidget* dock = new QDockWidget(tr("Entities"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea);

	QListWidget* list = new QListWidget(dock);
	dock->setWidget(list);
	addDockWidget(Qt::LeftDockWidgetArea, dock);

	_list = list;
	_dock = dock;
};


void MainWindow::create_menubar(void) {
	_menu = menuBar();

	QMenu *file = _menu->addMenu("&File");
	file->addAction("Open");
	file->addAction("New");
};


void MainWindow::create_actions(void) {
	_decode_WAV = new QAction(QIcon(":/icons/audio.svg"), "Decode WAV", this);
	connect(_decode_WAV, &QAction::triggered, this, &MainWindow::open_WAV);
	_decode_IQ = new QAction(QIcon(":/icons/audio-spectrum.svg"), "Decode IQ", this);
};


void MainWindow::create_toolbar(void) {
	_bar = addToolBar("");
	_bar->setIconSize(QSize(40, 40));
	_bar->addAction(_decode_WAV);
	_bar->addAction(_decode_IQ);
};


void MainWindow::open_WAV(void) {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open WAV"), "/home/zarya", tr("WAV Files (*.wav)"));
	if (!fileName.isEmpty()) {
		emit load_WAV(fileName);
	}
};

