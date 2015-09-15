#ifndef CHATLINE_H
#define CHATLINE_H

#include <QWidget>

class QLineEdit;
class QPushButton;

class ChatLine : public QWidget
{
	Q_OBJECT

private:
	QLineEdit *textEd_;
	QPushButton *sendBtn_;

	Q_SLOT void doSend();

public:
	explicit ChatLine(QWidget *parent = 0);
	virtual ~ChatLine();

	Q_SLOT void setEnabled(bool yesno);

	Q_SIGNAL void send(const QString &text);
};

#endif // CHATLINE_H
