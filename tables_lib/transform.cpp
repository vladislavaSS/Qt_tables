#include "functions.h"

QString Tables::bin2hex(const QString& binaryStr) {

  for (QChar c : binaryStr) if (c != '0' && c != '1') return QString();

  bool ok;
  quint64 decimalValue = binaryStr.toULongLong(&ok, 2);
  if (!ok) return QString();

  QString hexStr = QString::number(decimalValue, 16).toUpper();
  return hexStr;
}

QString Tables::hex2Json(QString& Result, QString& text, int bitNumber, int bitCount) {

  if (text.isEmpty()) return "N/A";

  int contrl_summ = bitNumber + Result.size();
  if (bitNumber > bitCount - 1) Result = "";
  else if (bitNumber < bitCount - 1) {
    if (Result.isEmpty()) Result += QString(bitCount - 1 - bitNumber, '0') + text;
    else if (!Result.isEmpty() && contrl_summ < bitCount) Result += QString(bitCount - 1 - contrl_summ, '0') + text;
    else Result += text;
  } else Result += text;

  return Result;

}

QString Tables::dec2bin(const QString& decimalStr, int bitWidth) {

  bool ok;
  int decimalValue = decimalStr.toInt(&ok);

  if (!ok) return QString();

  QString binaryStr;
  if (decimalValue == 0) binaryStr = "0";
  else {
    while (decimalValue > 0) {
      binaryStr.prepend(QString::number(decimalValue % 2));
      decimalValue /= 2;
    }
  }

  if (binaryStr.size() < bitWidth) binaryStr = QString(bitWidth - binaryStr.size(), '0') + binaryStr;
  return binaryStr;
}

QString Tables::hex2bin(QString &hexString) {

  bool ok;

  if (hexString == "N/A") return hexString;

  hexString = hexString.remove("0x").toUpper();
  int value = hexString.toLongLong(&ok, 16);

  if (!ok) return QString();

  QString binaryString = QString::number(value, 2);

  return binaryString.rightJustified(bitCount, '0');

}

QString Tables::bin2dec(const QString& binaryString) {
  bool ok;
  long long decimalValue = binaryString.toLongLong(&ok, 2);

  if (!ok) {
    return "";
  }

  return QString::number(decimalValue);
}

bool Tables::isBinary(const QString &numericPart) {
  QString filtered = numericPart;
  filtered.remove('0');
  filtered.remove('1');
  return filtered.isEmpty();
}

QString Tables::line2hex(QLineEdit *lineEdit, QString value, QString text){

    if (lineEdit->property("bitName") == "CLKout0_DIV [7:0]"){
    if (lineEdit->text() == "")
      value = lineEdit->property("default").toString();
    else value = lineEdit->text();
    int intValue = value.toInt()/2;
    value = QString::number(intValue);
  } else if (lineEdit->property("bitName") == "CLKout0_DLY [3:0]") {
    if (lineEdit->text() == "")
      value = lineEdit->property("default").toString();
    else value = lineEdit->text();
    int intValue = value.toInt()/150;
    value = QString::number(intValue);
  } else {
    if (lineEdit->text() == "")
      value = lineEdit->property("default").toString();
    else value = lineEdit->text();
  }

  if (value == lineEdit->property("default").toString() && !LMKflag)
    text = value;
  else text = dec2bin(value, lineEdit->property("bitWidth").toInt());

  return text;

}

QString Tables::combo2hex(QComboBox *comboBox){

    QString comboBoxText = comboBox->currentText();
    QStringList parts = comboBoxText.split(" ");
    QString numericPart = parts.isEmpty() ? QString() : parts[0];

    if (comboBox->property("bitName") == "Part ID (read only)" || comboBox->property("bitName") == "HB3[5:0]"
            || comboBox->property("bitName") == "HB2[5:0]")
        numericPart = dec2bin(numericPart, comboBox->property("bitWidth").toInt());

    return numericPart;
}

QString Tables::check2hex(QCheckBox *checkBox, QString checkBoxValue){

    if (checkBox->checkState() == Qt::PartiallyChecked)
      checkBoxValue = "?";
    else if (checkBox->isChecked())
      checkBoxValue = "1";
    else checkBoxValue = "0";

    return checkBoxValue;

}

void Tables::setTextLine(QLineEdit *lineEdit, QString data) {

    if (lineEdit->property("bitName") == "CLKout0_DIV [7:0]"){
      int intdata = data.toInt()*2;
      lineEdit->setText(QString::number(intdata));
    } else if (lineEdit->property("bitName") == "CLKout0_DLY [3:0]") {
      int intdata = data.toInt()*150;
      lineEdit->setText(QString::number(intdata));
    } else if (lineEdit->property("bitName") == "chip_ID") {;
        data = lineEdit->property("default").toString();
        lineEdit->setText(bin2dec(data));
      } else lineEdit->setText(data);
}

void Tables::setTextCombo(QComboBox *comboBox, QString value) {

    bool valueFound = false;
    for (int i = 0; i < comboBox->count(); ++i) {
      QString existingText = comboBox->itemText(i);
      QString textBeforeSpace = existingText.split(" ").first();
      if (textBeforeSpace == value) {
        valueFound = true;
        comboBox->setCurrentText(existingText);
        break;
      }
    }
    if (!valueFound) {
      comboBox->addItem(value);
      comboBox->setCurrentText(value);
    }

}

void Tables::fileForm(rapidjson::Value& resultValue, QString child, const QString& Result, rapidjson::Document::AllocatorType& allocator, bool read) {

    resultValue.AddMember(
    rapidjson::Value("Addr", allocator),
    rapidjson::Value(child.toStdString().c_str(), allocator),
    allocator
  );

  if (!read && Result != "N/A") {
    resultValue.AddMember(
      rapidjson::Value("Data", allocator),
      rapidjson::Value(Result.toStdString().c_str(), allocator),
      allocator
    );
  }

}







