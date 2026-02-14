//Including header files
#include <iostream>
#include <vector>
#include <queue>
#include <conio.h>

using namespace std;

// --- Function Declaration ---

// Function for taking inputs in two arrays with indefinite size
void addArrayItems(vector<int> &arrA, vector<int> &arrB);


// Function for Loading items to the Fifos
void loadToFifos(const vector<int> &arrA, const vector<int> &arrB, 
                 queue<int> &qA, queue<int> &qB, int &index);

// Function for Adding items popped from Fifos
void adder(queue<int> &qA, queue<int> &qB, 
                     vector<int> &results);

// Function to display output Array
void displayResults(const vector<int> &results);

// --- Main Logic Loop ---
int main() {
    vector<int> arrayA;
    vector<int> arrayB;
    vector<int> resultArray;

    queue<int> fifoA, fifoB;
    int currentIndex = 0;
    addArrayItems(arrayA,arrayB);
    cout << "\n____________________________________\n"
            "1. To Load Press \"ENTER\" \n"<<
            "2. To Add Press \"+\" \n"<<
            "3. To Exit Press \"ESC\" \n" << 
            "------------------------------------" << endl;

    while (true) {
        //Checking for the key press
        if (_kbhit()) {
            char key = _getch();
            // Enter key ACSII-13 and ESC key ACSII-27
            if (key == 13) { 
                loadToFifos(arrayA, arrayB, fifoA, fifoB, currentIndex);
            } 
            else if (key == '+') {
                adder(fifoA, fifoB, resultArray);
            } 
            else if (key == 27) { 
                break;
            }
        }
    }

    // Displaying the result array
    displayResults(resultArray);
    _getch();
    return 0;
}

// --- Function Definitions Section---

// Adding items to both the array one by one
void addArrayItems(vector<int> &arrA, vector<int> &arrB){
    cout<<"\nEnter the items of arrays(Items will be stored in alternate arrays).To stop entering array items press \"s\": \n";
    string item1,item2;
    while(true){
        cin>>item1;
        if(item1=="s"){
            cout<<"Arrays are created...";
            break;   
        }
        cin>>item2;
        if(item2=="s"){
            cout<<"Arrays are created...";
            break;
        }
        arrA.push_back(stoi(item1));
        arrB.push_back(stoi(item2));
    }
}


// Pushes the next pair of elements from the source arrays into the FIFOs.
void loadToFifos(const vector<int> &arrA, const vector<int> &arrB, 
                 queue<int> &qA, queue<int> &qB, int &index) {
    if (index < arrA.size()) {
        qA.push(arrA[index]);
        qB.push(arrB[index]);
        cout << "[ENTER Pressed] Items Loaded : " <<"("<< arrA[index] << ", " << arrB[index] << ")" << endl;
        index++;
    } else {
        cout << "[ENTER Pressed] No Elements in Array to Load !!!" << endl;
    }
}


//Pops the front elements from both FIFOs, sums them, and stores in the result array.
void adder(queue<int> &qA, queue<int> &qB, vector<int> &results) {
    if (!qA.empty() && !qB.empty()) {
        int valA = qA.front(); qA.pop();
        int valB = qB.front(); qB.pop();
        
        int sum = valA + valB;
        results.push_back(sum);
        
        cout << "[+ Pressed] Adder Result :  " << valA << " + " << valB << " = " << sum << endl;
    } else {
        cout << "[+ Pressed] FIFOs are empty !!!" << endl;
    }
}

// Displaying the final output array.
void displayResults(const vector<int> &results) {
    cout << "\n----------------------Result------------------------" << endl;
    cout << "Output Array is : [ ";
    for (const int& val : results) {
        cout << val << " ";
    }
    cout << "]" << endl;
}