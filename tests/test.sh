#!/bin/bash


RT_FILE_DIR=rt_files/ng
FILES=$(ls -r "$RT_FILE_DIR")
for rt_file in $FILES; do
  echo "==========="
  echo "$rt_file"
  valgrind --leak-check=full ./miniRT "$RT_FILE_DIR"/"$rt_file" 2>&1 | grep "definitely lost"
done
