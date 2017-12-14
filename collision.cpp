#include "collision.h"

/*
HashedToOriginal create_messages(){
    
    HashedToOriginal hash;
	string random;

    for (int i = 0; i < SIZE_M; i++) {
		random = create_random_string();
		//cout << "random " << random <<"hash"<< cryptohash(random) << endl;
		hash.insert(pair<string,string>(cryptohash(random),random));
		//hash[cryptohash(random)] = random;
    }

    return hash;
}

string cryptohash(const string& original) {
	string hashed = md5(original);
	hashed.resize(SIZE_HASH);
	return hashed;
}
 

*/

int cryptohash(const string& original) {
	string hashed = md5(original);
	hashed.resize(SIZE_HASH);
	return stoi(hashed, nullptr, 16);
}

StringToHash create_messages() {
	default_random_engine generator(100);
	StringToHash messages;
	string created;
	int random;

	for (int i = 0; i < SIZE_M; i++) {
		created = string(SIZE_STR, ' ');
		random = generator();

		do
			for (int i = 0; i < SIZE_STR; i++) {
				created[i] = random % 26 + 'a';
				random /= 26;

				if (random == 0)
					random = generator();
			}
		while (messages.find(created) != messages.end());

		messages[created] = cryptohash(created);
	}

	return messages;
}

HashToString find_collisons(const HashToString& hashes, int n_messages, StringToHash::const_iterator& iterator) {
	HashToString collisions;
	auto iteratoraux = hashes.end();

	for (int i = 0; i < n_messages && i < hashes.size(); i++) {
		//cout << i << endl;
// bug segentation esta aqui, ainda nao resolvi
//aparentemente a treta esta np conjunto gerado
		if (hashes.count(iterator->second) > 0 && iterator->second != 0){
			//cout<<collisions[iterator->second]<<" | iterator->second | "<< iterator->second<<endl;
			//cout << "iterator->first" << iterator->first << endl;
			collisions[iterator->second] = iterator->first;
		}

		iterator++;
	}
	//cout << "passou do loop"<< endl;
	return collisions;
}

const StringToHash message_set = create_messages();

int execute(int m1, int m2, int m3){
	HashToString hashes1, hashes2, hashes3;
	auto iterator = message_set.begin();

	assert(message_set.size() == SIZE_M);
	//assert((m1 + m2 + m3) == SIZE_M);
	//cout << m1 << " " << m2<< " "<< m3 << endl;
	
	iterator = message_set.begin();
	

	for (int i = 0; i < m1; i++) {
		hashes1[iterator->second] = iterator->first;
		iterator++;
	}
	
	//cout << " passou dentro da execute "<< endl;
	hashes2 = find_collisons(hashes1, m2, iterator);
	hashes3 = find_collisons(hashes2, m2, iterator);

	//cout << " passou dentro da execute 2"<< endl;
	return hashes3.size();
}


/*
void calculate(Configurations &configuration){
    
	HashedToOriginal hash[3];
	int select_set = 0, count[3] = {0,0,0};
	list<string> collided_hashs; 
	cout << "m1"<< configuration.m[0] <<"m2"<< configuration.m[1]<< "m3" << configuration.m[2] << endl;
	cout <<"massage set " << message_set.size() << endl;
    for(auto i = message_set.begin(); i != message_set.end(); i++){
		
		do{
			select_set = random()%3;
			//cout << "select_set" << select_set << endl;
		}while(count[select_set] == configuration.m[select_set]);
		//cout << i->first <<" "<< i->second << endl;
		hash[select_set].insert(pair<string,string>(i->first,i->second));
		count[select_set]++;
	}
	
	
	for(size_t i = 0; i < 3; i++){
		for(auto j = hash[i].begin(); j != hash[i].end(); j++){
			cout << "iterator->first: "<< j->first <<"iterator->second: "<< j->second<< endl;
		}
	}
	

	
	for (auto i = hash[0].begin(); i != hash[0].end(); i++){
		//if ((hash[0].at(i->first)!= i->second) && (hash[1].at(i->first) != i->second))
		//	collided_hashs.push_back(i->second);
		//cout << hash[0][i->first]<< "A"<< i->second<<"B"<< hash[1][i->first] << endl;
		
		
		cout << hash[0][i->first]<< " " << i->first<< endl;
		
		if ((hash[0][i->second] == i->first ) && (hash[1][i->second] == i->second )){	    
			collided_hashs.push_back(i->first);
		}
		
	}
	*/

	//cout <<" size "<< hash[2].size() << endl;
	/*
	for (auto i = hash[2].begin(); i != hash[2].end(); i++){
		if(hash[0].count(i->second)>0){
			cout << "entrou ";

		}
	}
	
	configuration.collision_value = collided_hashs.size();
	
	
}*/
/*
int find_collisons(const HashedToOriginal& hashes, const HashedToOriginal& hashes1) {
	HashedToOriginal collisions;
	auto iterator = 


	for (int i = 0; i < n_messages; i++) {
        
        try {
			
			if (hashes.at(hashed) != random)
				collisions[hashed] = random;
		}

		catch (exception& e) {}
	}

	return collisions;
}
*/
/*
string create_random_string() {
	static set<string> created;
	static default_random_engine generator;

	int random = generator();
	string str = string(SIZE_STR, ' ');

	do
		for (int i = 0; i < SIZE_STR; i++) {
			str[i] = random % 26 + 'a';
			random /= 26;

			if (random == 0)
				random = generator();
		}
	while ( !created.insert(str).second );
	// clog << created.size() << '\r';

	return str;
}
*/
/*inline void show(const HashedToOriginal& hashes) {
	clog << "String\t\tHash" << endl;

	for (auto i = hashes.begin(); i != hashes.end(); ++i)
		clog << i->second << '\t' << i->first << endl;

	clog << endl;
}*/

