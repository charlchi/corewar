for file in `ls examples/*.s | sort -V`
do
  echo $file
  ./asm "$file" > asdfasdf.asdfasdf
done
