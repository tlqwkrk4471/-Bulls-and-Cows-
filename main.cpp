#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool opp_win = false;

void judgeNumber1(int my[], int you[])
{
    int strike = 0, ball = 0;
    for(int i = 0; i < 5; i++) {
        if(my[i] == you[i]) strike++;
        else {
            for(int j = 0; j < 5; j++) {
                if(my[i] == you[j]) { ball++; break; }
            }
        }
    }
    if(strike == 0 && ball == 0) printf("OUT\n");
    else if(strike == 5) opp_win = true;
    else printf("%dS %dB\n", strike, ball);
    return;
}

bool judgeNumber2(int my[], int you[], int compare_strike, int compare_ball)
{
    int strike = 0, ball = 0;
    for(int i = 0; i < 5; i++) {
        if(my[i] == you[i]) strike++;
        else {
            for(int j = 0; j < 5; j++) {
                if(my[i] == you[j]) { ball++; break; }
            }
        }
    }
    if(strike == compare_strike && ball == compare_ball) return true;
    else return false;
}

int main()
{
    int aiNumber[5], questionNumber[5], predictNumber[30240][5], initializer_Count = 0, inputNumber[5], candidateNumber = 0;
    int noNumber_address[30240], noNumber_address_Count = 0;
    int strike, ball; //��ǻ�Ͱ� ��� ���� �󸶳� ������� ��밡 �˷��� ��

    //questionNumber ���� �ʱ�ȭ
    printf("LOADING... ");
    for(int i = 0; i < 5; i++) {
        retry1:
        srand(time(NULL)); //���� �ʱ�ȭ
        questionNumber[i] = rand()%10;
        for(int j = 0; j < i; j++) {
            if(questionNumber[i] == questionNumber[j]) goto retry1;
        }
    }
    printf("START!\n");

    //predictionNumber �ʱ�ȭ
    for(int p = 0; p <= 9; p++) {
        for(int q = 0; q <= 9; q++) {
            if(q == p) continue;
            for(int r = 0; r <= 9; r++) {
                if(r == p || r == q) continue;
                for(int s = 0; s <= 9; s++) {
                    if(s == p || s == q || s == r) continue;
                    for(int t = 0; t <= 9; t++) {
                        if(t == p || t == q || t == s || t == r) continue;
                        predictNumber[initializer_Count][0] = p;
                        predictNumber[initializer_Count][1] = q;
                        predictNumber[initializer_Count][2] = r;
                        predictNumber[initializer_Count][3] = s;
                        predictNumber[initializer_Count++][4] = t;
                    }
                }
            }
        }
    }

    //��밡 ����� �ϴ� ��ǻ�� ���� �Է�
    /*printf("Input AI Number: ");
    for(int i = 0; i < 5; i++) scanf("%d", &aiNumber[i]);*/
    for(int i = 0; i < 5; i++) {
        retry:
        srand(time(NULL)); //���� �ʱ�ȭ
        aiNumber[i] = rand()%10;
        for(int j = 0; j < i; j++) {
            if(aiNumber[i] == aiNumber[j]) goto retry;
        }
    }

    while(1) {

        /**��ǻ�� ����**/
        //��ǻ�Ͱ� ��뿡�� ���� ����
        printf("\n�� AI [%d %d %d %d %d]\n", questionNumber[0], questionNumber[1], questionNumber[2], questionNumber[3], questionNumber[4]);
        //��ǻ�Ͱ� ��� ���� �󸶳� ������� ��밡 �˷���
        printf("STRIKE: ");
        scanf("%d", &strike);
        printf("BALL: ");
        scanf("%d", &ball);

        if(strike == 5) {
            printf("�� YOU FAILED!!! ��");
            printf("\nAI Number [%d %d %d %d %d]\n", aiNumber[0], aiNumber[1], aiNumber[2], aiNumber[3], aiNumber[4]);
            return 0;
        }

        candidateNumber = 0;
        //���ǿ� ���缭 ����� �� �Ÿ��� (�ɷ��� ���ڵ� noNumber ���� �ۼ�)
        for(int i = 0; i < 30240; i++) {
            for(int j = 0; j < noNumber_address_Count; j++) {
                if(i == noNumber_address[j]) {candidateNumber++; goto overlap;} //noNumber ���Ͽ� ������ �н�
            }

            //���� question �� prediction ���ؼ� ���� strike, ball ������ �ٸ��� noNumber ���� �߰�
            if(!(judgeNumber2(questionNumber, predictNumber[i], strike, ball))) {noNumber_address[noNumber_address_Count++] = i; candidateNumber++;}
            overlap:;
        }
        printf("Number of Candidate : %d\n", 30240-candidateNumber);
        printf("Winning Rate : %d\n", (30240-candidateNumber)/30240*100);

        //questionNumber ������
        for(int i = 0; i < 30240; i++) {
            for(int j = 0; j < noNumber_address_Count; j++) {
                if(i == noNumber_address[j]) goto there;
            }
            questionNumber[0] = predictNumber[i][0];
            questionNumber[1] = predictNumber[i][1];
            questionNumber[2] = predictNumber[i][2];
            questionNumber[3] = predictNumber[i][3];
            questionNumber[4] = predictNumber[i][4];
            goto exit;
            there:;
        }
        exit:

        /**��� ����**/
        //��밡 ��ǻ�Ϳ��� ���� ����
        printf("\n�� Player: ");
        for(int i = 0; i < 5; i++) scanf("%d", &inputNumber[i]);
        judgeNumber1(aiNumber, inputNumber);

        if(opp_win == true) {
            printf("\n�� YOU WIN!!! ��");
            printf("ai Number [%d %d %d %d %d]\n", aiNumber[0], aiNumber[1], aiNumber[2], aiNumber[3], aiNumber[4]);
            return 0;
        }
    }

    return 0;
}
