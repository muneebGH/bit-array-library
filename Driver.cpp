#include"BitArray.h"
int main()
{
	BitArray a{ 16 };
	a.on(0);
	a.on(1);
	a.on(15);
	a.dump();

	cout << a.getUnsignedIntegralValue();
	system("pause");
	return 0;
}