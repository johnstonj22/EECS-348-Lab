#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <stdexcept>
#include <variant>
//import these librarires

using namespace std;

template<typename T>
class Matrix { //defines the matrix class using a template to allow for handling of ints and doubles
private:
    int size;
    vector<vector<T>> data;

public:
    Matrix(int n) : size(n), data(n, vector<T>(n)) {}

    void set(int row, int col, T value) {
        data[row][col] = value;
    }

    T get(int row, int col) const {
        return data[row][col];
    }

    int getSize() const {
        return size;
    }

    void printAsDouble() const { //prints the values in the matrix as doubles
        cout << fixed << setprecision(2);
        for (const auto& row : data) {
            for (const auto& val : row)
                cout << setw(8) << static_cast<double>(val);
            cout << endl;
        }
    }

    void printDiagonalSums() const {  //calculates and prints the sums of the diagonals
        T mainSum = 0;
        T secondarySum = 0;
        for (int i = 0; i < size; ++i) {
            mainSum += data[i][i];
            secondarySum += data[i][size - 1 - i];
        }
        cout << "\nSum of main diagonal: " << static_cast<double>(mainSum) << endl;
        cout << "Sum of secondary diagonal: " << static_cast<double>(secondarySum) << endl;
    }

    Matrix<T> operator+(const Matrix<T>& other) const { //operator overloading for addition
        if (size != other.size) {
            throw runtime_error("Matrix sizes do not match for addition.");
        }
        Matrix<T> result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.set(i, j, this->get(i, j) + other.get(i, j));
            }
        }
        cout << "\nResult of matrix addition:\n";
        result.printAsDouble();
        return result;
    }

    Matrix<T> operator*(const Matrix<T>& other) const { //operator overloading for multiplication
        if (size != other.size) {
            throw runtime_error("Matrix sizes do not match for multiplication.");
        }
        Matrix<T> result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                T sum = 0;
                for (int k = 0; k < size; ++k) {
                    sum += this->get(i, k) * other.get(k, j);
                }
                result.set(i, j, sum);
            }
        }
        cout << "\nResult of matrix multiplication:\n";
        result.printAsDouble();
        return result;
    }

    friend istream& operator>>(istream& in, Matrix<T>& matrix) { //allows acces to the member variables of matrix
        for (int i = 0; i < matrix.size; ++i) {
            for (int j = 0; j < matrix.size; ++j) {
                T val;
                in >> val;
                matrix.set(i, j, val);
            }
        }
        return in;
    }
};

template<typename T>
void swapMatrixRows(vector<vector<T>>& matrix, int r1, int r2) { // swaps given rows in a matrix
    if (matrix.empty() || r1 < 0 || r2 < 0 || r1 >= static_cast<int>(matrix.size()) || r2 >= static_cast<int>(matrix.size())) {
        cerr << "Invalid row indices for matrix row swap." << endl;
        return;
    }
    swap(matrix[r1], matrix[r2]);
    cout << "Swapped matrix rows:\n";
    for (const auto& row : matrix) {
        for (const auto& val : row)
            cout << static_cast<double>(val) << " ";
        cout << endl;
    }
}

template<typename T>
void swapMatrixColumns(vector<vector<T>>& matrix, int c1, int c2) { // swaps given columns in a matrix
    if (matrix.empty() || c1 < 0 || c2 < 0 || c1 >= static_cast<int>(matrix[0].size()) || c2 >= static_cast<int>(matrix[0].size())) {
        cerr << "Invalid column indices for matrix column swap." << endl;
        return;
    }
    for (auto& row : matrix) {
        swap(row[c1], row[c2]);
    }
    cout << "Swapped matrix columns:\n";
    for (const auto& row : matrix) {
        for (const auto& val : row)
            cout << static_cast<double>(val) << " ";
        cout << endl;
    }
}

template<typename T>
void updateMatrixValue(vector<vector<T>>& matrix, int row, int col, T newValue) { // updates a value in a matrix
    if (row < 0 || row >= static_cast<int>(matrix.size()) || col < 0 || col >= static_cast<int>(matrix[0].size())) {
        cerr << "Invalid matrix indices for update." << endl;
        return;
    }
    matrix[row][col] = newValue;
    cout << "Updated matrix after setting element at (" << row << ", " << col << ") to " << newValue << ":\n";
    for (const auto& r : matrix) {
        for (const auto& val : r)
            cout << static_cast<double>(val) << " ";
        cout << endl;
    }
}

template<typename T>
vector<vector<T>> matrix1ToVector(const Matrix<T>& matrix) { // converts a matrix to a plain 2d vector
    int size = matrix.getSize();
    vector<vector<T>> vec(size, vector<T>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            vec[i][j] = matrix.get(i, j);
        }
    }
    return vec;
}

template<typename T>
pair<Matrix<T>, Matrix<T>> fileToMatrix(const string& inputFile) { //reads in a file and converts contents to matrices
    ifstream file(inputFile);
    if (!file) {
        throw runtime_error("File couldn't be opened: " + inputFile);
    }
    int N, typeFlag;
    file >> N >> typeFlag;
    if (file.fail() || N <= 0 || (typeFlag != 0 && typeFlag != 1)) {
        throw runtime_error("Invalid matrix size or type flag.");
    }
    Matrix<T> matrix1(N);
    Matrix<T> matrix2(N);

    file >> matrix1 >> matrix2;

    cout << "\nMatrix 1:\n";
    matrix1.printAsDouble();

    cout << "\nMatrix 2:\n";
    matrix2.printAsDouble();

    return {matrix1, matrix2};
}

int main() { //demos the matrix functions
    string inputFile;
    cout << "Enter filename: ";
    getline(cin, inputFile);
    try {
        ifstream check(inputFile);
        int N, typeFlag;
        check >> N >> typeFlag;
        check.close();

        if (typeFlag == 0) {
            auto matrices = fileToMatrix<int>(inputFile);
            auto matrix1 = matrices.first;
            auto matrix2 = matrices.second;

            Matrix<int> sum = matrix1 + matrix2;
            Matrix<int> product = matrix1 * matrix2;

            cout << "\nDiagonal sums of Matrix 1:\n";
            matrix1.printDiagonalSums();

            vector<vector<int>> demoMatrix = matrix1ToVector(matrix1);
            cout << "\nDemo row swap (0 and 1):\n";
            swapMatrixRows(demoMatrix, 0, 1);

            cout << "\nDemo column swap (0 and 1):\n";
            swapMatrixColumns(demoMatrix, 0, 1);

            cout << "\nDemo value update at (0, 0) to 999:\n";
            updateMatrixValue(demoMatrix, 0, 0, 999);

        } else if (typeFlag == 1) {
            auto matrices = fileToMatrix<double>(inputFile);
            auto matrix1 = matrices.first;
            auto matrix2 = matrices.second;

            Matrix<double> sum = matrix1 + matrix2;
            Matrix<double> product = matrix1 * matrix2;

            cout << "\nDiagonal sums of Matrix 1:\n";
            matrix1.printDiagonalSums();

            vector<vector<double>> demoMatrix = matrix1ToVector(matrix1);
            cout << "\nDemo row swap (0 and 1):\n";
            swapMatrixRows(demoMatrix, 0, 1);

            cout << "\nDemo column swap (0 and 1):\n";
            swapMatrixColumns(demoMatrix, 0, 1);

            cout << "\nDemo value update at (0, 0) to 999.0:\n";
            updateMatrixValue(demoMatrix, 0, 0, 999.0);

        } else {
            throw runtime_error("Unknown type flag in file.");
        }
    } catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }

    return 0;
}
