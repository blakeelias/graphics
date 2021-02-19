#include "globals.h"
#include "signals.h"

#include <signal.h>
#include <stdlib.h>

static void signals_handle(int signum);

void signals_init(void){
	signal(SIGFPE , signals_handle);
	signal(SIGILL , signals_handle);
	signal(SIGSEGV, signals_handle);
	signal(SIGBUS , signals_handle);
	signal(SIGABRT, signals_handle);
	signal(SIGHUP , signals_handle);
	signal(SIGINT , signals_handle);
  //signal(SIGQUIT, signals_handle);
	signal(SIGTERM, signals_handle);
  //signal(SIGKILL, signals_handle);
	signal(SIGCHLD, signals_handle);
}

static void signals_handle(int signum){
	fflush(stdin);
	fflush(stdout);
	fflush(stderr);
	if(dodebug(D_SIGNALS)){
		fprintf(stderr, "\n" PROGRAM_NAME " received ");
		fprintf(stderr, "\033[1m");
	}
	switch(signum){
		case SIGFPE:  if(dodebug(D_SIGNALS)){ fprintf(stderr, "SIGFPE" ); } break;
		case SIGILL:  if(dodebug(D_SIGNALS)){ fprintf(stderr, "SIGILL" ); } break;
		case SIGSEGV: if(dodebug(D_SIGNALS)){ fprintf(stderr, "SIGSEGV"); }
			{
				FILE *segf;
				segf = fopen("ver/segfaults.num", "r");
				char segs[16];
				if(!fgets(segs, 16, segf)){
				}
				//debug_w("segs = '%s', segi = %d.", segs, atoi(segs));
				fclose(segf);
				segf = fopen("ver/segfaults.num", "w");
				fprintf(segf, "%d", atoi(segs) + 1);
				fclose(segf);
			}
			break;
		case SIGBUS:  if(dodebug(D_SIGNALS)){ fprintf(stderr, "SIGBUS" ); } break;
		case SIGABRT: if(dodebug(D_SIGNALS)){ fprintf(stderr, "SIGABRT"); } break;
		case SIGHUP:  if(dodebug(D_SIGNALS)){ fprintf(stderr, "SIGHUP" ); } break;
		case SIGINT:  if(dodebug(D_SIGNALS)){ fprintf(stderr, "SIGINT" ); } break;
		case SIGTERM: if(dodebug(D_SIGNALS)){ fprintf(stderr, "SIGTERM"); } break;
		case SIGCHLD: if(dodebug(D_SIGNALS)){ fprintf(stderr, "SIGCHLD"); } break;
		default:      if(dodebug(D_SIGNALS)){ fprintf(stderr, "an unrecognized signal");} break;
	}
	if(dodebug(D_SIGNALS)){ fprintf(stderr, "\033[m.\n"); } else { fprintf(stderr, "\n"); }
	exit(EXIT_SUCCESS);
}
