/* 

	Final project for Programming Techniques 20/21-S2
	-----<By Ricardo Macías and Carlos Carmona>----

*/
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <cstring>
// We add here the functions and classes made by ourselves
#include "functions.h"
/* This next two libraries are for generating a random number of 5 digits.
This number will work as the password of watching an online movie, making it more realistic */
#include <stdlib.h>
#include <time.h>
// This next library is for making pauses during the execution of the program
#include <unistd.h>

using namespace std;

int main() {
	int option, days, tries;
	long long int cardNumber;
	float price, totalPrice = -1;
	bool directly; // this variable will stop or not the message of 'pressing any button to continue' from appearing
	vector<Movie> info; // we create a vector to store the movies
	vector<Actor> actorsData= readActorsFromFile(); //we create a vector to store the actors information
	readInfo(info, actorsData); // we store the movies in the vector
	string nameOfMovie, lowerName, username, expiredDate, startDate, endDate, keepGoing;
	vector<Rentals> rented; // vector to store rented movies
	Rentals rentedMovie;
	srand(time(NULL)); // this initializes the random number generator
	do{
		cout << "_________________/ Main Menu \\_________________\n_________________\\Movies Club/_________________\n1 - Watch online movies\n2 - Rent a movie DVD\n3 - Show DVD rentals\n4 - Show DVD availability\n5 - Exit.\n\n\nSelect an option... ";
		option = getInput(1,5); // we use the function getInput to get a number between 1 and 5
		cin.ignore(1, '\n'); // used to enable the use of getline()
		directly = false; 
		tries = 0;
		try{
			switch (option){
				case 1:
					cout << "\nIntroduce the title of the movie: ";
					getline(cin, nameOfMovie);
					lowerName = nameOfMovie;
					to_lower(lowerName);
					price = findMovie(info, nameOfMovie);	
					while(price == -1){ //we use this loop to check if the movie introduced is in our movies file
						if (tries >= 3) throw  "You have had many tries already\nIf you don't know the movies available check option 4 at the main menu";
						cout << "The movie title must be wrong, try typing it again: ";
						getline(cin, nameOfMovie);
						lowerName = nameOfMovie;
						to_lower(lowerName);
						price = findMovie(info, nameOfMovie);	
						tries += 1;		
					}
					cout << "The total price is: "<< price<< "\nDo you want to continue (Y/N)? ";
					getline(cin, keepGoing); // we now will check if the input introduced is a valid one
					while((keepGoing[0] != 'N'&& keepGoing[0] != 'n' && keepGoing[0] != 'Y'&& keepGoing[0] != 'y') || (keepGoing.size() != 1)){
						cout << "The only valid characters are 'y' or 'n', try again: ";
						getline(cin, keepGoing);
					}
					if (keepGoing[0] == 'Y'|| keepGoing[0] == 'y'){ // once verified the input, we will ask for the information if the answer is yes
						cout << "Introduce your complete name: ";
						getline(cin, username);
						cout << "Introduce your card number: ";
						cardNumber = getCardNumber(); // we use getCardNumber function as the number is too big for an int variable, and to check that it is a number
						cout <<  "Introduce the expired date (dd/mm/yyyy): ";
						cin.ignore(1, '\n');
						getline(cin, expiredDate);
						while (!validDate(stringToNum(expiredDate))){ // here we check if the date is valid
							cout << "The date introduced is not valid or your credit card has expired\nTry introducing a valid one again: ";
							getline(cin, expiredDate);
						}
						cout << "The payment has been made.";
						sleep(2); // this is for stopping the execution for 2 seconds and making it more readable
						cout <<"\n\n\nThank you, " << username <<", for using our www.ricarlosmovies.net .........";
						sleep(2); // now a random number will be printed as if it was the password
						cout <<"\n\nTo watch the movie, please follow the following link with the password: "<<10000+rand()%(100000-10000) <<"\nwww.ricarlosmovies.net/" << lowerName <<"/login/";
						sleep(3);
					}else{
						cout << "\n\n\n\n";
						directly = true; // this is just to jump directly to the main menu
					}
					break;
				case 2:
					cout << "\nIntroduce the title of the movie: ";
					getline(cin, nameOfMovie);
					price = findMovie(info, nameOfMovie);
					while(price == -1){ // we use this loop to check if the movie introduced is in our movies file
						if (tries >= 3) throw  "You have had many tries already\nIf you don't know the movies available check option 4 at the main menu";	// this breaks the loop if the user makes too many mistakes
						cout << "The movie title must be wrong, try typing it again: ";
						getline(cin, nameOfMovie);
						price = findMovie(info, nameOfMovie);
						tries += 1;		
					}
					cout << "Introduce the start date (dd/mm/yyyy): ";
					cin >> startDate;
					while (!validDate(stringToNum(startDate))){ // we use this to check if the date introduced is a valid one
						cout << "The date introduced is not valid, remember it has to be either today or a one in the future\nTry introducing a valid one again: ";
						cin >> startDate;
					}
					cout << "Introduce how many days (max 25): ";
					days = getInput(1,25); // same function we used for selecting an option in the menu
					totalPrice = price*days;
					endDate = numToString(increaseDate(stringToNum(startDate), days)); // we compute the date when the rental ends
					if (checkAvailability(rented, nameOfMovie, stringToNum(startDate), stringToNum(endDate))){ // here we use the function in order to see if a DVD is available in order to rent it
						cout << "The total required price is: "<< totalPrice  << "\nDo you want to continue (Y/N)? ";
						cin.ignore(1, '\n');
						getline(cin, keepGoing);
						while((keepGoing[0] != 'N'&& keepGoing[0] != 'n' && keepGoing[0] != 'Y'&& keepGoing[0] != 'y') || (keepGoing.size() != 1)){
							cout << "The only valid characters are 'y' or 'n', try again: ";
							getline(cin, keepGoing);
						}
						if (keepGoing[0] == 'Y'|| keepGoing[0] == 'y'){ //if the user wants to continue, we will ask for the information
							cout << "Introduce your complete name: ";
							getline(cin, username);
							cout << "Introduce your card number: ";
							cardNumber = getCardNumber();
							cout << "Introduce the expired date (dd/mm/yyyy): ";
							cin.ignore(1, '\n');
							getline(cin, expiredDate);
							while (!validDate(stringToNum(expiredDate))){ // we check also here if the date is valid
								cout << "The date introduced is not valid or your credit card has expired\nTry introducing a valid one again: ";
								getline(cin, expiredDate);
							}
							rentedMovie = Rentals( username, nameOfMovie, startDate, endDate, totalPrice); // used for storing each rental in a vector
							rented.push_back(rentedMovie);
							cout << "The payment has been made."; // now we display the rental information
							sleep(2);
							cout << "\n\n\nThank you, " << username <<", for using our www.ricarlosmovies.net .........";
							sleep(2);
							cout << "\n\nThe movie	 : "<< nameOfMovie;
							sleep(1);
							cout<<"\nRental start date: "<< startDate;
							sleep(1);
							cout << "\nRental end date  : "<< endDate;
							sleep(1);
							cout << "\nTotal price	 : " << price*days;
							sleep(1); 
							cout << "\nClient's name	 : "<<username;
							sleep(2);
						}else{
							totalPrice = -1;
							cout << "\n\n\n\n";
							directly = true;
						}
					}else{
						cout << "\n\nThere is not an available DVD according the specified dates. "; // this is if there was not a DVD available for the specified dates
						sleep(2);
					}
					break;
				case 3:	
					if (totalPrice != -1){
						cout << "Do you want to see all DVD rentals (1) or just the rentals of a specific movie (2)? ";
						option = getInput(1,2); // we select the option here
						switch (option)	{
							case 1:
								printAllRentals(rented); // this will print every movie in the rentals vector
								break;
							case 2:
								cout<<"\nIntroduce the title of the movie: ";
								cin.ignore(1, '\n');
								getline(cin, nameOfMovie);
								price = findMovie(info, nameOfMovie);
								while(price == -1){ //we use this loop to check if the movie introduced is in our movies file
									if (tries >= 3) throw  "You have had many tries already\nIf you don't know the movies available check option 4 at the main menu";
									cout << "The movie title must be wrong, try typing it again: ";
									getline(cin, nameOfMovie);
									price = findMovie(info, nameOfMovie);
									tries += 1;			
								}
								printRentals(rented,nameOfMovie); // this will only print the movies in the rental vector which have the title asked
								break;
						}
					}else{
						cout << "\n\nThere hasn't been any rental yet, try again after renting a DVD first"; // this is if the rental vector is empty
					}
					sleep(3);
					break;
				case 4:
					printAll(info); // we display all the information read from the text files
					sleep(2);
					cout << "\nThese are all the movies that are offered at our menu\nFor which one of those would you like to check its availability?\n(After selecting a movie you will be displayed its information and the intervals when it can be rented): ";
					do{
						getline(cin, nameOfMovie);
						price = findMovie(info, nameOfMovie);
						while(price == -1){ //we use this loop to check if the movie introduced is in our movies file
							if (tries >= 3) throw  "You have had many tries already\nIf you don't know the movies available check option 4 at the main menu";
							cout << "The movie title must be wrong, try typing it again: ";
							getline(cin, nameOfMovie);
							price = findMovie(info, nameOfMovie);
							tries += 1;			
						}
						printAsked(info, nameOfMovie, rented); // we print the specific information of the movie asked
						sleep(1);
						cout << "\nDo you want to check the availability of another DVD (Y/N)? ";
						getline(cin, keepGoing);
						while((keepGoing[0] != 'N'&& keepGoing[0] != 'n' && keepGoing[0] != 'Y'&& keepGoing[0] != 'y') || (keepGoing.size() != 1)){
							cout << "The only valid characters are 'y' or 'n', try again: ";
							getline(cin, keepGoing);
						}
						if (keepGoing[0] == 'Y'|| keepGoing[0] == 'y'){
							cout << "\nEnter the movie title: ";
						}
					}while (keepGoing[0] == 'Y'|| keepGoing[0] == 'y');
					directly = true;
					cout << "\n\n\n\n";
					break;			
			}
		}catch(const char *e){ // this is if the user mistakes too many times the title of a movie
			cout << e;
			sleep(2);
		}
		if ((!directly) && (option != 5)){
			cout <<"\n\nPress any key to return to the main menu ..... "; 
			getch(); //used for waiting until the user decides to proceed
			cout << "\n\n\n\n";
		}
	}while(option !=5);
	cout << "\n\nThank you for using us! See you soon :)"; // the final line of code to say goodbye
	return 0;
}
