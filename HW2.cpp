// Program Name: Lab 2
//
// Description:  
//  This assignment was to encode then decode a file. 
//	Endoing took decimal values of a particular word using materials from Lab 1. 
//	A tree was used and the particular letters were encoded by if LEFT or RIGHT in the tree. 
//
// What's on your mind about this lab?
//  There was no main problem in this lab, but it did take a lot of brainstorming.
//  I had to change how I put data into the tree than the given template. 
//  I could not get what was given to work or figure it out :(
//  Using knowledge from CIS 22C - I still managed to get the encoded message out.
//  This lab was pretty enjoyable and made me think very hard.
//	I can feel myself becoming a more critical thinker.
//
// Author: Jason Yoon
//
// Date: 11/2/2018
//
// IDE Used: Visual Microsoft
//


// TEXT FILE:
//	HELLO!THIS IS FOR LAB ASSIGNMENT 2!THIS LAB WAS A LITTLE DIFFICULT, BUT I THINK I MANAGED TO FIGURE IT OUT.
//	I HAD TO USE SOME PREVIOUS KNOWLEDGE FROM CIS 22C AND DID NOT USE THE ORIGINAL TEMPLATES WE WERE GIVEN.
// OUTPUT WILL BE BELOW




#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>
#include <utility>
#include <typeinfo>
#include <iterator>
#include <sstream>
#include <unordered_map> 
using namespace std;

class ASCIItoMorseDecimal {
private:
	vector<pair<string, string>> WordstoDecimal{
	{ "999", " "},{ "9999", "." },{ "9", "A" },{ "106", "B" },{ "102", "C" },
	{ "26","D" },{ "2", "E" },{ "166","F" },{ "22","G" },{ "170","H" },
	{ "10","I" },{ "149","J" },{ "25","K" },{ "154","L" },{ "5","M" },
	{ "6","N" },{ "21","O" },{ "150","P" },{ "89","Q" },{ "38","R" },
	{ "42","S" },{ "1","T" },{ "41","U" },{ "169","V" },{ "37","W" },
	{ "105","X" },{ "101","Y" },{ "90","Z" },{ "153","Ä" },{ "86","Ö" },
	{ "165","Ü" },{ "85","Ch" },{ "341","0" },{ "597","1" },{ "661","2" },
	{ "677", "3" },{ "681", "4" },{ "682","5" },{ "426","6" },{ "362","7" },
	{ "346","8" },{ "342","9" },{ "2457","10" },{ "1445","," },{ "2650","?" },
	{ "662","!" },{ "1386",":" },{ "2470","\"" },{ "2390","\'" },{ "425","=" }
	};

public:
	ASCIItoMorseDecimal() {};
	vector<pair<string, string>> convertToDecimal(vector<string> toBeConverted);
};



class FileIO {
private:
	unsigned char* memblock;
	int size;
public:
	FileIO() {};
	vector<char> readFile(string FILE_NAME);
	vector<string> vectorizeFile(vector<char> filereader);
	void setSize(int size) { this->size = size; }
	int getSize() { return size; }

};

template <class T>
class TreeNode {
public:
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
	bool branch = false;
	bool visited = false;
	int code = 0;
	TreeNode() {};
	TreeNode(T input) {
		data = input;
		left = NULL;
		right = NULL;
	};
};

class mapNode {
public:
	string data;
	bool visited;
	void setData(string data) { this->data = data; };
	string getData() { return data; }
	void setVisited(bool trigger) { visited = trigger; };
	bool getVisited() { return visited; };
	mapNode() {};
	mapNode(string data) {
		this->data = data;
		visited = false;
	}
};


class EncryptwithTree {
	private:
		priority_queue <pair<int,string>> morseDecimals;
		TreeNode<pair<int, string >>* top;
		unordered_map<string, mapNode> umap;
		vector<string> key;
	public:
		void makeQueue(vector<pair<string, string>> morseDecimals);
		TreeNode<pair<int, string>>* priorityQueueTree();
		void encode(TreeNode<pair<int, string >>* top, string encodedString);
		vector<pair<string, string>> retrieveEncodedMessage(vector<pair<string, string>> pairContainer);

};



