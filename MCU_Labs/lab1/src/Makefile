FAMILY=-mpic14
MCU=-p12f683
CC=sdcc
LD=sdcc
# direccion local
CFLAGS=-I. -I/home/markos/Documentos/MCU/Software-PIC/sdcc-4.0.0/share/sdcc/non-free/include
# direccion default
#CFLAGS=-I. -I/usr/local/share/sdcc/non-free/include
TARGET=bingo

SRCS = bingo.c

all:
	${CC} --use-non-free ${FAMILY} ${MCU} ${CFLAGS} -o ${TARGET} ${SRCS}
#	${LD} -o ${TARGET}.elf ${TARGET}.o
#	${OBJCOPY} -j .text -j .data -O ihex ${TARGET}.o ${TARGET}.hex
#	${SIZE} -C --mcu=${MCU} ${TARGET}.elf

clean:
	rm -f *.c~ *.h~ *.o *.elf *.hex *.asm
