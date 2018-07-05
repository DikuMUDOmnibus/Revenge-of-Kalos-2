CC      = gcc
PROF    =
NOCRYPT =
C_FLAGS = -O -Wall -g -ggdb -Dlinux $(PROF) $(NOCRYPT)
L_FLAGS = -O -lcrypt $(PROF) -lz

O_FILES = act_comm.o act_info.o act_move.o act_obj.o act_wiz.o comm.o const.o \
          db.o fight.o handler.o interp.o magic.o save.o special.o update.o \
          kav_info.o kav_fight.o kav_wiz.o clan.o  mage.o rot_wiz.o \
          demon.o drow.o wizutil.o ninja.o paladin.o vic.o monk.o arcane.o \
          xk_act.o angel.o xkilla.o xk_wiz.o alien.o board.o shatan.o \
	  bit.o olc.o olc_act.o olc_save.o tables.o mem.o free.o string.o \
          lookup.o mccp.o cheers.o hydra.o alias.o quest.o arena.o \
          auction.o vampire.o illusion.o 

 
RoK: $(O_FILES)
	rm -f RoK
	$(CC) $(L_FLAGS) -o RoK $(O_FILES)
#	$(CC) -E -MM *.c -I. > .depend
#############################################
# Uncomment top line only if you ned to add
# more dependencies (ie add more C files)

act_comm.o: act_comm.c merc.h player.h old.h
act_info.o: act_info.c merc.h player.h old.h
act_move.o: act_move.c merc.h player.h old.h
act_obj.o: act_obj.c merc.h player.h old.h
act_wiz.o: act_wiz.c merc.h player.h old.h
alias.o: alias.c include.h
alien.h.o: alien.h
alien.o: alien.c merc.h player.h old.h
arena.o: arena.c merc.h player.h 
board.o: board.c merc.h player.h old.h board.h
board.o.h: board.h
clan.o: clan.c merc.h player.h old.h
comm.o: comm.c merc.h player.h old.h
const.o: const.c merc.h player.h old.h
db.o: db.c merc.h player.h old.h
demon.o: demon.c merc.h player.h old.h
drow.o: drow.c merc.h player.h old.h drow.h
xk_act.o: xk_act.c merc.h player.h old.h
fight.o: fight.c merc.h player.h old.h
handler.o: handler.c merc.h player.h old.h
hunt.o: hunt.c merc.h player.h old.h
interp.o: interp.c merc.h player.h old.h
kav_fight.o: kav_fight.c merc.h player.h old.h
kav_info.o: kav_info.c merc.h player.h old.h
kav_wiz.o: kav_wiz.c merc.h player.h old.h
mage.o: mage.c merc.h player.h old.h
magic.o: magic.c merc.h player.h old.h
mccp.o: mccp.c merc.h player.h old.h telnet.h
merc.h.o: merc.h player.h old.h
monk.o: monk.c merc.h player.h old.h
ninja.o: ninja.c merc.h player.h old.h
old.h.o: old.h
paladin.o: paladin.c merc.h player.h old.h
player.h.o: player.h
rot_wiz.o: rot_wiz.c merc.h player.h old.h
rotain.o: rotain.c merc.h player.h old.h
save.o: save.c merc.h player.h old.h
special.o: special.c merc.h player.h old.h
telnet.h.o: telnet.h
update.o: update.c merc.h player.h old.h
vic.o: vic.c merc.h player.h old.h
wizutil.o: wizutil.c merc.h player.h old.h
xkilla.o: xkilla.c merc.h player.h old.h
arcane.o: arcane.c merc.h player.h old.h
hydra.o: hydra.c merc.h player.h old.h
xk_wiz.o: xk_wiz.c merc.h player.h old.h
include.h.o: include.h
quest.o: quest.c include.h
mob_commands.o: mob_commands.c merc.h
mob_prog.o: mob_prog.c merc.h
auction.o: auction.c merc.h
shatan.o: shatan.c merc.h player.h old.h
vampire.o: vampire.c merc.h player.h old.h
illusion.o: illusion.c merc.h player.h old.h
