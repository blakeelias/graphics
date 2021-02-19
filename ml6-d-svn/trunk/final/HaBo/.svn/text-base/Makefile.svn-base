THISFILE=Makefile
SRCDIR=src/
HDRDIR=hdr/
OBJDIR=obj/
OBJS=$(OBJDIR)main.o $(OBJDIR)globals.o $(OBJDIR)screen.o $(OBJDIR)matrix.o $(OBJDIR)line.o $(OBJDIR)signals.o $(OBJDIR)world.o $(OBJDIR)animation.o $(OBJDIR)scene.o $(OBJDIR)objects.o $(OBJDIR)aircraft.o $(OBJDIR)environment.o $(OBJDIR)camera.o $(OBJDIR)stack.o $(OBJDIR)render.o $(OBJDIR)parse.o $(OBJDIR)surface.o

GLBLDEPS=$(THISFILE)

# Additional options:
# For debugging         , add "-ggdb"     to CCOPTS
# For profiling         , add "-pg"       to CCOPTS and LDOPTS
# For optimization      , add "-O[1-3]" and "-finline-functions"
#                                         to BOTHOPTS
# For pain and suffering, add "-pedantic" to CCOPTS

override BOTHOPTS+=# -mtune=native -O6 -finline-functions

CC=gcc
override CCOPTS+=$(BOTHOPTS) -ggdb -Wall -Winline -I$(HDRDIR) -c# -Wextra
#GTKC=`pkg-config --cflags gtk+-2.0`
SDLC=`pkg-config --cflags sdl`

LD=gcc
override LDOPTS+=$(BOTHOPTS) -lm -pthread
#GTKL=`pkg-config --libs   gtk+-2.0`
SDLL=`pkg-config --libs   sdl`

TARGET=habo

all : incmakes $(GLBLDEPS) makever $(TARGET)


$(TARGET) : $(OBJS) $(GLBLDEPS)
	$(LD) $(LDOPTS) $(SDLL) \
	$(OBJS) -o $(TARGET)
	@ver/incbuild
	@ver/makever
	@ver/decmakes


$(OBJDIR)main.o: src/main.c /usr/include/stdio.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/environments.h /usr/include/bits/confname.h \
 /usr/include/getopt.h hdr/globals.h /usr/include/SDL/SDL_keysym.h \
 hdr/matrix.h hdr/macros.h hdr/animation.h /usr/include/xlocale.h \
 hdr/scene.h hdr/objects.h hdr/aircraft.h hdr/globals.h hdr/camera.h \
 hdr/objects.h hdr/signals.h hdr/screen.h hdr/camera.h hdr/scene.h \
 hdr/world.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)main.c -o $(OBJDIR)main.o

$(OBJDIR)globals.o: src/globals.c hdr/globals.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)globals.c -o $(OBJDIR)globals.o

$(OBJDIR)screen.o: src/screen.c /usr/include/stdio.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/environments.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/signal.h /usr/include/bits/signum.h \
 /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
 /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h \
 /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h \
 /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h \
 /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h \
 /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h \
 /usr/include/SDL/SDL_platform.h /usr/include/string.h \
 /usr/include/xlocale.h /usr/include/strings.h /usr/include/inttypes.h \
 /usr/include/stdint.h /usr/include/bits/wchar.h /usr/include/ctype.h \
 /usr/include/iconv.h /usr/include/SDL/begin_code.h \
 /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h \
 /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h \
 /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h \
 /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h \
 /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h \
 /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h \
 /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h \
 /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h \
 /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h \
 /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h \
 hdr/animation.h hdr/scene.h hdr/objects.h hdr/aircraft.h hdr/globals.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/globals.h \
 hdr/render.h hdr/screen.h hdr/camera.h hdr/stack.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) $(SDLC) \
	$(SRCDIR)screen.c -o $(OBJDIR)screen.o