int main() {
	FileIO fileObj;
	ASCIItoMorseDecimal morseDecimal; // example
	vector<string> decimalContainer;
	vector<pair<string, string>> pairContainer;
	vector<char> filereader;
	EncryptwithTree treeOperations;
	TreeNode<pair<int, string >>* top;


	filereader = fileObj.readFile("Lab2File.txt");
	decimalContainer = fileObj.vectorizeFile(filereader); // Here the vector will just be made
	pairContainer = morseDecimal.convertToDecimal(decimalContainer); // vector is then converted here
	cout <<endl;

	treeOperations.makeQueue(pairContainer);
	top = treeOperations.priorityQueueTree();
	treeOperations.encode(top, "");
	pairContainer = treeOperations.retrieveEncodedMessage(pairContainer);

	//cout << "Encrypted Message:\n";
	//for (auto index : pairContainer)
	//	cout << index.first << " ";
	
	cout << "\n\nPrinting Original Message: ";
	for (auto index : pairContainer)
		cout << index.second;


	cin.get();
	return 0; 
}

vector<pair<string, string>>EncryptwithTree::retrieveEncodedMessage(vector<pair<string, string>> pairContainer) {
	unordered_map<string, mapNode>::iterator map_index;
	for (int index = 0; index < pairContainer.size(); index++) {

		for (map_index = umap.begin(); map_index != umap.end(); map_index++) {
			if (map_index->second.getData() == pairContainer[index].second) {
				pairContainer[index].first.replace(pairContainer[index].first.begin(), pairContainer[index].first.end(), map_index->first);
			}

		}
	}

	//for (auto i : umap)
	//	cout << i.first << " " << i.second.getData() << endl;

	return pairContainer;
}



void EncryptwithTree::encode(TreeNode<pair<int, string >>* top, string encodedString) {
	vector<pair<string, string>> newPairContainer;

	if (top == nullptr) {
		return;
	}

	if (top->branch == true) {
		encode(top->left, encodedString += "0");
		encode(top->right, encodedString += "1");
	}

	if (top->branch == false) { // key has to be encoded string for duplicates
		umap[encodedString] = mapNode(top->data.second);
	}
}

TreeNode<pair<int, string>>* EncryptwithTree::priorityQueueTree() {
	int left, right, branchReference = 0;
	TreeNode<pair<int, string>>* Leftnode = new TreeNode<pair<int, string>>;
	TreeNode<pair<int, string>>* Rightnode = new TreeNode<pair<int, string>>;
	TreeNode<pair<int, string>>* Branch = new TreeNode<pair<int, string>>;


	Leftnode->data = morseDecimals.top();
	left = morseDecimals.top().first;
	morseDecimals.pop();
	Rightnode->data = morseDecimals.top();
	right = morseDecimals.top().first;
	morseDecimals.pop();

	Branch->branch = true;
	Branch->left = Leftnode;
	Branch->right = Rightnode;
	branchReference = left + right;

	while (morseDecimals.size() > 1) {
		if (branchReference > morseDecimals.top().first) { // have to make new branch
			TreeNode<pair<int, string>>* newBranch = new TreeNode<pair<int, string>>;
			TreeNode<pair<int, string>>* Leftnode = new TreeNode<pair<int, string>>;
			newBranch->branch = true;
			Leftnode->data = morseDecimals.top();
			newBranch->left = Leftnode;
			left = morseDecimals.top().first;
			branchReference = left + branchReference;
			newBranch->right = Branch;
			morseDecimals.pop();
			Branch = newBranch;
		}

		if (branchReference < morseDecimals.top().first) { // have to make new branch
			TreeNode<pair<int, string>>* newBranch = new TreeNode<pair<int, string>>;
			TreeNode<pair<int, string>>* Rightnode = new TreeNode<pair<int, string>>;
			newBranch->branch = true;
			Rightnode->data = morseDecimals.top();
			newBranch->right = Rightnode;
			right = morseDecimals.top().first;
			branchReference = right + branchReference;
			newBranch->left = Branch;
			morseDecimals.pop();
			Branch = newBranch;
		}
	}

	// these operations to branch out the last node in queue
	TreeNode<pair<int, string>>* TopNode = new TreeNode<pair<int, string>>;
	TreeNode<pair<int, string>>* newBranch = new TreeNode<pair<int, string>>;
	TopNode->data = morseDecimals.top();
	if (branchReference > morseDecimals.top().first) {
		newBranch->branch = true;
		newBranch->left = TopNode;
		left = morseDecimals.top().first;
		branchReference = left + branchReference;
		newBranch->right = Branch;
	}
	if (branchReference < morseDecimals.top().first) {
		newBranch->branch = true;
		newBranch->right = TopNode;
		right = morseDecimals.top().first;
		branchReference = right + branchReference;
		newBranch->left = Branch;
	}

	morseDecimals.pop();
	top = newBranch;
	return top;
}

