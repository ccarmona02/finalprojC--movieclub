#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include "movies.cpp"
#include <ctime>
#include <limits> // for validating numeric inputs

using namespace std;

// function to obtain an integer input between two numbers
int getInput(int min, int max){
	
	int num;
	bool valid_input = false;

	do{
		cin >> num;	

		if (!(valid_input = cin.good()))  {
			cout << "That's not a valid option, try again : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}else if ((num < min) || (num > max)){
			cout << "The number must be between " << min << " and "<< max<<", try again: ";
		}

	} while((!valid_input) || (num < min) || (num > max) );
	cin.clear();

	return num;
}

/* As the card number length is way bigger than the usual option input, 
we need a similar function to getInput but with 'long long int' variables */
long long int getCardNumber(){ 
	
	long long int num;
	bool valid_input = false;

	do{
		cin >> num;	

		if (!(valid_input = cin.good()))  {
			cout << "That's not a valid option, try again : ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	} while(!valid_input) ;

	return num;
}

// very similar function to one in Aula Global, used for storing information of a text file into a vector of classes
vector<Actor> readActorsFromFile(){  
	
	vector<Actor> actors;
	ifstream file;
	file.open("actors.txt");
	string name, nationality;
	int birthdate;
	
	if (!file){
		cout << "File does not exist " << endl;
	}else{
		while (!file.eof()){
			//Read name
			getline(file,name);
			//Read birthdate
			file >> birthdate;
			file.ignore(1, '\n');		
			//Read nationallity
			getline(file, nationality);			
			Actor currentActor(name, birthdate, nationality);			
			actors.push_back(currentActor); 
		}			
	}		
	file.close();	
	return actors;
}

// function to complete the information of actors from their name
void findActorData(vector<Actor> data, string name, int &birthdate, string &nationality){
	
	string temp;
	
	for(int i= 0; i< data.size(); i++){
		temp = data[i].getName();
		if (temp.compare(name)){
			birthdate = data[i].getBirthdate();
			nationality = data[i].getNationality();
		}
	}
}

// function used to store the movies read from the file into classes
 void readInfo(vector<Movie> &movieClasses, vector<Actor> data){
 	
	ifstream myfile;
	myfile.open("movies.txt");
	if(!myfile){
		cout<<"File does not exist"<<endl;
	}else{
		
		string title, director, genre, nationality, description;
		vector<Actor> actors;
		int year, birthdate;
		float price;
		
		while (!myfile.eof()) { // we will read here all the information of each movie
			getline(myfile, title);
			myfile>> price;
			myfile.ignore(1, '\n');
			myfile>> year;
			myfile.ignore(1, '\n');
			getline(myfile, genre);
			getline(myfile, director);
			getline(myfile, description);
			actors.clear();
			string moreActors = "who knows";
			while (moreActors !=";"){
				getline(myfile, moreActors);
				if (moreActors !=";"){
					findActorData(data, moreActors, birthdate, nationality);
					Actor act(moreActors, birthdate, nationality);
					actors.push_back(act);
				}
			}
			Movie mov1(title, price, year, genre, director, description , actors); // here each class is created
			movieClasses.push_back(mov1); // and here each one is stored into a vector
		}			
	myfile.close();	
	}
}

/*replaces all upper case characters with their lower case case equivalent.
It substitutes the blank spaces with low bars which will be very useful to compare movies */
void to_lower (string &s){  
	for(int i = 0; i < s.size(); i++){
		s[i] = tolower(s[i]);
		if (s[i]== ' '){
			s[i] = '_';
		}
	}
}


/* looks for the required title in the vector of movies.
Returns price and correct the movie title to display it as the original title*/
float findMovie(vector<Movie> movieClasses, string &requiredMovie ){
	string tempName, original;
	to_lower(requiredMovie);
	for (int i = 0; i < movieClasses.size(); i++){
		tempName = movieClasses[i].getTitle();
		original = tempName;
		to_lower(tempName);
		if ( tempName == requiredMovie ){
			requiredMovie = original;
			return movieClasses[i].getPrice();
		}
	}
	
	return -1;
}

// function to convert a date of the kind dd/mm/yyyy to an integer number
int stringToNum(string str){
	
	string day, month;
	int d, m, y;
	
	day = str.substr(0, 2);
    str.erase(0, 3);
    month = str.substr(0, 2);
    str.erase(0, 3);
	d = atoi(day.c_str());
	m = atoi(month.c_str());
	y = atoi(str.c_str());
	return (y*10000 + m*100+d);
}

// function to convert an integer number to a date of the kind dd/mm/yyyy
string numToString(int numberDate){
	int yearFromNum = numberDate/10000;
	int monthFromNum = (numberDate - yearFromNum*10000)/100;
	int dayFromNum = numberDate - yearFromNum*10000 - monthFromNum*100;
	string d = to_string(dayFromNum);
	string m = to_string(monthFromNum);
	string y = to_string(yearFromNum);
	if (dayFromNum < 10) d = "0" + d;
	if (monthFromNum < 10) m = "0" + m;
	string dateAsString = d + "/" + m + "/" + y;
	return dateAsString;
}

// this function is for checking if it is a leap year, in order to set the days of February to 28 or 29
bool isLeapYear(int year){
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)){
		return true;
	}else{
		return false;
	}
}

