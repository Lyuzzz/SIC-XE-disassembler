/******************************************************************************************
 * Group members:
 * Zhiyu Li		    #821009794			cssc4632
 * Hengshuo Zhang	#822112545			cssc4662
 ******************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <streambuf>
#include <vector>
#include <utility>
#include <map>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;
#define Opcode_List_lenth 59

/*********************convert****************************/
/*************************************************************************
 * This equation is used to convert hexadecimal numbers to decimal numbers.
 * @param hexadecimal numbers
 * @return decimal numbers
 *************************************************************************/
int HextoDecimal(string hexvalue) {
    int num = 0;
    int num16 = 1;

    string numlist = "0123456789ABCDEF";
    for (int i = hexvalue.length() - 1; i >= 0; --i) {
        num += numlist.find(toupper(hexvalue[i])) * num16;
        num16 *= 16;
    }
    return num;
}

/*************************************************************************
 * This equation is used to convert the letters contained in String type values to uppercase.
 * (Easy to call hexadecimal related functions)
 * @param string
 * @return Upper case string
 *************************************************************************/
string toUpper(string s){
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}
/*************************************************************************
 * This equation is used to convert decimal numbers to hexadecimal numbers.
 * @param decimal numbers
 * @return hexadecimal numbers
 *************************************************************************/
string DecToHex(int num){
    string str;
    stringstream ss;
    ss << std::hex << num;
    ss >> str;
    str = toUpper(str);
    return str;
}
/*************************************************************************
 * This equation is used to convert Int type values to String type values.
 * @param   int
 * @return  string
 *************************************************************************/
string InttoString(int n) {
    ostringstream stream;
    stream << n;
    return stream.str();
}
/*************************************************************************
 * This equation is used to convert a hexadecimal String type value to a binary String type value.
 * @param hexadecimal String type value
 * @return binary String type value
 *************************************************************************/


//need big fix under
string HextoBin(string str){
    string Bin = "";
    char Hex;
    while(!str.empty()){
        Hex = str[0];
        switch (Hex){
            case '0': Bin += "0000";
                break;
            case '1': Bin += "0001";
                break;
            case '2': Bin += "0010";
                break;
            case '3': Bin += "0011";
                break;
            case '4': Bin += "0100";
                break;
            case '5': Bin += "0101";
                break;
            case '6': Bin += "0110";
                break;
            case '7': Bin += "0111";
                break;
            case '8': Bin += "1000";
                break;
            case '9': Bin += "1001";
                break;
            case 'A': Bin += "1010";
                break;
            case 'B': Bin += "1011";
                break;
            case 'C': Bin += "1100";
                break;
            case 'D': Bin += "1101";
                break;
            case 'E': Bin += "1110";
                break;
            case 'F': Bin += "1111";
                break;
        }
        str.erase(0,1);
    }
    return Bin;
}
/*************************************************************************
 * This equation is used to convert a binary String type value to a hexadecimal String type value.
 * @param binary String type value
 * @return hexadecimal String type value
 *************************************************************************/
string BintoHex(string Binary){
    string hex = "";
    string Bin = "";
    while(!Binary.empty()){
        Bin = Binary.substr(0,4);

        if(Bin == "0000") {hex += "0";}
        else if(Bin == "0001") {hex += "1";}
        else if(Bin == "0010") {hex += "2";}
        else if(Bin == "0011") {hex += "3";}
        else if(Bin == "0100") {hex += "4";}
        else if(Bin == "0101") {hex += "5";}
        else if(Bin == "0110") {hex += "6";}
        else if(Bin == "0111") {hex += "7";}
        else if(Bin == "1000") {hex += "8";}
        else if(Bin == "1001") {hex += "9";}
        else if(Bin == "1010") {hex += "A";}
        else if(Bin == "1011") {hex += "B";}
        else if(Bin == "1100") {hex += "C";}
        else if(Bin == "1101") {hex += "D";}
        else if(Bin == "1110") {hex += "E";}
        else if(Bin == "1111") {hex += "F";}

        Binary.erase(0,4);
    }
    return hex;

}
/*************************************************************************
 * This equation is used to convert a hexadecimal String type value to a String type value in the form of Two's complement.
 * @param string Hex value
 * @return Two's complement
 *************************************************************************/
string twosComp(string hex){
    string bin = HextoBin(hex);


    for(int i = 0; i < bin.length(); i++){
        if(bin[i] == '0')
            bin[i] = '1';
        else
            bin[i] = '0';
    }


    string HexN = BintoHex(bin);
    int dec = HextoDecimal(HexN);
    dec++;
    HexN = DecToHex(dec);
    return HexN;
}

/****************************************opcode******************************************/


