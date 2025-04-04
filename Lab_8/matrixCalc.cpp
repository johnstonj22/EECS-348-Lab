#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;

int matrix_num() { // asks user for which matrix to perform operation on
    int matrix_num = 3;
    cout << "Which matrix do you want to calculate the diagonal sum for 1 or 2: ";
    cin >> matrix_num;
    while (matrix_num != 1 &&  matrix_num != 2) {
        cout << "Invalid number" << endl;
        cout << "Which matrix do you want to calculate the diagonal sum for 1 or 2: ";
        cin >> matrix_num;
    }
    return matrix_num;
}

pair<vector<vector<int>>, vector<vector<int>>> create_matrices() { //asks user for input file and creates 2 matrices
    int file_not_opened = 1;
    ifstream file;

    while (file_not_opened) {
        string file_name;
        cout << "Enter Matrix File Name: ";


        getline(cin, file_name);

        cout << "Trying to open: [" << file_name << "]" << endl;

        file.open(file_name);
        if (file.is_open()) {
            file_not_opened = 0;
            cout << "File opened successfully!\n";
        } else {
            cout << "The file couldn't be opened\n";
        }
    }

    int n;
    file >> n;

    vector<vector<int>> matrix_1(n, vector<int>(n));
    vector<vector<int>> matrix_2(n, vector<int>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> matrix_1[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> matrix_2[i][j];

    cout << "matrix 1" << endl;
    print_matrix(matrix_1);
    cout << "matrix 2" << endl;
    print_matrix(matrix_2);

    return {matrix_1, matrix_2};
}



void print_matrix(const vector<vector<int>>& matrix) { // prints a given matrix
    int max_num_width = 0;
    int num_width = 0;
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix.size(); j++) {
            num_width = to_string(matrix[i][j]).length();
            if (max_num_width < num_width) {
                max_num_width = num_width;
            }
        }
    }
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix.size(); j++) {
            cout << setw(max_num_width) << matrix[i][j];
        }
        cout << endl;
    }
}

void add_matrices(const vector<vector<int>>& matrix_1, const vector<vector<int>>& matrix_2) { //adds 2 matrices and prints the result
    vector<vector<int>> matrix_3;
    for (size_t i = 0; i < matrix_1.size(); i++) {
        vector<int> row;
        for (size_t j = 0; j < matrix_2.size(); j++) {
            row.push_back(matrix_1[i][j] + matrix_2[i][j]);
        }
        matrix_3.push_back(row);
    }
    cout << "Result of Matrix Addition:" << endl;
    print_matrix(matrix_3);
}

void multiply_matrices(const vector<vector<int>>& matrix_1, const vector<vector<int>>& matrix_2) { // multiplies 2 matrices and prints the result
    size_t n = matrix_1.size();
    vector<vector<int>> matrix_3(n, vector<int>(n, 0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            for (size_t k = 0; k < n; k++) {
                matrix_3[i][j] += matrix_1[i][k] * matrix_2[k][j];
            }
        }
    }
    cout << "Result of Matrix Multiplication:" << endl;
    print_matrix(matrix_3);
}

void diagonal_sum(const vector<vector<int>>& matrix) { // adds the diagonals of a matrix and prints the result
    size_t n = matrix.size();
    int sum = 0;
    for (size_t i = 0; i < n; i++) {
        sum += matrix[i][i] + matrix[i][n - 1 - i];
    }
    cout << "Results of summing the diagonals is: " << sum << endl; 
}

int swap_rows(vector<vector<int>>& matrix, int row_1, int row_2) { // swaps rows of a matrix and prints the result
    int n = static_cast<int>(matrix.size());
    if (row_1 < n && row_1 >= 0 && row_2 < n && row_2 >= 0) {
        vector<int> temp = matrix[row_1];
        matrix[row_1] = matrix[row_2];
        matrix[row_2] = temp;
        cout << "Result of swapping rows "<< row_1 << " and " << row_2 << ":" << endl;
        print_matrix(matrix);
        return 1;
    } else {
        return 0;
    }
}

