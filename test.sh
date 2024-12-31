#!/usr/bin/bash

if [ -z $1 ] || [ -z $2 ]
then
  echo "Usage: $0: <NUM_PAGES> <NUM_TRAILS>"
  exit 1
fi

if [ ! -e ./tlb ]
then
  gcc -O0 -g -Wall -W -Wextra -Werror -pedantic tlb.c -o tlb
fi

if [ -e ./tlb_data.bat ]
then
  rm tlb_data.bat parse_tlb_data.bat
fi

NUM_PAGES=$((2**$1))
NUM_TRAILS=$2

echo "Start TLB processing..."

COUNTER=1
while [ ${COUNTER} -le ${NUM_PAGES} ]
do
  ./tlb ${COUNTER} ${NUM_TRAILS} >> tlb_data.bat
  COUNTER=$((COUNTER * 2))
done

echo "Done"

exit 0
