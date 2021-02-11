// Bible class function definitions
// Computer Science, MVNU

#include "Ref.h"
#include "Verse.h"
#include "Bible.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Bible::Bible() { // Default constructor
	infile = "/home/class/csc3004/Bibles/web-complete";
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; }

// REQUIRED: lookup finds a given verse in this Bible
const Verse Bible::lookup(Ref ref, LookupResult& status) { 
    // TODO: scan the file to retrieve the line with ref ...
	
	/*   
	Use a loop
	Fail condition: fails if it hits the end of the Bible  
	*/
	
	/*What I did:
	used the loop from "display_book" to scan the Bible file and once it finds the right 
	book, chapter, and verse It calls the Ref parse constructor.
	Removed "int requestedBook" from input.
	Added another 2 loops checking for the right chapter and verse.
	took out:
	display the verse (if we got one) 
	display_verse(buffer);
	
	
	*/
    ifstream instream;
	instream.open(infile.c_str(), ios::in);
		
	int requestedBook = ref.getBook();
	int requestedChap = ref.getChap();
	int requestedVerse = ref.getVerse();
	
	string finalString = "";
	
    string buffer, verseText;
    int book, chap, verse;

    /* read in every verse */
    do {
        /* get the next verse */
        getline(instream, buffer);
		
		//cout<< buffer << endl;  
		
		if(instream.fail()==true){
			status = OTHER;
			Verse verse;
			return verse;
		}
		
		Ref ref2 (buffer);
		book = ref2.getBook();
		
        /* See if it is the right book, chapter, and verse */
        if (ref == ref2) {
					
			/* create and return the verse object */
			Verse theVerse(buffer);
			status = SUCCESS;
			return (theVerse);			
        }
		
		/*Add else statements for if the chapter or verse do not exist.*/
		
		//If the verse does not exist:
		
		else if ((ref2.getBook() == requestedBook)&&(requestedChap < ref2.getChap())){
			status = NO_VERSE;
			cout<< "Issue: no verse. Moving to next chapter." << endl <<endl;
			Verse v;
			return (v);
		}
		
		
		//If the chapter does not exist:
		
		else if (requestedBook < ref2.getBook()){
			status = NO_CHAPTER;
			cout<< "Issue: no chapter. Moving to next book." << endl;
			Verse v;
			return (v);
		}
		
		
    } while (requestedBook >= book && !instream.fail());
	
    // update the status variable
	status = NO_BOOK; // placeholder until retrieval is attempted
	Verse v;
    return(v);
}

// REQUIRED: Return the reference after the given ref
const Ref next(const Ref ref, LookupResult& status) {
	//use lookup function, and based on that status, adjust.
	/*string buffer;
	getline(instream, buffer);
	
	if(status == NO_VERSE){
		status == SUCCESS;
	}
	
	else if(status == NO_CHAPTER){
		
	}
	return next;*/	
};

// OPTIONAL: Return the reference before the given ref
const Ref prev(const Ref ref, LookupResult& status) {
	/*
	int prevVerse = ref.getVerse()--;
	int sameBook = ref.getBook();
	int sameChap = ref.getChap();
	
	Ref prev(sameBook,sameChap,prevVerse);
	return prev;
	*/
};

// Return an error message string to describe status
const string Bible::error(LookupResult status) {
	cout << "Error finding Verse. Status: " << status << "/n";
};

void Bible::display() {
	cout << "Bible file: " << infile << endl;
}
