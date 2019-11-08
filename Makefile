CFLAGS += -g    
Read:   Read.o MFRC522.o spi.o gpio.o
        $(CC) $(CFLAGS) -o $@ Read.o MFRC522.o spi.o gpio.o

Read.o: Read.c
        $(CC) $(CFLAGS) -c $< -o $@
    
MFRC522.o:      MFRC522.c
        $(CC) $(CFLAGS) -c $< -o $@
    
spi.o:  spi.c
        $(CC) $(CFLAGS) -c $< -o $@
        
gpio.o: gpio.c
        $(CC) $(CFLAGS) -c $< -o $@
            
clean:      
        rm -f *.o Read
