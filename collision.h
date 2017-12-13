#include <iostream>
#include <map>
#include <random>
#include <set>
#include <string>
#include "md5.h"
#include <cassert>


#define SIZE_HASH	4
#define SIZE_M      100000 
#define N_SETS      3
#define SIZE_STR	10


typedef struct configuration{

    int conf[4];

}Configuration;

using namespace std;

using HashToString = map<int, string>;
using StringToHash = map<string, int>;


int cryptohash(const string& original);
StringToHash create_messages();
HashToString find_collisons(const HashToString& hashes, int n_messages, StringToHash::const_iterator& iterator);
int execute(int m1, int m2, int m3);
int get_best(Configuration configuration, Configuration sons[9]);
void hill_climbing(Configuration configuration, Configuration &result);
void printf_conf(Configuration configuration);

