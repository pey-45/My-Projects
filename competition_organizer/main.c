#include "operations.h"
#define MAX_PARAM 100

void fixStrError(char str[MAX_PARAM])
{
    if (str[strlen(str)-1]=='\n')
        str[strlen(str)-1] = '\0';
}

void processCommand (char command, tListJ *L)
{
    char param1[MAX_PARAM], param2[MAX_PARAM], param3[MAX_PARAM];

    switch (command)
    {
        case 'C':
            printf("Operation: Create\n\n");

            printf("Jury name:");
            fgets(param1, MAX_PARAM, stdin);
            printf("Jury's total voters:");
            fgets(param2, MAX_PARAM, stdin);

            fixStrError(param1);
            fixStrError(param2);

            Create(param1, param2, L);

            break;

        case 'N':
            printf("Operation: New\n\n");

            printf("Jury name:");
            fgets(param1, MAX_PARAM, stdin);
            printf("Participant name:");
            fgets(param2, MAX_PARAM, stdin);
            printf("EU participant [eu/non-eu]:");
            fgets(param3, MAX_PARAM, stdin);

            fixStrError(param1);
            fixStrError(param2);
            fixStrError(param3);

            New(param1, param2, param3, L);

            break;

        case 'V':
            printf("Operation: Vote\n\n");

            printf("Jury name:");
            fgets(param1, MAX_PARAM, stdin);
            printf("Participant name:");
            fgets(param2, MAX_PARAM, stdin);

            fixStrError(param1);
            fixStrError(param2);

            Vote(param1, param2, L);

            break;

        case 'D':
            printf("Operation: Disqualify\n\n");

            printf("Participant name:");
            fgets(param1, MAX_PARAM, stdin);

            fixStrError(param1);

            Disqualify(param1, L);

            break;

        case 'R':
            printf("Operation: Remove\n\n");

            Remove(L);

            break;

        case 'S':
            printf("Operation: Stats\n\n");

            Stats(L);

            break;

        case 'W':
            printf("Operation: Winners\n\n");

            Winners(L);

            break;

        default:
            break;
    }
}

int main()
{
    char command = '.';
    tListJ *L = malloc(sizeof(tListJ));
    createEmptyListJ(L);
    char aux;

    while (command != 'E')
    {
        printf("********************\nSelect an option:\n\t(C)reate\n\t(N)ew\n\t(V)ote\n\t(D)isqualify\n\t(R)emove\n\t(S)tats\n\t(W)inners\n\t(E)xit\n\n");
        scanf(" %c", &command);
        scanf("%c", &aux);
        processCommand(command, L);
    }

    return 0;
}