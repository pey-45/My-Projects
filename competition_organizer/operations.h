#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "jury_list.h"

void Create (char *param1, char *param2, tListJ *L)
{
    tItemJ jury;

    strcpy(jury.juryName, param1);
    jury.totalVoters = strtol(param2, NULL, 10);
    createEmptyListP(&jury.participantList);
    jury.nullVotes = 0;
    jury.validVotes = 0;

    if (findItemJ(param1, *L)==NULLJ)
        insertItemJ(jury, L)? printf("* Create: jury %s totalvoters %s\n", param1, param2):printf("+ Error: Create not possible\n");
    else
        printf("+ Error: Create not possible\n");
}

void New (char *param1, char *param2, char *param3, tListJ *L)
{
    tItemP participant;

    strcpy(participant.participantName, param2);
    participant.numVotes = 0;
    participant.EUParticipant = strcmp(param3, "eu")==0? true:false;

    tPosJ jury_pos = findItemJ(param1, *L);

    if (jury_pos!=NULLJ)
    {
        tItemJ jury = getItemJ(jury_pos, *L);

        if (findItemP(param2, jury.participantList)==NULLP)
        {
            insertItemP(participant, &jury.participantList)? printf("* New: jury %s participant %s location %s\n", param1, param2, param3):printf("+ Error: New not possible\n");
            updateItemJ(jury, jury_pos, L);
        }
        else
            printf("+ Error: New not possible\n");
    }
    else
        printf("+ Error: New not possible\n");
}

void Vote (char *param1, char *param2, tListJ *L)
{
    tPosJ jury_pos = findItemJ(param1, *L);

    if (jury_pos!=NULLJ)
    {
        tItemJ jury = getItemJ(jury_pos, *L);
        tPosP participant_pos = findItemP(param2, jury.participantList);

        if (participant_pos!=NULLP)
        {
            tItemP participant = getItemP(participant_pos, jury.participantList);

            ++participant.numVotes;
            updateItemP(participant, participant_pos, &jury.participantList);

            ++jury.validVotes;

            printf("* Vote: jury %s participant %s location %s numvotes %d\n", param1, param2, participant.EUParticipant==true?"eu":"non-eu", participant.numVotes);
        }
        else
        {
            printf("+ Error: Vote not possible. Participant %s not found in jury %s. NULLVOTE\n", param2, param1);
            ++jury.nullVotes;
        }

        updateItemJ(jury, jury_pos, L);
    }
    else
        printf("+ Error: Vote not possible\n");
}

void Disqualify (char *param1, tListJ *L)
{
    tPosJ jury_pos;
    tItemJ jury;
    tPosP participant_pos;
    tItemP participant;

    if (!isEmptyListJ(*L))
    {
        for (jury_pos = firstJ(*L); jury_pos!=NULLJ; jury_pos = nextJ(jury_pos, *L))
        {
            jury = getItemJ(jury_pos, *L);

            printf("Jury %s\n", jury.juryName);

            if (findItemP(param1, jury.participantList)!=NULLP)
            {
                participant_pos = findItemP(param1, jury.participantList);
                participant = getItemP(participant_pos, jury.participantList);

                jury.nullVotes += participant.numVotes;
                jury.validVotes -= participant.numVotes;

                deleteAtPositionP(participant_pos, &jury.participantList);
                updateItemJ(jury, jury_pos, L);

                printf("Participant %s disqualified\n\n", param1);
            }
            else
                printf("No participant %s\n", param1);
        }
    }
    else
        printf("+ Error: Disqualify not possible\n");
}

void Remove (tListJ *L)
{
    tPosJ jury_pos;
    tItemJ jury;

    tListJ LJ = *L;

    if (!isEmptyListJ(*L))
    {
        for (jury_pos = firstJ(*L); jury_pos!=NULLJ; jury_pos = nextJ(jury_pos, *L))
        {
            jury = getItemJ(jury_pos, *L);

            if (jury.validVotes==0)
            {
                deleteAtPositionJ(jury_pos, L);

                jury_pos = previousJ(jury_pos,*L);

                printf("* Remove: jury %s\n", jury.juryName);
            }
        }
        if (&LJ==L)
            printf("+ Error: Remove not possible\n");
    }
    else
        printf("+ Error: Remove not possible\n");
}

