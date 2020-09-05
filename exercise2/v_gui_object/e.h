#ifndef E_H
#define E_H

#include <QDialog>
#include <QString>
namespace Ui {
class e;
}

class e : public QDialog
{
    Q_OBJECT

public:
    explicit e(QWidget *parent = nullptr);
    ~e();



private slots:
    void on_buttonBox_accepted();

private:
    Ui::e *ui;
};

#endif // E_H
