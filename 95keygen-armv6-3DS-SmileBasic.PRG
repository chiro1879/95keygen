' Constants
PAD_LENGTH = 5
MAX_ARR_SIZE = 10000

' Arrays
DIM arr$[0]
arrSize = 0

' Function to pad number with leading zeros
DEF PAD$(num, length)
    stri$ = STR$(num)
    WHILE LEN(stri$) < length
        stri$ = "0" + stri$
    WEND
    RETURN stri$
END

' Function to get a random number between min and max-1
DEF RNDINT(mini, maxi)
    RETURN RND(maxi - mini) + mini
END

' Build valid serial parts
FOR i = 0 to 9999
    numStr$ = PAD$(i, PAD_LENGTH)
    sum = 0
    FOR j = 0 TO 4
        sum = sum + VAL(MID$(numStr$, j+1, 1))
    NEXT
    IF sum MOD 7 == 0 THEN
        PUSH arr$, numStr$
        INC arrSize
    ENDIF
    IF i MOD 100 == 0 THEN
        PRINT "Calculating..."
        PRINT STR$(i * 100 / 10000) + "%"
    ENDIF
NEXT

' Generate parts
one$ = PAD$(RNDINT(1, 366), 3) ' Julian Date
two$ = PAD$(RNDINT(95, 99), 2) ' Year
three$ = arr$[RNDINT(0, arrSize-1)]
four$ = arr$[RNDINT(0, arrSize-1)]

' Construct key
key$ = one$ + two$ + "-OEM-00" + three$ + "-" + four$

' Print the result
PRINT key$
