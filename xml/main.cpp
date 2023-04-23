#include <iostream>
#include <string>
#include "tinyxml2.cpp"

using namespace std;
using namespace tinyxml2;

class Manager{
public:
	XMLDocument doc;
	
	Manager(){
		
		doc.LoadFile("test.xml");
	}
	string add_id(XMLElement* root, XMLElement* item, string id, string title, string foo_id){

		cout<<foo_id;
		item->SetAttribute("name", title.c_str());
		cout<<"a";
		if(foo_id == "0"){
    		item->SetAttribute("id", id.c_str());
			root->SetAttribute("id", id.c_str());
			return id;
		} 
		else {
			cout<<"a";
    		item->SetAttribute("id", foo_id.c_str());
			cout<<"a";
			root->SetAttribute("id", id.c_str());
			return foo_id;
		}

	}
	string check_id(XMLElement* root, string verified_name){

		for( root; root; root = root->NextSiblingElement()){
			string name = root->FirstChildElement( "Object" )->Attribute( "name" );
			string id = root->FirstChildElement( "Object" )->Attribute( "id" );

			if (name == verified_name) return id;
		}
		return "0";
	}

	string auto_inkrement(){

		XMLElement* counter = doc.FirstChildElement("Main")->FirstChildElement("Product")->FirstChildElement("id");
		string id_Attribute = counter->Attribute("id");

		int id = stoi(id_Attribute);
		id += 1;

		return to_string(id);
	}

	void add_product(){
		string title;

		cout << "Enter a Product name\n>>";
		cin >> title;

		XMLElement* root = doc.FirstChildElement("Main")->FirstChildElement("Product");
    	XMLElement* newItem = doc.NewElement("Object");

		string id = auto_inkrement();

		newItem->SetAttribute("name", title.c_str());
    	newItem->SetAttribute("id", id.c_str());
		root->FirstChildElement( "id" )->SetAttribute("id", id.c_str());
		
    	root->InsertEndChild(newItem);

		add_seller(id);
		add_brend(id);
		add_category(id);

		doc.SaveFile("test.xml");
	}

	void add_seller(string id){
		string title;

		cout << "Enter the seller title\n>>";
		cin >> title;

		XMLElement* root = doc.FirstChildElement("Main")->FirstChildElement("Seller");
    	XMLElement* newItem = doc.NewElement("Object");
		XMLElement* product_root = doc.FirstChildElement("Main")->FirstChildElement("Product")->FirstChildElement("id");

		string foo_id = check_id(root, title);
		id = add_id(product_root, newItem, id, title, foo_id);

    	root->InsertEndChild(newItem);
		doc.SaveFile("test.xml");

	}

	void add_brend(string id){
		string title;

		cout << "Enter the brend title\n>>";
		cin >> title;

		XMLElement* root = doc.FirstChildElement("Main")->FirstChildElement("Brend");
    	XMLElement* newItem = doc.NewElement("Object");
		XMLElement* product_root = doc.FirstChildElement("Main")->FirstChildElement("Product")->FirstChildElement("id");

		string foo_id = check_id(root, title);
   		id = add_id(product_root, newItem, id, title, foo_id);

    	root->InsertEndChild(newItem);
		doc.SaveFile("test.xml");
	}

	void add_category(string id){
		string title;

		cout << "Enter the category title\n>>";
		cin >> title;

		XMLElement* root = doc.FirstChildElement("Main")->FirstChildElement("Category");
    	XMLElement* newItem = doc.NewElement("Object");
		XMLElement* product_root = doc.FirstChildElement("Main")->FirstChildElement("Product")->FirstChildElement("id");

		string foo_id = check_id(root, title);
   		id = add_id(product_root, newItem, id, title, foo_id);

    	root->InsertEndChild(newItem);
		doc.SaveFile("test.xml");
	}
	~Manager(){
	}
};

int main(){
	int user_choise;
	string product_name;
	Manager* manager = new Manager();
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
		//else if(user_choise == 2) manager->add_seller();
		//else if(user_choise == 3) manager->add_brend();
		//else if(user_choise == 4) manager->add_category();
		else if(user_choise == 5) delete(manager);
		else if(user_choise == 6) system("reset_bd");
		else if(user_choise == 9) {
			cout << "Enter the Product name\n>>";
			cin >> product_name;
			//manager->show_products(product_name);
		}
	}while(user_choise != 0);
	system("pause");
	return 0;
}

