#include "pch.h"
#include "Employee.h"
#include <gtest/gtest.h>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

TEST(CreatorTests, CreatesFileWithOneEmployee) {
    ofstream input("creator_input.txt");
    input << "1 Roflik 15";
    input.close();
    remove("empl.bin");

    string cmd = "Creator.exe empl.bin 1 < creator_input.txt";
    int ret = system(cmd.c_str());

    ASSERT_EQ(ret, 0);
    ifstream f("empl.bin", ios::binary);
    ASSERT_TRUE(f.good());

    Employee e;
    ASSERT_TRUE(e.readBinary(f));
    EXPECT_EQ(1, e.num);
    EXPECT_EQ("Roflik", e.name);
    EXPECT_DOUBLE_EQ(15.0, e.hours);
}

TEST(ReporterTests, GeneratesReport) {
    Employee e{ 1, "Roflik", 15.0 };
    ofstream bin("empl.bin", ios::binary);
    e.writeBinary(bin);
    bin.close();

    remove("report.txt");

    string cmd = "Reporter.exe empl.bin report.txt 15";
    int ret = system(cmd.c_str());

    ASSERT_EQ(ret, 0);
    ifstream rep("report.txt");
    ASSERT_TRUE(rep.good());

    string line, all;
    while (getline(rep, line)) {
        all += line + "\n";
    }
    EXPECT_NE(all.find("Roflik"), string::npos);
    EXPECT_NE(all.find("225"), string::npos);
}

TEST(MainTests, RunsWholePipeline) {
    ofstream creatorIn("creator_input.txt");
    creatorIn << "1 Roflik 15";
    creatorIn.close();

    remove("empl.bin");
    remove("report.txt");

    string creatorCmd = "Creator.exe empl.bin 1 < creator_input.txt";
    int ret1 = system(creatorCmd.c_str());

    ASSERT_EQ(ret1, 0);
    ifstream bin("empl.bin", ios::binary);
    ASSERT_TRUE(bin.good());

    Employee e;
    ASSERT_TRUE(e.readBinary(bin));
    EXPECT_EQ(1, e.num);
    EXPECT_EQ("Roflik", e.name);
    EXPECT_DOUBLE_EQ(15.0, e.hours);

    string reporterCmd = "Reporter.exe empl.bin report.txt 15";
    int ret2 = system(reporterCmd.c_str());

    ASSERT_EQ(ret2, 0);
    ifstream rep("report.txt");
    ASSERT_TRUE(rep.good());

    string line, all;
    while (getline(rep, line)) {
        all += line + "\n";
    }
    EXPECT_NE(all.find("Roflik"), string::npos);
    EXPECT_NE(all.find("225"), string::npos);
}
