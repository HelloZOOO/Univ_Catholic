#include <stdio.h>

int main(){
    int IncomingData[20] = {7 , 0 , 1 , 2 , 0 , 3 , 0 , 4 , 2 , 3 , 0 , 3 , 2 , 1 , 2 , 0 , 1 , 7 , 0 , 1};

    for(int i=0;i<20;i++)
        scanf("%d", &IncomingData[i]);
    int frame[3];
    int pageFaults = 0;
    bool hereItis = false;
    for (int i = 0; i < 3; i++)
        frame[i] = -1; //! 전부 -1로 초기화
    int where = 0;

    for (int i = 0; i < 20; i++)
    {
        printf("%d\t\t", IncomingData[i]);
        hereItis = false;

        for(int j=0;j<3;j++)
        {
            if(frame[j] == IncomingData[i]) //데이터 n이 i 에있니?
                hereItis = true; //페이지 폴트가 안났다
        }
        
        //!페이지 폴트 발생 되었다면
        if (hereItis == false)
        {
            pageFaults++; //~페이지 폴트 증가
            frame[where] = IncomingData[i];
            where = (where + 1) % 3; // 0 1 2 가 반복되도록 서큘러로 구현
        }

        for (int j = 0; j < 3; j++)
            printf("%d\t", frame[j]);
        printf("\n");
    }
    
    printf("page faults: %d\n", pageFaults);

    return 0;
}