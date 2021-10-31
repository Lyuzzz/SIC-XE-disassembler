CS 530
Assignment: SIC/XE Disassembler

Group members:
Zhiyu Li		#821009794			cssc4632
Hengshuo Zhang	#822112545			cssc4662

File include: (on Gradescope)
	main.cpp
	Readme.txt
	Makefile

Step for a run with Makefile: (in Edoras)
1)Ensure that all of the following files are included in the run file.
		main.cpp
		Makefile
		test.obj
		test.sym
2)Enter the command "Make" to execute the program.
3)Enter the command ". /dissem test.obj test.sym" to execute the compilation.
4)Enter the command "cat out.lst" to view the disassembly results.
5)Execute the command "make clean" to remove all the "*. o" files.

Main.cpp (basic structure):
	Conversion: Binary Hex Decimal int String
	Opcode: Use the map method to associate opcode, mnemonic and format.
	Symtab: Using the map function, read the "test.sym" file and store the symbol table and literal table into two separate .sym files. 
	
	Read/Write Head Record: Read the line starting with "H" and return the program start position and ControlSection.
	Read/Write Text Record: 
	Read/Write End Record: Read the line starting with "E" and return to the program termination position.

	main function: Reads the ".obj" and ".sym" files, executes the run command, and writes and saves the results in the ".lis" file.


Program structure:
~Help Function
// This equation is used to convert hexadecimal numbers to decimal numbers.
	int HextoDecimal(string hexvalue);
// This equation is used to convert the letters contained in String type values to uppercase. (Easy to call hexadecimal related functions)
	string toUpper(string s);
// This equation is used to convert decimal numbers to hexadecimal numbers.
	string DecToHex(int num);
// This equation is used to convert Int type values to String type values.
	string InttoString(int n);
// This equation is used to convert a hexadecimal String type value to a binary String type value.
	string strToBin(string str);
// This equation is used to convert a binary String type value to a hexadecimal String type value.
	string binToStr(string str);
// This equation is used to convert a hexadecimal String type value to a String type value in the form of Two's complement.
	string twosComp(string hex);

~Opcode Table
	const static string opcode[];
	const static string mnemonic[];
	const static string format[];
// This equation is used to find the opcode.
	string getOpcode(string key);
// This equation is used to obtain the exact opcode value in the case of "format = 3/4".
	string findOpcode(string opcodes);
//This equation is used to obtain the Mnemonic of the opcode.
	string getMnemonic(string opcodes);
//This equation is used to obtain the Format of the opcode.
	string getFormat(string opcodes);
//This equation is used to obtain the value of the nixbpe take.
	string operandFinder(string op_val);
//This equation is used to adjust the data output format to ensure that 4 values are stored and filled from front to back with zeros for values below 4. (location address)
	string formataddr(string addr);



~Find and print Symbol Table
//This equation is used to open the ". sym" file and to read and sort it. The symbol and literal are stored in two separate tables for easy retrieval and recall.
	void creatFile();
//This equation opens the "z.sym" file and stores the symbol value in the file. Use the map function to perform the operation.
	map<string, string> symbolTable();
// This equation is to help find the symbol of Base Oprend.
	map<string, string> symbolTableReverse();
//This equation opens the "h.sym" file and stores the literal value in the file. Use the map function to perform the operation.
	map<string, string> symbolTablelit();
//
	map<string, string> LitTable();
//
	map<string, string> LenTable();
// This equation determines whether the input value matches the Literal Value, and if so, returns the element in the map.
	bool isLit( string curraddr);
// Get first 6 (index:1-7) numbers, for program start address. Print start address and symbol.
	string HeadRecord(string Hre);
// Use the read values to compare directly with the opcode table. And return the corresponding opcode Mnemonic.
	string op(string OTre);
//
	string objectcode(string obj);

~Main function
	[generate the “out.lst”]
	[read the “test.obj”]
	Read “H”
		Get first 6 (index:1-7) numbers, for program start address.
		Print start address and symbol.
	Read ”T” (Line by line)
		Get first 6 (index: 1-7) numbers, for starting address.
		Get follow up 2 (index: 8-9) numbers, for text record size.
Set a current address which equals to starting address for now.
While each line test record length is more significant than 1
Detect RESB, if the address at the end of the last test record is less than the following starting address, RESB active with integer need to add to the last address to equal to the following starting address.Find the literal or constant and send it to the out.lst with LTORG.
Check the object code is format two or not. If not, then check the object code is format four or not; if not, check format 3.
If format 2 met, print it to the out. lst.
If format four is met, check its nixbpe, which detects it is indirect, Immediate, or simple. Then check if the operand is LDB, print BASE following line.
If format 4 is met, check its nixbpe, which detects it is indirect, Immediate, or simple. Then, if the displacement is negative, use two’s complement to solve.  	
	

Read ”E”
 		if the last address is not equal to the total length of the Record, RESB active.
		Detects lines preceded by an "E".
		Print the End statement.
	File Close.




Some Common after Assignment:
This project was really confusing for me at the beginning because my group and I had never been exposed to the C++ programming language. It was no exaggeration to say that we needed to learn the language from the very basics of printing "Hello World!
This was a very challenging project for us because the content we studied and examined in the course was mainly SIC/XE assembly, and the whole project was SIC/XE disassembly.
At the beginning of the project, we studied how to extract the elements in the symbol table and store them using the map function. As well as trying to understand how the whole should work and the final presenting.
In the middle of the project, we spent a lot of time on understanding and thinking about how to read the Text Record, starting with extracting the Starting Address and Text Record Size, and looking at the relationship between the nixbpe value and the format step by step to understand how the program can determine and read the value in the symbol table. 
We tried a lot of methods in the middle of the project, but the one that finally guided us to success was Pseudocode, which was a very important step to write a clear and logical Pseudocode to help us understand how the program works in general. This is a crucial step in organizing our thoughts and achieving success.
It was incredible for me and my teammates to be able to complete this project. Two people were able to start from learning C++ in such a short period of time to eventually present the opposite of what we learned in the course in SIC/XE assembly in the form of code. I think that is very impressive.
Maybe our code doesn't run all the test files flawlessly, but we've gained enough new knowledge.

Best Team
Zhiyu Li 
Hengshuo Zhang