#define SIZE_HASH	4 
#define SIZE_M		100000
#define SIZE_STR	10
 
typedef struct configuration{
    
    int conf[4];
    
}Configuration;
        

int execute(int m1, int m2, int m3);
void hill_climbing(Configuration configuration, Configuration &result);
int get_best(Configuration configuration, Configuration sons[9]);
void printf_conf(Configuration configuration);