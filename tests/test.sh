#!/bin/bash

echo "hello"

RT_FILE_DIR=rt_files/ng
FILES=$(ls "$RT_FILE_DIR")
for rt_file in $FILES; do
  ./miniRT "$RT_FILE_DIR"/"$rt_file"
done
