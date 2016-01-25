#include <stdio.h>

# include "global.h"
# include "rand.h"

#include <string.h>

/* Reset ith semester table*/ 
void reset(int array[5][9]){
	int i, j;
	for(i=0; i<5; i++){
		for(j=0; j<9; j++){
			array[i][j] = 0;
		}
	}
}
/* Reset ith semester table*/ 
void reset( vector <int> array[5][9]){
	int i, j;
	for(i=0; i<5; i++){
		for(j=0; j<9; j++){
			array[i][j].clear();
		}
	}
}
/* Copy second array to first array*/
void copy_array(int array[5][9], int array1[5][9]){
	int i,j;
	for(i=0; i<5; i++){
		for(j=0; j<9; j++){
			array[i][j] = array1[i][j];
		}
	}
}
/* Print ith semester to be concerned with semester file*/
void print_semester(int array[5][9], FILE *fpt){
	int i, j;
	for(i=0; i<9; i++){
		for(j=0; j<5; j++){
			fprintf(fpt, "%d ", array[j][i]);
		}
		fprintf(fpt,"\n");
	}
}
int get_1_row(int slot){
	if(slot%5<3)
		return (slot%5)+2;
	else
		return (slot%5)+4;
}
int get_1_col(int slot){
	return slot/5;
}
int get_2_row(int slot){
	int j;
	if(slot%5 == 0){
		j=0;
	}if(slot%5 == 1){
		j=2;
	}if(slot%5 == 2){
		j=3;
	}if(slot%5 == 3){
		j=5;
	}if(slot%5 == 4){
		j=7;
	}
	return j;
}
int get_2_col(int slot){
	return slot/5;
}
int get_3_row(int slot){
	int j;
	if(slot%4 == 0){
		j=0;
	}if(slot%4 == 1){
		j=2;
	}if(slot%4 == 2){
		j=4;
	}if(slot%4 == 3){
		j=5;
	}
	return j;
}
int get_3_col(int slot){
	return slot/4;
}
bool is_prerequisite(int pre_index_of_course_list, int post_index_of_course_list){
	int i;
	for(i=0; i<(int)vec1.at(post_index_of_course_list)->size(); i++){
		if(strcmp(vec1.at(post_index_of_course_list)->at(i).c_str(), course_list[pre_index_of_course_list].code ) == 0){
			return true;
		}
	}
	return false;
}
/*///////////////////////////////////////////////////////*/
/* filling scheduling table for 1-hour class by using slot number 
9-10	-	-	-	-	-
10-11	-	-	-	-	-
11-12	0	5	10	15	20
12-13	1	6	11	16	21
13-14	2	7	12	17	22
14-15	-	-	-	-	-
15-16	-	-	-	-	-
16-17	3	8	13	18	23
17-18	4	9	14	19	24
*/
void adding_course_1_slot(int array[5][9], int slot){
	if(slot%5<3)
		array[slot/5][(slot%5)+2]++;
	else
		array[slot/5][(slot%5)+4]++;
}
void adding_course_1_slot(vector <int> array[5][9], int slot, int i){
	if(slot%5<3)
		array[slot/5][(slot%5)+2].push_back(i);
	else
		array[slot/5][(slot%5)+4].push_back(i);
}
/*///////////////////////////////////////////////////////*/
/* filling scheduling table for 2-hour class by using slot number 
9-10	0	5	10	15	20
10-11	-	-	-	-	-
11-12	1	6	11	16	21
12-13	2	7	12	17	22
13-14	-	-	-	-	-
14-15	3	8	13	18	23
15-16	-	-	-	-	-
16-17	4	9	14	19	24
17-18	-	-	-	-	-
*/
void adding_course_2_slot(int array[5][9], int slot){
	int j;
	if(slot%5 == 0){
		j=0;
	}
	if(slot%5 == 1){
		j=2;
	}
	if(slot%5 == 2){
		j=3;
	}
	if(slot%5 == 3){
		j=5;
	}
	if(slot%5 == 4){
		j=7;
	}
	array[slot/5][j]++;
	array[slot/5][j+1]++;
}
void adding_course_2_slot(vector <int> array[5][9], int slot, int i){
	int j;
	if(slot%5 == 0){
		j=0;
	}
	if(slot%5 == 1){
		j=2;
	}
	if(slot%5 == 2){
		j=3;
	}
	if(slot%5 == 3){
		j=5;
	}
	if(slot%5 == 4){
		j=7;
	}
	array[slot/5][j].push_back(i);
	array[slot/5][j+1].push_back(i);
}
/*///////////////////////////////////////////////////////*/
/* filling scheduling table for 3-hour class by using slot number 
9-10	0	4	8	12	16
10-11	-	-	-	-	-
11-12	1	5	9	13	17
12-13	-	-	-	-	-
13-14	2	6	10	14	18
14-15	3	7	11	15	19
15-16	-	-	-	-	-
16-17	-	-	-	-	-
17-18	-	-	-	-	-
*/
void adding_course_3_slot(int array[5][9], int slot){
	int j;
	if(slot%4 == 0){
		j=0;
	}if(slot%4 == 1){
		j=2;
	}if(slot%4 == 2){
		j=4;
	}if(slot%4 == 3){
		j=5;
	}
	array[slot/4][j]++;
	array[slot/4][j+1]++;
	array[slot/4][j+2]++;
}
void adding_course_3_slot(vector <int> array[5][9], int slot, int i){
	int j;
	if(slot%4 == 0){
		j=0;
	}if(slot%4 == 1){
		j=2;
	}if(slot%4 == 2){
		j=4;
	}if(slot%4 == 3){
		j=5;
	}
	array[slot/4][j].push_back(i);
	array[slot/4][j+1].push_back(i);
	array[slot/4][j+2].push_back(i);
}
/*///////////////////////////////////////////////////////*/
/* collision of CSE courses at the same time*/
int calculate_collision1(int array[5][9], int minimum_collision){
	int i, j, result=0;
	for(i=0; i<5; i++){
		for(j=0; j<9; j++){
			if(array[i][j] > minimum_collision){
				result += array[i][j] - 1;
			}
		}
	}
	return result;
}
int calculate_collision1(vector <int> array[5][9], int minimum_collision){
	int i, j, result=0;
	for(i=0; i<5; i++){
		for(j=0; j<9; j++){
			if((int)array[i][j].size() > minimum_collision){
				result += array[i][j].size() - 1;
			}
		}
	}
	return result;
}
/*///////////////////////////////////////////////////////*/
/* collision of CSE courses -1 0(calculate_collision1) +1 semester*/
/*
int calculate_collision2(int array1[5][9],int array2[5][9], int minimum_collision){
	int i,j, result=0;
	for(i=0; i<5; i++){
		for(j=0; j<9; j++){
			if(array1[i][j] > minimum_collision && array2[i][j] > minimum_collision){
				result++;
			}
		}
	}
	return result;
}
*/
int calculate_collision2(vector <int> array1[5][9],int array2[5][9], int minimum_collision){
	int i, j, result=0;
	for(i=0; i<5; i++){
		for(j=0; j<9; j++){
			if((int)array1[i][j].size() > minimum_collision && array2[i][j] > minimum_collision){
				result += array1[i][j].size() + array2[i][j] - 1;
			}
		}
	}
	return result;
}
int calculate_collision7(vector <int> array1[5][9], vector <int> array2[5][9], int minimum_collision){
	int i, j, k, l, result=0;
	for(i=0; i<5; i++){
		for(j=0; j<9; j++){
			if((int)array1[i][j].size() > minimum_collision && (int)array2[i][j].size() > minimum_collision){

				for(k=0; k<(int)array2[i][j].size(); k++){
					for(l=0; l<(int)array1[i][j].size(); l++){
						if(!is_prerequisite(array1[i][j][l], array2[i][j][k])){
							result++;
						}
					}
				}

			}
		}
	}
	return result;
}
/*///////////////////////////////////////////////////////*/
/*count consecutive 4(can be changed) hour for teachers table*/
int calculate_collision3(int array[5][9], int max_consecutive_hour ){ 
	int counter;
	int i, j, result=0;
	for(i=0; i<5; i++){
		counter = 0;
		for(j=0; j<9; j++){
			if(array[i][j] > 0){
				counter++;
			}
			else{
				counter=0;
			}
			if(counter >= max_consecutive_hour){
				result++;
			}
		}	
	}
	return result;
}
/*///////////////////////////////////////////////////////*/
/* if 1 day (or more) whole day is empty for teachers table 
	return 0 
	else return 1*/
