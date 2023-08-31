#ifndef _Chat_H
#define _Chat_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Stella.h"

using namespace std;

class Chat {
public:
    void respond(string phrase);
    void say(string phrase);

    Stella stella;

private:
    string callPythonNLPModule(string phrase);
};

#endif
