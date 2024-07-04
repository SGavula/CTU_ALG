#!/bin/sh

g++ main.cpp -o hw01;

# Test01 Mandatory
./hw01 < datapub/pub01.in > datapub/my-pub01.out;
diff datapub/pub01.out datapub/my-pub01.out;

# Test02 Mandatory
./hw01 < datapub/pub02.in > datapub/my-pub02.out;
diff datapub/pub02.out datapub/my-pub02.out;

# Test03 Mandatory
./hw01 < datapub/pub03.in > datapub/my-pub03.out;
diff datapub/pub03.out datapub/my-pub03.out;

# Test04 Mandatory
./hw01 < datapub/pub04.in > datapub/my-pub04.out;
diff datapub/pub04.out datapub/my-pub04.out;

# # Test05 Mandatory
./hw01 < datapub/pub05.in > datapub/my-pub05.out;
diff datapub/pub05.out datapub/my-pub05.out;

# Test06 Mandatory
./hw01 < datapub/pub06.in > datapub/my-pub06.out;
diff datapub/pub06.out datapub/my-pub06.out;
