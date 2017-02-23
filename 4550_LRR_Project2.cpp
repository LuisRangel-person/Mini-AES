//Luis Rangel(luisrngl5@gmail.com or LuisRangel@my.unt.edu)
//November 29,2016
//CSCE 4550-Project 2 Mini-AES Encryption
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

//strPreprocessing
//This function will take care of the preprocessing of the input string
//Param: a-The string that needs preprocessing
void strPreprocessing(string &a);
void strPreprocessing(string &a){
	//Removing Spaces using remove-erase idiom
	//Removing Whitespace
	a.erase(remove( a.begin(), a.end(), ' '), a.end());
	//Removing Punctuation
	a.erase(remove( a.begin(), a.end(), '!'), a.end());
	a.erase(remove( a.begin(), a.end(), '.'), a.end());
	a.erase(remove( a.begin(), a.end(), ','), a.end());
	a.erase(remove( a.begin(), a.end(), '?'), a.end());
	a.erase(remove( a.begin(), a.end(), '"'), a.end());
	a.erase(remove( a.begin(), a.end(), ':'), a.end());
	a.erase(remove( a.begin(), a.end(), ';'), a.end());
	a.erase(remove( a.begin(), a.end(), '('), a.end());
	a.erase(remove( a.begin(), a.end(), ')'), a.end());
	a.erase(remove( a.begin(), a.end(), '*'), a.end());
	a.erase(remove( a.begin(), a.end(), '{'), a.end());
	a.erase(remove( a.begin(), a.end(), '}'), a.end());
	a.erase(remove( a.begin(), a.end(), '-'), a.end());
	a.erase(remove( a.begin(), a.end(), '_'), a.end());
	a.erase(remove( a.begin(), a.end(), '$'), a.end());
	a.erase(remove( a.begin(), a.end(), '&'), a.end());
	a.erase(remove( a.begin(), a.end(), '#'), a.end());
	a.erase(remove( a.begin(), a.end(), '@'), a.end());
	a.erase(remove( a.begin(), a.end(), '^'), a.end());
	a.erase(remove( a.begin(), a.end(), '+'), a.end());
	a.erase(remove( a.begin(), a.end(), '='), a.end());
	a.erase(remove( a.begin(), a.end(), '['), a.end());
	a.erase(remove( a.begin(), a.end(), ']'), a.end());
	a.erase(remove( a.begin(), a.end(), '/'), a.end());
	a.erase(remove( a.begin(), a.end(), '\''), a.end());
}//strPreprocesing

//encryptSubs
//Uses the Vigenere cipher to sub the letters
//Param: b-The string to encrypt
//Param: k-The Key for the encryption
void encryptSubs(string &b, string k);
void encryptSubs(string &b, string k){
	vector<int> vig;//Vector to hold key values
	int temp, y;
	for(int i = 0; i < k.length();i++){
		temp = ((int) k[i]) - 65;//Gets the number of the char and its corresponding letter number
		vig.push_back(temp);//Adds the key value to the vector
	}//key loop
	y = 0;//This is an iterator for the key array
	for(int j = 0; j < b.length(); j++){
		temp = ((int) b[j]);//Makes the char into an int
		temp += vig[y];//Adds the offset based off the key array
		if(temp > 90){//Makes it so it loops back after it passes Z
			temp -= 26;
		}//Past Z
		b[j] = (char) temp;//Turns the int back into a char
		if(y == k.length() - 1){
			y = 0;
		}//if key length
		else{
			y++;
		}//Else, increment y
	}//text loop
}//encryptSubs

//strPad
//This function will pad the str so it can make 4x4 blocks
//Param - c-The str to be padded
void padStr(string &c);
void padStr(string &c){
	int padsi;//Pad size
	for(int u = 0; u < c.length(); u++){
		if(((u % 4) == 0) && u != 0){//Makes rows
			cout << endl;
		}//%4
		if(((u % 16) == 0) && u != 0){//Makes blocks
			cout << endl;
		}//%16
		cout << c[u];//Heh, c u
	}//u loop
	padsi = (16 - (c.length() % 16));
	for(int q = 0; q < padsi; q++){
		c = c + 'A';//Add A's for padding!
	}//filling loop
}//padStr

