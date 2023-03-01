# jpeg-xl_avif_example
Simple example how to save AVIF and JXL images

Required libraries:
* [libaom](https://aomedia.googlesource.com/aom/) - AV1 encoder used by libavif
* [libavif](https://github.com/AOMediaCodec/libavif) - to save AVIF images
* [libjxl](https://github.com/libjxl/libjxl) - to save JXL (JPEG XL) images

How to compile:

`g++ -Wall -Og *.cpp -lavif -ljxl -ljxl_threads -lexiv2 -o example`

Run:
`./example`

The program will generate `output.avif` and `output.jxl` in current folder. 
