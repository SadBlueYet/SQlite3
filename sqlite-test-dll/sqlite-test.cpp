#include <iostream>
#include "sqlite3.h"

using namespace std;

struct ID{
	int id = 0;
};

 static int callback(void *data, int argc, char **argv, char **azColName){
   ID *Id = (ID *)data ;
   printf("\n");
   Id->id = atoi(argv[0]);
   return 0;
}

class Manager{
public:
	sqlite3 *db = 0;

	Manager(const char* db){
		if(sqlite3_open(db, &this->db))
			fprintf(stderr, "ddd", sqlite3_errmsg(this->db));
	}

	void add_product(){
		
		string title, request, seller_title, brend_title, category_title;
		cout << "Enter a Product name\n>>";
		cin >> title;
		
		cout << "Enter a Brend name\n>>";
		cin >> brend_title;

		cout << "Enter a Seller name\n>>";
		cin >> seller_title;

		cout << "Enter a Categories name\n>>";
		cin >> category_title;
		
		request = "INSERT INTO Products (name, seller_id, brend_id, categories_id) VALUES ('" + title +
		"', '" + to_string(add_brend(brend_title)) + "', '" + to_string(add_seller(seller_title)) + "', '" + to_string(add_category(category_title)) + "');";
		sqlite3_exec(db, request.c_str(), 0, 0, 0);
	}

	int add_seller(string title){
		string request = "SELECT id from Seller WHERE name='" + title + "'";
		ID Id;
		sqlite3_exec(db, request.c_str(),callback,&Id,0);
		if(Id.id == 0) {
			string str = "INSERT INTO Seller (name) VALUES ('" + title + "');";
			sqlite3_exec(db, str.c_str(), 0, 0, 0);
			sqlite3_exec(db, request.c_str(),callback,&Id,0);
		}
		return Id.id;
	}

	int add_brend(string title){
		string request = "SELECT id from Brend WHERE name='" + title + "'";
		ID Id;
		sqlite3_exec(db, request.c_str(),callback,&Id,0);
		if(Id.id == 0) {
			string str = "INSERT INTO Brend (name) VALUES ('" + title + "');";
			sqlite3_exec(db, str.c_str(), 0, 0, 0);
			sqlite3_exec(db, request.c_str(),callback,&Id,0);
		}
		return Id.id;
	}

	int add_category(string title){
		string request = "SELECT id from Categories WHERE name='" + title + "'";
		ID Id;
		sqlite3_exec(db, request.c_str(),callback,&Id,0);
		if(Id.id == 0) {
			string str = "INSERT INTO Categories (name) VALUES ('" + title + "');";
			sqlite3_exec(db, str.c_str(), 0, 0, 0);
			sqlite3_exec(db, request.c_str(),callback,&Id,0);
		}
		return Id.id;
	}

	~Manager(){
		sqlite3_close(this->db);
	}
};

int main(){
	/*sqlite3 *db = 0;
	if(sqlite3_open("sqlite.db", &db))
		fprintf(stderr, "ddd", sqlite3_errmsg(db));
	else cout << "ff";
	string request = "INSERT INTO Seller ('name') VALUES ('PAPA');";
	//string sql = "DELETE FROM Categories WHERE id = 1;";
	sqlite3_exec(db, request.c_str(), 0, 0, 0);*/
	Manager* manager = new Manager("sqlite.db");
	manager->add_product();
	cout << '\n';
	system("pause");
}
