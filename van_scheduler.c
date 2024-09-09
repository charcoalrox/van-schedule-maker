//Take user input and make them an itenerary for when they should ride the van

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_BUILDINGS 11 //number of buildings vans are currently stopping at
#define MAX_VANS 5 //number of vans currently on the schedule
#define MAX_VAN_STOPS 5 //number of stops made by each van
#define MAX_SAVES 20 //maximum number of trips someone is allowed to book at once
const char *build_year = __DATE__ + 7; //CREDIT: (https://stackoverflow.com/questions/41898659/extract-only-year-from-date-macro by user "chqrlie"). Checks date so my program still works past 2020

typedef struct //stores building names and id's for use with the VanSchedule struct
{
    char building[30];
    int buildingid;
}BuildingsNames;

typedef struct //Stores van id numbers and schedules
{
    int van_id;
    int start_time;
    int end_time;
    int stop[MAX_VAN_STOPS];
}VanSchedule;

typedef struct //Saves booked trips for the current user
{
    int buildingid;
    int vanid;
    int month;
    int day;
    int time;
}UserSchedule;

#include "parameter_checks.h" //checks for user input errors in the functions
#include "non_printer_functions.h" //contains functions that aren't specifically built for printing the bus schedule
#include "van_printer_functions.h" //all functions required to print the van schedules under option 1 of the first menu


int main()
{
    while(1)//while loop reinitializes everything so user data gets reset every time a new person logs in
    {
        BuildingsNames buildingsnames[MAX_BUILDINGS];
        UserSchedule userschedule[MAX_SAVES];
        VanSchedule vanschedule[MAX_VANS];

        char username[20];
        int userinput[5];
        int functionabort = 0;

        vanscheduleinit(buildingsnames, vanschedule); //prepares the van struct files from the external documents
        system("@cls||clear"); //ensures privacy for any user using this program

        userinput[0] = 0;
        int savecounter = 0; //keeps track of how many trips a user has saved so they don't exceed the maximum alloted amount. Established here so it resets whenever someone logs out

        printf ("\nHello and welcome to Totally Real van Company!\n");
        printf ("Can I please get your username?: ");
        scanf ("%s", username);  

         if (strcmp(username, "systemabort.true") == 0) //terminates the program if a secret developer phrase is entered. Seemed bad not to have any means of terminating the software
         {
             exit(0);
         }

        printf ("Welcome in, %s!\n\n", username);

        while(userinput[0] != 4)
        {
            printf ("\nPlease choose one of the following options\n"
"1. View all van schedules by date and/or time\n"
"2. Input desired times and save your own schedule\n"
"3. View your currently scheduled vans within a set date and time\n"
"4. Log out\n"
"What would you like to do?: ");
            scanf("%d", &userinput[0]);

            switch (userinput[0])
            {
                case 1:
                    
                    while (userinput[0] != 5)
                    {
                        printf ("\n\nHow would you like to search for a schedule?\n"
    "1. Display all vans scheduled for today ("__DATE__")\n"
    "2. Display all vans for a specific date\n"
    "3. Display all vans for a specific time range\n"
    "4. Display all vans for a specific date and time\n"
    "5. Return to previous menu\n"
    "What would you like to do?: ");
                        scanf ("%d", &userinput[0]);
                        switch (userinput[0])
                        {
                            case 1:
                                todaysschedule(buildingsnames, vanschedule);
                                break;
                            case 2:
                                vansbydate(buildingsnames, functionabort, userinput, vanschedule);
                                break;
                            case 3:
                                vansbytime(buildingsnames, functionabort, userinput, vanschedule);
                                break;
                            case 4:
                                vansbydateandtime(buildingsnames, functionabort, userinput, vanschedule);
                                break;
                            case 5:
                                NULL; //This is the case for exiting the loop. It's only typed here so we don't get feedback from default when the user enters "5"
                                break;
                            default:
                                printf ("\n\nERROR: Invalid input. Please try again.\n\n");
                                break;
                        }
                    }
                    
                    break;
                case 2:
                    savecounter = uservanscheduler(buildingsnames, functionabort, savecounter, userinput, userschedule, vanschedule);
                    break;
                case 3:
                    savedscheduleprinter(buildingsnames, functionabort, userinput, userschedule);
                    break;
                case 4:
                    recieptprinter(savecounter, username, userschedule);
                    break;
                default:
                    printf ("\n\nERROR: Invalid input. Please try again.\n\n");
                    break;
            }
        }
    }
    
    return 0;
}