void EncryptwithTree::makeQueue(vector<pair<string, string>> decimals) {
	vector<pair<int,string>> stringToIntConverstions;
	for (int index = 0; index < decimals.size(); index++) {
		stringToIntConverstions.push_back(make_pair((stoi(decimals[index].first)),decimals[index].second)); // convert to int from string
	}

	for (int index = 0; index < decimals.size(); index++) {
		morseDecimals.push(stringToIntConverstions[index]); // make queue here saving the pair
	}

}

vector<pair<string, string>> ASCIItoMorseDecimal::convertToDecimal(vector<string> toBeConverted) { // testing here
	bool found = false;
	vector<pair<string,string>> convertedStrings;

	for (int index = 0; index < toBeConverted.size(); index++) {
		for (int vectorIndex = 0; vectorIndex < WordstoDecimal.size() && found == false; vectorIndex++) {
			if (toBeConverted[index] == WordstoDecimal[vectorIndex].second) {
				convertedStrings.push_back(WordstoDecimal[vectorIndex]);
				found = true;
			}

		}
		found = false;
	}

	return convertedStrings;
}

vector<char> FileIO::readFile(string FILE_NAME) { // reads the file


	ifstream file(FILE_NAME);
	ostringstream ss;
	ss << file.rdbuf();
	const string& s = ss.str();
	vector<char> vec(s.begin(), s.end());
	cout << "Original Message: ";
	copy(vec.begin(), vec.end(), ostream_iterator<char>(cout));
	cout << endl;
	return vec;

}

vector<string> FileIO::vectorizeFile(vector<char> filereader) {

	vector<string> vectorizedFile;

	for (int index = 0; index < filereader.size(); index++) {
		string changeCharToString(1, filereader[index]); // to string
		vectorizedFile.push_back(changeCharToString);
	}
	return vectorizedFile;
}

// OUTPUT MANIPULATED TO SAVE SPACE - inserted newline in messages
//Original Message : HELLO!THIS IS FOR LAB ASSIGNMENT 2!THIS LAB WAS A LITTLE DIFFICULT, BUT I THINK I MANAGED TO FIGURE IT OUT.
//					 I HAD TO USE SOME PREVIOUS KNOWLEDGE FROM CIS 22C AND DID NOT USE THE ORIGINAL TEMPLATES WE WERE GIVEN.
//
//Encrypted Message : ... taken out because it was too long
//
//Printing Original Message : HELLO!THIS IS FOR LAB ASSIGNMENT 2!THIS LAB WAS A LITTLE DIFFICULT, BUT I THINK I MANAGED TO FIGURE IT OUT.
//							  I HAD TO USE SOME PREVIOUS KNOWLEDGE FROM CIS 22C AND DID NOT USE THE ORIGINAL TEMPLATES WE WERE GIVEN.