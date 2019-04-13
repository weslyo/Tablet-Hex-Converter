# Tablet-Hex-Converter
The Tablet-Hex-Converter code is used to take the hex data outputted by the ssl-tablet project and convert it back into meaningful data for testing purposes.

The outputted data takes the following format
![](/Documents/binary_format.PNG)

The converter only gets the x, y, and pressure data since that is all we need to test.

An example of a file that could be inputted into this application can be found [here](https://github.com/weslyo/Tablet-Hex-Converter/blob/master/Documents/example_serial_out.txt). It is important to note that the converter looks for the byte `FF` and starts decoding everything past that point. `FF` is sent by the raspberry pi when the debug flag is set to true.