int swap_columns(vector<vector<int>>& matrix, int col_1, int col_2) { // swaps columns of a matrix and prints the result
    int n = static_cast<int>(matrix.size());
    if (col_1 < n && col_1 >= 0 && col_2 < n && col_2 >= 0) {
        int temp;
        for (int i = 0; i < n; i++) {
            temp = matrix[i][col_1];
            matrix[i][col_1] = matrix[i][col_2];
            matrix[i][col_2] = temp;
        }
        cout << "Result of swapping columns " << col_1 << " and " << col_2 << ":" << endl;
        print_matrix(matrix);
        return 1;
    } else {
        return 0;
    }
}

int replace_value(vector<vector<int>>& matrix, int row, int col, int val) { // replace a value of a matrix and print the result
    int n = static_cast<int>(matrix.size());
    if (row < n && row >= 0 && col < n && col > 0) {
        matrix[row][col] = val;
        cout << "Result of updating value at row " << row << " and col " << col << ":" << endl;
        print_matrix(matrix);
        return 1;
    }
    else {
        return 0;
    }
}

int main() { // allows for selection of operations
    pair<vector<vector<int>>, vector<vector<int>>> matrices = create_matrices();
    vector<vector<int>> matrix_1 = matrices.first;
    vector<vector<int>> matrix_2 = matrices.second;
    int program_not_done = 1;
    while (program_not_done) {
        int command = 1;
        cout << "Operations\n 1: Add Matrices\n 2: Multiply Matrices\n 3: Calculate Diagonal Sum\n 4: Swap Rows\n 5: Swap Columns\n 6: Replace Value\n 7: End Program\n";
        cout << "Enter a number to perform an operation: ";
        cin >> command;
        switch (command) {
            case 1: {
                add_matrices(matrix_1, matrix_2);
                break;
            }
            case 2: {
                multiply_matrices(matrix_1, matrix_2);
                break;
            }
            case 3: {
                int matrix_number = matrix_num();
                if (matrix_number == 1) {
                    diagonal_sum(matrix_1);
                } else {
                    diagonal_sum(matrix_2);
                }
                break;
            }
            case 4: {
                int matrix_number = matrix_num();
                int row_1, row_2;
                cout << "Enter the number of the first row to swap: ";
                cin >> row_1;
                cout << "Enter the number of the second row to swap: ";
                cin >> row_2;
                if (matrix_number == 1) {
                    if (!swap_rows(matrix_1, row_1, row_2)) {
                        cout << "Given rows were invalid\n";
                    }
                } else {
                    if (!swap_rows(matrix_2, row_1, row_2)) {
                        cout << "Given rows were invalid\n";
                    }
                }
                break;
            }
            case 5: {
                int matrix_number = matrix_num();
                int col_1, col_2;
                cout << "Enter the number of the first column to swap: ";
                cin >> col_1;
                cout << "Enter the number of the second column to swap: ";
                cin >> col_2;
                if (matrix_number == 1) {
                    if (!swap_columns(matrix_1, col_1, col_2)) {
                        cout << "Given columns were invalid\n";
                    }
                } else {
                    if (!swap_columns(matrix_2, col_1, col_2)) {
                        cout << "Given columns were invalid\n";
                    }
                }
                break;
            }
            case 6: {
                int matrix_number = matrix_num();
                int val, row, col;
                cout << "Enter the value to insert into the matrix: ";
                cin >> val;
                cout << "Enter the row number for the value to replace: ";
                cin >> row;
                cout << "Enter the column number for the value to replace: ";
                cin >> col;
                if (matrix_number == 1) {
                    if (!replace_value(matrix_1, row, col, val)) {
                        cout << "Given row or column was invalid\n";
                    }
                } else {
                    if (!replace_value(matrix_2, row, col, val)) {
                        cout << "Given row or column was invalid\n";
                    }
                }
                break;
            }
            case 7: {
                program_not_done = 0;
            }
            default:
                cout << "Invalid option. Try again.\n";
        }
    }
    return 0;
}
