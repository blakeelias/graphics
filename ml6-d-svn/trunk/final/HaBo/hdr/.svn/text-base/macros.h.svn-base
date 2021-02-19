#ifndef _MACROS_H
#define _MACROS_H

#define SQR(X) (X)*(X)
#define dot(X, Y) X[0]*Y[0] + X[1]*Y[1] + X[2]*Y[2]

#define pixel(X, Y) *((unsigned int *) (pixel_array + (((Y) * pixel_pitch + (X)) << 2)))
#define zbuf(X, Y) *(zbuffer + (Y) * pixel_pitch + (X))

#define intersect(C, P, Q, D) (P[D] + (C - P[0])/(Q[0] - P[0]) * (Q[D] - P[D]))

#define dodebug(KEY) (debugs[D_ALL] || (debugs[D_ANY] && debugs[KEY]))

#define error_n(STR     ) fprintf(stderr, "[%s:%s:%s:%d]: " STR "\n", PROGRAM_NAME, __FILE__, __FUNCTION__, __LINE__             )
#define error_w(STR, ...) fprintf(stderr, "[%s:%s:%s:%d]: " STR "\n", PROGRAM_NAME, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define debug_n(STR     ) if(dodebug(D_ANY)){ error_n(STR             ); }
#define debug_w(STR, ...) if(dodebug(D_ANY)){ error_w(STR, __VA_ARGS__); }
#define d_debug_n(KEY, STR     ) if(dodebug(KEY)){ error_n(STR             ); }
#define d_debug_w(KEY, STR, ...) if(dodebug(KEY)){ error_w(STR, __VA_ARGS__); }

#define var_dump(VAR, TYPE) error_w("%s = " TYPE ".", #VAR, VAR)

#endif
