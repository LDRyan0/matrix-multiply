# script to run everything at once
for d in */ ; do
  (cd "$d" && make)
done

for d in */ ; do 
  ./"${d}matrixMultiply"
done


