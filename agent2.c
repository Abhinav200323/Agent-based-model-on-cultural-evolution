#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define POPULATION_SIZE 100 // population size
#define GRID_SIZE 10

typedef struct {
    int x;
    int y;
    int religious_beliefs;
    int language1;
    int language2;
    int economic_situation;
    int thinking;
    int age_group;
} Agent;

//  religion[]={"Hinduism","sikhism","Islam","Christianity","jainism","Buddhism"} is represented by [0,1,2,3,4,5]
 //languages[]={"Hindi", "Bengali", "Telugu", "Marathi", "Tamil", "Urdu", "Gujarati", "Kannada", "Odia", "Malayalam","Punjabi","English","sinhala"} is represented by [0,1,2,3,4,5,6,7,8,9,10,11,12]
 // economic[]={"lower class","lower-middle class","middle class","upper middle class","upper class"} is represented by [0,1,2,3,4]
 //Thinking[]={"modern","traditional"}; is represented by [0,1]
 //age-group[]={"0-10","11-16","17-22","22-28","29+"} is represented by [0,1,2,3,4]

void initialize_agents(Agent agents[]);
void move_agents(Agent agents[]);
void update_traits(Agent agents[]);
void print_grid(Agent agents[]);

void initialize_agents(Agent agents[]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        agents[i].x = rand() % GRID_SIZE;
        agents[i].y = rand() % GRID_SIZE;
        agents[i].religious_beliefs = rand() % 6; 
        agents[i].language2 = rand() % 13;
        agents[i].economic_situation = rand() % 5; 
        agents[i].thinking = rand() % 2; 
        agents[i].age_group = rand() % 5;      
    switch(agents[i].religious_beliefs) {
            case 0:
                agents[i].language1 = 0;
                break;
            case 1:
                agents[i].language1= 10;
                break;
            case 2:
                agents[i].language1 = 5;
                break;
            case 3:
                agents[i].language1 = 11;
                break;
            case 4:
                agents[i].language1 = 6;
                break;
            case 5:
                agents[i].language1 = 12;
                break;
            default:
                agents[i].language1 = 0; 
                break;
        }
}
}

void move_agents(Agent agents[]) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        // Select a random agent for interaction
        int agent_index = rand() % POPULATION_SIZE;
        int dx = rand() % 3 - 1;
        int dy = rand() % 3 - 1;
        agents[agent_index].x = (agents[agent_index].x + dx + GRID_SIZE) % GRID_SIZE;
        agents[agent_index].y = (agents[agent_index].y + dy + GRID_SIZE) % GRID_SIZE;
    }
}


void update_traits(Agent agents[]) {
    // Define the influence percentages based on different factors
    float language_influence = 0.15;  // 15% influence based on language
    float age_group_influence = 0.1; // 10% influence based on age group
    float thinking_influence = 0.1;  // 10% influence based on thinking style
    float economic_influence = 0.25; // 25% influence based on economic condition

    for (int i = 0; i < POPULATION_SIZE; i++) {
        // Determine the chance of influence based on language
        float language_chance = 0.0;
        if (agents[i].language1 != agents[i].language2) {
            language_chance = language_influence;
        }

        // Determine the chance of influence based on age group
        float age_group_chance = 0.0;
        if (agents[i].age_group == 0) { //age group 0-10
            age_group_chance = age_group_influence - 0.13;
        }else if(agents[i].age_group == 1){//age group 10-16
            age_group_chance = age_group_influence - 0.1;
        }else if(agents[i].age_group == 2){//age group 17-22
            age_group_chance = age_group_influence + 0.1;
        }else if(agents[i].age_group == 3){//age group 22-28
            age_group_chance = age_group_influence ;
        }else if(agents[i].age_group == 4){//age group 29+
            age_group_chance = age_group_influence - 0.2;
        }

        // Determine the chance of influence based on thinking style
        float thinking_chance = (agents[i].thinking == 0) ? thinking_influence : 0.0;

        // Determine the chance of influence based on economic condition
        float economic_chance = 0.0;
        if (agents[i].economic_situation == 0) { // Consider lower class for influence
            economic_chance = economic_influence+0.1;
        }else if(agents[i].economic_situation == 0){// Consider lower- middle class for influence
            economic_chance = economic_influence;
        }else if(agents[i].economic_situation == 0){// Consider  middle class for influence
            economic_chance = economic_influence -0.5;
        }else if(agents[i].economic_situation == 0){// Consider upper middle class for influence
            economic_chance = economic_influence -0.1;
        }else if(agents[i].economic_situation == 0){// Consider  upper class for influence
            economic_chance = 0;
        }

        // Calculate total chance of influence
        float total_chance = language_chance + age_group_chance + thinking_chance + economic_chance;
        // Apply influence if there's a chance
        if (total_chance > 0.0) {
        // Check if language2 of agent i is same as language1 of agent i+1
      if (agents[i].language2 == agents[i + 1].language1) {
        // Generate a random number to determine if influence occurs
        float rand_val = (float)rand() / RAND_MAX;
        if (rand_val < total_chance) {
            // Exchange the religious beliefs between agents i and i+1
            int temp = agents[i].religious_beliefs;
            agents[i].religious_beliefs = agents[i + 1].religious_beliefs;
            agents[i + 1].religious_beliefs = temp;
        }
    }
}

    }
}


void print_agents_csv(Agent agents[], int timestep, const char* filename) {
    FILE *fp = fopen(filename, "w");
    if (fp != NULL) {
        // Print headers
        fprintf(fp, "Agent,X,Y,Religious Beliefs,Language1,Language2,Economic Situation,Thinking,Age Group\n");
        
        // Print data
        for (int i = 0; i < POPULATION_SIZE; i++) {
            fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n", 
                    i + 1, 
                    agents[i].x, 
                    agents[i].y, 
                    agents[i].religious_beliefs, 
                    agents[i].language1, 
                    agents[i].language2, 
                    agents[i].economic_situation, 
                    agents[i].thinking, 
                    agents[i].age_group);
        }
        
        fclose(fp);
        printf("Agents printed to %s\n", filename);
    } else {
        printf("Error opening file.\n");
    }
}

int main() {
    srand(time(NULL));

    Agent agents[POPULATION_SIZE];

    initialize_agents(agents);

    printf("Initial Data:\n");
    print_agents_csv(agents, 0, "initial_agents.csv");

    // Run simulation steps
    for (int t = 0; t < 10; t++) {
        move_agents(agents);
        update_traits(agents);
    }

    printf("Final Data:\n");
    print_agents_csv(agents, 10, "final_agents.csv");

    return 0;
}