$(OBJDIR)matrix.o: src/matrix.c hdr/globals.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/matrix.h \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/math.h \
 /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h \
 /usr/include/bits/huge_vall.h /usr/include/bits/inf.h \
 /usr/include/bits/nan.h /usr/include/bits/mathdef.h \
 /usr/include/bits/mathcalls.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)matrix.c -o $(OBJDIR)matrix.o

$(OBJDIR)line.o: src/line.c /usr/include/stdio.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
 /usr/include/unistd.h /usr/include/bits/posix_opt.h \
 /usr/include/bits/environments.h /usr/include/bits/confname.h \
 /usr/include/getopt.h /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h hdr/globals.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/line.h \
 hdr/globals.h hdr/screen.h hdr/camera.h hdr/scene.h hdr/objects.h \
 hdr/aircraft.h /usr/include/xlocale.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)line.c -o $(OBJDIR)line.o

$(OBJDIR)signals.o: src/signals.c hdr/globals.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/signals.h \
 /usr/include/signal.h /usr/include/bits/sigset.h \
 /usr/include/bits/signum.h /usr/include/time.h \
 /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
 /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h \
 /usr/include/sys/ucontext.h /usr/include/bits/pthreadtypes.h \
 /usr/include/bits/sigthread.h /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/sys/types.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/alloca.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)signals.c -o $(OBJDIR)signals.o

$(OBJDIR)world.o: src/world.c /usr/include/stdio.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h hdr/globals.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/world.h \
 hdr/objects.h hdr/aircraft.h /usr/include/xlocale.h hdr/globals.h \
 hdr/scene.h hdr/objects.h hdr/parse.h hdr/scene.h hdr/camera.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)world.c -o $(OBJDIR)world.o

$(OBJDIR)animation.o: src/animation.c /usr/include/stdint.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/include/bits/wchar.h /usr/include/time.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/time.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/xlocale.h \
 /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h \
 /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h \
 /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h \
 /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/wchar.h /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/alloca.h \
 /usr/include/string.h /usr/include/strings.h /usr/include/inttypes.h \
 /usr/include/ctype.h /usr/include/iconv.h /usr/include/SDL/begin_code.h \
 /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h \
 /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h \
 /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h \
 /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h \
 /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h \
 /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h \
 /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h \
 /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h \
 /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h \
 /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h \
 hdr/animation.h hdr/scene.h hdr/objects.h hdr/aircraft.h hdr/globals.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/matrix.h \
 hdr/objects.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) $(SDLC) \
	$(SRCDIR)animation.c -o $(OBJDIR)animation.o

$(OBJDIR)scene.o: src/scene.c /usr/include/stdio.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
 /usr/include/signal.h /usr/include/bits/signum.h \
 /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
 /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h \
 /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h hdr/objects.h \
 hdr/aircraft.h /usr/include/xlocale.h hdr/globals.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/scene.h \
 hdr/objects.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)scene.c -o $(OBJDIR)scene.o

$(OBJDIR)objects.o: src/objects.c hdr/aircraft.h /usr/include/time.h \
 /usr/include/features.h /usr/include/bits/predefs.h \
 /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h \
 /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/time.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/xlocale.h hdr/camera.h \
 hdr/scene.h hdr/objects.h hdr/aircraft.h hdr/globals.h \
 /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/wchar.h /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/objects.h \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h \
 /usr/include/alloca.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)objects.c -o $(OBJDIR)objects.o

$(OBJDIR)aircraft.o: src/aircraft.c /usr/include/stdlib.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/sys/types.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/time.h /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h \
 /usr/include/alloca.h /usr/include/math.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h hdr/aircraft.h \
 /usr/include/xlocale.h hdr/environment.h hdr/macros.h hdr/globals.h \
 /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/wchar.h /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)aircraft.c -o $(OBJDIR)aircraft.o

$(OBJDIR)environment.o: src/environment.c hdr/environment.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)environment.c -o $(OBJDIR)environment.o

$(OBJDIR)camera.o: src/camera.c hdr/camera.h hdr/scene.h hdr/objects.h \
 hdr/aircraft.h /usr/include/time.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/time.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/xlocale.h hdr/globals.h \
 /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/wchar.h /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h \
 /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/sys/types.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h \
 /usr/include/alloca.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)camera.c -o $(OBJDIR)camera.o

