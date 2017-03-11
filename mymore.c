/* more ver 0.1
 * ファイルを読みだして24行出力したら、一時停止して、次のコマンドを待つ。
 */

#include <stdio.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more();

int main(int ac, char *av[]){
    FILE *fp;
    if( ac == 1 )
        do_more( stdin );
    else
        while( --ac )
            if((fp = fopen(*++av, 'r')) != NULL)
            {
                do_more(fp);
                fclose(fp);
            }
            else
                exit(1);
    return  0;
}

void do_more(FILE *fp)
/*
 *  PAGELEN行の情報を読み込み、see_more()を呼び出して命令を待つ。
 */
{
}
