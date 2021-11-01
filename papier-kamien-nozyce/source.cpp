//Rafal Szychowski

#include <iostream>


int main() {

    int counter = 0, i = 0;
    float a_wins = 0, a_draws = 0, a_lost = 0;      //storing players stats outside of the loop
    float b_wins = 0, b_draws = 0, b_lost = 0;
    float c_wins = 0, c_draws = 0, c_lost = 0;
    float d_wins = 0, d_draws = 0, d_lost = 0;

    std::cin >> counter;

    while(i++ < counter){

        char player_1 = '\0', player_2 = '\0';
        char fig_1 = '\0', fig_2 = '\0';
        unsigned int power_1 = 0, power_2 = 0;
        bool player_1_won = false, player_2_won = false;

        std::cin >> player_1 >> fig_1 >> power_1;
        std::cin >> player_2 >> fig_2 >> power_2;

        if(fig_1 == 'J' && (fig_2 == 'P' || fig_2 == 'S'))  player_1_won = true;        //check if player_1 won
        else if(fig_1 == 'K' && (fig_2 == 'J' || fig_2 == 'N'))  player_1_won = true;
        else if(fig_1 == 'N' && (fig_2 == 'J' || fig_2 == 'P'))  player_1_won = true;
        else if(fig_1 == 'P' && (fig_2 == 'K' || fig_2 == 'S'))  player_1_won = true;
        else if(fig_1 == 'S' && (fig_2 == 'K' || fig_2 == 'N'))  player_1_won = true;

        else if(fig_2 == 'J' && (fig_1 == 'P' || fig_1 == 'S'))  player_2_won = true;   //check if player_2 won
        else if(fig_2 == 'K' && (fig_1 == 'J' || fig_1 == 'N'))  player_2_won = true;
        else if(fig_2 == 'N' && (fig_1 == 'J' || fig_1 == 'P'))  player_2_won = true;
        else if(fig_2 == 'P' && (fig_1 == 'K' || fig_1 == 'S'))  player_2_won = true;
        else if(fig_2 == 'S' && (fig_1 == 'K' || fig_1 == 'N'))  player_2_won = true;

        else if(power_1 > power_2) player_1_won = true;     //players used same figures, checking which won by comparing powers
        else if(power_1 < power_2) player_2_won = true;


        if(player_1_won){

            if(player_1 == 'a') a_wins++;       //adding win to the winner
            else if(player_1 == 'b') b_wins++;
            else if(player_1 == 'c') c_wins++;
            else if(player_1 == 'd') d_wins++;

            if(player_2 == 'a') a_lost++;       //adding lose to the loser
            else if(player_2 == 'b') b_lost++;
            else if(player_2 == 'c') c_lost++;
            else if(player_2 == 'd') d_lost++;
        }

        if(player_2_won){
            if(player_2 == 'a') a_wins++;
            else if(player_2 == 'b') b_wins++;
            else if(player_2 == 'c') c_wins++;
            else if(player_2 == 'd') d_wins++;

            if(player_1 == 'a') a_lost++;
            else if(player_1 == 'b') b_lost++;
            else if(player_1 == 'c') c_lost++;
            else if(player_1 == 'd') d_lost++;
        }


        if(player_1_won == false && player_2_won == false){     //adding draws if neither won
            if(player_1 == 'a') a_draws++;
            else if(player_1 == 'b') b_draws++;
            else if(player_1 == 'c') c_draws++;
            else if(player_1 == 'd') d_draws++;

            if(player_2 == 'a') a_draws++;
            else if(player_2 == 'b') b_draws++;
            else if(player_2 == 'c') c_draws++;
            else if(player_2 == 'd') d_draws++;
        }

    }


    int a_played = a_wins + a_draws + a_lost;   //counting played rounds to each player
    int b_played = b_wins + b_draws + b_lost;
    int c_played = c_wins + c_draws + c_lost;
    int d_played = d_wins + d_draws + d_lost;



    bool printed = false;       //used to adding additional lines if stats of different player were printed in the past

    if(a_played){

        float won_percentage = (a_wins/a_played)*100;
        float lost_percentage = (a_lost/a_played)*100;
        float draw_percentage = (a_draws/a_played)*100;

        std::cout << "gracz a";

        if(a_wins >= 1) std::cout << "\n    wygrane: " << won_percentage << "\%";
        if(a_draws >= 1) std::cout << "\n    remisy: " << draw_percentage << "\%";
        if(a_lost >= 1) std::cout << "\n    przegrane: " << lost_percentage << "\%";

        printed = true;
    }

    if(b_played){

        float won_percentage = (b_wins/b_played)*100;
        float lost_percentage = (b_lost/b_played)*100;
        float draw_percentage = (b_draws/b_played)*100;

        if(printed) std::cout << "\n\n";

        std::cout << "gracz b";

        if(b_wins >= 1) std::cout << "\n    wygrane: " << won_percentage << "\%";
        if(b_draws >= 1) std::cout << "\n    remisy: " << draw_percentage << "\%";
        if(b_lost >= 1) std::cout << "\n    przegrane: " << lost_percentage << "\%";

        printed = true;
    }

    if(c_played){

        float won_percentage = (c_wins/c_played)*100;
        float lost_percentage = (c_lost/c_played)*100;
        float draw_percentage = (c_draws/c_played)*100;

        if(printed) std::cout << "\n\n";

        std::cout << "gracz c";

        if(c_wins >= 1) std::cout << "\n    wygrane: " << won_percentage << "\%";
        if(c_draws >= 1) std::cout << "\n    remisy: " << draw_percentage << "\%";
        if(c_lost >= 1) std::cout << "\n    przegrane: " << lost_percentage << "\%";

        printed = true;
    }

    if(d_played){

        float won_percentage = (d_wins/d_played)*100;
        float lost_percentage = (d_lost/d_played)*100;
        float draw_percentage = (d_draws/d_played)*100;

        if(printed) std::cout << "\n\n";

        std::cout << "gracz d";

        if(d_wins >= 1) std::cout << "\n    wygrane: " << won_percentage << "\%";
        if(d_draws >= 1) std::cout << "\n    remisy: " << draw_percentage << "\%";
        if(d_lost >= 1) std::cout << "\n    przegrane: " << lost_percentage << "\%";

        printed = true;
    }

    return 0;
}
