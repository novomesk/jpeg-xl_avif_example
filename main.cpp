#include "export_avif.h"
#include "export_jxl.h"
#include "import_avif.h"
#include "import_jxl.h"

#include "exiv_wrapper.h"

#define TESTIMAGE_WIDTH 4128
#define TESTIMAGE_HEIGHT 1860

#define LOGE printf

static uint16_t generated_picture[TESTIMAGE_HEIGHT][TESTIMAGE_WIDTH][3];

int main(int argc, char *argv[])
{
    const int one_third = TESTIMAGE_WIDTH / 3;
    const int two_thirds = 2 * TESTIMAGE_WIDTH / 3;

    for (int y = 0; y < TESTIMAGE_HEIGHT; y++) {
        int x;
        for (x = 0; x < one_third; x++) {
            generated_picture[y][x][0] = 0;
            generated_picture[y][x][1] = 0;
            generated_picture[y][x][2] = 0xffff;
        }
        for (x = one_third; x < two_thirds; x++) {
            generated_picture[y][x][0] = 0xffff;
            generated_picture[y][x][1] = 0xffff;
            generated_picture[y][x][2] = 0;
        }
        for (x = two_thirds; x < TESTIMAGE_WIDTH; x++) {
            generated_picture[y][x][0] = 0xffff;
            generated_picture[y][x][1] = 0;
            generated_picture[y][x][2] = 0;
        }
    }

    Exiv2::Blob blob;
    const uint8_t *metadata_to_save = nullptr;
    size_t metadata_size = 0;

    if (prerare_exif_blob(blob, TESTIMAGE_WIDTH, TESTIMAGE_HEIGHT)) {
        metadata_to_save = blob.data();
        metadata_size = blob.size();
    } else {
        LOGE("No metadata to save");
    }

    save_avif_to_file("output.avif", TESTIMAGE_WIDTH, TESTIMAGE_HEIGHT, generated_picture[0][0], metadata_to_save, metadata_size);

    uint16_t *loaded_pixels = nullptr;
    uint32_t loaded_width = 0;
    uint32_t loaded_height = 0;

    if (load_avif_from_file("output.avif", &loaded_width, &loaded_height, &loaded_pixels)) {
        save_jxl_to_file("output.jxl", loaded_width, loaded_height, loaded_pixels, metadata_to_save, metadata_size);
        delete[] loaded_pixels;
    }

    if (load_jxl_from_file("jpegxl-logo.jxl", &loaded_width, &loaded_height, &loaded_pixels)) {
        save_jxl_to_file("output2.jxl", loaded_width, loaded_height, loaded_pixels, nullptr, 0);
        delete[] loaded_pixels;
    }
    return 0;
}