int calculate_collision4(int array[5][9]){ 
	int i, j, counter, tmp = 0;
	for(i=0; i<5; i++){
		counter=0;
		for(j=0; j<9; j++){
			if(array[i][j] > 0){
				counter=0;
				break;
			}
			else
				counter++;
		}
		if(counter == 9)
			tmp++;
	}
	if(tmp == 0)
		return 1;
	else
		return 0;
}
/*///////////////////////////////////////////////////////*/
/*if lecture and lab have been at the day slot return result;
else 0; */
int calculate_collision5(int array[5][9], int array1[5][9]){
	int i, j, k, result = 0;
	for(i=0; i<5; i++){
		for(j=0; j<9; j++){
			if(array[i][j] > 0 ){
				for(k=j; k<9; k++){
					if(array1[i][k] > 0){
						result++;
						break;
					}
				}
				break;
			}
			if(array1[i][j] > 0){
				for(k=j; k<9; k++){
					if(array[i][k] > 0){
						result++;
						break;
					}
				}
				break;
			}
		}
	}
	return result;
}

int calculate_collision6(vector<int> array[5][9]){
	int result=0, i, j, k,type1, type2;
	vector <int>  day;
	for(i=0; i < 5; i++){
		for(j=0; j<9; j++){
			for(k=0; k<(int)array[i][j].size(); k++){
				day.push_back(array[i][j][k]);
			}
		}
		for(j=0; j<(int)day.size(); j++){
			for(k=0; k<(int)day.size(); k++){
				if(j!=k && strcmp(course_list[j].code, course_list[k].code)==0){
					//result++;
					type1 = course_list[j].type;
					type2 = course_list[k].type;
					if( type1!=type2 && type1+type2 <= 1){
						result++;
					}
				}
			}
		}
		day.clear();
	}
	return result;
}
/*///////////////////////////////////////////////////////*/

