#include "Chat.h"
#include <iostream>
#include <fstream>
#include "json.hpp" 
#include <sstream>
using json = nlohmann::json;
string Chat::callPythonNLPModule(string phrase) {
    stringstream pythonCommand;
    pythonCommand << "python nlp_module.py \"" << phrase << "\"";
    string nlpOutput = "";
    FILE *pipe = popen(pythonCommand.str().c_str(), "r");
    if (!pipe) {
        cerr << "Error executing Python script." << endl;
        return "";
    }
    char buffer[128];
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            nlpOutput += buffer;
    }
    pclose(pipe);
    return nlpOutput;
}

void Chat::respond(string phrase) {

    string nlpOutput = callPythonNLPModule(phrase);

    
    json nlpJson = json::parse(nlpOutput);

    
    string intent = nlpJson["intent"];
    vector<pair<string, string>> entities = nlpJson["entities"];


    string response = "I'm sorry, I didn't understand.";
    if (intent == "greet") {
        response = "Hello! How can I assist you today?";
    } else if (intent == "search") {
        response = "Let me find that information for you.";
    }
    stella.say(response);
}

    
 
    
    
    
        
    
        
    
    


void Chat::say(string phrase) {
    this->stella.say(phrase);
}
