#include "simpletools.h"                      

int convert(char* logname);

int main()                                    
{
  char* test;
  int result;
  
  while(1)
  {
    memset(test, 0, 7);
    print("Enter a logical address string (xxx.xxx): ");
    test=getStr(test, 7);
    result = convert(test);
    print("\nConverted physical address = %d\n", result);
  }  
}


int convert(char* logname)
{
	char address[7];
	char first[3];
	char last[3];
	int i_first=0;
	int i_last=0;
	int i_p_address;

	strcpy(address, logname);
	for (int i = 0; i < 3; i++)
	{
		first[i] = address[i];
		last[i] = address[i + 4];
	}

  for (int j = 0; j < 3; j++)
  {
    if (first[j] == '1') { i_first += 0b00000001 << (2-j); }
    if (last[j] == '1') { i_last += 0b00000001 << (2-j); }
  }    
	i_p_address = (i_first * 10) + i_last;

	return i_p_address;
}

