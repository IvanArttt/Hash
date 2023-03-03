#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;


class HashFunction1
{
private:
	int* _HashTable;
	int _Module;
	int _Size;
	int _UpperBoundOfTheModule;
	bool Prime(int);
public:
	HashFunction1();
	HashFunction1(int*, int, int);
	~HashFunction1();
	bool Insert(int);
	bool Search(int);
	bool Remove(int);
	void ChangeUpperBoundOfTheModule(int);
	void Output(const char*);
	int Size();
};

bool HashFunction1::Prime(int Digit)
{
	for (int i = 2; i <= (int)sqrt(Digit) + 1; i++)
		if (Digit % i == 0) return false;
	return true;
}

void HashFunction1::ChangeUpperBoundOfTheModule(int UpperBoundOfTheModule)
{
	if (_HashTable == nullptr)
	{
		_UpperBoundOfTheModule = UpperBoundOfTheModule;
		_Module = (rand() % _UpperBoundOfTheModule) + 1;
		while (!Prime(_Module) || _Module < 3) _Module = (rand() % _UpperBoundOfTheModule) + 1;
	}
}

HashFunction1::HashFunction1()
{
	_HashTable = nullptr;
	_UpperBoundOfTheModule = rand();
	_Module = (rand() % _UpperBoundOfTheModule) + 1;
	while (!Prime(_Module) || _Module < 3)
		_Module = (rand() % _UpperBoundOfTheModule) + 1;
	_Size = 0;
}

HashFunction1::HashFunction1(int* Array, int ArraySize, int UpperBoundOfTheModule)
{
	if (ArraySize > UpperBoundOfTheModule)throw "Error: The size of the array is larger than the upper limit of the module";
	_UpperBoundOfTheModule = UpperBoundOfTheModule;
	_Module = (rand() % _UpperBoundOfTheModule) + 1;
	double alpha = (double)ArraySize / (double)_Module;
	while (alpha > 1 || !Prime(_Module))
	{
		_Module = (rand() % _UpperBoundOfTheModule) + 1;
		alpha = (double)ArraySize / (double)_Module;
	}

	_HashTable = new int[_Module];
	for (int i = 0; i < _Module; i++)//INT_MAX - служебный Empty
		_HashTable[i] = INT_MAX;     //INT_MIN - служебный Del

	for (int i = 0; i < ArraySize; i++)
		Insert(Array[i]);
}

HashFunction1::~HashFunction1()
{
	delete[] _HashTable;
}

bool HashFunction1::Insert(int Value)
{
	if (_Size == _UpperBoundOfTheModule)throw "Error: The size of the array is larger than the upper limit of the module";
	if (_Size == 0 || _HashTable == nullptr)
	{
		_HashTable = new int[_Module];
		for (int i = 0; i < _Module; i++)
			_HashTable[i] = INT_MAX;

		for (int i = 0; i < _Module; i++)
		{
			if (_HashTable[(Value % _Module + i) % _Module] == INT_MAX || _HashTable[(Value % _Module + i) % _Module] == INT_MIN)
			{
				_HashTable[(Value % _Module + i) % _Module] = Value;
				_Size++;
				return 1;
			}
		}
		return 0;
	}
	else
	{
		if (_Size == _Module)
		{
			int NewModule = (rand() % _UpperBoundOfTheModule) + 1;
			while (NewModule <= _Module || !Prime(_Module))
				NewModule = NewModule = (rand() % _UpperBoundOfTheModule) + 1;

			int* NewHashTable = new int[NewModule];
			for (int i = 0; i < NewModule; i++)
				NewHashTable[i] = INT_MAX;

			for (int j = 0; j < _Size; j++)
			{
				for (int i = 0; i < NewModule; i++)
				{
					if (NewHashTable[(_HashTable[j] % NewModule + i) % NewModule] == INT_MAX)
					{
						NewHashTable[(_HashTable[j] % NewModule + i) % NewModule] = _HashTable[j];
						break;
					}
				}
			}

			_Module = NewModule;
			delete[] _HashTable;
			_HashTable = new int[_Module];

			for (int i = 0; i < _Module; i++)
				_HashTable[i] = NewHashTable[i];
		}

		for (int i = 0; i < _Module; i++)
		{
			if (_HashTable[(Value % _Module + i) % _Module] == INT_MAX || _HashTable[(Value % _Module + i) % _Module] == INT_MIN)
			{
				_HashTable[(Value % _Module + i) % _Module] = Value;
				_Size++;
				return 1;
			}
		}
		return 0;
	}
	return 0;
}

