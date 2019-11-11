# include	<stdio.h>
# include	<unistd.h>
# include	<inttypes.h>
# include	<string.h>
# include	<stdlib.h>
# include	"MFRC522.h"

int debug = 1;

int
main(int argc, char *argv[])
{
    uint8_t mode, bits;
    int status;
    unsigned char backBits;
    unsigned char *uid;
    unsigned char blockno;
    char *next;

    if (argc == 2)
    {
        blockno = strtoul(argv[1], &next, 0);
	if (next == argv[1] || *next != '\0')
	{
	    fprintf(stderr, "%s: bad block number: \"%s\"\n", argv[0], argv[1]);
	    exit(255);
	}
    }
    else
        blockno = 8;

    MFRC522_Init(0);

    while ((status = MFRC522_Request(PICC_REQIDL, &backBits)) != MI_OK)
        usleep(500);
    // status = MFRC522_Request(PICC_REQIDL, &backBits);

    // If a card is found
    if (status == MI_OK)
	printf("Card detected\n");

    status = MFRC522_Anticoll(&uid);

    if (status == MI_OK)
    {
	unsigned char key[] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF };	// This is the default key for authentication
        // print UID
	printf("%02x %02x %02x %02x\n", uid[0], uid[1], uid[2], uid[3]);

	// Select the scanned tag
	MFRC522_SelectTag(uid);

	status = MFRC522_Auth(PICC_AUTHENT1A, blockno, key, sizeof(key), uid);

	// Check if authenticated
	if (status == MI_OK)
	{
	    // MFRC522_Read(0);
	    MFRC522_Read(blockno);
	    MFRC522_StopCrypto1();
	}
	else
	    fprintf(stderr, "Authentication error");
    }
}
