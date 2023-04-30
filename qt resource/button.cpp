#include <qapplication.h>
#include <qslider.h>
#include <qpushbutton.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <QPaintEvent>
#include <qresource.h>

class ImgButton : public QPushButton {
public:
	ImgButton() = default;
	ImgButton(QWidget* parent);
	void paintEvent(QPaintEvent* e) override;
	QSize sizeHint() const override;
	QSize minimumSizeHint() const override;
public slots:
	void setGreen();
	void setYellow();
	void setRed();
private:
	QPixmap mCurrentButtonPixmap;
	QPixmap mButtonGreenPixmap;
	QPixmap mButtonYellowPixmap;
	QPixmap mButtonRedPixmap;
	bool isDown = false;
};

ImgButton::ImgButton(QWidget* parent) {
	setParent(parent);
	setToolTip("Стоп");
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	mButtonGreenPixmap = QPixmap(":/green.png");
	mButtonYellowPixmap = QPixmap(":/yellow.png");
	mButtonRedPixmap = QPixmap(":/red.png");
	mCurrentButtonPixmap = mButtonGreenPixmap;
	setGeometry(mCurrentButtonPixmap.rect());
}

void ImgButton::paintEvent(QPaintEvent* e) {
	QPainter p(this);
	p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImgButton::sizeHint() const {
	return QSize(100, 100);
}

QSize ImgButton::minimumSizeHint() const {
	return sizeHint();
}

void ImgButton::setGreen() {
	mCurrentButtonPixmap = mButtonGreenPixmap;
	update();
}
void ImgButton::setYellow() {
	mCurrentButtonPixmap = mButtonYellowPixmap;
	update();
}
void ImgButton::setRed() {
	mCurrentButtonPixmap = mButtonRedPixmap;
	update();
}


int main(int argc, char** argv) {
	QResource::registerResource("/img.qrc");
	QApplication app(argc, argv);
	QWidget* window = new QWidget;
	window->setFixedSize(200, 200);
	ImgButton* button = new ImgButton(window);
	QSlider* slider = new QSlider(Qt::Horizontal, window);
	slider->setMinimum(0);
	slider->setMaximum(66);
	QObject::connect(slider, &QSlider::valueChanged, [&slider, &button](int newValue) {
		if (slider->value() == 0) {
			button->setGreen();
		}
		else if (slider->value() == 33) {
			button->setYellow();
		}
		else if (slider->value() == 66) {
			button->setRed();
		}
		});
	button->setFixedSize(100, 100);
	slider->resize(100, 20);
	button->move(50, 50);
	slider->move(50, 150);
	window->show();
	button->show();
	slider->show();
	return app.exec();
}