bool HashFunction1::Search(int Value)
{
	if (_Size == 0 || _HashTable == nullptr) return 0;
	for (int i = 0; i < _Module; i++)
	{
		if (_HashTable[(Value % _Module + i) % _Module] == Value) return 1;
		if (_HashTable[(Value % _Module + i) % _Module] == INT_MAX) return 0;
		if (_HashTable[(Value % _Module + i) % _Module] == INT_MIN) continue;
	}
	return 0;
}

bool HashFunction1::Remove(int Value)
{
	if (_Size == 0 || _HashTable == nullptr)return 0;
	for (int i = 0; i < _Module; i++)
	{
		if (_HashTable[(Value % _Module + i) % _Module] == Value)
		{
			_HashTable[(Value % _Module + i) % _Module] = INT_MIN;
			_Size--;
			return 1;
		}
		if (_HashTable[(Value % _Module + i) % _Module] == INT_MAX) return 0;
		if (_HashTable[(Value % _Module + i) % _Module] == INT_MIN) continue;
	}
	return 0;
}

void HashFunction1::Output(const char* option)
{
	if (option == "str")
	{
		if (_Size == 0 || _HashTable == nullptr)
		{
			cout << 0 << ')' << "[" << "EMPTY" << "]" << endl;
			return;
		}
		for (int i = 0; i < _Module; i++)
		{
			if (_HashTable[i] == INT_MAX) cout << i << ')' << "[" << "EMPTY" << "]" << " ";
			else if (_HashTable[i] == INT_MIN) cout << i << ')' << "[" << "DELETE" << "]" << " ";
			else cout << i << ')' << "[" << _HashTable[i] << "]" << " ";
		}cout << endl;
	}
	if (option == "stb")
	{
		if (_Size == 0 || _HashTable == nullptr)
		{
			cout << 0 << ')' << "[" << "EMPTY" << "]" << endl;
			return;
		}
		if (_Size == 0 || _HashTable == nullptr)
		{
			cout << 0 << ')' << "[" << "EMPTY" << "]" << endl;
			return;
		}
		for (int i = 0; i < _Module; i++)
		{
			if (_HashTable[i] == INT_MAX) cout << i << ')' << "[" << "EMPTY" << "]" << endl;
			else if (_HashTable[i] == INT_MIN) cout << i << ')' << "[" << "DELETE" << "]" << endl;
			else cout << i << ')' << "[" << _HashTable[i] << "]" << endl;
		}
	}
}

int HashFunction1::Size()
{
	return _Size;
}

class HashFunction2
{
private:
	HashFunction1* _ArrayOfHashTables;
	int _Module;
	bool Prime(int Digit)
	{
		for (int i = 2; i <= (int)sqrt(Digit) + 1; i++)
			if (Digit % i == 0) return false;
		return true;
	}
public:
	HashFunction2(int*, int, int);
	~HashFunction2();
	bool Insert(int);
	bool Search(int);
	bool Remove(int);
	void Output(const char*);
	int Size();
};

HashFunction2::HashFunction2(int* Array, int ArraySize, int UpperBoundOfTheModule)
{
	if (ArraySize > UpperBoundOfTheModule * UpperBoundOfTheModule) throw "Error: The size of the array is larger than the upper limit of the module";
	_Module = (rand() % UpperBoundOfTheModule) + 1;
	while (!Prime(_Module) || _Module < 3)
		_Module = (rand() % UpperBoundOfTheModule) + 1;

	_ArrayOfHashTables = new HashFunction1[_Module];
	for (int i = 0; i < _Module; i++)
		_ArrayOfHashTables[i].ChangeUpperBoundOfTheModule(UpperBoundOfTheModule);

	for (int i = 0; i < ArraySize; i++)
		_ArrayOfHashTables[Array[i] % _Module].Insert(Array[i]);
}

HashFunction2::~HashFunction2()
{
	delete[] _ArrayOfHashTables;
}

bool HashFunction2::Insert(int Value)
{
	return _ArrayOfHashTables[Value % _Module].Insert(Value);
}

bool HashFunction2::Search(int Value)
{
	return _ArrayOfHashTables[Value % _Module].Search(Value);
}

bool HashFunction2::Remove(int Value)
{
	return _ArrayOfHashTables[Value % _Module].Remove(Value);
}

void HashFunction2::Output(const char* option)
{
	for (int i = 0; i < _Module; i++)
	{
		cout << i << '}';
		_ArrayOfHashTables[i].Output(option);
	}
}

int HashFunction2::Size()
{
	int a = 0;
	for (int i = 0; i < _Module; i++)
		a += _ArrayOfHashTables[i].Size();
	return a;
}

int main()
{

	return 0;
}