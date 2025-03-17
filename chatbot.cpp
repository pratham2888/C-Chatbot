#include <iostream>
#include  <fstream>
#include <unordered_map>
#include <string>

using namespace std;

// Load knowledge base from a file
unordered_map<string, string> loadKnowledgeBase(const string& filename) {
    unordered_map<string, string> knowledgeBase;
    ifstream file(filename);
    string question, answer;

    while (getline(file, question) && getline(file, answer)) {
        knowledgeBase[question] = answer;
    }
    
    file.close();
    return knowledgeBase;
}

// Save new question-answer pairs to the file
void saveToKnowledgeBase(const string& filename, const string& question, const string& answer) {
    ofstream file(filename, ios::app); // Append mode
    file << question << endl << answer << endl;
    file.close();
}

// Main chatbot function
void chatbot() {
    string filename = "knowledge_base.txt";
    unordered_map<string, string> knowledgeBase = loadKnowledgeBase(filename);

    cout << "🤖 AI Chatbot is ready! Type 'exit' to quit.\n" << endl;

    while (true) {
        cout << "You: ";
        string userInput;
        getline(cin, userInput);

        if (userInput == "exit") {
            cout << "🤖 Chatbot: Goodbye! Have a great day! 🚀" << endl;
            break;
        }

        if (knowledgeBase.find(userInput) != knowledgeBase.end()) {
            cout << "🤖 Chatbot: " << knowledgeBase[userInput] << endl;
        } else {
            cout << "🤖 Chatbot: I don't know the answer. Teach me! What should I reply?" << endl;
            string newAnswer;
            getline(cin, newAnswer);
            knowledgeBase[userInput] = newAnswer;
            saveToKnowledgeBase(filename, userInput, newAnswer);
            cout << "🤖 Chatbot: Got it! I will remember this. 😊" << endl;
        }
    }
}

// Main function
int main() {
    chatbot();
    return 0;
}
