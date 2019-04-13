// TabletHexConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int hexToDec(string chars);

int main(int argc, char *argv[])
{
	
	if (argc < 2)
	{
		cout << "Drag a file into the application to convert it\n";
		system("pause");
		return 0;
	}
	if (argc == 2)
	{
		ifstream file;

		string filePath = argv[1];

		file.open(filePath);
		if (!file)
		{
			cout << "Unable to open file\n";
			return 1;
		}

		string token;
		bool startDecoding = false;
		int bytesCaptured = 0;
		long int bytes[7];

		while (file >> token) {
			if (startDecoding == true)
			{
				bytes[bytesCaptured] = hexToDec(token);
				bytesCaptured++;

				if (bytesCaptured == 7)
				{
					// We have our chunk of 7 bytes. Now retrieve the x, y and click values out of it
					long int xVal = 0;
					bytes[0] = bytes[0] & 0b00000011;
					bytes[0] = bytes[0] << 14;

					bytes[1] = bytes[1] & 0b01111111;
					bytes[1] = bytes[1] << 7;

					bytes[2]  = bytes[2] & 0b01111111;
					xVal = bytes[0] | bytes[1] | bytes[2];
					
					long int yVal = 0;
					int byteCopy = bytes[3];
					bytes[3] = bytes[3] & 0b00000011;
					bytes[3] = bytes[3] << 14;

					bytes[4] = bytes[4] & 0b01111111;
					bytes[4] = bytes[4] << 7;

					bytes[5] = bytes[5] & 0b01111111;
					yVal = bytes[3] | bytes[4] | bytes[5];

					int pressureVal = 0;
					bytes[6] = bytes[6] & 0b00111111;
					bytes[6] = bytes[6] << 1;
					byteCopy = byteCopy >> 2;
					byteCopy = byteCopy & 0b00000001;
					pressureVal = bytes[6] | byteCopy;


					cout << "(" << xVal << "," << yVal << ") " << pressureVal << endl;
					bytesCaptured = 0;

				}
			}
			else if (token == "FF")
			{
				// 'FF' is the first data sent over serial when the debug flag is true in the raspberry pi's code
				startDecoding = true;
			}
		}

		file.close();
	}

	system("pause");
    return 0;
}

// Takes in a string of hex characters and converts it to dec value
int hexToDec(string chars)
{
	int i, r, len, hex = 0;
	
	len = chars.length();
	for (i = 0; chars[i] != '\0'; i++)
	{
		len--;
		if (chars[i] >= '0' && chars[i] <= '9')
			r = chars[i] - 48;
		else if (chars[i] >= 'a' && chars[i] <= 'f')
			r = chars[i] - 87;
		else if (chars[i] >= 'A' && chars[i] <= 'F')
			r = chars[i] - 55;
		hex += r * pow(16, len);
	}

	return hex;
}


