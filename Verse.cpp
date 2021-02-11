// Verse class function definitions
// Computer Science, MVNU

#include "Verse.h"
#include <iostream>
using namespace std;

Verse::Verse() {  	// Default constructor
    verseText = "Uninitialized Verse!";
    verseRef = Ref();
} 

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s) {
	string localS = s;
	int book, chap, verse;
	
	string tempBook = GetNextToken(localS,":");
	string tempChap = GetNextToken(localS,":");
	string tempVerse = GetNextToken(localS," ");
	
	book = atoi(tempBook.c_str());
	chap = atoi(tempChap.c_str());
	verse = atoi(tempVerse.c_str());
	
	if(book <1 || chap < 1 || verse < 1){
		book = 0;
		chap = 0;
		verse = 0;
	}
	
	// use Ref constructor to create verseRef
	verseRef = Ref(book, chap,verse);
	
	// store the remainder of the string in verseText
	verseText = localS;
}  	

// REQUIRED: Accessors
string Verse::getVerse() {
	return verseText;
}

Ref Verse::getRef() {
	return verseRef;
}

// display reference and verse
void Verse::display() {
	cout << verseText << endl;
	/* Just the start of rhe display function */
 }
