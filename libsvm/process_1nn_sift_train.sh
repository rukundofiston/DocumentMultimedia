#!/bin/bash

for f in /home/m/mulhemp/sift/train/*.sift
do
  if [ ! -e train/1nn/`basename $f` ]; then
    sed -n '4,$p' $f | tr -d ";" | sed 's/<CIRCLE [1-9].*> //' > ./trav.sift
    R --slave --no-save --no-restore --no-environ --args centers256.txt 256 ./trav.sift ./res.sift < libsvm/1nn.R
    mv ./res.sift train/1nn/`basename $f`
  fi
done

\rm -f ./trav.sift ./res.sift