//shiftRows
//Shift the rows on the blocks
//Param - c, The String to be shifted
void shiftRows(string &c);
void shiftRows(string &c){
	char sh1, sh2, sh3;
	for(int r = 0; r < (c.length() / 16); r++){//Go though the blocks
		//First Row Ignored
		//c[(16 * r) + (0 * 4) + (0,1,2,3)];
		//Second Row, I shift 1 back
		sh1 = c[(16 * r) + (4)];
		c[(16 * r) + (4)] = c[(16 * r) + (4) + (1)];
		c[(16 * r) + (4) + (1)] = c[(16 * r) + (4) + (2)];
		c[(16 * r) + (4) + (2)] = c[(16 * r) + (4) + (3)];
		c[(16 * r) + (4) + (3)] = sh1;
		//Third Row, I Shift 2 back
		sh1 = c[(16 * r) + (4 * 2)];
		sh2 = c[(16 * r) + (4 * 2) + (1)];
		c[(16 * r) + (4 * 2)] = c[(16 * r) + (4 * 2) + (2)];
		c[(16 * r) + (4 * 2) + (1)] = c[(16 * r) + (4 * 2) + (3)];
		c[(16 * r) + (4 * 2) + (2)] = sh1;
		c[(16 * r) + (4 * 2) + (3)] = sh2;
		//Fourth Row, I shift 3 back
		sh1 = c[(16 * r) + (4 * 3)];
		sh2 = c[(16 * r) + (4 * 3) + (1)];
		sh3 = c[(16 * r) + (4 * 3) + (2)];
		c[(16 * r) + (4 * 3)] = c[(16 * r) + (4 * 3) + (3)];
		c[(16 * r) + (4 * 3) + (1)] = sh1;
		c[(16 * r) + (4 * 3) + (2)] = sh2;
		c[(16 * r) + (4 * 3) + (3)] = sh3;
	}//for
}//ShiftRows

//intToBin
//Turns ints into binary strings
//Param- n-Int to be turned into 8 bit binary
string intToBin(int n);
string intToBin(int n){
	int temp = n;
	string b;
	 b = "";
	if(temp >= 128){//8th Bit
		temp -= 128;
		b += '1';
	}
	else{
		b += '0';
	}
	if(temp >= 64){//7th Bit
		temp -= 64;
		b += '1';
	}
	else{
		b += '0';
	}
	if(temp >= 32){//6th Bit
		temp -= 32;
		b += '1';
	}
	else{
		b += '0';
	}
	if(temp >= 16){//5th Bit
		temp -= 16;
		b += '1';
	}
	else{
		b += '0';
	}
	if(temp >= 8){//4th Bit
		temp -= 8;
		b += '1';
	}
	else{
		b += '0';
	}
	if(temp >= 4){//3rd Bit
		temp -= 4;
		b += '1';
	}
	else{
		b += '0';
	}
	if(temp >= 2){//2nd Bit
		temp -= 2;
		b += '1';
	}
	else{
		b += '0';
	}
	if(temp >= 1){//1st Bit
		temp -= 1;
		b += '1';
	}
	else{
		b += '0';
	}
	return b;//Return binary string
}//intToBin

