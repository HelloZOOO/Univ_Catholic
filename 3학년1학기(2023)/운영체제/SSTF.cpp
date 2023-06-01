#include <stdio.h>

//53
//98,183,37,122,14,124,65,67
//53

int main() 
{
    int howmany=8;
    //scanf("%d", &howmany); //~큐 크기 howmany = 8

    int Location[8] = {98,183,37,122,14,124,65,67};
    /*
    for (int i = 0; i < howmany; i++){
        scanf("%d", &Location[i]); //~98,183,37,122,14,124,65,67
    }
    */
    int here = 53;
    //scanf("%d", &here); //~재위치 here = 53

    int soFar = 0;
    int now = 0;

    while(now != howmany)
    {
        int min = 987654321;
        int where;

        for (int i = 0; i < howmany; i++)
        {
            int distance = here - Location[i];
            //if(distance < 0)distance *= -1; //2의보수 = 1의 보수 + i
            if (distance < 0)distance = ~distance + 1;
            if(distance < min)
            {
                min = distance; //65-53=12
                where = i; 
            }
        }
        
        soFar += min;
        here = Location[where];
        Location[where] = 987654321;
        now++;
    }

    printf("총 이동 거리 : %d\n", soFar); //총 이동 거리

    return 0;
}