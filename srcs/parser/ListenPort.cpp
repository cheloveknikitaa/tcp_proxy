#include "../../include/parser/Parser.hpp"


bool operator==(const pair<int, ListenPort> &f1, const pair<int, ListenPort> &f2) {
    return (f1.second._address == f2.second._address && f1.second._port == f2.second._port);
};