const static string opcode[] = {"18", "58", "90", "40", "B4", "28","88", "A0",
                                "24", "64", "9C", "C4","C0", "F4", "3C", "30",
                                "34", "38","48", "00", "68", "50", "70", "08","6C",
                                "74", "04", "D0", "20", "60","98", "C8", "44", "D8",
                                "AC", "4C","A4", "A8", "F0", "EC", "0C", "78","54",
                                "80", "D4", "14", "7C", "E8","84", "10", "1C", "5C",
                                "94", "B0","E0", "F8", "2C", "B8", "DC"};
const static string mnemonic[] = {"ADD", "ADDF", "ADDR", "AND",
                                  "CLEAR", "COMP","COMPF", "COMPR",
                                  "DIV", "DIVF", "DIVR", "FIX","FLOAT",
                                  "HIO", "J", "JEQ", "JGT", "JLT","JSUB",
                                  "LDA", "LDB", "LDCH", "LDF", "LDL","LDS",
                                  "LDT", "LDX", "LPS", "MUL", "MULF","MULR",
                                  "NORM", "OR", "RD", "RMO", "RSUB","SHIFTL",
                                  "SHIFTR", "SIO", "SSK", "STA", "STB","STCH",
                                  "STF", "STI", "STL","STS", "STSW","STT", "STX",
                                  "SUB", "SUBF", "SUBR", "SVC","TD", "TIO", "TIX",
                                  "TIXR", "WD"};

const static string format[] = {"3/4", "3/4", "2", "3/4", "2", "3/4", "3/4", "2", "3/4", "3/4", "2", "1", "1", "1",
                                "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4",
                                "3/4", "3/4", "3/4", "3/4", "2", "1", "3/4", "3/4", "2", "3/4", "2", "2", "1", "3/4",
                                "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "3/4", "2",
                                "2", "3/4", "1", "3/4", "2", "3/4"};

/*************************************************************************
 * This equation is used to find the opcode.
 *************************************************************************/
string getOpcode(string key){
    unordered_map<string,string>opmap;

    for(int i =0; i<59; i++){
        opmap[opcode[i]] = mnemonic[i];
    }

    if (opmap.find(key) == opmap.end())
        return " not found\n";
    else

        return opmap[key];

}
/*************************************************************************
 * This equation is used to obtain the exact opcode value in the case of "format = 3/4".
 *************************************************************************/
string findOpcode(string opcodes) {

    //get 1st number (Hex and Binary) 0(01)
    string first_ox = opcodes.substr(0, 1);

    //
    string first_ob = HextoBin(first_ox);

    //get 2nd number (Hex and Binary)
    string second_ox = opcodes.substr(1, 1);
    string second_ob = HextoBin(second_ox);
    string second_shift = second_ob.substr(0, 2) + "00";

    //Reverse Binary to Hex >> Compare with opcode
    string final_opcode = BintoHex(first_ob) + BintoHex(second_shift);

    return final_opcode;
}
/*************************************************************************
 * This equation is used to obtain the Mnemonic of the opcode.
 *************************************************************************/
string getMnemonic(string opcodes) {
    unordered_map<string, string> opcode_map;

    for (int i = 0; i < Opcode_List_lenth; i++) {
        opcode_map[opcode[i]] = mnemonic[i];
    }
    return opcode_map[opcodes];
}
/*************************************************************************
 * This equation is used to obtain the Format of the opcode.
 *************************************************************************/

string getFormat(string opcodes) {
    unordered_map<string, string> opmap;
    for (int i = 0; i < Opcode_List_lenth; i++) {
        opmap[opcode[i]] = format[i];
    }
    return opmap[opcodes];
}
/*************************************************************************
 * This equation is used to obtain the value of the nixbpe take.
 *************************************************************************/
string operandFinder(string op_val){

    //"ni" part
    string opval1_0b = HextoBin(op_val.substr(0,1));

    //"xbpe" parts
    string opval2_0b = HextoBin(op_val.substr(1,1));

    string temp = opval1_0b.substr(2,2);
    string nixpbe = temp + opval2_0b;

    return nixpbe;




}
/*************************************************************************
 * This equation is used to adjust the data output format to ensure that 4 values are stored
 * and filled from front to back with zeros for values below 4. (location address)
 *************************************************************************/
string formataddr(string addr){
    stringstream ss;
    string str;

    if(addr.length() > 4)
        addr = addr.substr(addr.length()-4,4);

    ss << setfill('0') << setw(4) << addr;
    ss >> str;
    return str;
}

/******************get the sym table***********************************/
/*************************************************************************
 * This equation is used to open the ". sym" file and to read and sort it.
 * The symbol and literal are stored in two separate tables for easy retrieval and recall.
 *************************************************************************/
string file = "test";

