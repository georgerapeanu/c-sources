#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include "artclass.h"

#define fail(s, x...) do { \
		fprintf(stderr, s "\n", ## x); \
		exit(1); \
	} while(0)

#ifdef __cplusplus
extern "C" {
#endif

void __grader_init(int dim[2],
        int r[500][500], int g[500][500], int b[500][500]) {
    FILE *fd = fopen("artclass.jpg", "rb");
    if (fd == NULL)
        fail("Failed to open input file (artclass.jpg).");

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_buffer;
    int i, j;

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fd);
    jpeg_read_header(&cinfo, 0);
    jpeg_start_decompress(&cinfo);

    dim[0] = cinfo.output_height;
    dim[1] = cinfo.output_width;

    assert(cinfo.num_components == 3);
    assert(sizeof(JSAMPLE) == 1);

    row_buffer = (JSAMPROW) malloc(sizeof(JSAMPLE) * dim[1] * 3);
    for (j = 0; j < dim[0]; j++) {
        jpeg_read_scanlines(&cinfo, &row_buffer, 1);
        for (i = 0; i < dim[1]; i++) {
              r[j][i] = row_buffer[3*i+0];
              g[j][i] = row_buffer[3*i+1];
              b[j][i] = row_buffer[3*i+2];
        }
    }
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(fd);
}

#ifdef __cplusplus
}
#endif
