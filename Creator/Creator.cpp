#include <fstream>
#include <iostream>
#include <vector>
#include "Employee.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: Creator <output_file> <number_of_records>" << endl;
        return 1;
    }

    ofstream binfile(argv[1], ios::binary | ios::out);
    if (!binfile) {
        cerr << "Error: cannot open/create file " << argv[1] << endl;
        return 1;
    }

    int records = atoi(argv[2]);
    if (records <= 0) {
        cerr << "Error: number of records must be positive" << endl;
        return 1;
    }

    vector<Employee> empl_list;
    empl_list.reserve(records);

    cout << "Fill out the list of employees (number, name, hours): " << endl;
    for (int i = 0; i < records; i++) {
        cout << i + 1 << ". ";
        Employee e;
        cin >> e;
        empl_list.push_back(e);
    }

    for (const auto& e : empl_list) {
        e.writeBinary(binfile);
    }

    binfile.close();
    return 0;
}
