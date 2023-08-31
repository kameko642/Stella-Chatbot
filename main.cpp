#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

int main() {
    for (;;) {
        cout << "\nYOU: ";
        string phrase;
        getline(cin, phrase);

        stringstream pythonCommand;
        pythonCommand << "python nlp_module.py \"" << phrase << "\"";
        string nlpOutput = "";
        FILE *pipe = popen(pythonCommand.str().c_str(), "r");
        if (!pipe) {
            cerr << "Error executing Python script." << endl;
            return 1;
        }
        char buffer[128];
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                nlpOutput += buffer;
        }
        pclose(pipe);

      json nlpData = json::parse(nlpOutput);
        
        string intent = nlpData["intent"];
        vector<pair<string, string>> entities;
        for (const auto &entity : nlpData["entities"]) {
            entities.emplace_back(entity["type"], entity["text"]);
        }

       
        string response = "I'm sorry, I didn't understand.";
        if (intent == "greet") {
            response = "Hello! How can I assist you today?";
        } else if (intent == "search") {
            response = "Let me find that information for you.";
        } 

        cout << "Stella: " << response << endl;
    }

    return 0;
}
