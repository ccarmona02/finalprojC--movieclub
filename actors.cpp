#include <string>


using namespace std;

class Actor{
	private: // atributes
		string name, nationality;
		int birthdate;
	public:
		//Constructor
		Actor(string actorname, int birthday, string nation){
			name = actorname;
			birthdate = birthday;
			nationality = nation;
		}
		//getters
		string getName(){
			return name;
		}
		
		int getBirthdate(){
			return birthdate;
		}
		
		string getNationality(){
			return nationality;
		}
};
