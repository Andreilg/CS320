#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "caches.h"

#define String std::string

using namespace std;

void runCacheSimulator(Caches aoCaches, String asOutputFileName);

int main(int argc, char *argv[])
{
	vector< pair<char, int> > cooInputVector;

    if (argc != 3)
    {
        cerr << "Usage: ./cache-sim <input_file.txt> <output_file.txt>\n";
        exit(1);
    }

    ifstream coInputFile(argv[1]);
	String lsLine;

	if (coInputFile.is_open())
	{
		while (getline(coInputFile, lsLine))
		{
			char lsAction = lsLine.at(0); // "S"tore or "L"oad
			String lsAddress = lsLine.substr(2); // 0x00000000 - 0xFFFFFFFF
			unsigned int llHexAddress = stoul(lsAddress, nullptr, 16);

			cooInputVector.push_back(pair<char, int>(lsAction, llHexAddress));
		}

		coInputFile.close();
	}
	else
	{
		cerr << "Error opening file " << argv[1] << "\n";
        exit(3);
	}
	
    Caches loCaches(cooInputVector);
    runCacheSimulator(loCaches, argv[2]);

    return 0;
}

void runCacheSimulator(Caches aoCaches, String asOutputFileName)
{
    vector<int> lanTableRows = {32, 128, 512, 1024};
    int loRetVal;

    ofstream loOutputFile(asOutputFileName);
    if (! loOutputFile.is_open())
    {
        cerr << "Unable to open file " << asOutputFileName << "\n";
        exit(2);
    }

    // Q1: Direct Mapped Cache of size 1KB, 4KB, 16KB, 32KB
    for (int i = 0; i < lanTableRows.size(); i++)
    {
        loRetVal = aoCaches.directMapped(lanTableRows.at(i));
        loOutputFile << loRetVal << "," << aoCaches.getCountEntries();

        loOutputFile << ((i == lanTableRows.size() - 1) ? ";" : "; ");
    }
    loOutputFile << "\n";

    loOutputFile.close();
}