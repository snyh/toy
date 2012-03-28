OBJECTS :=  keypad.rel tetris.rel lcd.rel

all: $(OBJECTS)
	sdcc $^ -o game.ihx
	@packihx game.ihx > game.hex
	@rm *.rel *.lst *.rst *.ihx  *.lnk *.mem *.sym *.asm *.map

t: t.c
	sdcc  $<
	@packihx t.ihx > t.hex
	@rm *.rel *.lst *.rst *.ihx  *.lnk *.mem *.sym *.asm *.map


%.rel : %.c
	sdcc -c $<

clean:
	@rm *.rel *.lst *.rst *.ihx  *.lnk *.mem *.sym *.asm *.map

test: test.c
	sdcc $<
	packihx test.ihx > game.hex
	@rm *.rel *.lst *.rst *.ihx  *.lnk *.mem *.sym *.asm *.map
	
