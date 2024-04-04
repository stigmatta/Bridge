#include <iostream>
using namespace std;

/*
 ������� Bridge ��������� �������� ���������� �� �� ���������� ���,
 ����� �� � ������ ����� ���� �������� ����������.

������ ������� ������������ �����:
- ����� �������� ���������� �������� ���������� � ����������.
���, ��������, ������, ����� ���������� ���������� �������� �� ����� ���������� ���������.
- � ����������, � ���������� ������ ����������� ������ �����������.
� ����� ������ ������� ���� ��������� ������������� ������ ���������� � ���������� � �������� �� ����������;
- ��������� � ���������� ���������� �� ������ ����������� �� ��������, �� ���� ���������� ��� �� ������ �������������������;

����������:
- ��������� ���������� �� ����������;
- ��������� ������� �������������;
- �������� ������� ���������� �� ��������.
*/

/*
Implementor(ILanguage) - ���������� ���������� ��������� ��� ������� ����������.
*/
class IParticle abstract
{
private:

public:
	virtual void GetInfo() abstract;
	void SaveToFile()const
	{
		cout << "Data was saved to the file\n";
	}
	void PrintToConsole()const
	{
		cout << "Data was printed in the console\n";
	}

	void PrintInTheWindow()const
	{
		cout << "Data was printed in the message box\n";
	}
};

class VideoCard : public IParticle {
private:
	string model;
	int memorySize;
	int cudaCores;

public:
	// �����������
	VideoCard(string model, int memorySizeGB,int cudaCores)
		: model(model), memorySize(memorySize),cudaCores(cudaCores) {}


	void GetInfo()override {
		cout << "Model: " << model << endl;
		cout << "Memory Size: " << memorySize << "GB" << endl;
		cout << "CUDA Cores: " << cudaCores << endl;
	}
};

class Processor : public IParticle {
private:
	string model;
	int numberOfCores;
	int numberOfThreads;
public:
	Processor(string model, int numberOfCores, int numberOfThreads)
		: model(model), numberOfCores(numberOfCores), numberOfThreads(numberOfThreads) {}

	void GetInfo() override {
		cout << "Model: " << model << endl;
		cout << "Number of Cores: " << numberOfCores << endl;
		cout << "Number of Threads: " << numberOfThreads << endl;
	}
};

class HardDrive : public IParticle {
private:
	string model;
	int capacityGB;
public:
	HardDrive(string model, int capacityGB)
		: model(model), capacityGB(capacityGB) {}

	void GetInfo() override {
		cout << "Model: " << model << endl;
		cout << "Capacity: " << capacityGB << "GB" << endl;
	}
};



// Abstraction (Programmer) - ���������� ��������� ���������� � ������ ������ �� ������ ���������� ���� Implementor
class IReport abstract
{
protected:
	IParticle* particle;
public:
	IParticle* GetParticle()
	{
		return particle;
	}
	void SetParticle(IParticle* particle)
	{
		this->particle = particle;
	}
	virtual void PrintParticle() abstract;
};

// RefinedAbstraction (FreelanceProgrammer)  - ���������� ���������� ��������� ���������, ������������ ����������� Abstraction
class ConsoleReport: public IReport
{
public:
	void PrintParticle() override
	{
		particle->GetInfo();
		particle->PrintToConsole();
	}
};

// RefinedAbstraction (CorporateProgrammer)  - ���������� ���������� ��������� ���������, ������������ ����������� Abstraction
class WindowReport: public IReport
{
public:
	void PrintParticle()override
	{
		particle->GetInfo();
		particle->PrintInTheWindow();
	}
};

class FileReport :public IReport
{
public:
	void PrintParticle()override
	{
		particle->GetInfo();
		particle->SaveToFile();
	}
};

void client(IParticle* particle, IReport* report)
{
	report->SetParticle(particle);
	report->PrintParticle();
}

int main()
{
	IReport* report = new FileReport();
	IParticle* particle = new VideoCard("NVIDIA GeForce RTX 2070 Super",8, 2560);
	client(particle, report);
	cout << "\n\n";
	delete report;	
	delete particle;

	report = new ConsoleReport();
	particle = new HardDrive("Seagate Barracuda", 2000);
	client(particle, report);
	delete report;
	delete particle;

	system("pause");
	return 0;
}