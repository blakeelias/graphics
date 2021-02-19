#include "globals.h"
#include "signals.h"

#include <signal.h>
#include <stdlib.h>

static void signals_handle(int signum);

void signals_set_handlers(void){
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
	if(debug){
		fprintf(stderr, "\nsignals_handle invoked with ");
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
