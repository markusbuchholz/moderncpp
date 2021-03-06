#include <iostream>
#include <array>
#include <memory>
#include <chrono>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <numeric>
#include <filesystem>

using namespace std;

int main() {
    vector<int> numbers;
    for (size_t i = 0; i < 15; ++i) {
        numbers.emplace_back(i * 10 + 1);
    }

    // Save numbers in text file
    ofstream fout("numbers.txt");
    for (size_t i = 0; i < numbers.size(); ++i) {
        fout << numbers[i] << " ";
    }
    fout.close();

    // Load numbers from text file
    vector<int> m_numbers;
    ifstream fin("numbers.txt");
    for (size_t i = 0; i < numbers.size(); ++i) {
        int x;
        fin >> x;
        m_numbers.emplace_back(x);
    }
    fin.close();

    // Print numbers
    for_each(numbers.begin(), numbers.end(), [](auto x) { cout << x << " "; });
    cout << endl;
    for_each(m_numbers.begin(), m_numbers.end(), [](auto x) { cout << x << " "; });
    cout << endl;

    // Save numbers in binary file
    fout.open("numbers.bin", ios::binary);
    for (size_t i = 0; i < numbers.size(); ++i) {
        char* pointer_to_number = (char*)&numbers[i];
        size_t bytes_per_number = sizeof(numbers[i]);
        fout.write(pointer_to_number, bytes_per_number);
    }
    fout.close();

    // Load numbers from binary file
    m_numbers.clear();
    fin.open("numbers.bin", ios::binary);
    for (size_t i = 0; i < numbers.size(); ++i) {
        int x;
        char* pointer_to_number = (char*)&x;
        size_t bytes_per_number = sizeof(x);
        fin.read(pointer_to_number, bytes_per_number);
        m_numbers.emplace_back(x);
    }
    fin.close();

    // Print numbers
    for_each(numbers.begin(), numbers.end(), [](auto x) { cout << x << " "; });
    cout << endl;
    for_each(m_numbers.begin(), m_numbers.end(), [](auto x) { cout << x << " "; });
    cout << endl;

    // Compare file sizes
    cout << "File size (text): " << filesystem::file_size("numbers.txt") << " bytes" << endl;
    cout << "File size (binary): " << filesystem::file_size("numbers.bin") << " bytes" << endl;

    return 0;
}