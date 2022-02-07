// sercomm.cpp : Defines the entry point for the console application.
// library: https://github.com/imabot2/serialib
//
// version 1.0.0.3 : Delay changes from 2s to 3s
// version 1.0.0.2 : Add Total COM Number from 6 to 14
//					 Add function to allow user to input start of COM number to run
// version 1.0.0.1 : Initial


#include "stdafx.h"
#include <iostream>
// Serial library
#include "serialib.h"
#include <string>

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif


#if defined (_WIN32) || defined(_WIN64)
    //for serial ports above "COM9", we must use this extended syntax of "\\.\COMx".
    //also works for COM0 to COM9.
    //https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea?redirectedfrom=MSDN#communications-resources
    #define SERIAL_PORT1 "\\\\.\\COM1"
	#define SERIAL_PORT2 "\\\\.\\COM2"
	#define SERIAL_PORT3 "\\\\.\\COM3"
	#define SERIAL_PORT4 "\\\\.\\COM4"
	#define SERIAL_PORT5 "\\\\.\\COM5"
	#define SERIAL_PORT6 "\\\\.\\COM6"
	#define SERIAL_PORT7 "\\\\.\\COM7"
	#define SERIAL_PORT8 "\\\\.\\COM8"
	#define SERIAL_PORT9 "\\\\.\\COM9"
	#define SERIAL_PORT10 "\\\\.\\COM10"
	#define SERIAL_PORT11 "\\\\.\\COM11"
	#define SERIAL_PORT12 "\\\\.\\COM12"
	#define SERIAL_PORT13 "\\\\.\\COM13"
	#define SERIAL_PORT14 "\\\\.\\COM14"
#endif
#if defined (__linux__) || defined(__APPLE__)
    #define SERIAL_PORT "/dev/ttyACM0"
#endif


/*!
     \brief     Write, read and compare the char on the current serial port
     \param     totalCom : total number of COM port
	 \param		startCom : COM number to start
     \return    Null
  */
void Process(short totalCom, short startCom)
{
	// Serial object
    serialib serial;
	char* ComPort = SERIAL_PORT1;
	char* rString = new char[1];
    int ret = 0;

	for (int x = startCom; x < (totalCom + startCom); x++)
	{
		switch (x) {
			case 1:
				ComPort = SERIAL_PORT1;
			break;
			case 2:
				ComPort = SERIAL_PORT2;
			break;
			case 3:
				ComPort = SERIAL_PORT3;
			break;
			case 4:
				ComPort = SERIAL_PORT4;
			break;
			case 5:
				ComPort = SERIAL_PORT5;
			break;
			case 6:
				ComPort = SERIAL_PORT6;
			break;
			case 7:
				ComPort = SERIAL_PORT7;
			break;
			case 8:
				ComPort = SERIAL_PORT8;
			break;
			case 9:
				ComPort = SERIAL_PORT9;
			break;
			case 10:
				ComPort = SERIAL_PORT10;
			break;
			case 11:
				ComPort = SERIAL_PORT11;
			break;
			case 12:
				ComPort = SERIAL_PORT12;
			break;
			case 13:
				ComPort = SERIAL_PORT13;
			break;
			case 14:
				ComPort = SERIAL_PORT14;
			break;
			default:
				ComPort = SERIAL_PORT1;
			break;
		}
		
		// Connection to serial port
		char err = serial.openDevice(ComPort, 115200);

		// If connection fails, return the fail message, display a success message
		if (err != 1) 
			printf("\nFail connection(%s)\n", ComPort);
		else
			printf("\nSuccess connection(%s)\n", ComPort);


		// Display ASCII characters (from 32 to 128)
		for (int c = 32; c < 35; c++)
		{
			serial.writeChar(c);
			Sleep(100);
			ret = serial.readChar(rString, 100);
			//printf("rString: %d| ret: %d\n", (int)rString[0], ret);
			if((int)rString[0] == c)
			{
				printf("%s Pass | ", ComPort);
				rString[0] = int(0);	//reset
			}
			else 
				printf("%s Fail | ", ComPort);
			//Sleep(100);
		}

		Sleep(3000);
		// Close the serial device
		serial.closeDevice();

	}
}


/*!
     \brief     Validate user input
     \param     totalCom : total number of COM port
	 \param		startCom : COM number to start
     \return    Null
  */
bool ErrChecking(short totalCom, short startCom)
{
	//start 14 total 1 = 15 (ok)
	//start 14 total 2 = 16 (not ok)
	//start 13 total 2 = 15 (ok)
	//start 1 total 14 = 15 (ok)
	if(startCom < 1)
	{
		std::cout << "\nInvalid Input or over maximum com port. \n";
		return FALSE;
	}
	else if(totalCom < 1)
	{
		std::cout << "\nInvalid Input or over maximum com port. \n";
		return FALSE;
	}
	else if ((totalCom + startCom) < 16)
	{
		return TRUE;
	}
	else
	{
		std::cout << "\nInvalid Input or over maximum com port. \n";
		return FALSE;
	}
}


/*!
 * \brief main  Simple example that send ASCII characters to the serial device
 * \return      0 : success
 *              <0 : an error occured
 */
int _tmain(int argc, _TCHAR* argv[])
{
	short TotalCom = 1;
	short StartCom = 1;
	std::string cont = "";
	short ret = 0;

	while(TRUE)
	{
		// COM Number to Start
		std::cout << "Please enter which com port to start (1-14): ";
		std::cin >> StartCom;

		// Check how many serial ports to run
		std::cout << "Please enter total number of com port (1-14): ";
		std::cin >> TotalCom;

		if(!std::cin) // or if(cin.fail())
		{
			// user didn't input a number
			std::cin.clear(); // reset failbit
			std::cin.ignore(10000, '\n'); //skip bad input
			// next, request user reinput
			std::cout << "\n";
			printf("\nInvalid Input or over maximum com port. \n");
		}
		else
		{
			ret = ErrChecking(TotalCom, StartCom);

			if(ret)
			{
				// Pass/Fail Task
				Process(TotalCom, StartCom);
	
				for(int x=0; x<30; x++)
				{
					system("pause");
					Process(TotalCom, StartCom);
				}	
			}
		}
	}

	return 0;
}

