
//Brandon Kelley 2716916 & Anastasiya Kalinina 2754066
//matrixmul is a program that scans for the input of the dimensions and corresponding values of two matrices.
//if the dimensions are compatible for multiplication it then outputs the resulting matrix that is the answer
//if the dimensions are not compatible it then prints out a matrix of 0 0

#include<stdio.h>
#include<stdlib.h>


int main() {

    int n, k, k2, m; //matrix dimensions
    int i, j, q; //counter variables for loops
    int answer; // to be used to add each multiplication step together to get the final result for the specified index

    //max size possible for each matrix from assignment: 1 <= n,m,k <= 300
    //create the matrices to be 300 by 300
    int matrix1[300][300];
    int matrix2[300][300];
    int matrixAnswer[300][300];

    //formatting and getting input for matrix1
    printf("-------------------------------------------------------------------------------------------------------\n\n");
    printf("\t\t\t\t\tMatrix Multiplier: \n\n\tPlease Enter in the Dimensions (n x k) of the First Matrix Seperated by a Space:\n\n\t\t");
    scanf("%d%d", &n, &k);
    printf("\n\tMatrix 1 Dimensions: %d x %d\n", n, k);
    printf("\tEnter elements of first matrix: type one row at a time and seperate each number with a space\n");

    for (i = 0; i < n; i++) {        //loop through the dimensions of the first matrix and set the values in the corresponding array location
        printf("\n");
        for (j = 0; j < k; j++) {
            printf("\t\t");
            scanf("%d", &matrix1[i][j]);
        }
    }

    //printf("%d", matrix1[0][0]);        test to see if values are assigned to correct area for 2x2 matrix example
    //printf("%d", matrix1[0][1]);
    //printf("%d", matrix1[1][0]);
    //printf("%d", matrix1[1][1]);

    //formatting and getting input for matrix2
    printf("\n\tPlease Enter in the Dimensions (k x m) of the Second Matrix Separated by a Space:\n\n\t\t");
    scanf("%d%d", &k2, &m);
    printf("\n\tMatrix 2 Dimensions: %d x %d\n", k2, m);

    //check if the dimensions are compatible to be multiplied
    if (k != k2) {
        printf("\n\tError: Dimension Mismatch,\n\n\tThe Number of Rows of Matrix 1 must Equal The Number of Columns in Matrix 2\n");
        printf("\n\t Answer Matrix:\n\t\t0  0 \n");
        printf("\n\n-------------------------------------------------------------------------------------------------------");
        exit(1); // exit program with an error code
    }

    printf("\tEnter elements of second matrix: type one row at a time and separate each number with a space\n");

    for (i = 0; i < k2; i++) {		//loop through the dimensions of the second matrix and set the values in the corresponding array location
        printf("\n");
        for (j = 0; j < m; j++) {
            printf("\t\t");
            scanf("%d", &matrix2[i][j]);
        }
    }

    //printf("%d", matrix2[0][0]);        test  to see if values are assigned to correct area for 2x2 matrix example
    //printf("%d", matrix2[0][1]);
    //printf("%d", matrix2[1][0]);
    //printf("%d", matrix2[1][1]);

    //calculate the answer matrix by looping through matrix 1 and 2, multiplying the values and adding them to total for each specific index
    answer = 0;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            for (q = 0; q < k; q++) {
                answer += matrix1[i][q] * matrix2[q][j]; // do each step of multiplication and add it to the answer for that index
            }
            matrixAnswer[i][j] = answer; // set that index to the sum of all the multiplication steps
            answer = 0; // reset the answer variable back to 0 to be used again for the next index
        }
    }

    printf("\n\tResulting Answer Matrix:\n");
    printf("\n\t\t%d x %d", n, m);
    printf("\n\n\t\t");

    //loop through the answer matrix and print each value
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%d   ", matrixAnswer[i][j]);
        } printf("\n\t\t");
    }

    printf("\n\n-------------------------------------------------------------------------------------------------------");
    return 0;

}

