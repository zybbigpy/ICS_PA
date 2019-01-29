// #include "common.h"
// #include "string.h"

// typedef struct {
// 	char *name;
// 	uint32_t size;
// 	uint32_t disk_offset;
// } file_info;

// typedef struct {
// 	bool used;
// 	uint32_t index;
// 	uint32_t offset;
// } Fstate;

// enum {SEEK_SET, SEEK_CUR, SEEK_END};

// static const file_info file_table[] = {
// 	{"1.rpg", 188864, 1048576}, {"2.rpg", 188864, 1237440},
// 	{"3.rpg", 188864, 1426304}, {"4.rpg", 188864, 1615168},
// 	{"5.rpg", 188864, 1804032}, {"abc.mkf", 1022564, 1992896},
// 	{"ball.mkf", 134704, 3015460}, {"data.mkf", 66418, 3150164},
// 	{"desc.dat", 16027, 3216582}, {"fbp.mkf", 1128064, 3232609},
// 	{"fire.mkf", 834728, 4360673}, {"f.mkf", 186966, 5195401},
// 	{"gop.mkf", 11530322, 5382367}, {"map.mkf", 1496578, 16912689},
// 	{"mgo.mkf", 1577442, 18409267}, {"m.msg", 188232, 19986709},
// 	{"mus.mkf", 331284, 20174941}, {"pat.mkf", 8488, 20506225},
// 	{"rgm.mkf", 453202, 20514713}, {"rng.mkf", 4546074, 20967915},
// 	{"sss.mkf", 557004, 25513989}, {"voc.mkf", 1997044, 26070993},
// 	{"wor16.asc", 5374, 28068037}, {"wor16.fon", 82306, 28073411},
// 	{"word.dat", 5650, 28155717}, {"credits_bgm.wav", 10067800, 1048576},
// };

// #define NR_FILES (sizeof(file_table) / sizeof(file_table[0]))

// Fstate files[NR_FILES + 3];

// void ide_read(uint8_t *, uint32_t, uint32_t);
// void ide_write(uint8_t *, uint32_t, uint32_t);

// /* Please implement a simple file system here */

// int fs_open(const char *pathname, int flags) {
// 	panic("Please implement fs_open at fs.c");
// 	return -1;
// }

// size_t fs_read(int fd, void *buf, size_t len) {
// 	assert(fd > 2);
// 	panic("Please implement fs_read at fs.c");
// 	return -1;
// }

// size_t fs_write(int fd, void *buf, size_t len) {
// 	assert(fd <= 2);
// #ifdef HAS_DEVICE_SERIAL
// 	int i;
// 	extern void serial_printc(char);
// 	for(i = 0; i < len; i ++) {
// 		serial_printc( ((char *)buf)[i] );
// 	}
// #else
// 	asm volatile(".byte 0x82" : "=a" (len) : "a"(4), "b"(fd), "c"(buf), "d"(len));
// #endif

// 	return len;
// }

// off_t fs_lseek(int fd, off_t offset, int whence) {
// 	panic("Please implement fs_lseek at fs.c");
// 	return -1;
// }

// int fs_close(int fd) {
// 	panic("Please implement fs_close at fs.c");
// 	return -1;
// }


#include "common.h"
#include "string.h"

typedef struct {
	char *name;
	uint32_t size;
	uint32_t disk_offset;
} file_info;

typedef struct {
	bool used;
	uint32_t index;
	uint32_t offset;
} Fstate;

enum {SEEK_SET, SEEK_CUR, SEEK_END};

