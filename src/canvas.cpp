#include "canvas.hpp"

#include <QAudioDecoder>

#define N 20800

QByteArray* Canvas::_byteArray = new QByteArray;
QBuffer* Canvas::_device = nullptr;
QAudioInput* Canvas::_audio = nullptr;

QPixmap* Canvas::_line = nullptr;
QByteArray* Canvas::_header = new QByteArray;
QByteArray* Canvas::_data = new QByteArray;
int Canvas::datac = 0;
int Canvas::linec = 0;

Canvas::Canvas(QWidget *parent) : QOpenGLWidget(parent) {
	background = QBrush(QColor(80, 90, 90));
	circleBrush = QBrush(QColor(22, 11, 33));
	circlePen = QPen(Qt::black);
	circlePen.setWidth(1);
	textPen = QPen(Qt::white);
	textFont.setPixelSize(50);
	_line = new QPixmap;
	_header->append('P');
	_header->append('5');
	_header->append('\n');
	_header->append('2');
	_header->append('0');
	_header->append('8');
	_header->append('0');
	_header->append(' ');
	_header->append('1');
	_header->append('\n');
	_header->append('2');
	_header->append('5');
	_header->append('5');
	_header->append('\n');
};


void Canvas::paintEvent(QPaintEvent *event) {
	QPainter painter;
	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing);
	paint(&painter, event);
	painter.end();
};


void Canvas::paint(QPainter *painter, QPaintEvent *event) {
	painter->fillRect(QRect(QPoint(0,linec+1), QPoint(1920,event->rect().bottom())), background);
	painter->drawPixmap(QRect(QPoint(0,linec), QPoint(1040,linec)), *_line);
	linec++;
	qDebug() << linec;
};


void Canvas::test(void) {

};


void Canvas::load_WAV(QString file) {
	_decoder = new QAudioDecoder;
	QAudioFormat* format = new QAudioFormat;
	format->setSampleSize(8);
	format->setSampleRate(N);
	format->setChannelCount(1);
	_decoder->setAudioFormat(*format);
	qDebug() << _decoder->error();
	_decoder->setSourceFilename(file);
	connect(_decoder, &QAudioDecoder::bufferReady, this, &Canvas::print);
	connect(_decoder, QOverload<QAudioDecoder::Error>::of(&QAudioDecoder::error),
			[=](QAudioDecoder::Error error){print_error(error);});
	_decoder->start();
	qDebug() << "Started decoder...";
};


void Canvas::print_error(QAudioDecoder::Error error) {
	qDebug() << error;
};


void Canvas::print(void) {
	QAudioBuffer buf = _decoder->read();
	const quint8* data = buf.constData<quint8>();
	int samples = buf.sampleCount();
	for (int i = 0; i < samples; i++) {
		_data->append(data[i]);
		datac++;
		if (datac == N) {
			datac = 0;

			quint8* _hilb = hilbert(data);

			QByteArray bruh;
			bruh.append(*_header);
			for (int i = 0; i < N; i += 1) {
				bruh.append(_hilb[i]);
			}
			_line->loadFromData(bruh);
			update();
			_data->clear();
		}
	}
};


quint8* Canvas::hilbert(const quint8* in) {
	fftw_complex temp[N];

	for (int i = 0; i < N; ++i) {
		temp[i][0] = in[i];
		temp[i][1] = 0;
	}
	fftw_plan plan = fftw_plan_dft_1d(N, temp, temp, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	int hN = N >> 1;
	int numRem = hN;

	for (int i = 0; i < hN; ++i) {
		temp[i][0] *= 2;
		temp[i][1] *= 2;
	}

	if (N % 2 == 0) numRem--;
	else if (N > 1) {
		temp[hN][0] *= 2;
		temp[hN][1] *= 2;
	}

	memset(&temp[hN+1][0], 0, numRem * sizeof(fftw_complex));

	plan = fftw_plan_dft_1d(N, temp, temp, FFTW_BACKWARD, FFTW_ESTIMATE);
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	fftw_cleanup();

	for (int i = 0; i < N; ++i) {
		temp[i][0] /= N;
		temp[i][1] /= N;
	}

	quint8* out = new quint8[N];
	for (int i = 0; i < N; ++i) {
		out[i] = temp[i][0];
	}

	return out;
};

















