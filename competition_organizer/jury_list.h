#ifndef JURY_LIST_H
#define JURY_LIST_H

#include "participant_list.h"

#define NULLJ (-1)
#define MAX_LIST_LENGTH 10
#define unused __attribute__((unused))

typedef struct tItemJ {
    tJuryName juryName;
    tNumVotes totalVoters;
    tNumVotes validVotes;
    tNumVotes nullVotes;
    tListP participantList;
} tItemJ;

typedef int tPosJ;
typedef struct tListJ
{
    tItemJ ItemJ[MAX_LIST_LENGTH];
    tPosJ LastPos;
} tListJ;

void createEmptyListJ (tListJ* L)
{
    L->LastPos = NULLJ;
}

bool isEmptyListJ (tListJ L)
{
    return L.LastPos==NULLJ;
}

tPosJ firstJ (unused tListJ L)
{
    return 0;
}

tPosJ lastJ (tListJ L)
{
    return L.LastPos;
}

tPosJ nextJ (tPosJ pos, tListJ L)
{
    return pos==L.LastPos? NULLJ:++pos;
}

tPosJ previousJ (tPosJ pos, unused tListJ L)
{
    return --pos;
}

bool insertItemJ (tItemJ item, tListJ* L)
{
    if (L->LastPos==MAX_LIST_LENGTH-1)
        return false;

    ++L->LastPos;

    if (isEmptyListJ(*L) || strcmp(item.juryName, L->ItemJ[lastJ(*L)-1].juryName)>0)
        L->ItemJ[lastJ(*L)] = item;
    else
    {
        tPosJ jury_pos;
        for (jury_pos = lastJ(*L); jury_pos>0 && strcmp(item.juryName, L->ItemJ[jury_pos-1].juryName)<0; --jury_pos)
            L->ItemJ[jury_pos] = L->ItemJ[jury_pos-1];
        L->ItemJ[jury_pos] = item;
    }

    return true;
}

void deleteAtPositionJ (tPosJ pos, tListJ* L)
{
    tPosJ jury_pos;
    for (jury_pos = pos; jury_pos<=L->LastPos; ++jury_pos)
        L->ItemJ[jury_pos] = L->ItemJ[jury_pos+1];

    L->LastPos--;
}

tItemJ getItemJ (tPosJ pos, tListJ L)
{
    return L.ItemJ[pos];
}

void updateItemJ (tItemJ item, tPosJ pos, tListJ* L)
{
    L->ItemJ[pos] = item;
}

tPosJ findItemJ (tJuryName name, tListJ L)
{
    if (isEmptyListJ(L))
        return NULLJ;

    tPosJ jury_pos;
    for (jury_pos = 0; jury_pos<MAX_LIST_LENGTH && strcmp(L.ItemJ[jury_pos].juryName, name)<0 ; ++jury_pos);

    if (strcmp(L.ItemJ[jury_pos].juryName, name)==0)
        return jury_pos;
    else
        return NULLJ;
}


#endif //JURY_LIST_H