void creatFile(){
    string line;
    ifstream inFile;
    //int c = count(file);
    inFile.open( file + ".sym");
    ofstream MyFile( "z.sym");
    ofstream LitFile( "h.sym");


    //to erase the lines that mess with map

    while (getline(inFile, line) && line.find("Name")) {
        if (line.find("Symbol") == line.npos)
            if (line.find("--") == line.npos)
                MyFile << line << endl;
        if (line.empty()){
            break;


        }


    }
    while(!inFile.eof()){
        getline(inFile,line);
        if (line.find("Name") == line.npos)
            if (line.find("--") == line.npos)
                LitFile<<line<<endl;

    }



    MyFile.close();
    LitFile.close();
    inFile.close();



}

/*************************************************************************
 * This equation opens the "z.sym" file and stores the symbol value in the file.
 * Use the map function to perform the operation.
 *************************************************************************/

map<string, string> symbolTable(){
    map<string, string> myMap{};
    string line;
    ifstream inFile;
    inFile.open( "z.sym");
    int d = 0;
    while (inFile)
    {
        string key{}, value1{},value2{},value3{};

        {

            getline(inFile, value1, ' ') && getline(inFile, key);

            if(inFile) {
                string k = value1;
                if(k == ""){
                    k = "*" + InttoString(d);
                }
                int p = key.rfind(" 0");
                d++;
                myMap[key.substr(p+1,6)] = k;

            }
        }
    }
    inFile.close();
    return myMap;

}

/*************************************************************************
 * This equation is to help find the symbol of Base Oprend.
 *************************************************************************/
map<string, string> symbolTableReverse(){
    map<string, string> myMap{};
    string line;
    ifstream inFile;
    inFile.open( "z.sym");
    while (inFile)
    {
        string key{}, value1{},value2{},value3{};

        {

            getline(inFile, value1, ' ') && getline(inFile, key);

            if(inFile) {

                int p = key.rfind(" 0");

                myMap[value1] = key.substr(p+1,6);

            }
        }
    }
    inFile.close();
    return myMap;

}
/*************************************************************************
 * This equation opens the "h.sym" file and stores the literal value in the file. Use the map function to perform the operation.
 *************************************************************************/
map<string, string> symbolTablelit(){
    map<string, string> myMap{};
    string line;
    ifstream inFile;
    inFile.open( "h.sym");
    int d = 0;
    while (inFile)
    {
        string key{}, value1{},value2{},value3{};

        {

            getline(inFile, value1, ' ') && getline(inFile, key);

            if(inFile) {
                string k = value1;

                if(k == ""){

                    k = "*" + InttoString(d);
                }

                int p = key.rfind(" 0");
                d++;
                myMap[key.substr(p+1,6)] = k;

            }

        }
      }
    inFile.close();
    return myMap;

}
/*************************************************************************
 * Get the literal or constant by LitTable map
 *************************************************************************/
map<string, string> LitTable(){
    map<string, string> myMap{};
    vector<string> Lit;
    vector<string> cons;
    string line;
    ifstream inFile;
    inFile.open( "h.sym");
    int d = 0;


    while (inFile)
    {
        string key{}, value1{},value2{},value3{};

        {

            getline(inFile, value1, ' ') && getline(inFile, key);

            if(inFile) {
                int p = key.rfind(" 0");
                int l = key.rfind("C");
                int l2 = key.find("X");
                int c = key.rfind(" =");
                bool isConst = false;
                bool isX = false;
                Lit.push_back(key.substr(l+1,7));
                Lit.push_back(key.substr(l2+1,7));
                cons.push_back(key.substr(c+1,7));



                if(key.find("C'")){
                    isX;
                    isConst = true;
                }else if(key.find("X")){
                    isX = true;
                    isConst = true;
                }else{
                    isConst;
                }
                string k = value1;
                if(k == ""){

                    k = "*" + InttoString(d);
                }

                if(isX = true){
                    myMap.insert(pair <string, string> (k,key.substr(l2-1,10)));
                }else if(isX){
                    myMap.insert(pair <string, string> (k,key.substr(l-1,10)));
                }
                d++;



            }
        }
    }
    inFile.close();
    return myMap;
}

/*************************************************************************
 *get the length of literal or constant
 *************************************************************************/
map<string, string> LenTable(){
    map<string, string> myMap{};
    vector<string> Lit;
    vector<string> cons;
    string line;
    ifstream inFile;
    int d = 0;
    inFile.open( "h.sym");


    while (inFile)
    {
        string key{}, value1{},value2{},value3{};

        {

            getline(inFile, value1, ' ') && getline(inFile, key);

            if(inFile) {
                int p = key.rfind(" 0");
                int l = key.rfind("C");
                int l2 = key.find("X");
                int c = key.rfind(" =");
                int len = key.rfind(" ");
                bool isConst = false;
                bool isX = false;
                Lit.push_back(key.substr(l+1,7));
                Lit.push_back(key.substr(l2+1,7));
                cons.push_back(key.substr(c+1,7));



                if(key.find("C'")){
                    isX;
                    isConst = true;
                }else if(key.find("X")){
                    isX = true;
                    isConst = true;
                }else{
                    isConst;
                }
                string k = value1;
                if(k == ""){

                    k = "*" + InttoString(d);
                }
                if(isX = true){
                    myMap.insert(pair <string, string> (k,key.substr(len-3,1)));
                }else if(isX){
                    myMap.insert(pair <string, string> (k,key.substr(len-3,1)));
                }

                d++;


            }
        }
    }

    inFile.close();
    return myMap;
}
/*************************************************************************
 * This equation determines whether the input value matches the Literal Value, and if so, returns the element in the map.
 *************************************************************************/