// used to get the maximum days of the month we are in, instead of considering that every month has 30 days
int getMonthDays(int year, int month){
	if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)){
		return 31;
	}else if ((isLeapYear(year)) && (month == 2)){
		return  29;
	}else if (month == 2){
		return 28;
	}else{
		return 30;
	}	
}

// we use this function to increase the date introduced the number of days chosen
int increaseDate(int originalDate, int daysIncreased){
	int year = originalDate/10000;
	int month = (originalDate - year*10000)/100;
	int day = originalDate - year*10000 - month*100;
	int monthDays = getMonthDays(year, month);
	if ((day + daysIncreased) > monthDays){
		day = day+daysIncreased - monthDays;
		month += 1;
		if (month > 12){
			month = 1;
			year += 1;
		}
	}else{
		day = day + daysIncreased;
	}
	return (year*10000 + month*100+day);
	
}

// this function checks if the entered date is a valid one or not
bool validDate(int enteredDate){ 
	time_t t = time(0);   // get time now, copied from Aula Global
	tm* now = localtime(&t);
	
	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;
	
	int enteredYear = enteredDate/10000;
	int enteredMonth = (enteredDate - enteredYear*10000)/100;
	int enteredDay = enteredDate - enteredYear*10000 - enteredMonth*100;
	
	if ((enteredMonth < 1) || (enteredMonth > 12)) return false;
	if (enteredYear < 1000)  return false;	
	int maxDay = getMonthDays(enteredYear, enteredMonth);
	if ((enteredDay < 1) || (enteredDay > maxDay)) return false;
	
	int currentDateAsInt = (year * 10000 ) + (month * 100) + day;
	
	if (enteredDate < currentDateAsInt){
		return false;
	}
	return true;
}

// function to print all rentals stored in the rentals vector
void printAllRentals( vector<Rentals>rented){
	 
	string rentedMovie, cname, sdate, edate;
	float tprice;
	cout <<"\nMovie title \tClient's name \tStart date \tEnd date \tTotal price ";
	cout << "\n_____________________________________________________________________________\n\n";
	for (int i=0; i< rented.size(); i++){
		Rentals auxrent = rented[i];
		rentedMovie = auxrent.getMovieTitle();
		cname= auxrent.getName();
		sdate= auxrent.getStartDate();
		edate= auxrent.getEndDate();
		tprice= auxrent.getPrice();
		sleep(1);
		cout << rentedMovie << "\t" << cname << "\t" << sdate << "\t" << edate << "\t" << tprice<<"\n\n";			
		
	}
}

// function to only print the rentals of a specific movie
void printRentals( vector<Rentals>rented, string movieTitle){
	 
	string rentedMovie, original;
	to_lower( movieTitle);
	string cname, sdate, edate;
	float tprice;
	bool atLeastOnce = false;
	
	for (int i=0; i< rented.size(); i++){
		Rentals auxrent = rented[i];
		rentedMovie = auxrent.getMovieTitle();
		original = rentedMovie;
		to_lower( rentedMovie );
		
		if ( movieTitle == rentedMovie){
			if (!atLeastOnce){
				cout<<"\nList of rentals of the movie "<< original << ":";
				cout <<"\n\nClient's name \tStart date \tEnd date \tTotal price ";
				cout << "\n_______________________________________________________________________\n\n";
			}
			atLeastOnce = true;
			cname= auxrent.getName();
			sdate= auxrent.getStartDate();
			edate= auxrent.getEndDate();
			tprice= auxrent.getPrice();
			sleep(1);
			cout << cname << "\t" << sdate << "\t" << edate << "\t" << tprice<< "\n\n";
		}
	}
	if (!atLeastOnce){ // if there are no rentals of the asked movie, it prints this
		cout << "\n\nThere hasn't been any rental of this movie yet, try again later\n\n";
	}
}

// this checks if there is at least one rental of the asked movie
bool checkRentals( vector<Rentals> rented, string movieTitle){
	 
	string rentedMovie, original;
	to_lower( movieTitle);
	bool atLeastOnce = false;
	
	for (int i=0; i< rented.size(); i++){
		Rentals auxrent = rented[i];
		rentedMovie = auxrent.getMovieTitle();
		original = rentedMovie;
		to_lower( rentedMovie );
		
		if ( movieTitle == rentedMovie){
			atLeastOnce = true;			
		}
	}
	return atLeastOnce;
}

// function to print every movie read from the text file
void printAll(vector<Movie> info){
	cout <<"\nMovie titles offered\n_______________________\n\n";
	string tempTitle; // we declare a variable to store temporary the movie title
	for(int i= 0; i< info.size(); i++){
		tempTitle = info[i].getTitle();
		sleep(1);
		cout << tempTitle <<"\n\n";	
	}
}