//bitdrop
//Turns bit binary to Hex
//Param - f
char bitDrop(string f);
char bitDrop(string f){
	char temph;
	if(f == "0000"){
		temph = '0';
	}//0
	if(f == "0001"){
		temph = '1';
	}//1
	if(f == "0010"){
		temph = '2';
	}//2
	if(f == "0011"){
		temph = '3';
	}//3
	if(f == "0100"){
		temph = '4';
	}//4
	if(f == "0101"){
		temph = '5';
	}//5
	if(f == "0110"){
		temph = '6';
	}//6
	if(f == "0111"){
		temph = '7';
	}//7
	if(f == "1000"){
		temph = '8';
	}//8
	if(f == "1001"){
		temph = '9';
	}//9
	if(f == "1010"){
		temph = 'a';
	}//a 10
	if(f == "1011"){
		temph = 'b';
	}//b 11
	if(f == "1100"){
		temph = 'c';
	}//c 12
	if(f == "1101"){
		temph = 'd';
	}//d 13
	if(f == "1110"){
		temph = 'e';
	}//e 14
	if(f == "1111"){
		temph = 'f';
	}//f 15
	return temph;
}//bitdrop
//binToHex
//Turns bins into hex
//Param - b-Binary string to hexidecimal
string binToHex(string b);
string binToHex(string b){
	string bit1, bit2, hex;
	bit1 = "";
	bit2 = "";
	hex = "";
	bit1 += b[0];
	bit1 += b[1];
	bit1 += b[2];
	bit1 += b[3];
	bit2 += b[4];
	bit2 += b[5];
	bit2 += b[6];
	bit2 += b[7];
	hex += bitDrop(bit1);
	hex += bitDrop(bit2);
	return hex;
}//binToHex

//Hextoint
//Turns the hexidecimal into an int
//Param-String a, string to be turned into an int
int hexToInt(string a);
int hexToInt(string a){
	int sum = 0;
	switch(a[0]){
		case '0':
			sum += 0;
			break;
		case '1':
			sum += 16;
			break;
		case '2':
			sum += 32;
			break;
		case '3':
			sum += 48;
			break;
		case '4':
			sum += 64;
			break;
		case '5':
			sum += 80;
			break;
		case '6':
			sum += 96;
			break;
		case '7':
			sum += 112;
			break;
		case '8':
			sum += 128;
			break;
		case '9':
			sum += 144;
			break;
		case 'a'://10
			sum += 160;
			break;
		case 'b'://11
			sum += 176;
			break;
		case 'c'://12
			sum += 192;
			break;
		case 'd'://13
			sum += 208;
			break;
		case 'e'://14
			sum += 224;
			break;
		case 'f'://15
			sum += 240;
			break;
		default:
			break;
	}//switch
	switch(a[1]){
		case '0':
			sum += 0;
			break;
		case '1':
			sum += 1;
			break;
		case '2':
			sum += 2;
			break;
		case '3':
			sum += 3;
			break;
		case '4':
			sum += 4;
			break;
		case '5':
			sum += 5;
			break;
		case '6':
			sum += 6;
			break;
		case '7':
			sum += 7;
			break;
		case '8':
			sum += 8;
			break;
		case '9':
			sum += 9;
			break;
		case 'a'://10
			sum += 10;
			break;
		case 'b'://11
			sum += 11;
			break;
		case 'c'://12
			sum += 12;
			break;
		case 'd'://13
			sum += 13;
			break;
		case 'e'://14
			sum += 14;
			break;
		case 'f'://15
			sum += 15;
			break;
		default:
			break;
	}//switch
	return sum;
}//hexToInt

//parityParty
//This function will see if a binary string needs a parity bit and adds it if need be
//Param -t string to be paritied
string parityParty(string t){
	int count = 0;//Counts bits
	string bins, convert, temp;
	convert = "";
	for(int x = 0; x < t.length(); x++){
		count = 0;
		bins = intToBin((int)t[x]);
		for(int s = 0; s < bins.length(); s++){
			if(bins[s] == '1'){
			count++;
			}//if
		}//s loop
		if((count % 2) != 0){
			bins[0] = '1';//Sets most significant bit to 1
		}//odd count
		temp = binToHex(bins);
		convert += temp;
	}//x loop
	return convert;
}//parityParty

