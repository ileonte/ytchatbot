#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

#include "chatline.h"

ChatLine::ChatLine(QWidget *parent) : QWidget(parent)
{
	auto hl = new QHBoxLayout(this);
	hl->setContentsMargins(0, 0, 0, 0);

	textEd_ = new QLineEdit;
	sendBtn_ = new QPushButton(tr("Send"));

	connect(textEd_, &QLineEdit::returnPressed, this, &ChatLine::doSend);
	connect(textEd_, &QLineEdit::textChanged, [this]() {
		sendBtn_->setEnabled(!textEd_->text().isEmpty());
	});

	connect(sendBtn_, &QPushButton::pressed, this, &ChatLine::doSend);

	hl->addWidget(textEd_);
	hl->addWidget(sendBtn_);
}

ChatLine::~ChatLine()
{
}

void ChatLine::doSend()
{
	if (!textEd_->text().isEmpty()) {
		emit send(textEd_->text());
		textEd_->setText("");
		sendBtn_->setEnabled(false);
	}
}

void ChatLine::setEnabled(bool yesno)
{
	if (!yesno) {
		QWidget::setEnabled(false);
	} else {
		QWidget::setEnabled(true);
		sendBtn_->setEnabled(!textEd_->text().isEmpty());
	}
}
