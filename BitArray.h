#include<iostream>
#include<cmath>
using namespace std;
class BitArray
{
private:
	int capacity;
	unsigned char * data;
	bool isValidBit(int i)const
	{
		return i >= 0 && i < capacity;
	}
public:
	BitArray(int n = 8);
	BitArray(const BitArray & ref);
	void on(int bitNo);
	void off(int bitNo);
	bool checkBitStatus(int bitNo)const;
	void invert(int bitNo);
	void dump() const;
	BitArray AND(BitArray) const;
	BitArray OR(BitArray) const;
	void shiftLeft(int);
	void shiftRight(int);
	unsigned long long getUnsignedIntegralValue() const;
	void setIntegralValue(unsigned long long);
	~BitArray();
};