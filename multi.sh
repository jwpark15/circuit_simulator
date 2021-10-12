echo "========= s27 ========" > outputs.txt;
./simulator circuits/s27.txt 1110101 >> outputs.txt;
./simulator circuits/s27.txt 0001010 >> outputs.txt;
./simulator circuits/s27.txt 1010101 >> outputs.txt;
./simulator circuits/s27.txt 0110111 >> outputs.txt;
./simulator circuits/s27.txt 1010001 >> outputs.txt;

echo "====== s298f_2 =======" >> outputs.txt;
./simulator circuits/s298f_2.txt 10101010101010101 >> outputs.txt 
./simulator circuits/s298f_2.txt 01011110000000111 >> outputs.txt
./simulator circuits/s298f_2.txt 11111000001111000 >> outputs.txt
./simulator circuits/s298f_2.txt 11100001110001100 >> outputs.txt
./simulator circuits/s298f_2.txt 01111011110000000 >> outputs.txt

echo "====== s344f_2 =======" >> outputs.txt;
./simulator circuits/s344f_2.txt 101010101010101011111111 >> outputs.txt
./simulator circuits/s344f_2.txt 010111100000001110000000 >> outputs.txt
./simulator circuits/s344f_2.txt 111110000011110001111111 >> outputs.txt
./simulator circuits/s344f_2.txt 111000011100011000000000 >> outputs.txt
./simulator circuits/s344f_2.txt 011110111100000001111111 >> outputs.txt

echo "====== s349f_2 =======" >> outputs.txt;
./simulator circuits/s349f_2.txt 101010101010101011111111 >> outputs.txt
./simulator circuits/s349f_2.txt 010111100000001110000000 >> outputs.txt
./simulator circuits/s349f_2.txt 111110000011110001111111 >> outputs.txt
./simulator circuits/s349f_2.txt 111000011100011000000000 >> outputs.txt
./simulator circuits/s349f_2.txt 011110111100000001111111 >> outputs.txt


