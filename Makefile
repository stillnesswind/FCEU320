BUILDTARGET = dingux

MINIMAL_DRIVER = 1

CORE_OBJS = \
	src/cart.o src/cheat.o src/config.o src/movie.o src/oldmovie.o \
	src/drawing.o src/fceu.o src/fds.o src/file.o src/conddebug.o \
	src/filter.o src/ines.o src/input.o src/debug.o src/wave.o \
	src/nsf.o src/palette.o src/ppu.o src/sound.o src/state.o src/unif.o \
 	src/video.o src/vsuni.o src/x6502.o src/netplay.o
    
BOARDS_OBJS = \
    src/boards/01-222.o \
    src/boards/103.o \
    src/boards/106.o \
    src/boards/108.o \
    src/boards/112.o \
    src/boards/116.o \
    src/boards/117.o \
    src/boards/120.o \
    src/boards/121.o \
    src/boards/12in1.o \
    src/boards/15.o \
    src/boards/151.o \
    src/boards/156.o \
    src/boards/164.o \
    src/boards/168.o \
    src/boards/17.o \
    src/boards/170.o \
    src/boards/175.o \
    src/boards/176.o \
    src/boards/177.o \
    src/boards/178.o \
    src/boards/179.o \
    src/boards/18.o \
    src/boards/183.o \
    src/boards/185.o \
    src/boards/186.o \
    src/boards/187.o \
    src/boards/189.o \
    src/boards/193.o \
    src/boards/199.o \
    src/boards/208.o \
    src/boards/222.o \
    src/boards/225.o \
    src/boards/228.o \
    src/boards/230.o \
    src/boards/232.o \
    src/boards/234.o \
    src/boards/235.o \
    src/boards/244.o \
    src/boards/246.o \
    src/boards/252.o \
    src/boards/253.o \
    src/boards/28.o \
    src/boards/32.o \
    src/boards/33.o \
    src/boards/34.o \
    src/boards/3d-block.o \
    src/boards/411120-c.o \
    src/boards/43.o \
    src/boards/57.o \
    src/boards/603-5052.o \
    src/boards/68.o \
    src/boards/8157.o \
    src/boards/82.o \
    src/boards/8237.o \
    src/boards/830118C.o \
    src/boards/88.o \
    src/boards/90.o \
    src/boards/91.o \
    src/boards/95.o \
    src/boards/96.o \
    src/boards/99.o \
    src/boards/a9711.o \
    src/boards/a9746.o \
    src/boards/ac-08.o \
    src/boards/addrlatch.o \
    src/boards/ax5705.o \
    src/boards/bandai.o \
    src/boards/bb.o \
    src/boards/bmc13in1jy110.o \
    src/boards/bmc42in1r.o \
    src/boards/bmc64in1nr.o \
    src/boards/bmc70in1.o \
    src/boards/bonza.o \
    src/boards/bs-5.o \
    src/boards/cityfighter.o \
    src/boards/dance2000.o \
    src/boards/datalatch.o \
    src/boards/deirom.o \
    src/boards/dream.o \
    src/boards/edu2000.o \
    src/boards/famicombox.o \
    src/boards/ghostbusters63in1.o \
    src/boards/gs-2004.o \
    src/boards/gs-2013.o \
    src/boards/h2288.o \
    src/boards/karaoke.o \
    src/boards/kof97.o \
    src/boards/konami-qtai.o \
    src/boards/ks7012.o \
    src/boards/ks7013.o \
    src/boards/ks7017.o \
    src/boards/ks7030.o \
    src/boards/ks7031.o \
    src/boards/ks7032.o \
    src/boards/ks7037.o \
    src/boards/ks7057.o \
    src/boards/le05.o \
    src/boards/lh32.o \
    src/boards/lh53.o \
    src/boards/malee.o \
    src/boards/mmc1.o \
    src/boards/mmc3.o \
    src/boards/mmc5.o \
    src/boards/n-c22m.o \
    src/boards/n106.o \
    src/boards/n625092.o \
    src/boards/novel.o \
    src/boards/onebus.o \
    src/boards/pec-586.o \
    src/boards/sa-9602b.o \
    src/boards/sachen.o \
    src/boards/sc-127.o \
    src/boards/sheroes.o \
    src/boards/sl1632.o \
    src/boards/smb2j.o \
    src/boards/subor.o \
    src/boards/super24.o \
    src/boards/supervision.o \
    src/boards/t-227-1.o \
    src/boards/t-262.o \
    src/boards/tengen.o \
    src/boards/tf-1201.o \
    src/boards/transformer.o \
    src/boards/vrc2and4.o \
    src/boards/vrc7.o \
    src/boards/yoko.o \
    src/boards/__dummy_mapper.o

