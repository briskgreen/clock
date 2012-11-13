#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
void error_quit(char *msg)
{
	perror(msg);
	exit(1);
}
void *normal_quit(void *win)
{
	while(getchar()!='q')
		continue;
	delwin((WINDOW *)win);
	endwin();
	echo();
	printf("Exit. . .\n");
	printf("\nExit Clock Now. . .\n");
	exit(0);
}
int main(void)
{
	int x,y;
	time_t t;
	char buf[30];
	pthread_t thread;
	WINDOW *win;
	initscr();
	curs_set(0);
	noecho();
	getmaxyx(stdscr,y,x);
	if((win=newwin(5,40,y/2-5/2,x/2-40/2))==NULL)
		error_quit("Create New Window Error!");
	refresh();
	box(win,0,0);
	wrefresh(win);
	getmaxyx(win,y,x);
	if(pthread_create(&thread,NULL,normal_quit,win)==-1)
		error_quit("Create thread Error!");
	while(1)
	{
		t=time(NULL);
		snprintf(buf,strlen(ctime(&t)),"%s",ctime(&t));
		mvwprintw(win,y/2,x/2-(strlen(buf)+1)/2,buf/*ctime(&t)*/);
		//mvwprintw(win,y/2,x-1,"%c",'|');
		wrefresh(win);
		sleep(1);

	}
}
