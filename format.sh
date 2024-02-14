for file in $(find -name '*.c' -o -name '*.h')
do
  # echo "Formatting $file."
  clang-format --style="Chromium" -i $file
done