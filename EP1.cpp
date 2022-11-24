#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;

class State{
public:
    string name;
    State *transictions[2];
    bool finalState;
};

class Automaton{
public:
    State automaton[11];
    int validityStates;

    void buildAutomaton(string word){
        int i;
        this->validityStates = word.size() + 1;
        
        for(i = 0; i < validityStates; i++){
            automaton[i].name = i == 0 ? "eps" : word.substr(0,i);
            automaton[i].transictions[0] = i < word.size() ? (word[i] == 'a' ? &automaton[i+1] : &automaton[returnStatesNumber(this->automaton[i].name, word.substr(0,i).append(1, 'a'))]) : &automaton[i];
            automaton[i].transictions[1] = i < word.size() ? (word[i] == 'b' ? &automaton[i+1] : &automaton[returnStatesNumber(this->automaton[i].name, word.substr(0,i).append(1, 'b'))]) : &automaton[i];
            automaton[i].finalState = i == word.size();
        }
    }
    
    void printAutomatonStates(){
        for (int i = 0; i < validityStates; i++){
            cout << automaton[i].name << " " << automaton[i].transictions[0]->name << " " << automaton[i].transictions[1]->name << std::endl;
        }
    }
    
    int testWord(string word){
        State *state = &automaton[0];

        for (int i = 0; i < word.size(); ++i) {
            state = word[i] == 'a' ? state->transictions[0] : state->transictions[1];
        }

        return state->finalState;
    }

private:
    int returnStatesNumber(string stateName, string alternativeWord){
        int numberStates = 0;
        
        for (int i = 0; i < (stateName == "eps" ? 1 : stateName.size()); ++i) {
            if (stateName.substr(0, (i+1)) == alternativeWord.substr((alternativeWord.size() - (i+1)), (i+1))){
                numberStates = stateName.substr(0,(i+1)).size();
            }
        }
        
        return numberStates;
    }
};

int main() {
    Automaton *automaton = new Automaton();
    string word;
    int quantityTests;

    cin >> word;
    cin >> quantityTests;

    automaton->buildAutomaton(word);
    string testWords[quantityTests];

    for (int i = 0; i < quantityTests; ++i) {
        cin >> testWords[i];
    }

    automaton->printAutomatonStates();

    for (int i = 0; i < quantityTests; ++i) {
        cout << automaton->testWord(testWords[i]) << std::endl;
    }

    return 0;
}