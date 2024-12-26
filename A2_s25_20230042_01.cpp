//ASSIGNMENT NUMBER 2 FOR DOCTOR MOHAMED ELRAMLY
//AUTHOR NAME :ADHAM AYMAN MOHAMED MOHAMED 
//ID : 20230042
// SECTION NUMBER: S25



//   PROBLEM 1 LABEL GENRATOR //

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class LabelGenerator {
protected:
    string prefix;
    int currentIndex;

public:
    LabelGenerator(const string& prefix, int initialIndex = 1): prefix(prefix), currentIndex(initialIndex) {}

    virtual string nextLabel() {
        return prefix + to_string(currentIndex++);
    }
};

class FileLabelGenerator : public LabelGenerator {
private:
    string fileName;
    vector<string> fileLabels;
    int fileLabelIndex;

    void loadFileLabels() {
        ifstream file(fileName);
        if (!file.is_open()) {
            cerr << "Error: Could not open file " << fileName << endl;
            return;
        }

        string line;
        fileLabels.clear();
        while (getline(file, line)) {
            fileLabels.push_back(line);
        }
        file.close();
        fileLabelIndex = 0;
    }

public:
    FileLabelGenerator(const string& prefix, int initialIndex, const string& fileName): LabelGenerator(prefix, initialIndex), fileName(fileName), fileLabelIndex(0) {
        loadFileLabels(); 
    }

    // Override nextLabel to append file captions
    string nextLabel() override {
        string label = LabelGenerator::nextLabel();
        if (fileLabelIndex < fileLabels.size()) {
            label += " " + fileLabels[fileLabelIndex++];
        }
        return label;
    }

    void reset() {
        currentIndex = 1;  // Reset index to 1 (or change to the desired default)
        fileLabelIndex = 0;
    }

   
    size_t getLabelCount() const {
        return fileLabels.size();
    }
};

int main() {
    string userPrefix;
    int initialIndex;
    string fileName;

    //Allow user to enter the label he wants "Table", "Diagram", "Chart", "Figure" or anything he likes
    cout << "Enter the label prefix (e.g., 'Figure', 'Table', 'Chart'): ";
    getline(cin, userPrefix);

    //Allow user to enter a number to start like 4 (default is 1) so u can produce "Figure 4" Figure 5" "Figure 6"
    cout << "Enter the starting number (default is 1): ";
    cin >> initialIndex;
    cin.ignore();  // Ignore the newline character left in the buffer

    //File Label Generator has an extra parameter that is filename that allows user to enter a file to read captions
    cout << "Enter the filename with captions: ";
    getline(cin, fileName);
    FileLabelGenerator labelGen(userPrefix, initialIndex, fileName);
    cout << "Generated labels:\n";
    for (size_t i = 0; i < labelGen.getLabelCount(); i++) {
        cout << labelGen.nextLabel() << endl;
    }

    return 0;
}
