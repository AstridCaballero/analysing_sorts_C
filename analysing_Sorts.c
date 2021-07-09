#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Prototypes
void bubbleSort(int array[], int size);
int * insertionSort(int arr[], int size);
int * selectionSort(int arr[], int size);
int * mergeSort(int *arr, int size);

int main(void)
{
    // create file to store raw data
    FILE *rawData = fopen("rawData.csv", "a");
    if (rawData == NULL)
    {
        return 1;
    }
    fprintf(rawData, "range,bubble,insertion,selection,merge\n");

    // create file to store average data
    FILE *averageData = fopen("averageData.csv", "a");
    if (averageData == NULL)
    {
        return 1;
    }
    fprintf(averageData, "range,bubble,insertion,selection,merge\n");

    int SIZE = 5000;
    int numberIterations = 50;

    while (SIZE <= 50000){
        //variables to calculate the average  
        double totalTimeBubble = 0.0;
        double totalTimeSelection = 0.0;
        double totalTimeInsertion = 0.0;
        double totalTimeMerge = 0.0;       
        double averageTimeBubble = 0.0;
        double averageTimeInsertion = 0.0;
        double averageTimeSelection = 0.0;
        double averageTimeMerge = 0.0;

        //loop 'number_iterations' to calculate average
        int i;
        for (i = 1; i <= numberIterations; i++){             
                      
            //Generate random array
            int *randomArray = malloc(sizeof(int) * SIZE);
            if (randomArray == NULL){
                free(randomArray);
                return 1;
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
                return 1;
            }
            memcpy(bubbleArray, randomArray, (sizeof(int) * SIZE));            

            //sort copy of array using bubble sort
            clock_t start = clock();    
            bubbleSort(bubbleArray, SIZE);
            clock_t end = clock();
            double timeSpentBubble = (double)(end - start) / CLOCKS_PER_SEC;
            totalTimeBubble += timeSpentBubble;
            // printf("Bubble sort time: %f seconds\n", timeSpentBubble);

            //sort array using insertion sort
            start = clock(); 
            insertionSort(randomArray, SIZE);
            end = clock();
            double timeSpentInsertion = (double)(end - start) / CLOCKS_PER_SEC;
            totalTimeInsertion += timeSpentInsertion;
            // printf("Insertion sort time: %f seconds\n", timeSpentInsertion);

            //sort array using selection sort
            start = clock(); 
            selectionSort(randomArray, SIZE);
            end = clock();
            double timeSpentSelection = (double)(end - start) / CLOCKS_PER_SEC;
            totalTimeSelection += timeSpentSelection;
            // printf("Selection sort time: %f seconds\n", timeSpentSelection);

            //sort array using merge sort
            int *mergeArray = malloc(sizeof(int) * SIZE);
            if (mergeArray == NULL) {
                free(mergeArray);
                return 1;
            }
            start = clock(); 
            mergeArray = mergeSort(randomArray, SIZE);
            end = clock();
            double timeSpentMerge = (double)(end - start) / CLOCKS_PER_SEC;
            totalTimeMerge += timeSpentMerge;
            // //print array sorted with merge sort
            // for (int i = 0; i < SIZE; i++)
            // {
            //     printf( "arr[%d] = %d\n", i, mergeArray[i]);        
            // }  
            // printf("Merge sort time: %f seconds\n", timeSpentMerge);

            //store data in csv file
            fprintf(rawData, "%d,%f,%f,%f,%f\n", SIZE, timeSpentBubble, timeSpentInsertion, timeSpentSelection, timeSpentMerge);

            // // print sorted array using bubble sort
            // for (int e = 0; e < SIZE; e++)
            // {
            //     printf("%i ", bubbleArray[e]);
            // }
            // printf("\n");

            free(randomArray);
            free(bubbleArray);    
            free(mergeArray);    
        }  

        averageTimeBubble = totalTimeBubble/numberIterations;
        averageTimeInsertion = totalTimeInsertion/numberIterations;
        averageTimeSelection = totalTimeSelection/numberIterations;
        averageTimeMerge = totalTimeMerge/numberIterations;
        
        fprintf(averageData, "%d,%f,%f,%f,%f\n", SIZE, averageTimeBubble, averageTimeInsertion, averageTimeSelection, averageTimeMerge);

        printf("%d\n", SIZE);
        //Increment the size of the array        
        SIZE += 5000;
    }
    fclose(rawData);
    fclose(averageData);
    return 0;
}

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

