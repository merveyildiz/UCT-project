/* This file contains the variable and function declarations */

# ifndef _GLOBAL_H_
# define _GLOBAL_H_

# define INF 1.0e99
# define EPS 1.0e-14
# define E  2.71828182845905
# define PI 3.14159265358979

/* global variables */
typedef struct
{
    double constr_violation;        //about hard constraint
    double *xreal;                  //[course number] genin integer versiyonunu tutacak
    int **gene;                     //[courseNumber][6bit(48 slot var)]
    double *xbin;                   //hiç kullanılmamış
    double *obj;                    //
    int *ia;                        //(obj[i]-minobj)/epsilon
    double *constr;                 //
} individual;

typedef struct ind_lists
{
    individual *ind;
    struct ind_lists *parent;
    struct ind_lists *child;
} ind_list;

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
extern int neval;
extern int currenteval;
extern int nbinmut;
extern int nrealmut;
extern int nbincross;
extern int nrealcross;
extern int *nbits;
extern int *array;
extern double *min_realvar;
extern double *max_realvar;
extern double *min_binvar;
extern double *max_binvar;
extern double *epsilon;
extern double *min_obj;
extern int bitlength;
extern int elite_size;

/* global function declarations */
void allocate (individual *ind);
void deallocate (individual *ind);

void copy (individual *ind1, individual *ind2);

void crossover (individual *parent1, individual *parent2, individual *child1, individual *child2);
void realcross (individual *parent1, individual *parent2, individual *child1, individual *child2);
void bincross (individual *parent1, individual *parent2, individual *child1, individual *child2);

void decode (individual *ind);

int check_box_dominance (individual *a, individual *b);
int check_dominance (individual *a, individual *b);

void eval (individual *ind);

void initialize (individual *ind);

void insert (ind_list *node, individual *ind);
ind_list* del (ind_list *node);

void mutation (individual *ind);
void bin_mutate (individual *ind);
void real_mutate (individual *ind);

void test_problem (double *xreal, double *xbin, int **gene, double *obj, double *constr);

void report_pop (individual *ind, char * outputFileName);
void report_archive (ind_list *elite, char *outputFileName);

individual* tournament (individual *ind1, individual *ind2);

void update_elite (ind_list *elite, individual *ind);
void update_pop (individual *ea, individual *ind);

# endif