$(OBJDIR)stack.o: src/stack.c /usr/include/stdio.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 hdr/stack.h /usr/include/stdlib.h /usr/include/bits/waitflags.h \
 /usr/include/bits/waitstatus.h /usr/include/endian.h \
 /usr/include/bits/endian.h /usr/include/bits/byteswap.h \
 /usr/include/sys/types.h /usr/include/time.h /usr/include/sys/select.h \
 /usr/include/bits/select.h /usr/include/bits/sigset.h \
 /usr/include/bits/time.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h hdr/matrix.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)stack.c -o $(OBJDIR)stack.o

$(OBJDIR)render.o: src/render.c /usr/include/math.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h /usr/include/bits/huge_val.h \
 /usr/include/bits/huge_valf.h /usr/include/bits/huge_vall.h \
 /usr/include/bits/inf.h /usr/include/bits/nan.h \
 /usr/include/bits/mathdef.h /usr/include/bits/mathcalls.h hdr/camera.h \
 hdr/scene.h hdr/objects.h hdr/aircraft.h /usr/include/time.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/time.h /usr/include/bits/types.h \
 /usr/include/bits/typesizes.h /usr/include/xlocale.h hdr/globals.h \
 /usr/include/stdio.h /usr/include/libio.h /usr/include/_G_config.h \
 /usr/include/wchar.h /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/line.h \
 hdr/matrix.h hdr/render.h hdr/stack.h /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/sys/types.h \
 /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/sys/sysmacros.h \
 /usr/include/bits/pthreadtypes.h /usr/include/alloca.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)render.c -o $(OBJDIR)render.o

$(OBJDIR)parse.o: src/parse.c /usr/include/stdio.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 /usr/include/string.h /usr/include/xlocale.h /usr/include/stdlib.h \
 /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h \
 /usr/include/endian.h /usr/include/bits/endian.h \
 /usr/include/bits/byteswap.h /usr/include/sys/types.h \
 /usr/include/time.h /usr/include/sys/select.h /usr/include/bits/select.h \
 /usr/include/bits/sigset.h /usr/include/bits/time.h \
 /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h \
 /usr/include/alloca.h /usr/include/signal.h /usr/include/bits/signum.h \
 /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h \
 /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h \
 /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h hdr/globals.h \
 /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h hdr/parse.h \
 hdr/objects.h hdr/aircraft.h hdr/globals.h hdr/objects.h hdr/matrix.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)parse.c -o $(OBJDIR)parse.o

$(OBJDIR)surface.o: src/surface.c /usr/include/stdio.h /usr/include/features.h \
 /usr/include/bits/predefs.h /usr/include/sys/cdefs.h \
 /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h \
 /usr/include/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stddef.h \
 /usr/include/bits/types.h /usr/include/bits/typesizes.h \
 /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
 /usr/lib/gcc/i686-linux-gnu/4.4.5/include/stdarg.h \
 /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h \
 hdr/globals.h /usr/include/SDL/SDL_keysym.h hdr/matrix.h hdr/macros.h \
 hdr/surface.h hdr/line.h hdr/globals.h hdr/matrix.h \
 $(GLBLDEPS)
	$(CC) $(CCOPTS) \
	$(SRCDIR)surface.c -o $(OBJDIR)surface.o


makever :
	@if [ ! -f hdr/ver.h ]; then ver/makever; fi

incmakes :
	@ver/incmakes

force : clean all

clean : $(GLBLDEPS)
	rm -f $(TARGET) $(OBJDIR)*.o `find | grep "~"` hdr/ver.h gmon.out

$(THISFILE) : make/genMakefile.sh make/genMakefile.php make/$(THISFILE).specs
	make/genMakefile.sh $(THISFILE)


ref/disassembled : $(GLBLDEPS)
	objdump -d $(TARGET) > ref/disassembled

ref/profile : $(GLBLDEPS) gmon.out
	gprof $(TARGET) gmon.out > ref/profile


