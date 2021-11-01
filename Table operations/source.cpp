//Rafal Szychowski
#include <iostream>
//11 3 dla 12 elementow


int main(){


    int session;
    std::cin >> session;


    while(session > 0){         //Main loop

        int the_array[200000] = {0};  //Array initialization - whole array is set to 0s
        int array_length;
        std::cin >> array_length;
        {int i = 0;

        while(i < array_length){    //Saving numbers to the array

            std::cin >> the_array[i];

            i++;
        }}

        {int i = 0;
        while(i < array_length){
            std::cout << the_array[i] << " ";
            i++;
        }
        std::cout << "\n";
        }

        char operation = '\0';
        std::cin >> operation;

        while(operation != 'F'){    //Loop to execute operations on array

            if(operation == 'R'){

                int given_index;
                std::cin >> given_index;

                int reversing_length;
                std::cin >> reversing_length;


                int starting_index;

                if(given_index >= 0){       //calculating real starting index as the array is looped

                    starting_index = given_index % array_length;
                } else {

                    starting_index = (array_length + (given_index % array_length)) % array_length;
                };

                int fragment_number;
                if(reversing_length == 0) fragment_number = 0;
                else fragment_number = array_length / reversing_length;

                {int i = 0;

                while(i < fragment_number){

                    int j = 0;
                    int index = (starting_index + (i * reversing_length)) % array_length;
                    int fragment_start = (starting_index + (i * reversing_length)) % array_length;

                    while(j < (reversing_length / 2)){

                        int second_index;

                        second_index = (fragment_start - j - 1 + reversing_length) % array_length;

                        //std::cout << "index \tsecond index\ti\tj\n" << index << "\t" << second_index << "\t" << i << "\t" << j << "\n";

                        int tmp = the_array[index];
                        the_array[index] = the_array[second_index];
                        the_array[second_index] = tmp;
                        j++;
                        index += 1;
                        index = index % array_length;
                    }
                    i++;
                }}
            }


            else if(operation == 'C'){


                int given_index;
                std::cin >> given_index;

                int shift_length;               //length of array fragment being shifted
                std::cin >> shift_length;

                int shift_amount;               //how much the fragment is being shifted
                std::cin >> shift_amount;

                if(shift_length > 0 && array_length > 1 && shift_length > 1){


                int shift_amount_absolute;                                          //holding absolute value of shift_amount
                if(shift_amount < 0) shift_amount_absolute = shift_amount * (-1);
                else shift_amount_absolute = shift_amount;

                int direction;                              //which way the loop goes
                if(shift_amount < 0) direction = -1;
                else direction = 1;

                if(shift_length > array_length) shift_length = array_length;



                int starting_index;

                if(given_index >= 0){       //calculating real starting index as the array is looped

                    starting_index = given_index % array_length;
                } else {

                    starting_index = (array_length + (given_index % array_length)) % array_length;
                };

                int fragment_number = array_length / shift_length;

                bool shorter_fragment_exist = false;                            //if there is remaining fragment shorter than shifting length

                if(array_length % shift_length != 0)  shorter_fragment_exist = true;
                int last_index = 0;


            {
            int i = 0;
            while(i < fragment_number){

                int index = (starting_index + (i * shift_length)) % array_length;

                //std::cout << "\ni: " << i << "\n";

                int j = 0;
                while(j < shift_amount_absolute){


                    index = (starting_index + (i * shift_length)) % array_length;
                    int fragment_start = (starting_index + (i * shift_length)) % array_length;
                    int tmp = the_array[index];

                    int k = 0;
                    int next_index;

                    while(k < shift_length - 1){

                        //std::cout << "\tindex: " << index << "\tdirection: " << direction << "\tfragment start: " << fragment_start << "\n";

                        if(direction > 0){
                            if(index - direction < 0){                                  // o o | | | X    X-target index o-current fragment |-other fragment
                                if(fragment_start + shift_length >= array_length){
                                    next_index = array_length - 1;
                                    //std::cout << "\nWybor 0\n";
                                }
                                else{                                                   // o o X | | |
                                    next_index = fragment_start + shift_length - 1;
                                    //std::cout << "\nWybor 1\n";
                                }

                            }
                            else if(index - direction == 0){
                                if(index - direction < fragment_start && fragment_start + shift_length < array_length){   // | o o X | |
                                    next_index = fragment_start + shift_length - 1;
                                    //std::cout << "\nWybor 2\n";

                                }
                                else{                                                   // X o o | | |
                                    next_index = index - direction;
                                    //std::cout << "\nWybor 3\n";

                                }
                            }
                            else if(index - direction > 0){
                                if(index - direction < fragment_start && (fragment_start + shift_length) % array_length < fragment_start &&    // o X | | | o   X | | | o o
                                    index - direction > (fragment_start + shift_length) % array_length){
                                    next_index = (fragment_start + shift_length - 1) % array_length;
                                    //std::cout << "\nWybor 4\n";
                                }
                                else if(index - direction >= fragment_start && index - direction < (fragment_start + shift_length) % array_length && // | | | X o o  | | | o X o
                                         (fragment_start + shift_length) % array_length > fragment_start){
                                    next_index = index - direction;
                                    //std::cout << "\nWybor 5\n";
                                }
                                else if(shift_length == array_length){          //no short fragments, whole array is one fragment
                                    next_index = index - direction;
                                    //std::cout << "\nWybor 5A\n";
                                }
                                else if(index - direction == fragment_start){           // | X o o | |
                                    next_index = index - direction;
                                    //std::cout << "\nWybor 6\n";
                                }
                                else if(index - direction < fragment_start && fragment_start + shift_length - 1 <= array_length){
                                    next_index = fragment_start + shift_length - 1;
                                    //std::cout << "\nWybor 6AA\n";
                                }
                                else{
                                    next_index = index - direction;
                                    //std::cout << "\nWybor 7\n";
                                }
                            }
                        }

                        else if(direction < 0){
                            if(index - direction >= array_length){           // | | | X o o   X o o o o o
                                if(fragment_start + shift_length > array_length){    // X o | | | o
                                    next_index = 0;
                                    //std::cout << "\nWybor 8\n";
                                }
                                else{
                                    next_index = fragment_start;
                                    //std::cout << "\nWybor 8AAA\n";
                                }
                            }
                            else if(index - direction > fragment_start + shift_length - 1){     // | X o o | |
                                next_index = fragment_start;
                                //std::cout << "\nWybor 9\n";
                            }
                            else if(index - direction > (fragment_start + shift_length) % array_length && index - direction < fragment_start){    // o | | | X o
                                next_index = fragment_start;
                                //std::cout << "\nWybor 10\n";
                            }
                            else {
                                next_index = index - direction;
                                //std::cout << "\nWybor 11\n";
                            }
                        }

                        //std::cout << "\nindex: " << index << "\tnext index: " << next_index << "\n";

                        {int y = 0;
                        while(y < array_length){
                            //std::cout << the_array[y] << " ";
                            y++;
                        }}

                        //std::cout << "\n";

                        the_array[index] = the_array[next_index];

                        k++;
                        index = next_index;
                        last_index = index;


                        {int y = 0;
                        while(y < array_length){
                            //std::cout << the_array[y] << " ";
                            y++;
                        }}

                        if(k + 1 == shift_length) index = next_index;

                        //std::cout << "\n-----------------------------------------------\n\n";
                    }

                    //std::cout << "\nKONIEC\nindex: " << index << "\n";

                    the_array[next_index] = tmp;


                    j++;
                }

                i++;
            }
            }

            //std::cout << "\n\n\n KONIEC DLUGICH FRAGMENTOW\n\n---------------------------------------------\n\n";


           if(shorter_fragment_exist && array_length - (fragment_number * shift_length) > 1){

                int short_starting_index = (starting_index + (fragment_number * shift_length)) % array_length;
                int shorter_fragment_length = (array_length - (fragment_number * shift_length));
                int fragment_start = short_starting_index;

                //std::cout << "\nshort fragment length: " << shorter_fragment_length << "\tfragment number: " << fragment_number << "\n";

                int i = 0;
                int index = short_starting_index;

                while(i < shift_amount_absolute){

                    int tmp = the_array[short_starting_index];
                    int next_index;
                    int j = 0;
                    index = short_starting_index;

                    while(j < shorter_fragment_length - 1){


                        if(direction > 0){
                            if(index - direction < 0){                                  // o o | | | X    X-target index o-current fragment |-other fragment
                                if(fragment_start + shorter_fragment_length >= array_length){
                                    next_index = array_length - 1;
                                    //std::cout << "\nWybor 0\n";
                                }
                                else{                                                   // o o X | | |
                                    next_index = fragment_start + shorter_fragment_length - 1;
                                    //std::cout << "\nWybor 1\n";
                                }

                            }
                            else if(index - direction == 0){
                                if(index - direction < fragment_start && fragment_start + shorter_fragment_length < array_length){   // | o o X | |
                                    next_index = fragment_start + shorter_fragment_length - 1;
                                    //std::cout << "\nWybor 2\n";

                                }
                                else{                                                   // X o o | | |
                                    next_index = index - direction;
                                    //std::cout << "\nWybor 3\n";

                                }
                            }
                            else if(index - direction > 0){
                                if(index - direction < fragment_start && (fragment_start + shorter_fragment_length) % array_length < fragment_start &&    // | | o o X |   | | | o o X
                                    index - direction > (fragment_start + shorter_fragment_length) % array_length){
                                    next_index = (fragment_start + shorter_fragment_length - 1) % array_length;
                                    //std::cout << "\nWybor 4\n";
                                }
                                else if(index - direction >= fragment_start && index - direction < (fragment_start + shorter_fragment_length) % array_length && // | | | X o o  | | | o X o
                                         (fragment_start + shorter_fragment_length) % array_length > fragment_start){
                                    next_index = index - direction;
                                    //std::cout << "\nWybor 5\n";
                                }
                                else if(index - direction <= fragment_start){
                                    next_index = fragment_start + shorter_fragment_length - 1;
                                    //std::cout << "\nWybor 6\n";
                                }
                                else{
                                next_index = index - direction;
                                //std::cout << "\nWybor 7\n";
                                }
                            }
                        }

                        else if(direction < 0){
                            if(index - direction >= array_length){           // | | | X o o   X o o o o o
                                if(fragment_start + shorter_fragment_length > array_length){    // X o | | | o
                                    next_index = 0;
                                    //std::cout << "\nWybor 8\n";
                                }
                                else{
                                    next_index = fragment_start;
                                    //std::cout << "\nWybor 8AAA\n";
                                }
                            }
                            else if(index - direction > fragment_start + shorter_fragment_length - 1){     // | X o o | |
                                next_index = fragment_start;
                                //std::cout << "\nWybor 9\n";
                            }
                            else if(index - direction > (fragment_start + shorter_fragment_length) % array_length && index - direction < fragment_start){    // o | | | X o
                                next_index = fragment_start;
                                //std::cout << "\nWybor 10\n";
                            }
                            else {
                                next_index = index - direction;
                                //std::cout << "\nWybor 11\n";
                            }
                        }

                        //std::cout << "\nindex: " << index << "\tnext index: " << next_index << "\n";

                        {int y = 0;
                        while(y < array_length){
                            //td::cout << the_array[y] << " ";
                            y++;
                        }}

                        //std::cout << "\n";

                        the_array[index] = the_array[next_index];

                        index = next_index;
                        last_index = index;


                        {int y = 0;
                        while(y < array_length){
                            //std::cout << the_array[y] << " ";
                            y++;
                        }}

                        //std::cout << "\n-----------------------------------------------\n\n";
                        j++;
                    }

                the_array[next_index] = tmp;
                i++;

                }
            }
            }
            }


            else if(operation == 'S'){

            int given_index;
            std::cin >> given_index;

            int swap_length;               //length of array fragment being shifted
            std::cin >> swap_length;

            int starting_index;

            if(given_index >= 0){       //calculating real starting index as the array is looped

                starting_index = given_index % array_length;
            } else {

                starting_index = (array_length + (given_index % array_length)) % array_length;
            };

            int swap_pairs;
            if(swap_length == 0) swap_pairs = 0;
            else if (swap_length > array_length) {
                    swap_length = array_length;
                    swap_pairs = (array_length / swap_length) / 2;}
            else swap_pairs = (array_length / swap_length) / 2;


            {
            int i = 0;

            while(i < swap_pairs){

                int index = ((starting_index + ((i * 2 * swap_length))) % array_length);
                int j = 0;

                int next_index;

                while(j < swap_length){

                    next_index = (index + swap_length) % array_length;
                    int tmp = the_array[index];

                    //std::cout << "\narray[index]: " << the_array[index] << "\tarray[next_index]: " << the_array[next_index] << "\n";
                    //std::cout << "index: " << index << "\tnext index: " << next_index << "\n";

                    the_array[index] = the_array[next_index];
                    the_array[next_index] = tmp;

                    j++;
                    index = (index + 1) % array_length;
                }
                //std::cout << "\nkoniec petli j\n\n";
                i++;
            }
            }

            }


            std::cin >> operation;
        }
        {int i = 0;
        //std::cout << "\n";
        while(i < array_length){
            std::cout << the_array[i] << " ";
            i++;
        }
        std::cout << "\n";
        }

        session--;
    }


}
