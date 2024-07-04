#!/bin/sh

g++ main.cpp -o hw01;

# Test01 Mandatory
./hw01 < datapub/pub01.in > datapub/my-pub01.out;
diff datapub/pub01.out datapub/my-pub01.out;
#./hw01 < data/pub01.in > data/my-pub01.out 2> my-pub01-o.err;
#diff data/pub01.err my-pub01-o.err;

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

# Test07 Mandatory
./hw01 < datapub/pub07.in > datapub/my-pub07.out;
diff datapub/pub07.out datapub/my-pub07.out;

# Test08 Mandatory
./hw01 < datapub/pub08.in > datapub/my-pub08.out;
diff datapub/pub08.out datapub/my-pub08.out;

# Test09 Mandatory
./hw01 < datapub/pub09.in > datapub/my-pub09.out;
diff datapub/pub09.out datapub/my-pub09.out;

# Test09 Mandatory
./hw01 < datapub/pub10.in > datapub/my-pub10.out;
diff datapub/pub10.out datapub/my-pub10.out;