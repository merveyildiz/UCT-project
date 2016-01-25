/* This file contains the variable and function declarations */

# ifndef _GLOBAL_H_
# define _GLOBAL_H_

#include <vector>
#include <string>
using namespace std;

# define INF 1.0e14
# define EPS 1.0e-14
# define E  2.71828182845905
# define PI 3.14159265358979
# define GNUPLOT_COMMAND "gnuplot -persist"

typedef struct
{
    int rank;
    double constr_violation;
    double *xreal;
    int **gene;
    double *xbin;
    double *obj;
    double *constr;
    double crowd_dist;
}
individual;

typedef struct
{
    individual *ind;
}
population;

typedef struct lists
{
    int index;
    struct lists *parent;
    struct lists *child;
}
list;

typedef struct course_detail
{
	char code[100];
	char teacher[200];
	int type;
	int semester;
	int duration;
	int labHour;
	int elective;
} course;

extern int nreal;
extern int nbin;
extern int nobj;
extern int ncon;
extern int popsize;
extern double pcross_real;
extern double pcross_bin;
extern double pmut_real;
extern double pmut_bin;
extern double eta_c;
extern double eta_m;
extern int ngen;
extern int nbinmut;
extern int nrealmut;
extern int nbincross;
extern int nrealcross;
extern int *nbits;
extern double *min_realvar;
extern double *max_realvar;
extern double *min_binvar;
extern double *max_binvar;
extern int bitlength;
extern int choice;
extern int obj1;
extern int obj2;
extern int obj3;
extern int angle1;
extern int angle2;

extern course *course_list;
extern int course_list_size;
extern int teacher_list_size;
extern char teacher_list[50][200];
extern int scheduling_counter[8][5][9];
extern int scheduling[8][5][9];
extern int lab_scheduling[5][9];
extern int meeting[5][9];
extern vector <vector <string> *> vec1;


void reset(int array[5][9]);
void reset( vector <int> array[5][9]);
void print_semester(int array[5][9], FILE *fpt);
void adding_course_1_slot(int array[5][9], int slot);
void adding_course_2_slot(int array[5][9], int slot);
void adding_course_3_slot(int array[5][9], int slot);
void adding_course_1_slot(vector <int> array[5][9], int slot, int i);
void adding_course_2_slot(vector <int> array[5][9], int slot, int i);
void adding_course_3_slot(vector <int> array[5][9], int slot, int i);
int calculate_collision1(int array[5][9], int minimum_collusion);
/*int calculate_collision2(int array1[5][9],int array2[5][9], int minimum_collusion);*/
int calculate_collision3(int array[5][9], int max_consecutive_hour );
int calculate_collision4(int array[5][9]);
int calculate_collision5(int array[5][9], int array1[5][9]);
int calculate_collision1(vector <int> array[5][9], int minimum_collusion);
int calculate_collision2(vector <int> array1[5][9],int array2[5][9], int minimum_collusion);
int calculate_collision7(vector <int> array1[5][9], vector <int> array2[5][9], int minimum_collision);
int calculate_collision6(vector<int> array[5][9]);
void free_data(int ***data, size_t xlen, size_t ylen);
int ***alloc_data(size_t xlen, size_t ylen, size_t zlen);
void copy_array(int array[5][9], int array1[5][9]);


void allocate_memory_pop (population *pop, int size);
void allocate_memory_ind (individual *ind);
void deallocate_memory_pop (population *pop, int size);
void deallocate_memory_ind (individual *ind);

double maximum (double a, double b);
double minimum (double a, double b);

void crossover (individual *parent1, individual *parent2, individual *child1, individual *child2);
void realcross (individual *parent1, individual *parent2, individual *child1, individual *child2);
void bincross (individual *parent1, individual *parent2, individual *child1, individual *child2);

void assign_crowding_distance_list (population *pop, list *lst, int front_size);
void assign_crowding_distance_indices (population *pop, int c1, int c2);
void assign_crowding_distance (population *pop, int *dist, int **obj_array, int front_size);

void decode_pop (population *pop);
void decode_ind (individual *ind);

void onthefly_display (population *pop, FILE *gp, int ii);

int check_dominance (individual *a, individual *b);

void evaluate_pop (population *pop);
void evaluate_ind (individual *ind);

void fill_nondominated_sort (population *mixed_pop, population *new_pop);
void crowding_fill (population *mixed_pop, population *new_pop, int count, int front_size, list *cur);

void initialize_pop (population *pop);
void initialize_ind (individual *ind);

void insert (list *node, int x);
list* del (list *node);

void merge(population *pop1, population *pop2, population *pop3);
void copy_ind (individual *ind1, individual *ind2);

void mutation_pop (population *pop);
void mutation_ind (individual *ind);
void bin_mutate_ind (individual *ind);
void real_mutate_ind (individual *ind);

void test_problem (double *xreal, double *xbin, int **gene, double *obj, double *constr);

void assign_rank_and_crowding_distance (population *new_pop);

void report_pop (population *pop, FILE *fpt);
void report_feasible (population *pop, FILE *fpt);
void report_ind (individual *ind, FILE *fpt);

void quicksort_front_obj(population *pop, int objcount, int obj_array[], int obj_array_size);
void q_sort_front_obj(population *pop, int objcount, int obj_array[], int left, int right);
void quicksort_dist(population *pop, int *dist, int front_size);
void q_sort_dist(population *pop, int *dist, int left, int right);

void selection (population *old_pop, population *new_pop);
individual* tournament (individual *ind1, individual *ind2);

# endif
