#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "signals.h"
#include "constants.h"

static void handlesig(int signum);

void setsighandling(void){
	signal(SIGFPE , handlesig);
	signal(SIGILL , handlesig);
	signal(SIGSEGV, handlesig);
	signal(SIGBUS , handlesig);
	signal(SIGABRT, handlesig);
	signal(SIGHUP , handlesig);
	signal(SIGINT , handlesig);
  //signal(SIGQUIT, handlesig);
	signal(SIGTERM, handlesig);
  //signal(SIGKILL, handlesig);
	signal(SIGCHLD, handlesig);
}

static void handlesig(int signum){
	fflush(stdin);
	fflush(stdout);
	fflush(stderr);
	if(debug){
		fprintf(stderr, "\nhandlesig invoked with ");
		fprintf(stderr, "\033[1m");
	}
	switch(signum){
		case SIGFPE:  if(debug){ fprintf(stderr, "SIGFPE" ); } break;
		case SIGILL:  if(debug){ fprintf(stderr, "SIGILL" ); } break;
		case SIGSEGV: if(debug){ fprintf(stderr, "SIGSEGV"); } break;
		case SIGBUS:  if(debug){ fprintf(stderr, "SIGBUS" ); } break;
		case SIGABRT: if(debug){ fprintf(stderr, "SIGABRT"); } break;
		case SIGHUP:  if(debug){ fprintf(stderr, "SIGHUP" ); } break;
		case SIGINT:  if(debug){ fprintf(stderr, "SIGINT" ); } break;
		case SIGTERM: if(debug){ fprintf(stderr, "SIGTERM"); } break;
		case SIGCHLD: if(debug){ fprintf(stderr, "SIGCHLD"); } break;
		default:      if(debug){ fprintf(stderr, "an unrecognized signal");} break;
	}
	if(debug){ fprintf(stderr, "\033[m.\n"); } else { fprintf(stderr, "\n"); }
	exit(EXIT_SUCCESS);
}
