

/*
Student Name: SHUBHANKUR KUMAR
Student Id: 2018UEC1051
Description: This Program is to build a simulator for the Booth's 2's
complement number multiplier. In this practice, I used 16-bit operands for the 
multiplication, i.e., 16-bit multiplicand, 16-bit multiplier,
and 32-bit product. 
The baseline simulation granurarity is 1-bit ALU component implemented by 
ALU_1_bit() function, and this program also includes ALU_16_BIT() function, 
16-bit Booth's multiplier implemented by booth() function,and the main driver.
*/

#include<iostream>
#include <bitset> 
using namespace std;

unsigned short s = 0;
bitset<16> result{ s };
int l;

unsigned short accumulator = 0;
unsigned short MQ0 = 0;
unsigned short counter = 15;

bitset<16> AC{ accumulator };

/*
ALU_1_bit() function implements the simulator of 1-bit ALU, which performs at least 
addition and subtraction operations;
*/

int ALU_1_bit(int a, int b, int cin,string op)
{
	
	int carryout = 0;
	if (op == "add")
	{
		if (l < 16)
		{
			result[l] = a^b^cin;
			l++;
		}

		carryout = (a*b) + cin*(a^b);
		return carryout;
	}
	else if(op == "sub")
	{
		if (b == 0)
		{
			b = 1;
		}

		else 
		{
			b = 0;
		}
		if (l < 16)
		{
			result[l] = a^b^cin;
			l++;
		}

		carryout =(a*b) + cin*(a^b);
		return carryout;


	}

}
/*
ALU_16_BIT() function implements the simulator of 16-bit ALU, which uses 
the ALU_1_bit() function defined above. The ALU_16_BIT() function checks
the overflow error
*/

int ALU_16_BIT(bitset<16> M, bitset<16>N,string operation)
{
	int carry = 0;
	l = 0;
	result = 0;
	if (operation == "sub")
	{
		if (M[0] == 0 && N[0] == 1)
		{
			carry = 1;
		}
	}
	for (int y = 0; y < 16; y++)
	{
	 carry = ALU_1_bit(M[y],N[y],carry,operation);
	}

	AC = result;
	return carry;
}

/*
booth() function implements the simulator of the Booth's multiplier, 
which uses the 16-bit ALU as a subcomponent. This module have subcomponents like 
Registers MD, AC, MQ (16 bits each), and the cycle counter (initialized to 16);
This module is responsible for displaying the system state (register contents) 
at each clock;
*/

int booth(bitset<16>MD, bitset<16> MQ)
{
	bitset<1> MQ_1_BIT{ MQ0 };
	bitset<4> cycle_counter{ counter };
	
	cout<< "Cycle-Counter		MD			AC			MQ		MQ_1_BIT" << endl;
	cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << MQ_1_BIT << "  ---initial step "<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	for (int k = 0; k < 16; k++)
	{
		int x;
		unsigned short dec = 1;
		if (MQ[0] == 0 && MQ_1_BIT[0] == 0)
		{
			AC = AC;//first step
			cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << MQ_1_BIT << "  ---step1 of iteration " << k << endl;
			MQ_1_BIT[0] = MQ[0];
			MQ = MQ >> 1;
			MQ[15] = AC[0];
			
			AC = AC >> 1;
			AC[15] = AC[14]; //arithmetic shift

		
		}

		else if (MQ[0] == 0 && MQ_1_BIT[0] == 1)
		{
			ALU_16_BIT(AC, MD,"add");

			cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << MQ_1_BIT << "  ---step1 of iteration " << k << endl;

			// Now arithmetic shift

			MQ_1_BIT[0] = MQ[0];
			MQ = MQ >> 1;
			MQ[15] = AC[0];
			
			AC = result;
			AC = AC >> 1;
			AC[15] = AC[14]; 
		}
		else if (MQ[0] == 1 && MQ_1_BIT[0] == 0)
		{
			ALU_16_BIT(AC, MD,"sub");
			cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << MQ_1_BIT << "  ---step1 of iteration " << k << endl;

			// Now arithmetic shift

			MQ_1_BIT[0] = MQ[0];
			MQ = MQ >> 1;
			MQ[15] = AC[0];
			
			AC = AC >> 1;
			AC[15] = AC[14]; 


		}
		else if (MQ[0] == 1 && MQ_1_BIT[0] == 1)
		{
			AC = AC;
			cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << MQ_1_BIT << "  ---step1 of iteration " << k << endl;

			MQ_1_BIT[0] = MQ[0];
			MQ = MQ >> 1;
			MQ[15] = AC[0];
	
			AC = AC >> 1;
			AC[15] = AC[14]; //arithmetic shift

		}

		cout << cycle_counter << "		" << MD << "	" << AC << "	" << MQ << "	  " << MQ_1_BIT <<"  ---step2 of iteration "<<k<<endl;
		cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
		counter--;
		cycle_counter = counter;
	}
	cout << endl << endl;
	cout << "The Answer is : " << AC << MQ << endl;

	return 0;

}

/*
The main() function accesses two input operands (in 2's
 complement binary) from keyboard and calls the Booth's multiplier by 
 passing the operands. 
*/
int main()
{
	bitset<16> bitset1; 
	bitset<16> bitset2;
	
	cout << "Enter first number : " << endl;
	cin >> bitset1;
    
	cout << "Enter Second number : " << endl;
	cin >> bitset2;
	
	int overflow = booth(bitset1,bitset2);

	cout << endl << endl;

	if (overflow == 1)
		cout << "OVERFLOW..." << endl;
	else
		cout << "NO OVER FLOW...." << endl << endl << endl;


	system("pause");
    return 0;
}
