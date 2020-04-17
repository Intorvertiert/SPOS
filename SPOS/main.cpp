#include <iostream>
#include <fstream>
#include <ostream>

#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_RESET "\x1b[0m"

#define BUFFER 250000 //matrix 8x8
#define FILE_SIZE_ 10000000

// 1 GB = 1073741824 byte, size = 1 073 741 824*8 ~~ 8 000 000 000 byte

int64_t* multMatrix(const int64_t* firstMatrix, const int64_t* secondMatrix, const size_t bufferSize)
{
	size_t sizeMatrix = sqrt(bufferSize);
	int64_t* resultMatrix = new int64_t[bufferSize];
	for (size_t i = 0; i < bufferSize; ++i)
		resultMatrix[i] = 0;

	int64_t sum = 0;

	for (size_t i = 0; i < sizeMatrix; ++i)
	{
		
		for (size_t k = 0; k < sizeMatrix; ++k)
		{
			sum = firstMatrix[i*sizeMatrix+k];
			for (size_t j = 0; j < sizeMatrix; ++j)
			{
			
				resultMatrix[i*sizeMatrix+j] += sum * secondMatrix[k*sizeMatrix+j];
			}
		}
		
	}

	return resultMatrix;
}

void publisher(const char* fileName, int64_t* resultMatrix, size_t matrixBuffer)
{
	std::ofstream fout(fileName, std::ios::app);
	for (size_t i = 0; i < matrixBuffer; ++i)
	{
		fout << resultMatrix[i] << ',';
	}
	delete[] resultMatrix;
	fout.close();
	std::cout << "Endling process\n\n";
	
}


void createFile(const char* fileName, size_t size)
{
	std::ofstream fout(fileName);
	for (size_t i = 0; i < size; ++i)
		fout << -100 + rand()% 200 << ',';
	fout.close();
	std::cout << "stop filling\n";
}


int64_t* getBuffer(const char* fileName, const size_t iBuffer_t)
{
	std::ifstream fin(fileName, std::ios_base::in);
	if (!fin.is_open())
	{
		std::cout << "Open Error" << std::endl;
	}
	else
	{
		int64_t* matrix = new int64_t[iBuffer_t];
		char buffer[10];

		if (fin && !fin.eof())
		{
			for (size_t i = 0; i < iBuffer_t; ++i)
			{
				fin.getline(buffer, 5, ',');
				matrix[i] = atoi(buffer);
			}
		}
		fin.close();
		return matrix;
	}
	
}

void scoped(size_t scops)
{
	size_t counter = 0;
	for (size_t i = 0; i < scops; ++i) {
		int64_t* first = getBuffer("first.txt", BUFFER);
		std::cout << "first buff" << std::endl;
		int64_t* second = getBuffer("second.txt", BUFFER);
		std::cout << "second buff" << std::endl;
		int64_t* result = multMatrix(first, second, BUFFER);
		std::cout << "result buff" << std::endl;
		publisher("result.txt", result, BUFFER);

		delete[]first;
		delete[]second;
		std::cout << "counter = " << ++counter << std::endl;
	}
}



int main(int argc, char** argv)
{

	createFile("first.txt", FILE_SIZE_);
	createFile("second.txt", FILE_SIZE_);
	scoped(FILE_SIZE_/BUFFER);
	system("pause >> NULL");
	return 0;
}