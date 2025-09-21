#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Employee.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: Reporter <input_file> <report_file> <pay_per_hour>" << endl;
        return 1;
    }

    ifstream binfile(argv[1], ios::binary);
    if (!binfile) {
        cerr << "Error: cannot open input file " << argv[1] << endl;
        return 1;
    }

    ofstream report(argv[2]);
    if (!report) {
        cerr << "Error: cannot open report file " << argv[2] << endl;
        return 1;
    }

    double pph = atof(argv[3]);
    if (pph <= 0) {
        cerr << "Error: invalid pay per hour" << endl;
        return 1;
    }

    vector<Employee> empl;
    Employee temp;
    while (temp.readBinary(binfile)) {
        empl.push_back(temp);
    }

    report << "Report on file " << argv[1] << ":\n";
    report << "Number of employee, name, hours of work, salary\n";

    for (const auto& e : empl) {
        double salary = e.hours * pph;
        report << e.num << " " << e.name << " " << e.hours << " " << salary << endl;
    }
    return 0;
}
