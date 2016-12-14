This program must be compiled using the OSU flip server, with the command g++ CS325_Project2.cpp -o name_you_would_like_to_call_it. Ie, g++ CS325_Project2.cpp -o Project2Group6 if you would like to call the program Project2Group6

To run, while at the command line, enter the name of the program followed by the name of the text file you would like to read from, without the .txt extension (program only works with .txt files).  For instance, if your file is called "Amount.txt", enter Amount into the command line.

Once the program has finished it will output the results into the folder where you have run this program; the output file will be called your_file_name_change.txt; using the above example, it would be "Amountchange.txt." The output file contains the total number of coins and which coins were used to make change. The output file should not be read using MS notepad, as results will all be on a single line; it's recommended to use another text editor, such as WordPad. In addition to the coin output, the algorithm times will also be printed to the console.

This program uses three different algorithms to exchange a specific monetary value into the least amount of coins possible.
In your input text document in the folder you will be running this program, specify the value of each coin in the format, [X,Y,Z], where X, Y, and Z are all values of the coins.
In the next line, enter the Value you would like to exchange.