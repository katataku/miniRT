#!/bin/bash

echo "hello"

RT_FILE_DIR=rt_files/ng
FILES=$(ls -r "$RT_FILE_DIR")
for rt_file in $FILES; do
  echo "check $rt_file"
  ./miniRT "$RT_FILE_DIR"/"$rt_file"
done