//rgfMul
//This does the Rijnael's Galois Field
//Param-int x, number to be mixed, y, value of multiplication
int rgfMul(int x, int y);
int rgfMul(int x, int y){
	string bin, hex;
	int temp = 0;
	temp = x;
	bin = intToBin(x);
	if(y == 2){
		temp = x << 1;//Multiplication 
		if(bin[0] == '1'){
			temp -= 256;//Normalize
			temp = temp ^ 27;//XOR with 27
		}
	}//Value 2
	if(y == 3){
		temp = x << 1;//Mult by 2
		temp = temp ^ x;//XOR with x
		if(bin[0] == '1'){
			temp -= 256;//Normalize
			temp = temp ^ 27;//XOR with 27
		}
	}//Value 3
	//bin = intToBin(temp);
	//hex = binToHex(bin);
	return temp;
}//rgfMul

//mixCol
//This performs the mix colmuns part of the project
//Param, string n, string to be mixed
string mixCol(string n);
string mixCol(string n){
	string neo = n;
	string c0, c1, c2, c3, d0, d1, d2, d3;
	int i0, i1, i2, i3, a0, a1, a2, a3;
	c0 = "";
	c1 = "";
	c2 = "";
	c3 = "";
	for(int e = 0; e < (n.length() / 32); e++){//For each Column
		for(int r = 0; r < 8; r++){
			c0 += n[(e * 32) + r];
			c0 += n[(e * 32) + r + 1];
			c1 += n[(e * 32) + (r + 8)];
			c1 += n[(e * 32) + (r + 9)];
			c2 += n[(e * 32) + (r + 16)];
			c2 += n[(e * 32) + (r + 17)];
			c3 += n[(e * 32) + (r + 24)];
			c3 += n[(e * 32) + (r + 25)];
			i0 = hexToInt(c0);
			i1 = hexToInt(c1);
			i2 = hexToInt(c2);
			i3 = hexToInt(c3);
			a0 = rgfMul(i0, 2) ^  rgfMul(i1, 3) ^ i2 ^ i3;
			a1 = i0 ^ rgfMul(i1, 2) ^ rgfMul(i2, 3) ^ i3;
			a2 = i0 ^ i1 ^ rgfMul(i2, 2) ^ rgfMul(i3, 3);
			a3 = rgfMul(i0, 3) ^ i1 ^ i2 ^ rgfMul(i3, 2);
			d0 = binToHex(intToBin(a0));
			d1 = binToHex(intToBin(a1));
			d2 = binToHex(intToBin(a2));
			d3 = binToHex(intToBin(a3));
			//Inserting new chars
			neo[(e * 32) + r] = d0[0];
			neo[(e * 32) + r + 1] = d0[1];
			neo[(e * 32) + (r + 8)] = d1[0];
			neo[(e * 32) + (r + 9)] = d1[1];
			neo[(e * 32) + (r + 16)] = d2[0];
			neo[(e * 32) + (r + 17)] = d2[1];
			neo[(e * 32) + (r + 24)] = d3[0];
			neo[(e * 32) + (r + 25)] = d3[1];
			c0 = "";
			c1 = "";
			c2 = "";
			c3 = "";
			r++;
		}
	}//for
	return neo;
}//mixCol

