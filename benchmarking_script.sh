# Do chmod +X bechmarking_script.sh after cloning/pulling to make it executable
rm -rf video
mkdir video
make
./ppm
gcc -o dump cpu_json.c
./dump
python postcpuinfo.py
