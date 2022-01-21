// sercomm.cpp : Defines the entry point for the console application.
// library: https://github.com/imabot2/serialib

#include "stdafx.h"
#include <iostream>
// Serial library
#include "serialib.h"

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
#endif
#if defined (__linux__) || defined(__APPLE__)
    #define SERIAL_PORT "/dev/ttyACM0"
#endif


/*!
     \brief     Pass/Fail Loopback Test (connect loopback cable)
     \param     totalCom : total number of COM port
     \return    Null
  */
void Process(short totalCom)
{
	// Serial object
    serialib serial;
	char* ComPort = SERIAL_PORT1;
	char* rString = new char[1];
    int ret = 0;

	for (int x = 0; x < totalCom; x++)
	{
		switch (x) {
			case 0:
				ComPort = SERIAL_PORT1;
			break;
			case 1:
				ComPort = SERIAL_PORT2;
			break;
			case 2:
				ComPort = SERIAL_PORT3;
			break;
			case 3:
				ComPort = SERIAL_PORT4;
			break;
			case 4:
				ComPort = SERIAL_PORT5;
			break;
			case 5:
				ComPort = SERIAL_PORT6;
			break;
		}
		
		// Connection to serial port
		char err = serial.openDevice(ComPort, 115200);

		// If connection fails, return the fail message, display a success message
		if (err != 1) 
			printf("\nFail connection(%s)\n", ComPort);
		else {
			printf("\nSuccess connection(%s)\n", ComPort);

			// Display ASCII characters (from 32 to 128)
			for (int c = 32; c < 35; c++)
			{
				serial.writeChar(c);
				Sleep(100);
				ret = serial.readChar(rString, 100);
				//printf("rString: %d| ret: %d\n", (int)rString[0], ret);

				if ((int)rString[0] == c)
				{
					printf("%s Pass | ", ComPort);
					rString[0] = int(0);	//reset
				}
				else
					printf("%s Fail | ", ComPort);

				Sleep(100);
			}

			// Close the serial device
			serial.closeDevice();
		}
	}
}


/*!
 * \brief main  Simple example that send ASCII characters to the serial device
 * \return      0 : success
 *              <0 : an error occured
 */
int _tmain(int argc, _TCHAR* argv[])
{
	short TotalCom = 0;

    // Check how many serial ports to run
	std::cout << "Please enter number of com port (1-6): ";
	std::cin >> TotalCom;
	
	// Pass/Fail Loopback Test
	Process(TotalCom);
	
	for(int x=0; x<20; x++)
	{
		system("pause");
		Process(TotalCom);
	}
	
	return 0;
}

