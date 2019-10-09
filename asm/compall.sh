for file in `ls ../champs/*.s | sort -V`
do
  echo $file
  ./asm "$file" > asdfasdf.asdfasdf
done
