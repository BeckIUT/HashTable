#include<iostream>
#include<fstream>
#include<string>

using namespace std;

const int A[4] = { 33, 37, 39, 41 };
class Keys
{
public:
	string key;
	int hash_code;
	Keys* next;
	Keys(){ key = ""; next = NULL; }
};

class Hash_Table
{
	Keys* head;
	int collisions;
	int size;
public:
	Hash_Table(){ head = NULL; collisions = 0; size = 0; }
	bool is_Empty() const { return (head == NULL); }

	void Insert_Key(Keys* key)
	{
		if (is_Empty())
		{
			head = key;
			size++;
		}
		else
		{
			Keys* last = head;
			while (last != NULL)
			{
				if (last->next == NULL)
				{
					last->next = key;
					size++;
					collisions++;
					break;
				}
				last = last->next;
			}
		}
	}

	void print_Entries()
	{
		if (is_Empty())
		{
			return;
			cout << "Table is EMPTY !!!\n";
		}
		else
		{
			Keys* iterator = head;
			cout << "Entries with hash value " << iterator->hash_code << " : ";
			while (iterator != NULL)
			{
				cout << iterator->key;
				iterator = iterator->next;
				if (iterator == NULL)
					cout << endl;
				else
					cout << ", ";
			}
		}
	}

	void Find_Key(Keys* key)
	{
		Keys* iterator = head;
		bool found = false;
		while (iterator->key != key->key && iterator->next != NULL)
		{
			iterator = iterator->next;
		}

		if (iterator->key == key->key){
			cout << "\n\t\tKEY FOUND : " << iterator->key << endl;
			cout << "\n\t\tHASH VALUE : " << iterator->hash_code << endl;
			found = true;
		}
		if (!found)
			cout << "\n\t\tKEY WAS NOT FOUND\n";
	}

	int collision_Number()
	{
		return collisions;
	}

	void deleteEntry(){
		Keys* old = head;
		while (old != NULL){
			Keys* old2 = old;
			old = old->next;
			delete old2;
		}
		size = 0;
		collisions = 0;
		head = NULL;
	}
};

int hash_code(unsigned long long hash_value, int table_size)
{
	return (hash_value % table_size);
}

int hash_generator(string key, int table_size, int constant)
{
	unsigned long long hash_value = key.at(key.length() - 1);
	int a = constant;

	for (int i = key.length() - 2; i >= 0; i--)
	{
		hash_value = a*hash_value + key.at(i);
	}

	return hash_code(hash_value, table_size);
}

int main()
{
	Hash_Table table[3761];
	ifstream infor;
	infor.open("Strings_collections2.txt", ios::in);
	bool CONTINUE = true;
	int a = A[1];
	bool wordEntered = false;
	while (CONTINUE){

		cout << "\n\t\t--== WELCOME TO HASH TABLE GENERATOR ==--\n\t\t\t\t-= OPTIONS =-\n\t\t1. Import keys from an existing file\n\t\t2. Input manually\n\t\t3. Display all Hash Tables";
		cout << "\n\t\t4. Search for a key\n\t\t5. Diplay the table with max number of collisions\n\t\t6. Compare the number of collisions for {33, 37, 39, 41}\n\t\t7. Exit\n\n\t\tChoice : ";
		int choose_Option;
		cin >> choose_Option;

		switch (choose_Option){
		case 1:
			infor.seekg(0, ios::beg);
			for (int i = 0; i < 3761; i++){
				table[i].deleteEntry();
			}
			while (infor.eof() == 0){
				Keys* key1 = new Keys();
				string word;
				infor >> word;
				key1->key = word;
				key1->hash_code = hash_generator(key1->key, 3761, a);
				table[key1->hash_code].Insert_Key(key1);
			}
			wordEntered = true;
			break;
		case 2:{
				   Keys* key2 = new Keys();
				   string input;
				   cout << "Enter the key : ";
				   cin >> input;
				   key2->key = input;
				   key2->hash_code = hash_generator(key2->key, 3761, a);
				   table[key2->hash_code].Insert_Key(key2);
				   break;
		}
		case 3:{
				   for (int i = 0; i < 3761; i++){
					   table[i].print_Entries();
				   }
				   break;
		}
		case 4:{
				   if (wordEntered){
				   Keys* search = new Keys();
				   cout << "Enter the key : ";
				   string search_key;
				   cin >> search_key;
				   search->key = search_key;
				   search->hash_code = hash_generator(search->key, 3761, a);
				   table[search->hash_code].Find_Key(search);
				   }
				   else{
					   cout << "First enter the words!!!\n";
				   }
				   break;
		}
		case 5:{
				   int max = 0;
				   int index = 0;
				   for (int j = 0; j < 3761; j++){
					   if (max <= table[j].collision_Number()){
						   max = table[j].collision_Number();
						   index = j;
					   }
				   }
				   cout << "\n\t--== Table with max number of collisions[" << max << "] is " << index << " ==--\n";
				   table[index].print_Entries();
				   break;
		}
		case 6:{
				   Hash_Table table1[4][3761];
				   int con[4];
				   for (int i = 0; i < 4; i++){
					   con[i] = A[i];
					   infor.seekg(0, ios::beg);
					   while (infor.eof() == 0){
						   Keys* key3 = new Keys();
						   string word3;
						   infor >> word3;
						   key3->key = word3;
						   key3->hash_code = hash_generator(key3->key, 3761, con[i]);
						   table1[i][key3->hash_code].Insert_Key(key3);
					   }

					   int sum = 0;
					   for (int j = 0; j < 3761; j++){
							   sum += table1[i][j].collision_Number();
					   }
					   cout << "\n\t--== Number of collisions when a = " << con[i] << " is " << sum << " ==--\n";
				   }
				   break;
		}
		case 7:
			CONTINUE = false;
			break;
		default:
			cout << "!!! WRONG CHOICE !!!\n";
			break;
		}
		cin.get();
	}
	infor.close();
	cin.get();
	return 0;
}