INPUT_OBJS = src/input/arkanoid.o src/input/bworld.o src/input/cursor.o \
	src/input/fkb.o src/input/ftrainer.o src/input/hypershot.o src/input/mahjong.o \
	src/input/mouse.o src/input/oekakids.o src/input/powerpad.o src/input/quiz.o \
	src/input/shadow.o src/input/suborkb.o src/input/toprider.o src/input/zapper.o

MAPPERS_OBJS = \
	src/mappers/24and26.o \
	src/mappers/40.o \
	src/mappers/41.o \
	src/mappers/42.o \
	src/mappers/46.o \
	src/mappers/50.o \
	src/mappers/51.o \
	src/mappers/6.o \
	src/mappers/61.o \
	src/mappers/62.o \
	src/mappers/65.o \
	src/mappers/67.o \
	src/mappers/69.o \
	src/mappers/71.o \
	src/mappers/72.o \
	src/mappers/73.o \
	src/mappers/75.o \
	src/mappers/76.o \
	src/mappers/77.o \
	src/mappers/79.o \
	src/mappers/80.o \
	src/mappers/85.o \
	src/mappers/emu2413.o \
	src/mappers/mmc2and4.o

UTILS_OBJS = src/utils/crc32.o src/utils/endian.o src/utils/general.o \
	src/utils/guid.o src/utils/md5.o src/utils/memory.o src/utils/unzip.o \
	src/utils/xstring.o src/utils/font_zsnes.o
	
COMMON_DRIVER_OBJS = src/drivers/common/args.o src/drivers/common/cheat.o \
	src/drivers/common/config.o src/drivers/common/configSys.o

GUI_OBJS = src/drivers/dingoo/gui/gfceu320.o \
	src/drivers/dingoo/gui/gui.o \
	src/drivers/dingoo/gui/file_list.o \
	src/drivers/dingoo/gui/font.o \
	src/drivers/dingoo/gui/bitmap.o

MINIMAL_OBJS = src/drivers/dingoo/minimal/minimal.o
DRIVER_OBJS = src/drivers/dingoo/config.o src/drivers/dingoo/input.o \
	src/drivers/dingoo/dingoo.o src/drivers/dingoo/dingoo-joystick.o \
	src/drivers/dingoo/dingoo-throttle.o src/drivers/dingoo/dingoo-sound.o \
	src/drivers/dingoo/dingoo-video.o src/drivers/dingoo/dummy-netplay.o \
	$(MINIMAL_OBJS) $(GUI_OBJS)

OBJS = $(CORE_OBJS) $(BOARDS_OBJS) $(INPUT_OBJS) $(MAPPERS_OBJS) $(UTILS_OBJS) \
	$(COMMON_DRIVER_OBJS) $(DRIVER_OBJS)

DINGUX_TOOLCHAIN = mipsel-linux-uclibc-
DINGUX_BASE = /dingux/mipsel-linux-uclibc
CC = $(DINGUX_TOOLCHAIN)gcc
CXX = $(DINGUX_TOOLCHAIN)g++
LD = $(DINGUX_TOOLCHAIN)g++
AS = $(DINGUX_TOOLCHAIN)as
 
CFLAGS = -I$(DINGUX_BASE)/include
CXXFLAGS = -I$(DINGUX_BASE)/include
LDFLAGS = -L$(DINGUX_BASE)/lib

W_OPTS	= -Wno-write-strings -Wno-sign-compare

F_OPTS = -fomit-frame-pointer -fno-builtin -fno-common

CC_OPTS	= -O2 -mips32 $(F_OPTS) $(W_OPTS)

CFLAGS += $(CC_OPTS)
CFLAGS += -DDINGUX -DA320_HARDWARE -I./src \
	  -DLSB_FIRST \
	  -DPSS_STYLE=1 \
	  -DHAVE_ASPRINTF \
	  -DUSE_ZSNES_FONT \
	  -DFRAMESKIP \
	  -DFRACTIONAL_FRAMESKIP \
	  -D_REENTRANT \
	  -DSHOWFPS
CXXFLAGS += $(CFLAGS)
LDFLAGS  += $(CC_OPTS)
LIBS = -lpthread -lz -lm -lstdc++ -lgcov

TARGET = fceu320.dge 

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo Linking $@...
	@echo $(LD) $(LDFLAGS) $(OBJS) -o $@
	$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

%.o: %.c
	@echo Compiling $<...
	$(CC) $(CDEFS) $(CFLAGS) -c $< -o $@

%.o: %.o \
	@echo Compiling $<...
	$(CXX) $(CDEFS) $(CXXFLAGS) -c $< -o $@

%.o: %.s
	@echo Assembling $<...
	$(CXX) $(CDEFS) $(CXXFLAGS) -c $< -o $@

%.o: %.S
	@echo Assembling $<...
	$(CXX) $(CDEFS) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