int main(){
	string intext, inlin, inkey;//Strings to hold the input text, key and input line
		string ftext, fkey, fout;
		cout << "Enter the name of the plaintext file: ";
		cin >> ftext;
		cout << endl;
		cout << "Enter the name of the key file: ";
		cin >> fkey;
		cout << endl;
		cout << "Enter the name of the output file: ";
		cin >> fout;
		cout << endl;
		cout << "\nPrinting:" << ftext << " " << fkey << endl;
		string parbit;//Parity bited string
		ifstream text, key;
		text.open(ftext.c_str());//An ifstream for text
		key.open(fkey.c_str());//An ifstream for key
		ofstream ofile;
		ofile.open(fout.c_str());//Opens output file and deletes anything that was there already
		intext = "";//Empty string
		inkey = "";//Empty String
		if(text.is_open() && key.is_open()){//If both files are open
			while(getline(text, inlin)){
				intext = intext + inlin;
			}//while, line input for text
			while(getline(key, inlin)){
				inkey = inkey + inlin;
			}//while, line input for the key
			cout << "\nInput Text:\n" << intext << endl;
			cout << "\nInput Key:\n" << inkey << endl;
			ofile << "\nInput Text:\n" << intext << endl;//Output to file
			ofile << "\nInput Key:\n" << inkey << endl;
			//Preprocessing!
			cout << "**Beginning Preprocessing!**" << endl;
			ofile << "**Beginning Preprocessing!**" << endl;
			strPreprocessing(intext);
			cout << "\nProcessed Input:\n" << intext << endl;
			ofile << "\nProcessed Input:\n" << intext << endl;
			cout << "\n**Performing Substitution Cipher**" << endl;
			ofile << "\n**Performing Substitution Cipher**" << endl;
			encryptSubs(intext, inkey);
			cout << "\nSubstituted Text:\n" << intext << endl;
			ofile << "\nSubstituted Text:\n" << intext << endl;
			cout << "\n**Padding Text**\n" << endl;
			ofile << "\n**Padding Text**\n" << endl;
			padStr(intext);//Padding string
			cout << "\nPadded Text:\n" << endl;
			ofile << "\nPadded Text:\n" << endl;
			for(int w = 0; w < intext.length(); w++){
				if(((w % 4) == 0) && w != 0){//Makes rows
					cout << endl;
					ofile << endl;
				}//%4
				if(((w % 16) == 0) && w != 0){//Makes blocks
					cout << endl;
					ofile << endl;
				}//%16
				cout << intext[w];//Heh, c u
				ofile << intext[w];//Heh, c u
			}//w loop
			cout << "\n**Shifting Text**\n" << endl;
			ofile << "\n**Shifting Text**\n" << endl;
			shiftRows(intext);//Padding string
			cout << "\nShifted Text:\n" << endl;
			ofile << "\nShifted Text:\n" << endl;
			for(int z = 0; z < intext.length(); z++){
				if(((z % 4) == 0) && z != 0){//Makes rows
					cout << endl;
					ofile << endl;
				}//%4
				if(((z % 16) == 0) && z != 0){//Makes blocks
					cout << endl;
					ofile << endl;
				}//%16
				cout << intext[z];//Heh, c u
				ofile << intext[z];//Heh, c u
			}//z loop
			cout << endl;
			ofile << endl;
			cout << "\nParity Bit:\n" << endl;
			ofile << "\nParity Bit:\n" << endl;
			parbit = parityParty(intext);
			for(int b = 0; b < parbit.length(); b++){
				if(((b % 2) == 0) && b != 0){//Makes rows
					cout << " ";
					ofile << " ";
				}//%2
				if(((b % 8) == 0) && b != 0){//Makes rows
					cout << endl;
					ofile << endl;
				}//%8
				if(((b % 32) == 0) && b != 0){//Makes blocks
					cout << endl;
					ofile << endl;
				}//%32
				cout << parbit[b];//Heh, c u
				ofile << parbit[b];//Heh, c u
			}//b loop
			cout << endl;
			ofile << endl;
			string lop;
			lop = mixCol(parbit);
			cout << "\nColumn Mixing:\n" << endl;
			ofile << "\nColumn Mixing:\n" << endl;
			for(int h = 0; h < lop.length(); h++){
				if(((h % 2) == 0) && h != 0){//Makes rows
					cout << " ";
				ofile << " ";
				}//%2
				if(((h % 8) == 0) && h != 0){//Makes rows
					cout << endl;
					ofile << endl;
				}//%4
				if(((h % 32) == 0) && h != 0){//Makes blocks
					cout << endl;
					ofile << endl;
				}//%16
				cout << lop[h];//Heh, c u
				ofile << lop[h];//Heh, c u
			}//z loop
			cout << endl;
			ofile << endl;
			cout << "\nThank you and have a nice day! " << endl;
			ofile << "\nThank you and have a nice day! "<< endl;
			ofile.close();//Closing output file
		}//if both files are open
	return 0;
}//Main