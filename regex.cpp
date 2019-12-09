#include "regex.h"
#include "ui_regex.h"
#include "boost/regex.hpp"
#include <QString>
#include <QMessageBox>
#include <QTextCursor>
#include <QTextCharFormat>

RegEx::RegEx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegEx)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
}

RegEx::~RegEx()
{
    delete ui;
}

void RegEx::setMatchHighlighting(std::map<size_t, size_t> match_pos) {
  QTextCursor cursor = ui->textEdit_Text->textCursor();
  std::map<size_t, size_t>::const_iterator itr;
  for (itr = match_pos.begin(); itr != match_pos.end(); ++itr) {
    QTextCharFormat fmt;
    fmt.setBackground(QBrush(Qt::cyan));
    QTextCursor helper = cursor;
    helper.setPosition(itr->first, QTextCursor::MoveAnchor);
    helper.setPosition(itr->second, QTextCursor::KeepAnchor);
    helper.setCharFormat(fmt);
  }
}

void RegEx::on_pushButton_Match_clicked() {
  ui->textEdit_Text->setPlainText(ui->textEdit_Text->toPlainText());
  QString text, sReg;
  text = ui->textEdit_Text->toPlainText();
  if (text.isEmpty()) {
    ui->textEdit_Text->setFocus();
    return;
  }
  sReg = ui->lineEdit_RegEx->text();
  if (sReg.isEmpty()) {
    ui->lineEdit_RegEx->setFocus();
    return;
  }

  boost::regex::flag_type flag = boost::regex_constants::normal;
  if (ui->checkBox_ICase->isChecked()) flag |= boost::regex::icase;

  try {
    boost::wregex reg(sReg.toStdWString(), flag);

    QString result;
    std::wstring ws_text(text.toStdWString());
    boost::wsmatch match;

    std::map<size_t, size_t> match_pos;
    size_t n = 1;
    size_t pos_base = 0;
    while (boost::regex_search(ws_text, match, reg)) {
      size_t real_pos = match.position() + pos_base;
      match_pos.insert(
          std::pair<size_t, size_t>(real_pos, real_pos + match.length()));

      result += "match(" + QString::number(n++) + "): pos=";
      result += QString::number(real_pos) + LINE_BREAK;

      for (size_t i = 0; i < match.size(); ++i) {
        result += "    sub(" + QString::number(i) +
                  "):" + QString::fromStdWString(match[i].str());
        result += LINE_BREAK;
      }
      pos_base += ws_text.size() - match.suffix().str().size();
      ws_text = match.suffix().str();

      result += LINE_BREAK;
    }
    result = "total(" + QString::number(--n) + ") match:\n" + result;
    ui->textEdit_Match_Result->setPlainText(result);
    setMatchHighlighting(match_pos);
  } catch (boost::regex_error& e) {
    QMessageBox::warning(NULL, "error", e.what());
  }
}

void RegEx::on_pushButton_Replace_clicked() {
  QString text, sReg, sReplace;
  text = ui->textEdit_Text->toPlainText();
  if (text.isEmpty()) {
    ui->textEdit_Text->setFocus();
    return;
  }
  sReg = ui->lineEdit_RegEx->text();
  if (sReg.isEmpty()) {
    ui->lineEdit_RegEx->setFocus();
    return;
  }

  sReplace = ui->lineEdit_Replace->text();
  if (sReplace.isEmpty()) {
    ui->lineEdit_Replace->setFocus();
    return;
  }

  boost::regex::flag_type flag = boost::regex_constants::normal;
  if (ui->checkBox_ICase->isChecked()) flag |= boost::regex::icase;

  try {
    boost::wregex reg(sReg.toStdWString(), flag);

    std::wstring ws_text(text.toStdWString());
    std::wstring replace_result =
        boost::regex_replace(ws_text, reg, sReplace.toStdWString());

    ui->textEdit_Replace_Result->setPlainText(
        QString::fromStdWString(replace_result));
  } catch (boost::regex_error& e) {
    QMessageBox::warning(NULL, "error", e.what());
  }
}
