#include <iostream>
#include "sqlite3.h"

using namespace std;

struct ID{
	int id = 0;
};
static int call(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    return 0;
}
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
		
		string title, request;
		cout << "Enter a Product name\n>>";
		cin >> title;
		
		request = "INSERT INTO Products (name, seller_id, brend_id, categories_id) VALUES ('" + title +
		"', '" + to_string(add_seller()) + "', '" + to_string(add_brend()) + "', '" + to_string(add_category()) + "');";
		sqlite3_exec(db, request.c_str(), 0, 0, 0);
	}

	int add_seller(){
		string title;
		cout << "Enter the seller title\n>>";
		cin >> title;

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

	int add_brend(){
		string title;
		cout << "Enter the brend title\n>>";
		cin >> title;

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

	int add_category(){
		string title;
		cout << "Enter the category title\n>>";
		cin >> title;

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

	void show_products(string name){
		
    	string query = "SELECT * FROM Products WHERE name = '" + name + "'";

		//string query = "SELECT * FROM Products;";
		sqlite3_exec(db, query.c_str(), call, NULL, NULL);
	}

	~Manager(){
		sqlite3_close(this->db);
	}
};

int main(){
	int user_choise;
	string product_name;
	Manager* manager = new Manager("sqlite.db");
	do{
		cout << "1 - Enter the product\n"
		"2 - Enter the seller\n"
		"3 - Enter the brend\n"
		"4 - Enter the category\n"
		"5 - Close a data base\n"
		"6 - Clear a data base\n"
		"9 - Show a products\n"
		"0 - Exit the programm\n>>";
		cin >> user_choise;
		if(user_choise == 1) manager->add_product();
		else if(user_choise == 2) manager->add_seller();
		else if(user_choise == 3) manager->add_brend();
		else if(user_choise == 4) manager->add_category();
		else if(user_choise == 5) delete(manager);
		else if(user_choise == 6) system("reset_bd");
		else if(user_choise == 9) {
			cout << "Enter the Product name\n>>";
			cin >> product_name;
			manager->show_products(product_name);
		}

		

	}while(user_choise != 0);
	cout << '\n';
	system("pause");
	return 0;
}




















/*sqlite3 *db = 0;
	if(sqlite3_open("sqlite.db", &db))
		fprintf(stderr, "ddd", sqlite3_errmsg(db));
	else cout << "ff";
	string request = "INSERT INTO Seller ('name') VALUES ('PAPA');";
	//string sql = "DELETE FROM Categories WHERE id = 1;";
	sqlite3_exec(db, request.c_str(), 0, 0, 0);*/