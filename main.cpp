#include"parser.h"


int main()
{
	const int size = 8;
	string FileArray[size] = { "Test_files\\Test-1.txt" ,"Test_files\\Test-2.txt" ,"Test_files\\Test-3.txt" ,"Test_files\\Test-4.txt" ,"Test_files\\Test-5.txt" ,"Test_files\\Test-6.txt" ,"Test_files\\Test-7.txt","Test_files\\Test-8.txt" };
	fstream outputFile;
	outputFile.open("Output_files\\Result-1.txt", ios::out);
	int label = 0;
	int h = 0, m = 0;
	queues<int> q;
	for (int i = 0; i < size; i++)
	{
		outputFile << ReadFile(FileArray[i], to_string(label++), h, m, q);
		outputFile << "\n                               ------------         end            -----------------\n";
	}
	outputFile << "LRU:    hits = " << h << "     miss = " << m << endl;
	outputFile.close();
}
