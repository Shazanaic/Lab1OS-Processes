#pragma once
#include <iostream>
#include <string>

using namespace std;

class Employee {
public:
    int num{};
    string name;
    double hours{};

    Employee() = default;
    Employee(int n, const string& nm, double h) : num(n), name(nm), hours(h) {}

    friend istream& operator>>(istream& in, Employee& e) {
        return in >> e.num >> e.name >> e.hours;
    }

    friend ostream& operator<<(ostream& out, const Employee& e) {
        return out << e.num << " " << e.name << " " << e.hours;
    }

    void writeBinary(ostream& out) const {
        char marker = 1;
        out.write(&marker, sizeof(marker));

        out.write(reinterpret_cast<const char*>(&num), sizeof(num));

        size_t len = name.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        if (len > 0) {
            out.write(name.data(), len);
        }

        out.write(reinterpret_cast<const char*>(&hours), sizeof(hours));
    }

    bool readBinary(istream& in) {
        char marker{};
        if (!in.read(&marker, sizeof(marker)))
            return false;

        if (marker != 1) {
            return false;
        }

        if (!in.read(reinterpret_cast<char*>(&num), sizeof(num)))
            return false;

        size_t len{};
        if (!in.read(reinterpret_cast<char*>(&len), sizeof(len)))
            return false;

        if (len > 1000) {
            return false;
        }

        name.clear();
        if (len > 0) {
            name.resize(len);
            if (!in.read(&name[0], static_cast<std::streamsize>(len)))
                return false;
        }

        if (!in.read(reinterpret_cast<char*>(&hours), sizeof(hours)))
            return false;

        return true;
    }
};