bool isLit( string curraddr){
    ifstream litTab;
    litTab.open("h.sym");
    string lit;
    bool isLit = false;
    string::size_type idx;
    while(!(litTab.eof())){
        getline(litTab, lit);
        idx = lit.find(curraddr);
        if(idx == string::npos){
            isLit = false;

        }else{
            isLit = true;
            break;
        }
    }
    return isLit;

}
/*************************************************************************
 * Get first 6 (index:1-7) numbers, for program start address.
 * Print start address and symbol.
 *************************************************************************/
string HeadRecord(string Hre){
    // controlSection
    string firstLine;
    string controlSection = Hre.substr(1,6);
    // SIC/XE table Start address
    string firstStartAdr = Hre.substr(9, 4);
    if(HextoDecimal(firstStartAdr) > 0){
        firstLine = firstStartAdr + " " + controlSection + " " + "START" + " " + firstStartAdr;
    }else{
        firstLine = firstStartAdr + " " + controlSection + " " + "START" + " " + firstStartAdr.substr(3,1);
    }
    //string startAdr = Hre.substr()

    return firstLine;
}
/*************************************************************************
 * Use the read values to compare directly with the opcode table. And return the corresponding opcode Mnemonic.
 *************************************************************************/
string op(string OTre){
    string op = getMnemonic(findOpcode(OTre.substr(0,2)));

    return op;


}
/*int adderCounter(string rec, int curr){
    int curradr = curr;
    string addrMode = operandFinder(rec.substr(1,2));
    if(addrMode[5] = '1'){
        curradr +=  4;
    }else if(getFormat(findOpcode(rec.substr(0,2))) == "2"){
        curradr += 2;
    }else{
        curradr += 3;
    }
    return curradr;


}*/


/*string objFormat3(string Rec){
    string addrMode = operandFinder(Rec.substr(1,2));
    //simple
    if ((addrMode[0] = '1')&& (addrMode[1] = '1')){
        //PC or base and X
        if(addrMode[4] = '1'){

        }
    }
}*/

/*string TextRecord(string Tre){
    string Tline;
    Tre.erase(0,1);

    string TstartAdr = Tre.substr(0, 6);
    Tre.erase(0,6);
    int length = HextoDecimal(Tre.substr(0,2));
    Tre.erase(0,2);
    string instruction;

    int curr = HextoDecimal(TstartAdr.substr(2,4));
    int addr = 0;
    if(symbolTable()[TstartAdr] == "" && symbolTablelit()[TstartAdr] == ""){
        instruction = symbolTablelit()[TstartAdr] + "     ";
    }else{
        instruction = symbolTable()[TstartAdr];

    }
    string outputaddress = TstartAdr.substr(2,4);

    while(Tre.length()>1){
        string Hex = Tre.substr(0,2);
        Tre.erase(0,2);

        string opcode = findOpcode(Hex);
        string opcodeHex = getMnemonic(opcode);
        string opj = Hex.substr(1,1) + Tre.substr(0,1);
        string addrMode = operandFinder(opj);
        if(getFormat(opcode) == "2"){

            string format2Obj = Tre.substr(0,2);
            Tre.erase(0,2);
            return outputaddress + " " + instruction + " " + opcodeHex + "    " + Hex + format2Obj;
            addr = curr + 2;

        }
        else if(getFormat(opcode) == "3/4"){


            if (addrMode[5] = '1'){
                string op4 = op(Hex);
                string opr = symbolTable()["00" + Tre.substr(2,4)];
                string format4Obj = Hex + Tre.substr(0,6);
                Tre.erase(0,8);
                if(op4 == "LDB"){

                    return outputaddress + "    " + instruction + "  "  "+" + op4 + "    " + opr + "   " + format4Obj + '\n' + "              BASE" + " " + opr ;
                    addr = curr + 4;
                }
                return outputaddress + "    " + instruction + "  "  +  "+" + op4 + "    " + opr + "   " + format4Obj;
                addr = curr + 4;


            }else{
                Hex = Hex + Tre.substr(0, 3);
                Tre.erase(0, 3);
                string disp = Hex.substr(2, 3);
                return addr + "  " + Hex;
            }

        }
    }




    //int addr = adderCounter(Tre, HextoDecimal(TstartAdr.substr(2,4)));


    //Tline = outputaddress + " " + instruction + " " + objectcode(Tre);

    //cout<<DecToHex(addr);

    return Tline;

}*/


