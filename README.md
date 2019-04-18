# Tablet Hex Converter
The Tablet Hex Converter is a test tool created for a project I did. It is used to test serial output data of a microcontroller and see if it accurately mimics the output stream of a Wacom tablet. The converter takes a text file of recorded hex data and converts it back into decimal values.

The data being converted takes the following format
![](/TabletHexConverter/Documents/binary_format.PNG)

The converter will only get the x, y, and pressure data.

An example of a file that could be inputted into this application can be found [here](/TabletHexConverter/Documents/example_serial_out.txt). It is important to note that the converter looks for the byte `FF` and starts decoding everything past that point. `FF` is sent by the output device during testing.
