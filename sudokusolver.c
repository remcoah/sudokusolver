/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Remco Holstege 1217370
   Dated:     02/09/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/


/****************************************************************/

#define MINROWSET 0
#define MAXROWSET 8
#define MINCOLSET 9
#define MAXCOLSET 17
#define MINSQRSET 18
#define MAXSQRSET 26
#define PIPE "\n------+-------+------\n"

void print_sudoku(int sudoku[]);
void validsudoku(int sudoku[]);
int checkset(int sudoku[], int setnum);
int strategy_one(int sudoku[]);
int countunknown(int sudoku[]);

/*****************************************************************************/

/* main program controls all the action
*/
int main(int argc, char *argv[]) {
	
	fill_c2s();
	int sudoku[NCLL];

	/* Reading the values inputted */
	int n, excess, val;
    n = excess = 0;
    while (scanf("%d", &val)==1) {
        if (n==NCLL) {
            excess++;
        } else {
            sudoku[n] = val;
            n++;
        }
    }

	/* Check if input is in sudoku format */
	if ((n != NCLL) || excess) {
		printf("You have not inputted exactly 81 numbers\n");
		exit(EXIT_FAILURE);
	}

	print_sudoku(sudoku);
	validsudoku(sudoku);

	/* Implement strategy 1 as many times as possible */
	while (countunknown(sudoku)) {
		int movesmade = strategy_one(sudoku);
		if (!movesmade) {
			break;
		}
	}

	print_sudoku(sudoku);
	if (countunknown(sudoku) == 0) {
		printf("\nta daa!!!\n");
	}

	return 0;
}

/*****************************************************************************/

/* Prints out sudoku in a neat format and number of unknown cells */
void print_sudoku(int sudoku[]) {
	int unknown, i;
	unknown = 0;
	for (i=0; i<NCLL; i++) {
		if (((i != 0) && (i%(NDIM*NDIG) == 0))) {
			/* 3 lines have been written, draw horizontal border line */
			printf(PIPE);
		} else if ((i%NDIG == 0)) {
			/* Row complete, new line */
			printf("\n");
		} else if ((i%NDIM == 0)) {
			/* 3 cells written, draw vertical border line */
			printf("| ");
		}
		if (sudoku[i]==0) {
			/* Unkown value */
			printf(".");
			unknown++;
		} else {
			printf("%d", sudoku[i]);
		}

		/* Add space if number is not at end of line */
		if ((i == 0) || ((i+1)%NDIG != 0)) {
			printf(" ");
		}
	}
	printf("\n\n%2d cells are unknown\n", unknown);
}

/*****************************************************************************/

/* Checks if sudoku is valid, prints out any errors and exits */
void validsudoku(int sudoku[]) {
	int totalsetviolations = 0;
	int totalerrors = 0;

	/* Iterate through each set and check if valid */
	for (int set = 0; set < NSET; set++) {
		int errors = checkset(sudoku, set);
		if (errors != 0) {
			totalsetviolations++;
			totalerrors += errors;
		}
	}

	if (totalerrors) {
		printf("\n\n%d different sets have violations\n", totalsetviolations);
		printf("%d violations in total\n", totalerrors);
		exit(EXIT_FAILURE);
	}
}

/*****************************************************************************/

