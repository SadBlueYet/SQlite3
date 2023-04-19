#include <iostream>
#include "sqlite3.h"

using namespace std;

int main(){
	sqlite3 *db = 0;
	sqlite3_open("sqlite.db", &db);

	sqlite3_exec(db, "DROP TABLE IF EXISTS Brend", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS Seller", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS Categories", 0, 0, 0);
	sqlite3_exec(db, "DROP TABLE IF EXISTS Products", 0, 0, 0);
	
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Products ( id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, categories_id INTEGER, brend_id INTEGER, seller_id INTEGER)", 0, 0, 0);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Seller ( id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)", 0, 0, 0);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Brend ( id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)", 0, 0, 0);
	sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS Categories ( id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)", 0, 0, 0);
	
	sqlite3_close(db);
}