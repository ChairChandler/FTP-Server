#include "cdupparser.h"

bool CdupParser::parse(const QString &input) {
    return input == "CDUP" ? true : false;
}
