#include"BitArray.h"
BitArray::BitArray(int n)
{
	if (n <= 0)
	{
		n = 8;
	}
	capacity = n;
	int s = (int)ceil((float)capacity / 8);
	data = new unsigned char[s];
	for (int i = 0; i < s; i = i + 1)
	{
		data[i] = data[i] & 0;
	}
}

void BitArray::on(int bitNo)
{

	if (!isValidBit(bitNo))
	{
		return;
	}
	int exactBit = bitNo % 8;
	int exactByte = (int)ceil((float)bitNo / 8);
	exactByte -= 1;
	unsigned char ch = 1<<exactBit;
	data[exactByte] = data[exactByte] | ch;

}

void BitArray::off(int bitNo)
{

	if (!isValidBit(bitNo))
	{
		return;
	}
	int exactBit = bitNo % 8;
	int exactByte = (int)ceil((float)bitNo / 8);
	exactByte -= 1;
	unsigned char mask = 0;

	unsigned char ch = 1 << exactBit;
	mask = mask | ch;
	mask = ~mask;
	data[exactByte] = data[exactByte] & mask;
}


void BitArray::invert(int bitNo)
{
	if (checkBitStatus(bitNo))
	{
		off(bitNo);
	}
	else
	{
		on(bitNo);
	}
}


bool BitArray::checkBitStatus(int bitNo)const
{

	if (!isValidBit(bitNo))
	{
		exit(0);
	}
	int exactBit = bitNo % 8;
	int exactByte = (int)ceil((float)bitNo / 8);
	exactByte -= 1;
	
	unsigned char check = data[exactByte];

	unsigned char check2 = check;


	unsigned char ch = 1 << exactBit;
	check = check | ch;

	if (check == check2)
	{
		return true;
	}
	else
	{
		return false;
	}


}


void BitArray::dump()const
{
	int counter = 0;
	int j = capacity - 1;
	for (int i = 0; i < capacity; i = i + 1)
	{
		
		if (checkBitStatus(j))
		{
			cout << "1";
		}
		else
		{
			cout << "0";
		}
		j -= 1;

		

	}
	cout << "\n";
}

BitArray::~BitArray()
{
	delete[] data;
	data = nullptr;
	capacity = 0;
}

BitArray::BitArray(const BitArray & ref)
{

	if (ref.data)
	{
		capacity = ref.capacity;
		data = new unsigned char[capacity];
		for (int i = 0; i < capacity; i = i + 1)
		{
			data[i] = ref.data[i];
		}

	}
	else
	{
		data = nullptr;
		capacity = 0;
	}
}


BitArray BitArray::AND(BitArray a) const
{
	BitArray c{this->capacity};
	int i = 0;
	while (i < a.capacity && i < this->capacity)
	{
		bool check = a.checkBitStatus(i);
		bool check2 = this->checkBitStatus(i);
		if (check == check2)
		{
			if (check)
			{
				c.on(i);
			}
			else
			{
				c.off(i);
			}
		}
	}

	return c;
}







BitArray BitArray::OR(BitArray a) const
{
	BitArray c{ this->capacity };
	int i = 0;
	while (i < a.capacity && i < this->capacity)
	{
		bool check = a.checkBitStatus(i);
		bool check2 = this->checkBitStatus(i);
		if (check || check2)
		{
				c.on(i);
			
		}
	}
	return c;
}


unsigned long long BitArray::getUnsignedIntegralValue() const
{

	unsigned long long num = 0;
	for (int i = 0; i < capacity; i = i + 1)
	{
		bool check = checkBitStatus(i);
		
		if (check)
		{
			
			unsigned long long num2= (unsigned long long )pow(2.0,i);
			num += num2;
		}
	}

	return num;
}



void BitArray::shiftLeft(int shift)
{


	int loopCounter = capacity - shift;
	int index = capacity - shift;
	for (int i = 0; i < loopCounter; i = i + 1)
	{
		
		if (checkBitStatus(i + shift))
		{
			on(i);
		}
		else
		{
			off(i);
		}


	}

	for (int i = loopCounter; i < capacity; i = i + 1)
	{
		off(i);
	}

}



void BitArray::shiftRight(int shift)
{



	int loopCounter = capacity - shift;
	int index = capacity - shift;
	for (int i = 0; i < loopCounter; i = i + 1)
	{

		if (checkBitStatus(i))
		{
			on(i+shift);
		}
		else
		{
			off(i+shift);
		}


	}

	for (int i = loopCounter; i < capacity; i = i + 1)
	{
		off(i-loopCounter);
	}



}


void BitArray::setIntegralValue(unsigned long long val)
{

	unsigned long long max = 0;

	for(int i = 0; i < capacity; i = i + 1)
	{
		max = max + (int)pow(2.0, i);
	}


	if (val > max)
	{
		exit(0);
	}

	int i = 0;

	while (val > 0)
	{
		on(i);
		i = i + 1;
		val = val - (unsigned long long)pow(2.0, i);
	}
}