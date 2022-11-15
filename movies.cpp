#include <vector>
#include <string>
#include "actors.cpp"


using namespace std;

class Movie {
	
	private: // here are all the atributes of the class Movie
		string title, genre, director, descrip;
		int year;
		vector<Actor> actors;
		float price;
	
	public:
		
		Movie(){ };
		
		// constructor
		Movie (string myTitle, float myprice, int myYear, string mygenre, string mydirector, string mydescrip, vector<Actor> myActors){ 
			title = myTitle;
			price= myprice;
			year = myYear;
			genre= mygenre;
			director= mydirector;
			descrip= mydescrip;
			actors = myActors;
		} 
		// getters (some of them not used, but if needed, we already have them)
		string getTitle(){
			return title;
		}
		
		int getYear(){
			return year;
		}	
		vector<Actor> getActors(){
			return actors;
		}
		string getGenre(){ 
			return genre;	
		}
		string getDirector(){ 
			return director;	
		}
		string getDescrip(){ 
			return descrip;	
		}
		float getPrice(){ 
			return price;
		}	
};

class Rentals {
	private: //atributes
		string name, startDate, endDate;
		float totalprice;
		string movie;
	public:
		Rentals(){	}
		
		// constructor
		Rentals(string myName, string myMovie, string sdate, string edate, float tprice){
			 name=myName;
			 startDate= sdate;
			 endDate= edate;
			 totalprice=tprice;
			 movie= myMovie;
		}
		
		//getters
		string getName(){ 
			return name;
		}
		string getStartDate(){ 
			return startDate;
		}
		string getEndDate(){
			return endDate;
		 }
		float getPrice(){
			return totalprice;
		}
		string getMovieTitle(){
			return movie;
		}
	
};