// function to check if the interval to rent a DVD is available or not
bool checkAvailability(vector<Rentals> rented, string askedMovie,int startDay, int endDay){
	
	struct rentedDays{
		int starting, ending;
	};
	 
	string tempMovie;
	to_lower(askedMovie);
	string sDate, eDate;
	vector<rentedDays> dates;
	struct rentedDays tempDay;
	
	if (rented.empty()) return true; // here we store in a vector all the rentals of the movie asked
	for (int i=0; i< rented.size(); i++){
		Rentals auxrent = rented[i];
		tempMovie = auxrent.getMovieTitle();
		to_lower( tempMovie );
		if ( askedMovie == tempMovie){
			sDate= auxrent.getStartDate();
			eDate= auxrent.getEndDate();
			tempDay.starting = stringToNum(sDate);
			tempDay.ending = stringToNum(eDate);
			dates.push_back(tempDay);
		}
	}

	int timesRented;
	bool available = true;

	for (int i= startDay; i<=endDay ; i = increaseDate(i, 1)){// loop for checking the availability of every day of the desired rental
		timesRented = 0;
		for (int j = 0; j < dates.size(); j++){
			if ((i >= dates[j].starting) && (i <= dates[j].ending)){
				timesRented += 1;
			}
		}
		if (timesRented >= 3){ // if a day in the interval has been rented 3 times, it is not available
			available = false;
		}
	}
	return available;
}

// very similar to the function above, but this prints the dates when the movie is not available
void printAvailability(vector<Rentals> rented, string askedMovie){
	
	struct rentedDays{
		int starting, ending;
	};
	 
	string tempMovie;
	to_lower(askedMovie);
	string sDate, eDate;
	vector<rentedDays> dates;
	struct rentedDays tempDay;
	
	for (int i=0; i< rented.size(); i++){
		Rentals auxrent = rented[i];
		tempMovie = auxrent.getMovieTitle();
		to_lower( tempMovie );
		if ( askedMovie == tempMovie){
			sDate= auxrent.getStartDate();
			eDate= auxrent.getEndDate();
			tempDay.starting = stringToNum(sDate);
			tempDay.ending = stringToNum(eDate);
			dates.push_back(tempDay);
		}
	}
	
	int minDate = dates[0].starting, maxDate = dates[0].ending;
	
	for (int i = 0; i<dates.size(); i++){
		if (minDate > dates[i].starting){
			minDate = dates[i].starting;
		}
		if (maxDate < dates[i].ending){
			maxDate = dates[i].ending;
		}		
	}
	
	int timesRented;
	vector<int> rentedDates;

	for (int i= minDate; i<=maxDate ; i = increaseDate(i, 1)){// loop for checking the availability of every day of the desired rental
		timesRented = 0;
		for (int j = 0; j < dates.size(); j++){
			if ((i >= dates[j].starting) && (i <= dates[j].ending)){
				timesRented += 1;
			}
		}
		if (timesRented >= 3){
			rentedDates.push_back(i); // each day that the DVD has been rented 3 times is stored in a vector
		}
	}
	
	if (rentedDates.empty()){ // this happens if there is not a day that the movie has been rented 3 times
		cout << "\nAlthough there are rentals of this movie, it is still completely available\n";
	}else{ // this prints every day stored in the vector of days that the movie has been rented 3 times
		cout << "\nThis movie is not available the following days:\n";
		for (int i = 0 ; i<rentedDates.size(); i++){
			sleep(1);
			cout << " - "<< numToString(rentedDates[i]) << endl;
		}
	}
}

void printAsked(vector<Movie> info, string askedMovie, vector<Rentals> rented){
	int askedYear;
	string askedDirector, askedDescription; // we declare some variables to store the information about the asked movie	
	vector<Actor> askedActors;
	string tempName, original; // these are for locating the movie
	
	for(int i= 0; i< info.size(); i++){
		to_lower(askedMovie);
		tempName = info[i].getTitle();
		original = tempName;
		to_lower(tempName);
		if ( tempName == askedMovie ){ // we store the movie information
			askedDirector = info[i].getDirector();
			askedYear = info[i].getYear();
			askedActors = info[i].getActors();
			askedDescription = info[i].getDescrip();
			break;
		}
	} // it now prints the movie information
	cout << "\nPrinting data of "<<original<<endl;
	sleep(1);
	cout << "> Director   : " << askedDirector<<endl;
	sleep(1);
	cout << "> Year       : " << askedYear<<endl;
	sleep(1);
	cout << "> Main actors: " << askedActors[0].getName();
	for (int i = 1; i < askedActors.size(); i++){
		cout << ", "<< askedActors[i].getName();
	}
	cout << ".\n";
	sleep(1);
	cout << "> Description: " << askedDescription<<endl;
	sleep(1);
	if (checkRentals(rented, original)){ // here it displays the movie availability
		printAvailability(rented, original);	
	}else{
		cout << "\nThis movie is completely available, there are no rentals of this movie\n";
	}
	
}

