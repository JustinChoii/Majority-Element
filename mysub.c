// CS 111 - Project 2
// Spring 2018

// Brayan Gallardo - 67982922
// Justin Choi - 40532889

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*  
    QCOUNT returns:
    0 = Even - two 1's and two 0's
    2 = Three of one, one of the other
    4 = All 4 are the same

    
    mysub(int n):
    int n = number of values in the range of 10 to 10000
    
    mysub(int n) returns:
        0 when there is no majority and there is an even number of marbles for each.
        an index from range 1 - n of a majority marble element
        -1 when there is an error

*/


int mysub(int n){
    int qcountResult;


    int A_Index = 0;        // multiple indices to keep track of 0s and 1s.
    int A2_Index = 0;
    int A3_Index = 0;
    int A4_Index = 0;

    int B_Index = 0;        // multiple indices to keep track of 1s and 0s
    int B2_Index = 0;
    int B3_Index = 0;
    
    int A_Counter = 0;      // counter to keep track of A and B marbles
    int B_Counter = 0;

    bool indices_known = false;     // true when ready to increment by 2

    int index = 4;                  // Currently on index 4. After the first run, we will be on index 5. 
    int run = 1;

    int myArray[4] = {1, 2, 3, 4};  // Array of the indices to call QCOUNT on.

    int prevResult = QCOUNT(1, myArray);

    // indices_known is true when we have enough information on A and B count
    // Generally we can find indices_known within the first 5 indices, but
    // When there are constant QCOUNT results equal to 4
    
    while (indices_known == false && prevResult >= 0){    
        if (A_Counter > n/2){                       
            return A_Index;                         
        } 
        else if (B_Counter > n/2){
            return B_Index;
        } 

        myArray[0] = index - 3;
        myArray[1] = index - 2;
        myArray[2] = index - 1;
        myArray[3] = index - 0;
        index++;                // index = 1-4 first run, index = 2-5 second run and so forth

        qcountResult = QCOUNT(1, myArray);

        if (run == 1){                      // First run
            if (qcountResult == 4){
                A_Counter = 4;
                A_Index = 1;
                A2_Index = 2;
                A3_Index = 3;
                A4_Index = 4;
            }
            else if (qcountResult == 2){    // Do nothing because we don't know what is 0 and what is 1.
                                            // We don't need to keep track of the counter because we can update it in second round.

            }
            else if (qcountResult == 0){    // 0 means equal number of A and B within the first four indices
                A_Counter = 2;
                B_Counter = 2;

            }
            else{
                printf("Error! line 92 \n");
                return -1;
            }

            prevResult = QCOUNT(1, myArray);// Save the result, so we can use it as reference to find discrepancies. 
            run += 1;                       // Now second run. We don't want to go back into this if statement anymore.
            
        }

        else {                                              // run >= 2
            if (prevResult == 4 && qcountResult == 4){      // Consecutive A values
                A_Counter += 1;                             // A_Counter = 5
                                                            // Can be stuck long enough to return majority without going into to other conditions
            }                                               // Ex.) Stuck until B or until majority.
                                                            //      A A A A A A A A A A A A A B

            
            else if (prevResult == 2 && qcountResult == 4){ 
                B_Index = 1;                        // If qcount = 2, and then 4, then A_Count
                A_Index = 2;                        // There is a discrepancy. Only 1 B in index 1. 
                A2_Index = 3;                       // There are 3 A and then another A in the next index.
                A3_Index = 4;                       // B A A A A
                A4_Index = 5;
                B_Counter = 1;
                A_Counter = 4;
                indices_known = true;
                
            }

            else if (prevResult == 4 && qcountResult == 2){ 
                                                    // If qcount = 4 and then 2, then B_Count += 1;            
                                                    // There is a discrepancy of 1, so the last index in myArray is a B if all the other values are A
                B_Counter = 1;                      // B_Counter = 1
                B_Index = index - 1;                // B_Index = index - 1 because there could have been many consecutive values of A
                A_Index = 1;                        // A_Index = 1 
                A2_Index = 2;                       // A A A A B
                A3_Index = 3;
                A4_Index = 4;
                indices_known = true;
            } 

            
            // Need to test: 2 -> 0, 0 -> 0, and 0 -> 2
            // 4 -> 0 and 0 -> 4 are impossible. 

            // Testing 2 -> 0
            else if (prevResult == 2 && qcountResult == 0){
                // If first result == 2, and the second result == 0, then we know that there is
                // at least one discrepancy change. This means that index 1 and 5 are different.

                A_Index = 1;
                B_Index = 5;

                // Again, we need to test the middle three elements.

                myArray[0] = A_Index;
                myArray[1] = 3;
                myArray[2] = 4;
                myArray[3] = B_Index;
                qcountResult = QCOUNT(1, myArray);

                // QCOUNT = 4 is impossible so we don't test it.

                if (qcountResult == 0){
                    // 0 x x x 1
                    //     ^ ^ are being tested
                    // This is not enough information because we don't know what is what
                    // Same as earlier, make another array and test the opposite two.
                    // This time, because we know A and B are indices 1 and 5, we can test it much easier.

                    myArray[0] = A_Index;
                    myArray[1] = 2;
                    myArray[2] = 3;
                    myArray[3] = B_Index;
                    qcountResult = QCOUNT(1, myArray);

                    if (qcountResult == 0){
                        // Index 2 is the same as index 4 if there is no discrepancy.
                        A_Index = 2;
                        A2_Index = 4;
                        A3_Index = 1;
                        B_Index = 3;
                        B2_Index = 5;
                        A_Counter = 3;
                        B_Counter = 2;
                        indices_known = true;
                        
                    }

                    else if( qcountResult == 2){
                        // Index 2 is different from index 4. There is a discrepancy of 1.

                        A_Index = 2;
                        A2_Index = 3;
                        A3_Index = 1;
                        B_Index = 4;
                        B2_Index = 5;
                        A_Counter = 3;
                        B_Counter = 2;
                        indices_known = true;
                    }

                }
                else if (qcountResult == 2){
                    // 0 . x x 1
                    // 3 and 4 are the same value 
                    // index 2 must be B
                    B_Index = 2;
                    B2_Index = 2;
                    A_Index = 3;
                    A2_Index = 4;
                    A3_Index = 1;
                    A_Counter = 3;
                    B_Counter = 2;
                    indices_known = true;      

                }
                else{
                    printf("Error!    line 210 \n");
                    return -1;
                }
            }

            else if (prevResult == 2 && qcountResult == 2){ 
                // If qcount = 2, and then 2, then 2 -> 2
                // We know that 2 -> 2 means that myArray[0] == myArray[5] because no change.
                // Because we know no values changed, so index 1 and 5 have to be the same if we pop out 1 and insert index 5 into myArray.
                // Theoretical example: 0, 0, 1, 0 is the first 4. next value is a 0.
                // Known = A, x, x, x, B
                // We need to test to figure out the middle 3.
                // We can make a new array to test the middle 3.
                // We start with the left two indices, and if we get enough information, we don't need to find index 4.
                // If we need more information, we'll need to make a new array to test the right two of the middle 3 indices. 
                // Once we get this information, we can iterate through the rest of the n-5 indices until we have an answer!


                A_Index = 1;
                A2_Index = 5;   

                // Now we check the left 2 elements
                myArray[0] = 1;
                myArray[1] = 2;
                myArray[2] = 3;
                myArray[3] = 5;
                qcountResult = QCOUNT(1, myArray);
                if (qcountResult == 4){
                    // If all four of these values are A, then we know that index 4 is B.
                    B_Counter = 1;
                    A_Counter = 4;
                    B_Index = 4;
                    A_Index = 1;
                    A2_Index = 2;
                    A3_Index = 3;
                    A4_Index = 5;
                    indices_known = true;
                    
                }


                else if (qcountResult == 0){
                    // We are testing 0, x, x, x, 0
                    //                ^  ^  ^     ^
                    // If qcount == 0, then that means the values are 0, 1, 1, 1, 0
                    // 0, 1, 1, 1 returns 2 because there are three 1s, and one 0.
                    // 1, 1, 1, 0 returns 2 ebcause there are three 1s and one 0.
                    // if we test the left 2 of the middle three indices, and qcount == 0, then we know
                    // that the middle three indices are all 1.

                    // qcountResult == 0 means the indices were 0, 1, 1, 0
                    // myArray indices:1, 2, 3, 5
                    B_Counter = 3;
                    A_Counter = 2;

                    A_Index = 1;
                    A2_Index = 5;

                    B_Index = 4;
                    B2_Index = 3;
                    B3_Index = 2;

                    indices_known = true;
                    

                }
                else if (qcountResult == 2){
                    // qcount == 2 doesn't give us enough information so we need to test for the 4th index.
                    // We test for the 4th index by testing the right two elements.
                    // We could check 2 and 4, but it's easier to visualize if we test for the right two of the middle three indices.
                    myArray[0] = A_Index;
                    myArray[1] = 3;
                    myArray[2] = 4;
                    myArray[3] = A2_Index;

                    qcountResult = QCOUNT(1, myArray);


                    if (qcountResult == 4){
                        // We know index 2 is B
                        B_Index = 2;
                        B_Counter = 1;
                        A_Counter = 4;
                        A2_Index = 3;
                        A3_Index = 4;
                        A4_Index = 5;
                        indices_known = true;
                        

                    }
                    else if (qcountResult == 2){
                        // If still a 2, then we know that there is no dicrepancy change.
                        // Thus, the middle index (3) must be B.
                        B_Counter = 1;
                        A_Counter = 4;
                        B_Index = 3;
                        A2_Index = 2;
                        A3_Index = 4;
                        A4_Index = 5;
                        indices_known = true;
                        

                    }
                    else if (qcountResult == 0){
                        // Impossible???
                        // I think impossisble if the first two runs resulted in 2
                        // 0 x x x 0
                        //     ^ ^ we test these
                        // If this results in 0, then 3rd and 4th index = 1
                        // This means that the first iteration would've been equal to 0 instead of 2, so impossible.


                    }
                    else{
                        printf("Error! line 324 \n");
                        return -1;
                    }

                }
                else{
                    printf("Error! line 330 \n");
                    return -1;
                }


            }
            // Testing 0 -> 0


            else if (prevResult == 0 && qcountResult == 0){
                // If there is no discrepancy change, that means 1 and 5 are the same.
                A_Index = 1;
                A2_Index = 5;

                // Now we must check the middle three elements again.

                myArray[0] = A_Index;
                myArray[1] = 3;
                myArray[2] = 4;
                myArray[3] = A2_Index;  
                qcountResult = QCOUNT(1, myArray);  

                // 4 is impossible so we only test QCOUNT == 0 and 2

                if (qcountResult == 0){
                    // We know that there was a minimum of 2 A's in the first 5 elements.
                    // QCOUNT == 0 means that index 2 and 3 must be A.
                    // B x x x B
                    //     ^ ^

                    // B A A x B
                    // But we tested earlier for the first four, that there is 2 A and 2 B
                    // This means that 
                    // B A A x B
                    //       ^ must be B, so there are 3  and 2 A
                    // Second run
                    // B x x x B

                    A_Counter = 2;
                    B_Counter = 3;

                    A_Index = 3;
                    A2_Index = 4;
                    A3_Index = 4;
                    B_Index = 2;
                    B2_Index = 2;
                    indices_known = true;

                }   

                else if (qcountResult == 2){
                    // B x x x B
                    //     ^ ^
                    // QCOUNT == 2 meaning 3 B and 1 A.
                    // Not enough information for us, so we must check for the right two of the middle 3.
                    // B x x x B
                    //   ^ ^ 

                    myArray[0] = A_Index;
                    myArray[1] = 2;
                    myArray[2] = 3;
                    myArray[3] = A2_Index;  
                    qcountResult = QCOUNT(1, myArray);
                    // Impossible for it to equal 4 so we only test for 2 and 0

                    if (qcountResult == 2){
                        // B x x x B
                        //   ^ ^
                        // Testing for the first 2 gave us QCOUNT == 2, meaning that there are 3 B and 1 A
                        // B = 3, A = 2 AND 4
                        A_Counter = 2;
                        B_Counter = 3;

                        A_Index = 2;
                        A2_Index = 4;
                        A3_Index = 4;
                        B_Index = 3;
                        B2_Index = 3;
                        indices_known = true;
                        

                    }   
                    else if (qcountResult == 0){
                        // B x x x B
                        //   ^ ^
                        // If there is a discrepancy change, that means index 2 and 4 are different.
                        // This means 2 and 3 are A
                        A_Counter = 2;
                        B_Counter = 3;

                        A_Index = 2;
                        A2_Index = 3;
                        A3_Index = 3;
                        B_Index = 4;
                        B2_Index = 3;
                        indices_known = true;

                    }
                    else{
                        printf("Error!   line 429 \n");
                        return -1;
                    }

                }   
                else{
                    printf("Error!   line 435 \n");
                    return -1;
                }

            }

            else if (prevResult == 0 && qcountResult == 2){
                // Since there is a discrepancy change, we know that 1 and 5 are different.
                // A x x x B
                //   ^ ^ ^
                // There must be at least 1 A and 1 B in index 2 and 3.
                // If the discrepancy changes to 2, then index 4 must be A or B.
                // We need to figure out exactly which is which
                // We know 1 and 5 are A and B, so we test the left two given our known parameters.
                A_Index = 1;
                B_Index = 5;
                myArray[0] = A_Index;
                myArray[1] = 3;
                myArray[2] = 4;
                myArray[3] = B_Index;   
                qcountResult = QCOUNT(1, myArray);
                // qcount can't equal 4

                if (qcountResult == 2){
                    // A x x x B
                    //     ^ ^
                    // If this results in 2, then we know that the second index must be B, because there is no discrepancy change. 
                    // We now that ther are 3 A in the bag, so if QCOUNT = 2, then the second index must be B.

                    A_Index = 3;
                    B_Index = 2;
                    A2_Index = 4;
                    B2_Index = 5;
                    A_Counter = 3;
                    B_Counter = 2;
                    indices_known = true;
                    

                }
                else if (qcountResult == 0){
                    // Must test the opposite two indices and their marbles.
                    A_Index = 1;
                    B_Index = 5;

                    myArray[0] = A_Index;
                    myArray[1] = 2;
                    myArray[2] = 3;
                    myArray[3] = B_Index;   
                    qcountResult = QCOUNT(1, myArray);

                    // can't be 4

                    if (qcountResult == 2){
                        // We know that 4 and 5 are B since there is a discrepency change.
                        A_Counter = 3;
                        B_Counter = 2;  

                        A_Index = 2;
                        A2_Index = 3;

                        B_Index = 4;
                        B2_Index = 4;
                        B3_Index = 4;

                        indices_known = true;                     


                    }
                    else if (qcountResult == 0){
                        // we know that 3 and 5 are the same since there was no discrepency change.
                        A_Counter = 3;
                        B_Counter = 2; 


                        A_Index = 2;
                        A2_Index = 4;

                        B_Index = 3;
                        B2_Index = 3;
                        B3_Index = 5;
 
                        indices_known = true;                  

                    }
                    else {
                        printf("Error!   line 520  \n");
                        return -1;
                    }
                }
                else {
                    printf("Error!   line 525   \n");
                    return -1;
                }

            }

            else{
                printf("Error!   line 532   \n");
                return -1;
            }
            prevResult = QCOUNT(1, myArray);;
            run += 1;
        }
    }


    // Begin iterating by 2 for n/2 QCOUNT calls.

    while (index < n){
        // We need to test for majority so we don't check for every element.
        // If a majority was found earlier, we can stop checking.

        if (A_Counter > n/2){
            return A_Index;
        }
        else if (B_Counter > n/2){
            return B_Index;
        }

        // We can iterate by 2 because we now know the first 5 elements.
        // We can test using the first two values as A.
        // Doing this, ensures that every time we test two new values, we know exactly what they are.
        // If QCOUNT == 0, then both the values are different.
        //      B + 2
        // If QCOUNT == 4, then w e know the same two values have been seen.
        //      A + 2
        // If QCOUNT == 2, then only one of the values are different.
        //      A + 1, B + 1


        myArray[0] = A_Index;
        myArray[1] = A2_Index;
        myArray[2] = index; 
        myArray[3] = index + 1;
        index += 2;


        qcountResult = QCOUNT(1, myArray);
        if (qcountResult == 0){
            B_Counter += 2;
        }

        else if (qcountResult == 2){
            A_Counter += 1;
            B_Counter += 1;
        }

        else if (qcountResult == 4){
            A_Counter += 2;
        }

        else{
            printf("Error! line 587 \n");
            return -1;
        }

        if (index == n){
            // We only need to check the last element. Because we kept track of the previous indices, we only need to 
            // test once. We use A for the first two and B for the last one to make it easier.

            myArray[0] = A_Index;
            myArray[1] = A2_Index;
            myArray[2] = B_Index;
            myArray[3] = index; 

            qcountResult = QCOUNT(1, myArray);
            if (qcountResult == 2){
                A_Counter += 1;
            }
            if (qcountResult == 0){
                B_Counter += 1;
            }
        }

    }


    // index should now be at the last value. We iterated by 2 starting at an odd index, so if 
    // n is an even number, we need to do one last comparison.
    // if n is an odd number, we don't need to do this last comparison.

    

    // We are done, and now we test to find majority.
    if (A_Counter >  B_Counter){
        return A_Index;
    }
    else if (B_Counter > A_Counter){
        return B_Index;
    }
    else if (A_Counter == B_Counter){
        return 0;
    }
    else{
        printf("error! line 629");    
        return -1;
    }
}