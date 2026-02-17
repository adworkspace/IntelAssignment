//Including header files
#include <iostream>
#include <vector>
#include <queue>
#include <string>


using namespace std;

// All Control Signals.
enum Command {
    LOAD = 13,   // Enter key
    LOAD_LINUX=10,
    ADD = 43,    // + key
    SHOW = 61,   // = key
    EXIT_LQ = 'q',
    EXIT_UQ = 'Q'
};

// Platform-specific headers for raw input
#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

// Function to get a single character 
char getKey() {
    char ch = 0;

    // For Windows Compiler
    #ifdef _WIN32
        DWORD mode, read;
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(hInput, &mode);
        SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));
        ReadConsoleA(hInput, &ch, 1, &read, NULL);
        SetConsoleMode(hInput, mode);

    //For Linux Compiler
    #else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    #endif
    return ch;
}


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
            "3. To Show Results Press \"=\"\n"<<
            "4. To Exit Press \"Q/q\" \n" << 
            "------------------------------------\n" << endl;

    while (true) {
        //Checking for the key press
        char key=getKey();

            //Checking entered key for corresponding operations.
            
            if (key==LOAD||key==LOAD_LINUX) { 
                loadToFifos(arrayA, arrayB, fifoA, fifoB, currentIndex);
            } 
            else if (key==ADD) {
                adder(fifoA, fifoB, resultArray);
            } 
            else if(key==SHOW){
                displayResults(resultArray);
            }
            else if (key==EXIT_UQ||key==EXIT_LQ) { 
                cout<<"Terminating Program...\n";
                break;
            }   
            else{
                cout<<"Please Press a Valid Key...\n";
            } 
    }

    // Displaying the result array
    displayResults(resultArray);
    cout<<"End Of Program\n";
    return 0;
}

// --- Function Definitions Section---

// Adding items to both the array one by one
void addArrayItems(vector<int> &arrA, vector<int> &arrB){
    cout<<"\nEnter the items of arrays(Items will be stored in alternate arrays).To stop entering array items press \"S/s\": \n";
    string item1,item2;
    while(true){
        cin>>item1;
        if(item1=="s"||item1=="S"){
            cout<<"Arrays are created...";
            cin.ignore(1000, '\n');
            break;   
        }
        cin>>item2;
        if(item2=="s"|| item2=="S"){
            cout<<"Arrays are created...";
            cin.ignore(1000, '\n');
            break;
        }

        try {
            arrA.push_back(stoi(item1));
            arrB.push_back(stoi(item2));
        }
        catch (...) {
            cout << "Invalid number ignored!\n";
        }
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
        int valA = qA.front(); 
        qA.pop();
        int valB = qB.front(); 
        qB.pop();
        int sum = valA + valB;
        results.push_back(sum);
        
        cout << "[+ Pressed] Adder Result :  " << valA << " + " << valB << " = " << sum << endl;
    } else {
        cout << "[+ Pressed] FIFOs are empty !!!" << endl;
    }
}

// Displaying the final output array.
void displayResults(const vector<int> &results) {
    cout<< "\n----------------------Result------------------------" << endl;
    cout<< "Output Array is : [ ";
    for (const int& val : results) {
        cout << val << " ";
    }
    cout<< "]" << endl;
    cout<< "----------------------------------------------------\n";
}