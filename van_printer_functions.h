//Stores all off the different functions used to print van schedules for the user


void todaysschedule(BuildingsNames buildingsnames[MAX_BUILDINGS], VanSchedule vanschedule[MAX_VANS])
//triple nested loop to print my schedules. "i" keeps track of van id, "j" keeps schedule position, and "k" converts the building id to a human readable string
{
    for (int i = 0; i<MAX_VANS; i++)
        {
            printf ("\n\nVan: %d\n", vanschedule[i].van_id);
            printf(__DATE__);
            
            for (int j = 0; j<MAX_VAN_STOPS; j++)
            {
                for (int k = 0; k<MAX_BUILDINGS; k++)
                {
                    if (buildingsnames[k].buildingid == vanschedule[i].stop[j])
                    {
                        printf("\n%02d:00        %s", vanschedule[i].start_time+j, buildingsnames[k].building);
                        break;
                    }
                    
                    else
                    {
                        NULL;
                    }
                    
                }
            }
        }
}


void vansbydate(BuildingsNames buildingsnames[MAX_BUILDINGS], int functionabort, int userinput[4], VanSchedule vanschedule[MAX_VANS])
//Allows users to check the vans on specific dates.
//since we weren't told to do any sort of rotation, this is basically here to tell the user what holidays we aren't working.
{
    printf ("Please enter the month and day you would like to check (mm/dd): ");
    scanf ("%d/%d", &userinput[2], &userinput[3]);

    functionabort = daterangevalidity(functionabort, userinput);

    if (functionabort == 0)
    {
        for (int i = 0; i<MAX_VANS; i++)
        {
            printf ("\n\nVan: %d\n", vanschedule[i].van_id);
            printf("%02d  %02d %s" ,userinput[2], userinput[3], build_year);
            
            for (int j = 0; j<MAX_VAN_STOPS; j++)
            {
                for (int k = 0; k<MAX_BUILDINGS; k++)
                {
                    if (buildingsnames[k].buildingid == vanschedule[i].stop[j])
                    {
                        printf("\n%02d:00        %s", vanschedule[i].start_time+j, buildingsnames[k].building);
                        break;
                    }
                    
                    else
                    {
                        NULL;
                    }
                    
                }
            }
        }
    }
    
}


void vansbytime(BuildingsNames buildingsnames[MAX_BUILDINGS], int functionabort, int userinput[2], VanSchedule vanschedule[MAX_VANS])
//takes a time range from the user and only prints vans within those times
{
    printf ("Please enter the hour we will be starting this range at (military time): ");
    scanf ("%d", &userinput[0]);

    printf ("Please enter the time you will be stopping at (military time): ");
    scanf ("%d", &userinput[1]);

    functionabort = timerangevalidity(functionabort, userinput);
    
    if (functionabort == 0) //prints schedules withing range
    {
        for (int i = 0; i<MAX_VANS; i++)
        {
            printf ("\n\nVan: %d\n", vanschedule[i].van_id);
            printf(__DATE__);
            
            for (int j = 0; j<MAX_VAN_STOPS; j++)
            {
                for (int k = 0; k<MAX_BUILDINGS; k++)
                {
                    if (buildingsnames[k].buildingid == vanschedule[i].stop[j] && vanschedule[i].start_time+j >= userinput[0] && vanschedule[i].start_time+j <= userinput[1])
                    {
                        printf("\n%02d:00        %s", vanschedule[i].start_time+j, buildingsnames[k].building);
                        break;
                    }
                    
                    else
                    {
                        NULL;
                    }
                    
                }
            }
        }
    }
}


void vansbydateandtime(BuildingsNames buildingsnames[MAX_BUILDINGS], int functionabort, int userinput[4], VanSchedule vanschedule[MAX_VANS])
{
    printf ("Please enter the hour we will be starting this range at (military time): ");
    scanf ("%d", &userinput[0]);

    printf ("Please enter the time you will be stopping at (military time): ");
    scanf ("%d", &userinput[1]);

    functionabort = timerangevalidity(functionabort, userinput);

    if (functionabort == 0)
    {
        printf ("Please enter the month and day you would like to check (mm/dd): ");
        scanf ("%d/%d", &userinput[2], &userinput[3]);

        functionabort = daterangevalidity(functionabort, userinput);
    }

    if (functionabort == 0) //prints schedules within date and time range
    {
        for (int i = 0; i < MAX_VANS; i++)
        {
            printf ("\n\nVan: %d\n", vanschedule[i].van_id);
            printf("%02d  %02d %s" ,userinput[2], userinput[3], build_year);
            
            for (int j = 0; j < MAX_VAN_STOPS; j++)
            {
                for (int k = 0; k < MAX_BUILDINGS; k++)
                {
                    if (buildingsnames[k].buildingid == vanschedule[i].stop[j] && vanschedule[i].start_time+j >= userinput[0] && vanschedule[i].start_time+j <= userinput[1])
                    {
                        printf("\n%02d:00        %s", vanschedule[i].start_time+j, buildingsnames[k].building);
                        break;
                    }
                }
            }
        }
    }  
}