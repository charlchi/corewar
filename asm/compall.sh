for file in `ls ../champs/*.s | sort -V`
#for file in `ls examples/*.s | sort -V`
do
  echo $file
  ./asm "$file"
done