int * insertionSort(int arr[], int size)
{
    int i;
    // Sort [0] item
    int temp = arr[0];  
    int index;  
    int counter;
    // move to the right and compare 
    for (i = 0; i < size - 1; i++)
    {                 
        int j = i;
        counter = 0;
        // move to the left and compare
        if (arr[i] > arr[i + 1])
        {
            temp = arr[i + 1];
            index = i + 1;

            while ((j >= 0) && (arr[j] > arr[i + 1]))
            {      
                // count how many numbers to the left are bigger than arr[i + 1]
                counter++;      
                // move to the left
                j--;
            } 
            // move elements that are greater than arr[i + 1] to the right  
            int l = index;
            int m = counter;
            for (; m > 0; l--, m--)
            {
                arr[l] = arr[l - 1]; 
            }
            int new_index = index - counter;
            arr[new_index] = temp;
        }         
    }
    // int k;
    // for (k = 0; k < size; k++)
    // {
    //     printf( "arr[%d] = %d\n", k, arr[k]);        
    // } 

    return arr;
}

int * selectionSort(int arr[], int size)
{
    int counter = 1;    
    int n = 0;   
    while(counter != size)
    {
        int i;                
        int temp_small = arr[n];       
        int index;        
        for (i = n; i < size - 1; i++)
        {
            // Find smallest number                          
            if (temp_small > arr[i + 1])
            {
                temp_small = arr[i + 1];
                index = i + 1;
            }                   
        }
        // take smallest number and swap place with 1st place of unsorted array
        if (temp_small != arr[n])
        {            
            arr[index] = arr[n];           
            arr[n] = temp_small;            
        }        
        n++;
        counter++; 
    }  
    // int k;
    // for (k = 0; k < size; k++)
    // {
    //     printf( "arr[%d] = %d\n", k, arr[k]);        
    // }    
    return arr;  
}

int * mergeSort(int *arr, int size)
{
    // create variable for the new_array    
    int *new_arr = NULL;
    // prepare other variables
    int left;
    int right;
    int *left_arr = NULL;
    int *right_arr = NULL;      

    /* if only one item */
    if (size == 1)
    {
        new_arr = malloc(size * sizeof(int));
        if (new_arr != NULL)
        {
            new_arr[0] = arr[0];
        }        
    }
    else
    {
        int i;
        // Get number of elements for the left side
        left = size/2;
        left_arr = malloc(left * sizeof(int));
        if (left_arr != NULL)
        {            
            for (i = 0; i < left; i++)
            {
                left_arr[i]= arr[i];
            }
        }        
        
        // Get number of elements for the right side
        right = size - left;
        right_arr = malloc(right * sizeof(int));
        if (right_arr != NULL)
        {
            for (i = 0 ; i < right; i++)
            {
                right_arr[i] = arr[i + left];
            }
        }        
        /* sort left half of items */
        left_arr = mergeSort(left_arr, left);
        /* sort right half of itmes */
        right_arr = mergeSort(right_arr, right);

        /* Merge sorted halves */
        // Prepare variables        
        int j = 0;
        int k = 0;
        int index = 0;
        new_arr = malloc((size) * sizeof(int));
        if (new_arr != NULL)
        {
            // Compare left side with right side until one of the sides has all its elements store in new_arr
            while(j < left && k < right)
            {
                if (left_arr[j] > right_arr[k])
                {
                    new_arr[index] = right_arr[k];
                    index++;
                    k++;
                }
                else
                {
                    {
                        new_arr[index] = left_arr[j];
                        index++;
                        j++;
                    }
                }            
            }
            // store the remaining elements in one of the sides into new_array
            if (j == left)
            {
                for (; k < right; k++, index++)
                {
                    new_arr[index] = right_arr[k];
                }
            }
            else
            {
                for (; j < left; j++, index++)
                {
                    new_arr[index] = left_arr[j];
                }
            }                
        }               
    }     
    free (left_arr);
    free (right_arr);     
    return new_arr;     
}