/* Returns the number of errors in a set and prints any violations */
int checkset(int sudoku[], int setnum) {
	int errors = 0;

	/* String used to output the set type in which an error occurs */
	char settype[6];

	if ((MINROWSET <= setnum) && (setnum <= MAXROWSET)) {
		char rownum = setnum + 1 + '0';
		settype[0] = 'r';
		settype[1] = 'o';
		settype[2] = 'w';
		settype[3] = ' ';
		settype[4] = rownum;
		settype[5] = '\0';
	} else if ((MINCOLSET <= setnum) && (setnum <= MAXCOLSET)) {
		char colnum = setnum - MAXROWSET + '0';
		settype[0] = 'c';
		settype[1] = 'o';
		settype[2] = 'l';
		settype[3] = ' ';
		settype[4] = colnum;
		settype[5] = '\0';
	} else if ((MINSQRSET <= setnum) && (setnum <= MAXSQRSET)) {
		char sqrnum = setnum - MAXCOLSET + '0';
		settype[0] = 's';
		settype[1] = 'q';
		settype[2] = 'r';
		settype[3] = ' ';
		settype[4] = sqrnum;
		settype[5] = '\0';
	}

	/* A 2d array calculating to store frequency of each number in set */
	int cellcount[NDIG][2];
	for (int i = 0; i < NDIG; i++) {
		cellcount[i][0] = i + 1;
		cellcount[i][1]	= 0;
	}

	/* Counts occurrance of each number in the set */
	for (int j = 0; j < NDIG; j++) {
		int cellnum = sudoku[s2c[setnum][j]];
		if (cellnum == 0) {
			continue;
		} else {
			cellcount[cellnum - 1][1]++;
		}
	}

	/* Check if frequency of each number in the set is less than 1 */
	for (int k = 0; k < NDIG; k++) {
		if (cellcount[k][1] > 1) {
			errors++;
			printf("\nset %2d (%s): %d instances of %d", 
			setnum, settype, cellcount[k][1], cellcount[k][0]);
		}
	}

	return errors;
}

/*****************************************************************************/

/* Implements strategy 1 on sudoku and returns the total number of
   moves made in this implementation of strategy 1 */
int strategy_one(int sudoku[]) {
	int movesmade = 0;

	/* Making an empty layout for all moves implemented in this iteration of 
	   strategy 1 to ensure output is the same as expected by rubric */
	int newvals[NCLL];
	int i;
	for (i = 0; i < NCLL; i++) {
	 	newvals[i] = 0;
	}

	/* A 2d array which stores true or false values for what number a 
	   cell can be */
	int potentialcval[NDIG][2];

	for (int c = 0; c < NCLL; c++) {
		if (sudoku[c] == 0) {
			/* Empty cell, must implement strategy 1 */
			for (i = 0; i < NDIG; i++) {
				int sudokuval = i + 1;
				potentialcval[i][0] = sudokuval;
				potentialcval[i][1] = 1;
			}

			/* Iterate over each cell of the sets c is a member of and 
			   determine what values it cannot be */
			for (int s = 0; s < NGRP; s++) {
				int cellstocheck[NDIG];
				for (int r = 0; r < NDIG; r++) {
					cellstocheck[r] = s2c[c2s[c][s]][r];
				}
				for (int j = 0; j < NDIG; j++) {
					if (sudoku[cellstocheck[j]] != 0) {
						potentialcval[sudoku[cellstocheck[j]] - 1][1] = 0;
					}
				}
			}

			/* Now iterate over potential values and see if there is only 1 */
			int potentialsfreq = 0;
			int value = 0;
			for (int k = 0; k < NDIG; k++) {
				if (potentialcval[k][1]) {
					potentialsfreq++;
					value = k + 1;
				}
			}

			/* Implement move if possible */
			if (potentialsfreq == 1) {
				if (movesmade == 0) {
					printf("\nstrategy one\n");
				}
				printf("row %d col %d must be %d\n", rownum(c), colnum(c), 
				       value);
				newvals[c] = value;
				movesmade++;
			}
		}
	}

	/* Update sudoku with new values found */
	for (i=0; i<NCLL; i++) {
		if (newvals[i]) {
			sudoku[i] = newvals[i];
		}
	}

	return movesmade;
}

/*****************************************************************************/

/* Returns the number of unknown cells in a sudoku */
int countunknown(int sudoku[]) {
	int unknown = 0;
	for (int i = 0; i < NCLL; i++) {
		if (sudoku[i] == 0) {
			unknown++;
		}
	}
	return unknown;
}

/* algorithms are fun */