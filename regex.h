#ifndef REGEX_H
#define REGEX_H

#include <QDialog>
#include <map>

#define LINE_BREAK      "\n"

namespace Ui {
class RegEx;
}

class RegEx : public QDialog
{
    Q_OBJECT

public:
    explicit RegEx(QWidget *parent = 0);
    ~RegEx();

private:
    void setMatchHighlighting(std::map<size_t, size_t> match_pos);

private slots:
    void on_pushButton_Match_clicked();

    void on_pushButton_Replace_clicked();

private:
    Ui::RegEx *ui;
};

#endif // REGEX_H