int main() {
    creatFile();
    //test.lst file creat
    ofstream outList("out.lst");

    //test.obj file open
    ifstream objFile;
    objFile.open( "test.obj");

    string Records;
    string Hrecord;
    string Trecord;
    string Erecord;

    string TstartAdr;
    string firstStartAdr;
    string currAdr;

    string firstLine;

    string Ltor;


    string instruction;
    string controlSec;
    string totalLen;
    string currAdd2;
    string BaseOprend;
    int *currA;
    int currAddr3 = 0;
    int curr = 0;
    int addr = 0;
    currA = &addr;
    while(!objFile.eof()){
        while(getline(objFile, Records)){
            //if line with "H" then print Head record on file
        if(Records[0] == 'H'){
            totalLen = Records.substr(15,4);
            outList<<HeadRecord(Records)<<endl;
            controlSec = Records.substr(1,6);
            firstStartAdr = Records.substr(9,4);


        }
            //if line with "T" then print Text record on file
        if(Records[0] == 'T') {
                string Tline;
            //remove first letter "T"
                Records.erase(0,1);
            //get the staring text address, store in the variable then remove it
                string TstartAdr = Records.substr(0, 6);
                Ltor = TstartAdr;
            //get the size of text record, store in the variable then remove it
                Records.erase(0,6);
                int length = HextoDecimal(Records.substr(0,2));
                Records.erase(0,2);
                string instruction;
            //Set variables to store the current location


                curr = HextoDecimal(TstartAdr.substr(2,4));
                addr = HextoDecimal(firstStartAdr) + curr ;

                cout<<addr<<endl;


            //Determine if the current address matches the value in the symbol table
                if(symbolTable()[TstartAdr] == "" && symbolTablelit()[TstartAdr] == ""){
                    instruction = symbolTablelit()[TstartAdr] + "     ";
                }else{
                    instruction = symbolTable()[TstartAdr];

                }
                string outputaddress = TstartAdr.substr(2,4);

                string TA;
                string Oprend;
                string currAdd;

            //Enter the loop until the full line of text record is read.
                while(Records.length()>1){
                    currAdd = addr;
                    cout<<addr;

                    //RESB
                    if((currAddr3 < curr)){
                        int baseAddr =  HextoDecimal(symbolTableReverse()[BaseOprend]);
                        string REvalue;
                        int v  = curr- currAddr3;
                        string insb2 = symbolTable()["00" + formataddr(DecToHex(currAddr3))];
                        string insb_resb = symbolTable()["00" + formataddr(DecToHex(currAddr3))];
                        if(baseAddr > currAddr3){
                           REvalue = InttoString(baseAddr- currAddr3);
                        } else{
                            REvalue = InttoString(curr- currAddr3);
                        }

                        outList << formataddr(DecToHex(currAddr3)) + "  " + insb_resb + "    RESB   " + REvalue << endl;
                        //if the BASE address is found and less than current address

                        if((currAddr3 < baseAddr)&&(baseAddr < curr)&&(symbolTableReverse().count(BaseOprend) !=0)){
                            string BESvalue = InttoString(curr - baseAddr);
                            string insbBE = symbolTable()["00" + formataddr(symbolTableReverse()[BaseOprend])];
                            outList << formataddr(symbolTableReverse()[BaseOprend]) + "  " + insbBE + "    RESB   " + BESvalue << endl;


                        }




                    }


                   /* if((HextoDecimal(currAdd2) != curr) && (symbolTable().count("00" + formataddr(currAdd2))!=0)&&(symbolTable()["00" + formataddr(currAdd2)] != symbolTable()[TstartAdr])){
                        string REvalue = InttoString(curr - HextoDecimal(currAdd2));
                        string insb2 = symbolTable()["00" + formataddr(currAdd2)];
                        string insb_resb = symbolTable()["00" + formataddr(currAdd2)];
                        cout << currAdd2 << endl;
                        //
                        outList << formataddr(currAdd2) + "  " + insb_resb + "    RESB   " + REvalue << endl;

                    }*/

                   /* if(symbolTablelit().count("00" + formataddr(DecToHex(curr))) != 0 ) {
                        string inst = symbolTablelit()["00" + formataddr(DecToHex(curr))];
                        string opr  = LitTable()[inst];
                        string ins = symbolTable()["00" + formataddr(DecToHex(curr))];
                        int foundCon = opr.find("=");
                        int leng = HextoDecimal(LenTable()[inst]);
                        int byte = leng/2;
                        string lit = opr.substr(foundCon+3, leng);
                        outList<<"           LTORG"<<endl;
                        outList<< formataddr(DecToHex(curr)) + "   " + ins  + "  *" +"  " + opr + "  " + lit <<endl;

                        addr = addr + byte;
                        Records.erase(0,leng);

                    }
                    else */
                   if((symbolTablelit().count("00" + formataddr(DecToHex(addr))) != 0 )){
                        string Hex = Records.substr(0,2);
                        Records.erase(0,2);
                        string opj = Hex.substr(1,1) + Records.substr(0,1);
                        string addrMode = operandFinder(opj);
                        string inst = symbolTablelit()["00" + formataddr(DecToHex(addr))];
                        string opr  = LitTable()[inst];
                        int leng = HextoDecimal(LenTable()[inst]);


                        string ins = symbolTable()["00" + formataddr(DecToHex(addr))];
                        Records.erase(0,leng-2);
                        int byte = leng/2;


                        if(opr.at(0) == '='){
                            outList<<"           LTORG"<<endl;
                            int foundCon = opr.find("=");

                            string lit = opr.substr(foundCon+3, leng);
                            if((addrMode[0] != '0')&& (addrMode[1] != '0')){
                                string opcode = findOpcode(Hex);
                                string opcodeHex = getMnemonic(opcode);

                                outList<< formataddr(DecToHex(addr)) + "   " + ins + "  " + inst + "  " + opcodeHex + "  " + opr + "  " + lit <<endl;
                                addr = addr + byte;

                            }

                            outList<< formataddr(DecToHex(addr)) + "   " + ins  + "  *" +"  " + opr + "  " + lit <<endl;

                            addr = addr +  byte;

                            /*if(addr == HextoDecimal("02E6")){
                                addr += curr;
                                string REvalue = InttoString(HextoDecimal(totalLen) - addr);
                                int v  = HextoDecimal(totalLen) - addr;
                                string insb2 = symbolTable()["00" + formataddr(DecToHex(addr))];
                                string insb_resb = symbolTable()["00" + formataddr(DecToHex(addr))];

                                outList << formataddr(DecToHex(addr)) + "  " + insb_resb + "    RESB   " + REvalue << endl;
                            }*/

                        }else{
                            int foundLit = opr.find("X'");
                            string oprLit  = opr.substr(foundLit+2, leng);
                            outList<<formataddr(DecToHex(addr)) + "  "  + ins + " " + "  " + inst + "   BYTE" + opr + "  " + oprLit <<endl;
                            addr = addr + byte;
                        }



                    }






                    else{
                        //get the first number(opcode)
                    string Hex = Records.substr(0,2);
                    Records.erase(0,2);
                        //find the real opcode
                    string opcode = findOpcode(Hex);
                        //get the opcode's Mnemonic
                    string opcodeHex = getMnemonic(opcode);
                        //get the number for find nixbpe
                    string opj = Hex.substr(1,1) + Records.substr(0,1);
                        //addrMode = nixbpe
                    string addrMode = operandFinder(opj);


                    //check format 2 and return
                        if(getFormat(opcode) == "2"){

                            string format2Obj = Records.substr(0,2);
                            Records.erase(0,2);
                            outList<<outputaddress + " " + instruction + " " + opcodeHex + "    A    " + Hex + format2Obj << endl;
                            addr = addr + 2;

                    }
                        //check whether is format 3 or 4
                        if(getFormat(opcode) == "3/4") {
                            //check format 4 (e = 1)
                            if (addrMode[5] == '1') {
                                string op4 = op(Hex);
                                string opr = symbolTable()["00" + Records.substr(2, 4)];
                                string format4Obj = Hex + Records.substr(0, 6);
                                Records.erase(0, 6);
                                // check for Indirect
                                if ((addrMode[0] == '1') && (addrMode[1] == '0')) {
                                    opr = "@" + opr;
                                    // check for Immediate
                                } else if ((addrMode[0] == '0') && (addrMode[1] == '1')) {
                                    opr = "#" + opr;
                                }
                                if (op4 == "LDB") {
                                    if((addrMode[0] == '1') && (addrMode[1] == '1')){
                                        BaseOprend = opr.substr(0, 6);
                                    }else{
                                        BaseOprend = opr.substr(1, 6);
                                    }

                                    outList << formataddr(DecToHex(addr)) + "    " + instruction + "  "  "+" + op4 +
                                               "    " + opr + "   " + format4Obj + '\n' + "              BASE" + " " +
                                               opr.substr(1, 6) << endl;
                                    addr = addr  + 4;


                                } else if (symbolTablelit().count("00" + formataddr(DecToHex(addr))) != 0) {
                                    outList << formataddr(DecToHex(addr)) + "    " + instruction + "  " + "+" + op4 +
                                               "    " + opr + "   " + format4Obj << endl;
                                    addr = addr + 4;
                                } else {
                                   string l =format4Obj.substr(4,format4Obj.length());
                                    string lit = symbolTablelit()["00" + l];
                                    string Lit = LitTable()[lit];

                                    outList << formataddr(DecToHex(addr)) + "    " + instruction + "  " + "+" + op4 +
                                               "    " + Lit + "   " + format4Obj << endl;
                                    addr = addr + 4;
                                }


                            } else {



                                /*if((addrMode[0] == '0')&&(addrMode[1] == '0')&&(addrMode[2] == '0')&&(addrMode[3] == '0')&&(addrMode[4] == '0')&&(addrMode[5] == '0')){
                                    Hex = Hex + Records.substr(0, 4);
                                    string LitName = symbolTablelit()["00" +formataddr(DecToHex(addr))];
                                    string Lit = LitTable()[LitName];
                                    Records.erase(0,4);
                                    outList<<"               LTORG"<<endl;
                                    outList<< outputaddress +"  " + "*" + "  " + Lit + "  " + Hex << endl;
                                    addr = addr + curr + 3;
                                    if((addr-3 < addr)&&(symbolTable()["00" +formataddr(DecToHex(addr))] != "")){
                                        outList<< formataddr(DecToHex(addr)) + "   " + symbolTable()["00" +formataddr(DecToHex(addr))] + "    RESB   700"<<endl;
                                    }
                                }else*/
                                {


                                    string inst = symbolTable()["00" + formataddr(DecToHex(addr))];
                                    string op4 = op(Hex);

                                    Hex = Hex + Records.substr(0, 4);
                                    Records.erase(0, 4);

                                    string disp = Hex.substr(3, Hex.length());
                                    string pc = DecToHex(addr + 3);
                                    // Base relative
                                    if (addrMode[3] == '1') {
                                        string str = symbolTableReverse()[BaseOprend];
                                        TA = DecToHex(HextoDecimal(disp) + HextoDecimal(str));
                                        Oprend = BaseOprend;

                                    } else {

                                            TA = DecToHex(HextoDecimal(disp) + (addr + 3));
                                            if(symbolTablelit().count("00" + formataddr(TA)) !=0){
                                                string litn = symbolTablelit()["00" + formataddr(TA)];
                                                Oprend = LitTable()[litn];
                                            }else{
                                                Oprend = symbolTable()["00" + formataddr(TA)];
                                            }



                                    }
                                    //if disp is a negative number,use two's complement to solve it
                                    //PC relative
                                    if ((Oprend == "") && (addrMode[4] == '1')) {
                                        if (symbolTablelit().count("00" + formataddr(TA)) != 0) {
                                            string lit = symbolTablelit()["00" + formataddr(TA)];
                                            Oprend = LitTable()[lit];
                                        }else{
                                            string dis = twosComp(disp);
                                            string TAd = DecToHex((addr + 3) - HextoDecimal(dis));
                                            if (symbolTablelit().count("000" + TAd) != 0) {
                                                Oprend = symbolTablelit()["00" + formataddr(TAd)];
                                            } else {
                                                Oprend = symbolTable()["00" + formataddr(TAd)];
                                            }
                                        }



                                    }
                                    // check for Indexed
                                    if (addrMode[2] == '1') {
                                        Oprend += ",X";
                                    }

                                    /* if(Oprend == ""){
                                         string LitName = symbolTablelit()["000" +TA];
                                         Oprend = LitName;
                                     }*/
                                    // check for Indirect
                                    if ((addrMode[0] == '1') && (addrMode[1] == '0')) {
                                        Oprend = "@" + Oprend;
                                        // check for Immediate
                                    } else if ((addrMode[0] == '0') && (addrMode[1] == '1')) {
                                        if (Oprend != "") {
                                            Oprend = "#" + Oprend;
                                        } else if ((addrMode[2] == '0') && (addrMode[3] == '0')&& (addrMode[4] == '0')){
                                            Oprend = "#" + disp.substr(2, 1);
                                        }else{

                                            string TAd = DecToHex((addr + 3) - HextoDecimal(disp));
                                            if (symbolTablelit().count("000" + TAd) != 0) {
                                                Oprend = symbolTablelit()["00" + formataddr(TAd)];
                                            } else {
                                                Oprend = symbolTable()["00" + formataddr(TAd)];
                                            }
                                        }

                                    }


                                    outList << formataddr(DecToHex(addr)) + " " + inst + "  " + op4 + "  " + Oprend +
                                               "  " + Hex << endl;
                                    addr = addr + 3;

                                    /*if ((symbolTable()["00" + formataddr(DecToHex(addr))] != "") &&
                                        (addr > (addr - 3)) &&(Oprend != "#5")) {

                                        string ins = symbolTable()["00" + formataddr(DecToHex(addr))];

                                        currAdd = DecToHex(HextoDecimal(disp) + addr);
                                        //
                                        //string opr = InttoString(HextoDecimal(disp));
                                        string temp = DecToHex(HextoDecimal(TA) - HextoDecimal(pc));
                                        string opr = InttoString(HextoDecimal(temp));
                                        //

                                        string insb = symbolTable()["00" + formataddr(currAdd)];
                                        outList << formataddr(DecToHex(addr)) + "  " + ins + "    RESB" + "   " + opr
                                                << endl;

                                        addr += (HextoDecimal(TA) - HextoDecimal(pc));
                                        currAdd2 = DecToHex(HextoDecimal(TA));

                                        *//*string insb2 = symbolTable()["00" + formataddr(currAdd2)];
                                        string insb_resb = symbolTable()["00" + formataddr(currAdd2)];
                                        cout << currAdd2 << endl;
                                        //
                                        outList << formataddr(currAdd2) + "  " + insb_resb + "    RESB   1" << endl;*//*

                                    }*/

                                    /*if(addr == HextoDecimal("02E6")){
                                        addr += curr;
                                        string REvalue = InttoString(HextoDecimal(totalLen) - addr);
                                        int v  = HextoDecimal(totalLen) - addr;
                                        string insb2 = symbolTable()["00" + formataddr(DecToHex(addr))];
                                        string insb_resb = symbolTable()["00" + formataddr(DecToHex(addr))];

                                        outList << formataddr(DecToHex(addr)) + "  " + insb_resb + "    RESB   " + REvalue << endl;
                                    }*/
                                }

                            }


                        }

                    }

                    //currA = &addr;
                    currAddr3 = *currA;
                    currAdr = DecToHex(addr);


                  /*  if(symbolTablelit().count("00" + formataddr(DecToHex(curr))) != 0 ) {
                        string inst = symbolTablelit()["00" + formataddr(DecToHex(curr))];
                        string opr  = LitTable()[inst];
                        string ins = symbolTable()["00" + formataddr(DecToHex(curr))];
                        int foundCon = opr.find("=");
                        int leng = HextoDecimal(LenTable()[inst]);
                        int byte = leng/2;
                        string lit = opr.substr(foundCon+3, leng);
                        outList<<"           LTORG"<<endl;
                        outList<< formataddr(DecToHex(curr)) + "   " + ins  + "  *" +"  " + opr + "  " + lit <<endl;

                        addr = addr + byte;
                        Records.erase(0,leng);
                    }*/
                   /* if(addr+3 == HextoDecimal("02E6")){

                        string REvalue = InttoString(HextoDecimal(totalLen) - addr+3);
                        int v  = HextoDecimal(totalLen) - addr+3;
                        string insb2 = symbolTable()["00" + formataddr(DecToHex(addr+3))];
                        string insb_resb = symbolTable()["00" + formataddr(DecToHex(addr+3))];

                        outList << formataddr(DecToHex(addr+3)) + "  " + insb_resb + "    RESB   " + REvalue << endl;
                    }
*/
                }




        }


//if line with "E" then print End record on file
        else if(Records.at(0) == 'E'){



            int len = 1;

            //if the last address is not equal to the total length of the Record, RESB active.
            while(HextoDecimal(currAdr) + len <= HextoDecimal(totalLen) ){

                if((symbolTable().count("00" + formataddr(DecToHex(HextoDecimal(currAdr) + len))) != 0)&&(symbolTable().count("00" + formataddr(currAdr)) != 0)){

                    string insb2 = symbolTable()["00" + formataddr(DecToHex(HextoDecimal(currAdr)))];
                    outList << formataddr(currAdr) + "  " + insb2 + "    RESB   " + InttoString(len) << endl;

                    currAdr = DecToHex(HextoDecimal(currAdr) + len);

                    len = 1;

                }else  if(HextoDecimal(currAdr) + len == HextoDecimal(totalLen)){
                    string insb2 = symbolTable()["00" + formataddr(DecToHex(HextoDecimal(currAdr)))];
                    outList << formataddr(currAdr) + "  " + insb2 + "    RESB   " + InttoString(len) << endl;
                    break;
                } else{
                    len++;
                }


                /*string REvalue = InttoString(HextoDecimal(totalLen) - HextoDecimal(currAdr));

                outList << formataddr(currAdr) + "  " + insb2 + "    RESB   " + REvalue << endl;*/
            }
            cout<<HextoDecimal(totalLen) - currAddr3<< endl;
            outList<<  + "        END " + controlSec <<endl;
        }
}

       objFile.close();


/*cout<<symbolTableReverse()["RETADR"]<<endl;
cout<<twosComp("FFA");*/
    /*if (isLit("j") ){
        cout<<"correct"<<endl;
    }else{
        cout<<"wrong"<<endl;
    }*/


        /*}else if(Records[0] = 'E'){
            Trecord = Records;
        }
*/




    }




}
