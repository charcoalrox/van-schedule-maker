//Houses all of the functions that aren't used to print the schedule for the user


void vanscheduleinit(BuildingsNames buildingsnames[MAX_BUILDINGS], VanSchedule vanschedule[MAX_VANS])
//Imports external files and copies their information into structs for later use in this program
{
    FILE*Buildings;
    Buildings = fopen ("Buildings.txt", "r");
    FILE*Vans;
    Vans = fopen ("Vans.txt", "r");

    if (Buildings != NULL && Vans != NULL)
    {
        for (int i = 0; fscanf(Buildings, "%s %d", buildingsnames[i].building, &buildingsnames[i].buildingid) != EOF; i++);

        for (int j = 0; j < MAX_BUILDINGS; j++) //j represents which buildingsname struct we're currently on
        //converts underscores to spaces so the menus look better to customers
        {
            for (int k = 0; k < 20; k++) //runs through every building name and replaces underscores with spaces
            {
                if (buildingsnames[j].building[k] == '_')
                {
                    buildingsnames[j].building[k] = ' ';
                }
            }
        }
        
        for (int i = 0; fscanf(Vans, "%d,%d,%d,%d,%d,%d,%d,%d", &vanschedule[i].van_id, &vanschedule[i].start_time,
        &vanschedule[i].end_time, &vanschedule[i].stop[0], &vanschedule[i].stop[1], &vanschedule[i].stop[2], &vanschedule[i].stop[3], 
        &vanschedule[i].stop[4]) != EOF; i++);

    }

    if (Buildings == NULL || Vans == NULL)
    {
        printf ("ERROR: Important scheduling data is missing from the root file of the program.\n"
        "Please make sure \"Buildings.txt\" and \"Vans.txt\" are present in order to continue");
        exit(0); //to stop the program from getting stuck in a loop and crashing
    }

    fclose (Buildings);
    fclose (Vans);
}


int uservanscheduler(BuildingsNames buildingsnames[MAX_BUILDINGS], int functionabort, int savecounter, int userinput[5], UserSchedule userschedule[MAX_SAVES], VanSchedule vanschedule[MAX_VANS])
//takes user's information and schedules them the appropriate van
{
    if (savecounter < MAX_SAVES)
    {
        printf ("\n");//A nice, pretty line break going into this funciton
        for (int i = 1; i < MAX_BUILDINGS; i++)
        {
            printf ("%02d %s\n",buildingsnames[i].buildingid , buildingsnames[i].building);
        }
        printf ("\nPlease enter the number of your desired location: ");
        scanf ("%d", &userinput[4]);//I know it's odd saving the first value at 5 but I wanted to keep this funciton consistent with all of the schedule printers

        functionabort = buildingrangevalidity(functionabort, userinput);

        if (functionabort == 0) //code block checks user time input
        {
             printf ("Please enter the hour you wish to make this trip (military time): ");
             scanf ("%d", &userinput[0]);

             if (userinput[0] < 5 || userinput[0] > 17)
             {
                 functionabort = 1;
                 printf ("\n\nSorry. Our vans only run from 5:00 to 17:00\n\n");
             }
             else
             {
                 for (int i = 0; i < MAX_VANS; i++) //scans through all of the vans on schedule to see if any of them are visiting this building at this time
                 {
                     for (int j = 0; j < MAX_VAN_STOPS; j++)
                     {
                         if (userinput[4] == vanschedule[i].stop[j] && userinput[0] == vanschedule[i].start_time + j)
                         {
                             userschedule[savecounter].vanid = vanschedule[i].van_id;
                             i = MAX_VANS;
                             break;
                         }
                     }

                     if (i == MAX_VANS-1) //weirdly written but basically, this spits out an error if the user's time and location don't exist
                     {
                        functionabort = 1;
                        printf ("\n\nUnfortunately no vans are headed to that building at that time.\n\n");
                     }
                 }
             }
             
        }

        if (functionabort == 0) //code block checks user date input
        {
            printf ("Please enter the month and day of this trip(mm/dd): ");
            scanf ("%d/%d", &userinput[2], &userinput[3]);

            functionabort = daterangevalidity(functionabort, userinput);
        }

        if (functionabort == 0) //prints outputted user information if everything is valid
        {
            userschedule[savecounter].buildingid = userinput[4];
            //This spot SHOULD be userschedule.vanid but that's in the second major code block because I couldn't fit it down here.
            userschedule[savecounter].month = userinput[2];
            userschedule[savecounter].day = userinput[3];
            userschedule[savecounter].time = userinput[0];

            printf ("\nVan #%d will pick you up at %d on %d/%d/%s to take you building no. %d\n"
            ,userschedule[savecounter].vanid, userschedule[savecounter].time, userschedule[savecounter].month, userschedule[savecounter].day
            ,build_year, userschedule[savecounter].buildingid);
            
            savecounter++;
        }
    }
    else
    {
        printf ("Sorry. You have reached the maximum amount of trips one user can book at a time.");
    }

    return savecounter;
    
}


void savedscheduleprinter(BuildingsNames buildingsnames[MAX_BUILDINGS], int functionabort, int userinput[5], UserSchedule userschedule[MAX_SAVES])
{
    printf ("Please enter the hour we will be starting this range at (military time): ");
    scanf ("%d", &userinput[0]);

    printf ("Please enter the time you will be stopping at (military time): ");
    scanf ("%d", &userinput[1]);

    functionabort = timerangevalidity(functionabort, userinput);

    if (functionabort == 0) //Code block that checks user date input
    {
         printf ("What month and day would you like to check?(mm/dd): ");
         scanf ("%d/%d", &userinput[2], &userinput[3]);

         functionabort = daterangevalidity(functionabort, userinput);
    }

    if (functionabort == 0)
    {
        for (int i = 0; i < MAX_SAVES; i++) //runs through all of the userschedule structs to print all of their saved buildings within the date and time range.
        {
            if (userschedule[i].month == userinput[2] && userschedule[i].day == userinput[3] 
            && userschedule[i].time >= userinput[0] && userschedule[i].time <= userinput[1]) //checks that our structs fit given parameters
            {
                printf("\n\nVan: %d\n", userschedule[i].vanid);
                printf ("Date: %d/%d/%s\n", userschedule[i].month, userschedule[i].day, build_year);
                printf ("%02d:00        ", userschedule[i].time);
                for (int j = 0; j < MAX_BUILDINGS; j++) //runs through the building strings so we can print a real name instead of just the building number
                {
                    if (buildingsnames[j].buildingid == userschedule[i].buildingid)
                    {
                        printf ("%s\n", buildingsnames[j].building);
                        break;
                    }
                }
            }
        }
    }
    
}


void recieptprinter(int savecounter, char username[], UserSchedule userschedule[MAX_SAVES])
//Prints the user's saved schedule onto an external document so they can remember their trip times
{

    FILE*ScheduledStops;
    ScheduledStops = fopen("ScheduledStops.txt", "w");

    fprintf (ScheduledStops, "%s, Below are your booked stops with Totally Real Van Company\n"
"___________________________________________________________\n", username);

    for (int i = 0; i < savecounter; i++)
    {
        fprintf (ScheduledStops, "van: %d\n"
"date: %d/%d/%s\n"
"%02d:00        building no. %d\n\n", userschedule[i].vanid, userschedule[i].month, userschedule[i].day, build_year, userschedule[i].time, userschedule[i].buildingid);
    }

    fclose(ScheduledStops);
}