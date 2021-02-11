/* Demo server program for Bible lookup using AJAX/CGI interface
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, January 2020
 * Mount Vernon Nazarene University
 * 
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching 
 * field name, and returing a "form_iterator" oject, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 *     refers to the actual string entered in the form's "verse" field.
 */
 
#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"
using namespace cgicc;

int main() {
  /* A CGI program must send a response header with content type
   * back to the web client before any other output.
   * For an AJAX request, our response is not a complete HTML document,
   * so the response type is just plain text to insert into the web page.
   */
  cout << "Content-Type: text/plain\n\n";
  
  Cgicc cgi;  // create object used to access CGI request data

  // GET THE INPUT DATA
  // browser sends us a string of field name/value pairs from HTML form
  // retrieve the value for each appropriate field name
  form_iterator st = cgi.getElement("search_type");
  form_iterator book = cgi.getElement("book");
  form_iterator chapter = cgi.getElement("chapter");
  form_iterator verses = cgi.getElement("verse");
  form_iterator nv = cgi.getElement("num_verse");

	
  // Convert and check input data
  Bible webBible("/home/class/csc3004/Bibles/web-complete");
  Verse verse;
  int chapterNum;
  int verseNum;
  int bookNum;
  LookupResult result;
  bool validInput = false;
  if (chapter != cgi.getElements().end()) {
	 chapterNum = chapter->getIntegerValue();
	 if (chapterNum > 150) {
		 cout << "<p>The chapter number (" << chapterNum << ") is too high.</p>" << endl;
	 }
	 else if (chapterNum <= 0) {
		 cout << "<p>The chapter must be a positive number.</p>" << endl;
	 }
	 else
		 validInput = true;
  }
  
  /* TO DO: OTHER INPUT VALUE CHECKS ARE NEEDED ... but that's up to you! */
  
  if(verses != cgi.getElements().end()){
	  verseNum = verses->getIntegerValue();
	  if(verseNum <= 0){
		  cout << "<p>The Verse number must be greater than or equal to 1." << "</p>" << endl;
	  }
	  else{
		  validInput = true;
	  }
  }
  
  if(book != cgi.getElements().end()){
	  bookNum = book->getIntegerValue();
	  if((bookNum < 1)||(bookNum > 66)){
		  cout<< "Book number must be between 1 and 66" << endl;
	  }
	  else{
		validInput = true;
	  }
  }
  
  

   /* TO DO: PUT CODE HERE TO CALL YOUR BIBLE CLASS FUNCTIONS
   *        TO LOOK UP THE REQUESTED VERSES
   */
	int verseCount = nv->getIntegerValue();
	cout << "Search Type: <b>" << **st << "</b>" << endl;
	for(int x = 0; x < verseCount; x++){
		Ref ref(bookNum, chapterNum, verseNum);
		// Create a reference from the numbers
		
		// Use the Bible object to retrieve the verse by reference
		//cout << "Looking up reference: ";
		//ref.display();
		//cout << endl;

		verse = webBible.lookup(ref, result);

		if(result == NO_VERSE){
			if( x == 0){
					//cout << endl  "Result status: No Verse" << result << endl;
					break;
				}
			chapterNum++;
			verseNum = 1;
			result = OTHER;
			Ref newRef (bookNum, chapterNum, verseNum);
			
			//cout<< "Looking up reference: ";
			//newRef.display();
			cout<< endl;
			
			verse = webBible.lookup(newRef, result);
		}
		
		
		else if(result == NO_CHAPTER){
			if( x == 0){
				cout << endl << "Result status: No Chapter." << endl;
				break;
			}
			bookNum++;
			chapterNum = 1;
			verseNum = 1;
			result = OTHER;
			Ref newRef (bookNum, chapterNum, verseNum);
			verse = webBible.lookup(ref, result);
		}
		
		if (validInput) {
			cout << "<p>Your result: "
			<< **book << " " << **chapter << ":" << **verses 
			//<< "<em> The " << **nv
			<< "  " << verse.getVerse() << endl; //or verse.display();
			}		
		else {
			cout << "<p>Invalid Input: <em>report the more specific problem.</em></p>" << endl;
		}
		
		//verse.display();
		verseNum++;
		cout << endl;
	}
   
   //Ref newRef(bookNum,chapNum,verseNum);
   
   //lookup(newRef);
   
  /* SEND BACK THE RESULTS
   * Finally we send the result back to the client on the standard output stream
   * in HTML text format.
   * This string will be inserted as is inside a container on the web page, 
   * so we must include HTML formatting commands to make things look presentable!
   */
   /*
  if (validInput) {
	cout << "Search Type: <b>" << **st << "</b>" << endl;
	cout << "<p>Your result: "
		 << **book << " " << **chapter << ":" << **verses 
		 //<< "<em> The " << **nv
		 << "  " << verse.getVerse() << endl; //or verse.display();
  }		
  else {
	  cout << "<p>Invalid Input: <em>report the more specific problem.</em></p>" << endl;
  }
  return 0;
  */
}