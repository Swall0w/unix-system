/* more ver 0.1
 * ファイルを読みだして24行出力したら、一時停止して、次のコマンドを待つ。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more();

int main(int ac, char *av[]){
    FILE *fp;
    if( ac == 1 ){
        do_more( stdin );
    }else{
        while( --ac ){
            if((fp = fopen(*++av, "r")) != NULL){
            // don't use 'r' beacuse it's parsed as int type.
                do_more(fp);
                fclose(fp);
            }else{
                exit(1);
            }
        }
    }
    return  0;
}

void do_more(FILE *fp)
/*
 *  PAGELEN行の情報を読み込み、see_more()を呼び出して命令を待つ。
 */
{
    char    line[LINELEN];
    int     num_of_lines = 0;
    int     see_more(), reply;
    
    while( fgets(line, LINELEN, fp)){   /* 入力がまだある。 */
        if(num_of_lines == PAGELEN){    /* 画面いっぱいに？ */
            reply = see_more();         /* y:指示待ち       */
            if(reply == 0)              /* n:終了           */
                break;
            num_of_lines -= reply;      /* カウンタをリセット*/
        }
        if(fputs(line, stdout) == EOF ) /* 行を表示する     */
            exit(1);                    /* または終了する。 */
        num_of_lines++;
    }
}

int see_more()
/*
 *      メッセージを出力して応答を待つ。先に進める行数を返す。
 *      qならノー、スペースならイエス、CRなら1行
 */
 {
    int    c;
    printf("\033[7m more? \033[m");
    while((c=getchar()) != EOF)
    {
       if(c == 'q')
           return 0;
       if(c == ' ')
           return PAGELEN;
       if(c == '\n')
           return 1;
    }
    return 0;
}
