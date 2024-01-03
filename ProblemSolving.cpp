//*******************************************************************
//*****		STUDENT NAME: FATÝH ALTUNEL							*****
//*****		STUDENT NUMBER: B221202070							*****
//*****		ASSIGMENT #: 2										*****
//*****		I DID BY MYSELF										*****
//*******************************************************************
#include<iostream> // for cout, cin
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <iomanip> // for setw(), left,right etc
#include <string>  // for string class
#include <fstream> // for fstream class
using namespace std;
class Matrixes {
private:
    int InputMatrixSize; 
    int CoreMatrixSize; 
    int OutputMatrixSize;
    int** InputMatrix = nullptr;
    int** CoreMatrix = nullptr;
    int** OutputMatrix = nullptr;  
public:
    //Constructor of the class
    Matrixes() {
        srand(time(nullptr));
        this->InputMatrixSize = rand() % 16 + 5;    
        this->CoreMatrixSize = rand()  %  4 + 2;    
        this->OutputMatrixSize = InputMatrixSize - CoreMatrixSize + 1; //it is a rule for that project
    }
    //Destructor of the class
    ~Matrixes() {
        // deallocate InputMatrix
       for (int i = 0; i < InputMatrixSize; ++i) {
           delete[] InputMatrix[i];
        }
       delete[] InputMatrix;

        // deallocate CoreMatrix
        for (int i = 0; i < CoreMatrixSize; ++i) {
            delete[] CoreMatrix[i];
        }
        delete[] CoreMatrix;

        // deallocate OutputMatrix
        for (int i = 0; i < OutputMatrixSize; ++i) {
           delete[] OutputMatrix[i];
        }
        delete[] OutputMatrix;
    }
    void GenerateMatrix(string MatrixType) {  //Function generates a matrix based on string parametre
        if (MatrixType == "Input") { 
            if (InputMatrix) { //if the matrices have already been allocated memory, we should deallocate the memory before allocating new memory. 
                for (int i = 0; i < InputMatrixSize; ++i) {
                    delete[] InputMatrix[i];
                }
                delete[] InputMatrix;
            }           
            InputMatrix = new int*[InputMatrixSize]; // Allocating memory for InputMatrix

            for (int i = 0; i < InputMatrixSize; i++) { //We create 2. dimension of the matrix by this for loop
                InputMatrix[i] = new int[InputMatrixSize];
            }
            for (int i = 0; i < InputMatrixSize; i++) {  //Standart proccess for adding values to the 2D matrix
                for (int j = 0; j < InputMatrixSize; j++) {
                    int randomValue = rand() % 11 + 10;
                    InputMatrix[i][j] = randomValue; 
                }
            }           
        }
        else if (MatrixType == "Core") {
            if (CoreMatrix) { //if the matrices have already been allocated memory, we should deallocate the memory before allocating new memory. 
                for (int i = 0; i < CoreMatrixSize; ++i) {
                    delete[] CoreMatrix[i];
                }
                delete[] CoreMatrix;
            }      
            CoreMatrix = new int* [CoreMatrixSize]; // Allocating memory for CoreMatrix
            for (int i = 0; i < CoreMatrixSize; i++) {  //We create 2. dimension of the matrix by this for loop
                CoreMatrix[i] = new int[CoreMatrixSize];
            }
            for (int i = 0; i < CoreMatrixSize; i++) { 
                for (int j = 0; j < CoreMatrixSize; j++) { 
                    int randomValue = rand() % 10 + 1;
                    CoreMatrix[i][j] = randomValue;
                } 
            }        
        }
        else if (MatrixType == "Output") {
            // Deallocate existing memory
            if (OutputMatrix) {
                for (int i = 0; i < OutputMatrixSize; ++i) {
                    delete[] OutputMatrix[i];
                }
                delete[] OutputMatrix;
                OutputMatrix = nullptr; // Reset to nullptr after deallocation
            }

            // Allocate new memory
            OutputMatrix = new int* [OutputMatrixSize];     // Allocating memory for OutputMatrix
            for (int i = 0; i < OutputMatrixSize; i++) {    //We create 2. dimension of the matrix by this for loop
                OutputMatrix[i] = new int[OutputMatrixSize];
            }

            for (int a = 0; a < OutputMatrixSize; a++) {
                for (int b = 0; b < OutputMatrixSize; b++) {
                    int value = 0;
                    for (int i = 0; i < CoreMatrixSize; i++) {
                        for (int j = 0; j < CoreMatrixSize; j++) {
                            value += (InputMatrix[a + i][b + j] * CoreMatrix[CoreMatrixSize - 1 - i][CoreMatrixSize - 1 - j]);
                        }
                    }
                    OutputMatrix[a][b] = value / pow(CoreMatrixSize, 2);
                }
            }
        }
    }
    void ReadMatricesFromFile() { //This function reads the values of the Matrices and prints it
        ifstream file("data.txt", ios::in);     //Opens the data.txt file for reading.
        if (file.is_open()) {
            string line;

            // Read and ignore the header lines
            getline(file, line); // "Input Matrix:"

            // Determine the size of InputMatrix
            InputMatrixSize = 0;
            while (getline(file, line) && line != "Core Matrix:") {
                InputMatrixSize++; //it will increase InputMatrixSize till reaaches the Core Matrix: line
            }

            // Allocate memory for InputMatrix
            InputMatrix = new int* [InputMatrixSize];
            for (int i = 0; i < InputMatrixSize; ++i) {
                InputMatrix[i] = new int[InputMatrixSize];
            }

            // Reset the file to the beginning of the matrix
            file.close(); 
            file.open("data.txt", ios::in); //reopens the file

            // Skip the header line
            getline(file, line);

            // Read the Input Matrix
            cout << "Input Matrix:" << endl; 
            for (int i = 0; i < InputMatrixSize; ++i) {
                for (int j = 0; j < InputMatrixSize; ++j) {
                    if (!(file >> InputMatrix[i][j])) {
                        cout << "Error reading Input Matrix at position (" << i << ", " << j << ")." << endl;
                        return;
                    }
                    cout << left<<setw(4)<<InputMatrix[i][j]; 
                }
                cout << endl;
            }
            file.close(); 
            file.open("data.txt", ios::in);  
            while (getline(file, line) && line != "Core Matrix:") {}

            // Determine the size of CoreMatrix
            CoreMatrixSize = 0;
            while (getline(file, line) && line != "") {
                CoreMatrixSize++;
            }

            // Allocate memory for CoreMatrix
            CoreMatrix = new int* [CoreMatrixSize];
            for (int i = 0; i < CoreMatrixSize; ++i) {
                CoreMatrix[i] = new int[CoreMatrixSize];
            }

            // Reset the file to the beginning of the Core Matrix
            file.close();  
            file.open("data.txt", ios::in);  

            // Skip the lines till the header line for Core Matrix
            while (getline(file, line) && line != "Core Matrix:") {}

            // Read the Core Matrix
            cout << "Core Matrix:" << endl;
            for (int i = 0; i < CoreMatrixSize; ++i) {
                for (int j = 0; j < CoreMatrixSize; ++j) {
                    if (!(file >> CoreMatrix[i][j])) {
                        cout << "Error reading Core Matrix at position (" << i << ", " << j << ")." << endl;
                        return;
                    }
                    cout << left<<setw(4)<<CoreMatrix[i][j];  
                } 
                cout << endl; 
            }
            file.close(); 
            OutputMatrixSize = InputMatrixSize - CoreMatrixSize + 1; //It will evaluate the OutputMatrixSize based on read Matrices.
            cout << "Matrices read from data.txt" << endl;  
        }
        else {
            cout << "Error: Unable to open the file for reading." << endl;
        }
    }
    void PrintMatrix(int** matrix, int size) { //The function prints a matrix
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << left << setw(4) << matrix[i][j];
            }
            cout << endl;
        }
    }
    void PrintMatrices(string MatrixType) { //Function that prints matrices by using PrintMatrix function
        if (MatrixType == "Input") {
            cout << "Input Matrix: " << endl;
            PrintMatrix(InputMatrix, InputMatrixSize);
        }
        else if (MatrixType == "Core") {
            cout << "Core Matrix: " << endl;
            PrintMatrix(CoreMatrix, CoreMatrixSize);
        }
        else if (MatrixType == "Output") {
            cout << "Output Matrix: " << endl;  
            PrintMatrix(OutputMatrix, OutputMatrixSize);  
        }
        else if ("All") {
            cout << "Input Matrix: " << endl;
            PrintMatrix(InputMatrix, InputMatrixSize);
            cout << "Core Matrix: " << endl; 
            PrintMatrix(CoreMatrix, CoreMatrixSize); 
            cout << "Output Matrix: " << endl; 
            PrintMatrix(OutputMatrix, OutputMatrixSize); 
        }
    }
    void SaveMatrixToFile(ofstream& file, int** matrix, int size) { //It will save all the data to the file
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file << matrix[i][j] << " "; 
            }  
            file << "\n"; 
        }
    }
    void SaveMatrices() { //It will send the data.txt file and data to the SaveMatrixToFile function
        ofstream file("data.txt", ios::out);    
        if (file.is_open()) { //if there is a file(data.txt)
            file << "Input Matrix:" << endl; 
            SaveMatrixToFile(file, InputMatrix, InputMatrixSize); 
            file << "Core Matrix:" << endl; 
            SaveMatrixToFile(file, CoreMatrix, CoreMatrixSize);
            cout << "Matrices saved to data.txt" << endl;
        }
        else {
            cout << "Error: Unable to open the file for writing." << endl;
        }
    }
};
int main() {
    int choice; 
        do {
            cout << "**********MENU OPTIONS***********\n";
            cout << "**** 1.Generate new matrices ****\n";
            cout << "*******  2.Read matrices  *******\n";
            cout << "****  from an existing file  ****\n"; 
            cout << "*********************************\n";
            cout << "       Enter your choice: ";
            cin >> choice;
            Matrixes matrix;
            switch (choice) {
            case 1: {
                matrix.GenerateMatrix("Input"); 
                matrix.GenerateMatrix("Core"); 
                matrix.GenerateMatrix("Output");  
                matrix.SaveMatrices(); 
                matrix.PrintMatrices("All");
                break;
            }
            case 2: {     
                ifstream file("data.txt");
                if (!file.is_open()) {
                    cout << "File not found " << endl;
                    cout << "New file is creating" << endl;
                    matrix.GenerateMatrix("Input"); 
                    matrix.GenerateMatrix("Core"); 
                    matrix.GenerateMatrix("Output"); 
                    matrix.SaveMatrices(); 
                    matrix.PrintMatrices("All"); 
                    break;
                }
                else {
                    matrix.ReadMatricesFromFile();   
                    cout << endl;   
                    matrix.GenerateMatrix("Output");    
                    matrix.PrintMatrices("Output");   
                    break;
                }
            }
            default:
                cout << "Invalid input.\n";
                break;
            }
        } while (true);
        return 0;
}