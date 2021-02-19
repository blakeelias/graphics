#!/usr/bin/php
<?php
	$srcdir = "src/";
	$hdrdir = "hdr/";
	$objdir = "obj/";
?>
THISFILE=<?php echo "{$argv[1]}\n"; ?>
SRCDIR=<?php echo "$srcdir\n"; ?>
HDRDIR=<?php echo "$hdrdir\n"; ?>
OBJDIR=<?php echo "$objdir\n"; ?>
OBJS=<?php
	$specs = fopen("make/{$argv[1]}.specs", "r");
	$first = 1;
	while($line = fgets($specs)){
		if($first != 1){
			echo " ";
		}
		$first = 0;
		preg_match("/^(\w*)( (.*))?\n\$/", $line, $matches);
		$file = $matches[1];
		echo "\$(OBJDIR)$file.o";
	}
	echo "\n";
	fclose($specs);
?>

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

<?php
	$specs = fopen("make/{$argv[1]}.specs", "r");
	while($line = fgets($specs)){
		preg_match("/^(\w*)( (.*))?\n\$/", $line, $matches);
		$file = $matches[1];
		if(isset($matches[3])){
			$options = " " . $matches[3];
		} else {
			$options = "";
		}
		//echo "$file, $options\n";
		/*$srcfile = fopen("$srcdir$file.c", "r");
		$hdrdeps = "";
		while($srcline = fgets($srcfile)){
			if(preg_match("/^([ \t]*)#include([ \t]*)\"(.*?)\"/", $srcline, $srcmatches)){
				//echo "$srcline";
				//echo $srcmatches[1] . "\n";
				$hdrdeps .= "\$(HDRDIR)" . $srcmatches[3] . " ";
			} else {
				//echo "no match.\n";
			}
		}
		fclose($srcfile);*/
		//if($file == "main"){
		//	$verdep = "\$(HDRDIR)ver.h ";
		//} else {
		//	$verdep = "";
		//}
		if(isset($deps)){
			unset($deps);
		}
		echo "\n\$(OBJDIR)";
		exec("gcc -M -I$hdrdir $srcdir$file.c", $deps);
		$firstline = 1;
		foreach($deps as $depline){
			if($firstline){
				$firstline = 0;
			} else {
				echo "\n";
			}
			echo preg_replace("/ hdr\/ver.h/", "", $depline);
			//echo $depline;
		}
		echo " \\\n \$(GLBLDEPS)\n";
		//echo "\$(OBJDIR)$file.o : \$(SRCDIR)$file.c \$(GLBLDEPS)\n\t\$(CC) \$(CCOPTS)$options \\\n\t\$(SRCDIR)$file.c -o \$(OBJDIR)$file.o\n\n";
		echo "\t\$(CC) \$(CCOPTS)$options \\\n\t\$(SRCDIR)$file.c -o \$(OBJDIR)$file.o\n";
	}
	fclose($specs);
	echo "\n";
?>

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


<?php
	/*$srcdirdesc = opendir($srcdir);
	while($srcfilename = readdir($srcdirdesc)){
		if(!preg_match("/^(.*?)\.c\$/", $srcfilename)){
			continue;
		}
		$srcfile = fopen("$srcdir$srcfilename", "r");
		$hdrdeps = "";
		while($srcline = fgets($srcfile)){
			if(preg_match("/^([ \t]*)#include([ \t]*)\"(.*?)\"/", $srcline, $srcmatches)){
				//echo "$srcline";
				//echo $srcmatches[1] . "\n";
				if(strlen($hdrdeps) == 0){
					$hdrdeps = "\$(HDRDIR)" . $srcmatches[3];
				} else {
					$hdrdeps .= " " . "\$(HDRDIR)" . $srcmatches[3];
				}
			} else {
				//echo "no match.\n";
			}
		}
		fclose($srcfile);
		echo "\$(SRCDIR)$srcfilename : $hdrdeps\n\n";
	}
	closedir($srcdirdesc);
	
	
	
	$hdrdirdesc = opendir($hdrdir);
	while($hdrfilename = readdir($hdrdirdesc)){
		if(!preg_match("/^(.*?)\.h\$/", $hdrfilename)){
			continue;
		}
		$hdrfile = fopen("$hdrdir$hdrfilename", "r");
		$hdrdeps = "";
		while($hdrline = fgets($hdrfile)){
			if(preg_match("/^([ \t]*)#include([ \t]*)\"(.*?)\"/", $hdrline, $hdrmatches)){
				//echo "$srcline";
				//echo $srcmatches[1] . "\n";
				if(strlen($hdrdeps) == 0){
					$hdrdeps = "\$(HDRDIR)" . $hdrmatches[3];
				} else {
					$hdrdeps .= " " . "\$(HDRDIR)" . $hdrmatches[3];
				}
			} else {
				//echo "no match.\n";
			}
		}
		fclose($hdrfile);
		echo "\$(HDRDIR)$hdrfilename : $hdrdeps\n\n";
	}
	closedir($hdrdirdesc);*/
?>
