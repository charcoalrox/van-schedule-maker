//checks if the user has input invalid information. Returns an error if they do


int timerangevalidity(int functionabort, int userinput[2])
{
    if (userinput[0] >= userinput[1]) //checks if your hours are invalid. I would have put that at the bottom but !>= was too much for the compiler so it looks ugly now
        {
            printf ("\n\nERROR: given time range is invalid\n\n");
            functionabort = 1;
        }
    else
    {
        functionabort = 0;
    }

    return functionabort;
}


int daterangevalidity(int functionabort, int userinput[4])
{
    if ((userinput[2] == 9 && userinput[3] == 1) || (userinput[2] == 11 && userinput[3] == 11) || (userinput[2] == 11 && userinput[3] == 22) || (userinput[2] == 12 && userinput[3] == 25) //scans the user's input for national holidays
            || userinput[2] > 12 || userinput[3] > 31) //ensures the user's date is real
            {
                printf ("\n\nUnfortunately, our vans will not be operating on this day\n\n");
                functionabort = 1;
            }
    else
    {
        functionabort = 0;
    }

    return functionabort;
}



int buildingrangevalidity(int functionabort, int userinput[5])
{
    if (userinput[4] <= 0 || userinput[4] > MAX_BUILDINGS)//checks if the user has entered a real building
        {
            printf ("\n\nERROR: Entered building is not on our current list\n\n");
            functionabort = 1;
        }
    else
    {
        functionabort = 0;
    }

    return functionabort;   
}