void Stats (tListJ *L)
{
    tPosJ jury_pos;
    tItemJ jury;
    tPosP participant_pos;
    tItemP participant;

    if (!isEmptyListJ(*L))
    {
        for (jury_pos = firstJ(*L); jury_pos!=NULLJ; jury_pos = nextJ(jury_pos, *L))
        {
            jury = getItemJ(jury_pos, *L);

            printf("Jury %s:\n", jury.juryName);
            if (!isEmptyListP(jury.participantList))
            {
                for (participant_pos = firstP(jury.participantList); participant_pos!=NULLP; participant_pos = nextP(participant_pos, jury.participantList))
                {
                    participant = getItemP(participant_pos, jury.participantList);

                    printf("  Participant: %s from %s (%d votes, %.2f%c)\n", participant.participantName, participant.EUParticipant==true?"eu":"non-eu", participant.numVotes, (float)jury.validVotes==0? 0:(float)participant.numVotes/(float)jury.validVotes*100, '%');
                }
            }
            else
                printf("  No participants\n");
            printf("Nullvotes: %d\n", jury.nullVotes);
            printf("Participation: %d votes from %d voters (%.2f%c)\n\n", jury.validVotes+jury.nullVotes, jury.totalVoters, (float)(jury.validVotes+jury.nullVotes)/(float)jury.totalVoters*100, '%');
        }
    }
    else
        printf("Error: Stats not possible\n");
}

void Winners (tListJ *L)
{
    tPosJ jury_pos;
    tPosP participant_pos;
    tItemJ jury;
    tItemP participant;
    tItemP winner_eu;
    tItemP winner_non_eu;
    bool empate_eu;
    bool empate_non_eu;

    tNumVotes winner_eu_votes = -1, winner_non_eu_votes = -1;

    if (!isEmptyListJ(*L))
    {
        for (jury_pos = firstJ(*L); jury_pos!=NULLJ; jury_pos = nextJ(jury_pos, *L))
        {
            jury = getItemJ(jury_pos, *L);

            printf("Jury %s:\n", jury.juryName);

            if (!isEmptyListP(jury.participantList))
            {
                for (participant_pos = firstP(jury.participantList); participant_pos!=NULLP; participant_pos = nextP(participant_pos, jury.participantList))
                {
                    participant = getItemP(participant_pos, jury.participantList);

                    if (participant.numVotes==winner_eu_votes && participant.EUParticipant)
                        empate_eu = true;
                    else if (participant.numVotes==winner_non_eu_votes && !participant.EUParticipant)
                        empate_non_eu = true;
                    else
                    {
                        if (participant.numVotes>winner_eu_votes && participant.EUParticipant)
                        {
                            winner_eu = participant;
                            winner_eu_votes = participant.numVotes;
                        }
                        else if (participant.numVotes>winner_non_eu_votes && !participant.EUParticipant)
                        {
                            winner_non_eu = participant;
                            winner_non_eu_votes = participant.numVotes;
                        }
                    }
                }
            }

            winner_eu_votes!=-1 && !empate_eu? printf("  EU winner: %s (%d votes)\n", winner_eu.participantName, winner_eu_votes):printf("  No EU winner\n");
            winner_non_eu_votes!=-1 && !empate_non_eu? printf("  NON-EU winner: %s (%d votes)\n\n", winner_non_eu.participantName, winner_non_eu_votes):printf("  No NON-EU winner\n\n");

            winner_eu_votes = -1;
            winner_non_eu_votes = -1;
        }
    }
    else
        printf("Error: Winners not possible");
}

#endif //OPERATIONS_H