#include <cassert>
#include <random>
#include <string>
#include <unordered_map>

#include "md5.h"
#include "cryptohash.h"

using namespace std;

using Hash = long long;
using HashToString = unordered_map<Hash, string>;
using StringToHash = unordered_map<string, Hash>;

Hash cryptohash(const string& original) {
	string hashed = md5(original);
	hashed.resize(SIZE_HASH);
	return stoll(hashed, nullptr, 16);
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

const StringToHash message_set = create_messages();

HashToString find_collisons(const HashToString& hashes, int n_messages, StringToHash::const_iterator& iterator) {
	HashToString collisions;

	for (int i = 0; i < n_messages; i++) {
		assert(iterator != message_set.end());

		if (hashes.find(iterator->second) != hashes.end())
			collisions[iterator->second] = iterator->first;

		iterator++;
	}

	return collisions;
}

int execute(int m1, int m2, int m3) {
	auto iterator = message_set.begin();
	HashToString hashes1;

	assert(message_set.size() == SIZE_M);
	assert((m1 + m2 + m3) == SIZE_M);

	for (int i = 0; i < m1; i++) {
		hashes1[iterator->second] = iterator->first;
		iterator++;
	}

	const HashToString hashes2 = find_collisons(hashes1, m2, iterator);
	const HashToString hashes3 = find_collisons(hashes2, m3, iterator);

	return hashes3.size();
}

void hill_climbing(Configuration configuration, Configuration &result){
	
	int cont = 0;
	int value;
	bool flag = true;
	Configuration current = configuration;

	while(flag){
		Configuration sons[9];
		Configuration proximo = sons[get_best(current,sons)];

		//cout << "proximo "<< proximo.conf[3]<< endl;
		//cout << "corrente  "<< current.conf[3]<< endl;
		//cout << "count "<< cont <<endl; 
		if(current.conf[3] > proximo.conf[3] || (current.conf[3] == proximo.conf[3] && cont > 20) || cont == 20){
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



	
	for (size_t i = 0; i < 9; i++){
		int generated;
		sons[i].conf[2] = SIZE_M;
		for(size_t j = 0; j < 2; j++){
			generated= random()+(10000*j);
			sons[i].conf[j] = (generated % sons[i].conf[2]) + 1;
			sons[i].conf[2] -= sons[i].conf[j];
		}
	
		sons[i].conf[3] = execute(sons[i].conf[0],sons[i].conf[1],sons[i].conf[2]);
	}
	/*

	for(size_t i = 0; i < 9; i++){	
			sons[i] = configuration;
	}

	for(size_t i = 0; i < 9; i++){
		int random1 = random()%3,random2 = random()%3;
   		while(random1 == random2){
			random2 = random()%3;
		}

	  sons[i].conf[random1] = sons[i].conf[random2];
	  sons[i].conf[random2] = sons[i].conf[random1];
	  sons[i].conf[random1]-= 1000;
	  sons[i].conf[random2]+= 1000;

	  sons[i].conf[3] = execute(sons[i].conf[0],sons[i].conf[1],sons[i].conf[2]);
	  //cout << sons[i].conf[3] << endl;
	}*/

	int max = 0;
	for(size_t i = 0; i < 9; i++){
		

		//cout<<sons[i].conf[0]<<endl;
		//cout<<sons[i].conf[1]<<endl;
		//cout<<sons[i].conf[2]<<endl;
		if(sons[max].conf[3] < sons[i].conf[3])
			max = i;
		 
	}
	return max;	
   
	


		

}

/*
int get_best(Configuration configuration, Configuration sons[9]){

	//Configuration sons[9];

	for(size_t i = 0; i < 9; i++){
	
		sons[i] = configuration;
	}
	for(size_t i = 0; i < 9; i++){
		for(size_t j = 0; j < 3; j++){
			if(j != (i%3)){
				sons[i].conf[j] -= 100;
				break; 
			}
		}
		sons[i].conf[i%3] += 100; 
		sons[i].conf[3] = execute(sons[i].conf[0],sons[i].conf[1],sons[i].conf[2]);
	}
	int max = 0;
	for(size_t i = 0; i < 9; i++){
	
		if(sons[max].conf[3] < sons[i].conf[3])
			max = i;
		 
	}
	return max;	
}*/

void printf_conf(Configuration configuration){
	cout << "m1 "<< configuration.conf[0] << endl;
	cout << "m2 "<< configuration.conf[1] << endl;
	cout << "m3 "<< configuration.conf[2] << endl;
	cout << "collision "<< configuration.conf[3] << endl;
}


