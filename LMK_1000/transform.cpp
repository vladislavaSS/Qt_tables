#include "LMK1000-widget.h"

QString LMK1000Widget::bin2hex(const QString& binaryStr) {

    for (QChar c : binaryStr) if (c != '0' && c != '1') return QString();

    bool ok;
    quint64 decimalValue = binaryStr.toULongLong(&ok, 2);
    if (!ok) return QString();

    QString hexStr = QString::number(decimalValue, 16).toUpper();
    return hexStr;
}

QString LMK1000Widget::hex2Json(QString& Result, QString& text, int bitNumber, int bitCount) {

    int contrl_summ = bitNumber + Result.size();
    if (bitNumber > bitCount - 1) Result = "";
    else if (bitNumber < bitCount - 1) {
        if (Result.isEmpty()) Result += QString(bitCount - 1 - bitNumber, '0') + text;
        else if (!Result.isEmpty() && contrl_summ < bitCount) Result += QString(bitCount - 1 - contrl_summ, '0') + text;
        else Result += text;
    } else Result += text;

    return Result;
}

QString LMK1000Widget::dec2bin(const QString& decimalStr, int bitWidth) {

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

QString LMK1000Widget::hex2bin(QString &hexString) {

    bool ok;
    int bitCount;
    if (ADflag) bitCount = 8;
    else if (LMKflag) bitCount = 32;
    else if (HCMflag) bitCount = 0;

    hexString = hexString.remove("0x").toUpper();
    int value = hexString.toInt(&ok, 16);

    if (!ok) return QString();

    QString binaryString = QString::number(value, 2);

    return binaryString.rightJustified(bitCount, '0');

}

QString LMK1000Widget::bin2dec(const QString& binaryString) {
    bool ok;
    int decimalValue = binaryString.toLongLong(&ok, 2);

    if (!ok) {
        return "";
    }

    return QString::number(decimalValue);
}

bool LMK1000Widget::isBinary(const QString &numericPart) {
    QString filtered = numericPart;
    filtered.remove('0');
    filtered.remove('1');
    return filtered.isEmpty();
}


