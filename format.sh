files=$(find -name '*.c' -o -name '*.h')

for file in $files
do
  echo "Formatting $file."
  clang-format --style="Chromium" -i $file
done