static const file_info file_table[] = {
	{"1.rpg", 188864, 1048576}, {"2.rpg", 188864, 1237440},
	{"3.rpg", 188864, 1426304}, {"4.rpg", 188864, 1615168},
	{"5.rpg", 188864, 1804032}, {"abc.mkf", 1022564, 1992896},
	{"ball.mkf", 134704, 3015460}, {"data.mkf", 66418, 3150164},
	{"desc.dat", 16027, 3216582}, {"fbp.mkf", 1128064, 3232609},
	{"fire.mkf", 834728, 4360673}, {"f.mkf", 186966, 5195401},
	{"gop.mkf", 11530322, 5382367}, {"map.mkf", 1496578, 16912689},
	{"mgo.mkf", 1577442, 18409267}, {"m.msg", 188232, 19986709},
	{"mus.mkf", 331284, 20174941}, {"pat.mkf", 8488, 20506225},
	{"rgm.mkf", 453202, 20514713}, {"rng.mkf", 4546074, 20967915},
	{"sss.mkf", 557004, 25513989}, {"voc.mkf", 1997044, 26070993},
	{"wor16.asc", 5374, 28068037}, {"wor16.fon", 82306, 28073411},
	{"word.dat", 5650, 28155717}, {"credits_bgm.wav", 10067800, 1048576},
};

#define NR_FILES (sizeof(file_table) / sizeof(file_table[0]))

Fstate files[NR_FILES + 3];

void ide_read(uint8_t *buf, uint32_t offset, uint32_t len);
void ide_write(uint8_t *buf, uint32_t offset, uint32_t len);

/* Please implement a simple file system here */

int fs_open(const char *pathname, int flags) {
	//panic("Please implement fs_open at fs.c");
	int fd = -1;
	int i;
	for(i = 0; i < NR_FILES; i ++) {
		if(strcmp(pathname, file_table[i].name) == 0) {
			fd = i + 3;	//file k uses Fstate[k+3]
			break;
		}
	}
	assert(fd != -1);	//can't find pathname
	assert(files[fd].used == false); //file can't open again
	files[fd].used = true;
	//files[fd].index = file_table[i].disk_offset;
	files[fd].offset = 0;
	return fd;
}

size_t fs_read(int fd, void *buf, size_t len) {
	assert(fd > 2);
	//panic("Please implement fs_read at fs.c");
	/*  if (offset < size) {
			if (offset + len <= size)
				read len byte
			else
				read (size - offset) byte
		}
		else {
			read 0 byte
		}
	*/
	assert(files[fd].used == true);
	uint32_t size = file_table[fd - 3].size;
	if(files[fd].offset < size) { //file pointer in file
		uint32_t start = file_table[fd - 3].disk_offset + files[fd].offset;
		if(files[fd].offset + len > size) {	//read (size - offset) byte
			len = size - files[fd].offset;
		}
		ide_read((uint8_t *)buf, start, len);
		files[fd].offset += len;
		return len;
	}
	else { //file pointer at or past the end of file, read 0 byte
		return 0;
	}
}

size_t fs_write(int fd, void *buf, size_t len) {
	assert(fd <= 2);
#ifdef HAS_DEVICE_SERIAL
	int i;
	extern void serial_printc(char);
	for(i = 0; i < len; i ++) {
		serial_printc( ((char *)buf)[i] );
	}
#else
	asm volatile(".byte 0x82" : "=a" (len) : "a"(4), "b"(fd), "c"(buf), "d"(len));
#endif

	return len;
}

off_t fs_lseek(int fd, off_t offset, int whence) {
	//panic("Please implement fs_lseek at fs.c");
	assert(files[fd].used == true);
	uint32_t size = file_table[fd - 3].size;
	switch(whence) {
		case SEEK_SET:  files[fd].offset = offset;
						assert(files[fd].offset < size);
						break;
		case SEEK_CUR:  files[fd].offset += offset;
						//assert(files[fd].offset < size);
						break;
		case SEEK_END:  files[fd].offset = size + offset;
						//assert(files[fd].offset < size);
						break;
		default: return -1;
	}
	return files[fd].offset;
}

int fs_close(int fd) {
	//panic("Please implement fs_close at fs.c");
	assert(files[fd].used == true);
	files[fd].used = false;
	return 0;
}
