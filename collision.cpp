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
	default_random_engine generator;
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

void hill_climbing(Configuration configuration, Configuration &result){
	
	int cont = 0;
	int value;
	bool flag = true;
	Configuration current = configuration;

	while(flag){
		Configuration sons[10];
		Configuration proximo = sons[get_best(current,sons)];

		//cout << "proximo "<< proximo.conf[3]<< endl;
		//cout << "corrente  "<< current.conf[3]<< endl;
		//cout << "count "<< cont <<endl; 
		if(current.conf[3] > proximo.conf[3] || (current.conf[3] == proximo.conf[3] && cont > 10) || cont == 10){
			//cout << "passou " << endl; 
			result = current;
			cout << " Inicial "<< endl;
			printf_conf(configuration);
			cout << " Resultado "<< endl;
			printf_conf(result);
			flag = false;
		}
		else if(current.conf[3] == proximo.conf[3]){
			//cout << " entrou segundo "<< endl;
			cont++;
			value = proximo.conf[3];
		}
		else if(proximo.conf[3] == value && cont > 5){
			//cout << " entrou terceiro "<< endl;
			int i = random()%9;
			current = sons[i];
		}

		current = proximo;
	}
	   
}


int get_best(Configuration configuration, Configuration sons[9]){

	//Configuration sons[9];

	for(size_t i = 0; i < 9; i++){
		/*for(size_t j = 0; j < 3; j++){
			sons[i].conf[j] = configuration.conf[j];
		}*/
		sons[i] = configuration;
	}
	for(size_t i = 0; i < 9; i++){
		for(size_t j = 0; j < 3; j++){
			if(j != i%3){
				sons[i].conf[j] -= 1000;
				break; 
			}
		}
		sons[i].conf[i] += 1000; 
		sons[i].conf[3] = execute(sons[i].conf[0],sons[i].conf[1],sons[i].conf[2]);
	}
	int max = 0;
	for(size_t i = 0; i < 9; i++){
		/*
		for(size_t j = 0; j < 4; j++){
			cout << sons[i].conf[j] << " ";	
		}
		cout << endl;*/
		if(sons[max].conf[3] < sons[i].conf[3])
			max = i;
		 
	}
	return max;	
}

void printf_conf(Configuration configuration){
	cout << "m1 "<< configuration.conf[0] << endl;
	cout << "m2 "<< configuration.conf[1] << endl;
	cout << "m3 "<< configuration.conf[2] << endl;
	cout << "collision "<< configuration.conf[3] << endl;
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

