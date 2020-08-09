#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "canvas.hpp"

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenuBar>
#include <QToolBar>
#include <QDockWidget>
#include <QLayout>
#include <QStatusBar>
#include <QLabel>

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);
signals:
	void load_WAV(QString file);
private:
	static Canvas* _view;
	static QDockWidget* _dock;
	static QListWidget* _list;
	static QToolBar* _bar;
	static QMenuBar* _menu;
	static QStatusBar* _status;
	static QAction* _decode_WAV;
	static QAction* _decode_IQ;

	void create_menubar(void);
	void create_statusbar(void);
	void create_toolbar(void);
	void create_actions(void);
	void populate_central(void);
	void create_dockwidget(void);
	void open_WAV(void);
};

#endif // MAIN_WINDOW_HPP
