#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void bubbleSort(int array[], int size)
{
    // TODO: sort array using bubble sort
    int counter = -1;
    int i, temp;
    while (counter != 0)
    {
        counter = 0;
        for (i = 0; i < size - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                //swap
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                // increase counter
                counter++;
            }
        } 
        size--;   
    }
}

int main(void)
{
    // create file to store data
    FILE *rawData = fopen("rawData.csv", "a");
    if (rawData == NULL)
    {
        return 1;
    }

    int SIZE = 5;
    int numberIterations = 2;

    while (SIZE <= 10){
        //loop 'number_iterations' to calculate average
        int i;
        for (i = 1; i <= numberIterations; i++){
            printf("iteration %i\n", i);
            //Generate random array
            int *randomArray = malloc(sizeof(int) * SIZE);
            if (randomArray == NULL){
                free(randomArray);
                return -1;
            }
            // int radomArray[SIZE];
            srand(i);
            
            for (int j = 0; j < SIZE; j++) {
                randomArray[j] = rand()%100;
            }

            // // print original random array
            // for (int item = 0; item < SIZE; item++)
            // {
            //     printf("%i ", randomArray[item]);
            // }
            // printf("\n");

            // make a copy of random array
            int *bubbleArray = malloc(sizeof(int) * SIZE);
            if (bubbleArray == NULL) {
                free(bubbleArray);
                return -1;
            }
            memcpy(bubbleArray, randomArray, (sizeof(int) * SIZE));

            //sort copy of array using bubble sort
            clock_t start = clock();    
            bubbleSort(bubbleArray, SIZE);
            clock_t end = clock();
            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Bubble sort time: %f seconds\n", time_spent);

            fprintf(rawData, "%d,%f\n", SIZE, time_spent);

            // // print sorted array using bubble sort
            // for (int e = 0; e < SIZE; e++)
            // {
            //     printf("%i ", bubbleArray[e]);
            // }
            // printf("\n");

            free(randomArray);
            free(bubbleArray);         

        }  
        
        printf("%d\n", SIZE);
        //Increment the size of the array        
        SIZE += 5;
    }
    fclose(rawData);
    return 0;
}