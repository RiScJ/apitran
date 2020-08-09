#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QWidget>
#include <QBuffer>
#include <QAudioInput>
#include <QAudioDecoder>

#include <fftw3.h>
#include <QDebug>

class Canvas : public QOpenGLWidget
{	Q_OBJECT
public:
	explicit Canvas(QWidget *parent = nullptr);
	void paint(QPainter *painter, QPaintEvent *event);
	void test(void);
	void print(void);
	void load_WAV(QString file);
	void print_error(QAudioDecoder::Error error);
	quint8* hilbert(const quint8* in);
protected:
	void paintEvent(QPaintEvent *event) override;
private:
	QAudioDecoder* _decoder;

	QBrush background;
	QBrush circleBrush;
	QFont textFont;
	QPen circlePen;
	QPen textPen;
	static QBuffer* _device;
	static QAudioInput* _audio;
	static QByteArray* _byteArray;
	static QPixmap* _line;
	static QByteArray* _header;
	static QByteArray* _data;
	static int datac;
	static int linec;
};

#endif // CANVAS_HPP
